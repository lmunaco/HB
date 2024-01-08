//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include <memory>

#ifndef _WIN32
using RECT = struct tagRECT
{
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
};
#else
#include <windows.h>
#endif

#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif

using stBrush = struct stBrushtag
{
    short sx;
    short sy;
    short szx;
    short szy;
    short pvx;
    short pvy;
};
