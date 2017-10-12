#pragma once

#include "stdafx.h"
#include "StageLayer.h"
#include "BackgroundLayer.h"

class StageScene : public CCScene
{
public:
	StageScene();
	virtual ~StageScene() override;

	static StageScene* createScene();
	bool init();
	void gameLogic(float delayTime);

private:
	StageLayer *pLayer_Stage;
	BackGroundLayer *pLayer_BG;

	CharacterNumber selectedCharacter;
	int currentStageNumber;

	Character *player1;

};
