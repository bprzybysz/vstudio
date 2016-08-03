#pragma once
#include "HashMap.h"

namespace CeleraOne
{
	template <typename KeyT, typename ValueT>
	class DoubleHashMap : public HashMap<KeyT, ValueT>
	{
	public:
		using ProbHashFuncT = std::function<unsigned int(unsigned int)>;

	private:
		ProbHashFuncT _probHashFunc;

	protected:
		size_t Offset(const KeyT& key) const
		{
			auto hash = _hashFunc(key);
			hash >>= 2;
			auto x = static_cast<unsigned int>((hash >> 32) + (hash & 0xFFFFFFFF));
			auto probHash = _probHashFunc(x);
			auto offset = probHash % _hashMapSize;
			return offset == 0 ? _hashMapSize - 1 : offset;
		}

		size_t FindIndex(const KeyT& key) const override
		{
			auto offset = Offset(key);

			std::cout << "key=" << key << "(+" << offset << "):";

			size_t idx;
			for (idx = offset; ; idx += offset)
			{
				if (idx >= _hashMapSize)
					idx -= _hashMapSize;
				auto& entry = _hashMapPtr[idx];
				if (entry.state() == HashMapEntryT::EMPTY || entry.key() == key)
					break;
				std::cout << " x(" << idx << ")";
			}

			std::cout << " +[" << idx << "]\r\n";

			return idx;
		}

	public:
		explicit DoubleHashMap(size_t capacity, ProbHashFuncT prob_hash_func_t)
			: HashMap<KeyT, ValueT>(capacity),
			  _probHashFunc{prob_hash_func_t}
		{
		}
	};
}
