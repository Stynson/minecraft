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
				double n = mPerlinNoise.noise(chunk->getX() + i, chunk->getY() + j, -0.2);
				n -= floor(n);
				n *= Chunk::HEIGHT;
				for (auto z = 0; z < n; z++)
				{
					chunk->setBlockType(BlockType::DIRT, i, z, j);
				}
			}
		}
		return std::move(chunk);
	}
}
