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

void GameEngine::loadAssets()
{
	const sf::Texture* tempTxtr = &m_assets.addTexture("MarioWalk", "C:/Libraries/Assets/SS-MarioWalk.png");

	sf::IntRect tempRect = { {0, 0}, {static_cast<int>(tempTxtr->getSize().x) / 3, static_cast<int>(tempTxtr->getSize().y)} };
	Animation animObj{ "MarioWalk", 3U, 13U, "MarioWalk", tempRect };
	animObj.m_txtrPtr = &m_assets.getTexture("MarioWalk");
	m_assets.addAnimation("MarioWalk", animObj);

	tempTxtr = &m_assets.addTexture("MarioIdle", "C:/Libraries/Assets/SS-MarioIdle.png");

	tempRect = { {0, 0}, {static_cast<int>(tempTxtr->getSize().x), static_cast<int>(tempTxtr->getSize().y)} };
	animObj = { "MarioIdle", 1U, 13U, "MarioIdle", tempRect };
	animObj.m_txtrPtr = &m_assets.getTexture("MarioIdle");
	m_assets.addAnimation("MarioIdle", animObj);

	tempTxtr = &m_assets.addTexture("MarioJump", "C:/Libraries/Assets/SS-MarioJump.png");

	tempRect = { {0, 0}, {static_cast<int>(tempTxtr->getSize().x), static_cast<int>(tempTxtr->getSize().y)} };
	animObj = { "MarioJump", 1U, 13U, "MarioJump", tempRect };
	animObj.m_txtrPtr = &m_assets.getTexture("MarioJump");
	m_assets.addAnimation("MarioJump", animObj);

	tempTxtr = &m_assets.addTexture("Bowser", "C:/Libraries/Assets/SS-Bowser.png");

	tempRect = { {0, 0}, {static_cast<int>(tempTxtr->getSize().x) / 4, static_cast<int>(tempTxtr->getSize().y)} }; //4 will be changed to be part of the load assets config
	animObj = { "Bowser", 4U, 13U, "Bowser", tempRect };
	animObj.m_txtrPtr = &m_assets.getTexture("Bowser");
	m_assets.addAnimation("Bowser", animObj);

	tempTxtr = &m_assets.addTexture("Ground", "C:/Libraries/Assets/SS-Ground.png");

	tempRect = { {0, 0}, {static_cast<int>(tempTxtr->getSize().x), static_cast<int>(tempTxtr->getSize().y)} };
	animObj = { "Ground", 1U, 15U, "Ground", tempRect };
	animObj.m_txtrPtr = &m_assets.getTexture("Ground");
	m_assets.addAnimation("Ground", animObj);

	tempTxtr = &m_assets.addTexture("Block", "C:/Libraries/Assets/SS-Block.png");

	tempRect = { {0, 0}, {static_cast<int>(tempTxtr->getSize().x), static_cast<int>(tempTxtr->getSize().y)} };
	animObj = { "Block", 1U, 15U, "Block", tempRect };
	animObj.m_txtrPtr = &m_assets.getTexture("Block");
	m_assets.addAnimation("Block", animObj);

	tempTxtr = &m_assets.addTexture("Brick", "C:/Libraries/Assets/SS-Brick.png");

	tempRect = { {0, 0}, {static_cast<int>(tempTxtr->getSize().x), static_cast<int>(tempTxtr->getSize().y)} };
	animObj = { "Brick", 1U, 15U, "Brick", tempRect };
	animObj.m_txtrPtr = &m_assets.getTexture("Brick");
	m_assets.addAnimation("Brick", animObj);
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