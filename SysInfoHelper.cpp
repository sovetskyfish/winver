#include "SysInfoHelper.h"

#include <intrin.h>
#include <Windows.h>

void GetCPUName(char* CPUName)
{
	int CPUInfo[4] = { -1 };
	unsigned numOfExIds;
	__cpuid(CPUInfo, 0x80000000);
	numOfExIds = CPUInfo[0];
	unsigned long long ptr = 0;
	for (unsigned i = 0x80000000; i <= numOfExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		if (i == 0x80000002)
		{
			memcpy(CPUName, CPUInfo, sizeof(CPUInfo));
			ptr = max((unsigned long long)(CPUName + sizeof(CPUInfo) / sizeof(char)), ptr);
		}
		else if (i == 0x80000003)
		{
			memcpy(CPUName + 16, CPUInfo, sizeof(CPUInfo));
			ptr = max((unsigned long long)(CPUName + (16 + sizeof(CPUInfo)) / sizeof(char)), ptr);
		}
		else if (i == 0x80000004)
		{
			memcpy(CPUName + 32, CPUInfo, sizeof(CPUInfo));
			ptr = max((unsigned long long)(CPUName + (32 + sizeof(CPUInfo)) / sizeof(char)), ptr);
		}
	}
	*(char*)ptr = '\0';
}

DWORD GetCPUCoreNum()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	return sysInfo.dwNumberOfProcessors;
}

double GetSysMemoryGB()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return ((long double)statex.ullTotalPhys / 1024) / 1024 / 1024;
}