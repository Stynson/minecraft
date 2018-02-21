#include "mapGenerator.h"
#include "core.h"
#include <iostream>
#include <cmath>
#include <numeric>

namespace mc
{

	static int num = 4;

	std::unique_ptr<Chunk> MapGenerator::generate(int x, int z) const
	{
		auto chunk = std::make_unique<Chunk>(x, z);
		for (auto i = 0; i < Chunk::WIDTH / num; i++)
		{
			for (auto j = 0; j < Chunk::WIDTH / num; j++)
			{
				core::Vector<float> heights(num*num);
				for (int k = 0; k < num*num; k++)
				{
					heights.push_back(mPerlinNoise.noise((chunk->getX() + i * num) + k / num, (chunk->getZ() + j * num) + k % num, 0.8));
				}
				float average = std::accumulate(heights.begin(), heights.end(), 0.0) / heights.size();
				average -= floor(average);
				average *= Chunk::HEIGHT;
				if (average < 8)
				{
					for (auto l = (i*num); l < (i * num + num); l++)
					{
						for (auto m = (j * num); m < (j * num + num); m++)
						{
							//height = mPerlinNoise.noise(chunk->getX() + l, chunk->getZ() + m, -0.2);
							//height -= floor(height);
							for (auto y = 0; y < average; y++)
							{
								chunk->setBlockType(BlockType::WATER, l, y, m);
							}
							//chunk->setBlockType(BlockType::GRASS_DIRT, l, average, m);
						}
					}
				}
				else
				{
					for (auto l = (i*num); l < (i * num + num); l++)
					{
						for (auto m = (j * num); m < (j * num + num); m++)
						{
							//height = mPerlinNoise.noise(chunk->getX() + l, chunk->getZ() + m, -0.2);
							//height -= floor(height);
							for (auto y = 0; y < average - 1; y++)
							{
								chunk->setBlockType(BlockType::DIRT, l, y, m);
							}
							chunk->setBlockType(BlockType::GRASS_DIRT, l, average, m);
						}
					}
				}
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
			int height;
			for (int z = 0; chunk.getBlock(i, z, j).type != BlockType::AIR; z++)
			{
				height = z;
			}

			for (int z = height; z < height + 5; z++)
			{
				chunk.setBlockType(BlockType::TREE, i, z, j);
			}
			int decrease = 2;
			int increase = 5;
			for (int iter = 0; iter < 2; iter++)
			{
				for (int z = i - decrease; z < i + decrease + 1; z++)
				{
					for (int q = j - decrease; q < j + decrease + 1; q++)
					{
						chunk.setBlockType(BlockType::LEAF, z, height + 5, q);
					}
				}
					//decrease--;
				height++;
			}
			for (int z = i - (--decrease); z < i + decrease + 1; z++)
			{
				for (int q = j - decrease; q < j + decrease + 1; q++)
				{
					chunk.setBlockType(BlockType::LEAF, z, height + 5, q);
				}
			}
			chunk.setBlockType(BlockType::LEAF, i - decrease + 1, height + 6, j - decrease);
			chunk.setBlockType(BlockType::LEAF, i - decrease, height + 6, j - decrease + 1);
			chunk.setBlockType(BlockType::LEAF, i - decrease + 1, height + 6, j - decrease + 2);
			chunk.setBlockType(BlockType::LEAF, i - decrease + 2, height + 6, j - decrease + 1);
			chunk.setBlockType(BlockType::LEAF, i, height + 6, j);
			for (int z = height; z < height + 6; z++)
			{
				chunk.setBlockType(BlockType::TREE, i, z, j);
			}

		}

	}
}
