#include "chunk.h"

namespace mc
{

    size_t Chunk::idAt(uint8_t x, uint8_t y, uint8_t z) const
    {
        return (y * WIDTH * WIDTH) + (z * WIDTH) + x;
    }

	Block Chunk::getBlock(uint8_t x, uint8_t y, uint8_t z) const
    {
		return mData[idAt(x,y,z)];
	}

	void Chunk::setBlockType(BlockType type, uint8_t x, uint8_t y, uint8_t z)
    {
		mData[idAt(x,y,z)].type = type;
		++mVersion; //TODO mikor betoltjuk/setupoljuk a chunkot kurva sok ilyet hivunk, ehelyett 1 versiont eleg novelni olyankor
	}

}
