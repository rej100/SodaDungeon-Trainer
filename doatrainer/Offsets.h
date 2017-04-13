#pragma once

#include "stdafx.h"
#include "MemoryMg.h"

namespace Offsets
{
	DWORD money = 0x0; //Adress hajsu
	DWORD essence = 0x0; //adres essencji
	DWORD lvl = 0x0; //adres poziomu
	
	void calc_money(MemoryMg *mem)
	{
		DWORD temp = 0x0;
		temp = mem->Read<DWORD>(mem->mainModuleBase + 0x4093E4);
		money = temp + 0x4;
	}
	void calc_essence(MemoryMg *mem)
	{
		DWORD temp = 0x0;
		temp = mem->Read<DWORD>(mem->mainModuleBase + 0x4093E4);
		essence = temp + 0x8;
	}
	void calc_lvl(MemoryMg *mem)
	{
		DWORD temp = 0x0;
		temp = mem->Read<DWORD>(mem->mainModuleBase + 0x40A9F4);
		lvl = temp + 0x9c;
		//std::cout << "of lvl" << lvl << std::endl;
		//std::cout << "of lvl" << mem->Read<int>(lvl) << std::endl;
	}
}