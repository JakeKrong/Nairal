#include "EntityManager.h"
#include <cassert>

EntityManager::EntityManager() {
	for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
		m_availableEntities.push(entity);
	}
}

Entity EntityManager::CreateEntity() {
	assert(m_livingEntitiesCount < MAX_ENTITIES && "Too many entities in existance.");

	Entity id = m_availableEntities.front();
	m_availableEntities.pop();
	++m_livingEntitiesCount;

	return id;
}

void EntityManager::DestroyEntity(Entity entity) {
	assert(entity < MAX_ENTITIES && "Too many entities in existance.");
	
	m_Signatures[entity].reset();
	m_availableEntities.push(entity);
	--m_livingEntitiesCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
	assert(entity < MAX_ENTITIES && "Entity out of range");
	m_Signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
	assert(entity < MAX_ENTITIES && "Entity out of range");
	return m_Signatures[entity];
}