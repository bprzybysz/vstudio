#include "stdafx.h"
#include "gtest/gtest.h"
#include "FFT.h"
#include "FFTHelper.h"
#include <memory>
#include <iostream>




TEST(MyFFTUts, Create)
{
	int testArray[] = { 0,1,2,3,4,5,6,7 };
	FFTHelper helper;

	auto data = ToComplexVector(testArray, sizeof(testArray)/sizeof(int));

	FFT fft(data);
	fft.Compute();

	ASSERT_EQ(fft.Output(), helper.GetVec1());
}