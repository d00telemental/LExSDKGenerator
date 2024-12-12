#include "../../../Common.h"

/*
#############################################################################################
# Game: Unreal Development Kit                                                              #
# Version: 2015-02                                                                          #
# ========================================================================================= #
# File: GameDefines.h                                                                       #
#############################################################################################
*/

#ifdef _MSC_VER
    #pragma pack ( push, 0x4 )
#endif

/*
# ========================================================================================= #
# Defines
# ========================================================================================= #
*/

// Info
#define GAME_NAME				"Unreal Development Kit"
#define GAME_NAME_S				"UDK"
#define GAME_VERSION			"2015-02"

// Game
#define CLASS_ALIGN				0x4

// ProcessEvent Sig
#define ProcessEvent_Pattern	"\x40\x55\x41\x55\x41\x56\x48\x81\xEC\xC0\x00\x00\x00"
#define ProcessEvent_Mask		"xxxxxxxxxxxxx"

// UE3 Tables Sigs

// Function Flags (incomplete)
#define FUNC_Final				0x00000001
#define FUNC_Latent				0x00000008				// ???
#define FUNC_Simulated			0x00000100				// ???
#define FUNC_Exec				0x00000200
#define FUNC_Native				0x00000400
#define FUNC_Event				0x00000800

// Property Flags
#define	CPF_Edit				0x0000000000000001		// Property is user-settable in the editor.
#define	CPF_Const				0x0000000000000002		// Actor's property always matches class's default actor property.
#define CPF_Input				0x0000000000000004		// Variable is writable by the input system.
#define CPF_ExportObject		0x0000000000000008		// Object can be exported with actor.
#define CPF_OptionalParm		0x0000000000000010		// Optional parameter (if CPF_Param is set).
#define CPF_Net					0x0000000000000020		// Property is relevant to network replication.
#define CPF_EditConstArray		0x0000000000000040		// Prevent adding/removing of items from dynamic a array in the editor.
#define CPF_Parm				0x0000000000000080		// Function/When call parameter.
#define CPF_OutParm				0x0000000000000100		// Value is copied out after function call.
#define CPF_SkipParm			0x0000000000000200		// Property is a short-circuitable evaluation function parm.
#define CPF_ReturnParm			0x0000000000000400		// Return value.
#define CPF_CoerceParm			0x0000000000000800		// Coerce args into this function parameter.
#define CPF_Native      		0x0000000000001000		// Property is native: C++ code is responsible for serializing it.
#define CPF_Transient   		0x0000000000002000		// Property is transient: shouldn't be saved, zero-filled at load time.
#define CPF_Config      		0x0000000000004000		// Property should be loaded/saved as permanent profile.
#define CPF_Localized   		0x0000000000008000		// Property should be loaded as localizable text.
#define CPF_Travel      		0x0000000000010000		// Property travels across levels/servers.
#define CPF_EditConst   		0x0000000000020000		// Property is uneditable in the editor.
#define CPF_GlobalConfig		0x0000000000040000		// Load config from base class, not subclass.
#define CPF_Component			0x0000000000080000		// Property containts component references.
#define CPF_NeedCtorLink		0x0000000000400000		// Fields need construction/destruction.
#define CPF_NoExport    		0x0000000000800000		// Property should not be exported to the native class header file.
#define CPF_NoClear				0x0000000002000000		// Hide clear (and browse) button.
#define CPF_EditInline			0x0000000004000000		// Edit this object reference inline.
#define CPF_EdFindable			0x0000000008000000		// References are set by clicking on actors in the editor viewports.
#define CPF_EditInlineUse		0x0000000010000000		// EditInline with Use button.
#define CPF_Deprecated  		0x0000000020000000		// Property is deprecated.  Read it from an archive, but don't save it.
#define CPF_EditInlineNotify	0x0000000040000000		// EditInline, notify outer object on editor change.
#define CPF_RepNotify			0x0000000100000000		// Notify actors when a property is replicated
#define CPF_Interp				0x0000000200000000		// interpolatable property for use with matinee
#define CPF_NonTransactional	0x0000000400000000		// Property isn't transacted

