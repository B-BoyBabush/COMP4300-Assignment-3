#pragma once
#include "Assets.h"

inline sf::Texture& Assets::addTexture(const std::string& textureName, const std::string& filename)
{
	m_textures.emplace(textureName, sf::Texture{ filename, false }); //Add texture to map

	return m_textures[textureName]; //Return added texture
}

inline sf::Texture& Assets::getTexture(const std::string& textureName)
{
	return m_textures[textureName];
}

inline Animation& Assets::addAnimation(const std::string& animName, Animation& anim)
{
	m_animations.emplace(animName, std::move(anim));

	return m_animations[animName];
}

inline Animation& Assets::getAnimation(const std::string& animName)
{
	return m_animations[animName];
}