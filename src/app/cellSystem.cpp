#include "cellSystem.h"

namespace mc {

	Chunk* CellSystem::getChunk(int x, int z) {
		core::String key = std::to_string(x).c_str();
		key += "_";
		key += std::to_string(z).c_str();
		auto it = mMap.find(key);
		if (it == mMap.end())
		{
			return mMap.insert(it, std::make_pair(key, std::move(mGenerator.generate(x, z))))->second.get(); 
		}
		return it->second.get();
	}

	core::Vector<Chunk*> CellSystem::getNearbyChunks(const CameraData& cameraData) {
		return getNearbyChunks(cameraData, cameraData.viewDistance); 
	}

	core::Vector<Chunk*> CellSystem::getNearbyChunks(const CameraData& cameraData, int distance)
	{
		int offset = cameraData.chunkSize * cameraData.blockSize;
		auto chunkCoord = core::worldCoordToChunkCoord(cameraData.pos, offset);
		auto nearbyChunks = core::Vector<Chunk*>(0);
		nearbyChunks.reserve((distance + 1) * (distance + 1));
		for (auto j = chunkCoord.z - distance; j <= chunkCoord.z + distance; j++) {
			for (auto i = chunkCoord.x - distance; i <= chunkCoord.x + distance; i++) {
				nearbyChunks.push_back(this->getChunk(i, j));
			}
		}
		return nearbyChunks;
	}

	void CellSystem::setBlockType(BlockType type, glm::vec3 worldCoord)
	{
		int offset = Chunk::WIDTH * 1;
		auto chunkCoord = core::worldCoordToChunkCoord(worldCoord, offset);
		Chunk* currentChunk = getChunk(chunkCoord.x, chunkCoord.z);

		auto blockCoord = core::worldCoordToBlockCoord(worldCoord, offset);
		currentChunk->setBlockType(type, blockCoord.x, blockCoord.y, blockCoord.z);
	}

}
