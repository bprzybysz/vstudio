#include "stdafx.h"
#include "gtest/gtest.h"
#include "FFT.h"
#include <memory>

TEST(MyFFTUts, Create)
{
	int testArray[] = { 1, 2, 3, 4 };

	ToComplexVector(testArray, sizeof(testArray)/sizeof(int));

	
}