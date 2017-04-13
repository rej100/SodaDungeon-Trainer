// doatrainer.cpp : Defines the entry point for the console application.
//

//Jak co� pisa�em to dla laty wi�c wyja�niam tutaj nawet najbardziej podstawowe �eczy, EVER

#include "stdafx.h" // "precompiled header", taka rzecz kt�ra jest tylko w visual studio, w �rodku dajesz liste bibliotek zamiast kt�rych potem piszesz po prostu "stdafx.h"
#include "MemoryMg.h" //Moja biblioteka do memory managment
#include "Threads.h"

using namespace std;

int main()
{
	SetConsoleTitle("Cichy Soda Dungeon trainer v2.3"); // zmienia nazw� okienka na: Cichy Soda Dungeon trainer v2.3
	MemoryMg mem("dungeon.exe"); //Tworzy nowy obiekt klasy MemoryMg o nazwie "mem" i ustawia warto�� mem.processName na "dungeon.exe"

	// WA�NE! mem->processName to to samo co mem.process name, ze wzgl�dy na typ obiektu "mem"(zachowuje si� jak wska�nik) musz� w niekt�rych przypadkach u�ywa� "->" zamiast "."

	while (!mem.initialize()) //wykonuje funkcj� mem.initialize() dop�ki nie zwr�ci ona warto�ci true | Patrz MemoryMg.cpp
	{
		Sleep(300); //Czeka 300 milisecond pomi�dzy sprawdzaniem
	}
	system("cls"); // czy�ci konsol�
	std::cout << "initialization success!" << std::endl; //wypisuje menu
	std::cout << "SPACE - Add money" << std::endl; //wypisuje menu
	std::cout << "F10 - Add essence" << std::endl; //wypisuje menu
	std::cout << "F9 - Level + 1" << std::endl; //wypisuje menu
	std::cout << "F8 - Level - 1" << std::endl; //wypisuje menu
	std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl; //wypisuje menu

	Threads::threads_init(&mem); //Wywo�uje funkcj� threads_init z wska�nikiem do obiektu "mem" jako argumentem

	getchar(); //czeka na naci�ni�cie klawisza (nie powinno tutaj by� poniewa� od poprzedniej linijki program dzia�a w Treads.h)

    return 0;
}

