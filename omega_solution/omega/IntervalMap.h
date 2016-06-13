#pragma once

#include <assert.h>
#include <map>
#include <limits>

template<class K, class V>
class IntervalMap
{
	friend void IntervalMapTest()
	{
		
	};

private:
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	explicit IntervalMap(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	};

	// Assign value val to interval [keyBegin, keyEnd). 
	// Overwrite previous values in this interval. 
	// Do not change values outside this interval.
	// Conforming to the C++ Standard Library conventions, the interval 
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, 
	// and assign must do nothing.

	void assign(K const& keyBegin, K const& keyEnd, const V& val) {
		//if invalid boundaries - do nothing
		if (!(keyBegin < keyEnd))
			return; 

		//try to insert upper bound (if needed, proper val 
		//is set in next step)
		auto upper_info = m_map.emplace(keyEnd, val);
		auto upper_it = upper_info.first;

		//if successfully inserted, copy previous interval value
		auto upper_inserted = upper_info.second;
		if (upper_inserted)
			upper_it->second = std::prev(upper_it)->second;

		//try to insert lower bound
		auto lower_info = m_map.emplace(keyBegin, val);
		auto lower_it = lower_info.first;

		//if existing interval is hit, update its value
		auto lower_inserted = lower_info.second;
		if(!lower_inserted)
			lower_it->second = val;

		//if previous interval has the same value, 
		//mark it as true lower
		auto prev_to_lower_it = std::prev(lower_it);
		if (prev_to_lower_it != m_map.end()
			&& lower_it->second == prev_to_lower_it->second)
			lower_it = prev_to_lower_it;

		//mark to merge if next interval has the same value
		if (upper_it->second == lower_it->second)
			++upper_it;

		//overwrite intervals in the scope by removing them
		m_map.erase(++lower_it, upper_it);
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}


};


// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the IntervalMap, for example using a map of unsigned int
// intervals to char.



