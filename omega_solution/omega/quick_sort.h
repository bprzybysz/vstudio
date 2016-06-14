#pragma once

#include <vector>


template<class comparable>
class quick_sort
{
	public:
	virtual ~quick_sort()
	{
	}

	using comparable_vector = std::vector<comparable>;

	virtual comparable get_pivot(const comparable_vector& items) const;

	virtual void sort(comparable_vector & items) const;
};

template <class comparable>
comparable quick_sort<comparable>::get_pivot(const comparable_vector& items) const
{
	return items[items.size() / 2];
}

template <class comparable>
void quick_sort<comparable>::sort(comparable_vector & items) const
{
	if (items.size() <= 1)  return;


	comparable_vector smaller;
	comparable_vector same;
	comparable_vector larger;

	auto pivot = get_pivot(items);

	for (auto i : items)
	{
		if (i < pivot)
			smaller.push_back(std::move(i));
		else if (pivot < i)
			larger.push_back(std::move(i));
		else
			same.push_back(std::move(i));
	}

	sort(smaller);
	sort(larger);

	auto s_size = smaller.size();
	auto l_size = larger.size();

	if (s_size > 0)
		std::move(smaller.begin(), smaller.end(), items.begin());
	if (same.size() > 0)
		std::move(same.begin(), same.end(), items.begin() + s_size);
	if (larger.size() > 0)
		std::move(larger.begin(), larger.end(), items.end() - l_size);
}
