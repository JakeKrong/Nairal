#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

enum class GameState {
    Menu,
    Playing,
    GameOver
};

class IState {
public:
    virtual ~IState() = default;
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual void HandleEvent(const sf::Event& event) = 0;
};

class StateManager {
public:
    void ChangeState(std::unique_ptr<IState> newState);
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);
    void HandleEvent(const sf::Event& event);

    std::unique_ptr<IState> m_CurrentState;

    //Added
    std::unique_ptr<IState> m_PendingState = nullptr;
    bool m_StateChangePending = false;

    void EnqueueStateChange(std::unique_ptr<IState> newState);
};