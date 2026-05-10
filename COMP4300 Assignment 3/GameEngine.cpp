#pragma once
#include "GameEngine.h"

inline void GameEngine::init()
{
	m_assets.addTexture("Mario", "C:/Libraries/Assets/Mario.png");
	
	//DELETE
	std::vector<sf::Vector2i> rectPos{ { {29, 62}, {52, 62}, {74, 62} } };
	Animation animObj{ "MarioWalk", 3U, 13U, "Mario", sf::Vector2i{16, 31}, rectPos };
	animObj.m_txtrPtr = &m_assets.getTexture("Mario");
	m_assets.addAnimation("MarioWalk", animObj);
	//DELETE

	m_window.setFramerateLimit(60);
}

inline void GameEngine::sUserInput()
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

inline void GameEngine::sMovement()
{
	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CTransform>())
		{
			entity->getComponent<CTransform>().pos += entity->getComponent<CTransform>().vel;
		}
	}
}

inline void GameEngine::sAnimate()
{
	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CAnimation>())
		{
			Animation& anim = entity->getComponent<CAnimation>().m_animation;
			anim.m_animFrame = (anim.m_gameFrame / anim.m_speed) % anim.m_totalFrames;
			anim.m_gameFrame++;
		}
	}
}

inline void GameEngine::sRender()
{
	m_window.clear(sf::Color::Black);

	for (EntityPtr entity : m_entities.getEntities())
	{
		if (entity->hasComponent<CAnimation>())
		{
			Animation& anim = entity->getComponent<CAnimation>().m_animation;
			sf::Sprite sprite{ *anim.m_txtrPtr, sf::IntRect{ anim.m_framePos[anim.m_animFrame], anim.m_size } };
			sprite.setPosition(entity->getComponent<CTransform>().pos.toVec2f());
			sprite.scale({ 5.0f, 5.0f });

			m_window.draw(sprite);
		}
	}

	m_window.display();
}

inline void GameEngine::spawnPlayer()
{
	EntityPtr p = m_entities.addEntity("player");
	p->addComponent<CTransform>(Vec2{ 200.0f, 400.0f }, Vec2{ 1.0f, 0.0f }, Vec2{ 1.0f, 1.0f }, 0.0f);
	p->addComponent<CAnimation>(m_assets.getAnimation("MarioWalk"));
}

inline void GameEngine::spawnEnemy()
{
	return;
}

inline void GameEngine::run()
{
	spawnEnemy();

	spawnPlayer();

	while (m_window.isOpen())
	{
		m_entities.update();

		sUserInput();
		sMovement();
		sAnimate();
		sRender();

		m_currentFrame++;
	}
}