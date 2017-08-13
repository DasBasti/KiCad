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

#ifndef CACHED_CONTAINER_H_
#define CACHED_CONTAINER_H_

#include <gal/opengl/vertex_container.h>
#include <map>
#include <set>

namespace KIGFX
{
class VERTEX_ITEM;
class SHADER;

/**
 * @brief Class to store VERTEX instances with caching. It associates VERTEX
 * objects and with VERTEX_ITEMs. Caching vertices data in the memory and a
 * enables fast reuse of that data.
 */

class CACHED_CONTAINER : public VERTEX_CONTAINER
{
public:
    CACHED_CONTAINER( unsigned int aSize = DEFAULT_SIZE );
    virtual ~CACHED_CONTAINER() {}

    bool IsCached() const override
    {
        return true;
    }

    ///> @copydoc VERTEX_CONTAINER::SetItem()
    virtual void SetItem( VERTEX_ITEM* aItem ) override;

    ///> @copydoc VERTEX_CONTAINER::FinishItem()
    virtual void FinishItem() override;

    ///> @copydoc VERTEX_CONTAINER::Allocate()
    virtual VERTEX* Allocate( unsigned int aSize ) override;

    ///> @copydoc VERTEX_CONTAINER::Delete()
    virtual void Delete( VERTEX_ITEM* aItem ) override;

    ///> @copydoc VERTEX_CONTAINER::Clear()
    virtual void Clear() override;

    /**
     * Function GetBufferHandle()
     * returns handle to the vertex buffer. It might be negative if the buffer is not initialized.
     */
    virtual unsigned int GetBufferHandle() const = 0;

    /**
     * Function IsMapped()
     * returns true if vertex buffer is currently mapped.
     */
    virtual bool IsMapped() const = 0;

    ///> @copydoc VERTEX_CONTAINER::Map()
    virtual void Map() override = 0;

    ///> @copydoc VERTEX_CONTAINER::Unmap()
    virtual void Unmap() override = 0;

protected:
    ///> Maps size of free memory chunks to their offsets
    typedef std::pair<unsigned int, unsigned int> CHUNK;
    typedef std::multimap<unsigned int, unsigned int> FREE_CHUNK_MAP;

    /// List of all the stored items
    typedef std::set<VERTEX_ITEM*> ITEMS;

    ///> Stores size & offset of free chunks.
    FREE_CHUNK_MAP      m_freeChunks;

    ///> Stored VERTEX_ITEMs
    ITEMS               m_items;

    ///> Currently modified item
    VERTEX_ITEM*        m_item;

    ///> Properties of currently modified chunk & item
    unsigned int        m_chunkSize;
    unsigned int        m_chunkOffset;

    /**
     * Function reallocate()
     * resizes the chunk that stores the current item to the given size. The current item has
     * its offset adjusted after the call, and the new chunk parameters are stored
     * in m_chunkOffset and m_chunkSize.
     *
     * @param aSize is the requested chunk size.
     * @return true in case of success, false otherwise
     */
    bool reallocate( unsigned int aSize );

    /**
     * Function defragmentResize()
     * removes empty spaces between chunks and optionally resizes the container.
     * After the operation there is continous space for storing vertices at the end of the container.
     *
     * @param aNewSize is the new size of container, expressed in number of vertices
     * @return false in case of failure (e.g. memory shortage)
     */
    virtual bool defragmentResize( unsigned int aNewSize ) = 0;

    /**
     * Transfers all stored data to a new buffer, removing empty spaces between the data chunks
     * in the container.
     * @param aTarget is the destination for the defragmented data.
     */
    void defragment( VERTEX* aTarget );

    /**
     * Function mergeFreeChunks()
     * looks for consecutive free memory chunks and merges them, decreasing fragmentation of
     * memory.
     */
    void mergeFreeChunks();

    /**
     * Function getChunkSize()
     * returns size of the given chunk.
     *
     * @param aChunk is the chunk.
     */
    inline int getChunkSize( const CHUNK& aChunk ) const
    {
        return aChunk.first;
    }

    /**
     * Function getChunkOffset()
     * returns offset of the chunk.
     *
     * @param aChunk is the chunk.
     */
    inline unsigned int getChunkOffset( const CHUNK& aChunk ) const
    {
        return aChunk.second;
    }

    /**
     * Function addFreeChunk
     * Adds a chunk marked as free.
     */
    void addFreeChunk( unsigned int aOffset, unsigned int aSize );

private:
    /// Debug & test functions
    void showFreeChunks();
    void showUsedChunks();
    void test();
};
} // namespace KIGFX

#endif /* CACHED_CONTAINER_H_ */
