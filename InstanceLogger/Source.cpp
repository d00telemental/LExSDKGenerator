#include <cassert>
#include <Windows.h>
#include <stdio.h>

#include "../Common.h"


#pragma pack(4)
template <typename T>
struct TArray
{
    T* Data;
    int Count;
    int Max;
};

typedef TArray<wchar_t> FString;


#pragma region FName stuff
#if LE_GAME_INDEX == 2015

struct FNameEntry
{
    UINT64          Flags;
    UINT32          HashIndex : 31;
    UINT32          bUnicode : 1;
    FNameEntry*     HashNext;

    union
    {
        char        AnsiName[1];
        wchar_t     UnicodeName[1];
    };
};

struct FName
{
    UINT32          Index;
    INT32           Number;

    __forceinline FNameEntry const* Entry() const noexcept
    {
        return GNameArray->Data[Index];
    }

    __forceinline bool IsUnicode() const noexcept
    {
        return Entry()->bUnicode;
    }

    __forceinline char const* Name() const noexcept
    {
        FNameEntry const* const entry = Entry();
        return entry->AnsiName;
    }

    static TArray<FNameEntry*>* GNameArray;
};
TArray<FNameEntry*>* FName::GNameArray = nullptr;

#endif
#pragma endregion


#pragma region SFXName stuff
#if LE_GAME_INDEX != 2015

/** Packed index DWORD as seen in SFXNameEntry. */
struct SFXPackedIndex
{
    DWORD			Offset : 20;	// The actual index, I guess???
    DWORD			Length : 9;		// Length of the AnsiName or WideName in symbols \wo null-terminator.
    DWORD			Bits : 3;		// Always 4 or 0. No idea wtf it really is, flags maybe?
};

#pragma pack(1)
/** Name as seen in some kind of name pool. */
struct SFXNameEntry
{
    SFXPackedIndex  Index;			// 0x00
    SFXNameEntry*   HashNext;		// 0x04  Some pointer, often NULL.
    char			AnsiName[1];	// 0x0C  This *potentially* can be a widechar.
};

#pragma pack(1)
/** Name reference as seen in individual UObjects. */
struct SFXName
{
    DWORD			Offset : 29;	// Binary offset into an individual chunk.
    DWORD			Chunk : 3;		// Index of the chunk, I've only seen 0 or 1.
    signed long		Number;			// ?= InstanceIndex

    __forceinline char const* Name() const noexcept
    {
        auto chunk = GBioNamePools[Chunk];
        auto entry = (SFXNameEntry const*)((BYTE*)chunk + Offset);
        return entry->AnsiName;
    }

    static SFXNameEntry** GBioNamePools;
};
SFXNameEntry** SFXName::GBioNamePools = nullptr;

#endif
#pragma endregion


void NameDump()
{
    FILE* logFile = NULL;
    fopen_s(&logFile, "NameDump.txt", "w+");
    if (!logFile) return;

#if LE_GAME_INDEX == 2015

    writeln(L"NameDump starting, addr = %p", FName::GNameArray);

    for (int i = 0; i < FName::GNameArray->Count; i++)
    {
        if (FName::GNameArray->Data[i] == nullptr) continue;

        if (!FName::GNameArray->Data[i]->bUnicode)
        {
            fwriteln(logFile, L"Name[%04d] %S", i, &FName::GNameArray->Data[i]->AnsiName[0]);
        }
        else
        {
            fwriteln(logFile, L"Name[%04d] %s", i, &FName::GNameArray->Data[i]->UnicodeName[0]);
        }
    }

#else

    writeln(L"NameDump starting, addr = %p", SFXName::GBioNamePools);

    int poolCounter = 0;
    for (SFXNameEntry** namePool = reinterpret_cast<SFXNameEntry**>(SFXName::GBioNamePools);
        *namePool != nullptr;
        namePool++)
    {
        int entryCounter = 0;
        for (SFXNameEntry* nameEntry = *namePool;
            nameEntry->Index.Length != 0;
            nameEntry = reinterpret_cast<SFXNameEntry*>(reinterpret_cast<BYTE*>(nameEntry) + sizeof SFXNameEntry + nameEntry->Index.Length))
        {
            fwriteln(logFile, L"Name[%02d][%06d] %S", poolCounter, entryCounter, nameEntry->AnsiName);
            entryCounter++;
        }
        poolCounter++;
    }

#endif

    writeln(L"NameDump ending");
    fclose(logFile);
}


#pragma region Object stuff

#pragma pack(4)
struct UObject
{
#if LE_GAME_INDEX == 1

    void*				VfTableObject;         // 0x00
    signed long			ObjectInternalIndex;   // 0x08
    unsigned long long	ObjectFlags;           // 0x0C
    UObject*			HashNext;              // 0x14
    UObject*			HashOuterNext;         // 0x1C
    void*				StateFrame;            // 0x24
    void*				Linker;                // 0x2C
    void*				LinkerIndex;           // 0x34
    signed long			NetIndex;              // 0x3C
    UObject*			Outer;                 // 0x40
    SFXName             Name;                  // 0x48
    UObject*			Class;                 // 0x50
    UObject*			ObjectArchetype;       // 0x58

#elif LE_GAME_INDEX == 2

