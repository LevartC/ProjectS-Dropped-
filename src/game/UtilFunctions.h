#pragma once

#include "stdafx.h"

#define GETPATH(FileName) \
	(GetExecFolderNameA() + FileName).c_str()
string GetExecFolderNameA();
wstring GetExecFolderName();

wstring A2U(const string& Str);