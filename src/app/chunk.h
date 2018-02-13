#pragma once

#include <array>
#include "core.h"

namespace mc {

	enum class BlockType : uint8_t
	{
		AIR=0
		, DIRT
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

	class Chunk 
	{
	public:
		static const uint8_t WIDTH = 16;
		static const uint16_t HEIGHT = 16;

		Chunk() = default;
		Chunk(int x, int z) : mX(x), mZ(z) {};
		Chunk(Chunk const&) = delete;
		~Chunk(){}

		Chunk& operator=(Chunk const&) = delete;

		size_t getVersion() const { return mVersion; }

		operator core::String() const
		{ 
			return getKey();
		}
		core::String getKey() const
		{
			core::String key = std::to_string(mX).c_str();
			key += "_";
			key += std::to_string(mZ).c_str();
			return key;
		}
		Block getBlock(uint8_t x, uint8_t y, uint8_t z) const;
		void setBlockType(BlockType type, uint8_t x, uint8_t y, uint8_t z);
		bool isBlockType(BlockType type, uint8_t x, uint8_t y, uint8_t z);

		int getX() const { return mX; }
		int getZ() const { return mZ; }

	private:
		size_t idAt(uint8_t x, uint8_t y, uint8_t z) const;

		std::array<Block, WIDTH * WIDTH * HEIGHT> mData;
		int mX = 0;
		int mZ = 0;
		size_t mVersion = 0; 
	};

}
