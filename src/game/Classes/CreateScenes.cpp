#include "stdafx.h"

#include "CreateScenes.h"
#include "GamePlayLayer.h"

CCScene* GetGameScene()
{
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	GamePlayLayer *layer = GamePlayLayer::create();
#ifdef CHARACTER_TUNING
	//중요한작업
#else
	//블라블라블라
#endif
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}