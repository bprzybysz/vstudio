#pragma once
#include <vector>
#include <algorithm>

class MSort
{
public:
	MSort();
	~MSort();




	std::vector<int> msort(const std::vector<int> & intArray, const std::vector<char> & charArray)
	{
		auto newVector = intArray;


		for (auto it = charArray.begin(); it != charArray.end(); ++it)
		{
			newVector.push_back(*it);
		}
		
		int center = newVector.size() / 2;
		mergeSort(newVector, tmpVector, 0, center);
		mergeSort(newVector, tmpVector, center, newVector.size());
	}
};

