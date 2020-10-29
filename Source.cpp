#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <regex>
#include <chrono>
#include "Text.h"
//#include "set_name.cpp"

using namespace std;


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
	system("Pause");
	return 0;
}

