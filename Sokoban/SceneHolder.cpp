#include "SceneHolder.h"


SceneHolder::SceneHolder(TextureHolder * _texture_holder)
	: texture_holder(_texture_holder)
	, player(_texture_holder, Entity::size)
{

}

bool SceneHolder::play_level(const std::string & level)
{
	if (load_level(level))
		return true;
	return false;
}

bool SceneHolder::load_level(const std::string &filename)
{
	std::ifstream level(filename);
	if (!level || !level.is_open())
	{
		std::cout << "Error loading file." << std::endl;
		return false;
	}

	sf::Vector2i tile_position;

	std::string type ="";
	Textures::Textures texture_type;
	bool rows_counted = false;
	while (!level.eof())
	{
		level >> type;
		if (type == "P")
		{
			texture_type = Textures::Textures::GROUND;
			player.set_position(sf::Vector2i(tile_position.x, tile_position.y));
		}
		if (type == "w")
		{
			texture_type = Textures::Textures::WALL;
		}
		if (type == "-")
		{
			texture_type = Textures::Textures::GROUND;
		}
		if (type == "b")
		{
			texture_type = Textures::Textures::CRATE;
		}
		if (type == "o")
		{
			obj_to_complete++;
			texture_type = Textures::Textures::OBJ;
		}

		if (!was_created)
			tile[tile_position.x][tile_position.y] = Entity(texture_type, tile_position);
		else
			tile[tile_position.x][tile_position.y].set_texture_type(texture_type);

		tile_position.x++;
		if (!rows_counted)
			rows++;
		if (level.peek() == '\n')
		{
			rows_counted = true;
			tile_position.x = 0;
			tile_position.y++;
			columns++;
		}
	}

	//filling up remaining tiles
	for (int row = 0; row < 15; row++) {
		for (int column = 0; column < 15; column++) {
			if (tile[row][column].get_sprite().getTexture() == nullptr)
			{
				sf::Vector2i temp(row, column);
				tile[row][column] = Entity(Textures::Textures::GROUND, temp);
			}
		}
	}

	level.close();
	return true;
}

void SceneHolder::handlePlayerInput(sf::Keyboard::Key key, sf::RenderWindow &Window)
{
	if (key == sf::Keyboard::Escape)
		Window.close();
	
	if (key == sf::Keyboard::Up)
	{
		player.move("IsMovingUp");
	}
	else if (key == sf::Keyboard::Down)
	{
		player.move("IsMovingDown");
	}
	else if (key == sf::Keyboard::Left)
	{
		player.move("IsMovingLeft");
	}
	else if (key == sf::Keyboard::Right)
	{
		player.move("IsMovingRight");
	}
}

