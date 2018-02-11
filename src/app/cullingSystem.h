#pragma once

#include "cellSystem.h"
#include "core.h"

namespace mc {

	class CullingSystem {
	public:
		CullingSystem(CellSystem& cellSystem) : mCellSystem(cellSystem) {}

		core::Vector<Chunk*> getCulledChunks(float x, float y, float direction, int distance) ;

	private:
		CellSystem& mCellSystem;
	};

}