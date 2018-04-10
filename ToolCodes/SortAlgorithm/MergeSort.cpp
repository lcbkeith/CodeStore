#include <vector>
#include <algorithm>
//合并两个有序列表。
void mergeVec(std::vector<int>&srcVec, int low, int mid, int high, std::vector<int>& tmpVec)
{
	int i = low, j = mid + 1;

	int k = 0;
	while (i <= mid && j <= high)
	{
		if (srcVec[i] < srcVec[j])
		{
			tmpVec[k++] = srcVec[i++];
		}
		else
		{
			tmpVec[k++] = srcVec[j++];
		}
	}

	while (i <= mid)
	{
		tmpVec[k++] = srcVec[i++];
	}

	while (j <= high)
	{
		tmpVec[k++] = srcVec[j++];
	}

	for (int idx = 0; idx < k; idx++)
	{
		srcVec[low + idx] = tmpVec[idx];
	}
}

//自顶向下的归并排序
void mergeSort(std::vector<int>& srcVec, int low, int high, std::vector<int>& tmpVec)
{
	if (low < high)
	{
		int mid = (low + high) / 2;

		mergeSort(srcVec, low, mid, tmpVec);
		mergeSort(srcVec, mid + 1, high, tmpVec);
		mergeVec(srcVec, low, mid, high, tmpVec);
	}
}

//自底向上的归并排序
void MergeSortBU(std::vector<int>& srcVec)
{
	std::vector<int> tmpVec;
	tmpVec.resize(srcVec.size());

	int length = srcVec.size();
	for (int sz = 1; sz < length; sz *= 2)
	{
		for (int lo = 0; lo < length - sz; lo += 2 * sz)
		{
			mergeVec(srcVec, lo, lo + sz + -1,std::min(lo + 2 * sz - 1, length - 1), tmpVec);
		}
	}
}

void MergeSort(std::vector<int>& srcVec)
{
	std::vector<int> tmpVec;
	tmpVec.resize(srcVec.size());
	mergeSort(srcVec, 0, srcVec.size() - 1, tmpVec);
}
