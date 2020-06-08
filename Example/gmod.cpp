#include <iostream>
#include <Windows.h>
#include "EditMemory.h"
#include <string>
#include <thread>

void tp(HANDLE handle, uintptr_t tpX, uintptr_t tpY, uintptr_t tpZ)
{
    float x = 0;
    float y = 0;
    float z = 0;

    std::cout << "Please enter the following coordinates X Y Z:" << std::endl;

    int stop = 0;
    std::cin >> x;
    std::cin >> y;
    std::cin >> z;
    if (x && y && z == 999)
    {
        system("PAUSE");
    }

    int Xactuel = editmemory::ReadMem<float>(handle, (BYTE*)tpX);

    int Yactuel = editmemory::ReadMem<float>(handle, (BYTE*)tpY);

    int Zactuel = editmemory::ReadMem<float>(handle, (BYTE*)tpZ);

    editmemory::WriteMem<float>(handle, (LPVOID)tpX, x);

    editmemory::WriteMem<float>(handle, (LPVOID)tpY, y);

    editmemory::WriteMem<float>(handle, (LPVOID)tpZ, z);

    std::cout << Xactuel << std::endl;
    std::cout << Yactuel << std::endl;
    std::cout << Zactuel << std::endl;


}

int main()
{
    int choice;
    DWORD procID = GetProcId(L"hl2.exe");
    DWORD moduleBase = GetModuleBaseAddress(procID, L"server.dll");
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

    DWORD localPlayer = moduleBase + 0x8D1FB4;

    std::vector<unsigned int> Xoffsets = { 0x27C };
    std::vector<unsigned int> Yoffsets = { 0x280 };
    std::vector<unsigned int> Zoffsets = { 0x284 };

    uintptr_t tpX = FindDynamicAddr(handle, localPlayer, Xoffsets);
    uintptr_t tpY = FindDynamicAddr(handle, localPlayer, Yoffsets);
    uintptr_t tpZ = FindDynamicAddr(handle, localPlayer, Zoffsets);


    std::cout << "[1] TP HACK [*]" << std::endl;

    std::cin >> choice;

    if (choice == 1)
    {
        std::thread second(tp, handle, tpX, tpY, tpZ);
        second.join();
        main();
    }
    system("cls");
    return 0;
}


