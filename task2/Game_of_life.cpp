#include "Game_of_life.h"

Game_of_life::Game_of_life() {

}

void Game_of_life::read_map() {

	Map_s map;

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
				map_current[i][j] = 1.0;
			}
			else
			{
				map_current[i][j] = 0.0;
			}
			count++;
		}
	}

};

int Game_of_life::get_me_life()
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map_current[i][j] == 1.0)
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

int Game_of_life::comparator()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map_current[i][j] != map_next[i][j])
			{
				return -1;
			}
		}
	}
	return 0;
}

void Game_of_life::print_map()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map_current[i][j] == 1)
			{
				std::cout << '*';
			}
			else
			{
				std::cout << '_';
			}
		}
		std::cout << endl;
	}
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