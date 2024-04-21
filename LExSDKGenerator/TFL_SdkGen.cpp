/*
#############################################################################################
# TheFeckless UE3 SDK Generator v1.4_Beta-Rev.53-MELE
# ========================================================================================= #
# File: TFL_SdkGen.cpp																		
# ========================================================================================= #
# Credits: uNrEaL, Tamimego, SystemFiles, R00T88, _silencer, the1domo, K@N@VEL				
# Thanks: HOOAH07, lowHertz																	
# Forums: www.uc-forum.com, www.gamedeception.net											
# ========================================================================================= #
# This work is licensed under the															
# Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.				
# To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/	
# or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View,		
# California, 94041, USA.																	
############################################################################################# 
*/

#include "TFL_SdkGen.h"

/*
# ========================================================================================= #
# Print Code														
# ========================================================================================= #
*/

void PrintFileHeder ( char* cFileName, char* cFileExt, bool setPP = false, bool isFunctions = false )
{
    fprintf ( pFile, "/*\n" );
    fprintf ( pFile, "#############################################################################################\n" );
    fprintf ( pFile, "# %s (%s) SDK\n", GAME_NAME, GAME_VERSION );
    fprintf ( pFile, "# Generated with TheFeckless UE3 SDK Generator %s\n", SDK_GEN_VER );
    fprintf ( pFile, "# ========================================================================================= #\n" );
    fprintf ( pFile, "# File: %s.%s\n", cFileName, cFileExt );
    fprintf ( pFile, "# ========================================================================================= #\n" );
    fprintf ( pFile, "# Credits: %s\n", SDK_GEN_CREDITS );
    fprintf ( pFile, "# Thanks: %s\n", SDK_GEN_STHANKS );
    fprintf ( pFile, "# Forums: %s\n", SDK_GEN_FORUMS );
    fprintf ( pFile, "#############################################################################################\n" );
    fprintf ( pFile, "*/\n" );
    fprintf  (pFile, "\n\n" );

    if ( ! isFunctions )
    {
        fprintf ( pFile, "#pragma once\n" );
    }
    else
    {
        if ( ! strcmp ( cFileName, "Core_functions" ) )
        {
            fprintf ( pFile, "#include <cstdio>\n" );
            fprintf ( pFile, "#include <cstring>\n" );
            fprintf ( pFile, "\n" );
        }

        fprintf ( pFile, "#include \"../Includes.%s.hpp\"\n", LE_SHORTHAND );
    }
    fprintf ( pFile, "\n\n" );

    if ( setPP )
    {
        fprintf ( pFile, "#ifdef _MSC_VER\n" );
        fprintf ( pFile, "\t#pragma pack ( push, 0x%X )\n",  CLASS_ALIGN );
        fprintf ( pFile, "#endif\n" );
    }

    fprintf ( pFile, "#define LESDK_IN_GENERATED\n" );
    fprintf ( pFile, "\n" );
}

void PrintFileFooter()
{
    fprintf ( pFile, "\n\n" );

    fprintf ( pFile, "#undef LESDK_IN_GENERATED\n" );

    fprintf ( pFile, "\n" );

    fprintf ( pFile, "#ifdef _MSC_VER\n" );
    fprintf ( pFile, "\t#pragma pack ( pop )\n" );
    fprintf ( pFile, "#endif\n" );
}

void PrintSectionHeader ( char* cSectionName )
{
    fprintf ( pFile, "\n/*\n" );
    fprintf ( pFile, "# ========================================================================================= #\n" );
    fprintf ( pFile, "# %s\n", cSectionName );
    fprintf ( pFile, "# ========================================================================================= #\n" );
    fprintf ( pFile, "*/\n\n" );
}

/*
# ========================================================================================= #
# Generate Flags												
# ========================================================================================= #
*/