void SceneHolder::check_collision()
{
	//after we moved:
	//we have to (or not) change the entity texture and sprite
	Entity * player_tab = &tile[player.get_position().x][player.get_position().y];
	Entity * next_entity{ nullptr };
	//we hit a wall, move back
	if (player_tab->get_texture_type() == Textures::Textures::WALL)
	{
		if (player.get_direction()== "IsMovingUp")
			player.move_back("IsMovingUp");
		else if (player.get_direction() == "IsMovingDown")
			player.move_back("IsMovingDown");
		else if (player.get_direction() == "IsMovingLeft")
			player.move_back("IsMovingLeft");
		else if (player.get_direction() == "IsMovingRight")
			player.move_back("IsMovingRight");
	}

	//setting next_entity to that depending on the direction of player
	if (player.get_direction() == "IsMovingUp")
	{
		next_entity = &tile[player_tab->get_position().x][player_tab->get_position().y - 1];
	}
	else if (player.get_direction() == "IsMovingDown")
	{
		next_entity = &tile[player_tab->get_position().x][player_tab->get_position().y + 1];
	}
	else if (player.get_direction() == "IsMovingLeft")
	{
		next_entity = &tile[player_tab->get_position().x - 1][player_tab->get_position().y];
	}
	else if (player.get_direction() == "IsMovingRight")
	{
		next_entity = &tile[player_tab->get_position().x + 1][player_tab->get_position().y];
	}
	//we are standing on a crate
	if (player_tab->get_texture_type() == Textures::Textures::CRATE)
	{
		// 1st case: nothing ahead - set crate texture, set previous texture to ground
		if (next_entity->get_texture_type()
			== Textures::Textures::GROUND)
		{
			//changing &tile[][] - entity
			player_tab->set_texture_type(Textures::Textures::GROUND);
			next_entity->set_texture_type(Textures::Textures::CRATE);
		}
		// 2nd case: ahead is objective, set previous texture to ground, set red crate texture
		else if (next_entity->get_texture_type() == Textures::Textures::OBJ)
		{
			player_tab->set_texture_type(Textures::Textures::GROUND);
			next_entity->set_texture_type(Textures::Textures::CRATE_ON_OBJ);
		}
		// ahead is wall or crate
		else
			player.move_back(player.get_direction());
	}
	// we are standing on red crate
	else if (player_tab->get_texture_type() == Textures::Textures::CRATE_ON_OBJ)
	{
		// 1st case: ahead is ground, set back the obj texture
		if (next_entity->get_texture_type() == Textures::Textures::GROUND)
		{
			player_tab->set_texture_type(Textures::Textures::OBJ);
			next_entity->set_texture_type(Textures::Textures::CRATE);
		}
		// 2nd case: ahead obj
		else if (next_entity->get_texture_type() == Textures::Textures::OBJ)
		{
			player_tab->set_texture_type(Textures::Textures::OBJ);
			next_entity->set_texture_type(Textures::Textures::CRATE_ON_OBJ);
		}
		else
			player.move_back(player.get_direction());
	}

}

bool SceneHolder::check_if_finish()
{
	int crates_set = 0;
	for (int row = 0; row < 15; row++) {
		for (int column = 0; column < 15; column++) {
			if (tile[row][column].get_texture_type() == Textures::Textures::CRATE_ON_OBJ)
				crates_set++;
		}
	}
	if (crates_set == obj_to_complete)
		return true;
	return false;
}

void SceneHolder::set_text(sf::Text &text, sf::Font &font, const std::string & literal, 
	int char_size, int position, int y)
{
	text.setFont(font);
	text.setString(literal);
	text.setCharacterSize(char_size);
	text.setStyle(sf::Text::Bold);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(position / 2.0f, position / 2.0f + y));
}

void SceneHolder::process(const sf::Event & evnt, sf::RenderWindow &window)
{
	switch (evnt.type)
	{
	case sf::Event::KeyPressed:
		handlePlayerInput(evnt.key.code, window);
		break;
	case sf::Event::Closed:
		window.close();
		break;
	}

	check_collision();
	if (check_if_finish())
	{ 
		//setting all of tiles to ground - both its' sprites and textures
		for (int row = 0; row < 15; row++) {
			for (int column = 0; column < 15; column++) {
				tile[row][column].set_texture_type(Textures::Textures::GROUND);
			}
		}
		obj_to_complete = 0;
		rows = 0;
		columns = 0;
	}
}

void SceneHolder::choose_level(sf::Font &font, sf::RenderWindow &window)
{
	//setting text at the centre of the window
	sf::Text text;
	set_text(text, font, "Sokoban", 96, 640, 0);
	sf::Text text2;
	set_text(text2, font, "Please enter level number.", 48, 640, 100);
	
	int level = 0;
	while (true)
	{
		window.clear();
		window.draw(text);
		window.draw(text2);
		window.display();
		
		std::string levell;
		
		std::cin >> level;
		if (std::cin.good())
		{
			levell = "levels/" + std::to_string(level) + ".txt";
			if (!play_level(levell))
			{
				std::cout << "There is no such level" << std::endl;
				std::cin.clear();
				std::cin.ignore();
			}
			else
			{
				window.clear();
				break;
			}
		}
		else
		{
			std::cout << "Please enter a number." << std::endl;
			std::cin.clear();
			std::cin.ignore();
		}
	}
}

void SceneHolder::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int row = 0; row < 15; row++) {
		for (int column = 0; column < 15; column++) {
			target.draw(tile[row][column]);
		}
	}
	target.draw(player);
}
