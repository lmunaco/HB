//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include "Game.h"
#include "lan_eng.h"

extern char G_cSpriteAlphaDegree;

extern uint64_t unixtime();
extern uint64_t unixseconds();

void CGame::NotifyMsg_CannotGiveItem(char * pData)
{
    char * cp, cName[21], cTxt[256];
    uint16_t * wp, wItemIndex;
    int * ip, iAmount;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wItemIndex = *wp;
    cp += 2;

    ip = (int *)cp;
    iAmount = *ip;
    cp += 4;

    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[wItemIndex], cStr1, cStr2, cStr3);
    if (iAmount == 1) wsprintfA(cTxt, NOTIFYMSG_CANNOT_GIVE_ITEM2, cStr1, cName);
    else wsprintfA(cTxt, NOTIFYMSG_CANNOT_GIVE_ITEM1, iAmount, cStr1, cName);


    AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_DropItemFin_CountChanged(char * pData)
{
    char * cp, cTxt[256];
    uint16_t * wp, wItemIndex;
    int * ip, iAmount;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wItemIndex = *wp;
    cp += 2;

    ip = (int *)cp;
    iAmount = *ip;
    cp += 4;

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[wItemIndex]->m_cName, m_pItemList[wItemIndex]->m_dwAttribute, cStr1, cStr2, cStr3);
    wsprintfA(cTxt, NOTIFYMSG_THROW_ITEM1, iAmount, cStr1);

    AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_CannotJoinMoreGuildsMan(char * pData)
{
    char * cp, cName[12], cTxt[120];

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 10);

    wsprintfA(cTxt, NOTIFYMSG_CANNOT_JOIN_MOREGUILDMAN1, cName);
    AddEventList(cTxt, 10);
    AddEventList(NOTIFYMSG_CANNOT_JOIN_MOREGUILDMAN2, 10);
}

void CGame::NotifyMsg_DismissGuildsMan(char * pData)
{
    char * cp, cName[12], cTxt[120];
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 10);

    if (memcmp(m_cPlayerName, cName, 10) != 0)
    {
        wsprintfA(cTxt, NOTIFYMSG_DISMISS_GUILDMAN1, cName);
        AddEventList(cTxt, 10);
    }
    ClearGuildNameList();
}

void CGame::NotifyMsg_CannotRating(char * pData)
{
    char * cp, cTxt[120];
    uint16_t * wp, wTime;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wTime = *wp;
    cp += 2;

    if (wTime == 0) wsprintfA(cTxt, NOTIFYMSG_CANNOT_RATING1, wTime * 3);
    else wsprintfA(cTxt, NOTIFYMSG_CANNOT_RATING2, wTime * 3);
    AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_CannotRepairItem(char * pData)
{
    char * cp, cTxt[120], cStr1[64], cStr2[64], cStr3[64];
    uint16_t * wp, wV1, wV2;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wV1 = *wp;
    cp += 2;
    wp = (uint16_t *)cp;
    wV2 = *wp;
    cp += 2;
    ZeroMemory(cStr1, sizeof(cStr1));
    ZeroMemory(cStr2, sizeof(cStr2));
    ZeroMemory(cStr3, sizeof(cStr3));
    GetItemName(m_pItemList[wV1], cStr1, cStr2, cStr3);

    switch (wV2)
    {
        case 1:
            wsprintfA(cTxt, NOTIFYMSG_CANNOT_REPAIR_ITEM1, cStr1);
            AddEventList(cTxt, 10);
            break;
        case 2:
            wsprintfA(cTxt, NOTIFYMSG_CANNOT_REPAIR_ITEM2, cStr1);
            AddEventList(cTxt, 10);
            break;
    }
    m_bIsItemDisabled[wV1] = false;
}

void CGame::NotifyMsg_CannotSellItem(char * pData)
{
    char * cp, cTxt[120], cStr1[64], cStr2[64], cStr3[64];
    uint16_t * wp, wV1, wV2;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    wp = (uint16_t *)cp;
    wV1 = *wp;
    cp += 2;

    wp = (uint16_t *)cp;
    wV2 = *wp;
    cp += 2;

    ZeroMemory(cStr1, sizeof(cStr1));
    ZeroMemory(cStr2, sizeof(cStr2));
    ZeroMemory(cStr3, sizeof(cStr3));
    GetItemName(m_pItemList[wV1], cStr1, cStr2, cStr3);

    switch (wV2)
    {
        case 1:
            wsprintfA(cTxt, NOTIFYMSG_CANNOT_SELL_ITEM1, cStr1);//"
            AddEventList(cTxt, 10);
            break;

        case 2:
            wsprintfA(cTxt, NOTIFYMSG_CANNOT_SELL_ITEM2, cStr1);//"
            AddEventList(cTxt, 10);
            break;

        case 3:
            wsprintfA(cTxt, NOTIFYMSG_CANNOT_SELL_ITEM3, cStr1);//"
            AddEventList(cTxt, 10);
            AddEventList(NOTIFYMSG_CANNOT_SELL_ITEM4, 10);//"
            break;

        case 4:
            AddEventList(NOTIFYMSG_CANNOT_SELL_ITEM5, 10); // "
            AddEventList(NOTIFYMSG_CANNOT_SELL_ITEM6, 10); // "
            break;
    }
    m_bIsItemDisabled[wV1] = false;
}

void CGame::NotifyMsg_Charisma(char * pData)
{
    uint32_t * dwp;
    int  iPrevChar;
    char cTxt[120];

    iPrevChar = m_iCharisma;
    dwp = (uint32_t *)(pData + DEF_INDEX2_MSGTYPE + 2);
    m_iCharisma = (int)*dwp;

    if (m_iCharisma > iPrevChar)
    {
        wsprintfA(cTxt, NOTIFYMSG_CHARISMA_UP, m_iCharisma - iPrevChar);//"
        AddEventList(cTxt, 10);
        PlaySound('E', 21, 0);
    }
    else
    {
        wsprintfA(cTxt, NOTIFYMSG_CHARISMA_DOWN, iPrevChar - m_iCharisma);//"
        AddEventList(cTxt, 10);
    }
}

void CGame::NotifyMsg_DropItemFin_EraseItem(char * pData)
{
    char * cp;
    uint16_t * wp;
    int * ip, iAmount;
    short  sItemIndex;
    char   cTxt[120];

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    wp = (uint16_t *)cp;
    sItemIndex = *wp;
    cp += 2;

    ip = (int *)cp;
    iAmount = *ip;
    cp += 4;

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[sItemIndex], cStr1, cStr2, cStr3);

    ZeroMemory(cTxt, sizeof(cTxt));
    if (m_bIsItemEquipped[sItemIndex] == true)
    {
        wsprintfA(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
        AddEventList(cTxt, 10);
        m_sItemEquipmentStatus[m_pItemList[sItemIndex]->m_cEquipPos] = -1;
        m_bIsItemEquipped[sItemIndex] = false;
    }
    if (m_iHP > 0)
    {
        wsprintfA(cTxt, NOTIFYMSG_THROW_ITEM2, cStr1);
    }
    else
    {
        if (iAmount < 2)
            wsprintfA(cTxt, NOTIFYMSG_DROPITEMFIN_ERASEITEM3, cStr1); // "You dropped a %s."
        else
        {
            wsprintfA(cTxt, NOTIFYMSG_DROPITEMFIN_ERASEITEM5, cStr1); // "You dropped %s."
        }
    }
    AddEventList(cTxt, 10);
    EraseItem((char)sItemIndex);
    _bCheckBuildItemStatus();
}

void CGame::NotifyMsg_EnemyKillReward(char * pData)
{
    uint32_t * dwp;
    short * sp, sGuildRank;
    char * cp, cName[12], cGuildName[24], cTxt[120];
    int   iExp, iEnemyKillCount, iWarContribution;

    ZeroMemory(cName, sizeof(cName));
    ZeroMemory(cGuildName, sizeof(cGuildName));

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    dwp = (uint32_t *)cp;
    iExp = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iEnemyKillCount = *dwp;
    cp += 4;
    memcpy(cName, cp, 10);
    cp += 10;
    memcpy(cGuildName, cp, 20);
    cp += 20;
    sp = (short *)cp;
    sGuildRank = *sp;
    cp += 2;
    sp = (short *)cp;
    iWarContribution = *sp;
    cp += 2;

    if (iWarContribution > m_iWarContribution)
    {
        wsprintfA(G_cTxt, "%s +%d!", m_pGameMsgList[21]->m_pMsg, iWarContribution - m_iWarContribution);
        SetTopMsg(G_cTxt, 5);
    }
    else if (iWarContribution < m_iWarContribution)
    {
    }
    m_iWarContribution = iWarContribution;

    if (sGuildRank == -1)
    {
        wsprintfA(cTxt, NOTIFYMSG_ENEMYKILL_REWARD1, cName);
        AddEventList(cTxt, 10);
    }
    else
    {
        wsprintfA(cTxt, NOTIFYMSG_ENEMYKILL_REWARD2, cName, cGuildName);
        AddEventList(cTxt, 10);
    }

    /*	if( m_iExp != iExp )
        {	if (m_iExp > iExp) wsprintfA(cTxt, EXP_DECREASED,m_iExp - iExp);
            else wsprintfA(cTxt, EXP_INCREASED,iExp - m_iExp);
            AddEventList(cTxt, 10);
        }*/

    if (m_iEnemyKillCount != iEnemyKillCount)
    {
        if (m_iEnemyKillCount > iEnemyKillCount)
        {
            wsprintfA(cTxt, NOTIFYMSG_ENEMYKILL_REWARD5, m_iEnemyKillCount - iEnemyKillCount);//"Enemy-Kill-Count has been decreased by %dpoints."
            AddEventList(cTxt, 10);
            PlaySound('E', 24, 0); // son perdu 1 EK =(

        }
        else
        {
            wsprintfA(cTxt, NOTIFYMSG_ENEMYKILL_REWARD6, iEnemyKillCount - m_iEnemyKillCount);//"Enemy-Kill-Count has been increased by %dpoints."
            AddEventList(cTxt, 10);
            // Rajouté le son E48 en cas de victoire...(gros rire bien gras ....)
            PlaySound('E', 48, 0);
        }
    }
    else PlaySound('E', 23, 0);

    if (iExp >= 0) m_iExp = iExp;
    if (iEnemyKillCount >= 0) m_iEnemyKillCount = iEnemyKillCount;
}

void CGame::NotifyMsg_EventFishMode(char * pData)
{
    short sSprite, sSpriteFrame;
    char * cp, cName[21];
    uint16_t * wp, wPrice;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    wp = (uint16_t *)cp;
    wPrice = *wp;
    cp += 2;

    wp = (uint16_t *)cp;
    sSprite = (short)*wp;
    cp += 2;

    wp = (uint16_t *)cp;
    sSpriteFrame = (short)*wp;
    cp += 2;

    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;

    EnableDialogBox(24, 0, 0, wPrice, cName);
    m_stDialogBoxInfo[24].sV3 = sSprite;
    m_stDialogBoxInfo[24].sV4 = sSpriteFrame;

    AddEventList(NOTIFYMSG_EVENTFISHMODE1, 10);
}

void CGame::NotifyMsg_Exp(char * pData)
{
    uint32_t * dwp;
    int iPrevExp, * ip;
    char * cp, cTxt[120];

    iPrevExp = m_iExp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    dwp = (uint32_t *)cp;
    m_iExp = (int)*dwp;
    cp += 4;

    ip = (int *)cp;
    m_iRating = *ip;
    cp += 4;

    if (m_iExp > iPrevExp)
    {
        wsprintfA(cTxt, EXP_INCREASED, m_iExp - iPrevExp);
        AddEventList(cTxt, 10);
    }
    else
    {
        wsprintfA(cTxt, EXP_DECREASED, iPrevExp - m_iExp);
        AddEventList(cTxt, 10);
    }
}

void CGame::NotifyMsg_ForceDisconn(char * pData)
{
    uint16_t * wpCount;
    wpCount = (uint16_t *)(pData + 6);
    m_bForceDisconn = true;
    //m_cLogOutCount = (char)*wpCount;
    if (m_bIsProgramActive)
    {
        if (m_cLogOutCount < 0 || m_cLogOutCount > 5) m_cLogOutCount = 5;
        AddEventList(NOTIFYMSG_FORCE_DISCONN1, 10);
    }
    else
    {
        ws = nullptr;
        m_bEscPressed = false;
        if (m_bSoundFlag) m_pESound[38].stop();
        if ((m_bSoundFlag) && (m_bMusicStat == true))
        {
            m_pBGM.stop();
        }
        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
    }
}

void CGame::NotifyMsg_GiveItemFin_CountChanged(char * pData)
{
    char * cp, cName[21], cTxt[256];
    uint16_t * wp, wItemIndex;
    int * ip, iAmount;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wItemIndex = *wp;
    cp += 2;

    ip = (int *)cp;
    iAmount = *ip;
    cp += 4;

    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[wItemIndex]->m_cName, m_pItemList[wItemIndex]->m_dwAttribute, cStr1, cStr2, cStr3);
    if (iAmount == 1) wsprintfA(cTxt, NOTIFYMSG_GIVEITEMFIN_COUNTCHANGED1, cStr1, cName);
    wsprintfA(cTxt, NOTIFYMSG_GIVEITEMFIN_COUNTCHANGED2, iAmount, cStr1, cName);
    AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_GiveItemFin_EraseItem(char * pData)
{
    char * cp;
    uint16_t * wp;
    int * ip, iAmount;
    short  sItemIndex;
    char cName[21], cTxt[250];


    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    wp = (uint16_t *)cp;
    sItemIndex = *wp;
    cp += 2;

    ip = (int *)cp;
    iAmount = *ip;
    cp += 4;

    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[sItemIndex]->m_cName, m_pItemList[sItemIndex]->m_dwAttribute, cStr1, cStr2, cStr3);

    if (m_bIsItemEquipped[sItemIndex] == true)
    {
        wsprintfA(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
        AddEventList(cTxt, 10);

        // v1.42
        m_sItemEquipmentStatus[m_pItemList[sItemIndex]->m_cEquipPos] = -1;
        m_bIsItemEquipped[sItemIndex] = false;
    }
    if (strlen(cName) == 0) wsprintfA(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM2, iAmount, cStr1);
    else
    {
        if (strcmp(cName, "Howard") == 0)
            wsprintfA(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM3, iAmount, cStr1);
        else if (strcmp(cName, "William") == 0)
            wsprintfA(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM4, iAmount, cStr1);
        else if (strcmp(cName, "Kennedy") == 0)
            wsprintfA(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM5, iAmount, cStr1);
        else if (strcmp(cName, "Tom") == 0)
            wsprintfA(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM7, iAmount, cStr1);
        else wsprintfA(cTxt, NOTIFYMSG_GIVEITEMFIN_ERASEITEM8, iAmount, cStr1, cName);
    }
    AddEventList(cTxt, 10);
    EraseItem((char)sItemIndex);
    _bCheckBuildItemStatus();
}

void CGame::NotifyMsg_GlobalAttackMode(char * pData)
{
    char * cp;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    switch (*cp)
    {
        case 0:
            AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE1, 10);
            AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE2, 10);
            break;

        case 1:
            AddEventList(NOTIFYMSG_GLOBAL_ATTACK_MODE3, 10);
            break;
    }
    cp++;
}

void CGame::NotifyMsg_HP(char * pData)
{
    uint32_t * dwp;
    int iPrevHP;
    char cTxt[120];
    int iPrevMP;

    iPrevHP = m_iHP;
    dwp = (uint32_t *)(pData + DEF_INDEX2_MSGTYPE + 2);
    m_iHP = (int)*dwp;

    iPrevMP = m_iMP;
    dwp = (uint32_t *)(pData + DEF_INDEX2_MSGTYPE + 6);
    m_iMP = (int)*dwp;

    if (m_iHP > iPrevHP)
    {
        if ((m_iHP - iPrevHP) < 10) return;
        wsprintfA(cTxt, NOTIFYMSG_HP_UP, m_iHP - iPrevHP);
        AddEventList(cTxt, 10);
        PlaySound('E', 21, 0);
    }
    else
    {
        if ((m_cLogOutCount > 0) && (m_bForceDisconn == false))
        {
            m_cLogOutCount = -1;
            AddEventList(NOTIFYMSG_HP2, 10);//"Logout count cancels if HP decreases during the countdown."
        }
        m_dwDamagedTime = unixtime();
        if (m_iHP < 20) AddEventList(NOTIFYMSG_HP3, 10);
        if ((iPrevHP - m_iHP) < 10) return;
        wsprintfA(cTxt, NOTIFYMSG_HP_DOWN, iPrevHP - m_iHP);
        AddEventList(cTxt, 10);
    }
}

void CGame::NotifyMsg_Hunger(char * pData)
{
    char * cp, cHLv;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    cHLv = *cp;

    if ((cHLv <= 40) && (cHLv > 30)) AddEventList(NOTIFYMSG_HUNGER1, 10);//"
    if ((cHLv <= 25) && (cHLv > 20)) AddEventList(NOTIFYMSG_HUNGER2, 10);//"
    if ((cHLv <= 20) && (cHLv > 15)) AddEventList(NOTIFYMSG_HUNGER3, 10);//"
    if ((cHLv <= 15) && (cHLv > 10)) AddEventList(NOTIFYMSG_HUNGER4, 10);//"
    if ((cHLv <= 10) && (cHLv >= 0)) AddEventList(NOTIFYMSG_HUNGER5, 10);//"
}

void CGame::NotifyMsg_ItemColorChange(char * pData)
{
    short * sp, sItemIndex, sItemColor;
    char * cp;
    char cTxt[120];

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    sp = (short *)cp;
    sItemIndex = *sp;
    cp += 2;

    sp = (short *)cp;
    sItemColor = (short)*sp;
    cp += 2;

    if (m_pItemList[sItemIndex] != 0)
    {
        char cStr1[64], cStr2[64], cStr3[64];
        GetItemName(m_pItemList[sItemIndex], cStr1, cStr2, cStr3);
        if (sItemColor != -1)
        {
            m_pItemList[sItemIndex]->m_cItemColor = (char)sItemColor;
            wsprintfA(cTxt, NOTIFYMSG_ITEMCOLOR_CHANGE1, cStr1);
            AddEventList(cTxt, 10);
        }
        else
        {
            wsprintfA(cTxt, NOTIFYMSG_ITEMCOLOR_CHANGE2, cStr1);
            AddEventList(cTxt, 10);
        }
    }
}

