#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include<deque>
#include<algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include<string>
#include <iterator>
#include <sstream>
#include <memory>

using namespace std;

class Huff
{
private:
	struct Node;
	using uptr = std::unique_ptr<Node>;
	using Map = std::map<char, int>;
	using Abc = std::map<char, std::vector<bool>>;

	struct Node
	{
		uptr _left;
		uptr _right;
		std::size_t _frequency;
		char _data;

		Node() = default;
		Node(uptr left, uptr right) : _left{ std::move(left) },
			_right{ std::move(right) } {
			_frequency = _left->_frequency + _right->_frequency;
		}


		/*uptr copy_unique(Node *node)
		{
			auto ptr = std::make_unique<Node>(*node);
			return ptr;
		}*/

	};

	struct functor
	{
		bool operator()(uptr const& first, uptr const& second) const
		{
			return first->_frequency > second->_frequency;
		}
	};


public:
	Huff(std::string& what, std::string& in_file, std::string& out_file) :code_decode(what), in(in_file), out(out_file) 
	{
		do {
			if (what == "c")
			{
				code();
				break;
			}
			else if (what == "d")
			{
				decode();
				break;
			}
			else
			{
				std::cout << "Sorry, what you mean?????";
				std::cin >> what;
			}
		} while (true);
		
	};

	~Huff(){}

	Huff(const Huff& huffman) = delete;
	Huff& operator = (const Huff& huffman) = delete;

	Huff(Huff&& huffman) noexcept
	{
		this->code_decode = huffman.code_decode;
		this->alphabet = huffman.alphabet;
		this->in = huffman.in;
		this->out = huffman.out;
		this->text = huffman.text;
		this->ptrData = std::move(huffman.ptrData);
	}

	Huff& operator=(Huff&&huffman)
	{
		if (&huffman == this)
		{
			return *this;
		}

		this->code_decode = huffman.code_decode;
		this->alphabet = huffman.alphabet;
		this->in = huffman.in;
		this->out = huffman.out;
		this->text = huffman.text;
		this->ptrData = std::move(huffman.ptrData);

		return *this;
	}



private:
	void input();
	uptr make_tree();
	void freq_map();
	std::string readFile(const std::string& fileName);

	void for_code(uptr const& root, std::vector<bool>& boo);
	void c_key();
	void output(std::vector<bool>& boo);

	void d_key();
	void for_decode(uptr const& root, std::string& decodedcontent);
	std::size_t decoded_size(const Map& map);
	void code();
	void decode();

private:
	Map text; // <char, frequency>
	std::deque<uptr> ptrData; //дек указателей (дерево)
	Abc alphabet;
	
	std::string code_decode;
	std::string in;
	std::string out;
};
