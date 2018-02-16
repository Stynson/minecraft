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

		glm::vec3* raycast(const CameraData& cameraData, float radius, void(*drawStepPoints)(float, float, float)) {
			// From "A Fast Voxel Traversal Algorithm for Ray Tracing"
			// by John Amanatides and Andrew Woo, 1987
			// <http://www.cse.yorku.ca/~amana/research/grid.pdf>
			// <http://citeseer.ist.psu.edu/viewdoc/summary?doi=10.1.1.42.3443>
			// Extensions to the described algorithm:
			//   • Imposed a distance limit.
			//   • The face passed through to reach the current cube is provided to
			//     the callback.

			// The foundation of this algorithm is a parameterized representation of
			// the provided ray,
			//                    cameraPos + t * direction,
			// except that t is not actually stored; rather, at any given point in the
			// traversal, we keep track of the *greater* t values which we would have
			// if we took a step sufficient to cross a cube boundary along that axis
			// (i.e. change the integer part of the coordinate) in the variables
			// tMaxX, tMaxY, and tMaxZ.

			
			glm::vec3 direction = glm::normalize(cameraData.lookAt - cameraData.pos);
			auto cameraPos = cameraData.pos;
			if (cameraPos.x > 0) while (cameraPos.x > Chunk::WIDTH) cameraPos.x -= Chunk::WIDTH;
			else while (cameraPos.x < 0) cameraPos.x += Chunk::WIDTH;

			if (cameraPos.y > 0) while (cameraPos.y > Chunk::HEIGHT) cameraPos.y -= Chunk::HEIGHT;
			else while (cameraPos.y < 0) cameraPos.y += Chunk::HEIGHT;

			if (cameraPos.z > 0) while (cameraPos.z > Chunk::WIDTH) cameraPos.z -= Chunk::WIDTH;
			else while (cameraPos.z < 0) cameraPos.z += Chunk::WIDTH;

			// Direction to increment x,y,z when stepping.
			auto step = glm::vec3(
				signum(direction.x)
				, signum(direction.y)
				, signum(direction.z));
			// See description above. The initial values depend on the fractional
			// part of the cameraPos.
			auto tMax = glm::vec3(
				intbound(cameraPos[0], direction.x)
				, intbound(cameraPos[1], direction.y)
				, intbound(cameraPos[2], direction.z));
			// The change in t when taking a step (always positive).
			auto tDelta = glm::vec3(
				step.x / direction.x / precision
				, step.y / direction.y / precision
				, step.z / direction.z / precision);

			// Avoids an infinite loop.
			//if (dx === 0 && dy == = 0 && dz === 0)
			//	throw new RangeError("Raycast in zero direction!");

			// Rescale from units of 1 cube-edge to units of 'direction' so we can
			// compare with 't'.
			radius /= precision;
			radius /= std::sqrt(direction.x*direction.x + direction.y * direction.y + direction.z * direction.z);

			while (/* ray has not gone past bounds of world */
				(step.x > 0 ? cameraPos.x < getWidth() : cameraPos.x >= 0) &&
				(step.y > 0 ? cameraPos.y < getHeight() : cameraPos.y >= 0) &&
				(step.z > 0 ? cameraPos.z < getWidth() : cameraPos.z >= 0)) {

				drawStepPoints(cameraPos.x, cameraPos.y, cameraPos.z);

				// Invoke the callback, unless we are not *yet* within the bounds of the
				// world.
				if (!(
					cameraPos.x < 0
					|| cameraPos.y < 0
					|| cameraPos.z < 0
					|| cameraPos.x >= getWidth()
					|| cameraPos.y >= getHeight()
					|| cameraPos.z >= getWidth())
					)
				{
					if (int(getBlock(cameraPos.x, cameraPos.y, cameraPos.z)->type) > 0)
					{
						return &glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z);
					}
				}
				// tMaxX stores the t-value at which we cross a cube boundary along the
				// X axis, and similarly for Y and Z. Therefore, choosing the least tMax
				// chooses the closest cube boundary. Only the first case of the four
				// has been commented in detail.
				if (tMax.x < tMax.y)
				{
					if (tMax.x < tMax.z)
					{
						if (tMax.x > radius) break;
						// Update which cube we are now in.
						cameraPos.x += step.x;
						// Adjust tMaxX to the next X-oriented boundary crossing.
						tMax.x += tDelta.x;
					}
					else
					{
						if (tMax.z > radius) break;
						cameraPos.z += step.z;
						tMax.z += tDelta.z;
					}
				}
				else
				{
					if (tMax.y < tMax.z)
					{
						if (tMax.y > radius) break;
						cameraPos.y += step.y;
						tMax.y += tDelta.y;
					}
					else
					{
						// Identical to the second case, repeated for simplicity in
						// the conditionals.
						if (tMax.z > radius) break;
						cameraPos.z += step.z;
						tMax.z += tDelta.z;
					}
				}
			}
			return nullptr;
		}

		float intbound(float s, float ds) {
			// Find the smallest positive t such that s+t*ds is an integer.
			if (ds < 0) {
				return intbound(-s, -ds);
			}
			else
			{
				s = mod(s, 1);
				// problem is now s+t*ds = 1
				return (1 - s) / ds;
			}
		}

		float signum(float x) {
			return x > 0 ? precision : x < 0 ? -precision : 0.0f;
		}

		float mod(float value, float modulus) {
			return std::fmod(std::fmod(value, modulus) + modulus, modulus);
		}

		int getWidth() { return Chunk::WIDTH * mChunks.size() / 2 * 2; }
		int getHeight() { return Chunk::HEIGHT * mChunks.size() / 2 * 2; }

		Block* getBlock(float _x, float _y, float _z) {
			auto x = int(_x / 2);
			auto y = int(_y / 2);
			auto z = int(_z / 2);
			return &mChunks[x / Chunk::WIDTH * mChunks.size() / 2 + z / Chunk::WIDTH]->getBlock(x % Chunk::WIDTH, y, z % Chunk::WIDTH);
		}

	private:
		core::Vector<Chunk*> mChunks;
		float precision;
	};

}