#include "mapGenerator.h"
#include "core.h"
#include "iostream"

namespace mc 
{

	Chunk MapGenerator::generate(int x, int y)
	{
		auto chunk = Chunk();
		for (auto i = 0; i < Chunk::WIDTH; i++)
		{
			for (auto j = 0; j < Chunk::WIDTH; j++) 
			{
				for (auto z = mPerlinNoise.noise(i, j, 0); z > 0; z--)
				{				
					std::cout << "x:" << i << " y:" << j << "\nmagassag:" << z;
					chunk.setBlock(BlockType::DIRT, i, z, j);
				}
			}
		}
		return chunk;
	}
}
