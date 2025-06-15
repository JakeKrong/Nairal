#include "World.h"

void World::Init() {
	m_ComponentManager = CreateScope<ComponentManager>();
	m_EntityManager = CreateScope<EntityManager>();
	m_SystemManager = CreateScope<SystemManager>();
}

Entity World::CreateEntity(){
	return m_EntityManager->CreateEntity();
}

void World::DestroyEntity(Entity entity) {
	m_EntityManager->DestroyEntity(entity);
	m_ComponentManager->EntityDestroyed(entity);
	m_SystemManager->EntityDestroyed(entity);
}