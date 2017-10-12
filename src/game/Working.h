#pragma once

#include "stdafx.h"

#define XML_PARSING				//	XML 파싱중
#define CHARACTER_SETTING		//	캐릭터 세팅중
//#define SPRITE_ERROR			//	스프라이트 에러


#ifdef SAMPLE_SAVE				//	샘플 저장소

// Close Menu
/*
// Create a "close" menu item with close icon, it's an auto release object.
CCMenuItemImage *pCloseItem = CCMenuItemImage::create( 
	GETPATH(PATH_CLOSENORMAL_PNG),
	GETPATH(PATH_CLOSESELECTED_PNG),
	this, menu_selector(StageLayer::menuCloseCallback) );
CC_BREAK_IF(! pCloseItem);

// Place the menu item bottom-right conner.
pCloseItem->setPosition(ccp(winSize.width - 20, 20));


// Create a menu with the "close" menu item, it's an auto release object.
CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
pMenu->setPosition(CCPointZero);
CC_BREAK_IF(! pMenu);

// Add the menu to StageScene layer as a child layer.
this->addChild(pMenu, 1);
*/

/*	StageLayer.cpp - 미사일 가속도
	// Verify whether "UP" keyboard key is pressed or not  
	if (keyStateUp & SHIFTED)  
	{  
		ccp_P1Acc.y += m_fP1Step * m_fwinRatio_Y;
		if (ccp_P1Acc.y > m_fP1AccMax)
		{
			ccp_P1Acc.y = m_fP1AccMax;
		}
	}
	// Verify whether "DOWN" keyboard key is pressed or not  
	if (keyStateDown & SHIFTED)
	{  
		ccp_P1Acc.y -= m_fP1Step * m_fwinRatio_Y;	
		if (ccp_P1Acc.y < -m_fP1AccMax)
		{
			ccp_P1Acc.y = -m_fP1AccMax;
		}
	}
	if ( (!keyStateUp && ccp_P1Acc.y > 0) || (!keyStateDown && ccp_P1Acc.y < 0) || (keyStateUp && keyStateDown) )
	{
		ccp_P1Acc.y = 0.0f;
	}

	// Verify whether "LEFT" keyboard key is pressed or not  
	if(keyStateLeft & SHIFTED)  
	{  
		ccp_P1Acc.x -= m_fP1Step * m_fwinRatio_X;	
		if (ccp_P1Acc.x < -m_fP1AccMax)
		{
			ccp_P1Acc.x = -m_fP1AccMax;
		}
	}
	// Verify whether "DOWN" keyboard key is pressed or not  
	if (keyStateRight & SHIFTED)
	{  
		ccp_P1Acc.x += m_fP1Step * m_fwinRatio_X;
		if (ccp_P1Acc.x > m_fP1AccMax)
		{
			ccp_P1Acc.x = m_fP1AccMax;
		}
	}
	if ( (!keyStateLeft && ccp_P1Acc.x < 0) || (!keyStateRight && ccp_P1Acc.x > 0) || (keyStateLeft && keyStateRight) )
	{
		ccp_P1Acc.x = 0.0f;
	}
	ccp_P1Pos.x += ccp_P1Acc.x;
	ccp_P1Pos.y += ccp_P1Acc.y;
	pSprite_P1->setPosition(ccp_P1Pos);
*/

