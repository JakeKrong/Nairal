#pragma once
#include "../Core/Types.h"
#include <array>
#include <queue>

class EntityManager {
public:
    EntityManager();

    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    void SetSignature(Entity entity, Signature signature);
    Signature GetSignature(Entity entity);

private:
    std::queue<Entity> m_AvailableEntities{};
    std::array<Signature, MAX_ENTITIES> m_Signatures{};
    std::uint32_t m_LivingEntityCount{};
};