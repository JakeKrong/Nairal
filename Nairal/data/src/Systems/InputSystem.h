#pragma once
#include "System.h"
#include "../Core/World.h"
#include <SFML/Window/Event.hpp>

class InputSystem :public System {
public:
	void Update();
	void HandleEvents(const sf::Event& event);

private:
	bool m_LeftPressed{ false };
	bool m_RightPressed{ false };
	bool m_JumpPressed{ false };
};