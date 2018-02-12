#include "cellSystem.h"

namespace mc {

	Chunk* CellSystem::getChunk(int x, int z) {
		core::String key = std::to_string(x).c_str();
		key += "_";
		key += std::to_string(z).c_str();
		if (!mMap.count(key)) {
			mMap.insert(std::make_pair(key,std::move(mGenerator.generate(x, z))));
		}
		return mMap[key].get();
	}

	core::Vector<Chunk*> CellSystem::getNearbyChunks(int x, int z, int distance) 
	{
		auto nearbyChunks = core::Vector<Chunk*>(0);
		nearbyChunks.reserve((distance + 1) * (distance + 1));
		for (auto i = x - distance; i <= x + distance; i++) {
			for (auto j = z - distance; j <= z + distance; j++) {
				nearbyChunks.push_back(this->getChunk(i, j));
			}
		}
		return nearbyChunks;
	}

}
