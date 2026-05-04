#include "Vec2.h"
#include "EntityManager.h"
#include "Entity.h"
#include "GameEngine.cpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
	sf::RenderWindow window{ sf::VideoMode({1600, 900}), "Boshko's Window", sf::State::Windowed };
	sf::Vector2f windowCenter{ static_cast<float>(window.getSize().x / 2.0f), static_cast<float>(window.getSize().y / 2.0f) };

	sf::Texture texture{};	
	if (!texture.loadFromFile("C:/Libraries/Assets/Eyellure.png", false, sf::IntRect{ {0, 0}, {300, 300} }))
	{
		std::cout << "Could not find image!\n";
	}







	Entity ent{};
	ent.addComponent<CTransform>(Vec2{ 1.0f, 1.0f }, Vec2{ 32.0f, 16.0f });
	
	EntityManager mgmt{};
	std::shared_ptr<Entity> player = mgmt.addEntity("player");
	//player->addComponent<CTransform>(Vec2{ 7.0f, 7.0 });


	while (window.isOpen())
	{
		while (std::optional<sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{	window.close();	}

			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();
			}
		}

		window.clear(sf::Color::Black);
	

		window.display();
	}

	return 0;
}