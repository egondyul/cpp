#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include<sstream>
//#include "Game.h"

using namespace std;
typedef std::vector<std::vector<double>> Map_s;

class Game_of_life
{
	//friend class Game;
private:
	Map_s map_current, map_next;
	int n, m, quantity_of_iter;
public:
	Game_of_life();
	int get_iterator();
	void Game(Game_of_life& game);
	void game_interactive(Game_of_life& game);
	friend std::ostream& operator <<(std::ostream& out, const Game_of_life& game);
private:
	void read_map();
	bool Interactive_mode();
	int get_me_life();
	int get_live_neighbors(int ii, int jj);
	void read_neighb(std::vector<std::vector<signed int>>& nb, unsigned int x, unsigned int y);
	void next_generation();
	void copy_map();
	bool comparator();
};

