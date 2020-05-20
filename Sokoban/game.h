#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <chrono>
#include <thread>

#include <vector>
#include "state.h"
#include "TextureHolder.h"
#include "SceneHolder.h"

class Game
{
public:
	Game();
	void game_loop();	//main game loop
private:
	//calls scene_holder.process method
	void process();
	void render();

private:
	static const float		PlayerSpeed;

	TextureHolder texture_holder;
	SceneHolder scene_holder;

	sf::RenderWindow Window;
	sf::Sprite background;
	sf::Font font;
};
