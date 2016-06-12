#pragma once
#include "iomega.h"

class EXPORT omega : public iomega
{
public:
	int fun1(int x) override;
	virtual ~omega() = default;

};