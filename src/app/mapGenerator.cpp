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
		generateTrees(*chunk);
		return std::move(chunk);
	}

	void MapGenerator::generateTrees(Chunk& chunk) const
	{
		if (rand() % 1 == 0)
		{
			int i = rand() % Chunk::WIDTH;
			int j = rand() % Chunk::WIDTH;

			if (i - 3 < 0 || j - 3 < 0 || i + 3 > 15 || j + 3 > 15)
			{
				i = 5;
				j = 5;
			}
			double height;
			for (int z = 0; chunk.getBlock(i, z, j).type != BlockType::AIR; z++)
			{
				height = z;
			}

			for (int z = height; z < height + 5; z++)
			{
				chunk.setBlockType(BlockType::TREE, i, z, j);
			}
			int decrease = 3;
			int increase = 4;
			for (; height + 5 < Chunk::HEIGHT; height++)
			{
				for (int z = i - decrease; z < i + decrease + 1; z++)
				{
					for (int q = j - decrease; q < j + decrease + 1; q++)
					{
						chunk.setBlockType(BlockType::LEAF, z, height + 5, q);
					}
				}
				decrease--;
			}
		}

	}
}
