#pragma once

#include <string>
#include <map>
#include <iostream>
#include <assert.h>
#include <SFML/Graphics.hpp>

//enum class containing all of the textures
namespace Textures
{
	enum class Textures {
		CRATE, GROUND, NONE, OBJ, WALL, CRATE_ON_OBJ, BACKGROUND,
		PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT
	};
}

class TextureHolder
{
public:
	TextureHolder();
	//loads texture from file
	void load(const Textures::Textures &id, const std::string &filename);
	sf::Texture& get(const Textures::Textures &id);
private:
	//map containing id - texture pair
	std::map<Textures::Textures, std::unique_ptr<sf::Texture>> TextureMap;

	void load_all();
};
