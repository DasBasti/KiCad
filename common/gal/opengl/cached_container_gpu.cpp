/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright 2013-2017 CERN
 * @author Maciej Suminski <maciej.suminski@cern.ch>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include <gal/opengl/cached_container_gpu.h>
#include <gal/opengl/vertex_manager.h>
#include <gal/opengl/vertex_item.h>
#include <gal/opengl/shader.h>
#include <gal/opengl/utils.h>

#include <list>
#include <cassert>

#ifdef __WXDEBUG__
#include <wx/log.h>
#include <profile.h>
#endif /* __WXDEBUG__ */

using namespace KIGFX;

CACHED_CONTAINER_GPU::CACHED_CONTAINER_GPU( unsigned int aSize ) :
    CACHED_CONTAINER( aSize ), m_isMapped( false ), m_glBufferHandle( -1 )
{
    m_useCopyBuffer = GLEW_ARB_copy_buffer;

    glGenBuffers( 1, &m_glBufferHandle );
    glBindBuffer( GL_ARRAY_BUFFER, m_glBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, m_currentSize * VertexSize, NULL, GL_DYNAMIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    checkGlError( "allocating video memory for cached container" );
}


CACHED_CONTAINER_GPU::~CACHED_CONTAINER_GPU()
{
    if( m_isMapped )
        Unmap();

    glDeleteBuffers( 1, &m_glBufferHandle );
}


void CACHED_CONTAINER_GPU::Map()
{
    assert( !IsMapped() );

    glBindBuffer( GL_ARRAY_BUFFER, m_glBufferHandle );
    m_vertices = static_cast<VERTEX*>( glMapBuffer( GL_ARRAY_BUFFER, GL_READ_WRITE ) );
    checkGlError( "mapping vertices buffer" );

    m_isMapped = true;
}


void CACHED_CONTAINER_GPU::Unmap()
{
    assert( IsMapped() );

    glUnmapBuffer( GL_ARRAY_BUFFER );
    checkGlError( "unmapping vertices buffer" );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    m_vertices = NULL;
    checkGlError( "unbinding vertices buffer" );

    m_isMapped = false;
}


bool CACHED_CONTAINER_GPU::defragmentResize( unsigned int aNewSize )
{
    if( !m_useCopyBuffer )
        return defragmentResizeMemcpy( aNewSize );

    assert( IsMapped() );

    wxLogTrace( "GAL_CACHED_CONTAINER_GPU",
            wxT( "Resizing & defragmenting container from %d to %d" ), m_currentSize, aNewSize );

    // No shrinking if we cannot fit all the data
    if( usedSpace() > aNewSize )
        return false;

#ifdef __WXDEBUG__
    PROF_COUNTER totalTime;
#endif /* __WXDEBUG__ */

    GLuint newBuffer;

    // glCopyBufferSubData requires a buffer to be unmapped
    glUnmapBuffer( GL_ARRAY_BUFFER );

    // Create the destination buffer
    glGenBuffers( 1, &newBuffer );

    // It would be best to use GL_COPY_WRITE_BUFFER here,
    // but it is not available everywhere
#ifdef __WXDEBUG__
    GLint eaBuffer = -1;
    glGetIntegerv( GL_ELEMENT_ARRAY_BUFFER_BINDING, &eaBuffer );
    assert( eaBuffer == 0 );
#endif /* __WXDEBUG__ */
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, newBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, aNewSize * VertexSize, NULL, GL_DYNAMIC_DRAW );
    checkGlError( "creating buffer during defragmentation" );

    ITEMS::iterator it, it_end;
    int newOffset = 0;

    // Defragmentation
    for( it = m_items.begin(), it_end = m_items.end(); it != it_end; ++it )
    {
        VERTEX_ITEM* item = *it;
        int itemOffset    = item->GetOffset();
        int itemSize      = item->GetSize();

        // Move an item to the new container
        glCopyBufferSubData( GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER,
                itemOffset * VertexSize, newOffset * VertexSize, itemSize * VertexSize );

        // Update new offset
        item->setOffset( newOffset );

        // Move to the next free space
        newOffset += itemSize;
    }

    // Move the current item and place it at the end
    if( m_item->GetSize() > 0 )
    {
        glCopyBufferSubData( GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER,
                m_item->GetOffset() * VertexSize, newOffset * VertexSize,
                m_item->GetSize() * VertexSize );

        m_item->setOffset( newOffset );
        m_chunkOffset = newOffset;
    }

    // Cleanup
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    // Previously we have unmapped the array buffer, now when it is also
    // unbound, it may be officially marked as unmapped
    m_isMapped = false;
    glDeleteBuffers( 1, &m_glBufferHandle );

    // Switch to the new vertex buffer
    m_glBufferHandle = newBuffer;
    Map();
    checkGlError( "switching buffers during defragmentation" );

#ifdef __WXDEBUG__
    totalTime.Stop();

    wxLogTrace( "GAL_CACHED_CONTAINER_GPU",
                "Defragmented container storing %d vertices / %.1f ms",
                m_currentSize - m_freeSpace, totalTime.msecs() );
#endif /* __WXDEBUG__ */

    m_freeSpace += ( aNewSize - m_currentSize );
    m_currentSize = aNewSize;

    // Now there is only one big chunk of free memory
    m_freeChunks.clear();
    m_freeChunks.insert( std::make_pair( m_freeSpace, m_currentSize - m_freeSpace ) );

    return true;
}


