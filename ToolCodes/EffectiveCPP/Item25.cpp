/********************************************************************
created:	2015/06/26 19:21
filename: 	Item25.cpp
author:	 	Keith

purpose:	Effective C++ ����25������д��һ�������쳣��swap����
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
	//����template<>��ʾ����std::swap��һ��ȫ�ػ��汾��
	//�����<Widget>��ʾ������ػ��汾�����T��Widget����Ƶġ�
	//��
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
	//��
	std::swap(wid1, wid2);

}