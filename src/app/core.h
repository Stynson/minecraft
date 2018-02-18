#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
//#define WIN32_LEAN_AND_MEAN
#include <sstream>
//#include <..\um\debugapi.h>


#include <bx/debug.h>

#include <glm/vec3.hpp>

#define LOG( ... ) { bx::debugPrintf(__VA_ARGS__); }

//#define LOG( s )            \
//{                             \
//   std::ostringstream os_;    \
//   os_ << s;                   \
//   OutputDebugString( os_.str().c_str() );  \
//}



namespace core
{
	template<typename T>
	using Vector = std::vector<T>;
	template<typename Key, typename Value>
	using Map = std::map<Key, Value>;
	template<typename T>
	using Set = std::set<T>;
	using String = std::string;

	float shiftIntoRange(float number, int rangeBegin, int rangeEnd);
	glm::vec3 worldCoordToBlockCoord(glm::vec3 coord, int offset);
	glm::vec3 worldCoordToChunkCoord(glm::vec3 coord, int offset);

}
