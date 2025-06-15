#pragma once
#include <SFML/System/Vector2.hpp>

struct Collider {
	sf::Vector2f size{ 32.0f, 32.0f };
	sf::Vector2f offset{ 0.0f, 0.0f };
	bool isTrigger{ false };
};