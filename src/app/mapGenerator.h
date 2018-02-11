#pragma once

#include "chunk.h"
#include "perlin.h"
#include <memory>

namespace mc
{
	class MapGenerator
	{
	public:
		MapGenerator(int seed)
			: mSeed(seed)
			, mPerlinNoise(seed)
		{};
		std::unique_ptr<Chunk> generate(int x, int y);
	private:
		int mSeed;
		PerlinNoise mPerlinNoise;
	};
}
