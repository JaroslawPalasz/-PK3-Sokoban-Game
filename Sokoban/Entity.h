#pragma once

#include <SFML/Graphics.hpp>

#include "TextureHolder.h"

//class representing all of the tiles - wall, ground etc
class Entity : public sf::Drawable
{
public:
	//every instance of Entity has the pointer to textures
	static TextureHolder * texture_holder;
	//tile size 
	static const int size;

	Entity(const Textures::Textures &type, const sf::Vector2i &entity_position);
	//has to be default constructor
	Entity() {}
	
	//getters
	sf::Vector2i get_position(); 
	Textures::Textures get_texture_type();
	sf::Sprite get_sprite()
	{
		return entity_sprite;
	}

	void set_texture_type(const Textures::Textures &type);

private:
	sf::Sprite entity_sprite;
	Textures::Textures texture_type;

	virtual void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(entity_sprite);
	}
};