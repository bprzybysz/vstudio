#pragma once
#include <random>
#include <array>

namespace CeleraOne
{
	class RandomGen
	{
		static const int DIGS = 31;
		int _mersennep;


	public:

		RandomGen()
			: _mersennep{(1u << DIGS) - 1}
		{
		}

		int Digs() const
		{
			return DIGS;
		}

		int MersennePrime() const
		{
			return _mersennep;
		}

		template<typename Type>
		std::vector<Type> Number(int count, const std::uniform_int_distribution<Type> * distributionPtr = nullptr) const
		{
			std::vector<Type> result(count);

			std::random_device seed;
			std::mt19937_64 randGen;
			randGen.seed(seed());

			std::uniform_int_distribution<Type> dist(distributionPtr == nullptr ? 
				std::uniform_int_distribution<Type>{
					std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max()} 
				: *distributionPtr);


			for (auto i = 0; i < count; ++i)
				result[i] = dist(randGen);

			return result;
		}

		template<typename Type>
		Type Number() const
		{
			auto vec = Number<Type>(1);

			return vec[0];
		}

	};


	
}