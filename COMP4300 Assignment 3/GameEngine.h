#pragma once
#include <SFML/Window.hpp>
#include "Assets.h"

class Scene;

class GameEngine
{
	Assets											m_assets{};
	sf::RenderWindow								m_window{ sf::VideoMode({1600, 900}), "Boshko's Window", sf::State::Windowed };
	std::string										m_currentScene{ "play" };
	std::map<std::string, std::shared_ptr<Scene>>	m_scenes{};

public:
	GameEngine() {}

	const void sUserInput();
	void changeScene(const std::string& scene);
	void run();
	void init();

	const sf::RenderWindow& getWindow() const { return m_window; }

	sf::RenderWindow& setWindow() { return m_window; }
	Assets& getAssets() { return m_assets; }
};