#include "stdafx.h"
#include "Working.h"
#include "Global.h"
#include "Const.h"

#include "Working.h"
#include "UtilFunctions.h"
#include "Character.h"
#include "Log.h"

Character::Character(CCLayer *pLayer)
{
	this->pLayer = pLayer;

	spriteIndex = VECTOR_STARTNUM;
	missileLevel = MAP_STARTNUM;
	currentSprite = nullptr;
	currentCharacterStatus = CS_STAND;
	spriteStatus = CS_STAND;

	aniFrameCount = 0;

	dtMissileDelay = 0.0f;
	dtSpriteDelay = 0.0f;
	dtAnimation = 0.0f;
	dtMotionDelay = 0.0f;
}

Character::~Character()
{
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
	_meleeSprites.clear();
}

bool Character::createSprite(CharacterNumber charNum)
{
	Data = &g_CharData.find(charNum)->second;
	position = ccp(60 + Data->Size.width/2,
				CCDirector::sharedDirector()->getWinSize().height/2);
	currentRangeStruct = (RangeAttackStruct*)&Data->RangeAttack.find(missileLevel)->second;
	size = Data->Size;

	maxLife = life = Data->Life;
	//	Standing Image
	vector<CCSprite*> _tmpStandSprites;
	vector<int> _tmpStandFrames;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(CS_STAND)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(CS_STAND)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpStandSprites.push_back(pSprite);
		_tmpStandFrames.push_back(Data->Images.find(CS_STAND)->second[i].Frame);
	}
	_standardSprites.insert(make_pair(CS_STAND, _tmpStandSprites));
	_standardFrames.insert(make_pair(CS_STAND, _tmpStandFrames));

	//	Moving Image - Up
	vector<CCSprite*> _tmpUpSprites;
	vector<int> _tmpUpFrames;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(CS_UP)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(CS_UP)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpUpSprites.push_back(pSprite);
		_tmpUpFrames.push_back(Data->Images.find(CS_UP)->second[i].Frame);
	}
	_standardSprites.insert(make_pair(CS_UP, _tmpUpSprites));
	_standardFrames.insert(make_pair(CS_UP, _tmpUpFrames));
	//	Moving Image - Down
	vector<CCSprite*> _tmpDownSprites;
	vector<int> _tmpDownFrames;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(CS_DOWN)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(CS_DOWN)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpDownSprites.push_back(pSprite);
		_tmpDownFrames.push_back(Data->Images.find(CS_DOWN)->second[i].Frame);
	}
	_standardSprites.insert(make_pair(CS_DOWN, _tmpDownSprites));
	_standardFrames.insert(make_pair(CS_DOWN, _tmpDownFrames));
	//	Moving Image - Left
	vector<CCSprite*> _tmpLeftSprites;
	vector<int> _tmpLeftFrames;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(CS_LEFT)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(CS_LEFT)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpLeftSprites.push_back(pSprite);
		_tmpLeftFrames.push_back(Data->Images.find(CS_LEFT)->second[i].Frame);
	}
	_standardSprites.insert(make_pair(CS_LEFT, _tmpLeftSprites));
	_standardFrames.insert(make_pair(CS_LEFT, _tmpLeftFrames));
	//	Moving Image - Right
	vector<CCSprite*> _tmpRightSprites;
	vector<int> _tmpRightFrames;
	for(int i=VECTOR_STARTNUM; i<Data->Images.find(CS_RIGHT)->second.size(); ++i)
	{
		CCSprite* pSprite = NonGCSprite::create(
			GETPATH(Data->Images.find(CS_RIGHT)->second[i].Path),
			CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
		pSprite->setPosition(ccp(0, 0));
		_tmpRightSprites.push_back(pSprite);
		_tmpRightFrames.push_back(Data->Images.find(CS_RIGHT)->second[i].Frame);
	}
	_standardSprites.insert(make_pair(CS_RIGHT, _tmpRightSprites));
	_standardFrames.insert(make_pair(CS_RIGHT, _tmpRightFrames));
	//	Image - RangeAttack
	for (int i=MAP_STARTNUM; i<=Data->RangeAttack.size(); ++i)
	{
		vector<CCSprite*> _tmpRangeattackSprites;
		vector<int> _tmpRangeattackFrames;
		for(int j=VECTOR_STARTNUM; j<Data->RangeAttack.find(i)->second.ImagePath.size(); ++j)
		{
			CCSprite* pSprite = NonGCSprite::create(
				GETPATH(Data->RangeAttack.find(i)->second.ImagePath[j].Path),
				CCRectMake(0, 0, Data->Size.width, Data->Size.height) );
			pSprite->setPosition(ccp(0, 0));
			_tmpRangeattackSprites.push_back(pSprite);
			_tmpRangeattackFrames.push_back(Data->RangeAttack.find(i)->second.ImagePath[j].Frame);
		}
		_rangeSprites.insert(make_pair(i, _tmpRangeattackSprites));
		_rangeFrames.insert(make_pair(i, _tmpRangeattackFrames));
	}
	currentSprite = _standardSprites.find(currentCharacterStatus)->second[0];
	pLayer->addChild(currentSprite);
	currentSprite->setPosition(position);
	
	return true;
}

