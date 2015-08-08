#include "GridCard.h"

bool GridCard::init()
{
	if (!CCSprite::init())
	{
		return false;
	}

	setSF("5.png");
	show_num = 0;
	return true;
}

void GridCard::setSF(const char* frameName)
{
	initWithSpriteFrameName("5.png");
}

void GridCard::set_num(int num)
{
	//���ø����ڵ����֣��ڸ����ڼ�һ���µ���ʾ�õ�show_sprite������tag111.
	show_num = num;
	CCSprite* show_sprite = CCSprite::createWithSpriteFrameName("2.png");
	addChild(show_sprite, 2, show_num);
	show_sprite->setAnchorPoint(ccp(0, 0));
	CCLabelTTF* label = CCLabelTTF::create(CCString::createWithFormat("%d", num)->getCString(), "Consolas", 20);
	label->setPosition(show_sprite->getContentSize() / 2);
	show_sprite->addChild(label);

}

void GridCard::remove_num()
{
	if (show_num == 0)
	{
		return;
	}
	removeChildByTag(show_num);
	show_num = 0;
}
