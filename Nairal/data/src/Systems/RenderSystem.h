#pragma once
#include "System.h"
#include <SFML/Graphics/RenderWindow.hpp>

class RenderSystem : public System {
public:
    void Update(sf::RenderWindow& window);
};