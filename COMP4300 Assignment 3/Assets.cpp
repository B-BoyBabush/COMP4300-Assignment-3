#pragma once
#include <iostream>
#include "Assets.h"
#include "SFML/Graphics.hpp"

sf::Texture& Assets::addTexture(const std::string& textureName, const std::string& filename)
{
	m_textures.emplace(textureName, sf::Texture{ filename, false }); //Add texture to map

	return m_textures[textureName]; //Return added texture
}

sf::Texture& Assets::getTexture(const std::string& textureName)
{
	return m_textures[textureName];
}

Animation& Assets::addAnimation(const std::string& animName, Animation& anim)
{
	m_animations.emplace(animName, std::move(anim));

	return m_animations[animName];
}

Animation& Assets::getAnimation(const std::string& animName)
{
	return m_animations[animName];
}