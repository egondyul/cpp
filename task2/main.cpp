#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include<sstream>
//#include "Game.h"
#include "Game_of_life.h"

#ifdef _WIN32
    #include <windows.h>
    #define msleep(x) Sleep(x)
#else
    #include <unistd.h>
    #define msleep(x) usleep(x * 1000)
#endif
using namespace sf;

int main()
{
	Game_of_life game;
	game.read_map();
	int live_point=-1;
	bool is_optimal=false;

	do {
		game.print_map();
		game.copy_map();
		game.next_generation();

		is_optimal = game.comparator()==0;
		live_point = game.get_me_life();

		if (is_optimal == 0)
		{
			cout << "Optimal configuration detected" << endl;
		}

		if (live_point == 0) {
			cout << "All points died" << endl;
		}
		Sleep(1000);
	} while (live_point != 0 && !is_optimal);

	

	system("pause");
	return 0;
}