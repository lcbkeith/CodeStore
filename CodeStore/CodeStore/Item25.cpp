/********************************************************************
created:	2015/06/26 19:21
filename: 	Item25.cpp
author:	 	Keith

purpose:	Effective C++ 条款25：考虑写出一个不抛异常的swap函数
*********************************************************************/
#include <algorithm>

class WidgetImpl
{
public:
private:
	int a;
};


class Widget
{
public:
	Widget(WidgetImpl* impl)
	{
		pImpl = impl;
	}
	Widget(const Widget& rhs)
	{

	}

// 	Widget operator= (const Widget& rhs)
// 	{
// 		*pImpl = *(rhs.pImpl);
// 	}

	void swap(Widget& other)
	{
		std::swap(pImpl, other.pImpl);
	}
private:
	WidgetImpl* pImpl;
};


void swap(Widget&a, Widget&b)
{
	a.swap(b);
}


namespace std
{
	//这里template<>表示这是std::swap的一个全特化版本。
	//下面的<Widget>表示，这个特化版本是针对T是Widget而设计的。
	//①
// 	template<>
// 	void swap<Widget>(Widget&a, Widget&b)
// 	{
// 		a.swap(b);
// 	}
}

void main222()
{
	WidgetImpl* impl1 = new WidgetImpl();
	Widget wid1(impl1);
	Widget wid2(NULL);
	//①
	std::swap(wid1, wid2);

}