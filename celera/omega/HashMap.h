#pragma once

#include <memory>
#include <thread>
#include "PrimeHelper.h"
#include "HashMapEntry.h"

namespace CeleraOne
{
	class HashMapIsFullException : public std::exception
	{
	public:
		HashMapIsFullException()
			: exception("Hash map is full.")
		{
		}
	};

	class NonExistingEntryException : public std::exception
	{
	public:
		NonExistingEntryException()
			: exception("Non-existing entry lokkup attempt.")
		{
		}
	};


	template <typename KeyT, typename ValueT>
	class IHashMap abstract
	{
	protected:
		using HashMapEntryT = HashMapEntry<KeyT, ValueT>;
	public:
		virtual size_t HashMapSize() const = 0;
		virtual size_t CurrentSize() const = 0;
		virtual size_t Capacity() const = 0;
		virtual float MaxLoadFactor() const = 0;
		virtual const HashMapEntryT * HashMapPtr() const = 0;

		virtual float LoadFactor() const = 0;
		virtual void Insert(const KeyT& key, const ValueT& value) = 0;
		virtual void Delete(const KeyT& key) = 0;
		virtual bool Contains(const KeyT& key) const = 0;
		virtual const ValueT& Lookup(const KeyT& key) const = 0;

		virtual ~IHashMap();
	};

	template <typename KeyT, typename ValueT>
	inline IHashMap<KeyT, ValueT>::~IHashMap()
	{
	}

	template <typename KeyT, typename ValueT>
	class HashMap : public IHashMap<KeyT, ValueT>
	{
	protected:
		const float MAX_LOAD_FACTOR = 0.5;

		size_t _hashMapSize;
		size_t _currentSize;
		size_t _capacity;
		std::unique_ptr<HashMapEntryT[]> _hashMapPtr;
		std::hash<KeyT> _hashFunc;

		HashMap() = default;

	public:
		explicit HashMap(size_t capacity)
		{
			Reset(capacity);
		}

		HashMap(const HashMap& other)
		{
			*this = other;
		}

		HashMap(HashMap&& other)
		{
			*this = std::move(other);
		}

		HashMap& operator=(const HashMap& other)
		{
			if (this == &other)
				return *this;
			_hashMapSize = other._hashMapSize;
			_currentSize = other._currentSize;
			_capacity = other._capacity;
			_hashMapPtr.reset(new HashMapEntryT[_hashMapSize]);

			for (auto idx = 0; idx < _hashMapSize; ++idx)
			{
				_hashMapPtr[idx] = other._hashMapPtr[idx];
			}
			
			return *this;
		}

		HashMap& operator=(HashMap&& other)
		{
			if (this == &other)
				return *this;
			_hashMapSize = other._hashMapSize;
			_currentSize = other._currentSize;
			_capacity = other._capacity;
			_hashMapPtr.reset(other._hashMapPtr.release());
			return *this;
		}

		virtual ~HashMap()
		{
		}

		size_t HashMapSize() const override
		{
			return _hashMapSize;
		}

		size_t CurrentSize() const override
		{
			return _currentSize;
		}

		size_t Capacity() const override
		{
			return _capacity;
		}

		float MaxLoadFactor() const override
		{
			return MAX_LOAD_FACTOR;
		}

		const HashMapEntryT * HashMapPtr() const override
		{
			return _hashMapPtr.get();
		}

	protected:
		void Reset(size_t capacity)
		{
			_currentSize = 0;
			_hashMapSize = static_cast<size_t>(capacity / MAX_LOAD_FACTOR);
			if (!PrimeHelper::IsPrime(_hashMapSize))
				_hashMapSize = PrimeHelper::FindNextPrime(_hashMapSize);

			//auto oldHashMap = _hashMapPtr.release(); >> copy it to new one

			_hashMapPtr.reset(new HashMapEntryT[_hashMapSize]);
			_capacity = capacity;
		}

		virtual size_t FindIndex(const KeyT& key) const
		{
			auto idx = _hashFunc(key);
			auto offset = 1;

			for (; ; idx += offset , offset += 2)
			{
				if (idx >= _hashMapSize)
					idx -= _hashMapSize;
				auto& entry = _hashMapPtr[idx];
				if (entry.state() == HashMapEntryT::EMPTY || entry.key() == key)
					break;
			}

			return idx;
		}

	public:
		float LoadFactor() const override
		{
			return static_cast<float>(_currentSize) / _hashMapSize;
		}

		void Insert(const KeyT& key, const ValueT& value) override
		{
			if (_currentSize >= _capacity)
				throw HashMapIsFullException();

			auto idx = FindIndex(key);

			_hashMapPtr[idx].Assign(key, value);
			++_currentSize;
		}

		void Delete(const KeyT& key) override
		{
			auto idx = FindIndex(key);
			_hashMapPtr[idx].Erase();
		}

		bool Contains(const KeyT& key) const override
		{
			auto idx = FindIndex(key);
			return _hashMapPtr[idx].state() == HashMapEntryT::ACTIVE;
		}

		const ValueT& Lookup(const KeyT& key) const override
		{
			auto idx = FindIndex(key);
			if (_hashMapPtr[idx].state() != HashMapEntryT::ACTIVE)
				throw NonExistingEntryException();
			return _hashMapPtr[idx].value();
		}

		void Clear()
		{
			_currentSize = 0;
			for (auto idx = 0u; idx < _hashMapSize; ++idx)
			{
				_hashMapPtr[idx].Empty();
			}
		}
	};
}
