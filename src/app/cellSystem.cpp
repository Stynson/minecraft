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
		int x = std::floor(cameraData.pos.x / offset);
		int z = std::floor(cameraData.pos.z / offset);
		auto nearbyChunks = core::Vector<Chunk*>(0);
		nearbyChunks.reserve((distance + 1) * (distance + 1));
		for (auto j = z - distance; j <= z + distance; j++) {
			for (auto i = x - distance; i <= x + distance; i++) {
				nearbyChunks.push_back(this->getChunk(i, j));
			}
		}
		return nearbyChunks;
	}

	void CellSystem::setBlockType(BlockType type, glm::vec3 worldCoord)
	{
		int offset = Chunk::WIDTH * 1;
		int chunkX = std::floor(worldCoord.x / offset);
		int chunkZ = std::floor(worldCoord.z / offset);
		Chunk* currentChunk = getChunk(chunkX, chunkZ);

		auto blockX = worldCoord.x;
		auto blockZ = worldCoord.z;
		while (blockX > Chunk::WIDTH) blockX -= Chunk::WIDTH;
		while (blockX < Chunk::WIDTH) blockX += Chunk::WIDTH;
		while (blockZ > Chunk::WIDTH) blockZ -= Chunk::WIDTH;
		while (blockZ < Chunk::WIDTH) blockZ += Chunk::WIDTH;
		blockX = std::floor(std::fmod(blockX, offset));
		blockZ = std::floor(std::fmod(blockZ, offset));
		currentChunk->setBlockType(type, blockX, worldCoord.y, blockZ);
	}

}