void CGame::NotifyMsg_ItemDepleted_EraseItem(char * pData)
{
    char * cp;
    uint16_t * wp;
    short  sItemIndex;
    bool   bIsUseItemResult;
    char   cTxt[120];

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    wp = (uint16_t *)cp;
    sItemIndex = *wp;
    cp += 2;

    bIsUseItemResult = (bool)*cp;
    cp += 2;

    ZeroMemory(cTxt, sizeof(cTxt));

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[sItemIndex], cStr1, cStr2, cStr3);

    if (m_bIsItemEquipped[sItemIndex] == true)
    {
        wsprintfA(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
        AddEventList(cTxt, 10);
        m_sItemEquipmentStatus[m_pItemList[sItemIndex]->m_cEquipPos] = -1;
        m_bIsItemEquipped[sItemIndex] = false;
    }

    ZeroMemory(cTxt, sizeof(cTxt));
    if ((m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_CONSUME)
        || (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_ARROW))
    {
        wsprintfA(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM2, cStr1);
    }
    else
    {
        if (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE)
        {
            if (bIsUseItemResult == true)
            {
                wsprintfA(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM3, cStr1);
            }
        }
        else if (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_EAT)
        {
            if (bIsUseItemResult == true)
            {
                wsprintfA(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM4, cStr1);
                if ((m_sPlayerType >= 1) && (m_sPlayerType <= 3))
                    PlaySound('C', 19, 0);
                if ((m_sPlayerType >= 4) && (m_sPlayerType <= 6))
                    PlaySound('C', 20, 0);
            }
        }
        else if (m_pItemList[sItemIndex]->m_cItemType == DEF_ITEMTYPE_USE_DEPLETE_DEST)
        {
            if (bIsUseItemResult == true)
            {
                wsprintfA(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM3, cStr1);
            }
        }
        else
        {
            if (bIsUseItemResult == true)
            {
                wsprintfA(cTxt, NOTIFYMSG_ITEMDEPlETED_ERASEITEM6, cStr1);
                PlaySound('E', 10, 0);
            }
        }
    }
    AddEventList(cTxt, 10);

    if (bIsUseItemResult == true) 	m_bItemUsingStatus = false;
    EraseItem((char)sItemIndex);
    _bCheckBuildItemStatus();
}

void CGame::NotifyMsg_ItemLifeSpanEnd(char * pData)
{
    char * cp;
    short * sp, sEquipPos, sItemIndex;
    char cTxt[120];

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    sp = (short *)cp;
    sEquipPos = *sp;
    cp += 2;
    sp = (short *)cp;
    sItemIndex = *sp;
    cp += 2;

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[sItemIndex], cStr1, cStr2, cStr3);
    wsprintfA(cTxt, NOTIFYMSG_ITEMLIFE_SPANEND1, cStr1);
    AddEventList(cTxt, 10);
    m_sItemEquipmentStatus[m_pItemList[sItemIndex]->m_cEquipPos] = -1;
    m_bIsItemEquipped[sItemIndex] = false;
    m_pItemList[sItemIndex]->m_wCurLifeSpan = 0;

    PlaySound('E', 10, 0);
}

void CGame::NotifyMsg_ItemObtained(char * pData)
{
    char * cp;
    short * sp;
    uint32_t * dwp;
    int i, j;

    uint32_t dwCount, dwAttribute;
    char  cName[21], cItemType, cEquipPos;
    bool  bIsEquipped;
    short sSprite, sSpriteFrame, sLevelLimit, sSpecialEV2;
    char  cTxt[120], cGenderLimit, cItemColor;
    uint16_t * wp, wWeight, wCurLifeSpan;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    cp++;

    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;

    dwp = (uint32_t *)cp;
    dwCount = *dwp;
    cp += 4;

    cItemType = *cp;
    cp++;

    cEquipPos = *cp;
    cp++;

    bIsEquipped = (bool)*cp;
    cp++;

    sp = (short *)cp;
    sLevelLimit = *sp;
    cp += 2;

    cGenderLimit = *cp;
    cp++;

    wp = (uint16_t *)cp;
    wCurLifeSpan = *wp;
    cp += 2;

    wp = (uint16_t *)cp;
    wWeight = *wp;
    cp += 2;

    sp = (short *)cp;
    sSprite = *sp;
    cp += 2;

    sp = (short *)cp;
    sSpriteFrame = *sp;
    cp += 2;

    cItemColor = *cp;
    cp++;

    sSpecialEV2 = (short)*cp; // v1.41
    cp++;

    dwp = (uint32_t *)cp;
    dwAttribute = *dwp;
    cp += 4;
    /*
    bIsCustomMade = (bool)*cp;
    cp++;
    */

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(cName, dwAttribute, cStr1, cStr2, cStr3);

    ZeroMemory(cTxt, sizeof(cTxt));
    if (dwCount == 1) wsprintfA(cTxt, NOTIFYMSG_ITEMOBTAINED2, cStr1);
    else wsprintfA(cTxt, NOTIFYMSG_ITEMOBTAINED1, dwCount, cStr1);

    AddEventList(cTxt, 10);

    PlaySound('E', 20, 0);

    if ((cItemType == DEF_ITEMTYPE_CONSUME) || (cItemType == DEF_ITEMTYPE_ARROW))
    {
        for (i = 0; i < DEF_MAXITEMS; i++)
            if ((m_pItemList[i] != 0) && (memcmp(m_pItemList[i]->m_cName, cName, 20) == 0))
            {
                m_pItemList[i]->m_dwCount += dwCount;
                m_bIsItemDisabled[i] = false;
                return;
            }
    }

    short nX, nY;
    for (i = 0; i < DEF_MAXITEMS; i++)
    {
        if ((m_pItemList[i] != 0) && (memcmp(m_pItemList[i]->m_cName, cName, 20) == 0))
        {
            nX = m_pItemList[i]->m_sX;
            nY = m_pItemList[i]->m_sY;
            break;
        }
        else
        {
            nX = 40;
            nY = 30;
        }
    }


    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_pItemList[i] == 0)
        {
            m_pItemList[i] = new class CItem;
            memcpy(m_pItemList[i]->m_cName, cName, 20);
            m_pItemList[i]->m_dwCount = dwCount;
            //m_pItemList[i]->m_sX      =	40;
            //m_pItemList[i]->m_sY      =	30;
            m_pItemList[i]->m_sX = nX;
            m_pItemList[i]->m_sY = nY;
            bSendCommand(MSGID_REQUEST_SETITEMPOS, 0, i, nX, nY, 0, 0);
            m_pItemList[i]->m_cItemType = cItemType;
            m_pItemList[i]->m_cEquipPos = cEquipPos;
            m_bIsItemDisabled[i] = false;

            m_bIsItemEquipped[i] = false;
            m_pItemList[i]->m_sLevelLimit = sLevelLimit;
            m_pItemList[i]->m_cGenderLimit = cGenderLimit;
            m_pItemList[i]->m_wCurLifeSpan = wCurLifeSpan;
            m_pItemList[i]->m_wWeight = wWeight;
            m_pItemList[i]->m_sSprite = sSprite;
            m_pItemList[i]->m_sSpriteFrame = sSpriteFrame;
            m_pItemList[i]->m_cItemColor = cItemColor;
            m_pItemList[i]->m_sItemSpecEffectValue2 = sSpecialEV2; // v1.41
            m_pItemList[i]->m_dwAttribute = dwAttribute;
            //m_pItemList[i]->m_bIsCustomMade = bIsCustomMade;

            _bCheckBuildItemStatus();

            for (j = 0; j < DEF_MAXITEMS; j++)
                if (m_cItemOrder[j] == -1)
                {
                    m_cItemOrder[j] = i;
                    return;
                }
            return;
        }
}

void CGame::NotifyMsg_ItemPurchased(char * pData)
{
    char * cp;
    short * sp;
    uint32_t * dwp;
    uint16_t * wp;
    int i, j;

    uint32_t dwCount;
    char  cName[21], cItemType, cEquipPos, cGenderLimit;
    bool  bIsEquipped;
    short sSprite, sSpriteFrame, sLevelLimit;
    uint16_t  wCost, wWeight, wCurLifeSpan;
    char  cTxt[120], cItemColor;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    cp++;

    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;

    dwp = (uint32_t *)cp;
    dwCount = *dwp;
    cp += 4;

    cItemType = *cp;
    cp++;

    cEquipPos = *cp;
    cp++;

    bIsEquipped = (bool)*cp;
    cp++;

    sp = (short *)cp;
    sLevelLimit = *sp;
    cp += 2;

    cGenderLimit = *cp;
    cp++;

    wp = (uint16_t *)cp;
    wCurLifeSpan = *wp;
    cp += 2;

    wp = (uint16_t *)cp;
    wWeight = *wp;
    cp += 2;

    sp = (short *)cp;
    sSprite = *sp;
    cp += 2;

    sp = (short *)cp;
    sSpriteFrame = *sp;
    cp += 2;

    cItemColor = *cp; // v1.4
    cp++;

    wp = (uint16_t *)cp;
    wCost = *wp;
    ZeroMemory(cTxt, sizeof(cTxt));
    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(cName, 0, cStr1, cStr2, cStr3);
    wsprintfA(cTxt, NOTIFYMSG_ITEMPURCHASED, cStr1, wCost);
    AddEventList(cTxt, 10);

    if ((cItemType == DEF_ITEMTYPE_CONSUME) || (cItemType == DEF_ITEMTYPE_ARROW))
    {
        for (i = 0; i < DEF_MAXITEMS; i++)
            if ((m_pItemList[i] != 0) && (memcmp(m_pItemList[i]->m_cName, cName, 20) == 0))
            {
                m_pItemList[i]->m_dwCount += dwCount;
                return;
            }
    }

    short nX, nY;
    for (i = 0; i < DEF_MAXITEMS; i++)
    {
        if ((m_pItemList[i] != 0) && (memcmp(m_pItemList[i]->m_cName, cName, 20) == 0))
        {
            nX = m_pItemList[i]->m_sX;
            nY = m_pItemList[i]->m_sY;
            break;
        }
        else
        {
            nX = 40;
            nY = 30;
        }
    }

    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_pItemList[i] == 0)
        {
            m_pItemList[i] = new class CItem;
            memcpy(m_pItemList[i]->m_cName, cName, 20);
            m_pItemList[i]->m_dwCount = dwCount;
            //m_pItemList[i]->m_sX           = 40;
            //m_pItemList[i]->m_sY           = 30;
            m_pItemList[i]->m_sX = nX;
            m_pItemList[i]->m_sY = nY;
            bSendCommand(MSGID_REQUEST_SETITEMPOS, 0, i, nX, nY, 0, 0);
            m_pItemList[i]->m_cItemType = cItemType;
            m_pItemList[i]->m_cEquipPos = cEquipPos;
            m_bIsItemDisabled[i] = false;
            m_bIsItemEquipped[i] = false;
            m_pItemList[i]->m_sLevelLimit = sLevelLimit;
            m_pItemList[i]->m_cGenderLimit = cGenderLimit;
            m_pItemList[i]->m_wCurLifeSpan = wCurLifeSpan;
            m_pItemList[i]->m_wWeight = wWeight;
            m_pItemList[i]->m_sSprite = sSprite;
            m_pItemList[i]->m_sSpriteFrame = sSpriteFrame;
            m_pItemList[i]->m_cItemColor = cItemColor;    // v1.4

            // fixed v1.11
            for (j = 0; j < DEF_MAXITEMS; j++)
                if (m_cItemOrder[j] == -1)
                {
                    m_cItemOrder[j] = i;
                    return;
                }

            return;
        }
}

void CGame::NotifyMsg_ItemReleased(char * pData)
{
    char * cp;
    short * sp, sEquipPos, sItemIndex;
    char cTxt[120];

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    sp = (short *)cp;
    sEquipPos = *sp;
    cp += 2;
    sp = (short *)cp;
    sItemIndex = *sp;
    cp += 2;

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[sItemIndex], cStr1, cStr2, cStr3);
    wsprintfA(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
    AddEventList(cTxt, 10);

    /*	if (m_pItemList[sItemIndex]->m_cEquipPos != sEquipPos)
        {	wsprintfA(G_cTxt,"NotifyMsg_ItemReleased, sEquipPos sItemIndex mismatch: %s", cStr1);
            DebugLog(G_cTxt);
        }*/


    m_bIsItemEquipped[sItemIndex] = false;
    m_sItemEquipmentStatus[m_pItemList[sItemIndex]->m_cEquipPos] = -1;


    if (memcmp(m_pItemList[sItemIndex]->m_cName, "AngelicPendant", 14) == 0) PlaySound('E', 53, 0);
    else PlaySound('E', 29, 0);
}

void CGame::NotifyMsg_ItemRepaired(char * pData)
{
    char * cp, cTxt[120];
    uint32_t * dwp, dwItemID, dwLife;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    dwp = (uint32_t *)cp;
    dwItemID = *dwp;
    cp += 4;

    dwp = (uint32_t *)cp;
    dwLife = *dwp;
    cp += 4;

    m_pItemList[dwItemID]->m_wCurLifeSpan = (uint16_t)dwLife;
    m_bIsItemDisabled[dwItemID] = false;
    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[dwItemID], cStr1, cStr2, cStr3);

    wsprintfA(cTxt, NOTIFYMSG_ITEMREPAIRED1, cStr1);

    AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_ItemToBank(char * pData)
{
    char * cp, cIndex;
    uint32_t * dwp, dwCount, dwAttribute;
    char  cName[21], cItemType, cEquipPos, cGenderLimit, cItemColor;
    bool  bIsEquipped;
    short * sp, sSprite, sSpriteFrame, sLevelLimit, sItemEffectValue2, sItemSpecEffectValue2;
    uint16_t * wp, wWeight, wCurLifeSpan;
    char  cTxt[120];

    cp = (pData + DEF_INDEX2_MSGTYPE + 2);

    cIndex = *cp;
    cp++;

    cp++;

    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;

    dwp = (uint32_t *)cp;
    dwCount = *dwp;
    cp += 4;

    cItemType = *cp;
    cp++;

    cEquipPos = *cp;
    cp++;

    bIsEquipped = (bool)*cp;
    cp++;

    sp = (short *)cp;
    sLevelLimit = *sp;
    cp += 2;

    cGenderLimit = *cp;
    cp++;

    wp = (uint16_t *)cp;
    wCurLifeSpan = *wp;
    cp += 2;

    wp = (uint16_t *)cp;
    wWeight = *wp;
    cp += 2;

    sp = (short *)cp;
    sSprite = *sp;
    cp += 2;

    sp = (short *)cp;
    sSpriteFrame = *sp;
    cp += 2;

    cItemColor = *cp;
    cp++;

    // v1.432
    sp = (short *)cp;
    sItemEffectValue2 = *sp;
    cp += 2;

    dwp = (uint32_t *)cp;
    dwAttribute = *dwp;
    cp += 4;
    sItemSpecEffectValue2 = (short)*cp;
    cp++;

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(cName, dwAttribute, cStr1, cStr2, cStr3);


    if (m_pBankList[cIndex] == 0)
    {
        m_pBankList[cIndex] = new class CItem;

        memcpy(m_pBankList[cIndex]->m_cName, cName, 20);
        m_pBankList[cIndex]->m_dwCount = dwCount;

        m_pBankList[cIndex]->m_cItemType = cItemType;
        m_pBankList[cIndex]->m_cEquipPos = cEquipPos;

        m_pBankList[cIndex]->m_sLevelLimit = sLevelLimit;
        m_pBankList[cIndex]->m_cGenderLimit = cGenderLimit;
        m_pBankList[cIndex]->m_wCurLifeSpan = wCurLifeSpan;
        m_pBankList[cIndex]->m_wWeight = wWeight;
        m_pBankList[cIndex]->m_sSprite = sSprite;
        m_pBankList[cIndex]->m_sSpriteFrame = sSpriteFrame;
        m_pBankList[cIndex]->m_cItemColor = cItemColor;
        m_pBankList[cIndex]->m_sItemEffectValue2 = sItemEffectValue2;
        m_pBankList[cIndex]->m_dwAttribute = dwAttribute;
        m_pBankList[cIndex]->m_sItemSpecEffectValue2 = sItemSpecEffectValue2;

        ZeroMemory(cTxt, sizeof(cTxt));
        if (dwCount == 1) wsprintfA(cTxt, NOTIFYMSG_ITEMTOBANK3, cStr1);
        else wsprintfA(cTxt, NOTIFYMSG_ITEMTOBANK2, dwCount, cStr1);

        if (m_bIsDialogEnabled[14] == true) m_stDialogBoxInfo[14].sView = DEF_MAXBANKITEMS - 12;
        AddEventList(cTxt, 10);
    }
}

void CGame::NotifyMsg_Killed(char * pData)
{
    char * cp, cAttackerName[21];
    m_bCommandAvailable = false;
    m_cCommand = DEF_OBJECTSTOP;
    m_iHP = 0;
    m_cCommand = -1;
    // Restart
    m_bItemUsingStatus = false;
    ClearSkillUsingStatus();
    ZeroMemory(cAttackerName, sizeof(cAttackerName));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cAttackerName, cp, 20);
    cp += 20;
    /*	if (strlen(cAttackerName) == 0) // removed in v2.20 (bug?) Many servers send the info themselves.
            AddEventList(NOTIFYMSG_KILLED1, 10);//"you have died!"
        else
        {	wsprintfA(G_cTxt, NOTIFYMSG_KILLED2, cAttackerName);//"You were killed by %s's attack!"
            AddEventList(G_cTxt, 10);
        }*/
    AddEventList(NOTIFYMSG_KILLED1, 10);//"You have died!  Click the restart button in system menu "
    AddEventList(NOTIFYMSG_KILLED3, 10);//"to start again, or click the Log Out button to exit."
    //AddEventList(NOTIFYMSG_KILLED4, 10);//"Log Out
}

