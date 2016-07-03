#include "stdafx.h"
#include "gtest/gtest.h"

#include "../omega/Fibo.h"

TEST(Fibo, Test)
{
	EXPECT_EQ(Fibo::Fibonaci(0), 0);
	EXPECT_EQ(Fibo::Fibonaci(1), 1);
	EXPECT_EQ(Fibo::Fibonaci(2), 2);
	EXPECT_EQ(Fibo::Fibonaci(3), 3);
	EXPECT_EQ(Fibo::Fibonaci(4), 5);
	EXPECT_EQ(Fibo::Fibonaci(std::numeric_limits<unsigned int>().max()), 5);
}