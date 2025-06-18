#include "InputSystem.h"
#include "Component.h"
#include "World.h"
#include <SFML/Window/Keyboard.hpp>

extern World g_World;

void InputSystem::Update() {
	m_LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	m_RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	m_JumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	for (auto const& entity : m_Entities) {
		auto& player = g_World.GetComponent<Player>(entity);
		auto& physics = g_World.GetComponent<Physics>(entity);
		auto& transform = g_World.GetComponent<Transform>(entity);

		physics.velocity = 0.0f;

		//Horizontal movement
		if (m_LeftPressed) {
			physics.velocity.x = -player.speed;
		}
		if (m_RightPressed) {
			physics.velocity.x = player.speed;
		}

		//Jump
		if (m_JumpPressed && player.isGrounded && player.canJump) {
			physics.velocity.y = -player.jumpForce;
			player.isGrounded = false;
			player.canJump = false;
		}

		//Check if grounded based on y-coords
		if (transform.position.y >= 500.0f) {
			player.isGrounded = true;
		}
		else {
			player.isGrounded = false;
		}

		if (!m_JumpPressed) {
			player.canJump = true;
		}
	}
}