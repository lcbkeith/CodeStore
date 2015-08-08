#include "GameLayer.h"

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("main.plist");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	initWithColor(ccc4(0, 139, 139, 255));
	setPosition(winSize / 2);
	setContentSize(ccp(200, 200));
	ignoreAnchorPointForPosition(false);
	setAnchorPoint(ccp(0.5,0.5));

	//带颜色的背景
	extension::CCScale9Sprite* gameBg = extension::CCScale9Sprite::createWithSpriteFrameName("4.png");
	gameBg->setContentSize(ccp(200, 200));
	gameBg->setAnchorPoint(ccp(0, 0));
	addChild(gameBg);
	
// 	CCTexture2D* tex = CCSprite::createWithSpriteFrameName("5.png")->getTexture();
// 	CCSpriteBatchNode* sbn = CCSpriteBatchNode::createWithTexture(tex);
	//4*4的方格
	for (int x = 0; x < 4 ; x++)
	{
		for (int y = 0; y < 4 ; y++)
		{
			GridCard* grid = GridCard::create();
			grid->setSF("5.png");
			grid->num = 0;
			grid->setPosition(ccp(25+x*50, 25+y*50));
			CCLabelTTF* label = CCLabelTTF::create(CCString::createWithFormat("%d,%d",x,y)->getCString(), "Consolas", 16);
			label->setAnchorPoint(ccp(0, 0));
			grid->addChild(label);
			gameBg->addChild(grid,2, x*4+y);

			gridArr[x][y] = grid;
		}
	}

	setTouchEnabled(true);
	return true;
}

void GameLayer::onEnter()
{
	CCLayer::onEnter();
	begin_create();
}

void GameLayer::onExit()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("main.plist");
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog(CCString::createWithFormat("%d,%d", pTouch->getLocation().x, pTouch->getLocation().y)->getCString());
	
	return true;
}

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameLayer::begin_create()
{
	for (int index = 0; index < 2 ; index++)
	{
		create_new_num();
	}
	
}

void GameLayer::create_new_num()
{
	while (true)
	{
		char randx = rand() % 4;
		char randy = rand() % 4;
		GridCard* grid = gridArr[randx][randy];
		if (grid->num == 0)
		{
			//设置格子内的数字，在格子内加一个新的显示用的show_sprite。设置tag111.
			grid->num = 2;
			CCSprite* show_sprite = CCSprite::createWithSpriteFrameName("2.png");
			grid->addChild(show_sprite, 2, 111);
			show_sprite->setAnchorPoint(ccp(0, 0));
			CCLabelTTF* label = CCLabelTTF::create(CCString::createWithFormat("%d", grid->num)->getCString(), "Consolas", 20);
			label->setPosition(show_sprite->getContentSize() / 2);
			show_sprite->addChild(label);
			break;
		}
	}
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint point = touch->getLocation();

	CCPoint locPoint = convertToNodeSpace(point);

	if (locPoint.x < 0 || locPoint.y < 0 ||locPoint.x > getContentSize().width || locPoint.y > getContentSize().height)
	{
		return;
	}

	CCLog(CCString::createWithFormat("%.2f,%.2f", locPoint.x, locPoint.y)->getCString());
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{

}


