#include "../../../Common.h"

/*
#############################################################################################
# Game: Mass Effect 2 (Legendary Edition)													#
# Version: 2.0.0.48602																		#
# ========================================================================================= #
# File: GameDefines.h																		#
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
#define GAME_NAME				"Mass Effect 2 (Legendary Edition)"
#define GAME_NAME_S				"LE2"
#define GAME_VERSION			"2.0.0.48602"

// Game
#define CLASS_ALIGN				0x4

// ProcessEvent Sig
#define ProcessEvent_Pattern	"\x40\x55\x41\x56\x41\x57\x48\x81\xEC\x90\x00\x00\x00\x48\x8D\x6C\x24\x20"
#define ProcessEvent_Mask		"xxxxxxxxxxxxxxxxxx"

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
#define CCP_USTRINGREF
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
struct FNameEntry;
struct FName;


/*
# ========================================================================================= #
# Globals																					
# ========================================================================================= #
*/

TArray<UObject*>* GObjects = NULL;
FNameEntry** GBioNamePools = NULL;

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


/** Packed index DWORD as seen in FNameEntry. */
struct PackedIndex
{
	DWORD Offset : 20;  // The actual index, I guess???
	DWORD Length : 9;   // Length of the AnsiName or WideName in symbols \wo null-terminator.
	DWORD Bits : 3;     // Always 4 or 0. No idea wtf it really is, flags maybe?
};

#pragma pack(1)
/** Name as seen in some kind of name pool. */
struct FNameEntry
{
	PackedIndex Index;     // 0x00
	FNameEntry* HashNext;  // 0x04  Some pointer, often NULL.
	char AnsiName[1];      // 0x0C  This *potentially* can be a widechar.
};

#pragma pack(1)
/** Name reference as seen in individual UObjects. */
struct FName
{
	DWORD Offset : 29;  // Binary offset into an individual chunk.
	DWORD Chunk : 3;    // Index of the chunk, I've only seen 0 or 1.
	signed long Number;        // ?= InstanceIndex

	__forceinline
	char* GetName() const noexcept
	{
		auto chunk = GBioNamePools[Chunk];
		auto entry = (FNameEntry*)((BYTE*)chunk + Offset);
		return entry->AnsiName;
	}

	bool operator==(const FName& A) const noexcept
	{
		return Offset == A.Offset && Chunk == A.Chunk && Number == A.Number;
	}

	/** IDK if this actually works yet. */
	static bool TryFind(char* lookup, signed long instance, FName* outName)
	{
		for (FNameEntry** namePool = reinterpret_cast<FNameEntry**>(GBioNamePools);
			*namePool != nullptr;
			namePool++)
		{
			for (FNameEntry* nameEntry = *namePool;
				nameEntry->Index.Length != 0;
				nameEntry = reinterpret_cast<FNameEntry*>(reinterpret_cast<BYTE*>(nameEntry) + sizeof FNameEntry + nameEntry->Index.Length))
			{
				if (!strcmp(lookup, nameEntry->AnsiName))
				{
					FName name{};
					name.Offset = (DWORD)((unsigned long long)nameEntry - (unsigned long long)namePool);
					name.Chunk = (DWORD)((unsigned long long)namePool - (unsigned long long)GBioNamePools);
					name.Number = instance;
					*outName = name;
					return true;
				}
			}
		}
		outName = nullptr;
		return false;
	}
};


struct FScriptDelegate
{
	class UObject*		Object;
	struct FName		FunctionName;
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

// (0x0000 - 0x0060)
class UObject
{
public:
	void*					VfTableObject;							// 0x0000 (0x08)
	int						ObjectInternalInteger;					// 0x0008 (0x04)
	unsigned long long		ObjectFlags;                            // 0x000C (0x08)
	class UObject*			HashNext;                               // 0x0014 (0x08)
	class UObject*			HashOuterNext;                          // 0x001C (0x08)
	void*					StateFrame;                             // 0x0024 (0x08)
	class UObject*			Linker;                                 // 0x002C (0x08)
	long long				LinkerIndex;							// 0x0034 (0x08)
	int						NetIndex;                               // 0x003C (0x04)
	class UObject*			Outer;                                  // 0x0040 (0x08)
	struct FName			Name;                                   // 0x0048 (0x08)
	class UClass*			Class;                                  // 0x0050 (0x08)
	class UObject*			ObjectArchetype;						// 0x0058 (0x08)

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

