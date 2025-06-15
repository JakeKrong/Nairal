#pragma once
#include "Types.h"
#include <array>
#include <queue>

class EntityManager {
public:
	EntityManager();

	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, Signature signature);
	Signature GetSignature(Entity);

private:
	std::queue<Entity> m_availableEntities{};
	std::array<Signature, MAX_ENTITIES> m_Signatures;
	std::uint32_t m_livingEntitiesCount{};
};