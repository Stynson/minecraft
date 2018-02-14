#pragma once

#include "cellSystem.h"
#include "core.h"
#include "cameraData.h"

namespace mc {

	struct Plane
	{ 
		Plane() {}
		Plane(glm::vec3 aNormal, glm::vec3 aPoint)
			:normal(aNormal)
			, point(aPoint)
		{ 
			d = -glm::dot(normal, point);
		}
		glm::vec3 normal;
		glm::vec3 point;
		float d;

		float Plane::distance(glm::vec3 &p) {
			return ( d + glm::dot(normal, p) );
		}
	};

	class CullingSystem {
	public:
		CullingSystem(CellSystem& cellSystem)
			: mCellSystem(cellSystem)
		{}

		core::Vector<Chunk*> getCulledChunks(float x, float z, float atX, float atZ, const CameraData& cameraData);

	private:
		CellSystem& mCellSystem;
	};

}