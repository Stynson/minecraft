#pragma once
#include <array>

namespace mc
{
	enum class BlockType : uint8_t
	{
		AIR = 0
		, GRASS_DIRT
		, DIRT
		, COARSE_STONE
		, LEAF
		, TREE
	};

	struct Block
	{
		BlockType type = BlockType::AIR;
		uint8_t orientation = 0;

		Block() = default;
		Block(BlockType _type) : type(type), orientation(0) {}
		Block(BlockType _type, uint8_t _orientation) : type(_type), orientation(_orientation) {}
		Block(Block const&) = default;
		Block(Block &&) = default;

		Block& operator=(Block const&) = default;
		Block& operator=(Block &&) = default;
	};

	enum class Side : uint8_t
	{
		BACK = 0
		, FRONT
		, LEFT
		, RIGHT
		, UP
		, DOWN
	};

	class BlockDescriptors
	{
	public:
		struct BlockDescriptor
		{
			BlockDescriptor() {}
			BlockDescriptor(int x)
			{
				std::fill(textureIndex.begin(), textureIndex.end(), x);
			}
			BlockDescriptor(int a, int b, int c, int d, int e, int f)
			{
				textureIndex[0] = a;
				textureIndex[1] = b;
				textureIndex[2] = c;
				textureIndex[3] = d;
				textureIndex[4] = e;
				textureIndex[5] = f;
			}
			BlockDescriptor(std::array<int, 6> values)
			{
				textureIndex = values;
			}
			std::array<int, 6> textureIndex;
		};
		static int getBlockIndex(BlockType blockType, Side side)
		{
			return blockDescriptors[(int)blockType].textureIndex[(int)side];
		}
	private:

		static std::array<BlockDescriptor, 6> blockDescriptors;
	};
}
