#pragma once

#include <chunk.h>

namespace mc {
	class MapGenerator {
	public:
		MapGenerator(int seed) : mSeed(seed) {};
		Chunk generate(int x, int y);
	private:
		int mSeed;
	};

}
