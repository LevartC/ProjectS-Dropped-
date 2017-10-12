#include "stdafx.h"
#include "Const.h"
#include "Global.h"
#include "Working.h"
#include "Log.h"
#include "SelectScene.h"


SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::gameLogic(float delayTime)
{
	this->removeChild(pLayer_Select, true);
	this->unschedule(schedule_selector(SelectScene::gameLogic));
}

bool SelectScene::init()
{
	//	Super Init
	if ( !CCScene::init() )
	{
		return false;
	}

	//	ĳ���� ���� ���̾�
	pLayer_Select = new SelectLayer();
	if ( pLayer_Select && pLayer_Select->init() )
	{
		pLayer_Select->autorelease();
		return pLayer_Select;
	}
	else
	{
		SAFE_DELETE(pLayer_Select);
		return false;
	}

	//	���̾� �߰�
	this->addChild(pLayer_Select);

	//	������ �߰�
	this->schedule(schedule_selector(SelectScene::gameLogic));


	return true;
}

SelectScene* SelectScene::createScene()
{
	SelectScene *pScene = new SelectScene();

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