#include "CircleDeque/CircleDeque.h"
#include <time.h>
#include <iostream>
#include "MsgPool.h"

struct Ts
{
	Ts() :i(0) {}
	void Clear() { i = 0; }
	int i;
};

struct Mem
{
	void* mem;
	size_t size;
};
void main()
{
	srand(time(NULL));
	MessagePool pool;

	std::vector<Mem> vec;

	for (int index = 0; index < 10; index++)
	{
		int rndSize = (rand() % 1024)+1;
		Mem mem;
		mem.mem = pool.alloc(rndSize);
		mem.size = rndSize;

		vec.push_back(mem);
	}

	while (!vec.empty())
	{
		int rnd = rand() % vec.size();

		auto iter = vec.begin() + rnd;

		Mem& mem = *iter;

		pool.free(mem.mem, mem.size);
	}
}