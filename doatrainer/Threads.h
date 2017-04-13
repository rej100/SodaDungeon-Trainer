#pragma once

#include "stdafx.h"
#include "Offsets.h"
#include "MemoryMg.h"


namespace Threads
{
	void add_money(MemoryMg *mem)
	{
		//std::cout << "started m" << std::endl;
		while (true) //niesko�czona p�tla
		{
			if (GetAsyncKeyState(VK_SPACE)) //je�eli spacja jest wci�ni�ta
			{
				
				int tempcash = 0;
				tempcash = mem->Read<int>(Offsets::money); //czyta z adresu hajsu ilo�c hajsu i zapisuje do temcash
				system("cls"); //Czy�ci ekran
				tempcash += 500000; //  dodaje do przedchwilom wyczytanego hajsu 500000
				mem->Write<int>(Offsets::money, tempcash); //Wpisuje do adresu hajsi tempcash kt�ry teraz jest o 500000 wi�kszy ni� by�;
				//ZAMIAST TEGO NA G�RZE MOG�O TU PO PROSTU BY� mem->Write<int>(Offsets::money, tempcash + 500000);

				//mog�o tam by� nawet mem->Write<int>(Offsets::money, (mem->Read<int>(Offsets::money)+ 500000);

				std::cout << "SPACE - Add money" << std::endl; //wy�wietla menu
				std::cout << "F10 - Add essence" << std::endl; //wy�wietla menu
				std::cout << "F9 - Level + 1" << std::endl; //wy�wietla menu
				std::cout << "F8 - Level - 1" << std::endl; //wy�wietla menu
				std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl;
				std::cout << "cash: " << tempcash << std::endl; //wy�wietla hajs
			}
			Sleep(50); //WA�NE ABY P�TLA NIE WYKONYWA�A SI� NIESKO�CZENIE SZYBKO BO ZFAJCZYSZ PROCESOR
		}
	}
	void add_essence(MemoryMg *mem)
	{
		//std::cout << "started e" << std::endl;
		while (true)
		{
			if (GetAsyncKeyState(VK_F10))
			{
				int tempessence = 0;
				tempessence = mem->Read<int>(Offsets::essence);
				system("cls");
				tempessence += 50000;
				mem->Write<int>(Offsets::essence, tempessence);

				//podobnie jak wy�ej, tutaj mog�o by� mem->Write<int>(Offsets::money, (mem->Read<int>(Offsets::money)+ 500000);
				std::cout << "SPACE - Add money" << std::endl;
				std::cout << "F10 - Add essence" << std::endl;
				std::cout << "F9 - Level + 1" << std::endl;
				std::cout << "F8 - Level - 1" << std::endl;
				std::cout << "F7 - Recalculate offsets, press if something doesn't work" << std::endl;
				std::cout << "essence: " << tempessence << std::endl;
			}
			Sleep(50); //WA�NE ABY P�TLA NIE WYKONYWA�A SI� NIESKO�CZENIE SZYBKO BO ZFAJCZYSZ PROCESOR
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
				//std::cout << "lvlb: " << templvl << std::endl;
				templvl++; //dodaje do level'u 1
				mem->Write<int>(Offsets::lvl, templvl); //nadpisuje level
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
				//std::cout << "lvlb: " << templvl << std::endl;
				templvl--; //odejmuje OD level'u 1
				if (templvl <= 0) //je�eli templvl jest mniejszy ni� 0
					templvl = 1; //ustaw templvl na 1
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
		Sleep(50); //WA�NE ABY P�TLA NIE WYKONYWA�A SI� NIESKO�CZENIE SZYBKO BO ZFAJCZYSZ PROCESOR
	}

	void rec_off(MemoryMg *mem) // Ponownie oblicza adresy, w tym haksie to najwa�niejsza �ecz poniewa� ta ca�a gra soda dungeon bardzo lubi je psu� podczas gry
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

				Offsets::calc_money(mem); //Ponownie wywo�uje calc money
				Offsets::calc_essence(mem); //..
				Offsets::calc_lvl(mem); //.

				std::cout << "Offsets recalculated!" << std::endl;
				Sleep(1000);
			}
			Sleep(50); //WA�NE ABY P�TLA NIE WYKONYWA�A SI� NIESKO�CZENIE SZYBKO BO ZFAJCZYSZ PROCESOR
		}
	}

	void threads_init(MemoryMg *mem) //funkcja kt�ra stworzy z g��wnych funkcji haksa Thready(te� nie wiem jak przet�umaczy�)
	{
		Offsets::calc_money(mem); //Wywo�anie funkcji wyliczj�cej adres hajsu wcze�niej zdeklarowanej i zdefiniowanej w Offsets.h 
		Offsets::calc_essence(mem); //Domy�l si�
		Offsets::calc_lvl(mem); //..

		std::thread money(add_money, mem); //Stworzenie Threadu z funkcji add_money
		std::thread essence(add_essence, mem); //Domy�l si�
		std::thread lvl(lvl_manip, mem); //..
		std::thread recoff(rec_off, mem); //.

		money.join(); //Czekanie a� thread money zako�czy pierwsz� iteracj�(a to si� nie stanie nigdy, tamta p�tla while nie ma tutaj znaczenia) Sam do ko�ca nie rozumiem tej funkcji ale dzia�a wi�c nie dmucha�
	}
}