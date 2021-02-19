#include <tuple>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/*template<typename T, typename ...P>
class CSVIterator
{
private:
	std::ifstream* file;
	std::tuple<T, P...> data;
public:
	typedef std::input_iterator_tag iterator_category;
	typedef std::tuple<T, P...> value_type;
	typedef std::tuple<T, P...>* pointer;
	typedef std::tuple<T, P...>& reference;

	CSVIterator(std::ifstream& File) :file(File.good() ?&File::NULL) { ++(*this); }
	CSVIterator() :file(NULL) {}

	//preincrement
	CSVIterator& operator++() {
		if (file) { if (!((*file) >> data)) { file = NULL; } } return *this;
	}
	//postincrement
	CSVIterator operator++(int) { CSVIterator tmp(*this); ++(*this); return tmp; }
	std::tuple<T, P...> const& operator*() const { return data; }
	std::tuple<T, P...> const* operator->() const {return &data; }

	bool operator== (CSVIterator const& t) { return ((this == &t) || ((this->data == NULL) && (t.data == NULL))); }
	bool operator!=(CSVIterator const& t) { return !((*this) == t); }
};

template<typename T, typename ...P>
class CSVParser
{
private:
	std::ifstream& file;
public:
	CSVParser(std::ifstream& t) :file(t) {}
	CSVIterator begin() const {
		return CSVIterator{ file };
	}
	CSVIterator end() const {return CSVIterator{ };}
};*/


template<size_t I, typename... P>
struct reader
{
	static void read(std::istream& i, std::tuple<P...>& t)
	{
		i >> std::get<I>(t);
		reader<I - 1, P...>::read(i, t);
	}
};

template<typename... P>
struct reader<0, P...>
{
	static void read(std::istream& i, std::tuple<P...>& t)
	{
		i >> std::get<0>(t);
	}
};

template<typename... P>
void read(std::istream& i, std::tuple<P...>& t)
{
	reader<sizeof...(P) - 1, P...>::read(i, t);
}

class Is_empty
{
public:
	bool empty(std::ifstream& in) const
	{
		return in.eof();
	}
};

template<typename ...P>
class CSVparser
{
	std::tuple<P...> t;
	std::ifstream file; //std::move
	size_t num;
public:
	CSVparser< P...>(std::ifstream& f, size_t n)
	{
		file = std::move(f);
		num = n;
	}

	class iterator
	{
		CSVparser* element;
	public:
		//using value_type = std::tuple<T, P...>;
		using reference = const std::tuple< P...>&;
		//using pointer = const std::tuple<T, P...>*;
		using iterator_category = std::input_iterator_tag;
		iterator(CSVparser* elem = nullptr) :element{ elem } {}
		reference operator*() const { return element->t; }
		iterator& operator++() { increment(); return *this; }
		iterator operator++(int) { increment(); return *this; }
		bool operator == (iterator rhs) const { return element == rhs.element; }
		bool operator !=(iterator rhs) const { return !(rhs == *this); }
	protected:
		void increment()
		{
			element->next();
			if (element->empty())
			//if(file.eof())
			{
				element = nullptr;
			}
		}
		//tuple<P...> operator*();
	};


	iterator begin() { return iterator{ this }; }
	iterator end() { return iterator{}; }
	void next() { read<P...>(file, t); }
	bool empty() const { return file.eof(); }
};

template<class... Args>
std::ostream& operator<<(std::ostream& os, std::tuple<Args...> const& t) {
	bool first = true;
	std::apply([&os, &first](auto&&... args) {
		auto print = [&](auto&& val) {
			if (!first)
				os << ",";
			(os << " " << val);
			first = false;
		};
		(print(args), ...);
	}, t);
	return os;
}

int main()
{
	std::ifstream file("test.csv");
	CSVparser<int,int,double> parser(file,0);
	for (std::tuple<int, int, double> rs : parser)
	{
		std::cout << rs << std::endl;
	}
}



