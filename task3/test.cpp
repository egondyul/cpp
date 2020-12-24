#include "pch.h"


//integral is calculated analytically
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

#define N 2
#define NN N+1

int test1()
{
	return integ<NN, 1, 5>::val;
}

TEST(test1, positiv)
{
	EXPECT_EQ(124, test1());
}

int test2()
{
	return integ<NN, 0, 5>::val;
}

TEST(test2, positiv2)
{
	EXPECT_EQ(125, test2());
}

int test3()
{
	return integ<NN, 0, 0>::val;
}

TEST(test3, zero)
{
	EXPECT_EQ(0, test3());
}

#define M 0
#define MM M+1

int test4()
{
	return integ<MM, 0, 5>::val;
}

TEST(test4, new_m)
{
	EXPECT_EQ(5, test4());
}
