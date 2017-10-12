#pragma once

#include "stdafx.h"
#include "GameDataStruct.h"

struct BulletData
{
	string Name;					//	몬스터 이름
	CCSize Size;					//	사이즈

	int MoveSpeed;					//	이동속도
	int Damage;						//	대미지
	string DamageType;					//	대미지 속성타입
	int PiercingLevel;					//	관통레벨

	vector<ImageSpriteInfo> Images;		//	이미지
};
