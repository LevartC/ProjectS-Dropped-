#include "stdafx.h"
#include "LuaStateManager.h"
#include "Global.h"
#include "Const.h"
#include "Log.h"
#include "UtilFunctions.h"
#include "IGameObject.h"

LuaStateManager* g_Lua = nullptr;

#pragma region Glue 함수 영역
int LuaDebugLog(lua_State *L) 
{	
	wstring msg = A2U(lua_tostring(L, -1));
	DEBUG_LOG(msg.c_str());
	lua_pop(L, 1);

	return 0;
}

int LuaGetCharPos(lua_State *L)
{
//Todo: X, Y 는 실제 캐릭터로부터 읽도록 수정되어야 함
	int X = 100;
	int Y = 200;
	
	lua_newtable(L);
	
	lua_pushstring(L, "X");
	lua_pushnumber(L, X);
	lua_rawset(L, -3);

	lua_pushstring(L, "Y");
	lua_pushnumber(L, Y);
	lua_rawset(L, -3);
	
	return 1;
}

int LuaSetCharPos(lua_State *L)
{	
	return 0;
}

int LuaGetObjectPos(lua_State *L)
{
	IGameObject* pObject = reinterpret_cast<IGameObject*>(lua_tointeger(L, -1));

//Todo: X, Y 는 실제 객체로부터 읽도록 수정되어야 함
	int X = 300;
	int Y = 400;

	lua_newtable(L);

	lua_pushstring(L, "X");
	lua_pushnumber(L, X);
	lua_rawset(L, -3);

	lua_pushstring(L, "Y");
	lua_pushnumber(L, Y);
	lua_rawset(L, -3);
	
	return 1;
}

int LuaSetObjectPos(lua_State *L)
{
	return 0;
}
#pragma endregion

LuaStateManager::LuaStateManager(void)
{
	L = luaL_newstate();
}

LuaStateManager::~LuaStateManager(void)
{
	lua_close(L);
}

bool LuaStateManager::ReadScript( const char* LuaScript )
{
	return luaL_dostring(L, LuaScript) == 0;
}

bool LuaStateManager::ReadScriptFile( const char* FileName )
{	
	return luaL_dofile(L, FileName) == 0;
}

void LuaStateManager::AddLuaGlues()
{
	lua_register(L, "DebugLog", &LuaDebugLog);
	lua_register(L, "GetCharPos", &LuaGetCharPos);
	lua_register(L, "SetCharPos", &LuaSetCharPos);
	lua_register(L, "GetObjectPos", &LuaGetObjectPos);
	lua_register(L, "SetObjectPos", &LuaSetObjectPos);
}

void LuaStateManager::TestLua()
{
	int top = lua_gettop(L);
	lua_getglobal(L, "test");
	
	lua_pushnumber(L, 0x10000);

	lua_call(L, 1, 0);
}


void LuaStateManager::ExecuteMobSchedule(IScriptableObject* Object)
{
	CallScheduleFunction(Object, GetFunctionName(Object, LUA_MONSTER_FUNCTION));
}

void LuaStateManager::ExecuteBulletSchedule(IScriptableObject* Object)
{
	CallScheduleFunction(Object, GetFunctionName(Object, LUA_BULLET_FUNCTION));
}

std::string LuaStateManager::GetFunctionName(IScriptableObject* Object, string FunctionName)
{
	char Buffer[1024];
	sprintf(Buffer, FunctionName.c_str(), Object->objectNumber());

	return Buffer;
}

void LuaStateManager::CallScheduleFunction(IScriptableObject* Object, string FunctionName)
{
	lua_getglobal(L, FunctionName.c_str());
	lua_pushinteger(L, (INT_PTR)Object);

	lua_call(L, 1, 0);
}
