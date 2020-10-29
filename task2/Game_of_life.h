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
	void read_map();
	int get_me_life();
	int get_live_neighbors(int ii, int jj);
	void read_neighb(std::vector<std::vector<signed int>>& nb, unsigned int x, unsigned int y);
	void next_generation();
	void copy_map();
	int comparator();
	bool Interactive_mode();
	void print_map();
};

