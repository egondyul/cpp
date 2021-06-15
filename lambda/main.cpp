#include <iostream>
#include <fstream>
#include <iterator>
#include<sstream>
#include<cmath>
#include <vector>
#include"func.h"

using namespace std;

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

#define N 2
#define NN N+1

#define h 10

template<class F, typename T>
constexpr auto integrate(F function, T a, T b)
{
	double sum = 0.0;
	double step = (b - a) / h;
	for (double i = a + step / 2; i < b; i += step)
	{
		sum += function(i);
	}
	return step * sum;
}

constexpr auto ff = []( double x)
{
	return (x*x + x + 1);
};

int main(int argc, char** argv)
{
	//static const size_t
	std::cout << "(constexpr) numerical integration x from 1 to 5: "<< integral(0.0, 5.0) << std::endl;
	static_assert(integral(0.0, 5.0) == 12.5, "integrate<double>(0.0, 5.0)");
	
	std::cout << "(template) analytical integration x^2 from 1 to 5: "<< (double)integ<NN, 0, 5>::val/3 << std::endl;
	static_assert(integ<NN, 1, 5>::val == 124, "err");

	//inline static double const
/*	std::cout << "(template) analytical integration x^2 from 1 to 5: " << integ_adouble<NN, 0, 5>::val << std::endl;
	static_assert(integ_adouble<NN, 0, 5>::val <=)
	std::cout << "(template) numerical integration x from 0 to 5: " << integ_double<0, 5, 1>::val << std::endl;*/

	/*double a = 0;
	double b = 5;

	

	double integral = integrate(f, a, b);
	std::cout << integral << std::endl;*/

	static_assert(integrate(ff, 0, 5) == 5.0, "st");

 	return 0;
}