#include <Windows.h>
#include <tlhelp32.h>
#include <cstdio>

#pragma once

template<typename T> struct TArray;
struct SFXNameEntry;
class UObject;


#define LEx_MODULE_NAME     L"UDK"
#define LEx_NAME_ARRAY      0x3678F50       // RVA of the SFXName::GNameArray
#define LEx_OBJOBJECTS      0x3678F98       // RVA of the UObject::GObjObjects


class SDKInitializer
{
private:
    BYTE* ModuleBase;

    inline BYTE* GetModuleBaseAddress(wchar_t* moduleName)
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
                    if (moduleEntry.szModule == wcsstr(moduleEntry.szModule, moduleName))
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

    SDKInitializer()
    {
        ModuleBase = GetModuleBaseAddress(LEx_MODULE_NAME);
    }

public:

    inline struct TArray<struct FNameEntry*>* GetBioNameArray() const noexcept
    {
        return (struct TArray<struct FNameEntry*>*)(ModuleBase + LEx_NAME_ARRAY);
    }
    inline struct TArray<class UObject*>* GetObjects() const noexcept
    {
        return &*(struct TArray<class UObject*>*)(ModuleBase + LEx_OBJOBJECTS);
    }

    inline static SDKInitializer* Instance()
    {
        static SDKInitializer* initializer = nullptr;
        if (!initializer)
        {
            initializer = new SDKInitializer{};
        }
        return initializer;
    }
};
