#include "stdafx.h"
#include "MemoryMg.h"

//NAJPIERW PATRZ MemoryMg.h

MemoryMg::MemoryMg(char* processName) : //Definicja wczeœniej zdeklarowanego konstruktora
	processName(processName)
{

}

MemoryMg::~MemoryMg() //Definicja wczeœniej zdeklarowanego konstruktora
{

}

bool MemoryMg::initialize() // Definicja wczeœniej zdeklarowanej funkcji initialize
{
	if ((processHandle = GetProcessByName()) == NULL) //Je¿eli nie mo¿na uzyskaæ Handle do procesu wypisuje waiting for soda dungeon i zwraca false
	{
		std::cout << "Waiting for Soda Dungeon. " << std::endl;
		return false;
	}

	if ((mainModuleBase = GetModuleBase("dungeon.exe", &mainModuleSize)) == NULL) //je¿eli nie mo¿na uzyskaæ adresu modu³u "dungeon.exe" i jego wielkoœci wypisuje module fail i zwraca false
	{
		std::cout << "module fail" << std::endl;
		return false;
	}
	return true;
}

HANDLE MemoryMg::GetProcessByName() // Definicja wczeœniej... Wiesz o co mi chodzi
{
	DWORD pid = 0;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;

	int cj = 9692; //junk code poniewa¿ GetProcessByName w prawie wszystkich haksach jest taki sam
	int str = 64 + 21 - cj + 92 * cj; //junk code poniewa¿ GetProcessByName w prawie wszystkich haksach jest taki sam

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

DWORD MemoryMg::GetModuleBase(LPSTR lpModuleName, int *sizeOut) //Defini...
{
	MODULEENTRY32 lpModuleEntry = { 0 };
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
	if (!hSnapShot)
		return NULL;
	lpModuleEntry.dwSize = sizeof(lpModuleEntry);
	BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);

	int cj = 9692; //junk code z tego samego powodu co wczeœniej
	int str = 64 + 21 - cj + 92 * cj; //junk code z tego samego powodu co wczeœniej

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