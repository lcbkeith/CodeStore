/********************************************************************
created:	2015/06/24 14:52
filename: 	Item12.cpp
author:	 	Keith

purpose:	复制对象时勿忘其每一个成分
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
		:Customer(res),		//这里初始化base类
		priority(res.priority)
	{

	}

	PriorityCustomer& operator=(const PriorityCustomer& res)
	{
		//这里对base进行赋值
		//如果没有这一步，那么只赋值了派生类。
		//如果没有重写默认构造函数，则不需要这一步
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