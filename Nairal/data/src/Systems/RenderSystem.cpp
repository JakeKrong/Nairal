#include "RenderSystem.h"
#include "../Components/Component.h"
#include "../Core/World.h"
#include <SFML/Graphics/RectangleShape.hpp>

extern World g_World;

void RenderSystem::Update(sf::RenderWindow& window) {
	for (auto const& entity : m_Entities) {
		auto& transform = g_World.GetComponent<Transform>(entity);
		auto& renderable = g_World.GetComponent<Renderable>(entity);

		if (!renderable.visible) continue;

		sf::RectangleShape shape(renderable.size);
		shape.setPosition(transform.position);
		shape.setFillColor(renderable.color);
		shape.setRotation(sf::degrees(transform.rotation));
		shape.setScale(transform.scale);

		window.draw(shape);

	}
}