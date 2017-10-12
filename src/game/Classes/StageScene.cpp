
#include "stdafx.h"
#include "Const.h"
#include "Global.h"
#include "CharacterData.h"
#include "Working.h"
#include "Log.h"
#include "StageScene.h"


StageScene::StageScene()
{
	player1 = nullptr;
	selectedCharacter = CN_PENGUIN;
	currentStageNumber = 1;
}

StageScene::~StageScene()
{
	{ this->removeChild(pLayer_Stage, true); }
	{ this->removeChild(pLayer_BG, true); }
	CC_SAFE_RELEASE_NULL(pLayer_BG);
	DEBUG_LOG(L"BackgroundLayer Delete Complete.")
	CC_SAFE_RELEASE_NULL(pLayer_Stage);
	DEBUG_LOG(L"StageLayer Delete Complete.")

	//this->unschedule(schedule_selector(StageScene::gameLogic));
}

void StageScene::gameLogic(float delayTime)
{
	CCPoint bgPos = pLayer_BG->updateBgPosition(delayTime);
	pLayer_Stage->gameLogic(delayTime, bgPos);
}

bool StageScene::init()
{
	//	Super Init
	if ( !CCScene::init() )
	{
		return false;
	}

	//	스테이지 레이어 생성
	pLayer_Stage = new StageLayer(selectedCharacter);
	if ( pLayer_Stage && pLayer_Stage->init(1) )
	{
		//pLayer_Stage->autorelease();
		DEBUG_LOG(L"StageLayer init Complete.")
	}
	else
	{
		FATAL_LOG(L"Failed to init StageLayer.");
		SAFE_DELETE(pLayer_Stage);
		return false;
	}

	//	배경 레이어 생성
	pLayer_BG = new BackGroundLayer();
	if ( pLayer_BG && pLayer_BG->init(currentStageNumber) )
	{
		//pLayer_BG->autorelease();
		DEBUG_LOG(L"BGLayer init complete.")
	}
	else
	{
		FATAL_LOG(L"Failed to init Background.");
		SAFE_DELETE(pLayer_BG);
		return false;
	}

	//	레이어 추가
	this->addChild(pLayer_Stage, ZORDER_LAYER);
	this->addChild(pLayer_BG, ZORDER_BG);

	//	스케쥴 추가
	this->schedule(schedule_selector(StageScene::gameLogic));
	
	return true;
}

StageScene* StageScene::createScene()
{
	StageScene *pScene = new StageScene();

	if ( pScene && pScene->init() )
	{
		pScene->autorelease();
		return pScene;
	}
	else
	{
		return nullptr;
	}
}