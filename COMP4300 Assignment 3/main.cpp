#include "Vec2.h"
#include "EntityManager.h"
#include "Entity.h"
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

	sf::Sprite sprite{ texture };
	sprite.setOrigin(sf::Vector2f{ sprite.getTextureRect().size.x / 2.0f, sprite.getTextureRect().size.y / 2.0f });

	//Old^^^

	EntityManager EntityMgmt{};
	EntityMgmt.addEntity("player");
	EntityMgmt.update();



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
		window.draw(sprite);

		for (auto& e : EntityMgmt.getEntities())
		{
			if (e->cAnimation)
				window.draw(e->cAnimation->sprite);
		}

		window.display();

		sprite.move({ 0.01f, 0.01f });
	}

	return 0;
}