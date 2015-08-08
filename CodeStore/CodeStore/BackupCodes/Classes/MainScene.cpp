#include "MainScene.h"
#include "ScoreLayer.h"
#include "GameLayer.h"

void MainScene::initLayers()
{
	struct timeval now;
	gettimeofday(&now, NULL);

	srand(now.tv_sec);
	//±³¾°
	CCLayerColor* bgLayer = CCLayerColor::create(ccc4(180, 170, 160, 255));
	addChild(bgLayer);

	//·ÖÊýLayer
	ScoreLayer* sLayer = ScoreLayer::create();
	addChild(sLayer,1);

	GameLayer* gLayer = GameLayer::create();
	addChild(gLayer,2);
}

void MainScene::onEnter()
{
	CCScene::onEnter();
}

void MainScene::onExit()
{
	CCScene::onExit();
}
