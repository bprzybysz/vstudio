#include "stdafx.h"
#include <limits>
#include "gtest/gtest.h"
#include "../omega/CeleraFunc.h"


using namespace std;

TEST(CeleraTests, CeleraFunc)
{
	CeleraFunc func;
	unsigned __int64 celeraValue = 0;

	celeraValue = func.Calculate(123456789012345678UL);
	EXPECT_EQ(celeraValue, 4296299699UL);
}