#include <iostream>
#include "EditMemory.h"

//patching memory to get unlimited ammo.

int main()
{
	DWORD procId = GetProcId(L"gta-sa.exe");

	DWORD moduleBase = GetModuleBaseAddress(procId, L"gta-sa.exe");

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	editmemory::PatchMem((BYTE*)moduleBase + 0x375B96, (BYTE*)"\x40", 1, handle);
	//patching memory to change dec eax to inc eax.
}
