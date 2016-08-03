#pragma once
#include "HashMap.h"

namespace CeleraOne
{
	template <typename KeyT, typename ValueT>
	class DoubleHashMap : public HashMap<KeyT, ValueT>
	{
	public:
		using ProbHashFuncT = std::function<size_t(size_t)>;

	private:
		ProbHashFuncT _probHashFunc;

	protected:
		size_t FindIndex(const KeyT& key) const override
		{
			auto probHash = _probHashFunc(key);
			auto idx = probHash % _hashMapSize;
			auto offset = idx;

			std::cout << "Key: " << key;

			for (;; idx += offset)
			{
				if (idx >= _hashMapSize)
					idx -= _hashMapSize;
				auto& entry = _hashMapPtr[idx];
				if (entry.state() == HashMapEntryT::EMPTY || entry.key() == key)
					break;

				std::cout << " | clsn @ [" << idx << "]";
			}

			std::cout << " >>> found @ [" << idx << "]\r\n";

			return idx;
		}

	public:
		explicit DoubleHashMap(size_t capacity, ProbHashFuncT prob_hash_func_t)
			: HashMap<KeyT, ValueT>(capacity),
			_probHashFunc{ prob_hash_func_t }
		{
		}
	};

}
