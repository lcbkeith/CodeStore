/********************************************************************
created:	2015/06/24 14:52
filename: 	Item12.cpp
author:	 	Keith

purpose:	���ƶ���ʱ������ÿһ���ɷ�
*********************************************************************/
#include <string>
class Customer
{
public:
	Customer() :name(""){}

	Customer(const Customer& res) :name(res.name){}
	Customer& operator=(const Customer& res)
	{
		name = res.name;
		return *this;
	}

	std::string name;
	int val;
};

class PriorityCustomer : public Customer
{
public:
	PriorityCustomer() :priority(0)
	{

	}
	PriorityCustomer(const PriorityCustomer& res) 
		:Customer(res),		//�����ʼ��base��
		priority(res.priority)
	{

	}

	PriorityCustomer& operator=(const PriorityCustomer& res)
	{
		//�����base���и�ֵ
		//���û����һ������ôֻ��ֵ�������ࡣ
		//���û����дĬ�Ϲ��캯��������Ҫ��һ��
		__super::operator=(res); 

		priority = res.priority;
		return *this;
	}

	int priority;
};

void mainItem12()
{
	PriorityCustomer cus1;
	cus1.val = 0;
	cus1.name = "111";
	cus1.priority = 111;
	PriorityCustomer cus2;
	cus2 = cus1;
}