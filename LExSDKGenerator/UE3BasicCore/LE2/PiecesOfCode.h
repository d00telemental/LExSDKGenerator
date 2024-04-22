/*
#############################################################################################
# Game: Mass Effect 2 (Legendary Edition)													#
# Version: 2.0.0.48602																		#
# ========================================================================================= #
# File: PiecesOfCode.h																		#
#############################################################################################
*/

#include "../CommonPiecesOfCode.h"


#define CLASS_PROPERTIES_UFIELD "\
    class UField*					SuperField;							// 0x0060 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UField*					Next;								// 0x0068 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UENUM "\
    class TArray<struct SFXName>    Names;                              // 0x0070 (0x10) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UCONST "\
    class FString                   Value;                              // 0x0070 (0x10) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_USTRUCT "\
    class UField*                   Children;                           // 0x0070 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    int                             PropertySize;                       // 0x0078 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    class TArray<BYTE>              Script;                             // 0x007C (0x10) - NOT AUTO-GENERATED PROPERTY \n\
    int                             MinAlignment;                       // 0x008C (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                RefLink;                            // 0x0090 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                PropertyLink;                       // 0x0098 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                ConfigLink;                         // 0x00A0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                ConstructorLink;                    // 0x00A8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                ComponentPropertyLink;              // 0x00B0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                TransientPropertyLink;              // 0x00B8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class TArray<class UObject>     ScriptObjectReferences;				// 0x00C0 (0x10) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_USCRIPTSTRUCT "\
    class FString                   DefaultStructPropText;              // 0x00D0 (0x10) - NOT AUTO-GENERATED PROPERTY \n\
    int                             StructFlags;                        // 0x00E0 (0x04) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UFUNCTION "\
    DWORD							FunctionFlags;						// 0x00D0 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    short							iNative;							// 0x00D4 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    short							RepOffset;							// 0x00D6 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    struct SFXName					FriendlyName;						// 0x00D8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    BYTE							OperPrecedence;						// 0x00E0 (0x01) - NOT AUTO-GENERATED PROPERTY \n\
    BYTE							NumParms;							// 0x00E1 (0x01) - NOT AUTO-GENERATED PROPERTY \n\
    unsigned short					ParmsSize;							// 0x00E2 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    short							ReturnValueOffset;					// 0x00E4 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    char							PaddingEE[2];						// 0x00E6 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    void*							FirstPropertyToInit;				// 0x00E8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    void*							Func;								// 0x00F0 (0x08) - NOT AUTO-GENERATED PROPERTY \n"

#define CLASS_PROPERTIES_USTATE "\
    QWORD                           ProbeMask;                          // 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    QWORD                           IgnoreMask;                         // 0x00D8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    DWORD                           StateFlags;                         // 0x00E0 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    WORD                            LabelTableOffset;                   // 0x00E4 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    TMap<SFXName, UFunction*>       FuncMap;                            // 0x00E8 (0x48) - NOT AUTO-GENERATED PROPERTY \n"

#define CLASS_PROPERTIES_UCLASS "\
\n\
    DWORD                           ClassFlags;                         // 0x0130 (0x04) - NOT AUTO-GENERATED PROPERTY\n\
    DWORD                           ClassCastFlags;                     // 0x0134 (0x04) - NOT AUTO-GENERATED PROPERTY\n\
    DWORD                           ClassUnique;                        // 0x0138 (0x04) - NOT AUTO-GENERATED PROPERTY\n\
    UClass*                         ClassWithin;                        // 0x013C (0x08) - NOT AUTO-GENERATED PROPERTY\n\
    SFXName                         ClassConfigName;                    // 0x0144 (0x08) - NOT AUTO-GENERATED PROPERTY\n\
    TArray<FRepRecord>              ClassReps;                          // 0x014C (0x10) - NOT AUTO-GENERATED PROPERTY\n\
    TArray<UField*>                 NetFields;                          // 0x015C (0x10) - NOT AUTO-GENERATED PROPERTY\n\
    UObject*                        ClassDefaultObject;                 // 0x016C (0x08) - NOT AUTO-GENERATED PROPERTY\n\
\n\
    unsigned char                   UnknownData174[ 0x84 ];             // 0x0174 (0x84) - UNKNOWN DATA\n"

#define CLASS_PROPERTIES_UPROPERTY "\
    int                             ArrayDim;                           // 0x0070 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    int                             ElementSize;                        // 0x0074 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    unsigned long long              PropertyFlags;                      // 0x0078 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    unsigned short                  RepOffset;                          // 0x0080 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    unsigned short                  RepIndex;                           // 0x0082 (0x02) - NOT AUTO-GENERATED PROPERTY \n\
    struct SFXName                  Category;                           // 0x0084 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UEnum*                    ArraySizeEnum;                      // 0x008C (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    int                             Offset;                             // 0x0094 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                PropertyLinkNext;                   // 0x0098 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                ConfigLinkNext;                     // 0x00A0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                ConstructorLinkNext;                // 0x00A8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                NextRef;                            // 0x00B0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                RepOwner;                           // 0x00B8 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                ComponentPropertyLinkNext;          // 0x00C0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                TransientPropertyLinkNext;          // 0x00C8 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UBYTEPROPERTY "\
    class UEnum*                    Enum;                               // 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UBOOLPROPERTY "\
    DWORD                           BitMask;                            // 0x00D0 (0x04) - NOT AUTO-GENERATED PROPERTY \n\
    DWORD                           Unknown0xD4;                        // 0x00D4 (0x04) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UDELEGATEPROPERTY "\
    class UFunction*                Function;                           // 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UFunction*                SourceDelegate;                     // 0x00D8 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UOBJECTPROPERTY "\
    class UClass*                   PropertyClass;                      // 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UCLASSPROPERTY "\
    class UClass*                   MetaClass;                          // 0x00D8 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UINTERFACEPROPERTY "\
    class UClass*                   InterfaceClass;                     // 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_USTRUCTPROPERTY "\
    class UStruct*                  Struct;                             // 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UARRAYPROPERTY "\
    class UProperty*                Inner;                              // 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n"


#define CLASS_PROPERTIES_UMAPPROPERTY "\
    class UProperty*                Key;                                // 0x00D0 (0x08) - NOT AUTO-GENERATED PROPERTY \n\
    class UProperty*                Value;                              // 0x00D8 (0x08) - NOT AUTO-GENERATED PROPERTY \n"
