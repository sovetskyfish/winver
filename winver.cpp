#include <iostream>
#include <cstring>

#include "RegistryHelper.h"
#include "RegistryError.h"

#define CURRENT_VERSION_SUBKEY L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"

#define RegString(value) \
	std::wstring value = ::RegGetString(HKEY_LOCAL_MACHINE, CURRENT_VERSION_SUBKEY, L#value)

#define RegDword(value) \
	DWORD value = ::RegGetDword(HKEY_LOCAL_MACHINE, CURRENT_VERSION_SUBKEY, L#value)

#define Compare(value, value1, value2) \
	strcmp(argv[i], value1) == 0 || strcmp(argv[i], value2) == 0

void printHelp()
{
	std::cout
		<< "winver-cli [-d | --detail] [-g | --gui] [-h | --help]" << std::endl;
}

int main(int argc, char* argv[])
{
	bool displayHelp = false, displayDetails = false, displayGui = false;

	for (int i = 1; i < argc; i++)
	{
		if (Compare(argv[i], "-h", "--help"))
		{
			displayHelp = true;
		}
		else if (Compare(argv[i], "-d", "--detail"))
		{
			displayDetails = true;
		}
		else if (Compare(argv[i], "-g", "--gui"))
		{
			displayGui = true;
		}
		else
		{
			std::cout
				<< "Unable to understand option: "
				<< std::string(argv[i])
				<< ", IGNORING!!!"
				<< std::endl;
		}
	}

	if (displayHelp)
	{
		printHelp();
		return 0;
	}

	if (displayGui)
	{
		system("C:\\Windows\\System32\\winver.exe");
		return 0;
	}

	try
	{
		RegString(ProductName);
		RegString(DisplayVersion);
		RegString(CurrentBuildNumber);
		RegDword(UBR);

		if (displayDetails)
		{
			RegString(BuildLabEx);
			RegString(RegisteredOwner);
			RegString(RegisteredOrganization);
			RegString(ProductId);

			std::wcout
				<< "      Product : " << ProductName << " " << DisplayVersion << " (Build " << CurrentBuildNumber << "." << UBR << ")" << std::endl
				<< "   Build Info : " << BuildLabEx << std::endl
				<< "        Owner : " << RegisteredOwner << std::endl
				<< " Organization : " << RegisteredOrganization << std::endl
				<< "    ProductId : " << ProductId << std::endl;
		}
		else
		{
			std::wcout
				<< ProductName
				<< " " << DisplayVersion
				<< " (Build " << CurrentBuildNumber << "." << UBR << ")"
				<< std::endl;
		}
	}
	catch (...)
	{
		std::cout << "An error occurred while fetching information." << std::endl;
		return -1;
	}
}