#include<vector>
void QuickSort(std::vector<int>& vec, int left, int right)
{
	if (left >= right)
		return;

	int i = left, j = right;
	int key = vec[i];

	while (i < j)
	{
		while (i < j && vec[j] >= key)
			j--;
		if (i < j)
			vec[i++] = vec[j];

		while (i < j && vec[i] <= key)
			i++;

		if (i < j)
			vec[j--] = vec[i];
	}

	vec[i] = key;
	QuickSort(vec, left, i - 1);
	QuickSort(vec, i + 1, right);
}

// int main()
// {
// 	std::vector<int> tmp = { 6, 10, 10, 3, 7 ,1,8 };
// 	QuickSort(tmp, 0, 6);
// 	return 0;
// }