// This msg is sent by server when lvl-up
void CGame::NotifyMsg_LevelUp(char * pData)
{
    char * cp;
    int * ip;
    int i, iPrevLevel;
    char cTxt[120];

    iPrevLevel = m_iLevel;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    ip = (int *)cp;
    m_iLevel = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iStr = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iVit = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iDex = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iInt = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iMag = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iCharisma = *ip;
    cp += 4;

    m_iLU_Point = m_iLevel * 3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
    m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;

    wsprintfA(cTxt, NOTIFYMSG_LEVELUP1, m_iLevel);// "Level up!!! Level %d!"
    AddEventList(cTxt, 10);

    switch (m_sPlayerType)
    {
        case 1:
        case 2:
        case 3:
            PlaySound('C', 21, 0);
            break;

        case 4:
        case 5:
        case 6:
            PlaySound('C', 22, 0);
            break;
    }

    _RemoveChatMsgListByObjectID(m_sPlayerObjectID);

    for (i = 1; i < DEF_MAXCHATMSGS; i++)
        if (m_pChatMsgList[i] == 0)
        {
            ZeroMemory(cTxt, sizeof(cTxt));
            strcpy(cTxt, "Level up!");
            m_pChatMsgList[i] = new class CMsg(23, cTxt, m_dwCurTime);
            m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;

            if (m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i) == false)
            {
                delete m_pChatMsgList[i];
                m_pChatMsgList[i] = 0;
            }
            return;
        }
}

void CGame::NotifyMsg_SettingSuccess(char * pData)
{
    char * cp;
    int * ip;
    int iPrevLevel;
    char cTxt[120];
    iPrevLevel = m_iLevel;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    ip = (int *)cp;
    m_iLevel = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iStr = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iVit = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iDex = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iInt = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iMag = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iCharisma = *ip;
    cp += 4;
    wsprintfA(cTxt, "Your stat has been changed.");
    AddEventList(cTxt, 10);
    m_iLU_Point = m_iLevel * 3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
    m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
}

void CGame::NotifyMsg_MagicEffectOff(char * pData)
{
    char * cp;
    uint16_t * wp;
    short  sMagicType, sMagicEffect;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    sMagicType = (short)*wp;
    cp += 2;
    wp = (uint16_t *)cp;
    sMagicEffect = (short)*wp;
    cp += 2;
    switch (sMagicType)
    {
        case DEF_MAGICTYPE_PROTECT:
            switch (sMagicEffect)
            {
                case 1: // "Protection from arrows has vanished."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF1, 10);
                    break;
                case 2:	// "Protection from magic has vanished."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF2, 10);
                    break;
                case 3:	// "Defense shield effect has vanished."
                case 4:	// "Defense shield effect has vanished."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF3, 10);
                    break;
                case 5:	// "Absolute Magic Protection has been vanished."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF14, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_HOLDOBJECT:
            switch (sMagicEffect)
            {
                case 1:	// "Hold person magic effect has vanished."
                    m_bParalyze = false;
                    //m_bFullParalyze = false;
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF4, 10);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT // All para
                case 20:	// "Medusa kiss effect has vanished."
                    m_bParalyze = false;
                    m_bFullParalyze = false;
                    AddEventList("Medusa kiss effect has vanished.", 10);
                    break;

                default: //  other para level here
#endif

                case 2:	// "Paralysis magic effect has vanished."
                    m_bParalyze = false;
                    //m_bFullParalyze = false;
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF5, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_INVISIBILITY:
            switch (sMagicEffect)
            {
                case 1:	// "Invisibility magic effect has vanished."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF6, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_CONFUSE:
            switch (sMagicEffect)
            {
                case 1:	// "Language confuse magic effect has vanished."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF7, 10);
                    break;
                case 2:	// "Confusion magic has vanished."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF8, 10);
                    m_bIsConfusion = false;
                    break;
                case 3:	// "Illusion magic has vanished."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF9, 10);
                    m_iIlusionOwnerH = 0;
                    break;
                case 4:	// "At last, you gather your senses."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF15, 10);
                    m_bIllusionMVT = false;
                    break;
            }
            break;

        case DEF_MAGICTYPE_POISON:
            if (m_bIsPoisoned) AddEventList(NOTIFYMSG_MAGICEFFECT_OFF10, 10);
            m_bIsPoisoned = false;
            break;

        case DEF_MAGICTYPE_BERSERK:
            switch (sMagicEffect)
            {
                case 1:
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF11, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_POLYMORPH:
            switch (sMagicEffect)
            {
                case 1:
                    AddEventList(NOTIFYMSG_MAGICEFFECT_OFF12, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_ICE:
            AddEventList(NOTIFYMSG_MAGICEFFECT_OFF13, 10);
            break;
    }
}

void CGame::NotifyMsg_MagicEffectOn(char * pData)
{
    char * cp;
    uint32_t * dwp;
    uint16_t * wp;
    short  sMagicType, sMagicEffect, sOwnerH;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    sMagicType = (short)*wp;
    cp += 2;
    dwp = (uint32_t *)cp;
    sMagicEffect = (short)*dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    sOwnerH = (short)*dwp;
    cp += 4;
    switch (sMagicType)
    {
        case DEF_MAGICTYPE_PROTECT:
            switch (sMagicEffect)
            {
                case 1: // "You are completely protected from arrows!"
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON1, 10);
                    break;
                case 2: // "You are protected from magic!"
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON2, 10);
                    break;
                case 3: // "Defense ratio increased by a magic shield!"
                case 4: // "Defense ratio increased by a magic shield!"
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON3, 10);
                    break;
                case 5: // "You are completely protected from magic!"
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON14, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_HOLDOBJECT:
            switch (sMagicEffect)
            {
                case 1: // "You were bounded by a Hold Person spell! Unable to move!"
                    m_bParalyze = true;
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON4, 10);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT // All para
                case 20: // "You were kissed by a medusa spell! Unable to move a mere finger!"
                    m_bParalyze = true;
                    m_bFullParalyze = true;
                    AddEventList("You were kissed by a medusa spell! Unable to move a mere finger!", 10);
                    break;

                case 5: // "You were bounded by the power of the Medusa! Unable to move!"
                    m_bParalyze = true;
                    AddEventList("You were bounded by the power of the Medusa", 10);
                    break;

                default:
#endif
                case 2: // "You were bounded by a Paralysis spell! Unable to move!"
                    m_bParalyze = true;
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON5, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_INVISIBILITY:
            switch (sMagicEffect)
            {
                case 1: // "You are now invisible, no one can see you!"
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON6, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_CONFUSE:
            switch (sMagicEffect)
            {
                case 1:	// Confuse Language "No one understands you because of language confusion magic!"
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON7, 10);
                    break;

                case 2: // Confusion "Confusion magic casted, impossible to determine player allegience."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON8, 10);
                    m_bIsConfusion = true;
                    break;

                case 3:	// Illusion "Illusion magic casted, impossible to tell who is who!"
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON9, 10);
                    _SetIlusionEffect(sOwnerH);
                    break;

                case 4:	// IllusionMouvement "You are thrown into confusion, and you are flustered yourself."
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON15, 10);
                    m_bIllusionMVT = true;
                    break;
            }
            break;

        case DEF_MAGICTYPE_POISON:
            AddEventList(NOTIFYMSG_MAGICEFFECT_ON10, 10);
            m_bIsPoisoned = true;
            break;

        case DEF_MAGICTYPE_BERSERK:
            switch (sMagicEffect)
            {
                case 1:
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON11, 10);
                    break;
            }
            break;

        case DEF_MAGICTYPE_POLYMORPH:
            switch (sMagicEffect)
            {
                case 1:

#ifdef DEF_EQUILIBRIUM_PROJECT // Polymorph texts
                    if (m_sPlayerType <= 3)
                        AddEventList("Polymorph magic effect, you're now a male!", 10);
                    else
                        AddEventList("Polymorph magic effect, you became a woman!", 10);
#else
                    AddEventList(NOTIFYMSG_MAGICEFFECT_ON12, 10);
#endif

                    break;
            }
            break;

        case DEF_MAGICTYPE_ICE:
            AddEventList(NOTIFYMSG_MAGICEFFECT_ON13, 10);
            break;
    }
}

void CGame::NotifyMsg_MagicStudyFail(char * pData)
{
    char * cp, cMagicNum, cName[31], cFailCode;
    char cTxt[120];
    int * ip, iCost, iReqInt, iReqStr = 0;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    cFailCode = *cp;
    cp++;
    cMagicNum = *cp;
    cp++;
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 30);
    cp += 30;
    ip = (int *)cp;
    iCost = *ip;
    cp += 4;
    ip = (int *)cp;
    iReqInt = *ip;
    cp += 4;

    if (iCost > 0)
    {
        wsprintfA(cTxt, NOTIFYMSG_MAGICSTUDY_FAIL1, cName);
        AddEventList(cTxt, 10);
    }
    else
    {
        wsprintfA(cTxt, NOTIFYMSG_MAGICSTUDY_FAIL2, cName);
        AddEventList(cTxt, 10);
        wsprintfA(cTxt, NOTIFYMSG_MAGICSTUDY_FAIL3, iReqInt);
        AddEventList(cTxt, 10);
    }
}

void CGame::NotifyMsg_MagicStudySuccess(char * pData)
{
    char * cp, cMagicNum, cName[31];
    char cTxt[120];
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    cMagicNum = *cp;
    cp++;
    m_cMagicMastery[cMagicNum] = 1;
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 30);
    wsprintfA(cTxt, NOTIFYMSG_MAGICSTUDY_SUCCESS1, cName);
    AddEventList(cTxt, 10);
    PlaySound('E', 23, 0);
}

void CGame::NotifyMsg_MP(char * pData)
{
    uint32_t * dwp;
    int iPrevMP;
    char cTxt[120];
    iPrevMP = m_iMP;
    dwp = (uint32_t *)(pData + DEF_INDEX2_MSGTYPE + 2);
    m_iMP = (int)*dwp;
    if (abs(m_iMP - iPrevMP) < 10) return;
    if (m_iMP > iPrevMP)
    {
        wsprintfA(cTxt, NOTIFYMSG_MP_UP, m_iMP - iPrevMP);//"MP°
        AddEventList(cTxt, 10);
        PlaySound('E', 21, 0);
    }
    else
    {
        wsprintfA(cTxt, NOTIFYMSG_MP_DOWN, iPrevMP - m_iMP);//"MP°
        AddEventList(cTxt, 10);
    }
}

void CGame::NotifyMsg_NewGuildsMan(char * pData)
{
    char * cp, cName[12], cTxt[120];
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 10);
    wsprintfA(cTxt, NOTIFYMSG_NEW_GUILDMAN1, cName);
    AddEventList(cTxt, 10);
    ClearGuildNameList();
}

void CGame::NotifyMsg_PKcaptured(char * pData)
{
    char * cp;
    uint32_t * dwp;
    uint16_t * wp;
    int     iPKcount, iLevel, iExp, iRewardGold;
    char cTxt[120], cName[12];
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    iPKcount = *wp;
    cp += 2;
    wp = (uint16_t *)cp;
    iLevel = *wp;
    cp += 2;
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 10);
    cp += 10;
    dwp = (uint32_t *)cp;
    iRewardGold = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iExp = *dwp;
    cp += 4;
    wsprintfA(cTxt, NOTIFYMSG_PK_CAPTURED1, iLevel, cName, iPKcount);
    AddEventList(cTxt, 10);
    wsprintfA(cTxt, EXP_INCREASED, iExp - m_iExp);
    AddEventList(cTxt, 10);
    wsprintfA(cTxt, NOTIFYMSG_PK_CAPTURED3, iExp - m_iExp);
    AddEventList(cTxt, 10);
}

void CGame::NotifyMsg_PKpenalty(char * pData)
{
    char * cp;
    uint32_t * dwp;
    int     iPKcount, iExp, iStr, iVit, iDex, iInt, iMag, iChr;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    dwp = (uint32_t *)cp;
    iExp = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iStr = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iVit = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iDex = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iInt = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iMag = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iChr = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    iPKcount = *dwp;
    cp += 4;
    wsprintfA(G_cTxt, NOTIFYMSG_PK_PENALTY1, iPKcount);
    AddEventList(G_cTxt, 10);
    if (m_iExp > iExp)
    {
        wsprintfA(G_cTxt, NOTIFYMSG_PK_PENALTY2, m_iExp - iExp);
        AddEventList(G_cTxt, 10);
    }
    m_iExp = iExp;
    m_iStr = iStr;
    m_iVit = iVit;
    m_iDex = iDex;
    m_iInt = iInt;
    m_iMag = iMag;
    m_iCharisma = iChr;
    m_iPKCount = iPKcount;
}

void CGame::NotifyMsg_PlayerShutUp(char * pData)
{
    char * cp, cName[12];
    uint16_t * wp, wTime;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wTime = *wp;
    cp += 2;
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 10);
    cp += 10;
    if (memcmp(m_cPlayerName, cName, 10) == 0)
        wsprintfA(G_cTxt, NOTIFYMSG_PLAYER_SHUTUP1, wTime);
    else wsprintfA(G_cTxt, NOTIFYMSG_PLAYER_SHUTUP2, cName, wTime);

    AddEventList(G_cTxt, 10);
}

void CGame::NotifyMsg_PlayerStatus(bool bOnGame, char * pData)
{
    char cName[12], cMapName[12], * cp;
    uint16_t * wp;
    uint16_t  dx = 1, dy = 1;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 10);
    cp += 10;
    ZeroMemory(cMapName, sizeof(cMapName));
    memcpy(cMapName, cp, 10);
    cp += 10;
    wp = (uint16_t *)cp;
    dx = (uint16_t)*wp;
    cp += 2;
    wp = (uint16_t *)cp;
    dy = (uint16_t)*wp;
    cp += 2;
    ZeroMemory(G_cTxt, sizeof(G_cTxt));
    if (bOnGame == true)
    {
        if (strlen(cMapName) == 0)
            wsprintfA(G_cTxt, NOTIFYMSG_PLAYER_STATUS1, cName);
        else wsprintfA(G_cTxt, NOTIFYMSG_PLAYER_STATUS2, cName, cMapName, dx, dy);
    }
    else wsprintfA(G_cTxt, NOTIFYMSG_PLAYER_STATUS3, cName);
    AddEventList(G_cTxt, 10);
}

void CGame::NotifyMsg_QuestReward(char * pData)
{
    short * sp, sWho, sFlag;
    char * cp, cRewardName[21], cTxt[120];
    int * ip, iAmount, iIndex, iPreCon;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    sp = (short *)cp;
    sWho = *sp;
    cp += 2;
    sp = (short *)cp;
    sFlag = *sp;
    cp += 2;
    ip = (int *)cp;
    iAmount = *ip;
    cp += 4;
    ZeroMemory(cRewardName, sizeof(cRewardName));
    memcpy(cRewardName, cp, 20);
    cp += 20;
    iPreCon = m_iContribution;
    ip = (int *)cp;
    m_iContribution = *ip;
    m_iContributionPrice = 0;
    cp += 4;

    if (sFlag == 1)
    {
        m_stQuest.sWho = 0;
        m_stQuest.sQuestType = 0;
        m_stQuest.sContribution = 0;
        m_stQuest.sTargetType = 0;
        m_stQuest.sTargetCount = 0;
        m_stQuest.sX = 0;
        m_stQuest.sY = 0;
        m_stQuest.sRange = 0;
        m_stQuest.sCurrentCount = 0;
        m_stQuest.bIsQuestCompleted = false;
        ZeroMemory(m_stQuest.cTargetName, sizeof(m_stQuest.cTargetName));
        EnableDialogBox(21, 0, sWho + 110, 0);
        iIndex = m_stDialogBoxInfo[21].sV1;
        m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
        iIndex++;
        ZeroMemory(cTxt, sizeof(cTxt));
        if (memcmp(cRewardName, "°æÇèÄ¡", 6) == 0)
        {
            if (iAmount > 0) wsprintfA(cTxt, NOTIFYMSG_QUEST_REWARD1, iAmount);
        }
        else
        {
            wsprintfA(cTxt, NOTIFYMSG_QUEST_REWARD2, iAmount, cRewardName);
        }
        m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
        iIndex++;
        m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
        iIndex++;
        ZeroMemory(cTxt, sizeof(cTxt));
        if (iPreCon < m_iContribution)
            wsprintfA(cTxt, NOTIFYMSG_QUEST_REWARD3, m_iContribution - iPreCon);
        else wsprintfA(cTxt, NOTIFYMSG_QUEST_REWARD4, iPreCon - m_iContribution);

        m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
        iIndex++;
    }
    else EnableDialogBox(21, 0, sWho + 120, 0);
}

void CGame::NotifyMsg_RatingPlayer(char * pData)
{//int * ip;
    char * cp, cName[12];
    uint16_t  cValue;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    cValue = *cp;
    cp++;
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 10);
    cp += 10;
    //	ip = (int *)cp;
    //	m_iRating = *ip;
    cp += 4;
    ZeroMemory(G_cTxt, sizeof(G_cTxt));
    if (memcmp(m_cPlayerName, cName, 10) == 0)
    {
        if (cValue == 1)
        {
            strcpy(G_cTxt, NOTIFYMSG_RATING_PLAYER1);
            PlaySound('E', 23, 0);
        }
    }
    else
    {
        if (cValue == 1)
            wsprintfA(G_cTxt, NOTIFYMSG_RATING_PLAYER2, cName);
        else wsprintfA(G_cTxt, NOTIFYMSG_RATING_PLAYER3, cName);
    }
    AddEventList(G_cTxt, 10);
}

