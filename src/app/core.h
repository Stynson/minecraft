#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
//#define WIN32_LEAN_AND_MEAN
#include <sstream>
//#include <windows.h>
//#include <..\um\debugapi.h>

#include <glm/vec3.hpp>


#define LOG( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}

namespace core
{
	template<typename T>
	using Vector = std::vector<T>;
	template<typename Key, typename Value>
	using Map = std::map<Key, Value>;
	template<typename T>
	using Set = std::set<T>;
	using String = std::string;

}
