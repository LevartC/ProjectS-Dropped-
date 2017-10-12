#pragma once

#include "stdafx.h"

struct ImageSpriteInfo
{
	int Index;
	int Frame;
	string Path;
};

struct RangeAttackStruct
{
	int BulletNumber;					//	�Ѿ˹�ȣ
	int Damage;							//	�����
	vector<ImageSpriteInfo> ImagePath;	//	�̹��� ���
};

struct MeleeAttackStruct
{
	int Damage;
	int Range_X, Range_Y;
	int Speed;
	vector<ImageSpriteInfo> ImagePath;
	//map<int, string> ImagePath;		//	�̹�������
};