#include "stdafx.h"
#include "Global.h"
#include "Const.h"

#include "UtilFunctions.h"
#include "Log.h"

#include "Bullet.h"


Bullet::Bullet(CCLayer *pLayer)
{
	this->pLayer = pLayer;

	position = ccp(0, 0);

	spriteIndex = VECTOR_STARTNUM;
	currentSprite = nullptr;

	aniFrameCount = 0;
}

Bullet::~Bullet(void)
{
	pLayer->removeChild(currentSprite, false);
	for( auto it = _standardSprites.begin(); it != _standardSprites.end(); )
	{
		CC_SAFE_RELEASE(*it);
		it = _standardSprites.erase(it);
	}
	_standardSprites.clear();
}

bool Bullet::createSprite(int number, CCPoint position, CCPoint targetLocation,
						  float moveSpeed, float damage)
{
	Data = &g_BulletData.find(number)->second;
	this->startLocation = this->position = position;
	this->targetLocation = targetLocation;
	this->moveSpeed = moveSpeed;
	this->damage = damage;
	size = Data->Size;

	//	방향 좌표
	moveDirection = ccp(targetLocation.x - startLocation.x,
		targetLocation.y - startLocation.y);
	//	빗변을 구하고
	float dir = _hypot(moveDirection.x, moveDirection.y);
	//	속도의 비율을 곱한다.
	moveDirection.x *= moveSpeed / dir;
	moveDirection.y *= moveSpeed / dir;

	//	Standing Image
	for(int i=VECTOR_STARTNUM; i<Data->Images.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_standardSprites.push_back(pSprite);
	}
	currentSprite = _standardSprites[0];
	pLayer->addChild(currentSprite);
	currentSprite->setPosition(position);

	return true;
}

void Bullet::doAction(float delayTime)
{
	doNextSprite();
	position.x += moveDirection.x * delayTime;
	position.y += moveDirection.y * delayTime;
	currentSprite->setPosition(position);
}

CCSprite* Bullet::doNextSprite()
{
	if (_standardSprites.size() > 1)
	{
		++aniFrameCount;
		if (aniFrameCount >= _standardFrames[spriteIndex])
		{
			aniFrameCount -= _standardFrames[spriteIndex];
			if (currentSprite)
			{
				pLayer->removeChild(currentSprite, false);
			}
			++spriteIndex %= _standardSprites.size();
			currentSprite = _standardSprites[spriteIndex];
			if (currentSprite)
			{
				pLayer->addChild(currentSprite);
			}
			else
			{
				FATAL_LOG(L"Failed to change sprite");
			}
		}
	}
	return currentSprite;
}

CCPoint Bullet::getPosition()
{
	return position;
}

CCSize Bullet::getSize()
{
	return size;
}

void Bullet::setPosition( float pos_x, float pos_y )
{
	position.x = pos_x;
	position.y = pos_y;
	currentSprite->setPosition(position);
}

int Bullet::objectNumber()
{
	return 0;
}

CCLayer* Bullet::getParentLayer()
{
	return pLayer;
}

CCSprite* Bullet::getCurrentSprite()
{
	return currentSprite;
}

const BulletData* Bullet::getBulletData()
{
	return Data;
}

float Bullet::getDamage()
{
	return damage;
}

float Bullet::getMoveSpeed()
{
	return moveSpeed;
}


