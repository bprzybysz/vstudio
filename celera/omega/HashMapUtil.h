#pragma once

#include "HashMap.h"
#include <vector>

namespace CeleraOne
{
	class HashMapUtilException : std::exception
	{
	public:

		explicit HashMapUtilException(const char* const& string)
			: exception{string}
		{
		}
	};

	template <typename KeyT, typename ValueT>
	class HashMapUtil : public HashMap<KeyT, ValueT>
	{
	public:
		explicit HashMapUtil(size_t capacity)
			: HashMap<KeyT, ValueT>(capacity)
		{
		}

		explicit HashMapUtil(const HashMap<KeyT, ValueT> & baseHashMap)
			: HashMap<KeyT, ValueT>(baseHashMap)
		{
		}

		explicit HashMapUtil(HashMap<KeyT, ValueT> && baseHashMap)
			: HashMap<KeyT, ValueT>(std::move(baseHashMap))
		{
		}

		std::vector<HashMapEntryT> Preview() const
		{
			std::vector<HashMapEntryT> preview(_hashMapSize);

			for (auto i = 0u; i < _hashMapSize; ++i)
				preview[i] = _hashMapPtr[i];

			return std::move(preview);
		}


		std::vector<size_t> InsertKeysToIndexVector(std::vector<KeyT>& keys, bool resetHashMap)
		{
			auto size = keys.size();

			if (resetHashMap)
				Reset(size);

			std::vector<size_t> indexes((size));

			for (auto idx = 0u; idx < size; ++idx)
			{
				auto key = keys[idx];
				indexes[idx] = FindIndex(key);
				Insert(key, idx);
			}


			return std::move(indexes);
		}

		size_t HashIdx(const KeyT & key)
		{
			auto idx = FindIndex(key);
			if (_hashMapPtr[idx].state() != HashMapEntryT::ACTIVE)
				throw new HashMapUtilException("There's no entry in map for this key");
			return idx;
		}
	};

};