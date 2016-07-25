#include "stdafx.h"
#include "gtest/gtest.h"
#include "FFT.h"
#include "FFTHelper.h"
#include <memory>
#include <iostream>




TEST(MyFFTUts, Create)
{
	FFTHelper helper;

	auto data1 = helper.GetVec1();
	FFT fft(data1.input);
	fft.Compute();

	auto output = fft.Output();
	auto equals = std::equal(output.begin(), output.end(), data1.output.begin());

	ASSERT_TRUE(equals);
}