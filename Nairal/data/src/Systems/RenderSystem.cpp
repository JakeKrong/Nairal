#include "RenderSystem.h"
#include "../Components/Component.h"
#include "../Core/World.h"
#include <SFML/Graphics/RectangleShape.hpp>

void RenderSystem::Update(sf::RenderWindow& window) {
    for (auto const& entity : m_Entities) {
        auto& transform = m_World->GetComponent<Transform>(entity);
        auto& renderable = m_World->GetComponent<Renderable>(entity);

        if (!renderable.visible) continue;

        sf::RectangleShape shape(renderable.size);
        shape.setPosition(transform.position);
        shape.setRotation(sf::degrees(transform.rotation));


        if (renderable.texture) {
            shape.setTexture(renderable.texture);

            if (renderable.animated) {
                shape.setTextureRect(renderable.textureRect);
            }
        }
        else {
            shape.setFillColor(renderable.color);
        }
        //Flip
        if (!renderable.flipX) {
            shape.setScale(transform.scale);
            shape.setOrigin({ 0.0f,0.0f });
        }
        else {
            shape.setScale({ -transform.scale.x, transform.scale.y });
            shape.setOrigin({ renderable.size.x,0.0f });
        }

        window.draw(shape);
    }
}