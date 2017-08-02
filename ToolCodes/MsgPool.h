#pragma once
/********************************************************************
created: 	2017/05/19 0:14
filename: 	MsgPool.h
author: 	Keith
purpose: 	放入MessageQueue的内存块由此分配。如果最后一个MemBlock有空闲，就拿来用
			如果没有，就从头过滤一遍内存块，看有回收之后有空闲的没有。
			如果也没有（）。。。
			最后都没有的话。new一个内存块来用
*********************************************************************/
#include <mutex>

struct MiniLocker
{
	MiniLocker(std::mutex& locker) :m_mutex(&locker) { m_mutex->lock(); }
	~MiniLocker() { m_mutex->unlock(); }
	std::mutex* m_mutex;
};

class MessagePool
{
private:
	const static int BLOCKSIZE = 1024;
	struct MemBlock
	{
		MemBlock()
			:next(0)
			, pos(BLOCKSIZE),
			freePos(BLOCKSIZE)
		{
		}
		MemBlock* next;
		size_t pos;
		size_t freePos;
		char buffer[BLOCKSIZE];

		bool empty(void)
		{
			return freePos <= pos;
		}

		void reset()
		{
			next = 0;
			pos = freePos = BLOCKSIZE;
		}
	};

	MemBlock* _first;
	MemBlock* _last;
	std::mutex _allocMutex;
	std::mutex _freeMutex;
public:
	size_t BlockCount;
	MessagePool()
	{
		_first = _last = new MemBlock;
		BlockCount = 1;
	}

	void* alloc(size_t cb)
	{
		MiniLocker locker(_allocMutex);
		if (_last->pos < cb)
		{
			MiniLocker locker(_freeMutex);
			MemBlock* newBlock = 0;

			MemBlock* block = _first;
			while (block && block->freePos <= block->pos)
			{
				MemBlock* next = block->next;
				if (BlockCount <= 2)
				{
					newBlock = block;
					block = next;
					break;
				}

				if (newBlock == 0)
				{
					newBlock = block;
				}
				else
				{
					delete block;
					--BlockCount;
				}

				block = next;
			}
			if (newBlock == 0)
			{
				MemBlock* emptyBlock = _first;
				MemBlock* prevBlock = _first;
				while (emptyBlock && !emptyBlock->empty())
				{
					prevBlock = emptyBlock;
					emptyBlock = emptyBlock->next;
				}
				if (prevBlock && emptyBlock && prevBlock != emptyBlock)
				{
					prevBlock->next = emptyBlock->next;
					emptyBlock->next = 0;
					newBlock = emptyBlock;
					if (_last == emptyBlock)
					{
						_last = prevBlock;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////
			if (newBlock == 0)
			{
				newBlock = new MemBlock;
				++BlockCount;
			}
			else
			{
				newBlock->reset();
			}

			if (block == 0)
			{
				_first = _last = newBlock;
			}
			else
			{
				_first = block;
				_last = _last->next = newBlock;
			}
		}


		return (_last->buffer) + (_last->pos -= cb);
	}

	void free(void*p, size_t cb)
	{
		MiniLocker scopelock(_freeMutex);
		MemBlock* block = _first;
		while (block)
		{
			if (block->buffer <= (char*)p
				&& (char*)p < (char*)block + sizeof(MemBlock))
			{
				if (block->freePos > cb)
				{
					block->freePos -= cb;
				}
				else
				{
					block->freePos = 0;
				}

				return;
			}

			block = block->next;
		}
		int i = 0;
		i++;
	}
};