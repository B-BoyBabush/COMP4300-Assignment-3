#pragma once
#include "SFML/Graphics.hpp"
#include "EntityManager.h"
#include "Assets.h"

class GameEngine
{
	sf::RenderWindow	m_window{ sf::VideoMode({1600, 900}), "Boshko's Window", sf::State::Windowed };
	EntityManager		m_entities{};
	size_t				m_currentFrame{ 1 };
	Assets				m_assets{};

public:
	GameEngine()
	{
	}

	void init()
	{
		m_assets.addTexture("AxeKnight", "C:/Libraries/Assets/AxeKnight.png");
		m_assets.addTexture("Eyellure", "C:/Libraries/Assets/Eyellure.png");

		m_window.setFramerateLimit(60);
	}

	void sUserInput()
	{
		while (std::optional<sf::Event> event = m_window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				m_window.close();
			}

			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					m_window.close();
			}
		}

		return;
	}

	void sMovement()
	{
		for (std::shared_ptr<Entity> e : m_entities.getEntities())
		{
			if (e->hasComponent<CTransform>())
			{
				//position += velocity
				e->getComponent<CTransform>().pos += e->getComponent<CTransform>().vel;
			}
		}
	}

	void sRender()
	{
		m_window.clear(sf::Color::Black);

		for (std::shared_ptr<Entity> e : m_entities.getEntities())
		{
			if (e->hasComponent<CAnimation>())
			{
				e->getComponent<CAnimation>().m_animation.update(m_currentFrame);
				sf::Sprite sprite{ m_assets.getTexture(e->getComponent<CAnimation>().m_animation.m_textureName),
											e->getComponent<CAnimation>().m_animation.m_textureRect };
				sprite.setPosition({ e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y });
				m_window.draw(sprite);
			}
		}

		m_window.display();
	}

	void spawnPlayer()
	{
		std::shared_ptr<Entity> p = m_entities.addEntity("player");
		p->addComponent<CTransform>(Vec2{ 1500.0f, 400.0f }, Vec2{ -1.0f, 0.0f }, Vec2{ 1.0f, 1.0f }, 0.0f);
		p->addComponent<CAnimation>(CAnimation{ "Player", Vec2{30.0f, 30.0f}, 4, 15, "AxeKnight", sf::IntRect{{18, 10}, {40, 70}} });
	}

	void spawnEnemy()
	{
		std::shared_ptr<Entity> p = m_entities.addEntity("Enemy");
		p->addComponent<CTransform>(Vec2{ 300.0f, 300.0f }, Vec2{ 0.01f, 0.01f }, Vec2{ 1.0f, 1.0f }, 0.0f);
		p->addComponent<CAnimation>(CAnimation{ "Enemy", Vec2{30.0f, 30.0f}, 1, 1, "Eyellure", sf::IntRect{{0, 0}, {256, 256}} });
	}

	void run()
	{
		spawnEnemy();

		spawnPlayer();

		while (m_window.isOpen())
		{
			m_entities.update();

			sUserInput();
			sMovement();
			sRender();

			m_currentFrame++;
		}
	}
};