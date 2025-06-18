#pragma once
#include "System.h"
#include <SFML/Graphics/RenderWindow.hpp>

class RenderSystem :public System {
	void Update(sf::RenderWindow& window);
};