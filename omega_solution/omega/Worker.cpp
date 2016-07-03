#include "stdafx.h"
#include "Worker.h"


Worker::Worker(int workerId, Matrix & matrix)
	: _workerId{ workerId }, _matrix{ matrix }
{
}

void Worker::Process(Worker & worker)
{
	worker.ChaoSet();
}

void Worker::ChaoSet() const
{
	std::mt19937 _random(_workerId);

	auto count = dist20(_random);

	for (auto i = 0; i < count; ++i)
	{
		_matrix.SetElement(dist100(_random), _workerId);
	}
}
