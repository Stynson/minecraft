#pragma once

#include <glm/vec3.hpp> 
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mc
{ 
	struct CameraData
	{
		CameraData()
			:fov(glm::radians(60.0f))
			, ratio(4 / 3.0f)
			, nearDist(0.1f)
			, farDist((viewDistance - 1)*chunkSize*blockSize)
			, pos(0, 0, 0)
			, lookAt(0, 0, -30)
			, up(0,1,0)
			, view(1.0f)
		{}
		//More like game data
		int viewDistance = 10; //chunks
		int chunkSize = 16;
		//More like render data
		float blockSize = 2;

		glm::mat4 view;
		glm::vec3 pos;
		glm::vec3 lookAt;
		glm::vec3 up;
		float fov;
		float ratio;
		float nearDist;
		float farDist;
	};
}
