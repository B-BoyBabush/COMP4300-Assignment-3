#pragma once
#include "SFML/Graphics.hpp"
#include "EntityManager.h"
#include "Assets.h"

class GameEngine
{
	sf::RenderWindow m_window{};
	EntityManager m_entities{};
	unsigned int m_currentFrame{ 1 };
	Assets assets{};

	GameEngine()
	{}

	void init()
	{

	}

	void sRender()
	{
		m_window.clear(sf::Color::Black);


		m_window.display();
	}

	void spawnPlayer()
	{
		//std::shared_ptr<Entity> p = m_entities.addEntity("player");
		//p->cTransform = std::make_shared<CTransform>(Vec2{ 300.0f, 300.0f }, Vec2{ 0.0f, 0.0f });
		//p->cInput = std::make_shared<CInput>();
		//p->cAnimation = std::make_shared<CAnimation>();

	}

	void run()
	{
		init();
		spawnPlayer();

		while (m_window.isOpen())
		{

		}

	}
};