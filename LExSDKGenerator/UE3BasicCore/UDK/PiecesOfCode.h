/*
#############################################################################################
# Game: Unreal Development Kit                                                              #
# Version: 2015-02                                                                          #
# ========================================================================================= #
# File: PiecesOfCode.h                                                                      #
#############################################################################################
*/


#define CLASS_PROPERTIES_UOBJECT "\
    //void*                           VfTableObject;                      // 0x0000 (0x08)\n\
    UObject*                        HashNext;                           // 0x0008 (0x08)\n\
    unsigned long long              ObjectFlags;                        // 0x0010 (0x08)\n\
    UObject*                        HashOuterNext;                      // 0x0018 (0x08)\n\
    void*                           StateFrame;                         // 0x0020 (0x08)\n\
    UObject*                        Linker;                             // 0x0028 (0x08)\n\
    void*                           LinkerIndex;                        // 0x0030 (0x08)\n\
    signed long                     ObjectInternalInteger;              // 0x0038 (0x04)\n\
    signed long                     NetIndex;                           // 0x003C (0x04)\n\
    UObject*                        Outer;                              // 0x0040 (0x08)\n\
    FName                           Name;                               // 0x0048 (0x08)\n\
    UClass*                         Class;                              // 0x0050 (0x08)\n\
    UObject*                        ObjectArchetype;                    // 0x0058 (0x08)\n\
"


#define BASIC_FUNCTIONS_DEC "\
    static class TArray<class UObject*>* GObjObjects;\n\
\n\
    void AppendName(FStringView& OutString, FName::FormatMode Mode) const;\n\
    void AppendName(FString& OutString, FName::FormatMode Mode) const;\n\
    void AppendNameCPP(FStringView& OutString) const;\n\
    void AppendNameCPP(FString& OutString) const;\n\
    void AppendFullName(FStringView& OutString, FName::FormatMode Mode) const;\n\
    void AppendFullName(FString& OutString, FName::FormatMode Mode) const;\n\
\n\
    FString GetName() const;\n\
    FString GetNameCPP() const;\n\
    FString GetFullName() const;\n\
