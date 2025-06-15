#pragma once
#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Color.hpp>

struct Renderable {
	sf::Vector2f size{ 32.0f, 32.0f };
	sf::Color color{ sf::Color::White };
	bool visible{ true };
};