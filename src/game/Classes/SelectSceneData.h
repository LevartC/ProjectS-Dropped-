#pragma once

#include "stdafx.h"

struct InterfaceData
{
	string Name;					//	�������̽� �̸�
	CCPoint Position;				//	������
	CCSize Size;					//	������

	map<int, string> ImageNames;		//	�̹��� �̸� ����Ʈ
	map<int, string> ImagePaths;		//	�̹��� ��� ����Ʈ
};
