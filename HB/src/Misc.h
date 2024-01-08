//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include "GlobalDef.h"
#include <cstdint>

enum { CODE_ENG, CODE_HAN1, CODE_HAN2 };

class CGame;

class CMisc
{
public:
    int iGetTextLengthLoc(CGame * game, char * pStr, int iLength);
    bool bCheckValidName(char * pStr);
    bool bCheckIMEString(char * str);
    bool bDecode(char cKey, char * pStr);
    bool bEncode(char cKey, char * pStr);
    void ColorTransfer(char cPixelFormat, uint32_t fcolor, uint16_t * wR, uint16_t * wG, uint16_t * wB);
    char cCalcDirection(short sX, short sY, short dX, short dY);
    void ReplaceString(char * pStr, char cFrom, char cTo);
    bool bCheckValidString(char * str);
    void GetDirPoint(char cDir, int * pX, int * pY);
    void GetPoint(int x0, int y0, int x1, int y1, int * pX, int * pY, int * pError, int iCount);
    char cGetNextMoveDir(short sX, short sY, short dX, short dY);
    bool bIsValidSSN(char * pStr);
    bool bIsValidEmail(char * pStr);
    CMisc();
    virtual ~CMisc();
};
