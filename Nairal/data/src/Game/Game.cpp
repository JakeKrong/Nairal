#include "Game.h"
#include "../Components/Component.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/InputSystem.h"
#include "../Systems/LifetimeSystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

Game::Game()
    : m_Window(sf::VideoMode({ 800, 600 }), "Nairal: Dodge This!", sf::Style::Close)
{
    m_Window.setFramerateLimit(60);

    // Load font (you might want to use a real font file)
    if (!m_Font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        // Fallback to default font if file not found
        std::cout << "Warning: Could not load font file. Using default font.\n";
    }
}

Game::~Game() = default;

void Game::Run() {
    sf::Clock clock;

    // Start with playing state
    m_StateManager.ChangeState(std::make_unique<PlayingState>(this));

    while (m_Window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Clamp deltaTime to a max value (0.1s ~ 10 FPS)
        if (deltaTime > 0.1f)
            deltaTime = 0.1f;

		while (auto optEvent = m_Window.pollEvent()) {
			const sf::Event& event = *optEvent;

			if (event.is<sf::Event::Closed>()) {
				m_Window.close();
			}

			m_StateManager.HandleEvent(event);
		}

        m_StateManager.Update(deltaTime);

        m_Window.clear(sf::Color::Black);
        m_StateManager.Render(m_Window);
        m_Window.display();
    }
}

void Game::GameOver() {
    // This will be called by the collision system
    auto playingState = dynamic_cast<PlayingState*>(m_StateManager.m_CurrentState.get());
    if (playingState) {
        int finalScore = playingState->getScore();
        m_StateManager.EnqueueStateChange(std::make_unique<GameOverState>(this, finalScore));
    }
}

void Game::RestartGame() {
    m_StateManager.ChangeState(std::make_unique<PlayingState>(this));
}

// PlayingState Implementation
PlayingState::PlayingState(Game* game)
    : m_Game(game)
    , m_RandomGenerator(m_RandomDevice())
    , m_SpawnDistribution(50.0f, 750.0f)
    , m_ObstacleTypeDistribution(0, 2)
{
}

void PlayingState::Enter() {
    World& world = m_Game->GetWorld();
    world.Init();

    // Register components
    world.RegisterComponent<Transform>();
    world.RegisterComponent<Physics>();
    world.RegisterComponent<Renderable>();
    world.RegisterComponent<Collider>();
    world.RegisterComponent<Player>();
    world.RegisterComponent<Obstacle>();
    world.RegisterComponent<Lifetime>();

    // Register systems
    m_InputSystem = world.RegisterSystem<InputSystem>();
    m_PhysicsSystem = world.RegisterSystem<PhysicsSystem>();
    m_CollisionSystem = world.RegisterSystem<CollisionSystem>();
    m_RenderSystem = world.RegisterSystem<RenderSystem>();
    m_LifetimeSystem = world.RegisterSystem<LifetimeSystem>();
    m_AnimationSystem = world.RegisterSystem<AnimationSystem>();

    // Pass world reference to systems that need it
    m_InputSystem->SetWorld(&world);
    m_PhysicsSystem->SetWorld(&world);
    m_CollisionSystem->SetWorld(&world);
    m_RenderSystem->SetWorld(&world);
    m_LifetimeSystem->SetWorld(&world);
    m_AnimationSystem->SetWorld(&world);

    // Set system signatures
    Signature inputSignature;
    inputSignature.set(world.GetComponentType<Transform>());
    inputSignature.set(world.GetComponentType<Physics>());
    inputSignature.set(world.GetComponentType<Player>());
    world.SetSystemSignature<InputSystem>(inputSignature);

    Signature physicsSignature;
    physicsSignature.set(world.GetComponentType<Transform>());
    physicsSignature.set(world.GetComponentType<Physics>());
    world.SetSystemSignature<PhysicsSystem>(physicsSignature);

    Signature collisionSignature;
    collisionSignature.set(world.GetComponentType<Transform>());
    collisionSignature.set(world.GetComponentType<Collider>());
    world.SetSystemSignature<CollisionSystem>(collisionSignature);

    Signature renderSignature;
    renderSignature.set(world.GetComponentType<Transform>());
    renderSignature.set(world.GetComponentType<Renderable>());
    world.SetSystemSignature<RenderSystem>(renderSignature);

    Signature lifetimeSignature;
    lifetimeSignature.set(world.GetComponentType<Lifetime>());
    world.SetSystemSignature<LifetimeSystem>(lifetimeSignature);

    Signature animationSignature;
    animationSignature.set(world.GetComponentType<Renderable>());
    world.SetSystemSignature<AnimationSystem>(animationSignature);

    //Create background
    Entity background = world.CreateEntity();
    auto& backgroundTexture = m_Game->m_TextureManager.Load("../../../../Nairal/data/Sprites/Background.png");
    world.AddComponent(background, Transform{ {0.0f, 0.0f} });
    world.AddComponent(background, Renderable{ {800.0f, 600.0f}, sf::Color::White, true, &backgroundTexture });
    
    
    sf::Sound& bgm = m_Game->m_SoundManager.Play("../../../../Nairal/data/Audio/Terraria Music - Day.wav");
    bgm.setLooping(true);
    bgm.setVolume(40);
    bgm.play();

    //// Create test hitbox
    //Entity testHitBox = world.CreateEntity();
    //world.AddComponent(testHitBox, Transform{ {100.0f, 480.0f} });
    //world.AddComponent(testHitBox, Renderable{ {30, 30}, sf::Color::Blue, true });

    // Create player
    m_Player = world.CreateEntity();
    world.AddComponent(m_Player, Transform{ {100.0f, 400.0f} });
    world.AddComponent(m_Player, Physics{ {0.0f, 0.0f}, {0.0f, 0.0f}, 1.0f, true });
    auto& playerIdleTexture = m_Game->m_TextureManager.Load("../../../../Nairal/data/Sprites/DinosaurWalk.png");
    world.AddComponent(m_Player, Renderable{ {48, 48}, sf::Color::Blue, true, &playerIdleTexture, {{0,0} , {48, 48} }, true, 100, 108, 0, 4, 0.08f});
    world.AddComponent(m_Player, Collider{ {33, 48} });
    world.AddComponent(m_Player, Player{ 200.0f, 400.0f, false, true });
    m_CollisionSystem->SetPlayer(m_Player);

    // Create ground
    Entity ground = world.CreateEntity();
    auto& groundTexture = m_Game->m_TextureManager.Load("../../../../Nairal/data/Sprites/Ground.png");
    world.AddComponent(ground, Transform{ {0.0f, 532.0f} });
    world.AddComponent(ground, Physics{ {0.0f, 0.0f}, {0.0f, 0.0f}, 1.0f, false });
    world.AddComponent(ground, Renderable{ {800.0f, 68.0f}, sf::Color::Green, true, &groundTexture });
    world.AddComponent(ground, Collider{ {800.0f, 68.0f} });
    world.AddComponent(ground, Obstacle{ ObstacleTypes::Ground, 0.0f, false });

    // Set up collision callback
    m_CollisionSystem->OnPlayerHit = [this]() {
        m_Game->GameOver();
        };

    // Reset game state
    m_SpawnTimer = 0.0f;
    m_SpawnInterval = 2.0f;
    m_GameTime = 0.0f;
    m_Score = 0;
}

