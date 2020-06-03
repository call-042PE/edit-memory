#include <iostream>
#include "EditMemory.h"

int main()
{
	bool flyActived = false;

	DWORD procId = GetProcId(L"ac_client.exe");

	DWORD moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	DWORD localPlayer = moduleBase + 0x10F4F4;

	std::vector<unsigned int> ammoOffsets = { 0x150 };

	uintptr_t ammoAddr = FindDynamicAddr(handle, localPlayer, ammoOffsets);

	editmemory::WriteMem(handle, (BYTE*)ammoAddr, (BYTE*)1337);

	while (true)
	{
		int currentAmmo = editmemory::ReadMem<int>(handle, (BYTE*)ammoAddr);
		std::cout << currentAmmo << std::endl;
	}
}