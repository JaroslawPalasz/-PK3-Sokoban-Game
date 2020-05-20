#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "game.h"
#include "Entity.h"
#include "FontHolder.h"
#include "SceneHolder.h"
#include "player.h"
#include "TextureHolder.h"

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main()
{
	Game sokoban;
	sokoban.game_loop();

	return 0;
}
