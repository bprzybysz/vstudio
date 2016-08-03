#pragma once

#include <vector>
using namespace CeleraOne;

namespace ut
{
	using UIntHashMapEntryT = HashMapEntry<unsigned int, unsigned int>;
	using UIntHashMapT = HashMap<unsigned int, unsigned int>;
	using UIntDoubleHashMapT = DoubleHashMap<unsigned int, unsigned int>;
	using UIntUtilHashMapT = HashMapUtil<unsigned int, unsigned int>;
	using IUintHashMapT = IHashMap<unsigned int, unsigned int>;


	class HashMapUtHelper
	{
	public:
		struct HashMapProps;

		using HashMapPropsVectorT = std::vector<HashMapProps>;

		struct HashMapProps
		{
			size_t ExpectedHashMapSize;
			size_t ExpectedCapacity;
			size_t ExpectedCurrentSize;
			double ExpectedMaxLoadFactor;

			size_t SetMapCapacity;

			bool operator==(const HashMapProps& other) const
			{
				return ExpectedHashMapSize == other.ExpectedHashMapSize &&
					ExpectedCapacity == other.ExpectedCapacity &&
					ExpectedCurrentSize == other.ExpectedCurrentSize &&
					ExpectedMaxLoadFactor == other.ExpectedMaxLoadFactor;
			}
		};

		enum UnitTestId
		{
			HashMapCreateTest = 0,
			HashMapInsertTest = 1

		};

	private:

		static HashMapPropsVectorT InitTestData()
		{
			return std::move(
				HashMapPropsVectorT{
					{101, 50, 0, 0.5, 50},
					{23, 10, 4, 0.5, 10}
				});
		}

		HashMapPropsVectorT _testData;
	public:
		HashMapUtHelper()
		{
			_testData = InitTestData();
		}

		HashMapPropsVectorT::value_type operator[](UnitTestId testId) const
		{
			return _testData[testId];
		}

		bool AsExpected(const IUintHashMapT& hashMap, UnitTestId testId) const
		{
			return _testData[testId] ==
				HashMapProps{
					hashMap.HashMapSize(),
					hashMap.Capacity(),
					hashMap.CurrentSize(),
					hashMap.MaxLoadFactor(),
					hashMap.Capacity()};
		}
	};
}