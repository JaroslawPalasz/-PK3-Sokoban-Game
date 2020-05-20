#pragma once

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class Player : public sf::Drawable
{
public:
	Player(TextureHolder* _texture_holder, const int _size);
	TextureHolder* texture_holder;

	//move methods
	void move(const std::string &_direction);
	void move_back(const std::string &_direction);

	//set position of player_sprite
	void set_position(const sf::Vector2i & pos);
	//getters 
	sf::Vector2i get_position();
	std::string &get_direction();

private:
	//tile size
	const int size;
	sf::Sprite player_sprite;

	std::string move_direction;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(player_sprite);
	}
};