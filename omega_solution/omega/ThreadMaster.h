#pragma once

#include "dllexport.h"
class EXPORT ThreadMaster
{
	int _threadCount;
public:
	ThreadMaster(int threadCount);
	~ThreadMaster();
	void Spawn() const;
};

