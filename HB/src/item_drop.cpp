//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include "Game.h"
#include "lan_eng.h"

void CGame::bItemDrop_Bank(short msX, short msY)
{
    m_stDialogBoxInfo[39].sV1 = m_stMCursor.sSelectedObjectID;
    if (m_cCommand < 0) return;
    if (m_pItemList[m_stDialogBoxInfo[39].sV1] == 0) return;
    if (m_bIsItemDisabled[m_stDialogBoxInfo[39].sV1] == true) return;
    if (m_bIsDialogEnabled[17] == true)
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }
    if ((m_bIsDialogEnabled[20] == true) && ((m_stDialogBoxInfo[20].cMode == 1) || (m_stDialogBoxInfo[20].cMode == 2)))
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }
    if (m_bIsDialogEnabled[23] == true)
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }
    if (m_bIsDialogEnabled[4] == true)
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }
    if (((m_pItemList[m_stDialogBoxInfo[39].sV1]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[m_stDialogBoxInfo[39].sV1]->m_cItemType == DEF_ITEMTYPE_ARROW)) && (m_pItemList[m_stDialogBoxInfo[39].sV1]->m_dwCount > 1))
    {
        m_stDialogBoxInfo[17].sX = msX - 140;
        m_stDialogBoxInfo[17].sY = msY - 70;
        if (m_stDialogBoxInfo[17].sY < 0) m_stDialogBoxInfo[17].sY = 0;

        m_stDialogBoxInfo[17].sV1 = m_sPlayerX + 1;
        m_stDialogBoxInfo[17].sV2 = m_sPlayerY + 1;
        m_stDialogBoxInfo[17].sV3 = 1002;// NPC
        m_stDialogBoxInfo[17].sV4 = m_stDialogBoxInfo[39].sV1;

        ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
        EnableDialogBox(17, m_stDialogBoxInfo[39].sV1, m_pItemList[m_stDialogBoxInfo[39].sV1]->m_dwCount, 0);
    }
    else
    {
        if (_iGetBankItemCount() >= (DEF_MAXBANKITEMS - 1)) AddEventList(DLGBOX_CLICK_NPCACTION_QUERY9, 10);
        else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, m_stDialogBoxInfo[39].sV1, 1, m_stDialogBoxInfo[39].sV5, m_stDialogBoxInfo[39].sV6, m_pItemList[m_stDialogBoxInfo[39].sV1]->m_cName, m_stDialogBoxInfo[39].sV4); //v1.4
    }
}

