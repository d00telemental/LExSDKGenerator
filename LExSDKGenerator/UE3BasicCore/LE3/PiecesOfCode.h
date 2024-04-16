/*
#############################################################################################
# Game: Mass Effect 3 (Legendary Edition)													#
# Version: 2.0.0.48602																		#
# ========================================================================================= #
# File: PiecesOfCode.h																		#
#############################################################################################
*/


#define BASIC_STRUCTS "\
template< class T > struct TArray \n\
{ \n\
public: \n\
    T* Data; \n\
    int Count; \n\
    int Max; \n\
\n\
public: \n\
    TArray() \n\
    { \n\
        Data = NULL; \n\
        Count = Max = 0; \n\
    }; \n\
\n\
public: \n\
    int Num() \n\
    { \n\
        return this->Count; \n\
    }; \n\
\n\
    const T& operator() ( int i ) const \n\
    { \n\
        return this->Data[ i ]; \n\
    }; \n\
\n\
}; \n\
\n\
struct PackedIndex \n\
{ \n\
DWORD Offset : 20; \n\
DWORD Length : 9; \n\
DWORD Bits : 3; \n\
}; \n\
\n\
#pragma pack(1)\n\
struct FNameEntry\n\
{\n\
    PackedIndex Index;\n\
    FNameEntry* HashNext;\n\
    char AnsiName[1];\n\
};\n\
\n\
#pragma pack(1)\n\
struct FName\n\
{\n\
    DWORD Offset : 29;\n\
    DWORD Chunk : 3;\n\
    signed long Number;\n\
\n\
    __forceinline char* GetName() const noexcept\n\
    {\n\
        auto chunk = SDKInitializer::Instance()->GetBioNamePools()[Chunk]; \n\
        auto entry = (FNameEntry*)((BYTE*)chunk + Offset);\n\
        return entry->AnsiName;\n\
    }\n\
\n\
    bool operator==(const FName& A) const noexcept\n\
    {\n\
        return Offset == A.Offset && Chunk == A.Chunk && Number == A.Number;\n\
    }\n\
\n\
    static bool TryFind(char* lookup, signed long instance, FName* outName)\n\
    {\n\
        auto gBioNamePools = SDKInitializer::Instance()->GetBioNamePools();\n\
        for (FNameEntry** namePool = reinterpret_cast<FNameEntry**>(gBioNamePools);\n\
                *namePool != nullptr;\n\
                namePool++)\n\
        {\n\
            for (FNameEntry* nameEntry = *namePool;\n\
                    nameEntry->Index.Length != 0;\n\
                    nameEntry = reinterpret_cast<FNameEntry*>(reinterpret_cast<BYTE*>(nameEntry) + sizeof FNameEntry + nameEntry->Index.Length))\n\
            {\n\
                if (!strcmp(lookup, nameEntry->AnsiName))\n\
                {\n\
                    FName name{};\n\
                    name.Offset = (DWORD)((unsigned long long)nameEntry - (unsigned long long)*namePool);\n\
                    name.Chunk = (DWORD)((unsigned long long)namePool - (unsigned long long)gBioNamePools);\n\
                    name.Number = instance;\n\
                    *outName = name;\n\
                    return true;\n\
                }\n\
            }\n\
        }\n\
        outName = nullptr;\n\
        return false;\n\
    }\n\
\n\
    FName() : Offset{ 0 }, Chunk{ 0 }, Number{ 0 } { }\n\
\n\
    FName(char* lookup, signed long instance = 0)\n\
        : Offset{ 0 }, Chunk{ 0 }, Number{ instance }\n\
    {\n\
        if (!TryFind(lookup, instance, this))\n\
        { \n\
            if (IsDebuggerPresent()) DebugBreak();\n\n\
            if (!strcmp(lookup, \"None\")) \n\
            {\n\
                MessageBoxW(nullptr, L\"FName lookup contstructor failed for 'None'!\", L\"LE3 SDK ERROR\", MB_OK | MB_ICONERROR);\n\
                exit(-1);\n\
            }\n\
            else \n\
            {\n\
                *this = FName{ \"None\", instance };\n\
            }\n\
        } \n\
    }\n\
};\n\
\n\
struct FString : public TArray<wchar_t>  { \n\
    FString() {}; \n\
\n\
    FString ( wchar_t* Other ) \n\
    { \n\
        this->Max = this->Count = *Other ? ( (int)wcslen ( Other ) + 1 ) : 0; \n\
\n\
        if ( this->Count ) \n\
            this->Data = Other; \n\
    }; \n\
\n\
    ~FString() {}; \n\
\n\
    FString operator = ( wchar_t* Other ) \n\
    { \n\
        if ( this->Data != Other ) \n\
        { \n\
            this->Max = this->Count = *Other ? ( (int)wcslen ( Other ) + 1 ) : 0; \n\
\n\
            if ( this->Count ) \n\
                this->Data = Other; \n\
        } \n\
\n\
        return *this; \n\
    }; \n\
}; \n\
\n\
struct FScriptDelegate \n\
{ \n\
    class UObject*		Object; \n\
    struct FName		FunctionName; \n\
}; \n"



#define BASIC_FUNCTIONS_DEC "\
    static class TArray<class UObject*>* GObjObjects; \n\
\n\
    char* GetName(); \n\
    char* GetNameCPP(); \n\
    char* GetFullName(); \n\
\n\
    template<class T> static T* FindObject (char* ObjectFullName); \n\
    static class UClass* FindClass (char* ClassFullName); \n\
\n\
    bool IsA(class UClass* pClass); \n\n"



#define BASIC_FUNCTIONS_DEF "\
class TArray<class UObject*>* UObject::GObjObjects = nullptr; \n\
\n\
char* UObject::GetName() \n\
{ \n\
    static char cOutBuffer[ 256 ]; \n\
\n\
    sprintf_s ( cOutBuffer, \"%%s\", this->Name.GetName() ); \n\
\n\
    return cOutBuffer; \n\
} \n\
\n\
char* UObject::GetNameCPP() \n\
{ \n\
    static char cOutBuffer[ 256 ]; \n\
\n\
    if ( this->IsA ( UClass::StaticClass() ) ) \n\
    { \n\
        UClass* pClass = (UClass*) this; \n\
        while ( pClass ) \n\
        { \n\
            if ( ! strcmp ( pClass->GetName(), \"Actor\" ) ) \n\
            { \n\
                strcpy_s ( cOutBuffer, \"A\" ); \n\
                break; \n\
            } \n\
            else if ( ! strcmp ( pClass->GetName(), \"Object\" ) ) \n\
            { \n\
                strcpy_s ( cOutBuffer, \"U\" ); \n\
                break; \n\
            } \n\
\n\
            pClass = (UClass*) pClass->SuperField; \n\
        } \n\
    } \n\
    else \n\
    { \n\
        strcpy_s ( cOutBuffer, \"F\" ); \n\
    } \n\
\n\
    strcat_s ( cOutBuffer, this->GetName() ); \n\
\n\
    return cOutBuffer; \n\
} \n\
\n\
char* UObject::GetFullName() \n\
{ \n\
    if ( this->Class && this->Outer ) \n\
    { \n\
        static char cOutBuffer[ 256 ]; \n\
\n\
        if ( this->Outer->Outer ) \n\
        { \n\
            strcpy_s ( cOutBuffer, this->Class->GetName() ); \n\
            strcat_s ( cOutBuffer, \" \" ); \n\
            strcat_s ( cOutBuffer, this->Outer->Outer->GetName() ); \n\
            strcat_s ( cOutBuffer, \".\" ); \n\
            strcat_s ( cOutBuffer, this->Outer->GetName() ); \n\
            strcat_s ( cOutBuffer, \".\" ); \n\
            strcat_s ( cOutBuffer, this->GetName() ); \n\
        } \n\
        else \n\
        { \n\
            strcpy_s ( cOutBuffer, this->Class->GetName() ); \n\
            strcat_s ( cOutBuffer, \" \" ); \n\
            strcat_s ( cOutBuffer, this->Outer->GetName() ); \n\
            strcat_s ( cOutBuffer, \".\" ); \n\
            strcat_s ( cOutBuffer, this->GetName() ); \n\
        } \n\
\n\
        return cOutBuffer; \n\
    } \n\
\n\
    return \"(null)\"; \n\
} \n\
\n\
template< class T > T* UObject::FindObject ( char* ObjectFullName ) \n\
{ \n\
    for ( int i = 0; i < UObject::GObjObjects->Num(); ++i ) \n\
    { \n\
        UObject* Object = UObject::GObjObjects->GetData()[ i ]; \n\
\n\
        // skip no T class objects \n\
        if \n\
        ( \n\
                ! Object \n\
            ||	! Object->IsA ( T::StaticClass() ) \n\
        ) \n\
            continue; \n\
\n\
        // check \n\
        if ( ! _stricmp ( Object->GetFullName(), ObjectFullName ) ) \n\
            return (T*) Object; \n\
    } \n\
\n\
    return NULL; \n\
} \n\
\n\
UClass* UObject::FindClass ( char* ClassFullName ) \n\
{ \n\
    for ( int i = 0; i < UObject::GObjObjects->Num(); ++i ) \n\
    { \n\
        UObject* Object = UObject::GObjObjects->GetData()[ i ]; \n\
\n\
        if ( ! Object ) \n\
            continue; \n\
\n\
        if ( ! _stricmp ( Object->GetFullName(), ClassFullName ) ) \n\
            return (UClass*) Object; \n\
    } \n\
\n\
    return NULL; \n\
} \n\
\n\
bool UObject::IsA ( UClass* pClass ) \n\
{ \n\
    for ( UClass* SuperClass = this->Class; SuperClass; SuperClass = ( UClass* ) SuperClass->SuperField ) \n\
    { \n\
        if ( SuperClass == pClass ) \n\
            return true; \n\
    } \n\
\n\
    return false; \n\
} \n"



#define CLASS_PROPERTIES_UFIELD "\
    class UField*					SuperField;							// 0x0060 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UField*					Next;								// 0x0068 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UENUM "\
    class TArray<struct SFXName>    Names;                              // 0x0070 (0x10) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UCONST "\
    class FString                   Value;                              // 0x0070 (0x10) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_USTRUCT "\
    class UField*					Children;							// 0x0070 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    int								PropertySize;						// 0x0078 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    class TArray<BYTE>				Script;								// 0x007C (0x10) - NOT AUTO-GENERATED PROPERTY \n\
    int								MinAlignment;						// 0x008C (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*					    RefLink;							// 0x0090 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*					    PropertyLink;						// 0x0098 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*					    ConfigLink;							// 0x00A0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*					    ConstructorLink;					// 0x00A8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*					    ComponentPropertyLink;				// 0x00B0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*					    TransientPropertyLink;				// 0x00B8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class TArray<class UObject>     ScriptObjectReferences;				// 0x00C0 (0x10) - NOT AUTO-GENERATED PROPERTY \n\
    void*							UnknownD0;							// 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_USCRIPTSTRUCT "\
    class FString                   DefaultStructPropText;              // 0x00D8 (0x10) - NOT AUTO-GENERATED PROPERTY \n\
    int                             StructFlags;                        // 0x00E8 (0x04) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UFUNCTION "\
    void*							Func;								// 0x00D8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    DWORD							FunctionFlags;						// 0x00E0 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    short							iNative;							// 0x00E4 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    short							ParmsSize;							// 0x00E6 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    short							ReturnValueOffset;					// 0x00E8 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    BYTE							NumParms;							// 0x00EA (0x01) - NOT AUTO-GENERATED PROPERTY \n\
    BYTE							OperPrecendence;					// 0x00EB (0x01) - NOT AUTO-GENERATED PROPERTY \n\
    void*							FirstPropertyToInit;				// 0x00EC (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UPROPERTY "\
    int                             ArrayDim;                           // 0x0070 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    int                             ElementSize;                        // 0x0074 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    unsigned long long              PropertyFlags;                      // 0x0078 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    unsigned short                  RepOffset;                          // 0x0080 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    unsigned short                  RepIndex;                           // 0x0082 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    struct SFXName                  Category;                           // 0x0084 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UEnum*                    ArraySizeEnum;                      // 0x008C (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    int                             Offset;                             // 0x0094 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*                      PropertyLinkNext;                   // 0x0098 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*                      ConfigLinkNext;                     // 0x00A0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*                      ConstructorLinkNext;                // 0x00A8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*                      NextRef;                            // 0x00B0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*                      RepOwner;                           // 0x00B8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*                      ComponentPropertyLinkNext;          // 0x00C0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    UProperty*                      TransientPropertyLinkNext;          // 0x00C8 (0x08) - NOT AUTO-GENERATED PROPERTY \n"
