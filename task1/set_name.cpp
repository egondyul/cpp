#include "Text.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <regex>
#include <chrono>

using namespace std;
//typedef std::map<std::string, size_t> Words;

struct predicate
{
	bool operator()(const std::pair<std::string, size_t> &left, const std::pair<std::string, size_t> &right)
	{
		return left.second < right.second;
	}
};

void Text::set_name(std::string& nm)
{
	std::cout << "Enter name of file: ";
	std::cin >> nm;
}

Text::Text(Words& w)
{
	this->dictionary = w;
}

void Text::read_text(std::string& nm, Words& dictionary)
{
	std::ifstream in(nm);
	if (in)
	{
		std::string text{ std::istreambuf_iterator<char>{in},{} };
		std::regex word("[^[:punct:][:space:][:digit:]]+"); //ищем все, что ограничено пробелами или знаками пунктуации.
		auto begin = std::sregex_token_iterator{ text.begin(), text.end(), word };  //итератор доступа 
		auto end = std::sregex_token_iterator{};

		for (; begin != end; ++begin)
			++dictionary[begin->str()];
	}
	else
	{
		std::cout << "File didn't open :(";
	}
	in.close();
}

std::vector<pair<string, size_t>> Text::sorter(Words& M)
{
	vector<pair<string, size_t> > tmp;

	for (auto& it : M) {
		tmp.push_back(it);
	}
	sort(tmp.rbegin(), tmp.rend(), predicate());
	return tmp;
}

void Text::percent(std::vector<pair<string, size_t>>& M, std::vector<double>& p)
{

	double all = 0.0;
	for (int i = 0; i < M.size(); i++)
	{
		all += M[i].second;
	}
	for (int i = 0; i < M.size(); i++)
	{
		p.push_back((M[i].second * 100) / all);
	}
}

void Text::write_csv(ofstream& out, std::vector<pair<string, size_t>>& M, std::vector<double>& p)
{
	for (int i = 0; i < M.size(); i++)
	{
		out << M[i].first << ", " << M[i].second << ", " << p[i] << "%" << "\n";
	}
	out.close();
}
