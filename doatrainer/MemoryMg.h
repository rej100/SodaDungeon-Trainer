#pragma once
#include "stdafx.h"

//TUTAJ ZNAJDUJ� SI� TYLKO DEKLARACJE FUNKCI I ZMIENNYCH(z wyj�tkiem Write i Read) CA�Y KOD JEST W MemoryMg.cpp

class MemoryMg
{
public:
	MemoryMg(char* processName); //konstruktor do obiekt�w klasy MemoryMg
	~MemoryMg(); //konstruktor do obiekt�w klasy MemoryMg

	bool initialize(); //funkcja initialize

	template<class T>  //Tworzenie sobie w�asnego typu zmiennej kt�ry potem mo�na zast�pi� jakimkolwiek innym, dzi�ki temu nie musz� pisa� oddzielnej funkcji dla Czytania i wpisywania do\z pami�ci int'�w, float'�w, DWOR'D�w itd. TO TAK NAPRAWD� DZIA�A TROCH� INACZEJ ALE TAK JEST �ATWIEJ ZROZUMIE� WI�C JAK NA WIKIPEDI B�DZIE INACZEJ TO FUCK YOU
	inline T Read(DWORD address); //deklaracja funkcji Read kt�ra jako argument bierze 32bitowego unsigned(nie ujemnego) int'a(czyli tak zwany DWORD) i przechowuje go sobie jako "address" 

	template<class T> //Tworzenie sobie w�asnego typu zmiennej kt�ry potem mo�na zast�pi� jakimkolwiek innym, dzi�ki temu nie musz� pisa� oddzielnej funkcji dla Czytania i wpisywania do\z pami�ci int'�w, float'�w, DWOR'D�w itd.
	inline void Write(DWORD address, T value); //deklaracja funkcji Read kt�ra jako argument bierze 32bitowego unsigned(nie ujemnego) int'a(czyli tak zwany DWORD) i przechowuje go sobie jako "address" oraz T'a i przechowuje go sobie jako "value"

	//Powy�sze funkcje bior� tak�e jako argument typ zmiennej i przechowuj� go w T

	DWORD mainModuleBase; // 32bitowy unsigned(nieujemny) int, to samo co unsigned int, zazwyczaj u�ywa si� go do przechowywania liczb ca�kowitych nie ujemnych heksadecymalnych.
	//"heksadecymalny" to po prostu inny spos�b zapisywania liczb, np. 20 decymalne to 0x14 heksadecymalne a 8542 decymalne to 215E heksadecymalne

	//Linijk� wy�ej wymy�li�em sobie dwa s�owa, mianowicie "decymalne" i "heksadecymalne" bo zapomnia�em, �e po polsku to po prostu system dzisi�tny i szesnastkowy

	int mainModuleSize; //int przechowuj�cy wielko�� modu�u "dungeon.exe" TO NIE JEST WIELKO�� PLIKU "dungeon.exe"

	char* processName; // ci�g znak�w przechowuj�cy processName
	HANDLE processHandle; //Niewiem jak przet�umaczy� handle na polski �eby by�o programistycznie poprawnie wi�c po prostu handle do procesu "dungeon.exe"
	int processID; // PID procesu "dungeon.exe"

	HANDLE GetProcessByName(); //Deklaracja funkcji kt�ra da nam Handle do procesu "dungeon.exe" i  jego PID
	DWORD GetModuleBase(LPSTR lpModuleName, int *sizeout); //Funkcaj kt�ra da nam adres(Do kt�rego dodawa� b�dziemy offsety) modu�u kt�ry jej damy;
};

template<class T> //Tworzenie sobie w�asnego typu zmiennej kt�ry potem mo�na zast�pi� jakimkolwiek innym, dzi�ki temu nie musz� pisa� oddzielnej funkcji dla Czytania i wpisywania do\z pami�ci int'�w, float'�w, DWOR'D�w itd.
T MemoryMg::Read(DWORD address)
{
	T temp;
	ReadProcessMemory(processHandle, (LPVOID)address, &temp, sizeof(T), NULL); // Funkcja do ReadProcessMemory z windows.h do kt�rej podajemy potrzebne jej argumenty
	return temp;
}

template<class T>
void MemoryMg::Write(DWORD address, T value)
{
	WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(T), NULL); // Funkcja do WriteProcessMemory z windows.h do kt�rej podajemy potrzebne jej argumenty
}
