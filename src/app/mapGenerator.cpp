#include "mapGenerator.h"
#include "core.h"
#include <iostream>

namespace mc {

	Chunk MapGenerator::generate(int x, int y)
	{
		auto chunk = Chunk(x, y);
		for (auto i = 0; i < Chunk::WIDTH; i++) {
			for (auto j = 0; j < Chunk::WIDTH; j++) {
				//for (auto z = std::rand() % 100; z > 0; z--)
				//{
					//LOG("x:" << i << " y:" << j << "\nmagassag:" << z);
					chunk.setBlock(BlockType::DIRT, i, 0, j);
				//}
			}
		}
		return chunk;
	}
}
