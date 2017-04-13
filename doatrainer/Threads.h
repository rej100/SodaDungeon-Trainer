#pragma once

#include "stdafx.h"
#include "Offsets.h"
#include "MemoryMg.h"


namespace Threads
{
	void add_money(MemoryMg *mem)
	{
		while (true) 
		{
			if (GetAsyncKeyState(VK_SPACE)) 
			{
				
				int tempcash = 0;
				tempcash = mem->Read<int>(Offsets::money); 
				system("cls");
				tempcash += 500000; 
				mem->Write<int>(Offsets::money, tempcash);

				std::cout << "SPACE - Add money" << std::endl; 
				std::cout << "F10 - Add essence" << std::endl; 
				std::cout << "F9 - Level + 1" << std::endl; 
				std::cout << "F8 - Level - 1" << std::endl; 
				std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl;
				std::cout << "cash: " << tempcash << std::endl;
			}
			Sleep(50);
		}
	}
	void add_essence(MemoryMg *mem)
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_F10))
			{
				int tempessence = 0;
				tempessence = mem->Read<int>(Offsets::essence);
				system("cls");
				tempessence += 50000;
				mem->Write<int>(Offsets::essence, tempessence);

				std::cout << "SPACE - Add money" << std::endl;
				std::cout << "F10 - Add essence" << std::endl;
				std::cout << "F9 - Level + 1" << std::endl;
				std::cout << "F8 - Level - 1" << std::endl;
				std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl;
				std::cout << "essence: " << tempessence << std::endl;
			}
			Sleep(50);
		}
	}
	void lvl_manip(MemoryMg *mem)
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_F9))
			{
				int templvl = 0;
				templvl = mem->Read<int>(Offsets::lvl);
				system("cls");
				templvl++;
				mem->Write<int>(Offsets::lvl, templvl);
				std::cout << "SPACE - Add money" << std::endl;
				std::cout << "F10 - Add essence" << std::endl;
				std::cout << "F9 - Level + 1" << std::endl;
				std::cout << "F8 - Level - 1" << std::endl;
				std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl;

				std::cout << "lvl: " << templvl << std::endl;
				Sleep(250);
			}
			if (GetAsyncKeyState(VK_F8))
			{
				int templvl = 0;
				templvl = mem->Read<int>(Offsets::lvl);
				system("cls");
				templvl--; 
				if (templvl <= 0) 
					templvl = 1; 
				mem->Write<int>(Offsets::lvl, templvl);

				std::cout << "SPACE - Add money" << std::endl;
				std::cout << "F10 - Add essence" << std::endl;
				std::cout << "F9 - Level + 1" << std::endl;
				std::cout << "F8 - Level - 1" << std::endl;
				std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl;

				std::cout << "lvl: " << templvl << std::endl;
				Sleep(250);
			}
		}
		Sleep(50); 
	}

	void rec_off(MemoryMg *mem)
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_F7))
			{
				system("cls");
				std::cout << "SPACE - Add money" << std::endl;
				std::cout << "F10 - Add essence" << std::endl;
				std::cout << "F9 - Level + 1" << std::endl;
				std::cout << "F8 - Level - 1" << std::endl;
				std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl;

				std::cout << "Recalculating offsets.." << std::endl;

				Offsets::calc_money(mem);
				Offsets::calc_essence(mem);
				Offsets::calc_lvl(mem);

				std::cout << "Offsets recalculated!" << std::endl;
				Sleep(1000);
			}
			Sleep(50);
		}
	}

	void threads_init(MemoryMg *mem)
	{
		Offsets::calc_money(mem);
		Offsets::calc_essence(mem);
		Offsets::calc_lvl(mem);

		std::thread money(add_money, mem);
		std::thread essence(add_essence, mem); 
		std::thread lvl(lvl_manip, mem);
		std::thread recoff(rec_off, mem);

		money.join();
	}
}