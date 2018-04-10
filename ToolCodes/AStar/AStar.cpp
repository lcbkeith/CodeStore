#include "CVector3.h"
#include "atart_node.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

typedef vector<CVector3> ASTARPOINTLIST;
typedef std::map<int, CPathNode*> NODEMAP;
NODEMAP path_nodes_;

char nodes[10][10] = 
{ 
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,1,1,1,1,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,1,1,1,1,1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 }
};


void PrintMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << nodes[i][j] << ',';
		}
		std::cout << std::endl;
	}
}

int GetNode(int x, int z)
{
	if (x >= 10 || x < 0
		|| z >= 10 || z < 0)
		
		return -1;
	return nodes[x][z];
}

CPathNode* GetPathNode(int x, int z)
{
	int nodeState = GetNode(x, z);
	if (nodeState < 0)
		return nullptr;
	int key = x * 1000 + z;
	auto iter = path_nodes_.find(key);
	if (iter != path_nodes_.end())
		return iter->second;

	CPathNode* node = new CPathNode;
	node->set_x(x);
	node->set_z(z);
	CVector3 point(x, 0, z);
	if (nodeState == 1)
	{
		node->set_state(CPathNode::NODE_STATE_BLOCKED);
	}
	path_nodes_.insert({ key,node });
	return node;
}

class Cmp
{
public:
	bool operator() (const CPathNode* l, const CPathNode* r) const
	{
		if (l == NULL || r == NULL)
		{
			return false;
		}
		return l->f() > r->f();
	}
};

bool FindPath(const CVector3& start_pos, const CVector3& end_pos, ASTARPOINTLIST& path)
{

	CPathNode* start_node = GetPathNode(start_pos.x(),start_pos.z());
	CPathNode* end_node = GetPathNode(end_pos.x(), end_pos.z());

	if (!start_node || !end_node)
		return false;
	if (start_node->get_state() == CPathNode::NODE_STATE_BLOCKED ||
		end_node->get_state() == CPathNode::NODE_STATE_BLOCKED)
		return false;

	const SPathNodeDirection kDirections[] = {
		{ 0, 1, 10 },
	{ 1, 1, 14 },
	{ 1, 0, 10 },
	{ 1, -1, 14 },
	{ 0, -1, 10 },
	{ -1, -1, 14 },
	{ -1, 0, 10 },
	{ -1, 1, 14 }
	};
	std::vector<CPathNode*> open_list; // 开放列表
	open_list.push_back(start_node);
	start_node->set_state(CPathNode::NODE_STATE_OPEN);
	while (!open_list.empty())
	{
		CPathNode* node = open_list.front();
		std::pop_heap(open_list.begin(), open_list.end(), Cmp());
		open_list.pop_back();
		node->set_state(CPathNode::NODE_STATE_CLOSED); // 关闭 node
		if (node == end_node)
		{
			for (const CPathNode* cursor = node; cursor != NULL; cursor = cursor->get_parent())
			{
				path.push_back(CVector3(cursor->get_x(), 0, cursor->get_z()));
// 				nodes[cursor->get_x()][cursor->get_z()] = '*';
// 				PrintMap();
			}
			return true;
		}

		for (int32_t i = 0; i < sizeof(kDirections) / sizeof(SPathNodeDirection); i++)
		{
			//处理八方向
			int32_t neighbour_x = node->get_x() + kDirections[i].offset_x_;
			int32_t neighbour_z = node->get_z() + kDirections[i].offset_z_;

			CPathNode* neighbour_node = GetPathNode(neighbour_x, neighbour_z);
			if (neighbour_node == NULL)
			{
				continue;
			}

			if (neighbour_node->get_state() != CPathNode::NODE_STATE_UNKNOWN)
			{
				continue;
			}

// 			char tmp = nodes[neighbour_x][neighbour_z];
// 			nodes[neighbour_x][neighbour_z] = '*';
// 			PrintMap();
// 			nodes[neighbour_x][neighbour_z] = tmp;

			neighbour_node->set_g(node->get_g() + kDirections[i].delta_g_);
			//曼哈顿距离
			neighbour_node->set_h((abs(end_node->get_x() - neighbour_node->get_x()) + abs(end_node->get_z() - neighbour_node->get_z())) * 10);
			neighbour_node->set_parent(node);
			//加入 open list
			open_list.push_back(neighbour_node);
			std::push_heap(open_list.begin(), open_list.end(), Cmp());
			neighbour_node->set_state(CPathNode::NODE_STATE_OPEN);
		}
	}

	return false;
}
