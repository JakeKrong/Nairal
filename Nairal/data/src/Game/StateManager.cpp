#include "../Game/StateManager.h"

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

    if (m_StateChangePending) {
        ChangeState(std::move(m_PendingState));
        m_StateChangePending = false;
    }
}

void StateManager::Render(sf::RenderWindow& window) {
    if (m_CurrentState) {
        m_CurrentState->Render(window);
    }
}

void StateManager::HandleEvent(const sf::Event& event) {
    if (m_CurrentState) {
        m_CurrentState->HandleEvent(event);
    }
}

void StateManager::EnqueueStateChange(std::unique_ptr<IState> newState) {
    m_PendingState = std::move(newState);
    m_StateChangePending = true;
}