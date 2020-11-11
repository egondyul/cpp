//#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include<sstream>
//#include "Game.h"
#include "Game_of_life.h"

//using namespace sf;

int main()
{
	Game_of_life game;
	if (game.get_iterator() == 0)
	{
		game.game_interactive();
	}
	else {
		game.Game();
	}

	system("pause");
	return 0;
}