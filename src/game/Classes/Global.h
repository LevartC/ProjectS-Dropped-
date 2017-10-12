#pragma once

#include "stdafx.h"
#include "Character.h"
#include "CharacterData.h"
#include "MonsterData.h"
#include "BulletData.h"
#include "StageData.h"
#include "SelectSceneData.h"
#include "LuaStateManager.h"

__interface IGameObject;

//	Data
extern map<CharacterNumber, CharacterData> g_CharData;
extern map<int, MonsterData> g_MonsterData;
extern map<string, int> g_MonsterTable;
extern map<int, BulletData> g_BulletData;
extern map<int, StageData> g_StageData;
extern map<int, InterfaceData> g_SelectSceneData;


//	Global Objects
extern Character* g_player1Character;
extern set<IGameObject*> g_GameObjects;
extern LuaStateManager* g_Lua;