#include "PhysicsSystem.h"
#include "../Components/Component.h"
#include "../Core/World.h"

void PhysicsSystem::Update(float deltaTime) {
    for (auto const& entity : m_Entities) {
        auto& transform = m_World->GetComponent<Transform>(entity);
        auto& physics = m_World->GetComponent<Physics>(entity);

        // Apply gravity
        if (physics.affectedByGravity) {
            physics.acceleration.y = GRAVITY;
        }

        // Update velocity
        physics.velocity += physics.acceleration * deltaTime;

        // Update position
        transform.position += physics.velocity * deltaTime;

        // Remove the simple ground collision - let CollisionSystem handle it
        // The collision system will handle ground collision properly

        // Reset acceleration for next frame
        physics.acceleration = { 0.0f, 0.0f };
    }
}