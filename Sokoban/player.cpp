#include "player.h"

Player::Player(TextureHolder * _texture_holder, const int _size)
	: texture_holder(_texture_holder)
	, size(_size)
{
	player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_DOWN));

}

void Player::move(const std::string &_direction)
{
	std::string player_texture = "";
	sf::Vector2f movement(0, 0);
	if (_direction =="IsMovingUp")
	{
		move_direction = "IsMovingUp";
		player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_UP));
		movement.y -= size;
	}

	else if (_direction == "IsMovingDown")
	{
		move_direction = "IsMovingDown";
		player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_DOWN));
		movement.y += size;
	}

	else if (_direction == "IsMovingLeft")
	{
		move_direction = "IsMovingLeft";
		player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_LEFT));
		movement.x -= size;
	}

	else if (_direction == "IsMovingRight")
	{
		move_direction = "IsMovingRight";
		player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_RIGHT));
		movement.x += size;
	}

	player_sprite.move(movement);
}

void Player::move_back(const std::string &_direction)
{
	std::string player_texture = "";
	sf::Vector2f movement(0, 0);
	if (_direction == "IsMovingUp")
	{
		player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_UP));
		movement.y += size;
	}

	else if (_direction == "IsMovingDown")
	{
		player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_DOWN));
		movement.y -= size;
	}

	else if (_direction == "IsMovingLeft")
	{
		player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_LEFT));
		movement.x += size;
	}

	else if (_direction == "IsMovingRight")
	{
		player_sprite.setTexture(texture_holder->get(Textures::Textures::PLAYER_RIGHT));
		movement.x -= size;
	}

	player_sprite.move(movement);
}

void Player::set_position(const sf::Vector2i & pos)
{
	player_sprite.setPosition(pos.x*size, pos.y*size);
}

sf::Vector2i Player::get_position()
{
	return sf::Vector2i(player_sprite.getPosition().x / size, player_sprite.getPosition().y / size);
}

std::string &Player::get_direction()
{
	return move_direction;
}
