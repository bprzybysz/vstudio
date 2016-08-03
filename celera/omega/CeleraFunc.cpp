#include "stdafx.h"
#include "CeleraFunc.h"
#include <iostream>


CeleraFunc::CeleraFunc()
{
	InitEvalFactors();
}

CeleraFunc::~CeleraFunc()
{
}

void CeleraFunc::InitEvalFactors()
{
	_valOfFactors.clear();
	_valOfFactors.emplace_hint(_valOfFactors.end(), 0, 1);
	_valOfFactors.emplace_hint(_valOfFactors.end(), 1, 1);
}


unsigned __int64 CeleraFunc::Calculate(unsigned __int64 n)
{
	InitEvalFactors();
	return CalculateFactor(n);
}


unsigned __int64 CeleraFunc::CalculateFactor(unsigned __int64 n)
{
	auto halfN = n / 2;
	auto isEven = n % 2 == 0;
	unsigned __int64 sum = 0;

	if (!isEven)
		sum = ValOfFactor(halfN-1);

	sum += ValOfFactor(halfN);

	return sum;
}

unsigned __int64 CeleraFunc::ValOfFactor(unsigned __int64 n)
{
	auto it = _valOfFactors.find(n);
	if (it == _valOfFactors.end())
	{
		auto valOfN = CalculateFactor(n);
		it = _valOfFactors.emplace_hint(_valOfFactors.end(), n, valOfN);
	}

	return it->second;
}