#pragma once

//analytical integral
template<size_t p, size_t q>
class Power {
public:
	static const size_t value = p * Power<p, q - 1>::value;
};

template<size_t p>
class Power<p, 0> {
public:
	static const size_t value = 1;
};

template<size_t N, size_t a, size_t b>
struct integ
{
	static const size_t val = Power<b, N>::value - Power<a, N>::value;
};

//analytical double integral
template<size_t p, size_t q>
class Power_adouble {
public:
	inline static double const value = (double)p * Power<p, q - 1>::value;
};

template<size_t p>
class Power_adouble<p, 0> {
public:
	inline static double const value = 1.0;
};

template<size_t N, size_t a, size_t b>
struct integ_adouble
{
	inline static double const val =(double)( Power<b, N>::value - Power<a, N>::value)/N;
};

//new
#define N 100

template<int32_t it, int32_t a, int32_t b, int32_t q>
class Power_double {
public:
	inline static double const h = (double)(b - a) / N;
	inline static double const value = (a+it*h) * Power_double<it,a, b, q - 1>::value;
};

template<int32_t it, int32_t a, int32_t b>
class Power_double<it,a,b, 0> {
public:
	//inline static double const h = (b - a) / N;
	inline static double const value = 1;
};

template<int32_t it,  int32_t a, int32_t b, int32_t q>
struct sum_double
{
	inline static double const h = (double)(b - a) / N;

	inline static double const val = h * Power_double<it,a,b,q>::value + sum_double <it - 1, a, b, q>::val;
};

template< int32_t a, int32_t b, int32_t q>
struct sum_double<0,a,b,q>
{
	inline static double const h = (double)(b - a) / N;
	inline static double const val = h * Power_double<0, 0, 0, 1>::value;
};


template< int32_t a, int32_t b, int32_t q>
struct integ_double
{
	inline static double const val = sum_double<N, a, b, q>::val;
};

/*template<int32_t i>
struct sum
{
	inline static double const res = i * sum<i - 1>::res;
};

template<>
struct sum<0>
{
	inline static double const res = 0.0;
};*/

/*class doubl
{
private:
	static const T A_res;
	static const T B_res;

public:
	doubl integral(const double_A& c, const doubl& a, const doubl&b)
	{
		return (b - a)*c;
		//res_a = tmp.A;
		//res_b = tmp.B;
	}
	friend doubl operator+(const doubl&a, const doubl&b)
	{
		return doubl(a.A*b.B + b.A*a.B, a.B*b.B);
	}
	friend doubl operator*(const doubl&a, const doubl&b)
	{
		return doubl(a.A*b.A, a.B*b.B);
	}
	friend doubl operator-(const doubl&a, const doubl&b)
	{
		return doubl(a.A*b.B - b.A*a.B, a.B*b.B);
	}
};*/

/*template<int an, int ad,int bn, int bd, int it>
struct part_integral
{
	//брееед
	static const int res = h * (doubl<an, ad>+ doubl<it,1>*h) + part_integral<an,ad,bn,bd,it-1>;
};

template<int an, int ad, int bn, int bd >
struct part_integral<an, ad, bn, bd, 0>
{
	static const int res= h * (double_<0, 1>);
};

template<int an, int ad, int bn, int bd>
struct Integral
{
	static const int res = part_integral<an, ad, bn, bd, 9>::res;
};*/