#pragma once

#include "stdafx.h"

#define XML_PARSING				//	XML �Ľ���
#define CHARACTER_SETTING		//	ĳ���� ������
//#define SPRITE_ERROR			//	��������Ʈ ����


#ifdef SAMPLE_SAVE				//	���� �����

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

/*	StageLayer.cpp - �̻��� ���ӵ�
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
//	Ű üũ (�̻��� ����, �Ϲ� �̵��ø� ���� �ٸ��� üũ)
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
	//	ǥâ �ϳ��� ��� ������ ���� �񱳸� �Ͽ� �浹ó���� �Ѵ�
	for( it1=_missiles.begin(); it1 != _missiles.end(); ++it1 )
	{
		CCSprite *projectile = *it1;
		CCRect projectileRect = CCRectMake(
			projectile->getPosition().x - (projectile->getContentSize().width/2),
			projectile->getPosition().y - (projectile->getContentSize().height/2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);

		//	���� ���͸� ���� ���� �迭
		list< list<CCSprite*>::iterator > _monstersToDel;
		for( it2=_monsters.begin(); it2!=_monsters.end(); ++it2 )
		{
			CCSprite *target = *it2;
			CCRect targetRect = CCRectMake(
				target->getPosition().x - (target->getContentSize().width/2),
				target->getPosition().y - (target->getContentSize().height/2), 
				target->getContentSize().width,
				target->getContentSize().height);
			//	�浹üũ
			if(CCRect::CCRectIntersectsRect(projectileRect, targetRect))
			{
				_monstersToDel.push_back(it2);
			}
		}

		//	���� ���� �����
		list< list<CCSprite*>::iterator >::iterator it_it;
		for( it_it=_monstersToDel.begin(); it_it!=_monstersToDel.end(); it_it)
		{
			CCSprite *target = *(*it_it);
			it_it = _monsters.erase(*it_it);
			this->removeChild(target, true);
		}

		//: ���� ���� ������ 1 �̻��̸� ǥâ�� �浹�� ���̹Ƿ� 
		//: ���� ǥâ ���� �迭�� ���� ǥâ�� �߰��Ѵ�
		if(_monstersToDel.size() > 0)
		{
			projectileToDelete->addObject(projectile);
		}
		targetsToDelete->release();
	}

	//: ���� ǥâ�� �����
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
	//	�̻��� ��� ��ġ ����.
	CCSprite *sprMissile = NonGCSprite::create(GETPATH(PATH_MISSILE_PNG), 
		CCRectMake(0, 0, 20, 20));
	startloc.x += player1Character->getCharacterData()->Size.width/2;
	sprMissile->setPosition(ccp(startloc.x, startloc.y));
	//	�̻��� �߰�
	_missiles.push_back(sprMissile);
	this->addChild(sprMissile);
	
	//	�̻��� ������ ��ġ ���
	int arriveX;
	if ( startloc.x + length == m_winSize.width )
		arriveX = m_winSize.width + (sprMissile->getContentSize().width/2);
	int realY = (realX * ratio) + projectile->getPosition().y;
	CCPoint realDest = ccp(realX, realY);
	
	//	�̻��� ���� �Ÿ� ���ϱ�
	int offRealX = realX - projectile->getPosition().x;
	int offRealY = realY - projectile->getPosition().y;
	float length = sqrtf((offRealX*offRealX)+(offRealY*offRealY));

	int range = player1Character->getCharacterData()->AttackRange;		//  ��Ÿ�
	int velocity = player1Character->getCharacterData()->MissileSpeed;	//  �ӵ�
	float moveDuration = (float)range/velocity;			//  s = v*t �̹Ƿ� t = s/v;

	//	�̻��� �߻� ����
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
	//	�� ��������Ʈ�� Y ��ǥ�� �������� �Ͽ� ��ġ ���
	int minY = mop->getMonsterData()->Size.height/2;
	int maxY = winSize.height - mop->getMonsterData()->Size.height/2;
	int rangeY = maxY - minY;
	int actualY = ( rand() % rangeY ) + minY;
	mop->setPosition(winSize.width + mop->getMonsterData()->Size.width/2, actualY);
	_monsters.push_back(mop);

	/*
	//	���� �ӵ� ����
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = ( rand() % rangeDuration ) + minDuration;
	*/
	float moveRange = abs(mop->getCurrentSprite()->getPosition().x - (winSize.width - 100 - mop->getMonsterData()->Size.width/2)) / mop->getMonsterData()->MoveSpeed;
	//	move�׼� ����
	CCFiniteTimeAction *actionMove = CCMoveTo::actionWithDuration(moveRange,
		ccp(winSize.width - 100 - mop->getMonsterData()->Size.width/2, actualY));

	//	��������Ʈ �̵� �Ϸ� �Ŀ� ȣ��� �ݹ� �׼�
	CCFiniteTimeAction *actionMoveDone = CCCallFuncN::actionWithTarget(
											this, callfuncN_selector(StageLayer::spriteMoveFinished));
	mop->getCurrentSprite()->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

	//	���� ��������Ʈ ����
	CCSprite *target = NonGCSprite::create(GETPATH(PATH_BOSS_PNG), CCRectMake(0, 0, 270, 400));
	target->setPosition( ccp(winSize.width + (target->getContentSize().width/2), winSize.height/2) );
	this->addChild(target);

	//	move�׼� ����
	CCFiniteTimeAction *actionMove = CCMoveTo::actionWithDuration(
										10.0f, ccp(0-target->getContentSize().width/2, winSize.height/2));

	//	��������Ʈ �̵� �Ϸ� �� ȣ�� �׼�
	CCFiniteTimeAction *actionMoveDone = CCCallFuncN::actionWithTarget(
		this, callfuncN_selector(StageLayer::spriteMoveFinished));
	target->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));
}


#endif