void CGame::NotifyMsg_ServerChange(char * pData)
{
    char * cp, cWorldServerAddr[16];
    int * ip, iWorldServerPort;

    ZeroMemory(m_cMapName, sizeof(m_cMapName));
    ZeroMemory(m_cMapMessage, sizeof(m_cMapMessage));
    ZeroMemory(cWorldServerAddr, sizeof(cWorldServerAddr));

    // v1.43
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(m_cMapName, cp, 10);

    //	m_cMapIndex = GetOfficialMapName(m_cMapName, m_cMapMessage);
    cp += 10;

    memcpy(cWorldServerAddr, cp, 15);
    cp += 15;
    ip = (int *)cp;
    iWorldServerPort = *ip;
    cp += 4;
    if (log_ws)
        log_ws = nullptr;
    if (ws)
        ws = nullptr;
    perform_login_connect();

    m_bIsPoisoned = false;

    ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
    m_dwConnectMode = MSGID_REQUEST_ENTERGAME;
    //m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW; //Gateway
    m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW_TOWLSBUTMLS;
    ZeroMemory(m_cMsg, sizeof(m_cMsg));
    strcpy(m_cMsg, "55");
}

void CGame::NotifyMsg_SetItemCount(char * pData)
{
    char * cp;
    uint16_t * wp;
    uint32_t * dwp;
    short  sItemIndex;
    uint32_t  dwCount;
    bool   bIsItemUseResponse;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    sItemIndex = *wp;
    cp += 2;
    dwp = (uint32_t *)cp;
    dwCount = *dwp;
    cp += 4;
    bIsItemUseResponse = (bool)*cp;
    cp++;
    if (m_pItemList[sItemIndex] != 0)
    {
        m_pItemList[sItemIndex]->m_dwCount = dwCount;
        if (bIsItemUseResponse == true) m_bIsItemDisabled[sItemIndex] = false;
    }
}

void CGame::NotifyMsg_ShowMap(char * pData)
{
    char * cp;
    uint16_t * wp, w1, w2;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    w1 = *wp;
    cp += 2;
    wp = (uint16_t *)cp;
    w2 = *wp;
    cp += 2;
    if (w2 == 0) AddEventList(NOTIFYMSG_SHOW_MAP1, 10);
    else EnableDialogBox(22, 0, w1, w2 - 1);
}

void CGame::NotifyMsg_Skill(char * pData)
{
    uint16_t * wp;
    short sSkillIndex, sValue;
    char * cp;
    char cTxt[120];
    int i;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    sSkillIndex = (short)*wp;
    cp += 2;
    wp = (uint16_t *)cp;
    sValue = (short)*wp;
    cp += 2;
    _RemoveChatMsgListByObjectID(m_sPlayerObjectID);
    if (m_pSkillCfgList[sSkillIndex]->m_iLevel < sValue)
    {
        wsprintfA(cTxt, NOTIFYMSG_SKILL1, m_pSkillCfgList[sSkillIndex]->m_cName, sValue - m_pSkillCfgList[sSkillIndex]->m_iLevel);
        AddEventList(cTxt, 10);
        PlaySound('E', 23, 0);
        for (i = 1; i < DEF_MAXCHATMSGS; i++)
            if (m_pChatMsgList[i] == 0)
            {
                ZeroMemory(cTxt, sizeof(cTxt));
                wsprintfA(cTxt, "%s +%d%%", m_pSkillCfgList[sSkillIndex]->m_cName, sValue - m_pSkillCfgList[sSkillIndex]->m_iLevel);
                m_pChatMsgList[i] = new class CMsg(20, cTxt, m_dwCurTime);
                m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;
                if (m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i) == false)
                {
                    delete m_pChatMsgList[i];
                    m_pChatMsgList[i] = 0;
                }
                break;
            }
    }
    else if (m_pSkillCfgList[sSkillIndex]->m_iLevel > sValue)
    {
        wsprintfA(cTxt, NOTIFYMSG_SKILL2, m_pSkillCfgList[sSkillIndex]->m_cName, m_pSkillCfgList[sSkillIndex]->m_iLevel - sValue);
        AddEventList(cTxt, 10);
        PlaySound('E', 24, 0);
        for (i = 1; i < DEF_MAXCHATMSGS; i++)
            if (m_pChatMsgList[i] == 0)
            {
                ZeroMemory(cTxt, sizeof(cTxt));
                wsprintfA(cTxt, "%s -%d%%", m_pSkillCfgList[sSkillIndex]->m_cName, sValue - m_pSkillCfgList[sSkillIndex]->m_iLevel);
                m_pChatMsgList[i] = new class CMsg(20, cTxt, m_dwCurTime);
                m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;
                if (m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i) == false)
                {
                    delete m_pChatMsgList[i];
                    m_pChatMsgList[i] = 0;
                }
                break;
            }
    }
    m_pSkillCfgList[sSkillIndex]->m_iLevel = sValue;
    m_cSkillMastery[sSkillIndex] = (unsigned char)sValue;
}

void CGame::NotifyMsg_SkillTrainSuccess(char * pData)
{
    char * cp, cSkillNum, cSkillLevel;
    char cTemp[120];
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    cSkillNum = *cp;
    cp++;
    cSkillLevel = *cp;
    cp++;
    ZeroMemory(cTemp, sizeof(cTemp));
    wsprintfA(cTemp, NOTIFYMSG_SKILL_TRAIN_SUCCESS1, m_pSkillCfgList[cSkillNum]->m_cName, cSkillLevel);
    AddEventList(cTemp, 10);
    m_pSkillCfgList[cSkillNum]->m_iLevel = cSkillLevel;
    m_cSkillMastery[cSkillNum] = (unsigned char)cSkillLevel;
    PlaySound('E', 23, 0);
}

void CGame::NotifyMsg_SkillUsingEnd(char * pData)
{
    char * cp;
    uint16_t * wp, wResult;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wResult = *wp;
    switch (wResult)
    {
        case 0:
            AddEventList(NOTIFYMSG_SKILL_USINGEND1, 10);
            break;
        case 1:
            AddEventList(NOTIFYMSG_SKILL_USINGEND2, 10);
            break;
    }
    m_bSkillUsingStatus = false;
}

void CGame::NotifyMsg_SP(char * pData)
{
    uint32_t * dwp;
    int iPrevSP;
    iPrevSP = m_iSP;
    dwp = (uint32_t *)(pData + DEF_INDEX2_MSGTYPE + 2);
    m_iSP = (int)*dwp;
    if (abs(m_iSP - iPrevSP) < 10) return;
    if (m_iSP > iPrevSP)
    {
        wsprintfA(G_cTxt, NOTIFYMSG_SP_UP, m_iSP - iPrevSP);
        AddEventList(G_cTxt, 10);
        PlaySound('E', 21, 0);
    }
    else
    {
        wsprintfA(G_cTxt, NOTIFYMSG_SP_DOWN, iPrevSP - m_iSP);
        AddEventList(G_cTxt, 10);
    }
}

void CGame::NotifyMsg_TotalUsers(char * pData)
{
    uint16_t * wp;
    int iTotal;
    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE + 2);
    iTotal = (int)*wp;
    wsprintfA(G_cTxt, NOTIFYMSG_TOTAL_USER1, iTotal);
    AddEventList(G_cTxt, 10);
}

void CGame::NotifyMsg_WhisperMode(bool bActive, char * pData)
{
    char cName[12], * cp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 10);
    if (bActive == true)
    {
        wsprintfA(G_cTxt, NOTIFYMSG_WHISPERMODE1, cName);
        if (m_pWhisperMsg[DEF_MAXWHISPERMSG - 1] != 0)
        {
            delete m_pWhisperMsg[DEF_MAXWHISPERMSG - 1];
            m_pWhisperMsg[DEF_MAXWHISPERMSG - 1] = 0;
        }
        for (int i = DEF_MAXWHISPERMSG - 2; i >= 0; i--)
        {
            m_pWhisperMsg[i + 1] = m_pWhisperMsg[i];
            m_pWhisperMsg[i] = 0;
        }
        m_pWhisperMsg[0] = new class CMsg(0, cName, 0);
        m_cWhisperIndex = 0;
    }
    else wsprintfA(G_cTxt, NOTIFYMSG_WHISPERMODE2, cName);

    AddEventList(G_cTxt, 10);
}


void CGame::NotifyMsg_JoinGuildReject(char * pData)
{
    char * cp, cName[21];
    ZeroMemory(cName, sizeof(cName));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cName, cp, 20);
    cp += 20;
    EnableDialogBox(8, 0, 0, 0);
    _PutGuildOperationList(cName, 4);
}


void CGame::NotifyMsg_SetExchangeItem(char * pData)
{
    short * sp, sDir, sSprite, sSpriteFrame, sCurLife, sMaxLife, sPerformance;
    int * ip, iAmount, i;
    char * cp, cColor, cItemName[24], cCharName[12];
    uint32_t * dwp, dwAttribute;
    ZeroMemory(cItemName, sizeof(cItemName));
    ZeroMemory(cCharName, sizeof(cCharName));

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    sp = (short *)cp;
    sDir = *sp;
    cp += 2;
    sp = (short *)cp;
    sSprite = *sp;
    cp += 2;
    sp = (short *)cp;
    sSpriteFrame = *sp;
    cp += 2;
    ip = (int *)cp;
    iAmount = *ip;
    cp += 4;
    cColor = *cp;
    cp++;
    sp = (short *)cp;
    sCurLife = *sp;
    cp += 2;
    sp = (short *)cp;
    sMaxLife = *sp;
    cp += 2;
    sp = (short *)cp;
    sPerformance = *sp;
    cp += 2;
    memcpy(cItemName, cp, 20);
    cp += 20;
    memcpy(cCharName, cp, 10);
    cp += 10;
    dwp = (uint32_t *)cp;
    dwAttribute = *dwp;
    cp += 4;

    if (sDir >= 1000)  // Set the item I want to exchange
    {
        i = 0;
        while (m_stDialogBoxExchangeInfo[i].sV1 != -1)
        {
            i++;
            if (i >= 4) return; // Error situation
        }
    }
    else // Set the item he proposes me.
    {
        i = 4;
        while (m_stDialogBoxExchangeInfo[i].sV1 != -1)
        {
            i++;
            if (i >= 8) return; // Error situation
        }
    }
    m_stDialogBoxExchangeInfo[i].sV1 = sSprite;
    m_stDialogBoxExchangeInfo[i].sV2 = sSpriteFrame;
    m_stDialogBoxExchangeInfo[i].sV3 = iAmount;
    m_stDialogBoxExchangeInfo[i].sV4 = cColor;
    m_stDialogBoxExchangeInfo[i].sV5 = (int)sCurLife;
    m_stDialogBoxExchangeInfo[i].sV6 = (int)sMaxLife;
    m_stDialogBoxExchangeInfo[i].sV7 = (int)sPerformance;
    memcpy(m_stDialogBoxExchangeInfo[i].cStr1, cItemName, 20);
    memcpy(m_stDialogBoxExchangeInfo[i].cStr2, cCharName, 10);
    m_stDialogBoxExchangeInfo[i].dwV1 = dwAttribute;
    //if (i<4) m_stDialogBoxExchangeInfo[i].sItemID = sDir -1000;
}

void CGame::NotifyMsg_DismissGuildApprove(char * pData)
{
    char * cp, cName[24], cLocation[12];
    ZeroMemory(cName, sizeof(cName));
    ZeroMemory(cLocation, sizeof(cLocation));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cName, cp, 20);
    cp += 20;
    cp += 2;
    memcpy(cLocation, cp, 10);
    cp += 10;
    ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
    m_iGuildRank = -1;
    ZeroMemory(m_cLocation, sizeof(m_cLocation));
    memcpy(m_cLocation, cLocation, 10);
    if (memcmp(m_cLocation, "aresden", 7) == 0)
    {
        m_bAresden = true;
        m_bCitizen = true;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "arehunter", 9) == 0)
    {
        m_bAresden = true;
        m_bCitizen = true;
        m_bHunter = true;
    }
    else if (memcmp(m_cLocation, "elvine", 6) == 0)
    {
        m_bAresden = false;
        m_bCitizen = true;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "elvhunter", 9) == 0)
    {
        m_bAresden = false;
        m_bCitizen = true;
        m_bHunter = true;

#ifdef DEF_EQUILIBRIUM_PROJECT // m_bAresden, m_bCitizen, m_bHunter for me ready for later fix
    }
    else if (memcmp(m_cLocation, "executor", 8) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "evil", 4) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "NONE", 4) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = true;
#endif

    }
    else
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = true;
    }
    EnableDialogBox(8, 0, 0, 0);
    _PutGuildOperationList(cName, 5);
}

void CGame::NotifyMsg_DismissGuildReject(char * pData)
{
    char * cp, cName[21];
    ZeroMemory(cName, sizeof(cName));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cName, cp, 20);
    cp += 20;
    EnableDialogBox(8, 0, 0, 0);
    _PutGuildOperationList(cName, 6);
}

void CGame::NotifyMsg_DownSkillIndexSet(char * pData)
{
    uint16_t * wp;
    short sSkillIndex;
    char * cp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    sSkillIndex = (short)*wp;
    cp += 2;
    m_iDownSkillIndex = sSkillIndex;
    m_stDialogBoxInfo[15].bFlag = false;
}

void CGame::NotifyMsg_FishChance(char * pData)
{
    int iFishChance;
    char * cp;
    uint16_t * wp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    iFishChance = (int)*wp;
    cp += 2;
    m_stDialogBoxInfo[24].sV1 = iFishChance;
}

void CGame::NotifyMsg_GuildDisbanded(char * pData)
{
    char * cp, cName[24], cLocation[12];
    ZeroMemory(cName, sizeof(cName));
    ZeroMemory(cLocation, sizeof(cLocation));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cName, cp, 20);
    cp += 20;
    memcpy(cLocation, cp, 10);
    cp += 10;
    m_Misc.ReplaceString(cName, '_', ' ');
    EnableDialogBox(8, 0, 0, 0);
    _PutGuildOperationList(cName, 7);
    ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
    m_iGuildRank = -1;
    ZeroMemory(m_cLocation, sizeof(m_cLocation));
    memcpy(m_cLocation, cLocation, 10);
    if (memcmp(m_cLocation, "aresden", 7) == 0)
    {
        m_bAresden = true;
        m_bCitizen = true;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "arehunter", 9) == 0)
    {
        m_bAresden = true;
        m_bCitizen = true;
        m_bHunter = true;
    }
    else if (memcmp(m_cLocation, "elvine", 6) == 0)
    {
        m_bAresden = false;
        m_bCitizen = true;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "elvhunter", 9) == 0)
    {
        m_bAresden = false;
        m_bCitizen = true;
        m_bHunter = true;

#ifdef DEF_EQUILIBRIUM_PROJECT // m_bAresden, m_bCitizen, m_bHunter for me ready for later fix
    }
    else if (memcmp(m_cLocation, "executor", 8) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "evil", 4) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "NONE", 4) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = true;
#endif

    }
    else
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = true;
    }
}

void CGame::NotifyMsg_WhetherChange(char * pData)
{
    char * cp;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    m_cWhetherStatus = *cp;
    cp++;

    if (m_cWhetherStatus != 0)
        SetWhetherStatus(true, m_cWhetherStatus);
    else SetWhetherStatus(false, 0);
}

void CGame::NotifyMsg_TimeChange(char * pData)
{
    char * cp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    G_cSpriteAlphaDegree = *cp;
    switch (G_cSpriteAlphaDegree)
    {
        case 1:	m_bIsXmas = false; PlaySound('E', 32, 0); break;
        case 2: m_bIsXmas = false; PlaySound('E', 31, 0); break;
        case 3:
            if (m_cWhetherEffectType > 3) m_bIsXmas = true;
            else m_bIsXmas = false;
            PlaySound('E', 31, 0);
            G_cSpriteAlphaDegree = 2; break;
    }
    m_cGameModeCount = 1;
    m_bIsRedrawPDBGS = true;
}

void CGame::NotifyMsg_RepairItemPrice(char * pData)
{
    char * cp, cName[21];
    uint32_t * dwp, wV1, wV2, wV3, wV4;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    dwp = (uint32_t *)cp;
    wV1 = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    wV2 = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    wV3 = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    wV4 = *dwp;
    cp += 4;
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;
    EnableDialogBox(23, 2, wV1, wV2);
    m_stDialogBoxInfo[23].sV3 = wV3;
}

void CGame::NotifyMsg_SellItemPrice(char * pData)
{
    char * cp, cName[21];
    uint32_t * dwp, wV1, wV2, wV3, wV4;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    dwp = (uint32_t *)cp;
    wV1 = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    wV2 = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    wV3 = *dwp;
    cp += 4;
    dwp = (uint32_t *)cp;
    wV4 = *dwp;
    cp += 4;
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, cp, 20);
    cp += 20;
    EnableDialogBox(23, 1, wV1, wV2);
    m_stDialogBoxInfo[23].sV3 = wV3;
    m_stDialogBoxInfo[23].sV4 = wV4;
}

void CGame::NotifyMsg_QueryDismissGuildPermission(char * pData)
{
    char * cp, cName[12];
    ZeroMemory(cName, sizeof(cName));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cName, cp, 10);
    cp += 10;
    EnableDialogBox(8, 0, 0, 0);
    _PutGuildOperationList(cName, 2);
}


void CGame::NotifyMsg_QueryJoinGuildPermission(char * pData)
{
    char * cp, cName[12];
    ZeroMemory(cName, sizeof(cName));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cName, cp, 10);
    cp += 10;
    EnableDialogBox(8, 0, 0, 0);
    _PutGuildOperationList(cName, 1);
}


void CGame::NotifyMsg_QuestContents(char * pData)
{
    short * sp;
    char * cp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    sp = (short *)cp;
    m_stQuest.sWho = *sp;
    cp += 2;
    sp = (short *)cp;
    m_stQuest.sQuestType = *sp;
    cp += 2;
    sp = (short *)cp;
    m_stQuest.sContribution = *sp;
    cp += 2;
    sp = (short *)cp;
    m_stQuest.sTargetType = *sp;
    cp += 2;
    sp = (short *)cp;
    m_stQuest.sTargetCount = *sp;
    cp += 2;
    sp = (short *)cp;
    m_stQuest.sX = *sp;
    cp += 2;
    sp = (short *)cp;
    m_stQuest.sY = *sp;
    cp += 2;
    sp = (short *)cp;
    m_stQuest.sRange = *sp;
    cp += 2;
    sp = (short *)cp;
    m_stQuest.bIsQuestCompleted = (bool)*sp;
    cp += 2;
    ZeroMemory(m_stQuest.cTargetName, sizeof(m_stQuest.cTargetName));
    memcpy(m_stQuest.cTargetName, cp, 20);
    cp += 20;
    // v2.05
    //AddEventList(m_pGameMsgList[92]->m_pMsg, 10);
}

