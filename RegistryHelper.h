#pragma once
#include <string>
#include <Windows.h>

DWORD RegGetDword(
	HKEY hKey,
	const std::wstring& subKey,
	const std::wstring& value
);

std::wstring RegGetString(
	HKEY hKey,
	const std::wstring& subKey,
	const std::wstring& value
);