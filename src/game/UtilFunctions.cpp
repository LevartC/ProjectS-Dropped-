#include "stdafx.h"

#include "UtilFunctions.h"

string GetExecFolderNameA()
{
	char FullPath[MAX_PATH];
	GetModuleFileNameA(nullptr, FullPath, MAX_PATH);

	string Result = FullPath;
	auto Position = Result.find_last_of(L'\\');

	Result.resize(Position + 1);

	return move(Result);
}

wstring GetExecFolderName()
{
	wchar_t FullPath[MAX_PATH];
	GetModuleFileNameW(nullptr, FullPath, MAX_PATH);

	wstring Result = FullPath;
	auto Position = Result.find_last_of(L'\\');

	Result.resize(Position + 1);

	return move(Result);
}

std::wstring A2U(const string& Str)
{
	wstring result;
	size_t bufferLength = Str.size() + 1;
	wchar_t* Array = new wchar_t[bufferLength];
	MultiByteToWideChar(CP_ACP, 0, Str.c_str(), Str.size() + 1, Array, bufferLength);

	result = Array;
	delete [] Array;

	return std::move(result);
}
