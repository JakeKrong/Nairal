#pragma once
#include "StateManager.h"
#include "../Core/World.h"
#include "../Systems/System.h"
#include "../Core/TextureManager.h"
#include "../Core/SoundManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <random>

class PlayingState;
class GameOverState;

class Game {
public:
    Game();
    ~Game();

    void Run();
    void GameOver();
    void RestartGame();

    sf::RenderWindow& GetWindow() { return m_Window; }
    World& GetWorld() { return m_World; }
    sf::Font& GetFont() { return m_Font; }

private:
    sf::RenderWindow m_Window;
    StateManager m_StateManager;
    World m_World;
    sf::Font m_Font;
    TextureManager  m_TextureManager;
    SoundManager m_SoundManager;


    friend class PlayingState;
    friend class GameOverState;
};

// Game States
class PlayingState : public IState {
public:
    PlayingState(Game* game);

    void Enter() override;
    void Exit() override;
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;
    int getScore();

private:
    Game* m_Game;
    Entity m_Player;
    float m_SpawnTimer{ 0.0f };
    float m_SpawnInterval{ 2.0f };
    float m_GameTime{ 0.0f };
    int m_Score{ 0 };

    std::random_device m_RandomDevice;
    std::mt19937 m_RandomGenerator;
    std::uniform_real_distribution<float> m_SpawnDistribution;
    std::uniform_int_distribution<int> m_ObstacleTypeDistribution;

    void SpawnObstacle();
    void SpawnMeteor();
    void SpawnCannonball();
    void UpdateDifficulty();

    // Systems
    Ref<class InputSystem> m_InputSystem;
    Ref<class PhysicsSystem> m_PhysicsSystem;
    Ref<class CollisionSystem> m_CollisionSystem;
    Ref<class RenderSystem> m_RenderSystem;
    Ref<class LifetimeSystem> m_LifetimeSystem;
    Ref<class AnimationSystem> m_AnimationSystem;
};

class GameOverState : public IState {
public:
    GameOverState(Game* game, int finalScore);

    void Enter() override;
    void Exit() override;
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;

private:
    Game* m_Game;
    int m_FinalScore;
    sf::Text m_GameOverText;
    sf::Text m_ScoreText;
    sf::Text m_RestartText;
};