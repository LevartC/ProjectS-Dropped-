#pragma once

#include "stdafx.h"

struct InterfaceData
{
	string Name;					//	인터페이스 이름
	CCPoint Position;				//	포지션
	CCSize Size;					//	사이즈

	map<int, string> ImageNames;		//	이미지 이름 리스트
	map<int, string> ImagePaths;		//	이미지 경로 리스트
};
