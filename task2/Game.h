#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Game_of_life.h"

using namespace std;

class Game
{
	friend class Game_of_life;
	//friend void Game_of_life::next_generation(Map_s& map_next, Map_s& map_current);
	string name_of_game;
	sf::RenderWindow* window;
	const int game_width;
	const int game_height;
public:
	Game(void);
	bool Init();
	void Loop(Game_of_life& life);
	bool UnLoad();
	void Shutdown();
	~Game(void);
};