// Property SubClasses
#define CCP_UBYTE
#define CCP_UINT
#define CCP_UFLOAT
#define CCP_UBOOL
#define CCP_USTR
#define CCP_UNAME
#define CCP_UDELEGATE
#define CCP_UOBJECT
#define CCP_UCLASS
#define CCP_UINTERFACE
#define CCP_USTRUCT
#define CCP_UARRAY
#define CCP_UMAP

/*
# ========================================================================================= #
# Convenience forward decls
# ========================================================================================= #
*/

template< class T > struct TArray;
class UObject;
struct SFXNameEntry;
struct SFXName;


/*
# ========================================================================================= #
# Globals
# ========================================================================================= #
*/

TArray<UObject*>* GObjects = NULL;
SFXNameEntry** GBioNamePools = NULL;

/*
# ========================================================================================= #
# Structs
# ========================================================================================= #
*/

template< class T > struct TArray
{
public:
    T* Data;
    int Count;
    int Max;

public:
    TArray()
    {
        Data = NULL;
        Count = Max = 0;
    };

public:
    int Num()
    {
        return this->Count;
    };

    T& operator() ( int i )
    {
        return this->Data[ i ];
    };

    const T& operator() ( int i ) const
    {
        return this->Data[ i ];
    };
};
struct FString : public TArray<wchar_t> { };


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

    __forceinline char const* GetName() const noexcept
    {
        FNameEntry const* const entry = Entry();
        return entry->AnsiName;
    }

    static TArray<FNameEntry*>* GNameArray;
};
TArray<FNameEntry*>* FName::GNameArray = nullptr;


struct FScriptDelegate
{
    class UObject*      Object;
    struct FName        FunctionName;
};

struct FQWord
{
    int A;
    int B;
};

/*
# ========================================================================================= #
# Classes
# ========================================================================================= #
*/

class UClass;

// (0x0000 - 0x0060)
class UObject
{
public:
    void*                       VfTableObject;              // 0x0000 (0x08)
    UObject*                    HashNext;                   // 0x0008 (0x08)
    unsigned long long          ObjectFlags;                // 0x0010 (0x08)
    UObject*                    HashOuterNext;              // 0x0018 (0x08)
    void*                       StateFrame;                 // 0x0020 (0x08)
    UObject*                    Linker;                     // 0x0028 (0x08)
    void*                       LinkerIndex;                // 0x0030 (0x08)
    signed long                 ObjectInternalInteger;      // 0x0038 (0x04)
    signed long                 NetIndex;                   // 0x003C (0x04)
    UObject*                    Outer;                      // 0x0040 (0x08)
    FName                       Name;                       // 0x0048 (0x08)
    UClass*                     Class;                      // 0x0050 (0x08)
    UObject*                    ObjectArchetype;            // 0x0058 (0x08)

private:
    static UClass* pClassPointer;

public:
    static TArray<UObject*>* GObjObjects();

    char* GetName();
    char* GetNameCPP();
    char* GetFullName();
    char* GetPackageName();
    UObject* GetPackageObj();

    template<class T> static T* FindObject(char* ObjectFullName);
    template<class T> static unsigned int CountObject(char* ObjectName);
    static UClass* FindClass (char* ClassFullName);

    bool IsA (UClass* pClass);

