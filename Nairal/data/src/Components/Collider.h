#pragma once
#include <SFML/System/Vector2.hpp>

struct Collider {
	sf::Vector2f size{ 0.0f, 0.0f };
	sf::Vector2f offset{ 0.0f, 0.0f };
	bool isTrigger{ false };
};