#pragma once
#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
namespace VectorRank
{


typedef __int64 int64;
class RankItem
{
public:
	RankItem() :m_id(-1), m_rankVal(0), m_level(0), m_camp(0) {}
	RankItem(int64 oid, int64 rankVal) :
		m_id(oid),
		m_rankVal(rankVal),
		m_level(0),
		m_camp(0) {}

	int64	m_id;
	string	m_head;
	string	m_name;
	int64	m_rankVal;
	int		m_level;
	int		m_camp;
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

enum RankType
{
	RANK_COVER = 1,			//���Ը���ԭֵ
	RANK_TAKEBIGGER = 2,	//ȡ��ֵ
	RANK_ACCUMULATION = 3,	//�ۼ�
};
class RankList
{
public:
	RankList();
	RankList(RankType type, bool autoSort = true, int maxSize = 0);
	void Init(RankType type, bool autoSort = true, int maxSize = 0);

	const RankVec& GetRankVec() const;
	void Sort();									//�ֶ�����
	int GetIndexById(int64 id);						//��ȡid��Ӧ������index
	RankItem* GetIndex(int index);
	int LookupRankById(int64 id, const RankItem*& outItem);
	void Reserve(size_t size);

	bool PushRankItem(RankItem& rankItem);
	bool DeleteRankItem(int64 id);
	void Clear();
private:
	bool IsFull();
	bool Inited();

	RankVec m_rankVec;
	int m_maxSize;
	bool m_autoSort;	//�Ƿ��Զ�����
	RankType m_rankType;

	bool m_sorted;
	bool m_inited;
};




}