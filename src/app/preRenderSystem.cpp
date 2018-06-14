#include "preRenderSystem.h"

namespace mc
{
	size_t Mesh::sumVertexCount = 0;

    std::vector<Mesh*> PreRenderSystem::getMeshes(const CameraData& cameraData)
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

    std::unique_ptr<Mesh> PreRenderSystem::bakeMesh(Chunk* chunk)
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
}
