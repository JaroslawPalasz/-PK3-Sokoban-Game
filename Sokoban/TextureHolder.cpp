#include "TextureHolder.h"

TextureHolder::TextureHolder()
{
	load_all();
}

void TextureHolder::load(const Textures::Textures &id, const std::string &filename)
{
	sf::Texture * texture = new sf::Texture;
	//error loading file
	if (!texture->loadFromFile(filename))
	{
		std::cout << "Error loading file " + filename << std::endl;
	}

	TextureMap.insert(std::make_pair(id, texture));
}

sf::Texture & TextureHolder::get(const Textures::Textures &id)
{
	auto found = TextureMap.find(id);
	//texture doesn't exist, fatal error
	assert(found != TextureMap.end());
	return *found->second;
}

void TextureHolder::load_all()
{
	load(Textures::Textures::WALL, "textures/wall.png");
	load(Textures::Textures::CRATE, "textures/crate.png");
	load(Textures::Textures::GROUND, "textures/ground.png");
	load(Textures::Textures::NONE, "textures/none.png");
	load(Textures::Textures::OBJ, "textures/obj.png");
	load(Textures::Textures::BACKGROUND, "textures/background.png");
	load(Textures::Textures::CRATE_ON_OBJ, "textures/crate_on_obj.png");

	load(Textures::Textures::PLAYER_DOWN, "textures/player_down.png");
	load(Textures::Textures::PLAYER_UP, "textures/player_up.png");
	load(Textures::Textures::PLAYER_LEFT, "textures/player_left.png");
	load(Textures::Textures::PLAYER_RIGHT, "textures/player_right.png");
}
