#pragma comment(lib, "Psapi.lib")

#include <Windows.h>
#include <Psapi.h>
#include "../Common.h"

namespace TFLHACKT00LS
{
    //===========================================================================//
    //==== GetModuleInfo - Get Module Base, Module Size, Module Entry Point =====//
    //===========================================================================//

    MODULEINFO GetModuleInfo ( LPCTSTR lpModuleName );

    //===========================================================================//
    //==== FindPattern ==========================================================//
    //===========================================================================//

    unsigned long long FindPattern(unsigned long long startAddres, unsigned long long fileSize, PBYTE pattern, char mask[]);
}
