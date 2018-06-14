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

	const int atlasIndex = 2048;
	static PosNormalTangentTexcoordVertex s_cubeVertices[24] =
	{
		// BACK
		{ -0.5f,  0.5f,  0.5f, encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,  0, 0 },
		{ 0.5f,  0.5f,  0.5f,  encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,  atlasIndex, 0 },
		{ -0.5f, -0.5f,  0.5f, encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,  0, atlasIndex },
		{ 0.5f, -0.5f,  0.5f,  encodeNormalRgba8(0.0f,  0.0f,  1.0f), 0,  atlasIndex, atlasIndex },
		// FRONT
		{ 0.5f,  0.5f, -0.5f,  encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,  atlasIndex, 0 },
		{ -0.5f,  0.5f, -0.5f, encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,  0, 0 },
		{ 0.5f, -0.5f, -0.5f,  encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,  atlasIndex, atlasIndex },
		{ -0.5f, -0.5f, -0.5f, encodeNormalRgba8(0.0f,  0.0f, -1.0f), 0,  0, atlasIndex },
		// LEFT
		{ -0.5f,  0.5f, -0.5f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0, 0},
		{ -0.5f,  0.5f,  0.5f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, atlasIndex, 0 },
		{ -0.5f, -0.5f, -0.5f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0, atlasIndex },
		{ -0.5f, -0.5f,  0.5f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, atlasIndex, atlasIndex },
		// RIGHT
		{ 0.5f,  0.5f,  0.5f,  encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,  0, 0},
		{ 0.5f,  0.5f, -0.5f,  encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,  atlasIndex, 0 },
		{ 0.5f, -0.5f,  0.5f,  encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,  0, atlasIndex },
		{ 0.5f, -0.5f, -0.5f,  encodeNormalRgba8(1.0f,  0.0f,  0.0f), 0,  atlasIndex, atlasIndex },
		// UP
		{ 0.5f,  0.5f,  0.5f,  encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,  atlasIndex, 0 },
		{ -0.5f,  0.5f,  0.5f, encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,  0, 0 },
		{ 0.5f,  0.5f, -0.5f,  encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,  atlasIndex, atlasIndex },
		{ -0.5f,  0.5f, -0.5f, encodeNormalRgba8(0.0f,  1.0f,  0.0f), 0,  0, atlasIndex},
		// DOWN
		{ 0.5f, -0.5f, -0.5f,  encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,  atlasIndex, atlasIndex },
		{ -0.5f, -0.5f, -0.5f, encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,  0, atlasIndex },
		{ 0.5f, -0.5f,  0.5f,  encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,  atlasIndex, 0 },
		{ -0.5f, -0.5f,  0.5f, encodeNormalRgba8(0.0f, -1.0f,  0.0f), 0,  0, 0 },
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


	static uint16_t textJump = 2048;
	static uint8_t blockPerRow = 16;

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

		void addVertices(Side side, int x, int y, int z, BlockType blockType) {
			int blockIndex = BlockDescriptors::getBlockIndex(blockType, side);
			uint8_t vBegin = 4 * (int)side;
			for (auto i = vBegin; i < vBegin + 4; i++)
			{
				PosNormalTangentTexcoordVertex clone = s_cubeVertices[i];
				clone.m_x += blockSize * x;
				clone.m_y += blockSize * y;
				clone.m_z += blockSize * z;
				clone.m_u += blockIndex % blockPerRow * 2048;
				clone.m_v += blockIndex / blockPerRow * 2048;
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
			ibh = bgfx::createIndexBuffer(iMem, BGFX_BUFFER_INDEX32);
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
		float blockSize = 1;

		glm::vec3 getChunkPosition()
		{
			auto chunkOffset = chunkSize * blockSize;
			return glm::vec3((float)x * chunkOffset, 0, (float)z * chunkOffset);
		}

		void submitMesh(bgfx::ViewId id, bgfx::ProgramHandle program, glm::mat4 transform, bgfx::UniformHandle& texUniform, bgfx::TextureHandle& texHandle)
		{
			transform = glm::translate(transform, getChunkPosition());
			bgfx::setTransform(&transform[0][0]);

			bgfx::setVertexBuffer(id, vbh);
			bgfx::setIndexBuffer(ibh);

			bgfx::setTexture(0, texUniform, texHandle);

			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_MSAA
				| BGFX_STATE_CULL_CW
				| BGFX_STATE_BLEND_ALPHA
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
						auto block = chunk->getBlock(x, y, z);
						if (!chunk->isBlockType(BlockType::AIR, x, y, z))
						{
							if (x == 0 || chunk->isBlockType(BlockType::AIR, x - 1, y, z))
							{
								m->addVertices(Side::LEFT, x, y, z, block.type);
							}
							if (x == (Chunk::WIDTH - 1) || chunk->isBlockType(BlockType::AIR, x + 1, y, z))
							{
								m->addVertices(Side::RIGHT, x, y, z, block.type);
							}

							if (y == 0 || chunk->isBlockType(BlockType::AIR, x, y - 1, z))
							{
								m->addVertices(Side::DOWN, x, y, z, block.type);
							}
							if (y == (Chunk::WIDTH - 1) || chunk->isBlockType(BlockType::AIR, x, y + 1, z))
							{
								m->addVertices(Side::UP, x, y, z, block.type);
							}

							if (z == 0 || chunk->isBlockType(BlockType::AIR, x, y, z - 1))
							{
								m->addVertices(Side::FRONT, x, y, z, block.type);
							}
							if (z == (Chunk::WIDTH - 1) || chunk->isBlockType(BlockType::AIR, x, y, z + 1))
							{
								m->addVertices(Side::BACK, x, y, z, block.type);
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