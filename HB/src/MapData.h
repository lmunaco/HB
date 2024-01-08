//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include <cstdint>
#include "Tile.h"
#include "ActionID.h"
#include "Game.h"
#include "TileSpr.h"

#define MAPDATASIZEX	40
#define MAPDATASIZEY	35

class CMapData
{
public:
    CMapData(class CGame * pGame);
    virtual ~CMapData();
    void Init();
    void OpenMapDataFile(char * cFn);
    void GetOwnerStatusByObjectID(uint16_t wObjectID, char * pOwnerType, char * pDir, short * pAppr1, short * pAppr2, short * pAppr3, short * pAppr4, int * pStatus, int * pColor, char * pName);
    void ClearDeadChatMsg(short sX, short sY);
    void ClearChatMsg(short sX, short sY);
    void ShiftMapData(char cDir);
    void _bDecodeMapInfo(char * pHeader);
    bool __fastcall bSetChatMsgOwner(uint16_t wObjectID, short sX, short sY, int iIndex);
    bool __fastcall bSetDeadOwner(uint16_t wObjectID, short sX, short sY, short sType, char cDir, short sAppr1, short sAppr2, short sAppr3, short sAppr4, int iApprColor, int iStatus, char * pName);
    bool __fastcall bGetDeadOwner(short sX, short sY, short * pOwnerType, char * pDir, short * pAppr1, short * pAppr2, short * pAppr3, short * pAppr4, int * pApprColor, char * pFrame, char * pName, short * pItemSprite, short * pItemSpriteFrame, int * pCharIndex);
    bool __fastcall bGetOwner(short sX, short sY, short * pOwnerType, char * pDir, short * pAppr1, short * pAppr2, short * pAppr3, short * pAppr4, int * pApprColor, int * pStatus, char * pName, char * pAction, char * pFrame, int * pChatIndex, short * pV1, short * pV2);
    bool __fastcall bSetOwner(uint16_t wObjectID, int sX, int sY, int sType, int cDir, short sAppr1, short sAppr2, short sAppr3, short sAppr4, int iApprColor, int iStatus, char * pName, short sAction, short sV1, short sV2, short sV3, int iPreLoc = 0, int iFrame = 0);
    bool __fastcall bGetOwner(short sX, short sY, char * pName, short * pOwnerType, int * pOwnerStatus, uint16_t * pObjectID);
    bool bSetDynamicObject(short sX, short sY, uint16_t wID, short sType, bool bIsEvent);
    bool bIsTeleportLoc(short sX, short sY);
    bool bGetIsLocateable(short sX, short sY);
    bool bSetItem(short sX, short sY, short sItemSpr, short sItemSprFrame, char cItemColor, bool bDropEffect = true);
    int  iObjectFrameCounter(char * cPlayerName, short sViewPointX, short sViewPointY);

    CTile m_pData[MAPDATASIZEX][MAPDATASIZEY];
    CTile m_pTmpData[MAPDATASIZEX][MAPDATASIZEY];
    CTileSpr m_tile[752][752];
    CGame * m_pGame;

    struct
    {
        short m_sMaxFrame;
        short m_sFrameTime;
    } m_stFrame[DEF_TOTALCHARACTERS][DEF_TOTALACTION];
    uint64_t m_dwFrameTime;
    uint64_t m_dwDOframeTime;
    uint64_t m_dwFrameCheckTime;
    int m_iObjectIDcacheLocX[30000];
    int m_iObjectIDcacheLocY[30000];
    uint64_t m_dwFrameAdjustTime;
    short m_sMapSizeX, m_sMapSizeY;
    short m_sRectX, m_sRectY;
    short m_sPivotX, m_sPivotY;
};
