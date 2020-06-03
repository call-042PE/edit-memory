#include "EditMemory.h"


DWORD GetProcId(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		//loop through all process
		if (Process32First(hSnap, &procEntry))
		{

			do
			{
				//compare current lopping process name with procName parameters
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	//close handle a return the procId of the process
	CloseHandle(hSnap);
	return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				//same thing that GetProcId but for module
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}


			} while (Module32Next(hSnap, &modEntry));
		}
	}
	//close handle a return moduleBaseAddress
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t FindDynamicAddr(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		//ReadProcessMemory pointer by pointer to get the dynamic address
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}

void editmemory::PatchMem(BYTE* lpAddress, BYTE* src, unsigned int sizeofinstruction, HANDLE hProcess)
{
	DWORD oldProtection;
	VirtualProtectEx(hProcess, lpAddress, sizeofinstruction, PROCESS_VM_READ | PROCESS_VM_WRITE, &oldProtection);
	WriteProcessMemory(hProcess, lpAddress, src, sizeofinstruction, 0);
	VirtualProtectEx(hProcess, lpAddress, sizeofinstruction, oldProtection, &oldProtection);
}

void editmemory::WriteMem(HANDLE handle, BYTE* addr, BYTE* Value)
{
	WriteProcessMemory(handle, addr, &Value, sizeof(Value), nullptr);
}