#include "mapGenerator.h"
#include "core.h"
#include <iostream>
#include <cmath>

namespace mc
{ 
	std::unique_ptr<Chunk> MapGenerator::generate(int x, int z) const
	{
		auto chunk = std::make_unique<Chunk>(x, z);
		double height;
		for (auto i = 0; i < Chunk::WIDTH; i++)
		{
			for (auto j = 0; j < Chunk::WIDTH; j++)
			{
				height = mPerlinNoise.noise(chunk->getX() + i, chunk->getZ() + j, -0.2);
				height -= floor(height);
				height *= Chunk::HEIGHT;
				for (auto y = 0; y < height - 1; y++)
				{
					chunk->setBlockType(BlockType::DIRT, i, y, j);
				}
				chunk->setBlockType(BlockType::GRASS_DIRT, i, height, j);
			}
		}
		if (rand() % 3 == 1)
		{
			int i = rand() % Chunk::WIDTH;
			int j = rand() % Chunk::WIDTH;

			if (i - 3 < 0 || j - 3 < 0 || i + 3 > 15 || j + 3 > 15)
			{
				i = 5;
				j = 5;
			}
			for (int z = 0; chunk->getBlock(i, z, j).type != BlockType::AIR; z++)
			{
				height = z;
			}

			for (int z = height; z < height + 5; z++)
			{
				chunk->setBlockType(BlockType::TREE, i, z, j);
			}
			for (; height + 5 < 15; height++)
			{
				for (int z = i-2 ; z < i+3; z++)
				{
					for (int q = j-2; q < j+3; q++)
					{
						chunk->setBlockType(BlockType::LEAF, z, height + 5, q);
					}
				}
			}
		}
	
		return std::move(chunk);
	}
}
