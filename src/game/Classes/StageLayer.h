#pragma once 

#include "stdafx.h"
#include "Const.h"
#include "CharacterData.h"
#include "StageData.h"
#include "Character.h"
#include "Monster.h"
#include "Bullet.h"
#include "Working.h"

class StageLayer : public CCLayer
{
public:
	StageLayer(CharacterNumber charNum);
	virtual ~StageLayer() override;
	
	virtual bool init(int stageNumber);

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	void gameLogic(float delayTime, CCPoint bgPos);
	void keyboardInput(float delayTime);
	void missileInput(float delayTime);
	void missileMovedFinished(CCNode *node);
	void enemyCollisionCheck(float delayTime);
	void moveAllyBullet(float delayTime);
	void moveEnemyBullet(float delayTime);

	void addTarget(StageSceneType sc_type);
	void spriteMoveFinished(CCNode *node);

private:
	CCSize winSize;					// ������ ������

	StageSceneType stageStatus;
	CharacterNumber charNum;

	void setPlayerSprite();				//	�÷��̾� ��������Ʈ �߰�

	StageData* Data;

	vector< StageMonsterData* > _stageMonsters;	//	�������� ���� ���� ���
	list< Monster* > _monsters;					//	�� ��������Ʈ ��� ����
	list< Bullet* > _characterBullets;			//	ĳ���� �̻��� ��������Ʈ ���
	list< Bullet* > _enemyBullets;				//	���� �̻��� ��������Ʈ ���
	list< CCSprite* > _missiles;				//	ĳ���� �̻��� ��������Ʈ ���
//	list< Bullet* > _allyBullets;				//	�Ʊ� �̻��� ��������Ʈ ���


	float dtMissile;			//	�̻��� ����
	float dtAddTarget;			//	�� ���� ����

	float missileDelay;			//	�̻��� ������
};
