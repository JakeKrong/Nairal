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
	virtual void HandleEvents(const sf::Event& event) = 0;

private:
	std::unique_ptr<IState> m_CurrentState;
};

class StateManager {
public:
	void ChangeState(std::unique_ptr<IState> newState);
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);
	void HandleEvents(const sf::Event& event);

private:
	std::unique_ptr<IState> m_CurrentState;
};