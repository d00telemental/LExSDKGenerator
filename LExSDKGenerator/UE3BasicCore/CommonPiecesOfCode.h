#pragma once


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