void CGame::bItemDrop_SkillDialog()
{
    int iConsumeNum;
    char cItemID;

    if (m_cCommand < 0) return;
    cItemID = (char)m_stMCursor.sSelectedObjectID;
    if (m_pItemList[cItemID] == 0) return;
    if (m_bIsItemDisabled[cItemID] == true) return;

    if (m_bIsDialogEnabled[17] == true)
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }

    if ((m_bIsDialogEnabled[20] == true)
        && ((m_stDialogBoxInfo[20].cMode == 1) || (m_stDialogBoxInfo[20].cMode == 2)))
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }

    if (m_bIsDialogEnabled[23] == true)
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }

    switch (m_stDialogBoxInfo[26].cMode)
    {
        case 1:
            if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME)
            {
                iConsumeNum = 0;
                if (m_stDialogBoxInfo[26].sV1 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV2 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV3 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV4 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV5 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV6 == cItemID) iConsumeNum++;
                if (iConsumeNum >= (int)(m_pItemList[cItemID]->m_dwCount)) return;
            }
            if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EAT) ||
                (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) ||
                (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_NONE))
            {
            }
            else return;

            if (m_stDialogBoxInfo[26].sV1 == -1)
            {
                m_stDialogBoxInfo[26].sV1 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV2 == -1)
            {
                m_stDialogBoxInfo[26].sV2 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV3 == -1)
            {
                m_stDialogBoxInfo[26].sV3 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV4 == -1)
            {
                m_stDialogBoxInfo[26].sV4 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV5 == -1)
            {
                m_stDialogBoxInfo[26].sV5 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV6 == -1)
            {
                m_stDialogBoxInfo[26].sV6 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            AddEventList(BITEMDROP_SKILLDIALOG4, 10);
            break;

        case 4:
            if (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME)
            {
                iConsumeNum = 0;
                if (m_stDialogBoxInfo[26].sV1 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV2 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV3 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV4 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV5 == cItemID) iConsumeNum++;
                if (m_stDialogBoxInfo[26].sV6 == cItemID) iConsumeNum++;
                if (iConsumeNum >= (int)(m_pItemList[cItemID]->m_dwCount)) return;
            }

            if (m_stDialogBoxInfo[26].sV1 == -1)
            {
                m_stDialogBoxInfo[26].sV1 = cItemID;
                m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV2 == -1)
            {
                m_stDialogBoxInfo[26].sV2 = cItemID;
                m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV3 == -1)
            {
                m_stDialogBoxInfo[26].sV3 = cItemID;
                m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV4 == -1)
            {
                m_stDialogBoxInfo[26].sV4 = cItemID;
                m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV5 == -1)
            {
                m_stDialogBoxInfo[26].sV5 = cItemID;
                m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV6 == -1)
            {
                m_stDialogBoxInfo[26].sV6 = cItemID;
                m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            AddEventList(BITEMDROP_SKILLDIALOG4, 10); // "There is no more space for ingredients."
            break;

            // Crafting
        case 7:
            if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_NONE)			// Merien Stone
                || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_EQUIP)		// Necks XXXMagins
                || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME)		// stones
                || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_MATERIAL))	// XXXwares
            {
            }
            else return;

            if (m_stDialogBoxInfo[26].sV1 == -1)
            {
                m_stDialogBoxInfo[26].sV1 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV2 == -1)
            {
                m_stDialogBoxInfo[26].sV2 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV3 == -1)
            {
                m_stDialogBoxInfo[26].sV3 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV4 == -1)
            {
                m_stDialogBoxInfo[26].sV4 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV5 == -1)
            {
                m_stDialogBoxInfo[26].sV5 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            else if (m_stDialogBoxInfo[26].sV6 == -1)
            {
                m_stDialogBoxInfo[26].sV6 = cItemID;
                if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) && (m_pItemList[cItemID]->m_dwCount > 1))
                {
                }
                else m_bIsItemDisabled[cItemID] = true;
                return;
            }
            AddEventList(BITEMDROP_SKILLDIALOG4, 10); // "There is no more space for ingredients."
            break;

        default:
            break;
    }
}

