#pragma once

#include <array>
#include "block.h"
#include "core.h"

namespace mc { 

	class Chunk 
	{
	public:
		static const uint8_t WIDTH = 16;
		static const uint16_t HEIGHT = 32;

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
