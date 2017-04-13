
#include "stdafx.h" 
#include "MemoryMg.h" 
#include "Threads.h"

using namespace std;

int main()
{
	SetConsoleTitle("Cichy Soda Dungeon trainer v2.3"); 
	MemoryMg mem("dungeon.exe"); 

	while (!mem.initialize()) 
	{
		Sleep(300); 
	}
	system("cls"); 
	std::cout << "initialization success!" << std::endl; 
	std::cout << "SPACE - Add money" << std::endl; 
	std::cout << "F10 - Add essence" << std::endl; 
	std::cout << "F9 - Level + 1" << std::endl; 
	std::cout << "F8 - Level - 1" << std::endl; 
	std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl; 

	Threads::threads_init(&mem); 

	getchar(); 

    return 0;
}

