/********************************************************************
created:	2015/08/07 11:40
filename:   GameLayer.h
author:	 	Keith

purpose:	
*********************************************************************/
#ifndef __GameLayer_H__
#define __GameLayer_H__
#endif
#include "cocos2d.h"
#include "cocos-ext.h"

#include "GridCard.h"
USING_NS_CC;

USING_NS_CC_EXT;
class GameLayer :public CCLayerColor
{
public:
	GameLayer();
	virtual ~GameLayer();

	CREATE_FUNC(GameLayer);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void begin_create();

	void create_new_num();

private:
	GridCard* gridArr[4][4];
	CCLayer* grid_layer;
	CCLayer* scores_layer;
};
