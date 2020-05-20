#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "TextureHolder.h"
#include "Entity.h"
#include "player.h"

class SceneHolder : public sf::Drawable
{
public:
	SceneHolder(TextureHolder* _texture_holder);
	//calls load_level
	bool play_level(const std::string &level);
	//main process function
	void process(const sf::Event & evnt, sf::RenderWindow &window);
	//takes input from user and loads appropriate level
	void choose_level(sf::Font &font, sf::RenderWindow &window);
	//checks if we set all of the crates on obj tiles
	bool check_if_finish();
	bool was_created = false;
	//simple method for text output on screen
	void set_text(sf::Text &text, sf::Font &font, const std::string & literal, 
		int char_size, int position, int y);

private:
	TextureHolder * texture_holder;
	Player player;
	//maximum size of tile array = 15
	Entity tile[15][15];
	//number of rows, columns and crates to set to complete level
	int columns;
	int rows;
	int obj_to_complete = 0;

	//loads level from file
	bool load_level(const std::string &filename);
	void handlePlayerInput(sf::Keyboard::Key key, sf::RenderWindow &Window);
	//handles collisions between tiles
	void check_collision();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};