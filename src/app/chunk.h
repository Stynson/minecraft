#pragma once

#include <array>
namespace mc {

	enum class BlockType :uint8_t {
		AIR=0
		, DIRT
	};

	struct Block {
		BlockType type;
		uint8_t orientation;

		Block() : type(BlockType::AIR), orientation(0) {}

		Block(BlockType _type) : type(type), orientation(0) {}

		Block(BlockType _type, uint8_t _orientation) : type(_type), orientation(_orientation) {}

	};

	class Chunk {
	public:
		static const uint8_t WIDTH = 16;
		static const uint16_t HEIGHT = 16;

		Chunk() : mX(0), mY(0) {};

		Chunk(int x, int y) : mX(x), mY(y) {};

		Block getBlock(uint8_t x, uint8_t y, uint8_t z) const;
		void setBlockType(BlockType type, uint8_t x, uint8_t y, uint8_t z);

		int getX() const { return mX; }
		int getY() const { return mY;	}

	private:
		std::array<Block, WIDTH * WIDTH * HEIGHT> mData;
		int mX;
		int mY;



	};

}