void PlayingState::Exit() {
    std::cout << "[PlayingState] Exiting!\n";
    m_InputSystem.reset();
    m_PhysicsSystem.reset();
    m_CollisionSystem.reset();
    m_RenderSystem.reset();
    m_LifetimeSystem.reset();
    m_AnimationSystem.reset();
    m_Game->m_SoundManager.StopAll();
}

void PlayingState::Update(float deltaTime) {
    World& world = m_Game->GetWorld();

    m_GameTime += deltaTime;
    m_SpawnTimer += deltaTime;

    // Update difficulty
    UpdateDifficulty();

    // Spawn obstacles
    if (m_SpawnTimer >= m_SpawnInterval) {
        SpawnObstacle();
        m_SpawnTimer = 0.0f;
    }

    // Update systems
    m_InputSystem->Update();
    m_PhysicsSystem->Update(deltaTime);
    m_CollisionSystem->Update();
    m_LifetimeSystem->Update(deltaTime);
    m_AnimationSystem->Update(deltaTime);

    // Update score
    m_Score = static_cast<int>(m_GameTime * 10);
}

void PlayingState::Render(sf::RenderWindow& window) {
    m_RenderSystem->Update(window);

    // Render UI
    sf::Text scoreText(m_Game->GetFont());
    scoreText.setString("Score: " + std::to_string(m_Score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition({ 10, 10 });
    window.draw(scoreText);

    // Render UI
    sf::Text instrctText(m_Game->GetFont());
    instrctText.setString("A: Move Left\nD: Move Right\nSpace: Jump");
    instrctText.setCharacterSize(24);
    instrctText.setFillColor(sf::Color::Black);
    instrctText.setPosition({ 630, 10 });
    window.draw(instrctText);

    sf::Text timeText(m_Game->GetFont());
    timeText.setString("Time: " + std::to_string(static_cast<int>(m_GameTime)));
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
	timeText.setPosition({ 10, 40 });
    window.draw(timeText);
}

void PlayingState::HandleEvent(const sf::Event& event) {
    m_InputSystem->HandleEvents(event);
}

void PlayingState::SpawnObstacle() {
    World& world = m_Game->GetWorld();

    // Determine obstacle type based on game time
    int obstacleType = 0;
    if (m_GameTime > 5.0f) {
        obstacleType = m_ObstacleTypeDistribution(m_RandomGenerator);
    }

    switch (obstacleType) {
    case 0:
        SpawnMeteor();
        break;
    case 1:
        SpawnCannonball();
        break;
    case 2:
        SpawnMeteor(); // More meteors for higher difficulty
        break;
    }
}

void PlayingState::SpawnMeteor() {
    World& world = m_Game->GetWorld();

    Entity meteor = world.CreateEntity();
    float x = m_SpawnDistribution(m_RandomGenerator);

    world.AddComponent(meteor, Transform{ {x, -60.0f} });
    world.AddComponent(meteor, Physics{ {0.0f, 100.0f + m_GameTime * 10.0f}, {0.0f, 50.0f}, 1.0f, true });
    auto& meteorTexture = m_Game->m_TextureManager.Load("../../../../Nairal/data/Sprites/Meteor.png");
    world.AddComponent(meteor, Renderable{ {36.0f, 60.0f}, sf::Color::Red, true , &meteorTexture});
    world.AddComponent(meteor, Collider{ {30.0f, 30.0f} });
    world.AddComponent(meteor, Obstacle{ ObstacleTypes::Meteor, 1.0f, true });
    world.AddComponent(meteor, Lifetime{ 10.0f, true });
}

void PlayingState::SpawnCannonball() {
    World& world = m_Game->GetWorld();

    Entity cannonball = world.CreateEntity();
    float side = float(m_RandomGenerator() % 2); // 0 = left, 1 = right
    float x = side == 0 ? -55.0f : 855.0f;
    float velocityX = side == 0 ? 200.0f + m_GameTime * 5.0f : -(200.0f + m_GameTime * 5.0f);
    bool xFlip = side == 0 ? true : false;

    world.AddComponent(cannonball, Transform{ {x, 480.0f}, {1.0, 1.0f} });
    world.AddComponent(cannonball, Physics{ {velocityX, 0.0f}, {0.0f, 0.0f}, 1.0f, false });
    auto& birdTexture = m_Game->m_TextureManager.Load("../../../../Nairal/data/Sprites/Bird.png");
    world.AddComponent(cannonball, Renderable{ {63.0f, 54.0f}, sf::Color::Yellow, true, &birdTexture, {{0,0},{63,54}}, true, 63,54, 0, 2, 0.3f, 0.0f, xFlip});
    world.AddComponent(cannonball, Collider{ {50, 30} });
    world.AddComponent(cannonball, Obstacle{ ObstacleTypes::Cannonball, 1.0f, true });
    world.AddComponent(cannonball, Lifetime{ 8.0f, true });
    //std::cout << "THIS CANNONBALL IS FLIPPED? --> " << xFlip << "\n";
}

void PlayingState::UpdateDifficulty() {
    // Increase spawn rate over time
    float baseInterval = 2.0f;
    float difficultyMultiplier = std::max(0.3f, 1.0f - (m_GameTime * 0.02f));
    m_SpawnInterval = baseInterval * difficultyMultiplier;
}

int PlayingState::getScore() {
    return m_Score;
}

// GameOverState Implementation
GameOverState::GameOverState(Game* game, int finalScore)
    : m_Game(game)
    , m_FinalScore(finalScore)
	, m_RestartText(game->GetFont())
	, m_ScoreText(game->GetFont())
	, m_GameOverText(game->GetFont())
{
}

void GameOverState::Enter() {

    sf::Sound& deathSound = m_Game->m_SoundManager.Play("../../../../Nairal/data/Audio/death.wav");
    deathSound.setVolume(40);
    deathSound.play();

    m_GameOverText.setFont(m_Game->GetFont());
    m_GameOverText.setString("GAME OVER");
    m_GameOverText.setCharacterSize(48);
    m_GameOverText.setFillColor(sf::Color::Red);
	m_GameOverText.setPosition({ 250, 200 });

    m_ScoreText.setFont(m_Game->GetFont());
    m_ScoreText.setString("Final Score: " + std::to_string(m_FinalScore));
    m_ScoreText.setCharacterSize(24);
    m_ScoreText.setFillColor(sf::Color::White);
	m_ScoreText.setPosition({ 320, 280 });

    m_RestartText.setFont(m_Game->GetFont());
    m_RestartText.setString("Press R to Restart or ESC to Quit");
    m_RestartText.setCharacterSize(18);
    m_RestartText.setFillColor(sf::Color::White);
	m_RestartText.setPosition({ 270, 350 });
}

void GameOverState::Exit() {
    // Cleanup if needed
}

void GameOverState::Update(float deltaTime) {
    // No update logic needed for game over state
}

void GameOverState::Render(sf::RenderWindow& window) {
    // Draw semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));
    window.draw(overlay);

    window.draw(m_GameOverText);
    window.draw(m_ScoreText);
    window.draw(m_RestartText);
}

void GameOverState::HandleEvent(const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::R) {
            m_Game->RestartGame();
        }
        else if (keyPressed->code == sf::Keyboard::Key::Escape) {
            m_Game->GetWindow().close();
        }
    }
}