// Slates Item Drag&Drop
void CGame::bItemDrop_Slates()
{
    char cItemID;
    if (m_cCommand < 0) return;
    cItemID = (char)m_stMCursor.sSelectedObjectID;
    if (m_pItemList[cItemID] == 0) return;
    if (m_bIsItemDisabled[cItemID] == true) return;
    if (m_bIsDialogEnabled[17] == true)
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }

    if ((m_bIsDialogEnabled[20] == true) &&
        ((m_stDialogBoxInfo[20].cMode == 1) || (m_stDialogBoxInfo[20].cMode == 2)))
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }

    if (m_bIsDialogEnabled[23] == true)
    {
        AddEventList(BITEMDROP_SKILLDIALOG1, 10);
        return;
    }

    switch (m_stDialogBoxInfo[40].cMode)
    {
        case 1:
            if ((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_USE_SKILL_ENABLEDIALOGBOX) && (m_pItemList[cItemID]->m_sSpriteFrame >= 151) && (m_pItemList[cItemID]->m_sSpriteFrame <= 154))
            {
                char cItemIDText[20];
                switch (m_pItemList[cItemID]->m_sSpriteFrame)
                {
                    case 151:
                        if (m_stDialogBoxInfo[40].sV1 == -1)
                        {
                            m_bIsItemDisabled[cItemID] = true;
                            m_stDialogBoxInfo[40].sV1 = cItemID;
                            wsprintfA(cItemIDText, "Item ID : %d", cItemID);
                            AddEventList(cItemIDText, 10);
                        }
                        break;
                    case 152:
                        if (m_stDialogBoxInfo[40].sV2 == -1)
                        {
                            m_bIsItemDisabled[cItemID] = true;
                            m_stDialogBoxInfo[40].sV2 = cItemID;
                            wsprintfA(cItemIDText, "Item ID : %d", cItemID);
                            AddEventList(cItemIDText, 10);
                        }
                        break;
                    case 153:
                        if (m_stDialogBoxInfo[40].sV3 == -1)
                        {
                            m_bIsItemDisabled[cItemID] = true;
                            m_stDialogBoxInfo[40].sV3 = cItemID;
                            wsprintfA(cItemIDText, "Item ID : %d", cItemID);
                            AddEventList(cItemIDText, 10);
                        }
                        break;
                    case 154:
                        if (m_stDialogBoxInfo[40].sV4 == -1)
                        {
                            m_bIsItemDisabled[cItemID] = true;
                            m_stDialogBoxInfo[40].sV4 = cItemID;
                            wsprintfA(cItemIDText, "Item ID : %d", cItemID);
                            AddEventList(cItemIDText, 10);
                        }
                        break;
                }
            }
            break;

        default:
            break;
    }
}


void CGame::bItemDrop_Character()
{
    ItemEquipHandler((char)m_stMCursor.sSelectedObjectID);
}

