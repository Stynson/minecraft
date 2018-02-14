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

namespace mc
{
	/*struct PosColorVertex
	{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
	ms_decl
	.begin()
	.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
	.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
	.end();
	};

	static bgfx::VertexDecl ms_decl;
	};
	static PosColorVertex s_cubeVertices[8] =
	{
	{ -1.0f,  1.0f,  1.0f, 0xff000000 }
	,{ 1.0f,  1.0f,  1.0f, 0xff0000ff }
	,{ -1.0f, -1.0f,  1.0f, 0xff00ff00 }
	,{ 1.0f, -1.0f,  1.0f, 0xff00ffff }
	,{ -1.0f,  1.0f, -1.0f, 0xffff0000 }
	,{ 1.0f,  1.0f, -1.0f, 0xffff00ff }
	,{ -1.0f, -1.0f, -1.0f, 0xffffff00 }
	,{ 1.0f, -1.0f, -1.0f, 0xffffffff }
	};

	static const uint16_t s_cubeFaceIndices[24] =
	{
	0, 1, 2, 3
	,4, 6, 5, 7
	,0, 2, 4, 6
	,1, 5, 3, 7
	,0, 4, 1, 5
	,2, 3, 6, 7
	};*/

	struct PosNormalTangentTexcoordVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_normal;
		uint32_t m_tangent;
		int16_t m_u;
		int16_t m_v;

