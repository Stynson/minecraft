#include "chunk.h"

namespace mc {

	Block Chunk::getBlock(uint8_t x, uint8_t y, uint8_t z) const {
		return mData[(y * WIDTH * WIDTH) + (z * WIDTH) + x];
	}

	void Chunk::setBlockType(BlockType type, uint8_t x, uint8_t y, uint8_t z) {
		int id = (y * WIDTH * WIDTH) + (z * WIDTH) + x;
		mData[id].type = type;
		++mVersion; //TODO mikor betoltjuk/setupoljuk a chunkot kurva sok ilyet hivunk, ehelyett 1 versiont eleg novelni olyankor
	}

}
