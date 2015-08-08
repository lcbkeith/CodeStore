#include <map>
#include <memory>
#include <vector>
#include <time.h>
class testClass
{
public:
	testClass()
	{
		printf("testClass \n");
	}
	~testClass()
	{
		printf("~testClass \n");
	}
};
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
		if (rnd<0)
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
	if (get_size<=0)
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

	while ( output_vec.size() != get_size && !items.empty() )
	{
		int rnd = rand() % max_weight;
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
void main()
{
	time_t timep;

	time(&timep);

	srand(timep);
	std::vector<int> ivec1;
	std::vector<unsigned int> weight;
	for (int index = 0; index < 40 ; index++)
	{
		ivec1.push_back(index);
		weight.push_back(index * 2);
	}

	//std::vector<int> ivec1 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	//std::vector<unsigned int> weight = { 1,2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,32768 };
// {1,2,4,8,16,32,64,128,256,512};
	std::map<int, int> countMap;
// 	for (int index = 0; index < 100000 ; index++)
// 	{
// 		int i = random_gen(ivec1, weight);
// 		countMap[i]++;
// 		printf("rnd = %d \n", i);
// 	}
	int time1 = timep;
	for (int index = 0; index < 10000; index++)
	{
		std::vector<int> get_n = random_gen_n(ivec1, weight, 10);
		for (int id : get_n)
		{
			countMap[id]++;
		}
	}
	time(&timep);
	int diff = timep - time1;

	printf("diff time = %d\n", diff);
	int i = 1;
}