#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "chunk.h"
#include "cullingSystem.h"
#include "cameraData.h"
#include "core.h"


#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include "bounds.h"

#include <bx/allocator.h>
#include <bx/debug.h>
#include <bx/math.h>
#include <bx/rng.h>
#include <bgfx/bgfx.h>

#include "mesh.h"

namespace mc
{ 
	class PreRenderSystem
	{
	public:
		PreRenderSystem(CullingSystem& cullingSystem)
			:mCullingSystem(cullingSystem)
		{}
		std::vector<Mesh*> getMeshes(const CameraData& cameraData);
	private:
		std::unique_ptr<Mesh> bakeMesh(Chunk* chunk);

		CullingSystem& mCullingSystem;
		core::Vector<core::String> mOldChunks;
		using MeshMap = core::Map<core::String, std::pair<size_t, std::unique_ptr<Mesh>>>;
		MeshMap mOldMeshes;
	};
}
