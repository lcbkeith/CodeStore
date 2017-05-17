#include "CircleDeque/CircleDeque.h"
#include <time.h>
#include <iostream>

struct Ts
{
	Ts() :i(0) {}
	void Clear() { i = 0; }
	int i;
};
void main()
{
	srand(time(NULL));
	CircleDeque<Ts> testQueue(4);

	for (int idx = 0; idx < 1000; idx++)
	{
		
		int rnd = rand() % 100;
		std::cout << rnd << std::endl;
		if (rnd >=70)
		{
			Ts ts;
			ts.i = 1 + idx;
			testQueue.PushFront(ts);
		}
		else if (rnd >= 30)
		{
			Ts ts2;
			ts2.i = 1 + idx;
			testQueue.PushBack(ts2);
		}
		else if (rnd>= 15)
		{
			testQueue.PopFront();
		}
		else
		{
			testQueue.PopBack();
		}
	}
}