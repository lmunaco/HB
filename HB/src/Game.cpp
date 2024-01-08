//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include "Game.h"
#include "lan_eng.h"

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>

extern char G_cSpriteAlphaDegree;

char _cDrawingOrder[] = { 0, 1, 0, 0, 0, 0, 0, 1, 1 };
char _cMantleDrawingOrder[] = { 0, 1, 1, 1, 0, 0, 0, 2, 2 };
char _cMantleDrawingOrderOnRun[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1 };


short _tmp_sOwnerType, _tmp_sAppr1, _tmp_sAppr2, _tmp_sAppr3, _tmp_sAppr4;//, _tmp_iStatus;
//bool _tmp_iStatus;
int _tmp_iStatus;
char  _tmp_cAction, _tmp_cDir, _tmp_cFrame, _tmp_cName[12];
int   _tmp_iChatIndex, _tmp_dx, _tmp_dy, _tmp_iApprColor, _tmp_iEffectType, _tmp_iEffectFrame, _tmp_dX, _tmp_dY; // 21.171 2002-6-14
uint16_t  _tmp_wObjectID;
char cDynamicObjectData1, cDynamicObjectData2, cDynamicObjectData3, cDynamicObjectData4;
uint16_t  wFocusObjectID;
short sFocus_dX, sFocus_dY;
char  cFocusAction, cFocusFrame, cFocusDir, cFocusName[12];
short sFocusX, sFocusY, sFocusOwnerType, sFocusAppr1, sFocusAppr2, sFocusAppr3, sFocusAppr4;
int iFocuiStatus;
int   iFocusApprColor;

extern uint64_t unixtime();
extern uint64_t unixseconds();

CGame::CGame()
    : m_DDraw{ this }
{
    m_dwCheckSprTime = 0;
    int i;
    srand((unsigned)time(0));

#ifdef _DEBUG
    m_bToggleScreen = true;
#else
    m_bToggleScreen = false;
#endif

    m_stMCursor.sCursorFrame = 0;

    m_bShowFPS = false;
    m_cDetailLevel = 2;
    m_cLoading = 0;
    m_bZoomMap = true;
    m_bIsFirstConn = true;
    m_iItemDropCnt = 0;
    m_bItemDrop = false;
    m_bIsSpecial = false;
    m_cGameMode = DEF_GAMEMODE_ONLOADING;
    m_cWhisperIndex = DEF_MAXWHISPERMSG;
    m_cGameModeCount = 0;
    ZeroMemory(m_cMapName, sizeof(m_cMapName));
    m_pMapData = nullptr;
    m_cCommandCount = 0;
    m_dwCommandTime = 0; //v2.15 SpeedHack
    m_sPlayerX = 0;
    m_sPlayerY = 0;
    m_sViewDX = 0;
    m_sViewDY = 0;
    m_cCommand = DEF_OBJECTSTOP;
    m_bIsObserverMode = false;
    for (i = 0; i < DEF_MAXSPRITES; i++) m_pSprite[i] = 0;
    for (i = 0; i < DEF_MAXTILES; i++) m_pTileSpr[i] = 0;
    for (i = 0; i < DEF_MAXEFFECTSPR; i++) m_pEffectSpr[i] = 0;

    for (i = 0; i < DEF_MAXCHATMSGS; i++) m_pChatMsgList[i] = 0;

    for (i = 0; i < DEF_MAXEFFECTS; i++) m_pEffectList[i] = 0;

    for (i = 0; i < DEF_MAXITEMS; i++) m_pItemList[i] = 0;

    for (i = 0; i < DEF_MAXBANKITEMS; i++) m_pBankList[i] = 0;

    for (i = 0; i < 4; i++) m_pCharList[i] = 0;

    for (i = 0; i < 61; i++) m_cDialogBoxOrder[i] = 0;

    for (i = 0; i < DEF_MAXMAGICTYPE; i++) m_pMagicCfgList[i] = 0;

    for (i = 0; i < DEF_MAXSKILLTYPE; i++) m_pSkillCfgList[i] = 0;

    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        m_pMsgTextList[i] = 0;
        m_pMsgTextList2[i] = 0;
        m_pAgreeMsgTextList[i] = 0;
    }

    for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pBuildItemList[i] = 0;

    for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pDispBuildItemList[i] = 0;

    // Crafting:
    for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pCraftItemList[i] = 0;
    for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pDispCraftItemList[i] = 0;



    for (i = 0; i < DEF_MAXGAMEMSGS; i++) m_pGameMsgList[i] = 0;

    m_pExID = 0;

    for (i = 0; i < DEF_MAXITEMNAMES; i++) m_pItemNameList[i] = 0;

    m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
    m_stMCursor.dwSelectClickTime = 0;

    ZeroMemory(m_cLogServerAddr, sizeof(m_cLogServerAddr));
    m_iGameServerMode = 2;

    for (i = 0; i < DEF_MAXMENUITEMS; i++)
        m_pItemForSaleList[i] = 0;

    //Character-Info Dialog(F5)
    m_stDialogBoxInfo[1].sX = 30;
    m_stDialogBoxInfo[1].sY = 30;
    m_stDialogBoxInfo[1].sSizeX = 270;
    m_stDialogBoxInfo[1].sSizeY = 376;

    //Inventory Dialog(F6)
    m_stDialogBoxInfo[2].sX = 380;
    m_stDialogBoxInfo[2].sY = 210;
    m_stDialogBoxInfo[2].sSizeX = 225;
    m_stDialogBoxInfo[2].sSizeY = 185;

    //Magic Circle Dialog(F7)
    m_stDialogBoxInfo[3].sX = 337;
    m_stDialogBoxInfo[3].sY = 57;
    m_stDialogBoxInfo[3].sSizeX = 258;//280;
    m_stDialogBoxInfo[3].sSizeY = 328;//346;

    // Item drop confirmation
    m_stDialogBoxInfo[4].sX = 0;
    m_stDialogBoxInfo[4].sY = 0;
    m_stDialogBoxInfo[4].sSizeX = 270;
    m_stDialogBoxInfo[4].sSizeY = 105;

    // Age <15 box !?!?!?
    m_stDialogBoxInfo[5].sX = 0;
    m_stDialogBoxInfo[5].sY = 0;
    m_stDialogBoxInfo[5].sSizeX = 310;
    m_stDialogBoxInfo[5].sSizeY = 170;

    // ** This is a battle area **
    m_stDialogBoxInfo[6].sX = 0;
    m_stDialogBoxInfo[6].sY = 0;
    m_stDialogBoxInfo[6].sSizeX = 310;
    m_stDialogBoxInfo[6].sSizeY = 170;

    //Guild Menu Dialog
    m_stDialogBoxInfo[7].sX = 337;
    m_stDialogBoxInfo[7].sY = 57;
    m_stDialogBoxInfo[7].sSizeX = 258;
    m_stDialogBoxInfo[7].sSizeY = 339;

    //Guild Operation Dialog
    m_stDialogBoxInfo[8].sX = 337;
    m_stDialogBoxInfo[8].sY = 57;
    m_stDialogBoxInfo[8].sSizeX = 295;
    m_stDialogBoxInfo[8].sSizeY = 346;

    //Guide Map Dialog
    m_stDialogBoxInfo[9].sX = 512;
    m_stDialogBoxInfo[9].sY = 0;
    m_stDialogBoxInfo[9].sSizeX = 128;
    m_stDialogBoxInfo[9].sSizeY = 128;

    //Chatting History Dialog(F9)
    m_stDialogBoxInfo[10].sX = 135;
    m_stDialogBoxInfo[10].sY = 273;
    m_stDialogBoxInfo[10].sSizeX = 364;
    m_stDialogBoxInfo[10].sSizeY = 162;

    //Sale Menu Dialog
    m_stDialogBoxInfo[11].sX = 70;
    m_stDialogBoxInfo[11].sY = 50;
    m_stDialogBoxInfo[11].sSizeX = 258;
    m_stDialogBoxInfo[11].sSizeY = 339;

    //Level-Up Setting Dialog
    m_stDialogBoxInfo[12].sX = 0;
    m_stDialogBoxInfo[12].sY = 0;
    m_stDialogBoxInfo[12].sSizeX = 258;
    m_stDialogBoxInfo[12].sSizeY = 339;

    //City Hall Menu Dialog
    m_stDialogBoxInfo[13].sX = 337;
    m_stDialogBoxInfo[13].sY = 57;
    m_stDialogBoxInfo[13].sSizeX = 258;
    m_stDialogBoxInfo[13].sSizeY = 339;

    //Bank Dialog
    m_stDialogBoxInfo[14].sX = 60; //337
    m_stDialogBoxInfo[14].sY = 50;
    m_stDialogBoxInfo[14].sSizeX = 258;
    m_stDialogBoxInfo[14].sSizeY = 339;
    m_stDialogBoxInfo[14].sV1 = 13;

    //Skill Menu(F8)
    m_stDialogBoxInfo[15].sX = 337;
    m_stDialogBoxInfo[15].sY = 57;
    m_stDialogBoxInfo[15].sSizeX = 258;
    m_stDialogBoxInfo[15].sSizeY = 339;

    //Magic Shop Menu
    m_stDialogBoxInfo[16].sX = 30;
    m_stDialogBoxInfo[16].sY = 30;
    m_stDialogBoxInfo[16].sSizeX = 304;
    m_stDialogBoxInfo[16].sSizeY = 328;

    //Dialog items drop external screen
    m_stDialogBoxInfo[17].sX = 0;
    m_stDialogBoxInfo[17].sY = 0;
    m_stDialogBoxInfo[17].sSizeX = 215;
    m_stDialogBoxInfo[17].sSizeY = 87;

    //Text Dialog
    m_stDialogBoxInfo[18].sX = 20;
    m_stDialogBoxInfo[18].sY = 65;
    m_stDialogBoxInfo[18].sSizeX = 258; // 238
    m_stDialogBoxInfo[18].sSizeY = 339; // 274

    //System Menu Dialog(F12)
    m_stDialogBoxInfo[19].sX = 337;
    m_stDialogBoxInfo[19].sY = 107;
    m_stDialogBoxInfo[19].sSizeX = 258;//270; //v2.18
    m_stDialogBoxInfo[19].sSizeY = 268;//346;

    //NpcActionQuery Dialog
    m_stDialogBoxInfo[20].sX = 237;
    m_stDialogBoxInfo[20].sY = 57;
    m_stDialogBoxInfo[20].sSizeX = 252;
    m_stDialogBoxInfo[20].sSizeY = 87;

    //NpcTalk Dialog
    m_stDialogBoxInfo[21].sX = 337;
    m_stDialogBoxInfo[21].sY = 57;
    m_stDialogBoxInfo[21].sSizeX = 258;
    m_stDialogBoxInfo[21].sSizeY = 339;

    //Map
    m_stDialogBoxInfo[22].sX = 336;
    m_stDialogBoxInfo[22].sY = 88;
    m_stDialogBoxInfo[22].sSizeX = 270;
    m_stDialogBoxInfo[22].sSizeY = 346;

    //ItemSellorRepair Dialog
    m_stDialogBoxInfo[23].sX = 337;
    m_stDialogBoxInfo[23].sY = 57;
    m_stDialogBoxInfo[23].sSizeX = 258;
    m_stDialogBoxInfo[23].sSizeY = 339;

    //Fishing Dialog
    m_stDialogBoxInfo[24].sX = 193;
    m_stDialogBoxInfo[24].sY = 241;
    m_stDialogBoxInfo[24].sSizeX = 263;
    m_stDialogBoxInfo[24].sSizeY = 100;

    //Noticement Dialog
    m_stDialogBoxInfo[25].sX = 162;
    m_stDialogBoxInfo[25].sY = 40;
    m_stDialogBoxInfo[25].sSizeX = 315;
    m_stDialogBoxInfo[25].sSizeY = 171;

    //Manufacture Dialog
    m_stDialogBoxInfo[26].sX = 100;
    m_stDialogBoxInfo[26].sY = 60;
    m_stDialogBoxInfo[26].sSizeX = 258;
    m_stDialogBoxInfo[26].sSizeY = 339;

    //Exchange Dialog
    m_stDialogBoxInfo[27].sX = 100;
    m_stDialogBoxInfo[27].sY = 30;
    m_stDialogBoxInfo[27].sSizeX = 520;
    m_stDialogBoxInfo[27].sSizeY = 357;

    //Quest Dialog
    m_stDialogBoxInfo[28].sX = 0;
    m_stDialogBoxInfo[28].sY = 0;
    m_stDialogBoxInfo[28].sSizeX = 258;
    m_stDialogBoxInfo[28].sSizeY = 339;

    //Gauge Panel
    m_stDialogBoxInfo[29].sX = 0;
    m_stDialogBoxInfo[29].sY = 434;
    m_stDialogBoxInfo[29].sSizeX = 157;
    m_stDialogBoxInfo[29].sSizeY = 53;

    //Icon Panel
    m_stDialogBoxInfo[30].sX = 0;
    m_stDialogBoxInfo[30].sY = 427;
    m_stDialogBoxInfo[30].sSizeX = 640;
    m_stDialogBoxInfo[30].sSizeY = 53;//47;

    //Sell List Dialog
    m_stDialogBoxInfo[31].sX = 170;
    m_stDialogBoxInfo[31].sY = 70;
    m_stDialogBoxInfo[31].sSizeX = 258;
    m_stDialogBoxInfo[31].sSizeY = 339;

    //Party Dialog
    m_stDialogBoxInfo[32].sX = 0;
    m_stDialogBoxInfo[32].sY = 0;
    m_stDialogBoxInfo[32].sSizeX = 258;
    m_stDialogBoxInfo[32].sSizeY = 339;

    //Crusade Job Dialog
    m_stDialogBoxInfo[33].sX = 360;
    m_stDialogBoxInfo[33].sY = 65;
    m_stDialogBoxInfo[33].sSizeX = 258;
    m_stDialogBoxInfo[33].sSizeY = 339;

    //Item Upgrade Dialog
    m_stDialogBoxInfo[34].sX = 60;
    m_stDialogBoxInfo[34].sY = 50;
    m_stDialogBoxInfo[34].sSizeX = 258;
    m_stDialogBoxInfo[34].sSizeY = 339;

    //Help Menu Dialog(F1)
    m_stDialogBoxInfo[35].sX = 358;
    m_stDialogBoxInfo[35].sY = 65;
    m_stDialogBoxInfo[35].sSizeX = 258;
    m_stDialogBoxInfo[35].sSizeY = 339;

    //Crusade Commander Dialog
    m_stDialogBoxInfo[36].sX = 20;
    m_stDialogBoxInfo[36].sY = 20;
    m_stDialogBoxInfo[36].sSizeX = 310;
    m_stDialogBoxInfo[36].sSizeY = 386;

    //Crusade Constructor Dialog
    m_stDialogBoxInfo[37].sX = 20;
    m_stDialogBoxInfo[37].sY = 20;
    m_stDialogBoxInfo[37].sSizeX = 310;
    m_stDialogBoxInfo[37].sSizeY = 386;

    //Crusade Soldier Dialog
    m_stDialogBoxInfo[38].sX = 20;
    m_stDialogBoxInfo[38].sY = 20;
    m_stDialogBoxInfo[38].sSizeX = 310;
    m_stDialogBoxInfo[38].sSizeY = 386;

    // Give item ???
    m_stDialogBoxInfo[39].sX = 0;
    m_stDialogBoxInfo[39].sY = 0;
    m_stDialogBoxInfo[39].sSizeX = 291;
    m_stDialogBoxInfo[39].sSizeY = 413;

    // 3.51 Slates Dialog
    m_stDialogBoxInfo[40].sX = 100;
    m_stDialogBoxInfo[40].sY = 60;
    m_stDialogBoxInfo[40].sSizeX = 258;
    m_stDialogBoxInfo[40].sSizeY = 339;

    // Item exchange confirmation
    m_stDialogBoxInfo[41].sX = 285;
    m_stDialogBoxInfo[41].sY = 200;
    m_stDialogBoxInfo[41].sSizeX = 270;
    m_stDialogBoxInfo[41].sSizeY = 105;

    // MJ Stats Change DialogBox
    m_stDialogBoxInfo[42].sX = 0;
    m_stDialogBoxInfo[42].sY = 0;
    m_stDialogBoxInfo[42].sSizeX = 258;
    m_stDialogBoxInfo[42].sSizeY = 339;

    // Resurection
    m_stDialogBoxInfo[50].sX = 185;
    m_stDialogBoxInfo[50].sY = 100;
    m_stDialogBoxInfo[50].sSizeX = 270;
    m_stDialogBoxInfo[50].sSizeY = 105;

    //Guild Hall Menu Dialog
    m_stDialogBoxInfo[51].sX = 337;
    m_stDialogBoxInfo[51].sY = 57;
    m_stDialogBoxInfo[51].sSizeX = 258;
    m_stDialogBoxInfo[51].sSizeY = 339;

    m_bCtrlPressed = false;
    m_bShiftPressed = false;
    //m_bVK_OEM_7Pressed = false;
    m_bEnterPressed = false;
    m_bEscPressed = false;
    m_bSoundFlag = false;
    m_dwDialogCloseTime = 0;
    m_iTimeLeftSecAccount = 0;
    m_iTimeLeftSecIP = 0;
    m_bWhisper = true;
    m_bShout = true;
}

CGame::~CGame()
{
}

bool CGame::bInit()
{
    char seps[] = "&= ,\t\n";

    m_bCommandAvailable = true;
    m_dwTime = G_dwGlobalTime;
    m_bMusicStat = m_bSoundStat = m_bSoundFlag = true;
    m_bIsHideLocalCursor = false;
    m_cEnterCheck = m_cTabCheck = m_cLeftArrowCheck = 0;

    if (_bDecodeBuildItemContents() == false)
    {
        MessageBoxA(m_DDraw.handle, "File checksum error! Get Update again please!", "ERROR2", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    if (bReadItemNameConfigFile() == false)
    {
        MessageBoxA(m_DDraw.handle, "ItemName.cfg file contains wrong infomation.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    if (bInitMagicCfgList() == false)
    {
        MessageBoxA(m_DDraw.handle, "MAGICCFG.TXT file contains wrong infomation.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    // Skill
    if (bInitSkillCfgList() == false)
    {
        MessageBoxA(m_DDraw.handle, "SKILLCFG.TXT file contains wrong infomation.", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    if (m_DDraw.bInit(m_DDraw.fullscreen) == false)
    {
        MessageBoxA(m_DDraw.handle, "This program requires DirectX7.0a!", "ERROR", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    // Load interface sprites first to show sprites during loading
    m_pSprite[DEF_SPRID_MOUSECURSOR] = new CSprite(&m_DDraw, "interface", 0, false);
    m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS] = new CSprite(&m_DDraw, "interface", 1, false);
    m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE] = new CSprite(&m_DDraw, "interface2", 0, false);
    m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2] = new CSprite(&m_DDraw, "interface2", 1, false);
    m_pSprite[DEF_SPRID_INTERFACE_F1HELPWINDOWS] = new CSprite(&m_DDraw, "interface2", 2, false);
    m_pSprite[DEF_SPRID_INTERFACE_CRAFTING] = new CSprite(&m_DDraw, "interface2", 3, false);
    m_pSprite[DEF_SPRID_INTERFACE_FONT1] = new CSprite(&m_DDraw, "sprfonts", 0, false);
    m_pSprite[DEF_SPRID_INTERFACE_FONT2] = new CSprite(&m_DDraw, "sprfonts", 1, false);
    m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN] = new CSprite(&m_DDraw, "LoginDialog", 0, false);
    m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING] = new CSprite(&m_DDraw, "New-Dialog", 0, false);
    m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU] = new CSprite(&m_DDraw, "New-Dialog", 1, false);
    m_pSprite[DEF_SPRID_INTERFACE_ND_QUIT] = new CSprite(&m_DDraw, "New-Dialog", 2, false);

    m_stMCursor.sX = 0;
    m_stMCursor.sY = 0;
    m_pMapData = new class CMapData(this);
    ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
    ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
    ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));

    m_sPlayerType = 2;
    m_cPlayerTurn = 0;

    m_cDialogBoxOrder[60] = 29;
    m_cDialogBoxOrder[59] = 30; // GaugePannel

    m_cMenuDir = 4;
    m_cMenuDirCnt = 0;
    m_cMenuFrame = 0;

    m_cSoundVolume = 100;
    m_cMusicVolume = 100;

#ifdef DEF_EQUILIBRIUM_PROJECT
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(80, 70, 70), &m_wWR[1], &m_wWG[1], &m_wWB[1]); // Light-blue Special agile
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(70, 70, 80), &m_wWR[2], &m_wWG[2], &m_wWB[2]); // light-blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(70, 70, 80), &m_wWR[3], &m_wWG[3], &m_wWB[3]); // light-blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(70, 100, 70), &m_wWR[4], &m_wWG[4], &m_wWB[4]); // Green
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(130, 90, 10), &m_wWR[5], &m_wWG[5], &m_wWB[5]); // Critical
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(42, 53, 111), &m_wWR[6], &m_wWG[6], &m_wWB[6]); // Heavy-blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(145, 145, 145), &m_wWR[7], &m_wWG[7], &m_wWB[7]); // White
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(120, 100, 120), &m_wWR[8], &m_wWG[8], &m_wWB[8]); // Violet
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(75, 10, 10), &m_wWR[9], &m_wWG[9], &m_wWB[9]); // Heavy-Red
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0, 0, 0), &m_wWR[10], &m_wWG[10], &m_wWB[10]); // Noir 
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0, 0, 30), &m_wWR[11], &m_wWG[11], &m_wWB[11]); // Knight (noir bleuté)
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0, 0, 0), &m_wWR[12], &m_wWG[12], &m_wWB[12]); // Noir  <-> rouge (StormBringer)
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(145, 145, 145), &m_wWR[13], &m_wWG[13], &m_wWB[13]); // Blanc <-> Jaune
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(70, 70, 70), &m_wWR[14], &m_wWG[14], &m_wWB[14]); // Bleu  <-> rouge
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(135, 104, 30), &m_wWR[15], &m_wWG[15], &m_wWB[15]); // Golden special weapon


    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(200 / 2, 200 / 2, 200 / 2), &m_wR[0], &m_wG[0], &m_wB[0]);
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0x50 / 2, 0x50 / 2, 0xC0 / 2), &m_wR[1], &m_wG[1], &m_wB[1]); // Indigo Blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(79, 79, 62), &m_wR[2], &m_wG[2], &m_wB[2]); // Custom-Weapon Color
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(135, 104, 30), &m_wR[3], &m_wG[3], &m_wB[3]); // Gold
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(255 / 2, 36 / 2, 0), &m_wR[4], &m_wG[4], &m_wB[4]); // Crimson
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(10, 60, 10), &m_wR[5], &m_wG[5], &m_wB[5]); // Green
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0x50 / 2, 0x50 / 2, 0x50 / 2), &m_wR[6], &m_wG[6], &m_wB[6]); // Gray
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0x5F / 2, 0x9E / 2, 0xA0 / 2), &m_wR[7], &m_wG[7], &m_wB[7]); // Aqua
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0xFF / 2, 0x69 / 2, 0xB4 / 2), &m_wR[8], &m_wG[8], &m_wB[8]); // Pink
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(90, 60, 90), &m_wR[9], &m_wG[9], &m_wB[9]); // Violet

    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0, 35, 60), &m_wR[10], &m_wG[10], &m_wB[10]); // Blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0xD2 / 2, 0xB4 / 2, 0x8C / 2), &m_wR[11], &m_wG[11], &m_wB[11]); // Tan
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0xBD / 2, 0xB7 / 2, 0x6B / 2), &m_wR[12], &m_wG[12], &m_wB[12]); // Khaki
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(85, 85, 8), &m_wR[13], &m_wG[13], &m_wB[13]); // Yellow
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(75, 8, 8), &m_wR[14], &m_wG[14], &m_wB[14]); // Red
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(8, 8, 8), &m_wR[15], &m_wG[15], &m_wB[15]); // Black

#else
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(70, 70, 80), &m_wWR[1], &m_wWG[1], &m_wWB[1]); // Light-blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(70, 70, 80), &m_wWR[2], &m_wWG[2], &m_wWB[2]); // light-blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(70, 70, 80), &m_wWR[3], &m_wWG[3], &m_wWB[3]); // light-blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(70, 100, 70), &m_wWR[4], &m_wWG[4], &m_wWB[4]); // Green
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(130, 90, 10), &m_wWR[5], &m_wWG[5], &m_wWB[5]); // Critical
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(42, 53, 111), &m_wWR[6], &m_wWG[6], &m_wWB[6]); // Heavy-blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(145, 145, 145), &m_wWR[7], &m_wWG[7], &m_wWB[7]); // White
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(120, 100, 120), &m_wWR[8], &m_wWG[8], &m_wWB[8]); // Violet
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(75, 10, 10), &m_wWR[9], &m_wWG[9], &m_wWB[9]); // Heavy-Red
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(135, 104, 30), &m_wR[10], &m_wG[10], &m_wB[10]);	// Gold, buggy

    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(200 / 2, 200 / 2, 200 / 2), &m_wR[0], &m_wG[0], &m_wB[0]);
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0x50 / 2, 0x50 / 2, 0xC0 / 2), &m_wR[1], &m_wG[1], &m_wB[1]); // Indigo Blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(79, 79, 62), &m_wR[2], &m_wG[2], &m_wB[2]); // Custom-Weapon Color
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(135, 104, 30), &m_wR[3], &m_wG[3], &m_wB[3]); // Gold
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(255 / 2, 36 / 2, 0), &m_wR[4], &m_wG[4], &m_wB[4]); // Crimson
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(10, 60, 10), &m_wR[5], &m_wG[5], &m_wB[5]); // Green
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0x50 / 2, 0x50 / 2, 0x50 / 2), &m_wR[6], &m_wG[6], &m_wB[6]); // Gray
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0x5F / 2, 0x9E / 2, 0xA0 / 2), &m_wR[7], &m_wG[7], &m_wB[7]); // Aqua
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0xFF / 2, 0x69 / 2, 0xB4 / 2), &m_wR[8], &m_wG[8], &m_wB[8]); // Pink
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(90, 60, 90), &m_wR[9], &m_wG[9], &m_wB[9]); // Violet

    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0, 35, 60), &m_wR[10], &m_wG[10], &m_wB[10]); // Blue
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0xD2 / 2, 0xB4 / 2, 0x8C / 2), &m_wR[11], &m_wG[11], &m_wB[11]); // Tan
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0xBD / 2, 0xB7 / 2, 0x6B / 2), &m_wR[12], &m_wG[12], &m_wB[12]); // Khaki
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(85, 85, 8), &m_wR[13], &m_wG[13], &m_wB[13]); // Yellow
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(75, 10, 10), &m_wR[14], &m_wG[14], &m_wB[14]); // Red
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0x30, 0x30, 0x30), &m_wR[15], &m_wG[15], &m_wB[15]); // Black

#endif

    _LoadGameMsgTextContents();
    ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));

    return true;
}

void CGame::OnEvent(sf::Event event)
{
    //TODO: fix

    if (m_bInputStatus && event.type == sf::Event::TextEntered)
    {
        //rethink this
//         if (
//             event.key.code != Keyboard::Backspace
//             && event.key.code != Keyboard::Enter
//             && event.key.code != Keyboard::Escape
//             && event.key.code != Keyboard::Tab
// //             && event.key.code != Keyboard::LShift
// //             && event.key.code != Keyboard::RShift
// //             && event.key.code != Keyboard::LSystem
// //             && event.key.code != Keyboard::RSystem
// //             && event.key.code != Keyboard::Menu
// //             && event.key.code != Keyboard::LControl
// //             && event.key.code != Keyboard::RControl
// //             && event.key.code != Keyboard::LAlt
// //             && event.key.code != Keyboard::RAlt
//             )
        if (event.text.unicode == 8)
        {

        }
        else if (
            event.text.unicode != 9
            && event.text.unicode != 4
            && event.text.unicode != 13
            && event.text.unicode != 27
            )
        {
            std::string s{ (char)(((int32_t)event.text.unicode) & 0xff) };

            int len = strlen(m_pInputBuffer);
            if (len >= m_inputMaxLen - 1) return;
            m_pInputBuffer[len] = s[0];
            m_pInputBuffer[len + 1] = 0;
            return;
        }
    }

    switch (event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
                case Keyboard::Backspace:
                    if (m_pInputBuffer)
                        if (int len = strlen(m_pInputBuffer))
                            m_pInputBuffer[len - 1] = 0;
                    break;
                case Keyboard::Add:
                    m_pMapData->m_sPivotX++;
                    //zoom *= 1.05;
//                     m_sViewPointX *= 1.05;
//                     m_sViewPointY *= 1.05;
                    break;
                case Keyboard::Subtract:
                    m_pMapData->m_sPivotX--;
                    //zoom /= 1.05;
//                     m_sViewPointX /= 1.05;
//                     m_sViewPointY /= 1.05;
                    break;
                case Keyboard::Left:
                    m_cArrowPressed = 1;
                    //m_pMapData->ShiftMapData(7);
                    break;
                case Keyboard::Right:
                    m_cArrowPressed = 3;
                    //m_pMapData->ShiftMapData(3);
                    break;
                case Keyboard::Up:
                    m_sPlayerX++;
                    m_cArrowPressed = 2;
                    break;
                case Keyboard::Down:
                    m_sPlayerX--;
                    m_cArrowPressed = 4;
                    break;

                case Keyboard::F5:
                    RequestFullObjectData(owner_type::ot_player, m_sPlayerObjectID);
                    break;
                case Keyboard::F7:
                    RequestFullObjectData(owner_type::ot_player, m_sPlayerObjectID - 30000);
                    break;
                case Keyboard::Escape:
                    m_DDraw.clipmousegame = !m_DDraw.clipmousegame;
                    m_DDraw.window.setMouseCursorGrabbed(m_DDraw.clipmousegame);
                    m_bEscPressed = true;
                    break;
                case Keyboard::LShift:
                    m_bShiftPressed = true;
                    break;
                case Keyboard::LControl:
                    m_bCtrlPressed = true;
                    break;
                case Keyboard::LAlt:
                    m_altPressed = true;
                    break;
                case Keyboard::Tab:
                    if (m_bShiftPressed)
                    {
                        m_cCurFocus--;
                        if (m_cCurFocus < 1) m_cCurFocus = m_cMaxFocus;
                    }
                    else
                    {
                        m_cCurFocus++;
                        if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                    }
                    if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
                    {
                        bSendCommand((uint32_t)message_id::COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, 0, 0, 0, 0, 0);
                    }
                    break;
                case Keyboard::Return:
                    if (event.key.alt)
                    {
                        m_DDraw.ChangeDisplayMode();
                    }
                    else
                    {
                        m_bEnterPressed = true;
                    }
                    break;
                case Keyboard::F12:
                    m_DDraw.CreateScreenShot();
                    break;

                case Keyboard::F6:
                    //                     calcoldviewport = !calcoldviewport;
                    //                     if (!calcoldviewport)
                    //                     {
                    //                         AddEventList("Switched to new viewport code.");
                    //                     }
                    //                     else
                    //                     {
                    //                         AddEventList("Switched to old viewport code.");
                    //                     }
                    break;
            }
            break;
        }
        case sf::Event::KeyReleased:
        {
            if (event.key.code == Keyboard::Backspace)
            {
            }
            if (event.key.code == Keyboard::Tab)
            {
            }

            switch (event.key.code)
            {
                case Keyboard::Escape:
                    break;
                case Keyboard::LShift:
                    m_bShiftPressed = false;
                    break;
                case Keyboard::LControl:
                    m_bCtrlPressed = false;
                    break;
                case Keyboard::LAlt:
                    m_altPressed = false;
                    break;
                case Keyboard::Tab:
                    break;
                case Keyboard::Return:
                    break;
                case Keyboard::F12:
                    break;
                case Keyboard::F5:
                    break;
            }
            break;
        }
        case sf::Event::Resized:
            break;
        case sf::Event::LostFocus:
            m_DDraw.window.setFramerateLimit(m_DDraw.frame_limit_bg); //set to var
            break;
        case sf::Event::GainedFocus:
            if (m_cGameMode != DEF_GAMEMODE_ONLOADING)
                m_DDraw.window.setFramerateLimit(m_DDraw.frame_limit);
            else
                m_DDraw.window.setFramerateLimit(0);
            break;
        case sf::Event::MouseWheelScrolled:
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta > 0.f)
                {
                    //zoom *= 1.05;
                }
                else if (event.mouseWheelScroll.delta < 0.f)
                {
                    //zoom /= 1.05;
                }
            }
            else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
            {
            }
            else
            {
            }
            break;
        case sf::Event::MouseButtonPressed:
        {
            if (m_DDraw.wasinactive)
            {
                m_DDraw.wasinactive = false;
            }

            //             for (auto & rect : dialogs)
            //             {
            //                 if (rect.contains(m_stMCursor.sX, m_stMCursor.sY))
            //                 {
            //                     break;
            //                 }
            //             }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                m_stMCursor.RB = true;
            }
            else if (event.mouseButton.button == sf::Mouse::Left)
            {
                m_stMCursor.LB = true;
            }
            else if (event.mouseButton.button == sf::Mouse::Middle)
            {
                m_stMCursor.MB = true;
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                m_stMCursor.RB = false;
            }
            else if (event.mouseButton.button == sf::Mouse::Left)
            {
                m_stMCursor.LB = false;
            }
            else if (event.mouseButton.button == sf::Mouse::Middle)
            {
                m_stMCursor.MB = false;
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            float diffx = static_cast<float>(m_DDraw.screenwidth_v) / m_DDraw.screenwidth;
            float diffy = static_cast<float>(m_DDraw.screenheight_v) / m_DDraw.screenheight;
            uint16_t x = uint16_t(event.mouseMove.x * diffx);
            uint16_t y = uint16_t(event.mouseMove.y * diffy);

            // if admin client
            if (m_stMCursor.LB && m_bCtrlPressed)
            {
                // pan event
                //pan_x += event.mouseMove.x - m_stMCursor.sX;
                //pan_y += event.mouseMove.y - m_stMCursor.sY;
            }

            m_stMCursor.sX = x;
            m_stMCursor.sY = y;

            //std::cout << fmt::format("{:#4}, {:#4} || {:#4}, {:#4}\n", event.mouseMove.x, event.mouseMove.y, x, y);
            break;
        }
    }
}

void CGame::Quit()
{
    int i;
    ChangeGameMode(DEF_GAMEMODE_0);

    for (i = 0; i < DEF_MAXSPRITES; i++)
        if (m_pSprite[i] != 0) delete m_pSprite[i];
    for (i = 0; i < DEF_MAXTILES; i++)
        if (m_pTileSpr[i] != 0) delete m_pTileSpr[i];
    for (i = 0; i < DEF_MAXEFFECTSPR; i++)
        if (m_pEffectSpr[i] != 0) delete m_pEffectSpr[i];

    for (i = 0; i < 4; i++)
        if (m_pCharList[i] != 0) delete m_pCharList[i];

    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_pItemList[i] != 0)	delete m_pItemList[i];

    for (i = 0; i < DEF_MAXBANKITEMS; i++)
        if (m_pBankList[i] != 0)	delete m_pBankList[i];

    for (i = 0; i < DEF_MAXEFFECTS; i++)
        if (m_pEffectList[i] != 0) delete m_pEffectList[i];

    for (i = 0; i < DEF_MAXCHATMSGS; i++)
        if (m_pChatMsgList[i] != 0) delete m_pChatMsgList[i];

    for (i = 0; i < DEF_MAXCHATSCROLLMSGS; i++)
        if (m_pChatScrollList[i] != 0) delete m_pChatScrollList[i];

    for (i = 0; i < DEF_MAXWHISPERMSG; i++)
        if (m_pWhisperMsg[i] != 0) delete m_pWhisperMsg[i];

    for (i = 0; i < DEF_MAXMENUITEMS; i++)
        if (m_pItemForSaleList[i] != 0) delete m_pItemForSaleList[i];

    for (i = 0; i < DEF_MAXMAGICTYPE; i++)
        if (m_pMagicCfgList[i] != 0) delete m_pMagicCfgList[i];

    for (i = 0; i < DEF_MAXSKILLTYPE; i++)
        if (m_pSkillCfgList[i] != 0) delete m_pSkillCfgList[i];

    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        if (m_pMsgTextList[i] != 0)  delete m_pMsgTextList[i];
        if (m_pMsgTextList2[i] != 0) delete m_pMsgTextList2[i];
        if (m_pAgreeMsgTextList[i] != 0) delete m_pAgreeMsgTextList[i];
    }

    if (m_pExID != 0) delete m_pExID;

    for (i = 0; i < DEF_MAXBUILDITEMS; i++)
        if (m_pBuildItemList[i] != 0) delete m_pBuildItemList[i];

    for (i = 0; i < DEF_MAXBUILDITEMS; i++)
        if (m_pDispBuildItemList[i] != 0) delete m_pDispBuildItemList[i];

    // Crafting:
    for (i = 0; i < DEF_MAXBUILDITEMS; i++)
        if (m_pCraftItemList[i] != 0) delete m_pCraftItemList[i];
    for (i = 0; i < DEF_MAXBUILDITEMS; i++)
        if (m_pDispCraftItemList[i] != 0) delete m_pDispCraftItemList[i];


    for (i = 0; i < DEF_MAXGAMEMSGS; i++)
        if (m_pGameMsgList[i] != 0) delete m_pGameMsgList[i];

    for (i = 0; i < DEF_MAXITEMNAMES; i++)
        if (m_pItemNameList[i] != 0) delete m_pItemNameList[i];

    delete m_pMapData;
}

void CGame::CalcViewPoint()
{
    short dX, dY;
    dX = m_sViewPointX - m_sViewDstX;
    dY = m_sViewPointY - m_sViewDstY;
    if (abs(dX) < abs(m_sViewDX))
    {
        m_sViewPointX = m_sViewDstX;
        m_sViewDX = 0;
    }
    else
    {
        if (dX > 0) m_sViewDX--;
        if (dX < 0) m_sViewDX++;
        if (dX == 0) m_sViewDX = 0;
        if (abs(dX) < 40)
        {
            if (m_sViewDX > 4)  m_sViewDX = 4;
            else if (m_sViewDX < -4) m_sViewDX = -4;
        }
        m_sViewPointX += m_sViewDX;
    }

    if (abs(dY) < abs(m_sViewDY))
    {
        m_sViewPointY = m_sViewDstY;
        m_sViewDY = 0;
    }
    else
    {
        if (dY > 0) m_sViewDY--;
        if (dY < 0) m_sViewDY++;
        if (dY == 0) m_sViewDY = 0;
        if (abs(dY) < 40)
        {
            if (m_sViewDY > 4)  m_sViewDY = 4;
            else if (m_sViewDY < -4) m_sViewDY = -4;
        }
        m_sViewPointY += m_sViewDY;
    }
}

char _tmp_cTmpDirX[9] = { 0,0,1,1,1,0,-1,-1,-1 };
char _tmp_cTmpDirY[9] = { 0,-1,-1,0,1,1,1,0,-1 };
char CGame::cGetNextMoveDir(short sX, short sY, short dstX, short dstY, bool bMoveCheck, bool bMIM)
{
    char  cDir, cTmpDir;
    //int   aX, aY, aX2, aY2, dX, dY;
    int   aX, aY, dX, dY;
    int   i;
    if ((sX == dstX) && (sY == dstY)) return 0;
    dX = sX;
    dY = sY;
    if (bMIM == false) // MIM Fix
        cDir = m_Misc.cGetNextMoveDir(dX, dY, dstX, dstY);
    else cDir = m_Misc.cGetNextMoveDir(dstX, dstY, dX, dY);

    if (m_cPlayerTurn == 0)
        for (i = cDir; i <= cDir + 2; i++)
        {
            cTmpDir = i;
            if (cTmpDir > 8) cTmpDir -= 8;
            aX = _tmp_cTmpDirX[cTmpDir];
            aY = _tmp_cTmpDirY[cTmpDir];
            if (((dX + aX) == m_iPrevMoveX) && ((dY + aY) == m_iPrevMoveY) && (m_bIsPrevMoveBlocked == true) && (bMoveCheck == true))
            {
                m_bIsPrevMoveBlocked = false;
            }
            else if (m_pMapData->bGetIsLocateable(dX + aX, dY + aY) == true)
            {
                if (m_pMapData->bIsTeleportLoc(dX + aX, dY + aY) == true)
                {
                    if (_bCheckMoveable(dX + aX, dY + aY) == true) return cTmpDir;
                    else
                    {
                        SetTopMsg(DEF_MSG_GETNEXTMOVEDIR, 5);
                    }
                }
                else return cTmpDir;
            }
        }

    if (m_cPlayerTurn == 1)
        for (i = cDir; i >= cDir - 2; i--)
        {
            cTmpDir = i;
            if (cTmpDir < 1) cTmpDir += 8;
            aX = _tmp_cTmpDirX[cTmpDir];
            aY = _tmp_cTmpDirY[cTmpDir];
            if (((dX + aX) == m_iPrevMoveX) && ((dY + aY) == m_iPrevMoveY) && (m_bIsPrevMoveBlocked == true) && (bMoveCheck == true))
            {
                m_bIsPrevMoveBlocked = false;
            }
            else if (m_pMapData->bGetIsLocateable(dX + aX, dY + aY) == true)
            {
                if (m_pMapData->bIsTeleportLoc(dX + aX, dY + aY) == true)
                {
                    if (_bCheckMoveable(dX + aX, dY + aY) == true) return cTmpDir;
                    else
                    {
                        SetTopMsg(DEF_MSG_GETNEXTMOVEDIR, 5);
                    }
                }
                else return cTmpDir;
            }
        }
    return 0;
}

bool CGame::_bCheckMoveable(short sx, short sy)
{	// This function prevents the client from asking at TP from some maps to
    // ML or PL if not citizen
    // Incomplete function and useless (the server will handle such cases)
/*	if( m_bIsCrusadeMode ) return true;
    if( m_bHunter == false ) return true;
    if( m_bCitizen == false ) return true;
    if( m_bAresden == true && m_cMapIndex == 11 )
    {	if( sy == 20 )
        {	if( (sx>=39) && (sx<=47) ) return false;
            if( (sx>=360) && (sx<=368) ) return false;
        }
    }
    if( m_bAresden == false && m_cMapIndex == 3 )
    {
        if( sy == 373 )
        {	if( (sx>=27) && (sx<=32) ) return false;
        }
        if( sy == 374 )
        {	if( (sx>=298) && (sx<=305) ) return false;
        }
    }*/
    return true;
}

bool CGame::bSendCommand(uint32_t dwMsgID, uint16_t wCommand, char cDir, int iV1, int iV2, int iV3, const char * pString, int iV4)
{
    char * cp, cMsg[300] = {}, cTxt[256] = {}, cKey;
    uint16_t * wp;
    uint32_t * dwp;
    uint64_t dwTime;
    short * sp;
    int * ip, iRet, i, * fightzonenum;

    if ((!ws) && (!log_ws)) return false;
    dwTime = unixtime();
    ZeroMemory(cMsg, sizeof(cMsg));

#ifdef DEF_ANTI_HACK
    cKey = (char)(rand() % 245) + 1;
#else
    cKey = (char)(rand() % 255) + 1;
#endif

    switch (dwMsgID)
    {

        case MSGID_REQUEST_ANGEL:	// to Game Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            cp = (char *)(cMsg + 6);
            memset(cp, 0, 20);
            memcpy((char *)cp, pString, strlen(pString) + 1);
            cp += 20;
            ip = (int *)cp;
            *ip = iV1; // Angel ID
            iRet = write(cMsg, 30);
            break;

        case MSGID_REQUEST_RESURRECTPLAYER_YES:
        case MSGID_REQUEST_RESURRECTPLAYER_NO:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            iRet = write(cMsg, 6);
            break;

        case MSGID_REQUEST_HELDENIAN_SCROLL:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            cp = (char *)(cMsg + 6);
            memset(cp, 0, 20);
            memcpy((char *)cp, pString, strlen(pString) + 1);
            cp += 20;
            wp = (uint16_t *)cp;
            *wp = wCommand; // Item ID
            iRet = write(cMsg, 28);
            break;

        case MSGID_REQUEST_TELEPORT_LIST:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            cp = (char *)(cMsg + 6);
            memset(cp, 0, 20);
            memcpy(cp, "William", 20);
            iRet = write(cMsg, 26);
            break;

        case MSGID_REQUEST_HELDENIAN_TP_LIST: // Heldenian TP
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            cp = (char *)(cMsg + 6);
            memset(cp, 0, 20);
            memcpy(cp, "Gail", 20);
            iRet = write(cMsg, 26);
            break;

        case MSGID_REQUEST_HELDENIAN_TP: // Heldenian TP
        case MSGID_REQUEST_CHARGED_TELEPORT:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            ip = (int *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            *ip = iV1;
            iRet = write(cMsg, 10);
            break;

        case MSGID_REQUEST_SELLITEMLIST:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            for (i = 0; i < DEF_MAXSELLLIST; i++)
            {
                *cp = m_stSellItemList[i].iIndex;
                cp++;
                ip = (int *)cp;
                *ip = m_stSellItemList[i].iAmount;
                cp += 4;
            }

            iRet = write(cMsg, 70);
            break;

        case MSGID_REQUEST_RESTART:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            iRet = write(cMsg, 6);
            break;

        case MSGID_REQUEST_PANNING:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            *cp = cDir;
            cp++;

            iRet = write(cMsg, 7);
            break;

        case MSGID_REQUEST_CHANGEPASSWORD:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cAccountName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cAccountPassword, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cNewPassword, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cNewPassConfirm, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            iRet = log_write(cMsg, 46);
            break;

        case MSGID_REQUEST_CREATENEWACCOUNT:
            // to MainLog Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, m_cAccountName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, m_cAccountPassword, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            memcpy(cp, m_cEmailAddr, 50);
            cp += 50;

            ZeroMemory(cTxt, sizeof(cTxt));
            strcpy(cTxt, " "); // gender
            memcpy(cp, cTxt, 10);
            cp += 10;

            memcpy(cp, m_cAccountAge, 10);
            cp += 10;

            memcpy(cp, " ", 4);
            cp += 4;

            memcpy(cp, " ", 2);
            cp += 2;

            memcpy(cp, " ", 2);
            cp += 2;

            memcpy(cp, m_cAccountCountry, 17);
            cp += 17;

            memcpy(cp, m_cAccountSSN, 28);
            cp += 28;

            memcpy(cp, m_cAccountQuiz, 45);
            cp += 45;

            memcpy(cp, m_cAccountAnswer, 20);
            cp += 20;

            iRet = log_write(cMsg, 214);
            break;

        case MSGID_GETMINIMUMLOADGATEWAY:
        case MSGID_REQUEST_LOGIN:
            // to MainLog Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cAccountName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;
            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cAccountPassword, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;
            memcpy(cp, m_cWorldServerName, 30);
            cp += 30;
            iRet = log_write(cMsg, 56);

            break;

        case MSGID_REQUEST_CREATENEWCHARACTER:
            // to MainLog Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = (uint16_t)0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            memcpy(cp, m_cPlayerName, 10);
            cp += 10;

            memcpy(cp, m_cAccountName, 10);
            cp += 10;

            memcpy(cp, m_cAccountPassword, 10);
            cp += 10;

            memcpy(cp, m_cWorldServerName, 30);
            cp += 30;

            *cp = m_cGender;
            cp++;

            *cp = m_cSkinCol;
            cp++;

            *cp = m_cHairStyle;
            cp++;

            *cp = m_cHairCol;
            cp++;

            *cp = m_cUnderCol;
            cp++;

            *cp = m_ccStr;
            cp++;

            *cp = m_ccVit;
            cp++;

            *cp = m_ccDex;
            cp++;

            *cp = m_ccInt;
            cp++;

            *cp = m_ccMag;
            cp++;

            *cp = m_ccChr;
            cp++;

            iRet = log_write(cMsg, 77);
            break;

        case MSGID_REQUEST_ENTERGAME:
            // to MainLog Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = (uint16_t)m_wEnterGameType;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cPlayerName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.43
            memcpy(cTxt, m_cMapName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cAccountName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cAccountPassword, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ip = (int *)cp;
            *ip = m_iLevel;
            cp += 4;

            memcpy(cp, m_cWorldServerName, 30);
            cp += 30;

            iRet = log_write(cMsg, 80);
            break;

        case MSGID_REQUEST_DELETECHARACTER:
            // to MainLog Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = (uint16_t)m_wEnterGameType;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            memcpy(cp, m_pCharList[m_wEnterGameType - 1]->m_cName, 10);
            cp += 10;

            memcpy(cp, m_cAccountName, 10);
            cp += 10;

            memcpy(cp, m_cAccountPassword, 10);
            cp += 10;

            memcpy(cp, m_cWorldServerName, 30);
            cp += 30;

            iRet = log_write(cMsg, 66);
            break;

        case MSGID_REQUEST_SETITEMPOS:
            // to Game Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            *cp = cDir;

            cp++;

            sp = (short *)cp;
            *sp = (short)iV1;
            cp += 2;

            sp = (short *)cp;
            *sp = (short)iV2;
            cp += 2;

            iRet = write(cMsg, 11);
            break;

        case MSGID_COMMAND_CHECKCONNECTION:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);

#ifdef DEF_ANTI_HACK
            // Envoyer le CRC au serveur...
            if (m_bUseCRC_2 == true)
            {
                m_bUseCRC_2 = false;
                *wp = m_wCRC16_2;
                //wsprintfA(G_cTxt,"CRC envoyé: %#04X", m_wCRC16_1);
            }
            else
            {
                m_bUseCRC_2 = true;
                *wp = m_wCRC16_1;
                //wsprintfA(G_cTxt,"CRC envoyé: %#04X", m_wCRC16_2);
            }
#else
            * wp = 0;
#endif

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            dwp = (uint32_t *)cp;

#ifdef DEF_ANTI_HACK
            * dwp = (uint32_t)iV1;
#else
            * dwp = dwTime;
#endif

            cp += 4;
            iRet = write(cMsg, 10);

            break;

        case MSGID_REQUEST_INITDATA:
        case MSGID_REQUEST_INITPLAYER:
            // to Game Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, m_cPlayerName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, m_cAccountName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, m_cAccountPassword, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            *cp = (char)m_bIsObserverMode;
            cp++;

            // v2.04 Gateway
            memcpy(cp, m_cGameServerName, 20);
            cp += 20;

            iRet = write(cMsg, 37 + 21);

            //m_bIsObserverMode = false;
            break;
        case MSGID_LEVELUPSETTINGS:
            //if ((m_cLU_Str + m_cLU_Vit + m_cLU_Dex + m_cLU_Int + m_cLU_Mag + m_cLU_Char) > 3) return false;

            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            *cp = m_cLU_Str;
            cp++;

            *cp = m_cLU_Vit;
            cp++;

            *cp = m_cLU_Dex;
            cp++;

            *cp = m_cLU_Int;
            cp++;

            *cp = m_cLU_Mag;
            cp++;

            *cp = m_cLU_Char;
            cp++;

            iRet = write(cMsg, 12);
            break;

        case MSGID_COMMAND_CHATMSG:
            if (m_bIsTeleportRequested == true) return false;

            // to Game Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            sp = (short *)cp;
            *sp = m_sPlayerX;
            cp += 2;

            sp = (short *)cp;
            *sp = m_sPlayerY;
            cp += 2;

            memcpy(cp, m_cPlayerName, 10);
            cp += 10;

            *cp = (char)iV1;
            cp++;

            if (bCheckLocalChatCommand(pString) == true) return false;
            memcpy((char *)cp, pString, strlen(pString) + 1);

            iRet = write(cMsg, 22 + strlen(pString));
            break;

        case MSGID_COMMAND_COMMON:
            if (m_bIsTeleportRequested == true) return false;
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = wCommand;
            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            sp = (short *)cp;
            *sp = m_sPlayerX;
            cp += 2;
            sp = (short *)cp;
            *sp = m_sPlayerY;
            cp += 2;
            *cp = cDir;
            cp++;
            switch (wCommand)
            {
                case DEF_COMMONTYPE_BUILDITEM:
                    memcpy(cp, pString, 20);
                    cp += 20;
                    *cp = (char)m_stDialogBoxInfo[26].sV1;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV2;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV3;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV4;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV5;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV6;
                    cp++;
                    iRet = write(cMsg, 37);
                    break;

                case DEF_COMMONTYPE_REQ_CREATEPORTION:
                    *cp = (char)m_stDialogBoxInfo[26].sV1;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV2;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV3;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV4;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV5;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV6;
                    cp++;
                    iRet = write(cMsg, 18);
                    break;

                    //Crafting
                case DEF_COMMONTYPE_CRAFTITEM:
                    memcpy(cp, "                    ", 20);
                    cp += 20;
                    *cp = (char)m_stDialogBoxInfo[26].sV1;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV2;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV3;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV4;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV5;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[26].sV6;
                    cp++;
                    iRet = write(cMsg, 37);
                    break;

                    // Create Slate Request
                case DEF_COMMONTYPE_REQ_CREATESLATE:
                    *cp = (char)m_stDialogBoxInfo[40].sV1;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[40].sV2;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[40].sV3;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[40].sV4;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[40].sV5;
                    cp++;
                    *cp = (char)m_stDialogBoxInfo[40].sV6;
                    cp++;
                    iRet = write(cMsg, 18);
                    break;

                default:
                    if (pString == 0)
                    {
                        ip = (int *)cp;
                        *ip = iV1;
                        cp += 4;
                        ip = (int *)cp;
                        *ip = iV2;
                        cp += 4;
                        ip = (int *)cp;
                        *ip = iV3;
                        cp += 4;
                        dwp = (uint32_t *)cp;
                        *dwp = dwTime;
                        cp += 4;
                        iRet = write(cMsg, 23 + 4);
                    }
                    else
                    {
                        ip = (int *)cp;
                        *ip = iV1;
                        cp += 4;
                        ip = (int *)cp;
                        *ip = iV2;
                        cp += 4;
                        ip = (int *)cp;
                        *ip = iV3;
                        cp += 4;
                        memcpy(cp, pString, 30);
                        cp += 30;
                        ip = (int *)cp;
                        *ip = iV4;
                        cp += 4;
                        iRet = write(cMsg, 23 + 34);
                    }
                    break;
            }

            break;

        case MSGID_REQUEST_CREATENEWGUILD:
        case MSGID_REQUEST_DISBANDGUILD:
        {
            // to Game Server
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = DEF_MSGTYPE_CONFIRM;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cPlayerName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cAccountName, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;

            ZeroMemory(cTxt, sizeof(cTxt)); // v1.4
            memcpy(cTxt, m_cAccountPassword, 10);
            memcpy(cp, cTxt, 10);
            cp += 10;
            char cTemp[21] = {};
            ZeroMemory(cTemp, sizeof(cTemp));
            memcpy(cTemp, m_cGuildName, 20);
            m_Misc.ReplaceString(cTemp, ' ', '_');
            memcpy(cp, cTemp, 20);
            cp += 20;

            iRet = write(cMsg, 56);
            break;
        }

        case MSGID_REQUEST_TELEPORT:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = DEF_MSGTYPE_CONFIRM;

            iRet = write(cMsg, 6);

            m_bIsTeleportRequested = true;
            break;

        case MSGID_REQUEST_CIVILRIGHT:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = DEF_MSGTYPE_CONFIRM;

            iRet = write(cMsg, 6);
            break;

        case MSGID_REQUEST_RETRIEVEITEM:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = DEF_MSGTYPE_CONFIRM;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            *cp = (char)iV1;

            iRet = write(cMsg, 7);
            break;

        case MSGID_REQUEST_NOTICEMENT:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            *ip = iV1;
            cp += 4;

            iRet = write(cMsg, 10);
            break;

        case  MSGID_REQUEST_FIGHTZONE_RESERVE:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            fightzonenum = (int *)cp;
            *fightzonenum = iV1;
            cp += 4;

            iRet = write(cMsg, 10);
            break;

        case MSGID_STATECHANGEPOINT:
            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = 0;
            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);
            *cp = cStateChange1;
            cp++;
            *cp = cStateChange2;
            cp++;
            *cp = cStateChange3;
            cp++;
            iRet = write(cMsg, 12);
            break;

        default:
            if (m_bIsTeleportRequested == true) return false;

            dwp = (uint32_t *)(cMsg + DEF_INDEX4_MSGID);
            *dwp = dwMsgID;
            wp = (uint16_t *)(cMsg + DEF_INDEX2_MSGTYPE);
            *wp = wCommand;

            cp = (char *)(cMsg + DEF_INDEX2_MSGTYPE + 2);

            sp = (short *)cp;
            *sp = m_sPlayerX;
            cp += 2;

            sp = (short *)cp;
            *sp = m_sPlayerY;
            cp += 2;

            *cp = cDir;
            cp++;

            sp = (short *)cp;
            *sp = (short)iV1;
            cp += 2;

            sp = (short *)cp;
            *sp = (short)iV2;
            cp += 2;

            sp = (short *)cp;
            *sp = (short)iV3;
            cp += 2;
            if ((wCommand == DEF_OBJECTATTACK) || (wCommand == DEF_OBJECTATTACKMOVE))
            {
                sp = (short *)cp;
                *sp = (short)iV4;
                cp += 2;
                dwp = (uint32_t *)cp;
                *dwp = dwTime;
                cp += 4;
                iRet = write(cMsg, 19 + 4);
            }
            else
            {
                dwp = (uint32_t *)cp;
                *dwp = dwTime;
                cp += 4;

                iRet = write(cMsg, 17 + 4); //v2.171
            }
            m_cCommandCount++;
            break;
    }
    return true;
}



void CGame::GameRecvMsgHandler(uint32_t dwMsgSize, char * pData)
{
    uint32_t * dwpMsgID;
    dwpMsgID = (uint32_t *)(pData + DEF_INDEX4_MSGID);
    switch (*dwpMsgID)
    {
        case MSGID_RESPONSE_CHARGED_TELEPORT:
            ResponseChargedTeleport(pData);
            break;

        case MSGID_RESPONSE_TELEPORT_LIST:
            ResponseTeleportList(pData);
            break;

        case MSGID_RESPONSE_HELDENIAN_TP_LIST: // Heldenian TP
            ResponseHeldenianTeleportList(pData);
            break;

        case MSGID_RESPONSE_NOTICEMENT:
            NoticementHandler(pData);
            break;

        case MSGID_DYNAMICOBJECT:
            DynamicObjectHandler(pData);
            break;

        case MSGID_RESPONSE_INITPLAYER:
            InitPlayerResponseHandler(pData);
            break;

        case MSGID_RESPONSE_INITDATA:
            InitDataResponseHandler(pData);
            break;

        case MSGID_RESPONSE_MOTION:
            MotionResponseHandler(pData);
            break;

        case MSGID_EVENT_COMMON:
            CommonEventHandler(pData);
            break;

        case MSGID_EVENT_MOTION:
            MotionEventHandler(pData);
            break;

        case MSGID_EVENT_LOG:
            LogEventHandler(pData);
            break;

        case MSGID_COMMAND_CHATMSG:
            ChatMsgHandler(pData);
            break;

        case MSGID_PLAYERITEMLISTCONTENTS:
            InitItemList(pData);
            break;

        case MSGID_NOTIFY:
            NotifyMsgHandler(pData);
            break;

        case MSGID_RESPONSE_CREATENEWGUILD:
            CreateNewGuildResponseHandler(pData);
            break;

        case MSGID_RESPONSE_DISBANDGUILD:
            DisbandGuildResponseHandler(pData);
            break;

        case MSGID_PLAYERCHARACTERCONTENTS:
            InitPlayerCharacteristics(pData);
            break;

        case MSGID_RESPONSE_CIVILRIGHT:
            CivilRightAdmissionHandler(pData);
            break;

        case MSGID_RESPONSE_RETRIEVEITEM:
            RetrieveItemHandler(pData);
            break;

        case MSGID_RESPONSE_PANNING:
            ResponsePanningHandler(pData);
            break;

        case MSGID_RESPONSE_FIGHTZONE_RESERVE:
            ReserveFightzoneResponseHandler(pData);
            break;
    }
}


void CGame::ConnectionEstablishHandler(char cWhere)
{
    ChangeGameMode(DEF_GAMEMODE_ONWAITINGRESPONSE);

    switch (cWhere)
    {
        case DEF_SERVERTYPE_GAME:
            bSendCommand(MSGID_REQUEST_INITPLAYER, 0, 0, 0, 0, 0, 0);
            break;

        case DEF_SERVERTYPE_LOG:
            switch (m_dwConnectMode)
            {
                case MSGID_REQUEST_LOGIN:
                    bSendCommand(MSGID_REQUEST_LOGIN, 0, 0, 0, 0, 0, 0);
                    break;
                case MSGID_REQUEST_CREATENEWACCOUNT:
                    bSendCommand(MSGID_REQUEST_CREATENEWACCOUNT, 0, 0, 0, 0, 0, 0);
                    break;
                case MSGID_REQUEST_CREATENEWCHARACTER:
                    bSendCommand(MSGID_REQUEST_CREATENEWCHARACTER, 0, 0, 0, 0, 0, 0);
                    break;
                case MSGID_REQUEST_ENTERGAME:
                    bSendCommand(MSGID_REQUEST_ENTERGAME, 0, 0, 0, 0, 0, 0);
                    break;
                case MSGID_REQUEST_DELETECHARACTER:
                    bSendCommand(MSGID_REQUEST_DELETECHARACTER, 0, 0, 0, 0, 0, 0);
                    break;
                case MSGID_REQUEST_CHANGEPASSWORD:
                    bSendCommand(MSGID_REQUEST_CHANGEPASSWORD, 0, 0, 0, 0, 0, 0);
                    break;
                case MSGID_REQUEST_INPUTKEYCODE:
                    bSendCommand(MSGID_REQUEST_INPUTKEYCODE, 0, 0, 0, 0, 0, 0);
                    break;
            }
            break;
    }
}

void CGame::InitPlayerResponseHandler(char * pData)
{
    uint16_t * wp;
    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    switch (*wp)
    {
        case DEF_MSGTYPE_CONFIRM:
            bSendCommand(MSGID_REQUEST_INITDATA, 0, 0, 0, 0, 0, 0);
            ChangeGameMode(DEF_GAMEMODE_ONWAITINGINITDATA);
            break;

        case DEF_MSGTYPE_REJECT:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "3J");
            break;
    }
}

void CGame::MakeSprite(const char * FileName, short sStart, short sCount, bool bAlphaEffect)
{
    for (short i = 0; i < sCount; i++)
        m_pSprite[i + sStart] = new CSprite(&m_DDraw, FileName, i, bAlphaEffect);
}

void CGame::MakeTileSpr(const char * FileName, short sStart, short sCount, bool bAlphaEffect)
{
    for (short i = 0; i < sCount; i++)
        m_pTileSpr[i + sStart] = new CSprite(&m_DDraw, FileName, i, bAlphaEffect);
}

void CGame::MakeEffectSpr(const char * FileName, short sStart, short sCount, bool bAlphaEffect)
{
    for (short i = 0; i < sCount; i++)
        m_pEffectSpr[i + sStart] = new CSprite(&m_DDraw, FileName, i, bAlphaEffect);
}

void CGame::OnTimer()
{
    if (m_cGameMode < 0) return;
    uint64_t dwTime = unixtime();

    if (m_cGameMode != DEF_GAMEMODE_ONLOADING)
    {
        if ((dwTime - m_dwCheckSprTime) > 8000)
        {
            m_dwCheckSprTime = dwTime;
            if (m_bIsProgramActive) ReleaseUnusedSprites();
            if (ws && is_connected())
                bSendCommand(MSGID_COMMAND_CHECKCONNECTION, DEF_MSGTYPE_CONFIRM, 0, 0, 0, 0, 0);
        }
    }

    if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
    {
        if ((dwTime - m_dwCheckConnTime) > 5000)
        {
            m_dwCheckConnTime = dwTime;
            if ((m_bIsCrusadeMode) && (m_iCrusadeDuty == 0)) EnableDialogBox(33, 1, 0, 0);
        }

        if ((dwTime - m_dwCheckChatTime) > 2000)
        {
            m_dwCheckChatTime = m_dwTime;
            ReleaseTimeoverChatMsg();
            if (m_cCommandCount >= 6)
            {
                m_iNetLagCount++;
                if (m_iNetLagCount >= 7)
                {
                    ChangeGameMode(DEF_GAMEMODE_ONCONNECTIONLOST);
                    ws = nullptr;
                    return;
                }
            }
            else m_iNetLagCount = 0;
        }
    }
}


bool CGame::_bCheckDlgBoxClick(short msX, short msY)
{
    int i;
    char         cDlgID;
    m_stMCursor.sZ = 0;
    for (i = 0; i < 61; i++)
        if (m_cDialogBoxOrder[60 - i] != 0)
        {
            cDlgID = m_cDialogBoxOrder[60 - i];
            if ((m_stDialogBoxInfo[cDlgID].sX < msX) && ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) > msX) &&
                (m_stDialogBoxInfo[cDlgID].sY < msY) && ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) > msY))
            {
                switch (cDlgID)
                {
                    case 1:
                        DlgBoxClick_Character(msX, msY);
                        break;
                    case 2:
                        DlgBoxClick_Inventory(msX, msY);
                        break;
                    case 3:
                        DlgBoxClick_Magic(msX, msY);
                        break;
                    case 4:
                        DlgBoxClick_ItemDrop(msX, msY);
                        break;
                    case 5:
                        DlgBoxClick_15AgeMsg(msX, msY);
                        break;
                    case 6:
                        DlgBoxClick_WarningMsg(msX, msY);
                        break;
                    case 7:
                        DlgBoxClick_GuildMenu(msX, msY);
                        break;
                    case 8:
                        DlgBoxClick_GuildOp(msX, msY);
                        break;
                    case 9:
                        break;
                    case 11:
                        DlgBoxClick_Shop(msX, msY);
                        break;
                    case 12:
                        DlgBoxClick_LevelUpSettings(msX, msY);
                        break;
                    case 13:
                        DlgBoxClick_CityhallMenu(msX, msY);
                        break;
                    case 14:
                        DlgBoxClick_Bank(msX, msY);
                        break;
                    case 15:
                        DlgBoxClick_Skill(msX, msY);
                        break;
                    case 16:
                        DlgBoxClick_MagicShop(msX, msY);
                        break;
                    case 18:
                        DlgBoxClick_Text(msX, msY);
                        break;
                    case 19:
                        DlgBoxClick_SysMenu(msX, msY);
                        break;
                    case 20:
                        DlgBoxClick_NpcActionQuery(msX, msY);
                        break;
                    case 21:
                        DlgBoxClick_NpcTalk(msX, msY);
                        break;
                    case 23:
                        DlgBoxClick_ItemSellorRepair(msX, msY);
                        break;
                    case 24:
                        DlgBoxClick_Fish(msX, msY);
                        break;
                    case 25:
                        DlgBoxClick_ShutDownMsg(msX, msY);
                        break;
                    case 26:
                        DlgBoxClick_SkillDlg(msX, msY);
                        break;
                    case 27:
                        DlgBoxClick_Exchange(msX, msY);
                        break;
                    case 28:
                        DlgBoxClick_Quest(msX, msY);
                        break;
                    case 30:
                        DlgBoxClick_IconPannel(msX, msY);
                        break;
                    case 31:
                        DlgBoxClick_SellList(msX, msY);
                        break;
                    case 32:
                        DlgBoxClick_Party(msX, msY);
                        break;
                    case 33:
                        DlgBoxClick_CrusadeJob(msX, msY);
                        break;
                    case 34:
                        DlgBoxClick_ItemUpgrade(msX, msY);
                        break;
                    case 35:
                        DlgBoxClick_Help(msX, msY);
                        break;

                    case 36:
                        DlgBoxClick_Commander(msX, msY);
                        break;

                    case 37:
                        DlgBoxClick_Constructor(msX, msY);
                        break;

                    case 38:
                        DlgBoxClick_Soldier(msX, msY);
                        break;

                    case 40:
                        DlgBoxClick_Slates(msX, msY);
                        break;
                    case 41:
                        DlgBoxClick_ConfirmExchange(msX, msY);
                        break;
                    case 42:
                        DlgBoxClick_ChangeStatsMajestic(msX, msY);
                        break;
                    case 50:
                        DlgBoxClick_Resurect(msX, msY);
                        break;
                    case 51:
                        DlgBoxClick_CMDHallMenu(msX, msY);
                        break;
                }

                return true;
            }
        }

    return false;
}

bool CGame::_bCheckDlgBoxDoubleClick(short msX, short msY)
{
    int i;
    char cDlgID;
    for (i = 0; i < 61; i++)
        if (m_cDialogBoxOrder[60 - i] != 0)
        {
            cDlgID = m_cDialogBoxOrder[60 - i];
            if ((m_stDialogBoxInfo[cDlgID].sX < msX) && ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) > msX)
                && (m_stDialogBoxInfo[cDlgID].sY < msY) && ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) > msY))
            {
                switch (cDlgID)
                {
                    case 1:
                        DlbBoxDoubleClick_Character(msX, msY);
                        break;
                    case 2:
                        DlbBoxDoubleClick_Inventory(msX, msY);
                        break;
                    case 9:
                        DlbBoxDoubleClick_GuideMap(msX, msY);
                        break;
                }
                return true;
            }
        }
    return false;
}



void CGame::_SetItemOrder(char cWhere, char cItemID)
{
    int i;

    switch (cWhere)
    {
        case 0:
            for (i = 0; i < DEF_MAXITEMS; i++)
                if (m_cItemOrder[i] == cItemID)
                    m_cItemOrder[i] = -1;

            for (i = 1; i < DEF_MAXITEMS; i++)
                if ((m_cItemOrder[i - 1] == -1) && (m_cItemOrder[i] != -1))
                {
                    m_cItemOrder[i - 1] = m_cItemOrder[i];
                    m_cItemOrder[i] = -1;
                }

            for (i = 0; i < DEF_MAXITEMS; i++)
                if (m_cItemOrder[i] == -1)
                {
                    m_cItemOrder[i] = cItemID;
                    return;
                }
            break;
    }
}

bool CGame::_bCheckDraggingItemRelease(short msX, short msY)
{
    int i;
    char         cDlgID;
    for (i = 0; i < 61; i++)
        if (m_cDialogBoxOrder[60 - i] != 0)
        {
            cDlgID = m_cDialogBoxOrder[60 - i];
            if ((m_stDialogBoxInfo[cDlgID].sX < msX) && ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) > msX)
                && (m_stDialogBoxInfo[cDlgID].sY < msY) && ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) > msY))
            {
                EnableDialogBox(cDlgID, 0, 0, 0);
                switch (cDlgID)
                {
                    case 1:
                        bItemDrop_Character();
                        break;

                    case 2:
                        bItemDrop_Inventory(msX, msY);
                        break;

                    case 14:
                        bItemDrop_Bank(msX, msY);
                        break;

                    case 26: // Alchim / Manuf
                        bItemDrop_SkillDialog();
                        break;

                    case 27:
                        bItemDrop_ExchangeDialog(msX, msY);
                        break;

                    case 30:
                        bItemDrop_IconPannel(msX, msY);
                        break;

                    case 31:
                        bItemDrop_SellList(msX, msY);
                        break;

                    case 34:
                        bItemDrop_ItemUpgrade();
                        break;

                    case 40:
                        bItemDrop_Slates();
                        break;
                }
                return true;
            }
        }
    bItemDrop_ExternalScreen((char)m_stMCursor.sSelectedObjectID, msX, msY);
    return false;
}

void CGame::CommonEventHandler(char * pData)
{
    uint16_t * wp, wEventType;
    short * sp, sX, sY, sV1, sV2, sV3, sV4;
    char * cp;

    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    wEventType = *wp;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    sp = (short *)cp;
    sX = *sp;
    cp += 2;

    sp = (short *)cp;
    sY = *sp;
    cp += 2;

    sp = (short *)cp;
    sV1 = *sp;
    cp += 2;

    sp = (short *)cp;
    sV2 = *sp;
    cp += 2;

    sp = (short *)cp;
    sV3 = *sp;
    cp += 2;

    sp = (short *)cp;
    sV4 = *sp;
    cp += 2;

    switch (wEventType)
    {
        case DEF_COMMONTYPE_ITEMDROP:
            if ((sV1 == 6) && (sV2 == 0))
            {
                bAddNewEffect(4, sX, sY, 0, 0, 0);
            }
            m_pMapData->bSetItem(sX, sY, sV1, sV2, (char)sV3);
            break;

        case DEF_COMMONTYPE_SETITEM:
            m_pMapData->bSetItem(sX, sY, sV1, sV2, (char)sV3, false); // v1.4 color
            break;

        case DEF_COMMONTYPE_MAGIC:
            bAddNewEffect(sV3, sX, sY, sV1, sV2, 0, sV4);
            break;

        case DEF_COMMONTYPE_CLEARGUILDNAME:
            ClearGuildNameList();
            break;
    }
}

void CGame::ClearGuildNameList()
{
    for (int i = 0; i < DEF_MAXGUILDNAMES; i++)
    {
        m_stGuildName[i].dwRefTime = 0;
        m_stGuildName[i].iGuildRank = -1;
        ZeroMemory(m_stGuildName[i].cCharName, sizeof(m_stGuildName[i].cCharName));
        ZeroMemory(m_stGuildName[i].cGuildName, sizeof(m_stGuildName[i].cGuildName));
    }
}

void CGame::InitGameSettings()
{
    int i;

    m_bForceAttack = false;
    m_dwCommandTime = 0;

    m_bInputStatus = false;
    m_pInputBuffer = 0;

    m_iPDBGSdivX = 0;
    m_iPDBGSdivY = 0;
    m_bIsRedrawPDBGS = true;

    m_iCameraShakingDegree = 0;

    m_cCommand = DEF_OBJECTSTOP;
    m_cCommandCount = 0;

    m_bIsGetPointingMode = false;
    m_iPointCommandType = -1; //v2.15 0 -> -1

    m_bIsCombatMode = false;
    m_bRunningMode = false;

    m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
    m_stMCursor.dwSelectClickTime = 0;

    m_bSkillUsingStatus = false;
    m_bItemUsingStatus = false;
    m_bUsingSlate = false;
    m_bHackMoveBlocked = false;

    m_bIsWhetherEffect = false;
    m_cWhetherEffectType = 0;

    m_iDownSkillIndex = -1;
    m_stDialogBoxInfo[15].bFlag = false;

    m_bIsConfusion = false;

    m_iIlusionOwnerH = 0;
    m_cIlusionOwnerType = 0;

    m_iDrawFlag = 0;
    m_bDrawFlagDir = false;
    m_bIsCrusadeMode = false;
    m_iCrusadeDuty = 0;
    m_bIsAvatarMode = false;
    m_bIsAvatarMessenger = false;
    m_bIsHeldenianMode = false;
    m_bIsHeldenianMap = false;

    m_iNetLagCount = 0;

    m_dwCRC32 = 0;
    m_wCRC16_1 = 0;
    m_wCRC16_2 = 0;
    m_bUseCRC_2 = false;

    m_dwEnvEffectTime = unixtime();

    for (i = 0; i < DEF_MAXGUILDNAMES; i++)
    {
        m_stGuildName[i].dwRefTime = 0;
        m_stGuildName[i].iGuildRank = -1;
        ZeroMemory(m_stGuildName[i].cCharName, sizeof(m_stGuildName[i].cCharName));
        ZeroMemory(m_stGuildName[i].cGuildName, sizeof(m_stGuildName[i].cGuildName));
    }
    for (i = 0; i < 61; i++)
        m_bIsDialogEnabled[i] = false;

    for (i = 0; i < 58; i++)
        m_cDialogBoxOrder[i] = 0;

    for (i = 0; i < DEF_MAXEFFECTS; i++)
    {
        if (m_pEffectList[i] != 0) delete m_pEffectList[i];
        m_pEffectList[i] = 0;
    }

    for (i = 0; i < DEF_MAXCHATMSGS; i++)
    {
        if (m_pChatMsgList[i] != 0) delete m_pChatMsgList[i];
        m_pChatMsgList[i] = 0;
    }

    for (i = 0; i < DEF_MAXCHATSCROLLMSGS; i++)
    {
        if (m_pChatScrollList[i] != 0) delete m_pChatScrollList[i];
        m_pChatScrollList[i] = 0;
    }

    for (i = 0; i < DEF_MAXWHISPERMSG; i++)
    {
        if (m_pWhisperMsg[i] != 0) delete m_pWhisperMsg[i];
        m_pWhisperMsg[i] = 0;
    }

    ZeroMemory(m_cLocation, sizeof(m_cLocation));

    ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
    m_iGuildRank = -1;
    m_iTotalGuildsMan = 0;

    for (i = 0; i < 100; i++)
    {
        m_stGuildOpList[i].cOpMode = 0;
        ZeroMemory(m_stGuildOpList[i].cName, sizeof(m_stGuildOpList[i].cName));
    }

    for (i = 0; i < 6; i++)
    {
        ZeroMemory(m_stEventHistory[i].cTxt, sizeof(m_stEventHistory[i].cTxt));
        m_stEventHistory[i].dwTime = G_dwGlobalTime;

        ZeroMemory(m_stEventHistory2[i].cTxt, sizeof(m_stEventHistory2[i].cTxt));
        m_stEventHistory2[i].dwTime = G_dwGlobalTime;
    }

    for (i = 0; i < DEF_MAXMENUITEMS; i++)
    {
        if (m_pItemForSaleList[i] != 0) delete m_pItemForSaleList[i];
        m_pItemForSaleList[i] = 0;
    }

    for (i = 0; i < 41; i++)
    {
        m_stDialogBoxInfo[i].bFlag = false;
        m_stDialogBoxInfo[i].sView = 0;
        m_stDialogBoxInfo[i].bIsScrollSelected = false;
    }

    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_pItemList[i] != 0)
        {
            delete m_pItemList[i];
            m_pItemList[i] = 0;
        }

    for (i = 0; i < DEF_MAXSELLLIST; i++)
    {
        m_stSellItemList[i].iIndex = -1;
        m_stSellItemList[i].iAmount = 0;
    }

    for (i = 0; i < DEF_MAXBANKITEMS; i++)
        if (m_pBankList[i] != 0)
        {
            delete m_pBankList[i];
            m_pBankList[i] = 0;
        }

    for (i = 0; i < DEF_MAXMAGICTYPE; i++)
        m_cMagicMastery[i] = 0;

    for (i = 0; i < DEF_MAXSKILLTYPE; i++)
        m_cSkillMastery[i] = 0;

    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        if (m_pMsgTextList[i] != 0)
            delete m_pMsgTextList[i];
        m_pMsgTextList[i] = 0;

        if (m_pMsgTextList2[i] != 0)
            delete m_pMsgTextList2[i];
        m_pMsgTextList2[i] = 0;

        if (m_pAgreeMsgTextList[i] != 0)
            delete m_pAgreeMsgTextList[i];
        m_pAgreeMsgTextList[i] = 0;
    }

    for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
    {
        m_stPartyMember[i].cStatus = 0;
        ZeroMemory(m_stPartyMember[i].cName, sizeof(m_stPartyMember[i].cName));
    }

    m_iLU_Point = 0;
    m_cLU_Str = m_cLU_Vit = m_cLU_Dex = m_cLU_Int = m_cLU_Mag = m_cLU_Char = 0;
    m_bDialogTrans = false;
    m_cWhetherStatus = 0;
    m_cLogOutCount = -1;
    m_dwLogOutCountTime = 0;
    m_iSuperAttackLeft = 0;
    m_bSuperAttackMode = false;
    m_iFightzoneNumber = 0;
    ZeroMemory(m_cBGMmapName, sizeof(m_cBGMmapName));
    m_dwWOFtime = 0;
    m_stQuest.sWho = 0;
    m_stQuest.sQuestType = 0;
    m_stQuest.sContribution = 0;
    m_stQuest.sTargetType = 0;
    m_stQuest.sTargetCount = 0;
    m_stQuest.sCurrentCount = 0;
    m_stQuest.sX = 0;
    m_stQuest.sY = 0;
    m_stQuest.sRange = 0;
    m_stQuest.bIsQuestCompleted = false;
    ZeroMemory(m_stQuest.cTargetName, sizeof(m_stQuest.cTargetName));
    m_bIsObserverMode = false;
    m_bIsObserverCommanded = false;
    m_bIsPoisoned = false;
    m_bIsPrevMoveBlocked = false;
    m_iPrevMoveX = m_iPrevMoveY = -1;
    m_sDamageMove = 0;
    m_sDamageMoveAmount = 0;
    m_bForceDisconn = false;
    m_bIsSpecialAbilityEnabled = false;
    m_iSpecialAbilityType = 0;
    m_dwSpecialAbilitySettingTime = 0;
    m_iSpecialAbilityTimeLeftSec = 0;
    m_stMCursor.cSelectedObjectType = 0;
    m_bIsF1HelpWindowEnabled = false;
    m_bIsTeleportRequested = false;
    for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
    {
        m_stCrusadeStructureInfo[i].cType = 0;
        m_stCrusadeStructureInfo[i].cSide = 0;
        m_stCrusadeStructureInfo[i].sX = 0;
        m_stCrusadeStructureInfo[i].sY = 0;
    }
    ZeroMemory(m_cStatusMapName, sizeof(m_cStatusMapName));
    m_dwCommanderCommandRequestedTime = 0;
    ZeroMemory(m_cTopMsg, sizeof(m_cTopMsg));
    m_iTopMsgLastSec = 0;
    m_dwTopMsgTime = 0;
    m_iConstructionPoint = 0;
    m_iWarContribution = 0;
    ZeroMemory(m_cTeleportMapName, sizeof(m_cTeleportMapName));
    m_iTeleportLocX = m_iTeleportLocY = -1;
    ZeroMemory(m_cConstructMapName, sizeof(m_cConstructMapName));
    m_iConstructLocX = m_iConstructLocY = -1;

    ZeroMemory(m_cGateMapName, sizeof(m_cGateMapName));
    m_iGatePositX = m_iGatePositY = -1;
    m_iHeldenianAresdenLeftTower = -1;
    m_iHeldenianElvineLeftTower = -1;
    m_iHeldenianAresdenFlags = -1;
    m_iHeldenianElvineFlags = -1;
    m_bIsXmas = false;
    m_iTotalPartyMember = 0;
    m_iPartyStatus = 0;
    for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) ZeroMemory(m_stPartyMemberNameList[i].cName, sizeof(m_stPartyMemberNameList[i].cName));
    m_iGizonItemUpgradeLeft = 0;
    cStateChange1 = 0;
    cStateChange2 = 0;
    cStateChange3 = 0;
    EnableDialogBox(9, 0, 0, 0);
}

void CGame::_GetHairColorColor(int iColorType, int * pR, int * pG, int * pB)
{
    switch (iColorType)
    {
        case 0: // rouge foncé
            *pR = 14; *pG = -5; *pB = -5; break;
        case 1: // Orange
            *pR = 20; *pG = 0; *pB = 0; break;
        case 2: // marron tres clair
            *pR = 22; *pG = 13; *pB = -10; break;
        case 3: // vert
            *pR = 0; *pG = 10; *pB = 0; break;
        case 4: // Bleu flashy
            *pR = 0; *pG = 0; *pB = 22; break;
        case 5: // Bleu foncé
            *pR = -5; *pG = -5; *pB = 15; break;
        case 6: //Mauve
            *pR = 15; *pG = -5; *pB = 16; break;
        case 7: // Noir
            *pR = -6; *pG = -6; *pB = -6; break;

#ifdef DEF_EQUILIBRIUM_PROJECT // cheveux
        case 8: // Brun foncé
            *pR = 6; *pG = -2; *pB = -6; break;
        case 9: // Chatain
            *pR = 10; *pG = 3; *pB = -10; break;
        case 10: // chatain clair
            *pR = 14; *pG = 7; *pB = -14; break;
        case 11: // Blond
            *pR = 18; *pG = 20; *pB = 6; break;
        case 12: // Blond or
            *pR = 22; *pG = 24; *pB = -24; break;
        case 13: // Poivre et sel
            *pR = 12; *pG = 12; *pB = 9; break;
        case 14: // Gris clair
            *pR = 15; *pG = 19; *pB = 13; break;
        case 15: // Blanc
            *pR = 18; *pG = 26; *pB = 17; break;
#else
        case 8:
            *pR = 10; *pG = 3; *pB = 10; break;
        case 9:
            *pR = 10; *pG = 3; *pB = -10; break;
        case 10:
            *pR = -10; *pG = 3; *pB = 10; break;
        case 11:
            *pR = 10; *pG = 3; *pB = 20; break;
        case 12:
            *pR = 21; *pG = 3; *pB = 3; break;
        case 13:
            *pR = 3; *pG = 3; *pB = 25; break;
        case 14:
            *pR = 3; *pG = 11; *pB = 3; break;
        case 15:
            *pR = 6; *pG = 8; *pB = 0; break;
#endif

    }
}

void CGame::CreateNewGuildResponseHandler(char * pData)
{
    uint16_t * wpResult;
    wpResult = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    switch (*wpResult)
    {
        case DEF_MSGTYPE_CONFIRM:
            m_iGuildRank = 0;
            m_stDialogBoxInfo[7].cMode = 3;
            break;
        case DEF_MSGTYPE_REJECT:
            m_iGuildRank = -1;
            m_stDialogBoxInfo[7].cMode = 4;
            break;
    }
}

void CGame::InitPlayerCharacteristics(char * pData)
{
    int * ip;
    char * cp;
    uint16_t * wp;
    m_iAngelicStr = 0;
    m_iAngelicDex = 0;
    m_iAngelicInt = 0;
    m_iAngelicMag = 0;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    ip = (int *)cp;
    m_iHP = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iMP = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iSP = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iAC = *ip;		//â m_iDefenseRatio
    cp += 4;
    ip = (int *)cp;
    m_iTHAC0 = *ip;    //» m_iHitRatio
    cp += 4;
    ip = (int *)cp;
    m_iLevel = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iStr = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iInt = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iVit = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iDex = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iMag = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iCharisma = *ip;
    cp += 4;

    wp = (uint16_t *)cp;
    m_iLU_Point = *wp - 3;
    cp += 7; // 2 + 5

    /* ORIGINAL
    m_cLU_Str = *cp;
    cp++;
    m_cLU_Vit = *cp;
    cp++;
    m_cLU_Dex = *cp;
    cp++;
    m_cLU_Int = *cp;
    cp++;
    m_cLU_Mag = *cp;
    cp++;
    m_cLU_Char = *cp;
    cp++;

    m_iLU_Point = 3 - (m_cLU_Str + m_cLU_Vit + m_cLU_Dex + m_cLU_Int + m_cLU_Mag + m_cLU_Char);
*/

    ip = (int *)cp;
    m_iExp = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iEnemyKillCount = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iPKCount = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iRewardGold = *ip;
    cp += 4;

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

    cp = (char *)cp;
    memcpy(m_cGuildName, cp, 20);
    cp += 20;

    if (strcmp(m_cGuildName, "NONE") == 0)
        ZeroMemory(m_cGuildName, sizeof(m_cGuildName));

    m_Misc.ReplaceString(m_cGuildName, '_', ' ');
    ip = (int *)cp;
    m_iGuildRank = *ip;
    cp += 4;
    m_iSuperAttackLeft = (int)*cp;
    cp++;
    ip = (int *)cp;
    m_iFightzoneNumber = *ip;
    cp += 4;
}


void CGame::DisbandGuildResponseHandler(char * pData)
{
    uint16_t * wpResult;
    wpResult = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    switch (*wpResult)
    {
        case DEF_MSGTYPE_CONFIRM:
            ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
            m_iGuildRank = -1;
            m_stDialogBoxInfo[7].cMode = 7;
            break;
        case DEF_MSGTYPE_REJECT:
            m_stDialogBoxInfo[7].cMode = 8;
            break;
    }
}

void CGame::_PutGuildOperationList(char * pName, char cOpMode)
{
    int i;
    for (i = 0; i < 100; i++)
        if (m_stGuildOpList[i].cOpMode == 0)
        {
            m_stGuildOpList[i].cOpMode = cOpMode;
            ZeroMemory(m_stGuildOpList[i].cName, sizeof(m_stGuildOpList[i].cName));
            memcpy(m_stGuildOpList[i].cName, pName, 20);
            return;
        }
}

void CGame::_ShiftGuildOperationList()
{
    int i;
    ZeroMemory(m_stGuildOpList[0].cName, sizeof(m_stGuildOpList[0].cName));
    m_stGuildOpList[0].cOpMode = 0;

    for (i = 1; i < 100; i++)
        if ((m_stGuildOpList[i - 1].cOpMode == 0) && (m_stGuildOpList[i].cOpMode != 0))
        {
            m_stGuildOpList[i - 1].cOpMode = m_stGuildOpList[i].cOpMode;
            ZeroMemory(m_stGuildOpList[i - 1].cName, sizeof(m_stGuildOpList[i - 1].cName));
            memcpy(m_stGuildOpList[i - 1].cName, m_stGuildOpList[i].cName, 20);

            ZeroMemory(m_stGuildOpList[i].cName, sizeof(m_stGuildOpList[i].cName));
            m_stGuildOpList[i].cOpMode = 0;
        }
}



void CGame::SetItemCount(const char * pItemName, uint32_t dwCount)
{
    int i;
    char cTmpName[21] = {};
    ZeroMemory(cTmpName, sizeof(cTmpName));
    strcpy(cTmpName, pItemName);
    for (i = 0; i < DEF_MAXITEMS; i++)
        if ((m_pItemList[i] != 0) && (memcmp(m_pItemList[i]->m_cName, cTmpName, 20) == 0))
        {
            m_pItemList[i]->m_dwCount = dwCount;
            return;
        }
}


void CGame::AddEventList(const char * pTxt, char cColor, bool bDupAllow)
{
    int i;
    if ((bDupAllow == false) && (strcmp(m_stEventHistory[5].cTxt, pTxt) == 0)) return;
    if (cColor == 10)
    {
        for (i = 1; i < 6; i++)
        {
            strcpy(m_stEventHistory2[i - 1].cTxt, m_stEventHistory2[i].cTxt);
            m_stEventHistory2[i - 1].cColor = m_stEventHistory2[i].cColor;
            m_stEventHistory2[i - 1].dwTime = m_stEventHistory2[i].dwTime;
        }
        ZeroMemory(m_stEventHistory2[5].cTxt, sizeof(m_stEventHistory2[5].cTxt));
        strcpy(m_stEventHistory2[5].cTxt, pTxt);
        m_stEventHistory2[5].cColor = cColor;
        m_stEventHistory2[5].dwTime = m_dwCurTime;
    }
    else
    {
        for (i = 1; i < 6; i++)
        {
            strcpy(m_stEventHistory[i - 1].cTxt, m_stEventHistory[i].cTxt);
            m_stEventHistory[i - 1].cColor = m_stEventHistory[i].cColor;
            m_stEventHistory[i - 1].dwTime = m_stEventHistory[i].dwTime;
        }
        ZeroMemory(m_stEventHistory[5].cTxt, sizeof(m_stEventHistory[5].cTxt));
        strcpy(m_stEventHistory[5].cTxt, pTxt);
        m_stEventHistory[5].cColor = cColor;
        m_stEventHistory[5].dwTime = m_dwCurTime;
    }
}

int _iAttackerHeight[] = { 0, 35, 35,35,35,35,35, 0,0,0,
5,  // Slime
35, // Skeleton
40, // Stone-Golem
45, // Cyclops
35,// OrcMage
35,// ShopKeeper
5, // GiantAnt
8, // Scorpion
35,// Zombie
35,// Gandalf
35,// Howard
35,// Guard
10,// Amphis
38,// Clay-Golem
35,// Tom
35,// William
35,// Kennedy
35,// Hellhound
50,// Troll
45,// Orge
55,// Liche
65,// Demon
46,// Unicorn
49,// WereWolf
55,// Dummy
35,// Energysphere
75,// Arrow Guard Tower
75,// Cannon Guard Tower
50,// Mana Collector
50,// Detector
50,// Energy Shield Generator
50,// Grand Magic Generator
50,// ManaStone 42
40,// Light War Beetle
35,// GHK
40,// GHKABS
35,// TK
60,// BG
40,// Stalker
70,// HellClaw
85,// Tigerworm
50,// Catapult
85,// Gargoyle
70,// Beholder
40,// Dark-Elf
20,// Bunny
20,// Cat
40,// Giant-Frog
80,// Mountain-Giant
85,// Ettin
50,// Cannibal-Plant
50, // Rudolph 61
80, // Direboar 62
90, // Frost 63
40, // Crops 64
80, // IceGolem 65
190, // Wyvern 66
35, // npc 67
35, // npc 68
35, // npc 69
100, // Dragon 70
90, // Centaur 71
75, // ClawTurtle 72
200, // FireWyvern 73
80, // GiantCrayfish 74
120, // Gi Lizard 75
100, // Gi Tree 76
100, // Master Orc 77
80, // Minaus 78
100, // Nizie 79
25,  // Tentocle 80
200, // Abaddon	 81
60, // Sorceress 82
60, // ATK 83
70, // MasterElf 84
60, // DSK 85
50, // HBT 86
60, // CT 87
60, // Barbarian 88
60, // AGC 89
35, // ncp 90 Gail
35, // Gate 91
35, // 92
35, // 93
35, // 94
45, // 95 Willowisp
80, // 96 Air Elemental
70, // 97 Fire Elemental
60, // 98 Earth Elemental
100, // 99 Ice Elemental
35, // 100
35  // 101

};

void CGame::bAddNewEffect(short sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1)
{
    int i;
    short sAbsX, sAbsY, sDist;
    long lPan;
    int  iV2 = 0;
    if (m_cDetailLevel == 0) // Detail Level Low
    {
        switch (sType)
        {
            case 8:
            case 9:
            case 11:
            case 12:
            case 14:
            case 15:
                return;
        }
    }
    if (m_bIsProgramActive == false) return;
    sAbsX = abs(((m_sViewPointX / 32) + 10) - dX);
    sAbsY = abs(((m_sViewPointY / 32) + 7) - dY);
    if (sAbsX > sAbsY) sDist = sAbsX;
    else sDist = sAbsY;

    for (i = 0; i < DEF_MAXEFFECTS; i++)
        if (m_pEffectList[i] == 0)
        {
            m_pEffectList[i] = new class CEffect;
            m_pEffectList[i]->m_sType = sType;
            m_pEffectList[i]->m_sX = sX;
            m_pEffectList[i]->m_sY = sY;
            m_pEffectList[i]->m_dX = dX;
            m_pEffectList[i]->m_dY = dY;
            m_pEffectList[i]->m_iV1 = iV1;
            m_pEffectList[i]->m_cFrame = cStartFrame;
            m_pEffectList[i]->m_dwTime = m_dwCurTime;

            switch (sType)
            {
                case 1: // coup normal
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - _iAttackerHeight[iV1];
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 2;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 2:	// Flêche qui vole
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - _iAttackerHeight[iV1];
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
                    PlaySound('C', 4, sDist);
                    break;

                case 4: // Gold
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32;
                    m_pEffectList[i]->m_cMaxFrame = 12;
                    m_pEffectList[i]->m_dwFrameTime = 100;
                    sAbsX = abs(((m_sViewPointX / 32) + 10) - sX);
                    sAbsY = abs(((m_sViewPointY / 32) + 7) - sY);
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    lPan = -(((m_sViewPointX / 32) + 10) - sX) * 1000;
                    PlaySound('E', 12, sDist, lPan);
                    break;

                case 5: // FireBall Fire Explosion
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 11;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(((m_sViewPointX / 32) + 10) - sX) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist);
                    break;

                case 6:	 // Energy Bolt
                case 10: // Lightning Arrow
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 14;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(320 - (sX - m_sViewPointX)) * 1000;
                    PlaySound('E', 2, sDist, lPan);
                    SetCameraShakingEffect(sDist);
                    break;

                case 7: // Magic Missile Explosion
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 5;
                    m_pEffectList[i]->m_dwFrameTime = 50;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(320 - (sX - m_sViewPointX)) * 1000;
                    PlaySound('E', 3, sDist, lPan);
                    break;

                case 8: // Burst
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 4;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    break;

                case 9: // Burst
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_rX = 6 - (rand() % 12);
                    m_pEffectList[i]->m_rY = -8 - (rand() % 6);
                    m_pEffectList[i]->m_cMaxFrame = 14;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    break;

                case 11:
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_rX = 6 - (rand() % 12);
                    if (iV2 == 0)
                        m_pEffectList[i]->m_rY = -2 - (rand() % 4);
                    else m_pEffectList[i]->m_rY = -2 - (rand() % 10);
                    m_pEffectList[i]->m_cMaxFrame = 8;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    break;

                case 12: // Burst
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_rX = 8 - (rand() % 16);
                    m_pEffectList[i]->m_rY = 4 - (rand() % 12);
                    m_pEffectList[i]->m_cMaxFrame = 10;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    break;

                case 13: // Bulles druncncity
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 18;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    break;

                case 14: // Traces de pas ou Tremor (pas en low detail)
                    m_pEffectList[i]->m_mX = sX;
                    if (m_pEffectList[i]->m_iV1 > 0) // Case if hit by an arrow
                    {
                        m_pEffectList[i]->m_mY = sY - (_iAttackerHeight[m_pEffectList[i]->m_iV1] / 4 + rand() % (_iAttackerHeight[m_pEffectList[i]->m_iV1] / 2));
                        m_pEffectList[i]->m_mX = sX + (rand() % 5) - 2;
                    }
                    else m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 4;
                    m_pEffectList[i]->m_dwFrameTime = 100;
                    m_pEffectList[i]->m_iV1 = iV1;
                    break;

                case 15: // feu
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 16;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    break;

                case 16: //
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    break;

                case 17: // Ice Storm ?
                    m_pEffectList[i]->m_mX = sX + (rand() % 20) - 40;
                    m_pEffectList[i]->m_mY = sY + (rand() % 20) - 40;
                    m_pEffectList[i]->m_rX = 8 - (rand() % 16);
                    m_pEffectList[i]->m_rY = 4 - (rand() % 12);
                    m_pEffectList[i]->m_mX3 = sX;
                    m_pEffectList[i]->m_mY3 = sY;
                    m_pEffectList[i]->m_iV1 = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    break;

                case 18:
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 10;
                    m_pEffectList[i]->m_dwFrameTime = 50;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    SetCameraShakingEffect(sDist);
                    break;

                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27: // Critical strike with a weapon
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
                    break;

                case 30: // Mass-Fire-Strike (called 1 time)
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 9;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(320 - (sX - m_sViewPointX)) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist * 2);
                    break;

                case 31: // Mass-Fire-Strike (called 3 times)
                case 252: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 8;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(320 - (sX - m_sViewPointX)) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist);
                    break;

                case 32: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 4;
                    m_pEffectList[i]->m_dwFrameTime = 100;
                    break;

                case 33: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 16;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 34: //
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    SetCameraShakingEffect(sDist);
                    break;

                case 35: // Mass Magic-Missile
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 18;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(320 - (sX - m_sViewPointX)) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist * 2);
                    break;

                case 36: // Mass Magic-Missile
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(320 - (sX - m_sViewPointX)) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist);
                    break;

                case 40: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = ((sX - m_sViewPointX) - 320) * 30;
                    PlaySound('E', 45, sDist, lPan);
                    break;

                case 41: // Large Type 1, 2, 3, 4 Ice Strike
                case 42:
                case 43:
                case 44:
                case 45: // Small Type 1, 2
                case 46:
                    if (m_pEffectList[i]->m_iV1 > 1) // Ice Elemental
                    {
                        m_pEffectList[i]->m_mX = sX;
                        m_pEffectList[i]->m_mY = sY - m_pEffectList[i]->m_iV1;
                        m_pEffectList[i]->m_cMaxFrame = 7;
                        m_pEffectList[i]->m_dwFrameTime = 20;
                        m_pEffectList[i]->m_iV1 = 20;
                    }
                    else
                    {
                        m_pEffectList[i]->m_mX = sX;
                        m_pEffectList[i]->m_mY = sY - 220;
                        m_pEffectList[i]->m_cMaxFrame = 14;
                        m_pEffectList[i]->m_dwFrameTime = 20;
                        m_pEffectList[i]->m_iV1 = 20;
                    }
                    m_pEffectList[i]->m_iV1 = 20;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = ((sX - m_sViewPointX) - 320) * 30;
                    PlaySound('E', 46, sDist, lPan);
                    break;

                case 47: // Blizzard
                case 48: // Blizzard
                case 49: // Blizzard
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY - 220;
                    m_pEffectList[i]->m_cMaxFrame = 12;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    m_pEffectList[i]->m_iV1 = 20;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = ((sX - m_sViewPointX) - 320) * 30;
                    PlaySound('E', 46, sDist, lPan);
                    break;

                case 50: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 12;
                    m_pEffectList[i]->m_dwFrameTime = 50;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = ((sX - m_sViewPointX) - 320) * 30;
                    if ((rand() % 4) == 1) SetCameraShakingEffect(sDist);
                    PlaySound('E', 47, sDist, lPan);
                    break;

                case 51:
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 9; //15;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    break;

                case 52: // Protect ring
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = ((sX - m_sViewPointX) - 320) * 30;
                    PlaySound('E', 5, sDist, lPan);
                    break;

                case 53: // Hold twist
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = ((sX - m_sViewPointX) - 320) * 30;
                    PlaySound('E', 5, sDist, lPan);
                    break;

                case 54: // star twingkling (effect armes brillantes)
                case 55: // Unused
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 10;
                    m_pEffectList[i]->m_dwFrameTime = 15;
                    break;

                case 56: //  Mass-Chill-Wind
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 14;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = ((sX - m_sViewPointX) - 320) * 30;
                    PlaySound('E', 45, sDist, lPan);
                    break;

                case 57: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 16;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    break;

                case 60: //
                    m_pEffectList[i]->m_mX = sX + 300;
                    m_pEffectList[i]->m_mY = sY - 460;
                    m_pEffectList[i]->m_cMaxFrame = 10;
                    m_pEffectList[i]->m_dwFrameTime = 50;
                    break;

                case 61: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 16;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(((m_sViewPointX / 32) + 10) - sX) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist, 2);
                    break;

                case 62: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 6;
                    m_pEffectList[i]->m_dwFrameTime = 100;
                    break;

                case 63: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 16;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    break;

                case 64: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    break;

                case 65: // Crusade's MS
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 30;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    break;

                case 66: // Crusade MS explosion
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 14;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(((m_sViewPointX / 32) + 10) - sX) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist, 2);
                    break;

                case 67: // Crusade's MS fire + smoke ?
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 27;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 68: // worm-bite
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 17;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(((m_sViewPointX / 32) + 10) - sX) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    m_pEffectList[i]->m_iV1 = sDist;
                    //SetCameraShakingEffect(sDist, 2);
                    break;

                case 69: // identique au cas 70
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 11;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(((m_sViewPointX / 32) + 10) - (sX / 32)) * 1000;
                    PlaySound('E', 42, sDist, lPan);
                    break;

                case 70: // identtique au cas 69
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 11;
                    m_pEffectList[i]->m_dwFrameTime = 30;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(((m_sViewPointX / 32) + 10) - (sX / 32)) * 1000;
                    PlaySound('E', 42, sDist, lPan);
                    break;

                case 71: //
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    SetCameraShakingEffect(sDist);
                    break;

                case 72: // Blizzard
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = ((sX - m_sViewPointX) - 320) * 30;
                    if ((rand() % 4) == 1) SetCameraShakingEffect(sDist);
                    PlaySound('E', 47, sDist, lPan);
                    break;

                case 73:
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 60;
                    break;

                case 74:
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 19;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    break;

                case 75: //ice golem
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_dX = dX;
                    m_pEffectList[i]->m_dY = dY;
                    m_pEffectList[i]->m_cMaxFrame = 16;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    break;

                case 76: //ice golem
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_dX = dX;
                    m_pEffectList[i]->m_dY = dY;
                    m_pEffectList[i]->m_cMaxFrame = 16;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    break;

                case 77: //ice golem
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_dX = dX;
                    m_pEffectList[i]->m_dY = dY;
                    m_pEffectList[i]->m_cMaxFrame = 16;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    break;

                case 80:
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_iV1 = 20;
                    m_pEffectList[i]->m_cMaxFrame = 30;
                    m_pEffectList[i]->m_dwFrameTime = 25;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    SetCameraShakingEffect(sDist);
                    break;

                case 81: // StormBlade
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 27;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    break;

                case 82: // Gate Apocalypse
                    m_pEffectList[i]->m_cMaxFrame = 30;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    break;


                case 85: // Fire explosion from the ground (effect14.pak)
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 90;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(((m_sViewPointX / 32) + 10) - sX) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist, 2);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT // EP's Crystal axe hit
                case 109: // EP's Crystal axe hit
#endif
                case 100: // MagicMissile is Flying
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 1, sDist, lPan);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 115: // EP's Staminar-Recovery
                case 148: // Critical heal
                case 168: // Mass heal
                case 186: // Regenerate
#endif
                case 101: // Heal
                case 111: // Staminar-Drain
                case 121: // Great Heal
                case 123: // Staminar-Recovery
                case 128: // Great-Staminar-Recovery
                    m_pEffectList[i]->m_cMaxFrame = 14;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 5, sDist, lPan);
                    break;

#ifndef DEF_EQUILIBRIUM_PROJECT
                case 122: // EP's Tremor so remove from here
#endif

                case 102: // CreateFood
                case 126: // Possession
                case 127: // Poison
                case 134: // DetectInvi
                case 136: // Cure
                case 142: // Confuse language
                case 152: // Polymorph
                case 153: // Mass-Poison
                case 162: // Confusion
                case 171: // Mass-Confusion
                    m_pEffectList[i]->m_cMaxFrame = 13;
                    m_pEffectList[i]->m_dwFrameTime = 120;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 5, sDist, lPan);
                    break;

                case 110: // Energy-Bolt
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 1, sDist, lPan);
                    break;

                case 112: // Recall
                case 131: // Summon
                case 132: // Invi
                    m_pEffectList[i]->m_cMaxFrame = 12;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 5, sDist, lPan);
                    break;

                case 113: // Defense-Shield
                case 144: // Great-Defense-Shield
                    m_pEffectList[i]->m_cMaxFrame = 12;
                    m_pEffectList[i]->m_dwFrameTime = 120;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 5, sDist, lPan);
                    break;

                case 114: // Celebrating Light
                    bAddNewEffect(69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -12);
                    bAddNewEffect(69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -9);
                    bAddNewEffect(69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -6);
                    bAddNewEffect(69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, -3);
                    bAddNewEffect(69 + (rand() % 2), dX * 32 + 20 - (rand() % 40), dY * 32 + 20 - (rand() % 40), 0, 0, 0);
                    delete m_pEffectList[i];
                    m_pEffectList[i] = 0;
                    break;

                case 120: // Fire Ball
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 1, sDist, lPan);
                    break;

                case 124: // Protect form N.M
                case 133: // Protection from Magic
                    bAddNewEffect(52, dX * 32, dY * 32, 0, 0, 0, 0);
                    delete m_pEffectList[i];
                    m_pEffectList[i] = 0;
                    break;

                case 125: // Hold Person
                case 135: // Paralyze
#ifdef DEF_EQUILIBRIUM_PROJECT
                case 198: // Medusa Kiss
#endif
                    bAddNewEffect(53, dX * 32, dY * 32, 0, 0, 0, 0);
                    delete m_pEffectList[i];
                    m_pEffectList[i] = 0;
                    break;

                case 130: // Fire Strike
                case 137: // Lightning Arrow
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 1, sDist, lPan);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 104: // Abaddon's fury
                case 105: // Ultimate Elixir
                case 122: // EP's Tremor
#else
                case 138: // Tremor.
#endif
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    SetCameraShakingEffect(sDist, 2);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);

                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    m_pEffectList[i]->m_cMaxFrame = 2;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 143: // Lightning
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 50;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_rX = 5 - (rand() % 10);
                    m_pEffectList[i]->m_rY = 5 - (rand() % 10);
                    m_pEffectList[i]->m_cMaxFrame = 7;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 40, sDist, lPan);
                    break;

                case 145: // ChillWind
                    m_pEffectList[i]->m_cMaxFrame = 2;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 147: // Triple-Energy-Bolt
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 108: // EP's Test spell
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 10;
                    m_pEffectList[i]->m_dwFrameTime = 60;
                    lPan = -(((m_sViewPointX / 32) + 10) - sX) * 1000;
                    PlaySound('E', 3, sDist, lPan);
                    break;

                case 118: // EP's Test spell
                case 107: // EP's Test spell
                case 138: // EP's prayer.
                case 175: // Trance		
                case 117: // EP's Wood Mantle
                case 158: // EP's Bloody Mantle
                case 187: // EP's Magic Mantle
                case 182: // Warrior's spirit
#endif
                case 150: // Berserk : Cirlcle 6 magic
                case 177: // Illusion-Movement
                case 180: // Illusion
                case 183: // Inhibition-Casting
                case 190: // Mass-Illusion
                case 195: // Mass-Illusion-Movement
                    m_pEffectList[i]->m_cMaxFrame = 11;
                    m_pEffectList[i]->m_dwFrameTime = 100;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 5, sDist, lPan);
                    break;

                case 151: // LightningBolt
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 50;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_rX = 5 - (rand() % 10);
                    m_pEffectList[i]->m_rY = 5 - (rand() % 10);
                    m_pEffectList[i]->m_cMaxFrame = 10;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 40, sDist, lPan);
                    break;

                case 156: // Mass-Ligtning-Arrow
                    m_pEffectList[i]->m_cMaxFrame = 3;
                    m_pEffectList[i]->m_dwFrameTime = 130;
                    break;

                case 157: // Ice-Strike
                    m_pEffectList[i]->m_cMaxFrame = 2;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 160: // Energy-Strike
                    m_pEffectList[i]->m_cMaxFrame = 7;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 178: // Divine revenge
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 1, sDist, lPan);
                    break;

                case 106: // Forge's Breath
#endif

                case 161: // Mass-Fire-Strike
                case 251: //
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 1, sDist, lPan);
                    break;

                case 163: // Mass-Chill-Wind
                    m_pEffectList[i]->m_cMaxFrame = 2;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 164: // worm-bite
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 4, sDist, lPan);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);

                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    bAddNewEffect(14, dX * 32 + (rand() % 120) - 60, dY * 32 + (rand() % 80) - 40, 0, 0, 0, 0);
                    m_pEffectList[i]->m_cMaxFrame = 1;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 165: // Absolute-Magic-Protection
                    m_pEffectList[i]->m_cMaxFrame = 21;
                    m_pEffectList[i]->m_dwFrameTime = 70;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 5, sDist, lPan);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 103: // Abaddon's Terror
                case 192: // Mass armor break
                    m_pEffectList[i]->m_cMaxFrame = 13;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 5, sDist / 2, lPan);
                    break;
#endif
                case 166: // Armor Break
                    m_pEffectList[i]->m_cMaxFrame = 13;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 5, sDist, lPan);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 167: // Scan
                    m_pEffectList[i]->m_cMaxFrame = 12;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 50, sDist / 2, lPan);
                    break;
#endif

                case 170: // Bloody-Shock-Wave
                    m_pEffectList[i]->m_cMaxFrame = 7;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    break;

                case 172: // Mass-Ice-Strike
                    m_pEffectList[i]->m_cMaxFrame = 2;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 193: // Mass Lightning-Strike
#endif
                case 174: // Lightning-Strike
                    m_pEffectList[i]->m_cMaxFrame = 5;
                    m_pEffectList[i]->m_dwFrameTime = 120;
                    break;

                case 176: // Cancellation
                    m_pEffectList[i]->m_cMaxFrame = 23;
                    m_pEffectList[i]->m_dwFrameTime = 60;
                    sDist = sDist / 32;
                    lPan = -(((m_sViewPointX / 32) + 10) - sX) * 1000;
                    PlaySound('E', 5, sDist, lPan);
                    break;

                case 181: // MS
                    m_pEffectList[i]->m_mX = dX * 32 + 300;
                    m_pEffectList[i]->m_mY = dY * 32 - 460;
                    m_pEffectList[i]->m_cMaxFrame = 10;
                    m_pEffectList[i]->m_dwFrameTime = 25;
                    break;

#ifndef DEF_EQUILIBRIUM_PROJECT
                case 182: // Mass-Magic-Missile
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 1, sDist, lPan);
                    break;
#endif

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 116: // EP's Peace spell
                case 184: // EP's Magic Drain
                    m_pEffectList[i]->m_cMaxFrame = 29;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    break;
#endif
                case 244: // Mass MagicMissile
                    //case 184:
                    m_pEffectList[i]->m_cMaxFrame = 29;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 185: // EP's Blizzard
#endif
                case 191: // Blizzard
                    m_pEffectList[i]->m_cMaxFrame = 7;
                    m_pEffectList[i]->m_dwFrameTime = 80;
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 188: // Entangle
#endif
                    //case 192: // Hero set Effect
                case 242: // Hero set Effect
                    m_pEffectList[i]->m_cMaxFrame = 30;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    break;

                    //case 193: // Hero set Effect
                case 243: // Hero set Effect
                    m_pEffectList[i]->m_cMaxFrame = 19;
                    m_pEffectList[i]->m_dwFrameTime = 18;
                    break;

                case 194: // Resurrection
                    m_pEffectList[i]->m_cMaxFrame = 30;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    break;

                case 196: // Earth-Shock-Wave
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 30;
                    m_pEffectList[i]->m_dwFrameTime = 25;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    SetCameraShakingEffect(sDist);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 197: // EP's Explosion
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 20;
                    m_pEffectList[i]->m_cDir = m_Misc.cCalcDirection(sX, sY, dX, dY);
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 1, sDist / 4, lPan);
                    // Add enormous Shacking
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    SetCameraShakingEffect(sDist, 4);
                    break;
#endif

                case 200: //
                case 201: //
                case 202: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 15;
                    m_pEffectList[i]->m_dwFrameTime = 25;
                    break;

                case 203: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 18;
                    m_pEffectList[i]->m_dwFrameTime = 70;
                    break;

                case 204: //
                case 205: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 12;
                    m_pEffectList[i]->m_dwFrameTime = 70;
                    break;

                case 206: //
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 3;
                    m_pEffectList[i]->m_dwFrameTime = 70;
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT // buts, ZzZz
                case 210: // Effect14.pak, explosion sous les pieds			
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 9;
                    m_pEffectList[i]->m_dwFrameTime = 25;
                    break;

                case 237: // Air Elemental Attack			
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 50;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_rX = 5 - (rand() % 10);
                    m_pEffectList[i]->m_rY = 5 - (rand() % 10);
                    m_pEffectList[i]->m_cMaxFrame = 10;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('E', 40, sDist, lPan);
                    break;

                case 238: // Ice Elemental Attack
                    m_pEffectList[i]->m_cMaxFrame = 2;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                case 239: // Ice Elemental OnMove
                    m_pEffectList[i]->m_cMaxFrame = 2;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    m_pEffectList[i]->m_iV1 = 80;
                    break;

                case 240: //Air Elemental lightning onMove
                    m_pEffectList[i]->m_rX = 5 - (rand() % 10);
                    m_pEffectList[i]->m_rY = 5 - (rand() % 10);
                    m_pEffectList[i]->m_cMaxFrame = 7;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    PlaySound('E', 40, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY);
                    break;

                case 241: // Fire Elemental explosion onMove
                    m_pEffectList[i]->m_mX = sX;
                    m_pEffectList[i]->m_mY = sY;
                    m_pEffectList[i]->m_cMaxFrame = 9;
                    m_pEffectList[i]->m_dwFrameTime = 40;
                    sAbsX = abs(320 - (sX - m_sViewPointX));
                    sAbsY = abs(240 - (sY - m_sViewPointY));
                    if (sAbsX > sAbsY) sDist = sAbsX;
                    else sDist = sAbsY;
                    sDist = sDist / 32;
                    lPan = -(320 - (sX - m_sViewPointX)) * 1000;
                    PlaySound('E', 4, sDist + 2, lPan);
                    break;

                case 245: // But Elvine
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32;
                    m_pEffectList[i]->m_cMaxFrame = 30;
                    m_pEffectList[i]->m_dwFrameTime = 121;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('C', 21, sDist, lPan);
                    break;

                case 246: // But Ares
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32;
                    m_pEffectList[i]->m_cMaxFrame = 30;
                    m_pEffectList[i]->m_dwFrameTime = 120;
                    lPan = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    PlaySound('C', 21, sDist, lPan);
                    break;

                case 247: // ZzZz
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32;
                    m_pEffectList[i]->m_cMaxFrame = 17;
                    m_pEffectList[i]->m_dwFrameTime = 200;
                    m_pEffectList[i]->m_mX3 = sDist;
                    m_pEffectList[i]->m_mY3 = -(((m_sViewPointX / 32) + 10) - dX) * 1000;
                    m_pEffectList[i]->m_iV1 = rand() % 35; // Frame to start sound
                    m_pEffectList[i]->m_cFrame = -rand() % 12; // Start with delay
                    break;
#endif

                case 250: //
                    m_pEffectList[i]->m_mX = sX * 32;
                    m_pEffectList[i]->m_mY = sY * 32 - 40;
                    m_pEffectList[i]->m_iErr = 0;
                    m_pEffectList[i]->m_cMaxFrame = 0;
                    m_pEffectList[i]->m_dwFrameTime = 10;
                    break;

                default:
                    delete m_pEffectList[i];
                    m_pEffectList[i] = 0;
                    break;
            }
            if (m_pEffectList[i] != 0)
            {
                m_pEffectList[i]->m_mX2 = m_pEffectList[i]->m_mX;
                m_pEffectList[i]->m_mY2 = m_pEffectList[i]->m_mY;
            }
            return;
        }
}

void CGame::DrawEffects()
{
    int i, dX, dY, iDvalue, tX, tY, rX, rY, rX2, rY2, rX3, rY3, rX4, rY4, rX5, rY5, iErr;
    char  cTempFrame;
    uint64_t dwTime = m_dwCurTime;
    short sObjectType = 0;
    char  cName[21] = {};
    int iStatus = 0;

    for (i = 0; i < DEF_MAXEFFECTS; i++)
        if ((m_pEffectList[i] != 0) && (m_pEffectList[i]->m_cFrame >= 0))
        {
            switch (m_pEffectList[i]->m_sType)
            {
                case 1: // Normal hit
                    if (m_pEffectList[i]->m_cFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[8]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 2: // Arrow flying
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 2;
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[7]->PutSpriteFast(dX, dY, cTempFrame, dwTime);
                    break;

                case 4: // gold
                    /* 1.5
                    if (m_pEffectList[i]->m_cFrame < 9) break;
                    cTempFrame = m_pEffectList[i]->m_cFrame - 9;
                    dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
                    dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
                    m_pEffectSpr[1]->PutSpriteFast(dX, dY-40, cTempFrame, dwTime);
                    */
                    break;

                case 5: // FireBall Fire Explosion
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    iDvalue = (cTempFrame - 8) * (-5);
                    if (cTempFrame < 7)
                        m_pEffectSpr[3]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    else m_pEffectSpr[3]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);
                    break;

                case 6:	 // Energy Bolt
                case 10: // Lightning Arrow
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    iDvalue = (cTempFrame - 7) * (-6);
                    if (cTempFrame < 6)
                        m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    else m_pEffectSpr[6]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    break;

                case 7: // Magic Missile Explosion
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    iDvalue = (cTempFrame - 4) * (-3);
                    if (cTempFrame < 4)
                        m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    else m_pEffectSpr[6]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    break;

                case 8: // Burst
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    cTempFrame = 4 - cTempFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 9: // Burst
                    cTempFrame = (rand() % 5);
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 11: // pt grenat
                    cTempFrame = (rand() % 5) + 5;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[11]->PutTransSprite2(dX, dY, cTempFrame, dwTime);
                    break;

                case 12: // Burst
                    cTempFrame = (rand() % 6) + 10;
                    if (cTempFrame < 0) break;
                    iDvalue = (m_pEffectList[i]->m_cFrame - 4) * (-3);
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    if (cTempFrame < 4)
                        m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    else //m_pEffectSpr[11]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    //
                        m_pEffectSpr[11]->PutTransSprite(dX, dY, cTempFrame, dwTime);
                    break;

                case 13:
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    if (cTempFrame < 13)
                    {
                        m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, 25 + (cTempFrame / 5), dwTime);
                    }
                    else
                    {
                        m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, (8 + cTempFrame), dwTime);
                    }
                    break;

                case 14: // Traces de pas (terrain sec)
                    if (m_pEffectList[i]->m_cFrame < 0) break;
                    dX = m_pEffectList[i]->m_mX - m_sViewPointX;
                    dY = m_pEffectList[i]->m_mY - m_sViewPointY;
                    m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, (28 + m_pEffectList[i]->m_cFrame), dwTime);
                    break;

                case 15: // petits nuages rouges
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = m_pEffectList[i]->m_mX - m_sViewPointX;
                    dY = m_pEffectList[i]->m_mY - m_sViewPointY;
                    m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, (33 + cTempFrame), dwTime);
                    break;

                case 16: //
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 0, dwTime);
                    break;

                case 17: //test
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = 39 + (rand() % 3) * 3 + (rand() % 3);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    dX = (m_pEffectList[i]->m_mX2) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY2) - m_sViewPointY;
                    m_pEffectSpr[11]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 18: //
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[18]->PutTransSprite70_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 20: // critical hit
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27: // Critical strike with a weapon
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[8]->PutTransSprite_NoColorKey(dX, dY, 1, dwTime);
                    break;

                case 30: // Mass-Fire-Strike
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[14]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 31: // Mass-Fire-Strike
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[15]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 32: // Trace de pas  (raining weather)
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame + 20;
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[11]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 33: //
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    iDvalue = 0;
                    m_pEffectSpr[19]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    break;

                case 34: // absent (220 et 351)
                    break;

                case 35:
                    if (m_pEffectList[i]->m_cFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    m_pEffectSpr[6]->PutTransSprite_NoColorKey(dX - 30, dY - 18, cTempFrame, dwTime);
                    break;

                case 36:
                    if (m_pEffectList[i]->m_cFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    m_pEffectSpr[97]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 40:
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[20]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime); // 20
                    break;

                case 41: // Large Type 1, 2, 3, 4
                case 42:
                case 43:
                case 44:
                case 45: // Small Type 1, 2
                case 46:
                    dX = (m_pEffectList[i]->m_sX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_sY) - m_sViewPointY;
                    m_pEffectSpr[21]->PutFadeSprite(dX, dY, 48, dwTime);
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    if ((8 * (m_pEffectList[i]->m_sType - 41) + cTempFrame) < (8 * (m_pEffectList[i]->m_sType - 41) + 7))
                    {
                        iDvalue = -8 * (6 - cTempFrame);
                        m_pEffectSpr[21]->PutTransSpriteRGB(dX, dY, 8 * (m_pEffectList[i]->m_sType - 41) + cTempFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    }
                    else
                    {
                        if ((cTempFrame - 5) >= 8) cTempFrame = ((cTempFrame - 5) - 8) + 5;
                        m_pEffectSpr[21]->PutSpriteFast(dX, dY, 8 * (m_pEffectList[i]->m_sType - 41) + (cTempFrame - 5), dwTime);
                    }
                    break;

                case 47:
                case 48:
                case 49: // Blizzard
                    dX = (m_pEffectList[i]->m_sX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_sY) - m_sViewPointY;
                    m_pEffectSpr[m_pEffectList[i]->m_sType - 1]->PutRevTransSprite(dX, dY, 0, dwTime);
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    //PutString(dX, dY, "*", Color(255,255,255));
                    if (cTempFrame < 7)
                    {
                        iDvalue = -8 * (6 - cTempFrame);
                        m_pEffectSpr[m_pEffectList[i]->m_sType - 1]->PutTransSpriteRGB(dX, dY, cTempFrame + 1, iDvalue, iDvalue, iDvalue, dwTime);
                    }
                    else
                    {
                        if (cTempFrame >= 8) cTempFrame = cTempFrame % 8;
                        m_pEffectSpr[m_pEffectList[i]->m_sType - 1]->PutSpriteFast(dX, dY, cTempFrame + 1, dwTime);
                    }
                    break;

                case 50:
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;

                    if (cTempFrame <= 6)
                    {
                        iDvalue = 0;
                        m_pEffectSpr[22]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);	// RGB2
                    }
                    else
                    {
                        iDvalue = -5 * (cTempFrame - 6);
                        m_pEffectSpr[22]->PutTransSpriteRGB(dX, dY, 6, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    }
                    break;

                case 51: //
                    cTempFrame = m_pEffectList[i]->m_cFrame + 11; //15
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[28]->PutTransSprite25(dX, dY, cTempFrame, dwTime); //20
                    break;


                case 52: // Protection Ring commente par siementec, a voir
                    /*			cTempFrame = m_pEffectList[i]->m_cFrame;
                        dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
                        dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
                        m_pEffectSpr[24]->PutTransSprite(dX, dY, cTempFrame, dwTime);
                    */
                    break;


                case 53: // Hold Twist
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    if (cTempFrame < 0) cTempFrame = 0;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[25]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime); //25
                    break;

                case 54: //  star twingkling (effect armes brillantes)
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) cTempFrame = 0;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[28]->PutTransSprite(dX, dY, cTempFrame, dwTime);
                    break;

                case 55: // star twingkling ???? unused
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) cTempFrame = 0;
                    dX = (m_pEffectList[i]->m_mX);
                    dY = (m_pEffectList[i]->m_mY);
                    m_pEffectSpr[28]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 56: // Mass-Chill-Wind
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) cTempFrame = 0;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[29]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 57:  // absent (220 et 351)
                    break;

                case 60:  //
                case 181: // MS
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    if (cTempFrame > 4)
                    {
                        cTempFrame = cTempFrame / 4;
                    }
                    if (cTempFrame >= 0)
                    {
                        dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                        dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                        m_pEffectSpr[31]->PutSpriteFast(dX, dY, 15 + cTempFrame, dwTime);
                        m_pEffectSpr[31]->PutTransSprite(dX, dY, cTempFrame, dwTime);
                    }
                    break;

                case 61: // Fire aura on ground (crueffect1, 1)
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[32]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 62: // MS strike
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    if (cTempFrame > 0)
                    {
                        cTempFrame = cTempFrame - 1;
                        dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                        dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                        m_pEffectSpr[31]->PutRevTransSprite(dX, dY, 20 + cTempFrame, dwTime, cTempFrame / 3);
                    }
                    break;

                case 63: // Fire explosion (crueffect1, 2)
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[33]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 64: // effet halo blancchatre
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[34]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 65: // 1 nuage de Fumée noire qui monte
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    cTempFrame = cTempFrame / 6;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[31]->PutRevTransSprite(dX, dY, 20 + cTempFrame, dwTime, cTempFrame >> 2);
                    break;

                case 66: // MS explodes on the ground
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[39]->PutRevTransSprite(dX, dY, cTempFrame, dwTime);
                    m_pEffectSpr[39]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 67: // MS fire with smoke
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    switch (rand() % 3)
                    {
                        case 0: m_pEffectSpr[0]->PutTransSprite25_NoColorKey(dX, dY + 20, 1, dwTime); break;
                        case 1: m_pEffectSpr[0]->PutTransSprite50_NoColorKey(dX, dY + 20, 1, dwTime); break;
                        case 2: m_pEffectSpr[0]->PutTransSprite70_NoColorKey(dX, dY + 20, 1, dwTime); break;
                    }
                    m_pEffectSpr[35]->PutTransSprite70_NoColorKey(dX, dY, cTempFrame / 3, dwTime);
                    break;

                case 68: // worm-bite
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    if (cTempFrame <= 11)
                    {
                        m_pEffectSpr[40]->PutSpriteFast(dX, dY, cTempFrame, dwTime);
                        m_pEffectSpr[41]->PutTransSprite50_NoColorKey(dX, dY, cTempFrame, dwTime);
                        m_pEffectSpr[44]->PutRevTransSprite(dX - 2, dY - 3, cTempFrame, dwTime);
                        m_pEffectSpr[44]->PutTransSprite_NoColorKey(dX - 4, dY - 3, cTempFrame, dwTime);
                    }
                    else
                    {
                        switch (cTempFrame)
                        {
                            case 12:
                            case 13:
                            case 14: m_pEffectSpr[40]->PutSpriteFast(dX, dY, 11, dwTime); break;
                            case 15: m_pEffectSpr[40]->PutTransSprite70_NoColorKey(dX, dY, 11, dwTime); break;
                            case 16: m_pEffectSpr[40]->PutTransSprite50_NoColorKey(dX, dY, 11, dwTime); break;
                            case 17: m_pEffectSpr[40]->PutTransSprite25_NoColorKey(dX, dY, 11, dwTime); break;
                        }
                    }
                    break;

                case 69: // identique au cas 70
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[42]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 70: // identique au cas 69
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[43]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 71: // absent v220 et v351
                    break;

                case 72: // Blizzard
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    if (cTempFrame <= 8)
                    {
                        iDvalue = 0;
                        m_pEffectSpr[51]->PutTransSpriteRGB(dX, dY, cTempFrame, iDvalue, iDvalue, iDvalue, dwTime);
                    }
                    else
                    {
                        iDvalue = -1 * (cTempFrame - 8);
                        m_pEffectSpr[51]->PutTransSpriteRGB(dX, dY, 8, iDvalue, iDvalue, iDvalue, dwTime);	// RGB2
                    }
                    break;

                case 73: // absent v220 et v351
                case 74: // absent v220 et v351
                case 75: // absent v220 et v351
                case 76: // absent v220 et v351
                case 77: // absent v220 et v351
                    break;

                case 80:
                case 196: // Earth-Shock-Wave
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[91]->PutSpriteFast(dX, dY, cTempFrame, dwTime); //Nbe d'arguments modifiés ds la 351....
                    m_pEffectSpr[92]->PutTransSprite(dX, dY, cTempFrame, dwTime);
                    break;

                case 81: // StormBlade
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    m_pEffectSpr[100]->PutTransSprite_NoColorKey(dX + 70, dY + 70, cTempFrame, dwTime);
                    break;

                case 82: // Gate (apocalypse)
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    m_pEffectSpr[101]->PutTransSprite_NoColorKey(320, 480, cTempFrame, dwTime);
                    break;

                case 85: // Fire explosion from the ground (effect14.pak)
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    if (cTempFrame < 10)
                        m_pEffectSpr[108]->PutTransSprite_NoColorKey(dX + 30, dY + 35, cTempFrame, dwTime);
                    if (cTempFrame >= 7)
                        m_pEffectSpr[109]->PutTransSprite_NoColorKey(dX + 5, dY + 5, cTempFrame - 7, dwTime);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 109: // EP's Crystal axe hit
#endif
                case 100: // Magic Missile
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 0, dwTime);
                    break;


#ifdef DEF_EQUILIBRIUM_PROJECT
                case 148: // Critical heal
                case 168: // Mass heal
                case 186: // Regenerate
#endif

                case 101: // Heal
                case 121: // Great-Heal
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-5);
                    m_pEffectSpr[50]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 102: // Create Food
                case 124: // Protection from N.M
                case 125: // Hold-Person
                case 126: // Possession
                case 127: // Poison
                case 133: // Protect-From-Magic
                case 134: // Detect-Invisibility
                case 135: // Paralyze
                case 136: // Cure
                case 142: // Confuse Language
                case 152: // Polymorph
                case 153: // Mass-Poison
                case 162: // Confusion
                case 171: // Mass-Confusion

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 198: // Medusa Kiss
#endif
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-5);
                    if (cTempFrame < 5)
                        m_pEffectSpr[4]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    else m_pEffectSpr[4]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    break;

                case 110: // Energy-Bolt
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY, 2 + (rand() % 4), dwTime);
                    break;

                case 111: // Staminar Drain
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-5);
                    m_pEffectSpr[49]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 112: // Recall
                case 131: // Summon-Creature
                case 132: // Invisibility
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-5);
                    m_pEffectSpr[52]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 113: // Defense Shield
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-5);
                    if (cTempFrame < 6)
                        m_pEffectSpr[62]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    else m_pEffectSpr[62]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 178: // Divine revenge			
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[5]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 106: // Forge's Breath
#endif
                case 120: // Fire Ball
                case 130: // Fire Strike
                case 161: // Mass-Fire-Strike
                case 251: //
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[5]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 122: // Absent v220 et 351
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 115: // EP's Staminar-Recovery
#endif
                case 123: // Staminar-Recovery
                case 128: // Great-Staminar-Recovery
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-5);
                    m_pEffectSpr[56]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 137: // Lightning Arrow
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    tX = (m_pEffectList[i]->m_mX2) - m_sViewPointX;
                    tY = (m_pEffectList[i]->m_mY2) - m_sViewPointY;
                    iErr = 0;
                    m_Misc.GetPoint(dX, dY, tX, tY, &rX, &rY, &iErr, 15);
                    m_Misc.GetPoint(dX, dY, tX, tY, &rX2, &rY2, &iErr, 30);
                    m_Misc.GetPoint(dX, dY, tX, tY, &rX3, &rY3, &iErr, 45);
                    m_Misc.GetPoint(dX, dY, tX, tY, &rX4, &rY4, &iErr, 60);
                    m_Misc.GetPoint(dX, dY, tX, tY, &rX5, &rY5, &iErr, 75);
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[10]->PutTransSprite25_NoColorKey(rX5, rY5, cTempFrame, dwTime);
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[10]->PutTransSprite25_NoColorKey(rX4, rY4, cTempFrame, dwTime);
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[10]->PutTransSprite50_NoColorKey(rX3, rY3, cTempFrame, dwTime);
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[10]->PutTransSprite50_NoColorKey(rX2, rY2, cTempFrame, dwTime);
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[10]->PutTransSprite70_NoColorKey(rX, rY, cTempFrame, dwTime);
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[10]->PutTransSprite(dX, dY, cTempFrame, dwTime);
                    break;

                case 143: // Lightning
                    _DrawThunderEffect(m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY - 800,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX, m_pEffectList[i]->m_rY, 1);
                    _DrawThunderEffect(m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY - 800,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX + 4, m_pEffectList[i]->m_rY + 2, 2);
                    _DrawThunderEffect(m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY - 800,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX - 2, m_pEffectList[i]->m_rY - 2, 2);
                    break;

                case 144: // Great-Defense-Shield
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-5);
                    if (cTempFrame < 9)
                        m_pEffectSpr[63]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    else m_pEffectSpr[63]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    break;

                case 151: // Lightning Bolt
                    _DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX, m_pEffectList[i]->m_rY, 1);

                    _DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX + 2, m_pEffectList[i]->m_rY - 2, 2);

                    _DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX - 2, m_pEffectList[i]->m_rY - 2, 2);
                    break;

                case 165: // Absolute-Magic-Protect
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY; // 53 = APFM buble
                    m_pEffectSpr[53]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 103: // Abaddon's Terror
                case 192: // Mass armor break
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[55]->PutRevTransSprite(dX, dY + 35, m_pEffectList[i]->m_cFrame, dwTime);
                    m_pEffectSpr[54]->PutTransSprite50(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);

                    m_pEffectSpr[55]->PutRevTransSprite(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    m_pEffectSpr[54]->PutTransSprite50(dX, dY - 35, m_pEffectList[i]->m_cFrame, dwTime);

                    m_pEffectSpr[55]->PutRevTransSprite(dX - 30, dY + 20, m_pEffectList[i]->m_cFrame, dwTime);
                    m_pEffectSpr[54]->PutTransSprite50(dX - 30, dY - 15, m_pEffectList[i]->m_cFrame, dwTime);

                    m_pEffectSpr[55]->PutRevTransSprite(dX - 15, dY + 60, m_pEffectList[i]->m_cFrame, dwTime);
                    m_pEffectSpr[54]->PutTransSprite50(dX - 15, dY + 25, m_pEffectList[i]->m_cFrame, dwTime);

                    m_pEffectSpr[55]->PutRevTransSprite(dX + 15, dY + 60, m_pEffectList[i]->m_cFrame, dwTime);
                    m_pEffectSpr[54]->PutTransSprite50(dX + 15, dY + 25, m_pEffectList[i]->m_cFrame, dwTime);

                    m_pEffectSpr[55]->PutRevTransSprite(dX + 30, dY + 20, m_pEffectList[i]->m_cFrame, dwTime);
                    m_pEffectSpr[54]->PutTransSprite50(dX + 30, dY - 15, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

#endif
                case 166: // Armor-Break
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[55]->PutRevTransSprite(dX, dY + 35, m_pEffectList[i]->m_cFrame, dwTime);
                    m_pEffectSpr[54]->PutTransSprite50(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 167: // Scan
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pMapData->bGetOwner(m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY
                        , cName, &sObjectType, &iStatus, &m_wCommObjectID);
                    m_pEffectSpr[57]->PutTransSprite_NoColorKey(dX + 110, dY + 110 - _iAttackerHeight[sObjectType], m_pEffectList[i]->m_cFrame, dwTime);
                    break;
#endif

                case 176: // Cancellation
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[90]->PutTransSprite_NoColorKey(dX + 50, dY + 85, cTempFrame, dwTime);
                    break;

                case 177: // Illusion-Movement
                case 180: // Illusion
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-3);
                    if (cTempFrame < 9)	m_pEffectSpr[60]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    else m_pEffectSpr[60]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    break;

#ifndef DEF_EQUILIBRIUM_PROJECT
                case 182: //Mass-Magic-Missile
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[98]->PutTransSprite(dX, dY, cTempFrame, dwTime, 0);
                    break;
#endif

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 107: // EP's Test spell		
                case 117: // EP's Wood Mantle
                case 158: // EP's Bloody Mantle
                case 187: // EP's Magic Mantle
                case 118: // EP's Test spell
#endif
                case 183: // Inhibition-Casting
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-3);
                    if (cTempFrame < 9) m_pEffectSpr[94]->PutTransSprite_NoColorKey(dX, dY + 40, m_pEffectList[i]->m_cFrame, dwTime);
                    else m_pEffectSpr[94]->PutTransSpriteRGB(dX, dY + 40, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 116: // EP's Peace spell
                case 184: // EP's Magic Drain
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[96]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;
#endif
                case 244: // Mass MagicMissile
                    //case 184:
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = m_pEffectList[i]->m_mX - m_sViewPointX;
                    dY = m_pEffectList[i]->m_mY - m_sViewPointY;
                    m_pEffectSpr[96]->PutTransSprite(dX, dY, m_pEffectList[i]->m_cFrame, dwTime, 0);
                    break;

                case 190: // Mass-Illusion
                case 195: // Mass-Illusion-Movement
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    iDvalue = (cTempFrame - 5) * (-3);
                    if (cTempFrame < 9) m_pEffectSpr[61]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    else m_pEffectSpr[61]->PutTransSpriteRGB(dX, dY, m_pEffectList[i]->m_cFrame, iDvalue, iDvalue, iDvalue, dwTime); // RGB2
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 188: // Entangle
#endif
                    //case 192: // Mage Hero set effect
                case 242:
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[87]->PutTransSprite_NoColorKey(dX + 50, dY + 57, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT

                case 108: // EP's Test spell
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    //m_pEffectSpr[111]->PutTransSprite_NoColorKey(dX, dY+10, m_pEffectList[i]->m_cFrame, dwTime);
                    m_pEffectSpr[110]->PutTransSprite(dX, dY + 20, m_pEffectList[i]->m_cFrame, dwTime, 0);
                    break;

                    //case 138: // EP's Prayer (added effect in DrawEffectLigths as original Berserk)
                    //case 175: // Trance      (added effect in DrawEffectLigths as original Berserk)
                case 182: // Warrior's spirit
#endif
                case 243:
                    //case 193: // War Hero set effect
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[88]->PutTransSprite_NoColorKey(dX + 65, dY + 80, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 194: // Resurrection
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[99]->PutTransSprite(dX, dY, m_pEffectList[i]->m_cFrame, dwTime, 0);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 197: // Explosion
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = (m_pEffectList[i]->m_cDir - 1) * 4 + (rand() % 4);
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[5]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;
#endif


                case 200: // shotstar fall on ground
                    dX = m_pEffectList[i]->m_mX;
                    dY = m_pEffectList[i]->m_mY;
                    m_pEffectSpr[133]->PutTransSprite_NoColorKey(dX, dY, (rand() % 15), dwTime);
                    break;

                case 201: // shotstar fall on ground
                    dX = m_pEffectList[i]->m_mX;
                    dY = m_pEffectList[i]->m_mY;
                    m_pEffectSpr[134]->PutTransSprite_NoColorKey(dX, dY, (rand() % 15), dwTime);
                    break;

                case 202: // shotstar fall on ground
                    dX = m_pEffectList[i]->m_mX;
                    dY = m_pEffectList[i]->m_mY;
                    m_pEffectSpr[135]->PutTransSprite_NoColorKey(dX, dY, (rand() % 15), dwTime);
                    break;

                case 203: // explosion feu apoc
                    dX = m_pEffectList[i]->m_mX;
                    dY = m_pEffectList[i]->m_mY;
                    m_pEffectSpr[136]->PutTransSprite_NoColorKey(dX, dY, (rand() % 18), dwTime);
                    break;

                case 204: // Faille oblique
                    dX = m_pEffectList[i]->m_mX;
                    dY = m_pEffectList[i]->m_mY;
                    m_pEffectSpr[137]->PutTransSprite_NoColorKey(dX, dY, (rand() % 12), dwTime);
                    break;

                case 205: // Faille horizontale
                    dX = m_pEffectList[i]->m_mX;
                    dY = m_pEffectList[i]->m_mY;
                    m_pEffectSpr[138]->PutTransSprite_NoColorKey(dX, dY, (rand() % 12), dwTime);
                    break;

                case 206: // steams
                    dX = m_pEffectList[i]->m_mX;
                    dY = m_pEffectList[i]->m_mY;
                    m_pEffectSpr[139]->PutTransSprite_NoColorKey(dX, dY, (rand() % 20), dwTime);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT // Buts, ZzZz
                case 210: // Effect14.pak, explosion sous les pieds	
                    dX = m_pEffectList[i]->m_mX;
                    dY = m_pEffectList[i]->m_mY;
                    m_pEffectSpr[108]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 237: // Air Elemental Attack
                    _DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX, m_pEffectList[i]->m_rY, 1);

                    _DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX + 2, m_pEffectList[i]->m_rY - 2, 2);

                    _DrawThunderEffect(m_pEffectList[i]->m_mX - m_sViewPointX, m_pEffectList[i]->m_mY - m_sViewPointY,
                        m_pEffectList[i]->m_dX * 32 - m_sViewPointX, m_pEffectList[i]->m_dY * 32 - m_sViewPointY,
                        m_pEffectList[i]->m_rX - 2, m_pEffectList[i]->m_rY - 2, 2);
                    break;

                case 238: // Ice Elemental OnAttack	
                case 239: // Ice Elemental OnMove			
                    break;

                case 240: // Air Elemental lightning onMove
                    _DrawThunderEffect(m_pEffectList[i]->m_dX, 0, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY
                        , m_pEffectList[i]->m_rX, m_pEffectList[i]->m_rY, 1);
                    _DrawThunderEffect(m_pEffectList[i]->m_dX, 0, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY
                        , m_pEffectList[i]->m_rX + 4, m_pEffectList[i]->m_rY + 2, 2);
                    _DrawThunderEffect(m_pEffectList[i]->m_dX, 0, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY
                        , m_pEffectList[i]->m_rX - 2, m_pEffectList[i]->m_rY - 2, 2);
                    break;

                case 241: // Fire Elemental explosion onMove
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    if (cTempFrame < 0) break;
                    m_pEffectSpr[15]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    break;

                case 245: // But Elvine
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[64]->PutTransSprite_NoColorKey(dX + 50, dY - 80, m_pEffectList[i]->m_cFrame % 3, dwTime);
                    break;

                case 246: // But Ares
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[65]->PutTransSprite_NoColorKey(dX + 50, dY - 80, m_pEffectList[i]->m_cFrame % 3, dwTime);
                    break;

                case 247: // ZzZz
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[85]->PutTransSprite_NoColorKey(dX + 50, dY + 30, m_pEffectList[i]->m_cFrame, dwTime);
                    break;
#endif

                case 250: // Gate (round one)
                    dX = m_pEffectList[i]->m_mX - m_sViewPointX;
                    dY = m_pEffectList[i]->m_mY - m_sViewPointY;
                    m_pEffectSpr[103]->PutTransSprite_NoColorKey(dX, dY, (rand() % 3), dwTime);
                    break;

                case 252: // burst (lisgt salmon color)
                    dX = m_pEffectList[i]->m_mX - m_sViewPointX;
                    dY = m_pEffectList[i]->m_mY - m_sViewPointY;
                    m_pEffectSpr[104]->PutTransSprite_NoColorKey(dX, dY, (rand() % 3), dwTime);
                    break;
            }
        }
}



void CGame::DrawEffectLights()
{
    int i, dX, dY, iDvalue;
    uint64_t dwTime = m_dwCurTime;
    char  cTempFrame;
    for (i = 0; i < DEF_MAXEFFECTS; i++)
        if (m_pEffectList[i] != 0)
        {
            switch (m_pEffectList[i]->m_sType)
            {
                case 1:
                    break;

                case 2:
                    break;

                case 4:
                    break;

                case 5:	// Fire Explosion
                    if (m_pEffectList[i]->m_cFrame >= 0)
                    {
                        dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                        dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                        iDvalue = (m_pEffectList[i]->m_cFrame - 7) * (-1);
                        if (m_pEffectList[i]->m_cFrame < 6)
                            m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY + 30, 1, dwTime);
                        else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
                    }
                    break;

                case 6:	 // Energy Bolt
                case 10: // Lightning Arrow
                    if (m_pEffectList[i]->m_cFrame >= 0)
                    {
                        dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                        dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                        iDvalue = (m_pEffectList[i]->m_cFrame - 9) * (-1);
                        if (m_pEffectList[i]->m_cFrame < 8)
                            m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY + 30, 1, dwTime);
                        else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
                    }
                    break;
                case 7: // Magic Missile Explosion
                    if (m_pEffectList[i]->m_cFrame >= 0)
                    {
                        dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                        dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                        iDvalue = (m_pEffectList[i]->m_cFrame - 2) * (-1);
                        if (m_pEffectList[i]->m_cFrame < 2)
                            m_pEffectSpr[0]->PutTransSprite_NoColorKey(dX, dY + 30, 1, dwTime);
                        else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
                    }
                    break;

                case 16:
                case 61:
                case 66:
                case 100:
                case 110:
                case 120:
                case 130:
                case 137: // Lightning arrow
                    //case 165: // APFM fixed green light
                        // Light on ground below the flying effect
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    iDvalue = -5;
                    m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY + 30, 1, iDvalue, iDvalue, iDvalue, dwTime);
                    break;

                case 69:
                case 70:
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[0]->PutTransSprite25(dX, dY + 30, 1, dwTime);
                    break;

                case 33: //
                    /*
                    if (m_pEffectList[i]->m_cFrame >= 0) {
                        dX  = (m_pEffectList[i]->m_mX)  - m_sViewPointX;
                        dY  = (m_pEffectList[i]->m_mY)  - m_sViewPointY;
                        iDvalue = (m_pEffectList[i]->m_cFrame - 9)*(-1);
                        if (m_pEffectList[i]->m_cFrame < 8)
                             m_pEffectSpr[0]->PutTransSprite(dX, dY, 1, dwTime);
                        else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY, 1, iDvalue, iDvalue, iDvalue, dwTime);
                    }
                    */
                    break;

                case 40: //
                case 56:
                    if (m_pEffectList[i]->m_cFrame >= 0)
                    {
                        dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                        dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                        iDvalue = (m_pEffectList[i]->m_cFrame - 7) * (-1);
                        if (m_pEffectList[i]->m_cFrame < 6)
                            m_pEffectSpr[0]->PutTransSprite(dX, dY, 1, dwTime);
                        else m_pEffectSpr[0]->PutTransSpriteRGB(dX, dY, 1, iDvalue, iDvalue, iDvalue, dwTime);
                    }
                    break;

                case 52: // Protection Ring
                    if (m_pEffectList[i]->m_cFrame >= 0)
                    {
                        dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                        dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                        m_pEffectSpr[24]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    }
                    break;

                case 57:
                    if (m_pEffectList[i]->m_cFrame >= 0)
                    {
                        dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                        dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                        m_pEffectSpr[30]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    }
                    break;

                case 73:
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[74]->PutTransSprite(dX, dY - 34, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 74:
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[75]->PutTransSprite(dX, dY + 35, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 75: // Icegolem
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[76]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 76:// Icegolem
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[77]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 77:// Icegolem
                    dX = (m_pEffectList[i]->m_mX) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_mY) - m_sViewPointY;
                    m_pEffectSpr[78]->PutTransSprite25(dX + m_pEffectList[i]->m_dX * m_pEffectList[i]->m_cFrame, dY + m_pEffectList[i]->m_dY * m_pEffectList[i]->m_cFrame, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 138: // Prayer
                case 175: // Trance
#endif
                case 150: // Berserk : Cirlcle 6 magic
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[58]->PutTransSprite_NoColorKey(dX, dY, m_pEffectList[i]->m_cFrame, dwTime);
                    break;

                case 180: // Ilusion
                case 190: // Mass Illusion
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[59]->PutTransSprite_NoColorKey(dX, dY, cTempFrame, dwTime);
                    //if( cTempFrame < 9 ) m_pEffectSpr[59]->PutTransSprite_NoColorKey( dX, dY, cTempFrame, dwTime );
                    //else m_pEffectSpr[59]->PutSpriteFast( dX, dY, cTempFrame, dwTime );
                    break;

                case 177: // Illusion mvt
                case 195: // Mass Illusion mvt
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[102]->PutTransSprite_NoColorKey(dX, dY + 30, cTempFrame, dwTime);
                    break;

                case 183: // Inhibition casting
                    cTempFrame = m_pEffectList[i]->m_cFrame;
                    dX = (m_pEffectList[i]->m_dX * 32) - m_sViewPointX;
                    dY = (m_pEffectList[i]->m_dY * 32) - m_sViewPointY;
                    m_pEffectSpr[95]->PutTransSprite_NoColorKey(dX, dY + 40, cTempFrame, dwTime);
                    break;
            }
        }
}

void CGame::_LoadShopMenuContents(char cType)
{
    char cFileName[255] = {}, cTemp[255] = {};
    HANDLE hFile;
    FILE * pFile;
    uint32_t  dwFileSize;
    char * pBuffer;

    ZeroMemory(cTemp, sizeof(cTemp));
    ZeroMemory(cFileName, sizeof(cFileName));
    wsprintfA(cTemp, "contents%d", cType);
    strcat(cFileName, "contents");
    strcat(cFileName, "\\");
    strcat(cFileName, "\\");
    strcat(cFileName, cTemp);
    strcat(cFileName, ".txt");

    hFile = CreateFileA(cFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwFileSize = GetFileSize(hFile, 0);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

    pFile = fopen(cFileName, "rt");
    if (pFile == 0) return;
    else
    {
        pBuffer = new char[dwFileSize + 1];
        ZeroMemory(pBuffer, dwFileSize + 1);
        fread(pBuffer, dwFileSize, 1, pFile);

        __bDecodeContentsAndBuildItemForSaleList(pBuffer);
        delete[] pBuffer;
    }
    fclose(pFile);
}

bool CGame::__bDecodeContentsAndBuildItemForSaleList(char * pBuffer)
{
    char * pContents, * token;
    char seps[] = "= ,\t\n";
    char cReadModeA = 0;
    char cReadModeB = 0;
    int  iItemForSaleListIndex = 0;
    class CStrTok * pStrTok;

    pContents = pBuffer;

    pStrTok = new class CStrTok(pContents, seps);
    token = pStrTok->pGet();
    while (token != 0)
    {
        if (cReadModeA != 0)
        {
            //
            switch (cReadModeA)
            {
                case 1:
                    switch (cReadModeB)
                    {
                        case 1:
                            ZeroMemory(m_pItemForSaleList[iItemForSaleListIndex]->m_cName, sizeof(m_pItemForSaleList[iItemForSaleListIndex]->m_cName));
                            memcpy(m_pItemForSaleList[iItemForSaleListIndex]->m_cName, token, strlen(token));
                            cReadModeB = 2;
                            break;
                        case 2:	// m_cItemType
                            m_pItemForSaleList[iItemForSaleListIndex]->m_cItemType = atoi(token);
                            cReadModeB = 3;
                            break;
                        case 3: // m_cEquipPos
                            m_pItemForSaleList[iItemForSaleListIndex]->m_cEquipPos = atoi(token);
                            cReadModeB = 4;
                            break;
                        case 4: // m_sItemEffectType
                            //m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectType = atoi(token);
                            cReadModeB = 5;
                            break;
                        case 5:	// m_sItemEffectValue1
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue1 = atoi(token);
                            cReadModeB = 6;
                            break;
                        case 6: // m_sItemEffectValue2
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue2 = atoi(token);
                            cReadModeB = 7;
                            break;
                        case 7: // m_sItemEffectValue3
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue3 = atoi(token);
                            cReadModeB = 8;
                            break;
                        case 8: // m_sItemEffectValue4
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue4 = atoi(token);
                            cReadModeB = 9;
                            break;
                        case 9: // m_sItemEffectValue5
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue5 = atoi(token);
                            cReadModeB = 10;
                            break;
                        case 10: // m_sItemEffectValue6
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sItemEffectValue6 = atoi(token);
                            cReadModeB = 11;
                            break;
                        case 11: // m_wMaxLifeSpan
                            m_pItemForSaleList[iItemForSaleListIndex]->m_wMaxLifeSpan = (uint16_t)atoi(token);
                            cReadModeB = 12;
                            break;
                        case 12: // m_sMaxFixCount
                            //m_pItemForSaleList[iItemForSaleListIndex]->m_sMaxFixCount = atoi(token);
                            cReadModeB = 13;
                            break;
                        case 13: // m_sSprite
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sSprite = atoi(token);
                            cReadModeB = 14;
                            break;
                        case 14: // m_sSpriteFrame
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sSpriteFrame = atoi(token);
                            cReadModeB = 15;
                            break;
                        case 15: // m_wPrice
                            m_pItemForSaleList[iItemForSaleListIndex]->m_wPrice = atoi(token);
                            cReadModeB = 16;
                            break;
                        case 16: // m_wWeight
                            m_pItemForSaleList[iItemForSaleListIndex]->m_wWeight = atoi(token);
                            cReadModeB = 17;
                            break;
                        case 17: // Appr Value
                            //m_pItemForSaleList[iItemForSaleListIndex]->m_cApprValue = atoi(token);
                            cReadModeB = 18;
                            break;
                        case 18: // m_cSpeed
                            m_pItemForSaleList[iItemForSaleListIndex]->m_cSpeed = atoi(token);
                            cReadModeB = 19;
                            break;
                        case 19: // Level Limit
                            m_pItemForSaleList[iItemForSaleListIndex]->m_sLevelLimit = atoi(token);
                            m_pItemForSaleList[iItemForSaleListIndex]->m_dwCount = 1;
                            cReadModeA = 0;
                            cReadModeB = 0;
                            iItemForSaleListIndex++;
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
        else
        {
            if (memcmp(token, "ItemForSale", 4) == 0)
            {
                if (iItemForSaleListIndex >= DEF_MAXMENUITEMS)
                {
                    delete pStrTok;
                    return false;
                }
                cReadModeA = 1;
                cReadModeB = 1;
                m_pItemForSaleList[iItemForSaleListIndex] = new class CItem;
            }
        }
        token = pStrTok->pGet();
    }
    delete pStrTok;
    if ((cReadModeA != 0) || (cReadModeB != 0)) return false;
    return true;
}


static char __cSpace[] = { 8,8,8,8,8,8,8,8,8,8, 8,8,8,8,8, 8,6,8,7,8,8,9,10,9,7, 8,8,8,8,8, 8,8,
                          15,16,12,17,14,15,14,16,10,13, 19,10,17,17,15,14,15,16,13,17, 16,16,20,17,16,14,
                          8,8,8,8,8,8,	8,6,7,8,7,7,7,7,4,7,7,  4,11,7,8,8,7,8,6,5,8,9,14,8,9,8, 8,8,8,8,
                          8,8,8,8,8,8,8 };
void CGame::PutString_SprFont(int iX, int iY, std::string pStr, short sR, short sG, short sB)
{
    int iXpos;
    uint32_t iCnt;
    uint64_t dwTime = G_dwGlobalTime;

    iXpos = iX;
    for (iCnt = 0; iCnt < pStr.length(); iCnt++)
    {
        if ((pStr[iCnt] >= 33) && (pStr[iCnt] <= 122))
        {
            m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteRGB(iXpos + 1, iY, pStr[iCnt] - 33, sR + 11, sG + 7, sB + 6, dwTime);
            if ((sR == 0) && (sG == 0) && (sB == 0))
                m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteFast(iXpos, iY, pStr[iCnt] - 33, dwTime);
            else m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteRGB(iXpos, iY, pStr[iCnt] - 33, sR, sG, sB, dwTime);
            iXpos += __cSpace[pStr[iCnt] - 33];
        }
        else iXpos += 5;
    }
}

void CGame::PutString_SprFont2(int iX, int iY, std::string pStr, short sR, short sG, short sB)
{
    int iXpos;
    uint32_t iCnt;
    uint64_t dwTime = G_dwGlobalTime;

    iXpos = iX;
    for (iCnt = 0; iCnt < pStr.length(); iCnt++)
    {
        if ((pStr[iCnt] >= 33) && (pStr[iCnt] <= 122))
        {
            m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteFast(iXpos + 1, iY, pStr[iCnt] - 33, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteFast(iXpos + 1, iY + 1, pStr[iCnt] - 33, dwTime);
            if ((sR == 0) && (sG == 0) && (sB == 0))
                m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteFast(iXpos, iY, pStr[iCnt] - 33, dwTime);
            else m_pSprite[DEF_SPRID_INTERFACE_FONT1]->PutSpriteRGB(iXpos, iY, pStr[iCnt] - 33, sR, sG, sB, dwTime);
            iXpos += __cSpace[pStr[iCnt] - 33];
        }
        else iXpos += 5;
    }
}

void CGame::PutString_SprFont3(int iX, int iY, std::string pStr, short sR, short sG, short sB, bool bTrans, int iType)
{
    int iXpos, iAdd;
    uint32_t iCnt;
    uint64_t dwTime = G_dwGlobalTime;

    if (iType != -1)
    {
        iAdd = 95 * iType;
        iXpos = iX;
        for (iCnt = 0; iCnt < pStr.length(); iCnt++)
        {
            if ((pStr[iCnt] >= 32) && (pStr[iCnt] <= 126))
            {

                if (bTrans == false)
                {
                    m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutSpriteFast(iXpos, iY + 1, pStr[iCnt] - 32 + iAdd, dwTime);
                    m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutSpriteFast(iXpos + 1, iY + 1, pStr[iCnt] - 32 + iAdd, dwTime);
                    if ((sR == 0) && (sG == 0) && (sB == 0))
                        m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutSpriteFast(iXpos, iY, pStr[iCnt] - 32 + iAdd, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutSpriteRGB(iXpos, iY, pStr[iCnt] - 32 + iAdd, sR, sG, sB, dwTime);

                }
                else m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->PutTransSpriteRGB(iXpos, iY, pStr[iCnt] - 32 + iAdd, sR, sG, sB, dwTime);

                iXpos += (m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS2]->m_stBrush[pStr[iCnt] - 32 + iAdd].szx);
            }
            else iXpos += 5;
        }
    }
    else
    {
        iAdd = 0;
        iXpos = iX;
        for (iCnt = 0; iCnt < pStr.length(); iCnt++)
        {
            if ((pStr[iCnt] >= 32) && (pStr[iCnt] <= 126))
            {

                if (bTrans == false)
                {
                    m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutSpriteFast(iXpos, iY + 1, pStr[iCnt] - 32 + iAdd, dwTime);
                    m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutSpriteFast(iXpos + 1, iY + 1, pStr[iCnt] - 32 + iAdd, dwTime);
                    if ((sR == 0) && (sG == 0) && (sB == 0))
                        m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutSpriteFast(iXpos, iY, pStr[iCnt] - 32 + iAdd, dwTime);
                    else m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutSpriteRGB(iXpos, iY, pStr[iCnt] - 32 + iAdd, sR, sG, sB, dwTime);

                }
                else m_pSprite[DEF_SPRID_INTERFACE_FONT2]->PutTransSpriteRGB(iXpos, iY, pStr[iCnt] - 32 + iAdd, sR, sG, sB, dwTime);

                iXpos += (m_pSprite[DEF_SPRID_INTERFACE_FONT2]->m_stBrush[pStr[iCnt] - 32 + iAdd].szx);
            }
            else iXpos += 5;
        }
    }
}

static char __cSpace2[] = { 6,4,6,6,6,6,6,6,6,6,6 }; //{8,6,9,8,8,9,8,8,8,8};
void CGame::PutString_SprNum(int iX, int iY, std::string pStr, short sR, short sG, short sB)
{
    int iXpos;
    unsigned char iCnt;
    uint64_t dwTime = G_dwGlobalTime;
    //uint16_t  wR, wG, wB;
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(sR, sG, sB), &wR, &wG, &wB);
    iXpos = iX;
    for (iCnt = 0; iCnt < pStr.length(); iCnt++)
    {
        if ((pStr[iCnt] >= 0x30) && (pStr[iCnt] <= 0x39))
        {
            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSprite(iXpos + 2, iY, pStr[iCnt] - 0x30 + 6, dwTime);
            m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSprite(iXpos + 1, iY + 1, pStr[iCnt] - 0x30 + 6, dwTime);
            if ((sR == 0) && (sG == 0) && (sB == 0))
                m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSprite(iXpos, iY, pStr[iCnt] - 0x30 + 6, dwTime);
            else m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(iXpos, iY, pStr[iCnt] - 0x30 + 6, sR, sG, sB, dwTime);
            iXpos += __cSpace2[pStr[iCnt] - 0x30];
        }
    }
}

void CGame::PutString(int iX, int iY, std::string pString, Color color, bool bHide, char cBGtype, bool bIsPreDC)
{
    int i;
    if (pString.length() == 0)
        return;
    if (bHide == false)
    {
        switch (cBGtype)
        {
            case 0:
                PutFontString("default", iX + 1, iY, pString, color);
                break;
            case 1:
                PutFontString("default", iX, iY + 1, pString, Color(255, 5, 5, 255));
                PutFontString("default", iX + 1, iY + 1, pString, Color(255, 5, 5, 255));
                PutFontString("default", iX + 1, iY, pString, Color(255, 5, 5, 255));
                break;
        }
        PutFontString("default", iX, iY, pString, color);
    }
    else
    {
        for (i = 0; i < pString.length(); ++i)
            if (pString[i] != 0)
                pString[i] = '*';

        switch (cBGtype)
        {
            case 0:
                PutFontString("default", iX + 1, iY, pString, color);
                break;
            case 1:
                PutFontString("default", iX, iY + 1, pString, Color(255, 5, 5, 255));
                PutFontString("default", iX + 1, iY + 1, pString, Color(255, 5, 5, 255));
                PutFontString("default", iX + 1, iY, pString, Color(255, 5, 5, 255));
                break;
        }
        PutFontString("default", iX, iY, pString, color);
    }
}

void CGame::PutFontStringSize(std::string fontname, int iX, int iY, std::string text, Color color, int size)
{
    try
    {
        m_DDraw._text.setFont(m_DDraw._font.at(fontname));
        m_DDraw._text.setString(text);
        m_DDraw._text.setFillColor(color);
        m_DDraw._text.setPosition((float)iX, (float)iY);
        m_DDraw._text.setCharacterSize(size);
        m_DDraw.window.draw(m_DDraw._text);
    }
    catch (const std::out_of_range & oor)
    {
        //error
        //__asm int 3;
        __debugbreak();
    }
}

void CGame::PutFontString(std::string fontname, int iX, int iY, std::string text, Color color)
{
    try
    {
        m_DDraw._text.setFont(m_DDraw._font.at(fontname));
        m_DDraw._text.setString(text);
        m_DDraw._text.setFillColor(color);
        m_DDraw._text.setPosition((float)iX, (float)iY);
        m_DDraw._text.setCharacterSize(12);
        m_DDraw.back_buffer.draw(m_DDraw._text);
    }
    catch (const std::out_of_range & oor)
    {
        //error
        //__asm int 3;
        __debugbreak();
    }
}

void CGame::PutString(int iX, int iY, std::string pString, Color color)
{
    PutFontString("default", iX, iY, pString, color);
}

void CGame::PutString2(int iX, int iY, std::string pString, short sR, short sG, short sB)
{
    PutString(iX + 1, iY, pString, Color(0, 0, 0));
    PutString(iX, iY + 1, pString, Color(0, 0, 0));
    PutString(iX + 1, iY + 1, pString, Color(0, 0, 0));
    PutString(iX, iY, pString, Color(sR, sG, sB));
}

void CGame::PutAlignedString(int iX1, int iX2, int iY, std::string pString, short sR, short sG, short sB)
{
    try
    {
        m_DDraw._text.setFont(m_DDraw._font.at("default"));
        m_DDraw._text.setString(pString);
        m_DDraw._text.setFillColor(Color(sR, sG, sB));
        sf::FloatRect bounds = m_DDraw._text.getLocalBounds();
        // todo - properly make an aligned string function
        //_text.setPosition((float)((float(iX2) - iX1) / 2 + bounds.width), (float)iY);
        m_DDraw._text.setPosition(iX1, (float)iY);
        m_DDraw._text.setCharacterSize(12);

        m_DDraw.window.draw(m_DDraw._text);
    }
    catch (const std::out_of_range & oor)
    {
        //error
        //__asm int 3;
        __debugbreak();
    }
    //     RECT rt;
    //     m_DDraw._GetBackBufferDC();
    //     SetRect(&rt, iX1, iY, iX2, iY + 15);
    //     m_DDraw.DrawText(&rt, pString, Color(sR, sG, sB));
    //     m_DDraw._ReleaseBackBufferDC();
}

bool CGame::bInitMagicCfgList()
{
    char cFn[255] = {}, cTemp[255] = {};
    char * pContents, * token;
    char seps[] = "= ,\t\n";
    char cReadModeA = 0;
    char cReadModeB = 0;
    int  iMagicCfgListIndex = 0;
    class CStrTok * pStrTok;
    HANDLE hFile;
    FILE * pFile;
    uint32_t  dwFileSize;

    ZeroMemory(cTemp, sizeof(cTemp));
    ZeroMemory(cFn, sizeof(cFn));

    strcat(cFn, "data\\contents\\magiccfg.txt");

    hFile = CreateFileA(cFn, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwFileSize = GetFileSize(hFile, 0);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

    pFile = fopen(cFn, "rt");
    if (pFile == 0) return false;
    else
    {
        pContents = new char[dwFileSize + 1];
        ZeroMemory(pContents, dwFileSize + 1);
        fread(pContents, dwFileSize, 1, pFile);
        fclose(pFile);
    }

    pStrTok = new class CStrTok(pContents, seps);
    token = pStrTok->pGet();
    while (token != 0)
    {
        if (cReadModeA != 0)
        {
            switch (cReadModeA)
            {
                case 1:
                    switch (cReadModeB)
                    {
                        case 1:
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            if (m_pMagicCfgList[atoi(token)] != 0)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            m_pMagicCfgList[atoi(token)] = new class CMagic;
                            iMagicCfgListIndex = atoi(token);

                            cReadModeB = 2;
                            break;

                        case 2:
                            ZeroMemory(m_pMagicCfgList[iMagicCfgListIndex]->m_cName, sizeof(m_pMagicCfgList[iMagicCfgListIndex]->m_cName));
                            memcpy(m_pMagicCfgList[iMagicCfgListIndex]->m_cName, token, strlen(token));
                            cReadModeB = 3;
                            break;

                        case 3: // m_sValue1
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            m_pMagicCfgList[iMagicCfgListIndex]->m_sValue1 = atoi(token);
                            cReadModeB = 4;
                            break;

                        case 4: // m_sValue2	// INT
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            m_pMagicCfgList[iMagicCfgListIndex]->m_sValue2 = atoi(token);
                            cReadModeB = 5;
                            break;

                        case 5: // m_sValue3	// COST
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            m_pMagicCfgList[iMagicCfgListIndex]->m_sValue3 = atoi(token);
                            cReadModeB = 6;
                            break;

                        case 6: // m_sValue4	// STR
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            m_pMagicCfgList[iMagicCfgListIndex]->m_sValue4 = atoi(token);
                            cReadModeB = 7;
                            break;

                        case 7: // m_sValue5
                            cReadModeB = 8;
                            break;

                        case 8: // m_sValue6
                            cReadModeB = 9;
                            break;

                        case 9: // m_bIsVisible
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            if (atoi(token) == 0) m_pMagicCfgList[iMagicCfgListIndex]->m_bIsVisible = false;
                            else m_pMagicCfgList[iMagicCfgListIndex]->m_bIsVisible = true;
                            cReadModeA = 0;
                            cReadModeB = 0;
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
        else
        {
            if (memcmp(token, "magic", 5) == 0)
            {
                cReadModeA = 1;
                cReadModeB = 1;
            }
        }
        token = pStrTok->pGet();
    }

    delete pStrTok;
    delete[] pContents;

    if ((cReadModeA != 0) || (cReadModeB != 0))
    {
        return false;
    }

    return true;
}

bool CGame::bInitSkillCfgList()
{
    char cFn[255] = {}, cTemp[255] = {};
    char * pContents, * token;
    char seps[] = "= ,\t\n";
    char cReadModeA = 0;
    char cReadModeB = 0;
    int  iSkillCfgListIndex = 0;
    class CStrTok * pStrTok;
    HANDLE hFile;
    FILE * pFile;
    uint32_t  dwFileSize;

    ZeroMemory(cTemp, sizeof(cTemp));
    ZeroMemory(cFn, sizeof(cFn));

    strcat(cFn, "data\\contents\\Skillcfg.txt");

    hFile = CreateFileA(cFn, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwFileSize = GetFileSize(hFile, 0);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

    pFile = fopen(cFn, "rt");
    if (pFile == 0) return false;
    else
    {
        pContents = new char[dwFileSize + 1];
        ZeroMemory(pContents, dwFileSize + 1);
        fread(pContents, dwFileSize, 1, pFile);
        fclose(pFile);
    }

    pStrTok = new class CStrTok(pContents, seps);
    token = pStrTok->pGet();
    while (token != 0)
    {
        if (cReadModeA != 0)
        {
            switch (cReadModeA)
            {
                case 1:
                    switch (cReadModeB)
                    {
                        case 1:
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            if (m_pSkillCfgList[atoi(token)] != 0)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            m_pSkillCfgList[atoi(token)] = new class CSkill;
                            iSkillCfgListIndex = atoi(token);
                            cReadModeB = 2;
                            break;

                        case 2:
                            ZeroMemory(m_pSkillCfgList[iSkillCfgListIndex]->m_cName, sizeof(m_pSkillCfgList[iSkillCfgListIndex]->m_cName));
                            memcpy(m_pSkillCfgList[iSkillCfgListIndex]->m_cName, token, strlen(token));
                            cReadModeB = 3;
                            break;

                        case 3: // m_bIsUseable
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            m_pSkillCfgList[iSkillCfgListIndex]->m_bIsUseable = (bool)atoi(token);
                            cReadModeB = 4;
                            break;

                        case 4: // m_cUseMethod
                            if (_bGetIsStringIsNumber(token) == false)
                            {
                                delete[] pContents;
                                delete pStrTok;
                                return false;
                            }
                            m_pSkillCfgList[iSkillCfgListIndex]->m_cUseMethod = atoi(token);
                            cReadModeA = 0;
                            cReadModeB = 0;
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
        else
        {
            if (memcmp(token, "skill", 5) == 0)
            {
                cReadModeA = 1;
                cReadModeB = 1;
            }
        }
        token = pStrTok->pGet();
    }

    delete pStrTok;
    delete[] pContents;

    if ((cReadModeA != 0) || (cReadModeB != 0))
    {
        return false;
    }

    return true;
}


bool CGame::_bGetIsStringIsNumber(char * pStr)
{
    int i;
    for (i = 0; i < (int)strlen(pStr); i++)
        if ((pStr[i] != '-') && ((pStr[i] < (char)'0') || (pStr[i] > (char)'9'))) return false;

    return true;
}


void CGame::RequestFullObjectData(owner_type owner_type_, uint16_t wObjectID)
{
    StreamWrite sw;
    sw.write_enum(message_id::REQUEST_FULLOBJECTDATA);
    sw.WriteShort((short)owner_type_);
    sw.WriteInt64(wObjectID);
    write(sw);
}


void CGame::handle_stop()
{
    close(1000, "handle_stop()");
}

void CGame::close(uint32_t code, const std::string & reason)
{
    try
    {
        ws->close(code, "close()");
    }
    catch (std::system_error & ex)
    {
        std::cout << "close() mutex lock timeout?\n";
    }
}

void CGame::on_message(const ix::WebSocketMessagePtr & msg)
{
    if (msg->type == ix::WebSocketMessageType::Message)
    {
        std::cout << "received message\n";
        auto message = std::make_shared<CGame::MsgQueueEntry>();
        message->data = new char[msg->str.length()];
        memcpy(message->data, msg->str.c_str(), msg->str.length());
        message->size = msg->str.length();
        std::lock_guard<std::mutex> l(socketmut);
        PutMsgQueue(message, loginpipe);
    }
    else if (msg->type == ix::WebSocketMessageType::Open)
    {
        m_dwConnectMode = (uint32_t)message_id::REQUEST_LOGIN;
        ConnectionEstablishHandler(DEF_SERVERTYPE_LOG);
    }
    else if (msg->type == ix::WebSocketMessageType::Error)
    {
        std::cout << "ws error\n";
        connection_loss_gamemode();
        loggedin = false;
    }
    else if (msg->type == ix::WebSocketMessageType::Close)
    {
        std::cout << "ws close\n";
        connection_loss_gamemode();
        loggedin = false;
    }
}

bool CGame::is_connected() const
{
    return ws->getReadyState() == ix::ReadyState::Open;
}

bool CGame::is_closed() const
{
    return ws->getReadyState() == ix::ReadyState::Closed;
}

bool CGame::is_connecting() const
{
    return ws->getReadyState() == ix::ReadyState::Connecting;
}

bool CGame::is_closing() const
{
    return ws->getReadyState() == ix::ReadyState::Closing;
}

void CGame::PutMsgQueue(MsgQueue & q, char * data, uint32_t size)
{
    //poco_information(*logger, "PutMsgQueue()");
    std::shared_ptr<MsgQueueEntry> msg = std::make_shared<MsgQueueEntry>();

    msg->data = new char[size];
    memcpy(msg->data, data, size);
    msg->size = size;

    q.push_back(msg);
}

void CGame::PutMsgQueue(std::shared_ptr<CGame::MsgQueueEntry> msg, MsgQueue & q)
{
    q.push_back(msg);
}

std::shared_ptr<CGame::MsgQueueEntry> CGame::GetMsgQueue()
{
    std::shared_ptr<CGame::MsgQueueEntry> msg = socketpipe.front();
    socketpipe.pop_front();
    return msg;
}

void CGame::perform_connect()
{
    ws = std::make_unique<ix::WebSocket>();
    ws->disableAutomaticReconnection();
#if defined(HTTPS)
    ws->setUrl(fmt::format("wss://{}:{}", game_server_address, game_server_port));
#else
    ws->setUrl(fmt::format("ws://{}:{}", game_server_address, game_server_port));
#endif

    ws->setOnMessageCallback(
        [&](const ix::WebSocketMessagePtr & message)
        {
            on_message(message);
        }
    );
    ws->start();
}

void CGame::perform_login_connect()
{
    log_ws = std::make_unique<ix::WebSocket>();
    log_ws->disableAutomaticReconnection();
#if defined(HTTPS)
    log_ws->setUrl(fmt::format("wss://{}:{}", login_server_address, login_server_port));
#else
    log_ws->setUrl(fmt::format("ws://{}:{}", login_server_address, login_server_port));
#endif

    log_ws->setOnMessageCallback(
        [&](const ix::WebSocketMessagePtr & message)
        {
            on_message(message);
        }
    );
    log_ws->start();
}

int CGame::write(const char * data, const uint64_t size)
{
    std::cout << "Sent " << size << " cbytes of data\n";
    auto d = ix::IXWebSocketSendData{ data, size };
    return ws->sendBinary(d).payloadSize;
}

int CGame::write(StreamWrite & sw)
{
    std::cout << "Sent " << sw.position << " bytes of data\n";
    auto d = ix::IXWebSocketSendData{ sw.data, sw.position };
    return ws->sendBinary(d).payloadSize;
}

int CGame::write(nlohmann::json & obj)
{
    return ws->send(obj.dump(-1, 0x32, false, nlohmann::detail::error_handler_t::ignore)).payloadSize;
}

int CGame::log_write(const char * data, const uint64_t size)
{
    std::cout << "Sent login " << size << " cbytes of data\n";
    auto d = ix::IXWebSocketSendData{ data, size };
    return log_ws->sendBinary(d).payloadSize;
}

int CGame::log_write(StreamWrite & sw)
{
    std::cout << "Sent login " << sw.position << " bytes of data\n";
    auto d = ix::IXWebSocketSendData{ sw.data, sw.position };
    return log_ws->sendBinary(d).payloadSize;
}

int CGame::log_write(nlohmann::json & obj)
{
    return log_ws->send(obj.dump(-1, 0x32, false, nlohmann::detail::error_handler_t::ignore)).payloadSize;
}

std::shared_ptr<CGame::MsgQueueEntry> CGame::GetLoginMsgQueue()
{
    std::shared_ptr<CGame::MsgQueueEntry> msg = loginpipe.front();
    loginpipe.pop_front();
    return msg;
}

void CGame::_ReadMapData(short sPivotX, short sPivotY, char * pData)
{
    int i;
    char * cp, ucHeader, cDir, cName[12] = {}, cItemColor;
    short * sp, sTotal, sX, sY, sType, sAppr1, sAppr2, sAppr3, sAppr4, sItemSpr, sItemSprFrame, sDynamicObjectType;
    int iStatus;
    int * ip, iApprColor;
    uint16_t    wObjectID;
    uint16_t * wp, wDynamicObjectID;
    cp = pData;
    m_sVDL_X = sPivotX; // Valid Data Loc-X
    m_sVDL_Y = sPivotY;
    sp = (short *)cp;
    sTotal = *sp;
    cp += 2;
    for (i = 1; i <= sTotal; i++)
    {
        sp = (short *)cp;
        sX = *sp;
        cp += 2;
        sp = (short *)cp;
        sY = *sp;
        cp += 2;
        ucHeader = *cp;
        cp++;
        if (ucHeader & 0x01) // object ID
        {
            wp = (uint16_t *)cp;
            wObjectID = *wp;
            cp += 2;
            sp = (short *)cp;
            sType = *sp;// object type
            cp += 2;
            // dir
            cDir = *cp;
            cp++;
            if (wObjectID < 10000)
            {
                sp = (short *)cp;
                sAppr1 = *sp;// Appearance1
                cp += 2;
                sp = (short *)cp;
                sAppr2 = *sp;// Appearance2
                cp += 2;
                sp = (short *)cp;
                sAppr3 = *sp;// Appearance3
                cp += 2;
                sp = (short *)cp;
                sAppr4 = *sp;// Appearance4
                cp += 2;
                ip = (int *)cp;
                iApprColor = *ip;// v1.4 ApprColor
                cp += 4;
                // Status
                ip = (int *)cp;
                iStatus = *ip;
                cp += 4;
                // Name
                ZeroMemory(cName, sizeof(cName));
                memcpy(cName, cp, 10);
                cp += 10;
            }
            else // NPC
            {
                sAppr1 = sAppr3 = sAppr4 = 0;
                sp = (short *)cp;
                sAppr2 = *sp;// Appearance2
                cp += 2;
                // Status
                ip = (int *)cp;
                iStatus = *ip;
                cp += 4;
                // Name
                ZeroMemory(cName, sizeof(cName));
                memcpy(cName, cp, 5);
                cp += 5;
            }
            m_pMapData->bSetOwner(wObjectID, sPivotX + sX, sPivotY + sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, DEF_OBJECTSTOP, 0, 0, 0);
        }
        if (ucHeader & 0x02) // object ID (Dead)
        {
            wp = (uint16_t *)cp;
            wObjectID = *wp;
            cp += 2;
            sp = (short *)cp;
            sType = *sp;	// object type
            cp += 2;
            cDir = *cp;	// dir
            cp++;
            if (wObjectID < 10000)
            {
                sp = (short *)cp;
                sAppr1 = *sp;// Appearance1
                cp += 2;
                sp = (short *)cp;
                sAppr2 = *sp;// Appearance2
                cp += 2;
                sp = (short *)cp;
                sAppr3 = *sp;// Appearance3
                cp += 2;
                sp = (short *)cp;
                sAppr4 = *sp;// Appearance4
                cp += 2;
                ip = (int *)cp;
                iApprColor = *ip;// v1.4 ApprColor
                cp += 4;
                // Status
                ip = (int *)cp;
                iStatus = *ip;
                cp += 4;
                // Name
                ZeroMemory(cName, sizeof(cName));
                memcpy(cName, cp, 10);
                cp += 10;
            }
            else 	// NPC
            {
                sAppr1 = sAppr3 = sAppr4 = 0;
                sp = (short *)cp;
                sAppr2 = *sp;// Appearance2
                cp += 2;
                ip = (int *)cp;
                iStatus = *ip;// Status
                cp += 4;
                ZeroMemory(cName, sizeof(cName));	// Name
                memcpy(cName, cp, 5);
                cp += 5;
            }
            m_pMapData->bSetDeadOwner(wObjectID, sPivotX + sX, sPivotY + sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName);
        }
        if (ucHeader & 0x04)
        {
            sp = (short *)cp;
            sItemSpr = *sp;
            cp += 2;
            sp = (short *)cp;
            sItemSprFrame = *sp;
            cp += 2;
            cItemColor = *cp;
            cp++;
            m_pMapData->bSetItem(sPivotX + sX, sPivotY + sY, sItemSpr, sItemSprFrame, cItemColor, false);
        }
        if (ucHeader & 0x08) // Dynamic object
        {
            wp = (uint16_t *)cp;
            wDynamicObjectID = *wp;
            cp += 2;
            sp = (short *)cp;
            sDynamicObjectType = *sp;
            cp += 2;
            m_pMapData->bSetDynamicObject(sPivotX + sX, sPivotY + sY, wDynamicObjectID, sDynamicObjectType, false);
        }
    }
}

void CGame::LogEventHandler(char * pData)
{
    uint16_t * wp, wEventType, wObjectID;
    short * sp, sX, sY, sType, sAppr1, sAppr2, sAppr3, sAppr4;
    int iStatus;
    char * cp, cDir, cName[12] = {};
    int * ip, iApprColor;
    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    wEventType = *wp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wObjectID = *wp;
    cp += 2;
    sp = (short *)cp;
    sX = *sp;
    cp += 2;
    sp = (short *)cp;
    sY = *sp;
    cp += 2;
    sp = (short *)cp;
    sType = *sp;
    cp += 2;
    cDir = *cp;
    cp++;
    ZeroMemory(cName, sizeof(cName));
    if (wObjectID < 10000)
    {
        memcpy(cName, cp, 10);
        cp += 10;
        sp = (short *)cp;
        sAppr1 = *sp;
        cp += 2;
        sp = (short *)cp;
        sAppr2 = *sp;
        cp += 2;
        sp = (short *)cp;
        sAppr3 = *sp;
        cp += 2;
        sp = (short *)cp;
        sAppr4 = *sp;
        cp += 2;
        ip = (int *)cp;
        iApprColor = *ip;
        cp += 4;
        ip = (int *)cp;
        iStatus = *ip;
        cp += 4;
    }
    else 	// NPC
    {
        memcpy(cName, cp, 5);
        cp += 5;
        sAppr1 = sAppr3 = sAppr4 = 0;
        sp = (short *)cp;
        sAppr2 = *sp;
        cp += 2;
        ip = (int *)cp;
        iStatus = *ip;
        cp += 4;
    }

    switch (wEventType)
    {
        case DEF_MSGTYPE_CONFIRM:
            m_pMapData->bSetOwner(wObjectID, sX, sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, DEF_OBJECTSTOP, 0, 0, 0);
            switch (sType)
            {
                case 43: // LWB
                case 44: // GHK
                case 45: // GHKABS
                case 46: // TK
                case 47: // BG
                    bAddNewEffect(64, (sX) * 32, (sY) * 32, 0, 0, 0);
                    break;
            }
            break;

        case DEF_MSGTYPE_REJECT:
            m_pMapData->bSetOwner(wObjectID, -1, -1, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, DEF_OBJECTSTOP, 0, 0, 0);
            break;
    }

    _RemoveChatMsgListByObjectID(wObjectID);
}

void CGame::LogResponseHandler(char * pData)
{
    uint16_t * wp, wResponse;
    uint16_t wServerUpperVersion, wServerLowerVersion;
    uint32_t * dwp;
    char * cp, cCharName[12] = {};
    int * ip, i;

    dwp = (uint32_t *)(pData);
    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    wResponse = *wp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    switch (wResponse)
    {
        case DEF_LOGRESMSGTYPE_CHARACTERDELETED:
            cp = (pData + DEF_INDEX2_MSGTYPE + 2);
            //m_iAccountStatus = (int)*cp;
            cp++;
            m_iTotalChar = (int)*cp;
            cp++;
            for (i = 0; i < 4; i++)
                if (m_pCharList[i] != 0)
                {
                    delete m_pCharList[i];
                    m_pCharList[i] = 0;
                }

            for (i = 0; i < m_iTotalChar; i++)
            {
                m_pCharList[i] = new class CCharInfo;
                memcpy(m_pCharList[i]->m_cName, cp, 10);
                cp += 10;
                if (*cp == 0)
                {
                    m_pCharList[i]->m_sSex = 0; // Sex
                    cp += 40;
                }
                else
                {
                    cp++;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr1 = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr2 = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr3 = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr4 = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sSex = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sSkinCol = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sLevel = *wp;
                    cp += 2;
                    dwp = (uint32_t *)cp;
                    m_pCharList[i]->m_iExp = *dwp;
                    cp += 4;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sStr = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sVit = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sDex = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sInt = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sMag = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sChr = *wp;
                    cp += 2;
                    ip = (int *)cp; // v1.4
                    m_pCharList[i]->m_iApprColor = *ip;
                    cp += 4;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iYear = (int)*wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iMonth = (int)*wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iDay = (int)*wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iHour = (int)*wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iMinute = (int)*wp;
                    cp += 2;
                    ZeroMemory(m_pCharList[i]->m_cMapName, sizeof(m_pCharList[i]->m_cMapName));
                    memcpy(m_pCharList[i]->m_cMapName, cp, 10);
                    cp += 10;
                }
            }
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "3A");
            break;

        case DEF_LOGRESMSGTYPE_CONFIRM:
            cp = (pData + DEF_INDEX2_MSGTYPE + 2);
            wp = (uint16_t *)cp;
            wServerUpperVersion = *wp;
            cp += 2;
            wp = (uint16_t *)cp;
            wServerLowerVersion = *wp;
            cp += 2;
            //		m_iAccountStatus = (int)*cp;
            cp++;
            wp = (uint16_t *)cp;
            m_iAccntYear = *wp;
            cp += 2;
            wp = (uint16_t *)cp;
            m_iAccntMonth = *wp;
            cp += 2;
            wp = (uint16_t *)cp;
            m_iAccntDay = *wp;
            cp += 2;
            wp = (uint16_t *)cp;
            m_iIpYear = *wp;
            cp += 2;
            wp = (uint16_t *)cp;
            m_iIpMonth = *wp;
            cp += 2;
            wp = (uint16_t *)cp;
            m_iIpDay = *wp;
            cp += 2;
            m_iTotalChar = (int)*cp;
            cp++;
            for (i = 0; i < 4; i++)
                if (m_pCharList[i] != 0)
                {
                    delete m_pCharList[i];
                    m_pCharList[i] = 0;
                }

            for (i = 0; i < m_iTotalChar; i++)
            {
                m_pCharList[i] = new class CCharInfo;
                memcpy(m_pCharList[i]->m_cName, cp, 10);
                cp += 10;
                if (*cp == 0)
                {
                    m_pCharList[i]->m_sSex = 0;
                    cp += 40;
                }
                else
                {
                    cp++;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr1 = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr2 = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr3 = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr4 = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sSex = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sSkinCol = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sLevel = *wp;
                    cp += 2;
                    dwp = (uint32_t *)cp;
                    m_pCharList[i]->m_iExp = *dwp;
                    cp += 4;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sStr = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sVit = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sDex = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sInt = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sMag = *wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sChr = *wp;
                    cp += 2;
                    ip = (int *)cp;
                    m_pCharList[i]->m_iApprColor = *ip; // v1.4
                    cp += 4;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iYear = (int)*wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iMonth = (int)*wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iDay = (int)*wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iHour = (int)*wp;
                    cp += 2;
                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iMinute = (int)*wp;
                    cp += 2;
                    ZeroMemory(m_pCharList[i]->m_cMapName, sizeof(m_pCharList[i]->m_cMapName));
                    memcpy(m_pCharList[i]->m_cMapName, cp, 10);
                    cp += 10;
                }
            }
            ip = (int *)cp;
            m_iTimeLeftSecAccount = *ip;
            cp += 4;
            ip = (int *)cp;
            m_iTimeLeftSecIP = *ip;
            cp += 4;
            ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
            ClearContents_OnSelectCharacter();

#ifndef _DEBUG
#ifndef DEF_ANTI_HACK
            if ((wServerUpperVersion != DEF_UPPERVERSION) || (wServerLowerVersion != DEF_LOWERVERSION))
                ChangeGameMode(DEF_GAMEMODE_ONVERSIONNOTMATCH);
#else
            if ((wServerUpperVersion != DEF_HIDDEN_UPPERVERSION) || (wServerLowerVersion != DEF_HIDDEN_LOWERVERSION))
                ChangeGameMode(DEF_GAMEMODE_ONVERSIONNOTMATCH);
#endif
#endif
            break;

        case DEF_LOGRESMSGTYPE_REJECT:
            cp = (pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            m_iBlockYear = *ip;
            cp += 4;

            ip = (int *)cp;
            m_iBlockMonth = *ip;
            cp += 4;

            ip = (int *)cp;
            m_iBlockDay = *ip;
            cp += 4;

            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "7H");
            break;

        case DEF_LOGRESMSGTYPE_NOTENOUGHPOINT:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "7I");
            break;

        case DEF_LOGRESMSGTYPE_ACCOUNTLOCKED:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "7K");
            break;

        case DEF_LOGRESMSGTYPE_SERVICENOTAVAILABLE:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "7L");
            break;

        case DEF_LOGRESMSGTYPE_PASSWORDCHANGESUCCESS:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "6B");
            break;

        case DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "6C");
            break;

        case DEF_LOGRESMSGTYPE_PASSWORDMISMATCH:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "11");
            break;

        case DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "12");
            break;

        case DEF_LOGRESMSGTYPE_NEWACCOUNTCREATED:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "54");
            break;

        case DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "05");
            break;

        case DEF_LOGRESMSGTYPE_ALREADYEXISTINGACCOUNT:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "06");
            break;

        case DEF_LOGRESMSGTYPE_NOTEXISTINGCHARACTER:
            ChangeGameMode(DEF_GAMEMODE_ONMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "Not existing character!");
            break;

        case DEF_LOGRESMSGTYPE_NEWCHARACTERCREATED:
            ZeroMemory(cCharName, sizeof(cCharName));
            memcpy(cCharName, cp, 10);
            cp += 10;

            m_iTotalChar = (int)*cp;
            cp++;

            for (i = 0; i < 4; i++)
                if (m_pCharList[i] != 0) delete m_pCharList[i];
            //
            for (i = 0; i < m_iTotalChar; i++)
            {
                m_pCharList[i] = new class CCharInfo;
                memcpy(m_pCharList[i]->m_cName, cp, 10);
                cp += 10;
                if (*cp == 0)
                {
                    m_pCharList[i]->m_sSex = 0; // Sex
                    cp += 40;
                }
                else
                {
                    cp++;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr1 = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr2 = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr3 = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sAppr4 = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sSex = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sSkinCol = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sLevel = *wp;
                    cp += 2;

                    dwp = (uint32_t *)cp;
                    m_pCharList[i]->m_iExp = *dwp;
                    cp += 4;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sStr = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sVit = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sDex = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sInt = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sMag = *wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_sChr = *wp;
                    cp += 2;

                    ip = (int *)cp; // v1.4
                    m_pCharList[i]->m_iApprColor = *ip;
                    cp += 4;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iYear = (int)*wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iMonth = (int)*wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iDay = (int)*wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iHour = (int)*wp;
                    cp += 2;

                    wp = (uint16_t *)cp;
                    m_pCharList[i]->m_iMinute = (int)*wp;
                    cp += 2;

                    ZeroMemory(m_pCharList[i]->m_cMapName, sizeof(m_pCharList[i]->m_cMapName));
                    memcpy(m_pCharList[i]->m_cMapName, cp, 10);
                    cp += 10;
                }
            }
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "47");
            break;

        case DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "28");
            break;

        case DEF_LOGRESMSGTYPE_ALREADYEXISTINGCHARACTER:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "29");
            break;

        case DEF_ENTERGAMERESTYPE_PLAYING:
            ChangeGameMode(DEF_GAMEMODE_ONQUERYFORCELOGIN);
            break;

        case DEF_ENTERGAMERESTYPE_CONFIRM:
        {
            int iGameServerPort;
            char cGameServerAddr[16] = {};
            ZeroMemory(cGameServerAddr, sizeof(cGameServerAddr));
            cp = (pData + DEF_INDEX2_MSGTYPE + 2);
            memcpy(cGameServerAddr, cp, 16);
            cp += 16;
            wp = (uint16_t *)cp;
            iGameServerPort = *wp;
            cp += 2;
            ZeroMemory(m_cGameServerName, sizeof(m_cGameServerName));
            memcpy(m_cGameServerName, cp, 20);
            cp += 20;
            perform_connect();
        }
        break;

        case DEF_ENTERGAMERESTYPE_REJECT:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            switch (*cp)
            {
                case 1:	strcpy(m_cMsg, "3E"); break;
                case 2:	strcpy(m_cMsg, "3F"); break;
                case 3:	strcpy(m_cMsg, "33"); break;
                case 4: strcpy(m_cMsg, "3D"); break;
                case 5: strcpy(m_cMsg, "3G"); break;
                case 6: strcpy(m_cMsg, "3Z"); break;
                case 7: strcpy(m_cMsg, "3J"); break;
            }
            break;

        case DEF_ENTERGAMERESTYPE_FORCEDISCONN:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "3X");
            break;

        case DEF_LOGRESMSGTYPE_NOTEXISTINGWORLDSERVER:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "1Y");
            break;

        case DEF_LOGRESMSGTYPE_INPUTKEYCODE:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            switch (*cp)
            {
                case 1:	strcpy(m_cMsg, "8U"); break; //MainMenu, Keycode registration success
                case 2:	strcpy(m_cMsg, "82"); break; //MainMenu, Not existing Account
                case 3:	strcpy(m_cMsg, "81"); break; //MainMenu, Password wrong
                case 4: strcpy(m_cMsg, "8V"); break; //MainMenu, Invalid Keycode
                case 5: strcpy(m_cMsg, "8W"); break; //MainMenu, Already Used Keycode
            }
            break;


        case DEF_LOGRESMSGTYPE_FORCECHANGEPASSWORD:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "6M");
            break;

        case DEF_LOGRESMSGTYPE_INVALIDKOREANSSN:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "1a");
            break;

        case DEF_LOGRESMSGTYPE_LESSTHENFIFTEEN:
            ChangeGameMode(DEF_GAMEMODE_ONLOGRESMSG);
            ZeroMemory(m_cMsg, sizeof(m_cMsg));
            strcpy(m_cMsg, "1b");
            break;

    }
    log_ws = nullptr;
}

void CGame::LogRecvMsgHandler(char * pData)
{
    LogResponseHandler(pData);
}

void CGame::_InitOnCreateNewCharacter()
{
    m_cGender = rand() % 2 + 1;
    m_cSkinCol = rand() % 3 + 1;
    m_cHairStyle = rand() % 8;
    m_cHairCol = rand() % 16;
    m_cUnderCol = rand() % 8;
    m_ccStr = 10;
    m_ccVit = 10;
    m_ccDex = 10;
    m_ccInt = 10;
    m_ccMag = 10;
    m_ccChr = 10;
}

void CGame::ClearContents_OnCreateNewAccount()
{
    ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
    ZeroMemory(m_cAccountAge, sizeof(m_cAccountAge));
    ZeroMemory(m_cAccountCountry, sizeof(m_cAccountCountry));
    ZeroMemory(m_cAccountSSN, sizeof(m_cAccountSSN));
    ZeroMemory(m_cEmailAddr, sizeof(m_cEmailAddr));
    //v1.4334
    ZeroMemory(m_cAccountQuiz, sizeof(m_cAccountQuiz));
    ZeroMemory(m_cAccountAnswer, sizeof(m_cAccountAnswer));
}

void CGame::ChangeGameMode(char cMode)
{
    m_cGameMode = cMode;
    m_cGameModeCount = 0;
    m_dwTime = G_dwGlobalTime;

#ifndef DEF_SELECTSERVER
    if (cMode == DEF_GAMEMODE_ONSELECTSERVER)
    {
        ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
        strcpy(m_cWorldServerName, NAME_WORLDNAME1);
        m_cGameMode = DEF_GAMEMODE_ONLOGIN;
    }
#endif
}

void CGame::ReleaseUnusedSprites()
{
    int i;
    for (i = 0; i < DEF_MAXSPRITES; i++)
        if ((m_pSprite[i] != 0))
        {
            if ((m_pSprite[i]->m_bIsSurfaceEmpty == false) && (m_pSprite[i]->m_bOnCriticalSection == false))
            {
                if ((G_dwGlobalTime - m_pSprite[i]->m_dwRefTime) > 60000) m_pSprite[i]->_iCloseSprite();

            }
        }
    for (i = 0; i < DEF_MAXTILES; i++)
        if ((m_pTileSpr[i] != 0))
        {
            if ((m_pTileSpr[i]->m_bIsSurfaceEmpty == false) && (m_pTileSpr[i]->m_bOnCriticalSection == false))
            {
                if ((G_dwGlobalTime - m_pTileSpr[i]->m_dwRefTime) > 60000) m_pTileSpr[i]->_iCloseSprite();
            }
        }
    for (i = 0; i < DEF_MAXEFFECTSPR; i++)
        if ((m_pEffectSpr[i] != 0))
        {
            if ((m_pEffectSpr[i]->m_bIsSurfaceEmpty == false) && (m_pEffectSpr[i]->m_bOnCriticalSection == false))
            {
                if ((G_dwGlobalTime - m_pEffectSpr[i]->m_dwRefTime) > 60000) m_pEffectSpr[i]->_iCloseSprite();
            }
        }

//     for (i = 0; i < DEF_MAXSOUNDEFFECTS; i++)
//     {
//         if (m_pCSound[i] != 0)
//         {
//             if (((G_dwGlobalTime - m_pCSound[i]->m_dwTime) > 30000) && (m_pCSound[i]->m_bIsLooping == false)) m_pCSound[i]->_ReleaseSoundBuffer();
//         }
//         if (m_pMSound[i] != 0)
//         {
//             if (((G_dwGlobalTime - m_pMSound[i]->m_dwTime) > 30000) && (m_pMSound[i]->m_bIsLooping == false)) m_pMSound[i]->_ReleaseSoundBuffer();
//         }
//         if (m_pESound[i] != 0)
//         {
//             if (((G_dwGlobalTime - m_pESound[i]->m_dwTime) > 30000) && (m_pESound[i]->m_bIsLooping == false)) m_pESound[i]->_ReleaseSoundBuffer();
//         }
//     }
}

void CGame::PutChatScrollList(char * pMsg, char cType)
{
    int i;
    if (m_pChatScrollList[DEF_MAXCHATSCROLLMSGS - 1] != 0)
    {
        delete m_pChatScrollList[DEF_MAXCHATSCROLLMSGS - 1];
        m_pChatScrollList[DEF_MAXCHATSCROLLMSGS - 1] = 0;
    }
    for (i = DEF_MAXCHATSCROLLMSGS - 2; i >= 0; i--)
    {
        m_pChatScrollList[i + 1] = m_pChatScrollList[i];
        m_pChatScrollList[i] = 0;
    }
    m_pChatScrollList[0] = new class CMsg(1, pMsg, cType);
}

void CGame::ChatMsgHandler(char * pData)
{
    int i, iObjectID, iLoc;
    short * sp, sX, sY;
    char * cp, cMsgType, cName[21] = {}, cTemp[100] = {}, cMsg[100] = {}, cTxt1[100] = {}, cTxt2[100] = {};
    uint64_t dwTime;
    uint16_t * wp;
    bool bFlag;

    char cHeadMsg[200] = {};

    dwTime = m_dwCurTime;

    ZeroMemory(cTxt1, sizeof(cTxt1));
    ZeroMemory(cTxt2, sizeof(cTxt2));
    ZeroMemory(cMsg, sizeof(cMsg));

    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    iObjectID = (int)*wp;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    sp = (short *)cp;
    sX = *sp;
    cp += 2;

    sp = (short *)cp;
    sY = *sp;
    cp += 2;
    ZeroMemory(cName, sizeof(cName));
    memcpy(cName, (char *)cp, 10);
    cp += 10;

    cMsgType = *cp;
    cp++;

    if (bCheckExID(cName) == true) return;

    ZeroMemory(cTemp, sizeof(cTemp));
    strcpy(cTemp, cp);

    if ((cMsgType == 0) || (cMsgType == 2) || (cMsgType == 3))
    {
        if (m_Misc.bCheckIMEString(cTemp) == false) return;
    }
    if (!m_bWhisper)
    {
        if (cMsgType == 20) return;
    }
    if (!m_bShout)
    {
        if (cMsgType == 2 || cMsgType == 3) return;
    }

    ZeroMemory(cMsg, sizeof(cMsg));
    wsprintfA(cMsg, "%s: %s", cName, cTemp);
    bFlag = false;
    short sCheckByte = 0;
    while (bFlag == false)
    {
        iLoc = m_Misc.iGetTextLengthLoc(this, cMsg, 305);
        for (int i = 0; i < iLoc; i++) if (cMsg[i] < 0) sCheckByte++;
        if (iLoc == 0)
        {
            PutChatScrollList(cMsg, cMsgType);
            bFlag = true;
        }
        else
        {
            if ((sCheckByte % 2) == 0)
            {
                ZeroMemory(cTemp, sizeof(cTemp));
                memcpy(cTemp, cMsg, iLoc);
                PutChatScrollList(cTemp, cMsgType);
                ZeroMemory(cTemp, sizeof(cTemp));
                strcpy(cTemp, cMsg + iLoc);
                ZeroMemory(cMsg, sizeof(cMsg));
                strcpy(cMsg, " ");
                strcat(cMsg, cTemp);
            }
            else
            {
                ZeroMemory(cTemp, sizeof(cTemp));
                memcpy(cTemp, cMsg, iLoc + 1);
                PutChatScrollList(cTemp, cMsgType);
                ZeroMemory(cTemp, sizeof(cTemp));
                strcpy(cTemp, cMsg + iLoc + 1);
                ZeroMemory(cMsg, sizeof(cMsg));
                strcpy(cMsg, " ");
                strcat(cMsg, cTemp);
            }
        }
    }

    _RemoveChatMsgListByObjectID(iObjectID);

    for (i = 1; i < DEF_MAXCHATMSGS; i++)
        if (m_pChatMsgList[i] == 0)
        {
            m_pChatMsgList[i] = new class CMsg(1, (char *)(cp), dwTime);
            m_pChatMsgList[i]->m_iObjectID = iObjectID;

            if (m_pMapData->bSetChatMsgOwner(iObjectID, sX, sY, i) == false)
            {
                delete m_pChatMsgList[i];
                m_pChatMsgList[i] = 0;
            }

            if ((cMsgType != 0) && (m_bIsDialogEnabled[10] != true))
            {
                ZeroMemory(cHeadMsg, sizeof(cHeadMsg));
                wsprintfA(cHeadMsg, "%s:%s", cName, cp);
                AddEventList(cHeadMsg, cMsgType);
            }
            return;
        }
}

void CGame::ReleaseTimeoverChatMsg()
{
    int i;
    uint64_t dwTime;
    dwTime = G_dwGlobalTime;
    for (i = 1; i < DEF_MAXCHATMSGS; i++)
        if (m_pChatMsgList[i] != 0)
        {

            if ((m_pChatMsgList[i]->m_cType >= 1) && (m_pChatMsgList[i]->m_cType <= 20))
            {
                if ((dwTime - m_pChatMsgList[i]->m_dwTime) > DEF_CHATTIMEOUT_A)
                {
                    delete m_pChatMsgList[i];
                    m_pChatMsgList[i] = 0;
                }
            }
            else
                if ((m_pChatMsgList[i]->m_cType >= 21) && (m_pChatMsgList[i]->m_cType <= 40))
                {
                    if ((dwTime - m_pChatMsgList[i]->m_dwTime) > DEF_CHATTIMEOUT_B)
                    {
                        delete m_pChatMsgList[i];
                        m_pChatMsgList[i] = 0;
                    }
                }
                else
                    if ((m_pChatMsgList[i]->m_cType >= 41) && (m_pChatMsgList[i]->m_cType <= 60))
                    {
                        if ((dwTime - m_pChatMsgList[i]->m_dwTime) > DEF_CHATTIMEOUT_C)
                        {
                            delete m_pChatMsgList[i];
                            m_pChatMsgList[i] = 0;
                        }
                    }
                    else if ((dwTime - m_pChatMsgList[i]->m_dwTime) > DEF_CHATTIMEOUT_A)
                    {
                        delete m_pChatMsgList[i];
                        m_pChatMsgList[i] = 0;
                    }
        }
}

void CGame::DrawBackground(short sDivX, short sModX, short sDivY, short sModY)
{
    int indexX, indexY, ix, iy;
    short sSpr, sSprFrame;
    if (sDivX < 0 || sDivY < 0) return;
    if ((m_bIsRedrawPDBGS == true) || (m_iPDBGSdivX != sDivX) || (m_iPDBGSdivY != sDivY))
    {
        m_DDraw.setRenderTarget(DS_BG, true, Color(0, 0, 0, 0));
        // Pre-Draw Background Surface
        m_bIsRedrawPDBGS = false;
        m_iPDBGSdivX = sDivX;
        m_iPDBGSdivY = sDivY;
        SetRect(&m_DDraw.m_rcClipArea, 0, 0, 640 + 32, 480 + 32);
        indexY = sDivY + m_pMapData->m_sPivotY;
        for (iy = -sModY; iy < 427 + 48; iy += 32)
        {
            indexX = sDivX + m_pMapData->m_sPivotX;
            for (ix = -sModX; ix < 640 + 48; ix += 32)
            {
                sSpr = m_pMapData->m_tile[indexX][indexY].m_sTileSprite;
                sSprFrame = m_pMapData->m_tile[indexX][indexY].m_sTileSpriteFrame;
                m_pTileSpr[sSpr]->PutSpriteFastNoColorKey(ix - 16 + sModX, iy - 16 + sModY, sSprFrame, m_dwCurTime);
                indexX++;
            }
            indexY++;
        }
        SetRect(&m_DDraw.m_rcClipArea, 0, 0, 640, 480);
        m_DDraw.setRenderTarget(DS_BACK);
    }
    if (m_bIsCrusadeMode)
    {
        if (m_iConstructLocX != -1) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, m_iConstructLocX * 32 - m_sViewPointX, m_iConstructLocY * 32 - m_sViewPointY, 41);
        if (m_iTeleportLocX != -1) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_CRUSADE, m_iTeleportLocX * 32 - m_sViewPointX, m_iTeleportLocY * 32 - m_sViewPointY, 42);
    }
}


bool CGame::bEffectFrameCounter()
{
    int i, x;
    uint64_t dwTime;
    bool bRet = false;
    short sAbsX, sAbsY, sDist = 0;
    char  cDir;
    long lPan;
    dwTime = m_dwCurTime;
    dwTime += m_pMapData->m_dwFrameAdjustTime;
    for (i = 0; i < DEF_MAXEFFECTS; i++)
        if (m_pEffectList[i] != 0)
        {
            if ((dwTime - m_pEffectList[i]->m_dwTime) > m_pEffectList[i]->m_dwFrameTime)
            {
                m_pEffectList[i]->m_dwTime = dwTime;
                m_pEffectList[i]->m_cFrame++;
                bRet = true;
                m_pEffectList[i]->m_mX2 = m_pEffectList[i]->m_mX;
                m_pEffectList[i]->m_mY2 = m_pEffectList[i]->m_mY;
                switch (m_pEffectList[i]->m_sType)
                {
                    case 1: // coup normal
                        if (m_pEffectList[i]->m_cFrame == 1)
                        {
                            for (int j = 1; j <= m_pEffectList[i]->m_iV1; j++) bAddNewEffect(11, m_pEffectList[i]->m_mX + 15 - (rand() % 30), m_pEffectList[i]->m_mY + 15 - (rand() % 30), 0, 0, -1 * (rand() % 2));
                        }
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 2:	// (Arrow missing target ?)
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32 - 40,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 70);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32 - 40)) <= 2))
                        {	//bAddNewEffect(14, m_pEffectList[i]->m_mX +(rand() % 5) - 2, m_pEffectList[i]->m_mY +(rand() % 5) - 2, 0, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 4: // Gold Drop ,33,69,70
                    case 33: //
                    case 69:
                    case 70:
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 5:
                    case 30:
                    case 31: // Fire Explosion
                    case 252:
                        if (m_pEffectList[i]->m_cFrame == 1)
                        {
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                        }
                        if (m_pEffectList[i]->m_cFrame == 7)
                        {
                            bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0);
                            bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0);
                            bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0);
                        }
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 6: // Lightning Bolt Burst
                        if (m_pEffectList[i]->m_cFrame == 1)
                        {
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                        }
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 7: // Magic Missile Burst
                        if (m_pEffectList[i]->m_cFrame == 1)
                        {
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                        }
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 9:  // Burst Type 2
                    case 11: // Burst Type 3
                        m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
                        m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
                        m_pEffectList[i]->m_rY++;
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 10: // Lightning Arrow Burst
                        if (m_pEffectList[i]->m_cFrame == 1)
                        {
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                        }
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 12: // Burst Type 4
                        m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
                        m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 13: // Bulles druncncity
                        if (m_pEffectList[i]->m_cFrame < 15)
                        {
                            if ((rand() % 2) == 0)
                                m_pEffectList[i]->m_mX++;
                            else m_pEffectList[i]->m_mX--;
                            m_pEffectList[i]->m_mY--;
                        }
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 16: //
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 40);
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2))
                        {
                            bAddNewEffect(18, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, 0, 0, 0); // testcode 0111 18
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(9, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY + 20 - (rand() % 40), 0, 0, -1 * (rand() % 2));
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 17: // Ice-Storm
                        cDir = m_Misc.cGetNextMoveDir(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, m_pEffectList[i]->m_mX3, m_pEffectList[i]->m_mY3);
                        switch (cDir)
                        {
                            case 1:
                                m_pEffectList[i]->m_rY -= 2;
                                break;
                            case 2:
                                m_pEffectList[i]->m_rY -= 2;
                                m_pEffectList[i]->m_rX += 2;
                                break;
                            case 3:
                                m_pEffectList[i]->m_rX += 2;
                                break;
                            case 4:
                                m_pEffectList[i]->m_rX += 2;
                                m_pEffectList[i]->m_rY += 2;
                                break;
                            case 5:
                                m_pEffectList[i]->m_rY += 2;
                                break;
                            case 6:
                                m_pEffectList[i]->m_rX -= 2;
                                m_pEffectList[i]->m_rY += 2;
                                break;
                            case 7:
                                m_pEffectList[i]->m_rX -= 2;
                                break;
                            case 8:
                                m_pEffectList[i]->m_rX -= 2;
                                m_pEffectList[i]->m_rY -= 2;
                                break;
                        }
                        if (m_pEffectList[i]->m_rX < -10) m_pEffectList[i]->m_rX = -10;
                        if (m_pEffectList[i]->m_rX > 10) m_pEffectList[i]->m_rX = 10;
                        if (m_pEffectList[i]->m_rY < -10) m_pEffectList[i]->m_rY = -10;
                        if (m_pEffectList[i]->m_rY > 10) m_pEffectList[i]->m_rY = 10;
                        m_pEffectList[i]->m_mX += m_pEffectList[i]->m_rX;
                        m_pEffectList[i]->m_mY += m_pEffectList[i]->m_rY;
                        m_pEffectList[i]->m_mY3--;
                        if (m_pEffectList[i]->m_cFrame > 10)
                        {
                            m_pEffectList[i]->m_cFrame = 0;
                            if (abs(m_pEffectList[i]->m_sY - m_pEffectList[i]->m_mY3) > 100)
                            {
                                delete m_pEffectList[i];
                                m_pEffectList[i] = 0;
                            }
                        }
                        break;

                    case 20: // Critical strike with a weapon
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27: // Critical strike with a weapon
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32 - 40,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0);//-1*(rand() % 4));
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0);//-1*(rand() % 4));
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0);//-1*(rand() % 4));
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0);//-1*(rand() % 4));
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + 10 - (rand() % 20), m_pEffectList[i]->m_mY + 10 - (rand() % 20), 0, 0, 0);//-1*(rand() % 4));
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2) &&
                            (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32 - 40)) <= 2))
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 34: //
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        bAddNewEffect(33, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, 0, 0, -1 * (rand() % 4));
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2) &&
                            (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2))
                        {
                            bAddNewEffect(33, m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, 0, 0, 0); //7
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;


                    case 40:
                    case 56:
                        if (m_pEffectList[i]->m_cFrame == 9)
                        {
                            bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
                            bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
                            bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
                            bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
                            bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 100) - 50), m_pEffectList[i]->m_mY + ((rand() % 70) - 35), 0, 0, 0, 0);
                        }
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 41: //Large Type 1, 2, 3, 4
                    case 42:
                    case 43:
                    case 44:
                    case 45: // Small Type 1, 2
                    case 46:
                        if (m_pEffectList[i]->m_cFrame >= 7)
                        {
                            m_pEffectList[i]->m_mX--;
                            m_pEffectList[i]->m_mY += m_pEffectList[i]->m_iV1;
                            m_pEffectList[i]->m_iV1++;
                        }

                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            if ((m_pEffectList[i]->m_sType != 45) && (m_pEffectList[i]->m_sType != 46))
                            {
                                bAddNewEffect(50, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0);
                                bAddNewEffect(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                                bAddNewEffect(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                                bAddNewEffect(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                                bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                                bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                            }
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 47: // Blizzard
                    case 48:
                    case 49:
                        if (m_pEffectList[i]->m_cFrame >= 7)
                        {
                            m_pEffectList[i]->m_mX--;
                            m_pEffectList[i]->m_mY += m_pEffectList[i]->m_iV1;
                            m_pEffectList[i]->m_iV1 += 4;
                        }
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            if (m_pEffectList[i]->m_sType == 49)
                                bAddNewEffect(72, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0);
                            else bAddNewEffect(50, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0);
                            bAddNewEffect(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                            bAddNewEffect(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                            bAddNewEffect(14, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);

                            bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                            bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 60: //
                    case 181: // Meteor-Strike
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            bAddNewEffect(61, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
                            bAddNewEffect(63, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else if (m_pEffectList[i]->m_cFrame >= 0)
                        {
                            m_pEffectList[i]->m_mX -= 30;
                            m_pEffectList[i]->m_mY += 46;
                            bAddNewEffect(62, m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY, 0, 0, 0, 0);
                        }
                        break;

                    case 62:
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else if (m_pEffectList[i]->m_cFrame >= 0)
                        {
                            m_pEffectList[i]->m_mX += (rand() % 3) - 1;
                            m_pEffectList[i]->m_mY += (rand() % 3) - 1;
                        }
                        break;

                    case 65: // Building fire after MS (crusade) 65 & 67
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else if (m_pEffectList[i]->m_cFrame >= 0)
                        {
                            m_pEffectList[i]->m_mX += (rand() % 3) - 1;
                            m_pEffectList[i]->m_mY -= 4 + (rand() % 2);
                        }
                        break;

                    case 66:
                    case 203:
                    case 204:
                    case 205:
                    case 206:
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 68:
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else if (m_pEffectList[i]->m_cFrame == 11)
                        {
                            SetCameraShakingEffect(m_pEffectList[i]->m_iV1, 2);
                        }
                        break;

                    case 71:
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        bAddNewEffect(48, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, 0, 0, 0);
                        bAddNewEffect(51, m_pEffectList[i]->m_mX + ((rand() % 20) - 10), m_pEffectList[i]->m_mY + ((rand() % 20) - 10), 0, 0, 0, 0);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX) <= 2) &&
                            (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY)) <= 2))
                        {
                            bAddNewEffect(49, m_pEffectList[i]->m_mX/* + (rand() % 30) - 15*/, m_pEffectList[i]->m_mY/* + (rand() % 30) - 15*/, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 81: // StormBlade
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX
                            , m_pEffectList[i]->m_mY
                            , m_pEffectList[i]->m_dX * 32
                            , m_pEffectList[i]->m_dY * 32
                            , &m_pEffectList[i]->m_mX
                            , &m_pEffectList[i]->m_mY
                            , &m_pEffectList[i]->m_iErr
                            , 10);
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 85: //	Fire explosion from the ground (effect14.pak)	
                        if (m_pEffectList[i]->m_cFrame == 5)
                        {
                            bAddNewEffect(65, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY - (rand() % 30), 0, 0, -1 * (rand() % 2));
                        }
                        else if (m_pEffectList[i]->m_cFrame == 11)
                        {
                            bAddNewEffect(65, m_pEffectList[i]->m_mX + 20 - (rand() % 40), m_pEffectList[i]->m_mY - (rand() % 30), 0, 0, -1 * (rand() % 2));
                        }
                        else
                            if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                            {
                                delete m_pEffectList[i];
                                m_pEffectList[i] = 0;
                            }
                        break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                    case 109: // EP's Crystal axe hit
#endif
                    case 100: // Magic Missile
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));

                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2) &&
                            (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32/* - 40*/)) <= 2))
                        {
                            bAddNewEffect(7, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 110: // Enegy-Bolt
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
                        {
                            bAddNewEffect(6, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0); // 6 testcode 0111
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 120: // Fire Ball
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
                        {
                            bAddNewEffect(5, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 130: // Fire Strike
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
                        {
                            bAddNewEffect(5, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            bAddNewEffect(5, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7);
                            bAddNewEffect(5, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -5);
                            bAddNewEffect(5, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 137: // Lightning Arrow
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
                        {
                            bAddNewEffect(10, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 143: // Lightning
                    case 151: // Lightning-Bolt
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            bAddNewEffect(10, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            m_pEffectList[i]->m_rX = 5 - (rand() % 10);
                            m_pEffectList[i]->m_rY = 5 - (rand() % 10);
                        }
                        break;

                    case 145: // Chill-Wind
                        bAddNewEffect(40, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                        bAddNewEffect(40, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -10);
                        bAddNewEffect(40, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -6);
                        bAddNewEffect(40, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3);
                        delete m_pEffectList[i];
                        m_pEffectList[i] = 0;
                        break;

                    case 147:  // Triple-Energy-Bolt
                        bAddNewEffect(110, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                            m_pEffectList[i]->m_dX - 1, m_pEffectList[i]->m_dY - 1, 0);
                        bAddNewEffect(110, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                            m_pEffectList[i]->m_dX + 1, m_pEffectList[i]->m_dY - 1, 0);
                        bAddNewEffect(110, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                            m_pEffectList[i]->m_dX + 1, m_pEffectList[i]->m_dY + 1, 0);
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
                        lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX) * 1000;
                        PlaySound('E', 1, sDist, lPan);
                        bAddNewEffect(7, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                        delete m_pEffectList[i];
                        m_pEffectList[i] = 0;
                        break;

                    case 156: // Mass-Lightning-Arrow
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(137, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX, m_pEffectList[i]->m_dY, 0);
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX;
                            else sDist = sAbsY;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX) * 1000;
                            PlaySound('E', 1, sDist, lPan);
                        }
                        break;

                    case 157: // Ice-Strike
                        bAddNewEffect(41, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
                        for (x = 0; x < 14; x++)
                        {
                            bAddNewEffect(41 + (rand() % 3), m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 90) - 45, 0, 0, -1 * x - 1, 0);
                        }
                        for (x = 0; x < 6; x++)
                        {
                            bAddNewEffect(45 + (rand() % 2), m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 90) - 45, 0, 0, -1 * x - 1 - 10, 0);
                        }
                        delete m_pEffectList[i];
                        m_pEffectList[i] = 0;
                        break;

                    case 160: // Energy-Strike
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(16, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX * 32 + 50 - (rand() % 100), m_pEffectList[i]->m_dY * 32 + 50 - (rand() % 100), 0);
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX;
                            else sDist = sAbsY;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            PlaySound('E', 1, sDist, lPan);
                        }
                        break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                    case 178: // Divine revenge
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
                        {
                            bAddNewEffect(85, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 106: // Forge's Breath
#endif
                    case 161: // Mass-Fire-Strike
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
                        {
                            bAddNewEffect(30, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            bAddNewEffect(31, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7);
                            bAddNewEffect(31, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -5);
                            bAddNewEffect(31, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 163: // Mass-Chill-Wind Chill-Wind
                        bAddNewEffect(56, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                        bAddNewEffect(56, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -10);
                        bAddNewEffect(56, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -6);
                        bAddNewEffect(56, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3);
                        bAddNewEffect(56, m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50, m_pEffectList[i]->m_dY * 32 + (rand() % 70) - 35, 0, 0, -1 * (rand() % 10));
                        bAddNewEffect(56, m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50, m_pEffectList[i]->m_dY * 32 + (rand() % 70) - 35, 0, 0, -1 * (rand() % 10));
                        bAddNewEffect(56, m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50, m_pEffectList[i]->m_dY * 32 + (rand() % 70) - 35, 0, 0, -1 * (rand() % 10));
                        bAddNewEffect(56, m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50, m_pEffectList[i]->m_dY * 32 + (rand() % 70) - 35, 0, 0, -1 * (rand() % 10));
                        delete m_pEffectList[i];
                        m_pEffectList[i] = 0;
                        break;

                    case 164: // worm-bite
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            bAddNewEffect(68, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0); // testcode 0111 18
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 170: // Bloody-Shock-Wave
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else if ((m_pEffectList[i]->m_cFrame % 2) == 0)
                        {
                            bAddNewEffect(34, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX * 32 + 30 - (rand() % 60), m_pEffectList[i]->m_dY * 32 + 30 - (rand() % 60), 0);
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX;
                            else sDist = sAbsY;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            PlaySound('E', 1, sDist, lPan);
                        }
                        break;

                    case 172: // Mass-Ice-Strike
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 0);
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3), 0);
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3), 0);
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3), 0);
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3), 0);
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3), 0);
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3), 0);
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3), 0);
                        bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * (rand() % 3), 0);
                        for (x = 0; x < 16; x++)
                        {
                            bAddNewEffect(44, m_pEffectList[i]->m_dX * 32 + (rand() % 110) - 55 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 100) - 50, 0, 0, -1 * x - 1, 0);
                        }
                        for (x = 0; x < 8; x++)
                        {
                            bAddNewEffect(45 + (rand() % 2), m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 90) - 45, 0, 0, -1 * x - 1 - 10, 0);
                        }
                        delete m_pEffectList[i];
                        m_pEffectList[i] = 0;
                        break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                    case 193: // Mass Lightning-Strike	// Doublé et élargi l'effêt
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(151, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX + (rand() % 5) - 1, m_pEffectList[i]->m_dY + (rand() % 5) - 1, 0);
                            bAddNewEffect(151, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX + (rand() % 5) - 1, m_pEffectList[i]->m_dY + (rand() % 5) - 1, 0);
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX;
                            else sDist = sAbsY;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            PlaySound('E', 1, sDist / 2, lPan);
                        }
                        break;
#endif
                    case 174: // Lightning-Strike
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(151, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX + (rand() % 3) - 1, m_pEffectList[i]->m_dY + (rand() % 3) - 1, 0);
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX;
                            else sDist = sAbsY;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            PlaySound('E', 1, sDist, lPan);
                        }
                        break;

#ifndef DEF_EQUILIBRIUM_PROJECT
                    case 182: // Mass-Magic-Missile
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX
                            , m_pEffectList[i]->m_mY
                            , m_pEffectList[i]->m_dX * 32
                            , m_pEffectList[i]->m_dY * 32
                            , &m_pEffectList[i]->m_mX
                            , &m_pEffectList[i]->m_mY
                            , &m_pEffectList[i]->m_iErr
                            , 50);
                        bAddNewEffect(8, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, -1 * (rand() % 4));
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
                        {	// JLE 0043132A
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(35, m_pEffectList[i]->m_dX * 32 + 22, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7, 1);
                            bAddNewEffect(36, m_pEffectList[i]->m_dX * 32 - 22, m_pEffectList[i]->m_dY * 32 - 7, 0, 0, -7, 1);
                            bAddNewEffect(36, m_pEffectList[i]->m_dX * 32 + 30, m_pEffectList[i]->m_dY * 32 - 22, 0, 0, -5, 1);
                            bAddNewEffect(36, m_pEffectList[i]->m_dX * 32 + 12, m_pEffectList[i]->m_dY * 32 + 22, 0, 0, -3, 1);
                        }
                        break;
#endif

#ifdef DEF_EQUILIBRIUM_PROJECT
                    case 185: // EP's Blizzard = Standard Blizzard
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else /*if (m_pEffectList[i]->m_cFrame == 1)*/
                        {
                            bAddNewEffect(71, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX * 32 + (rand() % 120) - 60, m_pEffectList[i]->m_dY * 32 + (rand() % 120) - 60, 0);
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX;
                            else sDist = sAbsY;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            PlaySound('E', 1, sDist, lPan);
                        }
                        break;

                    case 191: // EP's Mass Blizzard
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else /*if (m_pEffectList[i]->m_cFrame == 1)*/
                        {
                            bAddNewEffect(71, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX * 32 + (rand() % 120) - 60, m_pEffectList[i]->m_dY * 32 + (rand() % 120) - 60, 0);
                            bAddNewEffect(71, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX * 32 + (rand() % 240) - 120, m_pEffectList[i]->m_dY * 32 + (rand() % 240) - 120, 0);
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX;
                            else sDist = sAbsY;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            PlaySound('E', 1, sDist / 2, lPan);
                        }
                        break;

#else // Standard Blizzard
                    case 191: // Blizzard
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else /*if (m_pEffectList[i]->m_cFrame == 1)*/
                        {
                            bAddNewEffect(71, m_pEffectList[i]->m_sX, m_pEffectList[i]->m_sY,
                                m_pEffectList[i]->m_dX * 32 + (rand() % 120) - 60, m_pEffectList[i]->m_dY * 32 + (rand() % 120) - 60, 0);
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX;
                            else sDist = sAbsY;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            PlaySound('E', 1, sDist, lPan);
                        }
                        break;

#endif

                    case 196: // Earth-Shock-Wave
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX
                            , m_pEffectList[i]->m_mY
                            , m_pEffectList[i]->m_dX * 32
                            , m_pEffectList[i]->m_dY * 32
                            , &m_pEffectList[i]->m_mX
                            , &m_pEffectList[i]->m_mY
                            , &m_pEffectList[i]->m_iErr
                            , 40);
                        bAddNewEffect(80, m_pEffectList[i]->m_mX + (rand() % 30) - 15, m_pEffectList[i]->m_mY + (rand() % 30) - 15, 0, 0, 0, 1);
                        bAddNewEffect(80, m_pEffectList[i]->m_mX + (rand() % 20) - 10, m_pEffectList[i]->m_mY + (rand() % 20) - 10, 0, 0, 0, 0);
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            sAbsX = abs(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            sAbsY = abs(((m_sViewPointY / 32) + 7) - m_pEffectList[i]->m_dY);
                            if (sAbsX > sAbsY) sDist = sAbsX - 10;
                            else sDist = sAbsY - 10;
                            lPan = -(((m_sViewPointX / 32) + 10) - m_pEffectList[i]->m_dX);
                            PlaySound('E', 1, sDist, lPan);
                        }
                        break;


#ifdef DEF_EQUILIBRIUM_PROJECT
                    case 197: // Explosion
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX, m_pEffectList[i]->m_mY,
                            m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32/* - 40*/,
                            &m_pEffectList[i]->m_mX, &m_pEffectList[i]->m_mY,
                            &m_pEffectList[i]->m_iErr, 50);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - m_pEffectList[i]->m_dY * 32) <= 2))
                        {
                            bAddNewEffect(30, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            bAddNewEffect(31, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7);
                            bAddNewEffect(31, m_pEffectList[i]->m_dX * 32 + 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -5);
                            bAddNewEffect(31, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3);

                            bAddNewEffect(31, m_pEffectList[i]->m_dX * 32 + 10, m_pEffectList[i]->m_dY * 32 - 50, 0, 0, -6);
                            bAddNewEffect(31, m_pEffectList[i]->m_dX * 32 - 50, m_pEffectList[i]->m_dY * 32 + 20, 0, 0, -1);


                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;
#endif

                    case 200:
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(203, m_pEffectList[i]->m_sX + 40, m_pEffectList[i]->m_sY + 120, 0, 0, 0, 0);
                            bAddNewEffect(204, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 70, 0, 0, 0, 0);
                            bAddNewEffect(205, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 75, 0, 0, 0, 0);
                            bAddNewEffect(206, m_pEffectList[i]->m_sX - 7, m_pEffectList[i]->m_sY + 27, 0, 0, 0, 0);
                            bAddNewEffect(201, (rand() % 160) + 320, (rand() % 120) + 240, 0, 0, 0, 1);
                            bAddNewEffect(202, (rand() % 160) + 320, (rand() % 120) + 240, 0, 0, 0, 1);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 201:
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(203, m_pEffectList[i]->m_sX + 110, m_pEffectList[i]->m_sY + 120, 0, 0, 0, 0);
                            bAddNewEffect(204, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 70, 0, 0, 0, 0);
                            bAddNewEffect(205, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 75, 0, 0, 0, 0);
                            bAddNewEffect(202, (rand() % 160) + 320, (rand() % 120) + 240, 0, 0, 0, 1);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 202:
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(203, m_pEffectList[i]->m_sX + 65, m_pEffectList[i]->m_sY + 120, 0, 0, 0, 0);
                            bAddNewEffect(204, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 70, 0, 0, 0, 0);
                            bAddNewEffect(205, m_pEffectList[i]->m_sX - 10, m_pEffectList[i]->m_sY + 75, 0, 0, 0, 0);
                            bAddNewEffect(206, m_pEffectList[i]->m_sX - 7, m_pEffectList[i]->m_sY + 27, 0, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

#ifdef DEF_EQUILIBRIUM_PROJECT // ZzZz

                    case 237: // Air Elemental Attack
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            bAddNewEffect(10, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            m_pEffectList[i]->m_rX = 5 - (rand() % 10);
                            m_pEffectList[i]->m_rY = 5 - (rand() % 10);
                        }
                        break;

                    case 238: // Ice Elemental Attack
                        bAddNewEffect(40, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0);
                        //bAddNewEffect(40, m_pEffectList[i]->m_dX*32 -30, m_pEffectList[i]->m_dY*32 -15, 0, 0, -10);
                        //bAddNewEffect(40, m_pEffectList[i]->m_dX*32 +35, m_pEffectList[i]->m_dY*32 -30, 0, 0, -6);
                        //bAddNewEffect(40, m_pEffectList[i]->m_dX*32 +20, m_pEffectList[i]->m_dY*32 +30, 0, 0, -3);
                        delete m_pEffectList[i];
                        m_pEffectList[i] = 0;
                        break;

                    case 239: // Ice Elemental OnMove
                        bAddNewEffect(41, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, m_pEffectList[i]->m_iV1);
                        for (x = 0; x < 5; x++)
                        {
                            bAddNewEffect(41 + (rand() % 3), m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 90) - 45, 0, 0, -1 * x - 1, m_pEffectList[i]->m_iV1);
                        }
                        for (x = 0; x < 3; x++)
                        {
                            bAddNewEffect(45 + (rand() % 2), m_pEffectList[i]->m_dX * 32 + (rand() % 100) - 50 + 10, m_pEffectList[i]->m_dY * 32 + (rand() % 90) - 45, 0, 0, -1 * x - 1 - 10, m_pEffectList[i]->m_iV1);
                        }
                        delete m_pEffectList[i];
                        m_pEffectList[i] = 0;
                        break;

                    case 240: // Air Elemental lightning onMove
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            m_pEffectList[i]->m_rX = 5 - (rand() % 10);
                            m_pEffectList[i]->m_rY = 5 - (rand() % 10);
                        }
                        break;

                    case 241: // Fire Elemental explosion onMove
                        if (m_pEffectList[i]->m_cFrame == 1) // etincelles qui jaillissent
                        {
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                            bAddNewEffect(12, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, -1 * (rand() % 2));
                        }
                        if (m_pEffectList[i]->m_cFrame == 7)
                        {
                            bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0);
                            if (rand() % 7 == 3) // parfois + violent!
                            {
                                bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0);
                                bAddNewEffect(15, m_pEffectList[i]->m_mX + 5 - (rand() % 10), m_pEffectList[i]->m_mY + 5 - (rand() % 10), 0, 0, 0);
                            }
                        }
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 247: // ZzZz
                        if (m_pEffectList[i]->m_cFrame >= m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else if (m_pEffectList[i]->m_iV1 == m_pEffectList[i]->m_cFrame)
                        {
                            PlaySound('M', 45, m_pEffectList[i]->m_mX3, m_pEffectList[i]->m_mY3);
                        }
                        break;
#endif

                    case 250: // Gate round
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX
                            , m_pEffectList[i]->m_mY
                            , m_pEffectList[i]->m_dX * 32
                            , m_pEffectList[i]->m_dY * 32 - 40
                            , &m_pEffectList[i]->m_mX
                            , &m_pEffectList[i]->m_mY
                            , &m_pEffectList[i]->m_iErr
                            , 10);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32 - 40)) <= 2))
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;

                    case 251: // Salmon burst (effect11s)
                        m_Misc.GetPoint(m_pEffectList[i]->m_mX
                            , m_pEffectList[i]->m_mY
                            , m_pEffectList[i]->m_dX * 32
                            , m_pEffectList[i]->m_dY * 32
                            , &m_pEffectList[i]->m_mX
                            , &m_pEffectList[i]->m_mY
                            , &m_pEffectList[i]->m_iErr
                            , 50);
                        if ((abs(m_pEffectList[i]->m_mX - m_pEffectList[i]->m_dX * 32) <= 2)
                            && (abs(m_pEffectList[i]->m_mY - (m_pEffectList[i]->m_dY * 32 - 40)) <= 2))
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        else
                        {
                            bAddNewEffect(252, m_pEffectList[i]->m_dX * 32, m_pEffectList[i]->m_dY * 32, 0, 0, 0, 1);
                            bAddNewEffect(252, m_pEffectList[i]->m_dX * 32 - 30, m_pEffectList[i]->m_dY * 32 - 15, 0, 0, -7, 1);
                            bAddNewEffect(252, m_pEffectList[i]->m_dX * 32 - 35, m_pEffectList[i]->m_dY * 32 - 30, 0, 0, -5, 1);
                            bAddNewEffect(252, m_pEffectList[i]->m_dX * 32 + 20, m_pEffectList[i]->m_dY * 32 + 30, 0, 0, -3, 1);
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;


#ifdef DEF_EQUILIBRIUM_PROJECT
                    case 103: // Abbadon's Terror
                    case 107: // Test spell
                    case 108: // Test spell
                    case 115: // EP's Stamina recovery
                    case 116: // EP's Peace spell
                    case 117: // EP's Wood Mantle
                    case 118: // Test spell
                    case 138: // Prayer
                    case 148: // Critical heal
                    case 158: // EP's Bloody Mantle
                    case 167: // Scan
                    case 168: // Mass heal
                    case 175: // Trance
                    case 182: // Warrior's spirit
                    case 186: // Regenerate
                    case 187: // EP's Magic Mantle
                    case 188: // Entangle
                    case 192: // Mass armor break
                    case 198: // Medusa Kiss
                    case 245: // Goal
                    case 246: // Goal

#endif

                    case 8:
                    case 14:
                    case 15:
                    case 18:
                    case 32:
                    case 35: //
                    case 36: //
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 57:
                    case 61:
                    case 63:
                    case 64:
                    case 67:
                    case 72:
                    case 73:
                    case 74:
                    case 75:
                    case 76:
                    case 77:
                    case 80: //
                    case 82: //

                    case 101:
                    case 102:
                    case 111:
                    case 112:
                    case 113:
                    case 121:
                    case 122:
                    case 123: // Stamina Rec
                    case 124:
                    case 125:
                    case 126:
                    case 127:
                    case 128: // Gr Stamina Rec
                    case 131:
                    case 132:
                    case 133:
                    case 134:
                    case 135:
                    case 136:
                    case 142:
                    case 144:
                    case 150: // Berserk : Cirlcle 6 magic
                    case 152: // Polymorph
                    case 153:
                    case 162:
                    case 165:
                    case 166:
                    case 171:
                    case 176: //
                    case 177: //

                    case 180:
                    case 183: //
                    case 184: // EP's Magic Drain
                    case 190:
                    case 194:
                    case 195:
                    case 242: // Mage hero effect
                    case 243: // War hero effect
                    case 244: // Mass MagicMissile
                    default:
                        if (m_pEffectList[i]->m_cFrame > m_pEffectList[i]->m_cMaxFrame)
                        {
                            delete m_pEffectList[i];
                            m_pEffectList[i] = 0;
                        }
                        break;
                }
            }
        }
    return bRet;
}


void CGame::GetPlayerTurn()
{
    char cDir;
    short sX, sY, sCnt1, sCnt2;
    int   iError;

    sX = m_sPlayerX;
    sY = m_sPlayerY;
    sCnt1 = 0;
    m_cPlayerTurn = 0;
    iError = 0;
    while (1)
    {
        cDir = cGetNextMoveDir(sX, sY, m_sCommX, m_sCommY);
        if (cDir == 0) break;
        switch (cDir)
        {
            case 1: sY--;       break;
            case 2: sX++; sY--; break;
            case 3: sX++;       break;
            case 4: sX++; sY++; break;
            case 5: sY++;       break;
            case 6: sX--; sY++; break;
            case 7: sX--;       break;
            case 8: sX--; sY--; break;
        }
        sCnt1++;
        if (sCnt1 > 30) break;
    }

    sX = m_sPlayerX;
    sY = m_sPlayerY;
    sCnt2 = 0;
    m_cPlayerTurn = 1;
    iError = 0;
    while (1)
    {
        cDir = cGetNextMoveDir(sX, sY, m_sCommX, m_sCommY);
        if (cDir == 0) break;
        switch (cDir)
        {
            case 1: sY--;       break;
            case 2: sX++; sY--; break;
            case 3: sX++;       break;
            case 4: sX++; sY++; break;
            case 5: sY++;       break;
            case 6: sX--; sY++; break;
            case 7: sX--;       break;
            case 8: sX--; sY--; break;
        }
        sCnt2++;
        if (sCnt2 > 30) break;
    }

    if (sCnt1 > sCnt2)
        m_cPlayerTurn = 0;
    else m_cPlayerTurn = 1;
}


int CGame::_iCheckDlgBoxFocus(short msX, short msY, char cButtonSide)
{
    int i;
    char cDlgID;
    short sX, sY;
    uint64_t dwTime = m_dwCurTime;
    if (cButtonSide == 1)
    {
        for (i = 0; i < 61; i++)
            if (m_cDialogBoxOrder[60 - i] != 0)
            {
                cDlgID = m_cDialogBoxOrder[60 - i];
                if ((m_stDialogBoxInfo[cDlgID].sX <= msX) && ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) >= msX) &&
                    (m_stDialogBoxInfo[cDlgID].sY <= msY) && ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) >= msY))
                {
                    EnableDialogBox(cDlgID, 0, 0, 0);

                    m_stMCursor.sPrevX = msX;
                    m_stMCursor.sPrevY = msY;
                    m_stMCursor.sDistX = msX - m_stDialogBoxInfo[cDlgID].sX;
                    m_stMCursor.sDistY = msY - m_stDialogBoxInfo[cDlgID].sY;

                    switch (cDlgID)
                    {
                        case 1:
                            if (bDlgBoxPress_Character(msX, msY) == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            break;

                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:

                        case 12:
                        case 13:
                        case 16:
                        case 17:
                        case 20:
                        case 22:
                        case 23:
                        case 24:
                        case 25:
                        case 28:
                        case 29:
                        case 30:
                        case 31:
                        case 32:
                        case 33:
                        case 34:
                        case 35:
                        case 36:
                        case 37:
                        case 38:
                        case 40:
                        case 50: // resur
                            // NPC
                        case 67:
                        case 68:
                        case 69:
                            m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                            m_stMCursor.sSelectedObjectID = cDlgID;
                            break;

                        case 2:	// (Sell Item)
                            if (bDlgBoxPress_Inventory(msX, msY) == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            break;

                        case 10:
                            sX = m_stDialogBoxInfo[10].sX;
                            sY = m_stDialogBoxInfo[10].sY;
                            if ((msX >= sX + 340) && (msX <= sX + 360) && (msY >= sY + 22) && (msY <= sY + 138))
                            {
                                m_stDialogBoxInfo[10].bIsScrollSelected = true;
                                return -1;
                            }

                            if (m_stDialogBoxInfo[10].bIsScrollSelected == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            else return -1;
                            break;

                        case 11:
                            sX = m_stDialogBoxInfo[11].sX;
                            sY = m_stDialogBoxInfo[11].sY;
                            if ((m_stDialogBoxInfo[11].cMode == 0) && (msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 20) && (msY <= sY + 330))
                            {
                                m_stDialogBoxInfo[11].bIsScrollSelected = true;
                                return -1;
                            }

                            if ((m_stDialogBoxInfo[11].bIsScrollSelected == false))
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            else return -1;
                            break;

                        case 14:
                            sX = m_stDialogBoxInfo[14].sX;
                            sY = m_stDialogBoxInfo[14].sY;
                            if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320))
                            {
                                m_stDialogBoxInfo[14].bIsScrollSelected = true;
                                return -1;
                            }

                            if (m_stDialogBoxInfo[14].bIsScrollSelected == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            else return -1;
                            break;

                        case 15:
                            sX = m_stDialogBoxInfo[15].sX;
                            sY = m_stDialogBoxInfo[15].sY;
                            if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320))
                            {
                                m_stDialogBoxInfo[15].bIsScrollSelected = true;
                                return -1;
                            }
                            if (m_stDialogBoxInfo[15].bIsScrollSelected == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            else return -1;
                            break;

                        case 18:
                            sX = m_stDialogBoxInfo[18].sX;
                            sY = m_stDialogBoxInfo[18].sY;
                            if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320))
                            {
                                m_stDialogBoxInfo[18].bIsScrollSelected = true;
                                return -1;
                            }

                            if (m_stDialogBoxInfo[18].bIsScrollSelected == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            else return -1;
                            break;

                        case 19:
                            sX = m_stDialogBoxInfo[19].sX;
                            sY = m_stDialogBoxInfo[19].sY;
                            if ((msX >= sX + 126) && (msX <= sX + 238) && (msY >= sY + 122) && (msY <= sY + 138))
                            {
                                m_stDialogBoxInfo[19].bIsScrollSelected = true;
                                return -1;
                            }
                            if ((msX >= sX + 126) && (msX <= sX + 238) && (msY >= sY + 139) && (msY <= sY + 155))
                            {
                                m_stDialogBoxInfo[19].bIsScrollSelected = true;
                                return -1;
                            }

                            if (m_stDialogBoxInfo[19].bIsScrollSelected == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            else return -1;
                            break;

                        case 21:
                            sX = m_stDialogBoxInfo[21].sX;
                            sY = m_stDialogBoxInfo[21].sY;
                            if ((msX >= sX + 240) && (msX <= sX + 260) && (msY >= sY + 40) && (msY <= sY + 320))
                            {
                                m_stDialogBoxInfo[21].bIsScrollSelected = true;
                                return -1;
                            }

                            if (m_stDialogBoxInfo[21].bIsScrollSelected == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            else return -1;
                            break;

                        case 26:
                            if (bDlgBoxPress_SkillDlg(msX, msY) == false)
                            {
                                m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                                m_stMCursor.sSelectedObjectID = cDlgID;
                            }
                            break;

                        case 27:
                            m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                            m_stMCursor.sSelectedObjectID = cDlgID;
                            break;

                        case 41: // Drag exchange confirmation dialog
                            m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                            m_stMCursor.sSelectedObjectID = cDlgID;
                            break;

                        case 42:  // Drag majestic stats
                            m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                            m_stMCursor.sSelectedObjectID = cDlgID;
                            break;

                        case 51:  // Drag Gail menu
                            m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_DLGBOX;
                            m_stMCursor.sSelectedObjectID = cDlgID;
                            break;
                    }
                    return 1;
                }
            }
        return 0;
    }
    else if (cButtonSide == 2)
    {
        if ((dwTime - m_dwDialogCloseTime) < 300) return 0;
        for (i = 0; i < 61; i++)
            if (m_cDialogBoxOrder[60 - i] != 0)
            {
                cDlgID = m_cDialogBoxOrder[60 - i];
                if ((m_stDialogBoxInfo[cDlgID].sX < msX) && ((m_stDialogBoxInfo[cDlgID].sX + m_stDialogBoxInfo[cDlgID].sSizeX) > msX) &&
                    (m_stDialogBoxInfo[cDlgID].sY < msY) && ((m_stDialogBoxInfo[cDlgID].sY + m_stDialogBoxInfo[cDlgID].sSizeY) > msY))
                {
                    if ((cDlgID != 5) && (cDlgID != 6) && (cDlgID != 8) && (cDlgID != 12) && ((cDlgID != 23) || (m_stDialogBoxInfo[23].cMode < 3)) && (cDlgID != 24) && (cDlgID != 27) && (cDlgID != 34) &&
                        (cDlgID != 33) && !((cDlgID == 32) && ((m_stDialogBoxInfo[cDlgID].cMode == 1) || (m_stDialogBoxInfo[cDlgID].cMode == 3))))
                        DisableDialogBox(cDlgID);
                    m_dwDialogCloseTime = dwTime;
                    return 1;
                }
            }
    }
    return 0;
}



void CGame::InitItemList(char * pData)
{
    char    cTotalItems;
    int     i, iAngelValue;
    short * sp;
    uint32_t * dwp;
    uint16_t * wp;
    char * cp;

    for (i = 0; i < DEF_MAXITEMS; i++)
        m_cItemOrder[i] = -1;

    for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++)
        m_sItemEquipmentStatus[i] = -1;

    for (i = 0; i < DEF_MAXITEMS; i++)
        m_bIsItemDisabled[i] = false;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    cTotalItems = *cp;
    cp++;

    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_pItemList[i] != 0)
        {
            delete m_pItemList[i];
            m_pItemList[i] = 0;
        }

    for (i = 0; i < DEF_MAXBANKITEMS; i++)
        if (m_pBankList[i] != 0)
        {
            delete m_pBankList[i];
            m_pBankList[i] = 0;
        }

    for (i = 0; i < cTotalItems; i++)
    {
        m_pItemList[i] = new class CItem;
        memcpy(m_pItemList[i]->m_cName, cp, 20);
        cp += 20;
        dwp = (uint32_t *)cp;
        m_pItemList[i]->m_dwCount = *dwp;
        m_pItemList[i]->m_sX = 40;
        m_pItemList[i]->m_sY = 30;
        cp += 4;
        m_pItemList[i]->m_cItemType = *cp;
        cp++;
        m_pItemList[i]->m_cEquipPos = *cp;
        cp++;
        if (*cp == 0) m_bIsItemEquipped[i] = false;
        else m_bIsItemEquipped[i] = true;
        cp++;
        if (m_bIsItemEquipped[i] == true)
        {
            m_sItemEquipmentStatus[m_pItemList[i]->m_cEquipPos] = i;
        }
        sp = (short *)cp;
        m_pItemList[i]->m_sLevelLimit = *sp;
        cp += 2;
        m_pItemList[i]->m_cGenderLimit = *cp;
        cp++;
        wp = (uint16_t *)cp;
        m_pItemList[i]->m_wCurLifeSpan = *wp;
        cp += 2;
        wp = (uint16_t *)cp;
        m_pItemList[i]->m_wWeight = *wp;
        cp += 2;
        sp = (short *)cp;
        m_pItemList[i]->m_sSprite = *sp;
        cp += 2;
        sp = (short *)cp;
        m_pItemList[i]->m_sSpriteFrame = *sp;
        cp += 2;
        m_pItemList[i]->m_cItemColor = *cp;
        cp++;
        m_pItemList[i]->m_sItemSpecEffectValue2 = (short)*cp; // v1.41
        cp++;
        dwp = (uint32_t *)cp;
        m_pItemList[i]->m_dwAttribute = *dwp;
        cp += 4;
        /*
        m_pItemList[i]->m_bIsCustomMade = (bool)*cp;
        cp++;
        */
        m_cItemOrder[i] = i;
        if ((m_pItemList[i]->m_cItemType == 1)
            && (m_bIsItemEquipped[i] == true)
            && (m_pItemList[i]->m_cEquipPos >= 11))
        {
            if (memcmp(m_pItemList[i]->m_cName, "AngelicPandent(STR)", 19) == 0)
            {
                iAngelValue = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
                m_iAngelicStr = iAngelValue;
            }
            else if (memcmp(m_pItemList[i]->m_cName, "AngelicPandent(DEX)", 19) == 0)
            {
                iAngelValue = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
                m_iAngelicDex = iAngelValue;
            }
            else if (memcmp(m_pItemList[i]->m_cName, "AngelicPandent(INT)", 19) == 0)
            {
                iAngelValue = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
                m_iAngelicInt = iAngelValue;
            }
            else if (memcmp(m_pItemList[i]->m_cName, "AngelicPandent(MAG)", 19) == 0)
            {
                iAngelValue = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
                m_iAngelicMag = iAngelValue;
            }
        }
    }

    cTotalItems = *cp;
    cp++;

    for (i = 0; i < DEF_MAXBANKITEMS; i++)
        if (m_pBankList[i] != 0)
        {
            delete m_pBankList[i];
            m_pBankList[i] = 0;
        }

    for (i = 0; i < cTotalItems; i++)
    {
        m_pBankList[i] = new class CItem;
        memcpy(m_pBankList[i]->m_cName, cp, 20);
        cp += 20;

        dwp = (uint32_t *)cp;
        m_pBankList[i]->m_dwCount = *dwp;
        cp += 4;

        m_pBankList[i]->m_sX = 40;
        m_pBankList[i]->m_sY = 30;

        m_pBankList[i]->m_cItemType = *cp;
        cp++;

        m_pBankList[i]->m_cEquipPos = *cp;
        cp++;

        sp = (short *)cp;
        m_pBankList[i]->m_sLevelLimit = *sp;
        cp += 2;

        m_pBankList[i]->m_cGenderLimit = *cp;
        cp++;

        wp = (uint16_t *)cp;
        m_pBankList[i]->m_wCurLifeSpan = *wp;
        cp += 2;

        wp = (uint16_t *)cp;
        m_pBankList[i]->m_wWeight = *wp;
        cp += 2;

        sp = (short *)cp;
        m_pBankList[i]->m_sSprite = *sp;
        cp += 2;

        sp = (short *)cp;
        m_pBankList[i]->m_sSpriteFrame = *sp;
        cp += 2;

        m_pBankList[i]->m_cItemColor = *cp;
        cp++;

        m_pBankList[i]->m_sItemSpecEffectValue2 = (short)*cp; // v1.41
        cp++;

        dwp = (uint32_t *)cp;
        m_pBankList[i]->m_dwAttribute = *dwp;
        cp += 4;
        /*
        m_pBankList[i]->m_bIsCustomMade = (bool)*cp;
        cp++;
        */
    }

    // Magic, Skill Mastery
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
}

void CGame::DrawDialogBoxs(short msX, short msY, short msZ, char cLB)
{
    int i;
    if (m_bIsObserverMode == true) return;
    m_stMCursor.sZ = 0;
    for (i = 0; i < 61; i++)
        if (m_cDialogBoxOrder[i] != 0)
        {
            switch (m_cDialogBoxOrder[i])
            {
                case 1:
                    //DrawDialogBox_Character(msX, msY); //@@@
                    DrawDialogBox_Character(msX, msY);
                    break;
                case 2:
                    DrawDialogBox_Inventory(msX, msY); //@@@
                    break;
                case 3:
                    DrawDialogBox_Magic(msX, msY, msZ); //@@@
                    break;
                case 4:
                    DrawDialogBox_ItemDrop(msX, msY); //@@@
                    break;
                case 5:
                    DrawDialogBox_15AgeMsg(msX, msY); //@@@
                    break;
                case 6:
                    DrawDialogBox_WarningMsg(msX, msY); //@@@
                    break;
                case 7:
                    DrawDialogBox_GuildMenu(msX, msY);
                    break;
                case 8:
                    DrawDialogBox_GuildOperation(msX, msY);
                    break;
                case 9:
                    DrawDialogBox_GuideMap(msX, msY, cLB);
                    break;
                case 10:
                    DrawDialogBox_Chat(msX, msY, msZ, cLB); //@@@
                    break;
                case 11:
                    DrawDialogBox_Shop(msX, msY, msZ, cLB); //@@@
                    break;
                case 12:
                    DrawDialogBox_LevelUpSetting(msX, msY); //@@@
                    break;
                case 13:
                    DrawDialogBox_CityHallMenu(msX, msY);
                    break;
                case 14:
                    DrawDialogBox_Bank(msX, msY, msZ, cLB); //@@@
                    break;
                case 15:
                    DrawDialogBox_Skill(msX, msY, msZ, cLB); //@@@
                    break;
                case 16:
                    DrawDialogBox_MagicShop(msX, msY, msZ); //@@@
                    break;
                case 17:
                    DrawDialogBox_QueryDropItemAmount();
                    break;
                case 18:
                    DrawDialogBox_Text(msX, msY, msZ, cLB); //@@@
                    break;
                case 19:
                    DrawDialogBox_SysMenu(msX, msY, cLB); //@@@
                    break;
                case 20:
                    DrawDialogBox_NpcActionQuery(msX, msY); //@@@
                    break;
                case 21:
                    DrawDialogBox_NpcTalk(msX, msY, cLB); //@@@
                    break;
                case 22:
                    DrawDialogBox_Map();
                    break;
                case 23:
                    DrawDialogBox_SellorRepairItem(msX, msY); //@@@
                    break;
                case 24:
                    DrawDialogBox_Fishing(msX, msY);
                    break;
                case 25:
                    DrawDialogBox_ShutDownMsg(msX, msY); //@@@
                    break;
                case 26: // Manuf
                    DrawDialogBox_SkillDlg(msX, msY, msZ, cLB);
                    break;
                case 27:
                    DrawDialogBox_Exchange(msX, msY); //@@@
                    break;
                case 28:
                    DrawDialogBox_Quest(msX, msY); //@@@
                    break;
                case 29:
                    DrawDialogBox_GaugePannel(); //@@@
                    break;
                case 30:
                    DrawDialogBox_IconPannel(msX, msY); //@@@
                    break;
                case 31:
                    DrawDialogBox_SellList(msX, msY); //@@@
                    break;
                case 32:
                    DrawDialogBox_Party(msX, msY); //@@@
                    break;
                case 33:
                    DrawDialogBox_CrusadeJob(msX, msY); //@@@
                    break;
                case 34:
                    DrawDialogBox_ItemUpgrade(msX, msY);
                    break;
                case 35:
                    DrawDialogBox_Help(msX, msY); //@@@
                    break;
                case 36:
                    DrawDialogBox_Commander(msX, msY); //@@@
                    break;
                case 37:
                    DrawDialogBox_Constructor(msX, msY); //@@@
                    break;
                case 38:
                    DrawDialogBox_Soldier(msX, msY); //@@@
                    break;
                case 40:
                    DrawDialogBox_Slates(msX, msY, msZ, cLB);
                    break;
                case 41:	// Confirmation Exchange
                    DrawDialogBox_ConfirmExchange(msX, msY);
                    break;
                case 42:
                    DrawDialogBox_ChangeStatsMajestic(msX, msY);
                    break;
                case 50: // Resurection?
                    DrawDialogBox_Resurect(msX, msY);
                    break;
                case 51: // Gail
                    DrawDialogBox_CMDHallMenu(msX, msY);
                    break;
            }
        }
    if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
    {
        if (m_iSuperAttackLeft > 0)
        {
            if (GetAsyncKeyState(VK_MENU) >> 15)
                m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL]->PutTransSprite(368, 439, 3, m_dwCurTime);
            wsprintfA(G_cTxt, "%d", m_iSuperAttackLeft);
            PutString_SprFont2(380, 454, G_cTxt, 220, 200, 200);
        }
    }
    else
    {
        if (m_iSuperAttackLeft > 0)
        {
            wsprintfA(G_cTxt, "%d", m_iSuperAttackLeft);
            PutString_SprFont2(380, 454, G_cTxt, 10, 10, 10);
        }
    }
}


void CGame::EnableDialogBox(int iBoxID, int cType, int sV1, int sV2, char * pString)
{
    int i;
    short sX, sY;

    switch (iBoxID)
    {
        case 11:
            if (m_bIsDialogEnabled[11] == false)
            {
                switch (cType)
                {
                    case 0:
                        break;
                    default:
                        _LoadShopMenuContents(cType);
                        m_stDialogBoxInfo[11].sV1 = cType;
                        m_stDialogBoxInfo[11].cMode = 0;
                        m_stDialogBoxInfo[11].sView = 0;
                        m_stDialogBoxInfo[11].bFlag = true;
                        m_stDialogBoxInfo[11].sV3 = 1;
                        break;
                }
            }
            break;

        case 12: // levelup diag
            if (m_bIsDialogEnabled[12] == false)
            {
                m_stDialogBoxInfo[12].sX = m_stDialogBoxInfo[1].sX + 20;
                m_stDialogBoxInfo[12].sY = m_stDialogBoxInfo[1].sY + 20;
                m_stDialogBoxInfo[12].sV1 = m_iLU_Point;
            }
            break;

        case 3: // Magic Dialog
            break;

        case 4:
            if (m_bIsDialogEnabled[4] == false)
            {
                m_stDialogBoxInfo[4].sView = cType;
            }
            break;

        case 5:
            if (m_bIsDialogEnabled[5] == false)
            {
                m_stDialogBoxInfo[5].sView = cType;
            }
            break;

        case 6:
            if (m_bIsDialogEnabled[6] == false)
            {
                m_stDialogBoxInfo[6].sView = cType;
            }
            break;

        case 7:
            if (m_stDialogBoxInfo[7].cMode == 1)
            {
                sX = m_stDialogBoxInfo[7].sX;
                sY = m_stDialogBoxInfo[7].sY;
                EndInputString();
                StartInputString(sX + 75, sY + 140, 21, m_cGuildName);
            }
            break;

        case 17: // demande quantité
            if (m_bIsDialogEnabled[17] == false)
            {
                m_stDialogBoxInfo[iBoxID].cMode = 1;
                m_stDialogBoxInfo[17].sView = cType;
                EndInputString();
                ZeroMemory(m_cAmountString, sizeof(m_cAmountString));
                wsprintfA(m_cAmountString, "%d", sV1);
                sX = m_stDialogBoxInfo[17].sX;
                sY = m_stDialogBoxInfo[17].sY;
                StartInputString(sX + 40, sY + 57, 11, m_cAmountString, false);
            }
            else
            {
                if (m_stDialogBoxInfo[17].cMode == 1)
                {
                    sX = m_stDialogBoxInfo[17].sX;
                    sY = m_stDialogBoxInfo[17].sY;
                    EndInputString();
                    StartInputString(sX + 40, sY + 57, 11, m_cAmountString, false);
                }
            }
            break;

        case 18:
            if (m_bIsDialogEnabled[18] == false)
            {
                switch (cType)
                {
                    case 0:
                        m_stDialogBoxInfo[18].cMode = 0;
                        m_stDialogBoxInfo[18].sView = 0;
                        break;
                    default:
                        _LoadTextDlgContents(cType);
                        m_stDialogBoxInfo[18].cMode = 0;
                        m_stDialogBoxInfo[18].sView = 0;
                        break;
                }
            }
            break;

        case 19:
            break;

        case 20: // Talk to npc or unicorn
            m_bIsItemDisabled[m_stDialogBoxInfo[20].sV1] = false;
            if (m_bIsDialogEnabled[20] == false)
            {
                m_stDialogBoxInfo[11].sV1 = m_stDialogBoxInfo[11].sV2 = m_stDialogBoxInfo[11].sV3 =
                    m_stDialogBoxInfo[11].sV4 = m_stDialogBoxInfo[11].sV5 = m_stDialogBoxInfo[11].sV6 = 0;
                m_stDialogBoxInfo[20].cMode = cType;
                m_stDialogBoxInfo[20].sView = 0;
                m_stDialogBoxInfo[20].sV1 = sV1;
                m_stDialogBoxInfo[20].sV2 = sV2;
            }
            break;

        case 21:
            if (m_bIsDialogEnabled[21] == false)
            {
                m_stDialogBoxInfo[21].cMode = cType;
                m_stDialogBoxInfo[21].sView = 0;
                m_stDialogBoxInfo[21].sV1 = _iLoadTextDlgContents2(sV1 + 20);
                m_stDialogBoxInfo[21].sV2 = sV1 + 20;
            }
            break;

        case 22:
            if (m_bIsDialogEnabled[22] == false)
            {
                m_stDialogBoxInfo[22].sV1 = sV1;
                m_stDialogBoxInfo[22].sV2 = sV2;

                m_stDialogBoxInfo[22].sSizeX = 290;
                m_stDialogBoxInfo[22].sSizeY = 290;
            }
            break;

        case 23:
            if (m_bIsDialogEnabled[23] == false)
            {
                m_stDialogBoxInfo[23].cMode = cType;
                m_stDialogBoxInfo[23].sV1 = sV1;		// ItemID
                m_stDialogBoxInfo[23].sV2 = sV2;
                if (cType == 2)
                {
                    m_stDialogBoxInfo[23].sX = m_stDialogBoxInfo[11].sX;
                    m_stDialogBoxInfo[23].sY = m_stDialogBoxInfo[11].sY;
                }
            }
            break;

        case 15:
            break;

        case 24:
            if (m_bIsDialogEnabled[24] == false)
            {
                m_stDialogBoxInfo[24].cMode = cType;
                m_stDialogBoxInfo[24].sV1 = sV1;
                m_stDialogBoxInfo[24].sV2 = sV2;
                m_bSkillUsingStatus = true;
            }
            break;

        case 25:
            if (m_bIsDialogEnabled[25] == false)
            {
                m_stDialogBoxInfo[25].cMode = cType;
                m_stDialogBoxInfo[25].sV1 = sV1;
                m_stDialogBoxInfo[25].sV2 = sV2;
            }
            break;

        case 26:
            switch (cType)
            {
                case 1:
                case 2: //
                    if (m_bIsDialogEnabled[26] == false)
                    {
                        m_stDialogBoxInfo[26].cMode = cType;
                        m_stDialogBoxInfo[26].sV1 = -1;
                        m_stDialogBoxInfo[26].sV2 = -1;
                        m_stDialogBoxInfo[26].sV3 = -1;
                        m_stDialogBoxInfo[26].sV4 = -1;
                        m_stDialogBoxInfo[26].sV5 = -1;
                        m_stDialogBoxInfo[26].sV6 = -1;
                        m_stDialogBoxInfo[26].cStr[0] = 0;
                        m_bSkillUsingStatus = true;
                        m_stDialogBoxInfo[26].sSizeX = 195;
                        m_stDialogBoxInfo[26].sSizeY = 215;
                        DisableDialogBox(17);
                        DisableDialogBox(20);
                        DisableDialogBox(23);
                    }
                    break;

                case 3:	//
                    if (m_bIsDialogEnabled[26] == false)
                    {
                        m_stDialogBoxInfo[26].sView = 0;
                        m_stDialogBoxInfo[26].cMode = cType;
                        m_stDialogBoxInfo[26].sV1 = -1;
                        m_stDialogBoxInfo[26].sV2 = -1;
                        m_stDialogBoxInfo[26].sV3 = -1;
                        m_stDialogBoxInfo[26].sV4 = -1;
                        m_stDialogBoxInfo[26].sV5 = -1;
                        m_stDialogBoxInfo[26].sV6 = -1;
                        m_stDialogBoxInfo[26].cStr[0] = 0;
                        m_stDialogBoxInfo[26].cStr[1] = 0;
                        m_stDialogBoxInfo[26].cStr[4] = 0;
                        m_bSkillUsingStatus = true;
                        _bCheckBuildItemStatus();
                        //m_stDialogBoxInfo[26].sX = 0;
                        //m_stDialogBoxInfo[26].sY = 0;
                        m_stDialogBoxInfo[26].sSizeX = 270;
                        m_stDialogBoxInfo[26].sSizeY = 381;
                        DisableDialogBox(17);
                        DisableDialogBox(20);
                        DisableDialogBox(23);
                    }
                    break;

                case 6:
                    if (m_bIsDialogEnabled[26] == false)
                    {
                        m_stDialogBoxInfo[26].cMode = cType;
                        m_stDialogBoxInfo[26].cStr[2] = sV1;
                        m_stDialogBoxInfo[26].cStr[3] = sV2;
                        m_stDialogBoxInfo[26].sSizeX = 270;
                        m_stDialogBoxInfo[26].sSizeY = 381;
                        m_bSkillUsingStatus = true;
                        _bCheckBuildItemStatus();
                        DisableDialogBox(17);
                        DisableDialogBox(20);
                        DisableDialogBox(23);
                    }
                    break;
                    // Crafting
                case 7:
                case 8:
                    if (m_bIsDialogEnabled[26] == false)
                    {
                        m_stDialogBoxInfo[26].cMode = cType;
                        m_stDialogBoxInfo[26].sV1 = -1;
                        m_stDialogBoxInfo[26].sV2 = -1;
                        m_stDialogBoxInfo[26].sV3 = -1;
                        m_stDialogBoxInfo[26].sV4 = -1;
                        m_stDialogBoxInfo[26].sV5 = -1;
                        m_stDialogBoxInfo[26].sV6 = -1;
                        m_stDialogBoxInfo[26].cStr[0] = 0;
                        m_stDialogBoxInfo[26].cStr[1] = 0;
                        m_bSkillUsingStatus = true;
                        //_bCheckCraftItemStatus();
                        m_stDialogBoxInfo[26].sSizeX = 195;
                        m_stDialogBoxInfo[26].sSizeY = 215;
                        DisableDialogBox(17);
                        DisableDialogBox(20);
                        DisableDialogBox(23);
                    }
                    break;
            }
            break;

        case 27:
            if (m_bIsDialogEnabled[27] == false)
            {
                m_stDialogBoxInfo[27].cMode = cType;
                for (i = 0; i < 8; i++)
                {
                    ZeroMemory(m_stDialogBoxExchangeInfo[i].cStr1, sizeof(m_stDialogBoxExchangeInfo[i].cStr1));
                    ZeroMemory(m_stDialogBoxExchangeInfo[i].cStr2, sizeof(m_stDialogBoxExchangeInfo[i].cStr2));
                    m_stDialogBoxExchangeInfo[i].sV1 = -1;
                    m_stDialogBoxExchangeInfo[i].sV2 = -1;
                    m_stDialogBoxExchangeInfo[i].sV3 = -1;
                    m_stDialogBoxExchangeInfo[i].sV4 = -1;
                    m_stDialogBoxExchangeInfo[i].sV5 = -1;
                    m_stDialogBoxExchangeInfo[i].sV6 = -1;
                    m_stDialogBoxExchangeInfo[i].sV7 = -1;
                    m_stDialogBoxExchangeInfo[i].dwV1 = 0;
                }
                DisableDialogBox(17);
                DisableDialogBox(20);
                DisableDialogBox(23);
                DisableDialogBox(26);
            }
            break;

        case 41:
            break;

        case 28:
            if (m_bIsDialogEnabled[28] == false)
            {
                m_stDialogBoxInfo[28].cMode = cType;
                m_stDialogBoxInfo[28].sX = m_stDialogBoxInfo[1].sX + 20;
                m_stDialogBoxInfo[28].sY = m_stDialogBoxInfo[1].sY + 20;
            }
            break;

        case 32:
            if (m_bIsDialogEnabled[32] == false)
            {
                m_stDialogBoxInfo[32].cMode = cType;
                m_stDialogBoxInfo[32].sX = m_stDialogBoxInfo[1].sX + 20;
                m_stDialogBoxInfo[32].sY = m_stDialogBoxInfo[1].sY + 20;
            }
            break;

        case 33:
            if ((m_iHP <= 0) || (m_bCitizen == false)) return;
            if (m_bIsDialogEnabled[33] == false)
            {
                m_stDialogBoxInfo[33].cMode = cType;
                m_stDialogBoxInfo[33].sX = 360;
                m_stDialogBoxInfo[33].sY = 65;
                m_stDialogBoxInfo[33].sV1 = sV1;
            }
            break;


#ifdef DEF_EQUILIBRIUM_PROJECT // Item upgrade
        case 34:
            if (m_bIsDialogEnabled[34] == false)
            {
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
                if (((iSoX > 0) || (iSoM > 0))
                    && (iSoO == 0))
                {
                    m_stDialogBoxInfo[34].cMode = 6; // Upgrade with Xelima/Merien
                    m_stDialogBoxInfo[34].sV1 = -1;
                    m_stDialogBoxInfo[34].sV2 = iSoX;
                    m_stDialogBoxInfo[34].sV3 = iSoM;
                    m_stDialogBoxInfo[34].sV4 = -1;
                    m_stDialogBoxInfo[34].sV5 = -1;
                    m_stDialogBoxInfo[34].sV6 = -1;
                    m_stDialogBoxInfo[34].sV7 = -1;
                    m_stDialogBoxInfo[34].dwV1 = 0;
                }
                else if ((iSoX == 0) && (iSoM == 0)
                    && (iSoO == 1) && (iSoE <= 1))
                {
                    m_stDialogBoxInfo[34].cMode = 11; // Alchemy Upgrade
                    m_stDialogBoxInfo[34].sV1 = -1;
                    m_stDialogBoxInfo[34].sV2 = -1;
                    m_stDialogBoxInfo[34].sV3 = -1;
                    m_stDialogBoxInfo[34].sV4 = iOilIndex;
                    m_stDialogBoxInfo[34].sV5 = iElixirIndex;
                    m_stDialogBoxInfo[34].sV6 = -1;
                    m_stDialogBoxInfo[34].sV7 = -1;
                    m_stDialogBoxInfo[34].dwV1 = 0;
                }
                else if ((iSoX == 0) && (iSoM == 0) && (iSoO == 0)
                    && (m_iGizonItemUpgradeLeft > 0))
                {
                    m_stDialogBoxInfo[34].cMode = 1; // gizon upgrade
                    m_stDialogBoxInfo[34].sV1 = -1;
                    m_stDialogBoxInfo[34].sV2 = -1;
                    m_stDialogBoxInfo[34].sV3 = -1;
                    m_stDialogBoxInfo[34].sV4 = -1;
                    m_stDialogBoxInfo[34].sV5 = -1;
                    m_stDialogBoxInfo[34].sV6 = -1;
                    m_stDialogBoxInfo[34].sV7 = -1;
                    m_stDialogBoxInfo[34].dwV1 = 0;
                }
                else
                {
                    m_stDialogBoxInfo[34].cMode = 5; // Main menu
                    m_stDialogBoxInfo[34].sV1 = -1;
                    m_stDialogBoxInfo[34].sV2 = iSoX;
                    m_stDialogBoxInfo[34].sV3 = iSoM;
                    m_stDialogBoxInfo[34].sV4 = iOilIndex;
                    m_stDialogBoxInfo[34].sV5 = iElixirIndex;
                    m_stDialogBoxInfo[34].sV6 = iSoX + iSoM;
                    if (iSoO == 0) m_stDialogBoxInfo[34].sV7 = 0; // No Oil present
                    else if (iSoO > 1)  m_stDialogBoxInfo[34].sV7 = 1; // Too much Oil error
                    else if (iSoE > 1)  m_stDialogBoxInfo[34].sV7 = 2; // Too much Elixir error
                    else                m_stDialogBoxInfo[34].sV7 = 3; // Correct Ol/Elixir
                    m_stDialogBoxInfo[34].dwV1 = 0;
                }
            }
            break;
#else
        case 34:
            if (m_bIsDialogEnabled[34] == false)
            {
                int iSoX, iSoM;
                iSoX = iSoM = 0;
                for (i = 0; i < DEF_MAXITEMS; i++)
                    if (m_pItemList[i] != 0)
                    {
                        if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 128)) iSoX++;
                        if ((m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 129)) iSoM++;
                    }
                if ((iSoX > 0) || (iSoM > 0))
                {
                    m_stDialogBoxInfo[34].cMode = 6; // Stone upgrade
                    m_stDialogBoxInfo[34].sV2 = iSoX;
                    m_stDialogBoxInfo[34].sV3 = iSoM;
                    m_stDialogBoxInfo[34].sV1 = -1;
                    m_stDialogBoxInfo[34].dwV1 = 0;
                }
                else if (m_iGizonItemUpgradeLeft > 0)
                {
                    m_stDialogBoxInfo[34].cMode = 1;
                    m_stDialogBoxInfo[34].sV2 = -1;
                    m_stDialogBoxInfo[34].sV3 = -1;
                    m_stDialogBoxInfo[34].sV1 = -1;
                    m_stDialogBoxInfo[34].dwV1 = 0;
                }
                else
                {
                    AddEventList(DRAW_DIALOGBOX_ITEMUPGRADE30, 10); // "Stone of Xelima or Merien is not present."
                    return;
                }
            }
            break;
#endif

        case 16:
            if (m_bIsDialogEnabled[iBoxID] == false)
            {
                if (m_cSkillMastery[4] == 0)
                {
                    DisableDialogBox(16);
                    EnableDialogBox(21, 0, 480, 0);
                    return;
                }
                else
                {
                    m_stDialogBoxInfo[iBoxID].cMode = 0;
                    m_stDialogBoxInfo[iBoxID].sView = 0;
                }
            }
            break;

        case 14:
            EndInputString();
            if (m_bIsDialogEnabled[iBoxID] == false)
            {
                m_stDialogBoxInfo[iBoxID].cMode = 0;
                m_stDialogBoxInfo[iBoxID].sView = 0;
                EnableDialogBox(2, 0, 0, 0);
            }
            break;

        case 40: // Slates
            if (m_bIsDialogEnabled[40] == false)
            {
                m_stDialogBoxInfo[40].sView = 0;
                m_stDialogBoxInfo[40].cMode = cType;
                m_stDialogBoxInfo[40].sV1 = -1;
                m_stDialogBoxInfo[40].sV2 = -1;
                m_stDialogBoxInfo[40].sV3 = -1;
                m_stDialogBoxInfo[40].sV4 = -1;
                m_stDialogBoxInfo[40].sV5 = -1;
                m_stDialogBoxInfo[40].sV6 = -1;
                m_stDialogBoxInfo[40].cStr[0] = 0;
                m_stDialogBoxInfo[40].cStr[1] = 0;
                m_stDialogBoxInfo[40].cStr[4] = 0;

                m_stDialogBoxInfo[40].sSizeX = 180;
                m_stDialogBoxInfo[40].sSizeY = 183;

                DisableDialogBox(17);
                DisableDialogBox(20);
                DisableDialogBox(23);
                DisableDialogBox(26);
            }
            break;
        case 42: // Change stats window
            if (m_bIsDialogEnabled[42] == false)
            {
                m_stDialogBoxInfo[42].sX = m_stDialogBoxInfo[12].sX + 10;
                m_stDialogBoxInfo[42].sY = m_stDialogBoxInfo[12].sY + 10;
                m_stDialogBoxInfo[42].cMode = 0;
                m_stDialogBoxInfo[42].sView = 0;
                m_bSkillUsingStatus = false;
            }
            break;
        case 50: // Resurection
            if (m_bIsDialogEnabled[50] == false)
            {
                m_stDialogBoxInfo[50].sX = 185;
                m_stDialogBoxInfo[50].sY = 100;
                m_stDialogBoxInfo[50].cMode = 0;
                m_stDialogBoxInfo[50].sView = 0;
                m_bSkillUsingStatus = false;
            }
            break;

        default:
            EndInputString();
            if (m_bIsDialogEnabled[iBoxID] == false)
            {
                m_stDialogBoxInfo[iBoxID].cMode = 0;
                m_stDialogBoxInfo[iBoxID].sView = 0;
            }
            break;
    }
    if (iBoxID != 30)
    {
        if (m_bIsDialogEnabled[iBoxID] == false)
        {
            if (m_stDialogBoxInfo[iBoxID].sY > 400) m_stDialogBoxInfo[iBoxID].sY = 410;
            if (m_stDialogBoxInfo[iBoxID].sX > 620) m_stDialogBoxInfo[iBoxID].sX = 620;
            if ((m_stDialogBoxInfo[iBoxID].sX + m_stDialogBoxInfo[iBoxID].sSizeX) < 10) m_stDialogBoxInfo[iBoxID].sX += 20;
            if ((m_stDialogBoxInfo[iBoxID].sY + m_stDialogBoxInfo[iBoxID].sSizeY) < 10) m_stDialogBoxInfo[iBoxID].sY += 20;
        }
    }
    m_bIsDialogEnabled[iBoxID] = true;
    if (pString != 0) strcpy(m_stDialogBoxInfo[iBoxID].cStr, pString);
    for (i = 0; i < 59; i++)
        if (m_cDialogBoxOrder[i] == iBoxID) m_cDialogBoxOrder[i] = 0;
    for (i = 1; i < 59; i++)
        if ((m_cDialogBoxOrder[i - 1] == 0) && (m_cDialogBoxOrder[i] != 0))
        {
            m_cDialogBoxOrder[i - 1] = m_cDialogBoxOrder[i];
            m_cDialogBoxOrder[i] = 0;
        }
    for (i = 0; i < 59; i++)
        if (m_cDialogBoxOrder[i] == 0)
        {
            m_cDialogBoxOrder[i] = iBoxID;
            return;
        }
}

void CGame::DisableDialogBox(int iBoxID)
{
    int i;

    switch (iBoxID)
    {
        case 4:
            m_bIsItemDisabled[m_stDialogBoxInfo[4].sView] = false;
            break;

        case 5:
            m_bIsItemDisabled[m_stDialogBoxInfo[5].sView] = false;
            break;

        case 6:
            m_bIsItemDisabled[m_stDialogBoxInfo[6].sView] = false;
            break;

        case 7:
            if (m_stDialogBoxInfo[7].cMode == 1)
                EndInputString();
            m_stDialogBoxInfo[7].cMode = 0;
            break;

        case 11:
            for (i = 0; i < DEF_MAXMENUITEMS; i++)
                if (m_pItemForSaleList[i] != 0)
                {
                    delete m_pItemForSaleList[i];
                    m_pItemForSaleList[i] = 0;
                }
            m_stDialogBoxInfo[39].sV3 = 0;
            m_stDialogBoxInfo[39].sV4 = 0; // v1.4
            m_stDialogBoxInfo[39].sV5 = 0;
            m_stDialogBoxInfo[39].sV6 = 0;
            break;

        case 14:
            if (m_stDialogBoxInfo[14].cMode < 0) return;
            break;

        case 17:
            if (m_stDialogBoxInfo[17].cMode == 1)
            {
                EndInputString();
                m_bIsItemDisabled[m_stDialogBoxInfo[17].sView] = false;
            }
            break;

        case 20: // v1.4
            m_bIsItemDisabled[m_stDialogBoxInfo[20].sV1] = false;
            break;

        case 21:
            if (m_stDialogBoxInfo[21].sV2 == 500)
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GETMAGICABILITY, 0, 0, 0, 0, 0);
            }
            break;

        case 24:
            m_bSkillUsingStatus = false;
            break;

        case 26:
            if (m_stDialogBoxInfo[26].sV1 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV1] = false;
            if (m_stDialogBoxInfo[26].sV2 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV2] = false;
            if (m_stDialogBoxInfo[26].sV3 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV3] = false;
            if (m_stDialogBoxInfo[26].sV4 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV4] = false;
            if (m_stDialogBoxInfo[26].sV5 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV5] = false;
            if (m_stDialogBoxInfo[26].sV6 != -1) m_bIsItemDisabled[m_stDialogBoxInfo[26].sV6] = false;
            m_bSkillUsingStatus = false;
            break;

        case 27:
            for (i = 0; i < 8; i++)
            {
                ZeroMemory(m_stDialogBoxExchangeInfo[i].cStr1, sizeof(m_stDialogBoxExchangeInfo[i].cStr1));
                ZeroMemory(m_stDialogBoxExchangeInfo[i].cStr2, sizeof(m_stDialogBoxExchangeInfo[i].cStr2));
                m_stDialogBoxExchangeInfo[i].sV1 = -1;
                m_stDialogBoxExchangeInfo[i].sV2 = -1;
                m_stDialogBoxExchangeInfo[i].sV3 = -1;
                m_stDialogBoxExchangeInfo[i].sV4 = -1;
                m_stDialogBoxExchangeInfo[i].sV5 = -1;
                m_stDialogBoxExchangeInfo[i].sV6 = -1;
                m_stDialogBoxExchangeInfo[i].sV7 = -1;
                m_stDialogBoxExchangeInfo[i].dwV1 = 0;
                if (m_bIsItemDisabled[m_stDialogBoxExchangeInfo[i].sItemID] == true)
                    m_bIsItemDisabled[m_stDialogBoxExchangeInfo[i].sItemID] = false;
            }
            break;


        case 31:
            for (i = 0; i < DEF_MAXSELLLIST; i++)
            {
                if (m_stSellItemList[i].iIndex != -1) m_bIsItemDisabled[m_stSellItemList[i].iIndex] = false;
                m_stSellItemList[i].iIndex = -1;
                m_stSellItemList[i].iAmount = 0;
            }
            break;

        case 34:
            if (m_stDialogBoxInfo[34].sV1 != -1)
                m_bIsItemDisabled[m_stDialogBoxInfo[34].sV1] = false;
            break;

        case 40:
            m_bIsItemDisabled[m_stDialogBoxInfo[40].sV1] = false;
            m_bIsItemDisabled[m_stDialogBoxInfo[40].sV2] = false;
            m_bIsItemDisabled[m_stDialogBoxInfo[40].sV3] = false;
            m_bIsItemDisabled[m_stDialogBoxInfo[40].sV4] = false;

            ZeroMemory(m_stDialogBoxInfo[40].cStr, sizeof(m_stDialogBoxInfo[40].cStr));
            ZeroMemory(m_stDialogBoxInfo[40].cStr2, sizeof(m_stDialogBoxInfo[40].cStr2));
            ZeroMemory(m_stDialogBoxInfo[40].cStr3, sizeof(m_stDialogBoxInfo[40].cStr3));
            ZeroMemory(m_stDialogBoxInfo[40].cStr4, sizeof(m_stDialogBoxInfo[40].cStr4));
            m_stDialogBoxInfo[40].sV1 = -1;
            m_stDialogBoxInfo[40].sV2 = -1;
            m_stDialogBoxInfo[40].sV3 = -1;
            m_stDialogBoxInfo[40].sV4 = -1;
            m_stDialogBoxInfo[40].sV5 = -1;
            m_stDialogBoxInfo[40].sV6 = -1;
            m_stDialogBoxInfo[40].sV9 = -1;
            m_stDialogBoxInfo[40].sV10 = -1;
            m_stDialogBoxInfo[40].sV11 = -1;
            m_stDialogBoxInfo[40].sV12 = -1;
            m_stDialogBoxInfo[40].sV13 = -1;
            m_stDialogBoxInfo[40].sV14 = -1;
            m_stDialogBoxInfo[40].dwV1 = 0;
            m_stDialogBoxInfo[40].dwV2 = 0;
            break;

        case 42:
            cStateChange1 = 0;
            cStateChange2 = 0;
            cStateChange3 = 0;
            /*	m_cLU_Str = 0;
                m_cLU_Vit = 0;
                m_cLU_Dex = 0;
                m_cLU_Int = 0;
                m_cLU_Mag = 0;
                m_cLU_Char = 0;*/
            break;

    }

    m_bIsDialogEnabled[iBoxID] = false;
    for (i = 0; i < 59; i++)
        if (m_cDialogBoxOrder[i] == iBoxID)
            m_cDialogBoxOrder[i] = 0;

    for (i = 1; i < 59; i++)
        if ((m_cDialogBoxOrder[i - 1] == 0) && (m_cDialogBoxOrder[i] != 0))
        {
            m_cDialogBoxOrder[i - 1] = m_cDialogBoxOrder[i];
            m_cDialogBoxOrder[i] = 0;
        }
}


int CGame::iGetTopDialogBoxIndex()
{
    int i;
    for (i = 58; i >= 0; i--)
        if (m_cDialogBoxOrder[i] != 0)
            return m_cDialogBoxOrder[i];

    return 0;
}



void CGame::DrawChatMsgs(short sX, short sY, short dX, short dY)
{
    int i;

    for (i = 0; i < DEF_MAXCHATMSGS; i++)
        if (m_pChatMsgList[i] != 0)
            if ((m_pChatMsgList[i]->m_sX >= sX) && (m_pChatMsgList[i]->m_sX <= dX) &&
                (m_pChatMsgList[i]->m_sY >= sY) && (m_pChatMsgList[i]->m_sY <= dY))
            {

                switch (m_pChatMsgList[i]->m_cType)
                {
                    case 41:
                    case 42:
                    case 21:
                    case 22:
                    case 23:
                        DrawChatMsgBox(m_pChatMsgList[i]->m_sX, m_pChatMsgList[i]->m_sY, i, false);
                        break;
                }
            }

    // drawing to backbuffer for a second pass?
    //m_DDraw._GetBackBufferDC();
    for (i = 0; i < DEF_MAXCHATMSGS; i++)
        if (m_pChatMsgList[i] != 0)
            if ((m_pChatMsgList[i]->m_sX >= sX) && (m_pChatMsgList[i]->m_sX <= dX) &&
                (m_pChatMsgList[i]->m_sY >= sY) && (m_pChatMsgList[i]->m_sY <= dY))
            {

                switch (m_pChatMsgList[i]->m_cType)
                {
                    case 41:
                    case 42:
                    case 21:
                    case 22:
                    case 23:
                        break;

                    case 20:
                    default:
                        DrawChatMsgBox(m_pChatMsgList[i]->m_sX, m_pChatMsgList[i]->m_sY, i, true);
                        break;
                }
            }
    //m_DDraw._ReleaseBackBufferDC();
}



void CGame::_LoadTextDlgContents(int cType)
{
    char * pContents, * token, cTemp[120], cFileName[120];
    char   seps[] = "\n";
    int    iIndex = 0, i;
    class  CStrTok * pStrTok;
    uint32_t  dwFileSize;
    HANDLE hFile;
    FILE * pFile;
    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        if (m_pMsgTextList[i] != 0)
            delete m_pMsgTextList[i];
        m_pMsgTextList[i] = 0;
    }
    // cType
    ZeroMemory(cTemp, sizeof(cTemp));
    ZeroMemory(cFileName, sizeof(cFileName));

    wsprintfA(cTemp, "contents%d", cType);
    strcat(cFileName, "contents");
    strcat(cFileName, "\\");
    strcat(cFileName, "\\");
    strcat(cFileName, cTemp);
    strcat(cFileName, ".txt");

    hFile = CreateFileA(cFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwFileSize = GetFileSize(hFile, 0);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
    pFile = fopen(cFileName, "rt");
    if (pFile == 0) return;
    else
    {
        pContents = new char[dwFileSize + 1];
        ZeroMemory(pContents, dwFileSize + 1);
        fread(pContents, dwFileSize, 1, pFile);
    }
    fclose(pFile);
    pStrTok = new class CStrTok(pContents, seps);
    token = pStrTok->pGet();
    while (token != 0)
    {
        m_pMsgTextList[iIndex] = new class CMsg(0, token, 0);
        token = pStrTok->pGet();
        iIndex++;
    }
    delete pStrTok;
    delete[] pContents;
}



int CGame::_iLoadTextDlgContents2(int iType)
{
    char * pContents, * token, cTemp[120] = {}, cFileName[120] = {};
    char   seps[] = "\n";
    int    iIndex = 0, i;
    class  CStrTok * pStrTok;
    uint32_t  dwFileSize;
    HANDLE hFile;
    FILE * pFile;
    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        if (m_pMsgTextList2[i] != 0)
            delete m_pMsgTextList2[i];
        m_pMsgTextList2[i] = 0;
    }
    // cType
    ZeroMemory(cTemp, sizeof(cTemp));
    ZeroMemory(cFileName, sizeof(cFileName));

    wsprintfA(cTemp, "contents%d", iType);

    strcat(cFileName, "contents");
    strcat(cFileName, "\\");
    strcat(cFileName, "\\");
    strcat(cFileName, cTemp);
    strcat(cFileName, ".txt");
    hFile = CreateFileA(cFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwFileSize = GetFileSize(hFile, 0);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
    pFile = fopen(cFileName, "rt");
    if (pFile == 0) return -1;
    else
    {
        pContents = new char[dwFileSize + 1];
        if (pContents == 0) return -1;
        ZeroMemory(pContents, dwFileSize + 1);
        fread(pContents, dwFileSize, 1, pFile);
    }
    fclose(pFile);
    pStrTok = new class CStrTok(pContents, seps);
    token = pStrTok->pGet();
    while (token != 0)
    {
        m_pMsgTextList2[iIndex] = new class CMsg(0, token, 0);
        token = pStrTok->pGet();
        iIndex++;
    }
    delete pStrTok;
    delete[] pContents;
    return iIndex;
}




void CGame::_LoadGameMsgTextContents()
{
    char * pContents, * token, cTemp[120] = {}, cFileName[120] = {};
    char   seps[] = ";\n";
    int    iIndex = 0, i;
    class  CStrTok * pStrTok;
    uint32_t  dwFileSize;
    HANDLE hFile;
    FILE * pFile;

    for (i = 0; i < DEF_MAXGAMEMSGS; i++)
    {
        if (m_pGameMsgList[i] != 0)
            delete m_pGameMsgList[i];
        m_pGameMsgList[i] = 0;
    }

    ZeroMemory(cTemp, sizeof(cTemp));
    ZeroMemory(cFileName, sizeof(cFileName));

    strcpy(cTemp, "GameMsgList");

    strcat(cFileName, "contents");
    strcat(cFileName, "\\");
    strcat(cFileName, "\\");
    strcat(cFileName, cTemp);
    strcat(cFileName, ".txt");

    hFile = CreateFileA(cFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwFileSize = GetFileSize(hFile, 0);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

    pFile = fopen(cFileName, "rt");
    if (pFile == 0) return;
    else
    {
        pContents = new char[dwFileSize + 1];
        ZeroMemory(pContents, dwFileSize + 1);
        fread(pContents, dwFileSize, 1, pFile);
    }

    fclose(pFile);

    pStrTok = new class CStrTok(pContents, seps);
    token = pStrTok->pGet();
    while (token != 0)
    {
        m_pGameMsgList[iIndex] = new class CMsg(0, token, 0);
        token = pStrTok->pGet();
        iIndex++;
    }

    delete pStrTok;
    delete[] pContents;
}

void CGame::_RequestMapStatus(const char * pMapName, int iMode)
{
    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_MAPSTATUS, 0, iMode, 0, 0, pMapName);
}

void CGame::AddMapStatusInfo(char * pData, bool bIsLastData)
{
    char * cp, cTotal;
    short * sp, sIndex;
    int i;

    ZeroMemory(m_cStatusMapName, sizeof(m_cStatusMapName));

    cp = (char *)(pData + 6);
    memcpy(m_cStatusMapName, cp, 10);
    cp += 10;

    sp = (short *)cp;
    sIndex = *sp;
    cp += 2;

    cTotal = *cp;
    cp++;

    for (i = 1; i <= cTotal; i++)
    {
        m_stCrusadeStructureInfo[sIndex].cType = *cp;
        cp++;
        sp = (short *)cp;
        m_stCrusadeStructureInfo[sIndex].sX = *sp;
        cp += 2;
        sp = (short *)cp;
        m_stCrusadeStructureInfo[sIndex].sY = *sp;
        cp += 2;
        m_stCrusadeStructureInfo[sIndex].cSide = *cp;
        cp++;

        sIndex++;
    }

    if (bIsLastData == true)
    {
        while (sIndex < DEF_MAXCRUSADESTRUCTURES)
        {
            m_stCrusadeStructureInfo[sIndex].cType = 0;
            m_stCrusadeStructureInfo[sIndex].sX = 0;
            m_stCrusadeStructureInfo[sIndex].sY = 0;
            m_stCrusadeStructureInfo[sIndex].cSide = 0;
            sIndex++;
        }
    }
}

// #ifdef DEF_USING_WIN_IME
// bool CGame::GetText(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
// {
//     if (m_pInputBuffer == 0) return false;
//     if (G_hEditWnd == 0) return false;
//     switch (msg)
//     {
//         case WM_CHAR:
//             if ((wparam == 22) || (wparam == 3) || (wparam == 9) || (wparam == 13)) return true;
//             if (strlen(m_pInputBuffer) < m_cInputMaxLen - 1) SendMessage(G_hEditWnd, msg, wparam, lparam);
//             return true;
//         case WM_IME_COMPOSITION:
//             if (strlen(m_pInputBuffer) < (m_cInputMaxLen - 2)) SendMessage(G_hEditWnd, msg, wparam, lparam);
//             return true;
//         case WM_IME_CHAR:
//         case WM_IME_COMPOSITIONFULL:
//         case WM_IME_CONTROL:
//         case WM_IME_ENDCOMPOSITION:
//         case WM_IME_NOTIFY:
//         case WM_IME_STARTCOMPOSITION:
//         case WM_IME_SETCONTEXT:
//         case WM_IME_KEYDOWN:
//         case WM_IME_KEYUP:
//         case WM_IME_SELECT:
//             SendMessage(G_hEditWnd, msg, wparam, lparam);
//             return true;
//         case WM_KEYUP:
//             SendMessage(G_hEditWnd, msg, wparam, lparam);
//             return false;
//         case WM_KEYDOWN:
//             if (wparam == 8) SendMessage(G_hEditWnd, msg, wparam, lparam);
//             return false;
//     }
//     return false;
// }
// 
// #else // no IME
// 
// bool CGame::GetText(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
// {
//     int len;
//     HIMC hIMC = 0;
//     if (m_pInputBuffer == 0) return false;
//     switch (msg)
//     {
//         case WM_IME_COMPOSITION:
//             ZeroMemory(m_cEdit, sizeof(m_cEdit));
//             if (lparam & GCS_RESULTSTR)
//             {
//                 hIMC = ImmGetContext(hWnd);
//                 len = ImmGetCompositionString(hIMC, GCS_RESULTSTR, 0, 0);
//                 if (len > 4) len = 4;
//                 ImmGetCompositionString(hIMC, GCS_RESULTSTR, m_cEdit, len);
//                 ImmReleaseContext(hWnd, hIMC);
//                 len = strlen(m_pInputBuffer) + strlen(m_cEdit);
//                 if (len < m_cInputMaxLen) strcpy(m_pInputBuffer + strlen(m_pInputBuffer), m_cEdit);
//                 ZeroMemory(m_cEdit, sizeof(m_cEdit));
//             }
//             else if (lparam & GCS_COMPSTR)
//             {
//                 hIMC = ImmGetContext(hWnd);
//                 len = ImmGetCompositionString(hIMC, GCS_COMPSTR, 0, 0);
//                 if (len > 4) len = 4;
//                 ImmGetCompositionString(hIMC, GCS_COMPSTR, m_cEdit, len);
//                 ImmReleaseContext(hWnd, hIMC);
//                 len = strlen(m_pInputBuffer) + strlen(m_cEdit);
//                 if (len >= m_cInputMaxLen) ZeroMemory(m_cEdit, sizeof(m_cEdit));
//             }
//             return true;
// 
//         case WM_CHAR:
//             if (wparam == 8)
//             {
//                 if (strlen(m_pInputBuffer) > 0)
//                 {
//                     len = strlen(m_pInputBuffer);
//                     switch (GetCharKind(m_pInputBuffer, len - 1))
//                     {
//                         case 1:
//                             m_pInputBuffer[len - 1] = 0;
//                             break;
//                         case 2:
//                         case 3:
//                             m_pInputBuffer[len - 2] = 0;
//                             m_pInputBuffer[len - 1] = 0;
//                             break;
//                     }
//                     ZeroMemory(m_cEdit, sizeof(m_cEdit));
//                 }
//             }
//             else if ((wparam != 9) && (wparam != 13) && (wparam != 27))
//             {
//                 len = strlen(m_pInputBuffer);
//                 if (len >= m_cInputMaxLen - 1) return false;
//                 m_pInputBuffer[len] = wparam & 0xff;
//                 m_pInputBuffer[len + 1] = 0;
//             }
//             return true;
//     }
//     return false;
// }
// #endif


int CGame::GetCharKind(char * str, int index)
{
    int kind = 1;
    do
    {
        if (kind == 2) kind = 3;
        else
        {
            if ((unsigned char)*str < 128) kind = 1;
            else kind = 2;
        }
        str++;
        index--;
    } while (index >= 0);
    return kind;
}

void CGame::ShowReceivedString(bool bIsHide)
{
    ZeroMemory(G_cTxt, sizeof(G_cTxt));

#ifdef DEF_USING_WIN_IME
    if (G_hEditWnd != 0) GetWindowText(G_hEditWnd, m_pInputBuffer, (int)m_cInputMaxLen);
    strcpy(G_cTxt, m_pInputBuffer);
#else
    strcpy(G_cTxt, m_pInputBuffer);
    if ((m_cEdit[0] != 0) && (strlen(m_pInputBuffer) + strlen(m_cEdit) + 1 <= m_cInputMaxLen))
    {
        strcpy(G_cTxt + strlen(m_pInputBuffer), m_cEdit);
    }
#endif
    if (bIsHide == true)
    {
        for (unsigned char i = 0; i < strlen(G_cTxt); i++)
            if (G_cTxt[i] != 0) G_cTxt[i] = '*';
    }

    if ((G_dwGlobalTime % 400) < 210) G_cTxt[strlen(G_cTxt)] = '_';

    PutString(m_iInputX + 1, m_iInputY + 1, G_cTxt, Color(0, 0, 0));
    PutString(m_iInputX, m_iInputY + 1, G_cTxt, Color(0, 0, 0));
    PutString(m_iInputX + 1, m_iInputY, G_cTxt, Color(0, 0, 0));
    PutString(m_iInputX, m_iInputY, G_cTxt, Color(255, 255, 255));
}

void CGame::ClearInputString()
{
    if (m_pInputBuffer != 0)	ZeroMemory(m_pInputBuffer, sizeof(m_pInputBuffer));
    ZeroMemory(m_cEdit, sizeof(m_cEdit));
#ifdef DEF_USING_WIN_IME
    if (G_hEditWnd != 0)	SetWindowText(G_hEditWnd, "");
#endif
}

void CGame::StartInputString(int sX, int sY, unsigned char iLen, char * pBuffer, bool bIsHide)
{
    m_bInputStatus = true;
    m_iInputX = sX;
    m_iInputY = sY;
    m_pInputBuffer = pBuffer;
    ZeroMemory(m_cEdit, sizeof(m_cEdit));
    m_cInputMaxLen = iLen;
#ifdef DEF_USING_WIN_IME
    if (bIsHide == false) G_hEditWnd = CreateWindow(RICHEDIT_CLASS, 0, WS_POPUP | ES_SELFIME, sX - 5, sY - 1, iLen * 12, 16, G_hWnd, (HMENU)0, G_hInstance, 0);
    else G_hEditWnd = CreateWindow(RICHEDIT_CLASS, 0, WS_POPUP | ES_PASSWORD | ES_SELFIME, sX - 5, sY - 1, iLen * 12, 16, G_hWnd, (HMENU)0, G_hInstance, 0);
    SetWindowText(G_hEditWnd, m_pInputBuffer);
    SendMessage(G_hEditWnd, EM_EXLIMITTEXT, 0, iLen - 1);
    SendMessage(G_hEditWnd, EM_SETLANGOPTIONS, 0, ~IMF_AUTOFONT);
    COMPOSITIONFORM composform;
    composform.dwStyle = CFS_POINT;
    composform.ptCurrentPos.x = sX;
    composform.ptCurrentPos.y = sY;
    HIMC hImc = ImmGetContext(G_hWnd);
    ImmSetCompositionWindow(hImc, &composform);
    int StrLen = strlen(m_pInputBuffer);
    SendMessage(G_hEditWnd, EM_SETSEL, StrLen, StrLen);
#endif
}

void CGame::EndInputString()
{
    m_bInputStatus = false;
#ifdef DEF_USING_WIN_IME
    if (G_hEditWnd != 0)
    {
        GetWindowText(G_hEditWnd, m_pInputBuffer, (int)m_cInputMaxLen);
        CANDIDATEFORM candiform;
        SendMessage(G_hEditWnd, WM_IME_CONTROL, IMC_GETCANDIDATEPOS, (LPARAM)&candiform);
        DestroyWindow(G_hEditWnd);
        G_hEditWnd = 0;
    }
#else
    int len = strlen(m_cEdit);
    if (len > 0)
    {
        m_cEdit[len] = 0;
        strcpy(m_pInputBuffer + strlen(m_pInputBuffer), m_cEdit);
        ZeroMemory(m_cEdit, sizeof(m_cEdit));
    }
#endif
}

void CGame::ReceiveString(char * pString)
{
    strcpy(pString, m_pInputBuffer);

#ifdef DEF_USING_WIN_IME
    if (G_hEditWnd != 0) GetWindowText(G_hEditWnd, pString, (int)m_cInputMaxLen);
#endif
}

void CGame::DrawNewDialogBox(char cType, int sX, int sY, int iFrame, bool bIsNoColorKey, bool bIsTrans)
{
    uint64_t dwTime = G_dwGlobalTime;

    if (m_pSprite[cType] == 0) return;
    if (bIsNoColorKey == false)
    {
        if (bIsTrans == true)
            m_pSprite[cType]->PutTransSprite2(sX, sY, iFrame, dwTime);
        else m_pSprite[cType]->PutSpriteFast(sX, sY, iFrame, dwTime);
    }
    else m_pSprite[cType]->PutSpriteFastNoColorKey(sX, sY, iFrame, dwTime);
}

void CGame::SetCameraShakingEffect(short sDist, int iMul)
{
    int iDegree;

    iDegree = 5 - sDist;
    if (iDegree <= 0) iDegree = 0;
    iDegree *= 2;

    if (iMul != 0) iDegree *= iMul;

    if (iDegree <= 2) return;

    m_iCameraShakingDegree = iDegree;
}

void CGame::MeteorStrikeComing(int iCode)
{
    switch (iCode)
    {
        case 1: //
            SetTopMsg(m_pGameMsgList[0]->m_pMsg, 5);
            break;
        case 2: //
            SetTopMsg(m_pGameMsgList[10]->m_pMsg, 10);
            break;
        case 3: //
            SetTopMsg(m_pGameMsgList[91]->m_pMsg, 5);
            break;
        case 4: //
            SetTopMsg(m_pGameMsgList[11]->m_pMsg, 10);
            break;
    }
}

void CGame::DrawObjectFOE(int ix, int iy, int iFrame)
{
    if (_iGetFOE(_tmp_iStatus) < 0) // red crusade circle
    {
        if (iFrame <= 4) m_pEffectSpr[38]->PutTransSprite(ix, iy, iFrame, G_dwGlobalTime);
    }
}

void CGame::SetTopMsg(const char * pString, unsigned char iLastSec)
{
    ZeroMemory(m_cTopMsg, sizeof(m_cTopMsg));
    strcpy(m_cTopMsg, pString);

    m_iTopMsgLastSec = iLastSec;
    m_dwTopMsgTime = G_dwGlobalTime;
}

void CGame::DrawTopMsg()
{
    if (strlen(m_cTopMsg) == 0) return;
    m_DDraw.DrawShadowBox(0, 0, 639, 30);

    if ((((G_dwGlobalTime - m_dwTopMsgTime) / 250) % 2) == 0)
        PutAlignedString(0, 639, 10, m_cTopMsg, 255, 255, 255);

    if (G_dwGlobalTime > (m_iTopMsgLastSec * 1000 + m_dwTopMsgTime))
    {
        ZeroMemory(m_cTopMsg, sizeof(m_cTopMsg));
    }
}


void CGame::CannotConstruct(int iCode)
{
    switch (iCode)
    {
        case 1: //
            SetTopMsg(m_pGameMsgList[18]->m_pMsg, 5);
            break;

        case 2: //
            wsprintfA(G_cTxt, "%s XY(%d, %d)", m_pGameMsgList[19]->m_pMsg, m_iConstructLocX, m_iConstructLocY);
            SetTopMsg(G_cTxt, 5);
            break;

        case 3: //
            SetTopMsg(m_pGameMsgList[20]->m_pMsg, 5);
            break;
        case 4: //
            SetTopMsg(m_pGameMsgList[20]->m_pMsg, 5);
            break;

    }
}

void CGame::DisplayCommaNumber_G_cTxt(int iGold)
{
    char cGold[20] = {};
    int iStrLen = 0;
    ZeroMemory(cGold, sizeof(cGold));
    ZeroMemory(G_cTxt, sizeof(G_cTxt));
    itoa(iGold, cGold, 10);
#ifdef DEF_COMMA_GOLD
    iStrLen = strlen(cGold);
    iStrLen--;
    int cnt = 0;
    for (int i = 0; i < iStrLen + 1; i++)
    {
        if ((cnt != 0) && ((cnt + 1) % 4 == 0))
        {
            G_cTxt[cnt] = ',';
            i--;
        }
        else G_cTxt[cnt] = cGold[iStrLen - i];
        cnt++;
    }
    iStrLen = strlen(G_cTxt);
    G_cTxt[iStrLen] = '\0';
    strrev(G_cTxt);
#else
    strcpy(G_cTxt, cGold);
#endif
}

void CGame::CrusadeContributionResult(int iWarContribution)
{
    int i;
    char cTemp[120] = {};
    DisableDialogBox(18);
    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        if (m_pMsgTextList[i] != 0)
            delete m_pMsgTextList[i];
        m_pMsgTextList[i] = 0;
    }
    if (iWarContribution > 0)
    {
        PlaySound('E', 23, 0, 0);
        PlaySound('C', 21, 0, 0);
        PlaySound('C', 22, 0, 0);
        m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[22]->m_pMsg, 0); // Congratulations! Your nation
        m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[23]->m_pMsg, 0); // was victory in the battle!
        m_pMsgTextList[2] = new class CMsg(0, " ", 0);
        m_pMsgTextList[3] = new class CMsg(0, m_pGameMsgList[24]->m_pMsg, 0); // As a victorious citizen
        m_pMsgTextList[4] = new class CMsg(0, m_pGameMsgList[25]->m_pMsg, 0); // You will receive
        m_pMsgTextList[5] = new class CMsg(0, m_pGameMsgList[26]->m_pMsg, 0); // a prize
        m_pMsgTextList[6] = new class CMsg(0, " ", 0);
        m_pMsgTextList[7] = new class CMsg(0, m_pGameMsgList[27]->m_pMsg, 0); // Experience point of the battle contribution:
        ZeroMemory(cTemp, sizeof(cTemp));											//
        wsprintfA(cTemp, "+%dExp Points!", iWarContribution);
        m_pMsgTextList[8] = new class CMsg(0, cTemp, 0);
        for (i = 9; i < 18; i++)
            m_pMsgTextList[i] = new class CMsg(0, " ", 0);

    }
    else if (iWarContribution < 0)
    {
        PlaySound('E', 24, 0, 0);
        PlaySound('C', 12, 0, 0);
        PlaySound('C', 13, 0, 0);
        m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[28]->m_pMsg, 0); // Unfortunately! Your country
        m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[29]->m_pMsg, 0); // have lost the all out war.
        m_pMsgTextList[2] = new class CMsg(0, " ", 0);
        m_pMsgTextList[3] = new class CMsg(0, m_pGameMsgList[30]->m_pMsg, 0); // As a losser citizen;
        m_pMsgTextList[4] = new class CMsg(0, m_pGameMsgList[31]->m_pMsg, 0); // the prize that accomplishes
        m_pMsgTextList[5] = new class CMsg(0, m_pGameMsgList[32]->m_pMsg, 0); // will not be given.
        m_pMsgTextList[6] = new class CMsg(0, " ", 0);
        m_pMsgTextList[7] = new class CMsg(0, m_pGameMsgList[33]->m_pMsg, 0); // I hope you to win
        m_pMsgTextList[8] = new class CMsg(0, m_pGameMsgList[34]->m_pMsg, 0); // in the next battle
        for (i = 9; i < 18; i++)
            m_pMsgTextList[i] = new class CMsg(0, " ", 0);
    }
    else if (iWarContribution == 0)
    {
        PlaySound('E', 25, 0, 0);
        m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[50]->m_pMsg, 0); // The battle that you have participated
        m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[51]->m_pMsg, 0); // is already finished;
        m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[52]->m_pMsg, 0); //
        m_pMsgTextList[3] = new class CMsg(0, " ", 0);
        m_pMsgTextList[4] = new class CMsg(0, m_pGameMsgList[53]->m_pMsg, 0); // You must connect after finishing
        m_pMsgTextList[5] = new class CMsg(0, m_pGameMsgList[54]->m_pMsg, 0); // the previous and before starting
        m_pMsgTextList[6] = new class CMsg(0, m_pGameMsgList[55]->m_pMsg, 0); // the next battle so you can receive
        m_pMsgTextList[7] = new class CMsg(0, m_pGameMsgList[56]->m_pMsg, 0); // the prize
        for (i = 8; i < 18; i++)
            m_pMsgTextList[i] = new class CMsg(0, " ", 0);
    }
    EnableDialogBox(18, 0, 0, 0);
}

void CGame::CrusadeWarResult(int iWinnerSide)
{
    int i, iPlayerSide;
    DisableDialogBox(18);
    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        if (m_pMsgTextList[i] != 0)
            delete m_pMsgTextList[i];
        m_pMsgTextList[i] = 0;
    }
    if (m_bCitizen == false) iPlayerSide = 0;
    else if (m_bAresden == true) iPlayerSide = 1;
    else if (m_bAresden == false) iPlayerSide = 2;
    if (iPlayerSide == 0)
    {
        switch (iWinnerSide)
        {
            case 0:
                PlaySound('E', 25, 0, 0);
                m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[35]->m_pMsg, 0); // All out war finished!
                m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[36]->m_pMsg, 0); // There was a draw in the
                m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[37]->m_pMsg, 0); // battle
                m_pMsgTextList[3] = new class CMsg(0, " ", 0);
                break;
            case 1:
                PlaySound('E', 25, 0, 0);
                m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[35]->m_pMsg, 0); // All out war finished!
                m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[38]->m_pMsg, 0); // Aresden was victorious
                m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[39]->m_pMsg, 0); // and put an end to the war
                m_pMsgTextList[3] = new class CMsg(0, " ", 0);
                break;
            case 2:
                PlaySound('E', 25, 0, 0);
                m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[35]->m_pMsg, 0); // All out war finished!
                m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[40]->m_pMsg, 0); // Elvine was victorious
                m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[41]->m_pMsg, 0); // and put an end to the war
                m_pMsgTextList[3] = new class CMsg(0, " ", 0);
                break;
        }
        for (i = 4; i < 18; i++)
            m_pMsgTextList[i] = new class CMsg(0, " ", 0);
    }
    else
    {
        if (iWinnerSide == 0)
        {
            PlaySound('E', 25, 0, 0);
            m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[35]->m_pMsg, 0); // All out war finished!
            m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[36]->m_pMsg, 0); // There was a draw in the
            m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[37]->m_pMsg, 0); // battle
            m_pMsgTextList[3] = new class CMsg(0, " ", 0);
            for (i = 4; i < 18; i++)
                m_pMsgTextList[i] = new class CMsg(0, " ", 0);
        }
        else
        {
            if (iWinnerSide == iPlayerSide)
            {
                PlaySound('E', 23, 0, 0);
                PlaySound('C', 21, 0, 0);
                PlaySound('C', 22, 0, 0);
                switch (iWinnerSide)
                {
                    case 1:
                        m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[35]->m_pMsg, 0); // All out war finished!;
                        m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[38]->m_pMsg, 0); // Aresden was victorious;
                        m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[39]->m_pMsg, 0); // and put an end to the war
                        m_pMsgTextList[3] = new class CMsg(0, " ", 0);
                        m_pMsgTextList[4] = new class CMsg(0, m_pGameMsgList[42]->m_pMsg, 0); // Congratulations!
                        m_pMsgTextList[5] = new class CMsg(0, m_pGameMsgList[43]->m_pMsg, 0); // As a victorious citizen
                        m_pMsgTextList[6] = new class CMsg(0, m_pGameMsgList[44]->m_pMsg, 0); // You will receive
                        m_pMsgTextList[7] = new class CMsg(0, m_pGameMsgList[45]->m_pMsg, 0); // a prize
                        break;
                    case 2:
                        m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[35]->m_pMsg, 0); // All out war finished!
                        m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[40]->m_pMsg, 0); // Elvine was victorious
                        m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[41]->m_pMsg, 0); // and put an end to the war
                        m_pMsgTextList[3] = new class CMsg(0, " ", 0);
                        m_pMsgTextList[4] = new class CMsg(0, m_pGameMsgList[42]->m_pMsg, 0); // Congratulations!
                        m_pMsgTextList[5] = new class CMsg(0, m_pGameMsgList[43]->m_pMsg, 0); // As a victorious citizen
                        m_pMsgTextList[6] = new class CMsg(0, m_pGameMsgList[44]->m_pMsg, 0); // You will receive
                        m_pMsgTextList[7] = new class CMsg(0, m_pGameMsgList[45]->m_pMsg, 0); // a prize
                        break;
                }
                for (i = 8; i < 18; i++)
                    m_pMsgTextList[i] = new class CMsg(0, " ", 0);
            }
            else if (iWinnerSide != iPlayerSide)
            {
                PlaySound('E', 24, 0, 0);
                PlaySound('C', 12, 0, 0);
                PlaySound('C', 13, 0, 0);
                switch (iWinnerSide)
                {
                    case 1:
                        m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[35]->m_pMsg, 0); // All out war finished!
                        m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[38]->m_pMsg, 0); // Aresden was victorious;
                        m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[39]->m_pMsg, 0); // and put an end to the war
                        m_pMsgTextList[3] = new class CMsg(0, " ", 0);
                        m_pMsgTextList[4] = new class CMsg(0, m_pGameMsgList[46]->m_pMsg, 0); // Unfortunately,
                        m_pMsgTextList[5] = new class CMsg(0, m_pGameMsgList[47]->m_pMsg, 0); // As a losser citizen
                        m_pMsgTextList[6] = new class CMsg(0, m_pGameMsgList[48]->m_pMsg, 0); // the prize that accomplishes
                        m_pMsgTextList[7] = new class CMsg(0, m_pGameMsgList[49]->m_pMsg, 0); // will not be given.
                        break;
                    case 2:
                        m_pMsgTextList[0] = new class CMsg(0, m_pGameMsgList[35]->m_pMsg, 0); // All out war finished!
                        m_pMsgTextList[1] = new class CMsg(0, m_pGameMsgList[40]->m_pMsg, 0); // Elvine was victorious
                        m_pMsgTextList[2] = new class CMsg(0, m_pGameMsgList[41]->m_pMsg, 0); // and put an end to the war
                        m_pMsgTextList[3] = new class CMsg(0, " ", 0);
                        m_pMsgTextList[4] = new class CMsg(0, m_pGameMsgList[46]->m_pMsg, 0); // Unfortunately,
                        m_pMsgTextList[5] = new class CMsg(0, m_pGameMsgList[47]->m_pMsg, 0); // As a losser citizen
                        m_pMsgTextList[6] = new class CMsg(0, m_pGameMsgList[48]->m_pMsg, 0); // the prize that accomplishes
                        m_pMsgTextList[7] = new class CMsg(0, m_pGameMsgList[49]->m_pMsg, 0); // will not be given.
                        break;
                }
                for (i = 8; i < 18; i++)
                    m_pMsgTextList[i] = new class CMsg(0, " ", 0);
            }
        }
    }
    EnableDialogBox(18, 0, 0, 0);
    DisableDialogBox(36);
    DisableDialogBox(37);
    DisableDialogBox(38);
}

void CGame::DrawChatMsgBox(short sX, short sY, int iChatIndex, bool bIsPreDC)
{
    char cMsg[100] = {}, cMsgA[22] = {}, cMsgB[22] = {}, cMsgC[22] = {}, * cp;
    int  iRet, iLines, i, iSize, iSize2, iLoc, iFontSize;
    uint64_t dwTime;
    Color rgb;
    bool bIsTrans;
    RECT rcRect = {};
    SIZE Size = {};

    ZeroMemory(cMsg, sizeof(cMsg));
    ZeroMemory(cMsgA, sizeof(cMsgA));
    ZeroMemory(cMsgB, sizeof(cMsgB));
    ZeroMemory(cMsgC, sizeof(cMsgC));

    dwTime = m_pChatMsgList[iChatIndex]->m_dwTime;
    strcpy(cMsg, m_pChatMsgList[iChatIndex]->m_pMsg);
    cp = (char *)cMsg;
    iLines = 0;

    rgb = Color(255, 255, 255);
    switch (m_pChatMsgList[iChatIndex]->m_cType)
    {
        case 1:
            rgb = Color(255, 255, 255);
            break;
        case 20:
            rgb = Color(255, 255, 20);
            // ¸Þ½ÃÁö Ç¥½Ã¿¡ µô·¹ÀÌ°¡ °É¸°´Ù.
            if ((m_dwCurTime - dwTime) < 650) return;
            else dwTime += 650;
            break;
        case 41:
            rgb = Color(255, 80, 80);
            break;

        case 42:
            rgb = Color(255, 80, 80);
            if ((m_dwCurTime - dwTime) < 650) return;
            else dwTime += 650;
            break;
    }

    if (strlen(cp) != 0)
    {
        memcpy(cMsgA, cp, 20);

        iRet = GetCharKind(cMsgA, 19);
        if (iRet == CODE_HAN1)
        {
            cMsgA[20] = cp[20];
            cp++;
        }
        cp += 20;
        iLines = 1;
    }

    if (strlen(cp) != 0)
    {
        memcpy(cMsgB, cp, 20);

        iRet = GetCharKind(cMsgB, 19);
        if (iRet == CODE_HAN1)
        {
            cMsgB[20] = cp[20];
            cp++;
        }
        cp += 20;
        iLines = 2;
    }

    if (strlen(cp) != 0)
    {
        memcpy(cMsgC, cp, 20);

        iRet = GetCharKind(cMsgC, 19);
        if (iRet == CODE_HAN1)
        {
            cMsgC[20] = cp[20];
            cp++;
        }
        cp += 20;
        iLines = 3;
    }

    iSize = 0;
    for (i = 0; i < 20; i++)
        if (cMsgA[i] != 0)

            if ((unsigned char)cMsgA[i] >= 128)
            {
                iSize += 5;	//6
                i++;
            }
            else iSize += 4;

    iLoc = m_dwCurTime - dwTime;
    switch (m_pChatMsgList[iChatIndex]->m_cType)
    {
        case 21:
        case 22:
        case 23://...
            if (iLoc > 80) iLoc = 10;
            else iLoc = iLoc >> 3;
            break;
        default://
            if (iLoc > 352) iLoc = 9;
            else if (iLoc > 320) iLoc = 10;
            else iLoc = iLoc >> 5;
            break;
    }

    if (m_cDetailLevel == 0)
        bIsTrans = false;
    else bIsTrans = true;

    switch (m_pChatMsgList[iChatIndex]->m_cType)
    {
        case 41:
        case 42:
            iSize2 = 0;
            for (i = 0; i < 100; i++)
                if (cMsg[i] != 0)
                    if ((unsigned char)cMsg[i] >= 128)
                    {
                        iSize2 += 5;
                        i++;
                    }
                    else iSize2 += 4;
            if (m_Misc.bCheckIMEString(cMsg) == false)
            {
                PutString(sX - iSize2, sY - 65 - iLoc, cMsg, Color(180, 30, 30));
                PutString(sX - iSize2 + 1, sY - 65 - iLoc, cMsg, Color(180, 30, 30));
            }
            else PutString_SprFont3(sX - iSize2, sY - 65 - iLoc, cMsg, m_wR[14] * 4, m_wG[14] * 4, m_wB[14] * 4, false, 0);
            break;

        case 21:
        case 22:
        case 23:
            iFontSize = 23 - (int)m_pChatMsgList[iChatIndex]->m_cType;
            switch (iLines)
            {
                case 1:
                    PutString_SprFont3(sX - iSize, sY - 65 - iLoc, cMsgA, m_wR[13] * 2, m_wG[13] * 2, m_wB[13] * 2, bIsTrans, iFontSize);
                    break;
                case 2:
                    PutString_SprFont3(sX - iSize, sY - 81 - iLoc, cMsgA, m_wR[13] * 2, m_wG[13] * 2, m_wB[13] * 2, bIsTrans, iFontSize);
                    PutString_SprFont3(sX - iSize, sY - 65 - iLoc, cMsgB, m_wR[13] * 2, m_wG[13] * 2, m_wB[13] * 2, bIsTrans, iFontSize);
                    break;
                case 3:
                    PutString_SprFont3(sX - iSize, sY - 97 - iLoc, cMsgA, m_wR[13] * 2, m_wG[13] * 2, m_wB[13] * 2, bIsTrans, iFontSize);
                    PutString_SprFont3(sX - iSize, sY - 81 - iLoc, cMsgB, m_wR[13] * 2, m_wG[13] * 2, m_wB[13] * 2, bIsTrans, iFontSize);
                    PutString_SprFont3(sX - iSize, sY - 65 - iLoc, cMsgC, m_wR[13] * 2, m_wG[13] * 2, m_wB[13] * 2, bIsTrans, iFontSize);
                    break;
            }
            break;

        case 20:
        default:
            PutChatString(sX - 80 + 1, sY - 65 - iLoc, (char *)cMsg, Color(0, 0, 0));
            PutChatString(sX - 80, sY - 65 - iLoc + 1, (char *)cMsg, Color(0, 0, 0));
            PutChatString(sX - 80, sY - 65 - iLoc, (char *)cMsg, rgb);
            break;
    }
}

void CGame::ClearContents_OnSelectCharacter()
{
    m_cCurFocus = 1;
}

void CGame::CivilRightAdmissionHandler(char * pData)
{
    uint16_t * wp, wResult;
    char * cp;

    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    wResult = *wp;

    switch (wResult)
    {
        case 0:
            m_stDialogBoxInfo[13].cMode = 4;
            break;

        case 1:
            m_stDialogBoxInfo[13].cMode = 3;
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ZeroMemory(m_cLocation, sizeof(m_cLocation));
            memcpy(m_cLocation, cp, 10);
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
            break;
    }
}

void CGame::_RemoveChatMsgListByObjectID(int iObjectID)
{
    int i;

    for (i = 1; i < DEF_MAXCHATMSGS; i++)
        if ((m_pChatMsgList[i] != 0) && (m_pChatMsgList[i]->m_iObjectID == iObjectID))
        {
            delete m_pChatMsgList[i];
            m_pChatMsgList[i] = 0;
        }
}

void CGame::PlaySound(char cType, int iNum, int iDist, long lPan)
{
    int iVol;
    float fPan = lPan;
    float forward = 0;

    if (m_bSoundFlag == false) return;
    if (m_bSoundStat == false) return;

    if (iDist > 10) iDist = 10;

    iVol = (m_cSoundVolume - 100) * 20;
    iVol += -200 * iDist;

    if (iVol > 0) iVol = 0;
    if (iVol < -10000) iVol = -10000;

    if (fPan != 0)
    {
        fPan -= 0.5f;
        forward = -4;
    }
    if (fPan > 0) fPan -= 3.f;
    else if (fPan < 0) fPan += 3.f;

    if (fPan >= -3 && fPan <= 3)
        fPan = 0;

    if (iVol > -2000)
    {
        switch (cType)
        {
            case 'C':
                m_pCSound[iNum].setMinDistance(4.f);
                m_pCSound[iNum].setAttenuation(1.f);
                m_pCSound[iNum].setPosition({ (float)fPan, 0 , forward });
                m_pCSound[iNum].play();
                break;

            case 'M':
                m_pMSound[iNum].setMinDistance(4.f);
                m_pMSound[iNum].setAttenuation(1.f);
                m_pMSound[iNum].setPosition({ (float)fPan, 0, forward });
                m_pMSound[iNum].play();
                break;

            case 'E':
                m_pESound[iNum].setMinDistance(4.f);
                m_pESound[iNum].setAttenuation(1.f);
                m_pESound[iNum].setPosition({ (float)fPan, 0, forward });
                m_pESound[iNum].play();
                break;
        }
    }
}

void CGame::_DrawBlackRect(int iSize)
{
    int ix, iy, sx, sy, dcx, dcy;
    uint64_t dwTime;

    dwTime = unixtime();

    dcx = 40 - iSize * 2;
    dcy = 30 - iSize * 2;

    sx = iSize * 16;
    sy = iSize * 16;

    for (ix = 0; ix < dcx; ix++)
    {
        m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(ix * 16 + sx, iSize * 16, 12, dwTime);
        m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(ix * 16 + sx, 464 - iSize * 16, 12, dwTime);
    }

    for (iy = 0; iy < dcy; iy++)
    {
        m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(iSize * 16, iy * 16 + sy, 12, dwTime);
        m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(624 - iSize * 16, iy * 16 + sy, 12, dwTime);
    }
}

bool CGame::_bCheckItemByType(char cType)
{
    int i;

    for (i = 0; i < DEF_MAXITEMS; i++)
        if ((m_pItemList[i] != 0) && (m_pItemList[i]->m_cItemType == cType)) return true;

    return false;
}


void CGame::DynamicObjectHandler(char * pData)
{
    uint16_t * wp;
    char * cp;
    short * sp, sX, sY, sV1, sV2, sV3;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE);
    wp = (uint16_t *)cp;
    cp += 2;

    sp = (short *)cp;
    sX = *sp;
    cp += 2;

    sp = (short *)cp;
    sY = *sp;
    cp += 2;

    sp = (short *)cp;
    sV1 = *sp;
    cp += 2;

    sp = (short *)cp;
    sV2 = *sp;		   // Dyamic Object Index
    cp += 2;

    sp = (short *)cp;
    sV3 = *sp;
    cp += 2;

    switch (*wp)
    {
        case DEF_MSGTYPE_CONFIRM:// Dynamic Object
            m_pMapData->bSetDynamicObject(sX, sY, sV2, sV1, true);
            break;

        case DEF_MSGTYPE_REJECT:// Dynamic object
            m_pMapData->bSetDynamicObject(sX, sY, sV2, 0, true);
            break;
    }
}

bool CGame::_bIsItemOnHand() // Fixed to remove ShieldCast
{
    int i;
    uint16_t wWeaponType;
    for (i = 0; i < DEF_MAXITEMS; i++)
        if ((m_pItemList[i] != 0) && (m_bIsItemEquipped[i] == true))
        {
            if ((m_pItemList[i]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                && (strcmp(m_pItemList[i]->m_cName, "GMShield") == 0))
                return false;
            else if ((m_pItemList[i]->m_cEquipPos == DEF_EQUIPPOS_LHAND)
                || (m_pItemList[i]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
                return true;
        }
    for (i = 0; i < DEF_MAXITEMS; i++)
        if ((m_pItemList[i] != 0) && (m_bIsItemEquipped[i] == true))
        {
            if (m_pItemList[i]->m_cEquipPos == DEF_EQUIPPOS_RHAND)
            {
                wWeaponType = ((m_sPlayerAppr2 & 0x0FF0) >> 4);
                if ((wWeaponType >= 34) && (wWeaponType < 40)) return false;
                //else if( wWeaponType == 27 ) return false; // Farming's hoe !
                else return true;
            }
        }
    return false;
}

int CGame::_iCalcTotalWeight()
{
    int i, iWeight, iCnt, iTemp;
    iCnt = 0;
    iWeight = 0;
    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_pItemList[i] != 0)
        {
            if ((m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_CONSUME)
                || (m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_ARROW))
            {
                iTemp = m_pItemList[i]->m_wWeight * m_pItemList[i]->m_dwCount;
                if (strcmp(m_pItemList[i]->m_cName, "Gold") == 0) iTemp = iTemp / 20;
                iWeight += iTemp;
            }
            else iWeight += m_pItemList[i]->m_wWeight;
            iCnt++;
        }

    return iWeight;
}

int CGame::iGetLevelExp(int iLevel)
{
    int iRet;
    if (iLevel == 0) return 0;
    iRet = iGetLevelExp(iLevel - 1) + iLevel * (50 + (iLevel * (iLevel / 17) * (iLevel / 17)));
    return iRet;
}

int CGame::_iGetTotalItemNum()
{
    int i, iCnt;
    iCnt = 0;
    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_pItemList[i] != 0) iCnt++;
    return iCnt;
}

bool CGame::bCheckExID(char * pName)
{
    if (m_pExID == 0) return false;
    if (memcmp(m_cPlayerName, pName, 10) == 0) return false;
    char cTxt[12] = {};
    ZeroMemory(cTxt, sizeof(cTxt));
    memcpy(cTxt, m_pExID->m_pMsg, strlen(m_pExID->m_pMsg));
    if (memcmp(cTxt, pName, 10) == 0) return true;
    else return false;
}

void CGame::DrawWhetherEffects()
{
#define MAXNUM 1000
    static int ix1[MAXNUM];
    static int iy2[MAXNUM];
    static int iFrame[MAXNUM];
    static int iNum = 0;
    int i;
    short dX, dY, sCnt;
    char cTempFrame;
    uint64_t dwTime = m_dwCurTime;

    switch (m_cWhetherEffectType)
    {
        case 1:
        case 2:
        case 3: // rain
            switch (m_cWhetherEffectType)
            {
                case 1: sCnt = DEF_MAXWHETHEROBJECTS / 5; break;
                case 2:	sCnt = DEF_MAXWHETHEROBJECTS / 2; break;
                case 3:	sCnt = DEF_MAXWHETHEROBJECTS;     break;
            }

            for (i = 0; i < sCnt; i++)
            {
                if ((m_stWhetherObject[i].cStep >= 0) && (m_stWhetherObject[i].cStep < 20) && (m_stWhetherObject[i].sX != 0))
                {
                    dX = m_stWhetherObject[i].sX - m_sViewPointX;
                    dY = m_stWhetherObject[i].sY - m_sViewPointY;
                    cTempFrame = 16 + (m_stWhetherObject[i].cStep / 6);
                    m_pEffectSpr[11]->PutTransSprite(dX, dY, cTempFrame, dwTime);
                }
                else if ((m_stWhetherObject[i].cStep >= 20) && (m_stWhetherObject[i].cStep < 25) && (m_stWhetherObject[i].sX != 0))
                {
                    dX = m_stWhetherObject[i].sX - m_sViewPointX;
                    dY = m_stWhetherObject[i].sY - m_sViewPointY;
                    m_pEffectSpr[11]->PutTransSprite(dX, dY, m_stWhetherObject[i].cStep, dwTime);
                }
            }
            break;

        case 4:
        case 5:
        case 6: // Snow
            switch (m_cWhetherEffectType)
            {
                case 4: sCnt = DEF_MAXWHETHEROBJECTS / 5; break;
                case 5:	sCnt = DEF_MAXWHETHEROBJECTS / 2; break;
                case 6:	sCnt = DEF_MAXWHETHEROBJECTS;     break;
            }
            for (i = 0; i < sCnt; i++)
            {
                if ((m_stWhetherObject[i].cStep >= 0) && (m_stWhetherObject[i].cStep < 80))
                {
                    dX = m_stWhetherObject[i].sX - m_sViewPointX;
                    dY = m_stWhetherObject[i].sY - m_sViewPointY;

                    if (dY >= 460)
                    {
                        cTempFrame = 39 + (m_stWhetherObject[i].cStep / 20) * 3;
                        dX = m_stWhetherObject[i].sBX;
                        dY = DEF_SNOW_POSITION_Y;// 426
                    }
                    else cTempFrame = 39 + (m_stWhetherObject[i].cStep / 20) * 3 + (rand() % 3);

                    m_pEffectSpr[11]->PutTransSprite(dX, dY, cTempFrame, dwTime);

                    if (m_bIsXmas == true)
                    {
                        if (dY == 478 - 53)
                        {
                            ix1[iNum] = dX;
                            iy2[iNum] = dY + (rand() % 5);
                            iFrame[iNum] = cTempFrame;
                            iNum++;
                        }
                        if (iNum >= MAXNUM) iNum = 0;
                    }
                }
            }
            if (m_bIsXmas == true)
            {
                for (i = 0; i <= MAXNUM; i++)
                {
                    if (iy2[i] > 10) m_pEffectSpr[11]->PutTransSprite(ix1[i], iy2[i], iFrame[i], dwTime);
                }
            }
            break;
    }
}

void CGame::WhetherObjectFrameCounter()
{
    int i;
    short sCnt;
    char  cAdd;
    uint64_t dwTime = m_dwCurTime;

    if ((dwTime - m_dwWOFtime) < 30) return;
    m_dwWOFtime = dwTime;

    switch (m_cWhetherEffectType)
    {
        case 1:
        case 2:
        case 3: // Rain
            switch (m_cWhetherEffectType)
            {
                case 1: sCnt = DEF_MAXWHETHEROBJECTS / 5; break;
                case 2:	sCnt = DEF_MAXWHETHEROBJECTS / 2; break;
                case 3:	sCnt = DEF_MAXWHETHEROBJECTS;     break;
            }
            for (i = 0; i < sCnt; i++)
            {
                m_stWhetherObject[i].cStep++;
                if ((m_stWhetherObject[i].cStep >= 0) && (m_stWhetherObject[i].cStep < 20))
                {
                    cAdd = (40 - m_stWhetherObject[i].cStep);
                    if (cAdd < 0) cAdd = 0;
                    m_stWhetherObject[i].sY = m_stWhetherObject[i].sY + cAdd;
                    if (cAdd != 0)
                        m_stWhetherObject[i].sX = m_stWhetherObject[i].sX - 1;
                }
                else if (m_stWhetherObject[i].cStep >= 25)
                {
                    if (m_bIsWhetherEffect == false)
                    {
                        m_stWhetherObject[i].sX = 0;
                        m_stWhetherObject[i].sY = 0;
                        m_stWhetherObject[i].cStep = 30;
                    }
                    else
                    {
                        m_stWhetherObject[i].sX = (m_pMapData->m_sPivotX * 32) + ((rand() % 940) - 200) + 300;
                        m_stWhetherObject[i].sY = (m_pMapData->m_sPivotY * 32) + ((rand() % 800) - 600) + 240;
                        m_stWhetherObject[i].cStep = -1 * (rand() % 10);
                    }
                }
            }
            break;

        case 4:
        case 5:
        case 6:
            switch (m_cWhetherEffectType)
            {
                case 4: sCnt = DEF_MAXWHETHEROBJECTS / 5; break;
                case 5:	sCnt = DEF_MAXWHETHEROBJECTS / 2; break;
                case 6:	sCnt = DEF_MAXWHETHEROBJECTS;     break;
            }
            for (i = 0; i < sCnt; i++)
            {
                m_stWhetherObject[i].cStep++;
                if ((m_stWhetherObject[i].cStep >= 0) && (m_stWhetherObject[i].cStep < 80))
                {
                    cAdd = (80 - m_stWhetherObject[i].cStep) / 10;
                    if (cAdd < 0) cAdd = 0;
                    m_stWhetherObject[i].sY = m_stWhetherObject[i].sY + cAdd;

                    if (m_stWhetherObject[i].sY > (426 + m_sViewPointY))
                    {
                        m_stWhetherObject[i].sY = 470 + m_sViewPointY;
                        if ((rand() % 10) != 2) m_stWhetherObject[i].cStep--;
                        if (m_stWhetherObject[i].sBX == 0) m_stWhetherObject[i].sBX = m_stWhetherObject[i].sX - m_sViewPointX;


                    }
                    else m_stWhetherObject[i].sX += 1 - (rand() % 3);
                }
                else if (m_stWhetherObject[i].cStep >= 80)
                {
                    if (m_bIsWhetherEffect == false)
                    {
                        m_stWhetherObject[i].sX = 0;
                        m_stWhetherObject[i].sY = 0;
                        m_stWhetherObject[i].sBX = 0;
                        m_stWhetherObject[i].cStep = 80;
                    }
                    else
                    {
                        m_stWhetherObject[i].sX = (m_pMapData->m_sPivotX * 32) + ((rand() % 940) - 200) + 300;
                        m_stWhetherObject[i].sY = (m_pMapData->m_sPivotY * 32) + ((rand() % 800) - 600) + 600;
                        m_stWhetherObject[i].cStep = -1 * (rand() % 10);
                        m_stWhetherObject[i].sBX = 0;
                    }
                }
            }
            break;
    }
}

void CGame::SetWhetherStatus(bool bStart, char cType)
{
    SYSTEMTIME SysTime;
    GetLocalTime(&SysTime);
    if (bStart == true)
    {
        m_bIsWhetherEffect = true;
        m_cWhetherEffectType = cType;
        if ((m_bSoundStat == true) && (m_bSoundFlag) && (cType >= 1) && (cType <= 3)) m_pESound[38].play();

        for (int i = 0; i < DEF_MAXWHETHEROBJECTS; i++)
        {
            m_stWhetherObject[i].sX = 1;
            m_stWhetherObject[i].sBX = 1;
            m_stWhetherObject[i].sY = 1;
            m_stWhetherObject[i].cStep = -1 * (rand() % 40);
        }
        if (cType >= 4 && cType <= 6)
        {
            if (m_bMusicStat) StartBGM();
        }
    }
    else
    {
        m_bIsWhetherEffect = false;
        m_cWhetherEffectType = 0;
        if ((m_bSoundStat == true) && (m_bSoundFlag)) m_pESound[38].stop();
    }
}

void CGame::DrawLine(int x0, int y0, int x1, int y1, Color color)
{
    DrawLine(x0, y0, x1, y1, color.r, color.g, color.b, color.a);
}

void CGame::DrawLine(int x0, int y0, int x1, int y1, int iR, int iG, int iB, int iA)
{
    if ((x0 == x1) && (y0 == y1))
        return;

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f((float)x0, (float)y0), Color(iR, iG, iB, iA)),
        sf::Vertex(sf::Vector2f((float)x1, (float)y1), Color(iR, iG, iB, iA)) };
    m_DDraw.window.draw(line, 2, sf::Lines);
}

void CGame::DrawLine2(int x0, int y0, int x1, int y1, int iR, int iG, int iB, int iA)
{
    DrawLine(x0, y0, x1, y1, iR, iG, iB, iA);
}

void CGame::_DrawThunderEffect(int sX, int sY, int dX, int dY, int rX, int rY, char cType)
{
    int j, iErr, pX1, pY1, iX1, iY1, tX, tY;
    char cDir;
    uint64_t dwTime;
    uint16_t  wR1 = 0, wG1 = 0, wB1 = 0, wR2 = 0, wG2 = 0, wB2 = 0, wR3 = 0, wG3 = 0, wB3 = 0, wR4 = 0, wG4 = 0, wB4 = 0;
    dwTime = m_dwCurTime;
    sX = pX1 = iX1 = tX = sX;
    sY = pY1 = iY1 = tY = sY;
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(50, 50, 100), &wR1, &wG1, &wB1);
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(30, 30, 100), &wR2, &wG2, &wB2);
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(0, 0, 30), &wR3, &wG3, &wB3);
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(50, 50, 200), &wR4, &wG4, &wB4);

    for (j = 0; j < 100; j++)
    {
        switch (cType)
        {
            case 1:
                DrawLine(pX1, pY1, iX1, iY1, 15, 15, 20);
                DrawLine(pX1 - 1, pY1, iX1 - 1, iY1, wR1, wG1, wB1);
                DrawLine(pX1 + 1, pY1, iX1 + 1, iY1, wR1, wG1, wB1);
                DrawLine(pX1, pY1 - 1, iX1, iY1 - 1, wR1, wG1, wB1);
                DrawLine(pX1, pY1 + 1, iX1, iY1 + 1, wR1, wG1, wB1);

                DrawLine(pX1 - 2, pY1, iX1 - 2, iY1, wR2, wG2, wB2);
                DrawLine(pX1 + 2, pY1, iX1 + 2, iY1, wR2, wG2, wB2);
                DrawLine(pX1, pY1 - 2, iX1, iY1 - 2, wR2, wG2, wB2);
                DrawLine(pX1, pY1 + 2, iX1, iY1 + 2, wR2, wG2, wB2);

                DrawLine(pX1 - 1, pY1 - 1, iX1 - 1, iY1 - 1, wR3, wG3, wB3);
                DrawLine(pX1 + 1, pY1 - 1, iX1 + 1, iY1 - 1, wR3, wG3, wB3);
                DrawLine(pX1 + 1, pY1 - 1, iX1 + 1, iY1 - 1, wR3, wG3, wB3);
                DrawLine(pX1 - 1, pY1 + 1, iX1 - 1, iY1 + 1, wR3, wG3, wB3);
                break;

            case 2:
                DrawLine2(pX1, pY1, iX1, iY1, wR4, wG4, wB4);
                break;
        }
        iErr = 0;
        m_Misc.GetPoint(sX, sY, dX, dY, &tX, &tY, &iErr, j * 10);
        pX1 = iX1;
        pY1 = iY1;
        cDir = m_Misc.cGetNextMoveDir(iX1, iY1, tX, tY);
        switch (cDir)
        {
            case 1:	rY -= 5; break;
            case 2: rY -= 5; rX += 5; break;
            case 3:	rX += 5; break;
            case 4: rX += 5; rY += 5; break;
            case 5: rY += 5; break;
            case 6: rX -= 5; rY += 5; break;
            case 7: rX -= 5; break;
            case 8: rX -= 5; rY -= 5; break;
        }
        if (rX < -20) rX = -20;
        if (rX > 20) rX = 20;
        if (rY < -20) rY = -20;
        if (rY > 20) rY = 20;
        iX1 = iX1 + rX;
        iY1 = iY1 + rY;
        if ((abs(tX - dX) < 5) && (abs(tY - dY) < 5)) break;
    }
    switch (cType)
    {
        case 1:
            m_pEffectSpr[6]->PutTransSprite(iX1, iY1, (rand() % 2), dwTime);
            break;
    }
}

bool CGame::bDlgBoxPress_SkillDlg(short msX, short msY)
{
    int i, iAdjX, iAdjY;
    char  cItemID;
    short sX, sY, x1, y1, x2, y2, sArray[10] = {};
    sX = m_stDialogBoxInfo[26].sX;
    sY = m_stDialogBoxInfo[26].sY;
    iAdjX = 5;
    iAdjY = 10;
    switch (m_stDialogBoxInfo[26].cMode)
    {
        case 1:
            ZeroMemory(sArray, sizeof(sArray));
            sArray[1] = m_stDialogBoxInfo[26].sV1;
            sArray[2] = m_stDialogBoxInfo[26].sV2;
            sArray[3] = m_stDialogBoxInfo[26].sV3;
            sArray[4] = m_stDialogBoxInfo[26].sV4;
            sArray[5] = m_stDialogBoxInfo[26].sV5;
            sArray[6] = m_stDialogBoxInfo[26].sV6;
            for (i = 1; i <= 6; i++)
                if ((sArray[i] != -1) && (m_pItemList[sArray[i]] != 0))
                {
                    cItemID = (char)sArray[i];
                    switch (i)
                    {
                        case 1: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55, sY + iAdjY + 55, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 2: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 45 * 1, sY + iAdjY + 55, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 3: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 45 * 2, sY + iAdjY + 55, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 4: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55, sY + iAdjY + 100, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 5: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 45 * 1, sY + iAdjY + 100, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 6: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 45 * 2, sY + iAdjY + 100, m_pItemList[cItemID]->m_sSpriteFrame); break;
                    }
                    x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
                    y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
                    x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
                    y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;
                    if ((msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
                    {
                        switch (i)
                        {
                            case 1: m_stDialogBoxInfo[26].sV1 = -1; break;
                            case 2: m_stDialogBoxInfo[26].sV2 = -1; break;
                            case 3: m_stDialogBoxInfo[26].sV3 = -1; break;
                            case 4: m_stDialogBoxInfo[26].sV4 = -1; break;
                            case 5: m_stDialogBoxInfo[26].sV5 = -1; break;
                            case 6: m_stDialogBoxInfo[26].sV6 = -1; break;
                        }
                        m_bIsItemDisabled[cItemID] = false;
                        m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                        m_stMCursor.sSelectedObjectID = cItemID;
                        m_stMCursor.sDistX = msX + iAdjX - x1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotX;
                        m_stMCursor.sDistY = msY + iAdjY - y1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotY;
                        return true;
                    }
                }
            break;

        case 4:
            ZeroMemory(sArray, sizeof(sArray));
            sArray[1] = m_stDialogBoxInfo[26].sV1;
            sArray[2] = m_stDialogBoxInfo[26].sV2;
            sArray[3] = m_stDialogBoxInfo[26].sV3;
            sArray[4] = m_stDialogBoxInfo[26].sV4;
            sArray[5] = m_stDialogBoxInfo[26].sV5;
            sArray[6] = m_stDialogBoxInfo[26].sV6;
            for (i = 1; i <= 6; i++)
                if ((sArray[i] != -1) && (m_pItemList[sArray[i]] != 0))
                {
                    cItemID = (char)sArray[i];
                    switch (i)
                    {
                        case 1: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 55 + 180, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 2: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 45 * 1 + 30 + 13, sY + iAdjY + 55 + 180, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 3: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 45 * 2 + 30 + 13, sY + iAdjY + 55 + 180, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 4: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 30 + 13, sY + iAdjY + 100 + 180, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 5: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 45 * 1 + 30 + 13, sY + iAdjY + 100 + 180, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 6: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55 + 45 * 2 + 30 + 13, sY + iAdjY + 100 + 180, m_pItemList[cItemID]->m_sSpriteFrame); break;
                    }
                    x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
                    y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
                    x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
                    y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;

                    if ((msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
                    {
                        switch (i)
                        {
                            case 1: m_stDialogBoxInfo[26].sV1 = -1; break;
                            case 2: m_stDialogBoxInfo[26].sV2 = -1; break;
                            case 3: m_stDialogBoxInfo[26].sV3 = -1; break;
                            case 4: m_stDialogBoxInfo[26].sV4 = -1; break;
                            case 5: m_stDialogBoxInfo[26].sV5 = -1; break;
                            case 6: m_stDialogBoxInfo[26].sV6 = -1; break;
                        }
                        m_bIsItemDisabled[cItemID] = false;
                        m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                        m_stMCursor.sSelectedObjectID = cItemID;
                        m_stMCursor.sDistX = msX + iAdjX - x1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotX;
                        m_stMCursor.sDistY = msY + iAdjY - y1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotY;
                        m_stDialogBoxInfo[26].cStr[4] = (char)_bCheckCurrentBuildItemStatus();
                        return true;
                    }
                }
            break;
            // Crafting
        case 7:
            ZeroMemory(sArray, sizeof(sArray));
            sArray[1] = m_stDialogBoxInfo[26].sV1;
            sArray[2] = m_stDialogBoxInfo[26].sV2;
            sArray[3] = m_stDialogBoxInfo[26].sV3;
            sArray[4] = m_stDialogBoxInfo[26].sV4;
            sArray[5] = m_stDialogBoxInfo[26].sV5;
            sArray[6] = m_stDialogBoxInfo[26].sV6;
            for (i = 1; i <= 6; i++)
                if ((sArray[i] != -1) && (m_pItemList[sArray[i]] != 0))
                {
                    cItemID = (char)sArray[i];
                    switch (i)
                    {
                        case 1: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 55, sY + iAdjY + 55, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 2: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 65 + 45 * 1, sY + iAdjY + 40, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 3: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 65 + 45 * 2, sY + iAdjY + 55, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 4: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 65, sY + iAdjY + 100, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 5: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 65 + 45 * 1, sY + iAdjY + 115, m_pItemList[cItemID]->m_sSpriteFrame); break;
                        case 6: m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->_GetSpriteRect(sX + iAdjX + 75 + 45 * 2, sY + iAdjY + 100, m_pItemList[cItemID]->m_sSpriteFrame); break;
                    }
                    x1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.left;
                    y1 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.top;
                    x2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.right;
                    y2 = (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_rcBound.bottom;
                    if ((msX > x1) && (msX < x2) && (msY > y1) && (msY < y2))
                    {
                        switch (i)
                        {
                            case 1: m_stDialogBoxInfo[26].sV1 = -1; break;
                            case 2: m_stDialogBoxInfo[26].sV2 = -1; break;
                            case 3: m_stDialogBoxInfo[26].sV3 = -1; break;
                            case 4: m_stDialogBoxInfo[26].sV4 = -1; break;
                            case 5: m_stDialogBoxInfo[26].sV5 = -1; break;
                            case 6: m_stDialogBoxInfo[26].sV6 = -1; break;
                        }
                        m_bIsItemDisabled[cItemID] = false;
                        m_stMCursor.cSelectedObjectType = DEF_SELECTEDOBJTYPE_ITEM;
                        m_stMCursor.sSelectedObjectID = cItemID;
                        m_stMCursor.sDistX = msX + iAdjX - x1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotX;
                        m_stMCursor.sDistY = msY + iAdjY - y1 + (short)m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[cItemID]->m_sSprite]->m_sPivotY;
                        return true;
                    }
                }
            break;
    }

    return false;
}
int CGame::_iGetAttackType()
{
    uint16_t wWeaponType;
    wWeaponType = ((m_sPlayerAppr2 & 0x0FF0) >> 4);
    if (wWeaponType == 0)
    {
        if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[5] >= 100)) return 20;
        else return 1;		// Boxe
    }
    else if ((wWeaponType >= 1) && (wWeaponType <= 2))
    {
        if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[7] >= 100)) return 21;
        else return 1;		//Dag, SS
    }
    else if ((wWeaponType > 2) && (wWeaponType < 20))
    {
        if ((wWeaponType == 7) || (wWeaponType == 18)) // Added Kloness Esterk
        {
            if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[9] >= 100)) return 22;
            else return 1;  // Esterk
        }
        else if (wWeaponType == 15)
        {
            if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[8] >= 100)) return 30;
            else return 5;  // StormBlade
        }
        else
        {
            if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[8] >= 100)) return 23;
            else return 1;	// LongSwords
        }
    }
    else if ((wWeaponType >= 20) && (wWeaponType < 29))
    {
        if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[10] >= 100)) return 24;
        else return 1;		// Haches
    }
    else if ((wWeaponType >= 30) && (wWeaponType < 33))
    {
        if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[14] >= 100)) return 26;
        else return 1;		// Hammers
    }
    else if ((wWeaponType >= 34) && (wWeaponType < 40))
    {
        if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[21] >= 100)) return 27;
        else return 1;		// Wands
    }
    else if (wWeaponType >= 40)
    {
        if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[6] >= 100)) return 25;
        else return 2;		// Bows
    }
    else if ((wWeaponType == 29) || (wWeaponType == 33))
    {
        if ((m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true) && (m_cSkillMastery[8] >= 100)) return 23;
        else return 1;		// LS
    }
    return 0;
}

int CGame::_iGetWeaponSkillType()
{
    uint16_t wWeaponType;
    wWeaponType = ((m_sPlayerAppr2 & 0x0FF0) >> 4);
    if (wWeaponType == 0)
    {
        return 5; // Openhand
    }
    else if ((wWeaponType >= 1) && (wWeaponType < 3))
    {
        return 7; // SS
    }
    else if ((wWeaponType >= 3) && (wWeaponType < 20))
    {
        if ((wWeaponType == 7) || (wWeaponType == 18)) // Esterk or KlonessEsterk
            return 9; // Fencing
        else return 8; // LS
    }
    else if ((wWeaponType >= 20) && (wWeaponType < 29))
    {
        return 10; // Axe (20..28)
    }
    else if ((wWeaponType >= 30) && (wWeaponType < 33))
    {
        return 14; // Hammer (30,31,32)
    }
    else if ((wWeaponType >= 34) && (wWeaponType < 40))
    {
        return 21; // Wand
    }
    else if (wWeaponType >= 40)
    {
        return 6;  // Bow
    }
    else if ((wWeaponType == 29) || (wWeaponType == 33))
    {
        return 8;  // LS LightingBlade || BlackShadow
    }
    return 1; // Fishing !
}

bool CGame::_bCheckBadWords(char * pMsg)
{
    return false;
}

int CGame::_iGetBankItemCount()
{
    int i, iCnt;

    iCnt = 0;
    for (i = 0; i < DEF_MAXBANKITEMS; i++)
        if (m_pBankList[i] != 0) iCnt++;

    return iCnt;
}

bool CGame::_bDecodeBuildItemContents()
{
    char cFileName[255], cTemp[255];
    HANDLE hFile;
    FILE * pFile;
    uint32_t  dwFileSize;
    char * pBuffer;
    bool   bRet;
    int    i;

    for (i = 0; i < DEF_MAXBUILDITEMS; i++)
        if (m_pBuildItemList[i] != 0)
        {
            delete m_pBuildItemList[i];
            m_pBuildItemList[i] = 0;
        }

    ZeroMemory(cTemp, sizeof(cTemp));
    ZeroMemory(cFileName, sizeof(cFileName));

    strcat(cFileName, "data\\contents\\BItemcfg.txt");

    hFile = CreateFileA(cFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwFileSize = GetFileSize(hFile, 0);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

    pFile = fopen(cFileName, "rt");
    if (pFile == 0) return false;
    else
    {
        pBuffer = new char[dwFileSize + 1];
        ZeroMemory(pBuffer, dwFileSize + 1);
        fread(pBuffer, dwFileSize, 1, pFile);
        bRet = __bDecodeBuildItemContents(pBuffer);
        delete[] pBuffer;
    }
    fclose(pFile);
    return bRet;
}

bool CGame::_bCheckBuildItemStatus()
{
    int iIndex, i, j, iMatch, iCount;
    char cTempName[21];
    int  iItemCount[DEF_MAXITEMS] = {};

    for (i = 0; i < DEF_MAXBUILDITEMS; i++)
        if (m_pDispBuildItemList[i] != 0)
        {
            delete m_pDispBuildItemList[i];
            m_pDispBuildItemList[i] = 0;
        }
    iIndex = 0;
    for (i = 0; i < DEF_MAXBUILDITEMS; i++)
        if (m_pBuildItemList[i] != 0)
        {	// Skill-Limit
            if (m_cSkillMastery[13] >= m_pBuildItemList[i]->m_iSkillLimit)
            {
                iMatch = 0;
                m_pDispBuildItemList[iIndex] = new class CBuildItem;
                memcpy(m_pDispBuildItemList[iIndex]->m_cName, m_pBuildItemList[i]->m_cName, 20);

                memcpy(m_pDispBuildItemList[iIndex]->m_cElementName1, m_pBuildItemList[i]->m_cElementName1, 20);
                memcpy(m_pDispBuildItemList[iIndex]->m_cElementName2, m_pBuildItemList[i]->m_cElementName2, 20);
                memcpy(m_pDispBuildItemList[iIndex]->m_cElementName3, m_pBuildItemList[i]->m_cElementName3, 20);
                memcpy(m_pDispBuildItemList[iIndex]->m_cElementName4, m_pBuildItemList[i]->m_cElementName4, 20);
                memcpy(m_pDispBuildItemList[iIndex]->m_cElementName5, m_pBuildItemList[i]->m_cElementName5, 20);
                memcpy(m_pDispBuildItemList[iIndex]->m_cElementName6, m_pBuildItemList[i]->m_cElementName6, 20);

                m_pDispBuildItemList[iIndex]->m_iElementCount[1] = m_pBuildItemList[i]->m_iElementCount[1];
                m_pDispBuildItemList[iIndex]->m_iElementCount[2] = m_pBuildItemList[i]->m_iElementCount[2];
                m_pDispBuildItemList[iIndex]->m_iElementCount[3] = m_pBuildItemList[i]->m_iElementCount[3];
                m_pDispBuildItemList[iIndex]->m_iElementCount[4] = m_pBuildItemList[i]->m_iElementCount[4];
                m_pDispBuildItemList[iIndex]->m_iElementCount[5] = m_pBuildItemList[i]->m_iElementCount[5];
                m_pDispBuildItemList[iIndex]->m_iElementCount[6] = m_pBuildItemList[i]->m_iElementCount[6];

                m_pDispBuildItemList[iIndex]->m_iSprH = m_pBuildItemList[i]->m_iSprH;
                m_pDispBuildItemList[iIndex]->m_iSprFrame = m_pBuildItemList[i]->m_iSprFrame;
                m_pDispBuildItemList[iIndex]->m_iMaxSkill = m_pBuildItemList[i]->m_iMaxSkill;
                m_pDispBuildItemList[iIndex]->m_iSkillLimit = m_pBuildItemList[i]->m_iSkillLimit;

                // ItemCount
                for (j = 0; j < DEF_MAXITEMS; j++)
                    if (m_pItemList[j] != 0)
                        iItemCount[j] = m_pItemList[j]->m_dwCount;
                    else iItemCount[j] = 0;

                // Element1
                ZeroMemory(cTempName, sizeof(cTempName));
                memcpy(cTempName, m_pBuildItemList[i]->m_cElementName1, 20);
                iCount = m_pBuildItemList[i]->m_iElementCount[1];
                if (iCount == 0) iMatch++;
                else
                {
                    for (j = 0; j < DEF_MAXITEMS; j++)
                        if (m_pItemList[j] != 0)
                        {
                            if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (uint32_t)(iCount)) &&
                                (iItemCount[j] > 0))
                            {
                                iMatch++;
                                m_pDispBuildItemList[iIndex]->m_bElementFlag[1] = true;
                                iItemCount[j] -= iCount;
                                goto CBIS_STEP2;
                            }
                        }
                }

                CBIS_STEP2:;
                // Element2
                ZeroMemory(cTempName, sizeof(cTempName));
                memcpy(cTempName, m_pBuildItemList[i]->m_cElementName2, 20);
                iCount = m_pBuildItemList[i]->m_iElementCount[2];
                if (iCount == 0) iMatch++;
                else
                {
                    for (j = 0; j < DEF_MAXITEMS; j++)
                        if (m_pItemList[j] != 0)
                        {
                            if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (uint32_t)(iCount)) &&
                                (iItemCount[j] > 0))
                            {
                                iMatch++;
                                m_pDispBuildItemList[iIndex]->m_bElementFlag[2] = true;
                                iItemCount[j] -= iCount;
                                goto CBIS_STEP3;
                            }
                        }
                }

                CBIS_STEP3:;
                // Element3
                ZeroMemory(cTempName, sizeof(cTempName));
                memcpy(cTempName, m_pBuildItemList[i]->m_cElementName3, 20);
                iCount = m_pBuildItemList[i]->m_iElementCount[3];
                if (iCount == 0) iMatch++;
                else
                {
                    for (j = 0; j < DEF_MAXITEMS; j++)
                        if (m_pItemList[j] != 0)
                        {
                            if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (uint32_t)(iCount)) &&
                                (iItemCount[j] > 0))
                            {
                                iMatch++;
                                m_pDispBuildItemList[iIndex]->m_bElementFlag[3] = true;
                                iItemCount[j] -= iCount;
                                goto CBIS_STEP4;
                            }
                        }
                }

                CBIS_STEP4:;
                // Element4
                ZeroMemory(cTempName, sizeof(cTempName));
                memcpy(cTempName, m_pBuildItemList[i]->m_cElementName4, 20);
                iCount = m_pBuildItemList[i]->m_iElementCount[4];
                if (iCount == 0) iMatch++;
                else
                {
                    for (j = 0; j < DEF_MAXITEMS; j++)
                        if (m_pItemList[j] != 0)
                        {
                            if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (uint32_t)(iCount)) &&
                                (iItemCount[j] > 0))
                            {
                                iMatch++;
                                m_pDispBuildItemList[iIndex]->m_bElementFlag[4] = true;
                                iItemCount[j] -= iCount;
                                goto CBIS_STEP5;
                            }
                        }
                }

                CBIS_STEP5:;

                // Element5
                ZeroMemory(cTempName, sizeof(cTempName));
                memcpy(cTempName, m_pBuildItemList[i]->m_cElementName5, 20);
                iCount = m_pBuildItemList[i]->m_iElementCount[5];
                if (iCount == 0) iMatch++;
                else
                {
                    for (j = 0; j < DEF_MAXITEMS; j++)
                        if (m_pItemList[j] != 0)
                        {
                            if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (uint32_t)(iCount)) &&
                                (iItemCount[j] > 0))
                            {
                                iMatch++;
                                m_pDispBuildItemList[iIndex]->m_bElementFlag[5] = true;
                                iItemCount[j] -= iCount;
                                goto CBIS_STEP6;
                            }
                        }
                }

                CBIS_STEP6:;

                // Element6
                ZeroMemory(cTempName, sizeof(cTempName));
                memcpy(cTempName, m_pBuildItemList[i]->m_cElementName6, 20);
                iCount = m_pBuildItemList[i]->m_iElementCount[6];
                if (iCount == 0) iMatch++;
                else
                {
                    for (j = 0; j < DEF_MAXITEMS; j++)
                        if (m_pItemList[j] != 0)
                        {
                            if ((memcmp(m_pItemList[j]->m_cName, cTempName, 20) == 0) && (m_pItemList[j]->m_dwCount >= (uint32_t)(iCount)) &&
                                (iItemCount[j] > 0))
                            {
                                iMatch++;
                                m_pDispBuildItemList[iIndex]->m_bElementFlag[6] = true;
                                iItemCount[j] -= iCount;
                                goto CBIS_STEP7;
                            }
                        }
                }

                CBIS_STEP7:;

                if (iMatch == 6) m_pDispBuildItemList[iIndex]->m_bBuildEnabled = true;
                iIndex++;
            }
        }
    return true;
}

bool CGame::_ItemDropHistory(char * ItemName)
{
    bool bFlag = false;
    if (m_iItemDropCnt == 0)
    {
        strcpy(m_cItemDrop[m_iItemDropCnt], ItemName);
        m_iItemDropCnt++;
        return true;
    }
    if ((1 <= m_iItemDropCnt) && (20 >= m_iItemDropCnt))
    {
        for (int i = 0; i < m_iItemDropCnt; i++)
        {
            if (strcmp(m_cItemDrop[i], ItemName) == 0)
            {
                bFlag = true;
                break;
            }
        }
        if (bFlag)
        {
            if (m_bItemDrop)
                return false;
            else
                return true;
        }

        if (20 < m_iItemDropCnt)
        {
            for (int i = 0; i < m_iItemDropCnt; i++)
                strcpy(m_cItemDrop[i - 1], ItemName);
            strcpy(m_cItemDrop[20], ItemName);
            m_iItemDropCnt = 21;
        }
        else
        {
            strcpy(m_cItemDrop[m_iItemDropCnt], ItemName);
            m_iItemDropCnt++;
        }
    }
    return true;
}


bool CGame::__bDecodeBuildItemContents(char * pBuffer)
{
    char * pContents, * token;
    char seps[] = "= ,\t\n";
    char cReadModeA = 0;
    char cReadModeB = 0;
    int  iIndex = 0;
    class CStrTok * pStrTok;
    pContents = pBuffer;
    pStrTok = new class CStrTok(pContents, seps);
    token = pStrTok->pGet();

    while (token != 0)
    {
        if (cReadModeA != 0)
        {
            switch (cReadModeA)
            {
                case 1:
                    switch (cReadModeB)
                    {
                        case 1:
                            ZeroMemory(m_pBuildItemList[iIndex]->m_cName, sizeof(m_pBuildItemList[iIndex]->m_cName));
                            memcpy(m_pBuildItemList[iIndex]->m_cName, token, strlen(token));
                            cReadModeB = 2;
                            break;
                        case 2:
                            m_pBuildItemList[iIndex]->m_iSkillLimit = atoi(token);
                            cReadModeB = 3;
                            break;
                        case 3: // m_cElementName1
                            ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName1, sizeof(m_pBuildItemList[iIndex]->m_cElementName1));
                            memcpy(m_pBuildItemList[iIndex]->m_cElementName1, token, strlen(token));
                            cReadModeB = 4;
                            break;
                        case 4: // m_iElementCount1
                            m_pBuildItemList[iIndex]->m_iElementCount[1] = atoi(token);
                            cReadModeB = 5;
                            break;
                        case 5: // m_cElementName2
                            ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName2, sizeof(m_pBuildItemList[iIndex]->m_cElementName2));
                            memcpy(m_pBuildItemList[iIndex]->m_cElementName2, token, strlen(token));
                            cReadModeB = 6;
                            break;
                        case 6: // m_iElementCount2
                            m_pBuildItemList[iIndex]->m_iElementCount[2] = atoi(token);
                            cReadModeB = 7;
                            break;
                        case 7: // m_cElementName3
                            ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName3, sizeof(m_pBuildItemList[iIndex]->m_cElementName3));
                            memcpy(m_pBuildItemList[iIndex]->m_cElementName3, token, strlen(token));
                            cReadModeB = 8;
                            break;
                        case 8: // m_iElementCount3
                            m_pBuildItemList[iIndex]->m_iElementCount[3] = atoi(token);
                            cReadModeB = 9;
                            break;
                        case 9: // m_cElementName4
                            ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName4, sizeof(m_pBuildItemList[iIndex]->m_cElementName4));
                            memcpy(m_pBuildItemList[iIndex]->m_cElementName4, token, strlen(token));
                            cReadModeB = 10;
                            break;
                        case 10: // m_iElementCount4
                            m_pBuildItemList[iIndex]->m_iElementCount[4] = atoi(token);
                            cReadModeB = 11;
                            break;
                        case 11: // m_cElementName5
                            ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName5, sizeof(m_pBuildItemList[iIndex]->m_cElementName5));
                            memcpy(m_pBuildItemList[iIndex]->m_cElementName5, token, strlen(token));
                            cReadModeB = 12;
                            break;
                        case 12: // m_iElementCount5
                            m_pBuildItemList[iIndex]->m_iElementCount[5] = atoi(token);
                            cReadModeB = 13;
                            break;
                        case 13: // m_cElementName6
                            ZeroMemory(m_pBuildItemList[iIndex]->m_cElementName6, sizeof(m_pBuildItemList[iIndex]->m_cElementName6));
                            memcpy(m_pBuildItemList[iIndex]->m_cElementName6, token, strlen(token));
                            cReadModeB = 14;
                            break;
                        case 14: // m_iElementCount6
                            m_pBuildItemList[iIndex]->m_iElementCount[6] = atoi(token);
                            cReadModeB = 15;
                            break;

                        case 15:
                            m_pBuildItemList[iIndex]->m_iSprH = atoi(token);
                            cReadModeB = 16;
                            break;

                        case 16:
                            m_pBuildItemList[iIndex]->m_iSprFrame = atoi(token);
                            cReadModeB = 17;
                            break;

                        case 17:
                            m_pBuildItemList[iIndex]->m_iMaxSkill = atoi(token);

                            cReadModeA = 0;
                            cReadModeB = 0;
                            iIndex++;
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
        else
        {
            if (memcmp(token, "BuildItem", 9) == 0)
            {
                cReadModeA = 1;
                cReadModeB = 1;
                m_pBuildItemList[iIndex] = new class CBuildItem;
            }
        }
        token = pStrTok->pGet();
    }
    delete pStrTok;
    if ((cReadModeA != 0) || (cReadModeB != 0)) return false;
    return true;
}


bool CGame::_bCheckCurrentBuildItemStatus()
{
    int i, iCount2, iMatch, iIndex, iItemIndex[7] = {};
    int iCount;
    int iItemCount[7] = {};
    char cTempName[21] = {};
    bool bItemFlag[7] = {};

    iIndex = m_stDialogBoxInfo[26].cStr[0];

    if (m_pBuildItemList[iIndex] == 0) return false;

    iItemIndex[1] = m_stDialogBoxInfo[26].sV1;
    iItemIndex[2] = m_stDialogBoxInfo[26].sV2;
    iItemIndex[3] = m_stDialogBoxInfo[26].sV3;
    iItemIndex[4] = m_stDialogBoxInfo[26].sV4;
    iItemIndex[5] = m_stDialogBoxInfo[26].sV5;
    iItemIndex[6] = m_stDialogBoxInfo[26].sV6;

    for (i = 1; i <= 6; i++)
        if (iItemIndex[i] != -1)
            iItemCount[i] = m_pItemList[iItemIndex[i]]->m_dwCount;
        else iItemCount[i] = 0;
    iMatch = 0;
    for (i = 1; i <= 6; i++) bItemFlag[i] = false;

    // Element1
    ZeroMemory(cTempName, sizeof(cTempName));
    memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName1, 20);
    iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[1];
    if (iCount == 0) iMatch++;
    else
    {
        for (i = 1; i <= 6; i++)
        {
            if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
                (m_pItemList[iItemIndex[i]]->m_dwCount >= (uint32_t)(iCount)) &&
                (iItemCount[i] > 0) && (bItemFlag[i] == false))
            {
                iMatch++;
                iItemCount[i] -= iCount;
                bItemFlag[i] = true;
                goto CCBIS_STEP2;
            }
        }
    }

    CCBIS_STEP2:;

    // Element2
    ZeroMemory(cTempName, sizeof(cTempName));
    memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName2, 20);
    iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[2];
    if (iCount == 0) iMatch++;
    else
    {
        for (i = 1; i <= 6; i++)
        {
            if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
                (m_pItemList[iItemIndex[i]]->m_dwCount >= (uint32_t)(iCount)) &&
                (iItemCount[i] > 0) && (bItemFlag[i] == false))
            {
                iMatch++;
                iItemCount[i] -= iCount;
                bItemFlag[i] = true;
                goto CCBIS_STEP3;
            }
        }
    }

    CCBIS_STEP3:;


    // Element3
    ZeroMemory(cTempName, sizeof(cTempName));
    memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName3, 20);
    iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[3];
    if (iCount == 0) iMatch++;
    else
    {
        for (i = 1; i <= 6; i++)
        {
            if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
                (m_pItemList[iItemIndex[i]]->m_dwCount >= (uint32_t)(iCount)) &&
                (iItemCount[i] > 0) && (bItemFlag[i] == false))
            {
                iMatch++;
                iItemCount[i] -= iCount;
                bItemFlag[i] = true;
                goto CCBIS_STEP4;
            }
        }
    }

    CCBIS_STEP4:;

    // Element4
    ZeroMemory(cTempName, sizeof(cTempName));
    memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName4, 20);
    iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[4];
    if (iCount == 0) iMatch++;
    else
    {
        for (i = 1; i <= 6; i++)
        {
            if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
                (m_pItemList[iItemIndex[i]]->m_dwCount >= (uint32_t)(iCount)) &&
                (iItemCount[i] > 0) && (bItemFlag[i] == false))
            {
                iMatch++;
                iItemCount[i] -= iCount;
                bItemFlag[i] = true;
                goto CCBIS_STEP5;
            }
        }
    }

    CCBIS_STEP5:;

    // Element5
    ZeroMemory(cTempName, sizeof(cTempName));
    memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName5, 20);
    iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[5];
    if (iCount == 0) iMatch++;
    else
    {
        for (i = 1; i <= 6; i++)
        {
            if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
                (m_pItemList[iItemIndex[i]]->m_dwCount >= (uint32_t)(iCount)) &&
                (iItemCount[i] > 0) && (bItemFlag[i] == false))
            {
                iMatch++;
                iItemCount[i] -= iCount;
                bItemFlag[i] = true;
                goto CCBIS_STEP6;
            }
        }
    }

    CCBIS_STEP6:;

    // Element6
    ZeroMemory(cTempName, sizeof(cTempName));
    memcpy(cTempName, m_pDispBuildItemList[iIndex]->m_cElementName6, 20);
    iCount = m_pDispBuildItemList[iIndex]->m_iElementCount[6];
    if (iCount == 0) iMatch++;
    else
    {
        for (i = 1; i <= 6; i++)
        {
            if ((iItemIndex[i] != -1) && (memcmp(m_pItemList[iItemIndex[i]]->m_cName, cTempName, 20) == 0) &&
                (m_pItemList[iItemIndex[i]]->m_dwCount >= (uint32_t)(iCount)) &&
                (iItemCount[i] > 0) && (bItemFlag[i] == false))
            {
                iMatch++;
                iItemCount[i] -= iCount;
                bItemFlag[i] = true;
                goto CCBIS_STEP7;
            }
        }
    }

    CCBIS_STEP7:;

    iCount = 0;
    for (i = 1; i <= 6; i++)
        if (m_pDispBuildItemList[iIndex]->m_iElementCount[i] != 0) iCount++;
    iCount2 = 0;
    for (i = 1; i <= 6; i++)
        if (iItemIndex[i] != -1) iCount2++;
    if ((iMatch == 6) && (iCount == iCount2)) return true;
    return false;
}

void CGame::NoticementHandler(char * pData)
{
    char * cp;
    FILE * pFile;
    uint16_t * wp;
    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    switch (*wp)
    {
        case DEF_MSGTYPE_CONFIRM:
            break;
        case DEF_MSGTYPE_REJECT:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            pFile = fopen("contents\\contents1000.txt", "wt");
            if (pFile == 0) return;
            fwrite(cp, strlen(cp), 1, pFile);
            fclose(pFile);
            m_stDialogBoxInfo[18].sX = 20;
            m_stDialogBoxInfo[18].sY = 65;
            EnableDialogBox(18, 1000, 0, 0);
            break;
    }
#ifdef DEF_MULTI_SHORTCUT
    AddEventList("Press Ctrl+H for news and help.", 10);
#else
    AddEventList("Press F1 for news and help.", 10);
#endif
    if (m_iLevel < 42) EnableDialogBox(35, 0, 0, 0);

}

#ifdef DEF_EQUILIBRIUM_PROJECT // _iGetFOE
int CGame::_iGetFOE(int iStatus)
{
    bool bCitizen, bAresden, bHunter;
    if (iStatus & 0x00080000) return -2; // Boss Mobs

    //I see a traveller: 1 1+0+0+0 bHunter
    //I see an   elvine: 4 0+0+4+0 bCitizen
    //I see an  elv civ: 5 1+0+4+0 bHunter  & bCitizen
    //I see an     ares: 6 0+2+4+0 bCitizen & bAresden
    //I see an  are civ: 7 1+2+4+0 bHunter  & bCitizen & bAresden
    //I see an executor: 6 0+2+0+0 bAresden (NotCitizen but Aresden, and not bHunter)

    if (m_iPKCount != 0) return -1;		// I'm crim, everybody is eny
    if (iStatus & 0x80000000) return -1;	// He's crim, so he's my eny

    if (iStatus & 0x40000000) bCitizen = true;
    else bCitizen = false;
    if (iStatus & 0x20000000) bAresden = true;
    else bAresden = false;

    if (iStatus & 0x10000000) bHunter = true;
    else bHunter = false;

    if ((m_bAresden == bAresden) && (m_bCitizen == bCitizen)) return 1;
    // We are same city (elvine/aresden/executor)=>friend
    if (bCitizen == false) // I am trav or exec
    {
        if (bHunter == true) return 0;		// Trav seen as neutral
        else return -1;					// Exec seen as eny
    }
    if ((m_bIsCrusadeMode == true) || (m_bIsAvatarMode == true))
    {
        return -1;
    }
    else
    {
        if ((m_bHunter == false) && (bHunter == false)) return -1;
    }
    return 0; // Civ see Civ as neutral
}
#else
int CGame::_iGetFOE(int iStatus)
{
    bool bPK, bCitizen, bAresden, bHunter;
    if (m_iPKCount != 0) return -1;
    if (iStatus & 0x80000000) bPK = true;
    else bPK = false;
    if (iStatus & 0x40000000) bCitizen = true;
    else bCitizen = false;
    if (iStatus & 0x20000000) bAresden = true;
    else bAresden = false;
    if (iStatus & 0x10000000) bHunter = true;
    else bHunter = false;
    if (bPK == true) return -2;
    if (bCitizen == false) return 0;
    if (m_bCitizen == false) return 0;
    if ((m_bAresden == true) && (bAresden == true)) return 1;
    if ((m_bAresden == false) && (bAresden == false)) return 1;
    if (m_bIsCrusadeMode == true) return -1;
    else
    {
        if ((m_bHunter == false) && (bHunter == false)) return -1;
        else return 0;
    }
}
#endif

void CGame::_SetIlusionEffect(int iOwnerH)
{
    char cDir;

    m_iIlusionOwnerH = iOwnerH;

    ZeroMemory(m_cName_IE, sizeof(m_cName_IE));
    m_pMapData->GetOwnerStatusByObjectID(iOwnerH, &m_cIlusionOwnerType, &cDir, &m_sAppr1_IE, &m_sAppr2_IE, &m_sAppr3_IE, &m_sAppr4_IE, &m_iStatus_IE, &m_iApprColor_IE, m_cName_IE);
}

void CGame::ResponsePanningHandler(char * pData)
{
    char * cp, cDir;
    short * sp, sX, sY;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    sp = (short *)cp;
    sX = *sp;
    cp += 2;

    sp = (short *)cp;
    sY = *sp;
    cp += 2;

    cDir = *cp;
    cp++;

    switch (cDir)
    {
        case 1: m_sViewDstY -= 32; m_sPlayerY--; break;
        case 2: m_sViewDstY -= 32; m_sPlayerY--; m_sViewDstX += 32; m_sPlayerX++; break;
        case 3: m_sViewDstX += 32; m_sPlayerX++; break;
        case 4: m_sViewDstY += 32; m_sPlayerY++; m_sViewDstX += 32; m_sPlayerX++; break;
        case 5: m_sViewDstY += 32; m_sPlayerY++; break;
        case 6: m_sViewDstY += 32; m_sPlayerY++; m_sViewDstX -= 32; m_sPlayerX--; break;
        case 7: m_sViewDstX -= 32; m_sPlayerX--; break;
        case 8: m_sViewDstY -= 32; m_sPlayerY--; m_sViewDstX -= 32; m_sPlayerX--; break;
    }

    m_pMapData->ShiftMapData(cDir);
    _ReadMapData(sX, sY, cp);

    m_bIsRedrawPDBGS = true;

    m_bIsObserverCommanded = false;
}

bool CGame::bReadItemNameConfigFile()
{
    FILE * pFile;
    HANDLE hFile;
    uint32_t  dwFileSize;
    char * cp, * token, cReadModeA, cReadModeB;
    char seps[] = "=\n";
    int iIndex;

    cReadModeA = 0;
    cReadModeB = 0;
    iIndex = 0;

    hFile = CreateFileA("data\\contents\\ItemName.cfg", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwFileSize = GetFileSize(hFile, 0);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
    pFile = fopen("data\\contents\\ItemName.cfg", "rt");
    if (pFile == 0) return false;
    else
    {
        cp = new char[dwFileSize + 2];
        ZeroMemory(cp, dwFileSize + 2);
        fread(cp, dwFileSize, 1, pFile);

        token = strtok(cp, seps);
        while (token != 0)
        {

            if (cReadModeA != 0)
            {
                switch (cReadModeA)
                {
                    case 1:
                        switch (cReadModeB)
                        {
                            case 1:
                                m_pItemNameList[iIndex] = new class CItemName;
                                strcpy(m_pItemNameList[iIndex]->m_cOriginName, token);
                                cReadModeB = 2;
                                break;

                            case 2:
                                strcpy(m_pItemNameList[iIndex]->m_cName, token);
                                cReadModeA = 0;
                                cReadModeB = 0;
                                iIndex++;
                                break;
                        }
                }
            }
            else
            {
                if (memcmp(token, "Item", 4) == 0)
                {
                    cReadModeA = 1;
                    cReadModeB = 1;
                }
            }
            token = strtok(0, seps);
        }
        delete[] cp;
    }
    if (pFile != 0) fclose(pFile);

    return true;
}

void CGame::OnSysKeyDown(WPARAM wParam)
{
    switch (wParam)
    {
        case VK_SHIFT:
            m_bShiftPressed = true;
            break;
        case VK_CONTROL:
            m_bCtrlPressed = true;
            break;
        case VK_RETURN:
            m_bEnterPressed = true;
            break;
    }
}

void CGame::OnSysKeyUp(WPARAM wParam)
{
    switch (wParam)
    {
        case VK_SHIFT:
            m_bShiftPressed = false;
            break;
        case VK_CONTROL:
            m_bCtrlPressed = false;
            break;
        case VK_RETURN:
            m_bEnterPressed = false;
            if (m_bToggleScreen == true)
            {
                m_bIsRedrawPDBGS = true;
                m_DDraw.ChangeDisplayMode();
            }
            break;
        case VK_ESCAPE:
            m_bEscPressed = false;

#ifdef DEF_MULTI_SHORTCUT
        case VK_F10:
            UseShortCut(3);
            break;
#endif
    }
}

void CGame::OnKeyUp(WPARAM wParam)
{
    int i = 0;
    uint64_t dwTime = unixtime();

    switch (wParam)
    {

#ifdef DEF_EQUILIBRIUM_PROJECT //  pour marcher en mode Course
        case 222: // VK_OEM_7:
            m_bVK_OEM_7Pressed = false;
            break;
#endif

        case VK_SHIFT:
            m_bShiftPressed = false;
            break;
        case VK_CONTROL:
            m_bCtrlPressed = false;
            break;
        case 65://'A'
            if (m_bCtrlPressed && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus))
            {
                if (m_bForceAttack)
                {
                    m_bForceAttack = false;
                    AddEventList(DEF_MSG_FORCEATTACK_OFF, 10);
                }
                else
                {
                    m_bForceAttack = true;
                    AddEventList(DEF_MSG_FORCEATTACK_ON, 10);
                }
            }
            break;

        case 68://'D'
            if (m_bCtrlPressed == true && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus))
            {
                m_cDetailLevel++;
                if (m_cDetailLevel > 2) m_cDetailLevel = 0;
                switch (m_cDetailLevel)
                {
                    case 0:
                        AddEventList(NOTIFY_MSG_DETAIL_LEVEL_LOW, 10);
                        break;
                    case 1:
                        AddEventList(NOTIFY_MSG_DETAIL_LEVEL_MEDIUM, 10);
                        break;
                    case 2:
                        AddEventList(NOTIFY_MSG_DETAIL_LEVEL_HIGH, 10);
                        break;
                }
            }
            break;

        case 72: // 'H' // Mimics VK_F1
            if (m_bCtrlPressed && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus))
            {
                if (m_bIsDialogEnabled[35] == false)
                    EnableDialogBox(35, 0, 0, 0);
                else
                {
                    DisableDialogBox(35);
                    DisableDialogBox(18);
                }
            }
            break;

        case 87: // 'W' // mimics VK_F11 Togles transparency
            if (m_bCtrlPressed && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus))
            {
                m_bDialogTrans = !m_bDialogTrans;
            }
            break;

        case 88: // 'X' // mimics VK_F12 Logout Window
            if (m_bCtrlPressed && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus))
            {
                if (m_bIsDialogEnabled[19] == false)
                    EnableDialogBox(19, 0, 0, 0);
                else DisableDialogBox(19);
            }
            break;

        case 77://'M'
            if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
            {
                if (m_bCtrlPressed)
                {
                    if (m_bIsDialogEnabled[9] == true) DisableDialogBox(9);
                    else EnableDialogBox(9, 0, 0, 0, 0);
                }
            }
            break;

#ifdef _DEBUG
        case 81://'Q'
            if ((m_bCtrlPressed == true) && (m_cGameMode == DEF_GAMEMODE_ONMAINGAME))
            {
                ZeroMemory(m_cChatMsg, sizeof(m_cChatMsg));
                strcpy(m_cChatMsg, "/enableadmincommand 147258 ");
                StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
                //ClearInputString();
            }
            break;
#endif

        case 82://'R'
            if (m_bCtrlPressed == true && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus))
            {
                if (m_bRunningMode)
                {
                    m_bRunningMode = false;
                    AddEventList(NOTIFY_MSG_CONVERT_WALKING_MODE, 10);
                }
                else
                {
                    m_bRunningMode = true;
                    AddEventList(NOTIFY_MSG_CONVERT_RUNNING_MODE, 10);
                }
            }
            break;

        case 83://'S'
            if (m_bCtrlPressed == true && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus))
            {
                if (m_bMusicStat == true) // Music Off
                {
                    m_bMusicStat = false;
                    if (m_bSoundFlag)
                        m_pBGM.stop();
                    AddEventList(NOTIFY_MSG_MUSIC_OFF, 10);
                    break;
                }
                else if (m_bSoundStat == true)
                {
                    m_pESound[38].stop();
                    m_bSoundStat = false;
                    AddEventList(NOTIFY_MSG_SOUND_OFF, 10);
                    break;
                }
                else 	// Music On
                {
                    if (m_bSoundFlag)
                    {
                        m_bMusicStat = true;
                        AddEventList(NOTIFY_MSG_MUSIC_ON, 10);
                    }
                    if (m_bSoundFlag)
                    {
                        m_bSoundStat = true;
                        AddEventList(NOTIFY_MSG_SOUND_ON, 10);
                    }
                    StartBGM();
                }
            }
            break;

        case 84: //'T'
            if (m_bCtrlPressed == true && m_cGameMode == DEF_GAMEMODE_ONMAINGAME && (!m_bInputStatus))
            {
                char tempid[100], cLB, cRB;
                short sX, sY, msX, msY, msZ;
                sX = m_stDialogBoxInfo[10].sX;
                sY = m_stDialogBoxInfo[10].sY;
                ZeroMemory(tempid, sizeof(tempid));
                cLB = m_stMCursor.LB;
                cRB = m_stMCursor.RB;
                msX = m_stMCursor.sX;
                msY = m_stMCursor.sY;
                msZ = m_stMCursor.sZ;
                if (m_bIsDialogEnabled[10] == true && (msX >= sX + 20) && (msX <= sX + 360) && (msY >= sY + 35) && (msY <= sY + 139))
                {
                    CStrTok * pStrTok;
                    char * token, cBuff[64];
                    char   seps[] = ":";
                    int i = (139 - msY + sY) / 13;
                    if (m_pChatScrollList[i + m_stDialogBoxInfo[10].sView] == 0) return;
                    if (m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg[0] == ' ') i++;
                    strcpy(cBuff, m_pChatScrollList[i + m_stDialogBoxInfo[10].sView]->m_pMsg);
                    pStrTok = new class CStrTok(cBuff, seps);
                    token = pStrTok->pGet();
                    wsprintfA(tempid, "/to %s", token);
                    bSendCommand(MSGID_COMMAND_CHATMSG, 0, 0, 0, 0, 0, tempid);
                    delete pStrTok;
                }
                else if (_tmp_sOwnerType < 7 && (strlen(_tmp_cName) > 0) && (m_iIlusionOwnerH == 0)
                    && ((m_bIsCrusadeMode == false) || _iGetFOE(_tmp_iStatus) >= 0))
                {
                    wsprintfA(tempid, "/to %s", _tmp_cName);
                    bSendCommand(MSGID_COMMAND_CHATMSG, 0, 0, 0, 0, 0, tempid);
                }
                else
                {
                    EndInputString();
                    wsprintfA(m_cChatMsg, "/to ");
                    StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
                }
            }
            break;
        case 107: //'+'
            if (m_bInputStatus == false) m_bZoomMap = true;
            break;
        case 109: //'-'
            if (m_bInputStatus == false) m_bZoomMap = false;
            break;

        case VK_F2:
            UseShortCut(1);
            break;

        case VK_F3:
            UseShortCut(2);
            break;

        case VK_INSERT:
            if (m_iHP <= 0) return;
            if (m_bItemUsingStatus == true)
            {
                AddEventList(USE_RED_POTION1, 10);
                return;
            }
            if (m_bIsDialogEnabled[27] == true)
            {
                AddEventList(USE_RED_POTION2, 10);
                return;
            }
            for (i = 0; i < DEF_MAXITEMS; i++)
                if ((m_pItemList[i] != 0) && (m_bIsItemDisabled[i] != true) &&
                    (m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 1))
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, i, 0, 0, 0);
                    m_bIsItemDisabled[i] = true;
                    m_bItemUsingStatus = true;
                    return;
                }

            for (i = 0; i < DEF_MAXITEMS; i++)
                if ((m_pItemList[i] != 0) && (m_bIsItemDisabled[i] != true) &&
                    (m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 2))
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, i, 0, 0, 0);
                    m_bIsItemDisabled[i] = true;
                    m_bItemUsingStatus = true;
                    return;
                }
            break;

        case VK_DELETE:
            if (m_iHP <= 0) return;
            if (m_bItemUsingStatus == true)
            {
                AddEventList(USE_BLUE_POTION1, 10);
                return;
            }
            if (m_bIsDialogEnabled[27] == true)
            {
                AddEventList(USE_BLUE_POTION2, 10);
                return;
            }

            for (i = 0; i < DEF_MAXITEMS; i++)
                if ((m_pItemList[i] != 0) && (m_bIsItemDisabled[i] != true) &&
                    (m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 3))
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, i, 0, 0, 0);
                    m_bIsItemDisabled[i] = true;
                    m_bItemUsingStatus = true;
                    return;
                }

            for (i = 0; i < DEF_MAXITEMS; i++)
                if ((m_pItemList[i] != 0) && (m_bIsItemDisabled[i] != true) &&
                    (m_pItemList[i]->m_sSprite == 6) && (m_pItemList[i]->m_sSpriteFrame == 4))
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, i, 0, 0, 0);
                    m_bIsItemDisabled[i] = true;
                    m_bItemUsingStatus = true;
                    return;
                }
            break;

        case VK_END:
            if (((m_bIsDialogEnabled[7] == true) && (m_stDialogBoxInfo[7].cMode == 1) && (iGetTopDialogBoxIndex() == 7)) ||
                ((m_bIsDialogEnabled[17] == true) && (m_stDialogBoxInfo[17].cMode == 1) && (iGetTopDialogBoxIndex() == 17)))
            {
            }
            else if ((!m_bInputStatus) && (m_cBackupChatMsg[0] != '!') && (m_cBackupChatMsg[0] != '~') && (m_cBackupChatMsg[0] != '^') &&
                (m_cBackupChatMsg[0] != '@'))
            {
                ZeroMemory(m_cChatMsg, sizeof(m_cChatMsg));
                strcpy(m_cChatMsg, m_cBackupChatMsg);
                StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
            }
            break;

        case VK_F4:
            if (m_cGameMode != DEF_GAMEMODE_ONMAINGAME) return;
            UseMagic(m_sMagicShortCut);
            break;

        case VK_F5:
            if (m_bIsDialogEnabled[1] == false)
                EnableDialogBox(1, 0, 0, 0);
            else DisableDialogBox(1);
            break;

        case VK_F6:
            if (m_bIsDialogEnabled[2] == false)
                EnableDialogBox(2, 0, 0, 0);
            else DisableDialogBox(2);
            break;

        case VK_F7:
            if (m_bIsDialogEnabled[3] == false)
                EnableDialogBox(3, 0, 0, 0);
            else DisableDialogBox(3);
            break;

        case VK_F8:
            if (m_bIsDialogEnabled[15] == false)
                EnableDialogBox(15, 0, 0, 0);
            else DisableDialogBox(15);
            break;

        case VK_F9:
            if (m_bIsDialogEnabled[10] == false)
                EnableDialogBox(10, 0, 0, 0);
            else DisableDialogBox(10);
            break;

        case VK_F11:
#ifdef DEF_MULTI_SHORTCUT
            UseShortCut(4);
#else
            m_bDialogTrans = !m_bDialogTrans;
#endif
            break;

        case VK_F12:
#ifdef DEF_MULTI_SHORTCUT
            UseShortCut(5);
#else
            if (m_bInputStatus) return;
            if (m_bIsDialogEnabled[19] == false)
                EnableDialogBox(19, 0, 0, 0);
            else DisableDialogBox(19);
#endif
            break;

        case VK_F1:
#ifdef DEF_MULTI_SHORTCUT
            UseShortCut(0);
#else
            if (m_bInputStatus) return;
            if (m_bIsDialogEnabled[35] == false)
                EnableDialogBox(35, 0, 0, 0);
            else
            {
                DisableDialogBox(35);
                DisableDialogBox(18);
            }
#endif
            break;

        case VK_UP:
            m_cArrowPressed = 1;
            if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
            {
                int iTotalMsg = 0;
                for (int i = DEF_MAXWHISPERMSG - 1; i >= 0; i--)
                {
                    if (m_pWhisperMsg[i] != 0)
                    {
                        iTotalMsg = i;
                        break;
                    }
                }
                m_cWhisperIndex++;
                if (m_cWhisperIndex > iTotalMsg) m_cWhisperIndex = 0;
                if (m_cWhisperIndex < 0) m_cWhisperIndex = iTotalMsg;
                if (m_pWhisperMsg[m_cWhisperIndex] != 0)
                {
                    EndInputString();
                    wsprintfA(m_cChatMsg, "/to %s", m_pWhisperMsg[m_cWhisperIndex]->m_pMsg);
                    StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
                }
            }
            break;

        case VK_RIGHT:
            m_cArrowPressed = 2;
            break;

        case VK_DOWN:
            m_cArrowPressed = 3;
            if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
            {
                int iTotalMsg = 0;
                for (int i = DEF_MAXWHISPERMSG - 1; i >= 0; i--)
                {
                    if (m_pWhisperMsg[i] != 0)
                    {
                        iTotalMsg = i;
                        break;
                    }
                }
                m_cWhisperIndex--;
                if (m_cWhisperIndex < 0) m_cWhisperIndex = iTotalMsg;
                if (m_cWhisperIndex > iTotalMsg) m_cWhisperIndex = 0;
                if (m_pWhisperMsg[m_cWhisperIndex] != 0)
                {
                    EndInputString();
                    wsprintfA(m_cChatMsg, "/to %s", m_pWhisperMsg[m_cWhisperIndex]->m_pMsg);
                    StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
                }
            }
            break;

        case VK_LEFT:
            m_cArrowPressed = 4;
            break;

        case VK_SNAPSHOT:
            m_DDraw.CreateScreenShot();
            break;

#ifndef DEF_USING_WIN_IME
        case VK_TAB:
            if (m_bShiftPressed)
            {
                m_cCurFocus--;
                if (m_cCurFocus < 1) m_cCurFocus = m_cMaxFocus;
            }
            else
            {
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
            }
            if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, 0, 0, 0, 0, 0);
            }
            break;

        case VK_RETURN:
            m_bEnterPressed = true;
            break;
#endif

        case VK_HOME:
            if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
            {
                bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLESAFEATTACKMODE, 0, 0, 0, 0, 0);
            }
            break;

        case VK_ESCAPE:
            m_bEscPressed = true;
            if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
            {
                if ((m_bIsObserverMode == true) && (m_bShiftPressed))  //ObserverMode Shift+Esc
                {	// Log Out
                    if (m_cLogOutCount == -1) m_cLogOutCount = 1;
                    DisableDialogBox(19);
                    PlaySound('E', 14, 5);
                }
                else if (m_cLogOutCount != -1)
                {
                    if (m_bForceDisconn == false)  //Esc
                    {
                        m_cLogOutCount = -1;
                        AddEventList(DLGBOX_CLICK_SYSMENU2, 10);//"Logout count stopped."
                    }
                }
                if (m_bIsGetPointingMode == true)
                {
                    m_bIsGetPointingMode = false;
                    AddEventList(COMMAND_PROCESSOR1, 10);
                }
                m_bIsF1HelpWindowEnabled = false;
            }
            break;

        case 33:
            if (m_cGameMode != DEF_GAMEMODE_ONMAINGAME) return;
            if (m_bInputStatus) return;
            if (m_bIsSpecialAbilityEnabled == true)
            {
                if (m_iSpecialAbilityType != 0)
                {
                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_ACTIVATESPECABLTY, 0, 0, 0, 0, 0);
                    m_bIsSpecialAbilityEnabled = false;
                }
                else AddEventList(ON_KEY_UP26, 10);
            }
            else
            {
                if (m_iSpecialAbilityType == 0) AddEventList(ON_KEY_UP26, 10);
                else
                {
                    if ((m_sPlayerAppr4 & 0x00F0) != 0)
                    {
                        AddEventList(ON_KEY_UP28, 10);
                        return;
                    }

                    i = (dwTime - m_dwSpecialAbilitySettingTime) / 1000;
                    i = m_iSpecialAbilityTimeLeftSec - i;
                    if (i < 0) i = 0;

                    ZeroMemory(G_cTxt, sizeof(G_cTxt));
                    if (i < 60)
                    {
                        switch (m_iSpecialAbilityType)
                        {
                            case 1: wsprintfA(G_cTxt, ON_KEY_UP29, i); break;//"
                            case 2: wsprintfA(G_cTxt, ON_KEY_UP30, i); break;//"
                            case 3: wsprintfA(G_cTxt, ON_KEY_UP31, i); break;//"
                            case 4: wsprintfA(G_cTxt, ON_KEY_UP32, i); break;//"
                            case 5: wsprintfA(G_cTxt, ON_KEY_UP33, i); break;//"
                            case 50:wsprintfA(G_cTxt, ON_KEY_UP34, i); break;//"
                            case 51:wsprintfA(G_cTxt, ON_KEY_UP35, i); break;//"
                            case 52:wsprintfA(G_cTxt, ON_KEY_UP36, i); break;//"
                        }
                    }
                    else
                    {
                        switch (m_iSpecialAbilityType)
                        {
                            case 1: wsprintfA(G_cTxt, ON_KEY_UP37, i / 60); break;//"
                            case 2: wsprintfA(G_cTxt, ON_KEY_UP38, i / 60); break;//"
                            case 3: wsprintfA(G_cTxt, ON_KEY_UP39, i / 60); break;//"
                            case 4: wsprintfA(G_cTxt, ON_KEY_UP40, i / 60); break;//"
                            case 5: wsprintfA(G_cTxt, ON_KEY_UP41, i / 60); break;//"
                            case 50:wsprintfA(G_cTxt, ON_KEY_UP42, i / 60); break;//"
                            case 51:wsprintfA(G_cTxt, ON_KEY_UP43, i / 60); break;//"
                            case 52:wsprintfA(G_cTxt, ON_KEY_UP44, i / 60); break;//"
                        }
                    }
                    AddEventList(G_cTxt, 10);
                }
            }
            break;
    }
}

void CGame::OnKeyDown(WPARAM wParam)
{
    switch (wParam)
    {

#ifdef DEF_EQUILIBRIUM_PROJECT //  pour marcher en mode Course
        case 222: // VK_OEM_7:
            m_bVK_OEM_7Pressed = true;
            break;
#endif

        case VK_CONTROL:
            m_bCtrlPressed = true;
            break;
        case VK_SHIFT:
            m_bShiftPressed = true;
            break;
        case VK_INSERT:
        case VK_DELETE:
        case VK_TAB:
        case VK_RETURN:
        case VK_ESCAPE:
        case VK_END:
        case VK_HOME:
        case VK_F1:
        case VK_F2:
        case VK_F3:
        case VK_F4:
        case VK_F5:
        case VK_F6:
        case VK_F7:
        case VK_F8:
        case VK_F9:
        case VK_F10:
        case VK_F11:
        case VK_F12:
        case VK_PRIOR: // Page-Up
        case VK_NEXT: // Page-Down
        case VK_LWIN:
        case VK_RWIN:
        case VK_MULTIPLY:
        case VK_ADD: //'+'
        case VK_SEPARATOR:
        case VK_SUBTRACT: //'-'
        case VK_DECIMAL:
        case VK_DIVIDE:
        case VK_NUMLOCK:
        case VK_SCROLL:
            break;

        default:
            if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME)
            {
                if (m_bCtrlPressed)
                {
                    switch (wParam)
                    {
                        case 48: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 9; break; // 0
                        case 49: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 0; break; // 1
                        case 50: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 1; break; // 2
                        case 51: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 2; break; // 3
                        case 52: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 3; break; // 4
                        case 53: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 4; break; // 5
                        case 54: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 5; break; // 6
                        case 55: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 6; break; // 7
                        case 56: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 7; break; // 8
                        case 57: EnableDialogBox(3, 0, 0, 0); m_stDialogBoxInfo[3].sView = 8; break; // 9
                    }
                }
                else if ((m_bInputStatus == false) && (GetAsyncKeyState(VK_MENU) >> 15 == false))
                {
                    StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
                    ClearInputString();
                }
            }
            break;
    }
}

void CGame::ReserveFightzoneResponseHandler(char * pData)
{
    uint16_t * wpResult;
    char * cp;
    int * ip;
    wpResult = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    switch (*wpResult)
    {
        case DEF_MSGTYPE_CONFIRM:
            AddEventList(RESERVE_FIGHTZONE_RESPONSE_HANDLER1, 10);
            m_stDialogBoxInfo[7].cMode = 14;
            m_iFightzoneNumber = m_iFightzoneNumberTemp;
            break;

        case DEF_MSGTYPE_REJECT:
            cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
            ip = (int *)cp;
            cp += 4;
            AddEventList(RESERVE_FIGHTZONE_RESPONSE_HANDLER2, 10);
            m_iFightzoneNumberTemp = 0;

            if (*ip == 0)
            {
                m_stDialogBoxInfo[7].cMode = 15;
            }
            else if (*ip == -1)
            {
                m_stDialogBoxInfo[7].cMode = 16;
            }
            else if (*ip == -2)
            {
                m_stDialogBoxInfo[7].cMode = 17;
            }
            else if (*ip == -3)
            {
                m_stDialogBoxInfo[7].cMode = 21;
            }
            else if (*ip == -4)
            {
                m_stDialogBoxInfo[7].cMode = 22;
            }
            break;
    }
}

void CGame::RetrieveItemHandler(char * pData)
{
    char * cp, cBankItemIndex, cItemIndex, cTxt[120];
    uint16_t * wp;
    int j;
    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    if (*wp != DEF_MSGTYPE_REJECT)
    {
        cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
        cBankItemIndex = *cp;
        cp++;
        cItemIndex = *cp;
        cp++;

        if (m_pBankList[cBankItemIndex] != 0)
        {
            // v1.42
            char cStr1[64], cStr2[64], cStr3[64];
            GetItemName(m_pBankList[cBankItemIndex], cStr1, cStr2, cStr3);

            ZeroMemory(cTxt, sizeof(cTxt));
            wsprintfA(cTxt, RETIEVE_ITEM_HANDLER4, cStr1);//""You took out %s."
            AddEventList(cTxt, 10);

            if ((m_pBankList[cBankItemIndex]->m_cItemType == DEF_ITEMTYPE_CONSUME) ||
                (m_pBankList[cBankItemIndex]->m_cItemType == DEF_ITEMTYPE_ARROW))
            {
                if (m_pItemList[cItemIndex] == 0) goto RIH_STEP2;
                delete m_pBankList[cBankItemIndex];
                m_pBankList[cBankItemIndex] = 0;
                for (j = 0; j <= DEF_MAXBANKITEMS - 2; j++)
                {
                    if ((m_pBankList[j + 1] != 0) && (m_pBankList[j] == 0))
                    {
                        m_pBankList[j] = m_pBankList[j + 1];
                        m_pBankList[j + 1] = 0;
                    }
                }
            }
            else
            {
                RIH_STEP2:;
                if (m_pItemList[cItemIndex] != 0) return;
                short nX, nY;
                nX = 40;
                nY = 30;
                for (j = 0; j < DEF_MAXITEMS; j++)
                {
                    if ((m_pItemList[j] != 0) && (memcmp(m_pItemList[j]->m_cName, cStr1, 20) == 0))
                    {
                        nX = m_pItemList[j]->m_sX + 1;
                        nY = m_pItemList[j]->m_sY + 1;
                        break;
                    }
                }
                m_pItemList[cItemIndex] = m_pBankList[cBankItemIndex];
                m_pItemList[cItemIndex]->m_sX = nX;
                m_pItemList[cItemIndex]->m_sY = nY;
                bSendCommand(MSGID_REQUEST_SETITEMPOS, 0, cItemIndex, nX, nY, 0, 0);

                for (j = 0; j < DEF_MAXITEMS; j++)
                    if (m_cItemOrder[j] == -1)
                    {
                        m_cItemOrder[j] = cItemIndex;
                        break;
                    }
                m_bIsItemEquipped[cItemIndex] = false;
                m_bIsItemDisabled[cItemIndex] = false;
                m_pBankList[cBankItemIndex] = 0;
                for (j = 0; j <= DEF_MAXBANKITEMS - 2; j++)
                {
                    if ((m_pBankList[j + 1] != 0) && (m_pBankList[j] == 0))
                    {
                        m_pBankList[j] = m_pBankList[j + 1];
                        m_pBankList[j + 1] = 0;
                    }
                }
            }
        }
    }
    m_stDialogBoxInfo[14].cMode = 0;
}

void CGame::EraseItem(char cItemID)
{
    int i;
    char cStr1[64], cStr2[64], cStr3[64];
    ZeroMemory(cStr1, sizeof(cStr1));
    ZeroMemory(cStr2, sizeof(cStr2));
    ZeroMemory(cStr3, sizeof(cStr3));
    for (i = 0; i < 6; i++)
    {
        if (m_sShortCut[i] == cItemID)
        {
            GetItemName(m_pItemList[cItemID], cStr1, cStr2, cStr3);
            if (i < 3) wsprintfA(G_cTxt, ERASE_ITEM, cStr1, cStr2, cStr3, i + 1);
            else wsprintfA(G_cTxt, ERASE_ITEM, cStr1, cStr2, cStr3, i + 7);
            AddEventList(G_cTxt, 10);
            m_sShortCut[i] = -1;
        }
    }

    if (cItemID == m_sRecentShortCut)
        m_sRecentShortCut = -1;
    // ItemOrder
    for (i = 0; i < DEF_MAXITEMS; i++)
        if (m_cItemOrder[i] == cItemID)
            m_cItemOrder[i] = -1;
    for (i = 1; i < DEF_MAXITEMS; i++)
        if ((m_cItemOrder[i - 1] == -1) && (m_cItemOrder[i] != -1))
        {
            m_cItemOrder[i - 1] = m_cItemOrder[i];
            m_cItemOrder[i] = -1;
        }
    // ItemList
    delete m_pItemList[cItemID];
    m_pItemList[cItemID] = 0;
    m_bIsItemEquipped[cItemID] = false;
    m_bIsItemDisabled[cItemID] = false;
}

void CGame::DrawNpcName(short sX, short sY, short sOwnerType, int iStatus)
{
    char cTxt[32], cTxt2[64];
    ZeroMemory(cTxt, sizeof(cTxt));
    ZeroMemory(cTxt2, sizeof(cTxt2));
    GetNpcName(sOwnerType, cTxt);
    if ((iStatus & 0x20) != 0) strcat(cTxt, DRAW_OBJECT_NAME50);//" Berserk"
    if ((iStatus & 0x40) != 0) strcat(cTxt, DRAW_OBJECT_NAME51);//" Frozen"
    PutString2(sX, sY, cTxt, 255, 255, 255);
    if (m_bIsObserverMode == true) PutString2(sX, sY + 14, cTxt, 50, 50, 255);
    else if (m_bIsConfusion || (m_iIlusionOwnerH != 0))
    {
        ZeroMemory(cTxt, sizeof(cTxt));
        strcpy(cTxt, DRAW_OBJECT_NAME87);//"(Unknown)"
        PutString2(sX, sY + 14, cTxt, 150, 150, 150); // v2.171
    }
    else
    {
        switch (_iGetFOE(iStatus))
        {

#ifdef DEF_EQUILIBRIUM_PROJECT // Mob's Boss
            case -2:
                PutString2(sX, sY + 14, "(Enemy Boss)", 210, 0, 255);
                break;
#else
            case -2:
                PutString2(sX, sY + 14, DRAW_OBJECT_NAME90, 255, 0, 0); // "(Enemy)"
                break;
#endif

            case -1:
                PutString2(sX, sY + 14, DRAW_OBJECT_NAME90, 255, 0, 0); // "(Enemy)"
                break;
            case 0:
                PutString2(sX, sY + 14, DRAW_OBJECT_NAME88, 50, 50, 255); // "Neutral"
                break;
            case 1:
                PutString2(sX, sY + 14, DRAW_OBJECT_NAME89, 30, 255, 30); // "(Friendly)"
                break;
        }
    }
#ifdef _DEBUG
    wsprintfA(cTxt2, "Status: 0x%.8X ", iStatus);
    PutString2(sX, sY + 42, cTxt2, 30, 255, 30);
    ZeroMemory(cTxt2, sizeof(cTxt2));
#endif

    switch ((iStatus & 0x0F00) >> 8)
    {
        case 0: break;
        case 1: strcpy(cTxt2, DRAW_OBJECT_NAME52); break;//"Clairvoyant"
        case 2: strcpy(cTxt2, DRAW_OBJECT_NAME53); break;//"Destruction of Magic Protection"
        case 3: strcpy(cTxt2, DRAW_OBJECT_NAME54); break;//"Anti-Physical Damage"
        case 4: strcpy(cTxt2, DRAW_OBJECT_NAME55); break;//"Anti-Magic Damage"
        case 5: strcpy(cTxt2, DRAW_OBJECT_NAME56); break;//"Poisonous"
        case 6: strcpy(cTxt2, DRAW_OBJECT_NAME57); break;//"Critical Poisonous"
        case 7: strcpy(cTxt2, DRAW_OBJECT_NAME58); break;//"Explosive"
        case 8: strcpy(cTxt2, DRAW_OBJECT_NAME59); break;//"Critical Explosive"
#ifdef DEF_EQUILIBRIUM_PROJECT // Mob's Special Abilities
        case 9:  strcpy(cTxt2, DRAW_OBJECT_NAME46); break;//"Swift"
        case 10: strcpy(cTxt2, DRAW_OBJECT_NAME47); break;//"Mighty"
        case 11: strcpy(cTxt2, DRAW_OBJECT_NAME48); break;//"Shaman"
        case 12: strcpy(cTxt2, DRAW_OBJECT_NAME49); break;//"Crippled"
#endif
    }
    if (m_Misc.bCheckIMEString(cTxt2)) PutString_SprFont3(sX, sY + 28, cTxt2, m_wR[13] * 4, m_wG[13] * 4, m_wB[13] * 4, false, 2);
    else PutString2(sX, sY + 28, cTxt2, 240, 240, 70);

}

void CGame::DrawObjectName(short sX, short sY, char * pName, int iStatus)
{
    char cTxt[64], cTxt2[64];
    short sR, sG, sB;
    int i, iGuildIndex, iFOE, iAddY = 0;
    bool bPK, bCitizen, bAresden, bHunter;
    iFOE = _iGetFOE(iStatus);
    if (iFOE < 0)
    {
        sR = 255; sG = 0; sB = 0;
        //{	sR = 250; sG = 250; sB = 250;
    }
    else if (iFOE == 0)
    {
        sR = 50; sG = 50; sB = 255;
    }
    else
    {
        sR = 30; sG = 200; sB = 30;
    }
    ZeroMemory(cTxt, sizeof(cTxt));
    ZeroMemory(cTxt2, sizeof(cTxt2));

    if (m_iIlusionOwnerH == 0)
    {
        if (m_bIsCrusadeMode == false) wsprintfA(cTxt, "%s", pName);
        else
        {
            if (_tmp_wObjectID >= 10000) strcpy(cTxt, NPC_NAME_MERCENARY); //"Mercenary"
            else
            {
                if (iFOE == -1) wsprintfA(cTxt, "%d", _tmp_wObjectID);
                else strcpy(cTxt, pName);
            }
        }
        if (m_iPartyStatus != 0)
        {
            for (i = 0; i < DEF_MAXPARTYMEMBERS; i++)
            {
                if (strcmp(m_stPartyMemberNameList[i].cName, pName) == 0)
                {
                    strcat(cTxt, BGET_NPC_NAME23); // ", Party Member"
                    break;
                }
            }
        }
    }
    else strcpy(cTxt, "?????");

    if ((iStatus & 0x20) != 0) strcat(cTxt, DRAW_OBJECT_NAME50);//" Berserk"
    if ((iStatus & 0x40) != 0) strcat(cTxt, DRAW_OBJECT_NAME51);//" Frozen"

    PutString2(sX, sY, cTxt, 255, 255, 255);
    ZeroMemory(cTxt, sizeof(cTxt));

#ifdef DEF_EQUILIBRIUM_PROJECT	// Naming an "Executor"
    if (iStatus & 0x80000000) bPK = true;
    else bPK = false;
    if (iStatus & 0x40000000) bCitizen = true;
    else bCitizen = false;
    if (iStatus & 0x20000000) bAresden = true;
    else bAresden = false;
    if (iStatus & 0x10000000) bHunter = true;
    else bHunter = false;
    if (memcmp(m_cPlayerName, pName, 10) == 0)
    {
        if (m_iGuildRank == 0)
        {
            wsprintfA(G_cTxt, DEF_MSG_GUILDMASTER, m_cGuildName);//" Guildmaster)"
            PutString2(sX, sY + 14, G_cTxt, 180, 180, 180);
            iAddY = 14;
        }
        if (m_iGuildRank > 0)
        {
            wsprintfA(G_cTxt, DEF_MSG_GUILDSMAN, m_cGuildName);//" Guildsman)"
            PutString2(sX, sY + 14, G_cTxt, 180, 180, 180);
            iAddY = 14;
        }
        if (bPK == true)
        {
            sR = 255; sG = 0; sB = 0;
        }
        else
        {
            sR = 30; sG = 200; sB = 30;
        }
    }
    else
    {
#else
    if (memcmp(m_cPlayerName, pName, 10) == 0)
    {
        if (m_iGuildRank == 0)
        {
            wsprintfA(G_cTxt, DEF_MSG_GUILDMASTER, m_cGuildName);//" Guildmaster)"
            PutString2(sX, sY + 14, G_cTxt, 180, 180, 180);
            iAddY = 14;
        }
        if (m_iGuildRank > 0)
        {
            wsprintfA(G_cTxt, DEF_MSG_GUILDSMAN, m_cGuildName);//" Guildsman)"
            PutString2(sX, sY + 14, G_cTxt, 180, 180, 180);
            iAddY = 14;
        }
        if (m_iPKCount != 0)
        {
            bPK = true;
            sR = 255; sG = 0; sB = 0;
        }
        else
        {
            bPK = false;
            sR = 30; sG = 200; sB = 30;
        }
        bCitizen = m_bCitizen;
        bAresden = m_bAresden;
        bHunter = m_bHunter;
    }
    else
    {
        if (iStatus & 0x80000000) bPK = true;
        else bPK = false;
        if (iStatus & 0x40000000) bCitizen = true;
        else bCitizen = false;
        if (iStatus & 0x20000000) bAresden = true;
        else bAresden = false;
        if (iStatus & 0x10000000) bHunter = true;
        else bHunter = false;
#endif

        if (m_bIsCrusadeMode == false || iFOE >= 0)
        {
            if (FindGuildName(pName, &iGuildIndex) == true)
            {
                if (m_stGuildName[iGuildIndex].cGuildName[0] != 0)
                {
                    if (strcmp(m_stGuildName[iGuildIndex].cGuildName, "NONE") != 0)
                    {
                        if (m_stGuildName[iGuildIndex].iGuildRank == 0)
                        {
                            wsprintfA(G_cTxt, DEF_MSG_GUILDMASTER, m_stGuildName[iGuildIndex].cGuildName);//
                            PutString2(sX, sY + 14, G_cTxt, 180, 180, 180);
                            m_stGuildName[iGuildIndex].dwRefTime = m_dwCurTime;
                            iAddY = 14;
                        }
                        else if (m_stGuildName[iGuildIndex].iGuildRank > 0)
                        {
                            wsprintfA(G_cTxt, DEF_MSG_GUILDSMAN, m_stGuildName[iGuildIndex].cGuildName);//"
                            PutString2(sX, sY + 14, G_cTxt, 180, 180, 180);
                            m_stGuildName[iGuildIndex].dwRefTime = m_dwCurTime;
                            iAddY = 14;
                        }
                    }
                    else
                    {
                        m_stGuildName[iGuildIndex].dwRefTime = 0;
                    }
                }
            }
            else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQGUILDNAME, 0, _tmp_wObjectID, iGuildIndex, 0, 0);
        }
    }

#ifdef DEF_EQUILIBRIUM_PROJECT // Naming an "Executor"
    if (bCitizen == false)
    {
        if (bHunter == true)
            strcpy(cTxt, DRAW_OBJECT_NAME60); // "Traveller"
        else strcpy(cTxt, "Executor"); // "Executor"
    }
    else
    {
        if (bAresden)
        {
            if (bHunter == true) strcpy(cTxt, DEF_MSG_ARECIVIL); // "Aresden Civilian"
            else strcpy(cTxt, DEF_MSG_ARESOLDIER); // "Aresden Combatant"
        }
        else
        {
            if (bHunter == true) strcpy(cTxt, DEF_MSG_ELVCIVIL);// "Elvine Civilian"
            else strcpy(cTxt, DEF_MSG_ELVSOLDIER);	// "Elvine Combatant"
        }
    }
    if (bPK == true)
    {
        if (bCitizen == false)
        {
            if (bHunter == true)
                strcpy(cTxt, DEF_MSG_PK);	//"Criminal"
            else strcpy(cTxt, "Executor Traitor");
        }
        else
        {
            if (bAresden) strcpy(cTxt, DEF_MSG_AREPK);// "Aresden Criminal"
            else strcpy(cTxt, DEF_MSG_ELVPK);   // "Elvine Criminal"
        }
    }
#else
    if (bCitizen == false)	strcpy(cTxt, DRAW_OBJECT_NAME60);// "Traveller"
    else
    {
        if (bAresden)
        {
            if (bHunter == true) strcpy(cTxt, DEF_MSG_ARECIVIL); // "Aresden Civilian"
            else strcpy(cTxt, DEF_MSG_ARESOLDIER); // "Aresden Combatant"
        }
        else
        {
            if (bHunter == true) strcpy(cTxt, DEF_MSG_ELVCIVIL);// "Elvine Civilian"
            else strcpy(cTxt, DEF_MSG_ELVSOLDIER);	// "Elvine Combatant"
        }
    }
    if (bPK == true)
    {
        if (bCitizen == false) strcpy(cTxt, DEF_MSG_PK);	//"Criminal"
        else
        {
            if (bAresden) strcpy(cTxt, DEF_MSG_AREPK);// "Aresden Criminal"
            else strcpy(cTxt, DEF_MSG_ELVPK);  // "Elvine Criminal"
        }
    }
#endif

    PutString2(sX, sY + 14 + iAddY, cTxt, sR, sG, sB);

#ifdef _DEBUG
    wsprintfA(cTxt2, "Status: 0x%.8X ", iStatus);
    PutString2(sX, sY + 42, cTxt2, 30, 255, 30);
    ZeroMemory(cTxt2, sizeof(cTxt2));
#endif
    }

bool CGame::FindGuildName(char * pName, int * ipIndex)
{
    int i, iRet = 0;
    uint64_t dwTmpTime;
    for (i = 0; i < DEF_MAXGUILDNAMES; i++)
    {
        if (memcmp(m_stGuildName[i].cCharName, pName, 10) == 0)
        {
            m_stGuildName[i].dwRefTime = m_dwCurTime;
            *ipIndex = i;
            return true;
        }
    }
    dwTmpTime = m_stGuildName[0].dwRefTime;
    for (i = 0; i < DEF_MAXGUILDNAMES; i++)
    {
        if (m_stGuildName[i].dwRefTime < dwTmpTime)
        {
            iRet = i;
            dwTmpTime = m_stGuildName[i].dwRefTime;
        }
    }
    ZeroMemory(m_stGuildName[iRet].cGuildName, sizeof(m_stGuildName[iRet].cGuildName));
    memcpy(m_stGuildName[iRet].cCharName, pName, 10);
    m_stGuildName[iRet].dwRefTime = m_dwCurTime;
    m_stGuildName[iRet].iGuildRank = -1;
    *ipIndex = iRet;
    return false;
}

void CGame::DrawVersion()
{
    uint64_t dwTime = unixtime();
    //uint16_t  wR, wG, wB;
    //m_Misc.ColorTransfer(m_DDraw.m_cPixelFormat, Color(140, 140, 140), &wR, &wG, &wB);
    // Ver
    m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(14, 463, 19, 140, 140, 140, dwTime);
    // Upper Version
    wsprintfA(G_cTxt, "%d", DEF_UPPERVERSION);
    PutString_SprNum(36, 463, G_cTxt, 140, 140, 140);
    // .
    m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(42, 463, 18, 140, 140, 140, dwTime);
    // Lower Version
    wsprintfA(G_cTxt, "%d", DEF_LOWERVERSION);
    PutString_SprNum(46, 463, G_cTxt, 140, 140, 140);
}

char CGame::GetOfficialMapName(const char * pMapName, char * pName)
{	// MapIndex
    if (strcmp(pMapName, "middleland") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME28);	// Middleland
        return 4;
    }
    else if (strcmp(pMapName, "huntzone3") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME31);	// Death Valley
        return 0;
    }
    else if (strcmp(pMapName, "huntzone1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME29);	// Rocky Highland
        return 1;
    }
    else if (strcmp(pMapName, "elvuni") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME57);	// Eldiniel Garden
        return 2;
    }
    else if (strcmp(pMapName, "elvine") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME24);	// Elvine City
        return 3;
    }
    else if (strcmp(pMapName, "elvfarm") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME2);	// Elvine Farm
        return 5;
    }
    else if (strcmp(pMapName, "arefarm") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME1);	// Aresden Farm
        return 6;
    }
    else if (strcmp(pMapName, "default") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME3);	// Beginner Zone
        return 7;
    }
    else if (strcmp(pMapName, "huntzone4") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME32);	// Silent Wood
        return 8;
    }
    else if (strcmp(pMapName, "huntzone2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME30);	// Eternal Field
        return 9;
    }
    else if (strcmp(pMapName, "areuni") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME56);	// Aresien Garden
        return 10;
    }
    else if (strcmp(pMapName, "aresden") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME22);	// Aresden City
        return 11;
    }
    else if (strcmp(pMapName, "dglv2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME25);	// Dungeon L2
        return 12;
    }
    else if (strcmp(pMapName, "dglv3") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME26);	// Dungeon L3
        return 13;
    }
    else if (strcmp(pMapName, "dglv4") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME53);	// Dungeon L4
        return 14;
    }
    else if (strcmp(pMapName, "elvined1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME23);	// Elvine Dungeon
        return 15;
    }
    else if (strcmp(pMapName, "aresdend1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME21);	// Aresden Dungeon
        return 16;
    }
    else if (strcmp(pMapName, "bisle") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME27);	// Bleeding Island
        return 17;
    }
    else if (strcmp(pMapName, "toh1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME60);	// Tower of Hell 1
        return 18;
    }
    else if (strcmp(pMapName, "toh2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME61);	// Tower of Hell 2
        return 19;
    }
    else if (strcmp(pMapName, "toh3") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME62);	// Tower of Hell 3
        return 20;
    }
    else if (strcmp(pMapName, "middled1x") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME58);	// Middleland Mine
        return 21;
    }
    else if (strcmp(pMapName, "middled1n") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME59);	// Middleland Dungeon
        return 22;
    }
    else if (strcmp(pMapName, "2ndmiddle") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME65);	// Promiseland
        return 23;
    }
    else if (strcmp(pMapName, "icebound") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME66);	// Ice Map
        return 24;
    }
    else if (strcmp(pMapName, "druncncity") == 0) // Apocalypse maps
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME70);
        return 25;
    }
    else if (strcmp(pMapName, "inferniaA") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME71);
        return 26;
    }
    else if (strcmp(pMapName, "inferniaB") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME72);
        return 27;
    }
    else if (strcmp(pMapName, "maze") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME73);
        return 28;
    }
    else if (strcmp(pMapName, "procella") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME74);
        return 29;
    }
    else if (strcmp(pMapName, "abaddon") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME75);
        return 30;
    }
    else if (strcmp(pMapName, "BtField") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME76);
        return 35;
    }
    else if (strcmp(pMapName, "GodH") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME77);
        return 36;
    }
    else if (strcmp(pMapName, "HRampart") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME78);
        return 37;
    }
    else if (strcmp(pMapName, "cityhall_1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME35);	// Aresden Cityhall
        return -1;
    }
    else if (strcmp(pMapName, "cityhall_2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME36);	// Elvine Cityhall
        return -1;
    }
    else if (strcmp(pMapName, "gldhall_1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME37);	// Aresden Guildhall
        return -1;
    }
    else if (strcmp(pMapName, "gldhall_2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME38);	// Elvine Guildhall
        return -1;
    }
    else if (memcmp(pMapName, "bsmith_1", 8) == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME33);	// Aresden Blacksmith
        return -1;
    }
    else if (memcmp(pMapName, "bsmith_2", 8) == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME34);	// Elvine Blacksmith
        return -1;
    }
    else if (memcmp(pMapName, "gshop_1", 7) == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME39);	// Aresden Shop
        return -1;
    }
    else if (memcmp(pMapName, "gshop_2", 7) == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME40);	// Elvine Shop
        return -1;
    }
    else if (memcmp(pMapName, "wrhus_1", 7) == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME43);	// Aresden Warehouse
        return -1;
    }
    else if (memcmp(pMapName, "wrhus_2", 7) == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME44);	// Elvine Warehouse
        return -1;
#ifdef DEF_EQUILIBRIUM_PROJECT	// Equilibrium WH
    }
    else if (strcmp(pMapName, "arewrhus") == 0)
    {
        strcpy(pName, "Equilibrium Warehouse");	// Aresden Warehouse
        return -1;
    }
    else if (strcmp(pMapName, "elvwrhus") == 0)
    {
        strcpy(pName, "Mayor's Warehouse");	// Elvine Warehouse
        return -1;
#else
    }
    else if (strcmp(pMapName, "arewrhus") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME45);	// Aresden Warehouse
        return -1;
    }
    else if (strcmp(pMapName, "elvwrhus") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME46);	// Elvine Warehouse
        return -1;
#endif


    }
    else if (strcmp(pMapName, "wzdtwr_1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME41);	// Magic Tower
        return -1;
    }
    else if (strcmp(pMapName, "wzdtwr_2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME42);	// Magic Tower
        return -1;
    }
    else if (strcmp(pMapName, "cath_1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME47);	// Aresien Church
        return -1;
    }
    else if (strcmp(pMapName, "cath_2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME48);	// Eldiniel Church
        return -1;
    }
    else if (strcmp(pMapName, "resurr1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME54);	// Revival Zone
        return -1;
    }
    else if (strcmp(pMapName, "resurr2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME55);	// Revival Zone
        return -1;
    }
    else if (strcmp(pMapName, "arebrk11") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME4);	// Aresden Barrack 1
        return -1;
    }
    else if (strcmp(pMapName, "arebrk12") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME5);	// Aresden Barrack 1
        return -1;
    }
    else if (strcmp(pMapName, "arebrk21") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME6);	// Aresden Barrack 2
        return -1;
    }
    else if (strcmp(pMapName, "arebrk22") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME7);	// Aresden Barrack 2
        return -1;
    }
    else if (strcmp(pMapName, "elvbrk11") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME8);	// Elvine Barrack 1
        return -1;
    }
    else if (strcmp(pMapName, "elvbrk12") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME9);	// Elvine Barrack 1
        return -1;
    }
    else if (strcmp(pMapName, "elvbrk21") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME10);	// Elvine Barrack 2
        return -1;
    }
    else if (strcmp(pMapName, "elvbrk22") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME11);	// Elvine Barrack 2
        return -1;
    }
    else if (strcmp(pMapName, "fightzone1") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME12);	// Arena 1
        return -1;
    }
    else if (strcmp(pMapName, "fightzone2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME13);	// Arena 2
        return -1;
    }
    else if (strcmp(pMapName, "fightzone3") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME14);	// Arena 3
        return -1;
    }
    else if (strcmp(pMapName, "fightzone4") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME15);	// Arena 4
        return -1;
    }
    else if (strcmp(pMapName, "fightzone5") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME16);	// Arena 5
        return -1;
    }
    else if (strcmp(pMapName, "fightzone6") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME17);	// Arena 6
        return -1;
    }
    else if (strcmp(pMapName, "fightzone7") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME18);	// Arena 7
        return -1;
    }
    else if (strcmp(pMapName, "fightzone8") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME19);	// Arena 8
        return -1;
    }
    else if (strcmp(pMapName, "fightzone9") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME20);	// Arena 9
        return -1;
    }
    else if (strcmp(pMapName, "arejail") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME63);	// Aresden Jail
        return -1;
    }
    else if (strcmp(pMapName, "elvjail") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME64);	// Elvine Jail
        return -1;
    }
    else if (strcmp(pMapName, "CmdHall_1") == 0) // Commander Halls
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME79);
        return -1;
    }
    else if (strcmp(pMapName, "CmdHall_2") == 0)
    {
        strcpy(pName, GET_OFFICIAL_MAP_NAME79);
        return -1;
    }
#ifdef DEF_EQUILIBRIUM_PROJECT	// Equilibrium map names
    else if (strcmp(pMapName, "catacombs") == 0)
    {
        strcpy(pName, "Equilibrium Catacombs");
        return 38;
    }
    else if (strcmp(pMapName, "qusmarsh") == 0)
    {
        strcpy(pName, "Qu's marsh");
        return 39;
    }
    else if (strcmp(pMapName, "asgarde") == 0)
    {
        strcpy(pName, "Mount Asgarde");
        return 40;
    }
    else if (strcmp(pMapName, "lost") == 0)
    {
        strcpy(pName, "Equilibrium City"); // Equilibrium city
        return 41;
    }
    else if (strcmp(pMapName, "stadium") == 0)
    {
        strcpy(pName, "Lost Stadium");
        return 42;
    }
    else if (strcmp(pMapName, "bsmith_3") == 0) // Equilibrium's stores
    {
        strcpy(pName, "Equilibrium Blacksmith");
        return -1;
    }
    else if (strcmp(pMapName, "gshop_3") == 0)
    {
        strcpy(pName, "Equilibrium Shop");
        return -1;
    }
    else if (strcmp(pMapName, "wrhus_3") == 0)
    {
        strcpy(pName, "Equilibrium Warehouse");
        return -1;
    }
#endif
    else
    {
        strcpy(pName, pMapName);
        return -1;
    }
}

bool CGame::bCheckLocalChatCommand(const char * pMsg)
{
    class  CStrTok * pStrTok = 0;
    char * token, cBuff[256], cTxt[120], cName[12], cTemp[120];
    char   seps[] = " \t\n";
    ZeroMemory(cBuff, sizeof(cBuff));
    ZeroMemory(cName, sizeof(cName));
    strcpy(cBuff, pMsg);
    if (memcmp(cBuff, "/showframe", 10) == 0)
    {
        if (m_bShowFPS) m_bShowFPS = false;
        else m_bShowFPS = true;
        return true;
    }
    if (memcmp(cBuff, "/enabletogglescreen", 19) == 0)
    {
        m_bToggleScreen = true;
        return true;
    }
    if (memcmp(cBuff, "/debug", 6) == 0)
    {	/*wsprintfA(G_cTxt,"Debug MP3: %d  wMain: %d"
                , (int) Mp3Debug()
                , (int) G_hWnd);
                DebugLog(G_cTxt);*/
        return true;
    }
    if (memcmp(cBuff, "/whon", 5) == 0)
    {
        m_bWhisper = true;
        AddEventList(BCHECK_LOCAL_CHAT_COMMAND6, 10);// Enable to listen to whispers."
        return true;
    }
    else if (memcmp(cBuff, "/whoff", 6) == 0)
    {
        m_bWhisper = false;
        AddEventList(BCHECK_LOCAL_CHAT_COMMAND7, 10);//
        return true;
    }
    else if (memcmp(cBuff, "/shon", 5) == 0)
    {
        m_bShout = true;
        AddEventList(BCHECK_LOCAL_CHAT_COMMAND8, 10); //Enalbe to chat in public."
        return true;
    }
    else if (memcmp(cBuff, "/shoff", 6) == 0)
    {
        m_bShout = false;
        AddEventList(BCHECK_LOCAL_CHAT_COMMAND9, 10); //Unable to chat in public."
        return true;
    }
    if (memcmp(cBuff, "/tooff", 6) == 0)
    {
        pStrTok = new class CStrTok(cBuff, seps);
        token = pStrTok->pGet();
        token = pStrTok->pGet();
        if (token != 0)
        {
            if (strlen(token) <= 10)
            {
                strcpy(cName, token);
                if (memcmp(m_cPlayerName, cName, 10) == 0)
                {
                    AddEventList(BCHECK_LOCAL_CHAT_COMMAND2, 10);
                    if (pStrTok != 0) delete pStrTok;
                    return true;
                }
                if (m_pExID != 0) delete m_pExID;
                wsprintfA(cTxt, BCHECK_LOCAL_CHAT_COMMAND3, token);
                AddEventList(cTxt, 10);
                m_pExID = new class CMsg(0, token, 0);
                if (pStrTok != 0) delete pStrTok;
                return true;
            }
            else AddEventList(BCHECK_LOCAL_CHAT_COMMAND5, 10);
        }
        if (pStrTok != 0) delete pStrTok;
        return true;
    }
    else if (memcmp(cBuff, "/toon", 5) == 0)
    {
        pStrTok = new class CStrTok(cBuff, seps);
        token = pStrTok->pGet();
        token = pStrTok->pGet();
        if (token != 0)
        {
            if (strlen(token) <= 10)
            {
                strcpy(cName, token);
                if (m_pExID != 0)
                {
                    ZeroMemory(cTemp, sizeof(cTemp));
                    strcpy(cTemp, m_pExID->m_pMsg);
                    if (memcmp(cTemp, cName, 10) == 0)
                    {
                        wsprintfA(cTxt, BCHECK_LOCAL_CHAT_COMMAND1, token);
                        AddEventList(cTxt, 10);
                        delete m_pExID;
                        m_pExID = 0;
                        if (pStrTok != 0) delete pStrTok;
                        return true;
                    }
                }
            }
            else AddEventList(BCHECK_LOCAL_CHAT_COMMAND5, 10);
        }
        if (pStrTok != 0) delete pStrTok;
        return true;
    }
    if (pStrTok != 0) delete pStrTok;
    return false;
}

bool CGame::bCheckItemOperationEnabled(char cItemID)
{
    if (m_pItemList[cItemID] == 0) return false;
    if (m_cCommand < 0) return false;
    if (m_bIsTeleportRequested == true) return false;
    if (m_bIsItemDisabled[cItemID] == true) return false;
    //if (m_bFullParalyze) return false;

    if ((m_pItemList[cItemID]->m_sSpriteFrame == 155) && (m_bUsingSlate == true))
    {
        if ((m_cMapIndex == 35) || (m_cMapIndex == 36) || (m_cMapIndex == 37))
        {
            AddEventList(DEF_MSG_NOTIFY_SLATE_WRONG_MAP, 10); // "You cannot use it right here."
            return false;
        }
        AddEventList(DEF_MSG_NOTIFY_SLATE_ALREADYUSING, 10); // Already Using Another Slate
        return false;
    }

    if (m_bIsDialogEnabled[17] == true)		// Inventory
    {
        AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10); // "Item transaction not finished."
        return false;
    }

    if (m_bIsDialogEnabled[20] == true)			// NpcActionQuery Dialog
    {
        AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
        return false;
    }

    if (m_bIsDialogEnabled[23] == true) 		//ItemSellorRepair Dialog
    {
        AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
        return false;
    }

    if (m_bIsDialogEnabled[26] == true)			//Manufacture Dialog
    {
        AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
        return false;
    }

    if (m_bIsDialogEnabled[27] == true)			//Exchange Dialog
    {
        AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
        return false;
    }

    if (m_bIsDialogEnabled[31] == true) 		//Sell List Dialog
    {
        AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
        return false;
    }

    if (m_bIsDialogEnabled[4] == true) 			// Item drop confirmation
    {
        AddEventList(BCHECK_ITEM_OPERATION_ENABLE1, 10);
        return false;
    }

    return true;
}

void CGame::ClearSkillUsingStatus()
{
    if (m_bSkillUsingStatus == true)
    {
        AddEventList(CLEAR_SKILL_USING_STATUS1, 10);//"
        DisableDialogBox(24);
        DisableDialogBox(26);
        if ((m_sPlayerType >= 1) && (m_sPlayerType <= 6)/* && ((m_sPlayerAppr2 & 0xF000) == 0)*/)
        {
            m_cCommand = DEF_OBJECTSTOP;
            m_sCommX = m_sPlayerX;
            m_sCommY = m_sPlayerY;
        }
    }
    m_bSkillUsingStatus = false;
}


void CGame::NpcTalkHandler(char * pData)
{
    char * cp, cRewardName[21], cTargetName[21], cTemp[21], cTxt[250];
    short * sp, sType, sResponse;
    int     iAmount, iIndex, iContribution, iX, iY, iRange;
    int     iTargetType, iTargetCount, iQuestionType;

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    sp = (short *)cp;
    sType = *sp;
    cp += 2;
    sp = (short *)cp;
    sResponse = *sp;
    cp += 2;
    sp = (short *)cp;
    iAmount = *sp;
    cp += 2;
    sp = (short *)cp;
    iContribution = *sp;
    cp += 2;
    sp = (short *)cp;
    iTargetType = *sp;
    cp += 2;
    sp = (short *)cp;
    iTargetCount = *sp;
    cp += 2;
    sp = (short *)cp;
    iX = *sp;
    cp += 2;
    sp = (short *)cp;
    iY = *sp;
    cp += 2;
    sp = (short *)cp;
    iRange = *sp;
    cp += 2;
    ZeroMemory(cRewardName, sizeof(cRewardName));
    memcpy(cRewardName, cp, 20);
    cp += 20;
    ZeroMemory(cTargetName, sizeof(cTargetName));
    memcpy(cTargetName, cp, 20);
    cp += 20;
    EnableDialogBox(21, sResponse, sType, 0);

    if ((sType >= 1) && (sType <= 100))
    {
        iIndex = m_stDialogBoxInfo[21].sV1;
        m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
        iIndex++;
        iQuestionType = 0;
        switch (sType)
        {
            case 1: //Monster Hunt
                ZeroMemory(cTemp, sizeof(cTemp));
                GetNpcName(iTargetType, cTemp);
                ZeroMemory(cTxt, sizeof(cTxt));
                wsprintfA(cTxt, NPC_TALK_HANDLER16, iTargetCount, cTemp);
                m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                iIndex++;

                ZeroMemory(cTxt, sizeof(cTxt));
                if (memcmp(cTargetName, "NONE", 4) == 0)
                {
                    strcpy(cTxt, NPC_TALK_HANDLER17);//"
                    m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                    iIndex++;
                }
                else
                {
                    ZeroMemory(cTemp, sizeof(cTemp));
                    GetOfficialMapName(cTargetName, cTemp);
                    wsprintfA(cTxt, NPC_TALK_HANDLER18, cTemp);//"Map : %s"
                    m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                    iIndex++;

                    if (iX != 0)
                    {
                        ZeroMemory(cTxt, sizeof(cTxt));
                        wsprintfA(cTxt, NPC_TALK_HANDLER19, iX, iY, iRange);//"Position: %d,%d within %d blocks"
                        m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                        iIndex++;
                    }

                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, NPC_TALK_HANDLER20, iContribution);//"
                    m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                    iIndex++;
                }
                iQuestionType = 1;
                break;

            case 7: //
                ZeroMemory(cTxt, sizeof(cTxt));
                m_pMsgTextList2[iIndex] = new class CMsg(0, NPC_TALK_HANDLER21, 0);
                iIndex++;

                ZeroMemory(cTxt, sizeof(cTxt));
                if (memcmp(cTargetName, "NONE", 4) == 0)
                {
                    strcpy(cTxt, NPC_TALK_HANDLER22);
                    m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                    iIndex++;
                }
                else
                {
                    ZeroMemory(cTemp, sizeof(cTemp));
                    GetOfficialMapName(cTargetName, cTemp);
                    wsprintfA(cTxt, NPC_TALK_HANDLER23, cTemp);
                    m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                    iIndex++;

                    if (iX != 0)
                    {
                        ZeroMemory(cTxt, sizeof(cTxt));
                        wsprintfA(cTxt, NPC_TALK_HANDLER24, iX, iY, iRange);
                        m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                        iIndex++;
                    }

                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, NPC_TALK_HANDLER25, iContribution);
                    m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                    iIndex++;
                }
                iQuestionType = 1;
                break;

            case 10: // Crusade
                ZeroMemory(cTxt, sizeof(cTxt));
                m_pMsgTextList2[iIndex] = new class CMsg(0, NPC_TALK_HANDLER26, 0);
                iIndex++;

                ZeroMemory(cTxt, sizeof(cTxt));
                strcpy(cTxt, NPC_TALK_HANDLER27);//"
                m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                iIndex++;

                ZeroMemory(cTxt, sizeof(cTxt));
                strcpy(cTxt, NPC_TALK_HANDLER28);//"
                m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                iIndex++;

                ZeroMemory(cTxt, sizeof(cTxt));
                strcpy(cTxt, NPC_TALK_HANDLER29);//"
                m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                iIndex++;

                ZeroMemory(cTxt, sizeof(cTxt));
                strcpy(cTxt, NPC_TALK_HANDLER30);//"
                m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                iIndex++;

                ZeroMemory(cTxt, sizeof(cTxt));
                strcpy(cTxt, " ");
                m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                iIndex++;

                ZeroMemory(cTxt, sizeof(cTxt));
                if (memcmp(cTargetName, "NONE", 4) == 0)
                {
                    strcpy(cTxt, NPC_TALK_HANDLER31);//"
                    m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                    iIndex++;
                }
                else
                {
                    ZeroMemory(cTemp, sizeof(cTemp));
                    GetOfficialMapName(cTargetName, cTemp);
                    wsprintfA(cTxt, NPC_TALK_HANDLER32, cTemp);//"
                    m_pMsgTextList2[iIndex] = new class CMsg(0, cTxt, 0);
                    iIndex++;
                }
                iQuestionType = 2;
                break;
        }

        switch (iQuestionType)
        {
            case 1:
                m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
                iIndex++;
                m_pMsgTextList2[iIndex] = new class CMsg(0, NPC_TALK_HANDLER33, 0);//"
                iIndex++;
                m_pMsgTextList2[iIndex] = new class CMsg(0, NPC_TALK_HANDLER34, 0);//"
                iIndex++;
                m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
                iIndex++;
                break;

            case 2:
                m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
                iIndex++;
                m_pMsgTextList2[iIndex] = new class CMsg(0, NPC_TALK_HANDLER35, 0);//"
                iIndex++;
                m_pMsgTextList2[iIndex] = new class CMsg(0, "  ", 0);
                iIndex++;
                break;

            default: break;
        }
    }
}

void CGame::GetNpcName(short sType, char * pName)
{
    switch (sType)
    {
        case 10: strcpy(pName, NPC_NAME_SLIME); break;
        case 11: strcpy(pName, NPC_NAME_SKELETON); break;
        case 12: strcpy(pName, NPC_NAME_STONEGOLEM); break;
        case 13: strcpy(pName, NPC_NAME_CYCLOPS); break;
        case 14: strcpy(pName, NPC_NAME_ORC); break;
        case 15: strcpy(pName, NPC_NAME_SHOP_KEEPER); break;
        case 16: strcpy(pName, NPC_NAME_GIANTANT); break;
        case 17: strcpy(pName, NPC_NAME_GIANTSCORPION); break;
        case 18: strcpy(pName, NPC_NAME_ZOMBIE); break;
        case 19: strcpy(pName, NPC_NAME_MAGICIAN); break;
        case 20: strcpy(pName, NPC_NAME_WAREHOUSE_KEEPER); break;
        case 21: strcpy(pName, NPC_NAME_GUARD); break;
        case 22: strcpy(pName, NPC_NAME_SNAKE); break;
        case 23: strcpy(pName, NPC_NAME_CLAYGOLEM); break;
        case 24: strcpy(pName, NPC_NAME_BLACKSMITH_KEEPER); break;
        case 25: strcpy(pName, NPC_NAME_CITYHALL_OFFICER); break;
        case 26: strcpy(pName, NPC_NAME_GUILDHALL_OFFICER); break;
        case 27: strcpy(pName, NPC_NAME_HELHOUND); break;
        case 28: strcpy(pName, NPC_NAME_TROLL); break;
        case 29: strcpy(pName, NPC_NAME_OGRE); break;
        case 30: strcpy(pName, NPC_NAME_LICHE); break;
        case 31: strcpy(pName, NPC_NAME_DEMON); break;
        case 32: strcpy(pName, NPC_NAME_UNICORN); break;
        case 33: strcpy(pName, NPC_NAME_WEREWOLF); break;
        case 34: strcpy(pName, NPC_NAME_DUMMY); break;
        case 35: strcpy(pName, NPC_NAME_ENERGYSPHERE); break;
        case 36:
            if (_tmp_sAppr2 != 0) strcpy(pName, NPC_NAME_ARROWGUARDTOWER_CK);
            else strcpy(pName, NPC_NAME_ARROWGUARDTOWER);
            break;
        case 37:
            if (_tmp_sAppr2 != 0) strcpy(pName, NPC_NAME_CANNONGUARDTOWER_CK);
            else strcpy(pName, NPC_NAME_CANNONGUARDTOWER);
            break;
        case 38:
            if (_tmp_sAppr2 != 0) strcpy(pName, NPC_NAME_MANACOLLECTOR_CK);
            else strcpy(pName, NPC_NAME_MANACOLLECTOR);
            break;
        case 39:
            if (_tmp_sAppr2 != 0) strcpy(pName, NPC_NAME_DETECTOR_CK);
            else strcpy(pName, NPC_NAME_DETECTOR);
            break;
        case 40: strcpy(pName, NPC_NAME_ENERGYSHIELD); break;
        case 41: strcpy(pName, NPC_NAME_GRANDMAGICGENERATOR); break;
        case 42: strcpy(pName, NPC_NAME_MANASTONE); break;
        case 43: strcpy(pName, NPC_NAME_LIGHTWARBEETLE); break;
        case 44: strcpy(pName, NPC_NAME_GODSHANDKNIGHT); break;
        case 45: strcpy(pName, NPC_NAME_GODSHANDKNIGHT_CK); break;
        case 46: strcpy(pName, NPC_NAME_TEMPLEKNIGHT); break;
        case 47: strcpy(pName, NPC_NAME_BATTLEGOLEM); break;
        case 48: strcpy(pName, NPC_NAME_STALKER); break;
        case 49: strcpy(pName, NPC_NAME_HELLCLAW); break;
        case 50: strcpy(pName, NPC_NAME_TIGERWORM); break;
        case 51: strcpy(pName, NPC_NAME_CATAPULT); break;
        case 52: strcpy(pName, NPC_NAME_GARGOYLE); break;
        case 53: strcpy(pName, NPC_NAME_BEHOLDER); break;
        case 54: strcpy(pName, NPC_NAME_DARKELF); break;
        case 55: strcpy(pName, NPC_NAME_RABBIT); break;
        case 56: strcpy(pName, NPC_NAME_CAT); break;
        case 57: strcpy(pName, NPC_NAME_FROG); break;
        case 58: strcpy(pName, NPC_NAME_MOUNTAIN_GIANT); break;
        case 59: strcpy(pName, NPC_NAME_ETTIN); break;
        case 60: strcpy(pName, NPC_NAME_CANNIBAL); break;
        case 61: strcpy(pName, NPC_NAME_RUDOLPH); break;
        case 62: strcpy(pName, NPC_NAME_DIREBOAR); break;
        case 63: strcpy(pName, NPC_NAME_FROST); break;
        case 64:
        {
            switch ((_tmp_sAppr2 & 0xFF00) >> 8)
            {
                case 1:	strcpy(pName, NPC_NAME_WATERMELON);	break;
                case 2: strcpy(pName, NPC_NAME_PUMPKIN); break;
                case 3: strcpy(pName, NPC_NAME_GARLIC); break;
                case 4: strcpy(pName, NPC_NAME_BARLEY); break;
                case 5:	strcpy(pName, NPC_NAME_CARROT); break;
                case 6: strcpy(pName, NPC_NAME_RADISH); break;
                case 7: strcpy(pName, NPC_NAME_CORN); break;
                case 8: strcpy(pName, NPC_NAME_BFLOWER); break;
                case 9: strcpy(pName, NPC_NAME_MELON); break;
                case 10: strcpy(pName, NPC_NAME_TOMATO); break;
                case 11: strcpy(pName, NPC_NAME_GRAPPE); break;
                case 12: strcpy(pName, NPC_NAME_BLUEGRAPPE); break;
                case 13: strcpy(pName, NPC_NAME_MUSHROM); break;
                case 14: strcpy(pName, NPC_NAME_GINSENG); break;
                default: strcpy(pName, NPC_NAME_CROP); break;
            }
        }
        break;
        case 65: strcpy(pName, NPC_NAME_ICEGOLEM); break;
        case 66: strcpy(pName, NPC_NAME_WYVERN); break;
        case 67: strcpy(pName, NPC_NAME_MCGAFFIN); break;
        case 68: strcpy(pName, NPC_NAME_PERRY); break;
        case 69: strcpy(pName, NPC_NAME_DEVLIN); break;

        case 70: strcpy(pName, NPC_NAME_DRAGON); break;
        case 71: strcpy(pName, NPC_NAME_CENTAUR); break;
        case 72: strcpy(pName, NPC_NAME_CLAWTUR); break;
        case 73: strcpy(pName, NPC_NAME_FIREWYV); break;
        case 74: strcpy(pName, NPC_NAME_GICRAYF); break;
        case 75: strcpy(pName, NPC_NAME_GILIZAR); break;
        case 76: strcpy(pName, NPC_NAME_GITREE); break;
        case 77: strcpy(pName, NPC_NAME_MASTORC); break;
        case 78: strcpy(pName, NPC_NAME_MINAUS); break;
        case 79: strcpy(pName, NPC_NAME_NIZIE); break;

        case 80: strcpy(pName, NPC_NAME_TENTOCL); break;
        case 81: strcpy(pName, NPC_NAME_ABADDON); break;
        case 82: strcpy(pName, NPC_NAME_SORCERS); break;
        case 83: strcpy(pName, NPC_NAME_ATK); break;
        case 84: strcpy(pName, NPC_NAME_MASTELF); break;
        case 85: strcpy(pName, NPC_NAME_DSK); break;
        case 86: strcpy(pName, NPC_NAME_HBT); break;
        case 87: strcpy(pName, NPC_NAME_CT); break;
        case 88: strcpy(pName, NPC_NAME_BARBAR); break;
        case 89: strcpy(pName, NPC_NAME_AGC); break;
        case 90: strcpy(pName, NPC_NAME_GAIL); break;
        case 91: strcpy(pName, NPC_NAME_GATE); break;

        case 95: strcpy(pName, NPC_NAME_WILLOWISP); break;
        case 96: strcpy(pName, NPC_NAME_AIRLEMENTAL); break;
        case 97: strcpy(pName, NPC_NAME_FIRELEMENTAL); break;
        case 98: strcpy(pName, NPC_NAME_EARTHLEMENTAL); break;
        case 99: strcpy(pName, NPC_NAME_ICELEMENTAL); break;
    }
}

void CGame::GetItemName(CItem * pItem, char * pStr1, char * pStr2, char * pStr3)
{
    int i;
    char cTxt[256], cTxt2[256], cName[51];
    uint32_t dwType1, dwType2, dwValue1, dwValue2, dwValue3;

    m_bIsSpecial = false;
    ZeroMemory(cName, sizeof(cName));
    ZeroMemory(pStr1, sizeof(pStr1));
    ZeroMemory(pStr2, sizeof(pStr2));
    ZeroMemory(pStr3, sizeof(pStr3));

    strcpy(cName, pItem->m_cName);
    for (i = 0; i < DEF_MAXITEMNAMES; i++)
        if ((m_pItemNameList[i] != 0) && (strcmp(m_pItemNameList[i]->m_cOriginName, pItem->m_cName) == 0))
        {
            strcpy(cName, m_pItemNameList[i]->m_cName);
            break;
        }

#ifdef DEF_EQUILIBRIUM_PROJECT
    if (0 == memcmp(pItem->m_cName, "Eldiniel", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Aresien", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "SwordSB", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Sting-Dart", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Excalibur", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "AresdenFlag", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "ElvineFlag", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "WandMShield", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "WandMS30", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "MagicNecklace", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Neck", 4)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "ClericSymbol", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "RingInfame", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "LuckyGoldRing", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "EmeraldRing", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "SapphireRing", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "aHero", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "eHero", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "ElfCape", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Blood", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Xelima", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Merien", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "IceElemental", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Medusa", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "DemonSlayer", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "DarkElf", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "RingOf", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Zem", 3)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Ice", 3)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Storm", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "DefenderAxe", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "DarkExecutor", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "LightingBlade", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Kloness", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "BerserkWand ", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "ResurWand", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "AcientTablet", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Fire-Bow", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Direction-Bow", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "BlueArmor", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "RedArmor", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "YellowArmor", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "LuckyArmor", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "LicheArmor", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "AbaddonArmor", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Egg9", 4)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "LichMS10", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "RevivalAxe", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Drow", 4)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "OgressArmor", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "LicheRobe", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Pink", 4)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "AirRing", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "EarthRing", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "FireRing", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "IceRing", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "AvatarRelic", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Magic", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "AngelicPandent", 14)) m_bIsSpecial = true;
#else
    if (0 == memcmp(pItem->m_cName, "AcientTablet", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "NecklaceOf", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "DarkElfBow", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "DarkExecutor", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "The_Devastator", 14)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "DemonSlayer", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "LightingBlade", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "5thAnniversary", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "RubyRing", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "SapphireRing", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Ringof", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "MagicNecklace", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "MagicWand(M.Shield)", 19)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "MagicWand(MS30-LLF)", 19)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Merien", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "BerserkWand", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "ResurWand", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Blood", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Swordof", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "StoneOf", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "ZemstoneofSacrifice", 19)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "StormBringer", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Aresden", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Elvine", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "EmeraldRing", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Excaliber", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Xelima", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "Kloness", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "aHeroOf", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(pItem->m_cName, "eHeroOf", 7)) m_bIsSpecial = true;
#endif

    if ((pItem->m_dwAttribute & 0x00000001) != 0)
    {
        m_bIsSpecial = true;
        strcpy(pStr1, cName);
        if (pItem->m_cItemType == DEF_ITEMTYPE_MATERIAL)
            wsprintfA(pStr2, GET_ITEM_NAME1, pItem->m_sItemSpecEffectValue2);		//"Purity: %d%%"
        else
        {	// Crafting Magins completion fix
            if (pItem->m_cEquipPos == DEF_EQUIPPOS_LFINGER)
            {
                wsprintfA(pStr2, GET_ITEM_NAME2, pItem->m_sItemSpecEffectValue2);	//"Completion: 
            }
            else
            {
                wsprintfA(pStr2, GET_ITEM_NAME2, pItem->m_sItemSpecEffectValue2 + 100);	//"Completion: +100	
            }
        }
    }
    else
    {
        if (pItem->m_dwCount == 1)
            wsprintfA(G_cTxt, "%s", cName);
        else wsprintfA(G_cTxt, DRAW_DIALOGBOX_SELLOR_REPAIR_ITEM1, pItem->m_dwCount, cName);//"%d %s"
        strcpy(pStr1, G_cTxt);
    }

    if ((pItem->m_dwAttribute & 0x00F0F000) != 0)
    {
        m_bIsSpecial = true;
        dwType1 = (pItem->m_dwAttribute & 0x00F00000) >> 20;
        dwValue1 = (pItem->m_dwAttribute & 0x000F0000) >> 16;
        dwType2 = (pItem->m_dwAttribute & 0x0000F000) >> 12;
        dwValue2 = (pItem->m_dwAttribute & 0x00000F00) >> 8;
        if (dwType1 != 0)
        {
            ZeroMemory(cTxt, sizeof(cTxt));
            switch (dwType1)
            {
                case 1: strcpy(cTxt, GET_ITEM_NAME3);   break;
                case 2: strcpy(cTxt, GET_ITEM_NAME4);   break; // "Poisoning "
                case 3: strcpy(cTxt, GET_ITEM_NAME5);   break; // "Righteous "

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 4: strcpy(cTxt, "Wizard's ");		break; // "Wizard's "
#else
                case 4: break;
#endif
                case 5: strcpy(cTxt, GET_ITEM_NAME6);   break; // "Agile "
                case 6: strcpy(cTxt, GET_ITEM_NAME7);   break;
                case 7: strcpy(cTxt, GET_ITEM_NAME8);   break;
                case 8: strcpy(cTxt, GET_ITEM_NAME9);   break;
                case 9: strcpy(cTxt, GET_ITEM_NAME10);  break;
                case 10: strcpy(cTxt, GET_ITEM_NAME11); break;
                case 11: strcpy(cTxt, GET_ITEM_NAME12); break;
                case 12: strcpy(cTxt, GET_ITEM_NAME13); break;
            }
            strcat(cTxt, pStr1);
            ZeroMemory(pStr1, sizeof(pStr1));
            strcpy(pStr1, cTxt);

            ZeroMemory(cTxt, sizeof(cTxt));
            switch (dwType1)
            {
                case 1: wsprintfA(cTxt, GET_ITEM_NAME14, dwValue1); break; // "Critical Hit Damage+%d"
                case 2: wsprintfA(cTxt, GET_ITEM_NAME15, dwValue1 * 5); break; // "Poison Damage+%d"
                case 3: break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 4:
                    switch (dwValue1)
                    {
                        case 1:  wsprintfA(cTxt, "Casts Magic Missile"); break;
                        case 2:  wsprintfA(cTxt, "Casts Energy Bolt"); break;
                        case 3:  wsprintfA(cTxt, "Casts FireBall"); break;
                        case 4:  wsprintfA(cTxt, "Casts FireStrike"); break;
                        case 5:  wsprintfA(cTxt, "Casts Triple Energy Bolt"); break;
                        case 6:  wsprintfA(cTxt, "Casts Chill Wind"); break;
                        case 7:  wsprintfA(cTxt, "Casts Ice Strike"); break;
                        case 8:  wsprintfA(cTxt, "Casts Energy Strike"); break;
                        case 9:  wsprintfA(cTxt, "Casts Armor Break"); break;
                        case 10: wsprintfA(cTxt, "Casts EarthWorm Strike"); break;
                        case 11: wsprintfA(cTxt, "Casts Mass Chill Wind"); break;
                        case 12: wsprintfA(cTxt, "Casts Mass Fire Strike"); break;
                        case 13: wsprintfA(cTxt, "Casts Mass Lightning Strike"); break;
                        case 14: wsprintfA(cTxt, "Casts Mass Ice Strike"); break;
                        case 15: wsprintfA(cTxt, "Casts Meteor Strike"); break;
                    }
                    break;
#else
                case 4: break;
#endif

                case 5: strcpy(cTxt, GET_ITEM_NAME16); break; // "Attack Speed -1"
                case 6: wsprintfA(cTxt, GET_ITEM_NAME17, dwValue1 * 4); break;
                case 7: strcpy(cTxt, GET_ITEM_NAME18); break;
                case 8: wsprintfA(cTxt, GET_ITEM_NAME19, dwValue1 * 7); break;
                case 9: strcpy(cTxt, GET_ITEM_NAME20); break;
                case 10: wsprintfA(cTxt, GET_ITEM_NAME21, dwValue1 * 3); break;
                case 11: wsprintfA(cTxt, GET_ITEM_NAME22, dwValue1); break;
                case 12: wsprintfA(cTxt, GET_ITEM_NAME23, dwValue1); break;
            }
            strcat(pStr2, cTxt);

            if (dwType2 != 0)
            {
                ZeroMemory(cTxt, sizeof(cTxt));
                switch (dwType2)
                {
                    case 1:  wsprintfA(cTxt, GET_ITEM_NAME24, dwValue2 * 7); break;
                    case 2:  wsprintfA(cTxt, GET_ITEM_NAME25, dwValue2 * 7); break;
                    case 3:  wsprintfA(cTxt, GET_ITEM_NAME26, dwValue2 * 7); break;
                    case 4:  wsprintfA(cTxt, GET_ITEM_NAME27, dwValue2 * 7); break;
                    case 5:  wsprintfA(cTxt, GET_ITEM_NAME28, dwValue2 * 7); break;//"SPrec
                    case 6:  wsprintfA(cTxt, GET_ITEM_NAME29, dwValue2 * 7); break;//"MPrec
                    case 7:  wsprintfA(cTxt, GET_ITEM_NAME30, dwValue2 * 7); break;
                    case 8:  wsprintfA(cTxt, GET_ITEM_NAME31, dwValue2 * 3); break;
                    case 9:  wsprintfA(cTxt, GET_ITEM_NAME32, dwValue2 * 3); break;
                    case 10: wsprintfA(cTxt, GET_ITEM_NAME33, dwValue2);   break;
                    case 11: wsprintfA(cTxt, GET_ITEM_NAME34, dwValue2 * 10); break;
                    case 12: wsprintfA(cTxt, GET_ITEM_NAME35, dwValue2 * 10); break;//"Gold +%
                }
                strcpy(pStr3, cTxt);
            }
        }
    }

    dwValue3 = (pItem->m_dwAttribute & 0xF0000000) >> 28;
    if (dwValue3 > 0)
    {
        if (pStr1[strlen(pStr1) - 2] == '+')
        {
            dwValue3 = atoi((char *)(pStr1 + strlen(pStr1) - 1)) + dwValue3;
            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, pStr1, strlen(pStr1) - 2);
            ZeroMemory(cTxt2, sizeof(cTxt2));
            wsprintfA(cTxt2, "%s+%d", cTxt, dwValue3);
            ZeroMemory(pStr1, sizeof(pStr1));
            strcpy(pStr1, cTxt2);

#ifdef DEF_EQUILIBRIUM_PROJECT // MS10..MS11..12..13..
        }
        else if ((strcmp(pItem->m_cName, "NeckMS10") == 0)
            || (strcmp(pItem->m_cName, "NeckMS15") == 0))
        {
            dwValue3 = atoi((char *)(pItem->m_cName + strlen(pItem->m_cName) - 1)) + dwValue3;
            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, pStr1, strlen(pStr1) - 2);
            ZeroMemory(cTxt2, sizeof(cTxt2));
            wsprintfA(cTxt2, "%s%d)", cTxt, dwValue3);
            ZeroMemory(pStr1, sizeof(pStr1));
            strcpy(pStr1, cTxt2);
#endif
        }
        else
        {
            ZeroMemory(cTxt, sizeof(cTxt));
            wsprintfA(cTxt, "+%d", dwValue3);
            strcat(pStr1, cTxt);
        }
    }
}

void CGame::GetItemName(char * cItemName, uint32_t dwAttribute, char * pStr1, char * pStr2, char * pStr3)
{
    int i;
    char cTxt[256], cTxt2[256], cName[51];
    uint32_t dwType1, dwType2, dwValue1, dwValue2, dwValue3;

    m_bIsSpecial = false;
    ZeroMemory(cName, sizeof(cName));
    ZeroMemory(pStr1, sizeof(pStr1));
    ZeroMemory(pStr2, sizeof(pStr2));
    ZeroMemory(pStr3, sizeof(pStr3));

    strcpy(cName, cItemName);
    for (i = 0; i < DEF_MAXITEMNAMES; i++)
        if ((m_pItemNameList[i] != 0) && (strcmp(m_pItemNameList[i]->m_cOriginName, cItemName) == 0))
        {
            strcpy(cName, m_pItemNameList[i]->m_cName);
            break;
        }

#ifdef DEF_EQUILIBRIUM_PROJECT
    if (0 == memcmp(cItemName, "Eldiniel", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Aresien", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "SwordSB", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Sting-Dart", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Excalibur", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "AresdenFlag", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "ElvineFlag", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "WandMShield", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "WandMS30", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "MagicNecklace", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Neck", 4)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "ClericSymbol", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "RingInfame", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "LuckyGoldRing", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "EmeraldRing", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "SapphireRing", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "aHero", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "eHero", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "ElfCape", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Blood", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Xelima", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Merien", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "IceElemental", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Medusa", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "DarkElf", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "RingOf", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Zem", 3)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Ice", 3)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Storm", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "DefenderAxe", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "DarkExecutor", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "LightingBlade", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Kloness", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "BerserkWand ", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "ResurWand", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "AcientTablet", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Fire-Bow", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Direction-Bow", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "BlueArmor", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "RedArmor", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "YellowArmor", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "LuckyArmor", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "LicheArmor", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "AbaddonArmor", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Egg9", 4)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "LichMS10", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "RevivalAxe", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Drow", 4)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "OgressArmor", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "LicheRobe", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Pink", 4)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "AirRing", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "EarthRing", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "FireRing", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "IceRing", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "AvatarRelic", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Magin", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "AngelicPandent", 14)) m_bIsSpecial = true;
#else
    if (0 == memcmp(cItemName, "AcientTablet", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "NecklaceOf", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "DarkElfBow", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "DarkExecutor", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "The_Devastator", 14)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "DemonSlayer", 10)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "LightingBlade", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "5thAnniversary", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "RubyRing", 8)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "SapphireRing", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Ringof", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "MagicNecklace", 13)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "MagicWand(M.Shield)", 19)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "MagicWand(MS30-LLF)", 19)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Merien", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "BerserkWand", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "ResurWand", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Blood", 5)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Swordof", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "StoneOf", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "ZemstoneofSacrifice", 19)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "StormBringer", 12)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Aresden", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Elvine", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "EmeraldRing", 11)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Excaliber", 9)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Xelima", 6)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "Kloness", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "aHeroOf", 7)) m_bIsSpecial = true;
    else if (0 == memcmp(cItemName, "eHeroOf", 7)) m_bIsSpecial = true;
#endif


    strcpy(pStr1, cName);

    if ((dwAttribute & 0x00F0F000) != 0)
    {
        m_bIsSpecial = true;
        dwType1 = (dwAttribute & 0x00F00000) >> 20;
        dwValue1 = (dwAttribute & 0x000F0000) >> 16;
        dwType2 = (dwAttribute & 0x0000F000) >> 12;
        dwValue2 = (dwAttribute & 0x00000F00) >> 8;
        if (dwType1 != 0)
        {
            ZeroMemory(cTxt, sizeof(cTxt));
            switch (dwType1)
            {
                case 1: strcpy(cTxt, GET_ITEM_NAME3); break;
                case 2: strcpy(cTxt, GET_ITEM_NAME4); break;
                case 3: strcpy(cTxt, GET_ITEM_NAME5); break;

#ifdef DEF_EQUILIBRIUM_PROJECT 
                case 4: strcpy(cTxt, "Wizard's ");	break; // "Wizard's "
#else
                case 4: break;
#endif

                case 5: strcpy(cTxt, GET_ITEM_NAME6); break;
                case 6: strcpy(cTxt, GET_ITEM_NAME7); break;
                case 7: strcpy(cTxt, GET_ITEM_NAME8); break;
                case 8: strcpy(cTxt, GET_ITEM_NAME9); break;
                case 9: strcpy(cTxt, GET_ITEM_NAME10); break;
                case 10: strcpy(cTxt, GET_ITEM_NAME11); break;
                case 11: strcpy(cTxt, GET_ITEM_NAME12); break;
                case 12: strcpy(cTxt, GET_ITEM_NAME13); break;
            }
            strcat(cTxt, pStr1);
            ZeroMemory(pStr1, sizeof(pStr1));
            strcpy(pStr1, cTxt);

            ZeroMemory(cTxt, sizeof(cTxt));
            switch (dwType1)
            {
                case 1: wsprintfA(cTxt, GET_ITEM_NAME14, dwValue1); break;
                case 2: wsprintfA(cTxt, GET_ITEM_NAME15, dwValue1 * 5); break;
                case 3: break;

#ifdef DEF_EQUILIBRIUM_PROJECT
                case 4:
                    switch (dwValue1)
                    {
                        case 1:  wsprintfA(cTxt, "Casts Magic Missile"); break;
                        case 2:  wsprintfA(cTxt, "Casts Energy Bolt"); break;
                        case 3:  wsprintfA(cTxt, "Casts FireBall"); break;
                        case 4:  wsprintfA(cTxt, "Casts FireStrike"); break;
                        case 5:  wsprintfA(cTxt, "Casts Triple Energy Bolt"); break;
                        case 6:  wsprintfA(cTxt, "Casts Chill Wind"); break;
                        case 7:  wsprintfA(cTxt, "Casts Ice Strike"); break;
                        case 8:  wsprintfA(cTxt, "Casts Energy Strike"); break;
                        case 9:  wsprintfA(cTxt, "Casts Armor Break"); break;
                        case 10: wsprintfA(cTxt, "Casts EarthWorm Strike"); break;
                        case 11: wsprintfA(cTxt, "Casts Mass Chill Wind"); break;
                        case 12: wsprintfA(cTxt, "Casts Mass Fire Strike"); break;
                        case 13: wsprintfA(cTxt, "Casts Mass Lightning Strike"); break;
                        case 14: wsprintfA(cTxt, "Casts Mass Ice Strike"); break;
                        case 15: wsprintfA(cTxt, "Casts Meteor Strike"); break;
                    }
                    break;
#else
                case 4: break;
#endif

                case 5: strcpy(cTxt, GET_ITEM_NAME16); break;
                case 6: wsprintfA(cTxt, GET_ITEM_NAME17, dwValue1 * 4); break;
                case 7: strcpy(cTxt, GET_ITEM_NAME18); break;
                case 8: wsprintfA(cTxt, GET_ITEM_NAME19, dwValue1 * 7); break;
                case 9: strcpy(cTxt, GET_ITEM_NAME20); break;
                case 10: wsprintfA(cTxt, GET_ITEM_NAME21, dwValue1 * 3); break;
                case 11: wsprintfA(cTxt, GET_ITEM_NAME22, dwValue1); break;
                case 12: wsprintfA(cTxt, GET_ITEM_NAME23, dwValue1); break;
            }
            strcat(pStr2, cTxt);

            if (dwType2 != 0)
            {
                ZeroMemory(cTxt, sizeof(cTxt));
                switch (dwType2)
                {
                    case 1:  wsprintfA(cTxt, GET_ITEM_NAME24, dwValue2 * 7);  break;
                    case 2:  wsprintfA(cTxt, GET_ITEM_NAME25, dwValue2 * 7);  break;
                    case 3:  wsprintfA(cTxt, GET_ITEM_NAME26, dwValue2 * 7);  break;
                    case 4:  wsprintfA(cTxt, GET_ITEM_NAME27, dwValue2 * 7);  break;
                    case 5:  wsprintfA(cTxt, GET_ITEM_NAME28, dwValue2 * 7);  break;
                    case 6:  wsprintfA(cTxt, GET_ITEM_NAME29, dwValue2 * 7);  break;
                    case 7:  wsprintfA(cTxt, GET_ITEM_NAME30, dwValue2 * 7);  break;
                    case 8:  wsprintfA(cTxt, GET_ITEM_NAME31, dwValue2 * 3);  break;
                    case 9:  wsprintfA(cTxt, GET_ITEM_NAME32, dwValue2 * 3);  break;
                    case 10: wsprintfA(cTxt, GET_ITEM_NAME33, dwValue2);    break;
                    case 11: wsprintfA(cTxt, GET_ITEM_NAME34, dwValue2 * 10); break;
                    case 12: wsprintfA(cTxt, GET_ITEM_NAME35, dwValue2 * 10); break;
                }
                strcpy(pStr3, cTxt);
            }
        }
    }

    dwValue3 = (dwAttribute & 0xF0000000) >> 28;
    if (dwValue3 > 0)
    {
        if (pStr1[strlen(pStr1) - 2] == '+')
        {
            dwValue3 = atoi((char *)(pStr1 + strlen(pStr1) - 1)) + dwValue3;
            ZeroMemory(cTxt, sizeof(cTxt));
            memcpy(cTxt, pStr1, strlen(pStr1) - 2);
            ZeroMemory(cTxt2, sizeof(cTxt2));
            wsprintfA(cTxt2, "%s+%d", cTxt, dwValue3);
            ZeroMemory(pStr1, sizeof(pStr1));
            strcpy(pStr1, cTxt2);
        }
        else

#ifdef DEF_EQUILIBRIUM_PROJECT  // MS10..MS11..12..13..
            if ((strcmp(cItemName, "NeckMS10") == 0)
                || (strcmp(cItemName, "NeckMS15") == 0))
            {
                dwValue3 = atoi((char *)(cItemName + strlen(cItemName) - 1)) + dwValue3;
                ZeroMemory(cTxt, sizeof(cTxt));
                memcpy(cTxt, pStr1, strlen(pStr1) - 2);
                ZeroMemory(cTxt2, sizeof(cTxt2));
                wsprintfA(cTxt2, "%s%d)", cTxt, dwValue3);
                ZeroMemory(pStr1, sizeof(pStr1));
                strcpy(pStr1, cTxt2);
            }
            else
#endif

            {
                ZeroMemory(cTxt, sizeof(cTxt));
                wsprintfA(cTxt, "+%d", dwValue3);
                strcat(pStr1, cTxt);
            }
    }
}

void CGame::PointCommandHandler(int indexX, int indexY, char cItemID)
{
    char cTemp[31] = {};
    if ((m_iPointCommandType >= 100) && (m_iPointCommandType < 200))
    {
        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_MAGIC, 0, indexX, indexY, m_iPointCommandType, 0);
    }
    else if ((m_iPointCommandType >= 0) && (m_iPointCommandType < 50))
    {
        bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQ_USEITEM, 0, m_iPointCommandType, indexX, indexY, cTemp, cItemID); // v1.4

        if (m_pItemList[m_iPointCommandType]->m_cItemType == DEF_ITEMTYPE_USE_SKILL)
            m_bSkillUsingStatus = true;
    }
    else if (m_iPointCommandType == 200) // Normal Hand
    {
        if ((strlen(m_cMCName) == 0) || (strcmp(m_cMCName, m_cPlayerName) == 0) || (m_cMCName[0] == '_'))
        {
            m_stDialogBoxInfo[32].cMode = 0;
            PlaySound('E', 14, 5);
            AddEventList(POINT_COMMAND_HANDLER1, 10);
        }
        else
        {
            m_stDialogBoxInfo[32].cMode = 3;
            PlaySound('E', 14, 5);
            ZeroMemory(m_stDialogBoxInfo[32].cStr, sizeof(m_stDialogBoxInfo[32].cStr));
            strcpy(m_stDialogBoxInfo[32].cStr, m_cMCName);
            bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_REQUEST_JOINPARTY, 0, 1, 0, 0, m_cMCName);
            return;
        }
    }
}

void CGame::StartBGM()
{
    if (m_bSoundFlag == false)
    {
        return;
    }
    char cWavFileName[32];
    ZeroMemory(cWavFileName, sizeof(cWavFileName));
    if ((m_bIsXmas == true) && (m_cWhetherEffectType >= 4)) strcpy(cWavFileName, "music\\Carol.wav");
    else
    {
        if (memcmp(m_cCurLocation, "aresden", 7) == 0) strcpy(cWavFileName, "music\\aresden.wav");
        else if (memcmp(m_cCurLocation, "elvine", 6) == 0) strcpy(cWavFileName, "music\\elvine.wav");
        else if (memcmp(m_cCurLocation, "dglv", 4) == 0) strcpy(cWavFileName, "music\\dungeon.wav");
        else if (memcmp(m_cCurLocation, "middled1", 8) == 0) strcpy(cWavFileName, "music\\dungeon.wav");
        else if (memcmp(m_cCurLocation, "middleland", 10) == 0) strcpy(cWavFileName, "music\\middleland.wav");
        else if (memcmp(m_cCurLocation, "druncncity", 10) == 0) strcpy(cWavFileName, "music\\druncncity.wav");
        else if (memcmp(m_cCurLocation, "inferniaA", 9) == 0) strcpy(cWavFileName, "music\\middleland.wav");
        else if (memcmp(m_cCurLocation, "inferniaB", 9) == 0) strcpy(cWavFileName, "music\\middleland.wav");
        else if (memcmp(m_cCurLocation, "maze", 4) == 0) strcpy(cWavFileName, "music\\dungeon.wav");
        else if (memcmp(m_cCurLocation, "abaddon", 7) == 0) strcpy(cWavFileName, "music\\abaddon.wav");
        else strcpy(cWavFileName, "music\\MainTm.wav");
    }

    int iVolume = (m_cMusicVolume - 100) * 20;
    if (iVolume > 0) iVolume = 0;
    if (iVolume < -10000) iVolume = -10000;
}


void CGame::CommandProcessor(short msX, short msY, short indexX, short indexY, char cLB, char cRB)
{
    char   cDir, absX, absY, cName[12];
    short  sX, sY, sObjectType, tX, tY;
    int iObjectStatus;
    int    iRet;
    uint64_t  dwTime = unixtime();
    uint16_t   wType = 0;
    int i;//, iFOE;
    char   cTxt[120];

    char  pDstName[21];
    short sDstOwnerType;
    int iDstOwnerStatus;

    bool  bGORet;
    if ((m_bIsObserverCommanded == false) && (m_bIsObserverMode == true))
    {
        if ((msX == 0) && (msY == 0) && (m_sViewDstX > 32 * 21) && (m_sViewDstY > 32 * 16)) bSendCommand(MSGID_REQUEST_PANNING, 0, 8, 0, 0, 0, 0);
        else
            if ((msX == 639) && (msY == 0) && (m_sViewDstX < 32 * m_pMapData->m_sMapSizeX - 32 * 21) && (m_sViewDstY > 32 * 16)) bSendCommand(MSGID_REQUEST_PANNING, 0, 2, 0, 0, 0, 0);
            else
                if ((msX == 639) && (msY == 479) && (m_sViewDstX < 32 * m_pMapData->m_sMapSizeX - 32 * 21) && (m_sViewDstY < 32 * m_pMapData->m_sMapSizeY - 32 * 16)) bSendCommand(MSGID_REQUEST_PANNING, 0, 4, 0, 0, 0, 0);
                else
                    if ((msX == 0) && (msY == 479)) bSendCommand(MSGID_REQUEST_PANNING, 0, 6, 0, 0, 0, 0);
                    else
                        if ((msX == 0) && (m_sViewDstX > 32 * 21)) bSendCommand(MSGID_REQUEST_PANNING, 0, 7, 0, 0, 0, 0);
                        else
                            if ((msX == 639) && (m_sViewDstX < 32 * m_pMapData->m_sMapSizeX - 32 * 21)) bSendCommand(MSGID_REQUEST_PANNING, 0, 3, 0, 0, 0, 0);
                            else
                                if ((msY == 0) && (m_sViewDstY > 32 * 16)) bSendCommand(MSGID_REQUEST_PANNING, 0, 1, 0, 0, 0, 0);
                                else
                                    if ((msY == 479) && (m_sViewDstY < 32 * m_pMapData->m_sMapSizeY - 32 * 16)) bSendCommand(MSGID_REQUEST_PANNING, 0, 5, 0, 0, 0, 0);
                                    else return;

        m_bIsObserverCommanded = true;
        m_cArrowPressed = 0;
        return;
    }

    if (m_bIsObserverMode == true) return;

    if (GetAsyncKeyState(VK_MENU) >> 15) // [ALT]
        m_bSuperAttackMode = true;
    else m_bSuperAttackMode = false;

    switch (m_stMCursor.cPrevStatus)
    {
        case DEF_CURSORSTATUS_0:
            if (cLB != 0)
            {
                iRet = _iCheckDlgBoxFocus(msX, msY, 1);
                if (iRet == 1)
                {
                    m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_SELECTED;
                    return;
                }
                else if (iRet == 0)
                {
                    m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_PRESSED;
                    // Added Golden LevelUp
                    if ((msX > 560) && (msX < 620) && (msY > 390) && (msY < 405)
                        && (m_iLU_Point > 0))
                    {
                        if (m_bIsDialogEnabled[12] != true)
                        {
                            EnableDialogBox(12, 0, 0, 0);
                            PlaySound('E', 14, 5);
                        }
                        m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
                        return;
                    }
                }
                else if (iRet == -1)
                {
                    return;
                }
            }
            else if (cRB != 0)
            {
                iRet = _iCheckDlgBoxFocus(msX, msY, 2);
                if (iRet == 1) return;
            }
            break;
        case DEF_CURSORSTATUS_PRESSED:
            if (cLB == 0) // Normal Click
            {
                m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
            }
            break;
        case DEF_CURSORSTATUS_SELECTED:
            if (cLB == 0)
            {
                if (((dwTime - m_stMCursor.dwSelectClickTime) < DEF_DOUBLECLICKTIME) 	// Double Click
                    && (msX == m_stMCursor.sClickX) && (msY == m_stMCursor.sClickY))
                {
                    m_stMCursor.dwSelectClickTime = m_stMCursor.dwSelectClickTime;
                    _bCheckDlgBoxDoubleClick(msX, msY);
                }
                else // Click
                {
                    _bCheckDlgBoxClick(msX, msY);
                    m_stMCursor.sClickX = msX;
                    m_stMCursor.sClickY = msY;
                }
                m_stMCursor.dwSelectClickTime = dwTime;
                m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
                if (m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_ITEM)
                {
                    _bCheckDraggingItemRelease(msX, msY);
                    m_stMCursor.cSelectedObjectType = 0;
                    m_stMCursor.sSelectedObjectID = 0;
                }
                return;
            }
            if (cLB != 0) 			// v2.05 01-11-30
            {
                if ((m_pMapData->bIsTeleportLoc(m_sPlayerX, m_sPlayerY) == true) && (m_cCommandCount == 0)) goto CP_SKIPMOUSEBUTTONSTATUS;

                if ((m_stMCursor.sPrevX != msX) || (m_stMCursor.sPrevY != msY))
                {
                    m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_DRAGGING;
                    m_stMCursor.sPrevX = msX;
                    m_stMCursor.sPrevY = msY;
                    if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
                        ((m_stMCursor.sSelectedObjectID == 30) || (m_stMCursor.sSelectedObjectID == 29)))
                    {
                        m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
                    }
                    if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
                        (m_stMCursor.sSelectedObjectID == 7) && (m_stDialogBoxInfo[7].cMode == 1))
                    {
                        EndInputString();
                        m_stDialogBoxInfo[7].cMode = 20;
                    }
                    // Query Drop Item Amount
                    if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
                        (m_stMCursor.sSelectedObjectID == 17) && (m_stDialogBoxInfo[17].cMode == 1))
                        // Guild Menu
                    {
                        EndInputString();
                        m_stDialogBoxInfo[17].cMode = 20;
                    }
                    return;
                }
                if ((m_cCommand == DEF_OBJECTMOVE) || (m_cCommand == DEF_OBJECTRUN)) goto MOTION_COMMAND_PROCESS;
                return;
            }
            break;
        case DEF_CURSORSTATUS_DRAGGING:
            if (cLB != 0)
            {
                if ((m_pMapData->bIsTeleportLoc(m_sPlayerX, m_sPlayerY) == true) && (m_cCommandCount == 0)) goto CP_SKIPMOUSEBUTTONSTATUS;
                if (m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX)
                {
                    m_stDialogBoxInfo[m_stMCursor.sSelectedObjectID].sX = msX - m_stMCursor.sDistX;
                    m_stDialogBoxInfo[m_stMCursor.sSelectedObjectID].sY = msY - m_stMCursor.sDistY;
                }
                m_stMCursor.sPrevX = msX;
                m_stMCursor.sPrevY = msY;

                if ((m_cCommand == DEF_OBJECTMOVE) || (m_cCommand == DEF_OBJECTRUN)) goto MOTION_COMMAND_PROCESS;
                return;
            }
            if (cLB == 0)
            {
                switch (m_stMCursor.cSelectedObjectType)
                {
                    case DEF_SELECTEDOBJTYPE_DLGBOX:
                        if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
                            (m_stMCursor.sSelectedObjectID == 7) && (m_stDialogBoxInfo[7].cMode == 20))
                        {
                            sX = m_stDialogBoxInfo[7].sX;
                            sY = m_stDialogBoxInfo[7].sY;
                            StartInputString(sX + 75, sY + 140, 21, m_cGuildName);
                            m_stDialogBoxInfo[7].cMode = 1;
                        }

                        if ((m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_DLGBOX) &&
                            (m_stMCursor.sSelectedObjectID == 17) && (m_stDialogBoxInfo[17].cMode == 20))
                        {	// Query Drop Item Amount
                            sX = m_stDialogBoxInfo[17].sX;
                            sY = m_stDialogBoxInfo[17].sY;
                            StartInputString(sX + 40, sY + 57, 11, m_cAmountString);
                            m_stDialogBoxInfo[17].cMode = 1;
                        }

                        if (m_stMCursor.sSelectedObjectID == 9)
                        {
                            if (msX < 320) m_stDialogBoxInfo[9].sX = 0;
                            else m_stDialogBoxInfo[9].sX = 640 - m_stDialogBoxInfo[9].sSizeX;
                            if (msY < 213) m_stDialogBoxInfo[9].sY = 0;
                            else m_stDialogBoxInfo[9].sY = 427 - m_stDialogBoxInfo[9].sSizeY;
                        }

                        m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
                        m_stMCursor.cSelectedObjectType = 0;
                        m_stMCursor.sSelectedObjectID = 0;
                        break;

                    case DEF_SELECTEDOBJTYPE_ITEM:
                        _bCheckDraggingItemRelease(msX, msY);
                        m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
                        m_stMCursor.cSelectedObjectType = 0;
                        m_stMCursor.sSelectedObjectID = 0;
                        break;

                    default:
                        m_stMCursor.cPrevStatus = DEF_CURSORSTATUS_0;
                        m_stMCursor.cSelectedObjectType = 0;
                        m_stMCursor.sSelectedObjectID = 0;
                        break;
                }
                return;
            }
            break;
    }

    CP_SKIPMOUSEBUTTONSTATUS:;
    if (m_bCommandAvailable == false) return;
    if ((dwTime - m_dwCommandTime) < 300)
    {
        ws = nullptr;
        m_bEscPressed = false;
        PlaySound('E', 14, 5);
        if (m_bSoundFlag) m_pESound[38].stop();
        if ((m_bSoundFlag) && (m_bMusicStat == true))
        {
            m_pBGM.stop();
        }
        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
        return;
    }
    if (m_iHP <= 0) return;

    if (m_sDamageMove != 0)
    {
        m_cCommand = DEF_OBJECTDAMAGEMOVE;
        goto MOTION_COMMAND_PROCESS;
    }

    if ((m_pMapData->bIsTeleportLoc(m_sPlayerX, m_sPlayerY) == true) && (m_cCommandCount == 0))
        RequestTeleportAndWaitData();

    // indexX, indexY
    if (cLB != 0) // Mouse Left button
    {
        if (m_bIsGetPointingMode == true)
        {
            if ((m_sMCX != 0) || (m_sMCY != 0))
                PointCommandHandler(m_sMCX, m_sMCY);
            else PointCommandHandler(indexX, indexY);

            m_bCommandAvailable = false;
            m_dwCommandTime = unixtime();
            m_bIsGetPointingMode = false;
            return;
        }

        m_pMapData->bGetOwner(m_sMCX, m_sMCY - 1, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID); // v1.4
        //m_pMapData->m_pData[dX][dY].m_sItemSprite
        if (memcmp(m_cMCName, m_cPlayerName, 10) == 0 && (sObjectType <= 6 || m_pMapData->m_pData[m_sPlayerX - m_pMapData->m_sPivotX][m_sPlayerY - m_pMapData->m_sPivotY].m_sItemSprite != 0))
        {//if (memcmp(m_cMCName, m_cPlayerName, 10) == 0 && ( sObjectType <= 6 || m_pMapData->m_pData[15][15].m_sItemSprite != 0 )) {
         //if (memcmp(m_cMCName, m_cPlayerName, 10) == 0 && sObjectType <= 6){
            if ((m_sPlayerType >= 1) && (m_sPlayerType <= 6)/* && ((m_sPlayerAppr2 & 0xF000) == 0)*/)
            {
                m_cCommand = DEF_OBJECTGETITEM;
                m_sCommX = m_sPlayerX;
                m_sCommY = m_sPlayerY;
            }
        }
        else
        {
            if (memcmp(m_cMCName, m_cPlayerName, 10) == 0) m_sMCY -= 1;
            if ((m_sMCX != 0) && (m_sMCY != 0)) // m_sMCX, m_sMCY
            {
                if (m_bCtrlPressed == true)
                {
                    m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID);
                    if ((iObjectStatus & 0x10) != 0) return;
                    if ((sObjectType == 15) || (sObjectType == 20) || (sObjectType == 24)) return;
                    m_stMCursor.sCursorFrame = 3;
                    absX = abs(m_sPlayerX - m_sMCX);
                    absY = abs(m_sPlayerY - m_sMCY);
                    if ((absX <= 1) && (absY <= 1))
                    {
                        wType = _iGetAttackType();
                        m_cCommand = DEF_OBJECTATTACK;
                        m_sCommX = m_sMCX;
                        m_sCommY = m_sMCY;
                    }
                    else if ((absX <= 2) && (absY <= 2) // strike on Big mobs & gate from a range
                        && ((sObjectType == 66) || (sObjectType == 73) || (sObjectType == 81) || (sObjectType == 91)))
                    {
                        wType = _iGetAttackType();
                        m_cCommand = DEF_OBJECTATTACK;
                        m_sCommX = m_sMCX;
                        m_sCommY = m_sMCY;
                    }
                    else // Pas au corp à corp
                    {
                        switch (_iGetWeaponSkillType())
                        {
                            case 6: // Bow
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                                wType = _iGetAttackType();
                                break;

                            case 5: // OpenHand
                            case 7: // SS
                                if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0)))
                                {
                                    if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                    {
                                        if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
                                        {
                                            m_cCommand = DEF_OBJECTATTACKMOVE;
                                            wType = _iGetAttackType();
                                        }
                                        else
                                        {
                                            m_cCommand = DEF_OBJECTRUN;
                                            GetPlayerTurn();
                                        }
                                        m_sCommX = m_sMCX;
                                        m_sCommY = m_sMCY;
                                    }
                                    else
                                    {
                                        m_cCommand = DEF_OBJECTMOVE;
                                        m_sCommX = m_sMCX;
                                        m_sCommY = m_sMCY;
                                        GetPlayerTurn();
                                    }
                                }
                                else
                                {
                                    if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)
                                        && (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                        m_cCommand = DEF_OBJECTRUN;	// Staminar
                                    else m_cCommand = DEF_OBJECTMOVE;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                    GetPlayerTurn();
                                }
                                break;

                            case 8: // LS
                                if ((absX <= 3) && (absY <= 3) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true)
                                    && (_iGetAttackType() != 30)) // Crit without StormBlade
                                {
                                    wType = _iGetAttackType();
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                }
                                else if ((absX <= 5) && (absY <= 5) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true)
                                    && (_iGetAttackType() == 30))  // Crit with StormBlade
                                {
                                    wType = _iGetAttackType();
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                }
                                else if ((absX <= 3) && (absY <= 3)
                                    && (_iGetAttackType() == 5))  // Normal hit with StormBlade
                                {
                                    wType = _iGetAttackType();
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                }
                                else // Swing
                                {
                                    if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0))
                                        && (_iGetAttackType() != 5)) // no Dash possible with StormBlade
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                        {
                                            if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
                                            {
                                                m_cCommand = DEF_OBJECTATTACKMOVE;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                m_cCommand = DEF_OBJECTRUN;
                                                GetPlayerTurn();
                                            }
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                        }
                                        else
                                        {
                                            m_cCommand = DEF_OBJECTMOVE;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            GetPlayerTurn();
                                        }
                                    }
                                    else
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)
                                            && (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                            m_cCommand = DEF_OBJECTRUN;
                                        else m_cCommand = DEF_OBJECTMOVE;
                                        m_sCommX = m_sMCX;
                                        m_sCommY = m_sMCY;
                                        GetPlayerTurn();
                                    }
                                }
                                break;

                            case 9: // Fencing
                                if ((absX <= 4) && (absY <= 4) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                {
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                    wType = _iGetAttackType();
                                }
                                else
                                {
                                    if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0)))
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                        {
                                            if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
                                            {
                                                m_cCommand = DEF_OBJECTATTACKMOVE;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                m_cCommand = DEF_OBJECTRUN;
                                                GetPlayerTurn();
                                            }
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                        }
                                        else
                                        {
                                            m_cCommand = DEF_OBJECTMOVE;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            GetPlayerTurn();
                                        }
                                    }
                                    else
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                            (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                            m_cCommand = DEF_OBJECTRUN;
                                        else m_cCommand = DEF_OBJECTMOVE;
                                        m_sCommX = m_sMCX;
                                        m_sCommY = m_sMCY;
                                        GetPlayerTurn();
                                    }
                                }
                                break;

                            case 10: // Axe
                                if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                {
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                    wType = _iGetAttackType();
                                }
                                else
                                {
                                    if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0)))
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                        {
                                            if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
                                            {
                                                m_cCommand = DEF_OBJECTATTACKMOVE;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                m_cCommand = DEF_OBJECTRUN;
                                                GetPlayerTurn();
                                            }
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                        }
                                        else
                                        {
                                            m_cCommand = DEF_OBJECTMOVE;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            GetPlayerTurn();
                                        }
                                    }
                                    else
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                            (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                            m_cCommand = DEF_OBJECTRUN;
                                        else m_cCommand = DEF_OBJECTMOVE;
                                        m_sCommX = m_sMCX;
                                        m_sCommY = m_sMCY;
                                        GetPlayerTurn();
                                    }
                                }
                                break;
                            case 14: // Hammer
                                if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                {
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                    wType = _iGetAttackType();
                                }
                                else
                                {
                                    if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0)))
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                        {
                                            if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
                                            {
                                                m_cCommand = DEF_OBJECTATTACKMOVE;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                m_cCommand = DEF_OBJECTRUN;
                                                GetPlayerTurn();
                                            }
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                        }
                                        else
                                        {
                                            m_cCommand = DEF_OBJECTMOVE;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            GetPlayerTurn();
                                        }
                                    }
                                    else
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                            (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                            m_cCommand = DEF_OBJECTRUN;
                                        else m_cCommand = DEF_OBJECTMOVE;
                                        m_sCommX = m_sMCX;
                                        m_sCommY = m_sMCY;
                                        GetPlayerTurn();
                                    }
                                }
                                break;
                            case 21: // Wand
                                if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                {
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                    wType = _iGetAttackType();
                                }
                                else
                                {
                                    if (((absX == 2) && (absY == 2)) || ((absX == 0) && (absY == 2)) || ((absX == 2) && (absY == 0)))
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                        {
                                            if (m_cSkillMastery[_iGetWeaponSkillType()] == 100)
                                            {
                                                m_cCommand = DEF_OBJECTATTACKMOVE;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                m_cCommand = DEF_OBJECTRUN;
                                                GetPlayerTurn();
                                            }
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                        }
                                        else
                                        {
                                            m_cCommand = DEF_OBJECTMOVE;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            GetPlayerTurn();
                                        }
                                    }
                                    else
                                    {
                                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                            (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                            m_cCommand = DEF_OBJECTRUN;
                                        else m_cCommand = DEF_OBJECTMOVE;
                                        m_sCommX = m_sMCX;
                                        m_sCommY = m_sMCY;
                                        GetPlayerTurn();
                                    }
                                }
                                break;
                        }
                    }
                }
                else // CTRL not pressed
                {
                    m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID);
                    if (sObjectType >= 10 || ((sObjectType >= 1) && (sObjectType <= 6)))
                    {
                        switch (sObjectType)
                        {
                            case 15: // ShopKeeper-W°
                                /*switch (cName[0]) {
                                case '1':*/
                                EnableDialogBox(20, 5, 11, 1);
                                tX = msX - 117;
                                tY = msY - 50;
                                if (tX < 0) tX = 0;
                                if ((tX + 235) > 639) tX = 639 - 235;
                                if (tY < 0) tY = 0;
                                if ((tY + 100) > 479) tY = 479 - 100;
                                m_stDialogBoxInfo[20].sX = tX;
                                m_stDialogBoxInfo[20].sY = tY;
                                m_stDialogBoxInfo[20].sV3 = 15;
                                /*	break;
                                }*/
                                break;

                            case 19: // Gandlf
                                /*switch (cName[0]) {
                                case '1':*/
                                EnableDialogBox(20, 0, 16, 0);
                                tX = msX - 117;
                                tY = msY - 50;
                                if (tX < 0) tX = 0;
                                if ((tX + 235) > 639) tX = 639 - 235;
                                if (tY < 0) tY = 0;
                                if ((tY + 100) > 479) tY = 479 - 100;
                                m_stDialogBoxInfo[20].sX = tX;
                                m_stDialogBoxInfo[20].sY = tY;
                                m_stDialogBoxInfo[20].sV3 = 19;
                                /*	break;
                                }*/
                                break;

                            case 20: // Howard
                                /*switch (cName[0]) {
                                case '1':*/
                                EnableDialogBox(20, 0, 14, 0);
                                tX = msX - 117;
                                tY = msY - 50;
                                if (tX < 0) tX = 0;
                                if ((tX + 235) > 639) tX = 639 - 235;
                                if (tY < 0) tY = 0;
                                if ((tY + 100) > 479) tY = 479 - 100;
                                m_stDialogBoxInfo[20].sX = tX;
                                m_stDialogBoxInfo[20].sY = tY;
                                m_stDialogBoxInfo[20].sV3 = 20;
                                m_stDialogBoxInfo[39].sV3 = 20;
                                m_stDialogBoxInfo[39].sV4 = m_wCommObjectID;
                                m_stDialogBoxInfo[39].sV5 = m_sMCX;
                                m_stDialogBoxInfo[39].sV6 = m_sMCY;
                                /*	break;
                                }*/
                                break;

                            case 24: // Tom
                                /*switch (cName[0]) {
                                case '1':*/
                                EnableDialogBox(20, 5, 11, 2);
                                tX = msX - 117;
                                tY = msY - 50;
                                if (tX < 0) tX = 0;
                                if ((tX + 235) > 639) tX = 639 - 235;
                                if (tY < 0) tY = 0;
                                if ((tY + 100) > 479) tY = 479 - 100;
                                m_stDialogBoxInfo[20].sX = tX;
                                m_stDialogBoxInfo[20].sY = tY;
                                m_stDialogBoxInfo[20].sV3 = 24;
                                m_stDialogBoxInfo[39].sV3 = 24;
                                m_stDialogBoxInfo[39].sV4 = m_wCommObjectID;
                                m_stDialogBoxInfo[39].sV5 = m_sMCX;
                                m_stDialogBoxInfo[39].sV6 = m_sMCY;
                                /*	break;
                                }*/
                                break;

                            case 25: // William
                                /*switch (cName[0]) {
                                case '1':*/
                                EnableDialogBox(20, 0, 13, 0);
                                tX = msX - 117;
                                tY = msY - 50;
                                if (tX < 0) tX = 0;
                                if ((tX + 235) > 639) tX = 639 - 235;
                                if (tY < 0) tY = 0;
                                if ((tY + 100) > 479) tY = 479 - 100;
                                m_stDialogBoxInfo[20].sX = tX;
                                m_stDialogBoxInfo[20].sY = tY;
                                m_stDialogBoxInfo[20].sV3 = 25;
                                /*	break;
                                }*/
                                break;

                            case 26: // Kennedy
                                /*switch (cName[0]) {
                                case '1':*/
                                EnableDialogBox(20, 0, 7, 0);
                                tX = msX - 117;
                                tY = msY - 50;
                                if (tX < 0) tX = 0;
                                if ((tX + 235) > 639) tX = 639 - 235;
                                if (tY < 0) tY = 0;
                                if ((tY + 100) > 479) tY = 479 - 100;
                                m_stDialogBoxInfo[20].sX = tX;
                                m_stDialogBoxInfo[20].sY = tY;
                                m_stDialogBoxInfo[20].sV3 = 26;
                                /*	break;
                                }*/
                                break;

                            case 21: // Guard
                                if ((_iGetFOE(iObjectStatus) >= 0) && (!m_bIsCombatMode))
                                {
                                    EnableDialogBox(20, 4, 0, 0);
                                    tX = msX - 117;
                                    tY = msY - 50;
                                    if (tX < 0) tX = 0;
                                    if ((tX + 235) > 639) tX = 639 - 235;
                                    if (tY < 0) tY = 0;
                                    if ((tY + 100) > 479) tY = 479 - 100;
                                    m_stDialogBoxInfo[20].sX = tX;
                                    m_stDialogBoxInfo[20].sY = tY;
                                    m_stDialogBoxInfo[20].sV3 = 21;
                                }
                                break;
                            case 67: // McGaffin
                            case 68: // Perry
                            case 69: // Devlin
                                if (!m_bIsCombatMode)
                                {
                                    EnableDialogBox(20, 4, 0, 0);
                                    tX = msX - 117;
                                    tY = msY - 50;
                                    if (tX < 0) tX = 0;
                                    if ((tX + 235) > 639) tX = 639 - 235;
                                    if (tY < 0) tY = 0;
                                    if ((tY + 100) > 479) tY = 479 - 100;
                                    m_stDialogBoxInfo[20].sX = tX;
                                    m_stDialogBoxInfo[20].sY = tY;
                                    m_stDialogBoxInfo[20].sV3 = sObjectType;
                                }
                                break;

                            case 32: // Unicorn
                                if (!m_bIsCombatMode)
                                {
                                    EnableDialogBox(20, 4, 0, 0);
                                    tX = msX - 117;
                                    tY = msY - 50;
                                    if (tX < 0) tX = 0;
                                    if ((tX + 235) > 639) tX = 639 - 235;
                                    if (tY < 0) tY = 0;
                                    if ((tY + 100) > 479) tY = 479 - 100;
                                    m_stDialogBoxInfo[20].sX = tX;
                                    m_stDialogBoxInfo[20].sY = tY;
                                    m_stDialogBoxInfo[20].sV3 = 32;
                                }
                                break;

                            case 90: // Gail
                                /*switch (cName[0]) {
                                case '1':*/
                                EnableDialogBox(20, 6, 0, 0);
                                tX = msX - 117;
                                tY = msY - 50;
                                if (tX < 0) tX = 0;
                                if ((tX + 235) > 639) tX = 639 - 235;
                                if (tY < 0) tY = 0;
                                if ((tY + 100) > 479) tY = 479 - 100;
                                m_stDialogBoxInfo[20].sX = tX;
                                m_stDialogBoxInfo[20].sY = tY;
                                m_stDialogBoxInfo[20].sV3 = 90;
                                /*break;
                            }*/
                                break;

                            default: // Other mobs
                                if (_iGetFOE(iObjectStatus) >= 0) break;
                                if ((sObjectType >= 1) && (sObjectType <= 6) && (m_bForceAttack == false)) break;
                                absX = abs(m_sPlayerX - m_sMCX);
                                absY = abs(m_sPlayerY - m_sMCY);
                                if ((absX <= 1) && (absY <= 1))
                                {
                                    wType = _iGetAttackType();
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                }
                                else if ((absX <= 2) && (absY <= 2) // strike on Big mobs & gate from a range
                                    && ((sObjectType == 66) || (sObjectType == 73) || (sObjectType == 81) || (sObjectType == 91)))
                                {
                                    wType = _iGetAttackType();
                                    m_cCommand = DEF_OBJECTATTACK;
                                    m_sCommX = m_sMCX;
                                    m_sCommY = m_sMCY;
                                }
                                else // Normal hit from a range.
                                {
                                    switch (_iGetWeaponSkillType())
                                    {
                                        case 6: // Bow
                                            m_cCommand = DEF_OBJECTATTACK;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            wType = _iGetAttackType();
                                            break;

                                        case 5: // Boxe
                                        case 7: // SS
                                            if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0)
                                                && (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                                m_cCommand = DEF_OBJECTRUN;
                                            else m_cCommand = DEF_OBJECTMOVE;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            GetPlayerTurn();
                                            break;

                                        case 8: // LS
                                            if ((absX <= 3) && (absY <= 3) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true)
                                                && (_iGetAttackType() != 30)) // Crit without StormBlade
                                            {
                                                if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                                    m_cCommand = DEF_OBJECTATTACKMOVE;
                                                else m_cCommand = DEF_OBJECTATTACK;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                wType = _iGetAttackType();
                                            }
                                            else if ((absX <= 5) && (absY <= 5) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true)
                                                && (_iGetAttackType() == 30)) // Crit with StormBlade
                                            {
                                                if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                                    m_cCommand = DEF_OBJECTATTACKMOVE;
                                                else m_cCommand = DEF_OBJECTATTACK;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                wType = _iGetAttackType();
                                            }
                                            else if ((absX <= 3) && (absY <= 3)
                                                && (_iGetAttackType() == 5)) // Normal hit with StormBlade
                                            {
                                                m_cCommand = DEF_OBJECTATTACK;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                                    (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                                    m_cCommand = DEF_OBJECTRUN;
                                                else m_cCommand = DEF_OBJECTMOVE;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                GetPlayerTurn();
                                            }
                                            break;

                                        case 9: // Fencing
                                            if ((absX <= 4) && (absY <= 4) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                            {
                                                if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                                    m_cCommand = DEF_OBJECTATTACKMOVE;
                                                else m_cCommand = DEF_OBJECTATTACK;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                                    (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                                    m_cCommand = DEF_OBJECTRUN;
                                                else m_cCommand = DEF_OBJECTMOVE;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                GetPlayerTurn();
                                            }
                                            break;

                                        case 10: //
                                            if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                            {
                                                if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                                    m_cCommand = DEF_OBJECTATTACKMOVE;
                                                else m_cCommand = DEF_OBJECTATTACK;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                                    (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                                    m_cCommand = DEF_OBJECTRUN;
                                                else m_cCommand = DEF_OBJECTMOVE;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                GetPlayerTurn();
                                            }
                                            break;
                                        case 14: //
                                            if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                            {
                                                if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                                    m_cCommand = DEF_OBJECTATTACKMOVE;
                                                else m_cCommand = DEF_OBJECTATTACK;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                                    (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                                    m_cCommand = DEF_OBJECTRUN;
                                                else m_cCommand = DEF_OBJECTMOVE;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                GetPlayerTurn();
                                            }
                                            break;
                                        case 21: //
                                            if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                            {
                                                if ((absX <= 1) && (absY <= 1) && (m_bShiftPressed || m_bRunningMode) && (m_iSP > 0))
                                                    m_cCommand = DEF_OBJECTATTACKMOVE;
                                                else m_cCommand = DEF_OBJECTATTACK;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                wType = _iGetAttackType();
                                            }
                                            else
                                            {
                                                if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                                                    (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                                                    m_cCommand = DEF_OBJECTRUN;
                                                else m_cCommand = DEF_OBJECTMOVE;
                                                m_sCommX = m_sMCX;
                                                m_sCommY = m_sMCY;
                                                GetPlayerTurn();
                                            }
                                            break;
                                    }
                                }
                                break;
                        }
                    }
                    else
                    {
                        if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                            (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                            m_cCommand = DEF_OBJECTRUN;
                        else m_cCommand = DEF_OBJECTMOVE;
                        m_sCommX = m_sMCX;
                        m_sCommY = m_sMCY;
                        GetPlayerTurn();
                    }
                }
            }
            else
            {
                if ((m_bShiftPressed || m_bRunningMode) && (m_iSP > 0) &&
                    (m_sPlayerType >= 1) && (m_sPlayerType <= 6))
                    m_cCommand = DEF_OBJECTRUN;
                else m_cCommand = DEF_OBJECTMOVE;
                m_sCommX = indexX;
                m_sCommY = indexY;
                GetPlayerTurn();
            }
        }
    }
    else if (cRB != 0) // Mouse Right button
    {
        m_cCommand = DEF_OBJECTSTOP;
        if (m_bIsGetPointingMode == true)
        {
            m_bIsGetPointingMode = false;
            AddEventList(COMMAND_PROCESSOR1, 10);
        }
        if (m_bCommandAvailable == false) return;
        if (m_cCommandCount >= 6) return;

        if ((m_sMCX != 0) && (m_sMCY != 0))
        {
            absX = abs(m_sPlayerX - m_sMCX);
            absY = abs(m_sPlayerY - m_sMCY);
            if (absX == 0 && absY == 0) return;

            if (m_bCtrlPressed == true)
            {
                m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID);
                if ((iObjectStatus & 0x10) != 0) return;
                if ((sObjectType == 15) || (sObjectType == 20) || (sObjectType == 24)) return;

                if ((absX <= 1) && (absY <= 1))
                {
                    wType = _iGetAttackType();
                    m_cCommand = DEF_OBJECTATTACK;
                    m_sCommX = m_sMCX;
                    m_sCommY = m_sMCY;
                }
                else if ((absX <= 2) && (absY <= 2) // strike on Big mobs & gate from a range
                    && ((sObjectType == 66) || (sObjectType == 73) || (sObjectType == 81) || (sObjectType == 91)))
                {
                    wType = _iGetAttackType();
                    m_cCommand = DEF_OBJECTATTACK;
                    m_sCommX = m_sMCX;
                    m_sCommY = m_sMCY;
                }
                else
                {
                    switch (_iGetWeaponSkillType())
                    {
                        case 6: // Bow
                            m_cCommand = DEF_OBJECTATTACK;
                            m_sCommX = m_sMCX;
                            m_sCommY = m_sMCY;
                            wType = _iGetAttackType();
                            break;

                        case 5: // Boxe
                        case 7: // SS
                            break;

                        case 8: // LS
                            if ((absX <= 3) && (absY <= 3) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true)
                                && (_iGetAttackType() != 30)) // without StormBlade
                            {
                                wType = _iGetAttackType();
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                            }
                            else if ((absX <= 5) && (absY <= 5) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true)
                                && (_iGetAttackType() == 30)) // with stormBlade crit
                            {
                                wType = _iGetAttackType();
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                            }
                            else if ((absX <= 3) && (absY <= 3)
                                && (_iGetAttackType() == 5)) // with stormBlade no crit
                            {
                                wType = _iGetAttackType();
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                            }
                            break;

                        case 9: // Fencing
                            if ((absX <= 4) && (absY <= 4) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                            {
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                                wType = _iGetAttackType();
                            }
                            break;

                        case 10: //
                            if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                            {
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                                wType = _iGetAttackType();
                            }
                            break;

                        case 14: //
                            if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                            {
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                                wType = _iGetAttackType();
                            }
                            break;
                        case 21: //
                            if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                            {
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                                wType = _iGetAttackType();
                            }
                            break;
                    }
                }
            }
            else // CTRL not pressed
            {
                absX = abs(m_sPlayerX - m_sMCX);
                absY = abs(m_sPlayerY - m_sMCY);
                m_pMapData->bGetOwner(m_sMCX, m_sMCY, cName, &sObjectType, &iObjectStatus, &m_wCommObjectID);
                if (sObjectType >= 10 || ((sObjectType >= 1) && (sObjectType <= 6)))
                {
                    switch (sObjectType)
                    {
                        case 15:
                        case 19:
                        case 20:
                        case 24:
                        case 25:
                        case 26: // npcs
                            break;

                        default: // All "normal mobs"
                            if (_iGetFOE(iObjectStatus) >= 0) break;
                            if ((sObjectType >= 1) && (sObjectType <= 6) && (m_bForceAttack == false)) break;
                            if ((absX <= 1) && (absY <= 1))
                            {
                                wType = _iGetAttackType();
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                            }
                            else if ((absX <= 2) && (absY <= 2) // strike on Big mobs & gate from a range
                                && ((sObjectType == 66) || (sObjectType == 73) || (sObjectType == 81) || (sObjectType == 91)))
                            {
                                wType = _iGetAttackType();
                                m_cCommand = DEF_OBJECTATTACK;
                                m_sCommX = m_sMCX;
                                m_sCommY = m_sMCY;
                            }
                            else //
                            {
                                switch (_iGetWeaponSkillType())
                                {
                                    case 6: // Bow
                                        m_cCommand = DEF_OBJECTATTACK;
                                        m_sCommX = m_sMCX;
                                        m_sCommY = m_sMCY;
                                        wType = _iGetAttackType();
                                        break;

                                    case 5: // Boxe
                                    case 7: // SS
                                        break;

                                    case 8: // LS
                                        if ((absX <= 3) && (absY <= 3) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true)
                                            && (_iGetAttackType() != 30)) // crit without StormBlade
                                        {
                                            wType = _iGetAttackType();
                                            m_cCommand = DEF_OBJECTATTACK;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                        }
                                        else if ((absX <= 5) && (absY <= 5) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true)
                                            && (_iGetAttackType() == 30)) // with stormBlade crit
                                        {
                                            wType = _iGetAttackType();
                                            m_cCommand = DEF_OBJECTATTACK;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                        }
                                        else if ((absX <= 3) && (absY <= 3)
                                            && (_iGetAttackType() == 5)) // with stormBlade no crit
                                        {
                                            wType = _iGetAttackType();
                                            m_cCommand = DEF_OBJECTATTACK;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                        }
                                        break;

                                    case 9: // fencing
                                        if ((absX <= 4) && (absY <= 4) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                        {
                                            m_cCommand = DEF_OBJECTATTACK;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            wType = _iGetAttackType();
                                        }
                                        break;

                                    case 10: //
                                        if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                        {
                                            m_cCommand = DEF_OBJECTATTACK;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            wType = _iGetAttackType();
                                        }
                                        break;
                                    case 14: // hammer
                                        if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                        {
                                            m_cCommand = DEF_OBJECTATTACK;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            wType = _iGetAttackType();
                                        }
                                        break;
                                    case 21: // wand
                                        if ((absX <= 2) && (absY <= 2) && (m_iSuperAttackLeft > 0) && (m_bSuperAttackMode == true))
                                        {
                                            m_cCommand = DEF_OBJECTATTACK;
                                            m_sCommX = m_sMCX;
                                            m_sCommY = m_sMCY;
                                            wType = _iGetAttackType();
                                        }
                                        break;
                                }
                            }
                            break;
                    }
                }
            }
        }
        else
        {
            cDir = m_Misc.cGetNextMoveDir(m_sPlayerX, m_sPlayerY, indexX, indexY);
            if (m_iHP <= 0) return;
            if (cDir == 0) return;
            if (m_cPlayerDir == cDir) return;
            ClearSkillUsingStatus();
            m_cPlayerDir = cDir;
            //if (m_bFullParalyze) return;
            bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTSTOP, m_cPlayerDir, 0, 0, 0, 0);

            m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
                m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
                m_iPlayerStatus, m_cPlayerName,
                m_cCommand, 0, 0, 0, 0,
                10);
            m_bCommandAvailable = false;
            m_dwCommandTime = unixtime();
            return;
        }
    }

    MOTION_COMMAND_PROCESS:;

    if (m_cCommand != DEF_OBJECTSTOP)
    {
        if (m_iHP <= 0) return;
        if (m_cCommandCount == 5) AddEventList(COMMAND_PROCESSOR2, 10, false);
        if (m_bCommandAvailable == false) return;
        if (m_cCommandCount >= 6) return;

        if (m_sPlayerType > 6)
        {
            switch (m_cCommand)
            {
                case DEF_OBJECTRUN:
                case DEF_OBJECTMAGIC:
                case DEF_OBJECTGETITEM:
                    m_cCommand = DEF_OBJECTSTOP;
                    break;
                case DEF_OBJECTDAMAGEMOVE:
                case DEF_OBJECTATTACKMOVE:
                    m_cCommand = DEF_OBJECTMOVE;

            }
        }

        ClearSkillUsingStatus();

        if (m_sDamageMove != 0)
        {
            m_cCommand = DEF_OBJECTDAMAGEMOVE;
            m_sCommX = m_sPlayerX;
            m_sCommY = m_sPlayerY;

            switch (m_sDamageMove)
            {
                case 1: m_sCommY--; break;
                case 2: m_sCommX++; m_sCommY--; break;
                case 3: m_sCommX++; break;
                case 4: m_sCommX++; m_sCommY++; break;
                case 5: m_sCommY++; break;
                case 6: m_sCommX--; m_sCommY++; break;
                case 7: m_sCommX--; break;
                case 8: m_sCommX--; m_sCommY--; break;
            }

            for (i = 1; i < DEF_MAXCHATMSGS; i++)
                if (m_pChatMsgList[i] == 0)
                {
                    ZeroMemory(cTxt, sizeof(cTxt));


#ifdef DEF_EQUILIBRIUM_PROJECT // damages critical a 200+
                    short sV1 = m_sDamageMoveAmount;
                    if (sV1 < 0) sV1 = 256 + sV1;
                    if (sV1 >= 200) strcpy(cTxt, COMMAND_PROCESSOR6); // "Critical!"
                    else			wsprintfA(cTxt, "-%dPts", sV1); //pts
                    int iFontType;
                    if ((sV1 >= 0) && (sV1 < 20))		iFontType = 21;
                    else if ((sV1 >= 20) && (sV1 < 50)) iFontType = 22;
                    else if ((sV1 >= 50) || (sV1 < 0))	iFontType = 23;
#else				
                    if (m_sDamageMoveAmount > 0)
                        wsprintfA(cTxt, "-%dPts", m_sDamageMoveAmount); //pts
                    else strcpy(cTxt, COMMAND_PROCESSOR6); // "Critical!"
                    int iFontType;
                    if ((m_sDamageMoveAmount >= 0) && (m_sDamageMoveAmount < 12))		iFontType = 21;
                    else if ((m_sDamageMoveAmount >= 12) && (m_sDamageMoveAmount < 40)) iFontType = 22;
                    else if ((m_sDamageMoveAmount >= 40) || (m_sDamageMoveAmount < 0))	iFontType = 23;
#endif

                    m_pChatMsgList[i] = new class CMsg(iFontType, cTxt, m_dwCurTime);
                    m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;

                    if (m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i) == false)
                    {
                        delete m_pChatMsgList[i];
                        m_pChatMsgList[i] = 0;
                    }
                    break;
                }
            m_sDamageMove = 0;
        }

        switch (m_cCommand)
        {
            case DEF_OBJECTRUN:
            case DEF_OBJECTMOVE:
            case DEF_OBJECTDAMAGEMOVE: // v1.43

                if (m_bParalyze) return;
                if (m_bHackMoveBlocked) return;
                bGORet = m_pMapData->bGetOwner(m_sCommX, m_sCommY, pDstName, &sDstOwnerType, &iDstOwnerStatus, &m_wCommObjectID); // v1.4

                if ((m_sPlayerX == m_sCommX) && (m_sPlayerY == m_sCommY))
                    m_cCommand = DEF_OBJECTSTOP;
                else if ((abs(m_sPlayerX - m_sCommX) <= 1) && (abs(m_sPlayerY - m_sCommY) <= 1) &&
                    (bGORet == true) && (sDstOwnerType != 0))
                    m_cCommand = DEF_OBJECTSTOP;
                else if ((abs(m_sPlayerX - m_sCommX) <= 2) && (abs(m_sPlayerY - m_sCommY) <= 2) &&
                    (m_pMapData->m_tile[m_sCommX][m_sCommY].m_bIsMoveAllowed == false))
                    m_cCommand = DEF_OBJECTSTOP;
                else
                {
                    if ((m_cCommand == DEF_OBJECTMOVE) && (m_sPlayerType <= 6))
                    {
                        if (m_bRunningMode || m_bShiftPressed) m_cCommand = DEF_OBJECTRUN;
                    }
                    if (m_cCommand == DEF_OBJECTRUN)
                    {
                        if ((m_bRunningMode == false) && (m_bShiftPressed == false)) m_cCommand = DEF_OBJECTMOVE;

#ifdef DEF_EQUILIBRIUM_PROJECT // RunMode + 2" = move 
                        if ((m_bRunningMode == true) && (m_bVK_OEM_7Pressed == true)) m_cCommand = DEF_OBJECTMOVE;
#endif

                        if (m_iSP < 1) m_cCommand = DEF_OBJECTMOVE;
                    }

                    cDir = cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY, true);
                    // Illusion Movement
                /*	if ((m_bIllusionMVT == true) && (m_cCommand != DEF_OBJECTDAMAGEMOVE))
                    {	cDir +=4;
                        if (cDir >8) cDir -=8;
                    }*/
                    // Illusion Movement
                    if ((m_bIllusionMVT == true) && (m_cCommand != DEF_OBJECTDAMAGEMOVE))
                    {
                        cDir = cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY, true, true);
                    }
                    if (cDir != 0)
                    {
                        m_cPlayerDir = cDir;
                        bSendCommand(MSGID_COMMAND_MOTION, m_cCommand, cDir, 0, 0, 0, 0);
                        switch (cDir)
                        {
                            case 1:	m_sPlayerY--; break;
                            case 2:	m_sPlayerY--; m_sPlayerX++;	break;
                            case 3:	m_sPlayerX++; break;
                            case 4:	m_sPlayerX++; m_sPlayerY++;	break;
                            case 5:	m_sPlayerY++; break;
                            case 6:	m_sPlayerX--; m_sPlayerY++;	break;
                            case 7:	m_sPlayerX--; break;
                            case 8:	m_sPlayerX--; m_sPlayerY--;	break;
                        }
                        m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
                            m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor, // v1.4
                            m_iPlayerStatus, m_cPlayerName,
                            m_cCommand, 0, 0, 0);
                        m_bCommandAvailable = false;
                        m_dwCommandTime = unixtime();
                        m_iPrevMoveX = m_sPlayerX;
                        m_iPrevMoveY = m_sPlayerY;
                    }
                }

                if (m_cCommand == DEF_OBJECTDAMAGEMOVE)
                {
                    m_bIsGetPointingMode = false;
                    m_iPointCommandType = -1;
                    m_stMCursor.sCursorFrame = 0;
                    ClearSkillUsingStatus();
                    m_cCommand = DEF_OBJECTSTOP;
                }
                break;

            case DEF_OBJECTATTACK:
                //if (m_bFullParalyze) return;
                cDir = m_Misc.cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY);
                // Illusion movement
                if (m_bIllusionMVT == true)
                {
                    cDir += 4;
                    if (cDir > 8) cDir -= 8;
                }
                if (cDir != 0)
                {
                    if ((wType == 2) || (wType == 25))
                    {
                        if (_bCheckItemByType(DEF_ITEMTYPE_ARROW) == false)
                            wType = 0;
                    }
                    if (wType >= 20)
                    {
                        m_iSuperAttackLeft--;
                        if (m_iSuperAttackLeft < 0) m_iSuperAttackLeft = 0;
                    }
                    m_cPlayerDir = cDir;
                    bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTATTACK, cDir, m_sCommX, m_sCommY, wType, 0, m_wCommObjectID);
                    m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
                        m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
                        m_iPlayerStatus, m_cPlayerName,
                        DEF_OBJECTATTACK,
                        m_sCommX - m_sPlayerX, m_sCommY - m_sPlayerY, wType);
                    m_bCommandAvailable = false;
                    m_dwCommandTime = unixtime();
                }
                m_cCommand = DEF_OBJECTSTOP;
                break;

            case DEF_OBJECTATTACKMOVE:
                if (m_bParalyze) return;
                if (m_bHackMoveBlocked) return;
                bGORet = m_pMapData->bGetOwner(m_sCommX, m_sCommY, pDstName, &sDstOwnerType, &iDstOwnerStatus, &m_wCommObjectID);
                if ((m_sPlayerX == m_sCommX) && (m_sPlayerY == m_sCommY))
                    m_cCommand = DEF_OBJECTSTOP;
                else if ((abs(m_sPlayerX - m_sCommX) <= 1) && (abs(m_sPlayerY - m_sCommY) <= 1) &&
                    (bGORet == true) && (sDstOwnerType != 0))
                    m_cCommand = DEF_OBJECTSTOP;
                else
                {
                    cDir = cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY, true);
                    // Illusion mvt
                /*	if (m_bIllusionMVT == true)
                    {	cDir +=4;
                        if (cDir >8) cDir -=8;
                    }*/
                    if (m_bIllusionMVT == true)
                    {
                        cDir = cGetNextMoveDir(m_sPlayerX, m_sPlayerY, m_sCommX, m_sCommY, true, true);
                    }
                    if (cDir != 0)
                    {
                        m_cPlayerDir = cDir;
                        bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTATTACKMOVE, cDir, m_sCommX, m_sCommY, wType, 0, m_wCommObjectID);
                        switch (cDir)
                        {
                            case 1:	m_sPlayerY--; break;
                            case 2:	m_sPlayerY--; m_sPlayerX++;	break;
                            case 3:	m_sPlayerX++; break;
                            case 4:	m_sPlayerX++; m_sPlayerY++;	break;
                            case 5:	m_sPlayerY++; break;
                            case 6:	m_sPlayerX--; m_sPlayerY++;	break;
                            case 7:	m_sPlayerX--; break;
                            case 8:	m_sPlayerX--; m_sPlayerY--;	break;
                        }

                        m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
                            m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
                            m_iPlayerStatus, m_cPlayerName,
                            m_cCommand, m_sCommX - m_sPlayerX, m_sCommY - m_sPlayerY, wType);
                        m_bCommandAvailable = false;
                        m_dwCommandTime = unixtime();
                        m_iPrevMoveX = m_sPlayerX;
                        m_iPrevMoveY = m_sPlayerY;
                    }
                }
                m_cCommand = DEF_OBJECTSTOP;
                break;

            case DEF_OBJECTGETITEM:
                //if (m_bFullParalyze) return;
                bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTGETITEM, m_cPlayerDir, 0, 0, 0, 0);
                m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
                    m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
                    m_iPlayerStatus, m_cPlayerName,
                    DEF_OBJECTGETITEM, 0, 0, 0);
                m_bCommandAvailable = false;
                m_cCommand = DEF_OBJECTSTOP;
                break;

            case DEF_OBJECTMAGIC:
                //if (m_bFullParalyze) return;
                bSendCommand(MSGID_COMMAND_MOTION, DEF_OBJECTMAGIC, m_cPlayerDir, m_iCastingMagicType, 0, 0, 0);
                m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
                    m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor,
                    m_iPlayerStatus, m_cPlayerName,
                    DEF_OBJECTMAGIC, m_iCastingMagicType, 0, 0);
                m_bCommandAvailable = false;
                m_dwCommandTime = unixtime();
                m_bIsGetPointingMode = true;
                m_cCommand = DEF_OBJECTSTOP;
                _RemoveChatMsgListByObjectID(m_sPlayerObjectID);
                for (i = 1; i < DEF_MAXCHATMSGS; i++)
                    if (m_pChatMsgList[i] == 0)
                    {
                        ZeroMemory(cTxt, sizeof(cTxt));
                        wsprintfA(cTxt, "%s!", m_pMagicCfgList[m_iCastingMagicType]->m_cName);
                        m_pChatMsgList[i] = new class CMsg(41, cTxt, unixtime());
                        m_pChatMsgList[i]->m_iObjectID = m_sPlayerObjectID;
                        m_pMapData->bSetChatMsgOwner(m_sPlayerObjectID, -10, -10, i);
                        return;
                    }
                break;

            default:
                break;
        }
    }
}

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

void CGame::ResponseTeleportList(char * pData)
{
    char * cp;
    int * ip, i;
#ifdef _DEBUG
    AddEventList("Teleport ???", 10);
#endif
    cp = pData + 6;
    ip = (int *)cp;
    m_iTeleportMapCount = *ip;
    cp += 4;
    for (i = 0; i < m_iTeleportMapCount; i++)
    {
        ip = (int *)cp;
        m_stTeleportList[i].iIndex = *ip;
        cp += 4;
        ZeroMemory(m_stTeleportList[i].mapname, sizeof(m_stTeleportList[i].mapname));
        memcpy(m_stTeleportList[i].mapname, cp, 10);
        cp += 10;
        ip = (int *)cp;
        m_stTeleportList[i].iX = *ip;
        cp += 4;
        ip = (int *)cp;
        m_stTeleportList[i].iY = *ip;
        cp += 4;
        ip = (int *)cp;
        m_stTeleportList[i].iCost = *ip;
        cp += 4;
    }
}

void CGame::ResponseChargedTeleport(char * pData)
{
    short * sp;
    char * cp;
    short sRejectReason = 0;
    cp = (char *)pData + DEF_INDEX2_MSGTYPE + 2;
    sp = (short *)cp;
    sRejectReason = *sp;

#ifdef _DEBUG
    AddEventList("charged teleport ?", 10);
#endif

    switch (sRejectReason)
    {
        case 1:
            AddEventList(RESPONSE_CHARGED_TELEPORT1, 10);
            break;
        case 2:
            AddEventList(RESPONSE_CHARGED_TELEPORT2, 10);
            break;
        case 3:
            AddEventList(RESPONSE_CHARGED_TELEPORT3, 10);
            break;
        case 4:
            AddEventList(RESPONSE_CHARGED_TELEPORT4, 10);
            break;
        case 5:
            AddEventList(RESPONSE_CHARGED_TELEPORT5, 10);
            break;
        case 6:
            AddEventList(RESPONSE_CHARGED_TELEPORT6, 10);
            break;
        default:
            AddEventList(RESPONSE_CHARGED_TELEPORT7, 10);
    }
}

void CGame::ShowEventList(uint64_t dwTime)
{
    int i;

    for (i = 0; i < 6; i++)
        if ((dwTime - m_stEventHistory[i].dwTime) < 5000)
        {
            switch (m_stEventHistory[i].cColor)
            {
                case 0:
                    PutString(10, 10 + i * 15, m_stEventHistory[i].cTxt, Color(225, 225, 225), false, 1, true);
                    break;
                case 1:
                    PutString(10, 10 + i * 15, m_stEventHistory[i].cTxt, Color(130, 255, 130), false, 1, true);
                    break;
                case 2:
                    PutString(10, 10 + i * 15, m_stEventHistory[i].cTxt, Color(255, 130, 130), false, 1, true);
                    break;
                case 3:
                    PutString(10, 10 + i * 15, m_stEventHistory[i].cTxt, Color(130, 130, 255), false, 1, true);
                    break;
                case 4:
                    PutString(10, 10 + i * 15, m_stEventHistory[i].cTxt, Color(230, 230, 130), false, 1, true);
                    break;
                case 10:
                    PutString(10, 10 + i * 15, m_stEventHistory[i].cTxt, Color(180, 255, 180), false, 1, true);
                    break;
                case 20:
                    PutString(10, 10 + i * 15, m_stEventHistory[i].cTxt, Color(150, 150, 170), false, 1, true);
                    break;
            }
        }

    for (i = 0; i < 6; i++)
        if ((dwTime - m_stEventHistory2[i].dwTime) < 5000)
        {
            switch (m_stEventHistory2[i].cColor)
            {
                case 0:
                    PutString(10, 322 + i * 15, m_stEventHistory2[i].cTxt, Color(225, 225, 225), false, 1, true);
                    break;
                case 1:
                    PutString(10, 322 + i * 15, m_stEventHistory2[i].cTxt, Color(130, 255, 130), false, 1, true);
                    break;
                case 2:
                    PutString(10, 322 + i * 15, m_stEventHistory2[i].cTxt, Color(255, 130, 130), false, 1, true);
                    break;
                case 3:
                    PutString(10, 322 + i * 15, m_stEventHistory2[i].cTxt, Color(130, 130, 255), false, 1, true);
                    break;
                case 4:
                    PutString(10, 322 + i * 15, m_stEventHistory2[i].cTxt, Color(230, 230, 130), false, 1, true);
                    break;
                case 10:
                    PutString(10, 322 + i * 15, m_stEventHistory2[i].cTxt, Color(180, 255, 180), false, 1, true);
                    break;
                case 20:
                    PutString(10, 322 + i * 15, m_stEventHistory2[i].cTxt, Color(150, 150, 170), false, 1, true);
                    break;
            }
        }
    if (m_bSkillUsingStatus == true)
    {
        PutString(280 - 29, 280 - 52, SHOW_EVENT_LIST1, Color(235, 235, 235), false, 1, true);
    }
}

void CGame::RequestTeleportAndWaitData()
{
    /*if (strcmp(m_cMapName, "aresden") == 0)
    {	if ( ((m_sPlayerX == 188) && (m_sPlayerY == 105))  ||
             ((m_sPlayerX == 187) && (m_sPlayerY == 105))  ||
             ((m_sPlayerX == 187) && (m_sPlayerY == 106))  ||
             ((m_sPlayerX == 186) && (m_sPlayerY == 106))  ||
             ((m_sPlayerX == 186) && (m_sPlayerY == 107))  )
        {	if ( (m_iLevel < 30) || (m_iLevel>80) )
            {	AddEventList(REQUEST_TELEPORT_AND_WAIT_DATA1, 10);
                return;
    }	}	}
    if (strcmp(m_cMapName, "elvine") == 0)
    {	if ( ((m_sPlayerX == 218) && (m_sPlayerY == 109))  ||
             ((m_sPlayerX == 217) && (m_sPlayerY == 109))  ||
             ((m_sPlayerX == 217) && (m_sPlayerY == 110))  ||
             ((m_sPlayerX == 216) && (m_sPlayerY == 110))  ||
             ((m_sPlayerX == 216) && (m_sPlayerY == 111))  )
        {	if ( (m_iLevel < 30) || (m_iLevel>80) )
            {	AddEventList(REQUEST_TELEPORT_AND_WAIT_DATA1, 10);
                return;
    }	}	}*/
    bSendCommand(MSGID_REQUEST_TELEPORT, 0, 0, 0, 0, 0, 0);
    ChangeGameMode(DEF_GAMEMODE_ONWAITINGINITDATA);
}

void CGame::InitDataResponseHandler(char * pData)
{
    int * ip, i;
    short * sp, sX, sY;
    char * cp, cMapFileName[32], cTxt[120], cPreCurLocation[12];
    bool  bIsObserverMode;
    HANDLE hFile;
    uint32_t  dwFileSize;

    ZeroMemory(cPreCurLocation, sizeof(cPreCurLocation));
    m_bParalyze = false;
    //m_bFullParalyze = false;
    m_bHackMoveBlocked = false;
    m_pMapData->Init();

    m_sMonsterID = 0;
    m_dwMonsterEventTime = 0;

    DisableDialogBox(7);
    DisableDialogBox(11);
    DisableDialogBox(13);
    DisableDialogBox(14);
    DisableDialogBox(16);
    DisableDialogBox(22);
    DisableDialogBox(20);
    DisableDialogBox(21);
    DisableDialogBox(23);
    DisableDialogBox(51); // Gail's diag

    m_cCommand = DEF_OBJECTSTOP;
    //m_bCommandAvailable = true;
    m_cCommandCount = 0;
    m_bIsGetPointingMode = false;
    m_iPointCommandType = -1;
    m_iIlusionOwnerH = 0;
    m_cIlusionOwnerType = 0;
    m_bIsTeleportRequested = false;
    m_bIsConfusion = false;
    m_bSkillUsingStatus = false;

    m_bItemUsingStatus = false;

    m_cRestartCount = -1;
    m_dwRestartCountTime = 0;

    for (i = 0; i < DEF_MAXEFFECTS; i++)
    {
        if (m_pEffectList[i] != 0) delete m_pEffectList[i];
        m_pEffectList[i] = 0;
    }

    for (i = 0; i < DEF_MAXWHETHEROBJECTS; i++)
    {
        m_stWhetherObject[i].sX = 0;
        m_stWhetherObject[i].sBX = 0;
        m_stWhetherObject[i].sY = 0;
        m_stWhetherObject[i].cStep = 0;
    }

    for (i = 0; i < DEF_MAXGUILDNAMES; i++)
    {
        m_stGuildName[i].dwRefTime = 0;
        m_stGuildName[i].iGuildRank = -1;
        ZeroMemory(m_stGuildName[i].cCharName, sizeof(m_stGuildName[i].cCharName));
        ZeroMemory(m_stGuildName[i].cGuildName, sizeof(m_stGuildName[i].cGuildName));
    }

    for (i = 0; i < DEF_MAXCHATMSGS; i++)
    {
        if (m_pChatMsgList[i] != 0) delete m_pChatMsgList[i];
        m_pChatMsgList[i] = 0;
    }

    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

    // PlayerObjectID
    sp = (short *)cp;
    m_sPlayerObjectID = *sp;
    cp += 2;

    sp = (short *)cp;
    sX = *sp;
    cp += 2;

    sp = (short *)cp;
    sY = *sp;
    cp += 2;

    sp = (short *)cp;
    m_sPlayerType = *sp;
    cp += 2;

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

    ip = (int *)cp; // v1.4
    m_iPlayerApprColor = *ip;
    cp += 4;

    ip = (int *)cp;
    m_iPlayerStatus = *ip;
    cp += 4;

    if ((m_iPlayerStatus & 0x00200000) == 0x00200000)
    {
        m_bIllusionMVT = true;
    }
    else
    {
        m_bIllusionMVT = false;
    }

    ZeroMemory(m_cMapName, sizeof(m_cMapName));
    ZeroMemory(m_cMapMessage, sizeof(m_cMapMessage));
    memcpy(m_cMapName, cp, 10);
    m_cMapIndex = GetOfficialMapName(m_cMapName, m_cMapMessage);
    m_bIsHeldenianMap = ((m_cMapIndex == 35) || (m_cMapIndex == 36) || (m_cMapIndex == 37));

    if (m_cMapIndex < 0)
    {
        m_stDialogBoxInfo[9].sSizeX = -1;
        m_stDialogBoxInfo[9].sSizeY = -1;
    }
    else
    {
        m_stDialogBoxInfo[9].sSizeX = 128;
        m_stDialogBoxInfo[9].sSizeY = 128;
    }
    cp += 10;

    strcpy(cPreCurLocation, m_cCurLocation);
    ZeroMemory(m_cCurLocation, sizeof(m_cCurLocation));
    memcpy(m_cCurLocation, cp, 10);
    cp += 10;

    G_cSpriteAlphaDegree = *cp;
    cp++;

    m_cWhetherStatus = *cp;
    cp++;
    switch (G_cSpriteAlphaDegree)
    {
        // Will be sent by server if DayTime is 3 (and a snowy weather)
        case 1:	m_bIsXmas = false; break;
        case 2: m_bIsXmas = false; break;
        case 3: // Special night with chrismas bulbs
            if (m_cWhetherStatus > 3) m_bIsXmas = true;
            else m_bIsXmas = false;
            G_cSpriteAlphaDegree = 2;
            break;
    }
    ip = (int *)cp;
    m_iContribution = *ip;
    m_iContributionPrice = 0;
    cp += 4;
    bIsObserverMode = (bool)*cp;
    cp++;
    ip = (int *)cp;
    m_iRating = *ip;
    cp += 4;
    ip = (int *)cp;
    m_iHP = *ip;
    cp += 4;
    m_cDiscount = (char)*cp;
    cp++;

    if (m_cWhetherStatus != 0)
        SetWhetherStatus(true, m_cWhetherStatus);
    else SetWhetherStatus(false, m_cWhetherStatus);

    ZeroMemory(cMapFileName, sizeof(cMapFileName));
    strcat(cMapFileName, "mapdata\\");
    if (memcmp(m_cMapName, "defaultmw", 9) == 0)
    {
        strcat(cMapFileName, "mw\\defaultmw");
    }
    else
    {
        strcat(cMapFileName, m_cMapName);
    }

    strcat(cMapFileName, ".amd");
    m_pMapData->OpenMapDataFile(cMapFileName);

    m_pMapData->m_sPivotX = sX;
    m_pMapData->m_sPivotY = sY;

    m_sPlayerX = sX + 14 + 5;
    m_sPlayerY = sY + 12 + 5;

    m_cPlayerDir = 5;

    if (bIsObserverMode == false)
    {
        m_pMapData->bSetOwner(m_sPlayerObjectID, m_sPlayerX, m_sPlayerY, m_sPlayerType, m_cPlayerDir,
            m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4, m_iPlayerApprColor, // v1.4
            m_iPlayerStatus, m_cPlayerName,
            DEF_OBJECTSTOP, 0, 0, 0);
    }

    m_sViewDstX = m_sViewPointX = (sX + 4 + 5) * 32;
    m_sViewDstY = m_sViewPointY = (sY + 5 + 5) * 32;
    _ReadMapData(sX + 4 + 5, sY + 5 + 5, cp);
    m_bIsRedrawPDBGS = true;
    // ------------------------------------------------------------------------+
    wsprintfA(cTxt, INITDATA_RESPONSE_HANDLER1, m_cMapMessage);
    AddEventList(cTxt, 10);

    m_stDialogBoxInfo[6].sX = 150;
    m_stDialogBoxInfo[6].sY = 130;

    if ((memcmp(m_cCurLocation, "middleland", 10) == 0)
        || (memcmp(m_cCurLocation, "dglv2", 5) == 0)
        || (memcmp(m_cCurLocation, "middled1n", 9) == 0))
        EnableDialogBox(6, 0, 0, 0);

    /*	bool bPrevSafe, bNowSafe;
        if( memcmp( cPreCurLocation, m_cLocation, 3 ) == 0 )
            bPrevSafe = true;
        else bPrevSafe = false;

        if( memcmp( m_cCurLocation, m_cLocation, 3 ) == 0 )
            bNowSafe = true;
        else bNowSafe = false;

        if( memcmp( m_cCurLocation, "2nd", 3 ) == 0 ) bNowSafe = true;
        if( m_iPKCount != 0 ) bNowSafe = false;

        if( bPrevSafe )
        {	if( bNowSafe == false ) SetTopMsg(DEF_MSG_DANGERZONE, 5);
        }else
        {	if( bNowSafe ) SetTopMsg(DEF_MSG_SAFEZONE, 5);
        }*/

        // ------------------------------------------------------------------------+

    ChangeGameMode(DEF_GAMEMODE_ONMAINGAME);
    m_DDraw.back_buffer.clear(sf::Color::Black);

    //v1.41
    if ((m_sPlayerAppr2 & 0xF000) != 0)
        m_bIsCombatMode = true;
    else m_bIsCombatMode = false;

    //v1.42
    if (m_bIsFirstConn == true)
    {
        m_bIsFirstConn = false;
        hFile = CreateFileA("contents\\contents1000.txt", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
        if (hFile == INVALID_HANDLE_VALUE)
            dwFileSize = 0;
        else
        {
            dwFileSize = GetFileSize(hFile, 0);
            CloseHandle(hFile);
        }
        bSendCommand(MSGID_REQUEST_NOTICEMENT, 0, 0, (int)dwFileSize, 0, 0, 0);
    }
    //cp += 2;
}

void CGame::MotionEventHandler(char * pData)
{
    uint16_t * wp, wEventType, wObjectID;
    short * sp, sX, sY, sType, sAppr1, sAppr2, sAppr3, sAppr4, sV1, sV2, sV3, sPrevAppr2;
    int iStatus;
    char * cp, cDir, cName[12];
    int * ip, iApprColor, iLoc;
    char    cTxt[120];
    int i;
    ZeroMemory(cName, sizeof(cName));
    sV1 = sV2 = sV3 = 0;
    wp = (uint16_t *)(pData + DEF_INDEX2_MSGTYPE);
    wEventType = *wp;
    cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
    wp = (uint16_t *)cp;
    wObjectID = *wp;
    cp += 2;
    iLoc = 0;
    if (wObjectID < 30000)
    {
        if (wObjectID < 10000) 	// Player
        {
            sp = (short *)cp;
            sX = *sp;
            cp += 2;
            sp = (short *)cp;
            sY = *sp;
            cp += 2;
            sp = (short *)cp;
            sType = *sp;
            cp += 2;
            cDir = *cp;
            cp++;
            memcpy(cName, cp, 10);
            cp += 10;
            sp = (short *)cp;
            sAppr1 = *sp;
            cp += 2;
            sp = (short *)cp;
            sAppr2 = *sp;
            cp += 2;
            sp = (short *)cp;
            sAppr3 = *sp;
            cp += 2;
            sp = (short *)cp;
            sAppr4 = *sp;
            cp += 2;
            ip = (int *)cp; // v1.4
            iApprColor = *ip;
            cp += 4;

            ip = (int *)cp;
            iStatus = *ip;
            cp += 4;

            iLoc = *cp;
            cp++;
        }
        else 	// Npc or mob
        {
            sp = (short *)cp;
            sX = *sp;
            cp += 2;
            sp = (short *)cp;
            sY = *sp;
            cp += 2;
            sp = (short *)cp;
            sType = *sp;
            cp += 2;
            cDir = *cp;
            cp++;
            memcpy(cName, cp, 5);
            cp += 5;
            sAppr1 = sAppr3 = sAppr4 = 0;
            sp = (short *)cp;
            sAppr2 = *sp;
            cp += 2;
            ip = (int *)cp;
            iStatus = *ip;
            cp += 4;
            iLoc = *cp;
            cp++;
        }
    }
    else
    {
        switch (wEventType)
        {
            case DEF_OBJECTMAGIC:
            case DEF_OBJECTDAMAGEMOVE:
            case DEF_OBJECTDAMAGE:
                cDir = *cp;
                cp++;
                sV1 = (short)*cp; //Damage
                cp++;
                sV2 = (short)*cp; //
                cp++;
                break;

            case DEF_OBJECTDYING:
                cDir = *cp;
                cp++;
                sV1 = (short)*cp; //Damage
                cp++;
                sV2 = (short)*cp; //
                cp++;
                sp = (short *)cp;
                sX = *sp;
                cp += 2;
                sp = (short *)cp;
                sY = *sp;
                cp += 2;
                break;

            case DEF_OBJECTATTACK:
                cDir = *cp;
                cp++;
                sV1 = *cp;
                cp++;
                sV2 = *cp;
                cp++;
                sp = (short *)cp;
                sV3 = *sp;
                cp += 2;
                break;

            default:
                cDir = *cp;
                cp++;
                break;
        }
    }

    if ((wEventType == DEF_OBJECT0ACTION) && (memcmp(cName, m_cPlayerName, 10) == 0))
    {
        m_sPlayerType = sType;
        m_sPlayerAppr1 = sAppr1;
        sPrevAppr2 = m_sPlayerAppr2;
        m_sPlayerAppr2 = sAppr2;
        m_sPlayerAppr3 = sAppr3;
        m_sPlayerAppr4 = sAppr4;
        m_iPlayerApprColor = iApprColor;
        m_iPlayerStatus = iStatus;
        if ((sPrevAppr2 & 0xF000) == 0)
        {
            if ((sAppr2 & 0xF000) != 0)
            {
                AddEventList(MOTION_EVENT_HANDLER1, 10);
                m_bIsCombatMode = true;
            }
        }
        else
        {
            if ((sAppr2 & 0xF000) == 0)
            {
                AddEventList(MOTION_EVENT_HANDLER2, 10);
                m_bIsCombatMode = false;
            }
        }
        if (m_cCommand != DEF_OBJECTRUN) m_pMapData->bSetOwner(wObjectID, sX, sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, (char)wEventType, sV1, sV2, sV3, iLoc);
    }
    else m_pMapData->bSetOwner(wObjectID, sX, sY, sType, cDir, sAppr1, sAppr2, sAppr3, sAppr4, iApprColor, iStatus, cName, (char)wEventType, sV1, sV2, sV3, iLoc);

    switch (wEventType)
    {
        case DEF_OBJECTMAGIC: // Casting
            _RemoveChatMsgListByObjectID(wObjectID - 30000);

            for (i = 1; i < DEF_MAXCHATMSGS; i++)
                if (m_pChatMsgList[i] == 0)
                {
                    ZeroMemory(cTxt, sizeof(cTxt));
                    wsprintfA(cTxt, "%s!", m_pMagicCfgList[sV1]->m_cName);
                    m_pChatMsgList[i] = new class CMsg(41, cTxt, m_dwCurTime);
                    m_pChatMsgList[i]->m_iObjectID = wObjectID - 30000;
                    if (m_pMapData->bSetChatMsgOwner(wObjectID - 30000, -10, -10, i) == false)
                    {
                        delete m_pChatMsgList[i];
                        m_pChatMsgList[i] = 0;
                    }
                    return;
                }
            break;

        case DEF_OBJECTDYING:
            _RemoveChatMsgListByObjectID(wObjectID - 30000);
            for (i = 1; i < DEF_MAXCHATMSGS; i++)
                if (m_pChatMsgList[i] == 0)
                {
                    ZeroMemory(cTxt, sizeof(cTxt));

#ifdef DEF_EQUILIBRIUM_PROJECT // damage Criticals a 200+

                    if (sV1 < 0) sV1 = 256 + sV1;
                    if (sV1 >= 200)	strcpy(cTxt, COMMAND_PROCESSOR6); // "Critical!"
                    else 			wsprintfA(cTxt, "-%dPts!", sV1); //pts			
                    int iFontType;
                    if ((sV1 >= 0) && (sV1 < 20))		iFontType = 21;
                    else if ((sV1 >= 20) && (sV1 < 50)) iFontType = 22;
                    else if (sV1 >= 50)	iFontType = 23;
#else
                    if (sV1 > 0)
                        wsprintfA(cTxt, "-%dPts!", sV1); //pts
                    else strcpy(cTxt, COMMAND_PROCESSOR6); // "Critical!"
                    int iFontType;
                    if ((sV1 >= 0) && (sV1 < 12))		iFontType = 21;
                    else if ((sV1 >= 12) && (sV1 < 40)) iFontType = 22;
                    else if ((sV1 >= 40) || (sV1 < 0))	iFontType = 23;
#endif
                    m_pChatMsgList[i] = new class CMsg(iFontType, cTxt, m_dwCurTime);
                    m_pChatMsgList[i]->m_iObjectID = wObjectID - 30000;
                    if (m_pMapData->bSetChatMsgOwner(wObjectID - 30000, -10, -10, i) == false)
                    {
                        delete m_pChatMsgList[i];
                        m_pChatMsgList[i] = 0;
                    }
                    return;
                }
            break;

        case DEF_OBJECTDAMAGEMOVE:
        case DEF_OBJECTDAMAGE:
            if (memcmp(cName, m_cPlayerName, 10) == 0)
            {
                m_bIsGetPointingMode = false;
                m_iPointCommandType = -1;
                m_stMCursor.sCursorFrame = 0;
                ClearSkillUsingStatus();
            }
            _RemoveChatMsgListByObjectID(wObjectID - 30000);

            for (i = 1; i < DEF_MAXCHATMSGS; i++)
                if (m_pChatMsgList[i] == 0)
                {
                    ZeroMemory(cTxt, sizeof(cTxt));

#ifdef DEF_EQUILIBRIUM_PROJECT // damages critical a 200+
                    if (sV1 != 0)
                    {
                        if (sV1 < 0) sV1 = 256 + sV1;

                        if (sV1 >= 200)	strcpy(cTxt, COMMAND_PROCESSOR6); // "Critical!"
                        else 			wsprintfA(cTxt, "-%dPts", sV1); //pts
                        int iFontType;
                        if ((sV1 >= 0) && (sV1 < 20))		iFontType = 21;
                        else if ((sV1 >= 20) && (sV1 < 50)) iFontType = 22;
                        else if (sV1 >= 50)	iFontType = 23;

                        m_pChatMsgList[i] = new class CMsg(iFontType, cTxt, m_dwCurTime);
                    }
                    else
                    {
                        strcpy(cTxt, " * Failed! *");
                        m_pChatMsgList[i] = new class CMsg(22, cTxt, m_dwCurTime);
                        PlaySound('C', 17, 0);
                    }

#else
                    if (sV1 != 0)
                    {
                        if (sV1 > 0)
                            wsprintfA(cTxt, "-%dPts", sV1); //pts
                        else strcpy(cTxt, COMMAND_PROCESSOR6); // "Critical!"
                        int iFontType;
                        if ((sV1 >= 0) && (sV1 < 12))		iFontType = 21;
                        else if ((sV1 >= 12) && (sV1 < 40)) iFontType = 22;
                        else if ((sV1 >= 40) || (sV1 < 0))	iFontType = 23;

                        m_pChatMsgList[i] = new class CMsg(iFontType, cTxt, m_dwCurTime);
                    }
                    else
                    {
                        strcpy(cTxt, " * Failed! *");
                        m_pChatMsgList[i] = new class CMsg(22, cTxt, m_dwCurTime);
                        PlaySound('C', 17, 0);
                    }
#endif
                    m_pChatMsgList[i]->m_iObjectID = wObjectID - 30000;
                    if (m_pMapData->bSetChatMsgOwner(wObjectID - 30000, -10, -10, i) == false)
                    {
                        delete m_pChatMsgList[i];
                        m_pChatMsgList[i] = 0;
                    }
                    return;
                }
            break;
    }
}

void CGame::GrandMagicResult(char * pMapName, int iV1, int iV2, int iV3, int iV4, int iHP1, int iHP2, int iHP3, int iHP4)
{
    int i, iTxtIdx = 0;
    char cTemp[120];

    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        if (m_pMsgTextList[i] != 0)
            delete m_pMsgTextList[i];
        m_pMsgTextList[i] = 0;
    }

    for (i = 0; i < 92; i++)
        if (m_pGameMsgList[i] == 0) return;

    if (strcmp(pMapName, "aresden") == 0)
    {
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[2]->m_pMsg, 0);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[3]->m_pMsg, 0);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, " ", 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d", m_pGameMsgList[4]->m_pMsg, iV1);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d", m_pGameMsgList[5]->m_pMsg, iV2);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d", m_pGameMsgList[6]->m_pMsg, iV3);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d", m_pGameMsgList[58]->m_pMsg, iV4);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, " ", 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d %d %d %d", NOTIFY_MSG_STRUCTURE_HP, iHP1, iHP2, iHP3, iHP4);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, " ", 0);

        if (iV2 == 0)
        {
            if ((m_bCitizen == true) && (m_bAresden == false))
            {
                PlaySound('E', 25, 0, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[59]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[60]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[61]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[62]->m_pMsg, 0);
                for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
            }
            else if ((m_bCitizen == true) && (m_bAresden == true))
            {
                PlaySound('E', 25, 0, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[69]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[70]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[71]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[72]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[73]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[74]->m_pMsg, 0);
                for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
            }
            else PlaySound('E', 25, 0, 0);
        }
        else
        {
            if (iV1 != 0)
            {
                if ((m_bCitizen == true) && (m_bAresden == false))
                {
                    PlaySound('E', 23, 0, 0);
                    PlaySound('C', 21, 0, 0);
                    PlaySound('C', 22, 0, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[63]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[64]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[65]->m_pMsg, 0);
                    for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
                }
                else if ((m_bCitizen == true) && (m_bAresden == true))
                {
                    PlaySound('E', 24, 0, 0);
                    PlaySound('C', 12, 0, 0);
                    PlaySound('C', 13, 0, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[75]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[76]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[77]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[78]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[79]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[80]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[81]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[82]->m_pMsg, 0);
                    for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
                }
                else PlaySound('E', 25, 0, 0);
            }
            else
            {
                if ((m_bCitizen == true) && (m_bAresden == false))
                {
                    PlaySound('E', 23, 0, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[66]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[67]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[68]->m_pMsg, 0);
                    for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
                }
                else if ((m_bCitizen == true) && (m_bAresden == true))
                {
                    PlaySound('E', 24, 0, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[83]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[84]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[85]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[86]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[87]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[88]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[89]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[90]->m_pMsg, 0);
                    for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
                }
                else PlaySound('E', 25, 0, 0);
            }
        }
    }
    else if (strcmp(pMapName, "elvine") == 0)
    {
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[7]->m_pMsg, 0);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[8]->m_pMsg, 0);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, " ", 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d", m_pGameMsgList[4]->m_pMsg, iV1);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d", m_pGameMsgList[5]->m_pMsg, iV2);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d", m_pGameMsgList[6]->m_pMsg, iV3);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d", m_pGameMsgList[58]->m_pMsg, iV4);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, " ", 0);

        ZeroMemory(cTemp, sizeof(cTemp));
        wsprintfA(cTemp, "%s %d %d %d %d", NOTIFY_MSG_STRUCTURE_HP, iHP1, iHP2, iHP3, iHP4);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, cTemp, 0);
        m_pMsgTextList[iTxtIdx++] = new class CMsg(0, " ", 0);

        if (iV2 == 0)
        {
            if ((m_bCitizen == true) && (m_bAresden == true))
            {
                PlaySound('E', 25, 0, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[59]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[60]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[61]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[62]->m_pMsg, 0);
                for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
            }
            else if ((m_bCitizen == true) && (m_bAresden == false))
            {
                PlaySound('E', 25, 0, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[69]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[70]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[71]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[72]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[73]->m_pMsg, 0);
                m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[74]->m_pMsg, 0);
                for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
            }
            else PlaySound('E', 25, 0, 0);
        }
        else
        {
            if (iV1 != 0)
            {
                if ((m_bCitizen == true) && (m_bAresden == true))
                {
                    PlaySound('E', 23, 0, 0);
                    PlaySound('C', 21, 0, 0);
                    PlaySound('C', 22, 0, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[63]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[64]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[65]->m_pMsg, 0);
                    for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
                }
                else if ((m_bCitizen == true) && (m_bAresden == false))
                {
                    PlaySound('E', 24, 0, 0);
                    PlaySound('C', 12, 0, 0);
                    PlaySound('C', 13, 0, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[75]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[76]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[77]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[78]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[79]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[80]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[81]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[82]->m_pMsg, 0);
                    for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
                }
                else PlaySound('E', 25, 0, 0);
            }
            else
            {
                if ((m_bCitizen == true) && (m_bAresden == true))
                {
                    PlaySound('E', 23, 0, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[66]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[67]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[68]->m_pMsg, 0);
                    for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
                }
                else if ((m_bCitizen == true) && (m_bAresden == false))
                {
                    PlaySound('E', 24, 0, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[83]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[84]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[85]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[86]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[87]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[88]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[89]->m_pMsg, 0);
                    m_pMsgTextList[iTxtIdx++] = new class CMsg(0, m_pGameMsgList[90]->m_pMsg, 0);
                    for (i = iTxtIdx; i < 18; i++) m_pMsgTextList[i] = new class CMsg(0, " ", 0);
                }
                else PlaySound('E', 25, 0, 0);
            }
        }
    }

    EnableDialogBox(18, 0, 0, 0);
}

// num : 1 - F2, 2 - F3
void CGame::UseShortCut(int num)
{
    int index;
    if (num < 3) index = num + 1;
    else index = num + 7;
    if (m_cGameMode != DEF_GAMEMODE_ONMAINGAME) return;
    if (m_bCtrlPressed == true)
    {
        if (m_sRecentShortCut == -1)
        {
            AddEventList(MSG_SHORTCUT1, 10);
            wsprintfA(G_cTxt, MSG_SHORTCUT2, index);// [F%d]
            AddEventList(G_cTxt, 10);
            wsprintfA(G_cTxt, MSG_SHORTCUT3, index);// [Control]-[F%d]
            AddEventList(G_cTxt, 10);
        }
        else
        {
            m_sShortCut[num] = m_sRecentShortCut;
            if (m_sShortCut[num] < 100)
            {
                if (m_pItemList[m_sShortCut[num]] == 0)
                {
                    m_sShortCut[num] = -1;
                    m_sRecentShortCut = -1;
                    return;
                }
                char cStr1[64] = {}, cStr2[64] = {}, cStr3[64] = {};
                ZeroMemory(cStr1, sizeof(cStr1));
                ZeroMemory(cStr2, sizeof(cStr2));
                ZeroMemory(cStr3, sizeof(cStr3));

                GetItemName(m_pItemList[m_sShortCut[num]], cStr1, cStr2, cStr3);
                wsprintfA(G_cTxt, MSG_SHORTCUT4, cStr1, cStr2, cStr3, index);// (%s %s %s) [F%d]
                AddEventList(G_cTxt, 10);
            }
            else if (m_sShortCut[num] >= 100)
            {
                if (m_pMagicCfgList[m_sShortCut[num] - 100] == 0)
                {
                    m_sShortCut[num] = -1;
                    m_sRecentShortCut = -1;
                    return;
                }
                wsprintfA(G_cTxt, MSG_SHORTCUT5, m_pMagicCfgList[m_sShortCut[num] - 100]->m_cName, index);// %s) [F%d]
                AddEventList(G_cTxt, 10);
            }
        }
    }
    else
    {
        if (m_sShortCut[num] == -1)
        {
            AddEventList(MSG_SHORTCUT1, 10);
            wsprintfA(G_cTxt, MSG_SHORTCUT2, index);// [F%d]
            AddEventList(G_cTxt, 10);
            wsprintfA(G_cTxt, MSG_SHORTCUT3, index);// [Control]-[F%d]
            AddEventList(G_cTxt, 10);
        }
        else if (m_sShortCut[num] < 100)
        {
            ItemEquipHandler((char)m_sShortCut[num]);
        }
        else if (m_sShortCut[num] >= 100) UseMagic(m_sShortCut[num] - 100);
    }
}

int CGame::iGetManaCost(int iMagicNo)
{
    int i, iManaSave, iManaCost, iTemp = 0;
    iManaSave = 0;
    if (iMagicNo < 0 || iMagicNo >= 100) return 1;
    for (i = 0; i < DEF_MAXITEMS; i++)
    {
        if (m_pItemList[i] == 0) continue;
        if (m_bIsItemEquipped[i] == true)
        {
            if (strcmp(m_pItemList[i]->m_cName, "MagicWand(MS10)") == 0)		iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "MagicWand(MS20)") == 0)		iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "MagicWand(MS30-LLF)") == 0) iManaSave += 30;
            else if (strcmp(m_pItemList[i]->m_cName, "WizMagicWand(MS10)") == 0)	iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "WizMagicWand(MS20)") == 0)	iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "MagicNecklace(MS10)") == 0) iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "DarkMageMagicStaff") == 0)	iManaSave += 25;
            else if (strcmp(m_pItemList[i]->m_cName, "DarkMageMagicStaffW") == 0) iManaSave += 25;
            else if (strcmp(m_pItemList[i]->m_cName, "DarkMageMagicWand") == 0)	iManaSave += 28;
            else if (strcmp(m_pItemList[i]->m_cName, "NecklaceOfLiche") == 0)   	iManaSave += 15;
            else if (strcmp(m_pItemList[i]->m_cName, "DarkMageTempleWand") == 0)	iManaSave += 28;
            else if (strcmp(m_pItemList[i]->m_cName, "BerserkWand(MS.20)") == 0)	iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "BerserkWand(MS.10)") == 0)	iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "KlonessWand(MS.20)") == 0)	iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "KlonessWand(MS.10)") == 0)	iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "ResurWand(MS.20)") == 0)	iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "ResurWand(MS.10)") == 0)	iManaSave += 10;

            else if (strcmp(m_pItemList[i]->m_cName, "MagicNecklace(MS12)") == 0)	iManaSave += 12;
            else if (strcmp(m_pItemList[i]->m_cName, "MagicNecklace(MS14)") == 0)	iManaSave += 14;
            else if (strcmp(m_pItemList[i]->m_cName, "MagicNecklace(MS16)") == 0)	iManaSave += 16;
            else if (strcmp(m_pItemList[i]->m_cName, "MagicNecklace(MS18)") == 0)	iManaSave += 18;

#ifdef DEF_EQUILIBRIUM_PROJECT	// Equilibrium Project Items
            else if (strcmp(m_pItemList[i]->m_cName, "WandMS10") == 0)			iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "WandMS20") == 0)			iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "WandMS30") == 0)			iManaSave += 30;
            else if (strcmp(m_pItemList[i]->m_cName, "WizardMS10") == 0)			iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "WizardMS20") == 0)			iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "MasterMS25") == 0)			iManaSave += 25;
            else if (strcmp(m_pItemList[i]->m_cName, "WarlordMS28") == 0)			iManaSave += 28;
            else if (strcmp(m_pItemList[i]->m_cName, "KlonessMS20") == 0)			iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "KlonessMS28") == 0)			iManaSave += 28;
            else if (strcmp(m_pItemList[i]->m_cName, "ResurWandMS20") == 0)		iManaSave += 20;
            else if (strcmp(m_pItemList[i]->m_cName, "WandMShield") == 0)			iManaSave += 15;
            else if (strcmp(m_pItemList[i]->m_cName, "LichMS10") == 0)			iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "BloodWandMS40") == 0)		iManaSave += 10;
            else if (strcmp(m_pItemList[i]->m_cName, "NeckMS10") == 0)
            {
                iManaSave += 10;
                // Merien Upgraded items
                iTemp = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
                iManaSave += iTemp;
            }
            else if (strcmp(m_pItemList[i]->m_cName, "NeckMS15") == 0)
            {
                iManaSave += 15;
                // Merien Upgraded items			
                iTemp = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
                iManaSave += iTemp;
            }
            else if (strcmp(m_pItemList[i]->m_cName, "LicheArmorW") == 0)
            {
                iManaSave += 10;
                // Merien Upgraded items			
                iTemp = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
                iManaSave += iTemp;
            }
            else if (strcmp(m_pItemList[i]->m_cName, "LicheArmorM") == 0)
            {
                iManaSave += 10;
                // Merien Upgraded items	
                iTemp = (m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
                iManaSave += iTemp;
            }
#endif

        }
    }
    if (iManaSave > 80) iManaSave = 80;
    iManaCost = m_pMagicCfgList[iMagicNo]->m_sValue1;
    if (m_bIsSafeAttackMode) iManaCost += (iManaCost / 2) - (iManaCost / 10);
    if (iManaSave > 0)
    {
        double dV1 = (double)iManaSave;
        double dV2 = (double)(dV1 / 100.0f);
        double dV3 = (double)iManaCost;
        dV1 = dV2 * dV3;
        dV2 = dV3 - dV1;
        iManaCost = (int)dV2;
    }
    if (iManaCost < 1) iManaCost = 1;
    return iManaCost;
}

void CGame::UseMagic(int iMagicNo)
{
    if (iMagicNo < 0 || iMagicNo >= 100) return;
    if ((m_cMagicMastery[iMagicNo] == 0) || (m_pMagicCfgList[iMagicNo] == 0)) return;

    // Casting
    if (m_iHP <= 0) return;
    if (m_bIsGetPointingMode == true) return;
    if (iGetManaCost(iMagicNo) > m_iMP) return;
    if (_bIsItemOnHand() == true)
    {
        AddEventList(DLGBOX_CLICK_MAGIC1, 10);
        return;
    }
    if (m_bSkillUsingStatus == true)
    {
        AddEventList(DLGBOX_CLICK_MAGIC2, 10);
        return;
    }
    if ((m_sPlayerAppr2 & 0xF000) == 0) bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, 0, 0, 0, 0, 0);
    m_cCommand = DEF_OBJECTMAGIC;
    m_iCastingMagicType = iMagicNo;
    m_sMagicShortCut = iMagicNo;
    m_sRecentShortCut = iMagicNo + 100;
    m_iPointCommandType = iMagicNo + 100;
    //m_bIsGetPointingMode = true;
    DisableDialogBox(3);
}


void CGame::ReleaseEquipHandler(char cEquipPos)
{
    char cStr1[64], cStr2[64], cStr3[64];
    //DebugLog("Debug: ReleaseEquipHandler: ...........");

    if (m_sItemEquipmentStatus[cEquipPos] < 0) return;
    // Remove Angelic Stats
    if ((cEquipPos >= 11)
        && (m_pItemList[m_sItemEquipmentStatus[cEquipPos]]->m_cItemType == 1))
    {
        char cItemID = m_sItemEquipmentStatus[cEquipPos];
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

    GetItemName(m_pItemList[m_sItemEquipmentStatus[cEquipPos]], cStr1, cStr2, cStr3);
    wsprintfA(G_cTxt, ITEM_EQUIPMENT_RELEASED, cStr1);
    AddEventList(G_cTxt, 10);

    /*	wsprintfA(G_cTxt,"Debug: ReleaseEquipHandler: %s", cStr1);
        DebugLog(G_cTxt);*/

    m_bIsItemEquipped[m_sItemEquipmentStatus[cEquipPos]] = false;
    m_sItemEquipmentStatus[cEquipPos] = -1;
}

void CGame::ItemEquipHandler(char cItemID)
{
    if (bCheckItemOperationEnabled(cItemID) == false) return;
    if (m_bIsItemEquipped[cItemID] == true) return;
    if (m_pItemList[cItemID]->m_cEquipPos == DEF_EQUIPPOS_NONE)
    {
        AddEventList(BITEMDROP_CHARACTER3, 10);//"The item is not available."
        return;
    }
    if (m_pItemList[cItemID]->m_wCurLifeSpan == 0)
    {
        AddEventList(BITEMDROP_CHARACTER1, 10); //"The item is exhausted. Fix it to use it."
        return;
    }
    if (m_pItemList[cItemID]->m_wWeight / 100 > m_iStr + m_iAngelicStr)
    {
        AddEventList(BITEMDROP_CHARACTER2, 10);
        return;
    }
    if (((m_pItemList[cItemID]->m_dwAttribute & 0x00000001) == 0) && (m_pItemList[cItemID]->m_sLevelLimit > m_iLevel))
    {
        AddEventList(BITEMDROP_CHARACTER4, 10);
        return;
    }
    if (m_bSkillUsingStatus == true)
    {
        AddEventList(BITEMDROP_CHARACTER5, 10);
        return;
    }
    if (m_pItemList[cItemID]->m_cGenderLimit != 0)
    {
        switch (m_sPlayerType)
        {
            case 1:
            case 2:
            case 3:
                if (m_pItemList[cItemID]->m_cGenderLimit != 1)
                {
                    AddEventList(BITEMDROP_CHARACTER6, 10);
                    return;
                }
                break;
            case 4:
            case 5:
            case 6:
                if (m_pItemList[cItemID]->m_cGenderLimit != 2)
                {
                    AddEventList(BITEMDROP_CHARACTER7, 10);
                    return;
                }
                break;
        }
    }

    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_EQUIPITEM, 0, cItemID, 0, 0, 0);
    m_sRecentShortCut = cItemID;

    ReleaseEquipHandler(m_pItemList[cItemID]->m_cEquipPos);
    switch (m_pItemList[cItemID]->m_cEquipPos)
    {
        case DEF_EQUIPPOS_HEAD:
        case DEF_EQUIPPOS_BODY:
        case DEF_EQUIPPOS_ARMS:
        case DEF_EQUIPPOS_PANTS:
        case DEF_EQUIPPOS_BOOTS:
        case DEF_EQUIPPOS_BACK:
            ReleaseEquipHandler(DEF_EQUIPPOS_FULLBODY);
            break;
        case DEF_EQUIPPOS_FULLBODY:
            ReleaseEquipHandler(DEF_EQUIPPOS_HEAD);
            ReleaseEquipHandler(DEF_EQUIPPOS_BODY);
            ReleaseEquipHandler(DEF_EQUIPPOS_ARMS);
            ReleaseEquipHandler(DEF_EQUIPPOS_PANTS);
            ReleaseEquipHandler(DEF_EQUIPPOS_BOOTS);
            ReleaseEquipHandler(DEF_EQUIPPOS_BACK);
            break;
        case DEF_EQUIPPOS_LHAND:
        case DEF_EQUIPPOS_RHAND:
            ReleaseEquipHandler(DEF_EQUIPPOS_TWOHAND);
            break;
        case DEF_EQUIPPOS_TWOHAND:
            ReleaseEquipHandler(DEF_EQUIPPOS_RHAND);
            ReleaseEquipHandler(DEF_EQUIPPOS_LHAND);
            break;
    }

    m_sItemEquipmentStatus[m_pItemList[cItemID]->m_cEquipPos] = cItemID;
    m_bIsItemEquipped[cItemID] = true;

    /*	wsprintfA(G_cTxt,"Debug Equiped Item: %s", m_pItemList[cItemID]->m_cName);
        DebugLog(G_cTxt);*/



        // Add Angelic Stats
    if ((m_pItemList[cItemID]->m_cItemType == 1)
        && (m_pItemList[cItemID]->m_cEquipPos >= 11))
    {
        int iAngelValue = 0;
        if (memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(STR)", 19) == 0)
        {
            iAngelValue = (m_pItemList[cItemID]->m_dwAttribute & 0xF0000000) >> 28;
            m_iAngelicStr = iAngelValue;
        }
        else if (memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(DEX)", 19) == 0)
        {
            iAngelValue = (m_pItemList[cItemID]->m_dwAttribute & 0xF0000000) >> 28;
            m_iAngelicDex = iAngelValue;
        }
        else if (memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(INT)", 19) == 0)
        {
            iAngelValue = (m_pItemList[cItemID]->m_dwAttribute & 0xF0000000) >> 28;
            m_iAngelicInt = iAngelValue;
        }
        else if (memcmp(m_pItemList[cItemID]->m_cName, "AngelicPandent(MAG)", 19) == 0)
        {
            iAngelValue = (m_pItemList[cItemID]->m_dwAttribute & 0xF0000000) >> 28;
            m_iAngelicMag = iAngelValue;
        }
    }

    char cStr1[64], cStr2[64], cStr3[64];
    GetItemName(m_pItemList[cItemID], cStr1, cStr2, cStr3);
    wsprintfA(G_cTxt, BITEMDROP_CHARACTER9, cStr1);
    AddEventList(G_cTxt, 10);
    PlaySound('E', 28, 0);
}

void CGame::CheckActiveAura(short sX, short sY, uint64_t dwTime, short sOwnerType)
{	// Used at the beginning of character drawing
    // DefenseShield
    if ((_tmp_iStatus & 0x02000000) != 0)
        //m_pEffectSpr[80]->PutTransSprite(sX+75, sY+107, _tmp_iEffectFrame%17, dwTime);
        m_pEffectSpr[80]->PutTransSprite50(sX + 75, sY + 107, _tmp_iEffectFrame % 17, dwTime);

    // Protection From Magic
    if ((_tmp_iStatus & 0x04000000) != 0)
        //m_pEffectSpr[79]->PutTransSprite(sX+101, sY+135, _tmp_iEffectFrame%15, dwTime);
        m_pEffectSpr[79]->PutTransSprite70(sX + 101, sY + 135, _tmp_iEffectFrame % 15, dwTime);

    // Protection From Arrow
    if ((_tmp_iStatus & 0x08000000) != 0)
        //m_pEffectSpr[72]->PutTransSprite(sX, sY+35, _tmp_iEffectFrame%30, dwTime);
        m_pEffectSpr[72]->PutTransSprite70(sX, sY + 35, _tmp_iEffectFrame % 30, dwTime);

    // Illusion
    if ((_tmp_iStatus & 0x01000000) != 0)
        //m_pEffectSpr[73]->PutTransSprite(sX+125, sY+95, _tmp_iEffectFrame%24, dwTime);
        m_pEffectSpr[73]->PutTransSprite70(sX + 125, sY + 130 - _iAttackerHeight[sOwnerType], _tmp_iEffectFrame % 24, dwTime);

    // Illusion movement
    if ((_tmp_iStatus & 0x00200000) != 0)
        //m_pEffectSpr[151]->PutTransSprite(sX+90, sY+55, _tmp_iEffectFrame%24, dwTime);
        m_pEffectSpr[151]->PutTransSprite70(sX + 90, sY + 90 - _iAttackerHeight[sOwnerType], _tmp_iEffectFrame % 24, dwTime);

    /*	// Hero Flag (Heldenian)  Flameches d'entangle
        if ((_tmp_iStatus & 0x00020000) != 0)
            m_pEffectSpr[87]->PutTransSprite70(sX+53, sY+54, _tmp_iEffectFrame%29, dwTime);*/
}

void CGame::CheckActiveAura2(short sX, short sY, uint64_t dwTime, short sOwnerType)
{	// Poison
    if ((_tmp_iStatus & 0x80) != 0)
        //m_pEffectSpr[81]->PutTransSprite(sX+115, sY+85, _tmp_iEffectFrame%21, dwTime);
        m_pEffectSpr[81]->PutTransSprite70(sX + 115, sY + 120 - _iAttackerHeight[sOwnerType], _tmp_iEffectFrame % 21, dwTime);
    //	_iAttackerHeight[]

    if ((m_bIsHeldenianMode == true) && (m_bIsHeldenianMap == true))
        // En heldenian, seul le BloodyMantle est possible
        // mais le hero est aussi possible 
    {
        if ((_tmp_iStatus & 0x00400000) != 0)			// BloodyMantle
            m_pEffectSpr[107]->PutTransSprite70(sX - 5, sY, _tmp_iEffectFrame % 15, dwTime);
        else if ((_tmp_iStatus & 0x00800000) != 0)		// Magic Mantle
            m_pEffectSpr[114]->PutTransSprite70(sX - 5, sY, _tmp_iEffectFrame % 15, dwTime);
        else if ((_tmp_iStatus & 0x00010000) != 0)		// ArrowMantle
            m_pEffectSpr[115]->PutTransSprite70(sX - 5, sY, _tmp_iEffectFrame % 15, dwTime);

        if ((_tmp_iStatus & 0x00020000) != 0)
            m_pEffectSpr[87]->PutTransSprite70(sX + 53, sY + 54, _tmp_iEffectFrame % 29, dwTime);
    }
    else
        // Hors Heldenian, l'effêt Hero est impossible, donc il donnera des Mantles au lieu de Slate effect
    {
        if ((_tmp_iStatus & 0x00020000) != 0) // Si Hero Flag ==> Mantles
        {
            if ((_tmp_iStatus & 0x00400000) != 0)			// BloodyMantle
                m_pEffectSpr[107]->PutTransSprite70(sX - 5, sY, _tmp_iEffectFrame % 8, dwTime);
            else if ((_tmp_iStatus & 0x00800000) != 0)		// Magic Mantle
                m_pEffectSpr[114]->PutTransSprite70(sX - 5, sY, _tmp_iEffectFrame % 8, dwTime);
            else if ((_tmp_iStatus & 0x00010000) != 0)		// ArrowMantle
                m_pEffectSpr[115]->PutTransSprite70(sX - 5, sY, _tmp_iEffectFrame % 8, dwTime);
            else
                m_pEffectSpr[87]->PutTransSprite70(sX + 53, sY + 54, _tmp_iEffectFrame % 29, dwTime);
        }
        else /// sinon ==> Slates
        {
            if ((_tmp_iStatus & 0x00400000) != 0) // Slate red  (HP)  Flame au sol
                m_pEffectSpr[149]->PutTransSprite70(sX + 90, sY + 120, _tmp_iEffectFrame % 15, dwTime);

            if ((_tmp_iStatus & 0x00800000) != 0) // Slate Blue (Mana) Bleu au sol
                m_pEffectSpr[150]->PutTransSprite70(sX + 1, sY + 26, _tmp_iEffectFrame % 15, dwTime);

            if ((_tmp_iStatus & 0x00010000) != 0) // Slate Green (XP) Mauve au sol
                m_pEffectSpr[148]->PutTransSprite70(sX, sY + 32, _tmp_iEffectFrame % 23, dwTime);
        }
    }

}

void CGame::DrawAngel(int iSprite, short sX, short sY, char cFrame, uint64_t dwTime)
{
    if ((_tmp_iStatus & 0x1000) != 0) m_pSprite[DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + iSprite]->PutSpriteFast(sX, sY, cFrame, dwTime);  //AngelicPendant(STR)
    else if ((_tmp_iStatus & 0x2000) != 0) m_pSprite[DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + (50 * 1) + iSprite]->PutSpriteFast(sX, sY, cFrame, dwTime); //AngelicPendant(DEX)
    else if ((_tmp_iStatus & 0x4000) != 0) m_pSprite[DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + (50 * 2) + iSprite]->PutSpriteFast(sX, sY - 20, cFrame, dwTime);//AngelicPendant(INT)
    else if ((_tmp_iStatus & 0x8000) != 0) m_pSprite[DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + (50 * 3) + iSprite]->PutSpriteFast(sX, sY - 20, cFrame, dwTime);//AngelicPendant(MAG)

}

int CGame::bHasHeroSet(short Appr3, short Appr4, char OwnerType)
{
    char cArmor, cLeg, cBerk, cHat;
    cArmor = (Appr3 & 0xF000) >> 12;
    cLeg = (Appr3 & 0x0F00) >> 8;
    cHat = (Appr3 & 0x00F0) >> 4;
    cBerk = Appr3 & 0x000F;
    switch (OwnerType)
    {
        case 1:
        case 2:
        case 3:
            if ((cArmor == 8) && (cLeg == 5) && (cHat == 9) && (cBerk == 3)) return (1); // Warr elv M
            if ((cArmor == 9) && (cLeg == 6) && (cHat == 10) && (cBerk == 4)) return (1); // Warr ares M
            if ((cArmor == 10) && (cLeg == 5) && (cHat == 11) && (cBerk == 3)) return (2); // Mage elv M
            if ((cArmor == 11) && (cLeg == 6) && (cHat == 12) && (cBerk == 4)) return (2); // Mage ares M
            break;
        case 4:
        case 5:
        case 6: // fixed
            if ((cArmor == 9) && (cLeg == 6) && (cHat == 9) && (cBerk == 4)) return (1); //warr elv W
            if ((cArmor == 10) && (cLeg == 7) && (cHat == 10) && (cBerk == 5)) return (1); //warr ares W
            if ((cArmor == 11) && (cLeg == 6) && (cHat == 11) && (cBerk == 4)) return (2); //mage elv W
            if ((cArmor == 12) && (cLeg == 7) && (cHat == 12) && (cBerk == 5)) return (2); //mage ares W
            break;
    }
    return 0;
}

void CGame::ShowHeldenianVictory(short sSide)
{
    int i, iPlayerSide;
    DisableDialogBox(18);
    for (i = 0; i < DEF_TEXTDLGMAXLINES; i++)
    {
        if (m_pMsgTextList[i] != 0)
            delete m_pMsgTextList[i];
        m_pMsgTextList[i] = 0;
    }
    if (m_bCitizen == false) iPlayerSide = 0;
    else if (m_bAresden == true) iPlayerSide = 1;
    else if (m_bAresden == false) iPlayerSide = 2;
    switch (sSide)
    {
        case 0:
            PlaySound('E', 25, 0, 0);
            m_pMsgTextList[0] = new class CMsg(0, "Heldenian holy war has been closed!", 0);
            m_pMsgTextList[1] = new class CMsg(0, " ", 0);
            m_pMsgTextList[2] = new class CMsg(0, "Heldenian Holy war ended", 0);
            m_pMsgTextList[3] = new class CMsg(0, "in a tie.", 0);
            break;
        case 1:
            PlaySound('E', 25, 0, 0);
            m_pMsgTextList[0] = new class CMsg(0, "Heldenian holy war has been closed!", 0);
            m_pMsgTextList[1] = new class CMsg(0, " ", 0);
            m_pMsgTextList[2] = new class CMsg(0, "Heldenian Holy war ended", 0);
            m_pMsgTextList[3] = new class CMsg(0, "in favor of Aresden.", 0);
            break;
        case 2:
            PlaySound('E', 25, 0, 0);
            m_pMsgTextList[0] = new class CMsg(0, "Heldenian holy war has been closed!", 0);
            m_pMsgTextList[1] = new class CMsg(0, " ", 0);
            m_pMsgTextList[2] = new class CMsg(0, "Heldenian Holy war ended", 0);
            m_pMsgTextList[3] = new class CMsg(0, "in favor of Elvine.", 0);
            break;
    }
    m_pMsgTextList[4] = new class CMsg(0, " ", 0);

    if (((iPlayerSide != 1) && (iPlayerSide != 2))   // Player not a normal citizen
        || (sSide == 0))								// or no winner
    {
        PlaySound('E', 25, 0, 0);
        m_pMsgTextList[5] = new class CMsg(0, " ", 0);
        m_pMsgTextList[6] = new class CMsg(0, " ", 0);
        m_pMsgTextList[7] = new class CMsg(0, " ", 0);
        m_pMsgTextList[8] = new class CMsg(0, " ", 0);
    }
    else
    {
        if (sSide == iPlayerSide)
        {
            PlaySound('E', 23, 0, 0);
            PlaySound('C', 21, 0, 0);
            PlaySound('C', 22, 0, 0);
            m_pMsgTextList[5] = new class CMsg(0, "Congratulation.", 0);
            m_pMsgTextList[6] = new class CMsg(0, "As cityzen of victory,", 0);
            m_pMsgTextList[7] = new class CMsg(0, "You will recieve a reward.", 0);
            m_pMsgTextList[8] = new class CMsg(0, "      ", 0);
        }
        else
        {
            PlaySound('E', 24, 0, 0);
            PlaySound('C', 12, 0, 0);
            PlaySound('C', 13, 0, 0);
            m_pMsgTextList[5] = new class CMsg(0, "To our regret", 0);
            m_pMsgTextList[6] = new class CMsg(0, "As cityzen of defeat,", 0);
            m_pMsgTextList[7] = new class CMsg(0, "You cannot recieve any reward.", 0);
            m_pMsgTextList[8] = new class CMsg(0, "     ", 0);
        }
    }
    for (i = 9; i < 18; i++)
        m_pMsgTextList[i] = new class CMsg(0, " ", 0);
    EnableDialogBox(18, 0, 0, 0);
    DisableDialogBox(36);
    DisableDialogBox(37);
    DisableDialogBox(38);
}


void CGame::ResponseHeldenianTeleportList(char * pData)
{
    char * cp;
    int * ip, i;
#ifdef _DEBUG
    AddEventList("Teleport ???", 10);
#endif
    cp = pData + 6;
    ip = (int *)cp;
    m_iTeleportMapCount = *ip;
    cp += 4;
    for (i = 0; i < m_iTeleportMapCount; i++)
    {
        ip = (int *)cp;
        m_stTeleportList[i].iIndex = *ip;
        cp += 4;
        ZeroMemory(m_stTeleportList[i].mapname, sizeof(m_stTeleportList[i].mapname));
        memcpy(m_stTeleportList[i].mapname, cp, 10);
        cp += 10;
        ip = (int *)cp;
        m_stTeleportList[i].iX = *ip;
        cp += 4;
        ip = (int *)cp;
        m_stTeleportList[i].iY = *ip;
        cp += 4;
        ip = (int *)cp;
        m_stTeleportList[i].iCost = *ip;
        cp += 4;
    }
}

void CGame::DKGlare(int iWeaponColor, int iWeaponIndex, int * iWeaponGlare)
{
    if (iWeaponColor != 9) return;
    if (((iWeaponIndex >= DEF_SPRID_WEAPON_M + 64 * 14) && (iWeaponIndex < DEF_SPRID_WEAPON_M + 64 * 14 + 56)) //msw3
        || ((iWeaponIndex >= DEF_SPRID_WEAPON_W + 64 * 14) && (iWeaponIndex < DEF_SPRID_WEAPON_W + 64 * 14 + 56))) //wsw3
    {
        *iWeaponGlare = 3;
    }
    else if (((iWeaponIndex >= DEF_SPRID_WEAPON_M + 64 * 37) && (iWeaponIndex < DEF_SPRID_WEAPON_M + 64 * 37 + 56)) //MStaff3
        || ((iWeaponIndex >= DEF_SPRID_WEAPON_W + 64 * 37) && (iWeaponIndex < DEF_SPRID_WEAPON_W + 64 * 37 + 56)))//WStaff3
    {
        *iWeaponGlare = 2;
    }
}

void CGame::DrawDruncncity()
{	//DebugLog("druncncity");
}

// Manque ondulations et coloration des persos en verdatre....
// Druncncity:
/*401E60  /$ 83EC 7C            SUB ESP,7C
00401E63  |. 56                 PUSH ESI
00401E64  |. 8BF1               MOV ESI,ECX
00401E66  |. 8B86 10000300      MOV EAX,uint32_t PTR DS:[ESI+30010]
00401E6C  |. 85C0               TEST EAX,EAX
00401E6E  |. 75 05              JNZ SHORT 00401E75
00401E70  |. 5E                 POP ESI
00401E71  |. 83C4 7C            ADD ESP,7C
00401E74  |. C3                 RETN
00401E75  |> 6A 00              PUSH 0
00401E77  |. 8D5424 08          LEA EDX,uint32_t PTR SS:[ESP+8]
00401E7B  |. 6A 01              PUSH 1
00401E7D  |. C74424 0C 7C000000 MOV uint32_t PTR SS:[ESP+C],7C
00401E85  |. 8B08               MOV ECX,uint32_t PTR DS:[EAX]
00401E87  |. 52                 PUSH EDX
00401E88  |. 6A 00              PUSH 0
00401E8A  |. 50                 PUSH EAX
00401E8B  |. FF51 64            CALL NEAR uint32_t PTR DS:[ECX+64]
00401E8E  |. 85C0               TEST EAX,EAX
00401E90  |. 74 07              JE SHORT 00401E99
00401E92  |. 33C0               XOR EAX,EAX
00401E94  |. 5E                 POP ESI
00401E95  |. 83C4 7C            ADD ESP,7C
00401E98  |. C3                 RETN
00401E99  |> 8B4C24 0C          MOV ECX,uint32_t PTR SS:[ESP+C]
00401E9D  |. 8B4424 28          MOV EAX,uint32_t PTR SS:[ESP+28]
00401EA1  |. 8B5424 10          MOV EDX,uint32_t PTR SS:[ESP+10]
00401EA5  |. 83C1 D8            ADD ECX,-28
00401EA8  |. 50                 PUSH EAX                                ; /Arg3
00401EA9  |. 51                 PUSH ECX                                ; |Arg2
00401EAA  |. 8B8E DC010300      MOV ECX,uint32_t PTR DS:[ESI+301DC]        ; |
00401EB0  |. 52                 PUSH EDX                                ; |Arg1
00401EB1  |. E8 4AF2FFFF        CALL 00401100                           ; \Original.00401100
00401EB6  |. 8B86 10000300      MOV EAX,uint32_t PTR DS:[ESI+30010]
00401EBC  |. 6A 00              PUSH 0
00401EBE  |. 50                 PUSH EAX
00401EBF  |. 8B08               MOV ECX,uint32_t PTR DS:[EAX]
00401EC1  |. FF91 80000000      CALL NEAR uint32_t PTR DS:[ECX+80]
00401EC7  |. B8 01000000        MOV EAX,1
00401ECC  |. 5E                 POP ESI
00401ECD  |. 83C4 7C            ADD ESP,7C
00401ED0  \. C3                 RETN*/

/*00401100  /$ 81EC C0010000      SUB ESP,1C0                             ;   colore le personage
00401106  |. 53                 PUSH EBX
00401107  |. 56                 PUSH ESI
00401108  |. 8BF1               MOV ESI,ECX
0040110A  |. 33DB               XOR EBX,EBX
0040110C  |. 8B8C24 D4010000    MOV ECX,uint32_t PTR SS:[ESP+1D4]
00401113  |. 3BCB               CMP ECX,EBX
00401115  |. 0F84 CE030000      JE 004014E9
0040111B  |. 55                 PUSH EBP
0040111C  |. 8BAC24 D0010000    MOV EBP,uint32_t PTR SS:[ESP+1D0]
00401123  |. 0FAFAC24 D4010000  IMUL EBP,uint32_t PTR SS:[ESP+1D4]
0040112B  |. 57                 PUSH EDI
0040112C  |. 896C24 14          MOV uint32_t PTR SS:[ESP+14],EBP
00401130  |. 8D442D 00          LEA EAX,uint32_t PTR SS:[EBP+EBP]
00401134  |. 894424 10          MOV uint32_t PTR SS:[ESP+10],EAX
00401138  |. 50                 PUSH EAX
00401139  |. 8B46 34            MOV EAX,uint32_t PTR DS:[ESI+34]
0040113C  |. 51                 PUSH ECX
0040113D  |. 50                 PUSH EAX
0040113E  |. FF15 E0C04B00      CALL NEAR uint32_t PTR DS:[4BC0E0]         ;  Original.00401000
00401144  |. BA 06000000        MOV EDX,6
00401149  |. B9 03000000        MOV ECX,3
0040114E  |. 899424 80000000    MOV uint32_t PTR SS:[ESP+80],EDX
00401155  |. 899424 84000000    MOV uint32_t PTR SS:[ESP+84],EDX
0040115C  |. 899424 88000000    MOV uint32_t PTR SS:[ESP+88],EDX
00401163  |. 899424 8C000000    MOV uint32_t PTR SS:[ESP+8C],EDX
0040116A  |. 899424 90000000    MOV uint32_t PTR SS:[ESP+90],EDX
00401171  |. 899424 94000000    MOV uint32_t PTR SS:[ESP+94],EDX
00401178  |. 899424 98000000    MOV uint32_t PTR SS:[ESP+98],EDX
0040117F  |. 899424 9C000000    MOV uint32_t PTR SS:[ESP+9C],EDX
00401186  |. 899424 A0000000    MOV uint32_t PTR SS:[ESP+A0],EDX
0040118D  |. 899424 A4000000    MOV uint32_t PTR SS:[ESP+A4],EDX
00401194  |. BF 04000000        MOV EDI,4
00401199  |. B8 05000000        MOV EAX,5
0040119E  |. BA 02000000        MOV EDX,2
004011A3  |. 83C4 0C            ADD ESP,0C
004011A6  |. 894C24 18          MOV uint32_t PTR SS:[ESP+18],ECX
004011AA  |. 894C24 1C          MOV uint32_t PTR SS:[ESP+1C],ECX
004011AE  |. 894C24 20          MOV uint32_t PTR SS:[ESP+20],ECX
004011B2  |. 894C24 24          MOV uint32_t PTR SS:[ESP+24],ECX
004011B6  |. 894C24 28          MOV uint32_t PTR SS:[ESP+28],ECX
004011BA  |. 897C24 2C          MOV uint32_t PTR SS:[ESP+2C],EDI
004011BE  |. 897C24 30          MOV uint32_t PTR SS:[ESP+30],EDI
004011C2  |. 897C24 34          MOV uint32_t PTR SS:[ESP+34],EDI
004011C6  |. 897C24 38          MOV uint32_t PTR SS:[ESP+38],EDI
004011CA  |. 897C24 3C          MOV uint32_t PTR SS:[ESP+3C],EDI
004011CE  |. 897C24 40          MOV uint32_t PTR SS:[ESP+40],EDI
004011D2  |. 897C24 44          MOV uint32_t PTR SS:[ESP+44],EDI
004011D6  |. 897C24 48          MOV uint32_t PTR SS:[ESP+48],EDI
004011DA  |. 894424 4C          MOV uint32_t PTR SS:[ESP+4C],EAX
004011DE  |. 894424 50          MOV uint32_t PTR SS:[ESP+50],EAX
004011E2  |. 894424 54          MOV uint32_t PTR SS:[ESP+54],EAX
004011E6  |. 894424 58          MOV uint32_t PTR SS:[ESP+58],EAX
004011EA  |. 894424 5C          MOV uint32_t PTR SS:[ESP+5C],EAX
004011EE  |. 894424 60          MOV uint32_t PTR SS:[ESP+60],EAX
004011F2  |. 894424 64          MOV uint32_t PTR SS:[ESP+64],EAX
004011F6  |. 894424 68          MOV uint32_t PTR SS:[ESP+68],EAX
004011FA  |. 894424 6C          MOV uint32_t PTR SS:[ESP+6C],EAX
004011FE  |. 894424 70          MOV uint32_t PTR SS:[ESP+70],EAX
00401202  |. 898424 9C000000    MOV uint32_t PTR SS:[ESP+9C],EAX
00401209  |. 898424 A0000000    MOV uint32_t PTR SS:[ESP+A0],EAX
00401210  |. 898424 A4000000    MOV uint32_t PTR SS:[ESP+A4],EAX
00401217  |. 898424 A8000000    MOV uint32_t PTR SS:[ESP+A8],EAX
0040121E  |. 898424 AC000000    MOV uint32_t PTR SS:[ESP+AC],EAX
00401225  |. 898424 B0000000    MOV uint32_t PTR SS:[ESP+B0],EAX
0040122C  |. 898424 B4000000    MOV uint32_t PTR SS:[ESP+B4],EAX
00401233  |. 898424 B8000000    MOV uint32_t PTR SS:[ESP+B8],EAX
0040123A  |. 898424 BC000000    MOV uint32_t PTR SS:[ESP+BC],EAX
00401241  |. 89BC24 C0000000    MOV uint32_t PTR SS:[ESP+C0],EDI
00401248  |. 89BC24 C4000000    MOV uint32_t PTR SS:[ESP+C4],EDI
0040124F  |. 89BC24 C8000000    MOV uint32_t PTR SS:[ESP+C8],EDI
00401256  |. 89BC24 CC000000    MOV uint32_t PTR SS:[ESP+CC],EDI
0040125D  |. 89BC24 D0000000    MOV uint32_t PTR SS:[ESP+D0],EDI
00401264  |. 89BC24 D4000000    MOV uint32_t PTR SS:[ESP+D4],EDI
0040126B  |. 89BC24 D8000000    MOV uint32_t PTR SS:[ESP+D8],EDI
00401272  |. 89BC24 DC000000    MOV uint32_t PTR SS:[ESP+DC],EDI
00401279  |. 89BC24 E0000000    MOV uint32_t PTR SS:[ESP+E0],EDI
00401280  |. 898C24 E4000000    MOV uint32_t PTR SS:[ESP+E4],ECX
00401287  |. 898C24 E8000000    MOV uint32_t PTR SS:[ESP+E8],ECX
0040128E  |. 898C24 EC000000    MOV uint32_t PTR SS:[ESP+EC],ECX
00401295  |. 898C24 F0000000    MOV uint32_t PTR SS:[ESP+F0],ECX
0040129C  |. 898C24 F4000000    MOV uint32_t PTR SS:[ESP+F4],ECX
004012A3  |. 898C24 F8000000    MOV uint32_t PTR SS:[ESP+F8],ECX
004012AA  |. 898C24 FC000000    MOV uint32_t PTR SS:[ESP+FC],ECX
004012B1  |. 898C24 00010000    MOV uint32_t PTR SS:[ESP+100],ECX
004012B8  |. 899424 04010000    MOV uint32_t PTR SS:[ESP+104],EDX
004012BF  |. 899424 08010000    MOV uint32_t PTR SS:[ESP+108],EDX
004012C6  |. 899424 0C010000    MOV uint32_t PTR SS:[ESP+10C],EDX
004012CD  |. 899424 10010000    MOV uint32_t PTR SS:[ESP+110],EDX
004012D4  |. 898C24 BC010000    MOV uint32_t PTR SS:[ESP+1BC],ECX
004012DB  |. 898C24 C0010000    MOV uint32_t PTR SS:[ESP+1C0],ECX
004012E2  |. 898C24 C4010000    MOV uint32_t PTR SS:[ESP+1C4],ECX
004012E9  |. 898C24 C8010000    MOV uint32_t PTR SS:[ESP+1C8],ECX
004012F0  |. 898C24 CC010000    MOV uint32_t PTR SS:[ESP+1CC],ECX
004012F7  |. B8 01000000        MOV EAX,1
004012FC  |. 33C9               XOR ECX,ECX
004012FE  |. 3BEB               CMP EBP,EBX
00401300  |. 899424 14010000    MOV uint32_t PTR SS:[ESP+114],EDX
00401307  |. 899424 18010000    MOV uint32_t PTR SS:[ESP+118],EDX
0040130E  |. 899424 1C010000    MOV uint32_t PTR SS:[ESP+11C],EDX
00401315  |. 899424 20010000    MOV uint32_t PTR SS:[ESP+120],EDX
0040131C  |. 899424 24010000    MOV uint32_t PTR SS:[ESP+124],EDX
00401323  |. 898424 28010000    MOV uint32_t PTR SS:[ESP+128],EAX
0040132A  |. 898424 2C010000    MOV uint32_t PTR SS:[ESP+12C],EAX
00401331  |. 898424 30010000    MOV uint32_t PTR SS:[ESP+130],EAX
00401338  |. 898424 34010000    MOV uint32_t PTR SS:[ESP+134],EAX
0040133F  |. 898424 38010000    MOV uint32_t PTR SS:[ESP+138],EAX
00401346  |. 898424 3C010000    MOV uint32_t PTR SS:[ESP+13C],EAX
0040134D  |. 898424 40010000    MOV uint32_t PTR SS:[ESP+140],EAX
00401354  |. 898424 44010000    MOV uint32_t PTR SS:[ESP+144],EAX
0040135B  |. 898424 48010000    MOV uint32_t PTR SS:[ESP+148],EAX
00401362  |. 898424 4C010000    MOV uint32_t PTR SS:[ESP+14C],EAX
00401369  |. 898424 50010000    MOV uint32_t PTR SS:[ESP+150],EAX
00401370  |. 899C24 54010000    MOV uint32_t PTR SS:[ESP+154],EBX
00401377  |. 899C24 58010000    MOV uint32_t PTR SS:[ESP+158],EBX
0040137E  |. 899C24 5C010000    MOV uint32_t PTR SS:[ESP+15C],EBX
00401385  |. 899C24 60010000    MOV uint32_t PTR SS:[ESP+160],EBX
0040138C  |. 899C24 64010000    MOV uint32_t PTR SS:[ESP+164],EBX
00401393  |. 899C24 68010000    MOV uint32_t PTR SS:[ESP+168],EBX
0040139A  |. 899C24 6C010000    MOV uint32_t PTR SS:[ESP+16C],EBX
004013A1  |. 899C24 70010000    MOV uint32_t PTR SS:[ESP+170],EBX
004013A8  |. 899C24 74010000    MOV uint32_t PTR SS:[ESP+174],EBX
004013AF  |. 899C24 78010000    MOV uint32_t PTR SS:[ESP+178],EBX
004013B6  |. 898424 7C010000    MOV uint32_t PTR SS:[ESP+17C],EAX
004013BD  |. 898424 80010000    MOV uint32_t PTR SS:[ESP+180],EAX
004013C4  |. 898424 84010000    MOV uint32_t PTR SS:[ESP+184],EAX
004013CB  |. 898424 88010000    MOV uint32_t PTR SS:[ESP+188],EAX
004013D2  |. 898424 8C010000    MOV uint32_t PTR SS:[ESP+18C],EAX
004013D9  |. 898424 90010000    MOV uint32_t PTR SS:[ESP+190],EAX
004013E0  |. 898424 94010000    MOV uint32_t PTR SS:[ESP+194],EAX
004013E7  |. 898424 98010000    MOV uint32_t PTR SS:[ESP+198],EAX
004013EE  |. 898424 9C010000    MOV uint32_t PTR SS:[ESP+19C],EAX
004013F5  |. 899424 A0010000    MOV uint32_t PTR SS:[ESP+1A0],EDX
004013FC  |. 899424 A4010000    MOV uint32_t PTR SS:[ESP+1A4],EDX
00401403  |. 899424 A8010000    MOV uint32_t PTR SS:[ESP+1A8],EDX
0040140A  |. 899424 AC010000    MOV uint32_t PTR SS:[ESP+1AC],EDX
00401411  |. 899424 B0010000    MOV uint32_t PTR SS:[ESP+1B0],EDX
00401418  |. 899424 B4010000    MOV uint32_t PTR SS:[ESP+1B4],EDX
0040141F  |. 899424 B8010000    MOV uint32_t PTR SS:[ESP+1B8],EDX
00401426  |. 0F8E A1000000      JLE 004014CD
0040142C  |> 83F9 0A            /CMP ECX,0A
0040142F  |. 7D 10              |JGE SHORT 00401441
00401431  |. 8B56 34            |MOV EDX,uint32_t PTR DS:[ESI+34]
00401434  |. 8B46 30            |MOV EAX,uint32_t PTR DS:[ESI+30]
00401437  |. 66:8B144A          |MOV DX,uint16_t PTR DS:[EDX+ECX*2]
0040143B  |. 66:891448          |MOV uint16_t PTR DS:[EAX+ECX*2],DX
0040143F  |. EB 7F              |JMP SHORT 004014C0
00401441  |> 8BC1               |MOV EAX,ECX
00401443  |. BD 80020000        |MOV EBP,280
00401448  |. 99                 |CDQ
00401449  |. F7FD               |IDIV EBP
0040144B  |. 3BD3               |CMP EDX,EBX
0040144D  |. 75 11              |JNZ SHORT 00401460
0040144F  |. 8B6E 38            |MOV EBP,uint32_t PTR DS:[ESI+38]
00401452  |. 45                 |INC EBP
00401453  |. 8BC5               |MOV EAX,EBP
00401455  |. 896E 38            |MOV uint32_t PTR DS:[ESI+38],EBP
00401458  |. 83F8 6E            |CMP EAX,6E
0040145B  |. 7C 03              |JL SHORT 00401460
0040145D  |. 895E 38            |MOV uint32_t PTR DS:[ESI+38],EBX
00401460  |> 3BD7               |CMP EDX,EDI
00401462  |. 7D 19              |JGE SHORT 0040147D
00401464  |. 8B46 38            |MOV EAX,uint32_t PTR DS:[ESI+38]
00401467  |. 395484 18          |CMP uint32_t PTR SS:[ESP+EAX*4+18],EDX
0040146B  |. 7E 10              |JLE SHORT 0040147D
0040146D  |. 8B56 34            |MOV EDX,uint32_t PTR DS:[ESI+34]
00401470  |. 8B46 30            |MOV EAX,uint32_t PTR DS:[ESI+30]
00401473  |. 66:8B144A          |MOV DX,uint16_t PTR DS:[EDX+ECX*2]
00401477  |. 66:891448          |MOV uint16_t PTR DS:[EAX+ECX*2],DX
0040147B  |. EB 43              |JMP SHORT 004014C0
0040147D  |> 81FA 7B020000      |CMP EDX,27B
00401483  |. 7E 20              |JLE SHORT 004014A5
00401485  |. 8B46 38            |MOV EAX,uint32_t PTR DS:[ESI+38]
00401488  |. 8B4484 18          |MOV EAX,uint32_t PTR SS:[ESP+EAX*4+18]
0040148C  |. 05 7B020000        |ADD EAX,27B
00401491  |. 3BC2               |CMP EAX,EDX
00401493  |. 7D 10              |JGE SHORT 004014A5
00401495  |. 8B56 34            |MOV EDX,uint32_t PTR DS:[ESI+34]
00401498  |. 8B46 30            |MOV EAX,uint32_t PTR DS:[ESI+30]
0040149B  |. 66:8B144A          |MOV DX,uint16_t PTR DS:[EDX+ECX*2]
0040149F  |. 66:891448          |MOV uint16_t PTR DS:[EAX+ECX*2],DX
004014A3  |. EB 1B              |JMP SHORT 004014C0
004014A5  |> 8B46 38            |MOV EAX,uint32_t PTR DS:[ESI+38]
004014A8  |. 8BD1               |MOV EDX,ECX
004014AA  |. 8B6C84 18          |MOV EBP,uint32_t PTR SS:[ESP+EAX*4+18]
004014AE  |. 8B46 34            |MOV EAX,uint32_t PTR DS:[ESI+34]
004014B1  |. 2BD5               |SUB EDX,EBP
004014B3  |. 8B6E 30            |MOV EBP,uint32_t PTR DS:[ESI+30]
004014B6  |. 66:8B5450 08       |MOV DX,uint16_t PTR DS:[EAX+EDX*2+8]
004014BB  |. 66:89544D 00       |MOV uint16_t PTR SS:[EBP+ECX*2],DX
004014C0  |> 8B4424 14          |MOV EAX,uint32_t PTR SS:[ESP+14]
004014C4  |. 41                 |INC ECX
004014C5  |. 3BC8               |CMP ECX,EAX
004014C7  |.^0F8C 5FFFFFFF      \JL 0040142C
004014CD  |> 8B4424 10          MOV EAX,uint32_t PTR SS:[ESP+10]
004014D1  |. 8B4E 30            MOV ECX,uint32_t PTR DS:[ESI+30]
004014D4  |. 8B9424 DC010000    MOV EDX,uint32_t PTR SS:[ESP+1DC]
004014DB  |. 50                 PUSH EAX                                ; /Arg3
004014DC  |. 51                 PUSH ECX                                ; |Arg2
004014DD  |. 52                 PUSH EDX                                ; |Arg1
004014DE  |. FF15 E0C04B00      CALL NEAR uint32_t PTR DS:[4BC0E0]         ; \Original.00401000
004014E4  |. 83C4 0C            ADD ESP,0C
004014E7  |. 5F                 POP EDI
004014E8  |. 5D                 POP EBP
004014E9  |> 5E                 POP ESI
004014EA  |. 5B                 POP EBX
004014EB  |. 81C4 C0010000      ADD ESP,1C0
004014F1  \. C2 0C00            RETN 0C*/

void CGame::Abaddon_corpse(int sX, int sY)
{
    int ir = (rand() % 20) - 10;
    _DrawThunderEffect(sX + 30, 0, sX + 30, sY - 10, ir, ir, 1);
    _DrawThunderEffect(sX + 30, 0, sX + 30, sY - 10, ir + 2, ir, 2);
    _DrawThunderEffect(sX + 30, 0, sX + 30, sY - 10, ir - 2, ir, 2);
    ir = (rand() % 20) - 10;
    _DrawThunderEffect(sX - 20, 0, sX - 20, sY - 35, ir, ir, 1);
    _DrawThunderEffect(sX - 20, 0, sX - 20, sY - 35, ir + 2, ir, 2);
    _DrawThunderEffect(sX - 20, 0, sX - 20, sY - 35, ir - 2, ir, 2);
    ir = (rand() % 20) - 10;
    _DrawThunderEffect(sX - 10, 0, sX - 10, sY + 30, ir, ir, 1);
    _DrawThunderEffect(sX - 10, 0, sX - 10, sY + 30, ir + 2, ir + 2, 2);
    _DrawThunderEffect(sX - 10, 0, sX - 10, sY + 30, ir - 2, ir + 2, 2);
    ir = (rand() % 20) - 10;
    _DrawThunderEffect(sX + 50, 0, sX + 50, sY + 35, ir, ir, 1);
    _DrawThunderEffect(sX + 50, 0, sX + 50, sY + 35, ir + 2, ir + 2, 2);
    _DrawThunderEffect(sX + 50, 0, sX + 50, sY + 35, ir - 2, ir + 2, 2);
    ir = (rand() % 20) - 10;
    _DrawThunderEffect(sX + 65, 0, sX + 65, sY - 5, ir, ir, 1);
    _DrawThunderEffect(sX + 65, 0, sX + 65, sY - 5, ir + 2, ir + 2, 2);
    _DrawThunderEffect(sX + 65, 0, sX + 65, sY - 5, ir - 2, ir + 2, 2);
    ir = (rand() % 20) - 10;
    _DrawThunderEffect(sX + 45, 0, sX + 45, sY - 50, ir, ir, 1);
    _DrawThunderEffect(sX + 45, 0, sX + 45, sY - 50, ir + 2, ir + 2, 2);
    _DrawThunderEffect(sX + 45, 0, sX + 45, sY - 50, ir - 2, ir + 2, 2);

    for (int x = sX - 50; x <= sX + 100; x += rand() % 35)
        for (int y = sY - 30; y <= sY + 50; y += rand() % 45)
        {
            ir = (rand() % 20) - 10;
            _DrawThunderEffect(x, 0, x, y, ir, ir, 2);
        }
}

void CGame::PutChatString(int iX, int iY, std::string pString, Color color)
{
    PutFontString("default", iX, iY, pString, color); //TODO: make 'chat' font?
}

void CGame::connection_loss_gamemode()
{
    switch (m_cGameMode)
    {
        case DEF_GAMEMODE_ONCONNECTING:
        case DEF_GAMEMODE_ONMAINGAME:
        case DEF_GAMEMODE_ONLOGIN:
        case DEF_GAMEMODE_ONSELECTCHARACTER:
        case DEF_GAMEMODE_ONLOGRESMSG:
            // play mode. connection stop here would typically indicate a disconnect
            ChangeGameMode(DEF_GAMEMODE_ONCONNECTIONLOST);
            break;
        case DEF_GAMEMODE_ONMAINMENU:
            break;
        default:
            ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
            break;
    }
}
