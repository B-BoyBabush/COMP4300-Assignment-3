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
	unsigned int		m_totalFrames{ 1 };
	unsigned int		m_speed{};
	unsigned int		m_gameFrame{ 0 };

	std::string			m_textureName{};
	sf::IntRect			m_intRect{};
	const sf::Texture*	m_txtrPtr{ nullptr };

	Animation(const std::string& name, const unsigned int& totalFrames, const unsigned int& speed,
		const std::string& textureName, const sf::IntRect intRect)
		: m_name		{ name }
		, m_totalFrames	{ totalFrames }
		, m_speed		{ speed }
		, m_textureName	{ textureName }
		, m_intRect		{ intRect }
	{}

	Animation()
	{}
};