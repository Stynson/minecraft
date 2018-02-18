#pragma once

#include "chunk.h"
#include "mapGenerator.h"
#include "cameraData.h"
#include <unordered_map>
#include "core.h"
#include <memory>

namespace mc {

	class CellSystem {
	public:
		CellSystem(MapGenerator generator)
			: mGenerator(generator)
		{
		};
		Chunk* getChunk(int x, int z) ;
		core::Vector<Chunk*> getNearbyChunks(const CameraData& cameraData);
		core::Vector<Chunk*> getNearbyChunks(const CameraData& cameraData, int distance);

		void setBlock(glm::vec3 coords, BlockType toType)
		{ 
			auto chunk = getChunk(coords.x, coords.y, coords.z);
			auto x = int(coords.x / mBlockSize) % Chunk::WIDTH;
			auto y = int(coords.y / mBlockSize);
			auto z = int(coords.z / mBlockSize) % Chunk::WIDTH;
			chunk->setBlockType(toType, x, y, z);
		}


	private:
		const int mBlockSize = 1;

		Chunk* getChunk(float _x, float _y, float _z) const {
			auto x = int(_x / mBlockSize / Chunk::WIDTH);
			auto z = int(_z / mBlockSize / Chunk::WIDTH);
			core::String key = std::to_string(x).c_str();
			key += "_";
			key += std::to_string(z).c_str();
			return mMap.find(key)->second.get();
		}
		std::unordered_map<core::String, std::unique_ptr<Chunk>> mMap;
		MapGenerator mGenerator;

	};

}
