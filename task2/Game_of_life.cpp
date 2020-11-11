#include "Game_of_life.h"

Game_of_life::Game_of_life() {
	read_map();
}

void Game_of_life::read_map() {

	std::string nm;
	std::cout << "enter the name of txt: ";
	std::cin >> nm;
	//int iter = 0;
	std::cout << "enter the quantity of iterations: ";
	std::cin >> quantity_of_iter;
	char name[1000];
	strcpy_s(name, nm.c_str());

	std::ifstream file(name);
	std::vector<char> tmp;
	if (file.is_open())
	{
		n, m;
		file >> n >> m;
		char s;
		while (file >> s)
		{
			tmp.push_back(s);
		}
	}
	else
	{
		cout << "sorry :(";
	}

	map_current.resize(n);
	for (int i = 0; i < n; i++)
	{
		map_current[i].resize(m);
	}
	map_next.resize(n);
	for (int i = 0; i < n; i++)
	{
		map_next[i].resize(m);
	}
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (tmp[count] == '*')
			{
				map_current[i][j] = 1;
			}
			else
			{
				map_current[i][j] = 0;
			}
			count++;
		}
	}

};

int Game_of_life::get_iterator()
{
	return quantity_of_iter;
}

int Game_of_life::get_me_life()
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map_current[i][j] == 1)
			{
				count++;
			}
		}
	}
	return count;
}

void Game_of_life::read_neighb(std::vector<std::vector<signed int>>& nb, unsigned int ii, unsigned int jj)
{
	int k = 0;
	if (ii == 0 && jj == 0)
	{
		nb[0][0] = 1;
		nb[0][1] = 0;

		nb[1][0] = 0;
		nb[1][1] = 1;

		nb[2][0] = 1;
		nb[2][1] = 1;
	}
	if (ii == 0 && jj!=0)
	{
		nb[0][0] = 0;
		nb[0][1] = jj - 1;

		nb[1][0] = 1;
		nb[1][1] = jj-1;

		nb[2][0] = 1;
		nb[2][1] = jj;

		nb[3][0] = 0;
		nb[3][1] = jj + 1;

		nb[4][0] = 1;
		nb[4][1] = jj + 1;
	}
	if (jj == 0 && ii!=0)
	{
		nb[0][0] = ii-1;
		nb[0][1] = 0;

		nb[1][0] = ii-1;
		nb[1][1] = 1;

		nb[2][0] = ii;
		nb[2][1] = 1;

		nb[3][0] = ii+1;
		nb[3][1] = 1;

		nb[4][0] = ii+1;
		nb[4][1] = 0;
	}
	for (int i = ii - 1; i <= ii + 1; i++) {
		for (int j = jj - 1; j <= jj + 1; j++) {
			if (i == ii && j == jj) {
				continue;
			}
			nb[k][0] = i;
			nb[k][1] = j;
			k++;
		}
	}
}


int Game_of_life::get_live_neighbors(int ii, int jj)
{
	int count = 0;
	std::vector<std::vector<signed int>> neighb;
	neighb.resize(8);
	for (int i = 0; i < 8; i++)
	{
		neighb[i].resize(2);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			neighb[i][j] = -1;
		}
	}
	signed int x, y;

	read_neighb(neighb, ii, jj);

	for (int i = 0; i < 8; i++)
	{
		x = neighb[i][0];
		y = neighb[i][1];

		if (x < 0 || y < 0)
		{
			continue;
		}
		if (x >= n || y >= m)
		{
			continue;
		}
		if (map_next[x][y] == 1) {
			count++;
		}
	}
	return count;
}

void Game_of_life::next_generation()
{
	int k;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			k = get_live_neighbors(i, j);

			if (map_next[i][j] == 0)
			{
				if (k == 3)
				{
					map_current[i][j] = 1;
				}
			}
			else {
				if (k < 2 || k>3)
				{
					map_current[i][j] = 0;
				}
			}
		}
	}
}

void Game_of_life::copy_map()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			map_next[i][j] = map_current[i][j];
		}
	}
}

bool Game_of_life::comparator()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map_current[i][j] != map_next[i][j])
			{
				return false;
			}
		}
	}
	return true;
}


bool Game_of_life::Interactive_mode()
{
	if (quantity_of_iter == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game_of_life::Game()
{
	int live_point = -1;
	int comp = 0;
	int endCycle = this->get_iterator();
	int k = 0;
	do {
		std::cout << *this;
		this->copy_map();
		this->next_generation();

		if (this->comparator())
		{
			comp++;
		}
		if (comp == 2)
		{
			cout << "Game Over ^)" << endl;
		}
		live_point = this->get_me_life();
		if (live_point == 0) {
			cout << "Plague ((((((((" << endl;
		}
		k++;
	} while (live_point != 0 && comp<2 && k<endCycle);
}

void Game_of_life::game_interactive()
{
	char enter;
	int live_point = -1;
	int comp = 0;
	int k = 0;
	do {
		k = 0;
		cin >> noskipws >> enter;
		if (enter == '\n') {
			k = 1;
			std::cout << *this;
			this->copy_map();
			this->next_generation();

			if (this->comparator())
			{
				comp++;
			}
			if (comp == 2)
			{
				cout << "Game Over ^)" << endl;
			}
			live_point = this->get_me_life();
			if (live_point == 0) {
				cout << "Plague ((((((((" << endl;
			}

			this->quantity_of_iter++;
		}
	} while (k == 1 && comp<2 && live_point != 0);
}

std::ostream& operator <<(std::ostream& out, const Game_of_life& game) {
	Map_s map = game.map_current;
	int n = map.size();
	int m = map[0].size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 1)
			{
				out << '*';
			}
			else
			{
				out << '_';
			}
		}
		out << endl;
	}
	return out;
}