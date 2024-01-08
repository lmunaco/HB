//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include "Game.h"
#include "lan_eng.h"
#include "defines.h"
#include "NetMessages.h"

extern uint64_t unixtime();
extern uint64_t unixseconds();

bool CGame::bDlgBoxPress_Character(short msX, short msY)
{
    int i;
    short sX, sY, sSprH, sFrame;
    char cEquipPoiStatus[DEF_MAXITEMEQUIPPOS] = {};

    if (m_bIsDialogEnabled[17] == true) return false;

    sX = m_stDialogBoxInfo[1].sX;
    sY = m_stDialogBoxInfo[1].sY;
    for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++) cEquipPoiStatus[i] = -1;
    for (i = 0; i < DEF_MAXITEMS; i++)
    {
        if ((m_pItemList[i] != 0) && (m_bIsItemEquipped[i] == true))	cEquipPoiStatus[m_pItemList[i]->m_cEquipPos] = i;
    }

    if ((m_sPlayerType >= 1) && (m_sPlayerType <= 3))
    {
        if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 72, sY + 135, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_HEAD];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_RFINGER];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_LFINGER];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_NECK];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 90, sY + 170, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_FULLBODY];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_BODY];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_BOOTS];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_ARMS];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_PANTS];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 41, sY + 137, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_BACK];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
    }
    else if ((m_sPlayerType >= 4) && (m_sPlayerType <= 6))
    {
        if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 72, sY + 139, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_HEAD];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_RFINGER];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_LFINGER];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_NECK];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 84, sY + 175, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_BODY];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_FULLBODY];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if ((cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1))
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_BOOTS];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_ARMS];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_PANTS];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 45, sY + 143, sFrame, msX, msY))
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = m_sItemEquipmentStatus[DEF_EQUIPPOS_BACK];
                m_stMCursor.sDistX = 0;
                m_stMCursor.sDistY = 0;
                return true;
            }
        }
    }
    return false;
}

void CGame::DlgBoxClick_CityhallMenu(short msX, short msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[13].sX;
    sY = m_stDialogBoxInfo[13].sY;
    switch (m_stDialogBoxInfo[13].cMode)
    {
        case 0:
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
            {
                if (m_bCitizen == true) return;
                m_stDialogBoxInfo[13].cMode = 1; // citizenship rq
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
            {
                if (m_iRewardGold <= 0) return;
                m_stDialogBoxInfo[13].cMode = 5; // rq reward gold
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
            {
                if (m_iEnemyKillCount < 100) return;
                m_stDialogBoxInfo[13].cMode = 7;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170))
            {
                if (m_stQuest.sQuestType == 0) return;
                m_stDialogBoxInfo[13].cMode = 8;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
            {
                if (m_bIsCrusadeMode) return;
                if (m_iPKCount != 0) return;
                if (m_bCitizen == false) return;
                if ((m_iLevel > 100) && (m_bHunter == false)) return;
                m_stDialogBoxInfo[13].cMode = 9;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
            {
                m_stDialogBoxInfo[13].cMode = 10;
                m_iTeleportMapCount = -1;
                bSendCommand(MSGID_REQUEST_TELEPORT_LIST, 0, 0, 0, 0, 0, 0);
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 220) && (msY < sY + 245))
            {
                if (m_bIsCrusadeMode == false) return;
                EnableDialogBox(33, 1, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 1:
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Yes Click
                bSendCommand(MSGID_REQUEST_CIVILRIGHT, DEF_MSGTYPE_CONFIRM, 0, 0, 0, 0, 0);
                m_stDialogBoxInfo[13].cMode = 2;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// No Click
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 3:	//
        case 4:	// OK°
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // No Click
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 5:
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Yes
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETREWARDMONEY, 0, 0, 0, 0, 0);
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);

            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // No
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

            // 3.51 Cityhall Menu - Request Hero's Items
        case 7:
            int iReqHeroItemID;
            // Hero's Cape
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 95) && (msY <= sY + 110))
            {
                if (m_bAresden == true) iReqHeroItemID = 400;
                else iReqHeroItemID = 401;
                ZeroMemory(m_cTakeHeroItemName, sizeof(m_cTakeHeroItemName));
                memcpy(m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU47, strlen(DRAW_DIALOGBOX_CITYHALL_MENU47));
                m_stDialogBoxInfo[13].cMode = 11;
                m_stDialogBoxInfo[13].sV1 = iReqHeroItemID;
                PlaySound('E', 14, 5);
            }
            // Hero's Helm
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 125) && (msY <= sY + 140))
            {
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 403;
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 404;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 405;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 406;
                ZeroMemory(m_cTakeHeroItemName, sizeof(m_cTakeHeroItemName));
                memcpy(m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU48, strlen(DRAW_DIALOGBOX_CITYHALL_MENU48));
                m_stDialogBoxInfo[13].cMode = 11;
                m_stDialogBoxInfo[13].sV1 = iReqHeroItemID;
                PlaySound('E', 14, 5);
            }
            // Hero's Cap
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 155) && (msY <= sY + 170))
            {
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 407;
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 408;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 409;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 410;
                ZeroMemory(m_cTakeHeroItemName, sizeof(m_cTakeHeroItemName));
                memcpy(m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU49, strlen(DRAW_DIALOGBOX_CITYHALL_MENU49));
                m_stDialogBoxInfo[13].cMode = 11;
                m_stDialogBoxInfo[13].sV1 = iReqHeroItemID;
                PlaySound('E', 14, 5);
            }
            // Hero's Armor
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 185) && (msY <= sY + 200))
            {
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 411;
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 412;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 413;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 414;
                ZeroMemory(m_cTakeHeroItemName, sizeof(m_cTakeHeroItemName));
                memcpy(m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU50, strlen(DRAW_DIALOGBOX_CITYHALL_MENU50));
                m_stDialogBoxInfo[13].cMode = 11;
                m_stDialogBoxInfo[13].sV1 = iReqHeroItemID;
                PlaySound('E', 14, 5);
            }
            // Hero's Robe
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 215) && (msY <= sY + 230))
            {
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 415;
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 416;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 417;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 418;
                ZeroMemory(m_cTakeHeroItemName, sizeof(m_cTakeHeroItemName));
                memcpy(m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU51, strlen(DRAW_DIALOGBOX_CITYHALL_MENU51));
                m_stDialogBoxInfo[13].cMode = 11;
                m_stDialogBoxInfo[13].sV1 = iReqHeroItemID;
                PlaySound('E', 14, 5);
            }
            // Hero's Hauberk
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 245) && (msY <= sY + 260))
            {
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 419;
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 420;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 421;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 422;
                ZeroMemory(m_cTakeHeroItemName, sizeof(m_cTakeHeroItemName));
                memcpy(m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU52, strlen(DRAW_DIALOGBOX_CITYHALL_MENU52));
                m_stDialogBoxInfo[13].cMode = 11;
                m_stDialogBoxInfo[13].sV1 = iReqHeroItemID;
                PlaySound('E', 14, 5);
            }
            // Hero's Leggings
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 275) && (msY <= sY + 290))
            {
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 423;
                if ((m_bAresden == true) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 424;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 1)) iReqHeroItemID = 425;
                if ((m_bAresden == false) && (m_pCharList[m_cCurFocus - 1]->m_sSex == 2)) iReqHeroItemID = 426;
                ZeroMemory(m_cTakeHeroItemName, sizeof(m_cTakeHeroItemName));
                memcpy(m_cTakeHeroItemName, DRAW_DIALOGBOX_CITYHALL_MENU53, strlen(DRAW_DIALOGBOX_CITYHALL_MENU53));
                m_stDialogBoxInfo[13].cMode = 11;
                m_stDialogBoxInfo[13].sV1 = iReqHeroItemID;
                PlaySound('E', 14, 5);
            }
            break;

        case 8:
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Yes
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_CANCELQUEST, 0, 0, 0, 0, 0);
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // No
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 9:
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Yes
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_HUNTMODE, 0, 0, 0, 0, 0);
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // No
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 10:
            if (m_iTeleportMapCount > 0)
            {
                for (int i = 0; i < m_iTeleportMapCount; i++)
                {
                    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i * 15) && (msY <= sY + 144 + i * 15))
                    {
                        bSendCommand(MSGID_REQUEST_CHARGED_TELEPORT, 0, 0, m_stTeleportList[i].iIndex, 0, 0, 0);
                        DisableDialogBox(13);
                        return;
                    }
                }
            }
            break;

        case 11: // Fix Drawjer
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETHEROMANTLE, 0, m_stDialogBoxInfo[13].sV1, 0, 0, 0);
                m_stDialogBoxInfo[13].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                m_stDialogBoxInfo[13].cMode = 7;
                PlaySound('E', 14, 5);
            }
            break;
    }
}

bool CGame::bDlgBoxPress_Inventory(short msX, short msY)
{
    int i;
    char  cItemID;
    short sX, sY, x1, x2, y1, y2;

#ifdef _DEBUG
    AddEventList("Press Inventory", 10);
#endif

    if (m_bIsDialogEnabled[2] == false) return false;
    if (m_bIsDialogEnabled[17] == true) return false;
    if (m_bIsDialogEnabled[4] == true) return false;

    sX = m_stDialogBoxInfo[2].sX;
    sY = m_stDialogBoxInfo[2].sY;

    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_cItemOrder[DEF_MAXITEMS - 1 - i] != -1)
        {
            cItemID = m_cItemOrder[DEF_MAXITEMS - 1 - i];

            if (m_pItemList[cItemID] != 0)
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + 32 + m_pItemList[cItemID]->m_sX,
                    sY + 44 + m_pItemList[cItemID]->m_sY, m_pItemList[cItemID]->m_sSpriteFrame);
                x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
                y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
                x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
                y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;
                if ((m_bIsItemDisabled[cItemID] == false) && (m_bIsItemEquipped[cItemID] == false) && (msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
                {

                    if (m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_bCheckCollison(sX + 32 + m_pItemList[cItemID]->m_sX, sY + 44 + m_pItemList[cItemID]->m_sY, m_pItemList[cItemID]->m_sSpriteFrame, msX, msY) == true)
                    {
                        _SetItemOrder(0, cItemID);
                        if ((m_bIsGetPointingMode == true) && (m_iPointCommandType < 100) && (m_iPointCommandType >= 0)
                            && (m_pItemList[m_iPointCommandType] != 0)
                            && (m_pItemList[m_iPointCommandType]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE_DEST)
                            && (m_iPointCommandType != cItemID))
                        {
                            PointCommandHandler(0, 0, cItemID);
                            //m_bCommandAvailable  = false;
                            m_bIsGetPointingMode = false;
                        }
                        else
                        {
                            m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                            m_stMCursor.sSelectedObjectID = cItemID;
                            m_stMCursor.sDistX = msX - x1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotX;
                            m_stMCursor.sDistY = msY - y1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotY;
                        }
                        return true;
                    }
                }
            }
        }
    return false;
}


void CGame::DlgBoxClick_15AgeMsg(short msX, short msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[5].sX;
    sY = m_stDialogBoxInfo[5].sY;
    if ((msX >= sX + 120) && (msX <= sX + 120 + DEF_BTNSZX) && (msY >= sY + 127) && (msY <= sY + 127 + DEF_BTNSZY))
        DisableDialogBox(5);
}

void CGame::DlgBoxClick_WarningMsg(short msX, short msY)// Á¤Áø±¤.
{
    short sX, sY;
    sX = m_stDialogBoxInfo[6].sX;
    sY = m_stDialogBoxInfo[6].sY;

    if ((msX >= sX + 120) && (msX <= sX + 120 + DEF_BTNSZX) && (msY >= sY + 127) && (msY <= sY + 127 + DEF_BTNSZY))
        DisableDialogBox(6);
}

void CGame::DlgBoxClick_ItemDrop(short msX, short msY)
{
    short sX, sY;
    if (m_cCommand < 0) return;

    sX = m_stDialogBoxInfo[4].sX;
    sY = m_stDialogBoxInfo[4].sY;

    if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
    {
        m_stDialogBoxInfo[4].cMode = 3;
        bSendCommand(MSGID_COMMAND_COMMON,
            DEF_COMMONTYPE_ITEMDROP,
            0,
            m_stDialogBoxInfo[4].sView,
            1,
            0,
            m_pItemList[m_stDialogBoxInfo[4].sView]->m_cName);
        //m_stDialogBoxInfo[40].sView ;
        DisableDialogBox(4);
    }

    else if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
    {

        for (int i = 0; i < DEF_MAXSELLLIST; i++)
            m_bIsItemDisabled[i] = false;

        DisableDialogBox(4);
    }
    else if ((msX >= sX + 35) && (msX <= sX + 240) && (msY >= sY + 80) && (msY <= sY + 90))
    {
        m_bItemDrop = !m_bItemDrop;
    }
}

void CGame::DlgBoxClick_ItemSellorRepair(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[23].sX;
    sY = m_stDialogBoxInfo[23].sY;

    switch (m_stDialogBoxInfo[23].cMode)
    {
        case 1:
            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Sell
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_SELLITEMCONFIRM, 0, m_stDialogBoxInfo[23].sV1, m_stDialogBoxInfo[23].sV4, m_stDialogBoxInfo[23].sV3, m_pItemList[m_stDialogBoxInfo[23].sV1]->m_cName); //v1.2
                m_stDialogBoxInfo[23].cMode = 3;
            }
            if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Cancel
                m_bIsItemDisabled[m_stDialogBoxInfo[23].sV1] = false;
                DisableDialogBox(23);
            }
            break;

        case 2:
            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Repair
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEMCONFIRM, 0, m_stDialogBoxInfo[23].sV1, 0, 0, m_pItemList[m_stDialogBoxInfo[23].sV1]->m_cName);
                m_stDialogBoxInfo[23].cMode = 4;
            }
            if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Cancel
                m_bIsItemDisabled[m_stDialogBoxInfo[23].sV1] = false;
                DisableDialogBox(23);
            }
            break;
    }
}


void CGame::DlgBoxClick_Bank(short msX, short msY)
{
    int i;
    short sX, sY;


    sX = m_stDialogBoxInfo[14].sX;
    sY = m_stDialogBoxInfo[14].sY;

    switch (m_stDialogBoxInfo[14].cMode)
    {
        case -1:
            break;

        case 0:
            for (i = 0; i < m_stDialogBoxInfo[14].sV1; i++)
                if ((msX > sX + 30) && (msX < sX + 210) && (msY >= sY + 110 + i * 15) && (msY <= sY + 124 + i * 15))
                {
                    if ((m_pBankList[m_stDialogBoxInfo[14].sView + i] != 0) && ((m_stDialogBoxInfo[14].sView + i) < DEF_MAXBANKITEMS))
                    {
                        if (_iGetTotalItemNum() >= 50)
                        {
                            AddEventList(DLGBOX_CLICK_BANK1, 10);
                            return;
                        }
                        bSendCommand(MSGID_REQUEST_RETRIEVEITEM, 0, 0, (m_stDialogBoxInfo[14].sView + i), 0, 0, 0);
                        m_stDialogBoxInfo[14].cMode = -1;
                        PlaySound('E', 14, 5);
                    }
                    return;
                }

            break;
    }
}

void CGame::DlgBoxClick_Fish(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[24].sX;
    sY = m_stDialogBoxInfo[24].sY;

    switch (m_stDialogBoxInfo[24].cMode)
    {
        case 0:
            if ((msX >= sX + 160) && (msX <= sX + 253) && (msY >= sY + 70) && (msY <= sY + 90))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETFISHTHISTIME, 0, 0, 0, 0, 0);
                AddEventList(DLGBOX_CLICK_FISH1, 10);
                DisableDialogBox(24);

                PlaySound('E', 14, 5);
            }
            break;
    }
}

void CGame::DlgBoxClick_Magic(short msX, short msY)
{
    int i, iCPivot, iYloc;
    short sX, sY;

    sX = m_stDialogBoxInfo[3].sX;
    sY = m_stDialogBoxInfo[3].sY;
    iCPivot = m_stDialogBoxInfo[3].sView * 10;
    iYloc = 0;
    for (i = 0; i < 9; i++)
    {
        if ((m_cMagicMastery[iCPivot + i] != 0) && (m_pMagicCfgList[iCPivot + i] != 0))
        {
            if ((msX >= sX + 30) && (msX <= sX + 240) && (msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 18 + iYloc))
            {
                UseMagic(iCPivot + i);
                PlaySound('E', 14, 5);
                return;
            }
            iYloc += 18;
        }
    }
    if ((msX >= sX + 16) && (msX <= sX + 38) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 0;
    if ((msX >= sX + 39) && (msX <= sX + 56) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 1;
    if ((msX >= sX + 57) && (msX <= sX + 81) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 2;
    if ((msX >= sX + 82) && (msX <= sX + 101) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 3;
    if ((msX >= sX + 102) && (msX <= sX + 116) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 4;
    if ((msX >= sX + 117) && (msX <= sX + 137) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 5;
    if ((msX >= sX + 138) && (msX <= sX + 165) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 6;
    if ((msX >= sX + 166) && (msX <= sX + 197) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 7;
    if ((msX >= sX + 198) && (msX <= sX + 217) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 8;
    if ((msX >= sX + 218) && (msX <= sX + 239) && (msY >= sY + 240) && (msY <= sY + 268))
        m_stDialogBoxInfo[3].sView = 9;

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 285) && (msY <= sY + 285 + DEF_BTNSZY))
    {
        if (m_cSkillMastery[12] == 0) AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY16, 10);
        else
        {
            for (i = 0; i < DEF_MAXITEMS; i++)
                if ((m_pItemList[i] != 0) && (m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX) &&
                    (m_pItemList[i]->m_sSpriteFrame == 55))
                {
                    EnableDialogBox(26, 1, 0, 0, 0);
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY10, 10);
                    PlaySound('E', 14, 5);
                    return;
                }
            AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY15, 10);
        }
        PlaySound('E', 14, 5);
    }
}

void CGame::DlgBoxClick_NpcActionQuery(short msX, short msY)
{
    short sX, sY;
    int   absX, absY;
    if (m_bIsDialogEnabled[27] == true)
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }
    sX = m_stDialogBoxInfo[20].sX;
    sY = m_stDialogBoxInfo[20].sY;

    switch (m_stDialogBoxInfo[20].cMode)
    {
        case 0: // Talk to npc
            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                EnableDialogBox(m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV2, 0, 0);
                DisableDialogBox(20);
            }
            if ((m_bIsDialogEnabled[21] == false) && (msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
            {
                switch (m_stDialogBoxInfo[20].sV1)
                {
                    case 7:	// Guild
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 1, 0, 0, 0);
                        AddEventList(TALKING_TO_GUILDHALL_OFFICER, 10);
                        break;
                    case 11: // BS or Shop
                        switch (m_stDialogBoxInfo[20].sV2)
                        {
                            case 1:
                                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 2, 0, 0, 0);
                                AddEventList(TALKING_TO_SHOP_KEEPER, 10);
                                break;
                            case 2:
                                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 3, 0, 0, 0);
                                AddEventList(TALKING_TO_BLACKSMITH_KEEPER, 10);
                                break;
                        }
                        break;
                    case 13: // CityHall officer
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 4, 0, 0, 0);
                        AddEventList(TALKING_TO_CITYHALL_OFFICER, 10);
                        break;
                    case 14: // WH keeper
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 5, 0, 0, 0);
                        AddEventList(TALKING_TO_WAREHOUSE_KEEPER, 10);
                        break;
                    case 16: // Magicmerchant
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 6, 0, 0, 0);
                        AddEventList(TALKING_TO_MAGICIAN, 10);
                        break;
                }
                DisableDialogBox(20);
            }
            break;

        case 1: // On other player
            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                absX = abs(m_stDialogBoxInfo[20].sV5 - m_sPlayerX);
                absY = abs(m_stDialogBoxInfo[20].sV6 - m_sPlayerY);
                if ((absX <= 4) && (absY <= 4))
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV3, m_stDialogBoxInfo[20].sV5, m_stDialogBoxInfo[20].sV6, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); //v1.4
                else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY7, 10); //"Too far to give the item."
                DisableDialogBox(20);
            }
            else if ((msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70))
            {
                absX = abs(m_stDialogBoxInfo[20].sV5 - m_sPlayerX);
                absY = abs(m_stDialogBoxInfo[20].sV6 - m_sPlayerY);
                if ((absX <= 4) && (absY <= 4))
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_EXCHANGEITEMTOCHAR, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV3, m_stDialogBoxInfo[20].sV5, m_stDialogBoxInfo[20].sV6, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); //v1.4
                else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY8, 10); //"Too far to exchange item."
                DisableDialogBox(20);
            }
            break;

        case 2: // Item on Shop/BS
            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_SELLITEM, 0, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV2, m_stDialogBoxInfo[20].sV3, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); // v1.4
                DisableDialogBox(20);
            }
            else if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
            {
                if (m_stDialogBoxInfo[20].sV3 == 1)
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEM, 0, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV2, 0, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); // v1.4
                    DisableDialogBox(20);
                }
            }
            break;

        case 3: // Put item in the WH
            if ((msX > sX + 25) && (msX < sX + 105) && (msY > sY + 55) && (msY < sY + 70))
            {
                absX = abs(m_stDialogBoxInfo[20].sV5 - m_sPlayerX);
                absY = abs(m_stDialogBoxInfo[20].sV6 - m_sPlayerY);
                if ((absX <= 8) && (absY <= 8))
                {
                    if (_iGetBankItemCount() >= (DEF_MAXBANKITEMS - 1))
                    {
                        AddEventList(DLGBOX_CLICK_NPCACTION_QUERY9, 10);//"here is no empty space left in warehouse."
                    }
                    else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV3, m_stDialogBoxInfo[20].sV5, m_stDialogBoxInfo[20].sV6, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_stDialogBoxInfo[20].sV4); //v1.4
                }
                else AddEventList(DLGBOX_CLICK_NPCACTION_QUERY7, 10);//"Too far to give the item."

                DisableDialogBox(20);
            }
            break;

        case 4: // talk to npc or Unicorn
            if ((m_bIsDialogEnabled[21] == false) && (msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
            {
                switch (m_stDialogBoxInfo[20].sV3)
                {
                    case 21: // Guard
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 21, 0, 0, 0);
                        AddEventList(TALKING_TO_GUARD, 10);//"Talking to Guard..."
                        break;

                    case 32: // Unicorn
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 32, 0, 0, 0);
                        AddEventList(TALKING_TO_UNICORN, 10);//"Talking to Unicorn..."
                        break;
                    case 67:
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 67, 0, 0, 0);
                        AddEventList(TALKING_TO_MCGAFFIN, 10);//"Talking to a town man..."
                        break;
                    case 68:
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 68, 0, 0, 0);
                        AddEventList(TALKING_TO_PERRY, 10);//"Talking to a town maiden..."
                        break;
                    case 69:
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 69, 0, 0, 0);
                        AddEventList(TALKING_TO_DEVLIN, 10);//"Talking to a town magician..."
                        break;
                }
            }
            DisableDialogBox(20);
            break;


        case 5: // Talk
            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                EnableDialogBox(m_stDialogBoxInfo[20].sV1, m_stDialogBoxInfo[20].sV2, 0, 0);
                DisableDialogBox(20);
            }
            if ((msX > sX + 25 + 75) && (msX < sX + 80 + 75) && (msY > sY + 55) && (msY < sY + 70))
            {
                EnableDialogBox(31, 0, 0, 0);
                DisableDialogBox(20);
            }

            if ((m_bIsDialogEnabled[21] == false) && (msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70))
            {
                switch (m_stDialogBoxInfo[20].sV1)
                {
                    case 7:	// Guild
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 1, 0, 0, 0);
                        AddEventList(TALKING_TO_GUILDHALL_OFFICER, 10);//"Talking to Guildhall Officer..."
                        break;

                    case 11: //
                        switch (m_stDialogBoxInfo[20].sV2)
                        {
                            case 1:
                                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 2, 0, 0, 0);
                                AddEventList(TALKING_TO_SHOP_KEEPER, 10);//"Talking to Shop Keeper..."
                                break;
                            case 2:
                                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 3, 0, 0, 0);
                                AddEventList(TALKING_TO_BLACKSMITH_KEEPER, 10);//"
                                break;
                        }
                        break;

                    case 13: //
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 4, 0, 0, 0);
                        AddEventList(TALKING_TO_CITYHALL_OFFICER, 10);//"
                        break;

                    case 14: //
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 5, 0, 0, 0);
                        AddEventList(TALKING_TO_WAREHOUSE_KEEPER, 10);//
                        break;

                    case 16: //
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TALKTONPC, 0, 6, 0, 0, 0);
                        AddEventList(TALKING_TO_MAGICIAN, 10);//"
                        break;
                }
                DisableDialogBox(20);
            }
            break;

        case 6: // Added Gail
            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                EnableDialogBox(51, 0, 0, 0);
                DisableDialogBox(20);
            }
    }
}

void CGame::DlgBoxClick_Shop(short msX, short msY)
{
    int i;
    short sX, sY;
    char cTemp[21];
    sX = m_stDialogBoxInfo[11].sX;
    sY = m_stDialogBoxInfo[11].sY;

    switch (m_stDialogBoxInfo[11].cMode)
    {
        case 0:
            for (i = 0; i < 13; i++)
                if ((msX >= sX + 20) && (msX <= sX + 220) && (msY >= sY + i * 18 + 65) && (msY <= sY + i * 18 + 79))
                {
                    if (_iGetTotalItemNum() >= 50)
                    {
                        AddEventList(DLGBOX_CLICK_SHOP1, 10);//"You cannot buy anything because your bag is full."
                        return;
                    }

                    PlaySound('E', 14, 5);
                    if (m_pItemForSaleList[m_stDialogBoxInfo[11].sView + i] != 0)
                        m_stDialogBoxInfo[11].cMode = m_stDialogBoxInfo[11].sView + i + 1;
                    return;
                }
            break;

        default:
            if ((msX >= sX + 145) && (msX <= sX + 162) && (msY >= sY + 209) && (msY <= sY + 230))
            {
                m_stDialogBoxInfo[11].sV3 += 10;
                if (m_stDialogBoxInfo[11].sV3 >= (50 - _iGetTotalItemNum()))
                    m_stDialogBoxInfo[11].sV3 = (50 - _iGetTotalItemNum());
            }

            if ((msX >= sX + 145) && (msX <= sX + 162) && (msY >= sY + 234) && (msY <= sY + 251))
            {
                m_stDialogBoxInfo[11].sV3 -= 10;
                if (m_stDialogBoxInfo[11].sV3 <= 1)
                    m_stDialogBoxInfo[11].sV3 = 1;
            }

            if ((msX >= sX + 163) && (msX <= sX + 180) && (msY >= sY + 209) && (msY <= sY + 230))
            {
                m_stDialogBoxInfo[11].sV3++;
                if (m_stDialogBoxInfo[11].sV3 >= (50 - _iGetTotalItemNum()))
                    m_stDialogBoxInfo[11].sV3 = (50 - _iGetTotalItemNum());
            }

            if ((msX >= sX + 163) && (msX <= sX + 180) && (msY >= sY + 234) && (msY <= sY + 251))
            {
                m_stDialogBoxInfo[11].sV3--;
                if (m_stDialogBoxInfo[11].sV3 <= 1)
                    m_stDialogBoxInfo[11].sV3 = 1;
            }

            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Purchase Click
                if ((50 - _iGetTotalItemNum()) < m_stDialogBoxInfo[11].sV3)
                {
                    AddEventList(DLGBOX_CLICK_SHOP1, 10);//"ou cannot buy anything because your bag is full."
                }
                else
                {
                    ZeroMemory(cTemp, sizeof(cTemp));
                    strcpy(cTemp, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cName);
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_PURCHASEITEM, 0, m_stDialogBoxInfo[11].sV3, 0, 0, cTemp);
                }
                m_stDialogBoxInfo[11].cMode = 0;
                m_stDialogBoxInfo[11].sV3 = 1;
                PlaySound('E', 14, 5);
            }

            if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel Click
                m_stDialogBoxInfo[11].cMode = 0;
                m_stDialogBoxInfo[11].sV3 = 1;
                PlaySound('E', 14, 5);
            }
            break;
    }
}

void CGame::DlgBoxClick_Skill(short msX, short msY)
{
    int i;
    short sX, sY;
    sX = m_stDialogBoxInfo[15].sX;
    sY = m_stDialogBoxInfo[15].sY;
    switch (m_stDialogBoxInfo[15].cMode)
    {
        case -1:
            break;
        case 0:
            for (i = 0; i < 17; i++)
                if ((i < DEF_MAXSKILLTYPE) && (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView] != 0))
                {
                    if ((msX >= sX + 44) && (msX <= sX + 135 + 44) && (msY >= sY + 45 + i * 15) && (msY <= sY + 59 + i * 15))
                    {
                        if ((m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_bIsUseable == true)
                            && (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_iLevel != 0))
                        {
                            if (m_bSkillUsingStatus == true)
                            {
                                AddEventList(DLGBOX_CLICK_SKILL1, 10); // "You are already using other skill."
                                return;
                            }
                            if ((m_bCommandAvailable == false) || (m_iHP <= 0))
                            {
                                AddEventList(DLGBOX_CLICK_SKILL2, 10); // "You can't use a skill while you are moving."
                                return;
                            }
                            if (m_bIsGetPointingMode == true)
                            {
                                return;
                            }
                            switch (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_cUseMethod)
                            {
                                case 0:
                                case 2:
                                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USESKILL, 0, (i + m_stDialogBoxInfo[15].sView), 0, 0, 0);
                                    m_bSkillUsingStatus = true;
                                    DisableDialogBox(15);
                                    PlaySound('E', 14, 5);
                                    break;
                            }
                        }
                    }
                    else if ((msX >= sX + 215) && (msX <= sX + 240) && (msY >= sY + 45 + i * 15) && (msY <= sY + 59 + i * 15))
                    {
                        if (m_stDialogBoxInfo[15].bFlag == false)
                        {
                            bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_SETDOWNSKILLINDEX, 0, i + m_stDialogBoxInfo[15].sView, 0, 0, 0);
                            PlaySound('E', 14, 5);
                            m_stDialogBoxInfo[15].bFlag = true;
                        }
                    }
                }
            break;
    }
}

void CGame::DlgBoxClick_SkillDlg(short msX, short msY)
{
    int i, iAdjX, iAdjY;
    short sX, sY;

    sX = m_stDialogBoxInfo[26].sX;
    sY = m_stDialogBoxInfo[26].sY;

    iAdjX = 5;
    iAdjY = 8;


    switch (m_stDialogBoxInfo[26].cMode)
    {
        case 1:
            if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
            {
                m_stDialogBoxInfo[26].cMode = 2;
                m_stDialogBoxInfo[26].cStr[0] = 1;
                m_stDialogBoxInfo[26].dwT1 = m_dwCurTime;
                PlaySound('E', 14, 5);
                AddEventList(DLGBOX_CLICK_SKILLDLG1, 10); // "Mixing a potion..."
                PlaySound('E', 41, 0);
            }
            break;
            // Crafting
        case 7:
            if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
            {
                if (m_stDialogBoxInfo[26].sV1 == -1)
                {
                    AddEventList(DLGBOX_CLICK_SKILLDLG2, 10); // "There is not enough crafting materials. Please put in more materials."
                    PlaySound('E', 14, 5);
                }
                else
                {
                    m_stDialogBoxInfo[26].cMode = 8;
                    m_stDialogBoxInfo[26].dwT1 = m_dwCurTime;
                    m_stDialogBoxInfo[26].cStr[1] = 1;
                    PlaySound('E', 14, 5);
                    AddEventList(DLGBOX_CLICK_SKILLDLG3, 10); // "Crafting the item in progress"
                    PlaySound('E', 51, 0);
                }
            }
            break;

        case 3:
            for (i = 0; i < 13; i++)
                if (m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView] != 0)
                {
                    if ((msX >= sX + iAdjX + 44) && (msX <= sX + iAdjX + 135 + 44) && (msY >= sY + iAdjY + 55 + i * 15) && (msY <= sY + iAdjY + 55 + 14 + i * 15))
                    {
                        m_stDialogBoxInfo[26].cMode = 4;
                        m_stDialogBoxInfo[26].cStr[0] = i + m_stDialogBoxInfo[26].sView;
                        PlaySound('E', 14, 5);
                    }
                }
            break;

        case 4:
            iAdjX = -1;
            iAdjY = -7;
            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bBuildEnabled == true)
            {
                if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
                {
                    // Back
                    m_stDialogBoxInfo[26].cMode = 3;
                    PlaySound('E', 14, 5);

                    if ((m_stDialogBoxInfo[26].sV1 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV1] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV1] = false;
                    if ((m_stDialogBoxInfo[26].sV2 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV2] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV2] = false;
                    if ((m_stDialogBoxInfo[26].sV3 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV3] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV3] = false;
                    if ((m_stDialogBoxInfo[26].sV4 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV4] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV4] = false;
                    if ((m_stDialogBoxInfo[26].sV5 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV5] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV5] = false;
                    if ((m_stDialogBoxInfo[26].sV6 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV6] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV6] = false;

                    m_stDialogBoxInfo[26].sV1 = -1;
                    m_stDialogBoxInfo[26].sV2 = -1;
                    m_stDialogBoxInfo[26].sV3 = -1;
                    m_stDialogBoxInfo[26].sV4 = -1;
                    m_stDialogBoxInfo[26].sV5 = -1;
                    m_stDialogBoxInfo[26].sV6 = -1;
                    m_stDialogBoxInfo[26].cStr[0] = 0;
                    m_stDialogBoxInfo[26].cStr[1] = 0;
                    m_stDialogBoxInfo[26].cStr[4] = 0;
                }

                if ((msX >= sX + iAdjX + 160) && (msX <= sX + iAdjX + 255) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
                {	// Manufacture
                    if (m_stDialogBoxInfo[26].cStr[4] == 1)
                    {
                        m_stDialogBoxInfo[26].cMode = 5;
                        m_stDialogBoxInfo[26].cStr[1] = 0;
                        m_stDialogBoxInfo[26].dwT1 = m_dwCurTime;
                        PlaySound('E', 14, 5);
                        PlaySound('E', 44, 0);
                    }
                }
            }
            else
            {
                if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372)) 	// Back
                {
                    m_stDialogBoxInfo[26].cMode = 3;
                    PlaySound('E', 14, 5);

                    if ((m_stDialogBoxInfo[26].sV1 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV1] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV1] = false;
                    if ((m_stDialogBoxInfo[26].sV2 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV2] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV2] = false;
                    if ((m_stDialogBoxInfo[26].sV3 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV3] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV3] = false;
                    if ((m_stDialogBoxInfo[26].sV4 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV4] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV4] = false;
                    if ((m_stDialogBoxInfo[26].sV5 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV5] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV5] = false;
                    if ((m_stDialogBoxInfo[26].sV6 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV6] != 0))
                        m_bIsItemDisabled[m_stDialogBoxInfo[26].sV6] = false;

                    m_stDialogBoxInfo[26].sV1 = -1;
                    m_stDialogBoxInfo[26].sV2 = -1;
                    m_stDialogBoxInfo[26].sV3 = -1;
                    m_stDialogBoxInfo[26].sV4 = -1;
                    m_stDialogBoxInfo[26].sV5 = -1;
                    m_stDialogBoxInfo[26].sV6 = -1;
                    m_stDialogBoxInfo[26].cStr[0] = 0;
                    m_stDialogBoxInfo[26].cStr[1] = 0;
                    m_stDialogBoxInfo[26].cStr[4] = 0;
                }
            }
            break;

        case 6:
            iAdjX = -1;
            iAdjY = -7;
            if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
            {
                // Back
                m_stDialogBoxInfo[26].cMode = 3;
                PlaySound('E', 14, 5);

                if ((m_stDialogBoxInfo[26].sV1 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV1] != 0))
                    m_bIsItemDisabled[m_stDialogBoxInfo[26].sV1] = false;
                if ((m_stDialogBoxInfo[26].sV2 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV2] != 0))
                    m_bIsItemDisabled[m_stDialogBoxInfo[26].sV2] = false;
                if ((m_stDialogBoxInfo[26].sV3 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV3] != 0))
                    m_bIsItemDisabled[m_stDialogBoxInfo[26].sV3] = false;
                if ((m_stDialogBoxInfo[26].sV4 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV4] != 0))
                    m_bIsItemDisabled[m_stDialogBoxInfo[26].sV4] = false;
                if ((m_stDialogBoxInfo[26].sV5 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV5] != 0))
                    m_bIsItemDisabled[m_stDialogBoxInfo[26].sV5] = false;
                if ((m_stDialogBoxInfo[26].sV6 != -1) && (m_pItemList[m_stDialogBoxInfo[26].sV6] != 0))
                    m_bIsItemDisabled[m_stDialogBoxInfo[26].sV6] = false;

                m_stDialogBoxInfo[26].sV1 = -1;
                m_stDialogBoxInfo[26].sV2 = -1;
                m_stDialogBoxInfo[26].sV3 = -1;
                m_stDialogBoxInfo[26].sV4 = -1;
                m_stDialogBoxInfo[26].sV5 = -1;
                m_stDialogBoxInfo[26].sV6 = -1;
                m_stDialogBoxInfo[26].cStr[0] = 0;
                m_stDialogBoxInfo[26].cStr[1] = 0;
                m_stDialogBoxInfo[26].cStr[4] = 0;
            }
            break;
    }
}


void CGame::DlgBoxClick_ChangeStatsMajestic(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[42].sX;
    sY = m_stDialogBoxInfo[42].sY;

    if ((cStateChange1 != 0) || (cStateChange2 != 0) || (cStateChange3 != 0))
    {
        if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 127) && (msY <= sY + 133) && (m_cLU_Str < 0))
        {
            if (cStateChange1 == DEF_STR)
            {
                cStateChange1 = 0;
                m_cLU_Str += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange2 == DEF_STR)
            {
                cStateChange2 = 0;
                m_cLU_Str += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange3 == DEF_STR)
            {
                cStateChange3 = 0;
                m_cLU_Str += 1;
                m_iLU_Point -= 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 146) && (msY <= sY + 152) && (m_cLU_Vit < 0))
        {
            if (cStateChange1 == DEF_VIT)
            {
                cStateChange1 = 0;
                m_cLU_Vit += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange2 == DEF_VIT)
            {
                cStateChange2 = 0;
                m_cLU_Vit += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange3 == DEF_VIT)
            {
                cStateChange3 = 0;
                m_cLU_Vit += 1;
                m_iLU_Point -= 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 165) && (msY <= sY + 171) && (m_cLU_Dex < 0))
        {
            if (cStateChange1 == DEF_DEX)
            {
                cStateChange1 = 0;
                m_cLU_Dex += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange2 == DEF_DEX)
            {
                cStateChange2 = 0;
                m_cLU_Dex += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange3 == DEF_DEX)
            {
                cStateChange3 = 0;
                m_cLU_Dex += 1;
                m_iLU_Point -= 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 184) && (msY <= sY + 190) && (m_cLU_Int < 0))
        {
            if (cStateChange1 == DEF_INT)
            {
                cStateChange1 = 0;
                m_cLU_Int += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange2 == DEF_INT)
            {
                cStateChange2 = 0;
                m_cLU_Int += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange3 == DEF_INT)
            {
                cStateChange3 = 0;
                m_cLU_Int += 1;
                m_iLU_Point -= 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 203) && (msY <= sY + 209) && (m_cLU_Mag < 0))
        {
            if (cStateChange1 == DEF_MAG)
            {
                cStateChange1 = 0;
                m_cLU_Mag += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange2 == DEF_MAG)
            {
                cStateChange2 = 0;
                m_cLU_Mag += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange3 == DEF_MAG)
            {
                cStateChange3 = 0;
                m_cLU_Mag += 1;
                m_iLU_Point -= 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 222) && (msY <= sY + 228) && (m_cLU_Char < 0))
        {
            if (cStateChange1 == DEF_CHR)
            {
                cStateChange1 = 0;
                m_cLU_Char += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange2 == DEF_CHR)
            {
                cStateChange2 = 0;
                m_cLU_Char += 1;
                m_iLU_Point -= 1;
            }
            else if (cStateChange3 == DEF_CHR)
            {
                cStateChange3 = 0;
                m_cLU_Char += 1;
                m_iLU_Point -= 1;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((cStateChange1 == 0) || (cStateChange2 == 0) || (cStateChange3 == 0) && (m_iGizonItemUpgradeLeft > 0))
    {
        if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133) && (m_iStr > 10))
        {
            if (cStateChange1 == 0)
            {
                cStateChange1 = DEF_STR;
                m_cLU_Str -= 1;
                m_iLU_Point += 1;
            }
            else if (cStateChange2 == 0)
            {
                cStateChange2 = DEF_STR;
                m_cLU_Str -= 1;
                m_iLU_Point += 1;
            }
            else
            {
                cStateChange3 = DEF_STR;
                m_cLU_Str -= 1;
                m_iLU_Point += 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152) && (m_iVit > 10))
        {
            if (cStateChange1 == 0)
            {
                cStateChange1 = DEF_VIT;
                m_cLU_Vit -= 1;
                m_iLU_Point += 1;
            }
            else if (cStateChange2 == 0)
            {
                cStateChange2 = DEF_VIT;
                m_cLU_Vit -= 1;
                m_iLU_Point += 1;
            }
            else
            {
                cStateChange3 = DEF_VIT;
                m_cLU_Vit -= 1;
                m_iLU_Point += 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171) && (m_iDex > 10))
        {
            if (cStateChange1 == 0)
            {
                cStateChange1 = DEF_DEX;
                m_cLU_Dex -= 1;
                m_iLU_Point += 1;
            }
            else if (cStateChange2 == 0)
            {
                cStateChange2 = DEF_DEX;
                m_cLU_Dex -= 1;
                m_iLU_Point += 1;
            }
            else
            {
                cStateChange3 = DEF_DEX;
                m_cLU_Dex -= 1;
                m_iLU_Point += 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190) && (m_iInt > 10))
        {
            if (cStateChange1 == 0)
            {
                cStateChange1 = DEF_INT;
                m_cLU_Int -= 1;
                m_iLU_Point += 1;
            }
            else if (cStateChange2 == 0)
            {
                cStateChange2 = DEF_INT;
                m_cLU_Int -= 1;
                m_iLU_Point += 1;
            }
            else
            {
                cStateChange3 = DEF_INT;
                m_cLU_Int -= 1;
                m_iLU_Point += 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209) && (m_iMag > 10))
        {
            if (cStateChange1 == 0)
            {
                cStateChange1 = DEF_MAG;
                m_cLU_Mag -= 1;
                m_iLU_Point += 1;
            }
            else if (cStateChange2 == 0)
            {
                cStateChange2 = DEF_MAG;
                m_cLU_Mag -= 1;
                m_iLU_Point += 1;
            }
            else
            {
                cStateChange3 = DEF_MAG;
                m_cLU_Mag -= 1;
                m_iLU_Point += 1;
            }
            PlaySound('E', 14, 5);
        }

        if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228) && (m_iCharisma > 10))
        {
            if (cStateChange1 == 0)
            {
                cStateChange1 = DEF_CHR;
                m_cLU_Char -= 1;
                m_iLU_Point += 1;
            }
            else if (cStateChange2 == 0)
            {
                cStateChange2 = DEF_CHR;
                m_cLU_Char -= 1;
                m_iLU_Point += 1;
            }
            else
            {
                cStateChange3 = DEF_CHR;
                m_cLU_Char -= 1;
                m_iLU_Point += 1;
            }
            PlaySound('E', 14, 5);
        }
    }
    else
    {
        if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        {
            bSendCommand(MSGID_STATECHANGEPOINT, 0, 0, 0, 0, 0, 0);
            DisableDialogBox(42);
            PlaySound('E', 14, 5);
        }
    }
    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        DisableDialogBox(42);
        PlaySound('E', 14, 5);
    }
}


void CGame::DlgBoxClick_Resurect(short msX, short msY)
{
    short sX, sY;
    //#define MSGID_REQUEST_RESURRECTPLAYER_YES				0x0FC94214
    //#define MSGID_REQUEST_RESURRECTPLAYER_NO				0x0FC94215
    sX = m_stDialogBoxInfo[50].sX;
    sY = m_stDialogBoxInfo[50].sY;
    if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
    {   // yes
        bSendCommand(MSGID_REQUEST_RESURRECTPLAYER_YES, 0, 0, 0, 0, 0, 0, 0);
        DisableDialogBox(50);
    }
    else if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
    {	// no
        bSendCommand(MSGID_REQUEST_RESURRECTPLAYER_NO, 0, 0, 0, 0, 0, 0, 0);
        DisableDialogBox(50);
    }
}


void CGame::DlgBoxClick_CMDHallMenu(short msX, short msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[51].sX;
    sY = m_stDialogBoxInfo[51].sY;
    switch (m_stDialogBoxInfo[51].cMode)
    {
        case 0: // initial diag
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
            {
                m_stDialogBoxInfo[51].cMode = 1; // TP diag
                m_iTeleportMapCount = -1;
                bSendCommand(MSGID_REQUEST_HELDENIAN_TP_LIST, 0, 0, 0, 0, 0, 0);
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
            {
                m_stDialogBoxInfo[51].cMode = 2; // Soldier Diag
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145)
                /*&& (m_iEnemyKillCount >= 3)*/)
            {
                m_stDialogBoxInfo[51].cMode = 3; // Flag Diag
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145)
                /*&& (m_iEnemyKillCount >= 3)*/)
            {
                m_stDialogBoxInfo[51].cMode = 3; // Flag Diag
                PlaySound('E', 14, 5);
            }

            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170)
                /*&& (m_iGizonItemUpgradeLeft >= 5)*/)
            {
                m_stDialogBoxInfo[51].cMode = 4; // Flag Diag
                PlaySound('E', 14, 5);
            }


        case 1: // TP now
            if (m_iTeleportMapCount > 0)
            {
                for (int i = 0; i < m_iTeleportMapCount; i++)
                {
                    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i * 15) && (msY <= sY + 144 + i * 15))
                    {
                        bSendCommand(MSGID_REQUEST_HELDENIAN_TP, 0, 0, m_stTeleportList[i].iIndex, 0, 0, 0);
                        DisableDialogBox(51);
                        return;
                    }
                }
            }
            break;

        case 2: // Buy a soldier scroll
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 70) && (msY < sY + 95)
                && (m_iConstructionPoint >= 2000) && (m_bIsCrusadeMode == false)) // Sorceress
            {
                bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 875, 1, 2, 3, 4, "Gail", 5);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 95) && (msY < sY + 120)
                && (m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == false)) // ATK
            {
                bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 876, 0, 0, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 120) && (msY < sY + 145)
                && (m_iConstructionPoint >= 1500) && (m_bIsCrusadeMode == false)) // Elf
            {
                bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 877, 0, 0, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 145) && (msY < sY + 170)
                && (m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == false)) // DSK
            {
                bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 878, 0, 0, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 170) && (msY < sY + 195)
                && (m_iConstructionPoint >= 4000) && (m_bIsCrusadeMode == false)) // HBT
            {
                bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 879, 0, 0, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY > sY + 195) && (msY < sY + 220)
                && (m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == false)) // Barbarian
            {
                bSendCommand(MSGID_REQUEST_HELDENIAN_SCROLL, 880, 0, 0, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 3: // Buy a Flag
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 140) && (msY <= sY + 165)
                && (m_iEnemyKillCount >= 3))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETOCCUPYFLAG, 0, 0, 0, 0, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 4: // Buy an Angel
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 175) && (msY <= sY + 200)
                && (m_iGizonItemUpgradeLeft >= 5))
            {
                bSendCommand(MSGID_REQUEST_ANGEL, 0, 0, 1, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 200) && (msY <= sY + 225)
                && (m_iGizonItemUpgradeLeft >= 5))
            {
                bSendCommand(MSGID_REQUEST_ANGEL, 0, 0, 2, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 225) && (msY <= sY + 250)
                && (m_iGizonItemUpgradeLeft >= 5))
            {
                bSendCommand(MSGID_REQUEST_ANGEL, 0, 0, 3, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 250) && (msY <= sY + 275)
                && (m_iGizonItemUpgradeLeft >= 5))
            {
                bSendCommand(MSGID_REQUEST_ANGEL, 0, 0, 4, 0, 0, "Gail", 0);
                PlaySound('E', 14, 5);
            }

            break;
    }
}


void CGame::DrawDialogBox_IconPannel(short msX, short msY)
{
    short sX, sY;
    uint64_t dwTime = m_dwCurTime;

    sX = m_stDialogBoxInfo[30].sX;
    sY = m_stDialogBoxInfo[30].sY;

    m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(sX, sY, 14, dwTime);

    if ((362 < msX) && (404 > msX) && (434 < msY) && (475 > msY))
    {
        m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(362, 434, 16, dwTime);
    }

    if (m_bIsCombatMode)
    {
        if (m_bIsSafeAttackMode)
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(368, 440, 4, dwTime);
        else m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(368, 440, 5, dwTime);
    }

    if ((m_bIsCrusadeMode) && (m_iCrusadeDuty != 0))
    {
        if (m_bAresden == true)
        {
            if ((322 <= msX) && (355 >= msX) && (434 < msY) && (475 > msY))
                m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 1, dwTime);
            else m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 2, dwTime);
        }
        else if (m_bAresden == false)
        {
            if ((322 <= msX) && (355 >= msX) && (434 < msY) && (475 > msY))
                m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 0, dwTime);
            else m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 15, dwTime);
        }
    }

    if (m_iLU_Point > 0)
    {
        if ((322 <= msX) && (355 >= msX) && (434 < msY) && (475 > msY))
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 17, dwTime);
        else m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(322, 434, 18, dwTime);
    }

    if ((msY > 436) && (msY < 478))
    {
        if ((msX > 410) && (msX < 447))
        {
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(412, 434, 6, dwTime);// Character
        }
        if ((msX > 447) && (msX < 484))
        {
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(449, 434, 7, dwTime);// Inventory
        }
        if ((msX > 484) && (msX < 521))
        {
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(486, 434, 8, dwTime);// Magic
        }
        if ((msX > 521) && (msX < 558))
        {
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(523, 434, 9, dwTime);// Skill
        }
        if ((msX > 558) && (msX < 595))
        {
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(560, 434, 10, dwTime);// History
        }
        if ((msX > 595) && (msX < 631))
        {
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFast(597, 434, 11, dwTime);// System Menu
        }
    }

    if (((msX > 144) && (msX < 317) && (msY > 434) && (msY < 477)) || (m_bCtrlPressed))
    {
        int iLev = 0;
        int iCurExp = iGetLevelExp(m_iLevel);
        int iNextExp = iGetLevelExp(m_iLevel + 1);

#ifdef DEF_4XXP_PER_LVL
        if (m_iLevel > 139)
        {
            iLev = (m_iLevel - 139) * 3;
            iNextExp = iGetLevelExp(m_iLevel + iLev);
        }
#endif

#ifdef DEF_EQUILIBRIUM_PROJECT // XP niv 151..153
        if ((m_bCitizen == true) && (m_iLevel > 150))
        {
            iCurExp = iGetLevelExp(150);
            iNextExp = iGetLevelExp(151);
        }
#endif

        if (m_iExp < iNextExp)
        {
            iNextExp = iNextExp - iCurExp;
            if (m_iExp > iCurExp) iCurExp = m_iExp - iCurExp; // curxp: partie faite
            else iCurExp = 0; // below current lvl !
            short sPerc = 0;
            if (iCurExp > 200000) sPerc = short(((iCurExp >> 4) * 10000) / (iNextExp >> 4));
            else sPerc = (short)((iCurExp * 10000) / iNextExp);
            wsprintfA(G_cTxt, "Rest Exp: %d(%d.%02d%%)", iNextExp - iCurExp, sPerc / 100, sPerc % 100);
        }
        else
        {
            wsprintfA(G_cTxt, "Exp: %d(100.00%)", m_iExp); // "Exp: 151000/150000"
        }
    }
    else wsprintfA(G_cTxt, "%s(%d,%d)", m_cMapMessage, m_sPlayerX, m_sPlayerY);
    PutAlignedString(135, 328, 456, G_cTxt, 200, 200, 120);
}

void CGame::DrawDialogBox_GaugePannel()
{
    int iMaxPoint, iBarWidth;
    // HP bar

#ifdef DEF_EQUILIBRIUM_PROJECT // HPs formula
    if (m_iAngelicStr != 0) iMaxPoint = m_iVit * 3 + (m_iLevel * 3 + (m_iStr + m_iAngelicStr)) / 2;
    else			       iMaxPoint = m_iVit * 3 + (m_iLevel * 3 + m_iStr) / 2;
#else

    if (m_iAngelicStr != 0) iMaxPoint = m_iVit * 3 + m_iLevel * 2 + (m_iStr + m_iAngelicStr) / 2;
    else				   iMaxPoint = m_iVit * 3 + m_iLevel * 2 + m_iStr / 2;
#endif

    if (m_iHP > iMaxPoint) m_iHP = iMaxPoint;
    iBarWidth = 101 - (m_iHP * 101) / iMaxPoint;
    if (iBarWidth < 0) iBarWidth = 0;
    if (iBarWidth > 101) iBarWidth = 101;
    m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFastWidth(23, 437, 12, iBarWidth, m_dwCurTime);

    wsprintfA(G_cTxt, "%d", (short)m_iHP);
    if (m_bIsPoisoned)
    {
        PutString_SprNum(85, 441, G_cTxt, m_wR[5] * 11, m_wG[5] * 11, m_wB[5] * 11);
        PutString_SprFont3(35, 440, "Poisoned", m_wR[5] * 8, m_wG[5] * 8, m_wB[5] * 8, true, 2);
    }
    else PutString_SprNum(85, 441, G_cTxt, 200, 100, 100);

    //MP bar
    iMaxPoint = (m_iMag + m_iAngelicMag) * 2 + m_iLevel * 2 + (m_iInt + m_iAngelicInt) / 2;
    if (m_iMP > iMaxPoint) m_iMP = iMaxPoint;
    iBarWidth = 101 - (m_iMP * 101) / iMaxPoint;
    if (iBarWidth < 0) iBarWidth = 0;
    if (iBarWidth > 101) iBarWidth = 101;
    m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFastWidth(23, 459, 12, iBarWidth, m_dwCurTime);
    wsprintfA(G_cTxt, "%d", (short)m_iMP);
    PutString_SprNum(85, 463, G_cTxt, 100, 100, 200);

    // SP bar
    if (m_iAngelicStr != 0) iMaxPoint = m_iLevel * 2 + (m_iStr + m_iAngelicStr) * 2;
    else				   iMaxPoint = m_iLevel * 2 + m_iStr * 2;
    if (m_iSP > iMaxPoint) m_iSP = iMaxPoint;
    iBarWidth = 167 - (m_iSP * 167) / iMaxPoint;
    if (iBarWidth < 0) iBarWidth = 0;
    if (iBarWidth > 167) iBarWidth = 167;
    m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutSpriteFastWidth(147, 435, 13, iBarWidth, m_dwCurTime);
}

void CGame::DrawDialogBox_Text(short msX, short msY, short msZ, char cLB)
{
    short sX, sY;
    int i, iTotalLines, iPointerLoc;
    double d1, d2, d3;

    sX = m_stDialogBoxInfo[18].sX;
    sY = m_stDialogBoxInfo[18].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);

    iTotalLines = 0;
    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
        if (m_pMsgTextList[i] != 0) iTotalLines++;

    if (iTotalLines > 17) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 1);
    if (iGetTopDialogBoxIndex() == 18 && msZ != 0)
    {
        m_stDialogBoxInfo[18].sView = m_stDialogBoxInfo[18].sView - msZ / 60;
        m_stMCursor.sZ = 0;
    }
    if (m_stDialogBoxInfo[18].sView < 0) m_stDialogBoxInfo[18].sView = 0;
    if (iTotalLines > 17 && m_stDialogBoxInfo[18].sView > iTotalLines - 17) m_stDialogBoxInfo[18].sView = iTotalLines - 17;

    if (iTotalLines > 17)
    {
        d1 = (double)m_stDialogBoxInfo[18].sView;
        d2 = (double)(iTotalLines - 17);
        d3 = (274.0f * d1) / d2;
        iPointerLoc = (int)(d3 + 0.5);
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 1);
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 242, sY + 35 + iPointerLoc, 7);
    }
    else iPointerLoc = 0;

    for (i = 0; i < 17; i++)
        if (m_pMsgTextList[i + m_stDialogBoxInfo[18].sView] != 0)
        {
            if (m_bDialogTrans == false)
            { // v2.173
                switch (m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg[0])
                {
                    case '_': PutAlignedString(sX + 24, sX + 236, sY + 50 + i * 13, (m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg + 1), 255, 255, 255); break;
                    case ';': PutAlignedString(sX + 24, sX + 236, sY + 50 + i * 13, (m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg + 1), 4, 0, 50); break;
                    default: PutAlignedString(sX + 24, sX + 236, sY + 50 + i * 13, m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg, 45, 25, 25); break;
                }
            }
            else PutAlignedString(sX + 24, sX + 236, sY + 50 + i * 13, m_pMsgTextList[i + m_stDialogBoxInfo[18].sView]->m_pMsg, 0, 0, 0);
        }

    if (cLB != 0 && iTotalLines > 17)
    {
        if ((iGetTopDialogBoxIndex() == 18))
        {
            if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320))
            {
                d1 = (double)(msY - (sY + 35));
                d2 = (double)(iTotalLines - 17);
                d3 = (d1 * d2) / 274.0f;
                iPointerLoc = (int)d3;
                if (iPointerLoc > iTotalLines - 17) iPointerLoc = iTotalLines - 17;
                m_stDialogBoxInfo[18].sView = iPointerLoc;
            }
        }
    }
    else m_stDialogBoxInfo[18].bIsScrollSelected = false;

    if ((msX > sX + DEF_RBTNPOSX) && (msX < sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void CGame::DrawDialogBox_15AgeMsg(short msX, short msY)
{
}


void CGame::DrawDialogBox_WarningMsg(short msX, short msY)//6
{
    short sX, sY;

    sX = m_stDialogBoxInfo[6].sX;
    sY = m_stDialogBoxInfo[6].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX, sY, 2);

    PutString2(sX + 63, sY + 35, DEF_MSG_WARNING1, 200, 200, 25);//" ** This is a battle area **"
    PutString(sX + 30, sY + 57, DEF_MSG_WARNING2, Color(220, 130, 45));//"This is a dangerous area where you"
    PutString(sX + 30, sY + 74, DEF_MSG_WARNING3, Color(220, 130, 45));//"cannot protected from others' attack."
    PutString(sX + 30, sY + 92, DEF_MSG_WARNING4, Color(220, 130, 45));//"To play the game in safe, go to the"
    PutString(sX + 30, sY + 110, DEF_MSG_WARNING5, Color(220, 130, 45));//" cityhall and change to civilian mode."

    if ((msX >= sX + 122) && (msX <= sX + 125 + DEF_BTNSZX) && (msY >= sY + 127) && (msY <= sY + 127 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 122, sY + 127, 1);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 122, sY + 127, 0);

}

void CGame::DrawDialogBox_ItemDrop(short msX, short msY)
{
    short sX, sY;
    char cTxt[120], cStr1[64], cStr2[64], cStr3[64];

    sX = m_stDialogBoxInfo[4].sX;
    sY = m_stDialogBoxInfo[4].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

    GetItemName(m_pItemList[m_stDialogBoxInfo[4].sView]->m_cName, m_pItemList[m_stDialogBoxInfo[4].sView]->m_dwAttribute, cStr1, cStr2, cStr3);

    if (strlen(m_stDialogBoxInfo[4].cStr) == 0)  wsprintfA(cTxt, "%s", cStr1);

    if (m_bIsSpecial)
    {
        PutString(sX + 35, sY + 20, cTxt, Color(0, 255, 50));
        PutString(sX + 36, sY + 20, cTxt, Color(0, 255, 50));
    }
    else
    {
        PutString(sX + 35, sY + 20, cTxt, Color(4, 0, 50));
        PutString(sX + 36, sY + 20, cTxt, Color(4, 0, 50));
    }
    PutString(sX + 35, sY + 36, DRAW_DIALOGBOX_ITEM_DROP1, Color(4, 0, 50));
    PutString(sX + 36, sY + 36, DRAW_DIALOGBOX_ITEM_DROP1, Color(4, 0, 50));

    if (m_bItemDrop)
    {
        if ((msX >= sX + 35) && (msX <= sX + 240) && (msY >= sY + 80) && (msY <= sY + 90))
        {
            PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, Color(255, 255, 255));
            PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, Color(255, 255, 255));
        }
        else
        {
            PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, Color(4, 0, 50));
            PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP2, Color(4, 0, 50));
        }
    }
    else
    {
        if ((msX >= sX + 35) && (msX <= sX + 240) && (msY >= sY + 80) && (msY <= sY + 90))
        {
            PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, Color(255, 255, 255));
            PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, Color(255, 255, 255));
        }
        else
        {
            PutString(sX + 35, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, Color(4, 0, 50));
            PutString(sX + 36, sY + 80, DRAW_DIALOGBOX_ITEM_DROP3, Color(4, 0, 50));
        }
    }

    if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55, 19);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55, 18);

    if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55, 3);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55, 2);
}

void CGame::DrawDialogBox_NpcTalk(short msX, short msY, char cLB)
{
    short sX, sY;
    int i, iTotalLines, iPointerLoc;
    double d1, d2, d3;
    sX = m_stDialogBoxInfo[21].sX;
    sY = m_stDialogBoxInfo[21].sY;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);

    switch (m_stDialogBoxInfo[21].cMode)
    {
        case 0: //  OK
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 1: // Accept / Decline
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 41);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 40);
            break;

        case 2: // Next
            if ((msX >= sX + 190) && (msX <= sX + 278) && (msY >= sY + 296) && (msY <= sY + 316))
                PutString_SprFont(sX + 190, sY + 270, "Next", 6, 6, 20);
            else PutString_SprFont(sX + 190, sY + 270, "Next", 0, 0, 7);
            break;
    }

    for (i = 0; i < 17; i++)
        if ((i < DEF_TEXTDLGMAXLINES) && (m_pMsgTextList2[i + m_stDialogBoxInfo[21].sView] != 0))
        {
            PutAlignedString(sX, sX + m_stDialogBoxInfo[21].sSizeX, sY + 57 + i * 15, m_pMsgTextList2[i + m_stDialogBoxInfo[21].sView]->m_pMsg, 45, 25, 25);
        }

    iTotalLines = 0;
    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
        if (m_pMsgTextList2[i] != 0) iTotalLines++;

    if (iTotalLines > 17)
    {
        d1 = (double)m_stDialogBoxInfo[21].sView;
        d2 = (double)(iTotalLines - 17);
        d3 = (274.0f * d1) / d2;
        iPointerLoc = (int)d3;
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 3);
    }
    else iPointerLoc = 0;

    if (cLB != 0 && iTotalLines > 17)
    {
        if ((iGetTopDialogBoxIndex() == 21))
        {
            if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320))
            {
                d1 = (double)(msY - (sY + 40));
                d2 = (double)(iTotalLines - 17);
                d3 = (d1 * d2) / 274.0f;
                iPointerLoc = (int)d3;

                if (iPointerLoc > iTotalLines) iPointerLoc = iTotalLines;
                m_stDialogBoxInfo[21].sView = iPointerLoc;
            }
        }
    }
    else m_stDialogBoxInfo[21].bIsScrollSelected = false;
}

void CGame::DrawDialogBox_Slates(short msX, short msY, short msZ, char cLB)
{
    int iAdjX, iAdjY;
    short sX, sY;
    uint64_t dwTime = m_dwCurTime;

    iAdjX = 5;
    iAdjY = 8;

    switch (m_stDialogBoxInfo[40].cMode)
    {
        // Slates Dialog
        case 1:
            sX = m_stDialogBoxInfo[40].sX;
            sY = m_stDialogBoxInfo[40].sY;
            iAdjX = -1;
            iAdjY = -7;

            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX, sY, 4);

            if (m_stDialogBoxInfo[40].sV1 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 20, sY + 12, 5);
            }
            if (m_stDialogBoxInfo[40].sV2 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 20, sY + 87, 6);
            }
            if (m_stDialogBoxInfo[40].sV3 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 85, sY + 32, 7);
            }
            if (m_stDialogBoxInfo[40].sV4 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 70, sY + 97, 8);
            }

            if ((m_stDialogBoxInfo[40].sV1 != -1) && (m_stDialogBoxInfo[40].sV2 != -1) && (m_stDialogBoxInfo[40].sV3 != -1) && (m_stDialogBoxInfo[40].sV4 != -1))
            {
                if ((msX >= sX + 120) && (msX <= sX + 180) && (msY >= sY + 150) && (msY <= sY + 165))
                    PutString_SprFont(sX + 120, sY + 150, "Casting", 6, 6, 20);
                else PutString_SprFont(sX + 120, sY + 150, "Casting", 0, 0, 7);
            }

            break;

            // Slates Dialog
        case 2:
            PlaySound('E', 16, 0);
            if (m_stDialogBoxInfo[40].cStr[0] != 0)
            {
                sX = m_stDialogBoxInfo[40].sX + iAdjX + (m_stDialogBoxInfo[40].cStr[0] - (rand() % (m_stDialogBoxInfo[40].cStr[0] * 2)));
                sY = m_stDialogBoxInfo[40].sY + iAdjY + (m_stDialogBoxInfo[40].cStr[0] - (rand() % (m_stDialogBoxInfo[40].cStr[0] * 2)));
            }
            else
            {
                sX = m_stDialogBoxInfo[40].sX;
                sY = m_stDialogBoxInfo[40].sY;
            }
            m_pSprite[DEF_SPRID_INTERFACE_ND_INVENTORY]->PutSpriteFast(sX, sY, 4, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ND_INVENTORY]->PutSpriteFast(sX + 22, sY + 14, 3, dwTime);
            //PutString_SprFont(sX + iAdjX + 170, sY + iAdjY + 170, "KURURURURURURURURU!!!", 20,6,6);
            PutAlignedString(199, 438, 201, "KURURURURURURURURU!!!", 220, 140, 160);
            PutAlignedString(200, 439, 200, "KURURURURURURURURU!!!", 90, 220, 200);

            if ((dwTime - m_stDialogBoxInfo[40].dwT1) > 1000)
            {
                m_stDialogBoxInfo[40].dwT1 = dwTime;
                m_stDialogBoxInfo[40].cStr[0]++;
            }
            if (m_stDialogBoxInfo[40].cStr[0] >= 5)
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_CREATESLATE, 0, m_stDialogBoxInfo[40].sV1, m_stDialogBoxInfo[40].sV2, m_stDialogBoxInfo[40].sV3, 0, m_stDialogBoxInfo[40].sV4);
                DisableDialogBox(40);
            }
            break;
    }
}

void CGame::DlgBoxClick_Slates(short msX, short msY)
{
    int iAdjX, iAdjY;
    short sX, sY;

    sX = m_stDialogBoxInfo[40].sX;
    sY = m_stDialogBoxInfo[40].sY;
    iAdjX = 5;
    iAdjY = 8;
    switch (m_stDialogBoxInfo[40].cMode)
    {
        // Slates DialogBox
        case 1:
            if ((m_stDialogBoxInfo[40].sV1 != -1) && (m_stDialogBoxInfo[40].sV2 != -1) && (m_stDialogBoxInfo[40].sV3 != -1) && (m_stDialogBoxInfo[40].sV4 != -1))
            {
                if ((msX >= sX + 120) && (msX <= sX + 180) && (msY >= sY + 150) && (msY <= sY + 165))
                {
                    m_stDialogBoxInfo[40].cMode = 2;
                    PlaySound('E', 14, 5);
                }
            }
            break;
    }
}

void CGame::DlgBoxClick_NpcTalk(int msX, int msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[21].sX;
    sY = m_stDialogBoxInfo[21].sY;

    switch (m_stDialogBoxInfo[21].cMode)
    {
        case 0: //  OK
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                DisableDialogBox(21);
                PlaySound('E', 14, 5);
            }
            break;

        case 1: // Accept / Decline
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Accept
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_QUESTACCEPTED, 0, 0, 0, 0, 0);
                DisableDialogBox(21);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Cancel
                DisableDialogBox(21);
                PlaySound('E', 14, 5);
            }
            break;

        case 2:	// Next
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                DisableDialogBox(21);
                PlaySound('E', 14, 5);
            }
            break;
    }
}

void CGame::DrawDialogBox_Chat(short msX, short msY, short msZ, char cLB)
{
    short sX, sY;
    int i, iPointerLoc;
    double d1, d2, d3;
    sX = m_stDialogBoxInfo[10].sX;
    sY = m_stDialogBoxInfo[10].sY;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 4, false, m_bDialogTrans);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 22, false, m_bDialogTrans);

    if (msZ != 0 && (iGetTopDialogBoxIndex() == 10))
    {
        m_stDialogBoxInfo[10].sView = m_stDialogBoxInfo[10].sView + msZ / 30;
        m_stMCursor.sZ = 0;
    }
    if (m_stDialogBoxInfo[10].sView < 0) m_stDialogBoxInfo[10].sView = 0;
    if (m_stDialogBoxInfo[10].sView > DEF_MAXCHATSCROLLMSGS - 8) m_stDialogBoxInfo[10].sView = DEF_MAXCHATSCROLLMSGS - 8;

    d1 = (double)m_stDialogBoxInfo[10].sView;
    d2 = (double)(105);
    d3 = (d1 * d2) / (DEF_MAXCHATSCROLLMSGS - 8);
    iPointerLoc = (int)d3;
    iPointerLoc = 105 - iPointerLoc;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 346, sY + 33 + iPointerLoc, 7);

    for (i = 0; i < 8; i++)
        if (m_pChatScrollList[i + m_stDialogBoxInfo[10].sView] != 0)
        {
            switch (m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_dwTime)
            {
                case 0:  PutString2(sX + 25, sY + 127 - i * 13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 230, 230, 230); break;
                case 1:  PutString2(sX + 25, sY + 127 - i * 13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 130, 200, 130); break;
                case 2:  PutString2(sX + 25, sY + 127 - i * 13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 255, 130, 130); break;
                case 3:  PutString2(sX + 25, sY + 127 - i * 13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 130, 130, 255); break;
                case 4:  PutString2(sX + 25, sY + 127 - i * 13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 230, 230, 130); break;
                case 10: PutString2(sX + 25, sY + 127 - i * 13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 180, 255, 180); break;
                case 20: PutString2(sX + 25, sY + 127 - i * 13, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg, 150, 150, 170); break;
            }
        }

    if ((cLB != 0) && (iGetTopDialogBoxIndex() == 10))
    {
        if ((msX >= sX + 336) && (msX <= sX + 361) && (msY >= sY + 28) && (msY <= sY + 140))
        {
            d1 = (double)(msY - (sY + 28));
            d2 = ((DEF_MAXCHATSCROLLMSGS - 8) * d1) / 105.0f;
            m_stDialogBoxInfo[10].sView = DEF_MAXCHATSCROLLMSGS - 8 - (int)d2;
        }

        if ((msX >= sX + 336) && (msX <= sX + 361) && (msY > sY + 18) && (msY < sY + 28))
            m_stDialogBoxInfo[10].sView = DEF_MAXCHATSCROLLMSGS - 8;

        if ((msX >= sX + 336) && (msX <= sX + 361) && (msY > sY + 140) && (msY < sY + 163))
            m_stDialogBoxInfo[10].sView = 0;
    }
    else m_stDialogBoxInfo[10].bIsScrollSelected = false;
}

void CGame::DlgBoxClick_ItemUpgrade(int msX, int msY)
{
    short sX, sY;
    int i, iSoX = 0, iSoM = 0;
    sX = m_stDialogBoxInfo[34].sX;
    sY = m_stDialogBoxInfo[34].sY;
    switch (m_stDialogBoxInfo[34].cMode)
    {
        case 1:	// Upgrade Majestic, items in the window
            if ((m_stDialogBoxInfo[34].sV1 != -1) && (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                int iValue = (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_dwAttribute & 0xF0000000) >> 28;
                iValue = iValue * (iValue + 6) / 8 + 2;
                if (m_iGizonItemUpgradeLeft < iValue) break;
                PlaySound('E', 14, 5);
                PlaySound('E', 44, 0);
                m_stDialogBoxInfo[34].cMode = 2;
                m_stDialogBoxInfo[34].dwV1 = unixtime();
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                PlaySound('E', 14, 5);
                DisableDialogBox(34);
            }
            break;

        case 3: // success
        case 4: // Not possible
        case 7: // Lost item
        case 8: // Failed
        case 9: // Failed
        case 10:// Failed
        case 12:// 12 Need stone!
        case 13:// 13 remove stones!
        case 14:// 14 No Oil present
        case 15:// 15 too much Oil error
        case 16:// 16 too much Elixir error
        case 17:// 17 remove Oils
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// OK
                PlaySound('E', 14, 5);
                DisableDialogBox(34);
            }
            break;



#ifdef DEF_EQUILIBRIUM_PROJECT // Upgrade Main menu click
        case 5: // main menu
            int iSoX, iSoM, iSoO, iSoE;
            iSoX = iSoM = iSoO = iSoE = 0;
            int iOilIndex, iElixirIndex;
            iOilIndex = iElixirIndex = -1;
            for (i = 0; i < DEF_MAXITEMS; i++)
                if (m_pItemList[i] != 0)
                {
                    if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 128)) iSoX++;
                    if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 129)) iSoM++;
                    if ((m_pItemList[i]->m_cItemType != DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX) // Strange stone to enchant Ancient weapon
                        && ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 163)))
                    {
                        iOilIndex = i;
                        iSoO++;
                    }
                    if ((m_pItemList[i]->m_cItemType != DEF_ITEMTYPE_EAT) // Not a summon potions
                        && (m_pItemList[i]->m_sSprite == 6)
                        && (m_pItemList[i]->m_sSpriteFrame >= 108)
                        && (m_pItemList[i]->m_sSpriteFrame <= 112))
                    {
                        int len = strlen(m_pItemList[i]->m_cName) - 6;
                        if (len <= 0)
                        {
                            iOilIndex = i;
                            iSoO++;
                        }
                        else
                        {
                            if (strcmp(m_pItemList[i]->m_cName + len, "Elixir") == 0)
                            {
                                iElixirIndex = i;
                                iSoE++; // Elixir
                            }
                            else
                            {
                                iOilIndex = i;
                                iSoO++;
                            }
                        }
                    }
                    if ((m_pItemList[i]->m_cItemType != DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX) // Not Slate
                        && (m_pItemList[i]->m_sSprite == 6)
                        && (m_pItemList[i]->m_sSpriteFrame == 155))
                    {
                        iOilIndex = i;
                        iSoO++;
                    }
                }
            m_stDialogBoxInfo[34].sV2 = iSoX;
            m_stDialogBoxInfo[34].sV3 = iSoM;
            m_stDialogBoxInfo[34].sV4 = iOilIndex;
            m_stDialogBoxInfo[34].sV5 = iElixirIndex;
            m_stDialogBoxInfo[34].sV6 = iSoX + iSoM;
            if (iSoO == 0) m_stDialogBoxInfo[34].sV7 = 0; // No Oil present
            else if (iSoO > 1)  m_stDialogBoxInfo[34].sV7 = 1; // Too much Oil error
            else if (iSoE > 1)  m_stDialogBoxInfo[34].sV7 = 2; // Too much Elixir error
            else                m_stDialogBoxInfo[34].sV7 = 3; // Correct Ol/Elixir

            if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 80) && (msY < sY + 95))
            {
                if (m_stDialogBoxInfo[34].sV6 <= 0)
                {
                    m_stDialogBoxInfo[34].cMode = 12;		// 12 Need stone!
                    PlaySound('E', 14, 5);
                }
                else
                {
                    m_stDialogBoxInfo[34].cMode = 6;		// 6 Xelima / Merien upgrade
                    PlaySound('E', 14, 5);
                }
            }
            else if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 100) && (msY < sY + 115))
            {
                if (m_stDialogBoxInfo[34].sV6 != 0)
                {
                    m_stDialogBoxInfo[34].cMode = 13;		// 13 remove stones!
                    PlaySound('E', 14, 5);
                }
                else if (m_stDialogBoxInfo[34].sV7 == 0)
                {
                    m_stDialogBoxInfo[34].cMode = 14;		// 14 No Oil present
                    PlaySound('E', 14, 5);
                }
                else if (m_stDialogBoxInfo[34].sV7 == 1)
                {
                    m_stDialogBoxInfo[34].cMode = 15;		// 15 too much Oil error
                    PlaySound('E', 14, 5);
                }
                else if (m_stDialogBoxInfo[34].sV7 == 2)
                {
                    m_stDialogBoxInfo[34].cMode = 16;		// 16 too much Elixir error
                    PlaySound('E', 14, 5);
                }
                else
                {
                    m_stDialogBoxInfo[34].cMode = 11;		// 11  Alchemy enchantement
                    PlaySound('E', 14, 5);
                }
            }
            else if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 120) && (msY < sY + 135))
            {
                if (m_stDialogBoxInfo[34].sV6 != 0)
                {
                    m_stDialogBoxInfo[34].cMode = 13;		// 13 remove stones!
                    PlaySound('E', 14, 5);
                }
                else if (m_stDialogBoxInfo[34].sV7 > 0)
                {
                    m_stDialogBoxInfo[34].cMode = 17;		// 17 remove Oils
                    PlaySound('E', 14, 5);
                }
                else
                {
                    m_stDialogBoxInfo[34].cMode = 1;		// 1  gizon upgrade
                    PlaySound('E', 14, 5);
                }
            }
            if ((m_stDialogBoxInfo[34].sV1 != -1) && (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Upgrade
                PlaySound('E', 14, 5);
                PlaySound('E', 44, 0);
                m_stDialogBoxInfo[34].cMode = 2;
                m_stDialogBoxInfo[34].dwV1 = unixtime();
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                PlaySound('E', 14, 5);
                DisableDialogBox(34);
            }
            break;
#else
        case 5: // main menu
            if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 100) && (msY < sY + 115))
            {
                PlaySound('E', 14, 5);
                iSoX = iSoM = 0;
                for (i = 0; i < DEF_MAXITEMS; i++)
                    if (m_pItemList[i] != 0)
                    {
                        if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 128)) iSoX++;
                        if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 129)) iSoM++;
                    }
                if ((iSoX > 0) || (iSoM > 0))
                {
                    m_stDialogBoxInfo[34].cMode = 6;
                    m_stDialogBoxInfo[34].sV2 = iSoX;
                    m_stDialogBoxInfo[34].sV3 = iSoM;
                }
                else AddEventList(DRAW_DIALOGBOX_ITEMUPGRADE30, 10); //"Stone of Xelima or Merien is not present."
            }
            if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 120) && (msY < sY + 135))
            {
                m_stDialogBoxInfo[34].cMode = 1;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                PlaySound('E', 14, 5);
                DisableDialogBox(34);
            }
            break;
#endif

        case 6: // Upgrade Xelima / Merien
            if ((m_stDialogBoxInfo[34].sV1 != -1) && (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Upgrade
                PlaySound('E', 14, 5);
                PlaySound('E', 44, 0);
                m_stDialogBoxInfo[34].cMode = 2;
                m_stDialogBoxInfo[34].dwV1 = unixtime();
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                PlaySound('E', 14, 5);
                DisableDialogBox(34);
            }
            break;


#ifdef DEF_EQUILIBRIUM_PROJECT // Upgrade alchimie click
        case 11: // Alchemy enchantement
            if ((m_stDialogBoxInfo[34].sV1 != -1)
                && (msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX)
                && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Enchant
                PlaySound('E', 14, 5);
                PlaySound('E', 44, 0);
                m_stDialogBoxInfo[34].cMode = 2;
                m_stDialogBoxInfo[34].dwV1 = unixtime();
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                PlaySound('E', 14, 5);
                DisableDialogBox(34);
            }
            break;
#endif
    }
}

void CGame::DlgBoxClick_SellList(short msX, short msY)
{
    int i, x;
    short sX, sY;
    sX = m_stDialogBoxInfo[31].sX;
    sY = m_stDialogBoxInfo[31].sY;
    for (i = 0; i < DEF_MAXSELLLIST; i++)
        if ((msX > sX + 25) && (msX < sX + 250) && (msY >= sY + 55 + i * 15) && (msY <= sY + 55 + 14 + i * 15))
        {
            if (m_pItemList[m_stSellItemList[i].iIndex] != 0)
            {
                m_bIsItemDisabled[m_stSellItemList[i].iIndex] = false;
                m_stSellItemList[i].iIndex = -1;

                PlaySound('E', 14, 5);

                // ÀçÁ¤·Ä
                for (x = 0; x < DEF_MAXSELLLIST - 1; x++)
                    if (m_stSellItemList[x].iIndex == -1)
                    {
                        m_stSellItemList[x].iIndex = m_stSellItemList[x + 1].iIndex;
                        m_stSellItemList[x].iAmount = m_stSellItemList[x + 1].iAmount;

                        m_stSellItemList[x + 1].iIndex = -1;
                        m_stSellItemList[x + 1].iAmount = 0;
                    }
            }
            return;
        }

    if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        // Sell
        bSendCommand(MSGID_REQUEST_SELLITEMLIST, 0, 0, 0, 0, 0, 0);
        PlaySound('E', 14, 5);
        DisableDialogBox(31);
    }

    if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        // Cancel
        PlaySound('E', 14, 5);
        DisableDialogBox(31);
    }
}

void CGame::DlgBoxClick_LevelUpSettings(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[12].sX;
    sY = m_stDialogBoxInfo[12].sY;
    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 127) && (msY <= sY + 133) && (m_iStr <= DEF_MAX_STATS) && (m_iLU_Point > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_iLU_Point >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point -= 5;
                m_cLU_Str += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_iLU_Point > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point--;
                m_cLU_Str++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 146) && (msY <= sY + 152) && (m_iVit <= DEF_MAX_STATS) && (m_iLU_Point > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_iLU_Point >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point -= 5;
                m_cLU_Vit += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_iLU_Point > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point--;
                m_cLU_Vit++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 165) && (msY <= sY + 171) && (m_iDex <= DEF_MAX_STATS) && (m_iLU_Point > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_iLU_Point >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point -= 5;
                m_cLU_Dex += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_iLU_Point > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point--;
                m_cLU_Dex++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 184) && (msY <= sY + 190) && (m_iInt <= DEF_MAX_STATS) && (m_iLU_Point > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_iLU_Point >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point -= 5;
                m_cLU_Int += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_iLU_Point > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point--;
                m_cLU_Int++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 203) && (msY <= sY + 209) && (m_iMag <= DEF_MAX_STATS) && (m_iLU_Point > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_iLU_Point >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point -= 5;
                m_cLU_Mag += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_iLU_Point > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point--;
                m_cLU_Mag++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 222) && (msY <= sY + 228) && (m_iCharisma <= DEF_MAX_STATS) && (m_iLU_Point > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_iLU_Point >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point -= 5;
                m_cLU_Char += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_iLU_Point > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_iLU_Point--;
                m_cLU_Char++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133) && (m_cLU_Str > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_cLU_Str >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Str -= 5;
                m_iLU_Point += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_cLU_Str > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Str--;
                m_iLU_Point++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152) && (m_cLU_Vit > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_cLU_Vit >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Vit -= 5;
                m_iLU_Point += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_cLU_Vit > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Vit--;
                m_iLU_Point++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171) && (m_cLU_Dex > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_cLU_Dex >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Dex -= 5;
                m_iLU_Point += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_cLU_Dex > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Dex--;
                m_iLU_Point++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190) && (m_cLU_Int > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_cLU_Int >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Int -= 5;
                m_iLU_Point += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_cLU_Int > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Int--;
                m_iLU_Point++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209) && (m_cLU_Mag > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_cLU_Mag >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Mag -= 5;
                m_iLU_Point += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_cLU_Mag > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Mag--;
                m_iLU_Point++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228) && (m_cLU_Char > 0))
    {
        if (m_bCtrlPressed == true)
        {
            if ((m_cLU_Char >= 5) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Char -= 5;
                m_iLU_Point += 5;
            }
            PlaySound('E', 14, 5);
        }
        else
        {
            if ((m_cLU_Char > 0) && (m_bIsDialogEnabled[42] == false))
            {
                m_cLU_Char--;
                m_iLU_Point++;
            }
            PlaySound('E', 14, 5);
        }
    }

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        if (m_stDialogBoxInfo[12].sV1 != m_iLU_Point)
            bSendCommand(MSGID_LEVELUPSETTINGS, 0, 0, 0, 0, 0, 0);
        //m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
        DisableDialogBox(12);
        PlaySound('E', 14, 5);
    }
    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
    {	// Change stats with Majestic
        if ((m_iGizonItemUpgradeLeft > 0) && (m_iLU_Point <= 0)
            && (m_cLU_Str == 0) && (m_cLU_Vit == 0) && (m_cLU_Dex == 0) && (m_cLU_Int == 0) && (m_cLU_Mag == 0) && (m_cLU_Char == 0))
        {
            DisableDialogBox(12);
            EnableDialogBox(42, 0, 0, 0);
            //PlaySound('E', 14, 5);
        }
    }
}


void CGame::DlgBoxClick_Text(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[18].sX;
    sY = m_stDialogBoxInfo[18].sY;

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        DisableDialogBox(18);
        PlaySound('E', 14, 5);
    }
}

void CGame::DlgBoxClick_Inventory(short msX, short msY)
{
    int i, sX, sY;
    sX = m_stDialogBoxInfo[2].sX;
    sY = m_stDialogBoxInfo[2].sY;
    if ((msX >= sX + 23) && (msX <= sX + 76) && (msY >= sY + 172) && (msY <= sY + 184))
    {
        if (m_iGizonItemUpgradeLeft == 0)
        {
            m_iGizonItemUpgradeLeft = 0;
        }
        EnableDialogBox(34, 5, 0, 0);
        PlaySound('E', 14, 5);

    }
    if ((msX >= sX + 140) && (msX <= sX + 212) && (msY >= sY + 172) && (msY <= sY + 184))
    {
        if (m_cSkillMastery[13] == 0)
        {
            AddEventList(DLGBOXCLICK_INVENTORY1, 10);
            AddEventList(DLGBOXCLICK_INVENTORY2, 10);//"The manufacturing manual is purchasable in Blacksmith."
        }
        else if (m_bSkillUsingStatus == true)
        {
            AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY5, 10);//""You are already using another skill."
            return;
        }
        else if (_bIsItemOnHand() == true)
        {
            AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);//""Your hands should be free to use this item."
            return;
        }
        else
        {
            for (i = 0; i < DEF_MAXITEMS; i++)
                if ((m_pItemList[i] != 0) && (m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX)
                    && (m_pItemList[i]->m_sSpriteFrame == 113)
                    && (m_pItemList[i]->m_wCurLifeSpan > 0))
                {
                    EnableDialogBox(26, 3, 0, 0, 0);
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY12, 10);//"Using a manufacturing skill..."
                    PlaySound('E', 14, 5);
                    return;
                }
            AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY14, 10);
        }
        PlaySound('E', 14, 5);
    }
}

void CGame::DlgBoxClick_Character(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[1].sX;
    sY = m_stDialogBoxInfo[1].sY;
    /*
        if ((msX >= sX + 100) && (msX <= sX + 150) && (msY >= sY + 90) && (msY <= sY + 110)) {
            MessageBoxA(0,"CRASHED!!!!","JK",MB_OK);
            DisableDialogBox(1);
            PlaySound('E', 14, 5);
        }*/

    if ((msX >= sX + 15) && (msX <= sX + 15 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
    {
        EnableDialogBox(28, 1, 0, 0);
        DisableDialogBox(1);
        PlaySound('E', 14, 5);
    }
    else if ((msX >= sX + 98) && (msX <= sX + 98 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
    {
        EnableDialogBox(32, 0, 0, 0);
        DisableDialogBox(1);
        PlaySound('E', 14, 5);
    }
    else if ((msX >= sX + 180) && (msX <= sX + 180 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
    {
        EnableDialogBox(12, 0, 0, 0);
        DisableDialogBox(1);
        PlaySound('E', 14, 5);
    }
}

void CGame::DlgBoxClick_FeedBackCard(short msX, short msY)
{

}

void CGame::DlgBoxClick_MagicShop(short msX, short msY)
{
    int i, iCPivot, iYloc, iAdjX, iAdjY;
    short sX, sY;

    sX = m_stDialogBoxInfo[16].sX;
    sY = m_stDialogBoxInfo[16].sY;

    iAdjX = -20;
    iAdjY = -35;

    iCPivot = m_stDialogBoxInfo[16].sView * 10;

    iYloc = 0;
    for (i = 0; i < 9; i++)
    {
        if ((m_pMagicCfgList[iCPivot + i] != 0) && (m_pMagicCfgList[iCPivot + i]->m_bIsVisible))
        {
            if ((msX >= sX + iAdjX + 44) && (msX <= sX + iAdjX + 135 + 44) && (msY >= sY + iAdjY + 70 + iYloc + 35) && (msY <= sY + iAdjY + 70 + 14 + iYloc + 35))
            {
                if (m_cMagicMastery[iCPivot + i] == 0)
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_STUDYMAGIC, 0, 0, 0, 0, m_pMagicCfgList[iCPivot + i]->m_cName);
                    //bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_STUDYMAGIC, 0, iCPivot + i, 0, 0, 0); //2002.02.07 »óÇÏ º¯°æ ¹è¿ì°í½ÍÀº ¸ÅÁ÷³×ÀÓ¿¡¼­ ¸¶¹ý¹øÈ£·Î º¯°æ..
                    PlaySound('E', 14, 5);
                }
                return;
            }
            iYloc += 18;
        }
    }

    if ((msX >= sX + iAdjX + 42 + 31) && (msX <= sX + iAdjX + 50 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 0;
    if ((msX >= sX + iAdjX + 55 + 31) && (msX <= sX + iAdjX + 68 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 1;
    if ((msX >= sX + iAdjX + 73 + 31) && (msX <= sX + iAdjX + 93 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 2;
    if ((msX >= sX + iAdjX + 98 + 31) && (msX <= sX + iAdjX + 113 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 3;
    if ((msX >= sX + iAdjX + 118 + 31) && (msX <= sX + iAdjX + 129 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 4;
    if ((msX >= sX + iAdjX + 133 + 31) && (msX <= sX + iAdjX + 150 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 5;
    if ((msX >= sX + iAdjX + 154 + 31) && (msX <= sX + iAdjX + 177 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 6;
    if ((msX >= sX + iAdjX + 181 + 31) && (msX <= sX + iAdjX + 210 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 7;
    if ((msX >= sX + iAdjX + 214 + 31) && (msX <= sX + iAdjX + 230 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 8;
    if ((msX >= sX + iAdjX + 234 + 31) && (msX <= sX + iAdjX + 245 + 31) && (msY >= sY + iAdjY + 248 + 35) && (msY <= sY + iAdjY + 260 + 35))
        m_stDialogBoxInfo[16].sView = 9;
}


void CGame::DlgBoxClick_GuildOp(short msX, short msY)
{
    short sX, sY;
    char cName[12], cName20[24];

    ZeroMemory(cName, sizeof(cName));
    ZeroMemory(cName20, sizeof(cName20));
    sX = m_stDialogBoxInfo[8].sX;
    sY = m_stDialogBoxInfo[8].sY;

    switch (m_stGuildOpList[0].cOpMode)
    {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                _ShiftGuildOperationList();
                if (m_stGuildOpList[0].cOpMode == 0) DisableDialogBox(8);
            }
            return;
    }

    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        // Approve
        PlaySound('E', 14, 5);

        switch (m_stGuildOpList[0].cOpMode)
        {
            case 1:
                strcpy(cName20, m_stGuildOpList[0].cName);
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_JOINGUILDAPPROVE, 0, 0, 0, 0, cName20);
                break;

            case 2:
                strcpy(cName20, m_stGuildOpList[0].cName);
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_DISMISSGUILDAPPROVE, 0, 0, 0, 0, cName20);
                break;
        }
        _ShiftGuildOperationList();
        if (m_stGuildOpList[0].cOpMode == 0) DisableDialogBox(8);
    }

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        // Reject
        PlaySound('E', 14, 5);

        switch (m_stGuildOpList[0].cOpMode)
        {
            case 1:
                strcpy(cName20, m_stGuildOpList[0].cName);
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_JOINGUILDREJECT, 0, 0, 0, 0, cName20);
                break;

            case 2:
                strcpy(cName20, m_stGuildOpList[0].cName);
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_DISMISSGUILDREJECT, 0, 0, 0, 0, cName20);
                break;
        }

        _ShiftGuildOperationList();
        if (m_stGuildOpList[0].cOpMode == 0) DisableDialogBox(8);
    }
}


void CGame::DlgBoxClick_IconPannel(short msX, short msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[30].sX;
    sY = m_stDialogBoxInfo[30].sY;
    /*	if ((msX > 322)	&& (msX < 355) && (434 < msY) && (475 > msY))
        {	if (m_iLU_Point <= 0) return;
            if (m_bIsDialogEnabled[12] == true)
                 DisableDialogBox(12);
            else EnableDialogBox(12, 0, 0, 0);
            PlaySound('E', 14, 5);
        }*/
    if ((msX > 322) && (msX < 355) && (434 < msY) && (475 > msY))
    {
        // Crusade
        if (m_bIsCrusadeMode == false) return;
        switch (m_iCrusadeDuty)
        {
            case 1: // Fighter
                EnableDialogBox(38, 0, 0, 0);
                break;

            case 2: // Constructor
                EnableDialogBox(37, 0, 0, 0);
                break;

            case 3: // Commander
                EnableDialogBox(36, 0, 0, 0);
                break;

            default: break;
        }
        PlaySound('E', 14, 5);
    }

    if ((362 < msX) && (404 > msX) && (434 < msY) && (475 > msY))
    {
        // Combat Mode Toggle
        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, 0, 0, 0, 0, 0);
        PlaySound('E', 14, 5);
    }

    // Character
    if ((413 <= msX) && (446 >= msX) && (434 < msY) && (475 > msY))
    {
        if (m_bIsDialogEnabled[1] == true)
            DisableDialogBox(1);
        else EnableDialogBox(1, 0, 0, 0);
        PlaySound('E', 14, 5);
    }

    // Inventory
    if ((453 <= msX) && (486 >= msX) && (434 < msY) && (475 > msY))
    {
        if (m_bIsDialogEnabled[2] == true)
            DisableDialogBox(2);
        else EnableDialogBox(2, 0, 0, 0);
        PlaySound('E', 14, 5);
    }

    // Magic
    if ((490 <= msX) && (522 >= msX) && (434 < msY) && (475 > msY))
    {
        if (m_bIsDialogEnabled[3] == true)
            DisableDialogBox(3);
        else EnableDialogBox(3, 0, 0, 0);
        PlaySound('E', 14, 5);
    }

    // Skill
    if ((526 <= msX) && (552 >= msX) && (434 < msY) && (475 > msY))
    {
        if (m_bIsDialogEnabled[15] == true)
            DisableDialogBox(15);
        else EnableDialogBox(15, 0, 0, 0);
        PlaySound('E', 14, 5);
    }

    // Chat
    if ((556 <= msX) && (587 >= msX) && (434 < msY) && (475 > msY))
    {
        if (m_bIsDialogEnabled[10] == true)
            DisableDialogBox(10);
        else EnableDialogBox(10, 0, 0, 0);
        PlaySound('E', 14, 5);
    }

    // System Menu
    if ((589 <= msX) && (621 >= msX) && (434 < msY) && (475 > msY))
    {
        if (m_bIsDialogEnabled[19] == true)
            DisableDialogBox(19);
        else EnableDialogBox(19, 0, 0, 0);
        PlaySound('E', 14, 5);
    }
}


void CGame::DlgBoxClick_Party(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[32].sX;
    sY = m_stDialogBoxInfo[32].sY;

    switch (m_stDialogBoxInfo[32].cMode)
    {
        case 0:
            if (m_iPartyStatus == 0)
            {
                if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 80) && (msY < sY + 100))
                {
                    m_stDialogBoxInfo[32].cMode = 2;
                    m_bIsGetPointingMode = true;
                    m_iPointCommandType = 200;
                    PlaySound('E', 14, 5);
                }
            }

            if (m_iPartyStatus != 0)
            {
                if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 100) && (msY < sY + 120))
                {
                    m_stDialogBoxInfo[32].cMode = 11;
                    PlaySound('E', 14, 5);
                }
            }

            if (m_iPartyStatus != 0)
            {
                if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 120) && (msY < sY + 140))
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, 0, 2, 0, 0, m_cMCName);
                    m_stDialogBoxInfo[32].cMode = 4;
                    PlaySound('E', 14, 5);
                }
            }

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY)) DisableDialogBox(32);
            break;

        case 1:
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACCEPTJOINPARTY, 0, 1, 0, 0, m_stDialogBoxInfo[32].cStr);
                DisableDialogBox(32);
                PlaySound('E', 14, 5);
            }

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACCEPTJOINPARTY, 0, 0, 0, 0, m_stDialogBoxInfo[32].cStr);
                DisableDialogBox(32);
                PlaySound('E', 14, 5);
            }
            break;

        case 2:
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                m_stDialogBoxInfo[32].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 3:
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                m_stDialogBoxInfo[32].cMode = 0;
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACCEPTJOINPARTY, 0, 2, 0, 0, m_stDialogBoxInfo[32].cStr);
                DisableDialogBox(32);
                PlaySound('E', 14, 5);
            }
            break;

        case 4:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                m_stDialogBoxInfo[32].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 11:
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, 0, 0, 0, 0, m_cMCName);
                m_stDialogBoxInfo[32].cMode = 5;
                PlaySound('E', 14, 5);
            }

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                m_stDialogBoxInfo[32].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;
    }
}

void CGame::DlgBoxClick_CrusadeJob(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[33].sX;
    sY = m_stDialogBoxInfo[33].sY;

    switch (m_stDialogBoxInfo[33].cMode)
    {
        case 1:
            if (m_bCitizen == false)
            {
                DisableDialogBox(33);
                PlaySound('E', 14, 5);
            }
            else if (m_bAresden == true)
            {
                if (m_iGuildRank == 0)
                {
                    if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 3, 0, 0, 0);
                        DisableDialogBox(33);
                        PlaySound('E', 14, 5);
                    }
                }
                else
                {
                    if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 1, 0, 0, 0);
                        DisableDialogBox(33);
                    }
                    if (m_iGuildRank != -1)
                    {
                        if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
                        {
                            bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 2, 0, 0, 0);
                            DisableDialogBox(33);
                            PlaySound('E', 14, 5);
                        }
                    }
                }
            }
            else if (m_bAresden == false)
            {
                if (m_iGuildRank == 0)
                {
                    if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 3, 0, 0, 0);
                        DisableDialogBox(33);
                        PlaySound('E', 14, 5);
                    }
                }
                else
                {
                    if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 1, 0, 0, 0);
                        DisableDialogBox(33);
                        PlaySound('E', 14, 5);
                    }
                    if (m_iGuildRank != -1)
                    {
                        if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
                        {
                            bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY, 0, 2, 0, 0, 0);
                            DisableDialogBox(33);
                            PlaySound('E', 14, 5);
                        }
                    }
                }
            }

            if ((msX > sX + 210) && (msX < sX + 260) && (msY >= sY + 296) && (msY <= sY + 316))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 813, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 2:
            if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 160) && (msY < sY + 175))
            {
                switch (m_iCrusadeDuty)
                {
                    case 1: EnableDialogBox(18, 803, 0, 0); break;
                    case 2: EnableDialogBox(18, 805, 0, 0); break;
                    case 3: EnableDialogBox(18, 808, 0, 0); break;
                }
            }

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                DisableDialogBox(33);
                PlaySound('E', 14, 5);
            }
            break;
    }
}


void CGame::DlgBoxClick_Commander(int msX, int msY)
{
    short sX, sY, tX, tY;
    double d1, d2, d3;
    if (m_bIsCrusadeMode == false) return;
    sX = m_stDialogBoxInfo[36].sX;
    sY = m_stDialogBoxInfo[36].sY;

    switch (m_stDialogBoxInfo[36].cMode)
    {
        case 0: // Main
            if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[36].cMode = 1;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                if (m_iTeleportLocX == -1)
                {
                    SetTopMsg(m_pGameMsgList[15]->m_pMsg, 5);
                }
                else if (strcmp(m_cMapName, m_cTeleportMapName) == 0)
                {
                    SetTopMsg(m_pGameMsgList[16]->m_pMsg, 5);
                }
                else
                {
                    m_stDialogBoxInfo[36].cMode = 2;
                    PlaySound('E', 14, 5);
                }
            }
            if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 46 + 100) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[36].cMode = 3;
                m_stDialogBoxInfo[36].sV1 = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 46 + 150) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[36].cMode = 4;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 808, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 1: // Set TP
            if ((msX >= sX + 15) && (msX <= sX + 15 + 278) && (msY >= sY + 60) && (msY <= sY + 60 + 272))
            {
                d1 = (double)(msX - (sX + 15));
                d2 = (double)(524.0f); //(752.0f);
                d3 = (d2 * d1) / 279.0f;
                tX = (int)d3;
                d1 = (double)(msY - (sY + 60));
                d2 = (double)(524.0f); //(680.0f);
                d3 = (d2 * d1) / (280.0f); //253.0f;
                tY = (int)d3;
                if (tX < 30) tX = 30;
                if (tY < 30) tY = 30;
                if (tX > 494) tX = 494;//722;
                if (tY > 494) tY = 494;//650;
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETGUILDTELEPORTLOC, 0, tX, tY, 0, "middleland");
                m_stDialogBoxInfo[36].cMode = 0;
                PlaySound('E', 14, 5);
                _RequestMapStatus("middleland", 1);
            }
            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[36].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 809, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 2: // Use TP
            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GUILDTELEPORT, 0, 0, 0, 0, 0);
                DisableDialogBox(36);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[36].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 810, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 3: // Summon Unit
            if (m_bAresden == true)
            {
                if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 3000)
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 47, 1, m_stDialogBoxInfo[36].sV1, 0);
                        PlaySound('E', 14, 5);
                        DisableDialogBox(36);
                    }
                }
                if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 2000)
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 46, 1, m_stDialogBoxInfo[36].sV1, 0);
                        PlaySound('E', 14, 5);
                        DisableDialogBox(36);
                    }
                }
                if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 1000)
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 43, 1, m_stDialogBoxInfo[36].sV1, 0);
                        PlaySound('E', 14, 5);
                        DisableDialogBox(36);
                    }
                }
                if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 1500)
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 51, 1, m_stDialogBoxInfo[36].sV1, 0);
                        PlaySound('E', 14, 5);
                        DisableDialogBox(36);
                    }
                }
            }
            else if (m_bAresden == false)
            {
                if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 3000)
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 45, 1, m_stDialogBoxInfo[36].sV1, 0);
                        PlaySound('E', 14, 5);
                        DisableDialogBox(36);
                    }
                }
                if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 2000)
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 44, 1, m_stDialogBoxInfo[36].sV1, 0);
                        PlaySound('E', 14, 5);
                        DisableDialogBox(36);
                    }
                }
                if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 1000)
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 43, 1, m_stDialogBoxInfo[36].sV1, 0);
                        PlaySound('E', 14, 5);
                        DisableDialogBox(36);
                    }
                }
                if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 1500)
                    {
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 51, 1, m_stDialogBoxInfo[36].sV1, 0);
                        PlaySound('E', 14, 5);
                        DisableDialogBox(36);
                    }
                }
            }
            if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 140) && (msY < sY + 160))
            {
                m_stDialogBoxInfo[36].sV1 = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 160) && (msY < sY + 175))
            {
                m_stDialogBoxInfo[36].sV1 = 1;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[36].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 811, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 4: // Set constr
            if ((msX >= sX + 15) && (msX <= sX + 15 + 278)
                && (msY >= sY + 60) && (msY <= sY + 60 + 272))
            {
                d1 = (double)(msX - (sX + 15));
                d2 = (double)(524.0);//(752.0f);
                d3 = (d2 * d1) / 279.0f;
                tX = (int)d3;
                d1 = (double)(msY - (sY + 60));
                d2 = (double)(524.0);//(680.0f);
                d3 = (d2 * d1) / (280.0);//253.0f;
                tY = (int)d3;
                if (tX < 30) tX = 30;
                if (tY < 30) tY = 30;
                if (tX > 494) tX = 494;//722;
                if (tY > 494) tY = 494;//650;
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETGUILDCONSTRUCTLOC, 0, tX, tY, 0, "middleland");
                m_stDialogBoxInfo[36].cMode = 0;
                PlaySound('E', 14, 5);
                _RequestMapStatus("middleland", 1);
            }
            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[36].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 812, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;
    }
}

void CGame::DlgBoxClick_Constructor(int msX, int msY)
{
    short sX, sY;
    if (m_bIsCrusadeMode == false) return;
    sX = m_stDialogBoxInfo[37].sX;
    sY = m_stDialogBoxInfo[37].sY;

    switch (m_stDialogBoxInfo[37].cMode)
    {
        case 0: // Main
            if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                if (m_iConstructLocX == -1)
                {
                    SetTopMsg(m_pGameMsgList[14]->m_pMsg, 5);
                }
                else
                {
                    m_stDialogBoxInfo[37].cMode = 1;
                    PlaySound('E', 14, 5);
                }
            }
            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                if (m_iTeleportLocX == -1)
                {
                    SetTopMsg(m_pGameMsgList[15]->m_pMsg, 5);
                }
                else if (strcmp(m_cMapName, m_cTeleportMapName) == 0)
                {
                    SetTopMsg(m_pGameMsgList[16]->m_pMsg, 5);
                }
                else
                {
                    m_stDialogBoxInfo[37].cMode = 2;
                    PlaySound('E', 14, 5);
                }
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 805, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 1: // Choose building
            if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 38, 1, m_stDialogBoxInfo[36].sV1, 0);
                PlaySound('E', 14, 5);
                DisableDialogBox(37);
            }
            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 39, 1, m_stDialogBoxInfo[36].sV1, 0);
                PlaySound('E', 14, 5);
                DisableDialogBox(37);
            }
            if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 36, 1, m_stDialogBoxInfo[36].sV1, 0);
                PlaySound('E', 14, 5);
                DisableDialogBox(37);
            }
            if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SUMMONWARUNIT, 0, 37, 1, m_stDialogBoxInfo[36].sV1, 0);
                PlaySound('E', 14, 5);
                DisableDialogBox(37);
            }

            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
            {
                m_stDialogBoxInfo[37].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 806, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 2: // Use TP
            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GUILDTELEPORT, 0, 0, 0, 0, 0);
                DisableDialogBox(37);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[37].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 807, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;
    }
}

void CGame::DlgBoxClick_Soldier(int msX, int msY)
{
    short sX, sY;
    if (m_bIsCrusadeMode == false) return;
    sX = m_stDialogBoxInfo[38].sX;
    sY = m_stDialogBoxInfo[38].sY;

    switch (m_stDialogBoxInfo[38].cMode)
    {
        case 0: // Main dlg
            if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                if (m_iTeleportLocX == -1)
                {
                    SetTopMsg(m_pGameMsgList[15]->m_pMsg, 5);
                }
                else if (strcmp(m_cMapName, m_cTeleportMapName) == 0)
                {
                    SetTopMsg(m_pGameMsgList[16]->m_pMsg, 5);
                }
                else
                {
                    m_stDialogBoxInfo[38].cMode = 1;
                    PlaySound('E', 14, 5);
                }
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 803, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;

        case 1: // Use TP
            if ((msX >= sX + 20) && (msX <= sX + 20 + 46 + 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GUILDTELEPORT, 0, 0, 0, 0, 0);
                DisableDialogBox(38);
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_stDialogBoxInfo[38].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                DisableDialogBox(18);
                EnableDialogBox(18, 804, 0, 0);
                PlaySound('E', 14, 5);
            }
            break;
    }
}


void CGame::DlgBoxClick_ShutDownMsg(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[25].sX;
    sY = m_stDialogBoxInfo[25].sY;
    if ((msX >= sX + 210) && (msX <= sX + 210 + DEF_BTNSZX) && (msY > sY + 127) && (msY < sY + 127 + DEF_BTNSZY))
    {
        DisableDialogBox(25);
        PlaySound('E', 14, 5);
    }
}


void CGame::DlgBoxClick_Exchange(short msX, short msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[27].sX;
    sY = m_stDialogBoxInfo[27].sY;
    switch (m_stDialogBoxInfo[27].cMode)
    {
        case 1: // Not yet confirmed the exchange
            if ((msX >= sX + 220) && (msX <= sX + 220 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)) // Exchange
            {
                if ((m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_stDialogBoxExchangeInfo[4].sV1 != -1))
                {	/*bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CONFIRMEXCHANGEITEM, 0
                        , m_stDialogBoxExchangeInfo[0].sV1 // ItemID; inutilisé par serveur
                        , m_stDialogBoxExchangeInfo[0].sV3 // Amount; inutilisé par serveur
                        , 0, 0);	*/
                    PlaySound('E', 14, 5);
                    m_stDialogBoxInfo[27].cMode = 2;
                    // Show confirmation Diag instead.
                    EnableDialogBox(41, 0, 0, 0);
                    m_stDialogBoxInfo[41].cMode = 1;
                }
                return;
            }
            if ((msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)
                && (m_bIsDialogEnabled[41] == false)) // Cancel only possible if confirmation is not activated
            {
                DisableDialogBox(27);
                DisableDialogBox(22);
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CANCELEXCHANGEITEM, 0, 0, 0, 0, 0);
                PlaySound('E', 14, 5);
                return;
            }
            break;

        case 2: // Someone already confirmed the exchange
            /*	if ((msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY))  // Cancel
                {	DisableDialogBox(27);
                    DisableDialogBox(22);
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CANCELEXCHANGEITEM, 0, 0, 0, 0, 0);
                    PlaySound('E', 14, 5);
                    return;
                }*/
            break;
    }
}

void CGame::DlgBoxClick_ConfirmExchange(short msX, short msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[41].sX;
    sY = m_stDialogBoxInfo[41].sY;

    switch (m_stDialogBoxInfo[41].cMode)
    {
        case 1: // Not yet confirmed the exchange
            // yes
            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
            {
                if ((m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_stDialogBoxExchangeInfo[4].sV1 != -1))
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CONFIRMEXCHANGEITEM, 0
                        , m_stDialogBoxExchangeInfo[0].sV1 // ItemID; inutilisé par serveur
                        , m_stDialogBoxExchangeInfo[0].sV3 // Amount; inutilisé par serveur
                        , 0, 0);
                    PlaySound('E', 14, 5);
                    m_stDialogBoxInfo[27].cMode = 2;
                    m_stDialogBoxInfo[41].cMode = 2;
                }
                return;
            }
            // No
            if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
            {
                DisableDialogBox(41);
                DisableDialogBox(27);
                DisableDialogBox(22);
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CANCELEXCHANGEITEM, 0, 0, 0, 0, 0);
                PlaySound('E', 14, 5);
                return;
            }
            break;
        case 2: // waiting for other side to confirm
            break;
    }
}

void CGame::DlgBoxClick_Quest(int msX, int msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[28].sX;
    sY = m_stDialogBoxInfo[28].sY;

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        DisableDialogBox(28);
        PlaySound('E', 14, 5);
    }
}


void CGame::DlgBoxClick_Help(int msX, int msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[35].sX;
    sY = m_stDialogBoxInfo[35].sY;
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 0) && (msY < sY + 50 + 15 * 1))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 1000, 0, 0);
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 1) && (msY < sY + 50 + 15 * 2))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 900, 0, 0);
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 2) && (msY < sY + 50 + 15 * 3))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 901, 0, 0);
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 3) && (msY < sY + 50 + 15 * 4))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 902, 0, 0);
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 4) && (msY < sY + 50 + 15 * 5))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 903, 0, 0);
        m_bIsF1HelpWindowEnabled = true;
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 5) && (msY < sY + 50 + 15 * 6))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 904, 0, 0); //
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 6) && (msY < sY + 50 + 15 * 7))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 905, 0, 0); //
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 7) && (msY < sY + 50 + 15 * 8))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 906, 0, 0); //
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 8) && (msY < sY + 50 + 15 * 9))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 907, 0, 0); //
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 9) && (msY < sY + 50 + 15 * 10))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 908, 0, 0); //
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 10) && (msY < sY + 50 + 15 * 11))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 909, 0, 0); //
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 11) && (msY < sY + 50 + 15 * 12))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 910, 0, 0); //
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 12) && (msY < sY + 50 + 15 * 13))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 911, 0, 0); // FAQ
    }

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 13) && (msY < sY + 50 + 15 * 14))
    {
        DisableDialogBox(18);
        EnableDialogBox(18, 912, 0, 0); //
    }
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
    {
        PlaySound('E', 14, 5);
        DisableDialogBox(35);
    }
}


void CGame::DlgBoxClick_SysMenu(short msX, short msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[19].sX;
    sY = m_stDialogBoxInfo[19].sY;
    if ((msX >= sX + 120) && (msX <= sX + 150) && (msY >= sY + 63) && (msY <= sY + 74))
    {
        m_cDetailLevel = 0; // v1.41
        AddEventList(NOTIFY_MSG_DETAIL_LEVEL_LOW, 10);
        PlaySound('E', 14, 5);
    }

    if ((msX >= sX + 151) && (msX <= sX + 200) && (msY >= sY + 63) && (msY <= sY + 74))
    {
        m_cDetailLevel = 1;
        AddEventList(NOTIFY_MSG_DETAIL_LEVEL_MEDIUM, 10);
        PlaySound('E', 14, 5);
    }

    if ((msX >= sX + 201) && (msX <= sX + 234) && (msY >= sY + 63) && (msY <= sY + 74))
    {
        m_cDetailLevel = 2;
        AddEventList(NOTIFY_MSG_DETAIL_LEVEL_HIGH, 10);
        PlaySound('E', 14, 5);
    }

    if ((msX >= sX + 24) && (msX <= sX + 115) && (msY >= sY + 81) && (msY <= sY + 100))
    {
        if (m_bSoundFlag)
        {
            if (m_bSoundStat == true)
            {
                m_pESound[38].stop();
                m_bSoundStat = false;
                AddEventList(NOTIFY_MSG_SOUND_OFF, 10);
            }
            else
            {
                m_bSoundStat = true;
                AddEventList(NOTIFY_MSG_SOUND_ON, 10);
            }
        }
    }

    if ((msX >= sX + 116) && (msX <= sX + 202) && (msY >= sY + 81) && (msY <= sY + 100))
    {
        if (m_bSoundFlag)
        {
            if (m_bMusicStat == true) 	// Music Off
            {
                m_bMusicStat = false;
                AddEventList(NOTIFY_MSG_MUSIC_OFF, 10);
                if (m_bSoundFlag)
                {
                    m_pBGM.stop();
                }
            }
            else // Music On
            {
                if (m_bSoundFlag)
                {
                    m_bMusicStat = true;
                    AddEventList(NOTIFY_MSG_MUSIC_ON, 10);
                    StartBGM();
                }
            }
        }
    }


    if ((msX >= sX + 23) && (msX <= sX + 108) && (msY >= sY + 108) && (msY <= sY + 119))
    {
        if (m_bWhisper == true)
        {
            m_bWhisper = false;
            AddEventList(BCHECK_LOCAL_CHAT_COMMAND7, 10);
        }
        else
        {
            m_bWhisper = true;
            AddEventList(BCHECK_LOCAL_CHAT_COMMAND6, 10);
        }
    }

    if ((msX >= sX + 123) && (msX <= sX + 203) && (msY >= sY + 108) && (msY <= sY + 119))
    {
        if (m_bShout == true)
        {
            m_bShout = false;
            AddEventList(BCHECK_LOCAL_CHAT_COMMAND9, 10);
        }
        else
        {
            m_bShout = true;
            AddEventList(BCHECK_LOCAL_CHAT_COMMAND8, 10);
        }
    }

    //Transparency Change
    if ((msX >= sX + 28) && (msX <= sX + 235) && (msY >= sY + 156) && (msY <= sY + 171)) m_bDialogTrans = !m_bDialogTrans;

    //Guide Map Toggle
    if ((msX >= sX + 28) && (msX <= sX + 127) && (msY >= sY + 178) && (msY <= sY + 193))
    {
        if (m_bIsDialogEnabled[9]) DisableDialogBox(9);
        else EnableDialogBox(9, 0, 0, 0, 0);
    }

    if (m_bForceDisconn) return;
    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
    {


#ifdef DEF_EQUILIBRIUM_PROJECT // Full par prevents logout
        if (m_cLogOutCount == -1)
        {
            if (m_bFullParalyze == false)
            {
#ifdef _DEBUG
                m_cLogOutCount = 1;
#else
                m_cLogOutCount = 11;
#endif
            }
            else // Medusa kiss prevents logout
            {
                m_cLogOutCount = -1;
                AddEventList(DLGBOX_CLICK_SYSMENU3, 10);//"Logout impossible while victim of a Medusa's kiss.."
                DisableDialogBox(19);
            }
        }
        else if (m_cLogOutCount != -1)
        {
            m_cLogOutCount = -1;
            AddEventList(DLGBOX_CLICK_SYSMENU2, 10);//"Logout count stopped."
            DisableDialogBox(19);
        }
        PlaySound('E', 14, 5);
    }
#else
        if (m_cLogOutCount == -1)
        {
#ifdef _DEBUG
            m_cLogOutCount = 1;
#else
            m_cLogOutCount = 11;
#endif

        }
        else if (m_cLogOutCount != -1)
        {
            m_cLogOutCount = -1;
            AddEventList(DLGBOX_CLICK_SYSMENU2, 10);//"Logout count stopped."
            DisableDialogBox(19);
        }
        PlaySound('E', 14, 5);
}
#endif


    if ((m_iHP <= 0) && (m_cRestartCount == -1))
    {
        if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
        {
            m_cRestartCount = 5;
            m_dwRestartCountTime = unixtime();
            DisableDialogBox(19);
            wsprintfA(G_cTxt, DLGBOX_CLICK_SYSMENU1, m_cRestartCount); // "Restarting game....%d"
            AddEventList(G_cTxt, 10);
            PlaySound('E', 14, 5);
        }
    }
}


void CGame::DlgBoxClick_GuildMenu(short msX, short msY)
{
    short sX, sY;
    char cTemp[21];
    int iAdjX, iAdjY;
    sX = m_stDialogBoxInfo[7].sX;
    sY = m_stDialogBoxInfo[7].sY;

    iAdjX = -13;
    iAdjY = 30;

    switch (m_stDialogBoxInfo[7].cMode)
    {
        case 0:
            if ((msX > sX + iAdjX + 80) && (msX < sX + iAdjX + 210) && (msY > sY + iAdjY + 63) && (msY < sY + iAdjY + 78))
            {
                if (m_iGuildRank != -1) return;
                if (m_iCharisma < 20) return;
                if (m_iLevel < 20) return;
                if (m_bIsCrusadeMode) return;
                EndInputString();
                StartInputString(sX + 75, sY + 140, 21, m_cGuildName);
                m_stDialogBoxInfo[7].cMode = 1;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 72) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 82) && (msY < sY + iAdjY + 99))
            {
                if (m_iGuildRank != 0) return;
                if (m_bIsCrusadeMode) return;
                m_stDialogBoxInfo[7].cMode = 5;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 61) && (msX < sX + iAdjX + 226) && (msY > sY + iAdjY + 103) && (msY < sY + iAdjY + 120))
            {
                m_stDialogBoxInfo[7].cMode = 9;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 60) && (msX < sX + iAdjX + 227) && (msY > sY + iAdjY + 123) && (msY < sY + iAdjY + 139))
            {
                m_stDialogBoxInfo[7].cMode = 11;
                PlaySound('E', 14, 5);
            }
            if (m_iFightzoneNumber < 0) break;
            if ((msX > sX + iAdjX + 72) && (msX < sX + iAdjX + 228) && (msY > sY + iAdjY + 143) && (msY < sY + iAdjY + 169))
            {
                if (m_iGuildRank != 0) return;
                if (m_iFightzoneNumber == 0)	m_stDialogBoxInfo[7].cMode = 13;
                else  m_stDialogBoxInfo[7].cMode = 19;
                PlaySound('E', 14, 5);
            }
            break;
        case 1:
            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Submit
                if (strcmp(m_cGuildName, "NONE") == 0) return;
                if (strlen(m_cGuildName) == 0) return;
                bSendCommand(MSGID_REQUEST_CREATENEWGUILD, DEF_MSGTYPE_CONFIRM, 0, 0, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 2;
                EndInputString();
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                m_stDialogBoxInfo[7].cMode = 0;
                EndInputString();
                PlaySound('E', 14, 5);
            }
            break;

        case 3:
        case 4:
        case 7:
        case 8:
        case 10:
        case 12:
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                m_stDialogBoxInfo[7].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 9:
            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Purchase¹
                ZeroMemory(cTemp, sizeof(cTemp));
                strcpy(cTemp, "GuildAdmissionTicket");
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_PURCHASEITEM, 0, 1, 0, 0, cTemp);
                m_stDialogBoxInfo[7].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                m_stDialogBoxInfo[7].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 11:
            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Purchase
                ZeroMemory(cTemp, sizeof(cTemp));
                strcpy(cTemp, "GuildSecessionTicket");
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_PURCHASEITEM, 0, 1, 0, 0, cTemp);
                m_stDialogBoxInfo[7].cMode = 0;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                m_stDialogBoxInfo[7].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 5:
            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Confirm
                bSendCommand(MSGID_REQUEST_DISBANDGUILD, DEF_MSGTYPE_CONFIRM, 0, 0, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 6;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + 154) && (msX <= sX + 154 + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // Cancel
                m_stDialogBoxInfo[7].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 13:
            if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 168) && (msY < sY + iAdjY + 185))
            {
                bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 1, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 18;
                m_iFightzoneNumberTemp = 1;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 168) && (msY < sY + iAdjY + 185))
            {
                bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 2, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 18;
                m_iFightzoneNumberTemp = 2;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 188) && (msY < sY + iAdjY + 205))
            {
                bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 3, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 18;
                m_iFightzoneNumberTemp = 3;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 188) && (msY < sY + iAdjY + 205))
            {
                bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 4, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 18;
                m_iFightzoneNumberTemp = 4;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 208) && (msY < sY + iAdjY + 225))
            {
                bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 5, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 18;
                m_iFightzoneNumberTemp = 5;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 208) && (msY < sY + iAdjY + 225))
            {
                bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 6, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 18;
                m_iFightzoneNumberTemp = 6;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 228) && (msY < sY + iAdjY + 245))
            {
                bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 7, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 18;
                m_iFightzoneNumberTemp = 7;
                PlaySound('E', 14, 5);
            }
            if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 228) && (msY < sY + iAdjY + 245))
            {
                bSendCommand(MSGID_REQUEST_FIGHTZONE_RESERVE, 0, 0, 8, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 18;
                m_iFightzoneNumberTemp = 8;
                PlaySound('E', 14, 5);
            }
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {	// Cancel
                m_stDialogBoxInfo[7].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;

        case 14://
        case 15://
        case 16://
        case 17://
        case 21://
        case 22://
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                // OK
                m_stDialogBoxInfo[7].cMode = 0;
                PlaySound('E', 14, 5);
            }
            break;
    }
}


void CGame::DrawDialogBox_GuideMap(short msX, short msY, char cLB)
{
    int  m_iMaxMapIndex = DEF_SPRID_INTERFACE_GUIDEMAP + m_cMapIndex + 1;
    int  m_iMinMapIndex = DEF_SPRID_INTERFACE_GUIDEMAP;
    int  m_iMinMapSquare = m_cMapIndex;
    //telescope.pak:  frames 1..31 <=> DEF_SPRID_INTERFACE_GUIDEMAP +1...+31 <=> m_cMapIndex 0..30
    //telescope1.pak: frames 1..3  <=> DEF_SPRID_INTERFACE_GUIDEMAP +36..+38 <=> m_cMapIndex 35..37 et +
    if (m_cMapIndex < 0) return;
    if (m_cMapIndex >= 35)
    {
        m_iMaxMapIndex = DEF_SPRID_INTERFACE_GUIDEMAP + m_cMapIndex + 1;
        m_iMinMapIndex = DEF_SPRID_INTERFACE_GUIDEMAP + 35;
        m_iMinMapSquare = m_cMapIndex - 35;
    }
    short sX, sY, shX, shY, szX, szY;
    sX = m_stDialogBoxInfo[9].sX;
    sY = m_stDialogBoxInfo[9].sY;
    szX = m_stDialogBoxInfo[9].sSizeX;
    szY = m_stDialogBoxInfo[9].sSizeY;
    if (sX < 20) sX = 0;
    if (sY < 20) sY = 0;
    if (sX > 640 - 128 - 20) sX = 640 - 128;
    if (sY > 427 - 128 - 20) sY = 427 - 128;
    for (shX = -2; shX < 130; shX++)
    {
        m_DDraw.PutPixel(sX + shX, sY - 2, 50, 50, 50);
        m_DDraw.PutPixel(sX + shX, sY - 1, 50, 50, 50);
        m_DDraw.PutPixel(sX + shX, sY + 128, 50, 50, 50);
        m_DDraw.PutPixel(sX + shX, sY + 129, 50, 50, 50);
    }
    for (shY = -2; shY < 130; shY++)
    {
        m_DDraw.PutPixel(sX - 2, sY + shY, 50, 50, 50);
        m_DDraw.PutPixel(sX - 1, sY + shY, 50, 50, 50);
        m_DDraw.PutPixel(sX + 128, sY + shY, 50, 50, 50);
        m_DDraw.PutPixel(sX + 129, sY + shY, 50, 50, 50);
    }
    if (m_bZoomMap)
    {
        shX = m_sPlayerX - 64;
        shY = m_sPlayerY - 64;
        if (shX < 0) shX = 0;
        if (shY < 0) shY = 0;
        if (shX > m_pMapData->m_sMapSizeX - 128) shX = m_pMapData->m_sMapSizeX - 128;
        if (shY > m_pMapData->m_sMapSizeY - 128) shY = m_pMapData->m_sMapSizeY - 128;
        if (m_bDialogTrans) m_pSprite[m_iMaxMapIndex]->PutShiftTransSprite2(sX, sY, shX, shY, 0, m_dwCurTime);
        else m_pSprite[m_iMaxMapIndex]->PutShiftSpriteFast(sX, sY, shX, shY, 0, m_dwCurTime);
        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX - shX + m_sPlayerX, sY - shY + m_sPlayerY, 37, m_dwCurTime);

        if ((m_dwCurTime - m_dwMonsterEventTime) < 30000)
        {
            if ((m_dwCurTime % 500) < 370)
            {
                if (m_sEventX >= shX && m_sEventX <= shX + 128 && m_sEventY >= shY && m_sEventY <= shY + 128)
                    m_pSprite[DEF_SPRID_INTERFACE_MONSTER]->PutSpriteFast(sX + m_sEventX - shX, sY + m_sEventY - shY, m_sMonsterID, m_dwCurTime);
            }
        }
        else
        {
            m_dwMonsterEventTime = 0;
            m_sMonsterID = 0;
        }
    }
    else // Sans zoom
    {
        if (m_bDialogTrans) m_pSprite[m_iMinMapIndex]->PutTransSprite2(sX, sY, m_iMinMapSquare, m_dwCurTime);
        else m_pSprite[m_iMinMapIndex]->PutSpriteFastNoColorKey(sX, sY, m_iMinMapSquare, m_dwCurTime);
        shX = (m_sPlayerX * 128) / (m_pMapData->m_sMapSizeX);
        shY = (m_sPlayerY * 128) / (m_pMapData->m_sMapSizeX);
        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + shX, sY + shY, 37, m_dwCurTime);

        if ((G_dwGlobalTime - m_dwMonsterEventTime) < 30000)
        {
            if ((m_dwCurTime % 500) < 370)
            {
                shX = (m_sEventX * 128) / (m_pMapData->m_sMapSizeX);
                shY = (m_sEventY * 128) / (m_pMapData->m_sMapSizeX);
                m_pSprite[DEF_SPRID_INTERFACE_MONSTER]->PutSpriteFast(sX + shX, sY + shY, m_sMonsterID, m_dwCurTime);
            }
        }
        else
        {
            m_dwMonsterEventTime = 0;
            m_sMonsterID = 0;
        }
    }

    if (cLB != 0) return;
    if (msX >= sX && msX < sX + szY && msY >= sY && msY < sY + szY)
    {
        if (sY > 213) shY = sY - 17;
        else shY = sY + szY + 4;
        if (m_bZoomMap) PutString(sX, shY, DEF_MSG_GUIDEMAP_MIN, Color(200, 200, 120));//"(-)
        else PutString(sX, shY, DEF_MSG_GUIDEMAP_MAX, Color(200, 200, 120));//"(+)

        if (m_bZoomMap)
        {
            shX = m_sPlayerX - 64;
            shY = m_sPlayerY - 64;
            if (shX < 0) shX = 0;
            if (shY < 0) shY = 0;
            if (shX > m_pMapData->m_sMapSizeX - 128) shX = m_pMapData->m_sMapSizeX - 128;
            if (shY > m_pMapData->m_sMapSizeY - 128) shY = m_pMapData->m_sMapSizeY - 128;
            shX += msX - sX;
            shY += msY - sY;
        }
        else
        {
            shX = (msX - sX) * m_pMapData->m_sMapSizeX / 128;
            shY = (msY - sY) * m_pMapData->m_sMapSizeX / 128;
        }
        wsprintfA(G_cTxt, "%d, %d", shX, shY);
        if (m_cMapIndex == 11) // Aresden
        {
            if (shX > 46 && shX < 66 && shY > 107 && shY < 127) strcpy(G_cTxt, DEF_MSG_MAPNAME_MAGICTOWER);
            else if (shX > 103 && shX < 123 && shY > 86 && shY < 116)  strcpy(G_cTxt, DEF_MSG_MAPNAME_GUILDHALL);
            else if (shX > 176 && shX < 196 && shY >  62 && shY < 82)  strcpy(G_cTxt, DEF_MSG_MAPNAME_CATH);
            else if (shX > 135 && shX < 155 && shY > 113 && shY < 133) strcpy(G_cTxt, DEF_MSG_MAPNAME_CITYHALL);
            else if (shX > 97 && shX < 117 && shY > 175 && shY < 195) strcpy(G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
            else if (shX > 223 && shX < 243 && shY > 124 && shY < 144) strcpy(G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
            else if (shX > 118 && shX < 138 && shY > 157 && shY < 177) strcpy(G_cTxt, DEF_MSG_MAPNAME_SHOP);
            else if (shX > 148 && shX < 178 && shY > 188 && shY < 208) strcpy(G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
            else if (shX > 69 && shX < 89 && shY > 199 && shY < 219) strcpy(G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
            else if (shX > 21 && shX < 41 && shY > 266 && shY < 286) strcpy(G_cTxt, DEF_MSG_MAPNAME_HUNT);
            else if (shX > 20 && shX < 40 && shY > 13 && shY < 33)  strcpy(G_cTxt, DEF_MSG_MAPNAME_ML);
            else if (shX > 246 && shX < 266 && shY > 16 && shY < 36)  strcpy(G_cTxt, DEF_MSG_MAPNAME_ML);
            else if (shX > 265 && shX < 285 && shY > 195 && shY < 215) strcpy(G_cTxt, DEF_MSG_MAPNAME_FARM);
            else if (shX > 88 && shX < 108 && shY > 150 && shY < 170) strcpy(G_cTxt, DEF_MSG_MAPNAME_CMDHALL);
        }
        else if (m_cMapIndex == 3) // Elvine
        {
            if (shX > 170 && shX < 190 && shY >  65 && shY < 85)      strcpy(G_cTxt, DEF_MSG_MAPNAME_MAGICTOWER);
            else if (shX > 67 && shX < 87 && shY > 130 && shY < 150)  strcpy(G_cTxt, DEF_MSG_MAPNAME_GUILDHALL);
            else if (shX > 121 && shX < 141 && shY >  66 && shY < 86)  strcpy(G_cTxt, DEF_MSG_MAPNAME_CATH);
            else if (shX > 135 && shX < 155 && shY > 117 && shY < 137) strcpy(G_cTxt, DEF_MSG_MAPNAME_CITYHALL);
            else if (shX > 190 && shX < 213 && shY > 118 && shY < 138) strcpy(G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
            else if (shX > 73 && shX < 103 && shY > 165 && shY < 185) strcpy(G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
            else if (shX > 217 && shX < 237 && shY > 142 && shY < 162) strcpy(G_cTxt, DEF_MSG_MAPNAME_SHOP);
            else if (shX > 216 && shX < 256 && shY > 99 && shY < 119) strcpy(G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
            else if (shX > 251 && shX < 271 && shY >  73 && shY < 93)  strcpy(G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
            else if (shX > 212 && shX < 232 && shY > 13 && shY < 33)  strcpy(G_cTxt, DEF_MSG_MAPNAME_HUNT);
            else if (shX > 16 && shX < 36 && shY > 262 && shY < 282) strcpy(G_cTxt, DEF_MSG_MAPNAME_ML);
            else if (shX > 244 && shX < 264 && shY > 248 && shY < 268) strcpy(G_cTxt, DEF_MSG_MAPNAME_ML);
            else if (shX > 264 && shX < 284 && shY > 177 && shY < 207) strcpy(G_cTxt, DEF_MSG_MAPNAME_FARM);
            else if (shX > 207 && shX < 227 && shY > 79 && shY < 99)  strcpy(G_cTxt, DEF_MSG_MAPNAME_CMDHALL);
        }
        else if (m_cMapIndex == 5) // Elvine Farm
        {
            if (shX > 62 && shX < 82 && shY >  187 && shY < 207) strcpy(G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
            else if (shX > 81 && shX < 101 && shY > 169 && shY < 189) strcpy(G_cTxt, DEF_MSG_MAPNAME_SHOP);
            else if (shX > 101 && shX < 131 && shY > 180 && shY < 200) strcpy(G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
            else if (shX > 130 && shX < 150 && shY > 195 && shY < 215) strcpy(G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
            else if (shX > 86 && shX < 106 && shY > 139 && shY < 159) strcpy(G_cTxt, DEF_MSG_MAPNAME_BARRACK);
        }
        else if (m_cMapIndex == 6) // Areden's Farm
        {
            if (shX > 30 && shX < 50 && shY >  80 && shY < 100) strcpy(G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
            else if (shX > 55 && shX < 85 && shY > 80 && shY < 100)  strcpy(G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
            else if (shX > 52 && shX < 72 && shY > 80 && shY < 100)  strcpy(G_cTxt, DEF_MSG_MAPNAME_SHOP);
            else if (shX > 70 && shX < 90 && shY > 60 && shY < 80)   strcpy(G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
            else if (shX > 45 && shX < 65 && shY > 123 && shY < 143) strcpy(G_cTxt, DEF_MSG_MAPNAME_BARRACK);
        }
        else if (m_cMapIndex == 42) // Stadium
        {
            if (shX > 41 && shX < 57 && shY > 63 && shY < 77)  strcpy(G_cTxt, DEF_MSG_MAPNAME_SIDE_ARESDEN);
            else if (shX > 83 && shX < 99 && shY > 38 && shY < 52)  strcpy(G_cTxt, DEF_MSG_MAPNAME_SIDE_ELVINE);
            else if (shX > 29 && shX < 40 && shY > 103 && shY < 112) strcpy(G_cTxt, DEF_MSG_MAPNAME_DUELGRAVE);
            else if (shX > 80 && shX < 103 && shY > 103 && shY < 120) strcpy(G_cTxt, DEF_MSG_MAPNAME_FIELD);
        }
        else if (m_cMapIndex == 41) // lost (Equilibrium city)
        {
            if (shX > 192 && shX < 202 && shY > 165 && shY < 175) strcpy(G_cTxt, DEF_MSG_MAPNAME_WAREHOUSE);
            else if (shX > 145 && shX < 155 && shY > 190 && shY < 200) strcpy(G_cTxt, DEF_MSG_MAPNAME_BLACKSMITH);
            else if (shX > 136 && shX < 146 && shY > 162 && shY < 172) strcpy(G_cTxt, DEF_MSG_MAPNAME_SHOP);
            else if (shX > 203 && shX < 213 && shY > 140 && shY < 150) strcpy(G_cTxt, DEF_MSG_MAPNAME_MAGICTOWER);
            else if (shX > 80 && shX < 100 && shY > 164 && shY < 177) strcpy(G_cTxt, "Eldiniel's Church");
            else if (shX > 92 && shX < 108 && shY > 107 && shY < 120) strcpy(G_cTxt, "Aresien's Temple");
            else if (shX > 55 && shX < 65 && shY > 141 && shY < 151) strcpy(G_cTxt, "Mayor's Warehouse");
            else if (shX > 204 && shX < 224 && shY > 18 && shY < 28) strcpy(G_cTxt, "Qu's marsh");
            else if (shX > 223 && shX < 233 && shY > 28 && shY < 33) strcpy(G_cTxt, DEF_MSG_MAPNAME_DUNGEON);
            else if (shX > 43 && shX < 63 && shY > 250 && shY < 265) strcpy(G_cTxt, DEF_MSG_MAPNAME_HUNT);
        }
        PutString(msX - 10, msY - 13, G_cTxt, Color(200, 200, 120));
    }
}


void CGame::DrawDialogBox_Inventory(int msX, int msY)
{
    int i;
    short sX, sY;
    uint64_t dwTime = m_dwCurTime;
    char cItemColor;
    sX = m_stDialogBoxInfo[2].sX;
    sY = m_stDialogBoxInfo[2].sY;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX, sY, 0);
    for (i = 0; i < DEF_MAXITEMS; i++)
        if ((m_cItemOrder[i] != -1) && (m_pItemList[m_cItemOrder[i]] != 0))
        {
            if (((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_ITEM)
                && (m_stMCursor.sSelectedObjectID == m_cItemOrder[i])) || (m_bIsItemEquipped[m_cItemOrder[i]] == true))
            {
            }
            else
            {
                cItemColor = m_pItemList[m_cItemOrder[i]]->m_cItemColor;
                if (m_bIsItemDisabled[m_cItemOrder[i]] == true)
                {
                    if (cItemColor == 0)
                        m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutTransSprite2(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
                            sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame, dwTime);
                    else
                    {
                        if ((m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                            || (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                            || (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                        {
                            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutTransSpriteRGB(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
                                sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame,
                                m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0],
                                dwTime);
                        }
                        else
                        {
                            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutTransSpriteRGB(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
                                sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame,
                                m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0],
                                dwTime);
                        }
                    }
                }
                else
                {
                    if (cItemColor == 0)
                        m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutSpriteFast(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
                            sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame, dwTime);
                    else
                    {
                        if ((m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                            || (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                            || (m_pItemList[m_cItemOrder[i]]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                        {
                            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutSpriteRGB(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
                                sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame,
                                m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0],
                                dwTime);
                        }
                        else
                        {
                            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_cItemOrder[i]]->m_sSprite]->PutSpriteRGB(sX + 32 + m_pItemList[m_cItemOrder[i]]->m_sX,
                                sY + 44 + m_pItemList[m_cItemOrder[i]]->m_sY, m_pItemList[m_cItemOrder[i]]->m_sSpriteFrame,
                                m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0],
                                dwTime);
                        }
                    }
                }
                if ((m_pItemList[m_cItemOrder[i]]->m_cItemType == DEF_ITEMTYPE_CONSUME)
                    || (m_pItemList[m_cItemOrder[i]]->m_cItemType == DEF_ITEMTYPE_ARROW))
                {
                    DisplayCommaNumber_G_cTxt((int)m_pItemList[m_cItemOrder[i]]->m_dwCount); // nbe show, as US: 1,200,000
                    PutString2(sX + 29 + m_pItemList[m_cItemOrder[i]]->m_sX + 10, sY + 41 + m_pItemList[m_cItemOrder[i]]->m_sY + 10
                        , G_cTxt, 200, 200, 200);
                }
            }
        }
    if ((msX >= sX + 23) && (msX <= sX + 76) && (msY >= sY + 172) && (msY <= sY + 184))
    {
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 23, sY + 172, 1);
    }
    if ((msX >= sX + 140) && (msX <= sX + 212) && (msY >= sY + 172) && (msY <= sY + 184))
    {
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_INVENTORY, sX + 140, sY + 172, 2);
    }
}


void CGame::DrawDialogBox_Map()
{
    short sX, sY;
    uint64_t dwTime = m_dwCurTime;
    double dV1, dV2, dV3;
    int    tX, tY, szX, szY, dX, dY;

    sX = m_stDialogBoxInfo[22].sX;
    sY = m_stDialogBoxInfo[22].sY;

    szX = 0;
    szY = 0;

    switch (m_stDialogBoxInfo[22].sV1)
    {
        case 1:
            switch (m_stDialogBoxInfo[22].sV2)
            {
                case 0: // aresden
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutTransSprite2(sX, sY, 0, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutSpriteFast(sX, sY, 0, dwTime);
                    dX = 19;
                    dY = 20;
                    szX = 260;
                    szY = 260;
                    break;

                case 1: // elvine
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutTransSprite2(sX, sY, 1, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1]->PutSpriteFast(sX, sY, 1, dwTime);
                    dX = 20;
                    dY = 18;
                    szX = 260;
                    szY = 260;
                    break;

                case 2: // middleland
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutTransSprite2(sX, sY, 0, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutSpriteFast(sX, sY, 0, dwTime);
                    dX = 11;
                    dY = 31;
                    szX = 280;
                    szY = 253;
                    break;

                case 3: // default
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutTransSprite2(sX, sY, 1, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2]->PutSpriteFast(sX, sY, 1, dwTime);
                    dX = 52;
                    dY = 42;
                    szX = 200;
                    szY = 200;
                    break;

                case 4: // aresden ¸
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutTransSprite2(sX, sY, 0, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutSpriteFast(sX, sY, 0, dwTime);
                    dX = 40;
                    dY = 40;
                    szX = 220;
                    szY = 220;
                    break;

                case 5: // elvine ¸
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutTransSprite2(sX, sY, 1, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3]->PutSpriteFast(sX, sY, 1, dwTime);
                    dX = 40;
                    dY = 40;
                    szX = 220;
                    szY = 220;
                    break;

                case 6: // aresden
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutTransSprite2(sX, sY, 0, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutSpriteFast(sX, sY, 0, dwTime);
                    dX = 40;
                    dY = 40;
                    szX = 220;
                    szY = 220;
                    break;

                case 7: // elvine
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutTransSprite2(sX, sY, 1, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4]->PutSpriteFast(sX, sY, 1, dwTime);
                    dX = 40;
                    dY = 40;
                    szX = 220;
                    szY = 220;
                    break;
                case 8: // aresden
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutTransSprite2(sX, sY, 0, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutSpriteFast(sX, sY, 0, dwTime);
                    dX = 40;
                    dY = 32;
                    szX = 220;
                    szY = 220;
                    break;

                case 9: // elvine
                    if (m_bDialogTrans)
                        m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutTransSprite2(sX, sY, 1, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5]->PutSpriteFast(sX, sY, 1, dwTime);
                    dX = 40;
                    dY = 38;
                    szX = 220;
                    szY = 220;
                    break;

            }

            dV1 = (double)m_pMapData->m_sMapSizeX;
            dV2 = (double)m_sPlayerX;
            dV3 = (dV2 * (double)szX) / dV1;
            tX = (int)dV3 + dX;

            dV1 = (double)m_pMapData->m_sMapSizeY;
            if (dV1 == 752) dV1 = 680;
            dV2 = (double)m_sPlayerY;
            dV3 = (dV2 * (double)szY) / dV1;
            tY = (int)dV3 + dY;


            //m_pSprite[DEF_SPRID_INTERFACE_MAPS1]->PutSpriteFast(sX +tX, sY +tY, 4, dwTime);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX + tX, sY + tY, 43);
            wsprintfA(G_cTxt, "%d,%d", m_sPlayerX, m_sPlayerY);
            PutString_SprFont3(sX + 10 + tX - 5, sY + 10 + tY - 6, G_cTxt, m_wR[13] * 4, m_wG[13] * 4, m_wB[13] * 4, false, 2);
            break;
    }
}


void CGame::DrawDialogBox_Bank(short msX, short msY, short msZ, char cLB)
{
    short sX, sY, szX;
    int  i, iTotalLines, iPointerLoc, iLoc;
    double d1, d2, d3;
    char cItemColor, cStr1[64], cStr2[64], cStr3[64];
    bool bFlag = false;

    sX = m_stDialogBoxInfo[14].sX;
    sY = m_stDialogBoxInfo[14].sY;
    szX = m_stDialogBoxInfo[14].sSizeX - 5;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 21);
    ZeroMemory(cStr1, sizeof(cStr1));
    ZeroMemory(cStr2, sizeof(cStr2));
    ZeroMemory(cStr3, sizeof(cStr3));
    iLoc = 45;

    switch (m_stDialogBoxInfo[14].cMode)
    {
        case -1:
            PutString(sX + 30 + 15, sY + 70, DRAW_DIALOGBOX_BANK1, Color(0, 0, 0));//"
            PutString(sX + 30 + 15, sY + 85, DRAW_DIALOGBOX_BANK2, Color(0, 0, 0));//"
            break;

        case 0:
            for (i = 0; i < m_stDialogBoxInfo[14].sV1; i++)
                if ((m_pBankList[i + m_stDialogBoxInfo[14].sView] != 0) && ((i + m_stDialogBoxInfo[14].sView) < DEF_MAXBANKITEMS))
                {
                    GetItemName(m_pBankList[i + m_stDialogBoxInfo[14].sView], cStr1, cStr2, cStr3);
                    if ((msX > sX + 30) && (msX < sX + 210) && (msY >= sY + 110 + i * 15) && (msY <= sY + 124 + i * 15))
                    {
                        bFlag = true;

                        PutAlignedString(sX, sX + szX, sY + 110 + i * 15, cStr1, 255, 255, 255);
                        if (m_bIsSpecial)
                            PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr1, 0, 255, 50);
                        else
                            PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr1, 255, 255, 255);

                        if (strlen(cStr2) > 0)
                        {
                            iLoc += 15;
                            PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr2, 150, 150, 150);
                        }
                        if (strlen(cStr3) > 0)
                        {
                            iLoc += 15;
                            PutAlignedString(sX + 70, sX + szX, sY + iLoc, cStr3, 150, 150, 150);
                        }
                        if (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sLevelLimit != 0 && m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_dwAttribute & 0x00000001)
                        {
                            iLoc += 15;
                            wsprintfA(G_cTxt, "%s: %d", DRAW_DIALOGBOX_SHOP24, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sLevelLimit);
                            PutAlignedString(sX + 70, sX + szX, sY + iLoc, G_cTxt, 150, 150, 150);
                        }

                        if ((m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cEquipPos != DEF_EQUIPPOS_NONE) && (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_wWeight >= 1100))
                        {
                            iLoc += 15;
                            int		_wWeight = 0;
                            if (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_wWeight % 100)				_wWeight = 1;
                            wsprintfA(G_cTxt, DRAW_DIALOGBOX_SHOP15, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_wWeight / 100 + _wWeight);

                            PutAlignedString(sX + 70, sX + szX, sY + iLoc, G_cTxt, 150, 150, 150);
                        }

                        cItemColor = m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cItemColor;
                        if (cItemColor == 0)
                        {
                            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSprite]->PutSpriteFast(sX + 60, sY + 68, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSpriteFrame, m_dwCurTime);
                        }
                        else
                        {
                            if ((m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                                || (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                                || (m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                            {
                                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSprite]->PutSpriteRGB(sX + 60, sY + 68, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSpriteFrame,
                                    m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
                            }
                            else m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSprite]->PutSpriteRGB(sX + 60, sY + 68, m_pBankList[i + m_stDialogBoxInfo[14].sView]->m_sSpriteFrame,
                                m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
                        }
                    }
                    else
                    {
                        if (m_bIsSpecial)
                            PutAlignedString(sX, sX + szX, sY + 110 + i * 15, cStr1, 0, 255, 50);
                        else
                            PutAlignedString(sX, sX + szX, sY + 110 + i * 15, cStr1, 0, 0, 0);
                    }
                }

            iTotalLines = 0;
            for (i = 0; i < DEF_MAXBANKITEMS; i++)
                if (m_pBankList[i] != 0) iTotalLines++;
            if (iTotalLines > m_stDialogBoxInfo[14].sV1)
            {
                d1 = (double)m_stDialogBoxInfo[14].sView;
                d2 = (double)(iTotalLines - m_stDialogBoxInfo[14].sV1);
                d3 = (274.0f * d1) / d2;
                iPointerLoc = (int)d3;
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 3);
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 242, sY + iPointerLoc + 35, 7);
            }
            else iPointerLoc = 0;
            if (cLB != 0 && (iGetTopDialogBoxIndex() == 14) && iTotalLines > m_stDialogBoxInfo[14].sV1)
            {
                if ((msX >= sX + 230) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320))
                {
                    d1 = (double)(msY - (sY + 35));
                    d2 = (double)(iTotalLines - m_stDialogBoxInfo[14].sV1);
                    d3 = (d1 * d2) / 274.0f;
                    m_stDialogBoxInfo[14].sView = (int)(d3 + 0.5);
                }
                else if ((msX >= sX + 230) && (msX <= sX + 260) && (msY > sY + 10) && (msY < sY + 40)) m_stDialogBoxInfo[14].sView = 0;
            }
            else m_stDialogBoxInfo[14].bIsScrollSelected = false;
            if (iGetTopDialogBoxIndex() == 14 && msZ != 0)
            {
                if (iTotalLines > 50) m_stDialogBoxInfo[14].sView = m_stDialogBoxInfo[14].sView - msZ / 30;
                else
                {//
                    if (msZ > 0) m_stDialogBoxInfo[14].sView--;
                    if (msZ < 0) m_stDialogBoxInfo[14].sView++;
                }
                m_stMCursor.sZ = 0;
            }
            if (iTotalLines > m_stDialogBoxInfo[14].sV1 && m_stDialogBoxInfo[14].sView > iTotalLines - m_stDialogBoxInfo[14].sV1) m_stDialogBoxInfo[14].sView = iTotalLines - m_stDialogBoxInfo[14].sV1;
            if (iTotalLines <= m_stDialogBoxInfo[14].sV1) m_stDialogBoxInfo[14].sView = 0;
            if (m_stDialogBoxInfo[14].sView < 0) m_stDialogBoxInfo[14].sView = 0;
            if (bFlag == false)
            {
                PutAlignedString(sX, sX + szX, sY + 45, DRAW_DIALOGBOX_BANK3);
                PutAlignedString(sX, sX + szX, sY + 60, DRAW_DIALOGBOX_BANK4);
                PutAlignedString(sX, sX + szX, sY + 75, DRAW_DIALOGBOX_BANK5);
            }
            break;
    }
}

void CGame::DrawDialogBox_FeedBackCard(short msX, short msY)
{
}

void CGame::DrawDialogBox_Character(short msX, short msY)
{
    short sX, sY, sSprH, sFrame;
    int i, iR, iG, iB, iSkirtDraw = 0;
    char cTxt2[120], cEquipPoiStatus[DEF_MAXITEMEQUIPPOS] = {};
    char  cItemColor, cCollison;

    sX = m_stDialogBoxInfo[1].sX;
    sY = m_stDialogBoxInfo[1].sY;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 0, false, m_bDialogTrans);

    ZeroMemory(G_cTxt, sizeof(G_cTxt));
    strcpy(G_cTxt, m_cPlayerName);
    strcat(G_cTxt, " : ");

    if (m_iPKCount > 0)
    {
        ZeroMemory(cTxt2, sizeof(cTxt2));
        wsprintfA(cTxt2, DRAW_DIALOGBOX_CHARACTER1, m_iPKCount);
        strcat(G_cTxt, cTxt2);
    }

    ZeroMemory(cTxt2, sizeof(cTxt2));
    wsprintfA(cTxt2, DRAW_DIALOGBOX_CHARACTER2, m_iContribution);
    strcat(G_cTxt, cTxt2);
    PutAlignedString(sX + 24, sX + 252, sY + 52, G_cTxt, 45, 20, 20);
    ZeroMemory(G_cTxt, sizeof(G_cTxt));

#ifdef DEF_EQUILIBRIUM_PROJECT // executor on F5 menu
    if (m_bCitizen == false)
    {
        if (m_bHunter)
            strcpy(G_cTxt, DRAW_DIALOGBOX_CHARACTER7); // "Traveller"
        else
        {
            strcpy(G_cTxt, "Executor");
            if (m_iGuildRank >= 0)
            {
                strcat(G_cTxt, "(");
                strcat(G_cTxt, m_cGuildName);
                if (m_iGuildRank == 0) strcat(G_cTxt, DEF_MSG_GUILDMASTER1);
                else strcat(G_cTxt, DEF_MSG_GUILDSMAN1); // " Guildsman)"
            }
        }
    }
    else
#else
    if (m_bCitizen == false)
    {
        strcpy(G_cTxt, DRAW_DIALOGBOX_CHARACTER7); // "Traveller"
    }
    else
#endif
    {
        if (m_bHunter)
        {
            if (m_bAresden)
                strcat(G_cTxt, DEF_MSG_ARECIVIL); //
            else strcat(G_cTxt, DEF_MSG_ELVCIVIL); // "Elvine Civilian"
        }
        else
        {
            if (m_bAresden)
                strcat(G_cTxt, DEF_MSG_ARESOLDIER); //
            else strcat(G_cTxt, DEF_MSG_ELVSOLDIER); //
        }
        if (m_iGuildRank >= 0)
        {
            strcat(G_cTxt, "(");
            strcat(G_cTxt, m_cGuildName);
            if (m_iGuildRank == 0) strcat(G_cTxt, DEF_MSG_GUILDMASTER1);
            else strcat(G_cTxt, DEF_MSG_GUILDSMAN1); // " Guildsman)"
        }
    }

    PutAlignedString(sX, sX + 275, sY + 69, G_cTxt, 45, 25, 25);

    int iTemp;
    // Level
    wsprintfA(G_cTxt, "%d", m_iLevel);
    PutAlignedString(sX + 180, sX + 250, sY + 106, G_cTxt, 45, 25, 25);
    // Exp
    wsprintfA(G_cTxt, "%d", m_iExp);
    PutAlignedString(sX + 180, sX + 250, sY + 125, G_cTxt, 45, 25, 25);
    // Next.Exp
    wsprintfA(G_cTxt, "%d", iGetLevelExp(m_iLevel + 1));
    PutAlignedString(sX + 180, sX + 250, sY + 142, G_cTxt, 45, 25, 25);

    // Hp
    iTemp = m_iHP;
#ifdef DEF_EQUILIBRIUM_PROJECT // HPs formula
    wsprintfA(G_cTxt, "%d/%d", iTemp, m_iVit * 3 + (m_iLevel * 3 + (m_iStr + m_iAngelicStr)) / 2);
#else
    wsprintfA(G_cTxt, "%d/%d", iTemp, m_iVit * 3 + m_iLevel * 2 + (m_iStr + m_iAngelicStr) / 2);
#endif
    PutAlignedString(sX + 180, sX + 250, sY + 173, G_cTxt, 45, 25, 25);

    // Mp
    iTemp = m_iMP;
    wsprintfA(G_cTxt, "%d/%d", iTemp, (m_iMag + m_iAngelicMag) * 2 + m_iLevel * 2 + (m_iInt + m_iAngelicInt) / 2);
    PutAlignedString(sX + 180, sX + 250, sY + 191, G_cTxt, 45, 25, 25);

    // Sp
    iTemp = m_iSP;
    wsprintfA(G_cTxt, "%d/%d", iTemp, m_iLevel * 2 + (m_iStr + m_iAngelicStr) * 2);
    PutAlignedString(sX + 180, sX + 250, sY + 208, G_cTxt, 45, 25, 25);

    // Max.Load
    wsprintfA(G_cTxt, "%d/%d", (_iCalcTotalWeight() / 100), ((m_iStr + m_iAngelicStr) * 5 + m_iLevel * 5));
    PutAlignedString(sX + 180, sX + 250, sY + 240, G_cTxt, 45, 25, 25);

    // Enemy Kills
    wsprintfA(G_cTxt, "%d", m_iEnemyKillCount);
    PutAlignedString(sX + 180, sX + 250, sY + 257, G_cTxt, 45, 25, 25);

    // Str
    if (m_iAngelicStr == 0)
    {
        wsprintfA(G_cTxt, "%d", m_iStr);
        PutAlignedString(sX + 48, sX + 82, sY + 285, G_cTxt, 45, 25, 25);
    }
    else
    {
        wsprintfA(G_cTxt, "%d", m_iStr + m_iAngelicStr);
        PutAlignedString(sX + 48, sX + 82, sY + 285, G_cTxt, 0, 0, 192);
    }

    // Vit
    wsprintfA(G_cTxt, "%d", m_iVit);
    PutAlignedString(sX + 218, sX + 251, sY + 285, G_cTxt, 45, 25, 25);

    // Dex
    if (m_iAngelicDex == 0)
    {
        wsprintfA(G_cTxt, "%d", m_iDex);
        PutAlignedString(sX + 48, sX + 82, sY + 302, G_cTxt, 45, 25, 25);
    }
    else
    {
        wsprintfA(G_cTxt, "%d", m_iDex + m_iAngelicDex);
        PutAlignedString(sX + 48, sX + 82, sY + 302, G_cTxt, 0, 0, 192);
    }

    // Int
    if (m_iAngelicInt == 0)
    {
        wsprintfA(G_cTxt, "%d", m_iInt);
        PutAlignedString(sX + 135, sX + 167, sY + 285, G_cTxt, 45, 25, 25);
    }
    else
    {
        wsprintfA(G_cTxt, "%d", m_iInt + m_iAngelicInt);
        PutAlignedString(sX + 135, sX + 167, sY + 285, G_cTxt, 0, 0, 192);
    }

    // Mag
    if (m_iAngelicMag == 0)
    {
        wsprintfA(G_cTxt, "%d", m_iMag);
        PutAlignedString(sX + 135, sX + 167, sY + 302, G_cTxt, 45, 25, 25);
    }
    else
    {
        wsprintfA(G_cTxt, "%d", m_iMag + m_iAngelicMag);
        PutAlignedString(sX + 135, sX + 167, sY + 302, G_cTxt, 0, 0, 192);
    }

    // Chr
    wsprintfA(G_cTxt, "%d", m_iCharisma);
    PutAlignedString(sX + 218, sX + 251, sY + 302, G_cTxt, 45, 25, 25);

    for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++)
        cEquipPoiStatus[i] = -1;

    for (i = 0; i < DEF_MAXITEMS; i++)
    {
        if ((m_pItemList[i] != 0) && (m_bIsItemEquipped[i] == true))	cEquipPoiStatus[m_pItemList[i]->m_cEquipPos] = i;
    }
    if ((m_sPlayerType >= 1) && (m_sPlayerType <= 3))
    {
        cCollison = -1;
        m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 0]->PutSpriteFast(sX + 171, sY + 290, m_sPlayerType - 1, m_dwCurTime);
        if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] == -1)
        {
            _GetHairColorColor(((m_sPlayerAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18]->PutSpriteRGB(sX + 171, sY + 290, (m_sPlayerAppr1 & 0x0F00) >> 8, iR, iG, iB, m_dwCurTime);
        }

        m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19]->PutSpriteFast(sX + 171, sY + 290, (m_sPlayerAppr1 & 0x000F), m_dwCurTime);

        if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_BACK]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 41, sY + 137, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 41, sY + 137, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 41, sY + 137, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 41, sY + 137, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 41, sY + 137, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_BACK;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_PANTS;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_ARMS;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_BOOTS;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_BODY]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_BODY;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_FULLBODY;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 90, sY + 170, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 90, sY + 170, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 90, sY + 170, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 90, sY + 170, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 90, sY + 170, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_LHAND;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 57, sY + 186, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 57, sY + 186, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 57, sY + 186, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 57, sY + 186, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_RHAND;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 57, sY + 186, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 57, sY + 186, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 57, sY + 186, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 57, sY + 186, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_TWOHAND;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_NECK]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 35, sY + 120, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 35, sY + 120, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 35, sY + 120, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 35, sY + 120, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_NECK;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 32, sY + 193, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 32, sY + 193, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 32, sY + 193, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 32, sY + 193, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_RFINGER;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 98, sY + 182, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 98, sY + 182, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 98, sY + 182, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 98, sY + 182, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_LFINGER;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteFast(sX + 72, sY + 135, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutSpriteRGB(sX + 72, sY + 135, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite2(sX + 72, sY + 135, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSpriteRGB(sX + 72, sY + 135, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 72, sY + 135, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_HEAD;
        }
        if (cCollison != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[cCollison]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[cCollison]]->m_sSpriteFrame;
            if (cCollison == DEF_EQUIPPOS_HEAD)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 72, sY + 135, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_RFINGER)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 32, sY + 193, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_LFINGER)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 98, sY + 182, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_NECK)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 35, sY + 120, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_TWOHAND)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 57, sY + 186, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_RHAND)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 57, sY + 186, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_LHAND)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 90, sY + 170, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_BODY)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_FULLBODY)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_BOOTS)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_ARMS)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_PANTS)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_BACK)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->PutTransSprite(sX + 41, sY + 137, sFrame, m_dwCurTime);
        }
    }
    else if ((m_sPlayerType >= 4) && (m_sPlayerType <= 6))
    {
        cCollison = -1;
        m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 40]->PutSpriteFast(sX + 171, sY + 290, m_sPlayerType - 4, m_dwCurTime);

        if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] == -1)
        {
            _GetHairColorColor(((m_sPlayerAppr1 & 0x00F0) >> 4), &iR, &iG, &iB);
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18 + 40]->PutSpriteRGB(sX + 171, sY + 290, (m_sPlayerAppr1 & 0x0F00) >> 8, iR, iG, iB, m_dwCurTime);
        }

        m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19 + 40]->PutSpriteFast(sX + 171, sY + 290, (m_sPlayerAppr1 & 0x000F), m_dwCurTime);

        if ((cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1))
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
            if ((sSprH == 12) && (sFrame == 0)) iSkirtDraw = 1;
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_BACK]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 45, sY + 143, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 45, sY + 143, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 45, sY + 143, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 45, sY + 143, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 45, sY + 143, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_BACK;
        }

        if ((cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) && (iSkirtDraw == 1))
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_BOOTS;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_PANTS;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_ARMS;
        }

        if ((cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1) && (iSkirtDraw == 0))
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_BOOTS;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_BODY]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_BODY;
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 171, sY + 290, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 171, sY + 290, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_FULLBODY;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 84, sY + 175, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 84, sY + 175, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 84, sY + 175, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 84, sY + 175, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 84, sY + 175, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_LHAND;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_cItemColor;
            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 60, sY + 191, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 60, sY + 191, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 60, sY + 191, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 60, sY + 191, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_RHAND;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_cItemColor;
            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 60, sY + 191, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 60, sY + 191, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 60, sY + 191, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 60, sY + 191, sFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_TWOHAND;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_NECK]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 35, sY + 120, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 35, sY + 120, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 35, sY + 120, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 35, sY + 120, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_NECK;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 32, sY + 193, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 32, sY + 193, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 32, sY + 193, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 32, sY + 193, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_RFINGER;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 98, sY + 182, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 98, sY + 182, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 98, sY + 182, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 98, sY + 182, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_LFINGER;
        }

        if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
            cItemColor = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_cItemColor;

            if (m_bIsItemDisabled[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]] == false)
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteFast(sX + 72, sY + 139, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutSpriteRGB(sX + 72, sY + 139, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            else
            {
                if (cItemColor == 0)
                    m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite2(sX + 72, sY + 139, sFrame, m_dwCurTime);
                else m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSpriteRGB(sX + 72, sY + 139, sFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], m_dwCurTime);
            }
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 72, sY + 139, sFrame, msX, msY))
                cCollison = DEF_EQUIPPOS_HEAD;
        }
        if (cCollison != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[cCollison]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[cCollison]]->m_sSpriteFrame;
            if (cCollison == DEF_EQUIPPOS_HEAD)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 72, sY + 139, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_RFINGER)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 32, sY + 193, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_LFINGER)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 98, sY + 182, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_NECK)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 35, sY + 120, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_TWOHAND)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 60, sY + 191, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_RHAND)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 60, sY + 191, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_LHAND)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 84, sY + 175, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_BODY)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_FULLBODY)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_BOOTS)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_ARMS)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_PANTS)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 171, sY + 290, sFrame, m_dwCurTime);
            else if (cCollison == DEF_EQUIPPOS_BACK)
                m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->PutTransSprite(sX + 45, sY + 143, sFrame, m_dwCurTime);
        }
    }

    // v2.05
    if ((msX >= sX + 15) && (msX <= sX + 15 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 15, sY + 340, 5, false, m_bDialogTrans);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 15, sY + 340, 4, false, m_bDialogTrans);

    if ((msX >= sX + 98) && (msX <= sX + 98 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 98, sY + 340, 45, false, m_bDialogTrans);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 98, sY + 340, 44, false, m_bDialogTrans);

    if ((msX >= sX + 180) && (msX <= sX + 180 + DEF_BTNSZX) && (msY >= sY + 340) && (msY <= sY + 340 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 180, sY + 340, 11, false, m_bDialogTrans);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 180, sY + 340, 10, false, m_bDialogTrans);
}


void CGame::DrawDialogBox_LevelUpSetting(short msX, short msY)
{
    short sX, sY, szX;
    uint64_t dwTime = m_dwCurTime;
    char cTxt[120];
    int iStats;
    sX = m_stDialogBoxInfo[12].sX;
    sY = m_stDialogBoxInfo[12].sY;
    szX = m_stDialogBoxInfo[12].sSizeX;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 2);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX + 16, sY + 100, 4);

    PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_LEVELUP_SETTING1);
    PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_LEVELUP_SETTING2);

    // Points Left - Display in green if > 0
    PutString(sX + 20, sY + 85, DRAW_DIALOGBOX_LEVELUP_SETTING3, Color(0, 0, 0));
    wsprintfA(cTxt, "%d", m_iLU_Point);
    if (m_iLU_Point > 0)
    {
        PutString(sX + 73, sY + 102, cTxt, Color(0, 255, 0));
    }
    else
    {
        PutString(sX + 73, sY + 102, cTxt, Color(0, 0, 0));
    }
    // Strength
    PutString(sX + 24, sY + 125, DRAW_DIALOGBOX_LEVELUP_SETTING4, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iStr);
    PutString(sX + 109, sY + 125, cTxt, Color(25, 35, 25));
    iStats = m_iStr + m_cLU_Str;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats != m_iStr)
    {
        PutString(sX + 162, sY + 125, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 125, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 127) && (msY <= sY + 133) && (m_iStr < DEF_MAX_STATS))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 127, 5, dwTime);
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133) && (m_cLU_Str > 0))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 127, 6, dwTime);

    // Vitality
    PutString(sX + 24, sY + 144, DRAW_DIALOGBOX_LEVELUP_SETTING5, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iVit);
    PutString(sX + 109, sY + 144, cTxt, Color(25, 35, 25));
    iStats = m_iVit + m_cLU_Vit;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats != m_iVit)
    {
        PutString(sX + 162, sY + 144, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 144, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 146) && (msY <= sY + 152) && (m_iVit < DEF_MAX_STATS))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 146, 5, dwTime);
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152) && (m_cLU_Vit > 0))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 146, 6, dwTime);

    // Dexterity
    PutString(sX + 24, sY + 163, DRAW_DIALOGBOX_LEVELUP_SETTING6, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iDex);
    PutString(sX + 109, sY + 163, cTxt, Color(25, 35, 25));
    iStats = m_iDex + m_cLU_Dex;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats != m_iDex)
    {
        PutString(sX + 162, sY + 163, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 163, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 165) && (msY <= sY + 171) && (m_iDex < DEF_MAX_STATS))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 165, 5, dwTime);
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171) && (m_cLU_Dex > 0))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 165, 6, dwTime);

    // Intelligence
    PutString(sX + 24, sY + 182, DRAW_DIALOGBOX_LEVELUP_SETTING7, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iInt);
    PutString(sX + 109, sY + 182, cTxt, Color(25, 35, 25));
    iStats = m_iInt + m_cLU_Int;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats != m_iInt)
    {
        PutString(sX + 162, sY + 182, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 182, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 184) && (msY <= sY + 190) && (m_iInt < DEF_MAX_STATS))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 184, 5, dwTime);
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190) && (m_cLU_Int > 0))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 184, 6, dwTime);

    // Magic
    PutString(sX + 24, sY + 201, DRAW_DIALOGBOX_LEVELUP_SETTING8, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iMag);
    PutString(sX + 109, sY + 201, cTxt, Color(25, 35, 25));
    iStats = m_iMag + m_cLU_Mag;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats != m_iMag)
    {
        PutString(sX + 162, sY + 201, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 201, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 203) && (msY <= sY + 209) && (m_iMag < DEF_MAX_STATS))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 203, 5, dwTime);
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209) && (m_cLU_Mag > 0))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 203, 6, dwTime);

    // Charisma
    PutString(sX + 24, sY + 220, DRAW_DIALOGBOX_LEVELUP_SETTING9, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iCharisma);
    PutString(sX + 109, sY + 220, cTxt, Color(25, 35, 25));
    iStats = m_iCharisma + m_cLU_Char;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats != m_iCharisma)
    {
        PutString(sX + 162, sY + 220, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 220, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 195) && (msX <= sX + 205) && (msY >= sY + 222) && (msY <= sY + 228) && (m_iCharisma < DEF_MAX_STATS))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 195, sY + 222, 5, dwTime);
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228) && (m_cLU_Char > 0))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 222, 6, dwTime);

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
    if ((m_cLU_Str == 0) && (m_cLU_Vit == 0) && (m_cLU_Dex == 0) && (m_cLU_Int == 0) && (m_cLU_Mag == 0) && (m_cLU_Char == 0))
    {
        if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        {
            if (m_iLU_Point <= 0) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 21);
        }
        else
        {
            if (m_iLU_Point <= 0) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 20);
        }
    }
}

void CGame::DrawDialogBox_CityHallMenu(short msX, short msY)
{
    short sX, sY, szX;
    char cTxt[120];

    sX = m_stDialogBoxInfo[13].sX;
    sY = m_stDialogBoxInfo[13].sY;
    szX = m_stDialogBoxInfo[13].sSizeX;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 18);//CityHall Menu Text

    switch (m_stDialogBoxInfo[13].cMode)
    {
        case 0:
            // citizenship req
            if (m_bCitizen == false)
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
                    PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 255, 255, 255);	//"
                else PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 4, 0, 50);		//"
            }
            else    PutAlignedString(sX, sX + szX, sY + 70, DRAW_DIALOGBOX_CITYHALL_MENU1, 65, 65, 65);			//"

            if (m_iRewardGold > 0)
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
                    PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 255, 255, 255);	//"
                else PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 4, 0, 50);		//"
            }
            else    PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU4, 65, 65, 65);			//"

            // 3.51 Cityhall Menu - Request Hero's Items
            if ((m_iEnemyKillCount >= 100) && (m_iContribution >= 10))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
                    PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 255, 255, 255);
                else PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 4, 0, 50);
            }
            else    PutAlignedString(sX, sX + szX, sY + 120, DRAW_DIALOGBOX_CITYHALL_MENU8, 65, 65, 65);

            // Cancel quest
            if (m_stQuest.sQuestType != 0)
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170))
                    PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 255, 255, 255);//"
                else PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 4, 0, 50);//"
            }
            else    PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_CITYHALL_MENU11, 65, 65, 65);//"

            // change playmode
            if ((m_bIsCrusadeMode == false) && m_bCitizen && (m_iPKCount == 0))
            {
                if (m_bHunter == true)
                {
                    if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
                        PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 255, 255, 255);
                    else
                        PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 4, 0, 50);
                }
                else if (m_iLevel < 100)
                {
                    if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
                        PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 255, 255, 255);
                    else
                        PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 4, 0, 50);
                }
                else // Disable...
                    PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 65, 65, 65);
            }
            else       PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU56, 65, 65, 65);

            // Teleport menu
#ifdef DEF_EQUILIBRIUM_PROJECT // TP for all
            if (m_bIsCrusadeMode == false)
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
                    PutAlignedString(sX, sX + szX, sY + 195, "Direct teleporting service", 255, 255, 255);
                else PutAlignedString(sX, sX + szX, sY + 195, "Direct teleporting service", 4, 0, 50);
            }
            else    PutAlignedString(sX, sX + szX, sY + 195, "Direct teleporting service", 65, 65, 65);
#else
            if ((m_bIsCrusadeMode == false) && m_bCitizen && (m_iPKCount == 0))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
                    PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 255, 255, 255);//"Teleporting to dungeon level 2."
                else PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 4, 0, 50);
            }
            else    PutAlignedString(sX, sX + szX, sY + 195, DRAW_DIALOGBOX_CITYHALL_MENU69, 65, 65, 65);
#endif

            //Change crusade role
            if (m_bIsCrusadeMode && m_bCitizen)
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 220) && (msY < sY + 220))
                    PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 255, 255, 255);//"Change the crusade assignment."
                else PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 4, 0, 50);//"
            }
            else    PutAlignedString(sX, sX + szX, sY + 220, DRAW_DIALOGBOX_CITYHALL_MENU14, 65, 65, 65);//"

            PutAlignedString(sX, sX + szX, sY + 270, DRAW_DIALOGBOX_CITYHALL_MENU17);//"Select an Item you want."

            break;

        case 1: // become citizen warning
            PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU18, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU19, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_CITYHALL_MENU20, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU21, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU22, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU23, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_CITYHALL_MENU24, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 200, DRAW_DIALOGBOX_CITYHALL_MENU25, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU26, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 230, DRAW_DIALOGBOX_CITYHALL_MENU27, 55, 25, 25);//"

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
            break;

        case 2: // Offering Citizenship.
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU28, 55, 25, 25);//"
            break;

        case 3: //Congratulations!! You acquired Citizenship"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU29, 55, 25, 25);//"

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 4: //Failed on acquiring citizenship!"
            PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU30, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 100, DRAW_DIALOGBOX_CITYHALL_MENU31, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 115, DRAW_DIALOGBOX_CITYHALL_MENU32, 55, 25, 25);//"

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 5: //The prize gold for your"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU33, 55, 25, 25);//"
            wsprintfA(cTxt, DRAW_DIALOGBOX_CITYHALL_MENU34, m_iRewardGold);//"
            PutAlignedString(sX, sX + szX, sY + 140, cTxt, 55, 25, 25);
            PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU35, 55, 25, 25);//"

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
            break;

        case 7:// 3.51 Cityhall Menu - Request Hero's Items
            PutAlignedString(sX, sX + szX, sY + 60, DRAW_DIALOGBOX_CITYHALL_MENU46, 255, 255, 255);// Here are the Hero's Item aivable :
            // Hero's Cape (EK 300)
            if (m_iEnemyKillCount >= 300)
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 110))
                    PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 255, 255, 255);// On mouse over Mode
                else PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 4, 0, 50);// Normal Mode
            }
            else PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU47, 65, 65, 65);// Disabled Mode
            // Hero's Helm (EK 150 - Contrib 20)
            if ((m_iEnemyKillCount >= 150) && (m_iContribution >= 20))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 125) && (msY < sY + 140))
                    PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 255, 255, 255);// On mouse over Mode
                else PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 4, 0, 50);// Normal Mode
            }
            else PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU48, 65, 65, 65);// Disabled Mode
            // Hero's Cap (EK 100 - Contrib 20)
            if ((m_iEnemyKillCount >= 100) && (m_iContribution >= 20))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 155) && (msY < sY + 170))
                    PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 255, 255, 255);// On mouse over Mode
                else PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 4, 0, 50);// Normal Mode
            }
            else PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU49, 65, 65, 65);// Disabled Mode
            // Hero's Armor (EK 300 - Contrib 30)
            if ((m_iEnemyKillCount >= 300) && (m_iContribution >= 30))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 185) && (msY < sY + 200))
                    PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 255, 255, 255);// On mouse over Mode
                else PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 4, 0, 50);// Normal Mode
            }
            else PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_CITYHALL_MENU50, 65, 65, 65);// Disabled Mode
            // Hero's Robe (EK 200 - Contrib 20)
            if ((m_iEnemyKillCount >= 200) && (m_iContribution >= 20))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 215) && (msY < sY + 230))
                    PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 255, 255, 255);// On mouse over Mode
                else PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 4, 0, 50);// Normal Mode
            }
            else PutAlignedString(sX, sX + szX, sY + 215, DRAW_DIALOGBOX_CITYHALL_MENU51, 65, 65, 65);// Disabled Mode
            // Hero's Hauberk (EK 100 - Contrib 10)
            if ((m_iEnemyKillCount >= 100) && (m_iContribution >= 10))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 245) && (msY < sY + 260))
                    PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 255, 255, 255);// On mouse over Mode
                else PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 4, 0, 50);// Normal Mode
            }
            else PutAlignedString(sX, sX + szX, sY + 245, DRAW_DIALOGBOX_CITYHALL_MENU52, 65, 65, 65);// Disabled Mode
            // Hero's Leggings (EK 150 - Contrib 15)
            if ((m_iEnemyKillCount >= 150) && (m_iContribution >= 15))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 275) && (msY < sY + 290))
                    PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 255, 255, 255);// On mouse over Mode
                else PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 4, 0, 50);// Normal Mode
            }
            else PutAlignedString(sX, sX + szX, sY + 275, DRAW_DIALOGBOX_CITYHALL_MENU53, 65, 65, 65);// Disabled Mode
            break;

        case 8: // cancel current quest?
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU54, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU55, 55, 25, 25);//"

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
            break;

        case 9: // You are civilian/ combatant now
            if (m_bHunter)
            {
                PutAlignedString(sX, sX + szX, sY + 53, DRAW_DIALOGBOX_CITYHALL_MENU57, 200, 200, 25);//"
            }
            else
            {
                PutAlignedString(sX, sX + szX, sY + 53, DRAW_DIALOGBOX_CITYHALL_MENU58, 200, 200, 25);//"
            }
            PutAlignedString(sX, sX + szX, sY + 78, DRAW_DIALOGBOX_CITYHALL_MENU59, 55, 25, 25);//"

            PutString(sX + 35, sY + 108, DRAW_DIALOGBOX_CITYHALL_MENU60, Color(220, 130, 45));//"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU61, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_CITYHALL_MENU62, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_CITYHALL_MENU63, 55, 25, 25);//"
            PutString(sX + 35, sY + 177, DRAW_DIALOGBOX_CITYHALL_MENU64, Color(220, 130, 45));//"
            PutAlignedString(sX, sX + szX, sY + 194, DRAW_DIALOGBOX_CITYHALL_MENU65, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 209, DRAW_DIALOGBOX_CITYHALL_MENU66, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 224, DRAW_DIALOGBOX_CITYHALL_MENU67, 55, 25, 25);//"

            PutAlignedString(sX, sX + szX, sY + 252, DRAW_DIALOGBOX_CITYHALL_MENU68, 55, 25, 25);//"
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
            break;

        case 10: // TP 2nd screen
            if (m_iTeleportMapCount > 0)

#ifdef DEF_EQUILIBRIUM_PROJECT
            {
                PutAlignedString(sX, sX + szX, sY + 50, "Direct teleporting service", 55, 25, 25);
                PutAlignedString(sX, sX + szX, sY + 80, "Possible destinations:", 55, 25, 25);
                PutAlignedString(sX, sX + szX, sY + 95, "(a fare may be required)", 55, 25, 25);
                PutAlignedString(sX, sX + szX, sY + 110, "Would you like to teleport?", 55, 25, 25);
#else
                {
                    PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_CITYHALL_MENU69, 55, 25, 25);//"Teleporting to dungeon level 2."
                    PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU70, 55, 25, 25);//"5000Gold is required"
                    PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU71, 55, 25, 25);//"to teleport to dungeon level 2."
                    PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_CITYHALL_MENU72, 55, 25, 25);//"Would you like to teleport?"
                    PutString2(sX + 35, sY + 250, DRAW_DIALOGBOX_CITYHALL_MENU72_1, 55, 25, 25);//"Civilians cannot go some area."
#endif
                    for (int i = 0; i < m_iTeleportMapCount; i++)
                    {
                        ZeroMemory(cTxt, sizeof(cTxt));
                        GetOfficialMapName(m_stTeleportList[i].mapname, cTxt);
                        wsprintfA(G_cTxt, DRAW_DIALOGBOX_CITYHALL_MENU77, cTxt, m_stTeleportList[i].iCost);
                        if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i * 15) && (msY <= sY + 144 + i * 15))
                            PutAlignedString(sX, sX + szX, sY + 130 + i * 15, G_cTxt, 255, 255, 255);
                        else PutAlignedString(sX, sX + szX, sY + 130 + i * 15, G_cTxt, 250, 250, 0);
                    }
                }
            else if (m_iTeleportMapCount == -1)
            {
                PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU73, 55, 25, 25);//"Now it's searching for possible area"
                PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_CITYHALL_MENU74, 55, 25, 25);//"to teleport."
                PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_CITYHALL_MENU75, 55, 25, 25);//"Please wait for a moment."
            }
            else
            {
                PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_CITYHALL_MENU76, 55, 25, 25);//"There is no area that you can teleport."
            }
            break;

        case 11: // ask for taking hero mantle
            PutAlignedString(sX, sX + szX - 1, sY + 125, m_cTakeHeroItemName, 55, 25, 25);
            PutAlignedString(sX + 1, sX + szX, sY + 125, m_cTakeHeroItemName, 55, 25, 25);
            PutAlignedString(sX, sX + szX, sY + 260, DRAW_DIALOGBOX_CITYHALL_MENU46A, 55, 25, 25); // would you like..
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX)
                && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX)
                && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
            break;
            }
    }

void CGame::DrawDialogBox_ConfirmExchange(short msX, short msY)
{
    short sX, sY;
    sX = m_stDialogBoxInfo[41].sX;
    sY = m_stDialogBoxInfo[41].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);
    switch (m_stDialogBoxInfo[41].cMode)
    {
        case 1: // Question
            PutString(sX + 35, sY + 30, "Do you really want to exchange?", Color(4, 0, 50));
            PutString(sX + 36, sY + 30, "Do you really want to exchange?", Color(4, 0, 50));

            if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55, 18);

            if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55, 2);
            break;

        case 2: // Waiting for response
            PutString(sX + 45, sY + 36, "Waiting for response...", Color(4, 0, 50));
            PutString(sX + 46, sY + 36, "Waiting for response...", Color(4, 0, 50));
            break;
    }
}

void CGame::DrawDialogBox_Exchange(short msX, short msY)
{
    short sX, sY, szX, sXadd;
    uint64_t dwTime = m_dwCurTime;
    char cItemColor, cTxt[120], cTxt2[128];
    char cNameStr[120], cSubStr1[120], cSubStr2[120];
    int iLoc, i;

    sX = m_stDialogBoxInfo[27].sX;
    sY = m_stDialogBoxInfo[27].sY;
    szX = m_stDialogBoxInfo[27].sSizeX;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_NEWEXCHANGE, sX, sY, 0);
    switch (m_stDialogBoxInfo[27].cMode)
    {
        case 1: // Not yet confirmed exchange
            PutAlignedString(sX + 80, sX + 180, sY + 38, m_cPlayerName, 35, 55, 35); // my name
            if (m_stDialogBoxExchangeInfo[4].sV1 != -1) // Other name if applicable
                PutAlignedString(sX + 250, sX + 540, sY + 38, m_stDialogBoxExchangeInfo[4].cStr2, 35, 55, 35);
            for (i = 0; i < 8; i++) // draw items
            {
                sXadd = (58 * i) + 48; if (i > 3) sXadd += 20;
                if (m_stDialogBoxExchangeInfo[i].sV1 != -1)
                {
                    cItemColor = m_stDialogBoxExchangeInfo[i].sV4;
                    if (cItemColor == 0)
                    {
                        m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteFast(sX + sXadd, sY + 130, m_stDialogBoxExchangeInfo[i].sV2, dwTime);
                    }
                    else
                    {
                        switch (m_stDialogBoxExchangeInfo[i].sV1)
                        {//sV1 : Sprite
                            case 1: //  Swds
                            case 2: //  Bows
                            case 3: //  Shields
                            case 15: // Axes hammers
                            case 17: // Wands
                                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(sX + sXadd, sY + 130
                                    , m_stDialogBoxExchangeInfo[i].sV2, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                                break;
                            default: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(sX + sXadd, sY + 130
                                , m_stDialogBoxExchangeInfo[i].sV2, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                                break;
                        }
                    }
                    GetItemName(m_stDialogBoxExchangeInfo[i].cStr1, m_stDialogBoxExchangeInfo[i].dwV1, cNameStr, cSubStr1, cSubStr2);
                    // If pointer over item then show this item data
                    if ((msX >= sX + sXadd - 6) && (msX <= sX + sXadd + 42)
                        && (msY >= sY + 61) && (msY <= sY + 200))
                    {
                        wsprintfA(cTxt, "%s", cNameStr);
                        if (m_bIsSpecial)
                        {
                            PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 0, 255, 50);
                            PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 0, 255, 50);
                        }
                        else
                        {
                            PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 35, 35, 35);
                            PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 35, 35, 35);
                        }
                        iLoc = 0;
                        if (strlen(cSubStr1) != 0)
                        {
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cSubStr1, 0, 0, 0);
                            iLoc += 15;
                        }
                        if (strlen(cSubStr2) != 0)
                        {
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cSubStr2, 0, 0, 0);
                            iLoc += 15;
                        }
                        if (m_stDialogBoxExchangeInfo[i].sV3 != 1) // Item avec Quantity
                        {
                            if (m_stDialogBoxExchangeInfo[i].sV3 > 1)
                            {
                                DisplayCommaNumber_G_cTxt(m_stDialogBoxExchangeInfo[i].sV3);
                                strcpy(cTxt2, G_cTxt);
                            }
                            else wsprintfA(cTxt2, DRAW_DIALOGBOX_EXCHANGE2, m_stDialogBoxExchangeInfo[i].sV3);
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt2, 35, 35, 35);
                            iLoc += 15;
                        }
                        if (m_stDialogBoxExchangeInfo[i].sV5 != -1) // completion
                        {	// Crafting Magins completion fix
                            if (m_stDialogBoxExchangeInfo[i].sV1 == 22)
                            {
                                if ((m_stDialogBoxExchangeInfo[i].sV2 > 5)
                                    && (m_stDialogBoxExchangeInfo[i].sV2 < 10))
                                {
                                    wsprintfA(cTxt, GET_ITEM_NAME2, (m_stDialogBoxExchangeInfo[i].sV7 - 100)); //Completion - 100
                                }
                            }
                            else if (m_stDialogBoxExchangeInfo[i].sV1 == 6)
                            {
                                wsprintfA(cTxt, GET_ITEM_NAME1, (m_stDialogBoxExchangeInfo[i].sV7 - 100)); //Purity
                            }
                            else
                            {
                                wsprintfA(cTxt, GET_ITEM_NAME2, m_stDialogBoxExchangeInfo[i].sV7); //Completion
                            }
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt, 35, 35, 35);
                            iLoc += 15;
                        }
                        if (iLoc < 45) // Endurance
                        {
                            wsprintfA(cTxt, DRAW_DIALOGBOX_EXCHANGE3, m_stDialogBoxExchangeInfo[i].sV5, m_stDialogBoxExchangeInfo[i].sV6);
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt, 35, 35, 35);
                            iLoc += 15;
                        }
                    }
                }
            }
            if ((m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_stDialogBoxExchangeInfo[4].sV1 == -1))
            {
                PutAlignedString(sX, sX + szX, sY + 235 + 10, DRAW_DIALOGBOX_EXCHANGE9, 55, 25, 25); // Please wait until other player decides
                PutAlignedString(sX, sX + szX, sY + 250 + 10, DRAW_DIALOGBOX_EXCHANGE10, 55, 25, 25);// to exchange. If you want to cancel the
                PutAlignedString(sX, sX + szX, sY + 265 + 10, DRAW_DIALOGBOX_EXCHANGE11, 55, 25, 25);// exchange press the CANCEL button now.
                PutString_SprFont(sX + 220, sY + 310, "Exchange", 15, 15, 15);
            }
            else if ((m_stDialogBoxExchangeInfo[0].sV1 == -1) && (m_stDialogBoxExchangeInfo[4].sV1 != -1))
            {
                PutAlignedString(sX, sX + szX, sY + 205 + 10, DRAW_DIALOGBOX_EXCHANGE12, 55, 25, 25);// Other player offered an item exchange
                PutAlignedString(sX, sX + szX, sY + 220 + 10, DRAW_DIALOGBOX_EXCHANGE13, 55, 25, 25);// Select an item which you want to exc-
                PutAlignedString(sX, sX + szX, sY + 235 + 10, DRAW_DIALOGBOX_EXCHANGE14, 55, 25, 25);// hange with above item, drag it to the
                PutAlignedString(sX, sX + szX, sY + 250 + 10, DRAW_DIALOGBOX_EXCHANGE15, 55, 25, 25);// blank and press the EXCHANGE button.
                PutAlignedString(sX, sX + szX, sY + 265 + 10, DRAW_DIALOGBOX_EXCHANGE16, 55, 25, 25);// And you can also reject an offer by
                PutAlignedString(sX, sX + szX, sY + 280 + 10, DRAW_DIALOGBOX_EXCHANGE17, 55, 25, 25);// pressing the CANCEL button.
                PutString_SprFont(sX + 220, sY + 310, "Exchange", 15, 15, 15);
            }
            else if ((m_stDialogBoxExchangeInfo[0].sV1 != -1) && (m_stDialogBoxExchangeInfo[4].sV1 != -1))
            {
                PutAlignedString(sX, sX + szX, sY + 205 + 10, DRAW_DIALOGBOX_EXCHANGE18, 55, 25, 25);// The preparation for item exchange
                PutAlignedString(sX, sX + szX, sY + 220 + 10, DRAW_DIALOGBOX_EXCHANGE19, 55, 25, 25);// has been finished. Press the EXCHANGE
                PutAlignedString(sX, sX + szX, sY + 235 + 10, DRAW_DIALOGBOX_EXCHANGE20, 55, 25, 25);// button to exchange as above. Press the
                PutAlignedString(sX, sX + szX, sY + 250 + 10, DRAW_DIALOGBOX_EXCHANGE21, 55, 25, 25);// CANCEL button to cancel. Occasionally
                PutAlignedString(sX, sX + szX, sY + 265 + 10, DRAW_DIALOGBOX_EXCHANGE22, 55, 25, 25);// when you press the EXCHANGE button, you
                PutAlignedString(sX, sX + szX, sY + 280 + 10, DRAW_DIALOGBOX_EXCHANGE23, 55, 25, 25);// will not be able to cancel the exchange.
                if ((msX >= sX + 200) && (msX <= sX + 200 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY))
                    PutString_SprFont(sX + 220, sY + 310, "Exchange", 6, 6, 20);
                else PutString_SprFont(sX + 220, sY + 310, "Exchange", 0, 0, 7);
            }
            if ((msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY)
                && (m_bIsDialogEnabled[41] == false))
                PutString_SprFont(sX + 450, sY + 310, "Cancel", 6, 6, 20);
            else PutString_SprFont(sX + 450, sY + 310, "Cancel", 0, 0, 7);
            break;

        case 2: // You have confirmed the exchange
            PutAlignedString(sX + 80, sX + 180, sY + 38, m_cPlayerName, 35, 55, 35); // my name
            if (m_stDialogBoxExchangeInfo[4].sV1 != -1) // Other name if applicable
                PutAlignedString(sX + 250, sX + 540, sY + 38, m_stDialogBoxExchangeInfo[4].cStr2, 35, 55, 35);
            for (i = 0; i < 8; i++) // draw items
            {
                sXadd = (58 * i) + 48; if (i > 3) sXadd += 20;
                if (m_stDialogBoxExchangeInfo[i].sV1 != -1)
                {
                    cItemColor = m_stDialogBoxExchangeInfo[i].sV4;
                    if (cItemColor == 0)
                    {
                        m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteFast(sX + sXadd, sY + 130, m_stDialogBoxExchangeInfo[i].sV2, dwTime);
                    }
                    else
                    {
                        switch (m_stDialogBoxExchangeInfo[i].sV1)
                        {
                            case 1: // Swds
                            case 2: // Bows
                            case 3: // Shields
                            case 15: // Axes hammers
                            case 17: // Wands
                                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(sX + sXadd, sY + 130
                                    , m_stDialogBoxExchangeInfo[i].sV2, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                                break;
                            default: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxExchangeInfo[i].sV1]->PutSpriteRGB(sX + sXadd, sY + 130
                                , m_stDialogBoxExchangeInfo[i].sV2, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                                break;
                        }
                    }
                    GetItemName(m_stDialogBoxExchangeInfo[i].cStr1, m_stDialogBoxExchangeInfo[i].dwV1, cNameStr, cSubStr1, cSubStr2);
                    // If pointer over item then show this item data
                    if ((msX >= sX + sXadd - 6) && (msX <= sX + sXadd + 42)
                        && (msY >= sY + 61) && (msY <= sY + 200))
                    {
                        wsprintfA(cTxt, "%s", cNameStr);
                        if (m_bIsSpecial)
                        {
                            PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 0, 255, 50);
                            PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 0, 255, 50);
                        }
                        else
                        {
                            PutAlignedString(sX + 15, sX + 155, sY + 215, cTxt, 35, 35, 35);
                            PutAlignedString(sX + 16, sX + 156, sY + 215, cTxt, 35, 35, 35);
                        }
                        iLoc = 0;
                        if (strlen(cSubStr1) != 0)
                        {
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cSubStr1, 0, 0, 0);
                            iLoc += 15;
                        }
                        if (strlen(cSubStr2) != 0)
                        {
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cSubStr2, 0, 0, 0);
                            iLoc += 15;
                        }
                        if (m_stDialogBoxExchangeInfo[i].sV3 != 1) // Item avec Quantity
                        {
                            if (m_stDialogBoxExchangeInfo[i].sV3 > 1)
                            {
                                DisplayCommaNumber_G_cTxt(m_stDialogBoxExchangeInfo[i].sV3);
                                strcpy(cTxt2, G_cTxt);
                            }
                            else wsprintfA(cTxt2, DRAW_DIALOGBOX_EXCHANGE2, m_stDialogBoxExchangeInfo[i].sV3);
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt2, 35, 35, 35);
                            iLoc += 15;
                        }
                        if (m_stDialogBoxExchangeInfo[i].sV5 != -1) // completion
                        {	// Crafting Magins completion fix
                            if (m_stDialogBoxExchangeInfo[i].sV1 == 22)
                            {
                                if ((m_stDialogBoxExchangeInfo[i].sV2 > 5)
                                    && (m_stDialogBoxExchangeInfo[i].sV2 < 10))
                                {
                                    wsprintfA(cTxt, GET_ITEM_NAME2, (m_stDialogBoxExchangeInfo[i].sV7 - 100)); //Completion - 100
                                }
                            }
                            else if (m_stDialogBoxExchangeInfo[i].sV1 == 6)
                            {
                                wsprintfA(cTxt, GET_ITEM_NAME1, (m_stDialogBoxExchangeInfo[i].sV7 - 100)); //Purity
                            }
                            else
                            {
                                wsprintfA(cTxt, GET_ITEM_NAME2, m_stDialogBoxExchangeInfo[i].sV7); //Completion
                            }
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt, 35, 35, 35);
                            iLoc += 15;
                        }
                        if (iLoc < 45) // Endurance
                        {
                            wsprintfA(cTxt, DRAW_DIALOGBOX_EXCHANGE3, m_stDialogBoxExchangeInfo[i].sV5, m_stDialogBoxExchangeInfo[i].sV6);
                            PutAlignedString(sX + 16, sX + 155, sY + 235 + iLoc, cTxt, 35, 35, 35);
                            iLoc += 15;
                        }
                    }
                }
            }
            wsprintfA(cTxt, DRAW_DIALOGBOX_EXCHANGE33, m_stDialogBoxExchangeInfo[4].cStr2);
            PutAlignedString(sX, sX + szX, sY + 205 + 10, cTxt, 55, 25, 25);                     // Please wait until %s agrees to
            PutAlignedString(sX, sX + szX, sY + 220 + 10, DRAW_DIALOGBOX_EXCHANGE34, 55, 25, 25);// exchange. The exchange can't be achieved
            PutAlignedString(sX, sX + szX, sY + 235 + 10, DRAW_DIALOGBOX_EXCHANGE35, 55, 25, 25);// unless both people agree.
            PutAlignedString(sX, sX + szX, sY + 250 + 10, DRAW_DIALOGBOX_EXCHANGE36, 55, 25, 25);//  If other player does not decide to exchange
            PutAlignedString(sX, sX + szX, sY + 265 + 10, DRAW_DIALOGBOX_EXCHANGE37, 55, 25, 25);// you can cancel the exchange by pressing the
            PutAlignedString(sX, sX + szX, sY + 280 + 10, DRAW_DIALOGBOX_EXCHANGE38, 55, 25, 25);// CANCEL button. But if other player already
            PutAlignedString(sX, sX + szX, sY + 295 + 10, DRAW_DIALOGBOX_EXCHANGE39, 55, 25, 25);// decided to exchange, you can't cancel anymore

            /*	if ( (msX >= sX + 450) && (msX <= sX + 450 + DEF_BTNSZX) && (msY >= sY + 310) && (msY <= sY + 310 + DEF_BTNSZY) )
                     PutString_SprFont(sX + 450, sY + 310, "Cancel", 6,6,20);
                else PutString_SprFont(sX + 450, sY + 310, "Cancel", 0,0,7);*/
            break;
    }
}

void CGame::DrawDialogBox_Fishing(short msX, short msY)
{

    short sX, sY;
    uint64_t dwTime = m_dwCurTime;
    char  cTxt[120];

    sX = m_stDialogBoxInfo[24].sX;
    sY = m_stDialogBoxInfo[24].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_stDialogBoxInfo[24].cStr, 0, cStr1, cStr2, cStr3);

    switch (m_stDialogBoxInfo[24].cMode)
    {
        case 0:
            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_stDialogBoxInfo[24].sV3]->PutSpriteFast(sX + 18 + 35, sY + 18 + 17, m_stDialogBoxInfo[24].sV4, dwTime);
            wsprintfA(cTxt, "%s", cStr1);
            PutString(sX + 98, sY + 14, cTxt, Color(255, 255, 255));
            wsprintfA(cTxt, DRAW_DIALOGBOX_FISHING1, m_stDialogBoxInfo[24].sV2);
            PutString(sX + 98, sY + 28, cTxt, Color(0, 0, 0));
            PutString(sX + 97, sY + 43, DRAW_DIALOGBOX_FISHING2, Color(0, 0, 0));
            wsprintfA(cTxt, "%d %%", m_stDialogBoxInfo[24].sV1);
            PutString_SprFont(sX + 157, sY + 40, cTxt, 10, 0, 0);
            if ((msX >= sX + 160) && (msX <= sX + 253) && (msY >= sY + 70) && (msY <= sY + 90))
                PutString_SprFont(sX + 160, sY + 70, "Try Now!", 6, 6, 20);
            else PutString_SprFont(sX + 160, sY + 70, "Try Now!", 0, 0, 7);
            break;
    }

}

void CGame::DrawDialogBox_GuildMenu(short msX, short msY)
{
    short sX, sY, szX;
    int iAdjX, iAdjY;

    sX = m_stDialogBoxInfo[7].sX;
    sY = m_stDialogBoxInfo[7].sY;
    szX = m_stDialogBoxInfo[7].sSizeX;

    iAdjX = -13;
    iAdjY = 30;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 19);

    switch (m_stDialogBoxInfo[7].cMode)
    {
        case 0:
            if ((m_iGuildRank == -1) && (m_iCharisma >= 20) && (m_iLevel >= 20))
            {
                if ((msX > sX + iAdjX + 80) && (msX < sX + iAdjX + 210) && (msY > sY + iAdjY + 63) && (msY < sY + iAdjY + 78))
                    PutAlignedString(sX, sX + szX, sY + iAdjY + 65, DRAW_DIALOGBOX_GUILDMENU1, 255, 255, 255);//"
                else PutAlignedString(sX, sX + szX, sY + iAdjY + 65, DRAW_DIALOGBOX_GUILDMENU1, 4, 0, 50);//"
            }
            else PutAlignedString(sX, sX + szX, sY + iAdjY + 65, DRAW_DIALOGBOX_GUILDMENU1, 65, 65, 65);//"

            if (m_iGuildRank == 0)
            {
                if ((msX > sX + iAdjX + 72) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 82) && (msY < sY + iAdjY + 99))
                    PutAlignedString(sX, sX + szX, sY + iAdjY + 85, DRAW_DIALOGBOX_GUILDMENU4, 255, 255, 255);//"
                else PutAlignedString(sX, sX + szX, sY + iAdjY + 85, DRAW_DIALOGBOX_GUILDMENU4, 4, 0, 50);//"
            }
            else PutAlignedString(sX, sX + szX, sY + iAdjY + 85, DRAW_DIALOGBOX_GUILDMENU4, 65, 65, 65);//"

            if ((msX > sX + iAdjX + 61) && (msX < sX + iAdjX + 226) && (msY > sY + iAdjY + 103) && (msY < sY + iAdjY + 120))
                PutAlignedString(sX, sX + szX, sY + iAdjY + 105, DRAW_DIALOGBOX_GUILDMENU7, 255, 255, 255);//"
            else PutAlignedString(sX, sX + szX, sY + iAdjY + 105, DRAW_DIALOGBOX_GUILDMENU7, 4, 0, 50);//"

            if ((msX > sX + iAdjX + 60) && (msX < sX + iAdjX + 227) && (msY > sY + iAdjY + 123) && (msY < sY + iAdjY + 139))
                PutAlignedString(sX, sX + szX, sY + iAdjY + 125, DRAW_DIALOGBOX_GUILDMENU9, 255, 255, 255);//"
            else PutAlignedString(sX, sX + szX, sY + iAdjY + 125, DRAW_DIALOGBOX_GUILDMENU9, 4, 0, 50);//"

            if (m_iGuildRank == 0 && m_iFightzoneNumber == 0)
            {
                if ((msX > sX + iAdjX + 72) && (msX < sX + iAdjX + 228) && (msY > sY + iAdjY + 143) && (msY < sY + iAdjY + 169))
                    PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU11, 255, 255, 255);//"
                else PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU11, 4, 0, 50);//"

            }
            else if (m_iGuildRank == 0 && m_iFightzoneNumber > 0)
            {
                if ((msX > sX + iAdjX + 72) && (msX < sX + iAdjX + 216) && (msY > sY + iAdjY + 143) && (msY < sY + iAdjY + 169))
                    PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU13, 255, 255, 255);//"
                else PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU13, 4, 0, 50);//"

            }
            else if (m_iFightzoneNumber < 0)
            {
                PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU13, 65, 65, 65);//"
            }
            else PutAlignedString(sX, sX + szX, sY + iAdjY + 145, DRAW_DIALOGBOX_GUILDMENU11, 65, 65, 65);//"

            PutAlignedString(sX, sX + szX, sY + iAdjY + 205, DRAW_DIALOGBOX_GUILDMENU17);//"
            break;

        case 1:
            PutAlignedString(sX + 24, sX + 239, sY + 125, DRAW_DIALOGBOX_GUILDMENU18, 55, 25, 25);//"
            PutString(sX + 75, sY + 144, "____________________", Color(25, 35, 25));

            if (iGetTopDialogBoxIndex() != 7)
                PutString(sX + 75, sY + 140, m_cGuildName, Color(255, 255, 255), 16, false, 2);

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
            {
                if ((strcmp(m_cGuildName, "NONE") == 0) || (strlen(m_cGuildName) == 0))
                {
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);//Create Gray Button
                }
                else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 25);//Create Highlight Button
            }
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);//Create Gray Button

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);//Red Cancel Button
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);//Gray Cancel Button
            break;

        case 2:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU19, 55, 25, 25);//"
            break;
        case 3:
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_GUILDMENU20, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 140, m_cGuildName, 55, 25, 25);
            PutAlignedString(sX, sX + szX, sY + 144, "____________________", 25, 35, 25);
            PutAlignedString(sX, sX + szX, sY + 160, DRAW_DIALOGBOX_GUILDMENU21, 55, 25, 25);//"

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
        case 4:
            PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU22, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU23, 55, 25, 25);//"

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
        case 5:
            PutAlignedString(sX, sX + szX, sY + 90, DRAW_DIALOGBOX_GUILDMENU24);
            PutAlignedString(sX, sX + szX, sY + 105, m_cGuildName, 35, 35, 35);
            PutAlignedString(sX, sX + szX, sY + 109, "____________________", 0, 0, 0);
            PutAlignedString(sX, sX + szX, sY + 130, DRAW_DIALOGBOX_GUILDMENU25);//"
            PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_GUILDMENU26);//"
            PutAlignedString(sX, sX + szX, sY + 160, DRAW_DIALOGBOX_GUILDMENU27);//"
            PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_GUILDMENU28, 55, 25, 25);//"

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
            break;
        case 6:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU29, 55, 25, 25);//"
            break;
        case 7:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU30, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
        case 8:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU31, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
        case 9:
            PutAlignedString(sX, sX + szX, sY + iAdjY + 60, DRAW_DIALOGBOX_GUILDMENU32);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 75, DRAW_DIALOGBOX_GUILDMENU33);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 90, DRAW_DIALOGBOX_GUILDMENU34);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 105, DRAW_DIALOGBOX_GUILDMENU35);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 130, DRAW_DIALOGBOX_GUILDMENU36);//"
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 31);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 30);
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;
        case 10:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU37, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
        case 11:
            PutAlignedString(sX, sX + szX, sY + iAdjY + 60, DRAW_DIALOGBOX_GUILDMENU38);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 75, DRAW_DIALOGBOX_GUILDMENU39);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 90, DRAW_DIALOGBOX_GUILDMENU40);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 105, DRAW_DIALOGBOX_GUILDMENU41);//
            PutAlignedString(sX, sX + szX, sY + iAdjY + 130, DRAW_DIALOGBOX_GUILDMENU42);//"
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 31);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 30);
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;
        case 12:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU43, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 13:
            PutAlignedString(sX, sX + szX, sY + iAdjY + 40, DRAW_DIALOGBOX_GUILDMENU44);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 55, DRAW_DIALOGBOX_GUILDMENU45);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 70, DRAW_DIALOGBOX_GUILDMENU46);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 85, DRAW_DIALOGBOX_GUILDMENU47);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 100, DRAW_DIALOGBOX_GUILDMENU48);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 115, DRAW_DIALOGBOX_GUILDMENU49);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 130, DRAW_DIALOGBOX_GUILDMENU50);//"

            if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 168) && (msY < sY + iAdjY + 185))
                PutString(sX + iAdjX + 65 + 25 - 23, sY + iAdjY + 170, DRAW_DIALOGBOX_GUILDMENU51, Color(255, 255, 255));
            else PutString(sX + iAdjX + 65 + 25 - 23, sY + iAdjY + 170, DRAW_DIALOGBOX_GUILDMENU51, Color(4, 0, 50));

            if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 168) && (msY < sY + iAdjY + 185))
                PutString(sX + iAdjX + 150 + 25 - 23, sY + iAdjY + 170, DRAW_DIALOGBOX_GUILDMENU53, Color(255, 255, 255));
            else PutString(sX + iAdjX + 150 + 25 - 23, sY + iAdjY + 170, DRAW_DIALOGBOX_GUILDMENU53, Color(4, 0, 50));

            if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 188) && (msY < sY + iAdjY + 205))
                PutString(sX + iAdjX + 65 + 25 - 23, sY + iAdjY + 190, DRAW_DIALOGBOX_GUILDMENU55, Color(255, 255, 255));
            else PutString(sX + iAdjX + 65 + 25 - 23, sY + iAdjY + 190, DRAW_DIALOGBOX_GUILDMENU55, Color(4, 0, 50));

            if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 188) && (msY < sY + iAdjY + 205))
                PutString(sX + iAdjX + 150 + 25 - 23, sY + iAdjY + 190, DRAW_DIALOGBOX_GUILDMENU57, Color(255, 255, 255));
            else PutString(sX + iAdjX + 150 + 25 - 23, sY + iAdjY + 190, DRAW_DIALOGBOX_GUILDMENU57, Color(4, 0, 50));

            if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 208) && (msY < sY + iAdjY + 225))
                PutString(sX + iAdjX + 65 + 25 - 23, sY + iAdjY + 210, DRAW_DIALOGBOX_GUILDMENU59, Color(255, 255, 255));
            else PutString(sX + iAdjX + 65 + 25 - 23, sY + iAdjY + 210, DRAW_DIALOGBOX_GUILDMENU59, Color(4, 0, 50));

            if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 208) && (msY < sY + iAdjY + 225))
                PutString(sX + iAdjX + 150 + 25 - 23, sY + iAdjY + 210, DRAW_DIALOGBOX_GUILDMENU61, Color(255, 255, 255));
            else PutString(sX + iAdjX + 150 + 25 - 23, sY + iAdjY + 210, DRAW_DIALOGBOX_GUILDMENU61, Color(4, 0, 50));

            if ((msX > sX + iAdjX + 65) && (msX < sX + iAdjX + 137) && (msY > sY + iAdjY + 228) && (msY < sY + iAdjY + 245))
                PutString(sX + iAdjX + 65 + 25 - 23, sY + iAdjY + 230, DRAW_DIALOGBOX_GUILDMENU63, Color(255, 255, 255));
            else PutString(sX + iAdjX + 65 + 25 - 23, sY + iAdjY + 230, DRAW_DIALOGBOX_GUILDMENU63, Color(4, 0, 50));

            if ((msX > sX + iAdjX + 150) && (msX < sX + iAdjX + 222) && (msY > sY + iAdjY + 228) && (msY < sY + iAdjY + 245))
                PutString(sX + iAdjX + 150 + 25 - 23, sY + iAdjY + 230, DRAW_DIALOGBOX_GUILDMENU65, Color(255, 255, 255));
            else PutString(sX + iAdjX + 150 + 25 - 23, sY + iAdjY + 230, DRAW_DIALOGBOX_GUILDMENU65, Color(4, 0, 50));

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 14:
            PutAlignedString(sX, sX + szX, sY + 130, DRAW_DIALOGBOX_GUILDMENU66, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 145, DRAW_DIALOGBOX_GUILDMENU67, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 160, DRAW_DIALOGBOX_GUILDMENU68, 55, 25, 25);//
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 15:
            PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU69, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU70, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 16:
            PutAlignedString(sX, sX + szX, sY + 135, DRAW_DIALOGBOX_GUILDMENU71, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_GUILDMENU72, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 17:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU73, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 18:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU74, 55, 25, 25);//"
            break;

        case 19:
            if (m_iFightzoneNumber > 0)
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_GETFIGHTZONETICKET, 0, 0, 0, 0, 0);
            m_stDialogBoxInfo[7].cMode = 0;
            break;

        case 20:
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_GUILDMENU75, 55, 25, 25);//"
            PutString(sX + 75, sY + 144, "____________________", Color(25, 35, 25));
            PutString(sX + 75, sY + 140, m_cGuildName, Color(255, 255, 255), false, 2);
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 25);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 24);
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 21:
            PutAlignedString(sX, sX + szX, sY + iAdjY + 95, DRAW_DIALOGBOX_GUILDMENU76, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 110, DRAW_DIALOGBOX_GUILDMENU77, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 135, DRAW_DIALOGBOX_GUILDMENU78, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 150, DRAW_DIALOGBOX_GUILDMENU79, 55, 25, 25);//"
            PutAlignedString(sX, sX + szX, sY + iAdjY + 165, DRAW_DIALOGBOX_GUILDMENU80, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 22:
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_GUILDMENU81, 55, 25, 25);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
    }
}

void CGame::DrawDialogBox_GuildOperation(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[8].sX;
    sY = m_stDialogBoxInfo[8].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 19);

    switch (m_stGuildOpList[0].cOpMode)
    {
        case 1:
            PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION1);
            PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35, 35, 35);
            PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
            PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION2);
            PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION3);
            PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION4);
            PutAlignedString(sX + 24, sX + 248, sY + 160, DRAW_DIALOGBOX_GUILD_OPERATION5, 55, 25, 25);

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 35);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 34);
            break;

        case 2:
            PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION6);
            PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35, 35, 35);
            PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
            PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION7);
            PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION8);
            PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION9);
            PutAlignedString(sX + 24, sX + 248, sY + 160, DRAW_DIALOGBOX_GUILD_OPERATION10, 55, 25, 25);

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 33);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 32);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 35);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 34);
            break;

        case 3:
            PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION11);
            PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35, 35, 35);
            PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
            PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION12);
            PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION13);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 4:
            PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION14);
            PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35, 35, 35);
            PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
            PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION15);
            PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION16);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 5:
            PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION17);
            PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35, 35, 35);
            PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
            PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION18);
            PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION19);
            PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION20);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 6:
            PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION21);
            PutAlignedString(sX + 24, sX + 248, sY + 65, m_stGuildOpList[0].cName, 35, 35, 35);
            PutAlignedString(sX + 24, sX + 248, sY + 69, "____________________", 0, 0, 0);
            PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION22);
            PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION23);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 7:
            PutAlignedString(sX + 24, sX + 248, sY + 50, DRAW_DIALOGBOX_GUILD_OPERATION24);
            //PutString(sX + 60, sY + 65, m_stGuildOpList[0].cName, Color(35,35,35));
            //PutString(sX + 60, sY + 69, "____________________", Color(0,0,0));
            PutAlignedString(sX + 24, sX + 248, sY + 90, DRAW_DIALOGBOX_GUILD_OPERATION25);
            PutAlignedString(sX + 24, sX + 248, sY + 105, DRAW_DIALOGBOX_GUILD_OPERATION26);
            PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_GUILD_OPERATION27);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
    }
}

int  _tmp_iMCProb[] = { 0, 300, 250, 200, 150, 100, 80, 70, 60, 50, 40 };
int  _tmp_iMLevelPenalty[] = { 0,   5,   5,   8,   8,   10, 14, 28, 32, 36, 40 };

void CGame::DrawDialogBox_Magic(short msX, short msY, short msZ)
{
    short sX, sY, sMagicCircle, sLevelMagic;
    int  iCPivot, i, iYloc, iResult, iManaCost;
    char cTxt[120], cMana[10];
    uint64_t dwTime = m_dwCurTime;
    double dV1, dV2, dV3, dV4;

    sX = m_stDialogBoxInfo[3].sX;
    sY = m_stDialogBoxInfo[3].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 1, false, m_bDialogTrans);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 7, false, m_bDialogTrans);

    if (iGetTopDialogBoxIndex() == 3 && msZ != 0)
    {
        if (msZ > 0) m_stDialogBoxInfo[3].sView--;
        if (msZ < 0) m_stDialogBoxInfo[3].sView++;
        m_stMCursor.sZ = 0;
    }
    if (m_stDialogBoxInfo[3].sView < 0) m_stDialogBoxInfo[3].sView = 9;
    if (m_stDialogBoxInfo[3].sView > 9) m_stDialogBoxInfo[3].sView = 0;

    //Circle
    ZeroMemory(cTxt, sizeof(cTxt));
    switch (m_stDialogBoxInfo[3].sView)
    {
        case 0: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC1);  break;//"Circle One"
        case 1: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC2);  break;//"Circle Two"
        case 2: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC3);  break;//"Circle Three"
        case 3: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC4);  break;//"Circle Four"
        case 4: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC5);  break;//"Circle Five"
        case 5: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC6);  break;//"Circle Six"
        case 6: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC7);  break;//"Circle Seven"
        case 7: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC8);  break;//"Circle Eight"
        case 8: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC9);  break;//"Circle Nine"
        case 9: strcpy(cTxt, DRAW_DIALOGBOX_MAGIC10); break;//"Circle Ten"
    }
    PutAlignedString(sX + 3, sX + 256, sY + 50, cTxt);
    PutAlignedString(sX + 4, sX + 257, sY + 50, cTxt);
    iCPivot = m_stDialogBoxInfo[3].sView * 10;
    iYloc = 0;

    for (i = 0; i < 9; i++)
    {
        if ((m_cMagicMastery[iCPivot + i] != 0) && (m_pMagicCfgList[iCPivot + i] != 0))
        {
            wsprintfA(cTxt, "%s", m_pMagicCfgList[iCPivot + i]->m_cName);

            m_Misc.ReplaceString(cTxt, '-', ' ');
            iManaCost = iGetManaCost(iCPivot + i);
            if (iManaCost > m_iMP)
            {
                if (m_Misc.bCheckIMEString(cTxt) == false)
                {
                    PutString(sX + 30, sY + 73 + iYloc, cTxt, Color(41, 16, 41));
                    PutString(sX + 31, sY + 73 + iYloc, cTxt, Color(41, 16, 41));
                }
                else PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 5, 5, 5);
                wsprintfA(cMana, "%3d", iManaCost);
                PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 5, 5, 5);
            }
            else
                if ((msX >= sX + 30) && (msX <= sX + 240) && (msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 14 + iYloc))
                {
                    if (m_Misc.bCheckIMEString(cTxt) == false)
                    {
                        PutString(sX + 30, sY + 73 + iYloc, cTxt, Color(255, 255, 255));
                        PutString(sX + 31, sY + 73 + iYloc, cTxt, Color(255, 255, 255));
                    }
                    else PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 250, 250, 250);
                    wsprintfA(cMana, "%3d", iManaCost);
                    PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 250, 250, 250);
                }
                else
                {
                    if (m_Misc.bCheckIMEString(cTxt) == false)
                    {
                        PutString(sX + 30, sY + 73 + iYloc, cTxt, Color(8, 0, 66));
                        PutString(sX + 31, sY + 73 + iYloc, cTxt, Color(8, 0, 66));
                    }
                    else PutString_SprFont(sX + 30, sY + 70 + iYloc, cTxt, 1, 1, 8);
                    wsprintfA(cMana, "%3d", iManaCost);
                    PutString_SprFont(sX + 206, sY + 70 + iYloc, cMana, 1, 1, 8);
                }

            iYloc += 18;
        }

    }

    if (iYloc == 0)
    {
        PutAlignedString(sX + 3, sX + 256, sY + 100, DRAW_DIALOGBOX_MAGIC11);//"
        PutAlignedString(sX + 3, sX + 256, sY + 115, DRAW_DIALOGBOX_MAGIC12);//"
        PutAlignedString(sX + 3, sX + 256, sY + 130, DRAW_DIALOGBOX_MAGIC13);//"
        PutAlignedString(sX + 3, sX + 256, sY + 145, DRAW_DIALOGBOX_MAGIC14);//"
        PutAlignedString(sX + 3, sX + 256, sY + 160, DRAW_DIALOGBOX_MAGIC15);//"
    }

    m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 30, sY + 250, 19, dwTime);

    switch (m_stDialogBoxInfo[3].sView)
    {
        case 0: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 30, sY + 250, 20, dwTime); break;
        case 1: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 43, sY + 250, 21, dwTime); break;
        case 2: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 61, sY + 250, 22, dwTime); break;
        case 3: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 86, sY + 250, 23, dwTime); break;
        case 4: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 106, sY + 250, 24, dwTime); break;
        case 5: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 121, sY + 250, 25, dwTime); break;
        case 6: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 142, sY + 250, 26, dwTime); break;
        case 7: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 169, sY + 250, 27, dwTime); break;
        case 8: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 202, sY + 250, 28, dwTime); break;
        case 9: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 222, sY + 250, 29, dwTime); break;
    }

    sMagicCircle = m_stDialogBoxInfo[3].sView + 1;
    if (m_cSkillMastery[4] == 0)
        dV1 = 1.0f;
    else dV1 = (double)m_cSkillMastery[4];
    dV2 = (double)(dV1 / 100.0f);
    dV3 = (double)_tmp_iMCProb[sMagicCircle];
    dV1 = dV2 * dV3;
    iResult = (int)dV1;
    if ((m_iInt + m_iAngelicInt) > 50) iResult += ((m_iInt + m_iAngelicInt) - 50) / 2;
    sLevelMagic = (m_iLevel / 10);
    if (sMagicCircle != sLevelMagic)
    {
        if (sMagicCircle > sLevelMagic)
        {
            dV1 = (double)(m_iLevel - sLevelMagic * 10);
            dV2 = (double)abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle];
            dV3 = (double)abs(sMagicCircle - sLevelMagic) * 10;
            dV4 = (dV1 / dV3) * dV2;
            iResult -= abs(abs(sMagicCircle - sLevelMagic) * _tmp_iMLevelPenalty[sMagicCircle] - (int)dV4);
        }
        else
        {
            iResult += 5 * abs(sMagicCircle - sLevelMagic);
        }
    }

    switch (m_cWhetherStatus)
    {
        case 0: break;
        case 1: iResult = iResult - (iResult / 24); break;
        case 2:	iResult = iResult - (iResult / 12); break;
        case 3: iResult = iResult - (iResult / 5);  break;
    }
    for (i = 0; i < DEF_MAXITEMS; i++)
    {
        if (m_pItemList[i] == 0) continue;
        if (m_bIsItemEquipped[i] == true)
        {
            if (((m_pItemList[i]->m_dwAttribute & 0x00F00000) >> 20) == 10)
            {
                dV1 = (double)iResult;
                dV2 = (double)(((m_pItemList[i]->m_dwAttribute & 0x000F0000) >> 16) * 3);
                dV3 = dV1 + dV2;
                iResult = (int)dV3;
                break;
            }
        }
    }

    if (iResult > 100) iResult = 100;
    if (m_iSP < 1) iResult = iResult * 9 / 10;
    if (iResult < 1) iResult = 1;

    ZeroMemory(cTxt, sizeof(cTxt));
    wsprintfA(cTxt, DRAW_DIALOGBOX_MAGIC16, iResult);//"
    PutAlignedString(sX, sX + 256, sY + 267, cTxt);
    PutAlignedString(sX + 1, sX + 257, sY + 267, cTxt);

    // v2.15
    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 285) && (msY <= sY + 285 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 285, 49, false, m_bDialogTrans);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 285, 48, false, m_bDialogTrans);
}

void CGame::DrawDialogBox_MagicShop(short msX, short msY, short msZ)
{
    short sX, sY;
    uint64_t dwTime = m_dwCurTime;
    int  i;

    int  iCPivot, iYloc;
    char cTxt[120], cMana[10];

    sX = m_stDialogBoxInfo[16].sX;
    sY = m_stDialogBoxInfo[16].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX, sY, 1);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 14);

    if (iGetTopDialogBoxIndex() == 16 && msZ != 0)
    {
        if (msZ > 0) m_stDialogBoxInfo[16].sView--;
        if (msZ < 0) m_stDialogBoxInfo[16].sView++;
        m_stMCursor.sZ = 0;
    }
    if (m_stDialogBoxInfo[16].sView < 0) m_stDialogBoxInfo[16].sView = 9;
    if (m_stDialogBoxInfo[16].sView > 9) m_stDialogBoxInfo[16].sView = 0;

    PutString(sX - 20 + 60 - 17, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP11, Color(45, 25, 25));//"Spell Name"
    PutString(sX - 20 + 232 - 20, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP12, Color(45, 25, 25));//"Req.Int"
    PutString(sX - 20 + 270, sY - 35 + 90, DRAW_DIALOGBOX_MAGICSHOP13, Color(45, 25, 25));//"Cost"

    iCPivot = m_stDialogBoxInfo[16].sView * 10;

    iYloc = 0;
    for (i = 0; i < 9; i++)
    {
        if ((m_pMagicCfgList[iCPivot + i] != 0) && (m_pMagicCfgList[iCPivot + i]->m_bIsVisible))
        {
            wsprintfA(cTxt, "%s", m_pMagicCfgList[iCPivot + i]->m_cName);

            m_Misc.ReplaceString(cTxt, '-', ' ');
            if (m_cMagicMastery[iCPivot + i] != 0)
            {
                if (m_Misc.bCheckIMEString(cTxt) == false)
                {
                    PutString(sX + 24, sY + 73 + iYloc, cTxt, Color(41, 16, 41));
                    PutString(sX + 25, sY + 73 + iYloc, cTxt, Color(41, 16, 41));
                }
                else PutString_SprFont(sX + 24, sY + 70 + iYloc, cTxt, 5, 5, 5);
                wsprintfA(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue2);
                PutString_SprFont(sX + 200, sY + 70 + iYloc, cMana, 5, 5, 5);
                wsprintfA(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue3);
                PutString_SprFont(sX + 241, sY + 70 + iYloc, cMana, 5, 5, 5);
            }
            else
                if ((msX >= sX + 24) && (msX <= sX + 24 + 135) && (msY >= sY + 70 + iYloc) && (msY <= sY + 70 + 14 + iYloc))
                {
                    if (m_Misc.bCheckIMEString(cTxt) == false)
                    {
                        PutString(sX + 24, sY + 73 + iYloc, cTxt, Color(255, 255, 255));
                        PutString(sX + 25, sY + 73 + iYloc, cTxt, Color(255, 255, 255));
                    }
                    else PutString_SprFont(sX - 20 + 44, sY + 70 + iYloc, cTxt, 250, 250, 250);
                    wsprintfA(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue2);
                    PutString_SprFont(sX - 20 + 220, sY + 70 + iYloc, cMana, 250, 250, 250);
                    wsprintfA(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue3);
                    PutString_SprFont(sX - 20 + 261, sY + 70 + iYloc, cMana, 250, 250, 250);
                }
                else
                {
                    if (m_Misc.bCheckIMEString(cTxt) == false)
                    {
                        PutString(sX + 24, sY + 73 + iYloc, cTxt, Color(8, 0, 66));
                        PutString(sX + 25, sY + 73 + iYloc, cTxt, Color(8, 0, 66));
                    }
                    else PutString_SprFont(sX - 20 + 44, sY + 70 + iYloc, cTxt, 1, 1, 8);
                    wsprintfA(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue2);
                    PutString_SprFont(sX - 20 + 220, sY + 70 + iYloc, cMana, 1, 1, 8);
                    wsprintfA(cMana, "%3d", m_pMagicCfgList[iCPivot + i]->m_sValue3);
                    PutString_SprFont(sX - 20 + 261, sY + 70 + iYloc, cMana, 1, 1, 8);
                }
            iYloc += 18;
        }
    }

    m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX + 55, sY + 250, 19, dwTime);

    switch (m_stDialogBoxInfo[16].sView)
    {
        case 0: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 44 + 31, sY + 250, 20, dwTime); break;
        case 1: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 57 + 31, sY + 250, 21, dwTime); break;
        case 2: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 75 + 31, sY + 250, 22, dwTime); break;
        case 3: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 100 + 31, sY + 250, 23, dwTime); break;
        case 4: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 120 + 31, sY + 250, 24, dwTime); break;
        case 5: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 135 + 31, sY + 250, 25, dwTime); break;
        case 6: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 156 + 31, sY + 250, 26, dwTime); break;
        case 7: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 183 + 31, sY + 250, 27, dwTime); break;
        case 8: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 216 + 31, sY + 250, 28, dwTime); break;
        case 9: m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS]->PutSpriteFast(sX - 20 + 236 + 31, sY + 250, 29, dwTime); break;
    }

    PutAlignedString(sX, sX + m_stDialogBoxInfo[16].sSizeX, sY + 275, DRAW_DIALOGBOX_MAGICSHOP14, 45, 25, 25);
}

void CGame::DrawDialogBox_ShutDownMsg(short msX, short msY)
{
    short sX, sY, szX;

    sX = m_stDialogBoxInfo[25].sX;
    sY = m_stDialogBoxInfo[25].sY;
    szX = m_stDialogBoxInfo[25].sSizeX;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX, sY, 2);

    switch (m_stDialogBoxInfo[25].cMode)
    {
        case 1:
            ZeroMemory(G_cTxt, sizeof(G_cTxt));
            if (m_stDialogBoxInfo[25].sV1 != 0) wsprintfA(G_cTxt, DRAW_DIALOGBOX_NOTICEMSG1, m_stDialogBoxInfo[25].sV1);
            else strcpy(G_cTxt, DRAW_DIALOGBOX_NOTICEMSG2);
            PutAlignedString(sX, sX + szX, sY + 31, G_cTxt, 100, 10, 10);
            PutAlignedString(sX, sX + szX, sY + 48, DRAW_DIALOGBOX_NOTICEMSG3);
            PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_NOTICEMSG4);
            PutAlignedString(sX, sX + szX, sY + 82, DRAW_DIALOGBOX_NOTICEMSG5);
            PutAlignedString(sX, sX + szX, sY + 99, DRAW_DIALOGBOX_NOTICEMSG6);
            if ((msX >= sX + 210) && (msX <= sX + 210 + DEF_BTNSZX) && (msY > sY + 127) && (msY < sY + 127 + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 0);
            break;

        case 2:
            PutAlignedString(sX, sX + szX, sY + 31, DRAW_DIALOGBOX_NOTICEMSG7, 100, 10, 10);
            PutAlignedString(sX, sX + szX, sY + 48, DRAW_DIALOGBOX_NOTICEMSG8);
            PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_NOTICEMSG9);
            PutAlignedString(sX, sX + szX, sY + 82, DRAW_DIALOGBOX_NOTICEMSG10);
            PutAlignedString(sX, sX + szX, sY + 99, DRAW_DIALOGBOX_NOTICEMSG11);
            if ((msX >= sX + 210) && (msX <= sX + 210 + DEF_BTNSZX) && (msY > sY + 127) && (msY < sY + 127 + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 210, sY + 127, 0);
            break;
    }
}

void CGame::DrawDialogBox_NpcActionQuery(short msX, short msY)
{
    short sX, sY, szX;

    char cTxt[120], cTxt2[120], cStr1[64], cStr2[64], cStr3[64];

    ZeroMemory(cStr1, sizeof(cStr1));
    ZeroMemory(cStr2, sizeof(cStr2));
    ZeroMemory(cStr3, sizeof(cStr3));

    sX = m_stDialogBoxInfo[20].sX;
    sY = m_stDialogBoxInfo[20].sY;
    szX = m_stDialogBoxInfo[20].sSizeX;

    //DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5); //5
    //DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6); //6

    switch (m_stDialogBoxInfo[20].cMode)
    {
        case 0: // npc
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
            switch (m_stDialogBoxInfo[20].sV3)
            {
                case 15:
                    PutString(sX + 33, sY + 23, NPC_NAME_SHOP_KEEPER, Color(45, 25, 25));
                    PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_SHOP_KEEPER, Color(255, 255, 255));
                    break;
                case 19:
                    PutString(sX + 33, sY + 23, NPC_NAME_MAGICIAN, Color(45, 25, 25));
                    PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_MAGICIAN, Color(255, 255, 255));
                    break;
                case 20:
                    PutString(sX + 33, sY + 23, NPC_NAME_WAREHOUSE_KEEPER, Color(45, 25, 25));
                    PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_WAREHOUSE_KEEPER, Color(255, 255, 255));
                    break;
                case 24:
                    PutString(sX + 33, sY + 23, NPC_NAME_BLACKSMITH_KEEPER, Color(45, 25, 25));
                    PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_BLACKSMITH_KEEPER, Color(255, 255, 255));
                    break;
                case 25:
                    PutString(sX + 33, sY + 23, NPC_NAME_CITYHALL_OFFICER, Color(45, 25, 25));
                    PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_CITYHALL_OFFICER, Color(255, 255, 255));
                    break;
                case 26: // "Guildhall Officer"
                    PutString(sX + 33, sY + 23, NPC_NAME_GUILDHALL_OFFICER, Color(45, 25, 25));
                    PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_GUILDHALL_OFFICER, Color(255, 255, 255));
                    break;
                case 90: //Gail
                    PutString(sX + 33, sY + 23, "Heldenian staff officer", Color(45, 25, 25));
                    PutString(sX + 33 - 1, sY + 23 - 1, "Heldenian staff officer", Color(255, 255, 255));
                    break;
            }

            if (m_stDialogBoxInfo[20].sV3 == 25)
            {   // OFFER
                if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
                {
                    PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, Color(255, 255, 255)); // "Offer"
                    PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, Color(255, 255, 255));
                }
                else
                {
                    PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, Color(4, 0, 50));
                    PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY13, Color(4, 0, 50));
                }
            }
            else if (m_stDialogBoxInfo[20].sV3 == 20)
            {   // WITHDRAW
                if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
                {
                    PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, Color(255, 255, 255)); // "Withdraw"
                    PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, Color(255, 255, 255));
                }
                else
                {
                    PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, Color(4, 0, 50));
                    PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY17, Color(4, 0, 50));
                }
            }
            else if (m_stDialogBoxInfo[20].sV3 == 19)
            {   // LEARN
                if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
                {
                    PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, Color(255, 255, 255)); // "Learn"
                    PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, Color(255, 255, 255));
                }
                else
                {
                    PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, Color(4, 0, 50));
                    PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY19, Color(4, 0, 50));
                }
            }
            else
            {   // TRADE
                if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
                {
                    PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(255, 255, 255)); // "Trade"
                    PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(255, 255, 255));
                }
                else
                {
                    PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(4, 0, 50));
                    PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(4, 0, 50));
                }
            }

            if (m_bIsDialogEnabled[21] == false)
            {
                if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
                {
                    PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(255, 255, 255)); // "Talk"
                    PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(255, 255, 255));
                }
                else
                {
                    PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(4, 0, 50));
                    PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(4, 0, 50));
                }
            }
            break;

        case 1: // Other char
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);
            GetItemName(m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_dwAttribute, cStr1, cStr2, cStr3);
            wsprintfA(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, m_stDialogBoxInfo[20].sV3, cStr1); //"%d %s to"
            wsprintfA(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, m_stDialogBoxInfo[20].cStr); // "%s"

            PutString(sX + 24, sY + 25, cTxt, Color(45, 25, 25));
            PutString(sX + 24, sY + 40, cTxt2, Color(45, 25, 25));

            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, Color(255, 255, 255));//"Give"
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, Color(255, 255, 255));
            }
            else
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, Color(4, 0, 50));
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY30, Color(4, 0, 50));
            }

            if ((msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70))
            {
                PutString(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, Color(255, 255, 255));//"Exchange"
                PutString(sX + 156, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, Color(255, 255, 255));
            }
            else
            {
                PutString(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, Color(4, 0, 50));
                PutString(sX + 156, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY34, Color(4, 0, 50));
            }
            break;

        case 2: // Shop / BS
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
            GetItemName(m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_dwAttribute, cStr1, cStr2, cStr3);

            wsprintfA(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, m_stDialogBoxInfo[20].sV3, cStr1);//"%d %s to"
            wsprintfA(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, m_stDialogBoxInfo[20].cStr);//"%s"

            PutString(sX + 24, sY + 20, cTxt, Color(45, 25, 25));
            PutString(sX + 24, sY + 35, cTxt2, Color(45, 25, 25));

            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, Color(255, 255, 255));//"Sell"
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, Color(255, 255, 255));
            }
            else
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, Color(4, 0, 50));
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, Color(4, 0, 50));
            }

            if ((m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cItemType == DEF_ITEMTYPE_CONSUME) ||
                (m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cItemType == DEF_ITEMTYPE_ARROW))
            {
            }
            else
            {
                if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
                {
                    PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, Color(255, 255, 255));//"Repair"
                    PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, Color(255, 255, 255));
                }
                else
                {
                    PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, Color(4, 0, 50));
                    PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY43, Color(4, 0, 50));
                }
            }
            break;

        case 3: // WH
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);
            GetItemName(m_pItemList[m_stDialogBoxInfo[20].sV1]->m_cName, m_pItemList[m_stDialogBoxInfo[20].sV1]->m_dwAttribute, cStr1, cStr2, cStr3);

            wsprintfA(cTxt, DRAW_DIALOGBOX_NPCACTION_QUERY29, m_stDialogBoxInfo[20].sV3, cStr1);//"%d %s to"
            wsprintfA(cTxt2, DRAW_DIALOGBOX_NPCACTION_QUERY29_1, m_stDialogBoxInfo[20].cStr);//"%s"

            PutAlignedString(sX, sX + 240, sY + 20, cTxt, 45, 25, 25);
            PutAlignedString(sX, sX + 240, sY + 35, cTxt2, 45, 25, 25);

            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, Color(255, 255, 255));//"Deposit"
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, Color(255, 255, 255));
            }
            else
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, Color(4, 0, 50));
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY48, Color(4, 0, 50));
            }
            break;

        case 4: // talk to npc or unicorn
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
            switch (m_stDialogBoxInfo[20].sV3)
            {
                case 21:
                    PutString(sX + 35, sY + 25, NPC_NAME_GUARD, Color(45, 25, 25));//
                    PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_GUARD, Color(255, 255, 255));
                    break;
                case 32:
                    PutString(sX + 35, sY + 25, NPC_NAME_UNICORN, Color(45, 25, 25));//"
                    PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_UNICORN, Color(255, 255, 255));//"
                    break;
                case 67:
                    PutString(sX + 35, sY + 25, NPC_NAME_MCGAFFIN, Color(45, 25, 25));
                    PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_MCGAFFIN, Color(255, 255, 255));
                    break;
                case 68:
                    PutString(sX + 35, sY + 25, NPC_NAME_PERRY, Color(45, 25, 25));
                    PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_PERRY, Color(255, 255, 255));
                    break;
                case 69:
                    PutString(sX + 35, sY + 25, NPC_NAME_DEVLIN, Color(45, 25, 25));
                    PutString(sX + 35 - 1, sY + 25 - 1, NPC_NAME_DEVLIN, Color(255, 255, 255));
                    break;

            }

            if (m_bIsDialogEnabled[21] == false)
            {
                if ((msX > sX + 125) && (msX < sX + 180) && (msY > sY + 55) && (msY < sY + 70))
                {
                    PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(255, 255, 255));
                    PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(255, 255, 255));
                }
                else
                {
                    PutString(sX + 125, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(4, 0, 50));
                    PutString(sX + 126, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(4, 0, 50));
                }
            }
            break;

        case 5: // Shop / BS
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 6);
            switch (m_stDialogBoxInfo[20].sV3)
            {
                case 15:
                    PutString(sX + 33, sY + 23, NPC_NAME_SHOP_KEEPER, Color(45, 25, 25));//Shop Keeper"
                    PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_SHOP_KEEPER, Color(255, 255, 255));
                    break;
                case 24:
                    PutString(sX + 33, sY + 23, NPC_NAME_BLACKSMITH_KEEPER, Color(45, 25, 25));//"BlackSmith Keeper"
                    PutString(sX + 33 - 1, sY + 23 - 1, NPC_NAME_BLACKSMITH_KEEPER, Color(255, 255, 255));//"
                    break;
            }

            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(255, 255, 255));//"Trade"
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(255, 255, 255));
            }
            else
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(4, 0, 50));
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(4, 0, 50));
            }

            if ((msX > sX + 25 + 79) && (msX < sX + 80 + 75) && (msY > sY + 55) && (msY < sY + 70))
            {
                PutString(sX + 28 + 75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, Color(255, 255, 255));//"Sell"
                PutString(sX + 29 + 75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, Color(255, 255, 255));
            }
            else
            {
                PutString(sX + 28 + 75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, Color(4, 0, 50));
                PutString(sX + 29 + 75, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY39, Color(4, 0, 50));
            }
            if (m_bIsDialogEnabled[21] == false)
            {
                if ((msX > sX + 155) && (msX < sX + 210) && (msY > sY + 55) && (msY < sY + 70))
                {
                    PutString(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(255, 255, 255));//"Talk"
                    PutString(sX + 156, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(255, 255, 255));
                }
                else
                {
                    PutString(sX + 155, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(4, 0, 50));
                    PutString(sX + 156, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY25, Color(4, 0, 50));
                }
            }
            break;

        case 6: //Gail
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);
            if ((msX > sX + 25) && (msX < sX + 100) && (msY > sY + 55) && (msY < sY + 70))
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(255, 255, 255)); // "Trade"
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(255, 255, 255));
            }
            else
            {
                PutString(sX + 28, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(4, 0, 50));
                PutString(sX + 29, sY + 55, DRAW_DIALOGBOX_NPCACTION_QUERY21, Color(4, 0, 50));
            }
            PutString(sX + 33, sY + 23, "Heldenian staff officer", Color(45, 25, 25));
            PutString(sX + 33 - 1, sY + 23 - 1, "Heldenian staff officer", Color(255, 255, 255));
            break;
    }
}

void CGame::DrawDialogBox_Party(short msX, short msY)
{
    short sX, sY, szX;
    int  i, iNth;
    sX = m_stDialogBoxInfo[32].sX;
    sY = m_stDialogBoxInfo[32].sY;
    szX = m_stDialogBoxInfo[32].sSizeX;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 3);

    switch (m_stDialogBoxInfo[32].cMode)
    {
        case 0:
            if (m_iPartyStatus == 0)
            {
                if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 80) && (msY < sY + 100))
                    PutAlignedString(sX, sX + szX, sY + 85, DRAW_DIALOGBOX_PARTY1, 255, 255, 255);//"
                else PutAlignedString(sX, sX + szX, sY + 85, DRAW_DIALOGBOX_PARTY1, 4, 0, 50);//"
            }
            else PutAlignedString(sX, sX + szX, sY + 85, DRAW_DIALOGBOX_PARTY1, 65, 65, 65);//"

            if (m_iPartyStatus != 0)
            {
                if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 100) && (msY < sY + 120))
                    PutAlignedString(sX, sX + szX, sY + 105, DRAW_DIALOGBOX_PARTY4, 255, 255, 255);//"
                else PutAlignedString(sX, sX + szX, sY + 105, DRAW_DIALOGBOX_PARTY4, 4, 0, 50);//"
            }
            else PutAlignedString(sX, sX + szX, sY + 105, DRAW_DIALOGBOX_PARTY4, 65, 65, 65);//"

            if (m_iPartyStatus != 0)
            {
                if ((msX > sX + 80) && (msX < sX + 195) && (msY > sY + 120) && (msY < sY + 140))
                    PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY7, 255, 255, 255);//"
                else PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY7, 4, 0, 50);//"
            }
            else PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY7, 65, 65, 65);//"


            switch (m_iPartyStatus)
            {
                case 0:
                    PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY10);//"
                    PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_PARTY11);//"
                    PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_PARTY12);//"
                    break;

                case 1:
                case 2:
                    PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY13);//"
                    PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_PARTY14);//"
                    PutAlignedString(sX, sX + szX, sY + 185, DRAW_DIALOGBOX_PARTY15);//"
                    break;
            }

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
            break;

        case 1: //
            wsprintfA(G_cTxt, DRAW_DIALOGBOX_PARTY16, m_stDialogBoxInfo[32].cStr);
            PutAlignedString(sX, sX + szX, sY + 95, G_cTxt);
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY17);//"join the party. You can"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY18);//"share the experience by"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY19);//"the ratio of level if"
            PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY20);//"you join the party."
            PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_PARTY21);//"Would you like to join party?"

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
            break;

        case 2:
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY22);//"Click the character which"
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY23);//"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY24);//"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY25);//"

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 3:
            wsprintfA(G_cTxt, DRAW_DIALOGBOX_PARTY26, m_stDialogBoxInfo[32].cStr);//"
            PutAlignedString(sX, sX + szX, sY + 95, G_cTxt);
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY27);//"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY28);//"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY29);//"
            PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY30);//"

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 4:
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY31);//"
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY32);//"

            iNth = 0;
            for (i = 0; i <= DEF_MAXPARTYMEMBERS; i++)
                if (strlen(m_stPartyMemberNameList[i].cName) != 0)
                {
                    wsprintfA(G_cTxt, "%s", m_stPartyMemberNameList[i].cName);
                    PutAlignedString(sX + 17, sX + 270, sY + 140 + 15 * (iNth), G_cTxt);
                    iNth++;
                }

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 5:
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY33);//"
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY34);//"
            break;

        case 6:
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY35);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 7:
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY36);//"
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY37);//"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY38);//"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY39);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 8:
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY40);//"
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY41);//"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY42);//"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY43);//"
            PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY44);//"
            PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_PARTY45);//"


            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 9:
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY46);//"
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY47);//"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY48);//"
            PutAlignedString(sX, sX + szX, sY + 140, DRAW_DIALOGBOX_PARTY49);//"
            PutAlignedString(sX, sX + szX, sY + 155, DRAW_DIALOGBOX_PARTY50);//"
            PutAlignedString(sX, sX + szX, sY + 170, DRAW_DIALOGBOX_PARTY51);//"

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 10:
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY52);//"
            PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_PARTY53);//"
            PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_PARTY54);//"
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 11: //
            PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_PARTY55);//"
            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 19);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 18);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 3);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 2);
            break;
    }
}

void CGame::DrawDialogBox_QueryDropItemAmount()
{
    short sX, sY;
    char cTxt[120], cStr1[64], cStr2[64], cStr3[64];

    sX = m_stDialogBoxInfo[17].sX;
    sY = m_stDialogBoxInfo[17].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 5);

    switch (m_stDialogBoxInfo[17].cMode)
    {
        case 1:
            GetItemName(m_pItemList[m_stDialogBoxInfo[17].sView]->m_cName, m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwAttribute, cStr1, cStr2, cStr3);
            if (strlen(m_stDialogBoxInfo[17].cStr) == 0)
                wsprintfA(cTxt, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT1, cStr1);
            else wsprintfA(cTxt, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT2, cStr1, m_stDialogBoxInfo[17].cStr);//"%s:

            if (m_stDialogBoxInfo[17].sV3 < 1000)
                PutString(sX + 30, sY + 20, cTxt, Color(55, 25, 25));

            PutString(sX + 30, sY + 35, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT3, Color(55, 25, 25));//"
            if (iGetTopDialogBoxIndex() != 17)
                PutString(sX + 40, sY + 57, m_cAmountString, Color(255, 255, 255), false, 2);
            wsprintfA(cTxt, "__________ (0 ~ %d)", m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount);
            PutString(sX + 38, sY + 62, cTxt, Color(25, 35, 25));
            break;

        case 20:
            GetItemName(m_pItemList[m_stDialogBoxInfo[17].sView]->m_cName, m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwAttribute, cStr1, cStr2, cStr3);
            if (strlen(m_stDialogBoxInfo[17].cStr) == 0) // v1.4
                wsprintfA(cTxt, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT1, cStr1);//"%s:
            else wsprintfA(cTxt, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT2, cStr1, m_stDialogBoxInfo[17].cStr);//"%s:

            if (m_stDialogBoxInfo[17].sV3 < 1000) // v1.4
                PutString(sX + 30, sY + 20, cTxt, Color(55, 25, 25));

            PutString(sX + 30, sY + 35, DRAW_DIALOGBOX_QUERY_DROP_ITEM_AMOUNT3, Color(55, 25, 25));//"
            PutString(sX + 40, sY + 57, m_cAmountString, Color(255, 255, 255), false, 2);
            wsprintfA(cTxt, "__________ (0 ~ %d)", m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount);
            PutString(sX + 38, sY + 62, cTxt, Color(25, 35, 25));
            break;
    }
}


void CGame::DrawDialogBox_Quest(int msX, int msY)
{
    short sX, sY, szX;
    char cTxt[120], cTemp[21];

    sX = m_stDialogBoxInfo[28].sX;
    sY = m_stDialogBoxInfo[28].sY;
    szX = m_stDialogBoxInfo[28].sSizeX;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 4);

    switch (m_stDialogBoxInfo[28].cMode)
    {
        case 1:
            switch (m_stQuest.sQuestType)
            {
                case 0:
                    PutAlignedString(sX, sX + szX, sY + 50 + 115 - 30, DRAW_DIALOGBOX_QUEST1, 55, 25, 25); // " You are not on a quest."
                    break;

                case 1:	//  Hunt
                    if (m_stQuest.bIsQuestCompleted == false)
                        PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST2, 55, 25, 25); // "You are on a monster conquering quest."
                    else PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST3, 55, 25, 25); // "You accomplished the monster conquering quest."

                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, "Rest Monster : %d", m_stQuest.sCurrentCount); // "Rest Monster : %s"
                    PutAlignedString(sX, sX + szX, sY + 50 + 20, cTxt, 55, 25, 25);  // m_stQuest.sCurrentCount

                    ZeroMemory(cTemp, sizeof(cTemp));
                    switch (m_stQuest.sWho)
                    {
                        case 1:
                        case 2:
                        case 3: break;
                        case 4: strcpy(cTemp, NPC_NAME_CITYHALL_OFFICER); break;
                        case 5:
                        case 6:
                        case 7: break;
                    }
                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, DRAW_DIALOGBOX_QUEST5, cTemp); // "Client: %s"
                    PutAlignedString(sX, sX + szX, sY + 50 + 45, cTxt, 55, 25, 25);

                    ZeroMemory(cTemp, sizeof(cTemp));
                    GetNpcName(m_stQuest.sTargetType, cTemp);
                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, NPC_TALK_HANDLER16, m_stQuest.sTargetCount, cTemp);
                    PutAlignedString(sX, sX + szX, sY + 50 + 60, cTxt, 55, 25, 25);

                    ZeroMemory(cTxt, sizeof(cTxt));
                    if (memcmp(m_stQuest.cTargetName, "NONE", 4) == 0)
                    {
                        strcpy(cTxt, DRAW_DIALOGBOX_QUEST31); // "Location : Anywhere"
                        PutAlignedString(sX, sX + szX, sY + 50 + 75, cTxt, 55, 25, 25);
                    }
                    else
                    {
                        ZeroMemory(cTemp, sizeof(cTemp));
                        GetOfficialMapName(m_stQuest.cTargetName, cTemp);
                        wsprintfA(cTxt, DRAW_DIALOGBOX_QUEST32, cTemp); // "Map : %s"
                        PutAlignedString(sX, sX + szX, sY + 50 + 75, cTxt, 55, 25, 25);

                        if (m_stQuest.sX != 0)
                        {
                            ZeroMemory(cTxt, sizeof(cTxt));
                            wsprintfA(cTxt, DRAW_DIALOGBOX_QUEST33, m_stQuest.sX, m_stQuest.sY, m_stQuest.sRange); // "Position: %d, %d Range: %d block"
                            PutAlignedString(sX, sX + szX, sY + 50 + 90, cTxt, 55, 25, 25);
                        }
                    }

                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, DRAW_DIALOGBOX_QUEST34, m_stQuest.sContribution); // "Contribution: %d"
                    PutAlignedString(sX, sX + szX, sY + 50 + 105, cTxt, 55, 25, 25);
                    break;

                case 7: //
                    if (m_stQuest.bIsQuestCompleted == false)
                        PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST26, 55, 25, 25);
                    else PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_QUEST27, 55, 25, 25);

                    ZeroMemory(cTemp, sizeof(cTemp));
                    switch (m_stQuest.sWho)
                    {
                        case 1:
                        case 2:
                        case 3: break;
                        case 4: strcpy(cTemp, NPC_NAME_CITYHALL_OFFICER); break;
                        case 5:
                        case 6:
                        case 7: break;
                    }
                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, DRAW_DIALOGBOX_QUEST29, cTemp);
                    PutAlignedString(sX, sX + szX, sY + 50 + 45, cTxt, 55, 25, 25);

                    PutAlignedString(sX, sX + szX, sY + 50 + 60, DRAW_DIALOGBOX_QUEST30, 55, 25, 25);

                    ZeroMemory(cTxt, sizeof(cTxt));
                    if (memcmp(m_stQuest.cTargetName, "NONE", 4) == 0)
                    {
                        strcpy(cTxt, DRAW_DIALOGBOX_QUEST31);
                        PutAlignedString(sX, sX + szX, sY + 50 + 75, cTxt, 55, 25, 25);
                    }
                    else
                    {
                        ZeroMemory(cTemp, sizeof(cTemp));
                        GetOfficialMapName(m_stQuest.cTargetName, cTemp);
                        wsprintfA(cTxt, DRAW_DIALOGBOX_QUEST32, cTemp);
                        PutAlignedString(sX, sX + szX, sY + 50 + 75, cTxt, 55, 25, 25);

                        if (m_stQuest.sX != 0)
                        {
                            ZeroMemory(cTxt, sizeof(cTxt));
                            wsprintfA(cTxt, DRAW_DIALOGBOX_QUEST33, m_stQuest.sX, m_stQuest.sY, m_stQuest.sRange);
                            PutAlignedString(sX, sX + szX, sY + 50 + 90, cTxt, 55, 25, 25);
                        }
                    }

                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, DRAW_DIALOGBOX_QUEST34, m_stQuest.sContribution);//" %dPoint"
                    PutAlignedString(sX, sX + szX, sY + 50 + 105, cTxt, 55, 25, 25);
                    break;
            }
            break;

        case 2:
            PutAlignedString(sX, sX + szX, sY + 50 + 115 - 30, DRAW_DIALOGBOX_QUEST35, 55, 25, 25);
            break;
    }

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void CGame::DrawDialogBox_SellList(short msX, short msY)
{
    short sX, sY, szX;
    int  i, iItem;
    char cTemp[255], cStr1[64], cStr2[64], cStr3[64];

    sX = m_stDialogBoxInfo[31].sX;
    sY = m_stDialogBoxInfo[31].sY;
    szX = m_stDialogBoxInfo[31].sSizeX;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

    iItem = 0;
    for (i = 0; i < DEF_MAXSELLLIST; i++)
        if (m_stSellItemList[i].iIndex != -1)
        {
            ZeroMemory(cTemp, sizeof(cTemp));
            GetItemName(m_pItemList[m_stSellItemList[i].iIndex]->m_cName, m_pItemList[m_stSellItemList[i].iIndex]->m_dwAttribute, cStr1, cStr2, cStr3);
            if (m_stSellItemList[i].iAmount > 1)
            {
                wsprintfA(cTemp, DRAW_DIALOGBOX_SELL_LIST1, m_stSellItemList[i].iAmount, cStr1);
                if ((msX > sX + 25) && (msX < sX + 250) && (msY >= sY + 55 + i * 15) && (msY <= sY + 55 + 14 + i * 15))
                    PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTemp, 255, 255, 255);
                else
                {
                    if (m_bIsSpecial)
                        PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTemp, 0, 255, 50);
                    else
                        PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cTemp, 45, 25, 25);
                }
            }
            else
            {
                if ((msX > sX + 25) && (msX < sX + 250) && (msY >= sY + 55 + i * 15) && (msY <= sY + 55 + 14 + i * 15))
                {
                    if ((strlen(cStr2) == 0) && (strlen(cStr3) == 0)) PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 255, 255, 255);
                    else
                    {
                        ZeroMemory(G_cTxt, sizeof(G_cTxt));
                        if ((strlen(cStr1) + strlen(cStr2) + strlen(cStr3)) < 36)
                        {
                            if ((strlen(cStr2) > 0) && (strlen(cStr3) > 0)) wsprintfA(G_cTxt, "%s(%s, %s)", cStr1, cStr2, cStr3);
                            else wsprintfA(G_cTxt, "%s(%s%s)", cStr1, cStr2, cStr3);
                            PutAlignedString(sX, sX + szX, sY + 55 + i * 15, G_cTxt, 255, 255, 255);

                        }
                        else
                        {
                            if ((strlen(cStr2) > 0) && (strlen(cStr3) > 0)) wsprintfA(G_cTxt, "(%s, %s)", cStr2, cStr3);
                            else wsprintfA(G_cTxt, "(%s%s)", cStr2, cStr3);
                            PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 255, 255, 255);
                            PutAlignedString(sX, sX + szX, sY + 55 + i * 15 + 15, G_cTxt, 200, 200, 200);
                            i++;
                        }
                    }
                }
                else
                {
                    if ((strlen(cStr2) == 0) && (strlen(cStr3) == 0))
                    {
                        if (m_bIsSpecial)
                            PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 0, 255, 50);
                        else
                            PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 45, 25, 25);
                    }
                    else
                    {
                        ZeroMemory(G_cTxt, sizeof(G_cTxt));
                        if ((strlen(cStr1) + strlen(cStr2) + strlen(cStr3)) < 36)
                        {
                            if ((strlen(cStr2) > 0) && (strlen(cStr3) > 0)) wsprintfA(G_cTxt, "%s(%s, %s)", cStr1, cStr2, cStr3);
                            else wsprintfA(G_cTxt, "%s(%s%s)", cStr1, cStr2, cStr3);

                            if (m_bIsSpecial)
                                PutAlignedString(sX, sX + szX, sY + 55 + i * 15, G_cTxt, 0, 255, 50);
                            else
                                PutAlignedString(sX, sX + szX, sY + 55 + i * 15, G_cTxt, 45, 25, 25);

                        }
                        else
                        {
                            if (m_bIsSpecial)
                                PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 0, 255, 50);
                            else
                                PutAlignedString(sX, sX + szX, sY + 55 + i * 15, cStr1, 45, 25, 25);
                        }
                    }
                }
            }
        }
        else iItem++;

    if (iItem == DEF_MAXSELLLIST)
    {
        PutAlignedString(sX, sX + szX, sY + 55 + 30 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST2);//"
        PutAlignedString(sX, sX + szX, sY + 55 + 45 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST3);//"
        PutAlignedString(sX, sX + szX, sY + 55 + 60 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST4);//"
        PutAlignedString(sX, sX + szX, sY + 55 + 75 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST5);//"
        PutAlignedString(sX, sX + szX, sY + 55 + 95 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST6);//"
        PutAlignedString(sX, sX + szX, sY + 55 + 110 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST7);//"
        PutAlignedString(sX, sX + szX, sY + 55 + 125 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST8);//"
        PutAlignedString(sX, sX + szX, sY + 55 + 155 + 282 - 117 - 170, DRAW_DIALOGBOX_SELL_LIST9);//"

    }

    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY) && (iItem < DEF_MAXSELLLIST))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 39);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 38);

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
}

void CGame::DrawDialogBox_SellorRepairItem(short msX, short msY)
{
    short sX, sY;
    uint64_t dwTime = m_dwCurTime;
    char cItemID, cItemColor, cTxt[120], cTemp[120], cStr2[120], cStr3[120];

    sX = m_stDialogBoxInfo[23].sX;
    sY = m_stDialogBoxInfo[23].sY;

    switch (m_stDialogBoxInfo[23].cMode)
    {
        case 1:
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

            cItemID = m_stDialogBoxInfo[23].sV1;

            cItemColor = m_pItemList[cItemID]->m_cItemColor;
            if (cItemColor == 0)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteFast(sX + 62 + 15, sY + 84 + 30,
                    m_pItemList[cItemID]->m_sSpriteFrame, dwTime);
            else
            {
                switch (m_pItemList[cItemID]->m_sSprite)
                {
                    case 1: // Swds
                    case 2: // Bows
                    case 3: // Shields
                    case 15: // Axes hammers
#ifdef DEF_EQUILIBRIUM_PROJECT
                    case 17: // Wands
#endif
                        m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteRGB(sX + 62 + 15, sY + 84 + 30
                            , m_pItemList[cItemID]->m_sSpriteFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                        break;
                    default: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteRGB(sX + 62 + 15, sY + 84 + 30
                        , m_pItemList[cItemID]->m_sSpriteFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                        break;
                }
            }
            ZeroMemory(cTemp, sizeof(cTemp));
            ZeroMemory(cStr2, sizeof(cStr2));
            ZeroMemory(cStr3, sizeof(cStr3));

            GetItemName(m_pItemList[cItemID]->m_cName, m_pItemList[cItemID]->m_dwAttribute, cTemp, cStr2, cStr3);
            if (m_stDialogBoxInfo[23].sV4 == 1) strcpy(cTxt, cTemp);
            else wsprintfA(cTxt, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM1, m_stDialogBoxInfo[23].sV4, cTemp);

            if (m_bIsSpecial)
            {
                PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 0, 255, 50);
                PutAlignedString(sX + 25 + 1, sX + 240 + 1, sY + 60, cTxt, 0, 255, 50);
            }
            else
            {
                PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 45, 25, 25);
                PutAlignedString(sX + 25 + 1, sX + 240 + 1, sY + 60, cTxt, 45, 25, 25);
            }

            wsprintfA(cTxt, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM2, m_stDialogBoxInfo[23].sV2);
            PutString(sX + 95 + 15, sY + 53 + 60, cTxt, Color(45, 25, 25));
            wsprintfA(cTxt, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM3, m_stDialogBoxInfo[23].sV3);
            PutString(sX + 95 + 15, sY + 53 + 75, cTxt, Color(45, 25, 25));
            PutString(sX + 55, sY + 190, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM4, Color(45, 25, 25));

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 39);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 38);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 2:
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 10);
            cItemID = m_stDialogBoxInfo[23].sV1;
            cItemColor = m_pItemList[cItemID]->m_cItemColor; // v1.4
            if (cItemColor == 0)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteFast(sX + 62 + 15, sY + 84 + 30,
                    m_pItemList[cItemID]->m_sSpriteFrame, dwTime);
            else
            {
                switch (m_pItemList[cItemID]->m_sSprite)
                {
                    case 1: // Swds
                    case 2: // Bows
                    case 3: // Shields
                    case 15: // Axes hammers
#ifdef DEF_EQUILIBRIUM_PROJECT
                    case 17: // Wands
#endif
                        m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteRGB(sX + 62 + 15, sY + 84 + 30
                            , m_pItemList[cItemID]->m_sSpriteFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                        break;

                    default: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->PutSpriteRGB(sX + 62 + 15, sY + 84 + 30
                        , m_pItemList[cItemID]->m_sSpriteFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                        break;
                }
            }
            ZeroMemory(cTemp, sizeof(cTemp));
            ZeroMemory(cStr2, sizeof(cStr2));
            ZeroMemory(cStr3, sizeof(cStr3));
            GetItemName(m_pItemList[cItemID], cTemp, cStr2, cStr3);
            wsprintfA(cTxt, "%s", cTemp);
            //		PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 45,25,25);
            //		PutAlignedString(sX + 25 +1, sX + 240 +1, sY + 60, cTxt, 45,25,25);
            if (m_bIsSpecial)
            {
                PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 0, 255, 50);
                PutAlignedString(sX + 25 + 1, sX + 240 + 1, sY + 60, cTxt, 0, 255, 50);
            }
            else
            {
                PutAlignedString(sX + 25, sX + 240, sY + 60, cTxt, 45, 25, 25);
                PutAlignedString(sX + 25 + 1, sX + 240 + 1, sY + 60, cTxt, 45, 25, 25);
            }
            wsprintfA(cTxt, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM2, m_stDialogBoxInfo[23].sV2);
            PutString(sX + 95 + 15, sY + 53 + 60, cTxt, Color(45, 25, 25));
            wsprintfA(cTxt, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM6, m_stDialogBoxInfo[23].sV3);
            PutString(sX + 95 + 15, sY + 53 + 75, cTxt, Color(45, 25, 25));
            PutString(sX + 55, sY + 190, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM7, Color(45, 25, 25));

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 43);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 42);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 3:
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

            PutString(sX + 55, sY + 100, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM8, Color(45, 25, 25));//"
            PutString(sX + 55, sY + 120, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM9, Color(45, 25, 25));//"
            PutString(sX + 55, sY + 135, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM10, Color(45, 25, 25));//"
            break;

        case 4:
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 10);

            PutString(sX + 55, sY + 100, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM11, Color(45, 25, 25));//"
            PutString(sX + 55, sY + 120, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM9, Color(45, 25, 25));//"
            PutString(sX + 55, sY + 135, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM10, Color(45, 25, 25));//"
            break;
    }
}

void CGame::DrawDialogBox_Shop(short msX, short msY, short msZ, char cLB)
{
    short sX, sY;
    uint64_t dwTime = m_dwCurTime;
    int  i, iTemp;
    char cTemp[255], cStr2[255], cStr3[255];

#ifdef DEF_EQUILIBRIUM_PROJECT // Prices /charisma
    int  iCost, iMsgLoc = {};
#else
    int  iCost, iDiscountCost, iDiscountRatio;
#endif

    double dTmp1 = {}, dTmp2 = {}, dTmp3 = {};
    int  iTotalLines, iPointerLoc;
    bool bFlagStatLow = false;
    bool bFlagRedShown = false;
    double d1, d2, d3;

    sX = m_stDialogBoxInfo[11].sX;
    sY = m_stDialogBoxInfo[11].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 11);

    switch (m_stDialogBoxInfo[11].cMode)
    {
        case 0:
            iTotalLines = 0;
            for (i = 0; i < DEF_MAXMENUITEMS; i++)
                if (m_pItemForSaleList[i] != 0) iTotalLines++;
            if (iTotalLines > 13)
            {
                d1 = (double)m_stDialogBoxInfo[11].sView;
                d2 = (double)(iTotalLines - 13);
                d3 = (274.0f * d1) / d2;
                iPointerLoc = (int)(d3);
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 3);
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 242, sY + iPointerLoc + 35, 7);
            }
            else iPointerLoc = 0;

            if (cLB != 0 && iTotalLines > 13)
            {
                if ((iGetTopDialogBoxIndex() == 11))
                {
                    if ((msX >= sX + 235) && (msX <= sX + 260) && (msY >= sY + 10) && (msY <= sY + 330))
                    {
                        d1 = (double)(msY - (sY + 35));
                        d2 = (double)(iTotalLines - 13);
                        d3 = (d1 * d2) / 274.0f;
                        m_stDialogBoxInfo[11].sView = (int)(d3 + 0.5);
                    }
                }
            }
            else m_stDialogBoxInfo[11].bIsScrollSelected = false;
            if (iGetTopDialogBoxIndex() == 11 && msZ != 0)
            {
                m_stDialogBoxInfo[11].sView = m_stDialogBoxInfo[11].sView - msZ / 60;
                m_stMCursor.sZ = 0;
            }
            if (iTotalLines > 13 && m_stDialogBoxInfo[11].sView > iTotalLines - 13) m_stDialogBoxInfo[11].sView = iTotalLines - 13;
            if (m_stDialogBoxInfo[11].sView < 0 || iTotalLines < 13) m_stDialogBoxInfo[11].sView = 0;
            PutAlignedString(sX + 22, sX + 165, sY + 45, DRAW_DIALOGBOX_SHOP1); // "ITEM"
            PutAlignedString(sX + 23, sX + 166, sY + 45, DRAW_DIALOGBOX_SHOP1);
            PutAlignedString(sX + 153, sX + 250, sY + 45, DRAW_DIALOGBOX_SHOP3);
            PutAlignedString(sX + 154, sX + 251, sY + 45, DRAW_DIALOGBOX_SHOP3);

            for (i = 0; i < 13; i++)
                if (((i + m_stDialogBoxInfo[11].sView) < DEF_MAXMENUITEMS) && (m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView] != 0))
                {
                    ZeroMemory(cTemp, sizeof(cTemp));
                    GetItemName(m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView], cTemp, cStr2, cStr3);
                    if ((msX >= sX + 20) && (msX <= sX + 220) && (msY >= sY + i * 18 + 65) && (msY <= sY + i * 18 + 79))
                    {
                        PutAlignedString(sX + 10, sX + 190, sY + i * 18 + 65, cTemp, 255, 255, 255);
                    }
                    else PutAlignedString(sX + 10, sX + 190, sY + i * 18 + 65, cTemp, 4, 0, 50);
                }

            for (i = 0; i < 13; i++)
                if (((i + m_stDialogBoxInfo[11].sView) < DEF_MAXMENUITEMS) && (m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView] != 0))
                {

#ifdef DEF_EQUILIBRIUM_PROJECT // Prices charisma
                    iCost = (int)(m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice * ((100 + m_cDiscount) / 100.));
#else
                    iDiscountRatio = ((m_iCharisma - 10) / 4);
                    dTmp1 = (double)iDiscountRatio;
                    dTmp2 = dTmp1 / 100.0f;
                    dTmp1 = (double)m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice;
                    dTmp3 = dTmp1 * dTmp2;
                    iDiscountCost = (int)dTmp3;
                    iCost = (int)(m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice * ((100 + m_cDiscount) / 100.));
                    iCost = iCost - iDiscountCost;
#endif

                    if (iCost < (m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice / 2))
                        iCost = (m_pItemForSaleList[i + m_stDialogBoxInfo[11].sView]->m_wPrice / 2) - 1;
                    ZeroMemory(cTemp, sizeof(cTemp));
                    wsprintfA(cTemp, "%6d", iCost);
                    if ((msX >= sX + 20) && (msX <= sX + 220) && (msY >= sY + i * 18 + 65) && (msY <= sY + i * 18 + 79))
                        PutAlignedString(sX + 148, sX + 260, sY + i * 18 + 65, cTemp, 255, 255, 255);
                    else	PutAlignedString(sX + 148, sX + 260, sY + i * 18 + 65, cTemp, 4, 0, 50);
                }
            break;

        default:
            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sSprite]->PutSpriteFast(sX + 62 + 30 - 35, sY + 84 + 30 - 10,
                m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sSpriteFrame, dwTime);

            ZeroMemory(cTemp, sizeof(cTemp));
            GetItemName(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1], cTemp, cStr2, cStr3);

            PutAlignedString(sX + 25, sX + 240, sY + 50, cTemp, 255, 255, 255);
            PutAlignedString(sX + 26, sX + 241, sY + 50, cTemp, 255, 255, 255);

            strcpy(cTemp, DRAW_DIALOGBOX_SHOP3); //"PRICE"
            PutString(sX + 90, sY + 78 + 30 - 10, cTemp, Color(40, 10, 10));
            PutString(sX + 91, sY + 78 + 30 - 10, cTemp, Color(40, 10, 10));
            strcpy(cTemp, DRAW_DIALOGBOX_SHOP6); // "Weight"
            PutString(sX + 90, sY + 93 + 30 - 10, cTemp, Color(40, 10, 10));
            PutString(sX + 91, sY + 93 + 30 - 10, cTemp, Color(40, 10, 10));

#ifdef DEF_EQUILIBRIUM_PROJECT // Prices charisma
            iCost = (int)(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice * ((100 + m_cDiscount) / 100.));
#else
            iDiscountRatio = ((m_iCharisma - 10) / 4);
            dTmp1 = (double)iDiscountRatio;
            dTmp2 = dTmp1 / 100.0f;
            dTmp1 = (double)m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice;
            dTmp3 = dTmp1 * dTmp2;
            iDiscountCost = (int)dTmp3;
            iCost = (int)(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice * ((100 + m_cDiscount) / 100.));
            iCost = iCost - iDiscountCost;
#endif

            if (iCost < (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice / 2))
                iCost = (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wPrice / 2) - 1;

            wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP7, iCost);
            //": %d Gold"
            PutString(sX + 140, sY + 98, cTemp, Color(45, 25, 25));

            iTemp = m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight / 100;
            wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP8, iTemp);
            //": %d Stone"
            PutString(sX + 140, sY + 113, cTemp, Color(45, 25, 25));

            switch (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cEquipPos)
            {
                case DEF_EQUIPPOS_RHAND:
                case DEF_EQUIPPOS_TWOHAND:
                    strcpy(cTemp, DRAW_DIALOGBOX_SHOP9);  // Damage
                    PutString(sX + 90, sY + 145, cTemp, Color(40, 10, 10));
                    PutString(sX + 91, sY + 145, cTemp, Color(40, 10, 10));
                    strcpy(cTemp, DRAW_DIALOGBOX_SHOP10); //"Speed(Min.~Max.)"
                    PutString(sX + 40, sY + 175, cTemp, Color(40, 10, 10));
                    PutString(sX + 41, sY + 175, cTemp, Color(40, 10, 10));

                    if (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue3 != 0)
                    {
                        wsprintfA(cTemp, ": %dD%d+%d (S-M)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue1,
                            m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue2,
                            m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue3);
                    }
                    else
                    {
                        wsprintfA(cTemp, ": %dD%d (S-M)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue1,
                            m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue2);
                    }
                    PutString(sX + 140, sY + 145, cTemp, Color(45, 25, 25));
                    if (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue6 != 0)
                    {
                        wsprintfA(cTemp, ": %dD%d+%d (L)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue4,
                            m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5,
                            m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue6);
                    }
                    else
                    {
                        wsprintfA(cTemp, ": %dD%d (L)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue4,
                            m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                    }
                    PutString(sX + 140, sY + 160, cTemp, Color(45, 25, 25));
                    if (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cSpeed == 0)   wsprintfA(cTemp, ": 0(10~10)");
                    else wsprintfA(cTemp, ": %d(%d ~ %d)", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cSpeed, iTemp, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cSpeed * 13);
                    PutString(sX + 140, sY + 175, cTemp, Color(45, 25, 25));

                    if ((m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight / 100) > m_iStr)
                    {
                        wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP11, (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight / 100));
                        PutAlignedString(sX + 25, sX + 240, sY + 258, cTemp, 195, 25, 25);
                        PutAlignedString(sX + 26, sX + 241, sY + 258, cTemp, 195, 25, 25); // *Your STR should be at least %d to use this item."
                        bFlagRedShown = true;
                    }
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT	// Stats at BS -> Shields
                case DEF_EQUIPPOS_LHAND:
                case DEF_EQUIPPOS_HEAD:
                case DEF_EQUIPPOS_BODY:
                case DEF_EQUIPPOS_BOOTS:
                case DEF_EQUIPPOS_ARMS:
                case DEF_EQUIPPOS_PANTS:
                case DEF_EQUIPPOS_BACK:
                case DEF_EQUIPPOS_NECK:
                case DEF_EQUIPPOS_RFINGER:
                case DEF_EQUIPPOS_LFINGER:
#else
                case DEF_EQUIPPOS_LHAND:
                    strcpy(cTemp, DRAW_DIALOGBOX_SHOP12); // "Defence"
                    PutString(sX + 90, sY + 145, cTemp, Color(40, 10, 10));
                    PutString(sX + 91, sY + 145, cTemp, Color(40, 10, 10));
                    wsprintfA(cTemp, ": +%d%", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue1);
                    PutString(sX + 140, sY + 145, cTemp, Color(45, 25, 25));
                    if ((m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight / 100) > m_iStr)
                    {
                        wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP11, (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight / 100));
                        PutAlignedString(sX + 25, sX + 240, sY + 258, cTemp, 195, 25, 25); // "*Your STR should be at least %d to use this item."
                        PutAlignedString(sX + 26, sX + 241, sY + 258, cTemp, 195, 25, 25);
                        bFlagRedShown = true;
                    }
                    break;

                case DEF_EQUIPPOS_HEAD:
                case DEF_EQUIPPOS_BODY:
                case DEF_EQUIPPOS_BOOTS:
                case DEF_EQUIPPOS_ARMS:
                case DEF_EQUIPPOS_PANTS:
#endif

                    strcpy(cTemp, DRAW_DIALOGBOX_SHOP12); // "Defence"
                    PutString(sX + 90, sY + 145, cTemp, Color(40, 10, 10));
                    PutString(sX + 91, sY + 145, cTemp, Color(40, 10, 10));
                    wsprintfA(cTemp, ": +%d%", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue1);
                    PutString(sX + 140, sY + 145, cTemp, Color(45, 25, 25));
                    bFlagStatLow = false;
                    switch (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue4)
                    {
                        case 10://"Available for above Str %d"
                            wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP15, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iStr >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                                bFlagStatLow = true; // Means some red msg need to be shown at the bottom
                            }
                            break;
                        case 11: // "Available for above Dex %d"
                            wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP16, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iDex >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                                bFlagStatLow = true; // Means some red msg need to be shown at the bottom
                            }
                            break;
                        case 12: // "Available for above Vit %d"
                            wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP17, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iVit >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                                bFlagStatLow = true; // Means some red msg need to be shown at the bottom
                            }
                            break;
                        case 13: // "Available for above Int %d"
                            wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP18, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iInt >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                                bFlagStatLow = true; // Means some red msg need to be shown at the bottom
                            }
                            break;
                        case 14: // "Available for above Mag %d"
                            wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP19, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iMag >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                                bFlagStatLow = true; // Means some red msg need to be shown at the bottom
                            }
                            break;
                        case 15: // "Available for above Chr %d"
                            wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP20, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iCharisma >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                                bFlagStatLow = true; // Means some red msg need to be shown at the bottom
                            }
                            break;

#ifdef DEF_EQUILIBRIUM_PROJECT	// New items limitations
                        case 16: // mini contrib
                            wsprintfA(cTemp, "Mini Contribution %d", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iContribution >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;

                        case 17: // mini EKs
                            wsprintfA(cTemp, "Available for more than %d EKs", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iEnemyKillCount >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;

                        case 18: // mini reputation
                            wsprintfA(cTemp, "Mini reputation %d ", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iRating >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;

                        case 19: // mini reputation
                            wsprintfA(cTemp, "Mini reputation %d ", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iRating >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;

                        case 20:// max str
                            wsprintfA(cTemp, "Available for max Str %d", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iStr <= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;
                        case 21: // max dext
                            wsprintfA(cTemp, "Available for max Dex %d", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iDex <= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;
                        case 22: // max vit
                            wsprintfA(cTemp, "Available for max Vit %d", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iVit <= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;
                        case 23: // max int
                            wsprintfA(cTemp, "Available for max Int %d", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iInt <= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;
                        case 24: // max mag
                            wsprintfA(cTemp, "Available for max Mag %d", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iMag <= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;
                        case 25: // max charisma
                            wsprintfA(cTemp, "Available for max Chr %d", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iCharisma <= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;

                        case 27: // max EKs
                            wsprintfA(cTemp, "Forbidden if more than %d EKs", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if (m_iEnemyKillCount <= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5)
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;

                        case 66: // max EKs
                            wsprintfA(cTemp, "Available for blackest hearts only!", m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sItemEffectValue5);
                            if ((m_iPKCount > 0)
                                || (memcmp(m_cLocation, "executor", 8) == 0)
                                || (memcmp(m_cLocation, "evil", 4) == 0))
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 45, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 45, 25, 25);
                            }
                            else
                            {
                                PutAlignedString(sX + 25, sX + 240, sY + 160, cTemp, 125, 25, 25);
                                PutAlignedString(sX + 26, sX + 241, sY + 160, cTemp, 125, 25, 25);
                            }
                            break;

#endif

                        default:
                            break;
                    }
                    if ((m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight / 100) > m_iStr)
                    {
                        wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP11, (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_wWeight / 100));
                        PutAlignedString(sX + 25, sX + 240, sY + 288, cTemp, 195, 25, 25);
                        PutAlignedString(sX + 26, sX + 241, sY + 288, cTemp, 195, 25, 25); // "*Your STR should be at least %d to use this item."
                        bFlagRedShown = true;
                    }
                    else if (bFlagStatLow == true) // Means some stat is too low
                    {
                        strcpy(cTemp, DRAW_DIALOGBOX_SHOP21); // "(Warning!) Your stat is too low for this item."
                        PutAlignedString(sX + 25, sX + 240, sY + 258, cTemp, 195, 25, 25);
                        PutAlignedString(sX + 26, sX + 241, sY + 258, cTemp, 195, 25, 25);
                        bFlagRedShown = true;
                    }
                    else if ((strstr(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cName, "(M)") != 0)
                        && (m_sPlayerType > 3))
                    {
                        strcpy(cTemp, DRAW_DIALOGBOX_SHOP22); // "(Warning!) only for male."
                        PutAlignedString(sX + 25, sX + 240, sY + 258, cTemp, 195, 25, 25);
                        PutAlignedString(sX + 26, sX + 241, sY + 258, cTemp, 195, 25, 25);
                        bFlagRedShown = true;
                    }
                    else if ((strstr(m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_cName, "(W)") != 0)
                        && (m_sPlayerType <= 3))
                    {
                        strcpy(cTemp, DRAW_DIALOGBOX_SHOP23); // "(Warning!) only for female."
                        PutAlignedString(sX + 25, sX + 240, sY + 258, cTemp, 195, 25, 25);
                        PutAlignedString(sX + 26, sX + 241, sY + 258, cTemp, 195, 25, 25);
                        bFlagRedShown = true;
                    }
                    break;

                case DEF_EQUIPPOS_NONE:
                    break;
            }

            if (m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sLevelLimit != 0)
            {
                strcpy(cTemp, DRAW_DIALOGBOX_SHOP24); // "Level"
                if (m_iLevel >= m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sLevelLimit)
                {
                    PutString(sX + 90, sY + 190, cTemp, Color(40, 10, 10));
                    PutString(sX + 91, sY + 190, cTemp, Color(40, 10, 10));
                    wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP25, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sLevelLimit);
                    PutString(sX + 140, sY + 190, cTemp, Color(45, 25, 25));// ": above %d"
                }
                else
                {
                    PutString(sX + 90, sY + 190, cTemp, Color(40, 10, 10));
                    PutString(sX + 91, sY + 190, cTemp, Color(40, 10, 10));
                    wsprintfA(cTemp, DRAW_DIALOGBOX_SHOP25, m_pItemForSaleList[m_stDialogBoxInfo[11].cMode - 1]->m_sLevelLimit);
                    PutString(sX + 140, sY + 190, cTemp, Color(125, 25, 25));// ": above %d"
                    if (bFlagRedShown == false)
                    {
                        strcpy(cTemp, DRAW_DIALOGBOX_SHOP26); // "(Warning!) Your level is too low for this item."
                        PutAlignedString(sX + 25, sX + 240, sY + 258, cTemp, 195, 25, 25);
                        PutAlignedString(sX + 25 + 1, sX + 240 + 1, sY + 258, cTemp, 195, 25, 25);
                        bFlagRedShown = true;
                    }
                }
            }

            m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + 156, sY + 219, 19, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + 170, sY + 219, 19, dwTime);
            PutString(sX + 123 - 35, sY + 237 - 10, DRAW_DIALOGBOX_SHOP27, Color(40, 10, 10)); // "Quantity:"
            PutString(sX + 124 - 35, sY + 237 - 10, DRAW_DIALOGBOX_SHOP27, Color(40, 10, 10));
            if (iGetTopDialogBoxIndex() == 11 && msZ != 0)
            {
                m_stDialogBoxInfo[11].sV3 = m_stDialogBoxInfo[11].sV3 + msZ / 60;
                m_stMCursor.sZ = 0;
            }
            if (m_stDialogBoxInfo[11].sV3 > (50 - _iGetTotalItemNum())) m_stDialogBoxInfo[11].sV3 = (50 - _iGetTotalItemNum());
            if (m_stDialogBoxInfo[11].sV3 < 1) m_stDialogBoxInfo[11].sV3 = 1;

            if (m_stDialogBoxInfo[11].sV3 >= 10)
            {
                ZeroMemory(cTemp, sizeof(cTemp));
                _itoa(m_stDialogBoxInfo[11].sV3, cTemp, 10);
                cTemp[1] = 0;
                PutString(sX - 35 + 186, sY - 10 + 237, cTemp, Color(40, 10, 10));
                PutString(sX - 35 + 187, sY - 10 + 237, cTemp, Color(40, 10, 10));
                ZeroMemory(cTemp, sizeof(cTemp));
                _itoa(m_stDialogBoxInfo[11].sV3, cTemp, 10);
                PutString(sX - 35 + 200, sY - 10 + 237, (cTemp + 1), Color(40, 10, 10));
                PutString(sX - 35 + 201, sY - 10 + 237, (cTemp + 1), Color(40, 10, 10));
            }
            else
            {
                PutString(sX - 35 + 186, sY - 10 + 237, "0", Color(40, 10, 10));
                PutString(sX - 35 + 187, sY - 10 + 237, "0", Color(40, 10, 10));
                ZeroMemory(cTemp, sizeof(cTemp));
                _itoa(m_stDialogBoxInfo[11].sV3, cTemp, 10);
                PutString(sX - 35 + 200, sY - 10 + 237, (cTemp), Color(40, 10, 10));
                PutString(sX - 35 + 201, sY - 10 + 237, (cTemp), Color(40, 10, 10));
            }
            m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + 156, sY + 244, 20, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + 170, sY + 244, 20, dwTime);

            if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 31);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 30);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;
    }
}


void CGame::DrawDialogBox_Skill(short msX, short msY, short msZ, char cLB)
{
    short sX, sY;
    int  i, iTotalLines, iPointerLoc;
    char cTemp[255], cTemp2[255];
    double d1, d2, d3;

    sX = m_stDialogBoxInfo[15].sX;
    sY = m_stDialogBoxInfo[15].sY;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0); // Normal Dialog
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 1); // Skill Dialog Title Bar

    switch (m_stDialogBoxInfo[15].cMode)
    {
        case 0:
            for (i = 0; i < 17; i++)
                if ((i < DEF_MAXSKILLTYPE) && (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView] != 0))
                {
                    ZeroMemory(cTemp, sizeof(cTemp));
                    wsprintfA(cTemp, "%s", m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_cName);
                    m_Misc.ReplaceString(cTemp, '-', ' ');
                    ZeroMemory(cTemp2, sizeof(cTemp2));
                    wsprintfA(cTemp2, "%3d%%", m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_iLevel);
                    if ((msX >= sX + 25) && (msX <= sX + 166) && (msY >= sY + 45 + i * 15) && (msY <= sY + 59 + i * 15))
                    {
                        if ((m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_bIsUseable == true)
                            && (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_iLevel != 0))
                        {
                            PutString(sX + 30, sY + 45 + i * 15, cTemp, Color(255, 255, 255));
                            PutString(sX + 183, sY + 45 + i * 15, cTemp2, Color(255, 255, 255));
                        }
                        else
                        {
                            PutString(sX + 30, sY + 45 + i * 15, cTemp, Color(5, 5, 5));
                            PutString(sX + 183, sY + 45 + i * 15, cTemp2, Color(5, 5, 5));
                        }
                    }
                    else
                    {
                        if ((m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_bIsUseable == true)
                            && (m_pSkillCfgList[i + m_stDialogBoxInfo[15].sView]->m_iLevel != 0))
                        {
                            PutString(sX + 30, sY + 45 + i * 15, cTemp, Color(34, 30, 120));
                            PutString(sX + 183, sY + 45 + i * 15, cTemp2, Color(34, 30, 120));
                        }
                        else
                        {
                            PutString(sX + 30, sY + 45 + i * 15, cTemp, Color(5, 5, 5));
                            PutString(sX + 183, sY + 45 + i * 15, cTemp2, Color(5, 5, 5));
                        }
                    }

                    if (m_iDownSkillIndex == (i + m_stDialogBoxInfo[15].sView))
                        m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(sX + 215, sY + 47 + i * 15, 21, 50, 50, 50, m_dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + 215, sY + 47 + i * 15, 20, m_dwTime);
                }

            iTotalLines = 0;
            for (i = 0; i < DEF_MAXSKILLTYPE; i++)
                if (m_pSkillCfgList[i] != 0) iTotalLines++;

            if (iTotalLines > 17)
            {
                d1 = (double)m_stDialogBoxInfo[15].sView;
                d2 = (double)(iTotalLines - 17);
                d3 = (274.0f * d1) / d2;
                iPointerLoc = (int)d3;
            }
            else iPointerLoc = 0;
            if (iTotalLines > 17)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 1);
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 242, sY + iPointerLoc + 35, 7);
            }

            if (cLB != 0 && iTotalLines > 17)
            {
                if ((iGetTopDialogBoxIndex() == 15))
                {
                    if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 30) && (msY <= sY + 320))
                    {
                        d1 = (double)(msY - (sY + 35));
                        d2 = (double)(iTotalLines - 17);
                        d3 = (d1 * d2) / 274.0f;
                        iPointerLoc = (int)(d3 + 0.5);
                        if (iPointerLoc > iTotalLines - 17) iPointerLoc = iTotalLines - 17;
                        m_stDialogBoxInfo[15].sView = iPointerLoc;
                    }
                }
            }
            else m_stDialogBoxInfo[15].bIsScrollSelected = false;
            if (iGetTopDialogBoxIndex() == 15 && msZ != 0)
            {
                if (msZ > 0) m_stDialogBoxInfo[15].sView--;
                if (msZ < 0) m_stDialogBoxInfo[15].sView++;
                m_stMCursor.sZ = 0;
            }
            if (m_stDialogBoxInfo[15].sView < 0) m_stDialogBoxInfo[15].sView = 0;
            if (iTotalLines > 17 && m_stDialogBoxInfo[15].sView > iTotalLines - 17) m_stDialogBoxInfo[15].sView = iTotalLines - 17;
            break;
    }
}

void CGame::DrawDialogBox_SkillDlg(short msX, short msY, short msZ, char cLB)
{
    int i, iLoc, iAdjX, iAdjY;
    char cTemp[120], cTemp2[120];
    short sX, sY, szX;
    char cStr1[64], cStr2[64], cStr3[64];
    uint64_t dwTime = m_dwCurTime;

    iAdjX = 5;
    iAdjY = 8;

    switch (m_stDialogBoxInfo[26].cMode)
    {
        case 1: // Alchemy waiting incredients
            if (m_stDialogBoxInfo[26].cStr[0] != 0)
            {
                sX = m_stDialogBoxInfo[26].sX + iAdjX + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0] * 2)));
                sY = m_stDialogBoxInfo[26].sY + iAdjY + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0] * 2)));
            }
            else
            {
                sX = m_stDialogBoxInfo[26].sX;
                sY = m_stDialogBoxInfo[26].sY;
            }

            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX, sY, 1, dwTime);

            if (m_stDialogBoxInfo[26].sV1 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV2 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV3 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV4 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV5 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV6 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);

            if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
                PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 16, 16, 30);
            else PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 6, 6, 20);

            break;

        case 2: // Alchemy, creating a potion
            if (m_stDialogBoxInfo[26].cStr[0] != 0)
            {
                sX = m_stDialogBoxInfo[26].sX + iAdjX + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0] * 2)));
                sY = m_stDialogBoxInfo[26].sY + iAdjY + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0] * 2)));
            }
            else
            {
                sX = m_stDialogBoxInfo[26].sX;
                sY = m_stDialogBoxInfo[26].sY;
            }
            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX, sY, 1, dwTime);

            if (m_stDialogBoxInfo[26].sV1 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV2 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV3 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV4 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV5 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV6 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutTransSprite50(sX + iAdjX + 55 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);

            PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Creating...", 20, 6, 6);


            if ((dwTime - m_stDialogBoxInfo[26].dwT1) > 1000)
            {
                m_stDialogBoxInfo[26].dwT1 = dwTime;
                m_stDialogBoxInfo[26].cStr[0]++;
            }

            if (m_stDialogBoxInfo[26].cStr[0] >= 5)
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_CREATEPORTION, 0, 0, 0, 0, 0);
                DisableDialogBox(26);
                PlaySound('E', 42, 0);
            }
            break;

        case 3: // Manuf: Choose what you want to create
            sX = m_stDialogBoxInfo[26].sX;
            sY = m_stDialogBoxInfo[26].sY;
            szX = m_stDialogBoxInfo[26].sSizeX;
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
            PutString(sX + iAdjX + 44, sY + iAdjY + 38, "Name", Color(0, 0, 0));
            PutString(sX + iAdjX + 171, sY + iAdjY + 38, "Max.Skill", Color(0, 0, 0));

            iLoc = 0;
            for (i = 0; i < 13; i++)
                if (m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView] != 0)
                {

                    ZeroMemory(cTemp, sizeof(cTemp));
                    GetItemName(m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView]->m_cName, 0, cStr1, cStr2, cStr3);
                    wsprintfA(cTemp, "%s", cStr1);
                    ZeroMemory(cTemp2, sizeof(cTemp2));
                    wsprintfA(cTemp2, "%d%%", m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView]->m_iMaxSkill);

                    if ((msX >= sX + 30) && (msX <= sX + 180) && (msY >= sY + iAdjY + 55 + iLoc * 15) && (msY <= sY + iAdjY + 69 + iLoc * 15))
                    {
                        PutString(sX + 30, sY + iAdjY + 55 + iLoc * 15, cTemp, Color(255, 255, 255));
                        PutString(sX + 190, sY + iAdjY + 55 + iLoc * 15, cTemp2, Color(255, 255, 255));
                    }
                    else
                    {
                        if (m_pDispBuildItemList[i + m_stDialogBoxInfo[26].sView]->m_bBuildEnabled == true)
                        {
                            PutString(sX + 30, sY + iAdjY + 55 + iLoc * 15, cTemp, Color(34, 30, 120));
                            PutString(sX + 190, sY + iAdjY + 55 + iLoc * 15, cTemp2, Color(34, 30, 120));
                        }
                        else
                        {
                            PutString(sX + 30, sY + iAdjY + 55 + iLoc * 15, cTemp, Color(45, 25, 25));
                            PutString(sX + 190, sY + iAdjY + 55 + iLoc * 15, cTemp2, Color(45, 25, 25));
                        }
                    }

                    iLoc++;
                }
            if ((m_stDialogBoxInfo[26].sView >= 1) && (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView - 1] != 0))
                m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + iAdjX + 225, sY + iAdjY + 210, 23, dwTime);
            else m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutTransSpriteRGB(sX + iAdjX + 225, sY + iAdjY + 210, 23, 5, 5, 5, dwTime);

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView + 13] != 0)
                m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutSpriteFast(sX + iAdjX + 225, sY + iAdjY + 230, 24, dwTime);
            else m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2]->PutTransSpriteRGB(sX + iAdjX + 225, sY + iAdjY + 230, 24, 5, 5, 5, dwTime);

            if ((cLB != 0) && (iGetTopDialogBoxIndex() == 26))
            {
                if ((msX >= sX + iAdjX + 225) && (msX <= sX + iAdjX + 245) && (msY >= sY + iAdjY + 210) && (msY <= sY + iAdjY + 230))
                {
                    m_stDialogBoxInfo[26].sView--;
                }

                if ((msX >= sX + iAdjX + 225) && (msX <= sX + iAdjX + 245) && (msY >= sY + iAdjY + 230) && (msY <= sY + iAdjY + 250))
                {
                    if (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView + 13] != 0)
                        m_stDialogBoxInfo[26].sView++;
                }
            }
            if ((msZ != 0) && (iGetTopDialogBoxIndex() == 26))
            {
                m_stDialogBoxInfo[26].sView = m_stDialogBoxInfo[26].sView - msZ / 60;
                m_stMCursor.sZ = 0;
            }
            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView + 12] == 0)
            {
                while (1)
                {
                    m_stDialogBoxInfo[26].sView--;
                    if (m_stDialogBoxInfo[26].sView < 1) break;
                    if (m_pDispBuildItemList[m_stDialogBoxInfo[26].sView + 12] != 0) break;
                }
            }
            if (m_stDialogBoxInfo[26].sView < 0) m_stDialogBoxInfo[26].sView = 0;

            PutAlignedString(sX, sX + m_stDialogBoxInfo[26].sSizeX, sY + 265, DRAW_DIALOGBOX_SKILLDLG2, 55, 25, 25);//" List of items which you can make with"
            PutAlignedString(sX, sX + m_stDialogBoxInfo[26].sSizeX, sY + 280, DRAW_DIALOGBOX_SKILLDLG3, 55, 25, 25);//"your current skill. The items you can"
            PutAlignedString(sX, sX + m_stDialogBoxInfo[26].sSizeX, sY + 295, DRAW_DIALOGBOX_SKILLDLG4, 55, 25, 25);//"make now with your current stuff will"
            PutAlignedString(sX, sX + m_stDialogBoxInfo[26].sSizeX, sY + 310, DRAW_DIALOGBOX_SKILLDLG5, 55, 25, 25);//"be displayed in blue. "
            PutAlignedString(sX, sX + m_stDialogBoxInfo[26].sSizeX, sY + 340, DRAW_DIALOGBOX_SKILLDLG6, 55, 25, 25);//"Select an item you want to manufacture."
            break;

        case 4: // Manuf: Waiting for incredients
            sX = m_stDialogBoxInfo[26].sX;
            sY = m_stDialogBoxInfo[26].sY;
            szX = m_stDialogBoxInfo[26].sSizeX;
            iAdjX = -1;
            iAdjY = -7;
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
                m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprFrame, dwTime);

            ZeroMemory(cTemp, sizeof(cTemp));
            GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cName, 0, cStr1, cStr2, cStr3);
            wsprintfA(cTemp, "%s", cStr1);
            PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55, cTemp, Color(255, 255, 255));

            wsprintfA(cTemp, DRAW_DIALOGBOX_SKILLDLG7 // "Skill level: %d/%d"
                , m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSkillLimit
                , m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iMaxSkill);
            PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55 + 2 * 15, cTemp, Color(45, 25, 25));
            PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55 + 3 * 15 + 5, DRAW_DIALOGBOX_SKILLDLG8, Color(45, 25, 25));//"Ingredients Needed:"

            iLoc = 4;
            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[1] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName1, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[1] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(150, 150, 150));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[2] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName2, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[2] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(150, 150, 150));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[3] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName3, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[3] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(150, 150, 150));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[4] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName4, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[4] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(150, 150, 150));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[5] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName5, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[5] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(150, 150, 150));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[6] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName6, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[6] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(150, 150, 150));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bBuildEnabled == true)
            {
                m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 55 + 180, 2, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 45 * 1 + 13, sY + iAdjY + 55 + 180, 2, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 45 * 2 + 13, sY + iAdjY + 55 + 180, 2, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 100 + 180, 2, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 45 * 1 + 13, sY + iAdjY + 100 + 180, 2, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 45 * 2 + 13, sY + iAdjY + 100 + 180, 2, dwTime);

                if (m_stDialogBoxInfo[26].sV1 != -1)
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 55 + 180,
                        m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

                if (m_stDialogBoxInfo[26].sV2 != -1)
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 * 1 + 30 + 13, sY + iAdjY + 55 + 180,
                        m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

                if (m_stDialogBoxInfo[26].sV3 != -1)
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 * 2 + 30 + 13, sY + iAdjY + 55 + 180,
                        m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

                if (m_stDialogBoxInfo[26].sV4 != -1)
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 100 + 180,
                        m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

                if (m_stDialogBoxInfo[26].sV5 != -1)
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 * 1 + 30 + 13, sY + iAdjY + 100 + 180,
                        m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

                if (m_stDialogBoxInfo[26].sV6 != -1)
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 * 2 + 30 + 13, sY + iAdjY + 100 + 180,
                        m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);

                PutAlignedString(sX, sX + szX, sY + iAdjY + 230 + 75, DRAW_DIALOGBOX_SKILLDLG15, 55, 25, 25);//" Click MANUFACTURE button after"
                PutAlignedString(sX, sX + szX, sY + iAdjY + 245 + 75, DRAW_DIALOGBOX_SKILLDLG16, 55, 25, 25);//"dragging ingredients in the blanks"
                PutAlignedString(sX, sX + szX, sY + iAdjY + 260 + 75, DRAW_DIALOGBOX_SKILLDLG17, 55, 25, 25);//"to manufacture above item."

                if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
                    PutString_SprFont(sX + iAdjX + 25, sY + iAdjY + 330 + 23, "Back", 6, 6, 20);
                else PutString_SprFont(sX + iAdjX + 25, sY + iAdjY + 330 + 23, "Back", 0, 0, 7);


                if ((msX >= sX + iAdjX + 160) && (msX <= sX + iAdjX + 255) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
                {
                    if (m_stDialogBoxInfo[26].cStr[4] == 1)
                        PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 + 23, "Manufacture", 6, 6, 20);
                    else PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 + 23, "Manufacture", 10, 10, 10);
                }
                else
                {
                    if (m_stDialogBoxInfo[26].cStr[4] == 1)
                        PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 + 23, "Manufacture", 0, 0, 7);
                    else PutString_SprFont(sX + iAdjX + 153, sY + iAdjY + 330 + 23, "Manufacture", 10, 10, 10);
                }
            }
            else
            {
                PutAlignedString(sX, sX + szX, sY + iAdjY + 200 + 75, DRAW_DIALOGBOX_SKILLDLG18, 55, 25, 25);//"There are not enough ingredients to"
                PutAlignedString(sX, sX + szX, sY + iAdjY + 215 + 75, DRAW_DIALOGBOX_SKILLDLG19, 55, 25, 25);//"manufacture. Needed materials are"
                PutAlignedString(sX, sX + szX, sY + iAdjY + 230 + 75, DRAW_DIALOGBOX_SKILLDLG20, 55, 25, 25);//"displayed in grey."
                if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
                    PutString_SprFont(sX + iAdjX + 25, sY + iAdjY + 330 + 23, "Back", 6, 6, 20);
                else PutString_SprFont(sX + iAdjX + 25, sY + iAdjY + 330 + 23, "Back", 0, 0, 7);
            }
            break;

        case 5: // Manuf: in progress
            sX = m_stDialogBoxInfo[26].sX;
            sY = m_stDialogBoxInfo[26].sY;
            iAdjX = -1;
            iAdjY = -7;

            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
                m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprFrame, dwTime);

            ZeroMemory(cTemp, sizeof(cTemp));
            GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cName, 0, cStr1, cStr2, cStr3);
            wsprintfA(cTemp, "%s", cStr1);
            PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55, cTemp, Color(255, 255, 255));

            wsprintfA(cTemp, DRAW_DIALOGBOX_SKILLDLG7 // "Skill level: %d/%d"
                , m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSkillLimit, m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iMaxSkill);//"½ºÅ³ ¼öÁØ: %d/%d"
            PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55 + 2 * 15, cTemp, Color(45, 25, 25));
            PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55 + 3 * 15 + 5, DRAW_DIALOGBOX_SKILLDLG8, Color(45, 25, 25));//"Ingredients Needed:"

            iLoc = 4;
            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[1] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName1, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[1] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(120, 120, 120));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[2] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName2, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[2] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(120, 120, 120));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[3] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName3, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[3] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(120, 120, 120));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[4] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName4, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[4] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(120, 120, 120));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[5] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName5, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[5] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(120, 120, 120));
                iLoc++;
            }

            if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iElementCount[6] != 0)
            {
                GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cElementName6, 0, cStr1, cStr2, cStr3);
                wsprintfA(cTemp, "%s", cStr1);
                if (m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_bElementFlag[6] == true)
                    PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(45, 25, 25));
                else PutString(sX + iAdjX + 44 + 20 + 60, sY + iAdjY + 55 + iLoc * 15 + 5, cTemp, Color(120, 120, 120));
                iLoc++;
            }

            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 55 + 180, 2, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 45 * 1 + 13, sY + iAdjY + 55 + 180, 2, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 45 * 2 + 13, sY + iAdjY + 55 + 180, 2, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 100 + 180, 2, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 45 * 1 + 13, sY + iAdjY + 100 + 180, 2, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutSpriteFast(sX + iAdjX + 55 + 30 + 45 * 2 + 13, sY + iAdjY + 100 + 180, 2, dwTime);

            if (m_stDialogBoxInfo[26].sV1 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 55 + 180,
                    m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV2 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 * 1 + 30 + 13, sY + iAdjY + 55 + 180,
                    m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV3 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 * 2 + 30 + 13, sY + iAdjY + 55 + 180,
                    m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV4 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 100 + 180,
                    m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV5 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 * 1 + 30 + 13, sY + iAdjY + 100 + 180,
                    m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV6 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + 45 * 2 + 30 + 13, sY + iAdjY + 100 + 180,
                    m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);

            PutString(sX + iAdjX + 33, sY + iAdjY + 230 + 75, DRAW_DIALOGBOX_SKILLDLG29, Color(55, 25, 25));//" Manufacturing the items...."
            PutString(sX + iAdjX + 33, sY + iAdjY + 245 + 75, DRAW_DIALOGBOX_SKILLDLG30, Color(55, 25, 25));//"Please wait until manufacture finishes."

            if ((dwTime - m_stDialogBoxInfo[26].dwT1) > 1000)
            {
                m_stDialogBoxInfo[26].dwT1 = dwTime;
                m_stDialogBoxInfo[26].cStr[1]++;
                if (m_stDialogBoxInfo[26].cStr[1] >= 7) m_stDialogBoxInfo[26].cStr[1] = 7;
            }

            if (m_stDialogBoxInfo[26].cStr[1] == 4)
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_BUILDITEM, 0, 0, 0, 0, m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cName);
                m_stDialogBoxInfo[26].cStr[1]++;
            }
            break;

        case 6: // Manuf: Done
            sX = m_stDialogBoxInfo[26].sX;
            sY = m_stDialogBoxInfo[26].sY;
            iAdjX = -1;
            iAdjY = -7;

            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 0);
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 8);
            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprH]->PutSpriteFast(sX + iAdjX + 62 + 5, sY + iAdjY + 84 + 17,
                m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_iSprFrame, dwTime);

            ZeroMemory(cTemp, sizeof(cTemp));
            GetItemName(m_pDispBuildItemList[m_stDialogBoxInfo[26].cStr[0]]->m_cName, 0, cStr1, cStr2, cStr3);

            wsprintfA(cTemp, "%s", cStr1);
            PutString(sX + iAdjX + 44 + 10 + 60, sY + iAdjY + 55, cTemp, Color(255, 255, 255));

            if (m_stDialogBoxInfo[26].cStr[2] == 1)
            {
                PutString(sX + iAdjX + 33 + 11, sY + iAdjY + 200 - 45, DRAW_DIALOGBOX_SKILLDLG31, Color(55, 25, 25));//" Success in manufacture!"

                if (m_stDialogBoxInfo[26].sV1 == DEF_ITEMTYPE_MATERIAL)
                {
                    wsprintfA(G_cTxt, DRAW_DIALOGBOX_SKILLDLG32, m_stDialogBoxInfo[26].cStr[3]);//"The purity of product is %d%%."
                    PutString(sX + iAdjX + 33 + 11, sY + iAdjY + 215 - 45, G_cTxt, Color(55, 25, 25));
                }
                else
                {
                    wsprintfA(G_cTxt, DRAW_DIALOGBOX_SKILLDLG33, (int)m_stDialogBoxInfo[26].cStr[3] + 100);//"The completion of product is %d%%."
                    PutString(sX + iAdjX + 33, sY + iAdjY + 215 - 45, G_cTxt, Color(55, 25, 25));
                }
            }
            else
            {
                PutString(sX + iAdjX + 33 + 11, sY + iAdjY + 200, DRAW_DIALOGBOX_SKILLDLG34, Color(55, 25, 25));//"Failed on manufacture."
            }

            if ((msX >= sX + iAdjX + 32) && (msX <= sX + iAdjX + 95) && (msY >= sY + iAdjY + 353) && (msY <= sY + iAdjY + 372))
                PutString_SprFont(sX + iAdjX + 35, sY + iAdjY + 330 + 23, "Back", 6, 6, 20);
            else PutString_SprFont(sX + iAdjX + 35, sY + iAdjY + 330 + 23, "Back", 0, 0, 7);
            break;


        case 7: // Crafting, wait for incredients
            if (m_stDialogBoxInfo[26].cStr[0] != 0)
            {
                sX = m_stDialogBoxInfo[26].sX + iAdjX + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0] * 2)));
                sY = m_stDialogBoxInfo[26].sY + iAdjY + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0] * 2)));
            }
            else
            {
                sX = m_stDialogBoxInfo[26].sX;
                sY = m_stDialogBoxInfo[26].sY;
            }
            m_pSprite[DEF_SPRID_INTERFACE_CRAFTING]->PutSpriteFast(sX, sY, 0, dwTime);

            if (m_stDialogBoxInfo[26].sV1 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV2 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 40 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV3 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV4 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV5 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 115 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);

            if (m_stDialogBoxInfo[26].sV6 != -1)
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 75 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                    m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);
            if ((msX >= sX + iAdjX + 60) && (msX <= sX + iAdjX + 153) && (msY >= sY + iAdjY + 175) && (msY <= sY + iAdjY + 195))
                PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 16, 16, 30);
            else PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Try Now!", 6, 6, 20);
            break;

        case 8: // Crafting in progress
            if (m_stDialogBoxInfo[26].cStr[0] != 0)
            {
                sX = m_stDialogBoxInfo[26].sX + iAdjX + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0] * 2)));
                sY = m_stDialogBoxInfo[26].sY + iAdjY + (m_stDialogBoxInfo[26].cStr[0] - (rand() % (m_stDialogBoxInfo[26].cStr[0] * 2)));
            }
            else
            {
                sX = m_stDialogBoxInfo[26].sX;
                sY = m_stDialogBoxInfo[26].sY;
            }
            m_pSprite[DEF_SPRID_INTERFACE_CRAFTING]->PutSpriteFast(sX, sY, 0, dwTime);

            if (m_stDialogBoxInfo[26].sV1 != -1)
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSprite]->PutSpriteFast(sX + iAdjX + 55 + (1 - (rand() % 3)) + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                        m_pItemList[m_stDialogBoxInfo[26].sV1]->m_sSpriteFrame, dwTime);
                if ((m_pItemList[m_stDialogBoxInfo[26].sV1]->m_cItemType == DEF_ITEMTYPE_EQUIP)
                    && (m_pItemList[m_stDialogBoxInfo[26].sV1]->m_cEquipPos == DEF_EQUIPPOS_NECK))
                    m_iContributionPrice = 10;
            }
            if (m_stDialogBoxInfo[26].sV2 != -1)
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 40 + (1 - (rand() % 3)),
                        m_pItemList[m_stDialogBoxInfo[26].sV2]->m_sSpriteFrame, dwTime);
                if ((m_pItemList[m_stDialogBoxInfo[26].sV2]->m_cItemType == DEF_ITEMTYPE_EQUIP)
                    && (m_pItemList[m_stDialogBoxInfo[26].sV2]->m_cEquipPos == DEF_EQUIPPOS_NECK))
                    m_iContributionPrice = 10;
            }
            if (m_stDialogBoxInfo[26].sV3 != -1)
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 55 + (1 - (rand() % 3)),
                        m_pItemList[m_stDialogBoxInfo[26].sV3]->m_sSpriteFrame, dwTime);
                if ((m_pItemList[m_stDialogBoxInfo[26].sV3]->m_cItemType == DEF_ITEMTYPE_EQUIP)
                    && (m_pItemList[m_stDialogBoxInfo[26].sV3]->m_cEquipPos == DEF_EQUIPPOS_NECK))
                    m_iContributionPrice = 10;
            }
            if (m_stDialogBoxInfo[26].sV4 != -1)
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                        m_pItemList[m_stDialogBoxInfo[26].sV4]->m_sSpriteFrame, dwTime);
                if ((m_pItemList[m_stDialogBoxInfo[26].sV4]->m_cItemType == DEF_ITEMTYPE_EQUIP)
                    && (m_pItemList[m_stDialogBoxInfo[26].sV4]->m_cEquipPos == DEF_EQUIPPOS_NECK))
                    m_iContributionPrice = 10;
            }
            if (m_stDialogBoxInfo[26].sV5 != -1)
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSprite]->PutSpriteFast(sX + iAdjX + 65 + 45 * 1 + (1 - (rand() % 3)), sY + iAdjY + 115 + (1 - (rand() % 3)),
                        m_pItemList[m_stDialogBoxInfo[26].sV5]->m_sSpriteFrame, dwTime);
                if ((m_pItemList[m_stDialogBoxInfo[26].sV5]->m_cItemType == DEF_ITEMTYPE_EQUIP)
                    && (m_pItemList[m_stDialogBoxInfo[26].sV5]->m_cEquipPos == DEF_EQUIPPOS_NECK))
                    m_iContributionPrice = 10;
            }
            if (m_stDialogBoxInfo[26].sV6 != -1)
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT +
                    m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSprite]->PutSpriteFast(sX + iAdjX + 75 + 45 * 2 + (1 - (rand() % 3)), sY + iAdjY + 100 + (1 - (rand() % 3)),
                        m_pItemList[m_stDialogBoxInfo[26].sV6]->m_sSpriteFrame, dwTime);
                if ((m_pItemList[m_stDialogBoxInfo[26].sV6]->m_cItemType == DEF_ITEMTYPE_EQUIP)
                    && (m_pItemList[m_stDialogBoxInfo[26].sV6]->m_cEquipPos == DEF_EQUIPPOS_NECK))
                    m_iContributionPrice = 10;
            }
            PutString_SprFont(sX + iAdjX + 60, sY + iAdjY + 175, "Creating...", 20, 6, 6);

            if ((dwTime - m_stDialogBoxInfo[26].dwT1) > 1000)
            {
                m_stDialogBoxInfo[26].dwT1 = dwTime;
                m_stDialogBoxInfo[26].cStr[1]++;
            }
            if (m_stDialogBoxInfo[26].cStr[1] >= 5)//m_pDispCraftItemList
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_CRAFTITEM, 0, 0, 0, 0, 0);
                DisableDialogBox(26);
                PlaySound('E', 42, 0);
            }
            break;
    }
}

void CGame::DrawDialogBox_SysMenu(short msX, short msY, char cLB)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[19].sX;
    sY = m_stDialogBoxInfo[19].sY;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 0);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 6);
    PutString(sX + 23, sY + 63, DRAW_DIALOGBOX_SYSMENU_DETAILLEVEL, Color(45, 25, 25));
    PutString(sX + 24, sY + 63, DRAW_DIALOGBOX_SYSMENU_DETAILLEVEL, Color(45, 25, 25));
    if (m_cDetailLevel == 0)
        PutString(sX + 121, sY + 63, DRAW_DIALOGBOX_SYSMENU_LOW, Color(255, 255, 255));
    else PutString(sX + 121, sY + 63, DRAW_DIALOGBOX_SYSMENU_LOW, Color(45, 25, 25));
    if (m_cDetailLevel == 1)
        PutString(sX + 153, sY + 63, DRAW_DIALOGBOX_SYSMENU_NORMAL, Color(255, 255, 255));
    else PutString(sX + 153, sY + 63, DRAW_DIALOGBOX_SYSMENU_NORMAL, Color(45, 25, 25));
    if (m_cDetailLevel == 2)
        PutString(sX + 205, sY + 63, DRAW_DIALOGBOX_SYSMENU_HIGH, Color(255, 255, 255));
    else PutString(sX + 205, sY + 63, DRAW_DIALOGBOX_SYSMENU_HIGH, Color(45, 25, 25));

    PutString(sX + 23, sY + 84, DRAW_DIALOGBOX_SYSMENU_SOUND, Color(45, 25, 25));
    PutString(sX + 24, sY + 84, DRAW_DIALOGBOX_SYSMENU_SOUND, Color(45, 25, 25));
    if (m_bSoundFlag)
    {
        if (m_bSoundStat) PutString(sX + 85, sY + 85, DRAW_DIALOGBOX_SYSMENU_ON, Color(255, 255, 255));
        else PutString(sX + 83, sY + 85, DRAW_DIALOGBOX_SYSMENU_OFF, Color(200, 200, 200));
    }
    else PutString(sX + 68, sY + 85, DRAW_DIALOGBOX_SYSMENU_DISABLED, Color(100, 100, 100));

    PutString(sX + 123, sY + 84, DRAW_DIALOGBOX_SYSMENU_MUSIC, Color(45, 25, 25));
    PutString(sX + 124, sY + 84, DRAW_DIALOGBOX_SYSMENU_MUSIC, Color(45, 25, 25));
    if (m_bSoundFlag)
    {
        if (m_bMusicStat) PutString(sX + 180, sY + 85, DRAW_DIALOGBOX_SYSMENU_ON, Color(255, 255, 255));
        else PutString(sX + 178, sY + 85, DRAW_DIALOGBOX_SYSMENU_OFF, Color(200, 200, 200));
    }
    else PutString(sX + 163, sY + 85, DRAW_DIALOGBOX_SYSMENU_DISABLED, Color(100, 100, 100));

    PutString(sX + 23, sY + 106, DRAW_DIALOGBOX_SYSMENU_WHISPER, Color(45, 25, 25));
    PutString(sX + 24, sY + 106, DRAW_DIALOGBOX_SYSMENU_WHISPER, Color(45, 25, 25));
    if (m_bWhisper) PutString(sX + 85, sY + 106, DRAW_DIALOGBOX_SYSMENU_ON, Color(255, 255, 255));
    else PutString(sX + 82, sY + 106, DRAW_DIALOGBOX_SYSMENU_OFF, Color(200, 200, 200));

    PutString(sX + 123, sY + 106, DRAW_DIALOGBOX_SYSMENU_SHOUT, Color(45, 25, 25));
    PutString(sX + 124, sY + 106, DRAW_DIALOGBOX_SYSMENU_SHOUT, Color(45, 25, 25));
    if (m_bShout) PutString(sX + 180, sY + 106, DRAW_DIALOGBOX_SYSMENU_ON, Color(255, 255, 255));
    else PutString(sX + 177, sY + 106, DRAW_DIALOGBOX_SYSMENU_OFF, Color(200, 200, 200));

    PutString(sX + 23, sY + 124, DRAW_DIALOGBOX_SYSMENU_SOUNDVOLUME, Color(45, 25, 25));
    PutString(sX + 24, sY + 124, DRAW_DIALOGBOX_SYSMENU_SOUNDVOLUME, Color(45, 25, 25));
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 130 + m_cSoundVolume, sY + 129, 8);

    PutString(sX + 23, sY + 141, DRAW_DIALOGBOX_SYSMENU_MUSICVOLUME, Color(45, 25, 25));
    PutString(sX + 24, sY + 141, DRAW_DIALOGBOX_SYSMENU_MUSICVOLUME, Color(45, 25, 25));
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX + 130 + m_cMusicVolume, sY + 145, 8);

    PutString(sX + 23, sY + 158, DRAW_DIALOGBOX_SYSMENU_TRANSPARENCY, Color(45, 25, 25));
    PutString(sX + 24, sY + 158, DRAW_DIALOGBOX_SYSMENU_TRANSPARENCY, Color(45, 25, 25));
    if (m_bDialogTrans) PutString(sX + 208, sY + 158, DRAW_DIALOGBOX_SYSMENU_ON, Color(255, 255, 255));
    else PutString(sX + 207, sY + 158, DRAW_DIALOGBOX_SYSMENU_OFF, Color(200, 200, 200));

    PutString(sX + 23, sY + 180, DRAW_DIALOGBOX_SYSMENU_GUIDEMAP, Color(45, 25, 25));
    PutString(sX + 24, sY + 180, DRAW_DIALOGBOX_SYSMENU_GUIDEMAP, Color(45, 25, 25));
    if (m_bIsDialogEnabled[9]) PutString(sX + 99, sY + 180, DRAW_DIALOGBOX_SYSMENU_ON, Color(255, 255, 255));
    else PutString(sX + 98, sY + 180, DRAW_DIALOGBOX_SYSMENU_OFF, Color(200, 200, 200));

    SYSTEMTIME SysTime;
    GetLocalTime(&SysTime);
    ZeroMemory(G_cTxt, sizeof(G_cTxt));
    wsprintfA(G_cTxt, "%d:%d:%d:%d:%d", SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
    PutString(sX + 23, sY + 204, G_cTxt, Color(45, 25, 25));
    PutString(sX + 24, sY + 204, G_cTxt, Color(45, 25, 25));

    //v2.172
#ifdef _DEBUG
    PutString(sX + 23, sY + 41, UPDATE_SCREEN_ON_SELECT_CHARACTER36, Color(45, 25, 25)); // "Test server"
    PutString(sX + 24, sY + 41, UPDATE_SCREEN_ON_SELECT_CHARACTER36, Color(45, 25, 25)); // "Test server"
#else

#ifdef DEF_EQUILIBRIUM_PROJECT // Server name: Equilibrium Project
    PutString(sX + 23, sY + 41, "Equilibrium Project", Color(45, 25, 25));
    PutString(sX + 24, sY + 41, "Equilibrium Project", Color(45, 25, 25));
#else

    if (strcmp(m_cWorldServerName, NAME_WORLDNAME1) == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME1, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME1, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS2") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME2, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME2, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS3") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME3, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME3, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS4") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME4, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME4, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS5") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME5, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME5, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS6") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME6, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME6, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS7") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME7, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME7, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS8") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME8, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME8, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS9") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME9, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME9, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS10") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME10, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME10, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS11") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME11, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME11, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS12") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME12, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME12, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS13") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME13, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME13, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS14") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME14, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME14, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS15") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME15, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME15, Color(45, 25, 25));
    }
    else if (strcmp(m_cWorldServerName, "WS16") == 0)
    {
        PutString(sX + 23, sY + 41, MSG_WORLDNAME16, Color(45, 25, 25));
        PutString(sX + 24, sY + 41, MSG_WORLDNAME16, Color(45, 25, 25));
    }
#endif
#endif

    if ((cLB != 0) && (iGetTopDialogBoxIndex() == 19))
        //  (msX >= sX + 120) && (msX <= sX + 242) && (msY >= sY +122) && (msY <= sY +138)
    {
        if ((msX >= sX + 127) && (msX <= sX + 238) && (msY >= sY + 122) && (msY <= sY + 138))
        {
            m_cSoundVolume = msX - (sX + 127);
            if (m_cSoundVolume > 100) m_cSoundVolume = 100;
            if (m_cSoundVolume < 0) m_cSoundVolume = 0;
        }
        if ((msX >= sX + 127) && (msX <= sX + 238) && (msY >= sY + 139) && (msY <= sY + 155))
        {
            m_cMusicVolume = msX - (sX + 127);
            if (m_cMusicVolume > 100) m_cMusicVolume = 100;
            if (m_cMusicVolume < 0) m_cMusicVolume = 0;
            if (m_bSoundFlag)
            {
                int iVol;
                iVol = (m_cMusicVolume - 100) * 20;
                if (iVol > 0) iVol = 0;
                if (iVol < -10000) iVol = -10000;
                m_pBGM.setVolume(m_cMusicVolume);
                m_pBGM.stop();
            }
        }
    }
    else m_stDialogBoxInfo[19].bIsScrollSelected = false;

    // Log-Out
    if (m_cLogOutCount == -1)
    {
        if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + 225, 9);
        else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + 225, 8);
    }
    else  //Continue
    {
        if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + 225, 7);
        else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + 225, 6);
    }
    // Restart
    if ((m_iHP <= 0) && (m_cRestartCount == -1))
    {
        if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 225) && (msY <= sY + 225 + DEF_BTNSZY))
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 225, 37);
        else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + 225, 36);
    }
}


void CGame::DrawDialogBox_CrusadeJob(short msX, short msY)
{
    short sX, sY;

    sX = m_stDialogBoxInfo[33].sX;
    sY = m_stDialogBoxInfo[33].sY;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);

    switch (m_stDialogBoxInfo[33].cMode)
    {
        case 1:
            PutAlignedString(sX + 24, sX + 246, sY + 45 + 20, DRAWDIALOGBOX_CRUSADEJOB1);
            PutAlignedString(sX + 24, sX + 246, sY + 60 + 20, DRAWDIALOGBOX_CRUSADEJOB2);
            PutAlignedString(sX + 24, sX + 246, sY + 75 + 20, DRAWDIALOGBOX_CRUSADEJOB3);
            PutAlignedString(sX + 24, sX + 246, sY + 90 + 20, DRAWDIALOGBOX_CRUSADEJOB4);

            if (m_bCitizen == true)
            {
                if (m_bAresden)
                {
                    if (m_iGuildRank == 0)
                    {
                        if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
                            PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB5, 255, 255, 255);//(Commander)"
                        else PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB5, 4, 0, 50);//(Commander)"
                    }
                    else
                    {
                        if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
                            PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB7, 255, 255, 255);//(Soldier)"
                        else PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB7, 4, 0, 50);//(Soldier)"
                        if (m_iGuildRank != -1)
                        {
                            if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
                                PutAlignedString(sX + 24, sX + 246, sY + 175, DRAWDIALOGBOX_CRUSADEJOB9, 255, 255, 255);//(Constructor)"
                            else PutAlignedString(sX + 24, sX + 246, sY + 175, DRAWDIALOGBOX_CRUSADEJOB9, 4, 0, 50);//(Constructor)"

                        }
                    }
                }
                else if (m_bAresden == false)
                {
                    if (m_iGuildRank == 0)
                    {
                        if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
                            PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB5, 255, 255, 255);//(Commander)"
                        else PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB5, 4, 0, 50);//(Commander)"
                    }
                    else
                    {
                        if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 150) && (msY < sY + 165))
                            PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB7, 255, 255, 255);//(Soldier)"
                        else PutAlignedString(sX + 24, sX + 246, sY + 150, DRAWDIALOGBOX_CRUSADEJOB7, 4, 0, 50);//(Soldier)"
                        if (m_iGuildRank != -1)
                        {
                            if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 175) && (msY < sY + 190))
                                PutAlignedString(sX + 24, sX + 246, sY + 175, DRAWDIALOGBOX_CRUSADEJOB9, 255, 255, 255);//(Constructor)"
                            else PutAlignedString(sX + 24, sX + 246, sY + 175, DRAWDIALOGBOX_CRUSADEJOB9, 4, 0, 50);//(Constructor)"
                        }
                    }
                }
            }

            PutAlignedString(sX + 24, sX + 246, sY + 290 - 40, DRAWDIALOGBOX_CRUSADEJOB10);
            PutAlignedString(sX + 24, sX + 246, sY + 305 - 40, DRAWDIALOGBOX_CRUSADEJOB17);

            if ((msX > sX + 210) && (msX < sX + 260) && (msY >= sY + 296) && (msY <= sY + 316))
                PutString_SprFont(sX + 50 + 160, sY + 296, "Help", 6, 6, 20);
            else PutString_SprFont(sX + 50 + 160, sY + 296, "Help", 0, 0, 7);
            break;

        case 2:
            PutAlignedString(sX + 24, sX + 246, sY + 90 + 20, DRAWDIALOGBOX_CRUSADEJOB18);
            switch (m_iCrusadeDuty)
            {
                case 1: PutAlignedString(sX + 24, sX + 246, sY + 125, DRAWDIALOGBOX_CRUSADEJOB19); break;//"(Soldier)
                case 2: PutAlignedString(sX + 24, sX + 246, sY + 125, DRAWDIALOGBOX_CRUSADEJOB20); break;//"(Constructor)
                case 3: PutAlignedString(sX + 24, sX + 246, sY + 125, DRAWDIALOGBOX_CRUSADEJOB21); break;//"(Commander)
            }

            PutAlignedString(sX + 24, sX + 246, sY + 145, DRAWDIALOGBOX_CRUSADEJOB22);
            if ((msX > sX + 24) && (msX < sX + 246) && (msY > sY + 160) && (msY < sY + 175))
                PutAlignedString(sX + 24, sX + 246, sY + 160, DRAWDIALOGBOX_CRUSADEJOB23, 255, 255, 255);
            else PutAlignedString(sX + 24, sX + 246, sY + 160, DRAWDIALOGBOX_CRUSADEJOB23, 4, 0, 50);

            PutAlignedString(sX + 24, sX + 246, sY + 175, DRAWDIALOGBOX_CRUSADEJOB25);
            PutAlignedString(sX + 24, sX + 246, sY + 190, DRAWDIALOGBOX_CRUSADEJOB26);

            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;
    }
}


void CGame::DrawDialogBox_Commander(int msX, int msY)
{
    short sX, sY, szX, szY, MapSzX, MapSzY;
    uint64_t dwTime = G_dwGlobalTime;
    double dV1, dV2, dV3;
    int i, tX, tY;
    sX = m_stDialogBoxInfo[36].sX;
    sY = m_stDialogBoxInfo[36].sY;
    szX = m_stDialogBoxInfo[36].sSizeX;
    if ((dwTime - m_dwCommanderCommandRequestedTime) > 1000 * 10)
    {
        _RequestMapStatus("middleland", 3);
        _RequestMapStatus("middleland", 1);
        m_dwCommanderCommandRequestedTime = dwTime;
    }

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY - 5, 0, false, m_bDialogTrans); // Main image
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 15, false, m_bDialogTrans);

    switch (m_stDialogBoxInfo[36].cMode)
    {
        case 0: // Main dlg
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 3, dwTime); // btn
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 1, dwTime); // btn
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 340, 2, dwTime); // btn
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 340, 30, dwTime); // Btn TP
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime); // btn ?
            //PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER1);//"Middleland warfare building structure situation"
            PutAlignedString(sX, sX + szX, sY + 37, DRAW_DIALOGBOX_COMMANDER1);//"Middleland warfare building structure situation"

            if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 17, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER2, 255, 255, 255);//"Middleland teleport position set"
            }
            else if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 15, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER3, 255, 255, 255);//"Teleport to the selected area"
            }
            else if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 46 + 100)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 340, 16, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER4, 255, 255, 255);//"Recall warfare units"
            }
            else if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 46 + 150)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 340, 24, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER5, 255, 255, 255);//"Middleland construction building set"
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER6, 255, 255, 255);//"Commander's duty help"
            }
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, m_bDialogTrans);// Map
            break;

        case 1: // Set TP
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime); //btn <-
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);  //btn ?
            PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER7); // "Click and select the teleport location."

            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER8, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER9, 255, 255, 255);
            }
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, m_bDialogTrans);

            if ((msX >= sX + 15) && (msX <= sX + 15 + 278)
                && (msY >= sY + 60) && (msY <= sY + 60 + 272)) // shows TP posit on map following the mouse
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, msX, msY, 42, false, true);
            }
            break;

        case 2: // Use TP
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 1, dwTime);       // Btn TP
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime); // Btn <-
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);  // Btn ?
            PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER10); // "Teleport to the selected area"

            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 15, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER11, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER12, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER13, 255, 255, 255);
            }
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, m_bDialogTrans);
            break;

        case 3: // Choose summon
            if ((m_bCitizen == true) && (m_bAresden == true))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 6, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 5, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 7, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 35, dwTime);
            }
            else if ((m_bCitizen == true) && (m_bAresden == false))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 9, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 8, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 7, dwTime);
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 35, dwTime);
            }
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);

            PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER14); // "Recall warfare units"

            wsprintfA(G_cTxt, "%s %d", DRAW_DIALOGBOX_COMMANDER15, m_iConstructionPoint);
            PutAlignedString(sX, sX + 323, sY + 190, G_cTxt);

            if ((m_bCitizen == true) && (m_bAresden == true))
            {
                if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 3000)
                    {
                        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 11, dwTime);
                    }
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER16, 255, 255, 255);//"¹(Battle Golem)"
                    PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER17, 255, 255, 255);//"3000"
                }
                else if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 2000)
                    {
                        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 10, dwTime);
                    }
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER18, 255, 255, 255);//"(Temple Knight)"
                    PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER19, 255, 255, 255);//"2000"
                }
                else if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 1000)
                    {
                        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 12, dwTime);
                    }
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER20, 255, 255, 255);//"(Light War Beetle)"
                    PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER21, 255, 255, 255);//" 1000"
                }
                else if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 5000)
                    {
                        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 29, dwTime);
                    }
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER22, 255, 255, 255);//"(Catapult)"
                    PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER23, 255, 255, 255);// 1500"
                }
                else if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 140) && (msY < sY + 160))
                {
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER24, 255, 255, 255);
                }
                else if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 160) && (msY < sY + 175))
                {
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER25, 255, 255, 255);
                }
                else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                    && (msY >= sY + 340) && (msY <= sY + 340 + 52))
                {
                    m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER26, 255, 255, 255);
                }
                else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                    && (msY >= sY + 340) && (msY <= sY + 340 + 52))
                {
                    m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER27, 255, 255, 255); //"Warfare units recall related help"
                }
            }
            else if ((m_bCitizen == true) && (m_bAresden == false))
            {
                if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 3000)
                    {
                        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 14, dwTime);
                    }
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER28, 255, 255, 255);//"(God's Hand Knight Cavalry)"
                    PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER29, 255, 255, 255);//"3000"
                }
                else if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45)
                    && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 2000)
                    {
                        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 13, dwTime);
                    }
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER30, 255, 255, 255);//"°(God's Hand Knight)"
                    PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER31, 255, 255, 255);//"2000"
                }
                else if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 1000)
                    {
                        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 12, dwTime);
                    }
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER32, 255, 255, 255);//"(Light War Beetle)"
                    PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER33, 255, 255, 255);//" 1000"
                }
                else if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
                {
                    if (m_iConstructionPoint >= 5000)
                    {
                        m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 29, dwTime);
                    }
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER34, 255, 255, 255);//"(Catapult)"
                    PutString2(msX + 20, msY + 50, DRAW_DIALOGBOX_COMMANDER35, 255, 255, 255);//" 1500"
                }
                else if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 140) && (msY < sY + 160))
                {
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER36, 255, 255, 255);
                }
                else if ((msX >= sX + 20) && (msX <= sX + 380) && (msY > sY + 160) && (msY < sY + 175))
                {
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER37, 255, 255, 255);
                }
                else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                    && (msY >= sY + 340) && (msY <= sY + 340 + 52))
                {
                    m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER38, 255, 255, 255);

                }
                else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                    && (msY >= sY + 340) && (msY <= sY + 340 + 52))
                {
                    m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
                    PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER39, 255, 255, 255);
                }
            }
            PutAlignedString(sX, sX + 323, sY + 80, DRAW_DIALOGBOX_COMMANDER40);
            PutAlignedString(sX, sX + 323, sY + 95, DRAW_DIALOGBOX_COMMANDER41);
            PutAlignedString(sX, sX + 323, sY + 110, DRAW_DIALOGBOX_COMMANDER42);

            switch (m_stDialogBoxInfo[36].sV1)
            {
                case 0:
                    PutAlignedString(sX, sX + 323, sY + 140, DRAW_DIALOGBOX_COMMANDER43, 255, 255, 255);//"Guard Mode"
                    PutAlignedString(sX, sX + 323, sY + 160, DRAW_DIALOGBOX_COMMANDER44, 4, 0, 50);//"Hold Mode"
                    break;
                case 1:
                    PutAlignedString(sX, sX + 323, sY + 140, DRAW_DIALOGBOX_COMMANDER43, 4, 0, 50);//"Guard Mode"
                    PutAlignedString(sX, sX + 323, sY + 160, DRAW_DIALOGBOX_COMMANDER44, 255, 255, 255);//"Hold Mode"
                    break;
            }
            break;

        case 4: // Set Construction point
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);
            PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_COMMANDER47); // "Select the construction area and click."

            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER48, 255, 255, 255); // "Returns to commander's main menu"
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_COMMANDER49, 255, 255, 255); // "Construction area set related help"
            }
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21);
            if ((msX >= sX + 15) && (msX <= sX + 15 + 278)
                && (msY >= sY + 60) && (msY <= sY + 60 + 272)) // shows posit on map following the mouse
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, msX, msY, 41, false, true);
            }
            break;
    }

    switch (m_stDialogBoxInfo[36].cMode)
    {
        case 0: // Main
        case 1: // Set TP
        case 2: // Use TP
        case 4: // Set construc
            szX = 0;
            szY = 0;
            MapSzX = 0;
            MapSzY = 0;
            if (strcmp(m_cStatusMapName, "aresden") == 0)
            {
                szX = 250;
                szY = 250;
            }
            else if (strcmp(m_cStatusMapName, "elvine") == 0)
            {
                szX = 250;
                szY = 250;
            }
            else if (strcmp(m_cStatusMapName, "middleland") == 0)
            {
                szX = 279;
                szY = 280;
                MapSzX = 524;
                MapSzY = 524;
            }
            if (szX != 0)
            {
                for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
                    if (m_stCrusadeStructureInfo[i].cType != 0)
                    {
                        dV1 = (double)MapSzX;
                        dV2 = (double)m_stCrusadeStructureInfo[i].sX;
                        dV3 = (dV2 * (double)szX) / dV1;
                        tX = (int)dV3;
                        dV1 = (double)MapSzY;
                        dV2 = (double)m_stCrusadeStructureInfo[i].sY;
                        dV3 = (dV2 * (double)szY) / dV1;
                        tY = (int)dV3;
                        switch (m_stCrusadeStructureInfo[i].cType)
                        {
                            case 38:
                                if (m_stCrusadeStructureInfo[i].cSide == 1)
                                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 39, false, true); // Base
                                else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 37, false, true);
                                break;
                            case 36:
                            case 37:
                            case 39:
                                if (m_stCrusadeStructureInfo[i].cSide == 1)
                                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 38, false, true); // Base
                                else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 36, false, true);
                                break;
                            case 42:
                                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 40); // ManaStone
                                break;
                        }
                    }
                if (m_iTeleportLocX != -1)
                {
                    dV1 = (double)MapSzX;
                    dV2 = (double)m_iTeleportLocX;
                    dV3 = (dV2 * (double)szX) / dV1;
                    tX = (int)dV3;
                    dV1 = (double)MapSzY;
                    dV2 = (double)m_iTeleportLocY;
                    dV3 = (dV2 * (double)szY) / dV1;
                    tY = (int)dV3;
                    if ((m_stDialogBoxInfo[36].cMode == 1) && (tY >= 30) && (tY <= 494)) // Place the TP
                    {
                        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 42, false, true); //TP
                    }
                    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 42, false, true); //TP
                }
                if ((m_stDialogBoxInfo[36].cMode != 2) && (m_iConstructLocX != -1))
                {
                    dV1 = (double)MapSzX;
                    dV2 = (double)m_iConstructLocX;
                    dV3 = (dV2 * (double)szX) / dV1;
                    tX = (int)dV3;
                    dV1 = (double)MapSzY;
                    dV2 = (double)m_iConstructLocY;
                    dV3 = (dV2 * (double)szY) / dV1;
                    tY = (int)dV3;
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 41, false, true); // Contr pt
                }
                if (strcmp(m_cMapName, "middleland") == 0)
                {
                    dV1 = (double)MapSzX;//m_pMapData->m_sMapSizeX;
                    dV2 = (double)m_sPlayerX;
                    dV3 = (dV2 * (double)szX) / dV1;
                    tX = (int)dV3;
                    dV1 = (double)MapSzY;//m_pMapData->m_sMapSizeY;
                    dV2 = (double)m_sPlayerY;
                    dV3 = (dV2 * (double)szY) / dV1;
                    tY = (int)dV3;
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 43); // Player place
                }
            }
            if (m_stDialogBoxInfo[36].cMode != 3)
            {
                if ((msX >= sX + 15) && (msX <= sX + 15 + 278)
                    && (msY >= sY + 60) && (msY <= sY + 60 + 272)) // Draw mouse coordinates
                {
                    dV1 = (double)(msX - (sX + 15));
                    dV2 = (double)MapSzX;//(752.0f);
                    dV3 = (dV2 * dV1) / szX;//280.0f;
                    tX = (int)dV3;
                    dV1 = (double)(msY - (sY + 60));
                    dV2 = (double)MapSzX;//(680.0f);
                    dV3 = (dV2 * dV1) / szY;//253.0f;
                    tY = (int)dV3;
                    if (tX < 30) tX = 30;
                    if (tY < 30) tY = 30;
                    if (tX > MapSzX - 30) tX = MapSzX - 30;
                    if (tY > MapSzY - 30) tY = MapSzY - 30;
                    wsprintfA(G_cTxt, "%d,%d", tX, tY);
                    PutString_SprFont3(msX + 10, msY - 10, G_cTxt, m_wR[13] * 4, m_wG[13] * 4, m_wB[13] * 4, false, 2);
                }
            }
            break;
    }
}

void CGame::DrawDialogBox_Constructor(int msX, int msY)
{
    short sX, sY, szX, szY, MapSzX, MapSzY;
    uint64_t dwTime = G_dwGlobalTime;
    double dV1, dV2, dV3;
    int tX, tY;
    char cMapName[12];
    sX = m_stDialogBoxInfo[37].sX;
    sY = m_stDialogBoxInfo[37].sY;
    szX = m_stDialogBoxInfo[37].sSizeX;
    if ((dwTime - m_dwCommanderCommandRequestedTime) > 1000 * 10)
    {
        _RequestMapStatus("middleland", 1);
        m_dwCommanderCommandRequestedTime = dwTime;
    }

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY - 5, 0, false, m_bDialogTrans); // Main image
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 16, false, m_bDialogTrans);

    switch (m_stDialogBoxInfo[37].cMode)
    {
        case 0: // Main dlg
            if (m_iConstructLocX != -1)
            {
                ZeroMemory(cMapName, sizeof(cMapName));
                GetOfficialMapName(m_cConstructMapName, cMapName);
                wsprintfA(G_cTxt, DRAW_DIALOGBOX_CONSTRUCTOR1, cMapName, m_iConstructLocX, m_iConstructLocY);
                PutAlignedString(sX, sX + szX, sY + 40, G_cTxt);
            }
            else PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_CONSTRUCTOR2); //"Construction unavailable: Unable to construct"
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, m_bDialogTrans); // Map

            if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 24, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 30, dwTime);

            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 15, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 1, dwTime);

            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);

            if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR3, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50)
                && (msY >= sY + 322) && (msY <= sY + 322 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR4, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 322) && (msY <= sY + 322 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR5, 255, 255, 255);
            }
            break;

        case 1: // Select building
            PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_CONSTRUCTOR6); //"Select war building"
            PutAlignedString(sX, sX + 323, sY + 80, DRAW_DIALOGBOX_CONSTRUCTOR7); //"Constructs the war building here."
            PutAlignedString(sX, sX + 323, sY + 95, DRAW_DIALOGBOX_CONSTRUCTOR8); //"Press the building icon and"
            PutAlignedString(sX, sX + 323, sY + 110, DRAW_DIALOGBOX_CONSTRUCTOR9); //"the base will be formed and slowly finished"
            PutAlignedString(sX, sX + 323, sY + 125, DRAW_DIALOGBOX_CONSTRUCTOR10);//"Attack the building with Pickaxe."
            PutAlignedString(sX, sX + 323, sY + 140, DRAW_DIALOGBOX_CONSTRUCTOR11);//"Building is not activated"
            PutAlignedString(sX, sX + 323, sY + 155, DRAW_DIALOGBOX_CONSTRUCTOR12);//"while constructing."

            if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 27, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 220, 33, dwTime);

            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 28, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 220, 34, dwTime);

            if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 26, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100, sY + 220, 32, dwTime);

            if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 25, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150, sY + 220, 31, dwTime);

            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 322, 19, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 322, 20, dwTime);

            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 322, 18, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 322, 4, dwTime);

            if ((msX >= sX + 20) && (msX <= sX + 20 + 46) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR13, 255, 255, 255);//"(Mana Collector)"
            }
            else if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 50 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR14, 255, 255, 255);//"(Detector)"
            }
            else if ((msX >= sX + 20 + 100) && (msX <= sX + 20 + 100 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR15, 255, 255, 255);//"(Arrow Guard Tower)"
            }
            else if ((msX >= sX + 20 + 150) && (msX <= sX + 20 + 150 + 45) && (msY >= sY + 220) && (msY <= sY + 220 + 50))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR16, 255, 255, 255);//(Cannon Guard Tower)"
            }
            else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR17, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74) && (msY >= sY + 322) && (msY <= sY + 322 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR18, 255, 255, 255);
            }
            break;

        case 2: // Teleport
            PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_CONSTRUCTOR19); //"Teleport to position that commander pointed"
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, m_bDialogTrans); // map

            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 15, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 50, sY + 340, 1, dwTime);

            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 19, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 100 + 74, sY + 340, 20, dwTime);

            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);

            if ((msX >= sX + 20 + 50) && (msX <= sX + 20 + 46 + 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR20, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR21, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_CONSTRUCTOR22, 255, 255, 255);
            }
            break;
    }

    switch (m_stDialogBoxInfo[37].cMode)
    {
        case 0: // Main dlg
        case 2: // TP
            szX = 0;
            szY = 0;
            MapSzX = 0;
            MapSzY = 0;
            if (strcmp(m_cStatusMapName, "aresden") == 0)
            {
                szX = 250;
                szY = 250;
            }
            else if (strcmp(m_cStatusMapName, "elvine") == 0)
            {
                szX = 250;
                szY = 250;
            }
            else if (strcmp(m_cStatusMapName, "middleland") == 0)
            {
                szX = 279;
                szY = 280;
                MapSzX = 524;
                MapSzY = 524;
            }
            if (szX != 0)
            {
                for (int i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
                    if (m_stCrusadeStructureInfo[i].cType == 42)
                    {
                        dV1 = (double)MapSzX;
                        dV2 = (double)m_stCrusadeStructureInfo[i].sX;
                        dV3 = (dV2 * (double)szX) / dV1;
                        tX = (int)dV3;
                        dV1 = (double)MapSzY;
                        dV2 = (double)m_stCrusadeStructureInfo[i].sY;
                        dV3 = (dV2 * (double)szY) / dV1;
                        tY = (int)dV3;
                        switch (m_stCrusadeStructureInfo[i].cType)
                        {
                            case 42:
                                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 40); // ManaStone
                                break;
                        }
                    }
                if (m_iTeleportLocX != -1)
                {
                    dV1 = (double)MapSzX;
                    dV2 = (double)m_iTeleportLocX;
                    dV3 = (dV2 * (double)szX) / dV1;
                    tX = (int)dV3;
                    dV1 = (double)MapSzY;
                    dV2 = (double)m_iTeleportLocY;
                    dV3 = (dV2 * (double)szY) / dV1;
                    tY = (int)dV3;
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 42, false, true); //TP
                }
                if ((m_stDialogBoxInfo[37].cMode != 2) && (m_iConstructLocX != -1))
                {
                    dV1 = (double)MapSzX;
                    dV2 = (double)m_iConstructLocX;
                    dV3 = (dV2 * (double)szX) / dV1;
                    tX = (int)dV3;
                    dV1 = (double)MapSzY;
                    dV2 = (double)m_iConstructLocY;
                    dV3 = (dV2 * (double)szY) / dV1;
                    tY = (int)dV3;
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 41, false, true); // Contr pt
                }
                if (strcmp(m_cMapName, "middleland") == 0)
                {
                    dV1 = (double)MapSzX;//m_pMapData->m_sMapSizeX;
                    dV2 = (double)m_sPlayerX;
                    dV3 = (dV2 * (double)szX) / dV1;
                    tX = (int)dV3;
                    dV1 = (double)MapSzY;//m_pMapData->m_sMapSizeY;
                    dV2 = (double)m_sPlayerY;
                    dV3 = (dV2 * (double)szY) / dV1;
                    tY = (int)dV3;
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 43); // Player place
                }
            }
            if ((msX >= sX + 15) && (msX <= sX + 15 + 278)
                && (msY >= sY + 60) && (msY <= sY + 60 + 272))  // Draw mouse coordinates
            {
                dV1 = (double)(msX - (sX + 15));
                dV2 = (double)MapSzX;//(752.0f);
                dV3 = (dV2 * dV1) / szX;//280.0f;
                tX = (int)dV3;
                dV1 = (double)(msY - (sY + 60));
                dV2 = (double)MapSzX;//(680.0f);
                dV3 = (dV2 * dV1) / szY;//253.0f;
                tY = (int)dV3;
                if (tX < 30) tX = 30;
                if (tY < 30) tY = 30;
                if (tX > MapSzX - 30) tX = MapSzX - 30;
                if (tY > MapSzY - 30) tY = MapSzY - 30;
                wsprintfA(G_cTxt, "%d,%d", tX, tY);
                PutString_SprFont3(msX + 10, msY - 10, G_cTxt, m_wR[13] * 4, m_wG[13] * 4, m_wB[13] * 4, false, 2);
            }
            break;
    }
}

void CGame::DrawDialogBox_Soldier(int msX, int msY)
{
    short sX, sY, szX, szY, MapSzX, MapSzY;
    uint64_t dwTime = G_dwGlobalTime;
    char cMapName[120];
    double dV1, dV2, dV3;
    int tX, tY;
    sX = m_stDialogBoxInfo[38].sX;
    sY = m_stDialogBoxInfo[38].sY;
    szX = m_stDialogBoxInfo[38].sSizeX;
    if ((dwTime - m_dwCommanderCommandRequestedTime) > 1000 * 10)
    {
        _RequestMapStatus("middleland", 1);
        m_dwCommanderCommandRequestedTime = dwTime;
    }

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY - 5, 0, false, m_bDialogTrans);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX, sY, 21, false, m_bDialogTrans);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 17, false, m_bDialogTrans); // Crusade Soldier Menu Text

    switch (m_stDialogBoxInfo[38].cMode)
    {
        case 0: // Main dlg, Map
            if (m_iTeleportLocX != -1)
            {
                ZeroMemory(cMapName, sizeof(cMapName));
                GetOfficialMapName(m_cTeleportMapName, cMapName);
                wsprintfA(G_cTxt, DRAW_DIALOGBOX_SOLDIER1, cMapName, m_iTeleportLocX, m_iTeleportLocY);
                PutAlignedString(sX, sX + szX, sY + 40, G_cTxt);					// "Teleport position: %s near %d, %d"
            }
            else PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_SOLDIER2); //"Teleport position is not set."

            if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 15, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 1, dwTime);

            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);

            if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER3, 255, 255, 255); // "Teleport to position that commander pointed"
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER4, 255, 255, 255); // "Help for soldier"
            }
            break;

        case 1: // TP now
            PutAlignedString(sX, sX + szX, sY + 40, DRAW_DIALOGBOX_SOLDIER5); // "Teleport to position that commander pointed"
            if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 15, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20, sY + 340, 1, dwTime);

            if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74 - 50, sY + 340, 19, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74 - 50, sY + 340, 20, dwTime);

            if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 18, dwTime);
            }
            else m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE]->PutSpriteFast(sX + 20 + 150 + 74, sY + 340, 4, dwTime);

            if ((msX >= sX + 20) && (msX <= sX + 20 + 46)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER6, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74 - 50) && (msX <= sX + 20 + 46 + 150 + 74 - 50)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER7, 255, 255, 255);
            }
            else if ((msX >= sX + 20 + 150 + 74) && (msX <= sX + 20 + 46 + 150 + 74)
                && (msY >= sY + 340) && (msY <= sY + 340 + 52))
            {
                PutString2(msX + 20, msY + 35, DRAW_DIALOGBOX_SOLDIER8, 255, 255, 255);//"Help for teleport"
            }
            break;
    }

    switch (m_stDialogBoxInfo[38].cMode)
    {
        case 0: // Main
        case 1: // TP
            szX = 0;
            szY = 0;
            MapSzX = 0;
            MapSzY = 0;
            if (strcmp(m_cStatusMapName, "aresden") == 0)
            {
                szX = 250;
                szY = 250;
            }
            else if (strcmp(m_cStatusMapName, "elvine") == 0)
            {
                szX = 250;
                szY = 250;
            }
            else if (strcmp(m_cStatusMapName, "middleland") == 0)
            {
                szX = 279;
                szY = 280;	  // Fix for ML
                MapSzX = 524; // Fix for ML
                MapSzY = 524; // Fix for ML
            }
            if (szX != 0)
            {
                for (int i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
                    if (m_stCrusadeStructureInfo[i].cType == 42)
                    {
                        dV1 = (double)MapSzX;
                        dV2 = (double)m_stCrusadeStructureInfo[i].sX;
                        dV3 = (dV2 * (double)szX) / dV1;
                        tX = (int)dV3;
                        dV1 = (double)MapSzY;
                        dV2 = (double)m_stCrusadeStructureInfo[i].sY;
                        dV3 = (dV2 * (double)szY) / dV1;
                        tY = (int)dV3;
                        switch (m_stCrusadeStructureInfo[i].cType)
                        {
                            case 42:
                                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 40); // ManaStone
                                break;
                        }
                    }
                if (m_iTeleportLocX != -1)
                {
                    dV1 = (double)MapSzX;
                    dV2 = (double)m_iTeleportLocX;
                    dV3 = (dV2 * (double)szX) / dV1;
                    tX = (int)dV3;
                    dV1 = (double)MapSzY;
                    dV2 = (double)m_iTeleportLocY;
                    dV3 = (dV2 * (double)szY) / dV1;
                    tY = (int)dV3;
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 42, false, true); //TP
                }
                if (strcmp(m_cMapName, "middleland") == 0)
                {
                    dV1 = (double)MapSzX;//m_pMapData->m_sMapSizeX;
                    dV2 = (double)m_sPlayerX;
                    dV3 = (dV2 * (double)szX) / dV1;
                    tX = (int)dV3;
                    dV1 = (double)MapSzY;//m_pMapData->m_sMapSizeY;
                    dV2 = (double)m_sPlayerY;
                    dV3 = (dV2 * (double)szY) / dV1;
                    tY = (int)dV3;
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, sX + tX + 15, sY + tY + 60, 43); // Player place
                }
            }
            if ((msX >= sX + 15) && (msX <= sX + 15 + 278)
                && (msY >= sY + 60) && (msY <= sY + 60 + 272))  // Draw mouse coordinates
            {
                dV1 = (double)(msX - (sX + 15));
                dV2 = (double)MapSzX;//(752.0f);
                dV3 = (dV2 * dV1) / szX;//280.0f;
                tX = (int)dV3;
                dV1 = (double)(msY - (sY + 60));
                dV2 = (double)MapSzX;//(680.0f);
                dV3 = (dV2 * dV1) / szY;//253.0f;
                tY = (int)dV3;
                if (tX < 30) tX = 30;
                if (tY < 30) tY = 30;
                if (tX > MapSzX - 30) tX = MapSzX - 30;
                if (tY > MapSzY - 30) tY = MapSzY - 30;
                wsprintfA(G_cTxt, "%d,%d", tX, tY);
                PutString_SprFont3(msX + 10, msY - 10, G_cTxt, m_wR[13] * 4, m_wG[13] * 4, m_wB[13] * 4, false, 2);
            }
            break;
    }
}


void CGame::DrawDialogBox_Help(int msX, int msY)
{
    short sX, sY, szX;

    sX = m_stDialogBoxInfo[35].sX;
    sY = m_stDialogBoxInfo[35].sY;
    szX = m_stDialogBoxInfo[35].sSizeX;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);

    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 0) && (msY < sY + 50 + 15 * 1))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 0, DRAW_DIALOGBOX_HELP2, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 0, DRAW_DIALOGBOX_HELP2, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 1) && (msY < sY + 50 + 15 * 2))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 1, DRAW_DIALOGBOX_HELP1, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 1, DRAW_DIALOGBOX_HELP1, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 2) && (msY < sY + 50 + 15 * 3))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 2, DRAW_DIALOGBOX_HELP3, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 2, DRAW_DIALOGBOX_HELP3, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 3) && (msY < sY + 50 + 15 * 4))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 3, DRAW_DIALOGBOX_HELP4, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 3, DRAW_DIALOGBOX_HELP4, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 4) && (msY < sY + 50 + 15 * 5))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 4, DRAW_DIALOGBOX_HELP5, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 4, DRAW_DIALOGBOX_HELP5, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 5) && (msY < sY + 50 + 15 * 6))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 5, DRAW_DIALOGBOX_HELP6, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 5, DRAW_DIALOGBOX_HELP6, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 6) && (msY < sY + 50 + 15 * 7))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 6, DRAW_DIALOGBOX_HELP7, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 6, DRAW_DIALOGBOX_HELP7, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 7) && (msY < sY + 50 + 15 * 8))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 7, DRAW_DIALOGBOX_HELP8, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 7, DRAW_DIALOGBOX_HELP8, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 8) && (msY < sY + 50 + 15 * 9))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 8, DRAW_DIALOGBOX_HELP9, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 8, DRAW_DIALOGBOX_HELP9, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 9) && (msY < sY + 50 + 15 * 10))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 9, DRAW_DIALOGBOX_HELP10, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 9, DRAW_DIALOGBOX_HELP10, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 10) && (msY < sY + 50 + 15 * 11))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 10, DRAW_DIALOGBOX_HELP11, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 10, DRAW_DIALOGBOX_HELP11, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 11) && (msY < sY + 50 + 15 * 12))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 11, DRAW_DIALOGBOX_HELP12, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 11, DRAW_DIALOGBOX_HELP12, 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 12) && (msY < sY + 50 + 15 * 13))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 12, "F.A.Q.", 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 12, "F.A.Q.", 4, 0, 50);
    if ((msX >= sX + 25) && (msX <= sX + 248) && (msY >= sY + 50 + 15 * 13) && (msY < sY + 50 + 15 * 14))
        PutAlignedString(sX, sX + szX, sY + 50 + 15 * 13, DRAW_DIALOGBOX_HELP13, 255, 255, 255);
    else PutAlignedString(sX, sX + szX, sY + 50 + 15 * 13, DRAW_DIALOGBOX_HELP13, 4, 0, 50);

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}

void CGame::DrawDialogBox_ItemUpgrade(int msX, int msY)
{
    int i, sX, sY, iValue;
    char cItemColor, cStr1[120], cStr2[120], cStr3[120];
    uint64_t dwTime = unixtime();

    sX = m_stDialogBoxInfo[34].sX;
    sY = m_stDialogBoxInfo[34].sY;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 5); //Item Upgrade Text

    switch (m_stDialogBoxInfo[34].cMode)
    {
        case 1://Gizon box Drag item needed to be upgraded"
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 30, DRAW_DIALOGBOX_ITEMUPGRADE1); // Drag item needed to be upgraded"
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE2); // "from the inventory. Then press"
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 60, DRAW_DIALOGBOX_ITEMUPGRADE3); // 'Upgrade' button."
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);

#ifdef DEF_EQUILIBRIUM_PROJECT // Needed Upgrade pt
            wsprintfA(G_cTxt, "Gizon points available : %d:", m_iGizonItemUpgradeLeft);
            PutAlignedString(sX + 24, sX + 248, sY + 100, G_cTxt);
            if (m_stDialogBoxInfo[34].sV1 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
                // Server doesnt send this value, so I made it send as bit 24 of attribute
                //iValue = pow(2, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sItemSpecEffectValue3);
                iValue = (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_dwAttribute & 0x0F000000) >> 24;

                // Angelic Cost
                if ((m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos >= 11)
                    && (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemType == 1))
                {
                    if ((memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(STR)", 19) == 0)
                        || (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(DEX)", 19) == 0)
                        || (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(INT)", 19) == 0)
                        || (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(MAG)", 19) == 0))
                    {
                        iValue = (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_dwAttribute & 0xF0000000) >> 28;
                        switch (iValue)
                        {
                            case 0:	iValue = 2; break;
                            case 1: iValue = 4; break;
                            case 2: iValue = 6; break;
                            case 3: iValue = 8; break;
                            case 4: iValue = 10; break;
                            case 5: iValue = 12; break;
                            case 6: iValue = 14; break;
                            case 7: iValue = 16; break;
                            case 8: iValue = 18; break;
                            case 9: iValue = 20; break;
                            case 10: iValue = 22; break;
                            case 11: iValue = 24; break;
                            case 12: iValue = 26; break;
                            case 13: iValue = 28; break;
                            case 14: iValue = 30; break;
                        }
                        wsprintfA(G_cTxt, "Angelic upgrade gizon cost: %d", iValue);
                        if (m_iGizonItemUpgradeLeft < iValue)
                            PutAlignedString(sX + 24, sX + 248, sY + 115, G_cTxt, 195, 25, 25);
                        else PutAlignedString(sX + 24, sX + 248, sY + 115, G_cTxt);
                    }
                }
                else if (iValue == 0) // Unknown cost
                {
                    PutAlignedString(sX + 24, sX + 248, sY + 115, "cost 1st upg: 1, 2nd: 2, 3rd: 4, 4th: 8 ...");
                }
                else
                {	// Faudra modifier le serveur en consequence!
                    iValue = pow(2, iValue);
                    wsprintfA(G_cTxt, "Indicative needed gizon: %d", iValue);
                    if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 115) && (msY < sY + 130))
                    {
                        PutAlignedString(sX + 24, sX + 248, sY + 115, "(indicative value, can be higher)");
                        ZeroMemory(G_cTxt, sizeof(G_cTxt));
                    }
                    else if (m_iGizonItemUpgradeLeft < iValue)
                        PutAlignedString(sX + 24, sX + 248, sY + 115, G_cTxt, 195, 25, 25);
                    else PutAlignedString(sX + 24, sX + 248, sY + 115, G_cTxt);
                }

#else
            wsprintfA(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE11, m_iGizonItemUpgradeLeft);		// "Item upgrade point : %d"
            PutAlignedString(sX + 24, sX + 248, sY + 100, G_cTxt);
            if (m_stDialogBoxInfo[34].sV1 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
                iValue = (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_dwAttribute & 0xF0000000) >> 28;
                iValue = iValue * (iValue + 6) / 8 + 2;
                if ((m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos >= 11)
                    && (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemType == 1))
                {
                    if ((memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(STR)", 19) == 0)
                        || (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(DEX)", 19) == 0)
                        || (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(INT)", 19) == 0)
                        || (memcmp(m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cName, "AngelicPandent(MAG)", 19) == 0))
                    {
                        iValue = (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_dwAttribute & 0xF0000000) >> 28;
                        switch (iValue)
                        {
                            case 0:	iValue = 10; break;
                            case 1: iValue = 11; break;
                            case 2: iValue = 13; break;
                            case 3: iValue = 16; break;
                            case 4: iValue = 20; break;
                            case 5: iValue = 25; break;
                            case 6: iValue = 31; break;
                            case 7: iValue = 38; break;
                            case 8: iValue = 46; break;
                            case 9: iValue = 55; break;
                        }
                    }
                }
                wsprintfA(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE12, iValue); //"Needed upgrade point : %d"
                if (m_iGizonItemUpgradeLeft < iValue)
                    PutAlignedString(sX + 24, sX + 248, sY + 115, G_cTxt, 195, 25, 25);
                else PutAlignedString(sX + 24, sX + 248, sY + 115, G_cTxt);
#endif

                i = m_stDialogBoxInfo[34].sV1;
                cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
                if ((m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                }
                else
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                }
                ZeroMemory(cStr1, sizeof(cStr1));
                ZeroMemory(cStr2, sizeof(cStr2));
                ZeroMemory(cStr3, sizeof(cStr3));
                GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
                PutAlignedString(sX + 24, sX + 248, sY + 230 + 20, cStr1);
                PutAlignedString(sX + 24, sX + 248, sY + 245 + 20, cStr2);
                PutAlignedString(sX + 24, sX + 248, sY + 260 + 20, cStr3);
                if (m_iGizonItemUpgradeLeft < iValue)
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
                else
                {
                    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 47);
                    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
                }
            }
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 2: // in progress
            PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE5);
            PutAlignedString(sX + 24, sX + 248, sY + 55 + 45 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE6);
            if (m_stDialogBoxInfo[34].sV1 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
                i = m_stDialogBoxInfo[34].sV1;
                cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
                if ((m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                }
                else
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                }
                if ((rand() % 5) == 0) m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutTransSprite25(sX + 134, sY + 182, m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, dwTime);
                ZeroMemory(cStr1, sizeof(cStr1));
                ZeroMemory(cStr2, sizeof(cStr2));
                ZeroMemory(cStr3, sizeof(cStr3));
                GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
                PutAlignedString(sX + 24, sX + 248, sY + 230 + 20, cStr1);
                PutAlignedString(sX + 24, sX + 248, sY + 245 + 20, cStr2);
                PutAlignedString(sX + 24, sX + 248, sY + 260 + 20, cStr3);
            }
            if (((dwTime - m_stDialogBoxInfo[34].dwV1) / 1000 > 4) && (m_stDialogBoxInfo[34].dwV1 != 0))
            {
                m_stDialogBoxInfo[34].dwV1 = 0;
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_UPGRADEITEM, 0, m_stDialogBoxInfo[34].sV1, 0, 0, 0);
            }
            break;

        case 3: // Congratulations
            PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE7);//"Congratulation! item upgrade"
            PutAlignedString(sX + 24, sX + 248, sY + 55 + 45 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE8);//"has been succeeded."
            if (m_stDialogBoxInfo[34].sV1 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
                i = m_stDialogBoxInfo[34].sV1;
                cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
                if ((m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                }
                else
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                }
                ZeroMemory(cStr1, sizeof(cStr1));
                ZeroMemory(cStr2, sizeof(cStr2));
                ZeroMemory(cStr3, sizeof(cStr3));
                GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
                PutAlignedString(sX + 24, sX + 248, sY + 230 + 20, cStr1);
                PutAlignedString(sX + 24, sX + 248, sY + 245 + 20, cStr2);
                PutAlignedString(sX + 24, sX + 248, sY + 260 + 20, cStr3);
            }
            // OK
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 4: // Failed
            PutAlignedString(sX + 24, sX + 248, sY + 55 + 30 + 282 - 117 - 170, DRAW_DIALOGBOX_ITEMUPGRADE9);//"Item upgrade has failed."
            if ((m_stDialogBoxInfo[34].sV1 != -1) && (m_pItemList[m_stDialogBoxInfo[34].sV1] == 0))
            {
                PlaySound('E', 24, 0, 0);
                m_stDialogBoxInfo[34].cMode = 7;
                return;
            }
            if (m_stDialogBoxInfo[34].sV1 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
                i = m_stDialogBoxInfo[34].sV1;
                cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
                if ((m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                }
                else
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                }
                ZeroMemory(cStr1, sizeof(cStr1));
                ZeroMemory(cStr2, sizeof(cStr2));
                ZeroMemory(cStr3, sizeof(cStr3));
                GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
                PutAlignedString(sX + 24, sX + 248, sY + 230 + 20, cStr1);
                PutAlignedString(sX + 24, sX + 248, sY + 245 + 20, cStr2);
                PutAlignedString(sX + 24, sX + 248, sY + 260 + 20, cStr3);
            }

            // OK
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

#ifdef DEF_EQUILIBRIUM_PROJECT // Item upgrade DrawBox Menu global
        case 5: // select Stone/ Gizon
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 25, "Select enchantment's kind:");

            if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 80) && (msY < sY + 95))
            {
                PutAlignedString(sX + 24, sX + 248, sY + 80, "Normal item upgrade", 255, 255, 255);
                PutAlignedString(sX + 24, sX + 248, sY + 150, "Upgrading a normal item.");
                PutAlignedString(sX + 24, sX + 248, sY + 170, "With weapon upgrading,");
                PutAlignedString(sX + 24, sX + 248, sY + 185, "Stone of Xelima is needed.");
                PutAlignedString(sX + 24, sX + 248, sY + 200, "With armor items upgrading,");
                PutAlignedString(sX + 24, sX + 248, sY + 215, "Stone of Merien is needed.");

                PutAlignedString(sX + 24, sX + 248, sY + 255, "* Ancient or Strong items");
                PutAlignedString(sX + 24, sX + 248, sY + 270, " cannot be upgraded this way.");
            }
            else PutAlignedString(sX + 24, sX + 248, sY + 80, "Normal item upgrade", 4, 0, 50);

            if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 100) && (msY < sY + 115))
            {
                PutAlignedString(sX + 24, sX + 248, sY + 100, "Item enchantment", 255, 255, 255);
                PutAlignedString(sX + 24, sX + 248, sY + 150, "Enchant a manufactured item.");
                PutAlignedString(sX + 24, sX + 248, sY + 170, "A single Magic Oil is needed");
                PutAlignedString(sX + 24, sX + 248, sY + 185, "to enchant the item. You may");
                PutAlignedString(sX + 24, sX + 248, sY + 200, "use an Elixir to obtain a");
                PutAlignedString(sX + 24, sX + 248, sY + 215, "stated item, and a Ball to");
                PutAlignedString(sX + 24, sX + 248, sY + 230, "enhance the enchantment.");

                PutAlignedString(sX + 24, sX + 248, sY + 255, "* Only manufuctured items");
                PutAlignedString(sX + 24, sX + 248, sY + 270, " can be enchanted this way.");
            }
            else PutAlignedString(sX + 24, sX + 248, sY + 100, "Item enchantment", 4, 0, 50);

            if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 120) && (msY < sY + 135))
            {
                PutAlignedString(sX + 24, sX + 248, sY + 120, "Gizon item upgrade", 255, 255, 255);
                PutAlignedString(sX + 24, sX + 248, sY + 150, "Improving stated item.");
                PutAlignedString(sX + 24, sX + 248, sY + 170, "In order to improve stated items,");
                PutAlignedString(sX + 24, sX + 248, sY + 185, "enough gizon points are required.");
                PutAlignedString(sX + 24, sX + 248, sY + 200, "Each successive upgrade will");
                PutAlignedString(sX + 24, sX + 248, sY + 215, "double the needed points.");

                PutAlignedString(sX + 24, sX + 248, sY + 255, "* Only already enchanted items");
                PutAlignedString(sX + 24, sX + 248, sY + 270, " can be improved this way.");
            }
            else PutAlignedString(sX + 24, sX + 248, sY + 120, "Gizon item upgrade", 4, 0, 50);


#else
        case 5: // select Stone/ Gizon
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE13); // "Select which kind of items to upgrade."
            if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 100) && (msY < sY + 115))
            {
                PutAlignedString(sX + 24, sX + 248, sY + 100, DRAW_DIALOGBOX_ITEMUPGRADE14, 255, 255, 255); // "Normal item upgrade"
                PutAlignedString(sX + 24, sX + 248, sY + 150, DRAW_DIALOGBOX_ITEMUPGRADE16); // "Upgrading a normal item."
                PutAlignedString(sX + 24, sX + 248, sY + 165, DRAW_DIALOGBOX_ITEMUPGRADE17); // "With upgrading weapon"
                PutAlignedString(sX + 24, sX + 248, sY + 180, DRAW_DIALOGBOX_ITEMUPGRADE18); // "items, Stone of Xelima"
                PutAlignedString(sX + 24, sX + 248, sY + 195, DRAW_DIALOGBOX_ITEMUPGRADE19); // "is needed. With upgrading"
                PutAlignedString(sX + 24, sX + 248, sY + 210, DRAW_DIALOGBOX_ITEMUPGRADE20); // "armor items, Stone of"
                PutAlignedString(sX + 24, sX + 248, sY + 225, DRAW_DIALOGBOX_ITEMUPGRADE21); // "Merien is needed."
                PutAlignedString(sX + 24, sX + 248, sY + 255, DRAW_DIALOGBOX_ITEMUPGRADE26); // "* Majestic items cannot be"
                PutAlignedString(sX + 24, sX + 248, sY + 270, DRAW_DIALOGBOX_ITEMUPGRADE27); // "upgraded with this performance."
            }
            else PutAlignedString(sX + 24, sX + 248, sY + 100, DRAW_DIALOGBOX_ITEMUPGRADE14, 4, 0, 50); // "Normal item upgrade"
            if ((msX > sX + 24) && (msX < sX + 248) && (msY > sY + 120) && (msY < sY + 135))
            {
                PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_ITEMUPGRADE15, 255, 255, 255); // "Majestic item upgrade"
                PutAlignedString(sX + 24, sX + 248, sY + 150, DRAW_DIALOGBOX_ITEMUPGRADE22); // "Upgrading majestic items."
                PutAlignedString(sX + 24, sX + 248, sY + 165, DRAW_DIALOGBOX_ITEMUPGRADE23); // "In order to upgrade majestic items,"
                PutAlignedString(sX + 24, sX + 248, sY + 180, DRAW_DIALOGBOX_ITEMUPGRADE24); // "enough upgrade points for"
                PutAlignedString(sX + 24, sX + 248, sY + 195, DRAW_DIALOGBOX_ITEMUPGRADE25); // "majestic items are required."
                PutAlignedString(sX + 24, sX + 248, sY + 225, DRAW_DIALOGBOX_ITEMUPGRADE28); // "* Normal items cannot be"
                PutAlignedString(sX + 24, sX + 248, sY + 240, DRAW_DIALOGBOX_ITEMUPGRADE29); // "upgraded with this performance."
            }
            else PutAlignedString(sX + 24, sX + 248, sY + 120, DRAW_DIALOGBOX_ITEMUPGRADE15, 4, 0, 50); // "Majestic item upgrade"
#endif
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 6: // Stone upgrade
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 30, DRAW_DIALOGBOX_ITEMUPGRADE31); // "After bring a normal item to"
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, DRAW_DIALOGBOX_ITEMUPGRADE32); //
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 60, DRAW_DIALOGBOX_ITEMUPGRADE33); //
            if (m_stDialogBoxInfo[34].sV2 == 0)
            {
                PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, DRAW_DIALOGBOX_ITEMUPGRADE41, 195, 25, 25);//"You can upgrade only armor."
            }
            else
            {
                wsprintfA(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE34, m_stDialogBoxInfo[34].sV2);//"The number of upgrade(weapon): %d"
                PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, G_cTxt);
            }
            if (m_stDialogBoxInfo[34].sV3 == 0)
            {
                PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, DRAW_DIALOGBOX_ITEMUPGRADE42, 195, 25, 25);//"You can upgrade only weapon."
            }
            else
            {
                wsprintfA(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE35, m_stDialogBoxInfo[34].sV3);//"The number of upgrade(armor): %d"
                PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, G_cTxt);
            }

            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);

            if (m_stDialogBoxInfo[34].sV1 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
                i = m_stDialogBoxInfo[34].sV1;
                cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
                if ((m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                }
                else
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                }

                ZeroMemory(cStr1, sizeof(cStr1));
                ZeroMemory(cStr2, sizeof(cStr2));
                ZeroMemory(cStr3, sizeof(cStr3));
                GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
                PutAlignedString(sX + 24, sX + 248, sY + 230 + 20, cStr1);
                PutAlignedString(sX + 24, sX + 248, sY + 245 + 20, cStr2);
                PutAlignedString(sX + 24, sX + 248, sY + 260 + 20, cStr3);
                if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 47);
                else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
            }
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;

        case 7: // lost item
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE36);//"Due to the failure of upgrade, the"
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 145, DRAW_DIALOGBOX_ITEMUPGRADE37);//"item is gone. Try next time!"
            // OK
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 8: // impossible deja au max
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE38);//"Upgrading the item is not possible any more."
            // OK
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 9: // impossible
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE39);//"Upgrading the item is not possible."
            // OK
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 10: // plus de gizons
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 130, DRAW_DIALOGBOX_ITEMUPGRADE40);//"A point to upgrade items is not present"
            // OK
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

#ifdef DEF_EQUILIBRIUM_PROJECT

        case 11: // Alchemy upgrade
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 30, "After bringing a manuf item to");
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 45, "enchant from the inventory,");
            PutAlignedString(sX + 24, sX + 248, sY + 20 + 60, "press the 'Upgrade' button.");

            if (m_pItemList[m_stDialogBoxInfo[34].sV4] == 0) m_stDialogBoxInfo[34].sV4 = -1;
            if (m_stDialogBoxInfo[34].sV4 != -1)
            {
                ZeroMemory(G_cTxt, sizeof(G_cTxt));
                if (strcmp(m_pItemList[m_stDialogBoxInfo[34].sV4]->m_cName, "Stone") == 0)
                {
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, "You may enchant a weapon as Ancient.");
                }
                else if (strcmp(m_pItemList[m_stDialogBoxInfo[34].sV4]->m_cName, "SharpnessOil") == 0)
                {
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, "You may enchant a weapon as Sharp,");
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, "or an armor as Mana converting.");
                }
                else if (strcmp(m_pItemList[m_stDialogBoxInfo[34].sV4]->m_cName, "AgilityOil") == 0)
                {
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, "You may enchant a weapon as Agile,");
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, "or an armor as Light");
                }
                else if (strcmp(m_pItemList[m_stDialogBoxInfo[34].sV4]->m_cName, "PoisonOil") == 0)
                {
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, "You may Poison a weapon.");
                }
                else if (strcmp(m_pItemList[m_stDialogBoxInfo[34].sV4]->m_cName, "BerzerkOil") == 0)
                {
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, "You may enchant a weapon as Critical,");
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 95, "or an armor as Critical Increase.");
                }
                else if (strcmp(m_pItemList[m_stDialogBoxInfo[34].sV4]->m_cName, "TruthOil") == 0)
                {
                    PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, "You may enchant a weapon as Righteous.");
                }
            }
            else
            {
                PutAlignedString(sX + 24, sX + 248, sY + 20 + 80, "You need Magic Oil in bag to enchant!");
            }

            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);

            if (m_stDialogBoxInfo[34].sV1 != -1)
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME3, sX, sY, 3);
                i = m_stDialogBoxInfo[34].sV1;
                cItemColor = m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cItemColor;
                if ((m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
                    || (m_pItemList[m_stDialogBoxInfo[34].sV1]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0], dwTime);
                }
                else
                {
                    m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSprite]->PutSpriteRGB(sX + 134, sY + 182
                        , m_pItemList[m_stDialogBoxInfo[34].sV1]->m_sSpriteFrame, m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0], dwTime);
                }

                ZeroMemory(cStr1, sizeof(cStr1));
                ZeroMemory(cStr2, sizeof(cStr2));
                ZeroMemory(cStr3, sizeof(cStr3));
                GetItemName(m_pItemList[m_stDialogBoxInfo[34].sV1], cStr1, cStr2, cStr3);
                PutAlignedString(sX + 24, sX + 248, sY + 230 + 20, cStr1);
                PutAlignedString(sX + 24, sX + 248, sY + 245 + 20, cStr2);
                PutAlignedString(sX + 24, sX + 248, sY + 260 + 20, cStr3);
                if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX)
                    && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY)
                    && (m_stDialogBoxInfo[34].sV4 != -1))
                    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 47);
                else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 46);
            }
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 17);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 16);
            break;


        case 12: // 12 Need stone!
            PutAlignedString(sX + 24, sX + 248, sY + 100, "Xelima or Merien stone needed!", 195, 25, 25);
            PutAlignedString(sX + 24, sX + 248, sY + 150, "When upgrading weapons,");
            PutAlignedString(sX + 24, sX + 248, sY + 165, "Stone of Xelima is needed.");
            PutAlignedString(sX + 24, sX + 248, sY + 180, "When upgrading armor items,");
            PutAlignedString(sX + 24, sX + 248, sY + 195, "Stone of Merien is needed.");
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 13: // 13 remove stones!
            PutAlignedString(sX + 24, sX + 248, sY + 100, "Remove Xelima or Merien stone!", 195, 25, 25);
            PutAlignedString(sX + 24, sX + 248, sY + 150, "When enchanting manuf items,");
            PutAlignedString(sX + 24, sX + 248, sY + 165, "or upgrading enchanted items,");
            PutAlignedString(sX + 24, sX + 248, sY + 180, "Stone of Xelima or Merien must");
            PutAlignedString(sX + 24, sX + 248, sY + 195, "be removed from your bag.");
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 14: // 14 No Oil present
            PutAlignedString(sX + 24, sX + 248, sY + 100, "Magic Oil needed!", 195, 25, 25);
            PutAlignedString(sX + 24, sX + 248, sY + 150, "When enchanting manuf items,");
            PutAlignedString(sX + 24, sX + 248, sY + 165, "a Magic Oil must be placed");
            PutAlignedString(sX + 24, sX + 248, sY + 180, "in your bag.");
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 15: // 15 too much Oil error
            PutAlignedString(sX + 24, sX + 248, sY + 100, "Too much Magic Oils!", 195, 25, 25);
            PutAlignedString(sX + 24, sX + 248, sY + 150, "When enchanting manuf items,");
            PutAlignedString(sX + 24, sX + 248, sY + 165, "a SINGLE Magic Oil must be");
            PutAlignedString(sX + 24, sX + 248, sY + 180, "found in your bag.");
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 16: // 16 too much Elixir error
            PutAlignedString(sX + 24, sX + 248, sY + 100, "Too much Magic Elixirs!", 195, 25, 25);
            PutAlignedString(sX + 24, sX + 248, sY + 150, "When enchanting manuf items,");
            PutAlignedString(sX + 24, sX + 248, sY + 165, "a SINGLE Magic Elixir must");
            PutAlignedString(sX + 24, sX + 248, sY + 180, "be found in your bag.");
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

        case 17: // 17 remove Oils
            PutAlignedString(sX + 24, sX + 248, sY + 100, "Remove Magic Oil(s)!", 195, 25, 25);
            PutAlignedString(sX + 24, sX + 248, sY + 150, "In order to improve stated items,");
            PutAlignedString(sX + 24, sX + 248, sY + 165, "you must remove any Magic Oil");
            PutAlignedString(sX + 24, sX + 248, sY + 180, "or Strange Stone from your bag.");
            // Cancel
            if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + DEF_BTNPOSY) && (msY <= sY + DEF_BTNPOSY + DEF_BTNSZY))
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
            else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
            break;

#endif
    }
}


void CGame::DrawDialogBox_ChangeStatsMajestic(short msX, short msY)
{
    short sX, sY, szX;
    uint64_t dwTime = m_dwCurTime;
    char cTxt[120];
    int iStats;
    sX = m_stDialogBoxInfo[42].sX;
    sY = m_stDialogBoxInfo[42].sY;
    szX = m_stDialogBoxInfo[42].sSizeX;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 0);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, sX, sY, 2);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, sX + 16, sY + 100, 4);

    PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_LEVELUP_SETTING14);
    PutAlignedString(sX, sX + szX, sY + 65, DRAW_DIALOGBOX_LEVELUP_SETTING15);

    // Majestic Points Left - Display in green if > 0
    PutString(sX + 20, sY + 85, DRAW_DIALOGBOX_LEVELUP_SETTING16, Color(0, 0, 0));
    wsprintfA(cTxt, "%d", m_iGizonItemUpgradeLeft);
    if (m_iGizonItemUpgradeLeft > 0)
    {
        PutString(sX + 73, sY + 102, cTxt, Color(0, 255, 0));
    }
    else
    {
        PutString(sX + 73, sY + 102, cTxt, Color(0, 0, 0));
    }
    // Display only MouseOver Button for - (+ is disabled)
    // Strength
    PutString(sX + 24, sY + 125, DRAW_DIALOGBOX_LEVELUP_SETTING4, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iStr);
    PutString(sX + 109, sY + 125, cTxt, Color(25, 35, 25));
    iStats = m_iStr + m_cLU_Str;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats < m_iStr)
    {
        PutString(sX + 162, sY + 125, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 125, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 127) && (msY <= sY + 133))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 127, 6, dwTime);

    // Vitality
    PutString(sX + 24, sY + 144, DRAW_DIALOGBOX_LEVELUP_SETTING5, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iVit);
    PutString(sX + 109, sY + 144, cTxt, Color(25, 35, 25));
    iStats = m_iVit + m_cLU_Vit;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats < m_iVit)
    {
        PutString(sX + 162, sY + 144, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 144, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 146) && (msY <= sY + 152))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 146, 6, dwTime);

    // Dexterity
    PutString(sX + 24, sY + 163, DRAW_DIALOGBOX_LEVELUP_SETTING6, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iDex);
    PutString(sX + 109, sY + 163, cTxt, Color(25, 35, 25));
    iStats = m_iDex + m_cLU_Dex;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats < m_iDex)
    {
        PutString(sX + 162, sY + 163, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 163, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 165) && (msY <= sY + 171))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 165, 6, dwTime);

    // Intelligence
    PutString(sX + 24, sY + 182, DRAW_DIALOGBOX_LEVELUP_SETTING7, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iInt);
    PutString(sX + 109, sY + 182, cTxt, Color(25, 35, 25));
    iStats = m_iInt + m_cLU_Int;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats < m_iInt)
    {
        PutString(sX + 162, sY + 182, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 182, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 184) && (msY <= sY + 190))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 184, 6, dwTime);

    // Magic
    PutString(sX + 24, sY + 201, DRAW_DIALOGBOX_LEVELUP_SETTING8, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iMag);
    PutString(sX + 109, sY + 201, cTxt, Color(25, 35, 25));
    iStats = m_iMag + m_cLU_Mag;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats < m_iMag)
    {
        PutString(sX + 162, sY + 201, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 201, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 203) && (msY <= sY + 209))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 203, 6, dwTime);

    // Charisma
    PutString(sX + 24, sY + 220, DRAW_DIALOGBOX_LEVELUP_SETTING9, Color(5, 5, 5));
    wsprintfA(cTxt, "%d", m_iCharisma);
    PutString(sX + 109, sY + 220, cTxt, Color(25, 35, 25));
    iStats = m_iCharisma + m_cLU_Char;
    wsprintfA(cTxt, "%d", iStats);
    if (iStats < m_iCharisma)
    {
        PutString(sX + 162, sY + 220, cTxt, Color(255, 0, 0));
    }
    else
    {
        PutString(sX + 162, sY + 220, cTxt, Color(25, 35, 25));
    }
    if ((msX >= sX + 210) && (msX <= sX + 220) && (msY >= sY + 222) && (msY <= sY + 228))
        m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4]->PutSpriteFast(sX + 210, sY + 222, 6, dwTime);

    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_LBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 17);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_LBTNPOSX, sY + DEF_BTNPOSY, 16);

    if ((msX >= sX + DEF_RBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY > sY + DEF_BTNPOSY) && (msY < sY + DEF_BTNPOSY + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 1);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + DEF_RBTNPOSX, sY + DEF_BTNPOSY, 0);
}


void CGame::DrawDialogBox_Resurect(short msX, short msY)
{
    short sX, sY;
    //00476D02  |. 68 A4474C00    PUSH 004C47A4                    ;  ASCII "Someone intend to resurrect you."
    //00476D41  |. 68 8C474C00    PUSH 004C478C                    ;  ASCII "Will you revive here?"
    sX = m_stDialogBoxInfo[50].sX;
    sY = m_stDialogBoxInfo[50].sY;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME1, sX, sY, 2);

    PutString(sX + 50, sY + 20, "Someone intend to resurrect you.", Color(4, 0, 50));
    PutString(sX + 80, sY + 35, "Will you revive here?", Color(4, 0, 50));

    if ((msX >= sX + 30) && (msX <= sX + 30 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55, 19);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 30, sY + 55, 18);

    if ((msX >= sX + 170) && (msX <= sX + 170 + DEF_BTNSZX) && (msY >= sY + 55) && (msY <= sY + 55 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55, 3);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, sX + 170, sY + 55, 2);
}


void CGame::DrawDialogBox_CMDHallMenu(short msX, short msY)
{
    short sX, sY, szX;
    char cTxt[120];
    sX = m_stDialogBoxInfo[51].sX;
    sY = m_stDialogBoxInfo[51].sY;
    szX = m_stDialogBoxInfo[51].sSizeX;
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME2, sX, sY, 2);

    switch (m_stDialogBoxInfo[51].cMode)
    {
        case 0: // initial diag
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
                PutAlignedString(sX, sX + szX, sY + 70, "Teleport to Battle Field", 255, 255, 255);
            else PutAlignedString(sX, sX + szX, sY + 70, "Teleport to Battle Field", 4, 0, 50);

            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
                PutAlignedString(sX, sX + szX, sY + 95, "Hire a soldier", 255, 255, 255);
            else PutAlignedString(sX, sX + szX, sY + 95, "Hire a soldier", 4, 0, 50);

            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
                PutAlignedString(sX, sX + szX, sY + 120, "Taking Flags", 255, 255, 255);
            else PutAlignedString(sX, sX + szX, sY + 120, "Taking Flags", 4, 0, 50);
            // Angels
            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 170))
                PutAlignedString(sX, sX + szX, sY + 145, "Receive a Tutelary Angel", 255, 255, 255);
            else PutAlignedString(sX, sX + szX, sY + 145, "Receive a Tutelary Angel", 4, 0, 50);
            break;

        case 1: // TP diag
            if (m_iTeleportMapCount > 0)
            {	//PutAlignedString(sX, sX + szX, sY + 50, DRAW_DIALOGBOX_CITYHALL_MENU69, 55,25,25); // "Teleporting to dungeon level 2."
                //PutAlignedString(sX, sX + szX, sY + 80, DRAW_DIALOGBOX_CITYHALL_MENU70, 55,25,25); // "5000Gold is required"
                //PutAlignedString(sX, sX + szX, sY + 95, DRAW_DIALOGBOX_CITYHALL_MENU71, 55,25,25); //
                //PutAlignedString(sX, sX + szX, sY + 110, DRAW_DIALOGBOX_CITYHALL_MENU72, 55,25,25);//
                PutString2(sX + 35, sY + 250, DRAW_DIALOGBOX_CITYHALL_MENU72_1, 55, 25, 25);//"Civilians cannot go some area."
                for (int i = 0; i < m_iTeleportMapCount; i++)
                {
                    ZeroMemory(cTxt, sizeof(cTxt));
                    GetOfficialMapName(m_stTeleportList[i].mapname, cTxt);
                    wsprintfA(G_cTxt, DRAW_DIALOGBOX_CITYHALL_MENU77, cTxt, m_stTeleportList[i].iCost);
                    if ((msX >= sX + DEF_LBTNPOSX) && (msX <= sX + DEF_RBTNPOSX + DEF_BTNSZX) && (msY >= sY + 130 + i * 15) && (msY <= sY + 144 + i * 15))
                        PutAlignedString(sX, sX + szX, sY + 130 + i * 15, G_cTxt, 255, 255, 255);
                    else PutAlignedString(sX, sX + szX, sY + 130 + i * 15, G_cTxt, 250, 250, 0);
                }
            }
            else if (m_iTeleportMapCount == -1)
            {
                PutAlignedString(sX, sX + szX, sY + 125, DRAW_DIALOGBOX_CITYHALL_MENU73, 55, 25, 25);//"Now it's searching for possible area"
                PutAlignedString(sX, sX + szX, sY + 150, DRAW_DIALOGBOX_CITYHALL_MENU74, 55, 25, 25);//"to teleport."
                PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_CITYHALL_MENU75, 55, 25, 25);//"Please wait for a moment."
            }
            else
            {
                PutAlignedString(sX, sX + szX, sY + 175, DRAW_DIALOGBOX_CITYHALL_MENU76, 55, 25, 25);//"There is no area that you can teleport."
            }
            break;

        case 2: // Soldier diag
            PutAlignedString(sX, sX + szX, sY + 45, "You will hire a soldier by summon points", 255, 255, 255);
            if ((m_iConstructionPoint >= 2000) && (m_bIsCrusadeMode == false))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 70) && (msY < sY + 95))
                    PutAlignedString(sX, sX + szX, sY + 70, "Sorceress             2000 Point", 255, 255, 255);
                else PutAlignedString(sX, sX + szX, sY + 70, "Sorceress             2000 Point", 4, 0, 50);
            }
            else PutAlignedString(sX, sX + szX, sY + 70, "Sorceress             2000 Point", 65, 65, 65);

            if ((m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == false))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 95) && (msY < sY + 120))
                    PutAlignedString(sX, sX + szX, sY + 95, "Ancient Temple Knight 3000 Point", 255, 255, 255);
                else PutAlignedString(sX, sX + szX, sY + 95, "Ancient Temple Knight 3000 Point", 4, 0, 50);
            }
            else PutAlignedString(sX, sX + szX, sY + 95, "Ancient Temple Knight 3000 Point", 65, 65, 65);

            if ((m_iConstructionPoint >= 1500) && (m_bIsCrusadeMode == false))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 120) && (msY < sY + 145))
                    PutAlignedString(sX, sX + szX, sY + 120, "Elf Master            1500 Point", 255, 255, 255);
                else PutAlignedString(sX, sX + szX, sY + 120, "Elf Master            1500 Point", 4, 0, 50);
            }
            else PutAlignedString(sX, sX + szX, sY + 120, "Elf Master            1500 Point", 65, 65, 65);

            if ((m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == false))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 145) && (msY < sY + 171))
                    PutAlignedString(sX, sX + szX, sY + 145, "Dark Shadow Knight    3000 Point", 255, 255, 255);
                else PutAlignedString(sX, sX + szX, sY + 145, "Dark Shadow Knight    3000 Point", 4, 0, 50);
            }
            else PutAlignedString(sX, sX + szX, sY + 145, "Dark Shadow Knight    3000 Point", 65, 65, 65);

            if ((m_iConstructionPoint >= 4000) && (m_bIsCrusadeMode == false))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 170) && (msY < sY + 195))
                    PutAlignedString(sX, sX + szX, sY + 170, "Heavy Battle Tank     4000 Point", 255, 255, 255);
                else PutAlignedString(sX, sX + szX, sY + 170, "Heavy Battle Tank     4000 Point", 4, 0, 50);
            }
            else PutAlignedString(sX, sX + szX, sY + 170, "Heavy Battle Tank     4000 Point", 65, 65, 65);

            if ((m_iConstructionPoint >= 3000) && (m_bIsCrusadeMode == false))
            {
                if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 195) && (msY < sY + 220))
                    PutAlignedString(sX, sX + szX, sY + 195, "Barbarian             3000 Point", 255, 255, 255);
                else PutAlignedString(sX, sX + szX, sY + 195, "Barbarian             3000 Point", 4, 0, 50);
            }
            else PutAlignedString(sX, sX + szX, sY + 195, "Barbarian             3000 Point", 65, 65, 65);


#ifdef DEF_EQUILIBRIUM_PROJECT // max summon pts Heldenian
            //PutAlignedString(sX, sX + szX, sY + 220,"You should join a guild to hire soldiers.", 4,0,50);
            wsprintfA(G_cTxt, "Summon points : %d", m_iConstructionPoint);
            PutAlignedString(sX, sX + szX, sY + 250, G_cTxt, 4, 0, 50);
            PutAlignedString(sX, sX + szX, sY + 280, "Maximum summon points : 20000 points.", 4, 0, 50);
#else
            PutAlignedString(sX, sX + szX, sY + 220, "You should join a guild to hire soldiers.", 4, 0, 50);
            wsprintfA(G_cTxt, "Summon points : %d", m_iConstructionPoint);
            PutAlignedString(sX, sX + szX, sY + 250, G_cTxt, 4, 0, 50);
            PutAlignedString(sX, sX + szX, sY + 280, "Maximum summon points : 12000 points.", 4, 0, 50);
#endif
            PutAlignedString(sX, sX + szX, sY + 300, "Maximum hiring number : 5 ", 4, 0, 50);
            break;

        case 3: // Hire a Flag Diag
            PutAlignedString(sX, sX + szX, sY + 45, "You may acquire Flags with EK points.", 4, 0, 50);
            PutAlignedString(sX, sX + szX, sY + 70, "Price is 10 EK per Flag.", 4, 0, 50);
            if ((msX >= sX + 35) && (msX <= sX + 220) && (msY >= sY + 140) && (msY <= sY + 165))
                PutAlignedString(sX, sX + szX, sY + 140, "Take a Flag", 255, 255, 255);
            else
                PutAlignedString(sX, sX + szX, sY + 140, "Take a Flag", 250, 250, 0);
            break;

        case 4: // Tutelar Angel Diag

#ifdef DEF_EQUILIBRIUM_PROJECT // Pandents
            PutAlignedString(sX, sX + szX, sY + 45, "Obtain a tutelary Angel", 4, 0, 50);
            PutAlignedString(sX, sX + szX, sY + 80, "You need 5 gizon to get a Tutelary Angel.", 4, 0, 50);
            PutAlignedString(sX, sX + szX, sY + 105, "Would you like to buy a Tutelary Angel?", 4, 0, 50);
            wsprintfA(G_cTxt, "Gizon points available : %d:", m_iGizonItemUpgradeLeft);
#else
            PutAlignedString(sX, sX + szX, sY + 45, "5 magesty points will be deducted", 4, 0, 50);
            PutAlignedString(sX, sX + szX, sY + 80, "upon receiving the Pendant of Tutelary Angel.", 4, 0, 50);
            PutAlignedString(sX, sX + szX, sY + 105, "Would you like to receive the Tutelary Angel?", 4, 0, 50);
            wsprintfA(G_cTxt, DRAW_DIALOGBOX_ITEMUPGRADE11, m_iGizonItemUpgradeLeft);// "Item upgrade point : %d"
#endif

            PutAlignedString(sX, sX + szX, sY + 140, G_cTxt, 0, 0, 0);

            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 175) && (msY < sY + 200)
                && (m_iGizonItemUpgradeLeft > 4))
                PutAlignedString(sX, sX + szX, sY + 175, "Tutelary Angel (STR) will be handed out.", 255, 255, 255);
            else PutAlignedString(sX, sX + szX, sY + 175, "Tutelary Angel (STR) will be handed out.", 250, 250, 0);

            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 200) && (msY < sY + 225)
                && (m_iGizonItemUpgradeLeft > 4))
                PutAlignedString(sX, sX + szX, sY + 200, "Tutelary Angel (DEX) will be handed out.", 255, 255, 255);
            else PutAlignedString(sX, sX + szX, sY + 200, "Tutelary Angel (DEX) will be handed out.", 250, 250, 0);

            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 225) && (msY < sY + 250)
                && (m_iGizonItemUpgradeLeft > 4))
                PutAlignedString(sX, sX + szX, sY + 225, "Tutelary Angel (INT) will be handed out.", 255, 255, 255);
            else PutAlignedString(sX, sX + szX, sY + 225, "Tutelary Angel (INT) will be handed out.", 250, 250, 0);

            if ((msX > sX + 35) && (msX < sX + 220) && (msY > sY + 250) && (msY < sY + 275)
                && (m_iGizonItemUpgradeLeft > 4))
                PutAlignedString(sX, sX + szX, sY + 250, "Tutelary Angel (MAG) will be handed out.", 255, 255, 255);
            else PutAlignedString(sX, sX + szX, sY + 250, "Tutelary Angel (MAG) will be handed out.", 250, 250, 0);

            break;
    }
}


void CGame::DlbBoxDoubleClick_Character(short msX, short msY)
{
    char cEquipPoiStatus[DEF_MAXITEMEQUIPPOS] = {}, cItemID = -1;
    short sX, sY, sSprH, sFrame;
    int i;
    if (m_bIsDialogEnabled[17] == true) return;
    sX = m_stDialogBoxInfo[1].sX;
    sY = m_stDialogBoxInfo[1].sY;

    for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++)
        cEquipPoiStatus[i] = -1;

    for (i = 0; i < DEF_MAXITEMS; i++)
    {
        if ((m_pItemList[i] != 0) && (m_bIsItemEquipped[i] == true))	cEquipPoiStatus[m_pItemList[i]->m_cEquipPos] = i;
    }
    if ((m_sPlayerType >= 1) && (m_sPlayerType <= 3))
    {
        if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 41, sY + 137, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BACK];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_PANTS];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_ARMS];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BOOTS];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BODY];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 90, sY + 170, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_LHAND];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_RHAND];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 57, sY + 186, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_NECK];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_RFINGER];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_LFINGER];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH]->_bCheckCollison(sX + 72, sY + 135, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_HEAD];
        }
    }
    else if ((m_sPlayerType >= 4) && (m_sPlayerType <= 6))
    {
        if (cEquipPoiStatus[DEF_EQUIPPOS_BACK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BACK]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 45, sY + 143, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BACK];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BOOTS];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_PANTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_PANTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_PANTS];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_ARMS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_ARMS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_ARMS];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BOOTS] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BOOTS]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BOOTS];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_BODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_BODY]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_BODY];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 171, sY + 290, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_FULLBODY];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_LHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 84, sY + 175, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_LHAND];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_RHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_RHAND];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 60, sY + 191, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_TWOHAND];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_NECK] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_NECK]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 35, sY + 120, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_NECK];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_RFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_RFINGER]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 32, sY + 193, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_RFINGER];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_LFINGER] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_LFINGER]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 98, sY + 182, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_LFINGER];
        }
        if (cEquipPoiStatus[DEF_EQUIPPOS_HEAD] != -1)
        {
            sSprH = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSprite;
            sFrame = m_pItemList[cEquipPoiStatus[DEF_EQUIPPOS_HEAD]]->m_sSpriteFrame;
            if (m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + sSprH + 40]->_bCheckCollison(sX + 72, sY + 139, sFrame, msX, msY))
                cItemID = cEquipPoiStatus[DEF_EQUIPPOS_HEAD];
        }
    }

    if (cItemID == -1 || m_pItemList[cItemID] == 0) return;
    if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EAT)
        || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME)
        || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW)
        || (m_pItemList[cItemID]->m_dwCount > 1)) return;
    if ((m_bIsDialogEnabled[11] == true) && (m_bIsDialogEnabled[23] == false) && (m_stDialogBoxInfo[39].sV3 == 24))
        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEM, 0, cItemID, m_stDialogBoxInfo[39].sV3, 0, m_pItemList[cItemID]->m_cName, m_stDialogBoxInfo[39].sV4); // v1.4
    else
    {
        if (m_bIsItemEquipped[m_stMCursor.sSelectedObjectID] == true)
        {
            char cStr1[64], cStr2[64], cStr3[64];
            GetItemName(m_pItemList[m_stMCursor.sSelectedObjectID], cStr1, cStr2, cStr3);
            ZeroMemory(G_cTxt, sizeof(G_cTxt));
            wsprintfA(G_cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);//"
            AddEventList(G_cTxt, 10);
            if (memcmp(m_pItemList[m_stMCursor.sSelectedObjectID]->m_cName, "AngelicPendant", 14) == 0) PlaySound('E', 53, 0);
            else PlaySound('E', 29, 0);

            // Remove Angelic Stats
            if ((m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos >= 11)
                && (m_pItemList[m_stMCursor.sSelectedObjectID]->m_cItemType == 1))
            {
                char cItemID = m_stMCursor.sSelectedObjectID;
                if (memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(STR)", 19) == 0)
                {
                    m_iAngelicStr = 0;
                }
                else if (memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(DEX)", 19) == 0)
                {
                    m_iAngelicDex = 0;
                }
                else if (memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(INT)", 19) == 0)
                {
                    m_iAngelicInt = 0;
                }
                else if (memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(MAG)", 19) == 0)
                {
                    m_iAngelicMag = 0;
                }
            }
            bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_RELEASEITEM, 0, m_stMCursor.sSelectedObjectID, 0, 0, 0);
            m_bIsItemEquipped[m_stMCursor.sSelectedObjectID] = false;
            m_sItemEquipmentStatus[m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos] = -1;
            m_stMCursor.cSelectedObjectType = 0;
            m_stMCursor.sSelectedObjectID = 0;
        }
    }
}

void CGame::DlbBoxDoubleClick_GuideMap(short msX, short msY)
{
    short si = m_stMCursor.sCursorFrame;
    if (si != 0) return;
    if (m_cMapIndex < 0) return;

    short sX, sY, shX, shY, szX, szY;
    sX = m_stDialogBoxInfo[9].sX;
    sY = m_stDialogBoxInfo[9].sY;
    szX = m_stDialogBoxInfo[9].sSizeX;
    szY = m_stDialogBoxInfo[9].sSizeY;
    if (sX < 20) sX = 0;
    if (sY < 20) sY = 0;
    if (sX > 640 - 128 - 20) sX = 640 - 128;
    if (sY > 427 - 128 - 20) sY = 427 - 128;
    if (m_bZoomMap)
    {
        shX = m_sPlayerX - 64;
        shY = m_sPlayerY - 64;
        if (shX < 0) shX = 0;
        if (shY < 0) shY = 0;
        if (shX > m_pMapData->m_sMapSizeX - 128) shX = m_pMapData->m_sMapSizeX - 128;
        if (shY > m_pMapData->m_sMapSizeY - 128) shY = m_pMapData->m_sMapSizeY - 128;
        shX = shX + msX - sX;
        shY = shY + msY - sY;
    }
    else
    {
        shX = (m_pMapData->m_sMapSizeX * (msX - sX)) / 128;
        shY = (m_pMapData->m_sMapSizeX * (msY - sY)) / 128;
    }
    if (shX < 30 || shY < 30) return;
    if (shX > m_pMapData->m_sMapSizeX - 30 || shY > m_pMapData->m_sMapSizeY - 30) return;
    if ((m_bRunningMode == true) && (m_iSP > 0))
        m_cCommand = DEF_OBJECTRUN;
    else m_cCommand = DEF_OBJECTMOVE;
    m_sCommX = shX;
    m_sCommY = shY;
    GetPlayerTurn();
}

void CGame::DlbBoxDoubleClick_Inventory(short msX, short msY)
{
    register int i;
    char  cItemID, cTxt[120];
    short sX, sY, x1, x2, y1, y2;
    char cStr1[64], cStr2[64], cStr3[64];
    //if (m_iHP <= 0) return;
    if (m_bItemUsingStatus == true)
    {
        AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY1, 10); // "You can use after using the other item."
        return;
    }
    sX = m_stDialogBoxInfo[2].sX;
    sY = m_stDialogBoxInfo[2].sY;
    for (i = 0; i < DEF_MAXITEMS; i++)
    {
        if (m_cItemOrder[DEF_MAXITEMS - 1 - i] == -1) continue;
        cItemID = m_cItemOrder[DEF_MAXITEMS - 1 - i];
        if (m_pItemList[cItemID] == 0) continue;

        m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + 32 + m_pItemList[cItemID]->m_sX, sY + 44 + m_pItemList[cItemID]->m_sY, m_pItemList[cItemID]->m_sSpriteFrame);
        // Order
        x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
        y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
        x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
        y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;

        if ((m_bIsItemDisabled[cItemID] == false) && (m_bIsItemEquipped[cItemID] == false) && (msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
        {	// Order
            _SetItemOrder(0, cItemID);
            GetItemName(m_pItemList[cItemID], cStr1, cStr2, cStr3);

            if (m_bIsDialogEnabled[11] && (m_bIsDialogEnabled[23] == false) && (m_bIsDialogEnabled[23] == false) && (m_stDialogBoxInfo[39].sV3 == 24))
            {
                if (m_pItemList[cItemID]->m_cEquipPos != DEF_EQUIPPOS_NONE)
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_REPAIRITEM, 0, cItemID, m_stDialogBoxInfo[39].sV3, 0, m_pItemList[cItemID]->m_cName, m_stDialogBoxInfo[39].sV4); // v1.4
                    return;
                }
            }

            // DblClick Meats if Alchemy in progress
            if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EAT))		// 7
            {
                if (m_bIsDialogEnabled[26] == false) // bouffe pas le meat si alchi en cours
                {
                    if (bCheckItemOperationEnabled(cItemID) == false) return;
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, cItemID, 0, 0, 0);
                    m_bIsItemDisabled[cItemID] = true;
                    m_bItemUsingStatus = true;
                }
            }

            // DblClick scrolls & co
            if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE)	// 3
                || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_PERM)     // 9
                || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW))		// 6				
            {
                if (bCheckItemOperationEnabled(cItemID) == false) return;
                if ((unixtime() - m_dwDamagedTime) < 10000)
                {
                    if ((m_pItemList[cItemID]->m_sSprite == 6) && (m_pItemList[cItemID]->m_sSpriteFrame == 9))
                    {
                        wsprintfA(G_cTxt, BDLBBOX_DOUBLE_CLICK_INVENTORY3, cStr1);//"Item %s: Scrolls cannot be used until 10 seconds after taking damage."
                        AddEventList(G_cTxt, 10);
                        return;
                    }
                    if ((m_pItemList[cItemID]->m_sSprite == 6) && (m_pItemList[cItemID]->m_sSpriteFrame == 89))
                    {
                        wsprintfA(G_cTxt, BDLBBOX_DOUBLE_CLICK_INVENTORY3, cStr1);//"Item %s: Scrolls cannot be used until 10 seconds after taking damage."
                        AddEventList(G_cTxt, 10);
                        return;
                    }
                }
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, cItemID, 0, 0, 0);

                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE)
                    || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EAT))
                {
                    m_bIsItemDisabled[cItemID] = true;
                    m_bItemUsingStatus = true;
                }
            }

            if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_SKILL)		// 8
            {
                if (_bIsItemOnHand() == true)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);//"Your hands should be free to use this item."
                    return;
                }
                if (m_bSkillUsingStatus == true)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY5, 10);//"You are already using another skill."
                    return;
                }
                if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY6, 10);//"You can't use this item because it is exhausted."
                }
                else
                {
                    m_bIsGetPointingMode = true;
                    m_iPointCommandType = cItemID;
                    wsprintfA(cTxt, BDLBBOX_DOUBLE_CLICK_INVENTORY7, cStr1);//"Item %s: Select a position which you want to use."
                    AddEventList(cTxt, 10);
                }
            }

            if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE_DEST)	// 11
            {
                if (_bIsItemOnHand() == true)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);//"Your hands should be free to use this item."
                    return;
                }
                if (m_bSkillUsingStatus == true)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY13, 10);//"You are already using another skill."
                    return;
                }
                if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY6, 10);//"You can't use this item because it is exhausted."
                }
                else
                {
                    m_bIsGetPointingMode = true;
                    m_iPointCommandType = cItemID;
                    wsprintfA(cTxt, BDLBBOX_DOUBLE_CLICK_INVENTORY8, cStr1);//"Item %s: Select an item which you want to use."
                    AddEventList(cTxt, 10);
                }
            }

            if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX) // 10
            {
                if (_bIsItemOnHand() == true)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY4, 10);//"Your hands should be free to use this item."
                    return;
                }

                if (m_bSkillUsingStatus == true)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY5, 10);//"You are already using another skill."
                    return;
                }

                if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
                {
                    AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY6, 10);//"You can't use this item because it is exhausted."
                }
                else
                {
                    switch (m_pItemList[cItemID]->m_sSpriteFrame)
                    {
                        case 55: // Alchemy pot
                            if (m_cSkillMastery[12] == 0)
                            {
                                AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY9, 10);//"You should learn alchemy skill to use this item."
                            }
                            else
                            {
                                EnableDialogBox(26, 1, 0, 0, 0);
                                AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY10, 10);//"Using alchemy skill..."
                            }
                            break;
                        case 113: // Smith's Anvil
                            if (m_cSkillMastery[13] == 0)
                            {
                                AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY11, 10);//"You should learn manufacturing skill to use this item.."
                            }
                            else
                            {
                                EnableDialogBox(26, 3, 0, 0, 0);
                                AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY12, 10);//"Using a manufacturing skill..."
                            }
                            break;

                            // Crafting
                        case 0:
                            //if (m_pItemList[i]->m_sSprite == 22) 
                        {
                            EnableDialogBox(26, 7, 0, 0, 0);
                            AddEventList(BDLBBOX_DOUBLE_CLICK_INVENTORY17, 10);	//  "Initiating item Crafting..."
                        }
                        break;

                        case 151:
                        case 152:
                        case 153:
                        case 154:
                            EnableDialogBox(40, 1, 0, 0, 0);
                            break;
                    }
                }
            }
            // Dblclick Alchemy bowl
            if ((m_bIsDialogEnabled[26] == true) && (m_stDialogBoxInfo[26].cMode == 1))
            {
                bItemDrop_SkillDialog();
            }
            // Dblclick Manuf box
            if ((m_bIsDialogEnabled[26] == true) && (m_stDialogBoxInfo[26].cMode == 4))
            {
                bItemDrop_SkillDialog();
            }
            // Crafting
            // Dblclick Crafting box
            if ((m_bIsDialogEnabled[26] == true) && (m_stDialogBoxInfo[26].cMode == 7))
            {
                bItemDrop_SkillDialog();
            }
            if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EQUIP)
            {
                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                m_stMCursor.sSelectedObjectID = (short)cItemID;
                bItemDrop_Character();
                m_stMCursor.cSelectedObjectType = 0;
                m_stMCursor.sSelectedObjectID = 0;
            }
            return;
        }
    }
}

