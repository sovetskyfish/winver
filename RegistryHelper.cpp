#include "RegistryHelper.h"
#include "RegistryError.h"

DWORD RegGetDword(HKEY hKey, const std::wstring& subKey, const std::wstring& value)
{
	DWORD data{};
	DWORD dataSize = sizeof(data);

	LONG retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		value.c_str(),
		RRF_RT_REG_DWORD,
		nullptr,
		&data,
		&dataSize
	);

	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError{ "Cannot read DWORD from registry.", retCode };
	}

	return data;
}

std::wstring RegGetString(HKEY hKey, const std::wstring& subKey, const std::wstring& value)
{
	DWORD dataSize{};

	LONG retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		value.c_str(),
		RRF_RT_REG_SZ,
		nullptr,
		nullptr,
		&dataSize
	);

	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError{ "Cannot read string from registry", retCode };
	}

	std::wstring data;
	data.resize(dataSize / sizeof(wchar_t));

	retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		value.c_str(),
		RRF_RT_REG_SZ,
		nullptr,
		&data[0],
		&dataSize
	);

	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError{ "Cannot read string from registry", retCode };
	}

	// ÒÆ³ý Win32 API ·µ»ØµÄÄ©Î² NUL
	DWORD stringLengthInWchars = dataSize / sizeof(wchar_t);
	stringLengthInWchars--;
	data.resize(stringLengthInWchars);

	return data;
}
