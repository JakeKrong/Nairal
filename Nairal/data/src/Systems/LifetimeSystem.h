#pragma once
#include "../Systems/System.h"
#include <vector>

class LifetimeSystem : public System {
public:
    void Update(float deltaTime);

private:
    std::vector<Entity> m_EntitiesToDestroy;
};