    static UClass* StaticClass()
    {
        if (!pClassPointer)
            pClassPointer = UObject::FindClass("Class Core.Object");

        return pClassPointer;
    };
};

    // (0x0060 - 0x0068)
    class UField : public UObject
    {
    public:
        class UField*		Next;										// 0x0060 (0x08)

    private:
        static UClass* pClassPointer;

    public:
        static UClass* StaticClass()
        {
            if (!pClassPointer)
                pClassPointer = UObject::FindClass("Class Core.Field");

            return pClassPointer;
        };
    };

        // (0x0068 - 0x0078)
        class UEnum : public UField
        {
        public:
            TArray<FName>			Names;									// 0x0068 (0x10)

        private:
            static UClass* pClassPointer;

        public:
            static UClass* StaticClass()
            {
                if (!pClassPointer)
                    pClassPointer = UObject::FindClass ("Class Core.Enum");

                return pClassPointer;
            };
        };

        // (0x0068 - 0x0078)
        class UConst : public UField
        {
        public:
            struct FString		Value;										// 0x0068 (0x10)

        private:
            static UClass* pClassPointer;

        public:
            static UClass* StaticClass()
            {
                if (!pClassPointer)
                    pClassPointer = UObject::FindClass("Class Core.Const");

                return pClassPointer;
            };
        };

        class UProperty;

        // (0x0068 - 0x00D0)
        class UStruct : public UField
        {
        public:
            void*                           ScriptText;                         // 0x0068 (0x08)
            void*                           CppText;                            // 0x0070 (0x08)
            class UStruct*                  SuperStruct;                        // 0x0078 (0x08)
            class UField*					Children;							// 0x0080 (0x08)
            int								PropertySize;						// 0x0088 (0x04)
            struct TArray<BYTE>				Script;								// 0x008C (0x10)
            int                             TextPos;                            // 0x009C (0x04)
            int                             Line;                               // 0x00A0 (0x04)
            int								MinAlignment;						// 0x00A4 (0x04)
            UProperty*					    RefLink;							// 0x00A8 (0x08)
            UProperty*                      PropertyLink;                       // 0x00B0 (0x08)
            UProperty*                      ConstructorLink;                    // 0x00B8 (0x08)
            struct TArray<class UObject*>   ScriptObjectReferences;				// 0x00C0 (0x10)

        private:
            static UClass* pClassPointer;

        public:
            static UClass* StaticClass()
            {
                if ( ! pClassPointer )
                    pClassPointer = UObject::FindClass ( "Class Core.Struct" );

                return pClassPointer;
            };

            inline class UStruct* GetSuper() { return SuperStruct; }
        };

            // (0x00D0 - 0x00F4)
            class UScriptStruct : public UStruct
            {
            public:
                struct FString		DefaultStructPropText;						// 0x00D0 (0x10)
                int					StructFlags;                                // 0x00E0 (0x04)
                struct TArray<BYTE> StructDefaults;                             // 0x00E4 (0x10)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass ("Class Core.ScriptStruct");

                    return pClassPointer;
                };
            };

            // (0x00D0 - 0x0100)
            #pragma pack(1)
            class UFunction : public UStruct
            {
            public:
                DWORD               FunctionFlags;              // 0x00D0 (0x04)
                WORD                iNative;                    // 0x00D4 (0x02)
                WORD                RepOffset;                  // 0x00D6 (0x02)
                FName               FriendlyName;               // 0x00D8 (0x08)
                void*               DllImportFunction;          // 0x00E0 (0x08)
                BYTE                OperPrecedence;             // 0x00E8 (0x01)
                BYTE                NumParms;                   // 0x00E9 (0x01)
                WORD                ParmsSize;                  // 0x00EA (0x02)
                WORD                ReturnValueOffset;          // 0x00EC (0x02)
                unsigned char       Padding_EE[2];              // 0x00EE (0x02)
                UProperty*          FirstStructWithDefaults;    // 0x00F0 (0x08)
                void*               Func;                       // 0x00F8 (0x08)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass ( "Class Core.Function" );

                    return pClassPointer;
                };
            };

            // (0x00D0 - 0x0124)
            class UState : public UStruct
            {
            public:
                DWORD               ProbeMask;                  // 0x00D0 (0x04)
                DWORD               StateFlags;                 // 0x00D4 (0x04)
                WORD                LabelTableOffset;           // 0x00D8 (0x00)
                unsigned char       Padding[0x02];              // 0x00DA (0x02)
                unsigned char       FuncMap[0x48];              // 0x00DC (0x48)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if ( ! pClassPointer )
                        pClassPointer = UObject::FindClass ( "Class Core.State" );

                    return pClassPointer;
                };
            };

                // (0x0124 - 0x0280)
                class UClass : public UState
                {
                public:
                    DWORD               ClassFlags;                     // 0x0124 (0x04)
                    DWORD               ClassCastFlags;                 // 0x0128 (0x04)
                    INT                 ClassUnique;                    // 0x012C (0x04)
                    UClass*             ClassWithin;                    // 0x0130 (0x08)
                    FName               ClassConfigName;                // 0x0138 (0x08)
                    TArray<void*>       ClassReps;                      // 0x0140 (0x10)
                    TArray<UField*>     NetFields;                      // 0x0150 (0x10)
                    TArray<FName>       HideCategories;                 // 0x0160 (0x10)
                    TArray<FName>       AutoExpandCategories;           // 0x0170 (0x10)
                    TArray<FName>       AutoCollapseCategories;         // 0x0180 (0x10)
                    TArray<FName>       DontSortCategories;             // 0x0190 (0x10)
                    TArray<FName>       DependentOn;                    // 0x01A0 (0x10)
                    TArray<FName>       ClassGroupNames;                // 0x01B0 (0x10)
                    UINT                bForceScriptOrder;              // 0x01C0 (0x04)
                    FString             ClassHeaderName;                // 0x01C4 (0x10)
                    FName               DllBindName;                    // 0x01D4 (0x08)
                    void*               DllBindHandle;                  // 0x01DC (0x08)
                    UObject*            ClassDefaultObject;             // 0x01E4 (0x08)
                    void*               ClassConstructor;               // 0x01EC (0x08)
                    void*               ClassStaticConstructor;         // 0x01F4 (0x08)
                    void*               ClassStaticInitializer;         // 0x01FC (0x08)
                    unsigned char       ComponentNameToDefaultObjectMap[0x48]; // 0x0204 (0x48)
                    TArray<void*>       ImplementedInterfaces;          // 0x024C (0x10)
                    FString             DefaultPropText;                // 0x025C (0x10)
                    UINT                bNeedsPropertiesLinked;         // 0x026C (0x04)
                    TArray<DWORD>       ReferenceTokenStream;           // 0x0270 (0x10)

                private:
                    static UClass* pClassPointer;

                public:
                    static UClass* StaticClass()
                    {
                        if ( ! pClassPointer )
                            pClassPointer = UObject::FindClass ( "Class Core.Class" );

                        return pClassPointer;
                    };
                };

                static_assert(offsetof(UClass, ClassConfigName) == 0x0138);
                static_assert(offsetof(UClass, DllBindHandle) == 0x01DC);
                static_assert(offsetof(UClass, ComponentNameToDefaultObjectMap) == 0x0204);
                static_assert(offsetof(UClass, ReferenceTokenStream) == 0x0270);

        // (0x0068 - 0x00A8)
        class UProperty : public UField
        {
        public:
            int						ArrayDim;						// 0x0068 (0x04)
            int						ElementSize;					// 0x006C (0x04)
            unsigned long long		PropertyFlags;					// 0x0070 (0x08)
            unsigned short			RepOffset;						// 0x0078 (0x02)
            unsigned short			RepIndex;						// 0x007A (0x02)
            FName			        Category;						// 0x007C (0x08)
            UEnum*			        ArraySizeEnum;					// 0x0084 (0x08)
            int						Offset;							// 0x008C (0x04)
            UProperty*				PropertyLinkNext;				// 0x0090 (0x08)
            UProperty*				ConstructorLinkNext;			// 0x0098 (0x08)
            UProperty*				NextRef;						// 0x00A0 (0x08)

        private:
            static UClass* pClassPointer;

        public:
            static UClass* StaticClass()
            {
                if (!pClassPointer )
                    pClassPointer = UObject::FindClass("Class Core.Property");

                return pClassPointer;
            };
        };

            // (0x00A8 - 0x00B0)
            class UByteProperty : public UProperty
            {
            public:
                class UEnum*		Enum;						// 0x00A8 (0x08)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.ByteProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00A8)
            class UIntProperty : public UProperty
            {
            public:

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.IntProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00A8)
            class UFloatProperty : public UProperty
            {
            public:

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.FloatProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00AC)
            class UBoolProperty : public UProperty
            {
            public:
                DWORD			BitMask;						// 0x00A8 (0xAC)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.BoolProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00A8)
            class UStrProperty : public UProperty
            {
            public:

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.StrProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00A8)
            class UNameProperty : public UProperty
            {
            public:

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.NameProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00B8)
            class UDelegateProperty : public UProperty
            {
            public:
                class UFunction*		Function;								// 0x00A8 (0x08)
                class UFunction*		SourceDelegate;							// 0x00B0 (0x08)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.DelegateProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00B0)
            class UObjectProperty : public UProperty
            {
            public:
                class UClass*		PropertyClass;								// 0x00A8 (0x08)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.ObjectProperty");

                    return pClassPointer;
                };
            };

                // (0x00B0 - 0x00B8)
                class UClassProperty : public UObjectProperty
                {
                public:
                    class UClass*			MetaClass;							// 0x00B0 (0x08)

                private:
                    static UClass* pClassPointer;

                public:
                    static UClass* StaticClass()
                    {
                        if (!pClassPointer)
                            pClassPointer = UObject::FindClass("Class Core.ClassProperty");

                        return pClassPointer;
                    };
                };

            // (0x00A8 - 0x00B0)
            class UInterfaceProperty : public UProperty
            {
            public:
                class UClass*			InterfaceClass;							// 0x00A8 (0x08)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.InterfaceProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00B0)
            class UStructProperty : public UProperty
            {
            public:
                class UStruct*			Struct;									// 0x00A8 (0x08)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.StructProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00B0)
            class UArrayProperty : public UProperty
            {
            public:
                class UProperty*		Inner;									// 0x00A8 (0x08)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.ArrayProperty");

                    return pClassPointer;
                };
            };

            // (0x00A8 - 0x00B8)
            class UMapProperty : public UProperty
            {
            public:
                class UProperty*	Key;										// 0x00A8 (0x08)
                class UProperty*	Value;										// 0x00B0 (0x08)

            private:
                static UClass* pClassPointer;

            public:
                static UClass* StaticClass()
                {
                    if (!pClassPointer)
                        pClassPointer = UObject::FindClass("Class Core.MapProperty");

                    return pClassPointer;
                };
            };

/*
# ========================================================================================= #
# Init Core Classes Pointers
# ========================================================================================= #
*/

UClass* UObject								::pClassPointer = NULL;
UClass*		UField							::pClassPointer = NULL;
UClass*			UEnum						::pClassPointer = NULL;
UClass*			UConst						::pClassPointer = NULL;
UClass*			UStruct						::pClassPointer = NULL;
UClass*				UScriptStruct			::pClassPointer = NULL;
UClass*				UFunction				::pClassPointer = NULL;
UClass*				UState					::pClassPointer = NULL;
UClass*					UClass				::pClassPointer = NULL;
UClass*			UProperty					::pClassPointer = NULL;
UClass*				UByteProperty			::pClassPointer = NULL;
UClass*				UIntProperty			::pClassPointer = NULL;
UClass*				UFloatProperty			::pClassPointer = NULL;
UClass*				UBoolProperty			::pClassPointer = NULL;
UClass*				UStrProperty			::pClassPointer = NULL;
//UClass*				UStringRefProperty		::pClassPointer = NULL;
UClass*				UNameProperty			::pClassPointer = NULL;
UClass*				UDelegateProperty		::pClassPointer = NULL;
UClass*				UObjectProperty			::pClassPointer = NULL;
UClass*					UClassProperty		::pClassPointer = NULL;
UClass*				UInterfaceProperty		::pClassPointer = NULL;
UClass*				UStructProperty			::pClassPointer = NULL;
UClass*				UArrayProperty			::pClassPointer = NULL;
UClass*				UMapProperty			::pClassPointer = NULL;

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
    #pragma pack ( pop )
#endif
