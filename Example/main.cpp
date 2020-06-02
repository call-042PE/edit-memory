#include "EditMemory.h"
#include <vector>
#include <iostream>

int main()
{
	int ammo = 0;
	int newAmmo = 1337;
	DWORD procID = GetProcId(L"ac_client.exe");
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	//Opens an existing local process object. https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess
	uintptr_t moduleBase = GetModuleBaseAddress(procID, L"ac_client.exe");
	uintptr_t localPlayer = moduleBase + 0x10F4F4;
	std::vector<unsigned int> ammoOffsets = { 0x150 };
	uintptr_t ammoaddr = FindDynamicAddr(handle, localPlayer, ammoOffsets);
	while (TRUE)
	{
		//ReadProcessMemory(handle, (BYTE*)ammoaddr, &ammo, sizeof(ammo), nullptr);
		//WriteProcessMemory(handle, (BYTE*)ammoaddr, &newammo, sizeof(ammoaddr), nullptr);
		ammo = editmemory::ReadMem<int>(handle, (BYTE*)ammoaddr);
		std::cout << ammo << std::endl;
		editmemory::WriteMem(handle, (BYTE*)ammoaddr, (BYTE*)newAmmo);
	}
}