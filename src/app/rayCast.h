#pragma once

#include "core.h"
#include "chunk.h"
#include "cameraData.h"

#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mc
{

	class RayCast {
	public:
		struct RayCastResult {
			glm::vec3 blockCoord;
			glm::vec3 face;
			bool selected = false;

			RayCastResult(){};
			RayCastResult(glm::vec3 _coord, glm::vec3 _face) : blockCoord(_coord), face(_face), selected(true) {};
		};

		RayCast(core::Vector<Chunk*> chunks) : mChunks(chunks), mPrecision(0.1f)
		{
			mMatrixSize = static_cast<int>(std::sqrt(chunks.size()));
		}

		RayCast::RayCastResult raycast(const CameraData& cameraData, float radius, void(*drawStepPoints)(float, float, float)) const;

	private:
		core::Vector<Chunk*> mChunks;
		float mPrecision;
		int mMatrixSize;
		int mBlockSize = 1;

		float intbound(float s, float ds) const;
		float signum(float x) const;
		float mod(float value, float modulus) const;

		int getWidth() const { return Chunk::WIDTH * mMatrixSize * mBlockSize; }
		int getHeight() const { return Chunk::HEIGHT * mBlockSize; }

		Block* getBlock(glm::vec3 worldCoord) const {
			auto coord = core::worldCoordToBlockCoord(worldCoord, mBlockSize * Chunk::WIDTH);
			return &getChunk(worldCoord)->getBlock(coord.x, coord.y, coord.z);
		}

		Chunk* getChunk(glm::vec3 worldCoord) const {
			auto offset = mBlockSize * Chunk::WIDTH;
			auto coord = core::worldCoordToChunkCoord(worldCoord, offset);
			return mChunks[coord.z * mMatrixSize + coord.x];
		}
	};

}