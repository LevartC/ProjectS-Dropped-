#pragma once
#include "stdafx.h"

#define MAKE_STR(fmt, ...) wchar_t array##__LINE__ [4096]; \
	swprintf(array##__LINE__, fmt, __VA_ARGS__); 

#define DEBUG_LOG(fmt, ...) { \
	MAKE_STR(fmt, __VA_ARGS__); \
	LogManager::GetInstance()->WriteLog(LogManager::ltDebug, array##__LINE__); \
	}\

#define ERROR_LOG(fmt, ...) { \
	MAKE_STR(fmt, __VA_ARGS__); \
	LogManager::GetInstance()->WriteLog(LogManager::ltError, array##__LINE__); \
	}\

#define FATAL_LOG(fmt, ...) { \
	MAKE_STR(fmt, __VA_ARGS__); \
	LogManager::GetInstance()->WriteLog(LogManager::ltFatal, array##__LINE__); \
	}\

class LogManager
{
public:
	enum LogType
	{
		ltDebug = 0, //디버깅로그
		ltError = 1, //에러로그
		ltFatal = 2, //치명적 로그(프로그램 종료)
	};
	static LogManager* GetInstance();
	void WriteLog(LogType logType, wchar_t* log);
private:	
	LogManager();
	static LogManager *singletonLogManager;
};
