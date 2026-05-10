#pragma once
#include <SFML/Window.hpp>
#include "EntityManager.h"
#include "Assets.cpp"

class GameEngine
{
	sf::RenderWindow	m_window{ sf::VideoMode({1600, 900}), "Boshko's Window", sf::State::Windowed };
	EntityManager		m_entities{};
	size_t				m_currentFrame{ 1 };
	Assets				m_assets{};

public:
	GameEngine() {}

	void init();
	void run();
	void spawnPlayer();
	void spawnEnemy();
	void sRender();
	void sMovement();
	void sUserInput();
	//void sAnimate();
};