		static void init()
		{
			ms_decl
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Normal, 4, bgfx::AttribType::Uint8, true, true)
				.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Uint8, true, true)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
				.end();
		}

		static bgfx::VertexDecl ms_decl;
	};

	static PosNormalTangentTexcoordVertex s_cubeVertices[24] =
	{
		// BACK
		{ -1.0f,  1.0f,  1.0f, encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,  0, 0 },
	{ 1.0f,  1.0f,  1.0f,  encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,  0x7fff, 0 },
	{ -1.0f, -1.0f,  1.0f, encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,  0, 0x7fff },
	{ 1.0f, -1.0f,  1.0f,  encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,  0x7fff, 0x7fff },
	// FRONT
	{ 1.0f,  1.0f, -1.0f,  encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,  0x7fff, 0 },
	{ -1.0f,  1.0f, -1.0f, encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,  0, 0 },
	{ 1.0f, -1.0f, -1.0f,  encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,  0x7fff, 0x7fff },
	{ -1.0f, -1.0f, -1.0f, encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,  0, 0x7fff },
	// LEFT
	{ -1.0f,  1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{ -1.0f,  1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0x7fff, 0 },
	{ -1.0f, -1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0, 0x7fff },
	{ -1.0f, -1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0, 0 },
	// RIGHT
	{ 1.0f,  1.0f,  1.0f,  encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,  0x7fff, 0 },
	{ 1.0f,  1.0f, -1.0f,  encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,  0x7fff, 0x7fff },
	{ 1.0f, -1.0f,  1.0f,  encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,  0, 0 },
	{ 1.0f, -1.0f, -1.0f,  encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,  0, 0x7fff },
	// UP
	{ 1.0f,  1.0f,  1.0f,  encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,  0x7fff, 0 },
	{ -1.0f,  1.0f,  1.0f, encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,  0, 0 },
	{ 1.0f,  1.0f, -1.0f,  encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,  0x7fff, 0x7fff },
	{ -1.0f,  1.0f, -1.0f, encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,  0, 0x7fff },
	// DOWN
	{ 1.0f, -1.0f, -1.0f,  encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,  0x7fff, 0x7fff },
	{ -1.0f, -1.0f, -1.0f, encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,  0, 0x7fff },
	{ 1.0f, -1.0f,  1.0f,  encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,  0x7fff, 0 },
	{ -1.0f, -1.0f,  1.0f, encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,  0, 0 },
	};

	static const uint16_t s_cubeFaceIndices[24] =
	{
		0,  2,  1,  3,
		4,  6,  5,  7,

		8,  10,  9, 11,
		12, 14, 13, 15,

		16, 18, 17, 19,
		20, 22, 21, 23
	};
	static const uint16_t s_cubeIndices[36] =
	{
		0,  2,  1,
		1,  2,  3,
		4,  5,  6,
		5,  7,  6,

		8, 10,  9,
		9, 10, 11,
		12, 13, 14,
		13, 15, 14,

		16, 18, 17,
		17, 18, 19,
		20, 21, 22,
		21, 23, 22,
	};

	/**
	*         VERTEX NUMBER/NAMES
	*
	*         (-1,1,1)    0(LUF)         1(RUF) (1,1,1)
	*                       *--------------*
	*         (-1,1,-1)    /|             /|
	*   y           4(LUB)/ |      5(RUB)/ | (1,1,-1)
	*   |                *--------------*  |
	*   |                |  |           |  |
	*   |_____ x         |  | (-1,-1,1) |  |
	*   /                |  |2(LLF)     |  |
	*  /                 |  *-----------|--*3(RLF) (1,-1,1)
	*   -z               | /            | /
	*         (-1,-1,-1) |/             |/
	*              6(LLB)*--------------*7(RLB) (1,-1,-1)
	*
	* */

	enum class Side : uint8_t
	{
		BACK = 0
		, FRONT
		, LEFT
		, RIGHT
		, UP
		, DOWN
	};



	struct Mesh
	{
		int x = 0;
		int z = 0;
		Mesh()
		{
			vertices.reserve(16 * 16 * 16);
			indices.reserve(16 * 16 * 16);
		}
		Mesh(const Mesh&) = delete;
		Mesh& operator=(Mesh&) = delete;
		Mesh(Mesh&&) = default;
		static size_t sumVertexCount;
		~Mesh()
		{
			bgfx::destroy(getVertexBufferHandle());
			bgfx::destroy(getIndexBufferHandle());
			sumVertexCount -= submitedVertices;
		}

		core::Vector<PosNormalTangentTexcoordVertex> vertices;
		core::Vector<uint32_t> indices;
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;

		void addVertices(Side side, int x, int y, int z) {
			uint8_t vBegin = 4 * (int)side;
			for (auto i = vBegin; i < vBegin + 4; i++)
			{
				PosNormalTangentTexcoordVertex clone = s_cubeVertices[i];
				clone.m_x += 2 * x;
				clone.m_y += 2 * y;
				clone.m_z += 2 * z;
				vertices.push_back(clone);
			}
			indices.push_back(vertices.size() + 0);
			indices.push_back(vertices.size() + 1);
			indices.push_back(vertices.size() + 2);
			indices.push_back(vertices.size() + 2);
			indices.push_back(vertices.size() + 1);
			indices.push_back(vertices.size() + 3);
		}


		void createHandlers() {
			/*calcTangents(vertices.data()
			, sizeof(vertices[0])*vertices.size()
			, PosNormalTangentTexcoordVertex::ms_decl
			, indices.data()
			, sizeof(indices[0])*indices.size()
			);*/

			auto vMem = bgfx::copy(vertices.data(), sizeof(vertices[0])*vertices.size());
			vbh = bgfx::createVertexBuffer(vMem, PosNormalTangentTexcoordVertex::ms_decl);
			submitedVertices = vertices.size();
			sumVertexCount += submitedVertices;
			vertices.clear();

			auto iMem = bgfx::copy(indices.data(), sizeof(indices[0])*indices.size());
			ibh = bgfx::createIndexBuffer(iMem,BGFX_BUFFER_INDEX32);
			indices.clear();
		}
		size_t submitedVertices = 0;

		bgfx::VertexBufferHandle getVertexBufferHandle() const {
			return vbh;
		}
		bgfx::IndexBufferHandle getIndexBufferHandle() const {
			return ibh;
		}

		int chunkSize = 16;
		float blockSize = 2;

		glm::vec3 getChunkPosition()
		{
			auto chunkOffset = chunkSize * blockSize;
			return glm::vec3((float)x * chunkOffset, 0, (float)z * chunkOffset);
		}

		void submitMesh(bgfx::ViewId id, bgfx::ProgramHandle program, glm::mat4 transform, bgfx::UniformHandle& texUniform, bgfx::TextureHandle& texHandle)
		{
			transform = glm::translate(transform, getChunkPosition());
			bgfx::setTransform(&transform[0][0]);

			bgfx::setVertexBuffer(0, vbh);
			bgfx::setIndexBuffer(ibh);

			bgfx::setTexture(0, texUniform, texHandle);

			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_MSAA
				| BGFX_STATE_CULL_CW
			);
			bgfx::submit(id, program);
		}


	};

	class PreRenderSystem
	{
	public:
		PreRenderSystem(CullingSystem& cullingSystem)
			:mCullingSystem(cullingSystem)
		{}
		std::vector<Mesh*> getMeshes(const CameraData& cameraData)
		{
			auto newChunks = mCullingSystem.getCulledChunks(cameraData);
			auto newMeshes = MeshMap();
			auto result = core::Vector<Mesh*>();
			static int lastBakeCount = -1;
			int bakeCount = 0;
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
					auto mesh = bakeMesh(chunk);
					++bakeCount;
					result.push_back(mesh.get());
					newMeshes.insert(std::make_pair(chunk->getKey(), std::make_pair(chunk->getVersion(), std::move(mesh))));
				}
			}
			if (bakeCount != lastBakeCount)
			{
				LOG("Baked %d number of chunks in this frame!\n", bakeCount);
				LOG("%d number of chunks baked in total!\n", result.size());
				LOG("%d number of chunks loaded in total!\n", (2 * cameraData.viewDistance + 1)*(2 * cameraData.viewDistance + 1));
				LOG("%d vertices for terrain in total!\n\n", Mesh::sumVertexCount);
				lastBakeCount = bakeCount;
			}
			std::swap(mOldMeshes, newMeshes);
			return result;
		}
	private:
		std::unique_ptr<Mesh> bakeMesh(Chunk* chunk)
		{
			auto m = std::make_unique<Mesh>();
			for (auto y = 0; y < Chunk::HEIGHT; y++)
			{
				for (auto z = 0; z < Chunk::WIDTH; z++)
				{
					for (auto x = 0; x < Chunk::WIDTH; x++)
					{
						if (!chunk->isBlockType(BlockType::AIR, x, y, z))
						{
							if (x == 0 || chunk->isBlockType(BlockType::AIR, x - 1, y, z))
							{
								m->addVertices(Side::LEFT, x, y, z);
							}
							if (x == (Chunk::WIDTH - 1) || chunk->isBlockType(BlockType::AIR, x + 1, y, z))
							{
								m->addVertices(Side::RIGHT, x, y, z);
							}

							if (y == 0 || chunk->isBlockType(BlockType::AIR, x, y - 1, z))
							{
								m->addVertices(Side::DOWN, x, y, z);
							}
							if (y == (Chunk::WIDTH - 1) || chunk->isBlockType(BlockType::AIR, x, y + 1, z))
							{
								m->addVertices(Side::UP, x, y, z);
							}

							if (z == 0 || chunk->isBlockType(BlockType::AIR, x, y, z - 1))
							{
								m->addVertices(Side::FRONT, x, y, z);
							}
							if (z == (Chunk::WIDTH - 1) || chunk->isBlockType(BlockType::AIR, x, y, z + 1))
							{
								m->addVertices(Side::BACK, x, y, z);
							}
						}
					}
				}
			}
			m->x = chunk->getX();
			m->z = chunk->getZ();
			m->createHandlers();
			return std::move(m);
		}

		CullingSystem& mCullingSystem;
		core::Vector<core::String> mOldChunks;
		using MeshMap = core::Map<core::String, std::pair<size_t, std::unique_ptr<Mesh>>>;
		MeshMap mOldMeshes;
	};
}