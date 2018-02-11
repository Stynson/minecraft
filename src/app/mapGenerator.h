#pragma once

#include "chunk.h"
#include "perlin.h"

namespace mc
{
	class MapGenerator
	{
	public:
		MapGenerator(int seed)
			: mSeed(seed)
			, mPerlinNoise(seed)
		{};
		Chunk generate(int x, int y);
	private:
		int mSeed;
		PerlinNoise mPerlinNoise;
	};
}
