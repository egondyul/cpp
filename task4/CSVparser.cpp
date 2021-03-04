#include <tuple>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <type_traits>
#include <algorithm>
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

/*template <typename T>
bool read_tuple_element(std::istream& in, T& value) {
	in >> value;
	return true;
}

template <typename Tuple, std::size_t... I>
void read_tuple_elements(std::istream& in, Tuple& value, std::index_sequence<I...>) {
	std::initializer_list<bool>{ read_tuple_element(in, std::get<I>(value))... });
}

template <typename ...Targs>
tuple<Targs...> SimpleCSVParser<Targs...>::iterator::operator*() {
	std::istringstream in(cur);
	in.imbue(std::locale(std::locale(), new commasep)); // for comma separation
	std::tuple<Targs...> t;
	read_tuple_elements(in, t, std::make_index_sequence<sizeof...(Targs)>{});
	if (in) { // you may want to check if all data was consumed by adding && in.eof()
		// now do something with the filled t;
	}
	else {
		// the value could *not* successfully be read: somehow deal with that
	}
}*/

template<class Head, class... Tail>
std::tuple<Head, Tail...> tuple_read(std::ifstream& is) {
	Head val;
	char tmp;
	if (is.peek() == ',')
	{
		is >> tmp;
		is >> val;
		if constexpr (std::is_same_v<Head, std::string>)
		{
			val.erase(std::remove(val.begin(), val.end(), ','), val.end());
		}
		if constexpr (sizeof...(Tail) == 0)
			return std::tuple{ val };
		else
			return std::tuple_cat(std::tuple{ val }, tuple_read<Tail...>(is));

	}
	else
	{
		is >> val;
		if constexpr (sizeof...(Tail) == 0)
			return std::tuple{ val };
		else
			return std::tuple_cat(std::tuple{ val }, tuple_read<Tail...>(is));

	}
	//is.imbue(std::locale(std::locale(), new commasep));

}

template<class... Args>
std::ostream& operator<<(std::ostream& os, std::tuple<Args...> const& t) {
	std::apply([&os](auto&&... args) {
		auto print = [&](auto&& val) {
			os << " " << val;
		};
		(print(args), ...);
	}, t);
	return os;
}

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
	typedef std::input_iterator_tag iterator_category;
	typedef std::tuple<P...> value;
	typedef std::size_t it;
	typedef std::tuple<P...>* pointer;
	typedef std::tuple<P...>& reference;

	csvIterator(std::ifstream& file,size_t n) :in(file.good() ? &file : NULL) { 
		++(*this);
		while (n > 0)
		{
			--n;
			++(*this);
		}
	}

	csvIterator():in(nullptr){}

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
	size_t number;
public:
	CSVParser(std::ifstream& str, size_t n):stream(str)
	{
		number = n;
	}
	csvIterator<P...> begin()const {
		return csvIterator<P...>{ stream, number };
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
	/*std::cout << std::endl;
	for (csvIterator<int,std::string,std::string> loop(file); loop != csvIterator<int,std::string, std::string>(); ++loop)
	{
		std::cout << (*loop) << std::endl;
	}*/
	
	CSVParser<int, std::string, std::string> parser (file,0);
	for (std::tuple<int, std::string, std::string>rs : parser)
	{
		std::cout << rs << std::endl;
	}
}