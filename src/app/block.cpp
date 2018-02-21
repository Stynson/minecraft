#include "block.h"

namespace mc
{
	std::array<BlockDescriptors::BlockDescriptor, 6> BlockDescriptors::blockDescriptors = {
		BlockDescriptors::BlockDescriptor{0}
		,BlockDescriptors::BlockDescriptor{3,3,3,3,146,2}
		,BlockDescriptors::BlockDescriptor{2}
		,BlockDescriptors::BlockDescriptor{16}
		,BlockDescriptors::BlockDescriptor{146}
		,BlockDescriptors::BlockDescriptor{20,20,20,20,21,21}
	};
}
