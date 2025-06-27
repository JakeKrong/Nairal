#pragma once
#include "System.h"
#include "../Core/World.h"
#include <functional>
#include <SFML/System/Vector2.hpp>

class CollisionSystem : public System {
public:
    void Update();
    std::function<void()> OnPlayerHit;
    void SetPlayer(Entity player) { m_Player = player; }

private:
    bool CheckCollision(Entity a, Entity b);
    bool IsValidEntity(Entity entity);
    void HandleCollision(Entity entityA, Entity entityB);
    void HandleGroundCollision(Entity player, Entity ground);
    void HandlePlayerObstacleCollision(Entity player, Entity obstacleEntity);
    Entity m_Player = 0;

    template<typename T>
    bool HasComponent(Entity entity);

    sf::Vector2f GetColliderBounds(Entity entity);
};