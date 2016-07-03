#include "stdafx.h"
#include "ThreadMaster.h"

#include "Worker.h"
#include "Matrix.h"
#include <vector>
#include <thread>


ThreadMaster::ThreadMaster(int threadCount)
	: _threadCount(threadCount)
{
}


ThreadMaster::~ThreadMaster()
{
}

void ThreadMaster::Spawn() const
{
	std::vector<std::thread> threads(_threadCount);

	Matrix matrix;

	for (auto i = 0; i < _threadCount; ++i)
	{
		Worker w(i + 1, matrix);
		threads[i] = std::thread(Worker::Process, std::move(w));
	}

	for (auto i = 0; i < _threadCount; ++i)
	{
		threads[i].join();
	}
}
