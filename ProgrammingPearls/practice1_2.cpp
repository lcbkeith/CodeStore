/********************************************************************
created: 	2017/08/02 21:47
filename: 	practice1_2.cpp
author: 	Keith
purpose: 	���ʹ��λ�߼�������ʵ��λ����
*********************************************************************/
//��bitset<int> �е�ʵ���� bitset[pos / 32] |= 1<<(pos % 32)
//�����Ŀ�꣬���ǽ�/32��%32��Ϊֻ��λ����

const int N = 1000000;
const int BITSIZE = 32;
const int SHIFT = 5;
const int MASK = 0x1F; // 11111������ȡ��λ��֮��ǵ���λ��
int content[(N-1)/BITSIZE + 1];

void set(int n)
{
	//content[n << SHIFT]��ʾ�ڼ���intֵ
	//n&MASK ��ȡ��n<<SHIFT�󱻼����Ĳ���
	//1<< n&MASK ����һλ��Ϊ1
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