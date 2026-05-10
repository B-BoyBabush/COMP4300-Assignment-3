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