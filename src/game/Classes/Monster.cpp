#include "stdafx.h"
#include "Global.h"
#include "Const.h"
#include "Monster.h"
#include "UtilFunctions.h"


Monster::Monster(CCLayer *pLayer)
{
	this->pLayer = pLayer;

	position = ccp(0, 0);

	spriteIndex = VECTOR_STARTNUM;
	rangeAttackType = 1;
	currentSprite = nullptr;
	useLua = false;

	elapsedTime = 0.0f;
	patternNumber = 0;
	life = 0.0f;
	mana = 0.0f;

	currentMonsterStatus = MS_STAND;
	spriteStatus = MS_STAND;
}

Monster::~Monster()
{
	// 몬스터 부모 레이어에서 자식 노드를 지우는 함수.
	if (pLayer->getChildrenCount())
	{ pLayer->removeChild(currentSprite, false); }
	for( auto it = _standardSprites.begin(); it != _standardSprites.end(); )
	{
		for ( auto jt = it->second.begin(); jt != it->second.end(); )
		{
			CC_SAFE_RELEASE(*jt);
			jt = it->second.erase(jt);
		}
		it = _standardSprites.erase(it);
	}
	_standardSprites.clear();
	for( auto it = _meleeSprites.begin(); it != _meleeSprites.end(); )
	{
		for ( auto jt = it->second.begin(); jt != it->second.end(); )
		{
			CC_SAFE_RELEASE(*jt);
			jt = it->second.erase(jt);
		}
		it = _meleeSprites.erase(it);
	}
	_standardSprites.clear();
}

bool Monster::createSprite(int number, CCPoint position)
{
	Data = &g_MonsterData.find(number)->second;
	this->position = position;
	size = Data->Size;
	life = Data->Life;

	//	Standing Image
	vector<CCSprite*> _tmpStandSprites;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(MS_STAND)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(MS_STAND)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpStandSprites.push_back(pSprite);
	}
	_standardSprites.insert(make_pair(MS_STAND, _tmpStandSprites));
	//	Moving Image - Up
	vector<CCSprite*> _tmpUpSprites;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(MS_UP)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(MS_UP)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpUpSprites.push_back(pSprite);
	}
	_standardSprites.insert(make_pair(MS_UP, _tmpUpSprites));
	//	Moving Image - Down
	vector<CCSprite*> _tmpDownSprites;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(MS_DOWN)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(MS_DOWN)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpDownSprites.push_back(pSprite);
	}
	_standardSprites.insert(make_pair(MS_DOWN, _tmpDownSprites));
	//	Moving Image - Left
	vector<CCSprite*> _tmpLeftSprites;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(MS_LEFT)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(MS_LEFT)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpLeftSprites.push_back(pSprite);
	}
	_standardSprites.insert(make_pair(MS_LEFT, _tmpLeftSprites));
	//	Moving Image - Right
	vector<CCSprite*> _tmpRightSprites;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(MS_RIGHT)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(MS_RIGHT)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpRightSprites.push_back(pSprite);
	}
	_standardSprites.insert(make_pair(MS_RIGHT, _tmpRightSprites));
	//	Image - RangeAttack
	for (int i=MAP_STARTNUM; i<=Data->RangeAttack.size(); ++i)
	{
		vector<CCSprite*> _tmpRangeattackSprites;
		for(int j=VECTOR_STARTNUM; j<Data->RangeAttack.find(i)->second.ImagePath.size(); ++j)
		{
			CCSprite* pSprite = NonGCSprite::create(
				GETPATH(Data->RangeAttack.find(i)->second.ImagePath[j].Path),
				CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
			pSprite->setPosition(ccp(0, 0));
			_tmpRangeattackSprites.push_back(pSprite);
		}
		_rangeSprites.insert(make_pair(i, _tmpRangeattackSprites));
	}
	currentSprite = _standardSprites.find(currentMonsterStatus)->second[0];
	pLayer->addChild(currentSprite);
	currentSprite->setPosition(position);

	return true;
}

bool Monster::createSprite(string monsterName, CCPoint position)
{
	createSprite(g_MonsterTable.find(monsterName)->second, position);
	return true;
}

#define SAMPLE_MONSTER_POSITION_X 550.0f
#define MONSTER_RANGEATTACK_START_NUMBER 1
void Monster::doAction(float delayTime)
{
	doNextSprite();
	switch(patternNumber)
	{
	case 0:
		position.x -= Data->MoveSpeed * delayTime;
		if (position.x <= SAMPLE_MONSTER_POSITION_X)
		{
			position.x = SAMPLE_MONSTER_POSITION_X;
			++patternNumber;
		}
		break;
	case 1:
		elapsedTime += delayTime;
		if (elapsedTime >= 2.0f)
		{
			elapsedTime -= 2.0f;
			Bullet *tmpBullet = new Bullet(pLayer);
			tmpBullet->createSprite(Data->RangeAttack.find(MONSTER_RANGEATTACK_START_NUMBER)->second.BulletNumber,
				position, g_player1Character->getPosition(),
				Data->BulletSpeed, Data->RangeAttack.find(MONSTER_RANGEATTACK_START_NUMBER)->second.Damage);
			_bullets->push_back(tmpBullet);
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}

	currentSprite->setPosition(position);
}

CCSprite* Monster::doNextSprite()
{
	return currentSprite;
}

CCPoint Monster::getPosition()
{
	return position;
}

CCSize Monster::getSize()
{
	return size;
}

void Monster::setPosition( float pos_x, float pos_y )
{
	position.x = pos_x;
	position.y = pos_y;
	currentSprite->setPosition(position);
}

int Monster::objectNumber()
{
	return 0;
}

CCLayer* Monster::getParentLayer()
{
	return pLayer;
}

CCSprite* Monster::getCurrentSprite()
{
	return currentSprite;
}

const MonsterData* Monster::getMonsterData()
{
	return Data;
}

void Monster::setBulletList( list<Bullet*> *_bullets )
{
	this->_bullets = _bullets;
}

float Monster::subtractLife( float lifeValue )
{
	life -= lifeValue;
	return life;
}

float Monster::fillLife( float lifeValue )
{
	life += lifeValue;
	return life;
}
