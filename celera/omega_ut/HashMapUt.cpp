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

	TEST_F(HashMapUt, DoubleHashMapCreateTest)
	{
		HashGenerator hashGen;

		auto probHash = hashGen.GetHash<UIntDoubleHashMapT::ProbHashFuncT, size_t>();

		UIntDoubleHashMapT dmap(1000, probHash);

		const auto inCnt = 500;

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


//		UIntUtilHashMapT map(std::move(dmap));
//		auto preview = map.Preview();


		EXPECT_EQ(lookupValue, expected);
	}




}