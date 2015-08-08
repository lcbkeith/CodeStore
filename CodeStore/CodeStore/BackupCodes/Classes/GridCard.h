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
	CREATE_FUNC(GridCard);
	void setSF(const char* frameName);

	int num;

protected:
private:

};



#endif