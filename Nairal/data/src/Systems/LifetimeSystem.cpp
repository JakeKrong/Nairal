#include "LifetimeSystem.h"
#include "../Components/Component.h"
#include "../Core/World.h"

extern World g_World;

void LifetimeSystem::Update(float deltaTime) {
	m_EntitiesToDestroy.clear();

	for (auto const& entity : m_Entities) {
		auto& lifetime = g_World.GetComponent<Lifetime>(entity);

		lifetime.remainingTime -= deltaTime;

		if (lifetime.remainingTime <= 0 && lifetime.destroyOnTimeout) {
			m_EntitiesToDestroy.push_back(entity);
		}
	}

	for (Entity entity : m_EntitiesToDestroy) {
		g_World.DestroyEntity(entity);
	}
}