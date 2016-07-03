#pragma once

#include <array>
#include <mutex>

class Matrix
{
	using intArray = std::array<int, 100>;

	std::mutex _matrixMutex;
	intArray _matrix;
public:
	Matrix();

	void SetElement(int ix, int value);
};

