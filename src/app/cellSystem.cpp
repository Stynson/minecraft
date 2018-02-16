#include "cellSystem.h"

namespace mc {

	Chunk* CellSystem::getChunk(int x, int z) {
		core::String key = std::to_string(x).c_str();
		key += "_";
		key += std::to_string(z).c_str();
		auto it = mMap.find(key);
		if (it == mMap.end())
		{
			mMap.insert(it, std::make_pair(key, std::move(mGenerator.generate(x, z))));
		}
		return mMap[key].get();
	}

	core::Vector<Chunk*> CellSystem::getNearbyChunks(const CameraData& cameraData) {
		auto distance = cameraData.viewDistance;
		return getNearbyChunks(cameraData, distance);

	}

	core::Vector<Chunk*> CellSystem::getNearbyChunks(const CameraData& cameraData, int distance)
	{
		int offset = cameraData.chunkSize * cameraData.blockSize;
		int x = cameraData.pos.x / offset;
		int z = cameraData.pos.z / offset;
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
