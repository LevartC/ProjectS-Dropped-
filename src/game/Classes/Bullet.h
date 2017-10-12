#pragma once

#include "stdafx.h"
#include "IGameObject.h"
#include "BulletData.h"

class Bullet : public IScriptableObject
{
public:
	Bullet(CCLayer *pLayer);
	virtual ~Bullet(void);

	void doAction(float delayTime) override;
	CCPoint getPosition() override;
	CCSize getSize() override;
	void setPosition(float pos_x, float pos_y) override;
	int objectNumber() override;	

	bool createSprite(int number, CCPoint position, CCPoint targetPosition,
		float moveSpeed, float damage);
	CCSprite* doNextSprite();
	CCLayer* getParentLayer();
	CCSprite* getCurrentSprite();
	const BulletData* getBulletData();
	float getDamage();
	float getMoveSpeed();

private:
	CCLayer *pLayer;					//	부모 레이어
	vector<CCSprite*> _standardSprites;	//	기본 움직임 스프라이트
	vector<int> _standardFrames;			//	기본 스프라이트 프레임

	int spriteIndex;
	CCSprite *currentSprite;			//	현재 스프라이트
	const BulletData* Data;				//	캐릭터 데이터

	CCPoint position;					//	현 위치
	CCSize size;						//	크기
	CCPoint startLocation;				//	시작 위치
	CCPoint targetLocation;				//	목표물 위치
	CCPoint moveDirection;				//	움직이는 방향
	float moveSpeed;					//	이동속도
	float damage;						//	대미지

	int aniFrameCount;
	

	int piercingLevel;					//	피어싱 레벨
	vector<CCSprite*> ignoreList;		//	탄환 통과 리스트
};
