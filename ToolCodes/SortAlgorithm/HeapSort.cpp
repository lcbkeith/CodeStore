/*
第一部，堆化数据，从第一个有子节点的节点开始（length/2 -1 )
从后往前，最小（或者最大）的往上浮

然后开始排序，将第一个和最后一个交换，最小（或者最大）的
就在数组尾端，剩下的堆化。
*/

#include<vector>
void maxHeapify(std::vector<int>& src, int i, int length)
{
	int left = i * 2 + 1;
	while (left <= length)
	{
		int j = left;
		int right = left + 1;
		if (right < length && src[right] > src[left])
			j = right;

		if (src[i] >= src[j])
			break;

		std::swap(src[i], src[j]);
		i = j;
		left = i * 2 + 1;
	}
}

void minHeapify(std::vector<int>&src, int i, int length)
{
	int left = i * 2 + 1;

	while (left <= length)
	{
		int right = left + 1;
		int j = left;
		if (right < length && src[left] > src[right])
			j = right;

		if (src[i] <= src[j])
			break;

		std::swap(src[i], src[j]);
		i = j;
		left = i * 2 + 1;
	}
}

void HeapSort(std::vector<int>& src)
{
	if (src.empty())
		return;

	int length = src.size() - 1;
	//①make heap
	//std::make_heap(src.begin(), src.end());
	for (int idx = length / 2 - 1; idx >= 0; idx--)
	{
		minHeapify(src, idx, length);
	}
	//②adjust

	while (length >= 0)
	{
		std::swap(src[0], src[length--]);
		minHeapify(src, 0, length);
	}
}
