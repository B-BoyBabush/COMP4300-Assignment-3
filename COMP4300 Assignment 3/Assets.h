#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Assets
{
public:
	std::map<std::string, sf::Texture> textures{};

	Assets()
	{}

	sf::Texture& addTexture(const std::string& textureName, const std::string& filename)
	{
		textures.emplace(textureName, sf::Texture{ filename, false, sf::IntRect{ {0,0}, {300, 300}} }); //Add texture to map

		return textures[textureName]; //Return added texture
	}

	sf::Texture& getTexture(const std::string& textureName)
	{
		return textures[textureName];
	}
};