#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>

#include <glm/vec3.hpp>

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
