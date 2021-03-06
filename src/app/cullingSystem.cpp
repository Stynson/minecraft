#include "cullingSystem.h"
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mc {core::Vector<Chunk*> CullingSystem::getCulledChunks(const CameraData& cameraData)
	{
		auto nearbyChunks = mCellSystem.getNearbyChunks(cameraData);
		auto culledChunks = core::Vector<Chunk*>();
		culledChunks.reserve(nearbyChunks.size());

		float tanRatio = 2 * tan(cameraData.fov / 2);
		float nearHeight = tanRatio * cameraData.nearDist;
		float nearWidth = nearHeight * cameraData.ratio;
		float farHeight = tanRatio * cameraData.farDist;
		float farWidth = farHeight * cameraData.ratio;
		glm::vec3 ray = glm::normalize(cameraData.lookAt - cameraData.pos);
		glm::vec3 rightVector = glm::normalize(glm::cross(ray, cameraData.up));

		glm::vec3 farCenterPoint = cameraData.pos + ray * cameraData.farDist;
		glm::vec3 nearCenterPoint = cameraData.pos + ray * cameraData.nearDist;

		glm::vec3 rightPlanePoint = nearCenterPoint + rightVector * nearWidth / 2.0f * -1.0f;
		glm::vec3 rightPlaneNormal = glm::cross(cameraData.up, glm::normalize(rightPlanePoint - cameraData.pos)) * -1.0f;

		glm::vec3 leftPlanePoint = nearCenterPoint + rightVector * nearWidth / 2.0f;
		glm::vec3 leftPlaneNormal = glm::cross(cameraData.up, glm::normalize(leftPlanePoint - cameraData.pos));

		glm::vec3 upPlanePoint = nearCenterPoint + cameraData.up * nearHeight / 2.0f;
		glm::vec3 upPlaneNormal = glm::cross(cameraData.up, glm::normalize(upPlanePoint - cameraData.pos));

		glm::vec3 downPlanePoint = nearCenterPoint + cameraData.up * nearHeight / 2.0f * -1.0f;
		glm::vec3 downPlaneNormal = glm::cross(cameraData.up, glm::normalize(downPlanePoint - cameraData.pos));

		glm::vec3 nearPlanePoint = nearCenterPoint;
		glm::vec3 nearPlaneNormal = ray;

		glm::vec3 farPlanePoint = farCenterPoint;
		glm::vec3 farPlaneNormal = -ray;

		core::Vector<Plane> planes;
		planes.push_back(Plane{ nearPlaneNormal,nearPlanePoint });
		planes.push_back(Plane{ farPlaneNormal,farPlanePoint });

		planes.push_back(Plane{ leftPlaneNormal,rightPlanePoint });
		planes.push_back(Plane{ rightPlaneNormal,rightPlanePoint });

		//std::array<Plane, 3> planes = {
		//	Plane{rightPlaneNormal,rightPlanePoint}
		//	, Plane{leftPlaneNormal,leftPlanePoint}
		//	//, Plane{upPlaneNormal,upPlanePoint}
		//	// , Plane{downPlaneNormal,downPlanePoint}
		//	// , Plane{farPlaneNormal,farPlanePoint}
		//	, Plane{nearPlaneNormal,nearPlanePoint}
		//};

		int offset = cameraData.chunkSize*cameraData.blockSize;
		for (auto& chunk : nearbyChunks)
		{
			bool inside = true;
			for (auto& plane : planes)
			{
				glm::vec3 positive(chunk->getX()*offset, 0, chunk->getZ()*offset);
				if (plane.normal.x >= 0) positive.x += offset;
				if (plane.normal.z >= 0) positive.z += offset;

				if (plane.distance(positive) < 0)
				{
					inside = false;
					break;
				}

				//auto a = glm::normalize(glm::cross(plane.normal, (plane.point - positive)));
				/*auto b = glm::dot(plane.normal, positive);
				if (b < -0.0000001 )
				{
					inside = false;
					break;
				}*/


				//glm::vec3 negative(chunk->getX()*offset+offset, 0, chunk->getZ()*offset+offset);
				//if (plane.normal.x >= 0) positive.x -= offset;
				//if (plane.normal.z >= 0) positive.z -= offset;

				//if (glm::distance(plane.point, negative) < 0)
				//	//INTERSECT 
			}
			if (inside)
				culledChunks.push_back(chunk);
		}

		return culledChunks;
	}
}