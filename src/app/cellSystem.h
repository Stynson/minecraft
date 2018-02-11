#pragma once

#include "chunk.h"
#include "mapGenerator.h"
#include <map>

namespace mc {

	class CellSystem {
	public:
		CellSystem(MapGenerator generator) : mGenerator(generator) {};
		Chunk getChunk(int x, int y);

	private:
		std::map<std::string, Chunk> mMap;
		MapGenerator mGenerator;

	};

}
