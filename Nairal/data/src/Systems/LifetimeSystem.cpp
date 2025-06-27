#include "../Systems/LifetimeSystem.h"
#include "../Components/Component.h"
#include "../Core/World.h"
#include <iostream>

void LifetimeSystem::Update(float deltaTime) {
    if (!m_World) {
        //std::cerr << "[LifetimeSystem] Error: World is null!\n";
        return;
    }

    //std::cout << "[LifetimeSystem] Update start, entities to destroy: "
        //<< m_EntitiesToDestroy.size() << "\n";

    try {
        m_EntitiesToDestroy.clear();
    }
    catch (...) {
        std::cerr << "[LifetimeSystem] CRASH in vector::clear()\n";
        return;
    }

    for (auto const& entity : m_Entities) {
        if (!m_World->HasComponent<Lifetime>(entity)) continue;

        auto& lifetime = m_World->GetComponent<Lifetime>(entity);
        lifetime.remainingTime -= deltaTime;

        if (lifetime.remainingTime <= 0.0f && lifetime.destroyOnTimeout) {
            m_EntitiesToDestroy.push_back(entity);
        }
    }

    for (Entity entity : m_EntitiesToDestroy) {
        m_World->DestroyEntity(entity);
    }
}