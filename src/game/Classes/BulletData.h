#pragma once

#include "stdafx.h"
#include "GameDataStruct.h"

struct BulletData
{
	string Name;					//	���� �̸�
	CCSize Size;					//	������

	int MoveSpeed;					//	�̵��ӵ�
	int Damage;						//	�����
	string DamageType;					//	����� �Ӽ�Ÿ��
	int PiercingLevel;					//	���뷹��

	vector<ImageSpriteInfo> Images;		//	�̹���
};
