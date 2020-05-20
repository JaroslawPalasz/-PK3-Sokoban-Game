#include "game.h"

const float Game::PlayerSpeed = 1;
const int tile_size = 64;

Game::Game()
	: Window(sf::VideoMode(640, 640), "Sokoban", sf::Style::Titlebar | sf::Style::Close)
	, texture_holder()
	, scene_holder(&texture_holder)
{
	Window.setFramerateLimit(60);
	//every entity now has a pointer to the same texture holder class
	Entity::texture_holder = &texture_holder;	
	
	if (!font.loadFromFile("fonts/font.ttf"))
	{
		assert(0);
	}

	background.setTexture(texture_holder.get(Textures::Textures::BACKGROUND));

	scene_holder.choose_level(font, Window);
	
	scene_holder.was_created = true;
}

void Game::game_loop()
{
	while (Window.isOpen())
	{
		process();
		if (scene_holder.check_if_finish())
		{
			sf::Text text;
			scene_holder.set_text(text, font, "Level completed", 80, 640, 0);

			Window.clear();
			//Window.draw(scene_holder);
			Window.draw(text);
			Window.display();
			
			using namespace std::chrono_literals;
			std::chrono::milliseconds dura(900);
			std::this_thread::sleep_for(dura);
			Window.clear();

			scene_holder.choose_level(font, Window);
			
		}
		render();
		
	}
	//Window.close();
}

void Game::process()
{
	sf::Event evnt;
	while (Window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed)
			Window.close();
		else
		{
			scene_holder.process(evnt, Window);
		}
	}

}

void Game::render()
{
	Window.clear();
	Window.draw(background);
	Window.draw(scene_holder);
	Window.display();
}
