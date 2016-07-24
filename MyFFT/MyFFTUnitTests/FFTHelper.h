#pragma once

#include "../MyFFT/FFT.h"

class FFTHelper
{
public:
	FFTHelper();
	~FFTHelper();

	class Data
	{
	public:
		ComplexVectorT input;
		ComplexVectorT output;
	};


private:
	Data _data1 = Data{
		ComplexVectorT
		{
			ComplexDoubleT(0.0, 0.0),
			ComplexDoubleT(1.0, 0.0),
			ComplexDoubleT(2.0, 0.0),
			ComplexDoubleT(3.0, 0.0),
			ComplexDoubleT(4.0, 0.0),
			ComplexDoubleT(5.0, 0.0),
			ComplexDoubleT(6.0, 0.0),
			ComplexDoubleT(7.0, 0.0),

		},
	
		{
			ComplexDoubleT(28.000000000000000, 0),
			ComplexDoubleT(-4.0000000000000000, 9.6568542494923797),
			ComplexDoubleT(-4.0000000000000000, 4.0000000000000000),
			ComplexDoubleT(-4.0000000000000000, 1.6568542494923797),
			ComplexDoubleT(-4.0000000000000000, 0),
			ComplexDoubleT(-3.9999999999999996, -1.6568542494923797),
			ComplexDoubleT(-3.9999999999999996, -4.0000000000000000),
			ComplexDoubleT(-3.9999999999999987, -9.6568542494923797),
		}
	};

	const ComplexVectorT & GetVec(const Data & data)
	{
		return data.output;
	};

public:

	const ComplexVectorT & GetVec1()
	{
		return GetVec(_data1);
	};
};

