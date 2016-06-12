#pragma once
#include "dllexport.h"

class EXPORT iomega abstract
{
public:
	virtual int fun1(int x) = 0;

	virtual ~iomega();
};

inline iomega::~iomega()
{
}
