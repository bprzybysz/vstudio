#pragma once

#include "dllexport.h"
#include <vector>
#include <complex>
#include <unordered_map>

using ComplexDoubleT = std::complex<double>;
using ComplexVectorT = std::vector<ComplexDoubleT>;
using FiFactorsT = std::unordered_map<size_t, ComplexDoubleT>;

class EXPORT FFT
{
private:
	static const double PI;

public:
private:
	const ComplexVectorT & _input;
	ComplexVectorT _output;
	FiFactorsT _fifactors;
	size_t _input_size;
	size_t _multi;

	void InitFiFactors();
	inline const ComplexDoubleT & Fi(size_t k) const;
	ComplexVectorT DitFFT2(const ComplexDoubleT * x, size_t N, size_t s);
	void DitFFT21(size_t x0, size_t N, size_t s);

public:
	FFT(const ComplexVectorT & input);
	virtual ~FFT();

	void Compute();
	const ComplexVectorT & Output() const;


	EXPORT friend ComplexVectorT ToComplexVector(int * pInput, size_t size);
};

