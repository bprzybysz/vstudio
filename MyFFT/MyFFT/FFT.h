#pragma once

#include "dllexport.h"
#include <vector>
#include <unordered_map>
#include <complex>

class EXPORT ComplexDoubleT : public std::complex<double>
{
public:
	ComplexDoubleT() : std::complex<double>() {}
	explicit ComplexDoubleT(const std::complex<float>& complex)
		: std::complex<double>(complex)
	{
	}

	explicit ComplexDoubleT(const std::complex<long double>& complex)
		: std::complex<double>(complex)
	{
	}

	ComplexDoubleT(const _Ty& _Realval, const _Ty& _Imagval)
		: std::complex<double>(_Realval, _Imagval)
	{
	}

	explicit ComplexDoubleT(const std::_Dcomplex_value& _Right)
		: std::complex<double>(_Right)
	{
	}

	explicit ComplexDoubleT(const std::_Lcomplex_value& _Right)
		: std::complex<double>(_Right)
	{
	}

	bool operator==(const ComplexDoubleT & other) const
	{
		auto imag_diff = fabs(imag() / other.imag());
		auto imag_quals = imag_diff < 0.00000001;
		auto real_diff = fabs(real() / other.real());
		auto real_equals = real_diff < 0.00000001;
		return (imag_quals && real_equals);
	}
};

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

public:
	FFT(const ComplexVectorT & input);
	virtual ~FFT();

	void Compute();
	const ComplexVectorT & Output() const;


	EXPORT friend ComplexVectorT ToComplexVector(int * pInput, size_t size);
};

