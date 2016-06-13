#include "stdafx.h"
#include "heap.h"


heap::heap(int heap_size)
	: _heap(heap_size), _current_size{heap_size}
{
}


heap::~heap()
{
}
