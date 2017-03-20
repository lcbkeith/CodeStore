#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Rank.h"
#include <time.h>
void main()
{
	srand(time(0));

	RankList rList(RankType::RANK_ACCUMULATION,true,0);

	const int PUSH_COUNT = 1000000;
	const int ID_COUNT = 10000;

	clock_t start, ends;
	start = clock();
	for (int index = 0; index < PUSH_COUNT; index++)
	{
		int id = rand() % ID_COUNT;
		int value = rand() % 100000;

		RankItem rItem(id, value);
		rList.PushRankItem(rItem);
		
	}
	ends = clock();
	double diff = ends - start;
	double per = diff / PUSH_COUNT;
	cout << "size = " << rList.m_rankVec.size() << ",capacity = " << rList.m_rankVec.capacity() <<", diff = " << diff << ",per = " << per << endl;

	//rList.PrintOut();
	if (!rList.Check())
	{
		system("pause");
	}
	system("pause");
}

//3个设置, 类型, 最大容量, 是否自动排序