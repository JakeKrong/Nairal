#include "../Core/EntityManager.h"
#include <cassert>

EntityManager::EntityManager() {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        m_AvailableEntities.push(entity);
    }
}

Entity EntityManager::CreateEntity() {
    assert(m_LivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

    Entity id = m_AvailableEntities.front();
    m_AvailableEntities.pop();
    ++m_LivingEntityCount;

    return id;
}

void EntityManager::DestroyEntity(Entity entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    m_Signatures[entity].reset();
    m_AvailableEntities.push(entity);
    --m_LivingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");
    m_Signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");
    return m_Signatures[entity];
}