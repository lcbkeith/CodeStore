#include <vector>
#include "CircleQueue.h"
struct Ts
{
	Ts():i(0),j(0){}

	int i;
	int j;
};
void main()
{
	CircleQueue<Ts> testQueue(2);

	for (int idx = 0; idx < 1000 ; idx++)
	{
		Ts ts;
		ts.i = 1;
		ts.j = 2;
		testQueue.PushFront(ts);

		Ts ts2;
		ts2.i = 11;
		ts2.j = 22;
		testQueue.PushBack(ts2);
	}

}