#include "pch.h"
#include "../integral/main.cpp"

TEST(IntegrateTest, valueTest) {
	ASSERT_EQ(12.5, integral(0.0,5.0));
}