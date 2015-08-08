/********************************************************************
created:	2015/08/07 18:01
filename: 	GridCard.h
author:	 	Keith

purpose:	
*********************************************************************/
#ifndef __GridCard_H__
#define __GridCard_H__

#include "cocos2d.h"
USING_NS_CC;

class GridCard : public CCSprite
{
public:
	GridCard() :show_num(0){}
	~GridCard(){}
	CREATE_FUNC(GridCard);
	virtual bool init();
	void setSF(const char* frameName);

	void set_num(int num);
	void remove_num();

	int show_num;

protected:
private:

};



#endif