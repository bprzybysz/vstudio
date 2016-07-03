#pragma once
#include "iomega.h"

class EXPORT omega : public iomega
{
public:
	int sqr(int x) override;
	virtual ~omega() = default;

};