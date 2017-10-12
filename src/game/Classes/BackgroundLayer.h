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
	CCPoint bgPos;					//	��� ��ġ
	CCSprite *currentSprite;		//	��� ��������Ʈ
	CCSize winSize;					//	������ ������
	StageData *currentStageData;	//	�ش� �������� ������
};
