// omega_ut.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../googletest/include/gtest/gtest.h"


int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

