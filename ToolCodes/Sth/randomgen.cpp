#include <vector>
template<class T>
T random_gen(std::vector<T>& items, std::vector<unsigned int>& weight)
{
	//容错。items列表不能大于权重的列表。
	if (weight.size() < items.size())
	{
		int diff = items.size() - weight.size();
		for (int index = 0; index < diff; index++)
		{
			weight.push_back(1);
		}
	}
	int max_weight = 0;
	for (int index = 0; index < items.size(); index++)
	{
		max_weight += weight[index];
	}

	int rnd = rand() % max_weight;
	for (int index = 0; index < items.size(); index++)
	{
		rnd = rnd - weight[index];
		if (rnd < 0)
		{
			return items[index];
		}
	}
	return items[items.size() - 1];
}

template<class T>
std::vector<T> random_gen_n(std::vector<T> items, std::vector<unsigned int> weight, int get_size)
{
	if (items.size() <= get_size)
	{
		return items;
	}
	if (get_size <= 0)
	{
		std::vector<T> vec;
		return vec;
	}
	if (weight.size() < items.size())
	{
		int diff = items.size() - weight.size();
		for (int index = 0; index < diff; index++)
		{
			weight.push_back(1);
		}
	}
	int max_weight = 0;
	for (int index = 0; index < items.size(); index++)
	{
		max_weight += weight[index];
	}
	std::vector<T> output_vec;

	while (output_vec.size() != get_size && !items.empty())
	{
		int rnd = rand() % max_weight;
		printf("rnd = %d \n", rnd);
		bool found = false;
		auto item_iter = items.begin();
		auto weight_iter = weight.begin();
		while (item_iter != items.end())
		{
			rnd = rnd - *weight_iter;
			if (rnd < 0)
			{
				output_vec.push_back(*item_iter);
				max_weight -= *weight_iter;
				item_iter = items.erase(item_iter);
				weight_iter = weight.erase(weight_iter);
				found = true;
				break;
			}
			if (!found)
			{
				item_iter++;
				weight_iter++;
			}
		}
	}
	return output_vec;
}