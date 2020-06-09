#include <iostream>
#include "EditMemory.h"

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
		int currentAmmo = editmemory::ReadMem<int>(handle, (LPVOID)crosshairId);
		if (currentAmmo > 0 && currentAmmo < 64)
		{
			editmemory::WriteMem<int>(handle, LPVOID(moduleBase + 0x317C6EC), 5);
			Sleep(20);
			editmemory::WriteMem<int>(handle, LPVOID(moduleBase + 0x317C6EC), 4);
			Sleep(10);
		}
	}
}
