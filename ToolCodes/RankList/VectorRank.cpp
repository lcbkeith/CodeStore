#include "VectorRank.h"
#include <algorithm>
namespace VectorRank
{

RankList::RankList()
	:m_rankType(RANK_COVER),
	m_autoSort(true),
	m_maxSize(0),
	m_inited(false)
{

}

RankList::RankList(RankType type, bool autoSort /*= true*/, int maxSize /*= 0*/)
	:m_rankType(type),
	m_autoSort(autoSort),
	m_maxSize(maxSize),
	m_inited(true)
{
	if (m_maxSize > 0)
	{
		m_rankVec.reserve(m_maxSize);
	}
}

void RankList::Init(RankType type, bool autoSort /*= true*/, int maxSize /*= 0*/)
{
	m_rankType = type;
	m_autoSort = autoSort;
	m_maxSize = maxSize;
	Clear();
	m_sorted = true;
	m_inited = true;
}

const RankVec& RankList::GetRankVec() const
{
	return m_rankVec;
}

void RankList::Sort()
{
	if (m_sorted)
	{
		return;
	}
	sort(m_rankVec.begin(), m_rankVec.end(), greaterRankVal());
	m_sorted = true;
}


RankItem* RankList::GetIndex(int index)
{
	if (index < 0 || index >= (int)m_rankVec.size())
	{
		return NULL;
	}
	return &m_rankVec[index];
}

int RankList::LookupRankById(int64 id, const RankItem*& outItem)
{
	RankVec::iterator iter = std::find_if(m_rankVec.begin(), m_rankVec.end(), vectorFinder<RankItem>(id));
	if (iter == m_rankVec.end())
	{
		outItem = NULL;
		return -1;
	}
	outItem = &(*iter);
	return iter - m_rankVec.begin();
}

void RankList::Reserve(size_t size)
{
	m_rankVec.reserve(size);
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
		return true;
	}
	RankVec::iterator vecIter = std::find_if(m_rankVec.begin(), m_rankVec.end(), vectorFinder<RankItem>(rankItem.m_id));
	if (vecIter != m_rankVec.end())
	{
		int64 nowValue = vecIter->m_rankVal;
		//if (m_rankType == RANK_COVER)
		//{
		// 			
		//}
		if (m_rankType == RANK_TAKEBIGGER)
		{
			if (nowValue >= rankItem.m_rankVal)
			{
				return false;
			}
		}
		else if (m_rankType == RANK_ACCUMULATION)
		{
			rankItem.m_rankVal = nowValue + rankItem.m_rankVal;
		}

		if (rankItem.m_rankVal == nowValue)
		{
			return false;
		}

		if (m_autoSort)
		{
			m_rankVec.erase(vecIter);
			m_rankVec.insert(std::upper_bound(m_rankVec.begin(), m_rankVec.end(), rankItem, greaterRankVal()), rankItem);
		}
		else
		{
			vecIter->m_rankVal = rankItem.m_rankVal;
		}
	}
	else
	{
		if (IsFull())
		{
			Sort();
			if (rankItem.m_rankVal <= m_rankVec.back().m_rankVal)
			{
				return false;
			}
			m_rankVec.pop_back();
			m_rankVec.insert(std::upper_bound(m_rankVec.begin(), m_rankVec.end(), rankItem, greaterRankVal()), rankItem);
			return true;
		}
		if (m_autoSort)
		{
			m_rankVec.insert(std::upper_bound(m_rankVec.begin(), m_rankVec.end(), rankItem, greaterRankVal()), rankItem);
		}
		else
		{
			m_rankVec.push_back(rankItem);
			m_sorted = false;
		}
	}
	return true;
}

bool RankList::DeleteRankItem(int64 id)
{
	RankVec::iterator iter = std::find_if(m_rankVec.begin(), m_rankVec.end(), vectorFinder<RankItem>(id));
	if (iter != m_rankVec.end())
	{
		m_rankVec.erase(iter);
		return true;
	}
	return false;
}

void RankList::Clear()
{
	m_rankVec.clear();
	m_sorted = true;
}

bool RankList::Inited()
{
	return m_inited;
}


}