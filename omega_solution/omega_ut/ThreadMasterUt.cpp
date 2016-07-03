#include "stdafx.h"
#include "gtest/gtest.h"
#include "../omega/ThreadMaster.h"


TEST(ThreadMasterTests, TestSpawn)
{
	ThreadMaster master(100);
	

	master.Spawn();
}