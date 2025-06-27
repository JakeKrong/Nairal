#pragma once
#include "../Core/Types.h"
#include <set>
#include <iostream>

class World;

class System {
public:
    std::set<Entity> m_Entities;

    // Add world pointer
    void SetWorld(World* world) { m_World = world; std::cout << "[LifetimeSystem] World set!\n";}

protected:
    World* m_World = nullptr;
};