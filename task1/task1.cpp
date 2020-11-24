#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <regex>
#include <chrono>

using namespace std;

typedef std::map<std::string,size_t> Words;

struct predicate
{
	bool operator()(const std::pair<std::string, size_t> &left, const std::pair<std::string, size_t> &right)
	{
		return left.second < right.second;
	}
};

class Text
{
private:
	Words dictionary;
public:
	Text(Words w);
	void set_name(std::string& nm);
	void read_text(std::string& nm, Words& dictionary);
	std::vector<pair<string, size_t>> sorter(Words& M);
	void percent(std::vector<pair<string, size_t>>& M, std::vector<double>& p);
	void write_csv(ofstream& out, std::vector<pair<string, size_t>>& M, std::vector<double>& p);
};

Text::Text(Words w)
{
	this->dictionary = w;
}

void Text::set_name(std::string& nm)
{
	std::cout << "Enter name of file: ";
	std::cin >> nm;
}

void Text::read_text(std::string& nm, Words& dictionary)
{
	std::ifstream in(nm);
	if (in)
	{		
		std::string text{ std::istreambuf_iterator<char>{in},{} };
		std::regex word("[^[:punct:][:space:][:digit:]]+"); //èùåì âñå, ÷òî îãðàíè÷åíî ïðîáåëàìè èëè çíàêàìè ïóíêòóàöèè.
		auto begin = std::sregex_token_iterator{ text.begin(), text.end(), word };  //èòåðàòîð äîñòóïà 
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
	M.clear();
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


int main()
{
	
	Words words;
	Text text(words);
	std::string name;
	text.set_name(name);

	auto begin_time = std::chrono::steady_clock::now();

	text.read_text(name, words);

	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
	
	std::cout << "The time of regex = " << elapsed_ms.count() << endl;
	std::vector<pair<string, size_t>> txt_vector;
	txt_vector = text.sorter(words);
	std::vector<double> percentage;
	text.percent(txt_vector, percentage);
	std::ofstream out("output.csv");
	text.write_csv(out, txt_vector, percentage);
	return 0;
}

