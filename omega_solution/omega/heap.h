#pragma once
#include <vector>
#include <boost/functional/hash.hpp>


class heap
{
	using int_vector = std::vector<int>;

	int_vector _heap;
	int _current_size;

public:
	heap(int heap_size);
	~heap();


	friend size_t hash_value(const heap& obj)
	{
		size_t seed = 0x309A79FC;
		boost::hash_combine(seed, obj._heap);
		boost::hash_combine(seed, obj._current_size);
		return seed;
	}
};

