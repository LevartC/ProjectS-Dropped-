#pragma once

#include "stdafx.h"

__interface IGameObject
{
	virtual void doAction(float delayTime) = 0;
	virtual CCPoint getPosition() = 0;
	virtual CCSize getSize() = 0;
	virtual void setPosition(float pos_x, float pos_y) = 0;
};

__interface IScriptableObject : public IGameObject
{
	virtual int objectNumber() = 0;	
};