#pragma once

#include "stdafx.h"
#include "SelectLayer.h"

class SelectScene : public CCScene
{
public:
	SelectScene();
	virtual ~SelectScene() override;

	static SelectScene* createScene();
	bool init();
	void gameLogic(float delayTime);

private:
	SelectLayer *pLayer_Select;

};
