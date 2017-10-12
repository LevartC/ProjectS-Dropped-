#include "stdafx.h"

#include "CreateScenes.h"
#include "GamePlayLayer.h"

CCScene* GetGameScene()
{
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	GamePlayLayer *layer = GamePlayLayer::create();
#ifdef CHARACTER_TUNING
	//�߿����۾�
#else
	//�������
#endif
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}