void CGame::NotifyMsg_PlayerProfile(char * pData)
{
    char * cp;
    char cTemp[500];
    int i;
    ZeroMemory(cTemp, sizeof(cTemp));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    strcpy(cTemp, cp);
    for (i = 0; i < 500; i++)
        if (cTemp[i] == '_') cTemp[i] = ' ';
    AddEventList(cTemp, 10);
}

void CGame::NotifyMsg_NoticeMsg(char * pData)
{
    char * cp, cMsg[1000];
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    strcpy(cMsg, cp);
    AddEventList(cMsg, 10);
}

void CGame::NotifyMsg_OpenExchageWindow(char * pData)
{
    short * sp, sDir, sSprite, sSpriteFrame, sCurLife, sMaxLife, sPerformance;
    int * ip, iAmount;
    char * cp, cColor, cItemName[24], cCharName[12];
    uint32_t * dwp, dwAttribute;
    ZeroMemory(cItemName, sizeof(cItemName));
    ZeroMemory(cCharName, sizeof(cCharName));

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    sp = (short *)cp;
    sDir = *sp;
    cp += 2;
    sp = (short *)cp;
    sSprite = *sp;
    cp += 2;
    sp = (short *)cp;
    sSpriteFrame = *sp;
    cp += 2;
    ip = (int *)cp;
    iAmount = *ip;
    cp += 4;
    cColor = *cp;
    cp++;
    sp = (short *)cp;
    sCurLife = *sp;
    cp += 2;
    sp = (short *)cp;
    sMaxLife = *sp;
    cp += 2;
    sp = (short *)cp;
    sPerformance = *sp;
    cp += 2;
    memcpy(cItemName, cp, 20);
    cp += 20;
    memcpy(cCharName, cp, 10);
    cp += 10;
    dwp = (uint32_t *)cp;
    dwAttribute = *dwp;
    cp += 4;

    EnableDialogBox(27, 1, 0, 0, 0);
    int i;
    if (sDir >= 1000)  // Set the item I want to exchange
    {
        i = 0;
        while (m_stDialogBoxExchangeInfo[i].sV1 != -1)
        {
            i++;
            if (i >= 4) return; // Error situation
        }
        if ((sDir > 1000) && (i == 0))
        {
            m_bIsItemDisabled[sDir - 1000] = true;
            m_stDialogBoxExchangeInfo[0].sItemID = sDir - 1000;
        }
    }
    else // Set the item he proposes me.
    {
        i = 4;
        while (m_stDialogBoxExchangeInfo[i].sV1 != -1)
        {
            i++;
            if (i >= 8) return; // Error situation
        }
    }
    m_stDialogBoxExchangeInfo[i].sV1 = sSprite;
    m_stDialogBoxExchangeInfo[i].sV2 = sSpriteFrame;
    m_stDialogBoxExchangeInfo[i].sV3 = iAmount;
    m_stDialogBoxExchangeInfo[i].sV4 = cColor;
    m_stDialogBoxExchangeInfo[i].sV5 = (int)sCurLife;
    m_stDialogBoxExchangeInfo[i].sV6 = (int)sMaxLife;
    m_stDialogBoxExchangeInfo[i].sV7 = (int)sPerformance;
    memcpy(m_stDialogBoxExchangeInfo[i].cStr1, cItemName, 20);
    memcpy(m_stDialogBoxExchangeInfo[i].cStr2, cCharName, 10);
    m_stDialogBoxExchangeInfo[i].dwV1 = dwAttribute;
}

void CGame::NotifyMsg_JoinGuildApprove(char * pData)
{
    char * cp, cName[21];
    short * sp;
    ZeroMemory(cName, sizeof(cName));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cName, cp, 20);
    cp += 20;
    sp = (short *)cp;
    cp += 2;
    ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
    strcpy(m_cGuildName, cName);
    m_iGuildRank = *sp;
    EnableDialogBox(8, 0, 0, 0);
    _PutGuildOperationList(cName, 3);
}


void CGame::NotifyMsg_AdminInfo(char * pData)
{
    char * cp, cStr[256];
    int * ip, iV1, iV2, iV3, iV4, iV5;

    cp = (char *)(pData + 6);

    ip = (int *)cp;
    iV1 = *ip;
    cp += 4;

    ip = (int *)cp;
    iV2 = *ip;
    cp += 4;

    ip = (int *)cp;
    iV3 = *ip;
    cp += 4;

    ip = (int *)cp;
    iV4 = *ip;
    cp += 4;

    ip = (int *)cp;
    iV5 = *ip;
    cp += 4;

    ZeroMemory(cStr, sizeof(cStr));
    wsprintfA(cStr, "%d %d %d %d %d", iV1, iV2, iV3, iV4, iV5);
    AddEventList(cStr);
}


void CGame::NotifyMsg_BanGuildMan(char * pData)
{
    char * cp, cName[24], cLocation[12];
    ZeroMemory(cName, sizeof(cName));
    ZeroMemory(cLocation, sizeof(cLocation));
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    memcpy(cName, cp, 20);
    cp += 20;
    cp += 2;
    memcpy(cLocation, cp, 10);
    cp += 10;
    ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
    m_iGuildRank = -1;
    ZeroMemory(m_cLocation, sizeof(m_cLocation));
    memcpy(m_cLocation, cLocation, 10);
    if (memcmp(m_cLocation, "aresden", 7) == 0)
    {
        m_bAresden = true;
        m_bCitizen = true;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "arehunter", 9) == 0)
    {
        m_bAresden = true;
        m_bCitizen = true;
        m_bHunter = true;
    }
    else if (memcmp(m_cLocation, "elvine", 6) == 0)
    {
        m_bAresden = false;
        m_bCitizen = true;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "elvhunter", 9) == 0)
    {
        m_bAresden = false;
        m_bCitizen = true;
        m_bHunter = true;

#ifdef DEF_EQUILIBRIUM_PROJECT // m_bAresden, m_bCitizen, m_bHunter for me ready for later fix
    }
    else if (memcmp(m_cLocation, "executor", 8) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "evil", 4) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = false;
    }
    else if (memcmp(m_cLocation, "NONE", 4) == 0)
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = true;
#endif
    }
    else
    {
        m_bAresden = true;
        m_bCitizen = false;
        m_bHunter = true;
    }
    EnableDialogBox(8, 0, 0, 0);
    _PutGuildOperationList(cName, 8);
}


