#include "GameEngine.h"
#include "Action.h"
#include "Scene_Play.h"
#include "Animation.h"

#include "SFML/Graphics.hpp"

#include <memory>
#include <map>
#include <fstream>

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

void GameEngine::loadAssets()
{
	std::ifstream fin{ "C:/Libraries/Assets/AssetsConfig.txt"};

	std::string spriteName{};
	unsigned int totalFrames{};
	unsigned int animSpeed{};
	std::string filename{};

	while (fin >> spriteName)
	{
		fin >> totalFrames >> animSpeed >> filename;

		const sf::Texture* tempTxtr = &m_assets.addTexture(spriteName, filename);

		sf::IntRect tempRect = sf::IntRect{ {0, 0}, {static_cast<int>(tempTxtr->getSize().x / totalFrames), static_cast<int>(tempTxtr->getSize().y)} };
		Animation animObj = Animation{ spriteName, totalFrames, animSpeed, spriteName, tempRect };
		animObj.m_txtrPtr = &m_assets.getTexture(spriteName);
		m_assets.addAnimation(spriteName, animObj);
	}
}

void GameEngine::init()
{
	loadAssets();
	
	m_window.setFramerateLimit(60);
	m_window.setKeyRepeatEnabled(false);

	m_scenes["play"] = std::make_shared<Scene_Play>(this);
	changeScene("play");

	return;
}