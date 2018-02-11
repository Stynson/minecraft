#include "chunk.h"

namespace mc {

	Block Chunk::getBlock(uint8_t x, uint8_t y, uint8_t z) {
		return mData[(y * WIDTH * WIDTH) + (z * WIDTH) + x];
	}

	void Chunk::setBlock(Block block, uint8_t x, uint8_t y, uint8_t z) {
		mData[(y * WIDTH * WIDTH) + (z * WIDTH) + x] = block;
	}

}
