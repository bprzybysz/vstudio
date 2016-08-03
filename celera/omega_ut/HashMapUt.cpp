#include "stdafx.h"
#include "gtest/gtest.h"
#include "../omega/HashMapUtil.h"
#include "../omega/DoubleHashMap.h"
#include "HashMapUtHelper.h"
#include "../omega/RandomGen.h"
#include "../omega/HashGenerator.h"

using namespace CeleraOne;
using namespace ::testing;

namespace ut{

	class HashMapUt : public Test 
	{
	protected:
		HashMapUtHelper _helper;
	public:
		HashMapUt()
		{
		}

	};

	TEST_F(HashMapUt, HashMapCreateTest)
	{
		auto capacity = _helper[HashMapUtHelper::HashMapCreateTest].SetMapCapacity;

		UIntHashMapT hashMap(capacity);

		EXPECT_TRUE(_helper.AsExpected(hashMap, HashMapUtHelper::HashMapCreateTest));
	}


	TEST_F(HashMapUt, HashMapInsertTest)
	{
		UIntHashMapT map(10);

		std::vector<unsigned int> keys{ 1, 10, 100, 1000 };
		std::vector<unsigned int> vals{ 6, 60, 600, 6000 };

		map.Insert(keys[0], vals[0]);
		map.Insert(keys[1], vals[1]);
		map.Insert(keys[2], vals[2]);
		map.Insert(keys[3], vals[3]);

		if (!_helper.AsExpected(map, HashMapUtHelper::HashMapInsertTest))
			FAIL() << "Hash map has different properties than expected";

		auto hashMapPtr = map.HashMapPtr();

		std::vector<UIntHashMapEntryT> entries = {
			hashMapPtr[3], 
			hashMapPtr[4], 
			hashMapPtr[8], 
			hashMapPtr[12],
			hashMapPtr[0],
			hashMapPtr[22],
			hashMapPtr[11],
		};

		std::vector<UIntHashMapEntryT> expected = {
			{10, 60, UIntHashMapEntryT::ACTIVE},
			{1, 6, UIntHashMapEntryT::ACTIVE},
			{1000, 6000, UIntHashMapEntryT::ACTIVE},
			{100, 600, UIntHashMapEntryT::ACTIVE},
			{0, 0, UIntHashMapEntryT::EMPTY},
			{0, 0, UIntHashMapEntryT::EMPTY},
			{0, 0, UIntHashMapEntryT::EMPTY}
		};

		EXPECT_EQ(entries, expected);
	}


	TEST_F(HashMapUt, HashMapLookupTest)
	{
		UIntUtilHashMapT map(10);

		std::vector<unsigned int> keys{ 1, 10, 100, 1000 };
		std::vector<unsigned int> expected{ 6, 60, 600, 6000 };

		map.Insert(keys[0], expected[0]);
		map.Insert(keys[1], expected[1]);
		map.Insert(keys[2], expected[2]);
		map.Insert(keys[3], expected[3]);

		std::vector<unsigned int> lookups{
			map.Lookup(keys[0]),
			map.Lookup(keys[1]),
			map.Lookup(keys[2]),
			map.Lookup(keys[3])
		};

		EXPECT_EQ(lookups, expected);
	}

	TEST_F(HashMapUt, HashMapInsertList)
	{
		RandomGen gen;

		auto randNumbers = gen.Number<unsigned int>(100);


		HashMapUtil<unsigned int, unsigned int> map(100);

		auto ixs = map.InsertKeysToIndexVector(randNumbers, true); 
	}


	TEST_F(HashMapUt, HashMapInsertsThrowsHashMapIsFull)
	{
		UIntHashMapT map(50);
		try
		{
			for (auto i = 0; i < 51; ++i)
			{
				map.Insert(i, i);
			}

			FAIL() << "Expected HashEntryOperationException";
		}
		catch (HashMapIsFullException & )
		{
			SUCCEED();
		}
		catch (...)
		{
			FAIL() << "Expected HashEntryOperationException";
		}
	}

	TEST_F(HashMapUt, HashMapContainsTest)
	{
		UIntHashMapT map(7);

		auto data = std::vector < unsigned int > {111101, 1234, 7777, 4321, 88888, 1010101010, 44444};

		for(auto d : data)
			map.Insert(d, d);

		for (auto k : data)
		{
			if (!map.Contains(k))
				FAIL() << "Map should contain element key=" << k;
		}
	}

	TEST_F(HashMapUt, HashMapDeleteTest)
	{
		UIntHashMapT map(10);

		map.Insert(1111, 1111);
		if (!map.Contains(1111))
			FAIL() << "Map should contain element key=1111";
		map.Delete(1111);
		if (map.Contains(1111))
			FAIL() << "Map shouldn't contain element key=1111";
		map.Insert(1111, 3333);
		if (!map.Contains(1111))
			FAIL() << "Map should contain element key=1111";
	}

	TEST_F(HashMapUt, HashMapDeleteInBetweenClusterTest)
	{
		UIntHashMapT map(100);

		for (auto i = 100; i < 200; ++i)
		{
			map.Insert(i, i % 97);
		}

		UIntUtilHashMapT utMap(std::move(map));

		//erase key 167:  x(190) x(191) +[194]
		//test key 195 x(193) x(194) x(197) +[202]

		if (utMap.HashIdx(167) != 194)
			FAIL() << "Map should contain key 167 at [194]";
		utMap.Delete(167);
		if (utMap.Contains(167))
			FAIL() << "Map shouldn't contain element key=167";
		if (utMap.HashIdx(195) != 202)
			FAIL() << "Map should contain key 195 at [202]";

	}

	TEST_F(HashMapUt, HashMapCurrentSizeTest)
	{
		UIntHashMapT map(100);
		if(map.CurrentSize() != 0)
			FAIL() << "Map should be empty";

		map.Insert(101, 101);
		if (map.CurrentSize() != 1)
			FAIL() << "Map should contain 1 element!";

		map.Delete(101);
		if (map.CurrentSize() != 1)
			FAIL() << "Map should still be 1 element in size!";

		map.Insert(101, 101);
		if (map.CurrentSize() != 1)
			FAIL() << "Map should still be 1 element in size!";

		map.Insert(202, 202);
		if (map.CurrentSize() != 2)
			FAIL() << "Map should contain 2!";
	}

	TEST_F(HashMapUt, DoubleHashMapInsert500CompareLookup)
	{
		HashGenerator hashGen;

		auto probHash = hashGen.GetUniversalHash<UIntDoubleHashMapT::ProbHashFuncT>();

		const auto inCnt = 500;

		UIntDoubleHashMapT dmap(inCnt, probHash);

		std::vector<unsigned int> expected(inCnt);

		for (auto i = 0; i < inCnt; ++i)
		{
			expected[i] = i;
			dmap.Insert(i, i);
		}

		std::vector<unsigned int> lookupValue(inCnt);


		for (auto i = 0; i < inCnt; ++i)
		{
			lookupValue[i] = dmap.Lookup(i);
		}

		EXPECT_EQ(lookupValue, expected);
	}





}