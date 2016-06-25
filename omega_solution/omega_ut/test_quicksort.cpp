#include "stdafx.h"
#include "gtest/gtest.h"

#include "quick_sort.h"


template<class T>
int find_idx(const T & val, const std::vector<T> & input, int lower_ix = 0, int upper_ix = -1)
{
	if (input.size() == 0)
		return -1;

	if (upper_ix == -1)
		upper_ix = input.size();

	if (upper_ix - lower_ix == 1)
	{
		if (val < input[lower_ix])
			return -1;
		if (input[lower_ix] < val)
			return -1;
		return lower_ix;
	}

	int mid_ix = (lower_ix + upper_ix) / 2;

	const T & mid_val = input[mid_ix];

	if (val < mid_val)
		return find_idx(val, input, lower_ix, mid_ix);
	else 
		return find_idx(val, input, mid_ix, upper_ix);
}


TEST(quick_sort_tests, test1)
{
	std::vector<int> v = { -1, 1, 3, 6, 8, 10 };

	auto i1 = find_idx<int>(-1, v); //= 0
	auto i2 = find_idx<int>(10, v); //= 5
	auto i3 = find_idx<int>(-2, v); //= -1
	auto i4 = find_idx<int>(11, v); // = -1
	auto i5 = find_idx<int>(6, v);//= 3
	auto i6 = find_idx<int>(4, v);//= -1

	std::vector<int> v2 = { 1 };
	auto i7 = find_idx<int>(-1, v2);//=-1
	auto i8 = find_idx<int>(1, v2);//=0
	auto i9 = find_idx<int>(2, v2);//=-1

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
