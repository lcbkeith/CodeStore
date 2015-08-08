/********************************************************************
created:	2015/08/07 15:45
filename: 	ScoreLayer.h
author:	 	Keith

purpose:	
*********************************************************************/
#ifndef __ScoreLayer_H__
#define __ScoreLayer_H__
#include "cocos2d.h"
USING_NS_CC;

class ScoreLayer:public CCLayer
{
public:
	ScoreLayer();
	virtual ~ScoreLayer();

	CREATE_FUNC(ScoreLayer);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

protected:
private:
};

#endif