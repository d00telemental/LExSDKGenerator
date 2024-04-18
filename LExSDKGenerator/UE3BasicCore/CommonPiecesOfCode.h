#pragma once


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
    bool IsA(class UClass* pClass) const;\n\n"



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
    OutString.Reserve(256);\n\
    AppendName(OutString, SFXName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
FStringRAII UObject::GetNameCPP() const {\n\
    FStringRAII OutString{};\n\
    OutString.Reserve(256);\n\
    AppendNameCPP(OutString);\n\
    return OutString;\n\
}\n\
\n\
FStringRAII UObject::GetFullName() const {\n\
    FStringRAII OutString{};\n\
    OutString.Reserve(256);\n\
    AppendFullName(OutString, SFXName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
\n\
FStringRAII const& UObject::StaticName() const {\n\
    thread_local FStringRAII OutString{};\n\
    OutString.Reserve(256);\n\
    AppendName(OutString, SFXName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
FStringRAII const& UObject::StaticNameCPP() const {\n\
    thread_local FStringRAII OutString{};\n\
    OutString.Reserve(256);\n\
    AppendNameCPP(OutString);\n\
    return OutString;\n\
}\n\
\n\
FStringRAII const& UObject::StaticFullName() const {\n\
    thread_local FStringRAII OutString{};\n\
    OutString.Reserve(256);\n\
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