void CGame::bItemDrop_Inventory(short msX, short msY)
{
    short sX, sY, dX, dY;
    char  cTxt[120];
    if (m_cCommand < 0) return;
    if (m_pItemList[m_stMCursor.sSelectedObjectID] == 0) return;
    if ((m_bSkillUsingStatus == true) && (m_bIsItemEquipped[m_stMCursor.sSelectedObjectID] == true))
    {
        AddEventList(BITEMDROP_INVENTORY1, 10);
        return;
    }
    if (m_bIsItemDisabled[m_stMCursor.sSelectedObjectID] == true) return;
    sY = m_stDialogBoxInfo[2].sY;
    sX = m_stDialogBoxInfo[2].sX;
    dX = msX - sX - 32 - m_stMCursor.sDistX;
    dY = msY - sY - 44 - m_stMCursor.sDistY;
    if (dY < -10) dY = -10;
    if (dX < 0)   dX = 0;
    if (dX > 170) dX = 170;
    if (dY > 95) dY = 95;

    m_pItemList[m_stMCursor.sSelectedObjectID]->m_sX = dX;
    m_pItemList[m_stMCursor.sSelectedObjectID]->m_sY = dY;

    short sTmpSpr, sTmpSprFrm;
    sTmpSpr = m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSprite;
    sTmpSprFrm = m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSpriteFrame;

    char cItemID;
    if (m_bShiftPressed)
    {
        for (int i = 0; i < DEF_MAXITEMS; i++)
        {
            if (m_cItemOrder[DEF_MAXITEMS - 1 - i] != -1)
            {
                cItemID = m_cItemOrder[DEF_MAXITEMS - 1 - i];
                if (m_pItemList[cItemID] != 0 && memcmp(m_pItemList[cItemID]->m_cName, m_pItemList[m_stMCursor.sSelectedObjectID]->m_cName, 20) == 0)
                {
                    m_pItemList[cItemID]->m_sX = dX;
                    m_pItemList[cItemID]->m_sY = dY;
                    bSendCommand(MSGID_REQUEST_SETITEMPOS, 0, cItemID, dX, dY, 0, 0);
                }
            }
        }
    }
    else bSendCommand(MSGID_REQUEST_SETITEMPOS, 0, (char)(m_stMCursor.sSelectedObjectID), dX, dY, 0, 0);

    if (m_bIsItemEquipped[m_stMCursor.sSelectedObjectID] == true)
    {
        char cStr1[64], cStr2[64], cStr3[64];
        GetItemName(m_pItemList[m_stMCursor.sSelectedObjectID], cStr1, cStr2, cStr3);
        wsprintfA(cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
        AddEventList(cTxt, 10);

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
    }
}

void CGame::bItemDrop_SellList(short msX, short msY)
{
    int i;
    char cItemID;

    cItemID = (char)m_stMCursor.sSelectedObjectID;

    if (m_pItemList[cItemID] == 0) return;
    if (m_bIsItemDisabled[cItemID] == true) return;
    if (m_cCommand < 0) return;
    for (i = 0; i < DEF_MAXSELLLIST; i++)
        if (m_stSellItemList[i].iIndex == cItemID)
        {
            AddEventList(BITEMDROP_SELLLIST1, 10);
            return;
        }
    if (strcmp(m_pItemList[cItemID]->m_cName, "Gold") == 0)
    {
        AddEventList(BITEMDROP_SELLLIST2, 10);
        return;
    }
    if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
    {
        ZeroMemory(G_cTxt, sizeof(G_cTxt));
        char cStr1[64], cStr2[64], cStr3[64];
        GetItemName(m_pItemList[cItemID], cStr1, cStr2, cStr3);
        wsprintfA(G_cTxt, NOTIFYMSG_CANNOT_SELL_ITEM2, cStr1);
        AddEventList(G_cTxt, 10);
        return;
    }

    if (((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW)) &&
        (m_pItemList[cItemID]->m_dwCount > 1))
    {
        m_stDialogBoxInfo[17].sX = msX - 140;
        m_stDialogBoxInfo[17].sY = msY - 70;
        if (m_stDialogBoxInfo[17].sY < 0) m_stDialogBoxInfo[17].sY = 0;
        m_stDialogBoxInfo[17].sV1 = m_sPlayerX + 1;
        m_stDialogBoxInfo[17].sV2 = m_sPlayerY + 1;
        m_stDialogBoxInfo[17].sV3 = 1001;
        m_stDialogBoxInfo[17].sV4 = cItemID;
        ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
        EnableDialogBox(17, cItemID, m_pItemList[cItemID]->m_dwCount, 0);
        m_bIsItemDisabled[cItemID] = true;
    }
    else
    {
        for (i = 0; i < DEF_MAXSELLLIST; i++)
            if (m_stSellItemList[i].iIndex == -1)
            {
                m_stSellItemList[i].iIndex = cItemID;
                m_stSellItemList[i].iAmount = 1;
                m_bIsItemDisabled[cItemID] = true;
                return;
            }
        AddEventList(BITEMDROP_SELLLIST3, 10);
    }
}

void CGame::bItemDrop_ItemUpgrade()
{
    char cItemID;
    cItemID = (char)m_stMCursor.sSelectedObjectID;
    if (m_bIsItemDisabled[cItemID] == true) return;
    if (m_cCommand < 0) return;
#ifdef DEF_EQUILBRIUM_PROJECT // Allow enchant bars with Merien stones
    if ((m_pItemList[cItemID]->m_cEquipPos == DEF_EQUIPPOS_NONE)
        && (m_stDialogBoxInfo[34].cMode != 6)) return;
#else
    if (m_pItemList[cItemID]->m_cEquipPos == DEF_EQUIPPOS_NONE) return;
#endif

    switch (m_stDialogBoxInfo[34].cMode)
    {
        case 1:
            m_bIsItemDisabled[m_stDialogBoxInfo[34].sV1] = false;
            m_stDialogBoxInfo[34].sV1 = cItemID;
            m_bIsItemDisabled[cItemID] = true;
            PlaySound('E', 29, 0);
            break;

        case 6:
            m_bIsItemDisabled[m_stDialogBoxInfo[34].sV1] = false;
            m_stDialogBoxInfo[34].sV1 = cItemID;
            m_bIsItemDisabled[cItemID] = true;
            PlaySound('E', 29, 0);
            break;

#ifdef DEF_EQUILIBRIUM_PROJECT
        case 11: // Alchim
            m_bIsItemDisabled[m_stDialogBoxInfo[34].sV1] = false;
            m_stDialogBoxInfo[34].sV1 = cItemID;
            m_bIsItemDisabled[cItemID] = true;
            PlaySound('E', 29, 0);
            break;
#endif
    }
}


void CGame::bItemDrop_ExternalScreen(char cItemID, short msX, short msY)
{
    char  cName[21];
    short sType, tX, tY;
    int iStatus;

    if (bCheckItemOperationEnabled(cItemID) == false) return;

    if ((m_sMCX != 0) && (m_sMCY != 0) && (abs(m_sPlayerX - m_sMCX) <= 8) && (abs(m_sPlayerY - m_sMCY) <= 8))
    {
        ZeroMemory(cName, sizeof(cName));
        m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sType, &iStatus, &m_wCommObjectID);
        if (memcmp(m_cPlayerName, cName, 10) == 0)
        {
        }
        else
        {
            if (((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW))
                && (m_pItemList[cItemID]->m_dwCount > 1))
            {
                m_stDialogBoxInfo[17].sX = msX - 140;
                m_stDialogBoxInfo[17].sY = msY - 70;
                if (m_stDialogBoxInfo[17].sY < 0) m_stDialogBoxInfo[17].sY = 0;
                m_stDialogBoxInfo[17].sV1 = m_sMCX;
                m_stDialogBoxInfo[17].sV2 = m_sMCY;
                m_stDialogBoxInfo[17].sV3 = sType;
                m_stDialogBoxInfo[17].sV4 = m_wCommObjectID;
                ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
                if (sType < 10)
                    memcpy(m_stDialogBoxInfo[17].cStr, cName, 10);
                else
                {
                    GetNpcName(sType, m_stDialogBoxInfo[17].cStr);
                }
                EnableDialogBox(17, cItemID, m_pItemList[cItemID]->m_dwCount, 0);
            }
            else
            {
                switch (sType)
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        EnableDialogBox(20, 1, cItemID, sType);
                        m_stDialogBoxInfo[20].sV3 = 1;
                        m_stDialogBoxInfo[20].sV4 = m_wCommObjectID;
                        m_stDialogBoxInfo[20].sV5 = m_sMCX;
                        m_stDialogBoxInfo[20].sV6 = m_sMCY;

                        tX = msX - 117;
                        tY = msY - 50;
                        if (tX < 0) tX = 0;
                        if ((tX + 235) > 639) tX = 639 - 235;
                        if (tY < 0) tY = 0;
                        if ((tY + 100) > 479) tY = 479 - 100;
                        m_stDialogBoxInfo[20].sX = tX;
                        m_stDialogBoxInfo[20].sY = tY;

                        ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
                        strcpy(m_stDialogBoxInfo[20].cStr, cName);
                        //bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, cItemID, 1, m_sMCX, m_sMCY, m_pItemList[cItemID]->m_cName); //v1.4
                        break;

                    case 20: // Howard
                        EnableDialogBox(20, 3, cItemID, sType);
                        m_stDialogBoxInfo[20].sV3 = 1;
                        m_stDialogBoxInfo[20].sV4 = m_wCommObjectID; // v1.4
                        m_stDialogBoxInfo[20].sV5 = m_sMCX;
                        m_stDialogBoxInfo[20].sV6 = m_sMCY;

                        tX = msX - 117;
                        tY = msY - 50;
                        if (tX < 0) tX = 0;
                        if ((tX + 235) > 639) tX = 639 - 235;
                        if (tY < 0) tY = 0;
                        if ((tY + 100) > 479) tY = 479 - 100;
                        m_stDialogBoxInfo[20].sX = tX;
                        m_stDialogBoxInfo[20].sY = tY;

                        ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
                        GetNpcName(sType, m_stDialogBoxInfo[20].cStr);
                        //bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, cItemID, 1, m_sMCX, m_sMCY, m_pItemList[cItemID]->m_cName);
                        break;

                    case 15: // ShopKeeper-W
                    case 24: // Tom
                        EnableDialogBox(20, 2, cItemID, sType);
                        m_stDialogBoxInfo[20].sV3 = 1;
                        m_stDialogBoxInfo[20].sV4 = m_wCommObjectID; // v1.4
                        m_stDialogBoxInfo[20].sV5 = m_sMCX;
                        m_stDialogBoxInfo[20].sV6 = m_sMCY;

                        tX = msX - 117;
                        tY = msY - 50;
                        if (tX < 0) tX = 0;
                        if ((tX + 235) > 639) tX = 639 - 235;
                        if (tY < 0) tY = 0;
                        if ((tY + 100) > 479) tY = 479 - 100;
                        m_stDialogBoxInfo[20].sX = tX;
                        m_stDialogBoxInfo[20].sY = tY;

                        ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
                        GetNpcName(sType, m_stDialogBoxInfo[20].cStr);
                        break;

                    default:
                        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, cItemID, 1, m_sMCX, m_sMCY, m_pItemList[cItemID]->m_cName);
                        break;
                }
                //m_bIsItemDisabled[cItemID] = true;
            }
            m_bIsItemDisabled[cItemID] = true;
        }
    }
    else
    {
        if (((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW))
            && (m_pItemList[cItemID]->m_dwCount > 1))
        {
            m_stDialogBoxInfo[17].sX = msX - 140;
            m_stDialogBoxInfo[17].sY = msY - 70;
            if (m_stDialogBoxInfo[17].sY < 0)		m_stDialogBoxInfo[17].sY = 0;
            m_stDialogBoxInfo[17].sV1 = 0;
            m_stDialogBoxInfo[17].sV2 = 0;
            m_stDialogBoxInfo[17].sV3 = 0;
            m_stDialogBoxInfo[17].sV4 = 0;
            ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
            EnableDialogBox(17, cItemID, m_pItemList[cItemID]->m_dwCount, 0);
        }
        else
        {
            if (_ItemDropHistory(m_pItemList[cItemID]->m_cName))
            {
                m_stDialogBoxInfo[4].sX = msX - 140;
                m_stDialogBoxInfo[4].sY = msY - 70;
                if (m_stDialogBoxInfo[4].sY < 0)	m_stDialogBoxInfo[4].sY = 0;
                m_stDialogBoxInfo[4].sV1 = 0;
                m_stDialogBoxInfo[4].sV2 = 0;
                m_stDialogBoxInfo[4].sV3 = 1;
                m_stDialogBoxInfo[4].sV4 = 0;
                m_stDialogBoxInfo[4].sV5 = cItemID;
                ZeroMemory(m_stDialogBoxInfo[4].cStr, sizeof(m_stDialogBoxInfo[4].cStr));
                EnableDialogBox(4, cItemID, m_pItemList[cItemID]->m_dwCount, 0);
            }
            else
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_ITEMDROP, 0, cItemID, 1, 0, m_pItemList[cItemID]->m_cName);
            }
        }
        m_bIsItemDisabled[cItemID] = true;
    }
}


