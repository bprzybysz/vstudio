#pragma once

#include "RandomGen.h"


namespace CeleraOne
{
	class HashGenerator
	{
		RandomGen _randGen;

	public:

		template <typename FuncT, typename KeyT>
		FuncT GetHash()
		{
			auto hashDist = std::uniform_int_distribution<int>(1, _randGen.MersennePrime());
			auto randoms = _randGen.Number<int>(2, &hashDist);
			auto A = randoms[0];
			if (A == 0) 
				A = std::numeric_limits<int>::max();

			auto B = randoms[1];
			auto P = _randGen.MersennePrime();
			auto Digs = _randGen.Digs();

			return [=](const KeyT& key)
			{
				static std::hash<KeyT> hf; //maxuint*maxuint+maxuint < maxuint64!!!
				auto hf1 = hf(key);
				if (sizeof(hf1) == 8)
				{
					hf1 = (hf1 >> 33) ^ (hf1 & 0x7FFFFFFF);
					if (hf1 >= P)
						hf1 -= P;
				}
				auto x = static_cast<int>(hf1);

				auto hashVal = static_cast<long long>(A * x + B);
				hashVal = (hashVal >> Digs) + (hashVal & P);
				if (hashVal >= P)
					hashVal -= P;
				return static_cast<size_t>(hashVal);
			};
		}
	};
	
}
