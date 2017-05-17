#pragma once
#include <vector>
#include <vcruntime_string.h>

template<class T>
class CircleDeque
{
public:
	CircleDeque(size_t initSize = 512)
		:m_head(0),
		m_tail(0),
		m_dataSize(0)
	{
		ReAlloc(initSize);
	}

	void ReAlloc(size_t size)
	{
		size_t curSize = m_data.size();
		if (size <= curSize)
		{
			return;
		}

		m_data.resize(size);

		if (m_head != 0)
		{
			memmove(&*m_data.begin() + curSize, &*m_data.begin(), m_head * sizeof(T));
		}
	}

	void PushBack(T& obj)
	{
		if (Full())
		{
			ReAlloc(m_data.size() * 2);
		}
		m_data[m_tail] = obj;
		m_tail++;
		if (m_tail == m_data.size())
		{
			m_tail = 0;
		}
		m_dataSize++;
	}
	void PushFront(T& obj)
	{
		if (Full())
		{
			ReAlloc(m_data.size() * 2);
		}
		if (m_head == 0)
		{
			m_head = m_data.size();
		}
		m_head--;
		m_data[m_head] = obj;
		m_dataSize++;
	}

	T* Front()
	{
		if (Empty())
		{
			return nullptr;
		}
		return m_data[m_head];
	}
	T& Back()
	{
		if (Empty())
		{
			return nullptr;
		}
		if (m_tail == 0)
		{
			return m_data.back();
		}
		return m_data[m_tail - 1];
	}
	void PopFront()
	{
		if (Empty())
		{
			return;
		}
		m_data[m_head].Clear();
		m_head++;
		if (m_head == m_data.size())
		{
			m_head = 0;
		}
		m_dataSize --;
	}
	void PopBack()
	{
		if (Empty())
		{
			return;
		}

		if (m_tail == 0)
		{
			m_tail = m_data.size();
		}
		m_tail--;
		m_data[m_tail].Clear();
		m_dataSize--;

	}
	T* GetIndex(size_t index)
	{
		if (index >= m_data.size())
		{
			return nullptr;
		}
		return &m_data[index%m_data.size()];
	}

	bool Full()
	{
		return m_dataSize >= m_data.size();
	}

	bool Empty()
	{
		return m_dataSize == 0;
	}

	size_t DataSize()
	{
		return m_dataSize;
	}

protected:
private:
	size_t m_head;
	size_t m_tail;
	size_t m_dataSize;
	std::vector<T> m_data;
};
