#pragma once

#include "stdafx.h"
#include "GameDataStruct.h"

//	속성은 배열로, 온오프 체크만 가능하도록
enum PropertiesType
{
};

//	캐릭터 상수
enum CharacterNumber
{
	CN_PENGUIN = 1,
	CN_WOLF = 2,
	CN_BEAR = 3,
	CN_END
};

enum CharacterStatusType
{
	CS_STAND = 1,
	CS_UP = 2,
	CS_DOWN = 3,
	CS_LEFT = 4,
	CS_RIGHT = 5,
	CS_RANGEATTACK = 6,
	CS_MELEEATTACK = 7,
	CS_BESHOT = 8,
	CS_SKILL = 9,
	CS_END
};

struct CharacterData
{
	string Name;					//	캐릭터 이름
	CCSize Size;					//	캐릭터 사이즈
	int AttackRange;				//	사정거리
	int BulletSpeed;				//	총알 속력
	int Life, MaxLife;				//	시작시 기본 HP, 최대 HP
	int Mana, MaxMana;				//	시작시 기본 MP, 최대 MP
	int MoveSpeed;					//	이동속도
	int ShootPerSec;				//	초당 연사력

	map<CharacterStatusType, vector<ImageSpriteInfo>> Images;		//	이미지
	map<int, RangeAttackStruct> RangeAttack;	//	근거리 가변 레벨
	map<int, MeleeAttackStruct> MeleeAttack;	//	근거리 가변 레벨
};
