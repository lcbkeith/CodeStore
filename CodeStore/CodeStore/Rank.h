#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
typedef __int64 int64;
class RankItem
{
public:
	RankItem() :m_id(-1), m_rankVal(0) {}
	RankItem(int64 oid, int64 rankVal) :
		m_id(oid),
		m_rankVal(rankVal) {}

	int64	m_id;
	int64	m_rankVal;
};

template<class T>
struct vectorFinder
{
public:
	vectorFinder(const int64 id) :m_id(id) {}
	bool operator()(T const& rank) {
		return rank.m_id == m_id;
	}
private:
	int64 m_id;
};

struct greaterRankVal
{
	bool operator()(RankItem const& item1, RankItem const& item2)
	{
		if (item1.m_rankVal > item2.m_rankVal)
			return true;
		else
			return false;
	}
};

typedef std::vector<RankItem> RankVec;
typedef std::map<int64, int> RankIndexMap;
typedef std::vector<RankVec> AllCampRankVec;

enum RankType
{
	RANK_COVER = 1,			//���Ը���ԭֵ
	RANK_TAKEBIGGER = 2,	//ȡ��ֵ
	RANK_ACCUMULATION = 3,	//�ۼ�
};
class RankList
{
public:
	RankList(RankType type, bool autoSort = true, int maxSize = 0);

	RankVec& GetRankVec();

	void SetType(RankType type);
	void Sort();									//�ֶ�����
	int GetRankIndex(int64 id);						//��ȡid��Ӧ������index
	bool IsFull();

	bool PushRankItem(RankItem& rankItem);
	void SwapForwardOneByOne(size_t index);			//��ǰ�ȽϽ���
	void SwapBackwardOneByOne(size_t index);
	void PrintOut();
	bool Check();

	RankVec m_rankVec;
	RankIndexMap m_rankIndexMap;
	int m_maxSize;

	bool m_autoSort;	//�Ƿ��Զ�����
	RankType m_rankType;

	bool m_sorted;
};