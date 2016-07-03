#pragma once
#include "dllexport.h"

class EXPORT iomega abstract
{
public:
	virtual int sqr(int x) = 0;

	virtual ~iomega();
};

inline iomega::~iomega()
{
}
