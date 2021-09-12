#pragma once
#include <windows.h>
#include <TlHelp32.h>

#include <cstdio>
#include <string>


// IL and SdkGen settings.
// ========================================

/**
 * Index of LE game, starting with 1.
 * Launcher not supported for obvious reasons.
 */
#define LE_GAME_INDEX	2

/**
 * Base directory for SDK generation output.
 * Used as a base, an LE1/LE2/LE3 directory
 * will be created in this path.
 */
#define LE_BASE_OUTPUT  "D:\\Projects\\LExSDK\\"


#if LE_GAME_INDEX == 1

#define LEx_MODULE_NAME		L"MassEffect1.exe"
#define LEx_NAME_POOLS		0x16A2090       // RVA of the name pools
#define LEx_OBJOBJECTS		0x1770670       // RVA of the UObject::ObjObjects

#elif LE_GAME_INDEX == 2

#define LEx_MODULE_NAME		L"MassEffect2.exe"
#define LEx_NAME_POOLS		0x1668A10
#define LEx_OBJOBJECTS		0x173CC48

#elif LE_GAME_INDEX == 3

#define LEx_MODULE_NAME		L"MassEffect3.exe"
#define LEx_NAME_POOLS		0x0000000
#define LEx_OBJOBJECTS		0x0000000

#else

#error LE_GAME_INDEX not set for Common.h!

#endif


namespace Common
{
    void OpenConsole();
    void CloseConsole();

    // loosely based on https://stackoverflow.com/q/26572459
    BYTE* GetModuleBaseAddress(wchar_t* moduleName);
}

#define writeln(msg,...) fwprintf_s(stdout, L"" msg "\n", __VA_ARGS__)
#define fwriteln(file,msg,...) fwprintf_s(file, L"" msg "\n", __VA_ARGS__)
