#include "stdafx.h"
#include "Const.h"
#include "UtilFunctions.h"
#include "Log.h"
#include "SelectLayer.h"

SelectLayer::SelectLayer()
{

}

SelectLayer::~SelectLayer()
{

}

bool SelectLayer::init()
{
	bool ret = false;
	do
	{
		// super init first
		CC_BREAK_IF(! CCLayer::init());

		//	Get window size
		winSize = CCDirector::sharedDirector()->getWinSize();

		this->setTouchEnabled(true);

		setCharacterDivision();

		//	이동 스크롤 화면 스케줄 생성
		ret = true;
	} while (0);

	return ret;
}
void SelectLayer::gameLogic(float delayTime)
{
	keyboardInput(delayTime);
}

void SelectLayer::keyboardInput(float delayTime)
{
	static bool flag_left = false;
	if ( GetAsyncKeyState(VK_LEFT) & SHIFTED )
	{
		if (!flag_left)
		{
			flag_left = true;
			--currentNumber;
		}
	}
	else
	{
		flag_left = false;
	}
	static bool flag_right = false;
	if ( GetAsyncKeyState(VK_RIGHT) & SHIFTED )
	{
		if  ( !flag_right )
		{
			flag_right = true;
			++currentNumber;
		}
	}
	else
	{
		flag_right = false;
	}
}

bool SelectLayer::setCharacterDivision()
{
	/*
	CCSize size = CCSizeMake(200, 150);
	CCSprite *pSprite = NonGCSprite::create(GETPATH(PATH_SELECT_PENGUIN_PNG), 
					CCRectMake(size.width/2, size.height/2, size.width, size.height));

	
	this->addChild(pSprite);

	*/
	return true;
}