\n\
    template<class T> static T* FindObject (wchar_t const* const ObjectFullName) {\n\
        for ( int i = 0; i < (int)UObject::GObjObjects->Count(); ++i ) {\n\
            UObject* Object = UObject::GObjObjects->GetData()[ i ];\n\
            if ( ! Object || ! Object->IsA ( T::StaticClass() ) )\n\
                continue;\n\
            if ( Object->GetFullName().Equals ( ObjectFullName, true ) )\n\
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
void UObject::AppendName(FStringView& OutString, FName::FormatMode const Mode) const {\n\
    ::UGHSDK::AppendObjectName(this, OutString, Mode);\n\
}\n\
\n\
void UObject::AppendName(FString& OutString, FName::FormatMode const Mode) const {\n\
    ::UGHSDK::AppendObjectName(this, OutString, Mode);\n\
}\n\
\n\
void UObject::AppendNameCPP(FStringView& OutString) const {\n\
    ::UGHSDK::AppendObjectNameCPP(this, OutString);\n\
}\n\
\n\
void UObject::AppendNameCPP(FString& OutString) const {\n\
    ::UGHSDK::AppendObjectNameCPP(this, OutString);\n\
}\n\
\n\
void UObject::AppendFullName(FStringView& OutString, FName::FormatMode const Mode) const {\n\
    ::UGHSDK::AppendObjectNameFull(this, OutString, Mode);\n\
}\n\
\n\
void UObject::AppendFullName(FString& OutString, FName::FormatMode const Mode) const {\n\
    ::UGHSDK::AppendObjectNameFull(this, OutString, Mode);\n\
}\n\
\n\
\n\
FString UObject::GetName() const {\n\
    FString OutString{};\n\
    OutString.Reserve(255);\n\
    AppendName(OutString, FName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
FString UObject::GetNameCPP() const {\n\
    FString OutString{};\n\
    OutString.Reserve(255);\n\
    AppendNameCPP(OutString);\n\
    return OutString;\n\
}\n\
\n\
FString UObject::GetFullName() const {\n\
    FString OutString{};\n\
    OutString.Reserve(255);\n\
    AppendFullName(OutString, FName::k_formatInstanced);\n\
    return OutString;\n\
}\n\
\n\
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
        if ( Object->GetFullName().Equals ( ClassFullName, true ) ) \n\
            return (UClass*) Object; \n\
    } \n\
\n\
    return NULL; \n\
} \n\
\n\
bool UObject::IsA ( UClass* pClass ) const \n\
{ \n\
    for ( UClass* SuperClass = this->Class; SuperClass; SuperClass = ( UClass* ) SuperClass->SuperStruct ) \n\
    { \n\
        if ( SuperClass == pClass ) \n\
            return true; \n\
    } \n\
\n\
    return false; \n\
} \n"


#define CLASS_PROPERTIES_UFIELD "\
    class UField*                   Next;                               // 0x0060 (0x08)\n\
"


#define CLASS_PROPERTIES_UENUM "\
    class TArray<struct FName>      Names;                              // 0x0068 (0x10)\n\
"


#define CLASS_PROPERTIES_UCONST "\
    class FString                   Value;                              // 0x0068 (0x10)\n\
"


#define CLASS_PROPERTIES_USTRUCT "\
    void*                           ScriptText;                         // 0x0068 (0x08)\n\
    void*                           CppText;                            // 0x0070 (0x08)\n\
    class UStruct*                  SuperStruct;                        // 0x0078 (0x08)\n\
    class UField*                   Children;                           // 0x0080 (0x08)\n\
    int                             PropertySize;                       // 0x0088 (0x04)\n\
    class TArray<BYTE>              Script;                             // 0x008C (0x10)\n\
    int                             TextPos;                            // 0x009C (0x04)\n\
    int                             Line;                               // 0x00A0 (0x04)\n\
    int                             MinAlignment;                       // 0x00A4 (0x04)\n\
    UProperty*                      RefLink;                            // 0x00A8 (0x08)\n\
    UProperty*                      PropertyLink;                       // 0x00B0 (0x08)\n\
    UProperty*                      ConstructorLink;                    // 0x00B8 (0x08)\n\
    class TArray<class UObject*>    ScriptObjectReferences;             // 0x00C0 (0x10)\n\
"


#define CLASS_PROPERTIES_USCRIPTSTRUCT "\
    class FString                   DefaultStructPropText;              // 0x00D0 (0x10)\n\
    int                             StructFlags;                        // 0x00E0 (0x04)\n\
    class TArray<BYTE>              StructDefaults;                     // 0x00E4 (0x10)\n\
"


#define CLASS_PROPERTIES_UFUNCTION "\
     DWORD                          FunctionFlags;                      // 0x00D0 (0x04)\n\
     WORD                           iNative;                            // 0x00D4 (0x02)\n\
     WORD                           RepOffset;                          // 0x00D6 (0x02)\n\
     FName                          FriendlyName;                       // 0x00D8 (0x08)\n\
     void*                          DllImportFunction;                  // 0x00E0 (0x08)\n\
     BYTE                           OperPrecedence;                     // 0x00E8 (0x01)\n\
     BYTE                           NumParms;                           // 0x00E9 (0x01)\n\
     WORD                           ParmsSize;                          // 0x00EA (0x02)\n\
     WORD                           ReturnValueOffset;                  // 0x00EC (0x02)\n\
     unsigned char                  Padding_EE[2];                      // 0x00EE (0x02)\n\
     UProperty*                     FirstStructWithDefaults;            // 0x00F0 (0x08)\n\
     void*                          Func;                               // 0x00F8 (0x08)\n\
"

#define CLASS_PROPERTIES_USTATE "\
     DWORD                          ProbeMask;                          // 0x00D0 (0x04)\n\
     DWORD                          StateFlags;                         // 0x00D4 (0x04)\n\
     WORD                           LabelTableOffset;                   // 0x00D8 (0x00)\n\
     unsigned char                  Padding[0x02];                      // 0x00DA (0x02)\n\
     TMap<FName, UFunction*>        FuncMap;                            // 0x00DC (0x48)\n\
"

#define CLASS_PROPERTIES_UCLASS "\
\n\
     DWORD                          ClassFlags;                         // 0x0124 (0x04)\n\
     DWORD                          ClassCastFlags;                     // 0x0128 (0x04)\n\
     INT                            ClassUnique;                        // 0x012C (0x04)\n\
     UClass*                        ClassWithin;                        // 0x0130 (0x08)\n\
     FName                          ClassConfigName;                    // 0x0138 (0x08)\n\
     TArray<void*>                  ClassReps;                          // 0x0140 (0x10)\n\
     TArray<UField*>                NetFields;                          // 0x0150 (0x10)\n\
     TArray<FName>                  HideCategories;                     // 0x0160 (0x10)\n\
     TArray<FName>                  AutoExpandCategories;               // 0x0170 (0x10)\n\
     TArray<FName>                  AutoCollapseCategories;             // 0x0180 (0x10)\n\
     TArray<FName>                  DontSortCategories;                 // 0x0190 (0x10)\n\
     TArray<FName>                  DependentOn;                        // 0x01A0 (0x10)\n\
     TArray<FName>                  ClassGroupNames;                    // 0x01B0 (0x10)\n\
     UINT                           bForceScriptOrder;                  // 0x01C0 (0x04)\n\
     FString                        ClassHeaderName;                    // 0x01C4 (0x10)\n\
     FName                          DllBindName;                        // 0x01D4 (0x08)\n\
     void*                          DllBindHandle;                      // 0x01DC (0x08)\n\
     UObject*                       ClassDefaultObject;                 // 0x01E4 (0x08)\n\
     void*                          ClassConstructor;                   // 0x01EC (0x08)\n\
     void*                          ClassStaticConstructor;             // 0x01F4 (0x08)\n\
     void*                          ClassStaticInitializer;             // 0x01FC (0x08)\n\
     TMap<FName, UObject*>          ComponentNameToDefaultObjectMap;    // 0x0204 (0x48)\n\
     TArray<void*>                  ImplementedInterfaces;              // 0x024C (0x10)\n\
     FString                        DefaultPropText;                    // 0x025C (0x10)\n\
     UINT                           bNeedsPropertiesLinked;             // 0x026C (0x04)\n\
     TArray<DWORD>                  ReferenceTokenStream;               // 0x0270 (0x10)\n\
"

#define CLASS_PROPERTIES_UPROPERTY "\
     int                            ArrayDim;                           // 0x0068 (0x04)\n\
     int                            ElementSize;                        // 0x006C (0x04)\n\
     unsigned long long             PropertyFlags;                      // 0x0070 (0x08)\n\
     unsigned short                 RepOffset;                          // 0x0078 (0x02)\n\
     unsigned short                 RepIndex;                           // 0x007A (0x02)\n\
     FName                          Category;                           // 0x007C (0x08)\n\
     UEnum*                         ArraySizeEnum;                      // 0x0084 (0x08)\n\
     int                            Offset;                             // 0x008C (0x04)\n\
     UProperty*                     PropertyLinkNext;                   // 0x0090 (0x08)\n\
     UProperty*                     ConstructorLinkNext;                // 0x0098 (0x08)\n\
     UProperty*                     NextRef;                            // 0x00A0 (0x08)\n\
"


#define CLASS_PROPERTIES_UBYTEPROPERTY "\
    class UEnum*                    Enum;                               // 0x00A8 (0x08)\n\
"


#define CLASS_PROPERTIES_UBOOLPROPERTY "\
    DWORD                           BitMask;                            // 0x00A8 (0xAC)\n\
"


#define CLASS_PROPERTIES_UDELEGATEPROPERTY "\
    class UFunction*                Function;                           // 0x00A8 (0x08)\n\
    class UFunction*                SourceDelegate;                     // 0x00B0 (0x08)\n\
"


#define CLASS_PROPERTIES_UOBJECTPROPERTY "\
    class UClass*                   PropertyClass;                      // 0x00A8 (0x08)\n\
"


#define CLASS_PROPERTIES_UCLASSPROPERTY "\
    class UClass*                   MetaClass;                          // 0x00B0 (0x08)\n\
"


#define CLASS_PROPERTIES_UINTERFACEPROPERTY "\
    class UClass*                   InterfaceClass;                     // 0x00A8 (0x08)\n\
"


#define CLASS_PROPERTIES_USTRUCTPROPERTY "\
    class UStruct*                  Struct;                             // 0x00A8 (0x08)\n\
"


#define CLASS_PROPERTIES_UARRAYPROPERTY "\
    class UProperty*                Inner;                              // 0x00A8 (0x08)\n\
"


#define CLASS_PROPERTIES_UMAPPROPERTY "\
    class UProperty*                Key;                                // 0x00A8 (0x08)\n\
    class UProperty*                Value;                              // 0x00B0 (0x08)\n\
"
