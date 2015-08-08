/********************************************************************
created:	2015/08/07 15:50
filename: 	MainScene.h
author:	 	Keith

purpose:	
*********************************************************************/
#include "cocos2d.h"

USING_NS_CC;

class MainScene : public CCScene
{
public:
	CREATE_FUNC(MainScene);
	void initLayers();
	virtual void onEnter();
	virtual void onExit();
protected:
private:
};