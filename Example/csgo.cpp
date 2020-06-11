#include <iostream>
#include "EditMemory.h"

//simple triggerbot made with love and editmemory :p
//s/o to hazedumper https://github.com/frk1/hazedumper

int main()
{
	DWORD procId = GetProcId(L"csgo.exe");

	DWORD moduleBase = GetModuleBaseAddress(procId, L"client.dll");

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	DWORD localPlayer = moduleBase + 0xD36B94;

	std::vector<unsigned int> crosshairOffsets = { 0xB3D4 };

	uintptr_t crosshairId = FindDynamicAddr(handle, localPlayer, crosshairOffsets);

	while (true)
	{
		int currentCID = editmemory::ReadMem<int>(handle, (LPVOID)crosshairId);
		if (currentCID > 0 && currentCID < 64)
		{
			editmemory::WriteMem<int>(handle, LPVOID(moduleBase + 0x317C6EC), 5); // force player to shoot
			Sleep(20);
			editmemory::WriteMem<int>(handle, LPVOID(moduleBase + 0x317C6EC), 4);
			Sleep(10);
		}
		Sleep(1);
	}
}