void CGame::bItemDrop_IconPannel(short msX, short msY)
{
    short sX, sY, sItemIndex;
    sX = m_stDialogBoxInfo[30].sX;	sY = m_stDialogBoxInfo[30].sY;

    sItemIndex = m_stMCursor.sSelectedObjectID;
    if (m_bIsItemDisabled[sItemIndex] == true) return;
    if (m_cCommand < 0) return;
    if ((453 < msX) && (486 > msX) && (440 < msY) && (475 > msY))
    {
        bItemDrop_Inventory(m_stDialogBoxInfo[2].sX + (rand() % 148), m_stDialogBoxInfo[2].sY + (rand() % 55));
        return;
    }
    if ((425 < msX) && (448 > msX) && (440 < msY) && (475 > msY))
    {
        bItemDrop_Character();
        return;
    }
}


void CGame::bItemDrop_ExchangeDialog(short msX, short msY)
{
    char cItemID;
    if (m_cCommand < 0) return;
    if (m_stDialogBoxExchangeInfo[3].sV1 != -1) return; //Do not accept item's drop if already 4 items.

    cItemID = (char)m_stMCursor.sSelectedObjectID;
    if (((m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_CONSUME) || (m_pItemList[cItemID]->m_cItemType == DEF_ITEMTYPE_ARROW)) &&
        (m_pItemList[cItemID]->m_dwCount > 1))
    {
        m_stDialogBoxInfo[17].sX = msX - 140;
        m_stDialogBoxInfo[17].sY = msY - 70;
        if (m_stDialogBoxInfo[17].sY < 0) m_stDialogBoxInfo[17].sY = 0;
        m_stDialogBoxInfo[17].sV1 = m_sPlayerX + 1;
        m_stDialogBoxInfo[17].sV2 = m_sPlayerY + 1;
        m_stDialogBoxInfo[17].sV3 = 1000;
        m_stDialogBoxInfo[17].sV4 = cItemID;
        //m_stDialogBoxInfo[27].sView = cItemID;
        if (m_stDialogBoxExchangeInfo[0].sV1 == -1)			m_stDialogBoxExchangeInfo[0].sItemID = cItemID;
        else if (m_stDialogBoxExchangeInfo[1].sV1 == -1)	m_stDialogBoxExchangeInfo[1].sItemID = cItemID;
        else if (m_stDialogBoxExchangeInfo[2].sV1 == -1)	m_stDialogBoxExchangeInfo[2].sItemID = cItemID;
        else if (m_stDialogBoxExchangeInfo[3].sV1 == -1)	m_stDialogBoxExchangeInfo[3].sItemID = cItemID;
        else return; // Impossible case, tested at function beginning
        ZeroMemory(m_stDialogBoxInfo[17].cStr, sizeof(m_stDialogBoxInfo[17].cStr));
        EnableDialogBox(17, cItemID, m_pItemList[cItemID]->m_dwCount, 0);
        return;
    }
    else // hum? déjà on affiche? , bon je désactive, ca devrait plutôt s'afficher lors du retour du serveur.
    {	/*m_stDialogBoxInfo[27].sV1 = m_pItemList[cItemID]->m_sSprite;
        m_stDialogBoxInfo[27].sV2 = m_pItemList[cItemID]->m_sSpriteFrame;
        m_stDialogBoxInfo[27].sV3 = 1;
        m_stDialogBoxInfo[27].sV4 = m_pItemList[cItemID]->m_cItemColor;
        m_stDialogBoxInfo[27].sView = cItemID;*/
        if (m_stDialogBoxExchangeInfo[0].sV1 == -1)			m_stDialogBoxExchangeInfo[0].sItemID = cItemID;
        else if (m_stDialogBoxExchangeInfo[1].sV1 == -1)	m_stDialogBoxExchangeInfo[1].sItemID = cItemID;
        else if (m_stDialogBoxExchangeInfo[2].sV1 == -1)	m_stDialogBoxExchangeInfo[2].sItemID = cItemID;
        else if (m_stDialogBoxExchangeInfo[3].sV1 == -1)	m_stDialogBoxExchangeInfo[3].sItemID = cItemID;
        else return; // Impossible case, tested at function beginning
        m_bIsItemDisabled[cItemID] = true;
        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETEXCHANGEITEM, 0, cItemID, 1, 0, 0);
        //	   :bSendCommand(uint32_t dwMsgID,        uint16_t wCommand,             char cDir, int iV1, int iV2, int iV3, char * pString, int iV4)
        return;
    }
}

