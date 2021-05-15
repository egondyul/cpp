#include "huff.h"

void Huff::input()
{
	do {
		std::ifstream file(in, ios::binary);
		if (file)
		{
			while (!file.eof())
			{
				char c = file.get();
				text[c]++;
			}
			file.close();
			break;
		}
		else
		{
			std::cout << "Sorry, file is not open" << std::endl;
			std::cout << "try again: ";
			std::cin >> in;
		}
	} while (true);

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
		boo = alphabet[c];
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
		outfile.put(' ');
		outfile.close();
	}
	else
	{
		std::cout << "sorry, smt wrong";
	}
}

//---------------decode----------------//

void Huff::decode()
{
	d_key();
	//input();
	freq_map();
   	uptr root = make_tree();
	std::string decodedcontent;
	decodedcontent.reserve(decoded_size(text));
	for_decode(root, decodedcontent);

 }

std::string Huff:: readFile(const std::string& fileName) {
	std::ifstream f(fileName);
	std::stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

void Huff :: d_key()
{
	char buff = 0;
	std::string freq;
	std::string content = readFile("key.txt");
	for (std::size_t i{}; i < content.length(); ++i)
	{
		buff = content[i];
		i += 2;
		do
		{
			freq += content[i];
			++i;
		} while ((content[i] != ' ') && (content[i] != '.'));
		text[buff] = static_cast<unsigned int>(std::stoi(freq));
		freq.clear();
	}
	content.clear();
}

void Huff::for_decode(uptr const& root, std::string& decodedcontent)
{
	ifstream outfile(out, std::ios::binary);

	Node* tmp = root.get();
	int offset = 0; 
	int byte = outfile.get();
	while (!outfile.eof())
	{
 		if (byte & (1 << (7 - offset)))
		{
			tmp=tmp->_right.get();
		}
		else
		{
			tmp=tmp->_left.get();
		}

		if (tmp->_left==nullptr && tmp->_right==nullptr)
		{
			decodedcontent += tmp->_data;
			tmp = root.get();
		}
		offset++;
		if (offset == 8)
		{
			offset = 0;
			byte = outfile.get();
		}
	}
	outfile.close();

	do {
		std::ofstream outFile(in, std::ios::binary);
		if (outFile.is_open()) {
			outFile.write(&decodedcontent[0], static_cast<std::streamsize>(decodedcontent.size()));
			outFile.close();
			break;
		}
		else {
			std::cout << "output file didn't open for some reason";
			std::cout << "try again: ";
			std::cin >> in;
		}
	} while (true);
}

std::size_t Huff::decoded_size(const Map& map)
{
	std::size_t tmp = 0;
	for (const auto& i : map)
	{
		tmp += i.second;
	}
	return tmp;
}