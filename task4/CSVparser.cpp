#include <tuple>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <type_traits>
/*#include <boost/tokenizer.hpp>


using namespace std;
using namespace boost;

tokenizer<escaped_list_separator<char> > tk(
	line, escaped_list_separator<char>('\\', ',', '\"'));
for (tokenizer<escaped_list_separator<char> >::iterator i(tk.begin());
	i != tk.end(); ++i)
{
	vec.push_back(*i);
}*/

template<class Head, class... Tail>
std::tuple<Head, Tail...> tuple_read(std::ifstream& is) {
	Head val;
	is >> val;
	if constexpr (sizeof...(Tail) == 0)
		return std::tuple{ val };
	else
		return std::tuple_cat(std::tuple{ val }, tuple_read<Tail...>(is));
}



template<class... Args>
std::ostream& operator<<(std::ostream& os, std::tuple<Args...> const& t) {
	bool first = true;
	std::apply([&os, &first](auto&&... args) {
		auto print = [&](auto&& val) {
			if (!first)
				os << "";
			(os << " " << val);
			first = false;
		};
		(print(args), ...);
	}, t);
	return os;
}

struct comma
{
	char com = ',';
};

template<class Head, class... Args>
std::ifstream& operator>>(std::ifstream& is, std::tuple<Head, Args...> &tup) {
	//is.imbue(std::locale(std::locale(), ','));
	tup = tuple_read<Head, Args...>(is);
	return is;
}

template<class...P>
class csvIterator
{
private:
	std::ifstream* in;
	std::tuple<P...> t;
public:
	typedef std::input_iterator_tag iteratir_category;
	typedef std::tuple<P...> value;
	typedef std::size_t it;
	typedef std::tuple<P...>* pointer;
	typedef std::tuple<P...>& reference;

	csvIterator(std::ifstream& file) :in(file.good() ? &file : NULL) { ++(*this); }
	csvIterator():in(NULL){}

	//pre increment
	csvIterator& operator++(){
		if(in)
		{
			if (!((*in) >> t))
			{
				in = NULL;
			}
		}
		return *this;
	}
	//post increment
	csvIterator operator++(int) {
		csvIterator tmp(*this);
		++(*this);
		return tmp;
	}
	std::tuple<P...> const& operator*() const
	{
		return t;
	}
	std::tuple<P...>* operator->()const 
	{
		return &t;
	}

	bool operator==(csvIterator const& rhs)
	{
		return ((this == &rhs) || ((this->in == NULL) && (rhs.in == NULL)));
	}
	bool operator!=(csvIterator const& rhs)
	{
		return !((*this) == rhs);
	}
};

template<class...P>
class CSVParser
{
	std::ifstream& stream;
public:
	CSVParser(std::ifstream& str):stream(str){}
	csvIterator<P...> begin()const {
		return csvIterator<P...>{ stream };
	}
	csvIterator<P...> end()const {
		return csvIterator<P...>{ };
	}
};

int main()
{
	std::ifstream file("test.csv");
	/*std::tuple<int, string, string> t2;
	while (file >> t2)
	{
		std::cout << t2 << std::endl;
	}*/
	/*std::cout << endl;
	for (csvIterator<int,string,string> loop(file); loop != csvIterator<int,string, string>(); ++loop)
	{
		std::cout << (*loop) << endl;
	}*/
	CSVParser<int, std::string, std::string> parser (file);
	for (std::tuple<int, std::string, std::string>rs : parser)
	{
		std::cout << rs << std::endl;
	}
}