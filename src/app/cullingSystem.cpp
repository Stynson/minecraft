#include "cullingSystem.h"

namespace mc {
	core::Vector<Chunk*> CullingSystem::getCulledChunks(float x, float y, float direction, int distance) 
	{
		//auto culledChunks = core::Vector<Chunk>();
		//return culledChunks;
		return mCellSystem.getNearbyChunks((int)x, (int)y, distance);
	}
}