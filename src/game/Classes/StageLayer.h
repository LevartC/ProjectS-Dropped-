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
	CCSize winSize;					// 윈도우 사이즈

	StageSceneType stageStatus;
	CharacterNumber charNum;

	void setPlayerSprite();				//	플레이어 스프라이트 추가

	StageData* Data;

	vector< StageMonsterData* > _stageMonsters;	//	스테이지 출현 몬스터 목록
	list< Monster* > _monsters;					//	적 스프라이트 목록 관리
	list< Bullet* > _characterBullets;			//	캐릭터 미사일 스프라이트 목록
	list< Bullet* > _enemyBullets;				//	적군 미사일 스프라이트 목록
	list< CCSprite* > _missiles;				//	캐릭터 미사일 스프라이트 목록
//	list< Bullet* > _allyBullets;				//	아군 미사일 스프라이트 목록


	float dtMissile;			//	미사일 간격
	float dtAddTarget;			//	적 등장 간격

	float missileDelay;			//	미사일 딜레이
};
