#pragma once

#include "dllexport.h"
#include <vector>
#include <complex>

typedef std::vector<std::complex<double>> ComplexVectorT;

class EXPORT FFT
{
public:
private:
	const ComplexVectorT & _input;


public:
	FFT(const ComplexVectorT & input);
	virtual ~FFT();


	EXPORT friend ComplexVectorT ToComplexVector(int * pInput, size_t size);
};

