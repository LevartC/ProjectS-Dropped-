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
	CCLayer *pLayer;					//	�θ� ���̾�
	vector<CCSprite*> _standardSprites;	//	�⺻ ������ ��������Ʈ
	vector<int> _standardFrames;			//	�⺻ ��������Ʈ ������

	int spriteIndex;
	CCSprite *currentSprite;			//	���� ��������Ʈ
	const BulletData* Data;				//	ĳ���� ������

	CCPoint position;					//	�� ��ġ
	CCSize size;						//	ũ��
	CCPoint startLocation;				//	���� ��ġ
	CCPoint targetLocation;				//	��ǥ�� ��ġ
	CCPoint moveDirection;				//	�����̴� ����
	float moveSpeed;					//	�̵��ӵ�
	float damage;						//	�����

	int aniFrameCount;
	

	int piercingLevel;					//	�Ǿ�� ����
	vector<CCSprite*> ignoreList;		//	źȯ ��� ����Ʈ
};