    void*				VfTableObject;         // 0x00
    signed long			ObjectInternalIndex;   // 0x08
    unsigned long long	ObjectFlags;           // 0x0C
    UObject*			HashNext;              // 0x14
    UObject*			HashOuterNext;         // 0x1C
    void*				StateFrame;            // 0x24
    void*				Linker;                // 0x2C
    void*				LinkerIndex;           // 0x34
    signed long			NetIndex;              // 0x3C
    UObject*			Outer;                 // 0x40
    SFXName             Name;                  // 0x48
    UObject*			Class;                 // 0x50
    UObject*			ObjectArchetype;       // 0x58

#elif LE_GAME_INDEX == 3

    void*				VfTableObject;         // 0x00
    signed long			ObjectInternalIndex;   // 0x08
    unsigned long long	ObjectFlags;           // 0x0C
    UObject*			HashNext;              // 0x14
    UObject*			HashOuterNext;         // 0x1C
    void*				StateFrame;            // 0x24
    void*				Linker;                // 0x2C
    void*				LinkerIndex;           // 0x34
    signed long			NetIndex;              // 0x3C
    UObject*			Outer;                 // 0x40
    SFXName             Name;                  // 0x48
    UObject*			Class;                 // 0x50
    UObject*			ObjectArchetype;       // 0x58

#elif LE_GAME_INDEX == 2015

    void*               VfTableObject;
    UObject*            HashNext;
    unsigned long long  ObjectFlags;
    UObject*            HashOuterNext;
    void*               StateFrame;
    void*               Linker;
    void*               LinkerIndex;
    signed long         ObjectInternalIndex;
    signed long         NetIndex;
    UObject*            Outer;
    FName               Name;
    UObject*            Class;
    UObject*            ObjectArchetype;

#else

#error LE_GAME_INDEX not set for UObject!

#endif

    __forceinline char const* GetName() const noexcept
    {
        return Name.Name();
    }

    static TArray<UObject*>* GObjObjects;
};
TArray<UObject*>* UObject::GObjObjects;

void ObjectDump()
{
    FILE* logFile = NULL;
    fopen_s(&logFile, "ObjectDump.txt", "w+");
    if (!logFile) return;
    writeln(L"ObjectDump starting, addr = %p", UObject::GObjObjects);
    writeln(L"ObjectDump - GObjObjects->Count = %d", UObject::GObjObjects ? UObject::GObjObjects->Count : -1);

    for (int i = 0; i < UObject::GObjObjects->Count; i++)
    {
        auto obj = UObject::GObjObjects->Data[i];
        if (obj)
        {
            //writeln(L"Object[%06d] %#p %d.%d_%d (%S)", i, obj, obj->Name.Chunk, obj->Name.Offset, obj->Name.Number, obj->GetName());
            fwriteln(logFile, L"Object[%06d] %-50S 0x%p", i, obj->GetName(), obj);
        }
        else
        {
            fwriteln(logFile, L"Object[%06d] (nullptr) 0x%p", i, obj);
        }
    }

    writeln(L"ObjectDump ending");
    fclose(logFile);
}
#pragma endregion


void Initialize()
{
    BYTE* moduleBase = Common::GetModuleBaseAddress(LEx_MODULE_NAME);
    UObject::GObjObjects = reinterpret_cast<TArray<UObject*>*>(moduleBase + LEx_OBJOBJECTS);

#if LE_GAME_INDEX == 1 || LE_GAME_INDEX == 2 || LE_GAME_INDEX == 3
    SFXName::GBioNamePools = reinterpret_cast<SFXNameEntry**>(moduleBase + LEx_NAME_POOLS);
    //FName::GNameArray = nullptr;
#elif LE_GAME_INDEX == 2015
    //SFXName::GBioNamePools = nullptr;
    FName::GNameArray = reinterpret_cast<TArray<FNameEntry*>*>(moduleBase + LEx_NAME_ARRAY);
#endif
}
void OnAttach()
{
    Common::OpenConsole();
    Initialize();

    writeln(L"UObject::GObjObjects: Data = %p, Count = %d, Max = %d", UObject::GObjObjects->Data, UObject::GObjObjects->Count, UObject::GObjObjects->Max);
    writeln(L"FName::GNameArray: Data = %p, Count = %d, Max = %d", FName::GNameArray->Data, FName::GNameArray->Count, FName::GNameArray->Max);
    std::fflush(stdout);

    NameDump();
    ObjectDump();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OnAttach, NULL, 0, NULL);
        return true;
        break;

    case DLL_PROCESS_DETACH:
        Common::CloseConsole();
        return true;
        break;
    }
}
