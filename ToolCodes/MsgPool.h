#pragma once
/********************************************************************
created: 	2017/05/19 0:14
filename: 	MsgPool.h
author: 	Keith
purpose: 	����MessageQueue���ڴ���ɴ˷��䡣������һ��MemBlock�п��У���������
			���û�У��ʹ�ͷ����һ���ڴ�飬���л���֮���п��е�û�С�
			���Ҳû�У���������
			���û�еĻ���newһ���ڴ������
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