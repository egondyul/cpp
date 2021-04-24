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
	};

	struct functor
	{
		bool operator()(uptr const& first, uptr const& second) const
		{
			return first->_frequency > second->_frequency;
		}
	};

	//добавить копиконструктор и мувконструктор
public:
	Huff(std::string& what, std::string& in_file, std::string& out_file) :code_decode(what), in(in_file), out(out_file) 
	{
		if (what == "c")
		{
			code();
		}
		else if (what == "d")
		{
			decode();
		}
		else
		{
			std::cout << "Sorry, what you mean?????";
		}
	};

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

/*class Node
{
public:
	int a;
	char c;
	Node *left, *right;

	Node() { left = right = NULL; }

	Node(Node *L, Node *R)
	{
		left = L;
		right = R;
		a = L->a + R->a;
	}
};


struct MyCompare
{
	bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
};


vector<bool> code;
map<char, vector<bool> > table;

void BuildTable(Node *root)
{
	if (root->left != NULL)
	{
		code.push_back(0);
		BuildTable(root->left);
	}

	if (root->right != NULL)
	{
		code.push_back(1);
		BuildTable(root->right);
	}

	if (root->left == NULL && root->right == NULL) table[root->c] = code;

	code.pop_back();
}


int main(int argc, char *argv[])
{
	////// считаем частоты символов	
	ifstream f("1.txt", ios::out | ios::binary);

	map<char, int> m;

	while (!f.eof())
	{
		char c = f.get();
		m[c]++;
	}


	////// записываем начальные узлы в список list

	list<Node*> t;
	for (map<char, int>::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
		Node *p = new Node;
		p->c = itr->first;
		p->a = itr->second;
		t.push_back(p);
	}


	//////  создаем дерево		

	while (t.size() != 1)
	{
		t.sort(MyCompare());

		Node *SonL = t.front();
		t.pop_front();
		Node *SonR = t.front();
		t.pop_front();

		Node *parent = new Node(SonL, SonR);
		t.push_back(parent);

	}

	Node *root = t.front();   //root - указатель на вершину дерева

////// создаем пары 'символ-код':			

	BuildTable(root);

	////// Выводим коды в файл output.txt

	f.clear(); f.seekg(0); // перемещаем указатель снова в начало файла

	ofstream g("output.txt", ios::out | ios::binary);

	int count = 0; char buf = 0;
	while (!f.eof())
	{
		char c = f.get();
		vector<bool> x = table[c];
		for (int n = 0; n < x.size(); n++)
		{
			buf = buf | x[n] << (7 - count);
			count++;
			if (count == 8) { count = 0;   g << buf; buf = 0; }
		}
	}

	f.close();
	g.close();

	///// считывание из файла output.txt и преобразование обратно

	ifstream F("output.txt", ios::in | ios::binary);

	setlocale(LC_ALL, "Russian"); // чтоб русские символы отображались в командной строке

	Node *p = root;
	count = 0; char byte;
	byte = F.get();
	while (!F.eof())
	{
		bool b = byte & (1 << (7 - count));
		if (b) p = p->right; else p = p->left;
		if (p->left == NULL && p->right == NULL) { cout << p->c; p = root; }
		count++;
		if (count == 8) { count = 0; byte = F.get(); }
	}

	F.close();

	return 0;
}*/