bool CACHED_CONTAINER_GPU::defragmentResizeMemcpy( unsigned int aNewSize )
{
    assert( IsMapped() );

    wxLogTrace( "GAL_CACHED_CONTAINER_GPU",
            wxT( "Resizing & defragmenting container (memcpy) from %d to %d" ),
            m_currentSize, aNewSize );

    // No shrinking if we cannot fit all the data
    if( usedSpace() > aNewSize )
        return false;

#ifdef __WXDEBUG__
    PROF_COUNTER totalTime;
#endif /* __WXDEBUG__ */

    GLuint newBuffer;
    VERTEX* newBufferMem;

    // Create the destination buffer
    glGenBuffers( 1, &newBuffer );

    // It would be best to use GL_COPY_WRITE_BUFFER here,
    // but it is not available everywhere
#ifdef __WXDEBUG__
    GLint eaBuffer = -1;
    glGetIntegerv( GL_ELEMENT_ARRAY_BUFFER_BINDING, &eaBuffer );
    assert( eaBuffer == 0 );
#endif /* __WXDEBUG__ */
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, newBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, aNewSize * VertexSize, NULL, GL_DYNAMIC_DRAW );
    newBufferMem = static_cast<VERTEX*>( glMapBuffer( GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY ) );
    checkGlError( "creating buffer during defragmentation" );

    defragment( newBufferMem );

    // Cleanup
    glUnmapBuffer( GL_ELEMENT_ARRAY_BUFFER );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    Unmap();
    glDeleteBuffers( 1, &m_glBufferHandle );

    // Switch to the new vertex buffer
    m_glBufferHandle = newBuffer;
    Map();
    checkGlError( "switching buffers during defragmentation" );

#ifdef __WXDEBUG__
    totalTime.Stop();

    wxLogTrace( "GAL_CACHED_CONTAINER_GPU",
                "Defragmented container storing %d vertices / %.1f ms",
                m_currentSize - m_freeSpace, totalTime.msecs() );
#endif /* __WXDEBUG__ */

    m_freeSpace += ( aNewSize - m_currentSize );
    m_currentSize = aNewSize;

    // Now there is only one big chunk of free memory
    m_freeChunks.clear();
    m_freeChunks.insert( std::make_pair( m_freeSpace, m_currentSize - m_freeSpace ) );

    return true;
}
