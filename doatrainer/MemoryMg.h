#pragma once
#include "stdafx.h"


class MemoryMg
{
public:
	MemoryMg(char* processName); 
	~MemoryMg();

	bool initialize();

	template<class T>  
	inline T Read(DWORD address);  

	template<class T>
	inline void Write(DWORD address, T value); 

	DWORD mainModuleBase; 

	int mainModuleSize;

	char* processName; 
	HANDLE processHandle; 
	int processID; 

	HANDLE GetProcessByName();
	DWORD GetModuleBase(LPSTR lpModuleName, int *sizeout); 
};

template<class T>
T MemoryMg::Read(DWORD address)
{
	T temp;
	ReadProcessMemory(processHandle, (LPVOID)address, &temp, sizeof(T), NULL);
	return temp;
}

template<class T>
void MemoryMg::Write(DWORD address, T value)
{
	WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(T), NULL); // Funkcja do WriteProcessMemory z windows.h do której podajemy potrzebne jej argumenty
}
