#pragma once

#include "stdafx.h"
#include "IGameObject.h"
#include "CharacterData.h"
#include "Bullet.h"
#include "GameDataStruct.h"
#include "Working.h"

class Character : public IGameObject
{
public:
	Character(CCLayer *pLayer);
	virtual ~Character();

	void doAction(float delayTime) override;
	CCPoint getPosition() override;
	CCSize getSize() override;
	void setPosition(float pos_x, float pos_y) override;
	
	bool createSprite(CharacterNumber charNum);
	CCSprite* doNextSprite(float delayTime);

	CCLayer* getParentLayer();
	CCSprite* getCurrentSprite();
	const CharacterData* getCharacterData();
	RangeAttackStruct* getCurrentRangeStruct();
	int getMissileLevel();

	void setBulletList(list<Bullet*> *_bullets);
	void setCurrentCharacterStatus(CharacterStatusType status);
	CharacterStatusType getCurrentCharacterStatus();

private:
	CCLayer *pLayer;			//	부모 레이어
	list< Bullet* > *_bullets;	//	캐릭터 미사일 스프라이트 리스트

	//	스탠딩, 무빙, 원거리, 근거리 모션 스프라이트
	map< CharacterStatusType, vector<CCSprite*> > _standardSprites;
	map< int, vector<CCSprite*> > _rangeSprites;
	map< int, vector<CCSprite*> > _meleeSprites;
	//	스탠딩, 무빙, 원거리, 근거리 모션 프레임
	map< CharacterStatusType, vector<int> > _standardFrames;
	map< int, vector<int> > _rangeFrames;
	map< int, vector<int> > _meleeFrames;


	int spriteIndex;
	CharacterStatusType currentCharacterStatus;
	CharacterStatusType spriteStatus;
	int missileLevel;
	RangeAttackStruct* currentRangeStruct;		//	현재 원거리 공격 정보
	const CharacterData* Data;					//	캐릭터 데이터
	CCSprite *currentSprite;					//	현재 출력중인 스프라이트
	CCPoint position;							//	캐릭터 포지션
	CCSize size;								//	캐릭터 사이즈

	int aniFrameCount;

	float dtMissileDelay;
	float dtSpriteDelay;
	float dtAnimation;
	float dtMotionDelay;

	int life;
	int maxLife;
	int mana;
};

