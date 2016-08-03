#pragma once

#include "RandomGen.h"


namespace CeleraOne
{
	class HashGenerator
	{
		RandomGen _randGen;

	public:

		template <typename FuncT>
		FuncT GetUniversalHash() const
		{
			auto hashDist = std::uniform_int_distribution<unsigned int>(1, _randGen.MersennePrime() - 1);
			auto randoms = _randGen.Number<unsigned int>(2, &hashDist);
			auto A = randoms[0];
			if (A == 0) 
				A = hashDist.max();

			auto B = randoms[1];
			auto P = _randGen.MersennePrime();
			auto Digs = _randGen.Digs();

			std::cout << "H(x)=(A*x+B)%P. A="<<A<<" B="<<B<<" P="<<P<<"\n";

			return [=](unsigned int hash)
			{
				auto hashVal = static_cast<unsigned long long>(A) * hash + B;
				hashVal = (hashVal >> Digs) + (hashVal & P);
				if (hashVal >= P)
					hashVal -= P;
				return static_cast<unsigned int>(hashVal);
			};
		}
	};
	
}
