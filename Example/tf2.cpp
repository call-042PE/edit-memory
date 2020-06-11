#include <iostream>
#include "EditMemory.h"

//BunnyHop for tf2 made with editmemory ^^

int main()
{
	DWORD dw_LocalPlayer = 0x967F84;
	DWORD procId = GetProcId(L"hl2.exe");

	DWORD moduleBase = GetModuleBaseAddress(procId, L"server.dll");
	DWORD clientBase = GetModuleBaseAddress(procId, L"client.dll");

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	while (true)
	{
		uintptr_t localPlayer = moduleBase + dw_LocalPlayer;
		std::vector <unsigned int> m_Flags = { 0x3A0 };
		uintptr_t flag = FindDynamicAddr(handle, localPlayer, m_Flags);
		//if you don't know why i put 256 and 6 watch this video https://www.youtube.com/watch?v=igtUR9on0NE :p
		if (flag != 256 && GetAsyncKeyState(VK_SPACE))
		{
			editmemory::WriteMem<int>(handle, LPVOID(clientBase + 0xC692E0), 6);
			Sleep(25);
		}
		Sleep(1);
	}	
}
