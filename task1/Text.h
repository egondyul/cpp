#pragma once
#include <map>
#include <vector>
#include <string>

using namespace std;
typedef std::map<std::string, size_t> Words;

class Text
{
private:
	Words dictionary;
public:
	Text(Words& w);
	void set_name(std::string& nm);
	void read_text(std::string& nm, Words& dictionary);
	std::vector<pair<string, size_t>> sorter(Words& M);
	void percent(std::vector<pair<string, size_t>>& M, std::vector<double>& p);
	void write_csv(ofstream& out, std::vector<pair<string, size_t>>& M, std::vector<double>& p);
};
