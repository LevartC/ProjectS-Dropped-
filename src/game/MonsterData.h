#pragma once

#include "stdafx.h"
#include "GameDataStruct.h"

enum MonsterStatusType
{
	MS_STAND = 1,
	MS_UP = 2,
	MS_DOWN = 3,
	MS_LEFT = 4,
	MS_RIGHT = 5,
	MS_RANGEATTACK = 6,
	MS_MELEEATTACK = 7,
	MS_SKILL = 8,
	MS_END
};

struct MonsterData
{
	string Name;					//	몬스터 이름
	CCSize Size;					//	사이즈
	int AttackRange;				//	사정거리
	int BulletSpeed;				//	총알 속도
	int Life, MaxLife;				//	시작시 기본 HP, 최대 HP
	int Mana, MaxMana;				//	시작시 기본 MP, 최대 MP
	int MoveSpeed;					//	이동속도
	int ShootPerSec;				//	초당 연사력

	map<MonsterStatusType, vector<ImageSpriteInfo>> Images;		//	이미지
	map<int, RangeAttackStruct> RangeAttack;	//	근거리 가변 레벨
	map<int, MeleeAttackStruct> MeleeAttack;	//	근거리 가변 레벨
};

