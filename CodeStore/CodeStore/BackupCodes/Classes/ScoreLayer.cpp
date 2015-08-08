#include "ScoreLayer.h"

ScoreLayer::ScoreLayer()
{

}

ScoreLayer::~ScoreLayer()
{

}

bool ScoreLayer::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("main.plist"); 
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	CCSprite* goalSprite = CCSprite::createWithSpriteFrameName("4.png");
	CCSize spSize = goalSprite->getContentSize();

	int x = 20 +spSize.width;
	int y = winSize.height - spSize.height;
	goalSprite->setPosition(ccp(x, y));
	CCPoint ppp = goalSprite->getAnchorPoint();
	CCLabelTTF* label = CCLabelTTF::create("2048", "Consolas", 16);
	goalSprite->addChild(label);
	label->setPosition(spSize / 2);

	addChild(goalSprite);

	return true;
}

void ScoreLayer::onEnter()
{

}

void ScoreLayer::onExit()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("main.plist");
}
