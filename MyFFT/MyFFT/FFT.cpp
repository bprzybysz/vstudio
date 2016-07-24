#include "stdafx.h"
#include "FFT.h"
#include "dllexport.h"

const double FFT::PI = std::acos(-1);

FFT::FFT(const ComplexVectorT & input)
	: _input{ input }, _input_size{ input.size() }, 
	_fifactors(input.size() / 2)
{
	InitFiFactors();
}

FFT::~FFT()
{
}

void FFT::Compute()
{
	_multi = 0;
	_output = DitFFT2(_input.data(), _input_size, 1);
}


inline const ComplexDoubleT & FFT::Fi(size_t k) const
{
	auto it = _fifactors.find(k);

	if (it == _fifactors.end())
		throw std::exception("k factor not defined!");

	return it->second;
}

void FFT::InitFiFactors()
{
	double fdelta = -2 * PI / _input_size;

	double fi = 0.0;
	for (size_t k = 0; k < _input_size; k++, fi+=fdelta)
	{
		_fifactors[k] = std::move(ComplexDoubleT(cos(fi), sin(fi)));
	}
}

ComplexVectorT FFT::DitFFT2(const ComplexDoubleT * x, size_t N, size_t s)
{
	if (N == 1)
	{
		return std::move(ComplexVectorT{x[0]});
	}
	else
	{
		ComplexVectorT output(N);
		auto halfN = N / 2;

		auto leftX = DitFFT2(x, halfN, 2 * s);
		auto rightX = DitFFT2(x + s, halfN, 2 * s);

		auto step = _input_size / N;

		for (auto k = 0, fiIx = 0; k <= halfN - 1; ++k, fiIx+=step)
		{
			auto & t = leftX[k];

			auto & delta = rightX[k];
			delta*= Fi(fiIx);

			auto & outAtK = output[k] = std::move(delta);
			auto & outAtKNd2 = output[k + halfN] = t;
			outAtKNd2 -= outAtK;
			outAtK += t;

			//
			/*
			output[k] = std::move(delta);    //1:
			output[k] += t;					 //1: t + delta;
			output[k + N / 2] = std::move(t);//2:
			output[k + N / 2] -= output[k];  //2: t - delta;
			*/
		}

		return std::move(output);
	}

}

void FFT::DitFFT21(size_t x0, size_t N, size_t s)
{
	if(N > 1)
	{
		auto halfN = N / 2;
		DitFFT21(x0, halfN, 2*s);
		DitFFT21(x0 + s, halfN, 2*s);

		ComplexDoubleT t;
		const double pi = std::acos(-1);

		ComplexDoubleT f;
		for (auto k = x0; k <= x0 + halfN-1; ++k)
		{
			t = _output[k];

			auto fi = -2*pi*k/N; //TODO: can be optimized
			const ComplexDoubleT & f = ComplexDoubleT(cos(fi), sin(fi));

			auto delta = f*_output[k + halfN];
			_output[k] = t + delta;
			_output[k+halfN] = t - delta;
		}
	}
}

ComplexVectorT ToComplexVector(int * pInput, size_t size)
{
	ComplexVectorT newVector(size);

	for(size_t i = 0; i < size; ++i)
	{
		newVector[i] = static_cast<double>(pInput[i]);
	}

	return std::move(newVector);
}


const ComplexVectorT & FFT::Output() const 
{
	return _output;
};