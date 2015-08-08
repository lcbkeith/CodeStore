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
			grid->setPosition(ccp(25 + x * 50, 25 + y * 50));
			gameBg->addChild(grid, 2, x * 4 + y);

			CCLabelTTF* label = CCLabelTTF::create(CCString::createWithFormat("%d,%d", x, y)->getCString(), "Consolas", 16);
			label->setAnchorPoint(ccp(0, 0));
			grid->addChild(label);

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
		if (grid->show_num == 0)
		{
			//设置格子内的数字，在格子内加一个新的显示用的show_sprite。设置tag111.
			grid->set_num(2);
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

	begin_point = locPoint;

	//CCLog(CCString::createWithFormat("%.2f,%.2f", locPoint.x, locPoint.y)->getCString());
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if (begin_point.x == 0 &&  begin_point.y == 0)
	{
		return;
	}
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint point = touch->getLocation();
	CCPoint locPoint = convertToNodeSpace(point);

	if (locPoint.x < 0 || locPoint.y < 0 || locPoint.x > getContentSize().width || locPoint.y > getContentSize().height)
	{
		return;
	}


	CCPoint diff = locPoint - begin_point;

	if (abs(diff.x) + abs(diff.y) < 30)
		return;

	begin_point = ccp(0, 0);

	//CCLog(CCString::createWithFormat("moving %.2f,%.2f", locPoint.x, locPoint.y)->getCString());

	float ratio = abs(diff.x / diff.y);

	if (diff.x > 0 && ratio > 2.0f)
	{
		CCLog("right");
		if (doRight())
			create_new_num();
	}
	else if (diff.x < 0 && ratio > 2.0f)
	{
		CCLog("left");
		if (doLeft())
			create_new_num();
	}
	else if (diff.y > 0 && ratio < 0.5f)
	{
		CCLog("up");
		if (doUp())
			create_new_num();
	}
	else if (diff.y < 0 && ratio < 0.5f)
	{
		CCLog("down");
		if (doDown())
			create_new_num();
	}
}


bool GameLayer::doUp()
{
	bool ret = false;
	//从最上面一行开始看遍历。
	for (int x = 0; x < 4 ; x++)
	{
		for (int y = 3; y >= 0 ; y--)
		{
			GridCard* grid = gridArr[x][y];
			if (grid->show_num == 0)
			{
				continue;
			}
			for (int check_index = 3; check_index > y; check_index--)
			{
				GridCard* check_grid = gridArr[x][check_index];
				if (check_grid->show_num == 0)
				{
					//move到这里
					CCString* str = CCString::createWithFormat("%d,%d moveto  %d, %d ", x, y, x, check_index);
					CCLog(str->getCString());
					grid_move(grid, check_grid);
					ret = true;
					break;
				}
				else if (check_grid->show_num == grid->show_num)
				{
					//合并
					CCString* str = CCString::createWithFormat("%d,%d moveto  %d, %d ", x, y, x, check_index);
					CCLog(str->getCString());
					grid_merge(grid, check_grid);
					ret = true;
					break;
				}
				else if (check_grid->show_num != grid->show_num)
				{
					break;
				}
			}
		}
	}
	return ret;
}

bool GameLayer::doDown()
{
	bool ret = false;
	//从最下面一行开始看遍历。
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			GridCard* grid = gridArr[x][y];
			if (grid->show_num == 0)
			{
				continue;
			}
			for (int check_index = 0; check_index < y; check_index++)
			{
				GridCard* check_grid = gridArr[x][check_index];
				if (check_grid->show_num == 0)
				{
					//move到这里
					CCString* str = CCString::createWithFormat("%d,%d moveto  %d, %d ", x, y, x, check_index);
					CCLog(str->getCString());
					grid_move(grid, check_grid);
					ret = true;
					break;
				}

				else if (check_grid->show_num == grid->show_num)
				{
					//合并
					CCString* str = CCString::createWithFormat("%d,%d moveto  %d, %d ", x, y, x, check_index);
					CCLog(str->getCString());
					grid_merge(grid, check_grid);
					ret = true;
					break;
				}
				else if (check_grid->show_num != grid->show_num)
				{
					break;
				}
			}
		}
	}
	return ret;
}

bool GameLayer::doLeft()
{
	bool ret = false;
	//从最左面一行开始看遍历。
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			GridCard* grid = gridArr[x][y];
			if (grid->show_num == 0)
			{
				continue;
			}
			for (int check_index = 0; check_index < x ; check_index++)
			{
				GridCard* check_grid = gridArr[check_index][y];
				if (check_grid->show_num == 0)
				{
					//move到这里
					CCString* str = CCString::createWithFormat("%d,%d moveto  %d, %d ", x, y, x, check_index);
					CCLog(str->getCString());
					grid_move(grid, check_grid);
					ret = true;
					break;
				}
				else if (check_grid->show_num == grid->show_num)
				{
					//合并
					CCString* str = CCString::createWithFormat("%d,%d moveto  %d, %d ", x, y, x, check_index);
					CCLog(str->getCString());
					grid_merge(grid, check_grid);
					ret = true;
					break;
				}
				
			}
		}
	}
	return ret;
}

bool GameLayer::doRight()
{
	bool ret = false;
	//从最右面一行开始看遍历。
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >=0 ; x--)
		{
			GridCard* grid = gridArr[x][y];
			if (grid->show_num == 0)
			{
				continue;
			}
			for (int check_index = 3; check_index > x; check_index--)
			{
				GridCard* check_grid = gridArr[check_index][y];
				if (check_grid->show_num == 0)
				{
					//move到这里
					CCString* str = CCString::createWithFormat("%d,%d moveto  %d, %d ", x, y, x, check_index);
					CCLog(str->getCString());
					grid_move(grid, check_grid);
					break;
				}

				else if (check_grid->show_num == grid->show_num)
				{
					//合并
					CCString* str = CCString::createWithFormat("%d,%d moveto  %d, %d ", x, y, x, check_index);
					CCLog(str->getCString());
					grid_merge(grid, check_grid);
					ret = true;
					break;
				}
				else if (check_grid->show_num != grid->show_num)
				{
					break;
				}
			}
		}
	}
	return ret;
}

void GameLayer::check_opt(GridCard* g1, GridCard* g2)
{

}

//1-->2
void GameLayer::grid_move(GridCard* g1, GridCard* g2)
{
	CCPoint g1p = convertToWorldSpace(g1->getPosition());
	CCPoint g2p = convertToWorldSpace(g2->getPosition());
	CCPoint diff = g2p - g1p;

// 	CCMoveBy* action = CCMoveBy::create(0.2, diff);	
// 	g1->getChildByTag(g1->show_num)->runAction(action);

	//todo
	g2->set_num(g1->show_num);
	g1->remove_num();
}

void GameLayer::grid_merge(GridCard* g1, GridCard* g2)
{
	int new_number = g2->show_num * 2;
	g1->remove_num();
	g2->remove_num();
	g2->set_num(new_number);

}


