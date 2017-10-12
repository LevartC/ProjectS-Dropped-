#pragma once

#include "stdafx.h"

class NonGCSprite : public CCSprite
{
public:
	NonGCSprite(void);
	~NonGCSprite(void) override;

	static CCSprite* create(const char* FileName);
	static CCSprite* create(const char *pszFileName, const CCRect& rect);
};

