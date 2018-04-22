#include "core.h"
#include "chunk.h"
#include <cmath>

namespace core {
	
	glm::vec3 worldToChunkCoord(glm::vec3 worldPoint) {
		return glm::vec3(0, 0, 0);
	}

	float shiftIntoRange(float number, int rangeBegin, int rangeEnd) {
		int rangeDistance = rangeEnd - rangeBegin;
		while (number > rangeEnd) number -= rangeDistance;
		while (number < rangeBegin) number += rangeDistance;
		return number;
	}

	std::pair<float, int> shiftIntoRangeWithTrack(float number, int rangeBegin, int rangeEnd) {
		int rangeDistance = rangeEnd - rangeBegin;
		int shift = 0;
		while (number > rangeEnd)
		{
			number -= rangeDistance;
			shift -= rangeDistance;
		}
		while (number < rangeBegin)
		{
			number += rangeDistance;
			shift += rangeDistance;
		}
		return std::make_pair(number, shift);
	}

	glm::vec3 worldCoordToBlockCoord(glm::vec3 coord, int offset) {
		coord.x = core::shiftIntoRange(coord.x, 0, offset);
		coord.z = core::shiftIntoRange(coord.z, 0, offset);
		coord.x = std::floor(coord.x);
		coord.z = std::floor(coord.z);
		return coord;
	}

	glm::vec3 worldCoordToChunkCoord(glm::vec3 coord, int offset)
	{
		coord.x = std::floor(coord.x / offset);
		coord.z = std::floor(coord.z / offset);
		return coord;
	}

}
