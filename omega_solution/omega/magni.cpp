#include "stdafx.h"
#include "magni.h"


magni::magni()
{
}


magni::~magni()
{
}

int magni::solution(std::vector<int>& A)
{
	auto size = A.size();

	std::vector<int> leftMax(size);
	std::vector<int> rightMin(size);

	int max = -2147483648;
	for(auto i = 0; i < size; ++i)
	{
		if (max < A[i])
			max = A[i];

		leftMax[i]=max;
	}

	int min = 2147483647;

	for(int i = size-1; i >= 0; --i)
	{
		if (min > A[i])
			min = A[i];

		rightMin[i] = min;
	}

	for (auto i = 0; i < size; ++i)
	{
		if (A[i] >= leftMax[i] && A[i] <= rightMin[i]) {
			return i;
		}
	}
}
