#include "stdafx.h"
#include "intersect.h"


intersect::intersect()
{
}


intersect::~intersect()
{
}

int intersect::solution(int K, int L, int M, int N, int P, int Q, int R, int S)
{
	auto isLeftKLMN = K < P;

	auto dx = M < R ? M : R;

	if(isLeftKLMN)
	{
		if (M <= P)
			return 0;

		dx -= P;
	}
	else
	{
		if (R <= K)
			return 0;

		dx -= K;
	}


	auto isBottomKLMN = L < Q;
	auto dy = S < N ? S : N;

	if(isBottomKLMN)
	{
		if (N <= Q)
			return 0;
		dy -= Q;
	}
	else
	{
		if (S <= L)
			return 0;
		dy -= L;
	}

	long irsArea = dx * dy;

	return irsArea <= 2147483647 ? static_cast<int>(irsArea) : -1;
}
