#include "Entity.h"

TextureHolder * Entity::texture_holder = nullptr;
const int Entity::size = 64;

Entity::Entity(const Textures::Textures &type, const sf::Vector2i &entity_position)
	:texture_type(type)
{
	//set position and entity sprite:
	entity_sprite.setPosition(entity_position.x * size, entity_position.y * size);

	if (type == Textures::Textures::WALL)
		entity_sprite.setTexture(texture_holder->get(Textures::Textures::WALL));
	if (type == Textures::Textures::CRATE)
		entity_sprite.setTexture(texture_holder->get(Textures::Textures::CRATE));
	if (type == Textures::Textures::CRATE_ON_OBJ)
		entity_sprite.setTexture(texture_holder->get(Textures::Textures::CRATE_ON_OBJ));
	if (type == Textures::Textures::GROUND)
		entity_sprite.setTexture(texture_holder->get(Textures::Textures::GROUND));
	if (type == Textures::Textures::NONE)
		entity_sprite.setTexture(texture_holder->get(Textures::Textures::NONE));
	if (type == Textures::Textures::OBJ)
		entity_sprite.setTexture(texture_holder->get(Textures::Textures::OBJ));
}

sf::Vector2i Entity::get_position()
{
	return sf::Vector2i(entity_sprite.getPosition().x / size, entity_sprite.getPosition().y / size);
}

Textures::Textures Entity::get_texture_type()
{
	return texture_type;
}

void Entity::set_texture_type(const Textures::Textures &type)
{
	texture_type = type;
	entity_sprite.setTexture(texture_holder->get(type));
}
