#pragma once
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

namespace editmemory
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
}

DWORD GetProcId(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);