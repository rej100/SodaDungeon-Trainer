#pragma once
#include "stdafx.h"

//TUTAJ ZNAJDUJ¥ SIÊ TYLKO DEKLARACJE FUNKCI I ZMIENNYCH(z wyj¹tkiem Write i Read) CA£Y KOD JEST W MemoryMg.cpp

class MemoryMg
{
public:
	MemoryMg(char* processName); //konstruktor do obiektów klasy MemoryMg
	~MemoryMg(); //konstruktor do obiektów klasy MemoryMg

	bool initialize(); //funkcja initialize

	template<class T>  //Tworzenie sobie w³asnego typu zmiennej który potem mo¿na zast¹piæ jakimkolwiek innym, dziêki temu nie muszê pisaæ oddzielnej funkcji dla Czytania i wpisywania do\z pamiêci int'ów, float'ów, DWOR'Dów itd. TO TAK NAPRAWDÊ DZIA£A TROCHÊ INACZEJ ALE TAK JEST £ATWIEJ ZROZUMIEÆ WIÊC JAK NA WIKIPEDI BÊDZIE INACZEJ TO FUCK YOU
	inline T Read(DWORD address); //deklaracja funkcji Read która jako argument bierze 32bitowego unsigned(nie ujemnego) int'a(czyli tak zwany DWORD) i przechowuje go sobie jako "address" 

	template<class T> //Tworzenie sobie w³asnego typu zmiennej który potem mo¿na zast¹piæ jakimkolwiek innym, dziêki temu nie muszê pisaæ oddzielnej funkcji dla Czytania i wpisywania do\z pamiêci int'ów, float'ów, DWOR'Dów itd.
	inline void Write(DWORD address, T value); //deklaracja funkcji Read która jako argument bierze 32bitowego unsigned(nie ujemnego) int'a(czyli tak zwany DWORD) i przechowuje go sobie jako "address" oraz T'a i przechowuje go sobie jako "value"

	//Powy¿sze funkcje bior¹ tak¿e jako argument typ zmiennej i przechowuj¹ go w T

	DWORD mainModuleBase; // 32bitowy unsigned(nieujemny) int, to samo co unsigned int, zazwyczaj u¿ywa siê go do przechowywania liczb ca³kowitych nie ujemnych heksadecymalnych.
	//"heksadecymalny" to po prostu inny sposób zapisywania liczb, np. 20 decymalne to 0x14 heksadecymalne a 8542 decymalne to 215E heksadecymalne

	//Linijkê wy¿ej wymyœli³em sobie dwa s³owa, mianowicie "decymalne" i "heksadecymalne" bo zapomnia³em, ¿e po polsku to po prostu system dzisiêtny i szesnastkowy

	int mainModuleSize; //int przechowuj¹cy wielkoœæ modu³u "dungeon.exe" TO NIE JEST WIELKOŒÆ PLIKU "dungeon.exe"

	char* processName; // ci¹g znaków przechowuj¹cy processName
	HANDLE processHandle; //Niewiem jak przet³umaczyæ handle na polski ¿eby by³o programistycznie poprawnie wiêc po prostu handle do procesu "dungeon.exe"
	int processID; // PID procesu "dungeon.exe"

	HANDLE GetProcessByName(); //Deklaracja funkcji która da nam Handle do procesu "dungeon.exe" i  jego PID
	DWORD GetModuleBase(LPSTR lpModuleName, int *sizeout); //Funkcaj która da nam adres(Do którego dodawaæ bêdziemy offsety) modu³u który jej damy;
};

template<class T> //Tworzenie sobie w³asnego typu zmiennej który potem mo¿na zast¹piæ jakimkolwiek innym, dziêki temu nie muszê pisaæ oddzielnej funkcji dla Czytania i wpisywania do\z pamiêci int'ów, float'ów, DWOR'Dów itd.
T MemoryMg::Read(DWORD address)
{
	T temp;
	ReadProcessMemory(processHandle, (LPVOID)address, &temp, sizeof(T), NULL); // Funkcja do ReadProcessMemory z windows.h do której podajemy potrzebne jej argumenty
	return temp;
}

template<class T>
void MemoryMg::Write(DWORD address, T value)
{
	WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(T), NULL); // Funkcja do WriteProcessMemory z windows.h do której podajemy potrzebne jej argumenty
}
