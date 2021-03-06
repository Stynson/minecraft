#include "rayCast.h"

namespace mc {

	RayCast::RayCastResult RayCast::raycast(const CameraData& cameraData, float radius, void(*drawStepPoints)(float, float, float)) const {
		// From "A Fast Voxel Traversal Algorithm for Ray Tracing"
		// by John Amanatides and Andrew Woo, 1987
		// <http://www.cse.yorku.ca/~amana/research/grid.pdf>
		// <http://citeseer.ist.psu.edu/viewdoc/summary?doi=10.1.1.42.3443>
		// Extensions to the described algorithm:
		//   � Imposed a distance limit.
		//   � The face passed through to reach the current cube is provided to
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
		auto cameraMaxHorizontalPos = Chunk::WIDTH * std::ceil(mMatrixSize / 2.0f) * mBlockSize;
		auto cameraMinHorizontalPos = Chunk::WIDTH * std::floor(mMatrixSize / 2.0f) * mBlockSize;

		glm::vec3 shift(0.0f);
		auto shifted = core::shiftIntoRangeWithTrack(cameraPos.x, cameraMinHorizontalPos, cameraMaxHorizontalPos);
		cameraPos.x = shifted.first;
		shift.x = shifted.second;

		shifted = core::shiftIntoRangeWithTrack(cameraPos.z, cameraMinHorizontalPos, cameraMaxHorizontalPos);
		cameraPos.z = shifted.first;
		shift.z = shifted.second;

		// Direction to increment x,y,z when stepping.
		auto step = glm::vec3(
			signum(direction.x)
			, signum(direction.y)
			, signum(direction.z));
		// See description above. The initial values depend on the fractional
		// part of the cameraPos.
		auto tMax = glm::vec3(
			intbound(cameraPos.x, direction.x)
			, intbound(cameraPos.y, direction.y)
			, intbound(cameraPos.y, direction.z));
		// The change in t when taking a step (always positive).
		auto tDelta = glm::vec3(
			step.x / direction.x / mPrecision
			, step.y / direction.y / mPrecision
			, step.z / direction.z / mPrecision);
		auto face = glm::vec3(0.0f);

		// Avoids an infinite loop.
		//if (dx === 0 && dy == = 0 && dz === 0)
		//	throw new RangeError("Raycast in zero direction!");

		// Rescale from units of 1 cube-edge to units of 'direction' so we can
		// compare with 't'.
		radius /= mPrecision;
		radius /= std::sqrt(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);

		while (/* ray has not gone past bounds of world */
			(step.x > 0 ? cameraPos.x < getWidth() : cameraPos.x >= 0) &&
			(step.y > 0 ? cameraPos.y < getHeight() : cameraPos.y >= 0) &&
			(step.z > 0 ? cameraPos.z < getWidth() : cameraPos.z >= 0)) {

			drawStepPoints(
				cameraPos.x - shift.x
				, cameraPos.y
				, cameraPos.z - shift.z);

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
				Block selectedBlock = getBlock(cameraPos);
				if (int(selectedBlock.type) > 0)
				{
					auto selectedBlockCoord = glm::vec3(
						cameraPos.x - shift.x
						, cameraPos.y
						, cameraPos.z - shift.z);
					return RayCastResult(selectedBlockCoord, face);
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
					face.x = -step.x;
					face.y = 0;
					face.z = 0;
				}
				else
				{
					if (tMax.z > radius) break;
					cameraPos.z += step.z;
					tMax.z += tDelta.z;
					face.x = 0;
					face.y = 0;
					face.z = -step.z;
				}
			}
			else
			{
				if (tMax.y < tMax.z)
				{
					if (tMax.y > radius) break;
					cameraPos.y += step.y;
					tMax.y += tDelta.y;
					face.x = 0;
					face.y = -step.y;
					face.z = 0;
				}
				else
				{
					// Identical to the second case, repeated for simplicity in
					// the conditionals.
					if (tMax.z > radius) break;
					cameraPos.z += step.z;
					tMax.z += tDelta.z;
					face.x = 0;
					face.y = 0;
					face.z = -step.z;
				}
			}
		}
		return RayCastResult();
	}

	float RayCast::intbound(float s, float ds) const {
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

	float RayCast::signum(float x) const {
		return x > 0 ? mPrecision : x < 0 ? -mPrecision : 0.0f;
	}

	float RayCast::mod(float value, float modulus) const {
		return std::fmod(std::fmod(value, modulus) + modulus, modulus);
	}

}
