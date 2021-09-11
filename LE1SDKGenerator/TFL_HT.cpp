#include "TFL_HT.h"

namespace TFLHACKT00LS
{
	//===========================================================================//
	//==== GetModuleInfo - Get Module Base, Module Size, Module Entry Point =====//
	//===========================================================================//

	MODULEINFO GetModuleInfo ( LPCTSTR lpModuleName )
	{
		MODULEINFO miInfos = { NULL };

		HMODULE hmModule = GetModuleHandle ( lpModuleName );

		if ( hmModule )
		{
			GetModuleInformation ( GetCurrentProcess(), hmModule, &miInfos, sizeof ( MODULEINFO ) );
		}

		return miInfos;
	}

	//===========================================================================//
	//==== FindPattern ==========================================================//
	//===========================================================================//

	unsigned long long FindPattern ( unsigned long long startAddres, unsigned long long fileSize, PBYTE pattern, char mask[] )
	{
		unsigned long long pos = 0;
		unsigned long long searchLen = strlen ( mask ) - 1;

		for (unsigned long long retAddress = startAddres; retAddress < startAddres + fileSize; retAddress++ )
		{
			if ( *(PBYTE) retAddress == pattern[ pos ] || mask[ pos ] == '?' )
			{
				if ( mask[ pos + 1 ] == '\0' )
				{
					return ( retAddress - searchLen );
				}
					
				pos++;
			} 
			else
			{
				pos = 0;
			}		
		}

		return NULL;
	}
}