void Character::doAction(float delayTime)
{
	doNextSprite(delayTime);
	currentSprite->setPosition(position);
}

CCSprite* Character::doNextSprite(float delayTime)
{
	if (currentCharacterStatus == spriteStatus)
	{
		vector<CCSprite*> *spriteVector;
		vector<int> *frameVector;
		switch(spriteStatus)
		{
		case CS_STAND: case CS_UP: case CS_DOWN: case CS_LEFT: case CS_RIGHT:
			spriteVector = &_standardSprites.find(spriteStatus)->second;
			frameVector = &_standardFrames.find(spriteStatus)->second;
			break;
		case CS_RANGEATTACK:
			spriteVector = &_rangeSprites.find(missileLevel)->second;
			frameVector = &_rangeFrames.find(missileLevel)->second;
			break;
		case CS_MELEEATTACK:
			break;
		}
		if (spriteVector->size() > 1)
		{
			++aniFrameCount;
			if (aniFrameCount >= (*frameVector)[spriteIndex])
			{
				aniFrameCount -= (*frameVector)[spriteIndex];
				if (currentSprite)
				{
					pLayer->removeChild(currentSprite, false);
				}
				++spriteIndex %= spriteVector->size();
				currentSprite = (*spriteVector)[spriteIndex];
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
	}
	else
	{
		aniFrameCount = 0;
		spriteStatus = currentCharacterStatus;
		pLayer->removeChild(currentSprite, false);
		spriteIndex = VECTOR_STARTNUM;
		switch(spriteStatus)
		{
		case CS_STAND: case CS_UP: case CS_DOWN: case CS_LEFT: case CS_RIGHT:
			currentSprite = _standardSprites.find(spriteStatus)->second[spriteIndex];
			break;
		case CS_RANGEATTACK:
			currentSprite = _rangeSprites.find(missileLevel)->second[spriteIndex];
			break;
		default:
			break;
		}
		pLayer->addChild(currentSprite);
	}
	return currentSprite;
}

CCSprite* Character::getCurrentSprite()
{
	return currentSprite;
}

const CharacterData* Character::getCharacterData()
{
	return Data;
}

CCPoint Character::getPosition()
{
	return position;
}

CCSize Character::getSize()
{
	return size;
}

CCLayer* Character::getParentLayer()
{
	return pLayer;
}

CharacterStatusType Character::getCurrentCharacterStatus()
{
	return currentCharacterStatus;
}

void Character::setPosition(float pos_x, float pos_y)
{
	position.x = pos_x;
	position.y = pos_y;
	currentSprite->setPosition(position);
}

void Character::setCurrentCharacterStatus( CharacterStatusType status )
{
	currentCharacterStatus = status;
}

int Character::getMissileLevel()
{
	return missileLevel;
}

RangeAttackStruct* Character::getCurrentRangeStruct()
{
	return currentRangeStruct;
}

void Character::setBulletList( list<Bullet*> *_bullets )
{
	this->_bullets = _bullets;
}
