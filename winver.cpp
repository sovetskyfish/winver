#include <iostream>
#include <iomanip>
#include <cstring>

#include "RegistryHelper.h"
#include "RegistryError.h"
#include "SysInfoHelper.h"

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
		<< "winver-cli [-d | --detail] [-s | --spec] [-g | --gui] [-h | --help]" << std::endl;
}

char* TrimSpace(char* str) {
	char* end;
	while (isspace(*str)) {
		str++;
	}
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end)) {
		end--;
	}
	*(end + 1) = '\0';
	return str;
}

int main(int argc, char* argv[])
{
	bool displayHelp = false, displayDetails = false, displaySpecs = false, displayGui = false;

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
		else if (Compare(argv[i], "-s", "--spec"))
		{
			displaySpecs = true;
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
				<< "       Product : " << ProductName << " " << DisplayVersion << " (Build " << CurrentBuildNumber << "." << UBR << ")" << std::endl
				<< "    Build Info : " << BuildLabEx << std::endl
				<< "         Owner : " << RegisteredOwner << std::endl
				<< "  Organization : " << RegisteredOrganization << std::endl
				<< "     ProductId : " << ProductId << std::endl;

			if (displaySpecs)
			{
				char CPUName[0x40 + 1];
				::GetCPUName(CPUName);
				DWORD CPUCoreNum = ::GetCPUCoreNum();
				double memInGB = ::GetSysMemoryGB();
				std::wcout
					<< "           CPU : " << TrimSpace(CPUName)
					<< " [" << CPUCoreNum << " core(s)]" << std::endl
					<< " Available RAM : " << std::fixed << std::setprecision(2)
					<< memInGB << " GB" << std::endl;
			}
		}
		else
		{
			std::wcout
				<< ProductName
				<< " " << DisplayVersion
				<< " (Build " << CurrentBuildNumber << "." << UBR << ")"
				<< std::endl;
			if (displaySpecs)
			{
				char CPUName[0x40 + 1];
				::GetCPUName(CPUName);
				DWORD CPUCoreNum = ::GetCPUCoreNum();
				double memInGB = ::GetSysMemoryGB();
				std::wcout
					<< TrimSpace(CPUName)
					<< " [" << CPUCoreNum << " core(s)]"
					<< " with " << std::fixed
					<< std::setprecision(2)
					<< memInGB << " GB RAM installed"
					<< std::endl;
			}
		}
	}
	catch (...)
	{
		std::cout << "An error occurred while fetching information." << std::endl;
		return -1;
	}
}