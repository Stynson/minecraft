#include "cullingSystem.h"

namespace mc {
	core::Vector<Chunk*> CullingSystem::getCulledChunks(float x, float z, float direction, int distance) 
	{
		//auto culledChunks = core::Vector<Chunk>();
		//return culledChunks;
		return mCellSystem.getNearbyChunks((int)x, (int)z, distance);
	}
}