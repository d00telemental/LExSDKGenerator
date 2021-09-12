#include <Windows.h>
#include <stdio.h>

#include "../Common.h"


#pragma region SFXName stuff

#pragma pack(4)
template <typename T>
struct TArray
{
	T* Data;
	int Count;
	int Max;
};
typedef TArray<wchar_t> FString;

/** Packed index DWORD as seen in FNameEntry. */
struct PackedIndex
{
	DWORD			Offset : 20;	// The actual index, I guess???
	DWORD			Length : 9;		// Length of the AnsiName or WideName in symbols \wo null-terminator.
	DWORD			Bits : 3;		// Always 4 or 0. No idea wtf it really is, flags maybe?
};

#pragma pack(1)
/** Name as seen in some kind of name pool. */
struct FNameEntry
{
	PackedIndex		Index;			// 0x00
	FNameEntry*		HashNext;		// 0x04  Some pointer, often NULL.
	char			AnsiName[1];	// 0x0C  This *potentially* can be a widechar.
};

#pragma pack(1)
/** Name reference as seen in individual UObjects. */
struct FName
{
	DWORD			Offset : 29;	// Binary offset into an individual chunk.
	DWORD			Chunk : 3;		// Index of the chunk, I've only seen 0 or 1.
	signed long		Number;			// ?= InstanceIndex

	__forceinline
	char* Name() const noexcept
	{
		auto chunk = GBioNamePools[Chunk];
		auto entry = (FNameEntry*)((BYTE*)chunk + Offset);
		return entry->AnsiName;
	}

	static FNameEntry** GBioNamePools;
};
FNameEntry** FName::GBioNamePools;

void NameDump()
{
	FILE* logFile = NULL;
	fopen_s(&logFile, "NameDump.txt", "w+");
	if (!logFile) return;
	writeln(L"NameDump starting, addr = %p", FName::GBioNamePools);

	int poolCounter = 0;
	for (FNameEntry** namePool = reinterpret_cast<FNameEntry**>(FName::GBioNamePools);
		*namePool != nullptr;
		namePool++)
	{
		int entryCounter = 0;
		for (FNameEntry* nameEntry = *namePool;
			nameEntry->Index.Length != 0;
			nameEntry = reinterpret_cast<FNameEntry*>(reinterpret_cast<BYTE*>(nameEntry) + sizeof FNameEntry + nameEntry->Index.Length))
		{
			fwriteln(logFile, L"Name[%02d][%06d] %S", poolCounter, entryCounter, nameEntry->AnsiName);
			entryCounter++;
		}
		poolCounter++;
	}

	writeln(L"NameDump ending");
	fclose(logFile);
}

#pragma endregion


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
	FName				Name;                  // 0x48
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
	FName				Name;                  // 0x48
	UObject*			Class;                 // 0x50
	UObject*			ObjectArchetype;       // 0x58

#elif LE_GAME_INDEX == 3

#else

#error LE_GAME_INDEX not set for UObject!

#endif

	__forceinline
	char* GetName() const noexcept
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
			writeln(L"Object[%06d] %#p %d.%d_%d (%S)", i, obj, obj->Name.Chunk, obj->Name.Offset, obj->Name.Number, obj->GetName());
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
	FName::GBioNamePools = reinterpret_cast<FNameEntry**>(moduleBase + LEx_NAME_POOLS);
	UObject::GObjObjects = reinterpret_cast<TArray<UObject*>*>(moduleBase + LEx_OBJOBJECTS);
}
void OnAttach()
{
	Common::OpenConsole();
	Initialize();

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