/*
//	키 체크 (미사일 사용시, 일반 이동시를 서로 다르게 체크)
if ( GetAsyncKeyState(VK_UP) & SHIFTED && GetAsyncKeyState(0x5A) & SHIFTED )
{ p1Acc.y += P1_MOVEVAL2 * delayTime; }
else if ( GetAsyncKeyState(VK_UP) & SHIFTED )
{ p1Acc.y += P1_MOVEVAL * delayTime; }
if ( GetAsyncKeyState(VK_DOWN) & SHIFTED && GetAsyncKeyState(0x5A) & SHIFTED )
{ p1Acc.y -= P1_MOVEVAL2 * delayTime; }
else if ( GetAsyncKeyState(VK_DOWN) & SHIFTED )
{ p1Acc.y -= P1_MOVEVAL * delayTime; }
if ( GetAsyncKeyState(VK_LEFT) & SHIFTED && GetAsyncKeyState(0x5A) & SHIFTED )
{ p1Acc.x -= P1_MOVEVAL2 * delayTime; }
else if ( GetAsyncKeyState(VK_LEFT) & SHIFTED )
{ p1Acc.x -= P1_MOVEVAL * delayTime; }
if ( GetAsyncKeyState(VK_RIGHT) & SHIFTED && GetAsyncKeyState(0x5A) & SHIFTED )
{ p1Acc.x += P1_MOVEVAL2 * delayTime; }
else if ( GetAsyncKeyState(VK_RIGHT) & SHIFTED )
{ p1Acc.x += P1_MOVEVAL * delayTime; }
*/
	/*
	//	표창 하나당 모든 적과의 영역 비교를 하여 충돌처리를 한다
	for( it1=_missiles.begin(); it1 != _missiles.end(); ++it1 )
	{
		CCSprite *projectile = *it1;
		CCRect projectileRect = CCRectMake(
			projectile->getPosition().x - (projectile->getContentSize().width/2),
			projectile->getPosition().y - (projectile->getContentSize().height/2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);

		//	지울 몬스터를 담을 가변 배열
		list< list<CCSprite*>::iterator > _monstersToDel;
		for( it2=_monsters.begin(); it2!=_monsters.end(); ++it2 )
		{
			CCSprite *target = *it2;
			CCRect targetRect = CCRectMake(
				target->getPosition().x - (target->getContentSize().width/2),
				target->getPosition().y - (target->getContentSize().height/2), 
				target->getContentSize().width,
				target->getContentSize().height);
			//	충돌체크
			if(CCRect::CCRectIntersectsRect(projectileRect, targetRect))
			{
				_monstersToDel.push_back(it2);
			}
		}

		//	맞은 적을 지운다
		list< list<CCSprite*>::iterator >::iterator it_it;
		for( it_it=_monstersToDel.begin(); it_it!=_monstersToDel.end(); it_it)
		{
			CCSprite *target = *(*it_it);
			it_it = _monsters.erase(*it_it);
			this->removeChild(target, true);
		}

		//: 지울 적의 개수가 1 이상이면 표창과 충돌한 것이므로 
		//: 지울 표창 가변 배열에 현재 표창을 추가한다
		if(_monstersToDel.size() > 0)
		{
			projectileToDelete->addObject(projectile);
		}
		targetsToDelete->release();
	}

	//: 지울 표창을 지운다
	for(it=projectileToDelete->begin(); it!=projectileToDelete->end(); it++)
	{
		CCSprite *projectile = *it;
		_projectiles->removeObject(projectile);
		this->removeChild(projectile, true);
	}
	projectileToDelete->release();
	*/

	//	Missile Input
	/*
	//	미사일 출발 위치 설정.
	CCSprite *sprMissile = NonGCSprite::create(GETPATH(PATH_MISSILE_PNG), 
		CCRectMake(0, 0, 20, 20));
	startloc.x += player1Character->getCharacterData()->Size.width/2;
	sprMissile->setPosition(ccp(startloc.x, startloc.y));
	//	미사일 추가
	_missiles.push_back(sprMissile);
	this->addChild(sprMissile);
	
	//	미사일 목적지 위치 계산
	int arriveX;
	if ( startloc.x + length == m_winSize.width )
		arriveX = m_winSize.width + (sprMissile->getContentSize().width/2);
	int realY = (realX * ratio) + projectile->getPosition().y;
	CCPoint realDest = ccp(realX, realY);
	
	//	미사일 도착 거리 구하기
	int offRealX = realX - projectile->getPosition().x;
	int offRealY = realY - projectile->getPosition().y;
	float length = sqrtf((offRealX*offRealX)+(offRealY*offRealY));

	int range = player1Character->getCharacterData()->AttackRange;		//  사거리
	int velocity = player1Character->getCharacterData()->MissileSpeed;	//  속도
	float moveDuration = (float)range/velocity;			//  s = v*t 이므로 t = s/v;

	//	미사일 발사 지정
	CCFiniteTimeAction *missileAction = CCSequence::actions(
		CCMoveTo::actionWithDuration(moveDuration, ccp(startloc.x + range, startloc.y)),
		CCCallFuncN::actionWithTarget(
		this, callfuncN_selector(StageLayer::missileMovedFinished)), NULL);
	sprMissile->runAction(missileAction);
	*/
	
void StageLayer::addTarget(StageSceneType sc_type)
{
	Monster *mop = new Monster(this);
	mop->createSprite( "Seal", ccp(0, 0) );
	//	적 스프라이트의 Y 좌표를 랜덤으로 하여 위치 잡기
	int minY = mop->getMonsterData()->Size.height/2;
	int maxY = winSize.height - mop->getMonsterData()->Size.height/2;
	int rangeY = maxY - minY;
	int actualY = ( rand() % rangeY ) + minY;
	mop->setPosition(winSize.width + mop->getMonsterData()->Size.width/2, actualY);
	_monsters.push_back(mop);

	/*
	//	랜덤 속도 결정
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = ( rand() % rangeDuration ) + minDuration;
	*/
	float moveRange = abs(mop->getCurrentSprite()->getPosition().x - (winSize.width - 100 - mop->getMonsterData()->Size.width/2)) / mop->getMonsterData()->MoveSpeed;
	//	move액션 생성
	CCFiniteTimeAction *actionMove = CCMoveTo::actionWithDuration(moveRange,
		ccp(winSize.width - 100 - mop->getMonsterData()->Size.width/2, actualY));

	//	스프라이트 이동 완료 후에 호출될 콜백 액션
	CCFiniteTimeAction *actionMoveDone = CCCallFuncN::actionWithTarget(
											this, callfuncN_selector(StageLayer::spriteMoveFinished));
	mop->getCurrentSprite()->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

	//	보스 스프라이트 생성
	CCSprite *target = NonGCSprite::create(GETPATH(PATH_BOSS_PNG), CCRectMake(0, 0, 270, 400));
	target->setPosition( ccp(winSize.width + (target->getContentSize().width/2), winSize.height/2) );
	this->addChild(target);

	//	move액션 생성
	CCFiniteTimeAction *actionMove = CCMoveTo::actionWithDuration(
										10.0f, ccp(0-target->getContentSize().width/2, winSize.height/2));

	//	스프라이트 이동 완료 후 호출 액션
	CCFiniteTimeAction *actionMoveDone = CCCallFuncN::actionWithTarget(
		this, callfuncN_selector(StageLayer::spriteMoveFinished));
	target->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));
}


#endif