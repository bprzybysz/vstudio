#pragma once
#include <map>

#include "dllexport.h"

class EXPORT CeleraFunc
{
	using UlongToUlongMapT = std::map < unsigned __int64, unsigned __int64 > ;
	UlongToUlongMapT _valOfFactors;

	unsigned __int64 CalculateFactor(unsigned __int64 n);
	void InitEvalFactors();
	unsigned __int64 ValOfFactor(unsigned __int64 n);

public:
	CeleraFunc();
	virtual ~CeleraFunc();

	unsigned __int64 Calculate(unsigned __int64 n);
};

