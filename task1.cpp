#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <regex>

using namespace std;

typedef std::map<std::string, int> Words;

bool cmp(const pair<string, int>& a,
	const pair<string, int>& b)
{
	return a.second < b.second;
}


std::vector<pair<string,int>> sortir(Words& M)
{
	vector<pair<string, int> > A;

	for (auto& it : M) {
		A.push_back(it);
	}
	//M.clear();
	sort(A.rbegin(), A.rend(),cmp);
	return A;
	/*for (int i = 0; i < A.size(); i++)
	{
	   txt.insert(A[i]);
	}*/
}

void percent(std::vector<pair<string, int>>& M, std::vector<double>& p)
{

	double all=0.0;
	for (int i = 0; i < M.size(); i++)
	{
		all += M[i].second;
	}
	for (int i = 0; i < M.size(); i++)
	{
		p.push_back((M[i].second*100)/all);
	}
}

void write_csv(ofstream& out, std::vector<pair<string, int>>& M, std::vector<double>& p)
{
	for (int i = 0; i < M.size(); i++)
	{
		out << M[i].first <<", "<< M[i].second << ", " << p[i]<< "%"<<"\n";
	}
	out.close();
}

void read_text(std::ifstream& in, Words& dictionary)
{
	if (in)
	{
		/*std::string txt{ std::istreambuf_iterator<char>{in},{} };
		std::regex words("[^[:punct:][:space:]]+");
		for (auto it = std::sregex_iterator(txt.begin(), txt.end(), words); it != std::sregex_iterator(); ++it)
		{
		std::string word;
		std::transform(word.begin(), word.end(), word.begin(), ::toupper);
		Words[word]++;
		}*/
		std::string text{ std::istreambuf_iterator<char>{in},{} };                 //ñ÷èòûâàåì ôàéë â îáúåêò òèïà string.
																				   //ïîäãîòîâêà ê îáðàáîòêå òåêñòà
		std::regex word("[^[:punct:][:space:][:digit:]]+");                                  //èùåì âñå, ÷òî îãðàíè÷åíî ïðîáåëàìè èëè çíàêàìè ïóíêòóàöèè.
		auto begin = std::sregex_token_iterator{ text.begin(), text.end(), word };  //èòåðàòîð äîñòóïà ê ÷àñòè÷íûì ñîâïàäåíèÿì(õ.ç. êàê ïî ðóññêè).
		auto end = std::sregex_token_iterator{};                                  //òî-æå, òîëüêî óñòàíîâëåí íà êîíåö ïîñëåäîâàòåëüíîñòè.
																					//ñîñòàâëåíèå ñëîâàðÿ
		//std::map<std::string, int> dictio;                                            //ñëîâàðü.
		for (; begin != end; ++begin)
			++dictionary[begin->str()];

	}
	else
	{
		std::cout << "File didn't open :(";
	}
	in.close();
}

int main()
{
	std::ifstream in("uliss.txt");
	Words text;
	read_text(in, text);
	std::vector<double> p;
	std::vector<pair<string, int>> t;
	t=sortir(text);
	percent(t, p);
	std::ofstream out("output.csv");
	write_csv(out, t, p);
 	return 0;
}

