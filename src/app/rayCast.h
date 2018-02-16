#pragma once

#include "core.h"
#include "chunk.h"

#include <cmath>
#include <glm/vec3.hpp>

namespace mc
{

	class RayCast {
	public:
		RayCast(core::Vector<Chunk*> chunks) : mChunks(chunks) {}

		glm::vec3* raycast(glm::vec3 origin, glm::vec3 direction, float radius) {
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
			//                    origin + t * direction,
			// except that t is not actually stored; rather, at any given point in the
			// traversal, we keep track of the *greater* t values which we would have
			// if we took a step sufficient to cross a cube boundary along that axis
			// (i.e. change the integer part of the coordinate) in the variables
			// tMaxX, tMaxY, and tMaxZ.

			// Cube containing origin point.
			auto x = std::floor(origin[0]);
			auto y = std::floor(origin[1]);
			auto z = std::floor(origin[2]);
			// Break out direction vector.
			auto dx = direction[0];
			auto dy = direction[1];
			auto dz = direction[2];
			// Direction to increment x,y,z when stepping.
			auto stepX = signum(dx);
			auto stepY = signum(dy);
			auto stepZ = signum(dz);
			// See description above. The initial values depend on the fractional
			// part of the origin.
			auto tMaxX = intbound(origin[0], dx);
			auto tMaxY = intbound(origin[1], dy);
			auto tMaxZ = intbound(origin[2], dz);
			// The change in t when taking a step (always positive).
			auto tDeltaX = stepX / dx;
			auto tDeltaY = stepY / dy;
			auto tDeltaZ = stepZ / dz;
			// Buffer for reporting faces to the callback.
			auto face = glm::vec3(1.0f);

			// Avoids an infinite loop.
			//if (dx == = 0 && dy == = 0 && dz == = 0)
			//	throw new RangeError("Raycast in zero direction!");

			// Rescale from units of 1 cube-edge to units of 'direction' so we can
			// compare with 't'.
			radius /= std::sqrt(dx*dx + dy * dy + dz * dz);

			while (/* ray has not gone past bounds of world */
				(stepX > 0 ? x < getWidth() : x >= 0) &&
				(stepY > 0 ? y < getHeight() : y >= 0) &&
				(stepZ > 0 ? z < getWidth() : z >= 0)) {

				// Invoke the callback, unless we are not *yet* within the bounds of the
				// world.
				if (!(x < 0 || y < 0 || z < 0 || x >= getWidth() || y >= getHeight() || z >= getWidth()))
					//if (callback(x, y, z, blocks[x*wy*wz + y * wz + z], face))
					//	break;
					LOG("%d - %f, %f, %f\n", int(getBlock(x, y, z)->type), x, y, z);
					if(int(getBlock(x,y,z)->type) > 0) return &glm::vec3(x, y, z);

				// tMaxX stores the t-value at which we cross a cube boundary along the
				// X axis, and similarly for Y and Z. Therefore, choosing the least tMax
				// chooses the closest cube boundary. Only the first case of the four
				// has been commented in detail.
				if (tMaxX < tMaxY) {
					if (tMaxX < tMaxZ) {
						if (tMaxX > radius) break;
						// Update which cube we are now in.
						x += stepX;
						// Adjust tMaxX to the next X-oriented boundary crossing.
						tMaxX += tDeltaX;
						// Record the normal vector of the cube face we entered.
						face[0] = -stepX;
						face[1] = 0;
						face[2] = 0;
					}
					else {
						if (tMaxZ > radius) break;
						z += stepZ;
						tMaxZ += tDeltaZ;
						face[0] = 0;
						face[1] = 0;
						face[2] = -stepZ;
					}
				}
				else {
					if (tMaxY < tMaxZ) {
						if (tMaxY > radius) break;
						y += stepY;
						tMaxY += tDeltaY;
						face[0] = 0;
						face[1] = -stepY;
						face[2] = 0;
					}
					else {
						// Identical to the second case, repeated for simplicity in
						// the conditionals.
						if (tMaxZ > radius) break;
						z += stepZ;
						tMaxZ += tDeltaZ;
						face[0] = 0;
						face[1] = 0;
						face[2] = -stepZ;
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
			else {
				s = mod(s, 1);
				// problem is now s+t*ds = 1
				return (1 - s) / ds;
			}
		}

		int signum(float x) {
			return x > 0 ? 1 : x < 0 ? -1 : 0;
		}

		int mod(int value, int modulus) {
			return (value % modulus + modulus) % modulus;
		}

		int getWidth() { return Chunk::WIDTH * mChunks.size() / 2; }
		int getHeight() { return Chunk::HEIGHT * mChunks.size() / 2; }

		Block* getBlock(int x, int y, int z) {
			return &mChunks[x / Chunk::WIDTH * mChunks.size() / 2 + z / Chunk::WIDTH]->getBlock(x % Chunk::WIDTH, y, z % Chunk::WIDTH);
		}

	private:
		core::Vector<Chunk*> mChunks;
	};

}