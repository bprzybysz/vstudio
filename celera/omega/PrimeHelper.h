#pragma once
namespace CeleraOne
{
	class PrimeHelper
	{
	public:

		//given a number n, determine if it is prime
		static bool IsPrime(size_t n)
		{
			//loop from 2 to n/2 to check for factors
			for (auto i = 2; i <= n / 2; i++)
			{
				if (n % i == 0)     //found a factor that isn't 1 or n, therefore not prime
					return false;
			}

			return true;
		}

		static size_t FindNextPrime(size_t n)
		{
			auto nextPrime = n;
			auto found = false;

			//loop continuously until IsPrime returns true for a number above n
			while (!found)
			{
				nextPrime++;
				if (IsPrime(nextPrime))
					found = true;
			}

			return nextPrime;
		}
	};
}