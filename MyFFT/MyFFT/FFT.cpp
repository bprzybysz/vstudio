#include "stdafx.h"
#include "FFT.h"
#include "dllexport.h"


FFT::FFT(const ComplexVectorT & input)
	: _input{input}
{
}

FFT::~FFT()
{
}

ComplexVectorT ToComplexVector(int * pInput, size_t size)
{
	ComplexVectorT newVector(size);

	for(size_t i = 0; i < size; ++i)
	{
		newVector[i] = static_cast<double>(pInput[i]);
	}

	return ComplexVectorT();
}
