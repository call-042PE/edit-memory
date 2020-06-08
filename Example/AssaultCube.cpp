#include <iostream>
#include "EditMemory.h"

int main()
{
	DWORD procId = GetProcId(L"ac_client.exe");
	//getting procId.

	DWORD moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");
	//getting ModuleBase.

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
	//Opens an existing local process object. https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess

	DWORD localPlayer = moduleBase + 0x10F4F4;

	std::vector<unsigned int> ammoOffsets = { 0x150 };

	uintptr_t ammoAddr = FindDynamicAddr(handle, localPlayer, ammoOffsets);
	//finding dynamic address for reading/writing/patching it.

	editmemory::WriteMem<int>(handle, (LPVOID)ammoAddr, 1337);
	//writing to the ammoAddr 1337 value.

	while (true)
	{
		int currentAmmo = editmemory::ReadMem<int>(handle, (LPVOID)ammoAddr);
		//reading value in ammoAddr and stock it in currentAmmo integer.
		std::cout << currentAmmo << std::endl;
		//output currentAmmo integer value.
	}
}