void CGame::NotifyMsgHandler(char * pData)
{
    uint32_t * dwp;
    uint64_t dwTime, dwTemp;
    uint16_t * wp, wEventType;
    char * cp, cTemp[510], cTxt[120];
    short * sp, sX, sY, sV1, sV2, sV3, sV4, sV5, sV6, sV7, sV8, sV9;
    int * ip, i, iV1, iV2, iV3, iV4;

    dwTime = unixtime();

    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    wEventType = *wp;

    switch (wEventType)
    {

        case DEF_NOTIFY_SLATE_BERSERK:
            AddEventList(DEF_MSG_NOTIFY_SLATE_BERSERK, 10);//"Berserk magic casted!"
            m_bUsingSlate = true;
            break;

        case DEF_NOTIFY_LOTERY_LOST:
            AddEventList(DEF_MSG_NOTIFY_LOTERY_LOST, 10);//"You draw a blank. Please try again next time.."
            break;

        case DEF_NOTIFY_0BEF:				// 0x0BEF: // Crash or closes the client? (Calls SE entry !)
            // I'm noot sure at all of this function's result, so let's quit game...

            break;

        case DEF_NOTIFY_CRAFTING_SUCCESS:
            m_iContribution -= m_iContributionPrice;
            m_iContributionPrice = 0;
            DisableDialogBox(25);
            AddEventList(NOTIFY_MSG_HANDLER42, 10);		// "Item manufacture success!"
            PlaySound('E', 23, 5);
            switch (m_sPlayerType)
            {
                case 1:
                case 2:
                case 3:
                    PlaySound('C', 21, 0);
                    break;
                case 4:
                case 5:
                case 6:
                    PlaySound('C', 22, 0);
                    break;
            }
            break;

        case DEF_NOTIFY_CRAFTING_FAIL:
            m_iContributionPrice = 0;
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            iV1 = *ip; // Error reason
            switch (iV1)
            {
                case 1:
                    AddEventList(DEF_MSG_NOTIFY_CRAFTING_NO_PART, 10);		// "There is not enough material"		
                    PlaySound('E', 24, 5);
                    break;
                case 2:
                    AddEventList(DEF_MSG_NOTIFY_CRAFTING_NO_CONTRIB, 10);	// "There is not enough Contribution Point"	
                    PlaySound('E', 24, 5);
                    break;
                default:
                case 3:
                    AddEventList(DEF_MSG_NOTIFY_CRAFTING_FAILED, 10);		// "Crafting failed"	
                    PlaySound('E', 24, 5);
                    break;
            }
            break;

        case DEF_NOTIFY_ANGELIC_STATS:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            m_iAngelicStr = *ip;  // m_iAngelicStr
            cp += 4;
            ip = (int *)cp;
            m_iAngelicInt = *ip;  // m_iAngelicInt
            cp += 4;
            ip = (int *)cp;
            m_iAngelicDex = *ip;  // m_iAngelicDex
            cp += 4;
            ip = (int *)cp;
            m_iAngelicMag = *ip;  // m_iAngelicMag
            break;

        case DEF_NOTIFY_ITEM_CANT_RELEASE:
            AddEventList(DEF_MSG_NOTIFY_NOT_RELEASED, 10);//"Item cannot be released"			
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ItemEquipHandler(*cp);
            break;

        case DEF_NOTIFY_ANGEL_FAILED:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            iV1 = *ip; // Error reason
            switch (iV1)
            {
                case 1: // "BFB9BBF3C4A120BECAC0BA20B9F6B1D7C0D4B4CFB4D92E20A4D02E2EA4D0" (Stolen bytes ?)
                    AddEventList(DEF_MSG_NOTIFY_ANGEL_FAILED, 10); //"Impossible to get a Tutelary Angel."
                    break;
                case 2: //
                    AddEventList(DEF_MSG_NOTIFY_ANGEL_MAJESTIC, 10);//"You need additional Majesty Points."
                    break;
                case 3: //
                    AddEventList(DEF_MSG_NOTIFY_ANGEL_LOW_LVL, 10); //"Only Majesty characters can receive Tutelary Angel"
                    break;
            }
            break;

        case DEF_NOTIFY_ANGEL_RECEIVED:
            AddEventList(DEF_MSG_NOTIFY_ANGEL_RECEIVED, 10);// "You have received the Tutelary Angel."
            break;

        case DEF_NOTIFY_SPELL_SKILL:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            for (i = 0; i < DEF_MAXMAGICTYPE; i++)
            {
                m_cMagicMastery[i] = *cp;
                cp++;
            }
            for (i = 0; i < DEF_MAXSKILLTYPE; i++)
            {
                m_cSkillMastery[i] = (unsigned char)*cp;
                if (m_pSkillCfgList[i] != 0)
                    m_pSkillCfgList[i]->m_iLevel = (int)*cp;
                cp++;
            }
            break;

#ifdef DEF_EQUILIBRIUM_PROJECT // Avatar msg
        case DEF_NOTIFY_AVATAR:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            iV1 = *ip; // Msg type
            cp += 4;
            ip = (int *)cp;
            iV2 = *ip; // Statue rank
            cp += 4;
            ip = (int *)cp;
            iV3 = *ip; // Side of winer/messenger
            cp += 4;
            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, cp, 10);
            cp += 10;  // Messenger's Name
            ip = (int *)cp;
            iV4 = *ip; // XP
            cp += 4;
            switch (iV1)
            { // Msg type
                case 1: // Begin Avatar
                    PlaySound('E', 39, 0);
                    m_bIsAvatarMode = true;
                    if (m_bMusicStat) StartBGM();
                    wsprintfA(G_cTxt, "Avatar's relic quest on...", cTxt);
                    SetTopMsg(G_cTxt, 10);
                    break;
                case 2: // Relique ramassée	
                    PlaySound('E', 53, 0);
                    if (m_bCitizen == true)
                    {
                        if (((m_bAresden == true) && (iV3 == 1))
                            || ((m_bAresden == false) && (iV3 == 2)))
                        {
                            wsprintfA(G_cTxt, "Avatar's relic grasped by %s", cTxt);
                        }
                        else
                        {
                            wsprintfA(G_cTxt, "Avatar's relic captured by ennemi %s", cTxt);
                        }
                    }
                    else wsprintfA(G_cTxt, "Avatar's relic seized by %s", cTxt);
                    if (strcmp(cTxt, m_cPlayerName) == 0)
                    {
                        wsprintfA(G_cTxt, "By taking the relic, you're now the Avatar. Fetch the Great Dragon!");
                        m_bIsAvatarMessenger = true;
                    }
                    SetTopMsg(G_cTxt, 10);
                    break;
                case 3: // Relique droppée				
                    m_bIsAvatarMessenger = false;
                    PlaySound('E', 39, 0);
                    wsprintfA(G_cTxt, "Avatar's relic dropped by %s", cTxt);
                    SetTopMsg(G_cTxt, 10);
                    break;
                case 4: // Statue won
                    PlaySound('E', 53, 0);
                    if (strcmp(cTxt, m_cPlayerName) != 0)
                    {
                        switch (iV2)
                        {
                            case 2: // Dragon
                                wsprintfA(G_cTxt, "The Great Dragon gave %s's relic the Air elemental magic.", cTxt);
                                break;
                            case 3: // Demon
                                wsprintfA(G_cTxt, "The DemonLord imbued %s's relic with Fire's power.", cTxt);
                                break;
                            case 4: // Centaure
                                wsprintfA(G_cTxt, "The Faery's Earth magic replenishes %s's relic.", cTxt);
                                break;
                            case 5: // Allien
                                wsprintfA(G_cTxt, "Some Water magic refills %s's relic near the Allien.", cTxt);
                                break;
                            case 6: // Kloness
                            case 7: // Kloness
                                wsprintfA(G_cTxt, "The Kloness divine Power blessed %s's relic.", cTxt);
                                break;
                        }
                    }
                    else // msg for the messenger
                    {
                        switch (iV2)
                        {
                            case 2: // Dragon
                                wsprintfA(G_cTxt, "After the Great Dragon find the DemonLord.", cTxt);
                                break;
                            case 3: // Demon
                                wsprintfA(G_cTxt, "After the DemonLord search the Faery.", cTxt);
                                break;
                            case 4: // Centaure
                                wsprintfA(G_cTxt, "You found the Faery, but what about the Allien?", cTxt);
                                break;
                            case 5: // Allien
                                wsprintfA(G_cTxt, "Four elements already, now time go for a blessing!", cTxt);
                                break;
                            case 6: // Kloness
                                wsprintfA(G_cTxt, "Your nearlly achieved the Quest, find Aresien's statue...", cTxt);
                                break;
                            case 7: // Kloness
                                wsprintfA(G_cTxt, "Your nearlly achieved the Quest, find Aresien's statue...", cTxt);
                                break;
                        }
                    }
                    SetTopMsg(G_cTxt, 10);

                    break;
                case 5: // Finish Avatar			
                    m_bIsAvatarMode = false;
                    m_bIsAvatarMessenger = false;
                    if (m_bMusicStat) StartBGM();
                    switch (iV3)
                    {
                        case 1: // Aresien
                            wsprintfA(G_cTxt, "%s reached Aresien with the restored relic.", cTxt);
                            if ((m_bCitizen == true) && (m_bAresden == true))
                            {
                                PlaySound('E', 53, 0);
                            }
                            else
                            {
                                PlaySound('E', 39, 0);
                            }
                            break;
                        case 2: // Eldiniel
                            wsprintfA(G_cTxt, "%s reached Eldiniel with the restored relic.", cTxt);
                            if ((m_bCitizen == true) && (m_bAresden == false))
                            {
                                PlaySound('E', 53, 0);
                            }
                            else
                            {
                                PlaySound('E', 39, 0);
                            }
                            break;
                        default:
                            wsprintfA(G_cTxt, "The Avatar's relic quest was finished.", cTxt);
                            PlaySound('E', 53, 0);
                            break;
                    }
                    SetTopMsg(G_cTxt, 10);
                    if (iV4 != 0)
                    {
                        wsprintfA(G_cTxt, "You won %d XP for participation in Avatar's relic quest.", iV4);
                        AddEventList(G_cTxt, 10);
                    }
                    break;
            }
            break;
#endif

        case DEF_NOTIFY_NORECALL:
            AddEventList("You can not recall in this map.", 10);
            break;

        case DEF_NOTIFY_APOCGATESTARTMSG:
            SetTopMsg("The portal to the Apocalypse is opened.", 10);
            break;

        case DEF_NOTIFY_APOCGATEENDMSG:
            SetTopMsg("The portal to the Apocalypse is closed.", 10);
            break;

        case DEF_NOTIFY_APOCGATEOPEN:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            m_iGatePositX = *ip;
            cp += 4;
            ip = (int *)cp;
            m_iGatePositY = *ip;
            cp += 4;
            ZeroMemory(m_cGateMapName, sizeof(m_cGateMapName));
            memcpy(m_cGateMapName, cp, 10);
            cp += 10;
            break;

        case DEF_NOTIFY_QUESTCOUNTER:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            m_stQuest.sCurrentCount = (short)*ip;
            cp += 4;
            break;

        case DEF_NOTIFY_MONSTERCOUNT:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            wsprintfA(cTxt, "Rest Monster :%d", sV1);
            AddEventList(cTxt, 10);
            break;

        case DEF_NOTIFY_APOCGATECLOSE:
            m_iGatePositX = m_iGatePositY = -1;
            ZeroMemory(m_cGateMapName, sizeof(m_cGateMapName));
            break;

        case DEF_NOTIFY_APOCFORCERECALLPLAYERS:
            AddEventList("You are recalled by force, because the Apocalypse is started.", 10);
            break;

        case DEF_NOTIFY_ABADDONKILLED:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, cp, 10);
            cp += 10;
            wsprintfA(G_cTxt, "Abaddon is destroyed by %s", cTxt);
            AddEventList(G_cTxt, 10);
            break;

        case DEF_NOTIFY_0BE5: // Abaddon's related? Thunder?;  Case BE5 of switch 00454077
            /*00454255  |> B8 01000000    MOV EAX,1         ;  Case BE5 of switch 00454077
            0045425A  |. 5F             POP EDI
            0045425B  |. 8985 D8380700  MOV uint32_t PTR SS:[EBP+738D8],EAX
            00454261  |. 8985 DC380700  MOV uint32_t PTR SS:[EBP+738DC],EAX
            00454267  |. 8B85 88250700  MOV EAX,uint32_t PTR SS:[EBP+72588]
            0045426D  |. 5E             POP ESI
            0045426E  |. 8985 E0380700  MOV uint32_t PTR SS:[EBP+738E0],EAX
            00454274  |. 5D             POP EBP
            00454275  |. 5B             POP EBX
            00454276  |. 81C4 10080000  ADD ESP,810
            0045427C  |. C2 0400        RETN 4*/

            break;

        case DEF_NOTIFY_RESURRECTPLAYER: // Case BE9 of switch 00454077
            EnableDialogBox(50, 0, 0, 0);
            break;

        case DEF_NOTIFY_HELDENIANTELEPORT: //;  Case BE6 of switch 00454077
            m_bIsHeldenianMode = true;
            m_bIsHeldenianMap = ((m_cMapIndex == 35) || (m_cMapIndex == 36) || (m_cMapIndex == 37));
            SetTopMsg("Teleport to Heldenian field is available from now. Magic casting is forbidden until real battle.", 10);
            break;

        case DEF_NOTIFY_HELDENIANEND: //    ;  Case BE7 of switch 00454077
            m_bIsHeldenianMode = false;
            SetTopMsg("Heldenian holy war has been closed.", 10);
            break;

        case DEF_NOTIFY_0BE8: // ;  Case BE8 of switch 00454077
            SetTopMsg("Characters will be recalled by force as Heldenian begins.", 10);
            break;

        case DEF_NOTIFY_HELDENIANSTART: //  Case BEA of switch 00454077
            m_bIsHeldenianMode = true;
            m_bIsHeldenianMap = ((m_cMapIndex == 35) || (m_cMapIndex == 36) || (m_cMapIndex == 37));
            SetTopMsg("Heldenian real battle has been started form now on.", 10);
            break;

        case DEF_NOTIFY_HELDENIANVICTORY: // Case BEB of switch 00454077
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            ShowHeldenianVictory(sV1);
            m_iHeldenianAresdenLeftTower = -1;
            m_iHeldenianElvineLeftTower = -1;
            m_iHeldenianAresdenFlags = -1;
            m_iHeldenianElvineFlags = -1;
            break;

        case DEF_NOTIFY_HELDENIANCOUNT: // Case BEC of switch 00454077
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            m_iHeldenianAresdenLeftTower = (int)*sp;
            cp += 2;
            sp = (short *)cp;
            m_iHeldenianElvineLeftTower = (int)*sp;
            cp += 2;
            sp = (short *)cp;
            m_iHeldenianAresdenFlags = (int)*sp;
            cp += 2;
            sp = (short *)cp;
            m_iHeldenianElvineFlags = (int)*sp;
            cp += 2;
            break;

            // Slates
        case DEF_NOTIFY_SLATE_CREATESUCCESS:
            AddEventList(DEF_MSG_NOTIFY_SLATE_CREATESUCCESS, 10);
            break;
        case DEF_NOTIFY_SLATE_CREATEFAIL:
            AddEventList(DEF_MSG_NOTIFY_SLATE_CREATEFAIL, 10);
            break;
        case DEF_NOTIFY_SLATE_INVINCIBLE:
            AddEventList(DEF_MSG_NOTIFY_SLATE_INVINCIBLE, 10);
            m_bUsingSlate = true;
            break;
        case DEF_NOTIFY_SLATE_MANA:
            AddEventList(DEF_MSG_NOTIFY_SLATE_MANA, 10);
            m_bUsingSlate = true;
            break;
        case DEF_NOTIFY_SLATE_EXP:
            AddEventList(DEF_MSG_NOTIFY_SLATE_EXP, 10);
            m_bUsingSlate = true;
            break;
        case DEF_NOTIFY_SLATE_STATUS:
            AddEventList(DEF_MSG_NOTIFY_SLATECLEAR, 10); // "The effect of the prophecy-slate is disappeared."
            m_bUsingSlate = false;
            break;

            // MJ Stats Change
        case DEF_NOTIFY_STATECHANGE_SUCCESS:	// 0x0BB5
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            for (i = 0; i < DEF_MAXMAGICTYPE; i++)
            {
                m_cMagicMastery[i] = *cp;
                cp++;
            }
            for (i = 0; i < DEF_MAXSKILLTYPE; i++)
            {
                m_cSkillMastery[i] = (unsigned char)*cp;
                if (m_pSkillCfgList[i] != 0)
                    m_pSkillCfgList[i]->m_iLevel = (int)*cp;
                //else m_pSkillCfgList[i]->m_iLevel = 0;
                cp++;
            }
            // MJ Stats Change
            m_iStr += m_cLU_Str;
            m_iVit += m_cLU_Vit;
            m_iDex += m_cLU_Dex;
            m_iInt += m_cLU_Int;
            m_iMag += m_cLU_Mag;
            m_iCharisma += m_cLU_Char;
            m_iLU_Point = m_iLevel * 3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
            m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
            AddEventList("Your stat has been changed.", 10); // "Your stat has been changed."
            break;

        case DEF_NOTIFY_LEVELUP:
            NotifyMsg_LevelUp(pData);
            break;

        case DEF_NOTIFY_STATECHANGE_FAILED:
            m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
            m_iLU_Point = m_iLevel * 3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
            AddEventList("Your stat has not been changed.", 10);
            break;

        case DEF_NOTIFY_SETTING_FAILED:
            AddEventList("Your stat has not been changed.", 10);
            m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
            m_iLU_Point = m_iLevel * 3 - ((m_iStr + m_iVit + m_iDex + m_iInt + m_iMag + m_iCharisma) - 70) - 3;
            break;

        case DEF_NOTIFY_SETTING_SUCCESS:
            NotifyMsg_SettingSuccess(pData);
            break;

        case DEF_NOTIFY_AGRICULTURENOAREA:
            AddEventList(DEF_MSG_NOTIFY_AGRICULTURENOAREA, 10);
            break;
        case DEF_NOTIFY_AGRICULTURESKILLLIMIT:
            AddEventList(DEF_MSG_NOTIFY_AGRICULTURESKILLLIMIT, 10);
            break;

        case DEF_NOTIFY_NOMOREAGRICULTURE:
            AddEventList(DEF_MSG_NOTIFY_NOMOREAGRICULTURE, 10);
            break;
        case DEF_NOTIFY_SPAWNEVENT:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            m_sMonsterID = (short)(*cp);
            cp++;
            sp = (short *)cp;
            m_sEventX = *sp;
            cp += 2;
            sp = (short *)cp;
            m_sEventY = *sp;
            cp += 2;
            m_dwMonsterEventTime = dwTime;
            break;

        case DEF_NOTIFY_CHANGEPLAYMODE:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            memcpy(m_cLocation, cp, 10);
            cp += 10;
            if (memcmp(m_cLocation, "aresden", 7) == 0)
            {
                m_bAresden = true;
                m_bCitizen = true;
                m_bHunter = false;
            }
            else if (memcmp(m_cLocation, "arehunter", 9) == 0)
            {
                m_bAresden = true;
                m_bCitizen = true;
                m_bHunter = true;
            }
            else if (memcmp(m_cLocation, "elvine", 6) == 0)
            {
                m_bAresden = false;
                m_bCitizen = true;
                m_bHunter = false;
            }
            else if (memcmp(m_cLocation, "elvhunter", 9) == 0)
            {
                m_bAresden = false;
                m_bCitizen = true;
                m_bHunter = true;

#ifdef DEF_EQUILIBRIUM_PROJECT // m_bAresden, m_bCitizen, m_bHunter for me ready for later fix
            }
            else if (memcmp(m_cLocation, "executor", 8) == 0)
            {
                m_bAresden = true;
                m_bCitizen = false;
                m_bHunter = false;
            }
            else if (memcmp(m_cLocation, "evil", 4) == 0)
            {
                m_bAresden = true;
                m_bCitizen = false;
                m_bHunter = false;
            }
            else if (memcmp(m_cLocation, "NONE", 4) == 0)
            {
                m_bAresden = true;
                m_bCitizen = false;
                m_bHunter = true;
#endif

            }
            else
            {
                m_bAresden = true;
                m_bCitizen = false;
                m_bHunter = true;
            }
            AddEventList(DEF_MSG_GAMEMODE_CHANGED, 10);
            break;

        case DEF_NOTIFY_REQGUILDNAMEANSWER:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV2 = *sp;
            cp += 2;
            ZeroMemory(cTemp, sizeof(cTemp));
            memcpy(cTemp, cp, 20);
            cp += 20;

            ZeroMemory(m_stGuildName[sV2].cGuildName, sizeof(m_stGuildName[sV2].cGuildName));
            strcpy(m_stGuildName[sV2].cGuildName, cTemp);
            m_stGuildName[sV2].iGuildRank = sV1;
            for (i = 0; i < 20; i++) if (m_stGuildName[sV2].cGuildName[i] == '_') m_stGuildName[sV2].cGuildName[i] = ' ';
            break;

        case DEF_NOTIFY_FORCERECALLTIME:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            if ((int)(sV1 / 20) > 0)
                wsprintfA(G_cTxt, NOTIFY_MSG_FORCERECALLTIME1, (int)(sV1 / 20));
            else
                wsprintfA(G_cTxt, NOTIFY_MSG_FORCERECALLTIME2);
            AddEventList(G_cTxt, 10);
            break;

        case DEF_NOTIFY_GIZONITEMUPGRADELEFT: // Item upgrade is possible.
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            m_iGizonItemUpgradeLeft = sV1;
            dwp = (uint32_t *)cp;
            switch (*dwp)
            {
                case 1: //
                    AddEventList(NOTIFY_MSG_HANDLER_GIZONITEMUPGRADELEFT1, 10);
                    break;
            }
            cp += 4;
            break;

        case DEF_NOTIFY_GIZONITEMCHANGE:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            m_pItemList[sV1]->m_cItemType = *cp;
            cp++;
            wp = (uint16_t *)cp;
            m_pItemList[sV1]->m_wCurLifeSpan = *wp;
            cp += 2;
            sp = (short *)cp;
            m_pItemList[sV1]->m_sSprite = *sp;
            cp += 2;
            sp = (short *)cp;
            m_pItemList[sV1]->m_sSpriteFrame = *sp;
            cp += 2;
            m_pItemList[sV1]->m_cItemColor = *cp;
            cp++;
            m_pItemList[sV1]->m_sItemSpecEffectValue2 = *cp;
            cp++;
            dwp = (uint32_t *)cp;
            m_pItemList[sV1]->m_dwAttribute = *dwp;
            cp += 4;
            ZeroMemory(m_pItemList[sV1]->m_cName, sizeof(m_pItemList[sV1]->m_cName));
            memcpy(m_pItemList[sV1]->m_cName, cp, 20);
            cp += 20;
            if (m_bIsDialogEnabled[34] == true)
            {
                m_stDialogBoxInfo[34].cMode = 3; // success
            }
            PlaySound('E', 23, 5);
            switch (m_sPlayerType)
            {
                case 1:
                case 2:
                case 3:
                    PlaySound('C', 21, 0);
                    break;

                case 4:
                case 5:
                case 6:
                    PlaySound('C', 22, 0);
                    break;
            }
            break;

        case DEF_NOTIFY_ITEMATTRIBUTECHANGE:
        case 0x0BC0: // Unknown msg, but real in client v3.51
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            dwTemp = m_pItemList[sV1]->m_dwAttribute;
            dwp = (uint32_t *)cp;
            m_pItemList[sV1]->m_dwAttribute = *dwp;
            cp += 4;
            dwp = (uint32_t *)cp;
            if (*dwp != 0) m_pItemList[sV1]->m_sItemSpecEffectValue1 = (short)*dwp;
            cp += 4;
            dwp = (uint32_t *)cp;
            if (*dwp != 0) m_pItemList[sV1]->m_sItemSpecEffectValue2 = (short)*dwp;
            cp += 4;
            if (dwTemp == m_pItemList[sV1]->m_dwAttribute)
            {
                if (m_bIsDialogEnabled[34] == true)
                {
                    m_stDialogBoxInfo[34].cMode = 4;// Failed
                }
                PlaySound('E', 24, 5);
            }
            else
            {
                if (m_bIsDialogEnabled[34] == true)
                {
                    m_stDialogBoxInfo[34].cMode = 3; // Success
                }
                PlaySound('E', 23, 5);
                switch (m_sPlayerType)
                {
                    case 1:
                    case 2:
                    case 3:
                        PlaySound('C', 21, 0);
                        break;
                    case 4:
                    case 5:
                    case 6:
                        PlaySound('C', 22, 0);
                        break;
                }
            }
            break;

        case DEF_NOTIFY_ITEMUPGRADEFAIL:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            if (m_bIsDialogEnabled[34] == false) return;
            PlaySound('E', 24, 5);
            switch (sV1)
            {
                case 1:
                    m_stDialogBoxInfo[34].cMode = 8; // Failed
                    break;
                case 2:
                    m_stDialogBoxInfo[34].cMode = 9; // Failed
                    break;
                case 3:
                    m_stDialogBoxInfo[34].cMode = 10; // Failed
                    break;
            }
            break;

        case DEF_NOTIFY_PARTY:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV2 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV3 = *sp;
            cp += 2;
            switch (sV1)
            {
                case 1: //
                    switch (sV2)
                    {
                        case 0:
                            EnableDialogBox(32, 0, 0, 0);
                            m_stDialogBoxInfo[32].cMode = 9;
                            break;

                        case 1:
                            m_iPartyStatus = 1;
                            m_iTotalPartyMember = 0;
                            EnableDialogBox(32, 0, 0, 0);
                            m_stDialogBoxInfo[32].cMode = 8;
                            for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
                            bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, 0, 2, 0, 0, m_cMCName);
                            break;
                    }
                    break;

                case 2: //
                    m_iPartyStatus = 0;
                    m_iTotalPartyMember = 0;
                    EnableDialogBox(32, 0, 0, 0);
                    m_stDialogBoxInfo[32].cMode = 10;
                    for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
                    break;

                case 4:
                    ZeroMemory(cTxt, sizeof(cTxt));
                    memcpy(cTxt, cp, 10);
                    cp += 10;

                    switch (sV2)
                    {
                        case 0: //
                            EnableDialogBox(32, 0, 0, 0);
                            m_stDialogBoxInfo[32].cMode = 9;
                            break;

                        case 1: //
                            if (strcmp(cTxt, m_cPlayerName) == 0)
                            {
                                m_iPartyStatus = 2;
                                EnableDialogBox(32, 0, 0, 0);
                                m_stDialogBoxInfo[32].cMode = 8;
                            }
                            else
                            {
                                wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER1, cTxt);
                                AddEventList(G_cTxt, 10);
                            }

                            m_iTotalPartyMember++;
                            for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
                                if (strlen(m_stPartyMemberNameList[i].cName) == 0)
                                {
                                    ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
                                    memcpy(m_stPartyMemberNameList[i].cName, cTxt, 10);
                                    goto NMH_LOOPBREAK1;
                                }
                            NMH_LOOPBREAK1:;
                            break;

                        case 2: //
                            break;
                    }
                    break;

                case 5: //
                    m_iTotalPartyMember = 0;
                    for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));

                    m_iTotalPartyMember = sV3;
                    for (i = 1; i <= sV3; i++)
                    {
                        ZeroMemory(m_stPartyMemberNameList[i - 1].cName, sizeof(m_stPartyMemberNameList[i - 1].cName));
                        memcpy(m_stPartyMemberNameList[i - 1].cName, cp, 10);
                        cp += 11;
                    }
                    break;

                default:
                    sp = (short *)cp;
                    sV4 = *sp;
                    cp += 2;
                    break;

                case 6:
                    ZeroMemory(cTxt, sizeof(cTxt));
                    memcpy(cTxt, cp, 10);
                    cp += 10;

                    switch (sV2)
                    {
                        case 0: //
                            EnableDialogBox(32, 0, 0, 0);
                            m_stDialogBoxInfo[32].cMode = 7;
                            break;

                        case 1: //
                            if (strcmp(cTxt, m_cPlayerName) == 0)
                            {
                                m_iPartyStatus = 0;
                                EnableDialogBox(32, 0, 0, 0);
                                m_stDialogBoxInfo[32].cMode = 6;
                            }
                            else
                            {
                                wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER2, cTxt);
                                AddEventList(G_cTxt, 10);
                            }
                            for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
                                if (strcmp(m_stPartyMemberNameList[i].cName, cTxt) == 0)
                                {
                                    ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
                                    m_iTotalPartyMember--;
                                    goto NMH_LOOPBREAK2;
                                }
                            NMH_LOOPBREAK2:;
                            break;
                    }
                    break;

                case 7: //
                    EnableDialogBox(32, 0, 0, 0);
                    m_stDialogBoxInfo[32].cMode = 9;
                    break;

                case 8: //
                    m_iPartyStatus = 0;
                    m_iTotalPartyMember = 0;
                    for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
                    break;
            }
            break;

        case DEF_NOTIFY_CANNOTCONSTRUCT:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;

            CannotConstruct(sV1);
            PlaySound('E', 25, 0, 0);
            break;

        case DEF_NOTIFY_TCLOC:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

            sp = (short *)cp;
            m_iTeleportLocX = *sp;
            cp += 2;

            sp = (short *)cp;
            m_iTeleportLocY = *sp;
            cp += 2;

            ZeroMemory(m_cTeleportMapName, sizeof(m_cTeleportMapName));
            memcpy(m_cTeleportMapName, cp, 10);
            cp += 10;

            sp = (short *)cp;
            m_iConstructLocX = *sp;
            cp += 2;

            sp = (short *)cp;
            m_iConstructLocY = *sp;
            cp += 2;

            ZeroMemory(m_cConstructMapName, sizeof(m_cConstructMapName));
            memcpy(m_cConstructMapName, cp, 10);
            cp += 10;
            break;

        case DEF_NOTIFY_CONSTRUCTIONPOINT:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;

            sp = (short *)cp;
            sV2 = *sp;
            cp += 2;

            sp = (short *)cp;
            sV3 = *sp;
            cp += 2;

            if (sV3 == 0)
            {
                if ((sV1 > m_iConstructionPoint) && (sV2 > m_iWarContribution))
                {
                    wsprintfA(G_cTxt, "%s +%d, %s +%d", m_pGameMsgList[13]->m_pMsg, (sV1 - m_iConstructionPoint), m_pGameMsgList[21]->m_pMsg, (sV2 - m_iWarContribution));
                    SetTopMsg(G_cTxt, 5);
                    PlaySound('E', 23, 0, 0);
                }

                if ((sV1 > m_iConstructionPoint) && (sV2 == m_iWarContribution))
                {
                    if (m_iCrusadeDuty == 3)
                    {
                        wsprintfA(G_cTxt, "%s +%d", m_pGameMsgList[13]->m_pMsg, sV1 - m_iConstructionPoint);
                        SetTopMsg(G_cTxt, 5);
                        PlaySound('E', 23, 0, 0);
                    }
                }

                if ((sV1 == m_iConstructionPoint) && (sV2 > m_iWarContribution))
                {
                    wsprintfA(G_cTxt, "%s +%d", m_pGameMsgList[21]->m_pMsg, sV2 - m_iWarContribution);
                    SetTopMsg(G_cTxt, 5);
                    PlaySound('E', 23, 0, 0);
                }

                if (sV1 < m_iConstructionPoint)
                {
                    if (m_iCrusadeDuty == 3)
                    {
                        wsprintfA(G_cTxt, "%s -%d", m_pGameMsgList[13]->m_pMsg, m_iConstructionPoint - sV1);
                        SetTopMsg(G_cTxt, 5);
                        PlaySound('E', 25, 0, 0);
                    }
                }

                if (sV2 < m_iWarContribution)
                {
                    wsprintfA(G_cTxt, "%s -%d", m_pGameMsgList[21]->m_pMsg, m_iWarContribution - sV2);
                    SetTopMsg(G_cTxt, 5);
                    PlaySound('E', 24, 0, 0);
                }
            }

            m_iConstructionPoint = sV1;
            m_iWarContribution = sV2;
            break;

        case DEF_NOTIFY_NOMORECRUSADESTRUCTURE:
            SetTopMsg(m_pGameMsgList[12]->m_pMsg, 5);
            PlaySound('E', 25, 0, 0);
            break;

        case DEF_NOTIFY_GRANDMAGICRESULT:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

            wp = (uint16_t *)cp;
            sV1 = *wp;
            cp += 2;

            wp = (uint16_t *)cp;
            sV2 = *wp;
            cp += 2;

            wp = (uint16_t *)cp;
            sV3 = *wp;
            cp += 2;

            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, cp, 10);
            cp += 10;

            wp = (uint16_t *)cp;
            sV4 = *wp;
            cp += 2;

            wp = (uint16_t *)cp;
            sV5 = *wp;  //
            cp += 2;

            if (sV5 > 0)
            {
                wp = (uint16_t *)cp;
                sV6 = *wp;
                cp += 2;
                sV5--;
            }
            else sV6 = 0;

            if (sV5 > 0)
            {
                wp = (uint16_t *)cp;
                sV7 = *wp;
                cp += 2;
                sV5--;
            }
            else sV7 = 0;

            if (sV5 > 0)
            {
                wp = (uint16_t *)cp;
                sV8 = *wp;
                cp += 2;
                sV5--;
            }
            else sV8 = 0;

            if (sV5 > 0)
            {
                wp = (uint16_t *)cp;
                sV9 = *wp;
                cp += 2;
                sV5--;
            }
            else sV9 = 0;

            GrandMagicResult(cTxt, sV1, sV2, sV3, sV4, sV6, sV7, sV8, sV9);
            break;

        case DEF_NOTIFY_METEORSTRIKECOMING:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            wp = (uint16_t *)cp;
            sV1 = *wp;
            cp += 2;
            MeteorStrikeComing(sV1);
            PlaySound('E', 25, 0, 0);
            break;

        case DEF_NOTIFY_METEORSTRIKEHIT:
            SetTopMsg(m_pGameMsgList[17]->m_pMsg, 5);
            //StartMeteorStrikeEffect
            for (i = 0; i < 36; i++) bAddNewEffect(60, m_sViewPointX + (rand() % 640), m_sViewPointY + (rand() % 480), 0, 0, -(rand() % 80));
            break;

        case DEF_NOTIFY_MAPSTATUSNEXT:
            AddMapStatusInfo(pData, false);
            break;

        case DEF_NOTIFY_MAPSTATUSLAST:
            AddMapStatusInfo(pData, true);
            break;

        case DEF_NOTIFY_LOCKEDMAP:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;

            ZeroMemory(cTemp, sizeof(cTemp));
            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, cp, 10);
            cp += 10;

            GetOfficialMapName(cTxt, cTemp);
            wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER3, sV1, cTemp);
            SetTopMsg(G_cTxt, 10);
            PlaySound('E', 25, 0, 0);
            break;

        case DEF_NOTIFY_CRUSADE: // Crusade msg
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            iV1 = *ip; // Crusademode
            cp += 4;
            ip = (int *)cp;
            iV2 = *ip; // crusade duty
            cp += 4;
            ip = (int *)cp;
            iV3 = *ip;
            cp += 4;
            ip = (int *)cp;
            iV4 = *ip;
            cp += 4;
            if (m_bIsCrusadeMode == false)
            {
                if (iV1 != 0) // begin crusade
                {
                    m_bIsCrusadeMode = true;
                    if (m_bMusicStat) StartBGM(); // Change mp3 music for crusade 
                    m_iCrusadeDuty = iV2;
                    if ((m_iCrusadeDuty != 3) && (m_bCitizen == true))
                        _RequestMapStatus("middleland", 3);
                    if (m_iCrusadeDuty != 0)
                        EnableDialogBox(33, 2, iV2, 0);
                    else EnableDialogBox(33, 1, 0, 0);
                    if (m_bCitizen == false) EnableDialogBox(18, 800, 0, 0);
                    else if (m_bAresden == true) EnableDialogBox(18, 801, 0, 0);
                    else if (m_bAresden == false) EnableDialogBox(18, 802, 0, 0);
                    if (m_bCitizen == false) SetTopMsg(NOTIFY_MSG_CRUSADESTART_NONE, 10);
                    else SetTopMsg(m_pGameMsgList[9]->m_pMsg, 10);
                    PlaySound('E', 25, 0, 0);
                }
                if (iV3 != 0) // Crusade finished, show XP result screen
                {
                    CrusadeContributionResult(iV3);
                }
                if (iV4 == -1) // The crusade you played in was finished.
                {
                    CrusadeContributionResult(0); // You connect in this crusade, but did not connect after previous one => no XP....
                }
            }
            else
            {
                if (iV1 == 0) // crusade finished show result (1st result: winner)
                {
                    m_bIsCrusadeMode = false;
                    if (m_bMusicStat) StartBGM(); // Change mp3 at crusade's end
                    m_iCrusadeDuty = 0;
                    CrusadeWarResult(iV4);
                    SetTopMsg(m_pGameMsgList[57]->m_pMsg, 8);
                }
                else
                {
                    if (m_iCrusadeDuty != iV2)
                    {
                        m_iCrusadeDuty = iV2;
                        EnableDialogBox(33, 2, iV2, 0);
                        PlaySound('E', 25, 0, 0);
                    }
                }
                if (iV4 == -1)
                {
                    CrusadeContributionResult(0); // You connect in this crusade, but did not connect after previous one => no XP....
                }
            }
            break;

        case DEF_NOTIFY_SPECIALABILITYSTATUS:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV2 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV3 = *sp;
            cp += 2;
            if (sV1 == 1) // Use SA
            {
                PlaySound('E', 35, 0);
                AddEventList(NOTIFY_MSG_HANDLER4, 10); // "Use special ability!"
                switch (sV2)
                {
                    case 1: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER5, sV3); break;//"You are untouchable for %d seconds!"
                    case 2: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER6, sV3); break;//"
                    case 3: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER7, sV3); break;//"
                    case 4: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER8, sV3); break;//"
                    case 5: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER9, sV3); break;//"
                    case 50:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER10, sV3); break;//"
                    case 51:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER11, sV3); break;//"
                    case 52:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER12, sV3); break;//"
                    case 55: // Spell effect
                        if (sV3 > 90)
                            wsprintfA(G_cTxt, "You cast a powerfull incantation, you can't use it again before %d minutes.", sV3 / 60);
                        else
                            wsprintfA(G_cTxt, "You cast a powerfull incantation, you can't use it again before %d seconds.", sV3);
                        break;
                }
                AddEventList(G_cTxt, 10);
            }
            else if (sV1 == 2) // Finished using
            {
                if (m_iSpecialAbilityType != (int)sV2)
                {
                    PlaySound('E', 34, 0);
                    AddEventList(NOTIFY_MSG_HANDLER13, 10);//"Special ability has been set!"
                    if (sV3 >= 60)
                    {
                        switch (sV2)
                        {
                            case 1: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER14, sV3 / 60); AddEventList(G_cTxt, 10); break;//"Ability that decreases enemy's HP by 50%: Can use after %dMin"
                            case 2: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER15, sV3 / 60); AddEventList(G_cTxt, 10); break;//"
                            case 3: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER16, sV3 / 60); AddEventList(G_cTxt, 10); break;//"
                            case 4: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER17, sV3 / 60); AddEventList(G_cTxt, 10); break;//"
                            case 5: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER18, sV3 / 60); AddEventList(G_cTxt, 10); break;//"
                            case 50:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER19, sV3 / 60); AddEventList(G_cTxt, 10); break;//"
                            case 51:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER20, sV3 / 60); AddEventList(G_cTxt, 10); break;//"
                            case 52:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER21, sV3 / 60); AddEventList(G_cTxt, 10); break;//"
                        }
                    }
                    else
                    {
                        switch (sV2)
                        {
                            case 1: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER22, sV3); AddEventList(G_cTxt, 10); break;//"
                            case 2: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER23, sV3); AddEventList(G_cTxt, 10); break;//"
                            case 3: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER24, sV3); AddEventList(G_cTxt, 10); break;//"
                            case 4: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER25, sV3); AddEventList(G_cTxt, 10); break;//"
                            case 5: wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER26, sV3); AddEventList(G_cTxt, 10); break;//"
                            case 50:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER27, sV3); AddEventList(G_cTxt, 10); break;//"
                            case 51:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER28, sV3); AddEventList(G_cTxt, 10); break;//"
                            case 52:wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER29, sV3); AddEventList(G_cTxt, 10); break;//""Ability that makes character untouchable: Can use after %dSec"
                        }
                    }
                }
                m_iSpecialAbilityType = (int)sV2;
                m_dwSpecialAbilitySettingTime = dwTime;
                m_iSpecialAbilityTimeLeftSec = (int)sV3;
            }
            else if (sV1 == 3)  // End of using time
            {
                m_bIsSpecialAbilityEnabled = false;
                m_dwSpecialAbilitySettingTime = dwTime;
                if (sV3 == 0)
                {
                    m_iSpecialAbilityTimeLeftSec = 1200;
                    AddEventList(NOTIFY_MSG_HANDLER30, 10);//"Special ability has run out! Will be available in 20 minutes."
                }
                else
                {
                    m_iSpecialAbilityTimeLeftSec = (int)sV3;
                    if (sV3 > 90)
                        wsprintfA(G_cTxt, "Special ability has run out! Will be available in %d minutes.", sV3 / 60);
                    else wsprintfA(G_cTxt, "Special ability has run out! Will be available in %d seconds.", sV3);
                    AddEventList(G_cTxt, 10);
                }
            }
            else if (sV1 == 4) // Unequiped the SA item
            {
                AddEventList(NOTIFY_MSG_HANDLER31, 10);//"Special ability has been released."
                m_iSpecialAbilityType = 0;
            }
            else if (sV1 == 5) // Angel
            {
                PlaySound('E', 52, 0); // Angel
            }
            break;

        case DEF_NOTIFY_SPECIALABILITYENABLED:
            if (m_bIsSpecialAbilityEnabled == false)
            {
                PlaySound('E', 30, 5);
                AddEventList(NOTIFY_MSG_HANDLER32, 10);//"
            }
            m_bIsSpecialAbilityEnabled = true;
            break;

        case DEF_NOTIFY_ENERGYSPHEREGOALIN:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV2 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV3 = *sp;
            cp += 2;
            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, cp, 20);

            if (sV2 == sV3)
            {
                PlaySound('E', 24, 0);
                if (strcmp(cTxt, m_cPlayerName) == 0)
                {
                    AddEventList(NOTIFY_MSG_HANDLER33, 10);//You pushed energy sphere to enemy's energy portal! Contribution point will be decreased by 10 points."
                    m_iContribution += sV1; // fixed, server must match...
                    m_iContributionPrice = 0;
                    if (m_iContribution < 0) m_iContribution = 0;
                }
                else
                {
                    ZeroMemory(G_cTxt, sizeof(G_cTxt));
                    if (m_bAresden == true) wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER34, cTxt);//"%s(Aresden) pushed energy sphere to enemy's portal!!..."
                    else if (m_bAresden == false) wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER34_ELV, cTxt);//"%s(Elvine) pushed energy sphere to enemy's portal!!..."
                    AddEventList(G_cTxt, 10);
                }
            }
            else
            {
                PlaySound('E', 23, 0);
                if (strcmp(cTxt, m_cPlayerName) == 0)
                {
                    switch (m_sPlayerType)
                    {
                        case 1:
                        case 2:
                        case 3:	PlaySound('C', 21, 0); break;
                        case 4:
                        case 5:
                        case 6:	PlaySound('C', 22, 0); break;
                    }
                    AddEventList(NOTIFY_MSG_HANDLER35, 10);//"Congulaturations! You brought energy sphere to energy portal and earned experience and prize gold!"

                    m_iContribution += sV1; // fixed, server must match...
                    m_iContributionPrice = 0;
                    if (m_iContribution < 0) m_iContribution = 0;
                }
                else
                {
                    ZeroMemory(G_cTxt, sizeof(G_cTxt));
                    if (sV3 == 1)
                    {
                        wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER36, cTxt);//"Elvine %s : Goal in!"
                        AddEventList(G_cTxt, 10);
                    }
                    else if (sV3 == 2)
                    {
                        wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER37, cTxt);//"Aresden %s : Goal in!"
                        AddEventList(G_cTxt, 10);
                    }
                }
            }
            break;

        case DEF_NOTIFY_ENERGYSPHERECREATED:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV2 = *sp;
            cp += 2;
            ZeroMemory(G_cTxt, sizeof(G_cTxt));
            wsprintfA(G_cTxt, NOTIFY_MSG_HANDLER38, sV1, sV2);//"Energy sphere was dropped in (%d, %d) of middleland!"
            AddEventList(G_cTxt, 10);
            AddEventList(NOTIFY_MSG_HANDLER39, 10);//"A player who pushed energy sphere to the energy portal of his city will earn many Exp and Contribution."
            break;

        case DEF_NOTIFY_QUERY_JOINPARTY:
            EnableDialogBox(32, 0, 0, 0);
            m_stDialogBoxInfo[32].cMode = 1;
            ZeroMemory(m_stDialogBoxInfo[32].cStr, sizeof(m_stDialogBoxInfo[32].cStr));
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            strcpy(m_stDialogBoxInfo[32].cStr, cp);
            break;

        case DEF_NOTIFY_RESPONSE_CREATENEWPARTY:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;

            if ((bool)*sp == true)
            {
                m_stDialogBoxInfo[32].cMode = 2;
            }
            else
            {
                m_stDialogBoxInfo[32].cMode = 3;
            }
            break;

        case DEF_NOTIFY_DAMAGEMOVE:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            m_sDamageMove = *sp;
            cp += 2;
            sp = (short *)cp;
            m_sDamageMoveAmount = *sp;
            cp += 2;
            break;

        case DEF_NOTIFY_OBSERVERMODE:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            if (*sp == 1)
            {
                AddEventList(NOTIFY_MSG_HANDLER40);//"Observer Mode On. Press 'SHIFT + ESC' to Log Out..."
                m_bIsObserverMode = true;
                m_dwObserverCamTime = unixtime();
                char cName[12];
                ZeroMemory(cName, sizeof(cName));
                memcpy(cName, m_cPlayerName, 10);
                m_pMapData->bSetOwner(m_sPlayerObjectID, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, cName, 0, 0, 0, 0);
            }
            else
            {
                AddEventList(NOTIFY_MSG_HANDLER41);//"Observer Mode Off"
                m_bIsObserverMode = false;
                m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir, m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor, m_iPlayerStatus, m_cPlayerName, DEF_OBJECTSTOP, 0, 0, 0);
            }
            break;

        case DEF_NOTIFY_BUILDITEMSUCCESS:
            DisableDialogBox(26);
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            sV1 = *sp;
            cp += 2;
            sp = (short *)cp;
            sV2 = *sp;
            cp += 2;
            if (sV1 < 10000)
            {
                EnableDialogBox(26, 6, 1, sV1, 0);
                m_stDialogBoxInfo[26].sV1 = sV2;
            }
            else
            {
                EnableDialogBox(26, 6, 1, -1 * (sV1 - 10000), 0);
                m_stDialogBoxInfo[26].sV1 = sV2;
            }
            AddEventList(NOTIFY_MSG_HANDLER42, 10);
            PlaySound('E', 23, 5);
            switch (m_sPlayerType)
            {
                case 1:
                case 2:
                case 3:
                    PlaySound('C', 21, 0);
                    break;

                case 4:
                case 5:
                case 6:
                    PlaySound('C', 22, 0);
                    break;
            }
            break;

        case DEF_NOTIFY_BUILDITEMFAIL:
            DisableDialogBox(26);
            EnableDialogBox(26, 6, 0, 0);
            AddEventList(NOTIFY_MSG_HANDLER43, 10);
            PlaySound('E', 24, 5);
            break;

        case DEF_NOTIFY_QUESTREWARD:
            NotifyMsg_QuestReward(pData);
            break;

        case DEF_NOTIFY_QUESTCOMPLETED:
            m_stQuest.bIsQuestCompleted = true;
            DisableDialogBox(28);
            EnableDialogBox(28, 1, 0, 0);
            switch (m_sPlayerType)
            {
                case 1:
                case 2:
                case 3:	PlaySound('C', 21, 0); break;
                case 4:
                case 5:
                case 6:	PlaySound('C', 22, 0); break;
            }
            PlaySound('E', 23, 0);
            AddEventList(NOTIFY_MSG_HANDLER44, 10);
            break;

        case DEF_NOTIFY_QUESTABORTED:
            m_stQuest.sQuestType = 0;
            DisableDialogBox(28);
            EnableDialogBox(28, 2, 0, 0);
            break;

        case DEF_NOTIFY_QUESTCONTENTS:
            NotifyMsg_QuestContents(pData);
            break;

        case DEF_NOTIFY_ITEMCOLORCHANGE:
            NotifyMsg_ItemColorChange(pData);
            break;

        case DEF_NOTIFY_DROPITEMFIN_COUNTCHANGED:
            NotifyMsg_DropItemFin_CountChanged(pData);
            break;

        case DEF_NOTIFY_CANNOTGIVEITEM:
            NotifyMsg_CannotGiveItem(pData);
            break;

        case DEF_NOTIFY_GIVEITEMFIN_COUNTCHANGED:
            NotifyMsg_GiveItemFin_CountChanged(pData);
            break;

        case DEF_NOTIFY_EXCHANGEITEMCOMPLETE:
            AddEventList(NOTIFYMSG_EXCHANGEITEM_COMPLETE1, 10);
            DisableDialogBox(27);
            // MultiTrade
            DisableDialogBox(41);
            PlaySound('E', 23, 5);
            break;

        case DEF_NOTIFY_CANCELEXCHANGEITEM:
            PlaySound('E', 24, 5);
            AddEventList(NOTIFYMSG_CANCEL_EXCHANGEITEM1, 10);
            AddEventList(NOTIFYMSG_CANCEL_EXCHANGEITEM2, 10);
            // MultiTrade
            DisableDialogBox(41);
            DisableDialogBox(27);
            break;

        case DEF_NOTIFY_SETEXCHANGEITEM:
            NotifyMsg_SetExchangeItem(pData);
            break;

        case DEF_NOTIFY_OPENEXCHANGEWINDOW:
            NotifyMsg_OpenExchageWindow(pData);
            break;

        case DEF_NOTIFY_NOTFLAGSPOT:
            AddEventList(NOTIFY_MSG_HANDLER45, 10);
            break;

        case DEF_NOTIFY_ITEMPOSLIST:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            for (i = 0; i < DEF_MAXITEMS; i++)
            {
                sp = (short *)cp;
                sX = *sp;
                cp += 2;
                sp = (short *)cp;
                sY = *sp;
                cp += 2;
                if (m_pItemList[i] != 0)
                {
                    if (sY < -10) sY = -10;
                    if (sX < 0)   sX = 0;
                    if (sX > 170) sX = 170;
                    if (sY > 95)  sY = 95;

                    m_pItemList[i]->m_sX = sX;
                    m_pItemList[i]->m_sY = sY;
                }
            }
            break;

        case DEF_NOTIFY_ENEMYKILLS:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            m_iEnemyKillCount = *ip;
            break;

        case DEF_NOTIFY_DOWNSKILLINDEXSET:
            NotifyMsg_DownSkillIndexSet(pData);
            break;

        case DEF_NOTIFY_ADMINIFO:
            NotifyMsg_AdminInfo(pData);
            break;

        case DEF_NOTIFY_NPCTALK:
            NpcTalkHandler(pData);
            break;

        case DEF_NOTIFY_PORTIONSUCCESS:
            AddEventList(NOTIFY_MSG_HANDLER46, 10);
            break;

        case DEF_NOTIFY_PORTIONFAIL:
            AddEventList(NOTIFY_MSG_HANDLER47, 10);
            break;

        case DEF_NOTIFY_LOWPORTIONSKILL:
            AddEventList(NOTIFY_MSG_HANDLER48, 10);
            break;

        case DEF_NOTIFY_NOMATCHINGPORTION:
            AddEventList(NOTIFY_MSG_HANDLER49, 10);
            break;

        case DEF_NOTIFY_SUPERATTACKLEFT:
            sp = (short *)(pData + DEF_INDEX2_MSGTYPE + 2);
            m_iSuperAttackLeft = (int)*sp;
            break;

        case DEF_NOTIFY_SAFEATTACKMODE:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            switch (*cp)
            {
                case 1:
                    if (!m_bIsSafeAttackMode) AddEventList(NOTIFY_MSG_HANDLER50, 10);//"
                    m_bIsSafeAttackMode = true;
                    break;
                case 0:
                    if (m_bIsSafeAttackMode) AddEventList(NOTIFY_MSG_HANDLER51, 10);//"
                    m_bIsSafeAttackMode = false;
                    break;
            }
            break;

        case DEF_NOTIFY_IPACCOUNTINFO:
            ZeroMemory(cTemp, sizeof(cTemp));
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            strcpy(cTemp, cp);
            AddEventList(cTemp);
            break;

        case DEF_NOTIFY_REWARDGOLD:
            dwp = (uint32_t *)(pData + DEF_INDEX2_MSGTYPE + 2);
            m_iRewardGold = *dwp;
            break;

        case DEF_NOTIFY_SERVERSHUTDOWN:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            if (m_bIsDialogEnabled[25] == false)
                EnableDialogBox(25, *cp, 0, 0);
            else m_stDialogBoxInfo[25].cMode = *cp;
            PlaySound('E', 27, 0);
            break;

        case DEF_NOTIFY_GLOBALATTACKMODE:
            NotifyMsg_GlobalAttackMode(pData);
            break;

        case DEF_NOTIFY_WHETHERCHANGE:
            NotifyMsg_WhetherChange(pData);
            break;

        case DEF_NOTIFY_FISHCANCELED:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            wp = (uint16_t *)cp;
            switch (*wp)
            {
                case 0:
                    AddEventList(NOTIFY_MSG_HANDLER52, 10);
                    DisableDialogBox(24);
                    break;

                case 1:
                    AddEventList(NOTIFY_MSG_HANDLER53, 10);
                    DisableDialogBox(24);
                    break;

                case 2:
                    AddEventList(NOTIFY_MSG_HANDLER54, 10);
                    DisableDialogBox(24);
                    break;
            }
            break;

        case DEF_NOTIFY_FISHSUCCESS:
            AddEventList(NOTIFY_MSG_HANDLER55, 10);
            PlaySound('E', 23, 5);
            PlaySound('E', 17, 5);
            switch (m_sPlayerType)
            {
                case 1:
                case 2:
                case 3:
                    PlaySound('C', 21, 0);
                    break;

                case 4:
                case 5:
                case 6:
                    PlaySound('C', 22, 0);
                    break;
            }
            break;

        case DEF_NOTIFY_FISHFAIL:
            AddEventList(NOTIFY_MSG_HANDLER56, 10);
            PlaySound('E', 24, 5);
            break;

        case DEF_NOTIFY_FISHCHANCE:
            NotifyMsg_FishChance(pData);
            break;

        case DEF_NOTIFY_EVENTFISHMODE:
            NotifyMsg_EventFishMode(pData);
            break;

        case DEF_NOTIFY_NOTICEMSG:
            NotifyMsg_NoticeMsg(pData);
            break;

        case DEF_NOTIFY_RATINGPLAYER:
            NotifyMsg_RatingPlayer(pData);
            break;

        case DEF_NOTIFY_CANNOTRATING:
            NotifyMsg_CannotRating(pData);
            break;

        case DEF_NOTIFY_ADMINUSERLEVELLOW:
            AddEventList(NOTIFY_MSG_HANDLER58, 10);
            break;

        case DEF_NOTIFY_NOGUILDMASTERLEVEL:
            AddEventList(NOTIFY_MSG_HANDLER59, 10);
            break;
        case DEF_NOTIFY_SUCCESSBANGUILDMAN:
            AddEventList(NOTIFY_MSG_HANDLER60, 10);
            break;
        case DEF_NOTIFY_CANNOTBANGUILDMAN:
            AddEventList(NOTIFY_MSG_HANDLER61, 10);
            break;

        case DEF_NOTIFY_PLAYERSHUTUP:
            NotifyMsg_PlayerShutUp(pData);
            break;

        case DEF_NOTIFY_TIMECHANGE:
            NotifyMsg_TimeChange(pData);
            break;

        case DEF_NOTIFY_TOBERECALLED:
            AddEventList(NOTIFY_MSG_HANDLER62, 10);
            break;

        case DEF_NOTIFY_HUNGER:
            NotifyMsg_Hunger(pData);
            break;

        case DEF_NOTIFY_PLAYERPROFILE:
            NotifyMsg_PlayerProfile(pData);
            break;

        case DEF_NOTIFY_WHISPERMODEON:
            NotifyMsg_WhisperMode(true, pData);
            break;

        case DEF_NOTIFY_WHISPERMODEOFF:
            NotifyMsg_WhisperMode(false, pData);
            break;

        case DEF_NOTIFY_PLAYERONGAME:
            NotifyMsg_PlayerStatus(true, pData);
            break;

        case DEF_NOTIFY_PLAYERNOTONGAME:
            NotifyMsg_PlayerStatus(false, pData);
            break;

        case DEF_NOTIFY_CHARISMA:
            NotifyMsg_Charisma(pData);
            break;

        case DEF_NOTIFY_ITEMSOLD:
            DisableDialogBox(23);
            break;

        case DEF_NOTIFY_ITEMREPAIRED:
            DisableDialogBox(23);
            NotifyMsg_ItemRepaired(pData);
            break;

        case DEF_NOTIFY_CANNOTREPAIRITEM:
            NotifyMsg_CannotRepairItem(pData);
            break;

        case DEF_NOTIFY_CANNOTSELLITEM:
            NotifyMsg_CannotSellItem(pData);
            break;

        case DEF_NOTIFY_REPAIRITEMPRICE:
            NotifyMsg_RepairItemPrice(pData);
            break;

        case DEF_NOTIFY_SELLITEMPRICE:
            NotifyMsg_SellItemPrice(pData);
            break;

        case DEF_NOTIFY_SHOWMAP:
            NotifyMsg_ShowMap(pData);
            break;

        case DEF_NOTIFY_SKILLUSINGEND:
            NotifyMsg_SkillUsingEnd(pData);
            break;

        case DEF_NOTIFY_TOTALUSERS:
            NotifyMsg_TotalUsers(pData);
            break;

        case DEF_NOTIFY_MAGICEFFECTOFF:
            NotifyMsg_MagicEffectOff(pData);
            break;

        case DEF_NOTIFY_MAGICEFFECTON:
            NotifyMsg_MagicEffectOn(pData);
            break;

        case DEF_NOTIFY_CANNOTITEMTOBANK:
            AddEventList(NOTIFY_MSG_HANDLER63, 10);
            break;

        case DEF_NOTIFY_SERVERCHANGE:
            NotifyMsg_ServerChange(pData);
            break;

        case DEF_NOTIFY_SKILL:
            NotifyMsg_Skill(pData);
            break;

        case DEF_NOTIFY_SETITEMCOUNT:
            NotifyMsg_SetItemCount(pData);
            break;

        case DEF_NOTIFY_ITEMDEPLETED_ERASEITEM:
            NotifyMsg_ItemDepleted_EraseItem(pData);
            break;

        case DEF_NOTIFY_DROPITEMFIN_ERASEITEM:
            NotifyMsg_DropItemFin_EraseItem(pData);
            break;

        case DEF_NOTIFY_GIVEITEMFIN_ERASEITEM:
            NotifyMsg_GiveItemFin_EraseItem(pData);
            break;

        case DEF_NOTIFY_ENEMYKILLREWARD:
            NotifyMsg_EnemyKillReward(pData);
            break;

        case DEF_NOTIFY_PKCAPTURED:
            NotifyMsg_PKcaptured(pData);
            break;

        case DEF_NOTIFY_PKPENALTY:
            NotifyMsg_PKpenalty(pData);
            break;

        case DEF_NOTIFY_ITEMTOBANK:
            NotifyMsg_ItemToBank(pData);
            break;

        case DEF_NOTIFY_TRAVELERLIMITEDLEVEL:
            AddEventList(NOTIFY_MSG_HANDLER64, 10);
            break;

        case DEF_NOTIFY_LIMITEDLEVEL:
            AddEventList(NOTIFYMSG_LIMITED_LEVEL1, 10);
            break;

        case DEF_NOTIFY_ITEMLIFESPANEND:
            NotifyMsg_ItemLifeSpanEnd(pData);
            break;

        case DEF_NOTIFY_ITEMRELEASED:
            NotifyMsg_ItemReleased(pData);
            break;

        case DEF_NOTIFY_ITEMOBTAINED:
            NotifyMsg_ItemObtained(pData);
            break;

        case DEF_NOTIFY_ITEMPURCHASED:
            NotifyMsg_ItemPurchased(pData);
            break;

        case DEF_NOTIFY_QUERY_JOINGUILDREQPERMISSION:
            NotifyMsg_QueryJoinGuildPermission(pData);
            break;

        case DEF_NOTIFY_QUERY_DISMISSGUILDREQPERMISSION:
            NotifyMsg_QueryDismissGuildPermission(pData);
            break;

        case DEF_COMMONTYPE_JOINGUILDAPPROVE:
            NotifyMsg_JoinGuildApprove(pData);
            break;

        case DEF_COMMONTYPE_JOINGUILDREJECT:
            NotifyMsg_JoinGuildReject(pData);
            break;

        case DEF_COMMONTYPE_DISMISSGUILDAPPROVE:
            NotifyMsg_DismissGuildApprove(pData);
            break;

        case DEF_COMMONTYPE_DISMISSGUILDREJECT:
            NotifyMsg_DismissGuildReject(pData);
            break;

        case DEF_NOTIFY_CANNOTCARRYMOREITEM:
            AddEventList(NOTIFY_MSG_HANDLER65, 10);//"
            AddEventList(NOTIFY_MSG_HANDLER66, 10);//"
            // Bank dialog Box
            m_stDialogBoxInfo[14].cMode = 0;
            break;

        case DEF_NOTIFY_NOTENOUGHGOLD:
            DisableDialogBox(23);
            AddEventList(NOTIFY_MSG_HANDLER67, 10);//"Gold
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            if (*cp >= 0)
            {
                m_bIsItemDisabled[*cp] = false;
            }
            break;

        case DEF_NOTIFY_HP:
            NotifyMsg_HP(pData);
            break;
        case DEF_NOTIFY_MP:
            NotifyMsg_MP(pData);
            break;
        case DEF_NOTIFY_SP:
            NotifyMsg_SP(pData);
            break;
        case DEF_NOTIFY_KILLED:
            NotifyMsg_Killed(pData);
            break;
        case DEF_NOTIFY_EXP:
            NotifyMsg_Exp(pData);
            break;
        case DEF_NOTIFY_GUILDDISBANDED:
            NotifyMsg_GuildDisbanded(pData);
            break;
        case DEF_NOTIFY_CANNOTJOINMOREGUILDSMAN:
            NotifyMsg_CannotJoinMoreGuildsMan(pData);
            break;
        case DEF_NOTIFY_NEWGUILDSMAN:
            NotifyMsg_NewGuildsMan(pData);
            break;
        case DEF_NOTIFY_DISMISSGUILDSMAN:
            NotifyMsg_DismissGuildsMan(pData);
            break;
        case DEF_NOTIFY_MAGICSTUDYSUCCESS:
            NotifyMsg_MagicStudySuccess(pData);
            break;
        case DEF_NOTIFY_MAGICSTUDYFAIL:
            NotifyMsg_MagicStudyFail(pData);
            break;
        case DEF_NOTIFY_SKILLTRAINSUCCESS:
            NotifyMsg_SkillTrainSuccess(pData);
            break;
        case DEF_NOTIFY_SKILLTRAINFAIL:
            break;
        case DEF_NOTIFY_FORCEDISCONN:
            NotifyMsg_ForceDisconn(pData);
            break;
        case DEF_NOTIFY_FIGHTZONERESERVE:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            switch (*ip)
            {
                case -5:
                    AddEventList(NOTIFY_MSG_HANDLER68, 10);
                    break;
                case -4:
                    AddEventList(NOTIFY_MSG_HANDLER69, 10);
                    break;
                case -3:
                    AddEventList(NOTIFY_MSG_HANDLER70, 10);
                    break;
                case -2:
                    m_iFightzoneNumber = 0;
                    AddEventList(NOTIFY_MSG_HANDLER71, 10);
                    break;
                case -1:
                    m_iFightzoneNumber = m_iFightzoneNumber * -1;
                    AddEventList(NOTIFY_MSG_HANDLER72, 10);
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    wsprintfA(cTxt, NOTIFY_MSG_HANDLER73, *ip);//"
                    AddEventList(cTxt, 10);
                    break;
            }
            break;
    }
}

