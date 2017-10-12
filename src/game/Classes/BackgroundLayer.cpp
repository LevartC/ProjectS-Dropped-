
#include "stdafx.h"
#include "Const.h"
#include "Global.h"
#include "UtilFunctions.h"
#include "BackgroundLayer.h"


BackGroundLayer::BackGroundLayer()
{
	bgPos = CCPoint(0.0f, 0.0f);
}
BackGroundLayer::~BackGroundLayer()
{
	CC_SAFE_DELETE(this->currentSprite);
}
bool BackGroundLayer::init(int stageNumber)
{
	try
	{
		currentStageData = &g_StageData.find(stageNumber)->second;
		if( !CCLayer::init() ) throw false;

		//	Get window size
		winSize = CCDirector::sharedDirector()->getWinSize();

		//	��ũ���� ���ȭ�� ù ��ġ ����
		bgPos.x = currentStageData->Length/2.0f;
		bgPos.y = winSize.height/2;
		// ��� ȭ�� �����
		currentSprite = NonGCSprite::create(GETPATH(currentStageData->BackgroundImagePath));
		if( !currentSprite ) throw false;
		currentSprite->setPosition(ccp(bgPos.x, bgPos.y));
		// ���̾ ���ȭ�� �ֱ�
		this->addChild(currentSprite);

	}
	catch (bool ret)
	{
		return ret;
	}

	return true;
}

CCPoint BackGroundLayer::updateBgPosition(float delayTime)
{
	static bool endFlag = false;
	float endX = -currentStageData->Length/2.0f + winSize.width;
	//	��� �����̱�
	if (bgPos.x > endX )
	{
		bgPos.x -= currentStageData->MoveSpeed * delayTime;
	}
	else {
		endFlag = true;
		bgPos.x = endX;
	}
	currentSprite->setPosition(bgPos);
	//	���� ��ġ ����
	return ccp(-bgPos.x + currentStageData->Length/2.0f, bgPos.y);
}

float BackGroundLayer::getBgLength()
{
	return currentStageData->Length;
}

