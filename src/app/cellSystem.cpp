#include "cellSystem.h"

namespace mc {

	Chunk* CellSystem::getChunk(int x, int y) {
		core::String key = std::to_string(x).c_str();
		key += "_";
		key += std::to_string(y).c_str();
		if (!mMap.count(key)) {
			mMap.insert(std::make_pair(key,std::move(mGenerator.generate(x, y))));
		}
		return mMap[key].get();
	}

	core::Vector<Chunk*> CellSystem::getNearbyChunks(int x, int y, int distance) 
	{
		auto nearbyChunks = core::Vector<Chunk*>(0);
		nearbyChunks.reserve((distance + 1) * (distance + 1));
		for (auto i = x - distance; i <= x + distance; i++) {
			for (auto j = y - distance; j <= y + distance; j++) {
				nearbyChunks.push_back(this->getChunk(i, j));
			}
		}
		return nearbyChunks;
	}

}
