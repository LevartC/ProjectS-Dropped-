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
	CCLayer *pLayer;			//	�θ� ���̾�
	list< Bullet* > *_bullets;	//	ĳ���� �̻��� ��������Ʈ ����Ʈ

	//	���ĵ�, ����, ���Ÿ�, �ٰŸ� ��� ��������Ʈ
	map< CharacterStatusType, vector<CCSprite*> > _standardSprites;
	map< int, vector<CCSprite*> > _rangeSprites;
	map< int, vector<CCSprite*> > _meleeSprites;
	//	���ĵ�, ����, ���Ÿ�, �ٰŸ� ��� ������
	map< CharacterStatusType, vector<int> > _standardFrames;
	map< int, vector<int> > _rangeFrames;
	map< int, vector<int> > _meleeFrames;


	int spriteIndex;
	CharacterStatusType currentCharacterStatus;
	CharacterStatusType spriteStatus;
	int missileLevel;
	RangeAttackStruct* currentRangeStruct;		//	���� ���Ÿ� ���� ����
	const CharacterData* Data;					//	ĳ���� ������
	CCSprite *currentSprite;					//	���� ������� ��������Ʈ
	CCPoint position;							//	ĳ���� ������
	CCSize size;								//	ĳ���� ������

	int aniFrameCount;

	float dtMissileDelay;
	float dtSpriteDelay;
	float dtAnimation;
	float dtMotionDelay;

	int life;
	int maxLife;
	int mana;
};

