#include "Game.h"
#include "Game_of_life.h"

Game::Game(void) : game_width(640), game_height(480)
{

}

bool Game::Init()
{
	name_of_game = "Game of life";
	window = new sf::RenderWindow(sf::VideoMode(game_width, game_height), name_of_game.c_str());
	return true;
}

bool Game::UnLoad()
{
	//Log("Game resources unloaded");
	return true;
}

void Game::Loop(Game_of_life& life)
{
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color(250, 50, 50));
	rectangle.setSize(sf::Vector2f(5, 5));
	life.read_map();
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) /*Если поступило событие "Закрытие окна" надо завершить работу приложения, т.е. освободить ресурсы и закрыть программу*/
			{
				Shutdown();
				window->close();
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //Если нажали ESC - выход
		{
			Shutdown();
			window->close();
			break;
		}
		if (life.Interactive_mode())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				life.next_generation();
				life.copy_map();
			}
		}
		window->clear();
		window->display();
	}

}

void Game::Shutdown()
{
	UnLoad();
	//Log("The game shuts down\n");
}

Game::~Game(void)
{
}