	// (0x0060 - 0x0070)
	class UField : public UObject
	{
	public:
		class UField*		SuperField;									// 0x0060 (0x08)
		class UField*		Next;										// 0x0068 (0x08)

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

		// (0x0070 - 0x0080)
		class UEnum : public UField
		{
		public:
			TArray<FName>			Names;									// 0x0070 (0x10)

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

		// (0x0070 - 0x0080)
		class UConst : public UField
		{
		public:
			struct FString		Value;										// 0x0070 (0x10)													

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

		// (0x0070 - 0x00D0)
		class UStruct : public UField
		{
		public:
			class UField*					Children;							// 0x0070 (0x08)
			int								PropertySize;						// 0x0078 (0x04)
			struct TArray<BYTE>				Script;								// 0x007C (0x10)
			int								MinAlignment;						// 0x008C (0x04)
			void*							RefLink;							// 0x0090 (0x08)
			void*							PropertyLink;						// 0x0098 (0x08)
			void*							ConfigLink;							// 0x00A0 (0x08)
			void*							ConstructorLink;					// 0x00A8 (0x08)
			void*							ComponentPropertyLink;				// 0x00B0 (0x08)
			void*							TransientPropertyLink;				// 0x00B8 (0x08)
			struct TArray<class UObject>	ScriptObjectReferences;				// 0x00C0 (0x10)

		private:
			static UClass* pClassPointer;

		public:
			static UClass* StaticClass()
			{
				if ( ! pClassPointer )
					pClassPointer = UObject::FindClass ( "Class Core.Struct" );

				return pClassPointer;
			};
		};

			// (0x00D0 - 0x00E4)
			class UScriptStruct : public UStruct
			{
			public:
				struct FString		DefaultStructPropText;						// 0x00D0 (0x10)
				int					StructFlags;                                // 0x00E0 (0x04)

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

			// (0x00D0 - 0x0F8)
			class UFunction : public UStruct
			{
			public:
				DWORD				FunctionFlags;				// 0x00D0 (0x04)
				short				iNative;					// 0x00D4 (0x02)
				short				RepOffset;					// 0x00D6 (0x02)
				struct FName		FriendlyName;				// 0x00D8 (0x08)
				BYTE				OperPrecedence;				// 0x00E0 (0x01)
				BYTE				NumParms;					// 0x00E1 (0x01)
				unsigned short		ParmsSize;					// 0x00E2 (0x02)
				short				ReturnValueOffset;			// 0x00E4 (0x02)
				char				PaddingEE[2];				// 0x00E6 (0x02)
				void*				FirstPropertyToInit;		// 0x00E8 (0x08)
				void*				Func;						// 0x00F0 (0x08)

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

			// (0x00D0 - 0x0130)
			class UState : public UStruct
			{
			public:
				BYTE				UnknownD8[0x60];				// 0x00D0 (0x60)

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

				// (0x0130 - 0x01F8)
				class UClass : public UState
				{
				public:
					BYTE				UnknownData130[0xC8];			// 0x0130 (0xC8)

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

		// (0x0070 - 0x00D0)
		class UProperty : public UField 
		{
		public:
			int						ArrayDim;						//0x0070 (0x04)
			int						ElementSize;					//0x0074 (0x04)
			unsigned long long		PropertyFlags;					//0x0078 (0x08)
			unsigned short			RepOffset;						//0x0080 (0x02)
			unsigned short			RepIndex;						//0x0082 (0x02)
			struct FName			Category;						//0x0084 (0x08)
			class UEnum*			ArraySizeEnum;					//0x008C (0x08)
			int						Offset;							//0x0094 (0x04)
			void*					PropertyLinkNext;				//0x0098 (0x08)
			void*					ConfigLinkNext;					//0x00A0 (0x08)
			void*					ConstructorLinkNext;			//0x00A8 (0x08)
			void*					NextRef;						//0x00B0 (0x08)
			void*					RepOwner;						//0x00B8 (0x08)
			void*					ComponentPropertyLinkNext;		//0x00C0 (0x08)
			void*					TransientPropertyLinkNext;		//0x00C8 (0x08)

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

