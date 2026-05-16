#pragma once
#include "GameEngine.h"
#include "Animation.h"
#include "SFML/Graphics.hpp"
#include "Scene_Play.h"

const void GameEngine::sUserInput()
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
			
			Action action{ m_scenes[m_currentScene]->getActions(keyPressed->scancode), "START" };
			m_scenes[m_currentScene]->sDoAction(action);
		}

		else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			Action action{ m_scenes[m_currentScene]->getActions(keyReleased->scancode), "END" };
			m_scenes[m_currentScene]->sDoAction(action);
		}
	}

	return;
}

void GameEngine::changeScene(const std::string& scene)
{
	m_currentScene = scene;
	m_scenes[m_currentScene]->init();
}

void GameEngine::run()
{
	while (m_window.isOpen())
	{
		sUserInput();
		m_scenes[m_currentScene]->update();
	}
}

void GameEngine::init()
{
	m_assets.addTexture("Mario", "C:/Libraries/Assets/Mario.png");

	//DELETE
	std::vector<sf::Vector2i> rectPos{ { {29, 62}, {52, 62}, {74, 62} } };
	Animation animObj{ "MarioWalk", 3U, 13U, "Mario", sf::Vector2i{16, 31}, rectPos };
	animObj.m_txtrPtr = &m_assets.getTexture("Mario");
	m_assets.addAnimation("MarioWalk", animObj);
	//DELETE

	m_window.setFramerateLimit(60);
	m_window.setKeyRepeatEnabled(false);

	m_scenes["play"] = std::make_shared<Scene_Play>(this);
	changeScene("play");

	return;
}