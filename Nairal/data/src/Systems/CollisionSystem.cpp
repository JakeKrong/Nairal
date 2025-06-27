#include "../Core/ComponentManager.h"
#include "../Components/Component.h"
#include "../Core/World.h"
#include "../Systems/CollisionSystem.h"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

void CollisionSystem::Update() {
    if (!m_World) return;
    if (m_Entities.empty()) return;

    std::vector<Entity> entities(m_Entities.begin(), m_Entities.end());

    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            Entity entityA = entities[i];
            Entity entityB = entities[j];

            try {
                if (CheckCollision(entityA, entityB)) {
                    //std::cout << "[CollisionSystem] Detected collision: " << entityA << " vs " << entityB << "\n";
                    HandleCollision(entityA, entityB);
                }
            }
            catch (const std::exception& e) {
                std::cerr << "[CollisionSystem] Exception during collision check: "
                    << e.what() << "\n";
            }
        }
    }
}

bool CollisionSystem::CheckCollision(Entity a, Entity b) {
    if (!HasComponent<Transform>(a) || !HasComponent<Collider>(a)) return false;
    if (!HasComponent<Transform>(b) || !HasComponent<Collider>(b)) return false;

    auto& transformA = m_World->GetComponent<Transform>(a);
    auto& colliderA = m_World->GetComponent<Collider>(a);
    auto& transformB = m_World->GetComponent<Transform>(b);
    auto& colliderB = m_World->GetComponent<Collider>(b);

    sf::FloatRect rectA(
        transformA.position + colliderA.offset,
        colliderA.size
    );
    sf::FloatRect rectB(
        transformB.position + colliderB.offset,
        colliderB.size
    );

    return rectA.findIntersection(rectB).has_value();
}

void CollisionSystem::HandleCollision(Entity entityA, Entity entityB) {
    if (!m_World) return;

    Entity other = 0;

    if (entityA == m_Player && HasComponent<Obstacle>(entityB)) {
        other = entityB;
    }
    else if (entityB == m_Player && HasComponent<Obstacle>(entityA)) {
        other = entityA;
    }
    else {
        return; // Neither involved the player
    }

    auto& obstacle = m_World->GetComponent<Obstacle>(other);

    if (obstacle.type == ObstacleTypes::Ground) {
        HandleGroundCollision(m_Player, other);
    }
    else if (obstacle.deadly) {
        //std::cout << "[CollisionSystem] Player hit by deadly obstacle (" << static_cast<int>(obstacle.type) << ")\n";
        if (OnPlayerHit) OnPlayerHit();
    }
}

void CollisionSystem::HandlePlayerObstacleCollision(Entity player, Entity obstacleEntity) {
    if (!HasComponent<Obstacle>(obstacleEntity)) return;

    auto& obstacle = m_World->GetComponent<Obstacle>(obstacleEntity);

    if (obstacle.type == ObstacleTypes::Ground) {
        HandleGroundCollision(player, obstacleEntity);
    }
    else if (obstacle.deadly) {
        //std::cout << "[CollisionSystem] Player hit by deadly obstacle (" << static_cast<int>(obstacle.type) << ")\n";
        if (OnPlayerHit) {
            OnPlayerHit();
        }
    }
}

void CollisionSystem::HandleGroundCollision(Entity player, Entity ground) {
    if (!HasComponent<Transform>(player) ||
        !HasComponent<Physics>(player) ||
        !HasComponent<Player>(player) ||
        !HasComponent<Transform>(ground) ||
        !HasComponent<Collider>(ground)) {
        std::cerr << "[CollisionSystem] Missing component for ground collision\n";
        return;
    }

    auto& playerTransform = m_World->GetComponent<Transform>(player);
    auto& playerPhysics = m_World->GetComponent<Physics>(player);
    auto& playerComponent = m_World->GetComponent<Player>(player);
    auto& playerCollider = m_World->GetComponent<Collider>(player);
    auto& groundTransform = m_World->GetComponent<Transform>(ground);
    auto& groundCollider = m_World->GetComponent<Collider>(ground);

    if (playerPhysics.velocity.y > 0 &&
        playerTransform.position.y < groundTransform.position.y) {
        playerTransform.position.y = groundTransform.position.y - playerCollider.size.y;
        playerPhysics.velocity.y = 0.0f;
        playerComponent.isGrounded = true;

        //std::cout << "[CollisionSystem] Player grounded\n";
    }
}

template<typename T>
bool CollisionSystem::HasComponent(Entity entity) {
    try {
        m_World->GetComponent<T>(entity);
        return true;
    }
    catch (...) {
        return false;
    }
}
