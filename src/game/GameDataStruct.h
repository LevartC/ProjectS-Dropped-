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
	int BulletNumber;					//	총알번호
	int Damage;							//	대미지
	vector<ImageSpriteInfo> ImagePath;	//	이미지 경로
};

struct MeleeAttackStruct
{
	int Damage;
	int Range_X, Range_Y;
	int Speed;
	vector<ImageSpriteInfo> ImagePath;
	//map<int, string> ImagePath;		//	이미지파일
};