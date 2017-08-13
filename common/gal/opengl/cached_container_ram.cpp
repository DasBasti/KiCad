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

#include <gal/opengl/cached_container_ram.h>
#include <gal/opengl/vertex_manager.h>
#include <gal/opengl/vertex_item.h>
#include <gal/opengl/shader.h>
#include <gal/opengl/utils.h>

#include <confirm.h>
#include <list>
#include <cassert>

#ifdef __WXDEBUG__
#include <wx/log.h>
#include <profile.h>
#endif /* __WXDEBUG__ */

using namespace KIGFX;

CACHED_CONTAINER_RAM::CACHED_CONTAINER_RAM( unsigned int aSize ) :
    CACHED_CONTAINER( aSize ), m_verticesBuffer( 0 )
{
    glGenBuffers( 1, &m_verticesBuffer );
    checkGlError( "generating vertices buffer" );

    m_vertices = static_cast<VERTEX*>( malloc( aSize * VertexSize ) );
}


CACHED_CONTAINER_RAM::~CACHED_CONTAINER_RAM()
{
    glDeleteBuffers( 1, &m_verticesBuffer );
    free( m_vertices );
}


void CACHED_CONTAINER_RAM::Unmap()
{
    if( !m_dirty )
        return;

    // Upload vertices coordinates and shader types to GPU memory
    glBindBuffer( GL_ARRAY_BUFFER, m_verticesBuffer );
    checkGlError( "binding vertices buffer" );
    glBufferData( GL_ARRAY_BUFFER, usedSpace() * VertexSize, m_vertices, GL_STREAM_DRAW );
    checkGlError( "transferring vertices" );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    checkGlError( "unbinding vertices buffer" );
}


bool CACHED_CONTAINER_RAM::defragmentResize( unsigned int aNewSize )
{
    wxLogTrace( "GAL_CACHED_CONTAINER",
            wxT( "Resizing & defragmenting container (memcpy) from %d to %d" ),
            m_currentSize, aNewSize );

    // No shrinking if we cannot fit all the data
    if( usedSpace() > aNewSize )
        return false;

#ifdef __WXDEBUG__
    PROF_COUNTER totalTime;
#endif /* __WXDEBUG__ */

    VERTEX* newBufferMem = static_cast<VERTEX*>( malloc( aNewSize * VertexSize ) );

    if( !newBufferMem )
        return false;

    defragment( newBufferMem );

    // Switch to the new vertex buffer
    free( m_vertices );
    m_vertices = newBufferMem;

#ifdef __WXDEBUG__
    totalTime.Stop();

    wxLogTrace( "GAL_CACHED_CONTAINER",
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
