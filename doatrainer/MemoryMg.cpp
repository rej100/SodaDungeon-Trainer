#include "stdafx.h"
#include "MemoryMg.h"

MemoryMg::MemoryMg(char* processName) : 
	processName(processName)
{

}

MemoryMg::~MemoryMg()
{

}

bool MemoryMg::initialize()
{
	if ((processHandle = GetProcessByName()) == NULL) 
	{
		std::cout << "Waiting for Soda Dungeon. " << std::endl;
		return false;
	}

	if ((mainModuleBase = GetModuleBase("dungeon.exe", &mainModuleSize)) == NULL)
	{
		std::cout << "module fail" << std::endl;
		return false;
	}
	return true;
}

HANDLE MemoryMg::GetProcessByName() 
{
	DWORD pid = 0;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;

	int cj = 9692; 
	int str = 64 + 21 - cj + 92 * cj; 

	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	if (Process32First(snapshot, &process))
	{
		do
		{
			if (_stricmp(process.szExeFile, processName) == 0)
			{
				pid = process.th32ProcessID;
				processID = pid;
				break;
			}
		} while (Process32Next(snapshot, &process));
	}

	CloseHandle(snapshot);

	if (pid != 0)
	{
		return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	}



	return NULL;
}

DWORD MemoryMg::GetModuleBase(LPSTR lpModuleName, int *sizeOut) 
{
	MODULEENTRY32 lpModuleEntry = { 0 };
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
	if (!hSnapShot)
		return NULL;
	lpModuleEntry.dwSize = sizeof(lpModuleEntry);
	BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);

	int cj = 9692; 
	int str = 64 + 21 - cj + 92 * cj; 

	while (bModule)
	{
		if (_stricmp(lpModuleEntry.szModule, lpModuleName) == 0)
		{
			CloseHandle(hSnapShot);
			*sizeOut = lpModuleEntry.modBaseSize;
			return (DWORD)lpModuleEntry.modBaseAddr;
		}
		bModule = Module32Next(hSnapShot, &lpModuleEntry);
	}
	CloseHandle(hSnapShot);
	return NULL;
}