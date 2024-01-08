//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include <cstdint>
#include <ctime>
#include "polyfill.h"

#define DEF_MAXRECTS 30
#define DEF_MIRESULT_NONE 0
#define DEF_MIRESULT_PRESS 1
#define DEF_MIRESULT_CLICK 2

class CMouseInterface
{
public:
    int iGetStatus(int msX, int msY, char cLB, char * pResult);
    void AddRect(long sx, long sy, long dx, long dy);
    CMouseInterface();
    virtual ~CMouseInterface();
    RECT * m_pRect[DEF_MAXRECTS];
    char m_cPrevPress;
    uint64_t m_dwTime;
};
