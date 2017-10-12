#pragma once

#include "stdafx.h"


class SelectLayer : public CCLayer
{
public:
	SelectLayer();
	virtual ~SelectLayer() override;

	virtual bool init();

	bool setCharacterDivision();
	void gameLogic(float delayTime);
	void keyboardInput(float delayTime);

private:
	CCSize winSize;

	int currentNumber;
};