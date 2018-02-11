#pragma once

#include <array>
namespace mc {

	enum class BlockType :uint8_t {
		AIR
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
		static const uint8_t HEIGHT_MINUS_ONE = 255;

		Chunk(int x, int y) : mX(x), mY(y) {};

		Block getBlock(uint8_t x, uint8_t y, uint8_t z);
		void setBlock(Block type, uint8_t x, uint8_t y, uint8_t z);

	private:
		std::array<Block, WIDTH * WIDTH * HEIGHT_MINUS_ONE> mData;
		int mX;
		int mY;



	};

}