void GetAllPropertyFlags ( unsigned long long PropertyFlags, ostringstream& ssStreamBuffer )
{
    bool first = true;

    if ( PropertyFlags & CPF_Edit )				{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Edit";				first = false; }
    if ( PropertyFlags & CPF_Const )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Const";			first = false; }
    if ( PropertyFlags & CPF_Input )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Input";			first = false; }
    if ( PropertyFlags & CPF_ExportObject )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_ExportObject";		first = false; }
    if ( PropertyFlags & CPF_OptionalParm )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_OptionalParm";		first = false; }
    if ( PropertyFlags & CPF_Net )				{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Net";				first = false; }
    if ( PropertyFlags & CPF_EditConstArray )	{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_EditConstArray";	first = false; }
    if ( PropertyFlags & CPF_Parm )				{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Parm";				first = false; }
    if ( PropertyFlags & CPF_OutParm )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_OutParm";			first = false; }
    if ( PropertyFlags & CPF_SkipParm )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_SkipParm";			first = false; }
    if ( PropertyFlags & CPF_ReturnParm )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_ReturnParm";		first = false; }
    if ( PropertyFlags & CPF_CoerceParm )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_CoerceParm";		first = false; }
    if ( PropertyFlags & CPF_Native )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Native";			first = false; }
    if ( PropertyFlags & CPF_Transient )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Transient";		first = false; }
    if ( PropertyFlags & CPF_Config )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Config";			first = false; }
    if ( PropertyFlags & CPF_Localized )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Localized";		first = false; }
    if ( PropertyFlags & CPF_Travel )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Travel";			first = false; }
    if ( PropertyFlags & CPF_EditConst )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_EditConst";		first = false; }
    if ( PropertyFlags & CPF_GlobalConfig )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_GlobalConfig";		first = false; }
    if ( PropertyFlags & CPF_Component )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Component";		first = false; }
    if ( PropertyFlags & CPF_NeedCtorLink )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_NeedCtorLink";		first = false; }
    if ( PropertyFlags & CPF_NoExport )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_NoExport";			first = false; }
    if ( PropertyFlags & CPF_NoClear )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_NoClear";			first = false; }
    if ( PropertyFlags & CPF_EditInline )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_EditInline";		first = false; }
    if ( PropertyFlags & CPF_EdFindable )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_EdFindable";		first = false; }
    if ( PropertyFlags & CPF_EditInlineUse )	{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_EditInlineUse";	first = false; }
    if ( PropertyFlags & CPF_Deprecated )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Deprecated";		first = false; }
    if ( PropertyFlags & CPF_EditInlineNotify ) { ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_EditInlineNotify";	first = false; }
    if ( PropertyFlags & CPF_RepNotify )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_RepNotify";		first = false; }
    if ( PropertyFlags & CPF_Interp )			{ ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_Interp";			first = false; }
    if ( PropertyFlags & CPF_NonTransactional ) { ssStreamBuffer << ( first ? "( " : " | " ) << "CPF_NonTransactional";	first = false; }

    if ( ! first ) { ssStreamBuffer << " )"; }
}

void GetAllFunctionFlags ( unsigned long FunctionFlags, ostringstream& ssStreamBuffer )
{
    bool first = true;

    if ( FunctionFlags & FUNC_Final )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "FUNC_Final";		first = false; }
    if ( FunctionFlags & FUNC_Latent )	{ ssStreamBuffer << ( first ? "( " : " | " ) << "FUNC_Latent";		first = false; }
    if ( FunctionFlags & FUNC_Simulated )	{ ssStreamBuffer << ( first ? "( " : " | " ) << "FUNC_Simulated";	first = false; }
    if ( FunctionFlags & FUNC_Exec )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "FUNC_Exec";		first = false; }
    if ( FunctionFlags & FUNC_Event )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "FUNC_Event";		first = false; }
    if ( FunctionFlags & FUNC_Native )		{ ssStreamBuffer << ( first ? "( " : " | " ) << "FUNC_Native";		first = false; }

    if ( ! first ) { ssStreamBuffer << " )"; }
}

/*
# ========================================================================================= #
# String Utils														
# ========================================================================================= #
*/

string GetValidName ( const string& sName )
{
    string sBuffer = sName;

    for ( unsigned int i = 0; i < sBuffer.length(); i++ )
    {
        if
        ( 
                sBuffer[ i ] == ' '
            ||	sBuffer[ i ] == '?'
            ||	sBuffer[ i ] == '-'
            ||  sBuffer[ i ] == ':'
        )
        {
            sBuffer[ i ] = '_';
        }
    }
    
    return sBuffer;
}

string ToS ( const wchar_t* wcOrig )
{
    char sBuffer0[ SDK_BUFF_SIZE ] = { NULL };

    sprintf_s ( sBuffer0, "%S", wcOrig );

    return string ( sBuffer0 ); 
}

string ToS ( const char* cOrig )
{
    char sBuffer0[ SDK_BUFF_SIZE ] = { NULL };

    sprintf_s ( sBuffer0, "%s", cOrig );

    return string ( sBuffer0 ); 
}

bool StrStrMm_Exist ( StrStrMm_t& StrStrMm, string sKey, string sValue )
{
    pair< StrStrMm_t::iterator, StrStrMm_t::iterator > prRange;

    prRange = StrStrMm.equal_range ( sKey ); 

    for ( StrStrMm_t::iterator it = prRange.first; it != prRange.second; ++it )
    {
        if ( (*it).second == sValue )
            return true;
    }

    return false;
}

/*
# ========================================================================================= #
# Property Utils														
# ========================================================================================= #
*/

bool SortProperty ( UProperty* pPropertyA, UProperty* pPropertyB )
{
    if
    (
            pPropertyA->Offset == pPropertyB->Offset
        &&	pPropertyA->IsA ( UBoolProperty::StaticClass() )
        &&	pPropertyB->IsA ( UBoolProperty::StaticClass() )
    )
        return ( ( (UBoolProperty*) pPropertyA )->BitMask < ( (UBoolProperty*) pPropertyB )->BitMask );
    else
        return ( pPropertyA->Offset < pPropertyB->Offset );
}

bool SortPropertyPair ( pair< UProperty*, string > pPropertyA, pair< UProperty*, string > pPropertyB )
{
    if
    (
            pPropertyA.first->Offset == pPropertyB.first->Offset
        &&	pPropertyA.first->IsA ( UBoolProperty::StaticClass() )
        &&	pPropertyB.first->IsA ( UBoolProperty::StaticClass() )
    )
        return ( ( (UBoolProperty*) pPropertyA.first )->BitMask < ( (UBoolProperty*) pPropertyB.first )->BitMask );
    else
        return ( pPropertyA.first->Offset < pPropertyB.first->Offset );
}

// GetPropertyType
// Return values
// - (0) unknown
// - (1) uchar, ulong, int, float, pointers
// - (2) predefined struct
// - (3) custom struct
// - (4) tarray
// - (5) tmap
int GetPropertyType ( UProperty* pProperty, string& sPropertyType, bool bFuncRet = false )
{
    if ( ! pProperty ) // necessary because this function is recursive
        return 0; 


    if ( false ) {}

    #ifdef CCP_UBYTE
    else if	( pProperty->IsA ( UByteProperty::StaticClass() ) )		{ sPropertyType = "unsigned char";	return 1; }
    #endif	

    #ifdef CCP_UINT
    else if ( pProperty->IsA ( UIntProperty::StaticClass() ) )		{ sPropertyType = "int";			return 1; }
    #endif
    
    #ifdef CCP_UFLOAT
    else if ( pProperty->IsA ( UFloatProperty::StaticClass() ) )		{ sPropertyType = "float";			return 1; }
    #endif
    
    #ifdef CCP_UBOOL
    else if ( pProperty->IsA ( UBoolProperty::StaticClass() ) )
    {
        if ( bFuncRet )
            sPropertyType = "bool";
        else
            sPropertyType = "unsigned long";

        return 1;
    }
    #endif

    #ifdef CCP_USTR
    else if ( pProperty->IsA ( UStrProperty::StaticClass() ) )		{ sPropertyType = "class FString";			return 2; }
    #endif

    #ifdef CCP_USTRINGREF
    else if ( pProperty->IsA ( UStringRefProperty::StaticClass() ) )	{ sPropertyType = "int";			    return 1; }
    #endif
    
    #ifdef CCP_UNAME
    else if ( pProperty->IsA ( UNameProperty::StaticClass() ) )		{ sPropertyType = "struct SFXName";			return 2; }
    #endif	

    #ifdef CCP_UDELEGATE
    else if ( pProperty->IsA ( UDelegateProperty::StaticClass() ) )	{ sPropertyType = "struct FScriptDelegate"; return 2; }
    #endif

    #ifdef CCP_UOBJECT
    else if ( pProperty->IsA ( UObjectProperty::StaticClass() ) )	{ sPropertyType = "class " + GetValidName ( string ( ( (UObjectProperty*) pProperty )->PropertyClass->GetNameCPP() ) ) + "*";		return 1; }
    #endif
    
    #ifdef CCP_UCLASS
    else if ( pProperty->IsA ( UClassProperty::StaticClass() ) )		{ sPropertyType = "class " + GetValidName ( string ( ( (UClassProperty*) pProperty )->MetaClass->GetNameCPP() ) ) + "*";				return 1; }
    #endif
    
    #ifdef CCP_UINTERFACE
    else if ( pProperty->IsA ( UInterfaceProperty::StaticClass() ) )	{ sPropertyType = "class " + GetValidName ( string ( ( (UInterfaceProperty*) pProperty )->InterfaceClass->GetNameCPP() ) ) + "*";	return 1; }
    #endif

    #ifdef CCP_USTRUCT
    else if ( pProperty->IsA ( UStructProperty::StaticClass() ) )		
    { 
        // count name
        strcpy_s ( cBuffer, ( (UStructProperty*) pProperty )->Struct->GetName() );
        unsigned int nCounterF = UObject::CountObject< UScriptStruct > ( cBuffer );
        
        if ( nCounterF > 1 )
            sPropertyType = "struct " + GetValidName ( string ( ( (UStructProperty*) pProperty )->Struct->Outer->GetNameCPP() ) ) + "_" + GetValidName ( string ( ( (UStructProperty*) pProperty )->Struct->GetNameCPP() ) );
        else
            sPropertyType = "struct " + GetValidName ( string ( ( (UStructProperty*) pProperty )->Struct->GetNameCPP() ) );
        
        return 3; 
    }
    #endif

    #ifdef CCP_UARRAY
    else if ( pProperty->IsA ( UArrayProperty::StaticClass() ) )
    {
        string sPropertyTypeInner;
            
        if ( GetPropertyType ( ( (UArrayProperty*) pProperty )->Inner, sPropertyTypeInner ) )
        {
            sPropertyType = "class TArray<" + sPropertyTypeInner + ">";
            
            return 4;
        }
        else
            return 0;
    }
    #endif

    #ifdef CCP_UMAP
    else if ( pProperty->IsA ( UMapProperty::StaticClass() ) )
    {
        string sPropertyTypeKey;
        string sPropertyTypeValue;
        
        if
        ( 
                GetPropertyType ( ( (UMapProperty*) pProperty )-> Key, sPropertyTypeKey )
            &&	GetPropertyType ( ( (UMapProperty*) pProperty )-> Value, sPropertyTypeValue ) 
        )
        {
            sPropertyType = "TMap< " + sPropertyTypeKey + ", " + sPropertyTypeValue + " >";

            return 5;
        }
        else
            return 0;
    }
    #endif

    else
        return 0;
}

unsigned long GetPropertySize ( UProperty* pProperty )
{
    if ( false ) {}
    
    #ifdef CCP_UBYTE
    else if	( pProperty->IsA ( UByteProperty::StaticClass() ) )		{ return sizeof ( unsigned char ); }
    #endif
    
    #ifdef CCP_UINT
    else if ( pProperty->IsA ( UIntProperty::StaticClass() ) )		{ return sizeof ( int ); }
    #endif
    
    #ifdef CCP_UFLOAT
    else if ( pProperty->IsA ( UFloatProperty::StaticClass() ) )		{ return sizeof ( float ); }
    #endif

    #ifdef CCP_UBOOL
    else if ( pProperty->IsA ( UBoolProperty::StaticClass() ) )		{ return sizeof ( unsigned long ); }
    #endif

    #ifdef CCP_USTR
    else if ( pProperty->IsA ( UStrProperty::StaticClass() ) )		{ return sizeof ( FString ); }
    #endif

    #ifdef CCP_USTRINGREF
    else if ( pProperty->IsA ( UStringRefProperty::StaticClass() ) )	{ return sizeof ( int ); }
    #endif

    #ifdef CCP_UNAME
    else if ( pProperty->IsA ( UNameProperty::StaticClass() ) )		{ return sizeof ( FName ); }
    #endif

    #ifdef CCP_UDELEGATE
    else if ( pProperty->IsA ( UDelegateProperty::StaticClass() ) )	{ return sizeof ( FScriptDelegate ); }
    #endif

    #ifdef CCP_UOBJECT
    else if ( pProperty->IsA ( UObjectProperty::StaticClass() ) )	{ return sizeof ( void* ); }
    #endif

    #ifdef CCP_UCLASS
    else if ( pProperty->IsA ( UClassProperty::StaticClass() ) )		{ return sizeof ( void* ); }
    #endif

    #ifdef CCP_UINTERFACE
    else if ( pProperty->IsA ( UInterfaceProperty::StaticClass() ) )	{ return sizeof ( void* ); }
    #endif

    #ifdef CCP_USTRUCT
    else if ( pProperty->IsA ( UStructProperty::StaticClass() ) )	{ return pProperty->ElementSize; } // NOT SAFE !!!
    #endif

    #ifdef CCP_UARRAY
    else if ( pProperty->IsA ( UArrayProperty::StaticClass() ) )		{ return sizeof ( TArray< void* > ); }
    #endif

    #ifdef CCP_UMAP
    else if ( pProperty->IsA ( UMapProperty::StaticClass() ) )		{ return 0x3C; }
    #endif

    else
        return 0;
}

/*
# ========================================================================================= #
# Object Utils														
# ========================================================================================= #
*/

UScriptStruct* FindBiggestScriptStruct ( string ScriptStructFullName )
{
    signed long dwSize = 0;
    UScriptStruct* BiggestScriptStruct = NULL;

    for ( int i = 0; i < UObject::GObjObjects()->Count; ++i )
    {
        UObject* Object = UObject::GObjObjects()->Data[ i ];

        // skip no T class objects
        if
        (
                ! Object
            ||	! Object->IsA ( UScriptStruct::StaticClass() )
        )
            continue;

        // check
        if ( ScriptStructFullName == string ( Object->GetFullName() ) )
        {
            UScriptStruct* ScriptStruct = (UScriptStruct*) Object;

            if ( ScriptStruct->PropertySize >= dwSize )
            {
                BiggestScriptStruct = ScriptStruct;
                dwSize = ScriptStruct->PropertySize;
            }
        }
    }

    return BiggestScriptStruct;
}

/*
# ========================================================================================= #
# Generate Code															
# ========================================================================================= #
*/

// constants
void GenerateConst ( UConst* pConst )
{
    // stream buffers
    ostringstream ssStreamBuffer0; // main stream buffer
    ostringstream ssStreamBuffer1; // support stream buffer
    ostringstream ssStreamBuffer2; // support stream buffer
    
    // maps
    static StrStrMm_t mmNameValues;
    
    // get const name 
    string sConstName = GetValidName ( string ( pConst->GetName() ) );

    // remove default const
    if ( sConstName.find ( "Default__" ) != string::npos )
        return;

    // get const value
    string sConstValue = ToS ( pConst->Value.Data );

    // count existing const
    size_t stI = mmNameValues.count ( sConstName );

    // check if const exist
    if ( stI == 0 ) // name not used so not exist
    {
        // map const name value
        mmNameValues.insert ( StrStrPair_t ( sConstName, sConstValue ) );

        // stream to main buffer
        ssStreamBuffer0 << "#define CONST_" << SDKMC_SSCOL ( sConstName, SDK_COL1 ) << " " << sConstValue << "\n";
        
        // print main stream buffer to file
        SDKFN_PRINT ( pFile, ssStreamBuffer0 );
    }
    else if ( ! StrStrMm_Exist ( mmNameValues, sConstName, sConstValue ) ) // same name but different value
    {
        // map const name value
        mmNameValues.insert ( StrStrPair_t ( sConstName, sConstValue ) );

        // add number to name
        ssStreamBuffer1 << sConstName << SDKMC_SSDEC ( stI, 2 );

        // print const
        ssStreamBuffer0 << "#define CONST_" << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL1 ) << " " << sConstValue << "\n";
        
        // print main stream buffer to file
        SDKFN_PRINT ( pFile, ssStreamBuffer0 );

        // empty support stream buffer
        SDKFN_EMPTY ( ssStreamBuffer1 );	
    }
}

// enums
void GenerateEnum ( UEnum* pEnum )
{	
    // stream buffers
    ostringstream ssStreamBuffer0; // main stream buffer
    ostringstream ssStreamBuffer1; // support stream buffer
    ostringstream ssStreamBuffer2; // support stream buffer
    
    // get enum names
    string sEnumName = GetValidName ( string ( pEnum->GetName() ) );
    string sEnumOuterNameCPP = GetValidName ( string ( pEnum->Outer->GetNameCPP() ) );
    string sEnumFullName = string ( pEnum->GetFullName() );

    // remove default enum
    if ( sEnumName.find ( "Default__" ) != string::npos )
        return;

    // print enum open
    ssStreamBuffer0 << "// " << sEnumFullName << "\n"
                    //<< "enum " << sEnumOuterNameCPP << "_" << sEnumName << "\n{\n";
                    << "/*enum " << sEnumName << "\n{\n";

    // property unique name array
    StrIntM_t mPropertyName;

    // loop enum members
    for ( int i = 0; i < pEnum->Names.Num(); i++ )
    {		
        string sPropertyName = GetValidName ( ToS ( pEnum->Names.Data[ i ].GetName() ) ); 
        
        // check unique var name
        if ( mPropertyName.count ( sPropertyName ) == 0 ) // not exist
        {
            // insert in unique name array
            mPropertyName[ sPropertyName ] = 1;

            // stream to support buffer (property name)
            //ssStreamBuffer1 << sEnumOuterNameCPP << "_" << sEnumName << "_" << sPropertyName;
            ssStreamBuffer1 << sPropertyName;
        }
        else
        {
            // stream to support buffer (name + index)
            //ssStreamBuffer1 << sEnumOuterNameCPP << "_" << sEnumName << "_" << sPropertyName << SDKMC_SSDEC ( mPropertyName[ sPropertyName ], 2 );
            ssStreamBuffer1 << sPropertyName << SDKMC_SSDEC ( mPropertyName[ sPropertyName ], 2 );
                    
            // incremente name usage count
            mPropertyName[ sPropertyName ]++;
        }

        // stram to main buffer (name = value)
        if ( i != pEnum->Names.Num() - 1 )
        {
            ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL1 ) << " = " << i << ",\n";
        }
        else
        {
            ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL1 ) << " = " << i << "\n";
        }

        // empty support stream buffer
        SDKFN_EMPTY ( ssStreamBuffer1 );
    }

    // stream to main buffer (close enum)
    ssStreamBuffer0 << "};*/\n\n"; 

    // print main stream buffer to file
    SDKFN_PRINT ( pFile, ssStreamBuffer0 );
}

// script structs
void GenerateScriptStruct ( UScriptStruct* pScriptStruct )
{
    // stream buffers
    ostringstream ssStreamBuffer0; // main stream buffer
    ostringstream ssStreamBuffer1; // support stream buffer
    ostringstream ssStreamBuffer2; // support stream buffer

    // get struct names
    string sSStructFullName = string ( pScriptStruct->GetFullName() );
    string sSStructName = GetValidName ( string ( pScriptStruct->GetName() ) );
    string sSStructNameCPP = GetValidName ( string ( pScriptStruct->GetNameCPP() ) );
    string sSStructOuterNameCPP = GetValidName ( string ( pScriptStruct->Outer->GetNameCPP() ) );

    // log
    fprintf ( pLog, "ScriptStruct: %-100s - instance: 0x%p\n", sSStructName.c_str(), pScriptStruct );

    // stream to main buffer
    ssStreamBuffer0 << "// " << sSStructFullName << "\n";
    
    // vars
    signed long dwSize = 0;
    signed long dwLastOffset = 0;
    signed long dwMissedOffset = 0;

    // get superfield
    UScriptStruct* pSuperField = ( UScriptStruct* ) pScriptStruct->SuperField;

    // count name
    strcpy_s ( cBuffer, sSStructName.c_str() );
    unsigned int nCounterF = UObject::CountObject< UScriptStruct > ( cBuffer );

    // print struct
    if ( pSuperField && pSuperField != pScriptStruct )
    {
        // calculations
        dwSize = pScriptStruct->PropertySize - pSuperField->PropertySize;
        dwLastOffset = pSuperField->PropertySize;

        // get superfield name
        string sSFieldName = GetValidName ( string ( pSuperField->GetName() ) );
        string sSFieldNameCPP = GetValidName ( string ( pSuperField->GetNameCPP() ) );
        string sSFieldOuterNameCPP = GetValidName ( string ( pSuperField->Outer->GetNameCPP() ) );

        // count superfield name
        strcpy_s ( cBuffer, sSFieldName.c_str() );
        unsigned int nCounterSF = UObject::CountObject< UScriptStruct > ( cBuffer );

        // stream to main buffer
        ssStreamBuffer0 << "// " << SDKMC_SSHEX ( dwSize, 4 ) << "(" << SDKMC_SSHEX ( pScriptStruct->PropertySize, 4 ) << " - " << SDKMC_SSHEX ( pSuperField->PropertySize, 4 ) << ")\n";

        // special case same name structs
        if ( nCounterF > 1)
            ssStreamBuffer0	<< "struct " << sSStructOuterNameCPP << "_" << sSStructNameCPP << " : ";
        else
            ssStreamBuffer0	<< "struct " << sSStructNameCPP << " : ";

        if ( nCounterSF > 1)
            ssStreamBuffer0	<< sSFieldOuterNameCPP << "_" << sSFieldNameCPP << "\n";
        else
            ssStreamBuffer0	<< sSFieldNameCPP << "\n";

    }
    else
    {
        // calculations
        dwSize = pScriptStruct->PropertySize;

        // stream to main buffer
        ssStreamBuffer0 << "// " << SDKMC_SSHEX ( dwSize, 4 ) << "\n";
        
        if ( nCounterF > 1)
            ssStreamBuffer0	<< "struct " << sSStructOuterNameCPP << "_" << sSStructNameCPP << "\n";
        else
            ssStreamBuffer0	<< "struct " << sSStructNameCPP << "\n";
    }

    // stream to buffer
    ssStreamBuffer0 << "{\n";

    // property array
    vector< UProperty* > vProperty;

    // get struct properties
    for ( UProperty* pProperty = (UProperty*) pScriptStruct->Children; pProperty; pProperty = (UProperty*) pProperty->Next )
    {
        if (pProperty->ElementSize > 0 && !pProperty->IsA(UScriptStruct::StaticClass())) // additional check for ME3
            vProperty.push_back(pProperty);
    }

    // sort vStructProperty array using pStructProperty -> Offset
    sort ( vProperty.begin(), vProperty.end(), SortProperty );

    // property unique name array
    StrIntM_t mPropertyName;

    // unknown data unique name index
    int UnknownDataIndex = 0;

    // process struct properties
    for ( unsigned int i = 0; i < vProperty.size(); i++ )
    {
        UProperty* pProperty = vProperty[ i ];

        // fix missed offsets
        if ( dwLastOffset < pProperty->Offset )
        {
            dwMissedOffset = pProperty->Offset - dwLastOffset;

            // fix only if missed offset >= CLASS_ALIGN
            if ( dwMissedOffset >= CLASS_ALIGN ) 
            {
                // stream to support buffer
                ssStreamBuffer1 << "UnknownData" << SDKMC_SSDEC ( UnknownDataIndex, 2 ) << "[ " << SDKMC_SSHEX ( dwMissedOffset, 0 ) << " ];";

                // stream to main buffer
                ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( "unsigned char", SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                << "\t\t// " << SDKMC_SSHEX ( dwLastOffset, 4 ) << " (" << SDKMC_SSHEX ( dwMissedOffset, 4 ) << ") MISSED OFFSET\n";

                // empty support buffer
                SDKFN_EMPTY( ssStreamBuffer1 );

                UnknownDataIndex++;
            }
        }

        // declare property type
        string sPropertyType;

        // strem properties to main buffer
        if ( GetPropertyType ( pProperty, sPropertyType ) )
        {
            // get correct element size
            unsigned long dwCorrectElementSize = GetPropertySize ( pProperty );

            // get property name
            string sPropertyName = GetValidName ( string ( pProperty->GetName() ) );

            // check unique var name
            if ( mPropertyName.count ( sPropertyName ) == 0 ) // not exist
            {
                // insert in unique name array
                mPropertyName[ sPropertyName ] = 1;

                // stream to support buffer (property name)
                ssStreamBuffer1 << sPropertyName;
            }
            else
            {
                // stream to support buffer (name + index)
                ssStreamBuffer1 << sPropertyName << SDKMC_SSDEC ( mPropertyName[ sPropertyName ], 2 );
                    
                // incremente name usage count
                mPropertyName[ sPropertyName ]++;
            }

            // special case array
            if ( pProperty->ArrayDim > 1 )
            {
                // stream to support buffer
                ssStreamBuffer1 << "[ " << SDKMC_SSHEX ( pProperty->ArrayDim, 0 ) << " ]";
            }

            // special case bool
            if ( pProperty->IsA ( UBoolProperty::StaticClass() ) ) 
            {
                // stream to support buffer
                ssStreamBuffer1 << " : 1";
            }

            // stream to support buffer
            ssStreamBuffer1 << ";";
            
            // stream property flags to support stream
            GetAllPropertyFlags ( pProperty->PropertyFlags, ssStreamBuffer2 );

            // stream to main buffer
            ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( sPropertyType, SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                            << "\t\t// " << SDKMC_SSHEX ( pProperty->Offset, 4 ) << " (" << SDKMC_SSHEX ( ( pProperty->ElementSize * pProperty->ArrayDim ), 4 ) << ") [" << SDKMC_SSHEX ( pProperty->PropertyFlags, 16 ) << "]";

            // stream to main buffer (bitmask)
            if ( pProperty->IsA ( UBoolProperty::StaticClass() ) ) 
            {
                // stream to support buffer
                ssStreamBuffer0 << " [" << SDKMC_SSHEX ( ( (UBoolProperty*) pProperty )->BitMask, 8 ) << "] ";
            }
            else
            {
                ssStreamBuffer0 << SDKMC_SSCOL ( "", 14 ); // empty space
            }

            ssStreamBuffer0 << ssStreamBuffer2.str() << "\n";

            // empty support buffers
            SDKFN_EMPTY ( ssStreamBuffer1 );
            SDKFN_EMPTY ( ssStreamBuffer2 );	

            // check if property size and type size are equal otherwise add pad data
            int nOffserError = ( pProperty->ElementSize * pProperty->ArrayDim ) - ( dwCorrectElementSize * pProperty->ArrayDim );

            // correct wrong size elements
            if ( nOffserError > 0)
            {
                // stream to support buffer
                ssStreamBuffer1 << "UnknownData" << SDKMC_SSDEC ( UnknownDataIndex, 2 ) << "[ " << SDKMC_SSHEX ( nOffserError, 0 ) << " ];";

                // stream to main buffer
                ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( "unsigned char", SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                << "\t\t// " << SDKMC_SSHEX ( ( pProperty->Offset + nOffserError ), 4 ) << " (" << SDKMC_SSHEX ( nOffserError, 4 ) << ") FIX WRONG TYPE SIZE OF PREVIUS PROPERTY\n";

                // empty support buffers
                SDKFN_EMPTY ( ssStreamBuffer1 );
                
                UnknownDataIndex++;
            }
        }
        else
        {
            // stream to support buffer
            ssStreamBuffer1 << "UnknownData" << SDKMC_SSDEC ( UnknownDataIndex, 2 ) << "[ " << SDKMC_SSHEX ( ( pProperty->ElementSize * pProperty->ArrayDim ), 0 ) << " ];";

            // stream to main buffer
            ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( "unsigned char", SDK_COL1 ) << " " << SDKMC_SSCOL( ssStreamBuffer1.str(), SDK_COL2 ) 
                            << "\t\t// " << SDKMC_SSHEX ( pProperty->Offset, 4 ) << " (" << SDKMC_SSHEX ( ( pProperty->ElementSize * pProperty->ArrayDim ), 4 ) << ") UNKNOWN PROPERTY: " << string ( pProperty->GetFullName() ) << "\n";

            // empty support buffer
            SDKFN_EMPTY ( ssStreamBuffer1 );

            UnknownDataIndex++;
        }

        // calc new last offset
        dwLastOffset = pProperty->Offset + ( pProperty->ElementSize * pProperty->ArrayDim );
    }

    // fix last missed offsets
    if ( dwLastOffset < pScriptStruct->PropertySize )
    {
        dwMissedOffset = pScriptStruct->PropertySize - dwLastOffset;

        // fix only if missed offset >= CLASS_ALIGN
        if ( dwMissedOffset >= CLASS_ALIGN ) 
        {
            // stream to support buffer
            ssStreamBuffer1 << "UnknownData" << SDKMC_SSDEC ( UnknownDataIndex, 2 ) << "[ " << SDKMC_SSHEX ( dwMissedOffset, 0 ) << " ];";

            // stream to main buffer
            ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( "unsigned char", SDK_COL1 ) << " " << SDKMC_SSCOL( ssStreamBuffer1.str(), SDK_COL2 ) 
                            << "\t\t// " << SDKMC_SSHEX ( dwLastOffset, 4 ) << " (" << SDKMC_SSHEX ( dwMissedOffset, 4 ) << ") MISSED OFFSET\n";

            // empty support buffer
            SDKFN_EMPTY ( ssStreamBuffer1 );
        }
    }

    // stream to main buffer
    ssStreamBuffer0 << "};\n\n";

    // print main stream buffer to file
    SDKFN_PRINT ( pFile, ssStreamBuffer0 );
}

void GenerateScriptStructPre ( UScriptStruct* pScriptStruct, UObject* pPackageToProcess )
{
    // check package object (needed 'cause this function is recursive)
    UObject* pPackageObject = pScriptStruct->GetPackageObj();
    if ( ! pPackageObject || pPackageObject != pPackageToProcess )
        return;

    // skip empty scriptstructs
    //if ( pScriptStruct->PropertySize == 0 )
    //	return;

    // generated script structs
    static vector< string > vGenScriptStructs;

    // init property names
    string sSStructName = GetValidName ( string ( pScriptStruct->GetName() ) );
    string sScriptStructFullName = string ( pScriptStruct->GetFullName() );

    // remove default script struct
    if ( sSStructName.find ( "Default__" ) != string::npos )
        return;

    // remove uninitialized script struct (ME3 fix)
    if ( sSStructName.find ( "<uninitialized>" ) != string::npos )
        return;

    // init propertytype
    string sPropertyType;

    // check if already generated
    if ( find ( vGenScriptStructs.begin(), vGenScriptStructs.end(), sScriptStructFullName ) == vGenScriptStructs.end() ) // not generated
    {	
        // check if scriptstruct is duplicated, if it is get the biggest
        pScriptStruct = FindBiggestScriptStruct ( sScriptStructFullName );

        // check superfield prerequisites
        if 
        ( 
                pScriptStruct->SuperField 
            &&	pScriptStruct->SuperField != pScriptStruct
            &&  find ( vGenScriptStructs.begin(), vGenScriptStructs.end(), string ( ( (UScriptStruct*) ( pScriptStruct->SuperField ) )->GetFullName() ) ) == vGenScriptStructs.end() // not generated
        )
        {
            // generate superfield struct
            GenerateScriptStructPre ( (UScriptStruct*) ( pScriptStruct->SuperField ), pPackageToProcess );
        }

        // check properties prerequisites
        for ( UProperty* pStructProperty = (UProperty*) pScriptStruct->Children; pStructProperty; pStructProperty = (UProperty*) pStructProperty->Next )
        {
            int iTypeResult = GetPropertyType ( pStructProperty, sPropertyType );
            
            // check structs
            if
            ( 
                    iTypeResult == 3 // struct
                &&	(UScriptStruct*) ( ( (UStructProperty*) pStructProperty )->Struct ) != pScriptStruct // the prerequisite is not itself
                &&	find ( vGenScriptStructs.begin(), vGenScriptStructs.end(), string ( ( (UScriptStruct*) ( ( (UStructProperty*) pStructProperty )->Struct ) )->GetFullName() ) ) == vGenScriptStructs.end()	// not generated
            ) 
            {
                // generate property struct
                GenerateScriptStructPre ( (UScriptStruct*) ( ( (UStructProperty*) pStructProperty )->Struct ), pPackageToProcess );	
            }

            // check array of struct
            if
            ( 
                    iTypeResult == 4 // tarray
                &&	GetPropertyType ( ( (UArrayProperty*) pStructProperty )->Inner, sPropertyType ) == 3 // struct
                &&  (UScriptStruct*) ( ( (UStructProperty*) ( (UArrayProperty*) pStructProperty )->Inner )->Struct ) != pScriptStruct // the prerequisite is not itself
                &&	find ( vGenScriptStructs.begin(), vGenScriptStructs.end(), string ( ( (UScriptStruct*) ( ( (UStructProperty*) ( (UArrayProperty*) pStructProperty )->Inner )->Struct ) )->GetFullName() ) ) == vGenScriptStructs.end() // not generated
            ) 
            {
                // generate property struct
                GenerateScriptStructPre ( (UScriptStruct*) ( ( (UStructProperty*) ( (UArrayProperty*) pStructProperty )->Inner )->Struct ), pPackageToProcess );
            }

            // TODO: check TMap
        }

        // prerequisites ended
        GenerateScriptStruct ( pScriptStruct );
        vGenScriptStructs.push_back ( sScriptStructFullName );
    }
}

// functions
void GenerateFuncStruct ( UClass* pClass )
{
    // stream buffers
    ostringstream ssStreamBuffer0; // main stream buffer
    ostringstream ssStreamBuffer1; // support stream buffer
    ostringstream ssStreamBuffer2; // support stream buffer
    
    // function array
    vector< UFunction* > vFunction;
    
    // get functions
    for ( UProperty* pProperty = (UProperty*) pClass->Children; pProperty; pProperty = (UProperty*) pProperty->Next )
    {
        if ( pProperty->IsA ( UFunction::StaticClass() ) )
        {
            vFunction.push_back ( (UFunction*) pProperty );
        }
    }

    // process functions
    for ( unsigned int i = 0; i < vFunction.size(); i++ )
    {
        UFunction* pFunction = vFunction[ i ];

        // get function names
        string sFunctionFullName = string ( pFunction->GetFullName() ); 
        string sFunctionName = GetValidName ( string ( pFunction->GetName() ) );
        string sClassNameCPP = GetValidName ( string ( pClass->GetNameCPP() ) );

        // stream to support buffer (function flags)
        GetAllFunctionFlags ( pFunction->FunctionFlags, ssStreamBuffer1 );

        // stream to main buffer (function infos + function flags)
        ssStreamBuffer0 << "// " << sFunctionFullName << "\n"
                        << "// [" << SDKMC_SSHEX ( pFunction->FunctionFlags, 8 ) << "] "
                        << ssStreamBuffer1.str(); 

        // empty support buffers
        SDKFN_EMPTY ( ssStreamBuffer1 );
        
        // stream to main buffer (iNative index)
        if ( ( pFunction->FunctionFlags & FUNC_Native ) && pFunction->iNative )
        { 
            ssStreamBuffer0 << " iNative [" << SDKMC_SSHEX ( pFunction->iNative, 4 ) << "]";
        } 
        
        // stream to support buffer (struct name)
        if		( pFunction->FunctionFlags & FUNC_Exec )		{ ssStreamBuffer1 << "exec"; }
        else if	( pFunction->FunctionFlags & FUNC_Event )	{ ssStreamBuffer1 << "event"; }
        else												{ ssStreamBuffer1 << "exec"; }


        // stream to main buffer (struct name)
        ssStreamBuffer0 << "\n"
                        << "struct " << sClassNameCPP << "_" << ssStreamBuffer1.str() << sFunctionName << "_Parms\n"
                        << "{\n";
        
        // empty support buffers
        SDKFN_EMPTY ( ssStreamBuffer1 );

        // function property array
        vector< UProperty* > vProperty;

        // get function properties
        for ( UProperty* pProperty = (UProperty*) pFunction->Children; pProperty; pProperty = (UProperty*) pProperty->Next )
        {
            if ( pProperty->ElementSize > 0 )
                vProperty.push_back ( pProperty );
        }

        // sort vProperty array using pProperty -> Offset
        sort ( vProperty.begin(), vProperty.end(), SortProperty );

        // property unique name map
        StrIntM_t mPropertyName;

        // stream properties to main buffer
        for ( unsigned int i = 0; i < vProperty.size(); i++ )
        {
            UProperty* pProperty = vProperty[ i ];

            // dec property type
            string sPropertyType;

            if ( GetPropertyType ( pProperty, sPropertyType ) )
            {
                // get property name
                string sPropertyName = GetValidName ( string ( pProperty->GetName() ) );

                // check unique var name
                if ( mPropertyName.count ( sPropertyName ) == 0 ) // not exist
                {
                    // insert in unique name array
                    mPropertyName[ sPropertyName ] = 1;

                    // stream to support buffer (property name)
                    ssStreamBuffer1 << sPropertyName;
                }
                else
                {
                    // stream to support buffer (name + index)
                    ssStreamBuffer1 << sPropertyName << SDKMC_SSDEC ( mPropertyName[ sPropertyName ], 2 );
                    
                    // incremente name usage count
                    mPropertyName[ sPropertyName ]++;
                }

                // special case array
                if ( pProperty->ArrayDim > 1 )
                {
                    // stream to support buffer
                    ssStreamBuffer1 << "[ " << SDKMC_SSHEX ( pProperty->ArrayDim, 0 ) << " ]";
                }

                //// special case bool
                //if ( pProperty->IsA ( UBoolProperty::StaticClass() ) ) 
                //{
                //	// stream to support buffer
                //	ssStreamBuffer1 << " : 1";
                //}

                // stream to support buffer
                ssStreamBuffer1 << ";";

                // stream property flags to support stream
                GetAllPropertyFlags ( pProperty->PropertyFlags, ssStreamBuffer2 );

                // stream to main buffer ( comment not params )
                if ( pProperty->PropertyFlags & CPF_Parm ) // only function parms
                {
                    ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( sPropertyType, SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                    << "\t\t// " << SDKMC_SSHEX ( pProperty->Offset, 4 ) << " (" << SDKMC_SSHEX ( ( pProperty->ElementSize * pProperty->ArrayDim ), 4 ) << ") [" << SDKMC_SSHEX ( pProperty->PropertyFlags, 16 ) << "]";
                }
                else
                {
                    ssStreamBuffer0 << "\t// " << SDKMC_SSCOL ( sPropertyType, ( SDK_COL1 - 3 ) ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                    << "\t\t// " << SDKMC_SSHEX ( pProperty->Offset, 4 ) << " (" << SDKMC_SSHEX ( ( pProperty->ElementSize * pProperty->ArrayDim ), 4 ) << ") [" << SDKMC_SSHEX ( pProperty->PropertyFlags, 16 ) << "]";
                }
                                    
                //// stream to main buffer (bitmask)
                //if ( pProperty->IsA ( UBoolProperty::StaticClass() ) ) 
                //{
                //	// stream to support buffer
                //	ssStreamBuffer0 << " [" << SDKMC_SSHEX ( ( (UBoolProperty*) pProperty )->BitMask, 8 ) << "] ";
                //}
                //else
                {
                    ssStreamBuffer0 << SDKMC_SSCOL ( "", 14 ); // empty space
                }

                ssStreamBuffer0 << ssStreamBuffer2.str() << "\n";

                // empty support buffers
                SDKFN_EMPTY ( ssStreamBuffer1 );
                SDKFN_EMPTY ( ssStreamBuffer2 );	
            } 
            else
            { 
                // get property full name
                string sPropertyFullName = string ( pProperty->GetFullName() );

                // stream to main buffer
                ssStreamBuffer0 << "\t// UNKNOWN PROPERTY: " << sPropertyFullName << "\n";			
            }
        }

        // stream to main buffer
        ssStreamBuffer0 << "};\n\n";
    }

    // print main stream buffer to file
    SDKFN_PRINT ( pFile, ssStreamBuffer0 );
}

void GenerateFuncDef ( UClass* pClass )
{
    // stream buffers
    ostringstream ssStreamBuffer0; // main stream buffer
    ostringstream ssStreamBuffer1; // support stream buffer
    ostringstream ssStreamBuffer2; // support stream buffer

    // function array
    vector< UFunction* > vFunction;
    
    // get functions
    for ( UProperty* pProperty = (UProperty*) pClass->Children; pProperty; pProperty = (UProperty*) pProperty->Next )
    {
        if ( pProperty->IsA ( UFunction::StaticClass() ) )
        {
            vFunction.push_back ( (UFunction*) pProperty );
        }
    }

    // print out class pointer and StaticClass()

    auto className = GetValidName(string(pClass->GetNameCPP()));
    auto sClassFullName = string(pClass->GetFullName());

    if (		0 != strncmp(className.c_str(), "Default__", 9)
            &&	0 != strncmp(className.c_str(), "UClassDefault__", 15) )
    {
        ssStreamBuffer0 << "\n\n"
            << "class UClass* " << className << "::pClassPointer = NULL;"
            << "\n";

        if ( SDK_NO_STR )
        {
            ssStreamBuffer0 << "\n"
                << "class UClass* " << className << "::StaticClass()\n"
                << "\t{\n"
                << "\t\tif ( ! pClassPointer )\n"
                << "\t\t\tpClassPointer = (UClass*) UObject::GObjObjects->GetData()[ " << SDKMC_SSDEC(pClass->ObjectInternalInteger, 0) << " ];\n\n"
                << "\t\treturn pClassPointer;\n"
                << "\t};\n\n";
        }
        else
        {
            ssStreamBuffer0 << "\n"
                << "class UClass* " << className << "::StaticClass()\n"
                << "\t{\n"
                << "\t\tif ( ! pClassPointer )\n"
                << "\t\t\tpClassPointer = UObject::FindClass ( L\"" << sClassFullName << "\" );\n\n"
                << "\t\treturn pClassPointer;\n"
                << "\t};\n\n";
        }
    }

    // process functions
    for ( unsigned int i = 0; i < vFunction.size(); i++ )
    {
        UFunction* pFunction = vFunction[ i ];

        // get function names
        string sFunctionFullName = string ( pFunction->GetFullName() ); 
        string sFunctionName = GetValidName ( string ( pFunction->GetName() ) );
        string sClassNameCPP = GetValidName ( string ( pClass->GetNameCPP() ) );

        // stream to support buffer (function flags)
        GetAllFunctionFlags ( pFunction->FunctionFlags, ssStreamBuffer1 );

        // stream to main buffer (function infos + function flags)
        ssStreamBuffer0 << "// " << sFunctionFullName << "\n"
                        << "// [" << SDKMC_SSHEX ( pFunction->FunctionFlags, 8 ) << "] "
                        << ssStreamBuffer1.str(); 

        // empty support buffers
        SDKFN_EMPTY ( ssStreamBuffer1 );
        
        // stream to main buffer (iNative index)
        if ( ( pFunction->FunctionFlags & FUNC_Native ) && pFunction->iNative )
        { 
            ssStreamBuffer0 << " iNative [" << SDKMC_SSHEX ( pFunction->iNative, 4 ) << "]";
        }
        
        // funtion property "Parms" array
        vector< pair< UProperty*, string > > vProperty_Parms;

        // function property "OutParms" array
        vector< pair< UProperty*, string > > vProperty_OutParms;

        // function property "ReturnParm"
        pair< UProperty*, string > pProperty_ReturnParm;

        // property unique name map
        StrIntM_t mPropertyName;

        // get function properties
        for ( UProperty* pProperty = (UProperty*) pFunction->Children; pProperty; pProperty = (UProperty*) pProperty->Next )
        {
            if ( pProperty->ElementSize == 0 )
                continue;
            
            // get property name
            string sPropertyNameBuffer = GetValidName ( string ( pProperty->GetName() ) );
            string sPropertyNameUnique;

            // check unique var name
            if ( mPropertyName.count ( sPropertyNameBuffer ) == 0 ) // not exist
            {
                // insert in unique name array
                mPropertyName[ sPropertyNameBuffer ] = 1;

                // assign unique property name
                sPropertyNameUnique = sPropertyNameBuffer;
            }
            else
            {
                // stream to support buffer (name + index)
                ssStreamBuffer1 << sPropertyNameBuffer << SDKMC_SSDEC ( mPropertyName[ sPropertyNameBuffer ], 2 );
                
                // assign unique property name
                sPropertyNameUnique = ssStreamBuffer1.str();

                // empty stream buffer
                SDKFN_EMPTY ( ssStreamBuffer1 );

                // incremente name usage count
                mPropertyName[ sPropertyNameBuffer ]++;
            }
            
            if		( pProperty->PropertyFlags & CPF_ReturnParm )	{ pProperty_ReturnParm = make_pair ( pProperty, sPropertyNameUnique ); }			// property is the return param
            else if ( pProperty->PropertyFlags & CPF_OutParm )		{ vProperty_OutParms.push_back ( make_pair ( pProperty, sPropertyNameUnique ) ); }	// property is a out param			
            else if ( pProperty->PropertyFlags & CPF_Parm )		{ vProperty_Parms.push_back ( make_pair ( pProperty, sPropertyNameUnique ) ); }		// property is a in param
        }

        // sort vProperty arrays using pProperty -> Offset
        sort ( vProperty_Parms.begin(), vProperty_Parms.end(), SortPropertyPair );
        sort ( vProperty_OutParms.begin(), vProperty_OutParms.end(), SortPropertyPair );

        // stream to main buffer
        ssStreamBuffer0 << "\n// Parameters infos:\n";
        
        // property type
        string sPropertyType;

        // stream to main buffer properties infos ( CPF_ReturnParm )
        if ( pProperty_ReturnParm.first && GetPropertyType ( pProperty_ReturnParm.first, sPropertyType, true ) ) 
        { 
            // stram to support buffer (property flags)
            GetAllPropertyFlags ( pProperty_ReturnParm.first->PropertyFlags, ssStreamBuffer1 );

            // stream to main buffer (property type + name + flags)
            ssStreamBuffer0 << "// " << SDKMC_SSCOL ( sPropertyType, 30 ) << " " << SDKMC_SSCOL ( pProperty_ReturnParm.second, 30 ) << " " << ssStreamBuffer1.str() << "\n";

            // empty support buffer
            SDKFN_EMPTY ( ssStreamBuffer1 );
        }

        // stream to main buffer properties infos ( CPF_Parm )
        for ( unsigned int i = 0; i < vProperty_Parms.size(); i++ )
        {
            pair< UProperty*, string > pProperty ( vProperty_Parms[ i ] );

            if ( GetPropertyType ( pProperty.first, sPropertyType ) )
            {
                // stram to support buffer (property flags)
                GetAllPropertyFlags ( pProperty.first->PropertyFlags, ssStreamBuffer1 );

                // stream to main buffer (property type + name + flags)
                ssStreamBuffer0 << "// " << SDKMC_SSCOL ( sPropertyType, 30 ) << " " << SDKMC_SSCOL ( pProperty.second, 30 ) << " " << ssStreamBuffer1.str() << "\n";

                // empty support buffer
                SDKFN_EMPTY ( ssStreamBuffer1 );
            }
        }

        // stream to main buffer properties infos ( CPF_OutParm )
        for ( unsigned int i = 0; i < vProperty_OutParms.size(); i++ )
        {
            pair< UProperty*, string > pProperty ( vProperty_OutParms[ i ] );

            if ( GetPropertyType ( pProperty.first, sPropertyType ) )
            {
                // stram to support buffer (property flags)
                GetAllPropertyFlags ( pProperty.first->PropertyFlags, ssStreamBuffer1 );

                // stream to main buffer (property type + name + flags)
                ssStreamBuffer0 << "// " << SDKMC_SSCOL ( sPropertyType, 30 ) << " " << SDKMC_SSCOL ( pProperty.second, 30 ) << " " << ssStreamBuffer1.str() << "\n";

                // empty support buffer
                SDKFN_EMPTY ( ssStreamBuffer1 );
            }
        }

        // stream to main buffer return type
        if ( pProperty_ReturnParm.first && GetPropertyType ( pProperty_ReturnParm.first, sPropertyType, true ) ) 
        { 
            ssStreamBuffer0 << "\n" << sPropertyType;
        }
        else
        {
            ssStreamBuffer0 << "\nvoid";
        }

        // stream to main buffer function name
        if		( pFunction->FunctionFlags & FUNC_Exec )		{ ssStreamBuffer0 << " " << sClassNameCPP << "::" << sFunctionName << " ("; }
        else if ( pFunction -> FunctionFlags & FUNC_Event ) { ssStreamBuffer0 << " " << sClassNameCPP << "::event" << sFunctionName << " ("; }
        else												{ ssStreamBuffer0 << " " << sClassNameCPP << "::" << sFunctionName << " ("; }
        
        // init comma flag
        bool bPrintComma = false;

        // stream to main buffer properties ( CPF_Parm )
        for ( unsigned int i = 0; i < vProperty_Parms.size(); i++ )
        {
            pair< UProperty*, string > pProperty ( vProperty_Parms[ i ] );

            if ( GetPropertyType ( pProperty.first, sPropertyType ) )
            {
                // stream to main buffer (comma)
                if ( bPrintComma ) { ssStreamBuffer0 << ","; }

                // special case array
                if ( pProperty.first->ArrayDim > 1 )
                {
                    // stream to main buffer (property type + name)
                    ssStreamBuffer0 << " " << sPropertyType << "* " << pProperty.second;
                }
                else
                {
                    // stream to main buffer (property type + name)
                    ssStreamBuffer0 << " " << sPropertyType << " " << pProperty.second;
                }

                // set comma flag
                bPrintComma = true;
            }
        }

        // stream to main buffer properties ( CPF_OutParm )
        for ( unsigned int i = 0; i < vProperty_OutParms.size(); i++ )
        {
            pair< UProperty*, string > pProperty ( vProperty_OutParms[ i ] );

            if ( GetPropertyType ( pProperty.first, sPropertyType ) )
            {
                // stream to main buffer (comma)
                if ( bPrintComma ) { ssStreamBuffer0 << ","; }

                // stream to main buffer (property type* + name)
                ssStreamBuffer0 << " " << sPropertyType << "* " << pProperty.second;

                // set comma flag
                bPrintComma = true;
            }
        }

        // stream to main buffer function
        if ( SDK_NO_STR )
        {
            ssStreamBuffer0 << " )\n{\n"																																			// open function
                            << "\tstatic UFunction* pFn" << sFunctionName << " = NULL;\n\n"																							// function static pointer
                            << "\tif ( ! pFn" << sFunctionName << " )\n"																											// init function static pointer
                            << "\t\tpFn" << sFunctionName << " = (UFunction*) UObject::GObjObjects->GetData()[ " << SDKMC_SSDEC( pFunction->ObjectInternalInteger, 0 ) << " ];\n\n"
                            << "\t" << sClassNameCPP << "_";																														// params struct
        }
        else
        {
            ssStreamBuffer0 << " )\n{\n"																																			// open function
                            << "\tstatic UFunction* pFn" << sFunctionName << " = NULL;\n\n"																							// function static pointer
                            << "\tif ( ! pFn" << sFunctionName << " )\n"																											// init function static pointer
                            << "\t\tpFn" << sFunctionName << " = UObject::FindObject< UFunction > ( L\"" << sFunctionFullName << "\" );\n\n"
                            << "\t" << sClassNameCPP << "_";																														// params struct
        }																													

        // params struct
        if		( pFunction->FunctionFlags & FUNC_Exec )		{ ssStreamBuffer0 << "exec"; }
        else if ( pFunction->FunctionFlags & FUNC_Event )	{ ssStreamBuffer0 << "event"; }
        else												{ ssStreamBuffer0 << "exec"; }

        // params struct
        ssStreamBuffer0 << sFunctionName << "_Parms " << sFunctionName << "_Parms;\n";

        // stream to main buffer (populate parms struct) ( CPF_Parm )
        for ( unsigned int i = 0; i < vProperty_Parms.size(); i++ )
        {		
            pair< UProperty*, string > pProperty ( vProperty_Parms[ i ] );

            int iTypeResult = GetPropertyType ( pProperty.first, sPropertyType );

            if ( iTypeResult > 1 || pProperty.first->ArrayDim > 1 ) // struct, tarray, tmap OR array
            {
                ssStreamBuffer0 << "\tmemcpy ( &" << sFunctionName << "_Parms." << pProperty.second << ", &" << pProperty.second << ", " << SDKMC_SSHEX ( ( pProperty.first->ElementSize * pProperty.first->ArrayDim ), 0 ) << " );\n";
            }
            else if ( iTypeResult == 1 ) // dword, BYTE, string, ecc.
            {
                ssStreamBuffer0 << "\t" << sFunctionName << "_Parms." << pProperty.second << " = " << pProperty.second << ";\n";
            }
        }


        // UPDATE - d00t - Tentative attempt to fix the crashes due to outparms not getting pre-populated.

        // stream to main buffer (populate out part of parms struct) ( CPF_OutParm )
        for ( unsigned int i = 0; i < vProperty_OutParms.size(); i++ )
        {
            pair< UProperty*, string > pProperty( vProperty_OutParms[ i ] );

            ssStreamBuffer0 << "\n\tif ( " << pProperty.second << " )\n";

            int iTypeResult = GetPropertyType ( pProperty.first, sPropertyType );

            if ( iTypeResult > 1 || pProperty.first->ArrayDim > 1 ) // struct, tarray, tmap OR array
            {
                ssStreamBuffer0 << "\t\tmemcpy ( &" << sFunctionName << "_Parms." << pProperty.second << ", " << pProperty.second << ", " << SDKMC_SSHEX ( ( pProperty.first->ElementSize * pProperty.first->ArrayDim ), 0 ) << " );\n";
            }
            else if ( iTypeResult == 1 ) // dword, BYTE, string, ecc.
            {
                ssStreamBuffer0 << "\t\t" << sFunctionName << "_Parms." << pProperty.second << " = *" << pProperty.second << ";\n";
            }
        }

        // UPDATE - d00t


        // stream to main buffer (function native tricks)
        if ( ( pFunction->FunctionFlags & FUNC_Native ) && pFunction->iNative )
        {
            ssStreamBuffer0 << "\n\tunsigned short NativeIndex = pFn" << sFunctionName << "->iNative;\n"
                            << "\tpFn" << sFunctionName << "->iNative = 0;\n";
        }

        // stream to main buffer (function native tricks)
        if ( pFunction->FunctionFlags & FUNC_Native )
        {
            ssStreamBuffer0 << "\n\tpFn" << sFunctionName << "->FunctionFlags |= ~" << SDKMC_SSHEX ( FUNC_Native, 0 ) << ";\n";  
        }

        // stream to main buffer (call process event)
        ssStreamBuffer0 << "\n\tthis->ProcessEvent ( pFn" << sFunctionName << ", &" << sFunctionName << "_Parms, NULL );\n";

        // stream to main buffer (reset function native tricks)
        if ( pFunction -> FunctionFlags & FUNC_Native )
        {
            ssStreamBuffer0 << "\n\tpFn" << sFunctionName << "->FunctionFlags |= " << SDKMC_SSHEX ( FUNC_Native, 0 ) << ";\n";
        }

        // stream to main buffer (reset function native tricks)
        if ( ( pFunction -> FunctionFlags & FUNC_Native ) && pFunction -> iNative )
        {
            ssStreamBuffer0 << "\n\tpFn" << sFunctionName << "->iNative = NativeIndex;\n";
        }

        // stream to main buffer (populate CPF_OutParm)
        for ( unsigned int i = 0; i < vProperty_OutParms.size(); i++ )
        {
            pair< UProperty*, string > pProperty ( vProperty_OutParms[ i ] );

            // stream to main buffer (if outparm)
            ssStreamBuffer0 << "\n\tif ( " << pProperty.second << " )\n"; 

            int iTypeResult = GetPropertyType ( pProperty.first, sPropertyType );

            if ( iTypeResult > 1 || pProperty.first->ArrayDim > 1 ) // struct, tarray, tmap OR array
            {
                ssStreamBuffer0 << "\t\tmemcpy ( " << pProperty.second << ", &" << sFunctionName << "_Parms." << pProperty.second << ", " << SDKMC_SSHEX ( ( pProperty.first->ElementSize * pProperty.first->ArrayDim ), 0 ) << " );\n";
            }
            else if ( iTypeResult == 1 ) // dword, BYTE, string, ecc.
            {
                ssStreamBuffer0 << "\t\t*" << pProperty.second << " = " << sFunctionName << "_Parms." << pProperty.second << ";\n";
            }
        }

        // stream to main buffer (return value)
        if ( pProperty_ReturnParm.first && GetPropertyType ( pProperty_ReturnParm.first, sPropertyType ) )
        {
            ssStreamBuffer0 << "\n\treturn " << sFunctionName << "_Parms." << pProperty_ReturnParm.second << ";\n";
        }

        // stream to main buffer (function close)
        ssStreamBuffer0 << "};\n\n";
    }

    // print main stream buffer to file
    SDKFN_PRINT ( pFile, ssStreamBuffer0 );
}

void GenerateFuncDec ( UClass* pClass )
{
    // stream buffers
    ostringstream ssStreamBuffer0; // main stream buffer
    ostringstream ssStreamBuffer1; // support stream buffer
    ostringstream ssStreamBuffer2; // support stream buffer

    // function array
    vector< UFunction* > vFunction;
    
    // get functions
    for ( UProperty* pProperty = (UProperty*) pClass->Children; pProperty; pProperty = (UProperty*) pProperty->Next )
    {
        if ( pProperty->IsA ( UFunction::StaticClass() ) )
        {
            vFunction.push_back ( (UFunction*) pProperty );
        }
    }

    // process functions
    for ( unsigned int i = 0; i < vFunction.size(); i++ )
    {
        UFunction* pFunction = vFunction[ i ];

        //get function names
        string sFunctionName = GetValidName ( string ( pFunction->GetName() ) );	

        // funtion property "Parms" array
        vector< pair< UProperty*, string > > vProperty_Parms;

        // function property "OutParms" array
        vector< pair< UProperty*, string > > vProperty_OutParms;

        // function property "ReturnParm"
        pair< UProperty*, string > pProperty_ReturnParm;

        // property unique name map
        StrIntM_t mPropertyName;

        // get function properties
        for ( UProperty* pProperty = (UProperty*) pFunction->Children; pProperty; pProperty = (UProperty*) pProperty->Next )
        {
            if ( pProperty->ElementSize == 0 )
                continue;
            
            // get property name
            string sPropertyNameBuffer = GetValidName ( string ( pProperty->GetName() ) );
            string sPropertyNameUnique;

            // check unique var name
            if ( mPropertyName.count ( sPropertyNameBuffer ) == 0 ) // not exist
            {
                // insert in unique name array
                mPropertyName[ sPropertyNameBuffer ] = 1;

                // assign unique property name
                sPropertyNameUnique = sPropertyNameBuffer;
            }
            else
            {
                // stream to support buffer (name + index)
                ssStreamBuffer1 << sPropertyNameBuffer << SDKMC_SSDEC ( mPropertyName[ sPropertyNameBuffer ], 2 );
                
                // assign unique property name
                sPropertyNameUnique = ssStreamBuffer1.str();

                // empty stream buffer
                SDKFN_EMPTY ( ssStreamBuffer1 );

                // incremente name usage count
                mPropertyName[ sPropertyNameBuffer ]++;
            }
            
            if		( pProperty->PropertyFlags & CPF_ReturnParm )	{ pProperty_ReturnParm = make_pair ( pProperty, sPropertyNameUnique ); }			// property is the return param
            else if ( pProperty->PropertyFlags & CPF_OutParm )		{ vProperty_OutParms.push_back ( make_pair ( pProperty, sPropertyNameUnique ) ); }	// property is a out param			
            else if ( pProperty->PropertyFlags & CPF_Parm )		{ vProperty_Parms.push_back ( make_pair ( pProperty, sPropertyNameUnique ) ); }		// property is a in param
        }

        // sort vProperty arrays using pProperty -> Offset
        sort ( vProperty_Parms.begin(), vProperty_Parms.end(), SortPropertyPair );
        sort ( vProperty_OutParms.begin(), vProperty_OutParms.end(), SortPropertyPair );

        // property type
        string sPropertyType;

        // stream to main buffer return type
        if ( pProperty_ReturnParm.first && GetPropertyType ( pProperty_ReturnParm.first, sPropertyType, true ) ) 
        { 
            ssStreamBuffer0 << "\t" << sPropertyType;
        }
        else
        {
            ssStreamBuffer0 << "\tvoid";
        }

        // stream to main buffer function name
        if		( pFunction->FunctionFlags & FUNC_Exec )		{ ssStreamBuffer0 << " " << sFunctionName << " ("; }
        else if ( pFunction->FunctionFlags & FUNC_Event ) { ssStreamBuffer0 << " event" << sFunctionName << " ("; }
        else												{ ssStreamBuffer0 << " " << sFunctionName << " ("; }
            
        // init comma flag
        bool bPrintComma = false;

        // stream to main buffer properties ( CPF_Parm )
        for ( unsigned int i = 0; i < vProperty_Parms.size(); i++ )
        {
            pair< UProperty*, string > pProperty ( vProperty_Parms[ i ] );

            if ( GetPropertyType ( pProperty.first, sPropertyType ) )
            {
                // stream to main buffer (comma)
                if ( bPrintComma ) { ssStreamBuffer0 << ","; }

                // special case array
                if ( pProperty.first->ArrayDim > 1 )
                {
                    // stream to main buffer (property type + name)
                    ssStreamBuffer0 << " " << sPropertyType << "* " << pProperty.second;
                }
                else
                {
                    // stream to main buffer (property type + name)
                    ssStreamBuffer0 << " " << sPropertyType << " " << pProperty.second;
                }

                // set comma flag
                bPrintComma = true;
            }
        }

        // stream to main buffer properties ( CPF_OutParm )
        for ( unsigned int i = 0; i < vProperty_OutParms.size(); i++ )
        {
            pair< UProperty*, string > pProperty ( vProperty_OutParms[ i ] );

            if ( GetPropertyType ( pProperty.first, sPropertyType ) )
            {
                // stream to main buffer (comma)
                if ( bPrintComma ) { ssStreamBuffer0 << ","; }

                // stream to main buffer (property type* + name)
                ssStreamBuffer0 << " " << sPropertyType << "* " << pProperty.second;

                // set comma flag
                bPrintComma = true;
            }
        }

        // stream to main buffer
        ssStreamBuffer0 << " );\n";
    }

    // print main stream buffer to file
    SDKFN_PRINT ( pFile, ssStreamBuffer0 );
}

void GenerateVirtualFunc ( UClass* pClass )
{
    // stream buffers
    ostringstream ssStreamBuffer0; // main stream buffer
    ostringstream ssStreamBuffer1; // support stream buffer
    ostringstream ssStreamBuffer2; // support stream buffer

    // stream to main buffer
    ssStreamBuffer0 << "\n\t// Virtual Functions\n";

    unsigned long long VfTable = (unsigned long long)(pClass->VfTableObject);

    for (unsigned long long i = 0x0; i < 0x800; i += 0x8)
    {
        // check if pointed function is the ProcessEvent
        if (TFLHACKT00LS::FindPattern(*(unsigned long long*)(VfTable + i), 0x400, (BYTE*)ProcessEvent_Pattern, (char*)ProcessEvent_Mask))
        {
            // stream to main buffer (virtual function ProcessEvent)
            ssStreamBuffer0 << "\tvirtual void ProcessEvent ( class UFunction* pFunction, void* pParms, void* pResult = NULL );\t\t\t\t// " << SDKMC_SSHEX((*(unsigned long long*)(VfTable + i)), 8) << " (" << SDKMC_SSHEX(i, 2) << ")\n";
        
            break;
        }
        else
        {
            // stream to main buffer (virtual functions padding)
            ssStreamBuffer0 << "\tvirtual void VirtualFunction" << SDKMC_SSDEC((i / 0x8), 2) << " ( );\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t// " << SDKMC_SSHEX((*(unsigned long long*)(VfTable + i)), 8) << " (" << SDKMC_SSHEX(i, 2) << ")\n";
        }
    }

    // print main stream buffer to file
    SDKFN_PRINT(pFile, ssStreamBuffer0);
}

// classes
void GenerateClass ( UClass* pClass )
{
    // stream buffers
    ostringstream ssStreamBuffer0; // main stream buffer
    ostringstream ssStreamBuffer1; // support stream buffer
    ostringstream ssStreamBuffer2; // support stream buffer

    // vars
    DWORD dwSize = 0;
    signed long dwLastOffset = 0;
    DWORD dwMissedOffset = 0;
    static bool bUObjectVfTableCommented = false;

    // get suoerfield
    UClass* pSuperClass = ( UClass* ) pClass->SuperField;
    
    // get class names
    string sClassName = GetValidName ( string ( pClass->GetName() ) );
    string sClassNameCPP = GetValidName ( string ( pClass->GetNameCPP() ) );
    string sClassFullName = string ( pClass->GetFullName() );

    // log
    fprintf ( pLog, "Class:        %-100s - instance: 0x%p\n", sClassName.c_str(), pClass );

    // property array
    vector< UProperty* > vProperty;
    
    // get class properties
    for ( UProperty* pProperty = (UProperty*) pClass->Children; pProperty; pProperty = (UProperty*) pProperty->Next )
    {
        if
        ( 
                ! pProperty->IsA ( UFunction::StaticClass() ) 
            &&	! pProperty->IsA ( UConst::StaticClass() )
            &&	! pProperty->IsA ( UEnum::StaticClass() )
            &&	! pProperty->IsA ( UScriptStruct::StaticClass() )
            &&	pProperty->ElementSize > 0
            && // additional checks for ME3
            (		
                    ! pSuperClass
                ||
                (
                    pSuperClass
                &&	pSuperClass != pClass
                &&  pProperty->Offset >= pSuperClass->PropertySize
                )	
            )
        )
        {			
            vProperty.push_back ( pProperty );	
        }
    }

    // sort vProperty array using pProperty -> Offset
    sort ( vProperty.begin(), vProperty.end(), SortProperty );

    // stream to main buffer (infos)
    ssStreamBuffer0 << "// " << sClassFullName << "\n";

    // print class
    if ( pSuperClass && pSuperClass != pClass )
    {
        // calculations
        dwSize = pClass->PropertySize - pSuperClass->PropertySize;
        dwLastOffset = pSuperClass->PropertySize;

        // get superfield name
        string sSuperClassNameCPP = GetValidName ( string ( pSuperClass->GetNameCPP() ) );

        // stream to main buffer (class size + class name)
        ssStreamBuffer0 << "// " << SDKMC_SSHEX ( dwSize, 4 ) << " (" << SDKMC_SSHEX ( pClass->PropertySize, 4 ) << " - " << SDKMC_SSHEX( pSuperClass->PropertySize, 4 ) << ")\n"
                        << "class " << sClassNameCPP << " : public " << sSuperClassNameCPP;
    }
    else
    {
        // calculations
        dwSize = pClass->PropertySize;

        // stream to main buffer (class size + class name)
        ssStreamBuffer0 << "// " << SDKMC_SSHEX ( dwSize, 4 ) << "\n"
                        << "class " << sClassNameCPP;
    }

    // stream to main buffer (class open)
    ssStreamBuffer0 << "\n{\npublic:\n";

    if ( false ) {}

    // special classes that need to be filled manualy
    #ifdef CLASS_PROPERTIES_UFIELD
    else if ( pClass == UObject::FindClass ( "Class Core.Field" ) )			        // UField
        ssStreamBuffer0 << CLASS_PROPERTIES_UFIELD;
    #endif

    #ifdef CLASS_PROPERTIES_UENUM
    else if ( pClass == UObject::FindClass ( "Class Core.Enum" ) )		            // UEnum
        ssStreamBuffer0 << CLASS_PROPERTIES_UENUM;
    #endif

    #ifdef CLASS_PROPERTIES_UCONST
    else if ( pClass == UObject::FindClass ( "Class Core.Const" ) )		            // UConst
        ssStreamBuffer0 << CLASS_PROPERTIES_UCONST;
    #endif

    #ifdef CLASS_PROPERTIES_USTRUCT
    else if ( pClass == UObject::FindClass ( "Class Core.Struct" ) )		        // UStruct
        ssStreamBuffer0 << CLASS_PROPERTIES_USTRUCT;
    #endif

    #ifdef CLASS_PROPERTIES_USCRIPTSTRUCT
    else if ( pClass == UObject::FindClass ( "Class Core.ScriptStruct" ) )          // UScriptStruct
        ssStreamBuffer0 << CLASS_PROPERTIES_USCRIPTSTRUCT;
    #endif

    #ifdef CLASS_PROPERTIES_UFUNCTION
    else if ( pClass == UObject::FindClass ( "Class Core.Function" ) )		        // UFunction
        ssStreamBuffer0 << CLASS_PROPERTIES_UFUNCTION;
    #endif

    #ifdef CLASS_PROPERTIES_USTATE
    else if ( pClass == UObject::FindClass ( "Class Core.State" ) )		            // UState
        ssStreamBuffer0 << CLASS_PROPERTIES_USTATE;
    #endif

    #ifdef CLASS_PROPERTIES_UPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.Property" ) )		        // UProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_UBYTEPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.ByteProperty" ) )		    // UByteProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UBYTEPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_UBOOLPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.BoolProperty" ) )		    // UBoolProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UBOOLPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_UDELEGATEPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.DelegateProperty" ) )	    // UDelegateProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UDELEGATEPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_UOBJECTPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.ObjectProperty" ) )	    // UObjectProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UOBJECTPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_UCLASSPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.ClassProperty" ) )	        // UClassProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UCLASSPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_UINTERFACEPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.InterfaceProperty" ) )	    // UInterfaceProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UINTERFACEPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_USTRUCTPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.StructProperty" ) )	    // UStructProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_USTRUCTPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_UARRAYPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.ArrayProperty" ) )	        // UArrayProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UARRAYPROPERTY;
    #endif

    #ifdef CLASS_PROPERTIES_UMAPPROPERTY
    else if ( pClass == UObject::FindClass ( "Class Core.MapProperty" ) )	        // UMapProperty
        ssStreamBuffer0 << CLASS_PROPERTIES_UMAPPROPERTY;
    #endif

    else																	        // normal classes
    {
        // property unique name array
        StrIntM_t mPropertyName;		

        // unknown data unique name index
        int UnknownDataIndex = 0;

        // process class properties
        for ( unsigned int i = 0; i < vProperty.size(); i++ )
        {
            UProperty* pProperty = vProperty[ i ];

            // fix missed offsets
            if ( dwLastOffset < pProperty->Offset )
            {
                dwMissedOffset = pProperty->Offset - dwLastOffset;

                // fix only if missed offset >= CLASS_ALIGN
                if ( dwMissedOffset >= CLASS_ALIGN ) 
                {
                    // stream to support buffer
                    ssStreamBuffer1 << "UnknownData" << SDKMC_SSDEC ( UnknownDataIndex, 2 ) << "[ " << SDKMC_SSHEX ( dwMissedOffset, 0 ) << " ];";
                    
                    // stream to main buffer
                    ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( "unsigned char", SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                    << "\t\t// " << SDKMC_SSHEX ( dwLastOffset, 4 ) << " (" << SDKMC_SSHEX ( dwMissedOffset, 4 ) << ") MISSED OFFSET\n";

                    // empty support buffer
                    SDKFN_EMPTY ( ssStreamBuffer1 );
                
                    UnknownDataIndex++;
                }
            }

            // declare property type
            string sPropertyType;

            // strem properties to main buffer
            if ( GetPropertyType ( pProperty, sPropertyType ) )
            {
                // get correct element size
                unsigned long dwCorrectElementSize = GetPropertySize ( pProperty );
                
                // get property name
                string sPropertyName = GetValidName ( string ( pProperty->GetName() ) );

                // check unique var name
                if ( mPropertyName.count ( sPropertyName ) == 0 ) // not exist
                {
                    // insert in unique name array
                    mPropertyName[ sPropertyName ] = 1;

                    // stream to support buffer (property name)
                    ssStreamBuffer1 << sPropertyName;
                }
                else
                {
                    // stream to support buffer (name + index)
                    ssStreamBuffer1 << sPropertyName << SDKMC_SSDEC ( mPropertyName[ sPropertyName ], 2 );
                    
                    // incremente name usage count
                    mPropertyName[ sPropertyName ]++;
                }

                // special case array
                if ( pProperty->ArrayDim > 1 )
                {
                    // stream to support buffer
                    ssStreamBuffer1 << "[ " << SDKMC_SSHEX ( pProperty->ArrayDim, 0 ) << " ]";
                }

                // special case bool
                if ( pProperty->IsA ( UBoolProperty::StaticClass() ) ) 
                {
                    // stream to support buffer
                    ssStreamBuffer1 << " : 1";
                }

                // stream to support buffer
                ssStreamBuffer1 << ";";

                // stream property flags to support stream
                GetAllPropertyFlags ( pProperty->PropertyFlags, ssStreamBuffer2 );

                // comment out the VfTableObject in UObject
                if (		! bUObjectVfTableCommented
                        &&	! strcmp(sClassNameCPP.c_str(), "UObject")
                        &&  ! strcmp(sPropertyName.c_str(), "VfTableObject") )
                {
                    bUObjectVfTableCommented = true;
                    ssStreamBuffer0 << "\t// ";
                }

                // stream to main buffer
                ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( sPropertyType, SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                << "\t\t// " << SDKMC_SSHEX ( pProperty->Offset, 4 ) << " (" << SDKMC_SSHEX ( ( pProperty->ElementSize * pProperty->ArrayDim ), 4 ) << ") [" << SDKMC_SSHEX ( pProperty->PropertyFlags, 16 ) << "]";

                // stream to main buffer (bitmask)
                if ( pProperty->IsA ( UBoolProperty::StaticClass() ) ) 
                {
                    // stream to support buffer
                    ssStreamBuffer0 << " [" << SDKMC_SSHEX ( ( (UBoolProperty*) pProperty )->BitMask, 8 ) << "] ";
                }
                else
                {
                    ssStreamBuffer0 << SDKMC_SSCOL ( "", 14 ); // empty space
                }

                ssStreamBuffer0 << ssStreamBuffer2.str() << "\n";
                
                // empty support buffers
                SDKFN_EMPTY( ssStreamBuffer1 );
                SDKFN_EMPTY( ssStreamBuffer2 );	

                // check if property size and type size are egual otherwise add pad data
                int nOffserError = ( pProperty->ElementSize * pProperty->ArrayDim ) - ( dwCorrectElementSize * pProperty->ArrayDim );

                // correct wrong size elements
                if ( nOffserError > 0 )
                {
                    // stream to support buffer
                    ssStreamBuffer1 << "UnknownData" << SDKMC_SSDEC ( UnknownDataIndex, 2 ) << "[ " << SDKMC_SSHEX ( nOffserError, 0 ) << " ];";

                    // stream to main buffer
                    ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( "unsigned char", SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                    << "\t\t// " << SDKMC_SSHEX ( ( pProperty->Offset + nOffserError ), 4 ) << " (" << SDKMC_SSHEX ( nOffserError, 4 ) << ") FIX WRONG TYPE SIZE OF PREVIUS PROPERTY\n";

                    // empty support buffers
                    SDKFN_EMPTY ( ssStreamBuffer1 );
                
                    UnknownDataIndex++;
                }
            }
            else
            {
                // stream to support buffer
                ssStreamBuffer1 << "UnknownData" << SDKMC_SSDEC ( UnknownDataIndex, 2 ) << "[ " << SDKMC_SSHEX ( ( pProperty->ElementSize * pProperty->ArrayDim ), 0 ) << " ];";

                // stream to main buffer
                ssStreamBuffer0 << "\t" << SDKMC_SSCOL( "unsigned char", SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                << "\t\t// " << SDKMC_SSHEX ( pProperty->Offset, 4 ) << " (" << SDKMC_SSHEX ( ( pProperty->ElementSize * pProperty->ArrayDim ), 4 ) << ") UNKNOWN PROPERTY: " << string ( pProperty->GetFullName() ) << "\n";

                // empty support buffer
                SDKFN_EMPTY ( ssStreamBuffer1 );

                UnknownDataIndex++;
            }

            // calc new last offset
            dwLastOffset = pProperty->Offset + ( pProperty->ElementSize * pProperty->ArrayDim );
        }

        // fix last missed offsets
        if ( dwLastOffset < pClass->PropertySize )
        {
            dwMissedOffset = pClass->PropertySize - dwLastOffset;

            // fix only if missed offset >= CLASS_ALIGN
            if ( dwMissedOffset >= CLASS_ALIGN ) 
            {
                // stream to support buffer
                ssStreamBuffer1 << "UnknownData" << SDKMC_SSDEC ( UnknownDataIndex, 2 ) << "[ " << SDKMC_SSHEX ( dwMissedOffset, 0 ) << " ];";

                // stream to main buffer
                ssStreamBuffer0 << "\t" << SDKMC_SSCOL ( "unsigned char", SDK_COL1 ) << " " << SDKMC_SSCOL ( ssStreamBuffer1.str(), SDK_COL2 ) 
                                << "\t\t// " << SDKMC_SSHEX ( dwLastOffset, 4 ) << " (" << SDKMC_SSHEX ( dwMissedOffset, 4 ) << ") MISSED OFFSET\n";

                // empty support buffer
                SDKFN_EMPTY ( ssStreamBuffer1 );
            }
        }
    }

    // stream to main buffer
    ssStreamBuffer0 << "\nprivate:\n"
                    << "\tstatic UClass* pClassPointer;\n\n"	// static class pointer
                    << "public:\n"; 
    
    // print basic functions declaretion
    if ( pClass == UObject::FindClass ( "Class Core.Object" ) )
        ssStreamBuffer0 << BASIC_FUNCTIONS_DEC;

    // stream to main buffer (static class function)
    if ( SDK_NO_STR )
    {
        ssStreamBuffer0 << "\tstatic UClass* StaticClass();\n\n";
    }
    else
    {
        ssStreamBuffer0 << "\tstatic UClass* StaticClass();\n\n";
    }

    // print main stream buffer to file
    SDKFN_PRINT ( pFile, ssStreamBuffer0 );
    
    // print functions declaration
    GenerateFuncDec ( pClass );

    // print virtual functions
    if ( pClass == UObject::FindClass ( "Class Core.Object" ) )
        GenerateVirtualFunc ( pClass );

    // stream to main buffer
    ssStreamBuffer0 << "};\n\n";

    // print main stream buffer to file
    SDKFN_PRINT ( pFile, ssStreamBuffer0 );
}

void GenerateClassPre ( UClass* pClass, UObject* pPackageToProcess )
{
    UObject* pPackageObject = pClass->GetPackageObj();
    
    if ( ! pPackageObject )	// check package object (needed 'cause this function is recursive)
        return;

    // put PackagetoProcess in include vector (if not present)
    if ( find ( vIncludes.begin(), vIncludes.end(), pPackageToProcess ) == vIncludes.end() )
        vIncludes.push_back ( pPackageToProcess );


    if ( pPackageObject != pPackageToProcess )	// that means that the required class is in another package
    {
        // check if pPackageObject exist and is already before pPackageToProcess
        vector< UObject* >::iterator itPO = find ( vIncludes.begin(), vIncludes.end(), pPackageObject );
        vector< UObject* >::iterator itPTP = find ( vIncludes.begin(), vIncludes.end(), pPackageToProcess );
    
        if ( itPO == vIncludes.end() )	// required class package not present
        {
            // insert pPackageObject before pPackageToProcess
            vIncludes.insert ( itPTP, pPackageObject );
        }
        else if ( itPO >= itPTP )	// required class package is after this package
        {
            // insert pPackageObject before pPackageToProcess
            vIncludes.insert ( itPTP, pPackageObject );

            // delete old one
            vIncludes.erase ( itPO );
        }

        return;
    }

    // generated script structs
    static vector< string > vGenClass;

    // init property names
    string sClassName = GetValidName ( string ( pClass->GetName() ) );
    string sClassFullName = string ( pClass->GetFullName() );
    
    // remove default class
    if ( sClassName.find ( "Default__" ) != string::npos )
        return;

    // check if already generated
    if ( find ( vGenClass.begin(), vGenClass.end(), string ( pClass->GetFullName() ) ) == vGenClass.end() ) // not generated
    {	
        // check superfield prerequisites
        if 
        ( 
                pClass->SuperField 
            &&	pClass->SuperField != pClass
            &&  find ( vGenClass.begin(), vGenClass.end(), string ( pClass->SuperField->GetFullName() ) ) == vGenClass.end() // not generated
        )
        {
            // generate superfield class
            GenerateClassPre ( (UClass*) ( pClass->SuperField ), pPackageToProcess );
        }

        // prerequisites ended
        GenerateClass ( pClass );
        vGenClass.push_back ( sClassFullName );
    }
}

/*
# ========================================================================================= #
# Process Objects by Package															
# ========================================================================================= #
*/

void ProcessScriptStructsByPackage ( UObject* pPackageToProcess )
{
    for ( int i = 0; i < UObject::GObjObjects()->Num(); i++ )
    {
        // get object
        UObject* pObject = UObject::GObjObjects()->Data[ i ];
        
        if ( ! pObject )
            continue;

        // get package object
        UObject* pPackageObject = pObject->GetPackageObj();

        if ( ! pPackageObject )
            continue;

        // ScriptStruct
        if
        (
                pPackageObject == pPackageToProcess
            &&	pObject->IsA ( UScriptStruct::StaticClass() )
        )
        {
            GenerateScriptStructPre ( (UScriptStruct*) pObject, pPackageToProcess );
        }
    }
}

void ProcessConstsByPackage ( UObject* pPackageToProcess )
{	
    for ( int i = 0; i < UObject::GObjObjects()->Num(); i++ )
    {
        // get object
        UObject* pObject = UObject::GObjObjects()->Data[ i ];
        
        if ( ! pObject )
            continue;

        // get package object
        UObject* pPackageObject = pObject->GetPackageObj();

        if ( ! pPackageObject )
            continue;

        // Const
        if
        (
                pPackageObject == pPackageToProcess
            &&	pObject->IsA ( UConst::StaticClass() )
        )
        {
            GenerateConst ( (UConst*) pObject );
        }
    }
}

void ProcessEnumsByPackage ( UObject* pPackageToProcess )
{
    for ( int i = 0; i < UObject::GObjObjects()->Num(); i++ )
    {
        // get object
        UObject* pObject = UObject::GObjObjects()->Data[ i ];
        
        if ( ! pObject )
            continue;

        // get package object
        UObject* pPackageObject = pObject->GetPackageObj();

        if ( ! pPackageObject )
            continue;

        // Enum
        if
        (
                pPackageObject == pPackageToProcess
            &&	pObject->IsA ( UEnum::StaticClass() )
        )
        {
            GenerateEnum ( (UEnum*) pObject );
        }
    }
}

void ProcessClassesByPackage ( UObject* pPackageToProcess )
{
    for ( int i = 0; i < UObject::GObjObjects()->Num(); i++ )
    {
        // get object
        UObject* pObject = UObject::GObjObjects()->Data[ i ];
        
        if ( ! pObject )
            continue;

        // get package object
        UObject* pPackageObject = pObject->GetPackageObj();
        
        if ( ! pPackageObject )
            continue;

        // Class
        if
        (
                pPackageObject == pPackageToProcess
            &&	pObject->IsA ( UClass::StaticClass() )
        )
        {
            GenerateClassPre ( (UClass*) pObject, pPackageToProcess );
        }
    }
}

void ProcessFuncStructsByPackage ( UObject* pPackageToProcess )
{
    for ( int i = 0; i < UObject::GObjObjects()->Num(); i++ )
    {
        // get object
        UObject* pObject = UObject::GObjObjects()->Data[ i ];
        
        if ( ! pObject )
            continue;

        // get package object
        UObject* pPackageObject = pObject->GetPackageObj();

        if ( ! pPackageObject )
            continue;

        // Class
        if
        (
                pPackageObject == pPackageToProcess
            &&	pObject->IsA ( UClass::StaticClass() )
        )
        {
            GenerateFuncStruct ( (UClass*) pObject );
        }
    }
}

void ProcessFuncsByPackage ( UObject* pPackageToProcess )
{
    for ( int i = 0; i < UObject::GObjObjects()->Num(); i++ )
    {
        // get object
        UObject* pObject = UObject::GObjObjects()->Data[ i ];
        
        if ( ! pObject )
            continue;

        // get package object
        UObject* pPackageObject = pObject->GetPackageObj();
        
        if ( ! pPackageObject )
            continue;

        // Class
        if
        (
                pPackageObject == pPackageToProcess
            &&	pObject->IsA ( UClass::StaticClass() )
        )
        {
            GenerateFuncDef ( (UClass*) pObject );
        }
    }
}

void ProcessPackages()
{
    // create packages array
    vector< UObject* > vPackages;
    
    // loop objects and process packages
    for ( int i = 0; i < UObject::GObjObjects()->Num(); i++ )
    {
        // get object
        UObject* pObject = UObject::GObjObjects()->Data[ i ];
        
        if ( ! pObject )
            continue;

        if ( pObject->IsA ( UClass::StaticClass() ) )
        {
            // get package object
            UObject* pPackageObject = pObject->GetPackageObj();
            
            if ( ! pPackageObject )
                continue;

            // process package if not
            if ( find ( vPackages.begin(), vPackages.end(), pPackageObject ) == vPackages.end() ) // not found
            {
                vPackages.push_back ( pPackageObject );

                // create new structs package header file
                sprintf_s ( cBuffer, "%s\\%s\\SDK_HEADERS\\%s_structs.hpp", sOutputDir, GAME_NAME_S, pPackageObject->GetName() );
                fopen_s ( &pFile, cBuffer, "w+" );
            
                sprintf_s ( cBuffer, "%s_structs", pPackageObject->GetName() );
                PrintFileHeder ( cBuffer, "hpp", true, false );

                PrintSectionHeader ( "Script Structs" );
                ProcessScriptStructsByPackage ( pPackageObject );

                PrintFileFooter();
                fclose ( pFile );

                // create new classes package header file
                sprintf_s ( cBuffer, "%s\\%s\\SDK_HEADERS\\%s_classes.hpp", sOutputDir, GAME_NAME_S, pPackageObject->GetName() );
                fopen_s ( &pFile, cBuffer, "w+" );
            
                sprintf_s ( cBuffer, "%s_classes", pPackageObject->GetName() );
                PrintFileHeder ( cBuffer, "hpp", true, false);
            
                PrintSectionHeader ( "Constants" );
                ProcessConstsByPackage ( pPackageObject );

                PrintSectionHeader ( "Enums" );
                ProcessEnumsByPackage ( pPackageObject );

                PrintSectionHeader ( "Classes" );
                ProcessClassesByPackage ( pPackageObject );

                PrintFileFooter();
                fclose ( pFile );

                // create new function structs package header file
                sprintf_s ( cBuffer, "%s\\%s\\SDK_HEADERS\\%s_f_structs.hpp", sOutputDir, GAME_NAME_S, pPackageObject->GetName() );
                fopen_s ( &pFile, cBuffer, "w+" );
            
                sprintf_s ( cBuffer, "%s_f_structs", pPackageObject->GetName() );
                PrintFileHeder ( cBuffer, "hpp", true, false);
            
                PrintSectionHeader ( "Function Structs" );
                ProcessFuncStructsByPackage ( pPackageObject );

                PrintFileFooter();
                fclose ( pFile );

                // create new function package header file
                sprintf_s ( cBuffer, "%s\\%s\\SDK_HEADERS\\%s_functions.cpp", sOutputDir, GAME_NAME_S, pPackageObject->GetName() );
                fopen_s ( &pFile, cBuffer, "w+" );
            
                sprintf_s ( cBuffer, "%s_functions", pPackageObject->GetName() );
                PrintFileHeder ( cBuffer, "cpp", true, true );
            
                // print basic functions
                if ( pPackageObject == UObject::FindClass ( "Class Core.Object" )->GetPackageObj() )
                { 
                    PrintSectionHeader ( "Basic Functions" );
                    fprintf ( pFile, BASIC_FUNCTIONS_DEF ); 
                }

                PrintSectionHeader ( "Functions" );
                ProcessFuncsByPackage ( pPackageObject );

                PrintFileFooter();
                fclose ( pFile );
            }
        }
    }
}

/*
# ========================================================================================= #
# Initialization														
# ========================================================================================= #
*/

void Init_Core()
{
    auto const moduleBase = Common::GetModuleBaseAddress(LEx_MODULE_NAME);
    //auto const moduleBase = Common::GetFirstModuleBaseAddress();

    GBioNamePools = &*(FNameEntry**)(moduleBase + LEx_NAME_POOLS);
    fprintf(pLog, "GBioNamePools: 0x%p\n", GBioNamePools);
    
    GObjects = &*(TArray<UObject*>*)(moduleBase + LEx_OBJOBJECTS);
    fprintf(pLog, "GObjects: 0x%p\n", GObjects);

    fprintf(pLog, "\n");
}

/*
# ========================================================================================= #
# Finalization														
# ========================================================================================= #
*/

void Final_SdkHeaders()
{
    // init main header file
    sprintf_s ( cBuffer, "%s\\%s\\SdkHeaders.hpp", sOutputDir, GAME_NAME_S );
    fopen_s ( &pFile, cBuffer, "w+" );

    PrintFileHeder ( "SdkHeaders", "hpp" );
    PrintSectionHeader ( "Includes" );
    
    for ( unsigned int i = 0; i < vIncludes.size(); i++ )
    {
        fprintf ( pFile, "#include \"%s\\%s_structs.hpp\"\n",       LE_SHORTHAND, vIncludes[i]->GetName() );
        fprintf ( pFile, "#include \"%s\\%s_classes.hpp\"\n",       LE_SHORTHAND, vIncludes[i]->GetName() );		
        fprintf ( pFile, "#include \"%s\\%s_f_structs.hpp\"\n",     LE_SHORTHAND, vIncludes[i]->GetName() );		
        fprintf ( pFile, "// #include \"%s\\%s_functions.cpp\"\n",  LE_SHORTHAND, vIncludes[i]->GetName() );
    }

    fclose ( pFile );
}

/*
# ========================================================================================= #
# DllMain														
# ========================================================================================= #
*/

void OnAttach()
{
    FILE* pConfigFile = nullptr;
    fopen_s ( &pConfigFile, SDK_CONFIG_PATH, "r" );
    fread ( sOutputDir, 1, sizeof ( sOutputDir ), pConfigFile );
    fclose ( pConfigFile );

    OutputDebugStringA ( "Configured output directory:" );
    OutputDebugStringA ( sOutputDir );

    Sleep ( 40000 );

    if (bAbortRun)
    {
        // Attach thread was aborted by process termination.
        return;
    }
    
    // times
    SYSTEMTIME stST, stET;
    FILETIME ftST, ftET;
    ULARGE_INTEGER nST, nET;
    
    float fDiff;

    // mkdir base dir
    _mkdir ( sOutputDir );

    // mkdir sdk dir
    sprintf_s ( cBuffer, "%s\\%s", sOutputDir, GAME_NAME_S );
    _mkdir ( cBuffer );

    // mkdir sdk headers
    sprintf_s ( cBuffer, "%s\\%s\\SDK_HEADERS", sOutputDir, GAME_NAME_S );
    _mkdir ( cBuffer );

    // open log
    sprintf_s ( cBuffer, "%s\\%s\\UE3SdkGenerator.log", sOutputDir, GAME_NAME_S );
    fopen_s ( &pLog, cBuffer, "w+" );

    // get start time
    GetSystemTime ( &stST );

    // initialize
    fprintf(pLog, "\nStarting Init_Core\n");
    Init_Core();
    fprintf(pLog, "\nReturned from Init_Core\n");

    // process packages
    fprintf(pLog, "\nStarting ProcessPackages\n");
    ProcessPackages();
    fprintf(pLog, "\nReturned from ProcessPackages\n");

    // finalize
    fprintf(pLog, "\nStarting Final_SdkHeaders\n");
    Final_SdkHeaders();
    fprintf(pLog, "\nReturned from Final_SdkHeaders\n");

    // get end time
    GetSystemTime ( &stET );

    // calc delta time
    SystemTimeToFileTime ( &stST, &ftST );
    nST.HighPart = ftST.dwHighDateTime;
    nST.LowPart = ftST.dwLowDateTime;
    
    SystemTimeToFileTime ( &stET, &ftET );
    nET.HighPart = ftET.dwHighDateTime;
    nET.LowPart = ftET.dwLowDateTime;

    fDiff = ( nET.QuadPart - nST.QuadPart ) / 10000.0f / 1000.0f;	// seconds

    // print generation time
    fprintf ( pLog, "\nSDK Generated in %.3f seconds\n", fDiff );

    // close log
    fclose ( pLog );
}

BOOL WINAPI DllMain ( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
    switch ( dwReason )
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls ( hModule );
            CreateThread ( NULL, 0, ( LPTHREAD_START_ROUTINE ) OnAttach, NULL, 0, NULL );
            break;
        case DLL_PROCESS_DETACH:
            bAbortRun = true;
            break;
    }

    return TRUE;
}
