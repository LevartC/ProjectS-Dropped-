#pragma once

#include "stdafx.h"
#include "IGameObject.h"
#include "MonsterData.h"
#include "Working.h"

class Monster : public IScriptableObject
{
public:
	Monster(CCLayer *pLayer);
	virtual ~Monster(void);

	void doAction(float delayTime) override;
	CCPoint getPosition() override;
	CCSize getSize() override;
	void setPosition(float pos_x, float pos_y) override;
	int objectNumber() override;

	bool createSprite(int number, CCPoint position);
	bool createSprite(string monsterName, CCPoint position);
	CCSprite* doNextSprite();
	CCLayer* getParentLayer();
	CCSprite* getCurrentSprite();
	const MonsterData* getMonsterData();
	void setBulletList(list<Bullet*> *_bullets);
	void setCurrentMonsterStatus(MonsterStatusType status);
	MonsterStatusType getCurrentMonsterStatus();
	
	float subtractLife(float lifeValue);
	float fillLife(float lifeValue);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

private:
	CCLayer *pLayer;			//	부모 레이어
	list< Bullet* > *_bullets;	//	캐릭터 미사일 스프라이트 리스트

	map< MonsterStatusType, vector<CCSprite*> > _standardSprites;	//	스탠딩, 무빙 스프라이트
	map< int, vector<CCSprite*> > _rangeSprites;	//	원거리모션 스프라이트
	map< int, vector<CCSprite*> > _meleeSprites;	//	근거리모션 스프라이트

	int spriteIndex;
	MonsterStatusType currentMonsterStatus;
	MonsterStatusType spriteStatus;
	int rangeAttackType;

	CCSprite *currentSprite;					//	현재 출력중인 스프라이트
	const MonsterData* Data;					//	캐릭터 데이터

	CCPoint position;							//	캐릭터 포지션
	CCSize size;								//	캐릭터 사이즈

	float elapsedTime;							//	시간
	int patternNumber;							//	패턴번호
	

	bool useLua;

	float life;
	float mana;
};
