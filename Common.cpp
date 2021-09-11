#pragma once
#include "Common.h"

void Common::OpenConsole()
{
    AllocConsole();

    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(console, &lpConsoleScreenBufferInfo);
    SetConsoleScreenBufferSize(console, { lpConsoleScreenBufferInfo.dwSize.X, 30000 });
}

void Common::CloseConsole()
{
    FreeConsole();
}

// loosely based on https://stackoverflow.com/q/26572459
BYTE* Common::GetModuleBaseAddress(wchar_t* moduleName)
{
    auto pid = GetCurrentProcessId();

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    BYTE* baseAddress = nullptr;

    if (INVALID_HANDLE_VALUE != snapshot)
    {
        MODULEENTRY32 moduleEntry = { 0 };
        moduleEntry.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(snapshot, &moduleEntry))
        {
            do
            {
                if (0 == wcscmp(moduleEntry.szModule, moduleName))
                {
                    baseAddress = moduleEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(snapshot, &moduleEntry));
        }
        CloseHandle(snapshot);
    }

    return baseAddress;
}
