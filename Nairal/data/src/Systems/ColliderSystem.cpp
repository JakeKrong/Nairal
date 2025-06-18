#include "CollisionSystem.h"
#include "../Core/World.h"
#include "../Components/Component.h"
#include <SFML/Graphics/Rect.hpp>

extern World g_World;

void CollisionSystem::Update() {
	std::vector<Entity> entities(m_Entities.begin(), m_Entities.end());

	for (size_t i = 0; i < entities.size(); i++) {
		for (size_t j = i; j < entities.size(); j++) {
			Entity entityA = entities[i];
			Entity entityB = entities[j];

			if (CheckCollision(entityA, entityB)) {
				//Check if player is colliding with obstacle
				bool aIsPlayer = false, bIsPlayer = false;
				bool aIsObstacle = false, bIsObstacle = false;

				try {
					g_World.GetComponent<Player>(entityA);
					aIsPlayer = true;
				}
				catch(...){}

				try {
					g_World.GetComponent<Player>(entityB);
					bIsPlayer = true;
				}
				catch (...) {}

				try {
					g_World.GetComponent<Obstacle>(entityA);
					aIsObstacle = true;
				}
				catch (...) {}

				try {
					g_World.GetComponent<Obstacle>(entityB);
					bIsObstacle = true;
				}
				catch (...) {}

				if ((aIsPlayer && bIsObstacle) || (bIsPlayer && aIsObstacle)) {
					Entity obstacleEntity = aIsObstacle ? entityA : entityB;
					auto& obstacle = g_World.GetComponent<Obstacle>(obstacleEntity);

					if (obstacle.deadly && OnPlayerHit) {
						OnPlayerHit();
					}
				}
			}
		}
	}
}

bool CollisionSystem::CheckCollision(Entity a, Entity b) {
	auto& transformA = g_World.GetComponent<Transform>(a);
	auto& colliderA = g_World.GetComponent<Collider>(a);
	auto& transformB = g_World.GetComponent<Transform>(b);
	auto& colliderB = g_World.GetComponent<Collider>(b);

	sf::FloatRect rectA(
		sf::Vector2f(transformA.position.x + colliderA.offset.x,
					 transformA.position.y + colliderA.offset.y),
		sf::Vector2f(colliderA.size.x, colliderA.size.y)
	);

	sf::FloatRect rectB(
		sf::Vector2f(transformB.position.x + colliderB.offset.x,
			transformB.position.y + colliderB.offset.y),
		sf::Vector2f(colliderA.size.x, colliderA.size.y)
	);

	bool haveIntersection = false;
	if (rectA.findIntersection(rectB))
	{
		bool haveIntersection = true;
	}

	return haveIntersection;
}