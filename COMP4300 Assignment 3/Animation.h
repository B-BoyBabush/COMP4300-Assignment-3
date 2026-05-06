#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Animation
{
public:
	std::string		m_name{ "none" };
	Vec2			m_size{};
	unsigned int	m_animFrame{ 1 };
	unsigned int	m_totalFrames{  };
	unsigned int	m_speed{  };
	std::string		m_textureName{"none"};
	sf::IntRect		m_textureRect{};

	Animation(const std::string& name, const Vec2& size, const unsigned int& totalFrames, const unsigned int& speed, const std::string& textureName, const sf::IntRect& textureRect)
		: m_name{ name }
		, m_size{ size }
		, m_totalFrames{ totalFrames }
		, m_speed{ speed }
		, m_textureName{ textureName }
		, m_textureRect{ textureRect }
	{}

	Animation() {}
};