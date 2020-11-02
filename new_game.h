#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include<sstream>
//#include "Game.h"

using namespace std;

class Game_of_life
{
	//friend class Game;
private:
	double* map_current;
	double* map_next;
	int n, m, quantity_of_iter;
public:
	Game_of_life();
	~Game_of_life();
private:
	void read_map();

};

