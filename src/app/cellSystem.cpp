#include "cellSystem.h"

namespace mc {

	Chunk CellSystem::getChunk(int x, int y) {
		core::String key = x + "_" + y;
		if (!mMap.count(key)) {
			Chunk chunk = mGenerator.generate(x, y);
			mMap[key] = chunk;
		}
		return mMap[key];
	}

}
