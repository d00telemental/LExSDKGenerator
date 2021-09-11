#pragma once
#include <windows.h>
#include <TlHelp32.h>

#include <cstdio>
#include <string>


//typedef unsigned char        BYTE;
//typedef signed short         short;
//typedef unsigned short       unsigned short;
//typedef signed long          signed long;
//typedef unsigned long        DWORD;
//typedef signed long long     long long;
//typedef unsigned long long   unsigned long long;
//typedef wchar_t              wchar;


namespace Common
{
    void OpenConsole();
    void CloseConsole();

    // loosely based on https://stackoverflow.com/q/26572459
    BYTE* GetModuleBaseAddress(wchar_t* moduleName);
}

#define writeln(msg,...) fwprintf_s(stdout, L"" msg "\n", __VA_ARGS__)
#define fwriteln(file,msg,...) fwprintf_s(file, L"" msg "\n", __VA_ARGS__)
