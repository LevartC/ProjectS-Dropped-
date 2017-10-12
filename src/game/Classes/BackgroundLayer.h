#pragma once 

#include "stdafx.h"

class BackGroundLayer : public CCLayer
{
public:
	BackGroundLayer();
	virtual ~BackGroundLayer() override;

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(int stageNumber);
	CCPoint updateBgPosition(float delayTime);
	float getBgLength();

private:
	CCPoint bgPos;					//	배경 위치
	CCSprite *currentSprite;		//	배경 스프라이트
	CCSize winSize;					//	윈도우 사이즈
	StageData *currentStageData;	//	해당 스테이지 데이터
};
