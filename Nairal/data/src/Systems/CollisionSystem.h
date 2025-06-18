#pragma once
#include "System.h"
#include <functional>
#include <SFML/System/Vector2.hpp>

class CollisionSystem :public System{
	void Update();
	std::function<void()> OnPlayerHit;

private:
	bool CheckCollision(Entity a, Entity b);
	//sf::Vector2f GetColliderBounds(Entity entity); //Not used?
};