#include "cellSystem.h"

namespace mc {

	Chunk CellSystem::getChunk(int x, int y) {
		core::String key = x + "_" + y;
		if (!mMap.count(key)) {
			Chunk chunk = mGenerator.generate(x, y);
			mMap[key] = chunk;
		}
		return mMap[key];
	}

	core::Vector<Chunk> CellSystem::getNearbyChunks(int x, int y, int distance)
	{
		auto nearbyChunks = core::Vector<Chunk>();
		for (auto i = x - distance; i <= x + distance; i++) {
			for (auto j = y - distance; j <= y + distance; j++) {
				nearbyChunks.push_back(this->getChunk(i, j));
			}
		}
		return nearbyChunks;
	}

}
