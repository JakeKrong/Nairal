#include "StateManager.h"

void StateManager::ChangeState(std::unique_ptr<IState> newState) {
	if (m_CurrentState) {
		m_CurrentState->Exit();
	}

	m_CurrentState = std::move(newState);

	if (m_CurrentState) {
		m_CurrentState->Enter();
	}
}

void StateManager::Update(float deltaTime) {
	if (m_CurrentState) {
		m_CurrentState->Update(deltaTime);
	}
}

void StateManager::Render(sf::RenderWindow& window) {
	if (m_CurrentState) {
		m_CurrentState->Render(window);
	}
}

void StateManager::HandleEvents(sf::Event& event) {
	if (m_CurrentState) {
		m_CurrentState->HandleEvents(event);
	}
}