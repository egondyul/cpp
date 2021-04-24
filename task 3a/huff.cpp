#include "huff.h"

void Huff::input()
{
	if (code_decode == "c")
	{
		std::ifstream file(in, ios::binary);
		if (file)
		{
			while (!file.eof())
			{
				char c = file.get();
				text[c]++;
			}
		}
		else
		{
			std::cout << "Sorry, file is not open" << std::endl;
		}
		file.close();
	}
	else if (code_decode == "d")
	{
	
	}
}

void Huff::freq_map()
{
	for (const auto& i : text)
	{
		uptr data = std::make_unique<Node>();
		data->_data = i.first;
		data->_frequency = i.second;
		ptrData.emplace_back(std::move(data));
	}
}

Huff::uptr Huff::make_tree()
{
	while (ptrData.size() > 1)
	{
		std::sort(ptrData.begin(), ptrData.end(), functor());
		uptr left_son{ std::move(ptrData.back()) };
		ptrData.pop_back();

		uptr right_son{ std::move(ptrData.back()) };
		ptrData.pop_back();

		uptr parent = std::make_unique<Node>(std::move(left_son), std::move(right_son));
		ptrData.emplace_back(std::move(parent));
	}
	return std::move(ptrData.front());
}

//-----------------code-------------------//

void Huff::code()
{
	input();
	freq_map();
	uptr root = make_tree();
	std::vector<bool> boo;
	for_code(root, boo); //там ещё alphabet
	output(boo);
	c_key();
}

void Huff::for_code(uptr const& root, std::vector<bool>& boo)
{
	if (root->_left != nullptr)
	{
		boo.emplace_back(false);
		for_code(std::move(root->_left), boo);
	}
	if (root->_right != nullptr)
	{
		boo.emplace_back(true);
		for_code(std::move(root->_right), boo);
	}
	if (root->_data) alphabet[root->_data] = boo;
	if (!boo.empty()) boo.pop_back();
}

void Huff::output(std::vector<bool>& boo)
{
	std::ifstream infile(in, std::ios::binary);
	std::ofstream outfile(out, std::ios::binary);
	char buf=0;
	int count = 0;
	while (!infile.eof())
	{
		char c = infile.get();
		boo = alphabet[static_cast<char>(c)];
		for (int i = 0; i < boo.size(); i++)
		{
			buf = buf | boo[i] << (7 - count);
			++count;
			if (count == 8)
			{
				count = 0;
				outfile << buf;
				buf = 0;
			}
		}
		
	}
	outfile.close();
	infile.close();
}

void Huff::c_key()
{
	std::ofstream outfile("key.txt", std::ios::binary);
	/*Map::iterator it = text.begin(), end = text.end();
	for (; it != end; ++it)
	{
		outfile << it->first << '\t' << it->second << 'endl';
	}*/
	if (outfile.is_open())
	{
		auto&& index{ text.begin() };
		do
		{
			outfile.put(index->first);
			outfile.put(' ');
			outfile << std::to_string(index->second);
			++index;
			if (index != text.end())
			{
				outfile.put(' ');
			}
		} while (index != text.end());
		outfile.close();
	}
	else
	{
		std::cout << "sorry";
	}
}

//---------------decode----------------//

void Huff::decode()
{
	d_key();
	//input();
	//uptr root = make_tree();

}

std::string Huff:: readFile(const std::string& fileName) {
	std::ifstream f(fileName);
	std::stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

void Huff :: d_key()
{
	//std::string txt=readFile("key.txt");
	/*std::ifstream file("key.txt", std::ios::binary);
	std::stringstream ss;
	std::string txt;
	if (file.is_open())
	{
		ss << file.rdbuf();
		txt.str();
	}
	else
	{
		std::cout << "sorry";
	}*/

	std::ifstream file("key.txt");
	char key;
	std::size_t frequency;
	while (file >> key >> frequency)
	{
		text[key] = frequency;
	}
}