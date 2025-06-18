#include "PhysicsSystem.h"
#include "Component.h"
#include "Core/World.h"

extern World g_World;

void PhysicsSystem::Update(float deltaTime) {
	for (auto const& entity : m_Entities) {
		auto& transform = g_World.GetComponent<Transform>(entity); //Get transform and physics component of entity
		auto& physics = g_World.GetComponent<Physics>(entity);

		if (physics.affectedByGravity) {
			physics.acceleration.y = GRAVITY;
		}

		//Update velocity
		physics.velocity += physics.acceleration * deltaTime;

		//Update Position
		transform.position += physics.velocity * delaTime;

		//Check Ground Collision (currently use y-coords)
		if (transform.position.y >= GROUND_Y) {
			transform.position = GROUND_Y;
			if (physics.velocity.y > 0) {
				physics.velocity.y = 0;
			}
		}

		//Reset Acceleration
		physics.acceleration = { 0.0f, 0.0f };
	}
}