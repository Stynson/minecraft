#include "mapGenerator.h"

namespace mc {

	Chunk MapGenerator::generate(int x, int y)
	{
		auto chunk = Chunk(x, y);
		for (auto i = 0; i < Chunk::WIDTH; i++) {
			for (auto j = 0; j < Chunk::WIDTH; j++) {
				chunk.setBlock(BlockType::DIRT, i, 0, j);
			}
		}
		return chunk;
	}
}
