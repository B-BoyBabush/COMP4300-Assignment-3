#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Animation
{
public:
	std::string		m_name{};
	Vec2			m_size{};
	unsigned int	m_animFrame{ 1 };
	unsigned int	m_totalFrames{};
	unsigned int	m_speed{};
	std::string		m_textureName{};
	sf::IntRect		m_textureRect{};
	int				startX{};

	Animation(const std::string& name, const Vec2& size, const unsigned int& totalFrames, const unsigned int& speed, const std::string& textureName, const sf::IntRect& textureRect)
		: m_name		{ name }
		, m_size		{ size }
		, m_totalFrames	{ totalFrames }
		, m_speed		{ speed }
		, m_textureName	{ textureName }
		, m_textureRect	{ textureRect }
		, startX		{ textureRect.position.x }//TRASH METHOD - GET RID OF IT!
	{}

	Animation() {}

	void update(const size_t& m_currentFrame)
	{
		m_animFrame = (m_currentFrame / m_speed) % m_totalFrames;
		m_textureRect.position.x = startX + m_animFrame * m_textureRect.size.x; //Issue is that if I use
		//pos.x += m_animFrame * size.x then when animFrame gets back to zero, pos.x will be a high value and just keep going up
		//startX is used to capture the original x value, but this system is lowkey trash rn tbh rizz
	}
};
//