			// (0x00D0 - 0x00D8)
			class UByteProperty : public UProperty 
			{
			public:
				class UEnum*		Enum;						//0x00D0 (0x08)

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

			// (0x00D0 - 0x00D0)
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

			// (0x00D0 - 0x00D0)
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

			// (0x00D0 - 0x00D4)
			class UBoolProperty : public UProperty 
			{
			public:
				DWORD			BitMask;						// 0x00D0 (0x04)

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

			// (0x00D0 - 0x00D0)
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

			// (0x00D0 - 0x00D0)
			class UStringRefProperty : public UProperty 
			{
			public:

			private:
				static UClass* pClassPointer;

			public:
				static UClass* StaticClass()
				{
					if (!pClassPointer)
						pClassPointer = UObject::FindClass("Class Core.StringRefProperty");

					return pClassPointer;
				};
			};

			// (0x00D0 - 0x00D0)
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

			// (0x00D0 - 0x00E0)
			class UDelegateProperty : public UProperty 
			{
			public:
				class UFunction*		Function;								//0x00D0 (0x08)
				class UFunction*		SourceDelegate;							//0x00D8 (0x08)

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

			// (0x00D0 - 0x00D8)
			class UObjectProperty : public UProperty 
			{
			public:
				class UClass*		PropertyClass;								// 0x00D0 (0x08)

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

				// (0x00D8 - 0x00E0)
				class UClassProperty : public UObjectProperty 
				{
				public:
					class UClass*			MetaClass;							// 0x00D8 (0x08)

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

			// (0x00D0 - 0x00D8)
			class UInterfaceProperty : public UProperty
			{
			public:
				class UClass*			InterfaceClass;							// 0x00D0 (0x08)

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

			// (0x00D0 - 0x00D8)
			class UStructProperty : public UProperty 
			{
			public:
				class UStruct*			Struct;									// 0x00D0 (0x08)

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

			// (0x00D0 - 0x00D8)
			class UArrayProperty : public UProperty 
			{
			public:
				class UProperty*		Inner;									// 0x00D0 (0x08)

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

			// (0x00D0 - 0x00E0)
			class UMapProperty : public UProperty 
			{
			public:
				class UProperty*	Key;										// 0x00D0 (0x08)
				class UProperty*	Value;										// 0x00D8 (0x08)

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

UClass* UObject								::pClassPointer = NULL;  // +
UClass*		UField							::pClassPointer = NULL;  // +
UClass*			UEnum						::pClassPointer = NULL;  // +
UClass*			UConst						::pClassPointer = NULL;  // +
UClass*			UStruct						::pClassPointer = NULL;  // +
UClass*				UScriptStruct			::pClassPointer = NULL;  // +
UClass*				UFunction				::pClassPointer = NULL;  // +
UClass*				UState					::pClassPointer = NULL;  // +
UClass*					UClass				::pClassPointer = NULL;  // +
UClass*			UProperty					::pClassPointer = NULL;  // +
UClass*				UByteProperty			::pClassPointer = NULL;  // +
UClass*				UIntProperty			::pClassPointer = NULL;  // +
UClass*				UFloatProperty			::pClassPointer = NULL;  // +
UClass*				UBoolProperty			::pClassPointer = NULL;  // +
UClass*				UStrProperty			::pClassPointer = NULL;  // +
UClass*				UStringRefProperty		::pClassPointer = NULL;  // +
UClass*				UNameProperty			::pClassPointer = NULL;  // +
UClass*				UDelegateProperty		::pClassPointer = NULL;  // +
UClass*				UObjectProperty			::pClassPointer = NULL;  // +
UClass*					UClassProperty		::pClassPointer = NULL;  // +
UClass*				UInterfaceProperty		::pClassPointer = NULL;  // +
UClass*				UStructProperty			::pClassPointer = NULL;  // +
UClass*				UArrayProperty			::pClassPointer = NULL;  // +
UClass*				UMapProperty			::pClassPointer = NULL;  // +

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
	#pragma pack ( pop )
#endif