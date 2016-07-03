#include "stdafx.h"
#include "Fibo.h"


Fibo::Fibo()
{
}


Fibo::~Fibo()
{
}

unsigned long Fibo::Fibonaci(unsigned int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	if (n == 2)
		return 2;

	unsigned long fn1=2, fn2=1, fn0=0;

	for(unsigned int i = 3; i <= n; ++i)
	{
		fn0 = fn1 + fn2;
		fn2 = fn1;
		fn1 = fn0;
	}

	return fn0;
}
