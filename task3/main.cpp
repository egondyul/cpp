#include <iostream>
#include <fstream>
#include <iterator>
#include<sstream>


using namespace std;

template<class T>
T func(T x)
{
	return (x);//*x + x * x*x + x * x*x*x);
}

template<class T>
T integrate(T a, T b)
{
	static double sum = 0.0;
	static double step = (b - a) / 10;
	for (double i = a + step / 2; i < b; i += step)
	{
		sum += func(i);
	}
	return step * sum;
}

constexpr double f(double x)
{
	return x;
}

constexpr double integral(double a, double b)
{
	double sum = 0.0;
	double step = (b - a) / 10;
	for (double i = a + step / 2; i < b; i += step)
	{
		sum += f(i);
	}
	return step * sum;
}

int main(int argc, char** argv)
{
	std::cout << integrate<double>(0.0, 5.0) << std::endl;
	std::cout << std::endl;
	std::cout << integral(0.0, 5.0) << std::endl;
	static_assert(integral(0.0, 5.0) == 12.5, "integrate<double>(0.0, 5.0)");
	//constexpr double prove=integrate<double>(0.0,5.0);
	return 0;
}