#pragma once
#include <vector>


class heap
{
	using int_vector = std::vector<int>;

	int_vector _heap;
	int _current_size;

public:
	heap(int heap_size);
	~heap();
};

