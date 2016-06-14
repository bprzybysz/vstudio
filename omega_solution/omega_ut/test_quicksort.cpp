#include "stdafx.h"
#include "gtest/gtest.h"

#include "quick_sort.h"


TEST(quick_sort_tests, test1)
{
	srand(time(nullptr));

	const auto count = 1000;
	std::vector<int> items(count);

	for (auto i = 0; i < count; ++i)
	{
		items[i] = rand();
	}

	quick_sort<int> sort;

	sort.sort(items);

	EXPECT_TRUE(std::is_sorted(items.begin(), items.end()));
}
