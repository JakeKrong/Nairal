#include<SFML/Graphics.hpp>

class dump
{
	void sfmlWindow() {
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
	}
};