#pragma once


#define CLASS_PROPERTIES_UOBJECT "\
    // void*                            VfTableObject;                      // 0x0000 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    int                             ObjectInternalInteger;              // 0x0008 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    unsigned long long              ObjectFlags;                        // 0x000C (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UObject*                  HashNext;                           // 0x0014 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UObject*                  HashOuterNext;                      // 0x001C (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    struct FStateFrame*             StateFrame;                         // 0x0024 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UObject*                  Linker;                             // 0x002C (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    long long                       LinkerIndex;                        // 0x0034 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    int                             NetIndex;                           // 0x003C (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    class UObject*                  Outer;                              // 0x0040 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    struct SFXName                  Name;                               // 0x0048 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UClass*                   Class;                              // 0x0050 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UObject*                  ObjectArchetype;                    // 0x0058 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define BASIC_FUNCTIONS_DEC "\
    static class TArray<class UObject*>* GObjObjects;\n\
\n\
    void AppendName(FString& OutString, SFXName::FormatMode Mode) const;\n\
    void AppendName(FStringRAII& OutString, SFXName::FormatMode Mode) const;\n\
    void AppendNameCPP(FString& OutString) const;\n\
    void AppendNameCPP(FStringRAII& OutString) const;\n\
    void AppendFullName(FString& OutString, SFXName::FormatMode Mode) const;\n\
    void AppendFullName(FStringRAII& OutString, SFXName::FormatMode Mode) const;\n\
\n\
    FStringRAII GetName() const;\n\
    FStringRAII GetNameCPP() const;\n\
    FStringRAII GetFullName() const;\n\
\n\
    FStringRAII const& StaticName() const;\n\
    FStringRAII const& StaticNameCPP() const;\n\
    FStringRAII const& StaticFullName() const;\n\
\n\
    template<class T> static T* FindObject (wchar_t const* const ObjectFullName) {\n\
        for ( int i = 0; i < (int)UObject::GObjObjects->Count(); ++i ) {\n\
            UObject* Object = UObject::GObjObjects->GetData()[ i ];\n\
            if ( ! Object || ! Object->IsA ( T::StaticClass() ) )\n\
                continue;\n\
            if ( Object->StaticFullName().Equals ( ObjectFullName, true ) )\n\
                return (T*) Object;\n\
        } \n\
        return NULL;\n\
    }\n\
\n\
    static class UClass* FindClass (wchar_t const* ClassFullName);\n\
    bool IsA(class UClass* pClass) const;\n\
\n\
    template<class T> bool IsA() const requires requires { T::StaticClass(); } {\n\
        return this->IsA(T::StaticClass());\n\
    }\n\
\n\
	template<std::derived_from<UObject> T> T* Cast() {\n\
		return this->IsA<T>() ? reinterpret_cast<T*>(this) : nullptr;\n\
	}\n\
\n\
	template<std::derived_from<UObject> T> T const* Cast() const {\n\
		return this->IsA<T>() ? reinterpret_cast<T const*>(this) : nullptr;\n\
	}\n\
\n\
	template<std::derived_from<UObject> T> T* CastDirect() requires requires { T::StaticClass(); } {\n\
		return this->Class == T::StaticClass() ? reinterpret_cast<T*>(this) : nullptr;\n\
	}\n\
\n\
	template<std::derived_from<UObject> T> T const* CastDirect() const requires requires { T::StaticClass(); } {\n\
		return this->Class == T::StaticClass() ? reinterpret_cast<T const*>(this) : nullptr;\n\
	}\n\
\n"



#define BASIC_FUNCTIONS_DEF "\
class TArray<class UObject*>* UObject::GObjObjects = nullptr;\n\
\n\
void UObject::AppendName(FString& OutString, SFXName::FormatMode const Mode) const {\n\
    ::LESDK::AppendObjectName(this, OutString, Mode);\n\
}\n\
\n\
void UObject::AppendName(FStringRAII& OutString, SFXName::FormatMode const Mode) const {\n\
    ::LESDK::AppendObjectName(this, OutString, Mode);\n\
}\n\
\n\
void UObject::AppendNameCPP(FString& OutString) const {\n\
    ::LESDK::AppendObjectNameCPP(this, OutString);\n\
}\n\
\n\
void UObject::AppendNameCPP(FStringRAII& OutString) const {\n\
    ::LESDK::AppendObjectNameCPP(this, OutString);\n\
}\n\
\n\
void UObject::AppendFullName(FString& OutString, SFXName::FormatMode const Mode) const {\n\
    ::LESDK::AppendObjectNameFull(this, OutString, Mode);\n\
}\n\
\n\
void UObject::AppendFullName(FStringRAII& OutString, SFXName::FormatMode const Mode) const {\n\
    ::LESDK::AppendObjectNameFull(this, OutString, Mode);\n\
}\n\
\n\
\n\
FStringRAII UObject::GetName() const {\n\
    FStringRAII OutString{};\n\
    OutString.Reserve(255);\n\
    AppendName(OutString, SFXName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
FStringRAII UObject::GetNameCPP() const {\n\
    FStringRAII OutString{};\n\
    OutString.Reserve(255);\n\
    AppendNameCPP(OutString);\n\
    return OutString;\n\
}\n\
\n\
FStringRAII UObject::GetFullName() const {\n\
    FStringRAII OutString{};\n\
    OutString.Reserve(255);\n\
    AppendFullName(OutString, SFXName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
\n\
FStringRAII const& UObject::StaticName() const {\n\
    thread_local FStringRAII OutString{};\n\
    OutString.Clear();\n\
    OutString.Reserve(255);\n\
    AppendName(OutString, SFXName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
FStringRAII const& UObject::StaticNameCPP() const {\n\
    thread_local FStringRAII OutString{};\n\
    OutString.Clear();\n\
    OutString.Reserve(255);\n\
    AppendNameCPP(OutString);\n\
    return OutString;\n\
}\n\
\n\
FStringRAII const& UObject::StaticFullName() const {\n\
    thread_local FStringRAII OutString{};\n\
    OutString.Clear();\n\
    OutString.Reserve(255);\n\
    AppendFullName(OutString, SFXName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
UClass* UObject::FindClass ( wchar_t const* ClassFullName ) \n\
{ \n\
    for ( int i = 0; i < (int)UObject::GObjObjects->Count(); ++i ) \n\
    { \n\
        UObject* Object = UObject::GObjObjects->GetData()[ i ]; \n\
\n\
        if ( ! Object ) \n\
            continue; \n\
\n\
        if ( Object->StaticFullName().Equals ( ClassFullName, true ) ) \n\
            return (UClass*) Object; \n\
    } \n\
\n\
    return NULL; \n\
} \n\
\n\
bool UObject::IsA ( UClass* pClass ) const \n\
{ \n\
    for ( UClass* SuperClass = this->Class; SuperClass; SuperClass = ( UClass* ) SuperClass->SuperField ) \n\
    { \n\
        if ( SuperClass == pClass ) \n\
            return true; \n\
    } \n\
\n\
    return false; \n\
} \n"
