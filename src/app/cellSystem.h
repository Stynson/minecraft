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

	private:
		std::unordered_map<core::String, std::unique_ptr<Chunk>> mMap;
		MapGenerator mGenerator;

	};

}
