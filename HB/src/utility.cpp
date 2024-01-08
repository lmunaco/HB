//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include <cstdint>
#include <chrono>
#include "polyfill.h"

using namespace std::chrono;
using namespace std::chrono_literals;

uint64_t unixtime()
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

uint32_t unixseconds()
{
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

void SetRect(RECT & lprc, int xLeft, int yTop, int xRight, int yBottom)
{
    lprc.left = xLeft;
    lprc.top = yTop;
    lprc.right = xRight;
    lprc.bottom = yBottom;
}
