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






	std::tuple<int, char, bool> somal{};
	somal = std::make_tuple(5, 'h', true);

	std::cout << std::get<int>(somal) << " " << std::get<char>(somal) << '\n';


	somal = std::make_tuple(10, 'j', false);

	std::cout << std::get<int>(somal) << " " << std::get<char>(somal) << '\n';

	std::tuple<CTransform, CInput> jericho{};
	jericho = std::make_tuple<CTransform, CInput>(Vec2{ 13.0f, 13.0f }, CInput{});


	typedef std::tuple<CTransform, CBoundingBox, CInput, CAnimation> compTuple;

	Entity ent{};
	ent.addComponent<CTransform>(Vec2{ 1.0f, 1.0f });
	






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