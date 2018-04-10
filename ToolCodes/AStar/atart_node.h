#pragma once

typedef int int32_t;
struct SPathNodeDirection
{
	int32_t offset_x_;
	int32_t offset_z_;
	int32_t delta_g_;
};

class CPathNode
{
public:
	enum ENodeState
	{
		NODE_STATE_UNKNOWN = 0,
		NODE_STATE_OPEN = 1,
		NODE_STATE_CLOSED = 2,
		NODE_STATE_BLOCKED = 3,
	};

	CPathNode()
	{
		state_ = NODE_STATE_UNKNOWN;
		g_ = 0;
		h_ = 0;
		x_ = 0;
		z_ = 0;
		parent_ = nullptr;
	}
	~CPathNode() {}

	int32_t get_g() const { return g_; }
	void set_g(int32_t g) { g_ = g; }
	int32_t get_h() const { return h_; }
	void set_h(int32_t h) { h_ = h; }
	int32_t get_x() const { return x_; }
	void set_x(int32_t x) { x_ = x; }
	int32_t get_z() const { return z_; }
	void set_z(int32_t z) { z_ = z; }

	ENodeState get_state() const { return state_; }
	void set_state(ENodeState state) { state_ = state; }
	const CPathNode *get_parent() const { return parent_; }
	void set_parent(CPathNode *parent) { parent_ = parent; }

	int32_t f() const { return g_ + h_; }

	bool operator == (const CPathNode& other)
	{
		return x_ == other.x_;
		return z_ == other.z_;
	}
protected:
private:
	ENodeState state_;
	int32_t g_;
	int32_t h_;
	int32_t x_;
	int32_t z_;
	CPathNode *parent_;
};


