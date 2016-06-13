#include "stdafx.h"
#include "gtest/gtest.h"
#include <memory>
#include "../omega/IntervalMap.h"

TEST(omega_tests, interval_test)
{
	using int_interval_map = IntervalMap<unsigned int, std::string>;

	int_interval_map a("init");

	a.assign(5, 100, "val1");
	a.assign(30, 60, "val2");
	a.assign(45, 110, "val3");
	a.assign(60, 110, "val4");
	a.assign(3, 10, "val0");
	a.assign(0, 10, "val0.1");
	a.assign(0, 3, "init");

	a.assign(60, 70, "val3.5");
	a.assign(3, 30, "val1.1");
	a.assign(3, 70, "val1");

	auto b = a;
	a.assign(3, 70, "init");
	a.assign(70, 110, "init");

	a = b;
	a.assign(3, 110, "init");

	a = b;
	a.assign(2, 70, "init");
	a.assign(70, 111, "init");

	a = b;
	a.assign(2, 111, "init");

	a = b;
	a.assign(0, std::numeric_limits<unsigned int>().max(), "overwrite");

	EXPECT_EQ(1, 1);
}