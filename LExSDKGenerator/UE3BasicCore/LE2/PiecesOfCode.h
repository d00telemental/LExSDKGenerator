/*
#############################################################################################
# Game: Mass Effect 2 (Legendary Edition)													#
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
                MessageBoxW(nullptr, L\"FName lookup contstructor failed for 'None'!\", L\"LE2 SDK ERROR\", MB_OK | MB_ICONERROR);\n\
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
    static struct TArray<class UObject*>* GObjObjects(); \n\
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
struct TArray<class UObject*>* UObject::GObjObjects() \n\
{ \n\
    struct TArray<class UObject*>* ObjectArray = (struct TArray<class UObject*>*) SDKInitializer::Instance()->GetObjects(); \n\
    return ObjectArray; \n\
} \n\
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
    while ( ! UObject::GObjObjects() ) \n\
        Sleep ( 100 ); \n\
\n\
    for ( int i = 0; i < UObject::GObjObjects()->Count; ++i ) \n\
    { \n\
        UObject* Object = UObject::GObjObjects()->Data[ i ]; \n\
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
    while ( ! UObject::GObjObjects() ) \n\
        Sleep ( 100 ); \n\
\n\
    for ( int i = 0; i < UObject::GObjObjects()->Count; ++i ) \n\
    { \n\
        UObject* Object = UObject::GObjObjects()->Data[ i ]; \n\
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



#define CLASS_PROPERTIES_USTRUCT "\
    class UField*					Children;							// 0x0070 (0x08) \n\
    int								PropertySize;						// 0x0078 (0x04) \n\
    struct TArray<BYTE>				Script;								// 0x007C (0x10) \n\
    int								MinAlignment;						// 0x008C (0x04) \n\
    void*							RefLink;							// 0x0090 (0x08) \n\
    void*							PropertyLink;						// 0x0098 (0x08) \n\
    void*							ConfigLink;							// 0x00A0 (0x08) \n\
    void*							ConstructorLink;					// 0x00A8 (0x08) \n\
    void*							ComponentPropertyLink;				// 0x00B0 (0x08) \n\
    void*							TransientPropertyLink;				// 0x00B8 (0x08) \n\
    struct TArray<class UObject>	ScriptObjectReferences;				// 0x00C0 (0x10) \n"



#define CLASS_PROPERTIES_UFUNCTION "\
    DWORD							FunctionFlags;						// 0x00D0 (0x04) \n\
    short							iNative;							// 0x00D4 (0x02) \n\
    short							RepOffset;							// 0x00D6 (0x02) \n\
    struct FName					FriendlyName;						// 0x00D8 (0x08) \n\
    BYTE							OperPrecedence;						// 0x00E0 (0x01) \n\
    BYTE							NumParms;							// 0x00E1 (0x01) \n\
    unsigned short					ParmsSize;							// 0x00E2 (0x02) \n\
    short							ReturnValueOffset;					// 0x00E4 (0x02) \n\
    char							PaddingEE[2];						// 0x00E6 (0x02) \n\
    void*							FirstPropertyToInit;				// 0x00E8 (0x08) \n\
    void*							Func;								// 0x00F0 (0x08) \n"
