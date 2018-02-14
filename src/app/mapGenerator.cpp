#include "mapGenerator.h"
#include "core.h"
#include <iostream>
#include <cmath>

namespace mc
{ 
	std::unique_ptr<Chunk> MapGenerator::generate(int x, int z) const
	{
		auto chunk = std::make_unique<Chunk>(x, z);
		for (auto i = 0; i < Chunk::WIDTH; i++)
		{
			for (auto j = 0; j < Chunk::WIDTH; j++)
			{
				double height = mPerlinNoise.noise(chunk->getX() + i, chunk->getZ() + j, -0.2);
				height -= floor(height);
				height *= Chunk::HEIGHT;
				for (auto y = 0; y < height; y++)
				{
					chunk->setBlockType(BlockType::DIRT, i, y, j);
				}
			}
		}
		return std::move(chunk);
	}
}
