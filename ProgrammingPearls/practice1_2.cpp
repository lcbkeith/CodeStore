/********************************************************************
created: 	2017/08/02 21:47
filename: 	practice1_2.cpp
author: 	Keith
purpose: 	如何使用位逻辑运算来实现位向量
*********************************************************************/
//在bitset<int> 中的实现是 bitset[pos / 32] |= 1<<(pos % 32)
//这里的目标，就是将/32和%32改为只有位运算

const int N = 1000000;
const int BITSIZE = 32;
const int SHIFT = 5;
const int MASK = 0x1F; // 11111，用来取得位移之后盖掉的位置
int content[(N-1)/BITSIZE + 1];

void set(int n)
{
	//content[n << SHIFT]表示第几个int值
	//n&MASK 是取得n<<SHIFT后被挤掉的部分
	//1<< n&MASK 将这一位置为1
	content[n >> SHIFT] |= (1 << (n & MASK));
}

void clr(int n)
{
	content[n >> SHIFT] &= ~(1 << (n & MASK));
}

bool get(int n)
{
	return content[n >> SHIFT] & (1 << (n & MASK));
}

// void main()
// {
// 	for (int idx = 0; idx < N; idx++)
// 	{
// 		clr(idx);
// 	}
// 
// 	set(12);
// 	set(32);
// 	clr(12);
// 
// 	bool test = get(32);
// }