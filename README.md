# Edit-Memory
Edit Memory is a c++ module for helping beginners to start game hacking.

## How it work ?
This module have several functions for helping beginners to see how memory works in games.
We have many example on games such like AssaultCube,CSGO,GTA-SANANDREAS,etc...
With this module you can create simple game hack software and understand how memory/pointer/address works in game with less effort.

## What can i do with this ?
You can read/write address and patch instruction with simple function !

## Does this is undetectable ?
Huh...
Not really.
The module is based on function ReadProcessMemory and WriteProcessMemory these functions are well know by anticheat.

## Now, some example.

### Reading Process Memory
```cpp
#include <iostream>
#include "EditMemory.h"

int main()
{

	DWORD procId = GetProcId(L"ac_client.exe");

	DWORD moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	DWORD localPlayer = moduleBase + 0x10F4F4;

	std::vector<unsigned int> ammoOffsets = { 0x150 };

	uintptr_t ammoAddr = FindDynamicAddr(handle, localPlayer, ammoOffsets);

	while (true)
	{
		int currentAmmo = editmemory::ReadMem<int>(handle, (BYTE*)ammoAddr);
		std::cout << currentAmmo << std::endl;
	}
}
```

These are the required function for reading memory process.

### Writing Process Memory

When your understand how reading memory writing memory is not much harder.

```cpp
#include <iostream>
#include "EditMemory.h"

int main()
{

	DWORD procId = GetProcId(L"ac_client.exe");

	DWORD moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	DWORD localPlayer = moduleBase + 0x10F4F4;

	std::vector<unsigned int> ammoOffsets = { 0x150 };

	uintptr_t ammoAddr = FindDynamicAddr(handle, localPlayer, ammoOffsets);

	while (true)
	{
		int currentAmmo = editmemory::ReadMem<int>(handle, (BYTE*)ammoAddr);
		editmemory::WriteMem(handle, (BYTE*)ammoAddr, (BYTE*)1337);
		std::cout << currentAmmo << std::endl;
	}
}
```
See ? not much harder...
More at [Example](https://github.com/call-042PE/edit-memory/tree/master/Example)

### What are you waiting for ?
So now you have no excuse for not started game hacking !

## Credits
[GuidedHacking](https://guidedhacking.com/) to explain so well game hacking  :blush:
