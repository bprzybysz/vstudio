#include "stdafx.h"
#include "rcshift.h"


rcshift::rcshift()
{
}


rcshift::~rcshift()
{
}

int rcshift::solution(int N)
{
	if (N < 0 || N > 1073741823)
		return -1;

	auto Nmax = N;
	auto k = 0;
	int trbit;
	
	for(auto i = 1; i <= 29; ++i)
	{
		trbit = N & 0x1;
		N >>= 1;
		if (trbit == 1)
		{
			trbit <<= 29;
			N += trbit;
		}

		if (N > Nmax)
		{
			Nmax = N;
			k = i;
		}
	}

	return k;
}
