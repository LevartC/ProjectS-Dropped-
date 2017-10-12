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
	string Name;					//	���� �̸�
	CCSize Size;					//	������
	int AttackRange;				//	�����Ÿ�
	int BulletSpeed;				//	�Ѿ� �ӵ�
	int Life, MaxLife;				//	���۽� �⺻ HP, �ִ� HP
	int Mana, MaxMana;				//	���۽� �⺻ MP, �ִ� MP
	int MoveSpeed;					//	�̵��ӵ�
	int ShootPerSec;				//	�ʴ� �����

	map<MonsterStatusType, vector<ImageSpriteInfo>> Images;		//	�̹���
	map<int, RangeAttackStruct> RangeAttack;	//	�ٰŸ� ���� ����
	map<int, MeleeAttackStruct> MeleeAttack;	//	�ٰŸ� ���� ����
};

