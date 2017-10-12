#pragma once

#include "stdafx.h"
#include "GameDataStruct.h"

//	�Ӽ��� �迭��, �¿��� üũ�� �����ϵ���
enum PropertiesType
{
};

//	ĳ���� ���
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
	string Name;					//	ĳ���� �̸�
	CCSize Size;					//	ĳ���� ������
	int AttackRange;				//	�����Ÿ�
	int BulletSpeed;				//	�Ѿ� �ӷ�
	int Life, MaxLife;				//	���۽� �⺻ HP, �ִ� HP
	int Mana, MaxMana;				//	���۽� �⺻ MP, �ִ� MP
	int MoveSpeed;					//	�̵��ӵ�
	int ShootPerSec;				//	�ʴ� �����

	map<CharacterStatusType, vector<ImageSpriteInfo>> Images;		//	�̹���
	map<int, RangeAttackStruct> RangeAttack;	//	�ٰŸ� ���� ����
	map<int, MeleeAttackStruct> MeleeAttack;	//	�ٰŸ� ���� ����
};
