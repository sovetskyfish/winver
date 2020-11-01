#include <iostream>
#include "RegistryHelper.h"
#include "RegistryError.h"

#define CURRENT_VERSION_SUBKEY L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"

#define RegString(value) \
	std::wstring value = ::RegGetString(HKEY_LOCAL_MACHINE, CURRENT_VERSION_SUBKEY, L#value)

#define RegDword(value) \
	DWORD value = ::RegGetDword(HKEY_LOCAL_MACHINE, CURRENT_VERSION_SUBKEY, L#value)

int main(int argc, char* argv[])
{
	RegString(ProductName);
	RegString(DisplayVersion);
	RegString(CurrentBuildNumber);
	RegDword(UBR);

	std::wcout
		<< ProductName
		<< " " << DisplayVersion
		<< " (Build " << CurrentBuildNumber << "." << UBR << ")"
		<< std::endl;
}