#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class Assets
{
public:
	std::map<std::string, sf::Texture> m_textures{};

	Assets()
	{}

	sf::Texture& addTexture(const std::string& textureName, const std::string& filename);

	sf::Texture& getTexture(const std::string& textureName);
};