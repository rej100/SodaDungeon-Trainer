// doatrainer.cpp : Defines the entry point for the console application.
//

//Jak coœ pisa³em to dla laty wiêc wyjaœniam tutaj nawet najbardziej podstawowe ¿eczy, EVER

#include "stdafx.h" // "precompiled header", taka rzecz która jest tylko w visual studio, w œrodku dajesz liste bibliotek zamiast których potem piszesz po prostu "stdafx.h"
#include "MemoryMg.h" //Moja biblioteka do memory managment
#include "Threads.h"

using namespace std;

int main()
{
	SetConsoleTitle("Cichy Soda Dungeon trainer v2.3"); // zmienia nazwê okienka na: Cichy Soda Dungeon trainer v2.3
	MemoryMg mem("dungeon.exe"); //Tworzy nowy obiekt klasy MemoryMg o nazwie "mem" i ustawia wartoœæ mem.processName na "dungeon.exe"

	// WA¯NE! mem->processName to to samo co mem.process name, ze wzglêdy na typ obiektu "mem"(zachowuje siê jak wskaŸnik) muszê w niektórych przypadkach u¿ywaæ "->" zamiast "."

	while (!mem.initialize()) //wykonuje funkcjê mem.initialize() dopóki nie zwróci ona wartoœci true | Patrz MemoryMg.cpp
	{
		Sleep(300); //Czeka 300 milisecond pomiêdzy sprawdzaniem
	}
	system("cls"); // czyœci konsolê
	std::cout << "initialization success!" << std::endl; //wypisuje menu
	std::cout << "SPACE - Add money" << std::endl; //wypisuje menu
	std::cout << "F10 - Add essence" << std::endl; //wypisuje menu
	std::cout << "F9 - Level + 1" << std::endl; //wypisuje menu
	std::cout << "F8 - Level - 1" << std::endl; //wypisuje menu
	std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl; //wypisuje menu

	Threads::threads_init(&mem); //Wywo³uje funkcjê threads_init z wskaŸnikiem do obiektu "mem" jako argumentem

	getchar(); //czeka na naciœniêcie klawisza (nie powinno tutaj byæ poniewa¿ od poprzedniej linijki program dzia³a w Treads.h)

    return 0;
}

