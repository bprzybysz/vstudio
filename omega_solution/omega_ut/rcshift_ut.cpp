#include "stdafx.h"
#include "gtest/gtest.h"
#include "../omega/rcshift.h"

TEST(rcshift, test_rcshift)
{
	EXPECT_EQ(rcshift::solution(1), 1);
	EXPECT_EQ(rcshift::solution(121), 7);
	EXPECT_EQ(rcshift::solution(9736), 11);
}
