#pragma once

#include "stdafx.h"

__interface IScriptableObject;

class LuaStateManager
{
public:
	LuaStateManager(void);
	virtual ~LuaStateManager(void);

	bool ReadScript(const char* LuaScript);
	bool ReadScriptFile(const char* FileName);
	void AddLuaGlues();

	void ExecuteMobSchedule(IScriptableObject* Object);
	void ExecuteBulletSchedule(IScriptableObject* Object);
	
	void TestLua();
private:
	void CallScheduleFunction(IScriptableObject* Object, string FunctionName);
	string GetFunctionName(IScriptableObject* Object, string FunctionName);
	lua_State* L;	
};

