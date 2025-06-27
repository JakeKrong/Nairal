#pragma once
#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

struct Renderable {
	sf::Vector2f size{ 32.0f, 32.0f };
	sf::Color color{ sf::Color::White };
	bool visible{ true };
	sf::Texture* texture = nullptr;

	sf::IntRect textureRect{};
	bool animated = false;
	int frameWidth = 0, frameHeight = 0;
	int currentFrame = 0, totalFrames = 0;
	float frameTime = 0.3f, timeSinceLastFrame = 0.0f;
	bool flipX = false;
};