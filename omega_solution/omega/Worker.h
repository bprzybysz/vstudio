#pragma once


#include "Matrix.h"
#include <random>

class Worker
{
private:
	int _workerId;
	Matrix & _matrix;

	std::uniform_int_distribution<int> dist20 = std::uniform_int_distribution<int>(1, 20);
	std::uniform_int_distribution<int> dist100 = std::uniform_int_distribution<int>(0, 99);

public:



	Worker(int workerId, Matrix & matrix);

	static void Process(Worker & worker);
	void ChaoSet() const;
};

