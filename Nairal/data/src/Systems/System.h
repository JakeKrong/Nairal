#pragma once
#include "../Core/Types.h"
//Can instead change CMake config later to --> include_directories(${CMAKE_SOURCE_DIR}/src)
#include <set>

class System {
public:
	std::set<Entity> m_Entities;
};