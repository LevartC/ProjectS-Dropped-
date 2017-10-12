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
	string Name;					//	몬스터 이름
	CCSize Size;					//	사이즈
	float Length;					//	스테이지 넓이(길이)
	float MoveSpeed;				//	스테이지 이동진행속도

	map<int, StageMonsterData> StageMonsters;	//	몬스터 리스트

	string BackgroundImagePath;
};
