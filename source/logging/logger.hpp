#pragma once

#include <Windows.h>

namespace rise::logging
{
    inline void print( const char* text )
    {
        OutputDebugStringA( text );
        OutputDebugStringA( "\n" );
    }
}
