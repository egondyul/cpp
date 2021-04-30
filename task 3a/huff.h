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

		/*auto clone() const
		{
			return uptr(clone_impl());
		}

	protected:
		virtual Node* clone_impl() const
		{
			return new Node(*this);
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

	/*Huff(const Huff& huffman) :
		code_decode(huffman.code_decode), in(huffman.in), out(huffman.out), text(huffman.text), alphabet(huffman.alphabet)
	{
		std::deque<uptr> tmp;
		//ptrData.resize(huffman.ptrData.size());
		for (int i = 0; i < ptrData.size(); i++)
		{
			tmp.push_back(huffman.ptrData[i]->clone());
		}
		ptrData = tmp;
		
	}*/


	/*Huff& operator=(Huff const& huffman)
	{
		ptrData.resize(huffman.ptrData.size());
		for (int i = 0; i < ptrData.size(); i++)
		{
			ptrData[i] = huffman.ptrData[i]->clone();
		}
		return *this;
	}*/

	Huff(Huff&& huffman) noexcept
	{
		this->code_decode = huffman.code_decode;
		this->alphabet = huffman.alphabet;
		this->in = huffman.in;
		this->out = huffman.out;
		this->text = huffman.text;
		this->ptrData = std::move(huffman.ptrData);

	}

//	Huff& operator=(Huff&&huffman) = default;

	/*Huff(const Huff& huff) : code_decode(huff.code_decode), in(huff.in), out(huff.out), text(huff.text), alphabet(huff.alphabet), ptrData(huff.ptrData) {};

	Huff(Huff&& huff) : code_decode(huff.code_decode), in(huff.in), out(huff.out), text(huff.text), alphabet(huff.alphabet), ptrData(huff.ptrData) 
	{
	
	};*/

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
