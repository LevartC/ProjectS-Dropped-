#include "stdafx.h"
#include "NonGCSprite.h"


NonGCSprite::NonGCSprite(void)
{
}


NonGCSprite::~NonGCSprite(void)
{
}

CCSprite* NonGCSprite::create( const char* FileName )
{
	NonGCSprite *pobSprite = new NonGCSprite();
	if (pobSprite && pobSprite->initWithFile(FileName))
	{
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* NonGCSprite::create(const char *FileName, const CCRect& rect)
{
	NonGCSprite *pobSprite = new NonGCSprite();
	if (pobSprite && pobSprite->initWithFile(FileName, rect))
	{
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}