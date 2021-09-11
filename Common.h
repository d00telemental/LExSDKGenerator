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
#define LE_GAME_INDEX	1

/**
 * Base directory for SDK generation output.
 * Used as a base, an LE1/LE2/LE3 directory
 * will be created in this path.
 */
#define LE_BASE_OUTPUT  "D:\\Projects\\LExSDK\\"


namespace Common
{
    void OpenConsole();
    void CloseConsole();

    // loosely based on https://stackoverflow.com/q/26572459
    BYTE* GetModuleBaseAddress(wchar_t* moduleName);
}

#define writeln(msg,...) fwprintf_s(stdout, L"" msg "\n", __VA_ARGS__)
#define fwriteln(file,msg,...) fwprintf_s(file, L"" msg "\n", __VA_ARGS__)
