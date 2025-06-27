#include "InputSystem.h"
#include "../Components/Component.h"
#include "../Core/World.h"
#include <SFML/Window/Keyboard.hpp>

void InputSystem::Update() {
    if (!m_World) return;

	m_LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
	m_RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	m_JumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    for (auto const& entity : m_Entities) {
        auto& player = m_World->GetComponent<Player>(entity);
        auto& physics = m_World->GetComponent<Physics>(entity);
        auto& transform = m_World->GetComponent<Transform>(entity);
        auto& render = m_World->GetComponent<Renderable>(entity);

        // Horizontal movement
        physics.velocity.x = 0.0f;
        if (m_LeftPressed) {
            physics.velocity.x = -player.speed;
            render.flipX = true;
        }
        if (m_RightPressed) {
            physics.velocity.x = player.speed;
            render.flipX = false;
        }

        if(!player.isGrounded || (!m_LeftPressed && !m_RightPressed))
            render.currentFrame = 1;

        // Jump (only if grounded and can jump)
        if (m_JumpPressed && player.isGrounded && player.canJump) {
            physics.velocity.y = -player.jumpForce;
            player.isGrounded = false;
            player.canJump = false;
        }

        // Reset jump ability when not pressing jump
        if (!m_JumpPressed) {
            player.canJump = true;
        }

        // Keep player within screen bounds
        if (transform.position.x < 0) {
            transform.position.x = 0;
        }
        else if (transform.position.x > 768) { // 800 - 32 (player width)
            transform.position.x = 768;
        }
    }
}

void InputSystem::HandleEvents(const sf::Event& event) {
	// Handle discrete input events if needed
}