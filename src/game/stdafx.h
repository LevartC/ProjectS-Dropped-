#pragma once

#pragma warning(disable:4996)
#pragma warning(disable:4819)

#include <Windows.h>

#include "cocos2d.h"
#include "CCEGLView.h"
#include "tinyxml.h"
#include "lua.hpp"

#include <string>
#include <utility>
#include <list>
#include <vector>
#include <map>
#include <set>

using namespace std;
using namespace cocos2d;

#define SAFE_DELETE(ptr) if(ptr) { delete (ptr); (ptr) = nullptr; }
#define SAFE_DELETE_ARRAY(ptr) if(ptr) { delete [](ptr); (ptr) = nullptr; }

#define THROW_IF(Function, ErrorString) if( Function ) { throw wstring(ErrorString); }

#define SHIFTED     0x8000
#define UPPED		0x0001

#include "NonGCSprite.h"