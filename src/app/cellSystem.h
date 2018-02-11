#pragma once

#include "chunk.h"
#include "mapGenerator.h"
#include <map>
#include "core.h"

namespace mc {

	class CellSystem {
	public:
		CellSystem(MapGenerator generator) : mGenerator(generator) {};
		Chunk getChunk(int x, int y);
		core::Vector<Chunk> getNearbyChunks(int x, int y, int distance);

	private:
		core::Map<core::String, Chunk> mMap;
		MapGenerator mGenerator;

	};

}
