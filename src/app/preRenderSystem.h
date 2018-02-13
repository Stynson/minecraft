#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "chunk.h"
#include "cullingSystem.h"
#include "core.h"

namespace mc
{
	struct Mesh
	{
		Mesh() = default;
		Mesh(const Mesh&) = delete;
		Mesh& operator=(Mesh&) = delete;
		Mesh(Mesh&&) = default;
		~Mesh() = default;
		Chunk* hack;
	};

	class PreRenderSystem
	{
	public:
		PreRenderSystem(CullingSystem& cullingSystem)
			:mCullingSystem(cullingSystem)
		{}
		std::vector<Mesh*> getMeshes(float x, float z, float direction, int distance)
		{
			auto newChunks = mCullingSystem.getCulledChunks(x, z, direction, distance);
			auto newMeshes = MeshMap();
			auto result = core::Vector<Mesh*>();
			for (auto& chunk : newChunks)
			{
				auto it = mOldMeshes.find(chunk->getKey());
				if (it != mOldMeshes.end() && it->second.first == chunk->getVersion())
				{
					result.push_back(it->second.second.get());
					newMeshes.insert(std::move(*it));
				}
				else
				{
					auto mesh = cookMesh(chunk);
					result.push_back(mesh.get());
					newMeshes.insert(std::make_pair(chunk->getKey(), std::make_pair(chunk->getVersion(), std::move(mesh))));
				}
			}
			std::swap(mOldMeshes, newMeshes); 
			return result;
		}
	private:
		std::unique_ptr<Mesh> cookMesh(Chunk* chunk)
		{ 
			auto m = std::make_unique<Mesh>();
			m->hack = chunk;
			return std::move(m);
		}
		CullingSystem& mCullingSystem;
		core::Vector<core::String> mOldChunks;
		using MeshMap = core::Map<core::String, std::pair<size_t, std::unique_ptr<Mesh>>>;
		MeshMap mOldMeshes;
	};
}