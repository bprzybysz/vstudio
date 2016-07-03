#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix()
{
	std::memset(_matrix.data(), 0, 100*sizeof(int));
}

void Matrix::SetElement(int ix, int value)
{
	if (ix < 0 || ix > 99)
		throw std::exception("dupa");

	std::lock_guard<std::mutex> lck(_matrixMutex);
	_matrix[ix] = value;
}
