#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Assets
{
public:
	std::map<std::string, sf::Texture> m_textures{};
	std::map<std::string, Animation> m_animations{};

	Assets()
	{}

	sf::Texture& addTexture(const std::string& textureName, const std::string& filename);

	sf::Texture& getTexture(const std::string& textureName);

	Animation& addAnimation(const std::string& animName, Animation& anim);

	Animation& getAnimation(const std::string& animName);
};