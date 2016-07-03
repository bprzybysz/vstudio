#include "stdafx.h"
#include "gtest/gtest.h"
#include "../omega/omega.h"
#include <memory>

TEST(OmegaTest, Test1)
{
	omega a;

	EXPECT_EQ(a.sqr(2), 4);
}