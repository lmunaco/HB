//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include "Game.h"
#include "lan_eng.h"

extern uint64_t unixtime();
extern uint64_t unixseconds();

void CGame::MotionResponseHandler(char * pData)
{
    uint16_t * wp, wResponse;
    short * sp, sX, sY;
    char * cp, cDir;
    int * ip, iPreHP;
    //						          0 3        4 5						 6 7		8 9		   10	    11
    // Confirm Code(4) | MsgSize(4) | MsgID(4) | DEF_OBJECTMOVE_CONFIRM(2) | Loc-X(2) | Loc-Y(2) | Dir(1) | MapData ...
    // Confirm Code(4) | MsgSize(4) | MsgID(4) | DEF_OBJECTMOVE_REJECT(2)  | Loc-X(2) | Loc-Y(2)
    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    wResponse = *wp;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    switch (wResponse)
    {
        case DEF_OBJECTMOTION_CONFIRM:
            m_cCommandCount--;
            break;

        case DEF_OBJECTMOTION_ATTACK_CONFIRM:
            m_cCommandCount--;
            break;

        case DEF_OBJECTMOTION_REJECT:

            if (m_iHP <= 0) return;

            sp = (short *)cp;
            m_sPlayerX = *sp;
            cp += 2;

            sp = (short *)cp;
            m_sPlayerY = *sp;
            cp += 2;

            m_cCommand = DEF_OBJECTSTOP;
            m_sCommX = m_sPlayerX;
            m_sCommY = m_sPlayerY;

            m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
                m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
                m_iPlayerStatus, m_cPlayerName,
                DEF_OBJECTSTOP, 0, 0, 0);
            m_cCommandCount = 0;
            m_bIsGetPointingMode = false;
            m_sViewDstX = m_sViewPointX = (m_sPlayerX - 10) * 32;
            m_sViewDstY = m_sViewPointY = (m_sPlayerY - 7) * 32;

            m_bIsRedrawPDBGS = true;
            break;

        case DEF_OBJECTMOVE_CONFIRM:
            sp = (short *)cp;
            sX = *sp;
            cp += 2;
            sp = (short *)cp;
            sY = *sp;
            cp += 2;
            cDir = *cp;
            cp++;
            m_iSP = m_iSP - *cp;
            cp++;
            if (m_iSP < 0) m_iSP = 0;
            // v1.3
            //m_iOccupyStatus = (int)*cp;
            cp++;
            // v1.4
            iPreHP = m_iHP;
            ip = (int *)cp;
            m_iHP = *ip;
            cp += 4;

            if (m_iHP != iPreHP)
            {
                if (m_iHP < iPreHP)
                {
                    wsprintfA(G_cTxt, NOTIFYMSG_HP_DOWN, iPreHP - m_iHP);
                    AddEventList(G_cTxt, 10);
                    m_dwDamagedTime = unixtime();
                    if ((m_cLogOutCount > 0) && (m_bForceDisconn == false))
                    {
                        m_cLogOutCount = -1;
                        AddEventList(MOTION_RESPONSE_HANDLER2, 10);
                    }
                }
                else
                {
                    wsprintfA(G_cTxt, NOTIFYMSG_HP_UP, m_iHP - iPreHP);
                    AddEventList(G_cTxt, 10);
                }
            }
            m_pMapData->ShiftMapData(cDir);
            _ReadMapData(sX, sY, cp);
            m_bIsRedrawPDBGS = true;
            m_cCommandCount--;
            break;

        case DEF_OBJECTMOVE_REJECT:
            if (m_iHP <= 0) return;
            wp = (uint16_t *)cp;
            if (m_sPlayerObjectID != *wp) return;
            cp += 2;
            sp = (short *)cp;
            m_sPlayerX = *sp;
            cp += 2;
            sp = (short *)cp;
            m_sPlayerY = *sp;
            cp += 2;
            sp = (short *)cp;
            m_sPlayerType = *sp;
            cp += 2;
            m_cPlayerDir = *cp;
            cp++;
            //memcpy(cName, cp, 10);
            cp += 10;
            sp = (short *)cp;
            m_sPlayerAppr1 = *sp;
            cp += 2;
            sp = (short *)cp;
            m_sPlayerAppr2 = *sp;
            cp += 2;
            sp = (short *)cp;
            m_sPlayerAppr3 = *sp;
            cp += 2;
            sp = (short *)cp;
            m_sPlayerAppr4 = *sp;
            cp += 2;
            ip = (int *)cp;
            m_iPlayerApprColor = *ip;
            cp += 4;
            ip = (int *)cp;
            m_iPlayerStatus = *ip;
            cp += 4;
            m_cCommand = DEF_OBJECTSTOP;
            m_sCommX = m_sPlayerX;
            m_sCommY = m_sPlayerY;
            m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
                m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor, // v1.4
                m_iPlayerStatus, m_cPlayerName,
                DEF_OBJECTSTOP, 0, 0, 0,
                0, 7);
            m_cCommandCount = 0;
            m_bIsGetPointingMode = false;
            m_sViewDstX = m_sViewPointX = (m_sPlayerX - 10) * 32;
            m_sViewDstY = m_sViewPointY = (m_sPlayerY - 7) * 32;
            m_bIsPrevMoveBlocked = true;
            switch (m_sPlayerType)
            {
                case 1:
                case 2:
                case 3:
                    PlaySound('C', 12, 0);
                    break;
                case 4:
                case 5:
                case 6:
                    PlaySound('C', 13, 0);
                    break;
            }
            //m_bCommandAvailable = true;
            break;
    }
}
