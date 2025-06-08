// Nairal.cpp : Defines the entry point for the application.
#include <iostream>
#include <chrono>
#include <thread>
#include "GameStateManager.h"
#include<optional>
#include <SFML/Graphics.hpp>


#include "main.h"

class Nairal
{
	GameStateManager stateManager;

public:
	void Run()
	{
		const int targetFPS = 60;
		const std::chrono::milliseconds frameDuration(1000 / targetFPS);
		
		//using clock = std::chrono::high_resolution_clock;
		//std::atomic<bool> running = true;
		bool isRunning = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		int frameCount = 0;

		//stateManager.ChangeState(std::make_unique<ExplorationState>());

		std::cout << "Engine started. Press Ctrl+C to exit. \n";

		while (isRunning)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> delta = currentTime - lastTime;
			lastTime = currentTime;

			ProcessInput();
			Update(delta.count());
			Render();

			frameCount++;
			std::cout << "Frame: " << frameCount << " | Delta Time: " << delta.count() << "s" << std::endl;

			std::this_thread::sleep_until(currentTime + frameDuration);

			if (frameCount >= 3000) isRunning = false; // temporary exit after 300 frames
		}
	}

private:
	void ProcessInput(){
		std::cout << "\n[Input]";
	}

	void Update(float deltaTime) {
		std::cout << "[Update]";
	}

	void Render() {
		std::cout << "[Render]";
	}
};

int main()
{
	//Nairal nairal;
	//nairal.Run();
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3 + C++20");

	while (window.isOpen()) 
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is < sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear();
		window.display();
	}
	return 0;
}
