#pragma once

#include "stdafx.h"
#include "GameDataStruct.h"

struct StageMonsterData
{
	CCPoint Position;
	int MonsterNumber;
};

struct StageData
{
	string Name;					//	���� �̸�
	CCSize Size;					//	������
	float Length;					//	�������� ����(����)
	float MoveSpeed;				//	�������� �̵�����ӵ�

	map<int, StageMonsterData> StageMonsters;	//	���� ����Ʈ

	string BackgroundImagePath;
};
