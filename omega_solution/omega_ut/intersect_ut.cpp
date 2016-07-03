#include "stdafx.h"
#include "../omega/intersect.h"
#include "gtest/gtest.h"


TEST(intersectTests, test1)
{
	EXPECT_EQ(intersect::solution(0, 2, 5, 10, 3, 1, 20, 15), 16);
}