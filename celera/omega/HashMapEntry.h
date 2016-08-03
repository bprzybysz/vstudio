#include <mutex>

namespace CeleraOne
{
	class HashEntryOperationException : std::exception
	{
	public:

		explicit HashEntryOperationException(const char* const& string)
			: exception{string}
		{
		}
	};


	template<typename KeyT, typename ValueT>
	class HashMapEntry
	{
	public:
		enum EntryState
		{
			ACTIVE,
			EMPTY,
			ERASED
		};

	private:
		KeyT _key;
		EntryState _state;
		ValueT _value;
		std::mutex _mutex;

	public:
		HashMapEntry()
			: _key{}, _state(EMPTY), _value{}
		{
		}

		HashMapEntry(const KeyT& key, const ValueT& value, EntryState _state = EMPTY)
			: _key{ key }, _state{ _state }, _value{ value }
		{
		}

		HashMapEntry(const HashMapEntry & other)
		{
			*this = other;
		}

		HashMapEntry & operator=(const HashMapEntry & other)
		{
			_key = other._key;
			_value = other._value;
			_state = other._state;

			return *this;
		}


		friend bool operator==(const HashMapEntry& lhs, const HashMapEntry& rhs)
		{
			return lhs._key == rhs._key
				&& lhs._state == rhs._state
				&& lhs._value == rhs._value;
		}

		friend bool operator!=(const HashMapEntry& lhs, const HashMapEntry& rhs)
		{
			return !(lhs == rhs);
		}

		const KeyT& key() const
		{
			return _key;
		}

		const ValueT& value() const
		{
			return _value;
		}

		EntryState state() const
		{
			return _state;
		}

		void Assign(const ValueT& key, const ValueT& value)
		{
			std::lock_guard<std::mutex> lck(_mutex);
			if (_state == ACTIVE)
				throw new HashEntryOperationException("Active entry assignement attempt.");
			_value = value;
			_key = key;
			_state = ACTIVE;
		}

		void Update(const ValueT& key, const ValueT& value)
		{
			std::lock_guard<std::mutex> lck(_mutex);
			if (_key != key)
				throw new HashEntryOperationException("Wrong key entry update attempt.");
			if (_state != ACTIVE)
				throw new HashEntryOperationException("Inactive entry update attempt.");

			_value = value;
		}

		void Erase()
		{
			std::lock_guard<std::mutex> lck(_mutex);
			if (_state != ACTIVE)
				throw new HashEntryOperationException("Inactive entry erase attempt.");
			_state = ERASED;
		}

		void Empty()
		{
			std::lock_guard<std::mutex> lck(_mutex);
			_state = EMPTY;
		}
	};
}