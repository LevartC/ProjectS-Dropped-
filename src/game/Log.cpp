#include "stdafx.h"
#include "Log.h"
#include <cstdio>
#include <cstdlib>

LogManager* LogManager::singletonLogManager;

LogManager* LogManager::GetInstance()
{
	if(singletonLogManager == nullptr)
	{
		singletonLogManager = new LogManager();
	}
	
	return singletonLogManager;
}

LogManager::LogManager()
{
	AllocConsole();
	freopen( "CONOUT$",  "wt", stdout); 	
	
	//Todo : 파일로그 작업중
}

void LogManager::WriteLog(LogType logType, wchar_t* log)
{	
	switch (logType)
	{
	case ltDebug:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xa);
		wprintf(L"[Debug]");
		break;
	case ltError:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xe);
		wprintf(L"[Error]");
		break;
	case ltFatal:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xc);
		wprintf(L"[Fatal]");
		break;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf);

	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);	
	wprintf(L"[%04d-%02d-%02d %02d:%02d:%02d] ", systemTime.wYear, systemTime.wMonth, systemTime.wDay,
		systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	wprintf(L"%s\n", log);
}
