#pragma once
#include <windows.h>
#include <TlHelp32.h>

#include <cstdio>
#include <string>


// IL and SdkGen settings.
// ========================================

#if LE_GAME_INDEX == 1

#define LEx_MODULE_NAME		L"MassEffect1"
#define LEx_NAME_POOLS		0x16A2090       // RVA of the name pools
#define LEx_OBJOBJECTS		0x1770670       // RVA of the UObject::ObjObjects

#elif LE_GAME_INDEX == 2

#define LEx_MODULE_NAME		L"MassEffect2"
#define LEx_NAME_POOLS		0x1668A10       // RVA of the name pools
#define LEx_OBJOBJECTS		0x173CC48       // RVA of the UObject::ObjObjects

#elif LE_GAME_INDEX == 3

#define LEx_MODULE_NAME		L"MassEffect3"
#define LEx_NAME_POOLS		0x17B33D0       // RVA of the name pools
#define LEx_OBJOBJECTS		0x1887E40       // RVA of the UObject::ObjObjects

#else

#error LE_GAME_INDEX not set for Common.h!

#endif


namespace Common
{
    void OpenConsole();
    void CloseConsole();

    // loosely based on https://stackoverflow.com/q/26572459
    BYTE* GetModuleBaseAddress(wchar_t* moduleName);

    // support non-standard executable names by assuming that the first module is always what we want.
    BYTE* GetFirstModuleBaseAddress();
}

#define writeln(msg,...) fwprintf_s(stdout, L"" msg "\n", __VA_ARGS__)
#define fwriteln(file,msg,...) fwprintf_s(file, L"" msg "\n", __VA_ARGS__)
