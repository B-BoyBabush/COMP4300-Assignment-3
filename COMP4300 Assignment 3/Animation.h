#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Animation
{
public:
	typedef std::pair<int, int> IntPair;

	std::string			m_name{};
	unsigned int		m_animFrame{ 1 };
	unsigned int		m_totalFrames{};
	unsigned int		m_speed{};
	unsigned int		m_gameFrame{ 0 };

	std::string					m_textureName{};
	sf::Vector2i				m_size{};
	std::vector<sf::Vector2i>	m_framePos{};

	const sf::Texture*	m_txtrPtr{ nullptr };

	Animation(const std::string& name, const unsigned int& totalFrames, const unsigned int& speed,
		const std::string& textureName, const sf::Vector2i& size, const std::vector<sf::Vector2i> framePos)
		: m_name		{ name }
		, m_totalFrames	{ totalFrames }
		, m_speed		{ speed }
		, m_textureName	{ textureName }
		, m_size		{ size }
		, m_framePos	{ framePos }
	{}

	Animation()
	{}
};