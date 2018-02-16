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
		RayCast(core::Vector<Chunk*> chunks) : mChunks(chunks), mPrecision(0.1f)
		{
			mMatrixSize = std::sqrt(chunks.size());
		}

		glm::vec3* raycast(const CameraData& cameraData, float radius, void(*drawStepPoints)(float, float, float)) const;

	private:
		core::Vector<Chunk*> mChunks;
		float mPrecision;
		int mMatrixSize;
		int mBlockSize = 1;

		float intbound(float s, float ds) const;
		float signum(float x) const;
		float mod(float value, float modulus) const;

		int getWidth() const { return Chunk::WIDTH * mMatrixSize * mBlockSize; }
		int getHeight() const { return Chunk::HEIGHT * mMatrixSize * mBlockSize; }

		Block* getBlock(float _x, float _y, float _z) const {
			auto x = int(_x / mBlockSize);
			auto y = int(_y / mBlockSize);
			auto z = int(_z / mBlockSize);
			return &mChunks[int(z / Chunk::WIDTH) * mMatrixSize + int(x / Chunk::WIDTH)]->getBlock(x % Chunk::WIDTH, y, z % Chunk::WIDTH);
		}

		Chunk* getChunk(float _x, float _y, float _z) const {
			auto x = int(_x / mBlockSize / Chunk::WIDTH);
			auto z = int(_z / mBlockSize / Chunk::WIDTH);
			return mChunks[z * mMatrixSize + x];
		}
	};

}