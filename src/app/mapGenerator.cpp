#include "mapGenerator.h"
#include "core.h"
#include <iostream>

namespace mc
{ 
	std::unique_ptr<Chunk> MapGenerator::generate(int x, int y) const
	{
		auto chunk = std::make_unique<Chunk>(x, y);
		for (auto i = 0; i < Chunk::WIDTH; i++)
		{
			for (auto j = 0; j < Chunk::WIDTH; j++)
			{
				double n = mPerlinNoise.noise(i, j, -0.2);
				n = n - floor(n);
				for (auto z = 0; z < n * 255; z++)
				{
					chunk->setBlock(BlockType::DIRT, i, z, j);
				}
			}
		}
		return std::move(chunk);
	}
}
