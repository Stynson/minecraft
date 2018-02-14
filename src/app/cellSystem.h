#pragma once

#include "chunk.h"
#include "mapGenerator.h"
#include "cameraData.h"
#include <map>
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

	private:
		core::Map<core::String, std::unique_ptr<Chunk>> mMap;
		MapGenerator mGenerator;

	};

}
