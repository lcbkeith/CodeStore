#include "Rank.h"
#include "Rank.h"
#include <algorithm>
#include <iostream>
#include <ostream>

RankList::RankList(RankType type, bool autoSort /*= true*/, int maxSize /*= 0 */)
	:m_rankType(type),
	m_autoSort(autoSort),
	m_maxSize(maxSize)
{
	if (m_maxSize > 0)
	{
		m_rankVec.reserve(m_maxSize);
	}
}

RankVec& RankList::GetRankVec()
{
	return m_rankVec;
}

void RankList::SetType(RankType type)
{
	m_rankType = type;
}

void RankList::Sort()
{
	if (m_sorted)
	{
		return;
	}
	sort(m_rankVec.begin(), m_rankVec.end(), greaterRankVal());
	m_rankIndexMap.clear();
	for (size_t index = 0; index < m_rankVec.size(); index++)
	{
		m_rankIndexMap[m_rankVec[index].m_id] = index;
	}

	m_sorted = true;
}

int RankList::GetRankIndex(int64 id)
{
	if (!m_autoSort && !m_sorted)
	{
		Sort();
	}

	RankIndexMap::iterator iter = m_rankIndexMap.find(id);
	if (iter == m_rankIndexMap.end())
	{
		return -1;
	}
	return iter->second;
}

bool RankList::IsFull()
{
	return m_maxSize > 0 && m_rankVec.size() >= m_maxSize;
}

bool RankList::PushRankItem(RankItem& rankItem)
{
	if (m_rankVec.empty())
	{
		m_rankVec.push_back(rankItem);
		m_rankIndexMap[rankItem.m_id] = 0;
		return true;
	}

	RankVec::iterator vecIter = m_rankVec.end();
	RankIndexMap::iterator lookupIter = m_rankIndexMap.find(rankItem.m_id);
	if (lookupIter != m_rankIndexMap.end())
	{
		vecIter = m_rankVec.begin() + lookupIter->second;
	}

	if (vecIter == m_rankVec.end())
	{
		if (IsFull())
		{
			Sort();
			if (rankItem.m_rankVal >= m_rankVec.back().m_rankVal)
			{
				return false;
			}
			m_rankVec.push_back(rankItem);
			SwapForwardOneByOne(m_rankVec.size() - 1);
			m_rankIndexMap.erase(m_rankVec.back().m_id);
			m_rankVec.pop_back();
		}
		else
		{
			m_rankVec.push_back(rankItem);
			if (m_autoSort)
			{
				SwapForwardOneByOne(m_rankVec.size() - 1);
			}
			else
			{
				m_rankIndexMap[rankItem.m_id] = m_rankVec.size() - 1;
				m_sorted = false;
			}
		}
	}
	else
	{
		int64 nowValue = vecIter->m_rankVal;
		if (m_rankType == RANK_COVER)
		{
			vecIter->m_rankVal = rankItem.m_rankVal;
			//cout << "RANK_COVER ,old = " << nowValue << ", new = " << vecIter->m_rankVal << "\n";
		}
		else if (m_rankType == RANK_TAKEBIGGER)
		{
			if (vecIter->m_rankVal >= rankItem.m_rankVal)
			{
				return false;
			}
			vecIter->m_rankVal = rankItem.m_rankVal;
			//cout << "RANK_TAKEBIGGER ,old = " << nowValue << ", new = " << vecIter->m_rankVal << "\n";
		}
		else if (m_rankType == RANK_ACCUMULATION)
		{
			vecIter->m_rankVal = nowValue + rankItem.m_rankVal;
			//cout << "RANK_ACCUMULATION ,old = " << nowValue << ", new = " << vecIter->m_rankVal << "\n";
		}

		if (!m_autoSort)
		{
			if (vecIter->m_rankVal != nowValue)
			{
				m_sorted = false;
			}
			return true;
		}

		if (vecIter->m_rankVal > nowValue)
		{
			SwapForwardOneByOne(vecIter - m_rankVec.begin());
		}
		else if (vecIter->m_rankVal < nowValue)
		{
			SwapBackwardOneByOne(vecIter - m_rankVec.begin());
		}
	}
	return true;
}

void RankList::SwapForwardOneByOne(size_t index)
{
	if (index >= m_rankVec.size())
	{
		return;
	}
	RankVec::iterator vecIter = m_rankVec.begin() + index;
	RankVec::iterator tempIter = vecIter;

	while (tempIter != m_rankVec.begin())
	{
		tempIter--;
		if (tempIter->m_rankVal < vecIter->m_rankVal)
		{
			m_rankIndexMap[tempIter->m_id] ++;	//原来的名次+1
			std::swap(*tempIter, *vecIter);		//交换
			vecIter--;
		}
		else
		{
			break;
		}
	}
	m_rankIndexMap[vecIter->m_id] = vecIter - m_rankVec.begin();
}

void RankList::SwapBackwardOneByOne(size_t index)
{
	if (index + 1 >= m_rankVec.size())
	{
		return;
	}


	RankVec::iterator vecIter = m_rankVec.begin() + index;
	RankVec::iterator tempIter = vecIter;

	while (tempIter + 1 != m_rankVec.end())
	{
		tempIter++;
		if (tempIter->m_rankVal > vecIter->m_rankVal)
		{
			m_rankIndexMap[tempIter->m_id] --;	//原来的名次-1
			std::swap(*tempIter, *vecIter);		//交换
			vecIter++;
		}
		else
		{
			break;
		}
	}
	m_rankIndexMap[vecIter->m_id] = vecIter - m_rankVec.begin();
}

void RankList::PrintOut()
{
	for (int index = 0; index < m_rankVec.size(); index++)
	{
		std::cout << "rank = " << index + 1 << ", \t id = " << m_rankVec[index].m_id << ",\t value = " << m_rankVec[index].m_rankVal << "\n";
	}
	auto iter = m_rankIndexMap.begin();
	for (; iter != m_rankIndexMap.end(); iter++)
	{
		std::cout << "id = " << iter->first << " rank = " << iter->second + 1 << std::endl;
	}
}

bool RankList::Check()
{
	for (int index = 0; index < m_rankVec.size(); index++)
	{
		RankItem& item = m_rankVec[index];
		auto rankIter = m_rankIndexMap.find(item.m_id);
		if (rankIter == m_rankIndexMap.end() || rankIter->second != index)
		{
			cout << "error" << endl;
			return false;
		}
	}
	return true;
}
