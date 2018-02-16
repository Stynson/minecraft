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
		RayCast(core::Vector<Chunk*> chunks) : mChunks(chunks), precision(0.1f) {}

		glm::vec3* raycast(const CameraData& cameraData, float radius, void(*drawStepPoints)(float, float, float)) const;

	private:
		core::Vector<Chunk*> mChunks;
		float precision;

		float intbound(float s, float ds) const;
		float signum(float x) const;
		float mod(float value, float modulus) const;

		int getWidth() const { return Chunk::WIDTH * mChunks.size() / 2 * 2; }
		int getHeight() const { return Chunk::HEIGHT * mChunks.size() / 2 * 2; }

		Block* getBlock(float _x, float _y, float _z) const {
			auto x = int(_x / 2);
			auto y = int(_y / 2);
			auto z = int(_z / 2);
			return &mChunks[x / Chunk::WIDTH * mChunks.size() / 2 + z / Chunk::WIDTH]->getBlock(x % Chunk::WIDTH, y, z % Chunk::WIDTH);
		}
	};

}