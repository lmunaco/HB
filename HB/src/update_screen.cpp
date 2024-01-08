//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include "Game.h"
#include "lan_eng.h"
#include <ixwebsocket/IXWebSocket.h>

extern short _tmp_sOwnerType, _tmp_sAppr1, _tmp_sAppr2, _tmp_sAppr3, _tmp_sAppr4;//, _tmp_iStatus;
//bool _tmp_iStatus;
extern int _tmp_iStatus;
extern char  _tmp_cAction, _tmp_cDir, _tmp_cFrame, _tmp_cName[12];
extern int   _tmp_iChatIndex, _tmp_dx, _tmp_dy, _tmp_iApprColor, _tmp_iEffectType, _tmp_iEffectFrame, _tmp_dX, _tmp_dY; // 21.171 2002-6-14
extern uint16_t  _tmp_wObjectID;
extern char cDynamicObjectData1, cDynamicObjectData2, cDynamicObjectData3, cDynamicObjectData4;
extern uint16_t  wFocusObjectID;
extern short sFocus_dX, sFocus_dY;
extern char  cFocusAction, cFocusFrame, cFocusDir, cFocusName[12];
extern short sFocusX, sFocusY, sFocusOwnerType, sFocusAppr1, sFocusAppr2, sFocusAppr3, sFocusAppr4;
extern int iFocuiStatus;
extern int   iFocusApprColor;

extern uint64_t unixtime();
extern uint32_t unixseconds();

void CGame::UpdateScreen()
{
    G_dwGlobalTime = unixtime();
    if (m_cGameMode != DEF_GAMEMODE_ONMAINGAME)	m_pBGM.stop(); // MP3
    switch (m_cGameMode)
    {
        case DEF_GAMEMODE_ONVERSIONNOTMATCH:
            UpdateScreen_OnVersionNotMatch();
            break;

        case DEF_GAMEMODE_ONCONNECTING:
            UpdateScreen_OnConnecting();
            break;

        case DEF_GAMEMODE_ONMAINMENU:
            UpdateScreen_OnMainMenu();
            break;

        case DEF_GAMEMODE_ONLOADING:
            UpdateScreen_OnLoading(true);
            break;

        case DEF_GAMEMODE_ONMAINGAME:
            UpdateScreen_OnGame();
            break;

        case DEF_GAMEMODE_ONWAITINGINITDATA:
            UpdateScreen_OnWaitInitData();
            break;

        case DEF_GAMEMODE_ONCONNECTIONLOST:
            UpdateScreen_OnConnectionLost();
            break;

        case DEF_GAMEMODE_ONMSG:
            UpdateScreen_OnMsg();
            break;

        case DEF_GAMEMODE_ONLOGIN:
            UpdateScreen_OnLogin();
            break;

        case DEF_GAMEMODE_ONSELECTSERVER:
            UpdateScreen_OnSelectServer();
            break;

        case DEF_GAMEMODE_ONQUIT:
            UpdateScreen_OnQuit();
            break;

        case DEF_GAMEMODE_ONQUERYFORCELOGIN:
            UpdateScreen_OnQueryForceLogin();
            break;

        case DEF_GAMEMODE_ONSELECTCHARACTER:
            UpdateScreen_OnSelectCharacter();
            break;

        case DEF_GAMEMODE_ONCREATENEWCHARACTER:
            UpdateScreen_OnCreateNewCharacter();
            break;

        case DEF_GAMEMODE_ONWAITINGRESPONSE:
            UpdateScreen_OnWaitingResponse();
            break;

        case DEF_GAMEMODE_ONQUERYDELETECHARACTER:
            UpdateScreen_OnQueryDeleteCharacter();
            break;

        case DEF_GAMEMODE_ONLOGRESMSG:
            UpdateScreen_OnLogResMsg();
            break;

        case DEF_GAMEMODE_ONCHANGEPASSWORD:
            UpdateScreen_OnChangePassword();
            break;
    }

#ifdef DEF_USING_WIN_IME

    if (GetAsyncKeyState(VK_RETURN) != 0) m_cEnterCheck = 1;
    if ((m_cEnterCheck == 1) && (GetAsyncKeyState(VK_RETURN) == 0))
    {
        m_bEnterPressed = true;
        m_cEnterCheck = 0;
    }
    if (GetAsyncKeyState(VK_TAB) != 0) m_cTabCheck = 1;
    if ((m_cTabCheck == 1) && (GetAsyncKeyState(VK_TAB) == 0))
    {
        m_cCurFocus++;
        if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
        if (m_cGameMode == DEF_GAMEMODE_ONMAINGAME) bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_TOGGLECOMBATMODE, 0, 0, 0, 0, 0);
        m_cTabCheck = 0;
    }
    if (m_bInputStatus)
    {
        if (GetAsyncKeyState(VK_LEFT) != 0) m_cLeftArrowCheck = 1;
        if ((m_cLeftArrowCheck == 1) && (GetAsyncKeyState(VK_LEFT) == 0))
        {
            m_cLeftArrowCheck = 0;
            if (G_hEditWnd != 0)
            {
                int iStrLen = strlen(m_pInputBuffer);
                SendMessage(G_hEditWnd, EM_SETSEL, iStrLen, iStrLen);
            }
        }
    }
#endif

    float diffx = static_cast<float>(m_DDraw.screenwidth) / m_DDraw.screenwidth_v;
    float diffy = static_cast<float>(m_DDraw.screenheight) / m_DDraw.screenheight_v;
    int mx = int(m_stMCursor.sX * diffx);
    int my = int(m_stMCursor.sY * diffy);

    std::string cfps;
    cfps = std::format("FPS: {}\n\n\n\n\nm_sViewPointX: {}\nm_sViewDstX: {}", fps.getFPS(), m_sViewPointX, m_sViewDstX);

    m_DDraw._text.setString(cfps);
    m_DDraw._text.setPosition(5, 5);
    m_DDraw._text.setFillColor(Color(255, 255, 255, 255));
    m_DDraw._text.setCharacterSize(14);

    std::string pingstr;

    pingstr = std::format("Ping: {}", (ping / (1000i64 * 1000)) / 2);

    if (draw_version) DrawVersion();

    m_DDraw.back_buffer.display();

    m_DDraw.window.clear();

    m_DDraw.window.draw(m_DDraw.back_buffer_sprite);

    // draw mouse over everything - this draws it full size at every virtual resolution.
// this needs to go above `window.draw(sprite);` and draw to `visible` above to scale with virtual resolution
    if (m_bIsObserverMode == true)
    {
        DrawLine(mx - 5, my, mx + 5, my, Color(255, 0, 0));
        DrawLine(mx, my, mx, my + 5, Color(255, 0, 0));

        DrawLine(mx - 5, my - 1, mx + 5, my - 1, Color(255, 0, 0, 127));
        DrawLine(mx - 1, my - 5, mx - 1, my + 5, Color(255, 0, 0, 127));

        DrawLine(mx - 5, my + 1, mx + 5, my + 1, Color(255, 0, 0, 127));
        DrawLine(mx + 1, my - 5, mx + 1, my + 5, Color(255, 0, 0, 127));
    }
    else
        m_pSprite[DEF_SPRID_MOUSECURSOR]->draw_to(mx, my, m_stMCursor.sCursorFrame, unixseconds(), Color(255, 255, 255), DS_WIN);

    m_stMCursor.sZ = 0;

    sf::Text TESTTEXT;

    TESTTEXT.setFont(m_DDraw._font.at("arya"));

    int drawcursorx = mx;
    int drawcursory = my - 40;

    if (mx > m_DDraw.GetWidth() - 110)
        drawcursorx = mx - 120;
    if (my < 55)
        drawcursory = my + 50;

    TESTTEXT.setString(std::format("R({},{})", mx, my));
    TESTTEXT.setOutlineColor(Color(0, 0, 0));
    TESTTEXT.setOutlineThickness(3.f);
    TESTTEXT.setFillColor(Color(255, 255, 255));
    TESTTEXT.setCharacterSize(20);
    TESTTEXT.setColor(Color(255, 255, 255));
    TESTTEXT.setPosition((float)drawcursorx, (float)drawcursory);
    m_DDraw.draw_to(TESTTEXT, DS_WIN);

    TESTTEXT.setPosition((float)drawcursorx, (float)drawcursory - 20);
    TESTTEXT.setString(fmt::format("V({},{})", m_stMCursor.sX, m_stMCursor.sY));

    m_DDraw.draw_to(TESTTEXT, DS_WIN);

    m_DDraw.window.draw(m_DDraw._text);

    m_DDraw._text.setPosition(5, 25);
    m_DDraw._text.setString(pingstr);
    m_DDraw.window.draw(m_DDraw._text);

//     _text.setPosition(5, 40);
//     _text.setString(std::format("x: {} - y: {} - zoom: {}", xtest, ytest, zoom));
//     window.draw(_text);
}

void CGame::_Draw_UpdateScreen_OnCreateNewAccount()
{
    m_DDraw.back_buffer.clear(sf::Color::Black);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_NEWACCOUNT, 0, 0, 0, true);
    PutString2(329, 110, m_cAccountName, 200, 200, 200);
    PutString(329, 125, m_cAccountPassword, Color(200, 200, 200), true, 1);
    PutString(329, 140, m_cAccountPassword, Color(200, 200, 200), true, 1);
    PutString2(300, 202, m_cAccountCountry, 200, 200, 200);
    PutString2(300, 218, m_cAccountSSN, 200, 200, 200);
    PutString2(194, 257, m_cEmailAddr, 200, 200, 200);
}


void CGame::UpdateScreen_OnLoading(bool bActive)
{
    int i;
    if (bActive) UpdateScreen_OnLoading_Progress();

    switch (m_cLoading)
    {
        case 0:
        {
            m_pSprite[DEF_SPRID_MOUSECURSOR] = new CSprite(&m_DDraw, "interface", 0, false);
            m_pSprite[DEF_SPRID_INTERFACE_SPRFONTS] = new CSprite(&m_DDraw, "interface", 1, false);

            m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS1] = new CSprite(&m_DDraw, "Newmaps", 0, false);
            m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS2] = new CSprite(&m_DDraw, "Newmaps", 1, false);
            m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS3] = new CSprite(&m_DDraw, "Newmaps", 2, false);
            m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS4] = new CSprite(&m_DDraw, "Newmaps", 3, false);
            m_pSprite[DEF_SPRID_INTERFACE_NEWMAPS5] = new CSprite(&m_DDraw, "Newmaps", 4, false);

            m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN] = new CSprite(&m_DDraw, "LoginDialog", 0, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU] = new CSprite(&m_DDraw, "New-Dialog", 1, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_QUIT] = new CSprite(&m_DDraw, "New-Dialog", 2, false);

            m_pSprite[DEF_SPRID_INTERFACE_ND_GAME1] = new CSprite(&m_DDraw, "GameDialog", 0, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_GAME2] = new CSprite(&m_DDraw, "GameDialog", 1, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_GAME3] = new CSprite(&m_DDraw, "GameDialog", 2, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_GAME4] = new CSprite(&m_DDraw, "GameDialog", 3, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_CRUSADE] = new CSprite(&m_DDraw, "GameDialog", 4, false);
            //m_pSprite[DEF_SPRID_INTERFACE_GUIDEMAP] =      new CSprite(&m_DDraw, "GameDialog", 5, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_ICONPANNEL] = new CSprite(&m_DDraw, "GameDialog", 6, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_INVENTORY] = new CSprite(&m_DDraw, "GameDialog", 7, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_SELECTCHAR] = new CSprite(&m_DDraw, "GameDialog", 8, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_NEWCHAR] = new CSprite(&m_DDraw, "GameDialog", 9, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_NEWEXCHANGE] = new CSprite(&m_DDraw, "GameDialog", 10, false);

            m_pSprite[DEF_SPRID_INTERFACE_ND_TEXT] = new CSprite(&m_DDraw, "DialogText", 0, false);
            m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON] = new CSprite(&m_DDraw, "DialogText", 1, false);
            MakeSprite("Telescope", DEF_SPRID_INTERFACE_GUIDEMAP, 32, false);

#ifdef DEF_EQUILIBRIUM_PROJECT	// telescope2 
            MakeSprite("Telescope2", DEF_SPRID_INTERFACE_GUIDEMAP + 35, 9, false);
#else
            MakeSprite("Telescope2", DEF_SPRID_INTERFACE_GUIDEMAP + 35, 4, false);
#endif

            MakeSprite("monster", DEF_SPRID_INTERFACE_MONSTER, 1, false);
            m_cLoading = 4;
        }
        break;
        case 4:
        {
            MakeTileSpr("maptiles1", 0, 32, true);

#ifdef DEF_EQUILIBRIUM_PROJECT	// Structures1
            MakeTileSpr("structures1", 50, 20, true);
#else
            m_pTileSpr[1 + 50] = new CSprite(&m_DDraw, "structures1", 1, true);
            m_pTileSpr[5 + 50] = new CSprite(&m_DDraw, "structures1", 5, true);
#endif
            MakeTileSpr("Sinside1", 70, 27, false);
            MakeTileSpr("Trees1", 100, 46, true);
            MakeTileSpr("TreeShadows", 150, 46, true);
            MakeTileSpr("objects1", 200, 10, true);
            MakeTileSpr("objects2", 211, 5, true);
            MakeTileSpr("objects3", 216, 4, true);
            MakeTileSpr("objects4", 220, 2, true);
            m_cLoading = 8;
        }
        break;
        case 8:
        {
            MakeTileSpr("Tile223-225", 223, 3, true);
            MakeTileSpr("Tile226-229", 226, 4, true);
            MakeTileSpr("objects5", 230, 9, true);
            MakeTileSpr("objects6", 238, 4, true);
            MakeTileSpr("objects7", 242, 7, true);
            MakeTileSpr("maptiles2", 300, 15, true);
#ifdef DEF_EQUILIBRIUM_PROJECT
            MakeTileSpr("maptiles3", 315, 5, true);
#endif
            MakeTileSpr("maptiles4", 320, 10, true);
            MakeTileSpr("maptiles5", 330, 19, true);
            MakeTileSpr("maptiles6", 349, 4, true);
            MakeTileSpr("maptiles353-361", 353, 9, true);
            MakeTileSpr("Tile363-366", 363, 4, true);
            MakeTileSpr("Tile367-367", 367, 1, true);
            MakeTileSpr("Tile370-381", 370, 12, true);
            MakeTileSpr("Tile382-387", 382, 6, true);
            MakeTileSpr("Tile388-402", 388, 15, true);
            m_cLoading = 12;
        }
        break;
        case 12:
        {
            MakeTileSpr("Tile403-405", 403, 3, true);
            MakeTileSpr("Tile406-421", 406, 16, true);
            MakeTileSpr("Tile422-429", 422, 8, true);
            MakeTileSpr("Tile430-443", 430, 14, true);
            MakeTileSpr("Tile444-444", 444, 1, true);
            MakeTileSpr("Tile445-461", 445, 17, true);
            MakeTileSpr("Tile462-473", 462, 12, true);
            MakeTileSpr("Tile474-478", 474, 5, true);
            MakeTileSpr("Tile479-488", 479, 10, true);
            MakeTileSpr("Tile489-522", 489, 34, true);
            MakeTileSpr("Tile523-530", 523, 8, true);
            MakeTileSpr("Tile531-540", 531, 10, true);
            MakeTileSpr("Tile541-545", 541, 5, true);

            // DEF_SPRID_ITEMPACK_PIVOTPOINT+0
            MakeSprite("item-pack", DEF_SPRID_ITEMPACK_PIVOTPOINT + 1, 27, false);
            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + 20] = new CSprite(&m_DDraw, "item-pack", 17, false); //
            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + 21] = new CSprite(&m_DDraw, "item-pack", 18, false); //
            m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + 22] = new CSprite(&m_DDraw, "item-pack", 19, false); // Angels

            // DEF_SPRID_ITEMGROUND_PIVOTPOINT+1
            MakeSprite("item-ground", DEF_SPRID_ITEMGROUND_PIVOTPOINT + 1, 19, false);
            m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT + 20] = new CSprite(&m_DDraw, "item-ground", 17, false);
            m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT + 21] = new CSprite(&m_DDraw, "item-ground", 18, false);
            m_pSprite[DEF_SPRID_ITEMGROUND_PIVOTPOINT + 22] = new CSprite(&m_DDraw, "item-ground", 19, false);//Angels
            MakeSprite("item-dynamic", DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT, 3, false);

#ifdef DEF_EQUILIBRIUM_PROJECT  // Dynamic items, statues DEF_DYNAMICOBJECT_STATUE1
            m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT + 3] = new CSprite(&m_DDraw, "Objects6", 0, false);
            m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT + 4] = new CSprite(&m_DDraw, "Objects6", 2, false);
            m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT + 5] = new CSprite(&m_DDraw, "Objects1", 5, false);
            m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT + 6] = new CSprite(&m_DDraw, "Objects2", 1, false);
            m_pSprite[DEF_SPRID_ITEMDYNAMIC_PIVOTPOINT + 7] = new CSprite(&m_DDraw, "Objects2", 4, false);
#endif
            m_cLoading = 16;
        }
        break;
        case 16:
        {
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 0] = new CSprite(&m_DDraw, "item-equipM", 0, false);	// body
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 1] = new CSprite(&m_DDraw, "item-equipM", 1, false);	// 1-swords
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 2] = new CSprite(&m_DDraw, "item-equipM", 2, false);	// 2-bows
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 3] = new CSprite(&m_DDraw, "item-equipM", 3, false);	// 3-shields
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 4] = new CSprite(&m_DDraw, "item-equipM", 4, false);	// 4-tunics
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 5] = new CSprite(&m_DDraw, "item-equipM", 5, false);	// 5-shoes
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 7] = new CSprite(&m_DDraw, "item-equipM", 6, false);	// 6-berk
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 8] = new CSprite(&m_DDraw, "item-equipM", 7, false);	// 7-hoses
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 9] = new CSprite(&m_DDraw, "item-equipM", 8, false);	// 8-bodyarmor
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 15] = new CSprite(&m_DDraw, "item-equipM", 11, false); // Axe hammer
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 17] = new CSprite(&m_DDraw, "item-equipM", 12, false); // Wands
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 18] = new CSprite(&m_DDraw, "item-equipM", 9, false);  // hair
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 19] = new CSprite(&m_DDraw, "item-equipM", 10, false); // undies
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 20] = new CSprite(&m_DDraw, "item-equipM", 13, false); // capes
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 21] = new CSprite(&m_DDraw, "item-equipM", 14, false); // helm

            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 16] = new CSprite(&m_DDraw, "item-pack", 15); // Necks
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 22] = new CSprite(&m_DDraw, "item-pack", 19); // Angels

            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 40] = new CSprite(&m_DDraw, "item-equipW", 0, false); // body
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 41] = new CSprite(&m_DDraw, "item-equipW", 1, false); // 1-swords
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 42] = new CSprite(&m_DDraw, "item-equipW", 2, false); // 2-bows
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 43] = new CSprite(&m_DDraw, "item-equipW", 3, false); // 3-shields
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 45] = new CSprite(&m_DDraw, "item-equipW", 4, false); // 4-shoes
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 50] = new CSprite(&m_DDraw, "item-equipW", 5, false); // 5-Soustif
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 51] = new CSprite(&m_DDraw, "item-equipW", 6, false); // 6 berk
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 52] = new CSprite(&m_DDraw, "item-equipW", 7, false); // 7 hose
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 53] = new CSprite(&m_DDraw, "item-equipW", 8, false); // 8-hoses
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 55] = new CSprite(&m_DDraw, "item-equipW", 11, false); // Axe hammer
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 57] = new CSprite(&m_DDraw, "item-equipW", 12, false); // Wands
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 58] = new CSprite(&m_DDraw, "item-equipW", 9, false); // hair
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 59] = new CSprite(&m_DDraw, "item-equipW", 10, false);// undies
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 60] = new CSprite(&m_DDraw, "item-equipW", 13, false);// capes
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 61] = new CSprite(&m_DDraw, "item-equipW", 14, false);// helm

            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 56] = new CSprite(&m_DDraw, "item-pack", 15);// necks
            m_pSprite[DEF_SPRID_ITEMEQUIP_PIVOTPOINT + 62] = new CSprite(&m_DDraw, "item-pack", 19); // Angels
            MakeSprite("Bm", 500 + 15 * 8 * 0, 96, true);// Black Man (Type: 1)
            MakeSprite("Wm", 500 + 15 * 8 * 1, 96, true);// White Man (Type: 2)
            MakeSprite("Ym", 500 + 15 * 8 * 2, 96, true);// Yellow Man (Type: 3)
            m_cLoading = 20;
        }
        break;
        case 20:
        {
            MakeSprite("TutelarAngel1", DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + 50 * 0, 48, false);//(STR)
            MakeSprite("TutelarAngel2", DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + 50 * 1, 48, false);//(DEX)
            MakeSprite("TutelarAngel3", DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + 50 * 2, 48, false);//(INT)
            MakeSprite("TutelarAngel4", DEF_SPRID_TUTELARYANGELS_PIVOTPOINT + 50 * 3, 48, false);//(MAG)
            MakeSprite("Bw", 500 + 15 * 8 * 3, 96, true);// Black Woman (Type: 4)
            MakeSprite("Ww", 500 + 15 * 8 * 4, 96, true);// White Woman (Type: 5)
            MakeSprite("Yw", 500 + 15 * 8 * 5, 96, true);// Yellow Woman (Type: 6)
            m_cLoading = 24;
        }
        break;
        case 24:
        {
            MakeSprite("slm", DEF_SPRID_MOB + 7 * 8 * 0, 40, true);// Slime (Type: 10)
            MakeSprite("ske", DEF_SPRID_MOB + 7 * 8 * 1, 40, true);// Skeleton (Type: 11)
            MakeSprite("Gol", DEF_SPRID_MOB + 7 * 8 * 2, 40, true);// Stone-Golem (Type: 12)
            MakeSprite("Cyc", DEF_SPRID_MOB + 7 * 8 * 3, 40, true);// Cyclops (Type: 13)
            MakeSprite("Orc", DEF_SPRID_MOB + 7 * 8 * 4, 40, true);// Orc (Type: 14)
            MakeSprite("Shopkpr", DEF_SPRID_MOB + 7 * 8 * 5, 8);		// ShopKeeper-Woman (Type: 15)
            MakeSprite("Ant", DEF_SPRID_MOB + 7 * 8 * 6, 40, true);//  Giant-Ant (Type: 16)
            MakeSprite("Scp", DEF_SPRID_MOB + 7 * 8 * 7, 40, true);//  Scorpion (Type: 17)
            MakeSprite("Zom", DEF_SPRID_MOB + 7 * 8 * 8, 40, true);//  Zombie (Type: 18)
            MakeSprite("Gandlf", DEF_SPRID_MOB + 7 * 8 * 9, 8, true);// Gandalf ¸ (Type: 19)
            MakeSprite("Howard", DEF_SPRID_MOB + 7 * 8 * 10, 8, true);// Howard º¸°ü¼Ò ÁÖÀÎ (Type: 20)
            MakeSprite("Guard", DEF_SPRID_MOB + 7 * 8 * 11, 40, true);// Guard (Type: 21)
            MakeSprite("Amp", DEF_SPRID_MOB + 7 * 8 * 12, 40, true);// Amphis (Type: 22)
            MakeSprite("Cla", DEF_SPRID_MOB + 7 * 8 * 13, 40, true);// Clay-Golem (Type: 23)
            MakeSprite("tom", DEF_SPRID_MOB + 7 * 8 * 14, 8, true);// Tom (Type: 24)
            MakeSprite("William", DEF_SPRID_MOB + 7 * 8 * 15, 8, true);// William (Type: 25)
            m_cLoading = 28;
        }
        break;
        case 28:
        {
            MakeSprite("Kennedy", DEF_SPRID_MOB + 7 * 8 * 16, 8, true);// Kennedy (Type: 26)
            MakeSprite("Helb", DEF_SPRID_MOB + 7 * 8 * 17, 40, true);// Hellbound (Type: 27)
            MakeSprite("Troll", DEF_SPRID_MOB + 7 * 8 * 18, 40, true);// Troll (Type: 28)
            MakeSprite("Orge", DEF_SPRID_MOB + 7 * 8 * 19, 40, true);// Orge (Type: 29)
            MakeSprite("Liche", DEF_SPRID_MOB + 7 * 8 * 20, 40, true);// Liche (Type: 30)
            MakeSprite("Demon", DEF_SPRID_MOB + 7 * 8 * 21, 40, true);// Demon (Type: 31)
            MakeSprite("Unicorn", DEF_SPRID_MOB + 7 * 8 * 22, 40, true);// Unicorn (Type: 32)
            MakeSprite("WereWolf", DEF_SPRID_MOB + 7 * 8 * 23, 40, true);// WereWolf (Type: 33)
            MakeSprite("Dummy", DEF_SPRID_MOB + 7 * 8 * 24, 40, true);// Dummy (Type: 34)
            for (i = 0; i < 40; i++)
                m_pSprite[DEF_SPRID_MOB + i + 7 * 8 * 25] = new CSprite(&m_DDraw, "Effect5", 0, true);
            m_cLoading = 32;
        }
        break;
        case 32:
        {
            MakeSprite("GT-Arrow", DEF_SPRID_MOB + 7 * 8 * 26, 40, true);// Arrow-GuardTower (Type: 36)
            MakeSprite("GT-Cannon", DEF_SPRID_MOB + 7 * 8 * 27, 40, true);// Cannon-GuardTower (Type: 37)
            MakeSprite("ManaCollector", DEF_SPRID_MOB + 7 * 8 * 28, 40, true);// Mana Collector (Type: 38)
            MakeSprite("Detector", DEF_SPRID_MOB + 7 * 8 * 29, 40, true);// Detector (Type: 39)
            MakeSprite("ESG", DEF_SPRID_MOB + 7 * 8 * 30, 40, true);// ESG (Type: 40)
            MakeSprite("GMG", DEF_SPRID_MOB + 7 * 8 * 31, 40, true);// GMG (Type: 41)
            MakeSprite("ManaStone", DEF_SPRID_MOB + 7 * 8 * 32, 40, true);// ManaStone (Type: 42)
            MakeSprite("LWB", DEF_SPRID_MOB + 7 * 8 * 33, 40, true);// Light War Beetle (Type: 43)
            MakeSprite("GHK", DEF_SPRID_MOB + 7 * 8 * 34, 40, true);// God's Hand Knight (Type: 44)
            MakeSprite("GHKABS", DEF_SPRID_MOB + 7 * 8 * 35, 40, true);// God's Hand Knight with Armored Battle Steed (Type: 45)
            MakeSprite("TK", DEF_SPRID_MOB + 7 * 8 * 36, 40, true);// Temple Knight (Type: 46)
            MakeSprite("BG", DEF_SPRID_MOB + 7 * 8 * 37, 40, true);// Battle Golem (Type: 47)
            m_cLoading = 36;
        }
        break;
        case 36:
        {
            MakeSprite("Stalker", DEF_SPRID_MOB + 7 * 8 * 38, 40, true);// Stalker (Type: 48)
            MakeSprite("Hellclaw", DEF_SPRID_MOB + 7 * 8 * 39, 40, true);// Hellclaw (Type: 49)
            MakeSprite("Tigerworm", DEF_SPRID_MOB + 7 * 8 * 40, 40, true);// Tigerworm (Type: 50)
            MakeSprite("Catapult", DEF_SPRID_MOB + 7 * 8 * 41, 40, true);// Catapult (Type: 51)
            MakeSprite("Gagoyle", DEF_SPRID_MOB + 7 * 8 * 42, 40, true);// Gargoyle (Type: 52)
            MakeSprite("Beholder", DEF_SPRID_MOB + 7 * 8 * 43, 40, true);// Beholder (Type: 53)
            MakeSprite("DarkElf", DEF_SPRID_MOB + 7 * 8 * 44, 40, true);// Dark-Elf (Type: 54)
            MakeSprite("Bunny", DEF_SPRID_MOB + 7 * 8 * 45, 40, true);// Bunny (Type: 55)
            MakeSprite("Cat", DEF_SPRID_MOB + 7 * 8 * 46, 40, true);// Cat (Type: 56)
            MakeSprite("GiantFrog", DEF_SPRID_MOB + 7 * 8 * 47, 40, true);// GiantFrog (Type: 57)
            MakeSprite("MTGiant", DEF_SPRID_MOB + 7 * 8 * 48, 40, true);// Mountain Giant (Type: 58)
            m_cLoading = 40;
        }
        break;
        case 40:
        {
            MakeSprite("Ettin", DEF_SPRID_MOB + 7 * 8 * 49, 40, true);// Ettin (Type: 59)
            MakeSprite("CanPlant", DEF_SPRID_MOB + 7 * 8 * 50, 40, true);// Cannibal Plant (Type: 60)
            MakeSprite("Rudolph", DEF_SPRID_MOB + 7 * 8 * 51, 40, true);// Rudolph (Type: 61)
            MakeSprite("DireBoar", DEF_SPRID_MOB + 7 * 8 * 52, 40, true);// Boar (Type: 62)
            MakeSprite("frost", DEF_SPRID_MOB + 7 * 8 * 53, 40, true);// Frost (Type: 63)
            MakeSprite("Crop", DEF_SPRID_MOB + 7 * 8 * 54, 40, true);// Crop(Type: 64)
            MakeSprite("IceGolem", DEF_SPRID_MOB + 7 * 8 * 55, 40, true);// IceGolem (Type: 65)
            MakeSprite("Wyvern", DEF_SPRID_MOB + 7 * 8 * 56, 24, true);// Wyvern (Type: 66)
            MakeSprite("McGaffin", DEF_SPRID_MOB + 7 * 8 * 57, 16, true);// McGaffin (Type: 67)
            MakeSprite("Perry", DEF_SPRID_MOB + 7 * 8 * 58, 16, true);// Perry (Type: 68)
            MakeSprite("Devlin", DEF_SPRID_MOB + 7 * 8 * 59, 16, true);// Devlin (Type: 69)
            MakeSprite("Barlog", DEF_SPRID_MOB + 7 * 8 * 60, 40, true);// Barlog (Type: 70)
            MakeSprite("Centaurus", DEF_SPRID_MOB + 7 * 8 * 61, 40, true);// Centaurus (Type: 71)
            MakeSprite("ClawTurtle", DEF_SPRID_MOB + 7 * 8 * 62, 40, true);// Claw-Turtle (Type: 72)
            MakeSprite("FireWyvern", DEF_SPRID_MOB + 7 * 8 * 63, 24, true);// Fire-Wyvern (Type: 73)
            MakeSprite("GiantCrayfish", DEF_SPRID_MOB + 7 * 8 * 64, 40, true);// Giant-Crayfish (Type: 74)
            MakeSprite("GiantLizard", DEF_SPRID_MOB + 7 * 8 * 65, 40, true);// Giant-Lizard (Type: 75)
            m_cLoading = 44;
        }
        break;
        case 44:
        {
            MakeSprite("GiantPlant", DEF_SPRID_MOB + 7 * 8 * 66, 40, true);// Giant-Plant (Type: 76)
            MakeSprite("MasterMageOrc", DEF_SPRID_MOB + 7 * 8 * 67, 40, true);// MasterMage-Orc (Type: 77)
            MakeSprite("Minotaurs", DEF_SPRID_MOB + 7 * 8 * 68, 40, true);// Minotaurs (Type: 78)
            MakeSprite("Nizie", DEF_SPRID_MOB + 7 * 8 * 69, 40, true);// Nizie (Type: 79)
            MakeSprite("Tentocle", DEF_SPRID_MOB + 7 * 8 * 70, 40, true);// Tentocle (Type: 80)
            MakeSprite("yspro", DEF_SPRID_MOB + 7 * 8 * 71, 32, true);// Abaddon (Type: 81)
            MakeSprite("Sorceress", DEF_SPRID_MOB + 7 * 8 * 72, 40, true);// Sorceress (Type: 82)
            MakeSprite("TPKnight", DEF_SPRID_MOB + 7 * 8 * 73, 40, true);// TPKnight (Type: 83)
            MakeSprite("ElfMaster", DEF_SPRID_MOB + 7 * 8 * 74, 40, true);// ElfMaster (Type: 84)
            MakeSprite("DarkKnight", DEF_SPRID_MOB + 7 * 8 * 75, 40, true);// DarkKnight (Type: 85)
            MakeSprite("HBTank", DEF_SPRID_MOB + 7 * 8 * 76, 32, true);// HeavyBattleTank (Type: 86)
            MakeSprite("CBTurret", DEF_SPRID_MOB + 7 * 8 * 77, 32, true);// CBTurret (Type: 87)
            MakeSprite("Babarian", DEF_SPRID_MOB + 7 * 8 * 78, 40, true);// Babarian (Type: 88)
            MakeSprite("ACannon", DEF_SPRID_MOB + 7 * 8 * 79, 32, true);// ACannon (Type: 89)
            m_cLoading = 48;
        }
        break;
        case 48:
        {
            MakeSprite("Gail", DEF_SPRID_MOB + 7 * 8 * 80, 8, true); // Gail (Type: 90)
            //todo unable to load gate. gate sprite has always been a pain
            //MakeSprite("Gate", DEF_SPRID_MOB + 7 * 8 * 81, 24, true);// Heldenian Gate (Type: 91)/**/

            for (i = 0; i < 32; i++)
                m_pSprite[DEF_SPRID_MOB + i + 7 * 8 * 85] = new CSprite(&m_DDraw, "Effect14", 4, true);
            for (i = 32; i < 40; i++)
                m_pSprite[DEF_SPRID_MOB + i + 7 * 8 * 85] = new CSprite(&m_DDraw, "Effect14", 3, true);
            for (i = 0; i < 40; i++)
                m_pSprite[DEF_SPRID_MOB + i + 7 * 8 * 86] = new CSprite(&m_DDraw, "Effect13", 2, true);
            for (i = 0; i < 40; i++)
                m_pSprite[DEF_SPRID_MOB + i + 7 * 8 * 87] = new CSprite(&m_DDraw, "Effect", 9, true);
            for (i = 0; i < 40; i++)
                m_pSprite[DEF_SPRID_MOB + i + 7 * 8 * 89] = new CSprite(&m_DDraw, "Effect3", 0, true);

            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15 * 0] = new CSprite(&m_DDraw, "Mpt", i + 12 * 0, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15 * 1] = new CSprite(&m_DDraw, "Mpt", i + 12 * 1, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15 * 2] = new CSprite(&m_DDraw, "Mpt", i + 12 * 2, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15 * 3] = new CSprite(&m_DDraw, "Mpt", i + 12 * 3, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15 * 4] = new CSprite(&m_DDraw, "Mpt", i + 12 * 4, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15 * 5] = new CSprite(&m_DDraw, "Mpt", i + 12 * 5, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15 * 6] = new CSprite(&m_DDraw, "Mpt", i + 12 * 6, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_M + i + 15 * 7] = new CSprite(&m_DDraw, "Mpt", i + 12 * 7, true);
            m_cLoading = 52;
        }
        break;

        case 52:
        {
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15 * 0] = new CSprite(&m_DDraw, "Mhr", i + 12 * 0, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15 * 1] = new CSprite(&m_DDraw, "Mhr", i + 12 * 1, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15 * 2] = new CSprite(&m_DDraw, "Mhr", i + 12 * 2, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15 * 3] = new CSprite(&m_DDraw, "Mhr", i + 12 * 3, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15 * 4] = new CSprite(&m_DDraw, "Mhr", i + 12 * 4, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15 * 5] = new CSprite(&m_DDraw, "Mhr", i + 12 * 5, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15 * 6] = new CSprite(&m_DDraw, "Mhr", i + 12 * 6, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_M + i + 15 * 7] = new CSprite(&m_DDraw, "Mhr", i + 12 * 7, true);
            MakeSprite("MLArmor", DEF_SPRID_BODYARMOR_M + 15 * 1, 12, true);
            MakeSprite("MCMail", DEF_SPRID_BODYARMOR_M + 15 * 2, 12, true);
            MakeSprite("MSMail", DEF_SPRID_BODYARMOR_M + 15 * 3, 12, true);
            MakeSprite("MPMail", DEF_SPRID_BODYARMOR_M + 15 * 4, 12, true);
            MakeSprite("Mtunic", DEF_SPRID_BODYARMOR_M + 15 * 5, 12, true);
            MakeSprite("MRobe1", DEF_SPRID_BODYARMOR_M + 15 * 6, 12, true);
            MakeSprite("MSanta", DEF_SPRID_BODYARMOR_M + 15 * 7, 12, true);
            MakeSprite("MHRobe1", DEF_SPRID_BODYARMOR_M + 15 * 10, 12, true); //hero
            MakeSprite("MHRobe2", DEF_SPRID_BODYARMOR_M + 15 * 11, 12, true); //hero
            MakeSprite("MHPMail1", DEF_SPRID_BODYARMOR_M + 15 * 8, 12, true);  //hero
            MakeSprite("MHPMail2", DEF_SPRID_BODYARMOR_M + 15 * 9, 12, true);  //hero

#ifdef DEF_EQUILIBRIUM_PROJECT // armures executor
            MakeSprite("MHRobe3", DEF_SPRID_BODYARMOR_M + 15 * 13, 12, true); //executor
            MakeSprite("WHRobe3", DEF_SPRID_BODYARMOR_W + 15 * 13, 12, true); //executor
            MakeSprite("WHPMail3", DEF_SPRID_BODYARMOR_W + 15 * 14, 12, true); //executor
            MakeSprite("MHPMail3", DEF_SPRID_BODYARMOR_M + 15 * 14, 12, true); //executor

            MakeSprite("MHHelm3", DEF_SPRID_HEAD_M + 15 * 13, 12, true);		//executor
            MakeSprite("WHHelm3", DEF_SPRID_HEAD_W + 15 * 13, 12, true);		//executor

            MakeSprite("MHHauberk3", DEF_SPRID_BERK_M + 15 * 6, 12, true);		//executor			
            MakeSprite("WHHauberk3", DEF_SPRID_BERK_W + 15 * 6, 12, true);		//executor

            MakeSprite("MHLeggings3", DEF_SPRID_LEGG_M + 15 * 8, 12, true);		//executor
            MakeSprite("WHLeggings3", DEF_SPRID_LEGG_W + 15 * 8, 12, true);		//executor
#endif

            MakeSprite("MShirt", DEF_SPRID_BERK_M + 15 * 1, 12, true);
            MakeSprite("MHauberk", DEF_SPRID_BERK_M + 15 * 2, 12, true);
            MakeSprite("MHHauberk1", DEF_SPRID_BERK_M + 15 * 3, 12, true);
            MakeSprite("MHHauberk2", DEF_SPRID_BERK_M + 15 * 4, 12, true);
            m_cLoading = 56;
        }
        break;
        case 56:
        {
            MakeSprite("MTrouser", DEF_SPRID_LEGG_M + 15 * 1, 12, true);
            MakeSprite("MHTrouser", DEF_SPRID_LEGG_M + 15 * 2, 12, true);
            MakeSprite("MCHoses", DEF_SPRID_LEGG_M + 15 * 3, 12, true);
            MakeSprite("MLeggings", DEF_SPRID_LEGG_M + 15 * 4, 12, true);
            MakeSprite("MHLeggings1", DEF_SPRID_LEGG_M + 15 * 5, 12, true); // hero
            MakeSprite("MHLeggings2", DEF_SPRID_LEGG_M + 15 * 6, 12, true); // hero
            MakeSprite("MShoes", DEF_SPRID_BOOT_M + 15 * 1, 12, true);
            MakeSprite("MLBoots", DEF_SPRID_BOOT_M + 15 * 2, 12, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 1] = new CSprite(&m_DDraw, "Msw", i + 56 * 0, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 2] = new CSprite(&m_DDraw, "Msw", i + 56 * 1, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 3] = new CSprite(&m_DDraw, "Msw", i + 56 * 2, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 4] = new CSprite(&m_DDraw, "Msw", i + 56 * 3, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 5] = new CSprite(&m_DDraw, "Msw", i + 56 * 4, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 6] = new CSprite(&m_DDraw, "Msw", i + 56 * 5, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 7] = new CSprite(&m_DDraw, "Msw", i + 56 * 6, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 8] = new CSprite(&m_DDraw, "Msw", i + 56 * 7, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 9] = new CSprite(&m_DDraw, "Msw", i + 56 * 8, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 10] = new CSprite(&m_DDraw, "Msw", i + 56 * 9, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 11] = new CSprite(&m_DDraw, "Msw", i + 56 * 10, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 12] = new CSprite(&m_DDraw, "Msw", i + 56 * 11, true);
            m_cLoading = 60;
        }
        break;
        case 60:
        {
#ifdef DEF_EQUILIBRIUM_PROJECT  // men swd paks
            MakeSprite("Mswx", DEF_SPRID_WEAPON_M + 64 * 9, 56, true);
#else
            MakeSprite("Mswx", DEF_SPRID_WEAPON_M + 64 * 5, 56, true);
#endif
            MakeSprite("Msw2", DEF_SPRID_WEAPON_M + 64 * 13, 56, true);
            MakeSprite("Msw3", DEF_SPRID_WEAPON_M + 64 * 14, 56, true);
            MakeSprite("MStormBringer", DEF_SPRID_WEAPON_M + 64 * 15, 56, true);
            MakeSprite("MDarkExec", DEF_SPRID_WEAPON_M + 64 * 16, 56, true);
            MakeSprite("MKlonessBlade", DEF_SPRID_WEAPON_M + 64 * 17, 56, true);
            MakeSprite("MKlonessAstock", DEF_SPRID_WEAPON_M + 64 * 18, 56, true);
            MakeSprite("MDebastator", DEF_SPRID_WEAPON_M + 64 * 19, 56, true);
            MakeSprite("MAxe1", DEF_SPRID_WEAPON_M + 64 * 20, 56, true);// Axe
            MakeSprite("MAxe2", DEF_SPRID_WEAPON_M + 64 * 21, 56, true);
            MakeSprite("MAxe3", DEF_SPRID_WEAPON_M + 64 * 22, 56, true);
            MakeSprite("MAxe4", DEF_SPRID_WEAPON_M + 64 * 23, 56, true);
            MakeSprite("MAxe5", DEF_SPRID_WEAPON_M + 64 * 24, 56, true);
            MakeSprite("MPickAxe1", DEF_SPRID_WEAPON_M + 64 * 25, 56, true);
            MakeSprite("MAxe6", DEF_SPRID_WEAPON_M + 64 * 26, 56, true);
            MakeSprite("Mhoe", DEF_SPRID_WEAPON_M + 64 * 27, 56, true);
            MakeSprite("MKlonessAxe", DEF_SPRID_WEAPON_M + 64 * 28, 56, true);
            MakeSprite("MLightBlade", DEF_SPRID_WEAPON_M + 64 * 29, 56, true);
            m_cLoading = 64;
        }
        break;
        case 64:
        {
            MakeSprite("MHammer", DEF_SPRID_WEAPON_M + 64 * 30, 56, true);
            MakeSprite("MBHammer", DEF_SPRID_WEAPON_M + 64 * 31, 56, true);
            MakeSprite("MBabHammer", DEF_SPRID_WEAPON_M + 64 * 32, 56, true);
            MakeSprite("MBShadowSword", DEF_SPRID_WEAPON_M + 64 * 33, 56, true);
            MakeSprite("MBerserkWand", DEF_SPRID_WEAPON_M + 64 * 34, 56, true);
            MakeSprite("Mstaff1", DEF_SPRID_WEAPON_M + 64 * 35, 56, true);// Staff
            MakeSprite("Mstaff2", DEF_SPRID_WEAPON_M + 64 * 36, 56, true);
            MakeSprite("MStaff3", DEF_SPRID_WEAPON_M + 64 * 37, 56, true);
            MakeSprite("MReMagicWand", DEF_SPRID_WEAPON_M + 64 * 38, 56, true);
            MakeSprite("MKlonessWand", DEF_SPRID_WEAPON_M + 64 * 39, 56, true);
            // Bows 40 41 below
            MakeSprite("MDirectBow", DEF_SPRID_WEAPON_M + 64 * 42, 56, true);
            MakeSprite("MFireBow", DEF_SPRID_WEAPON_M + 64 * 43, 56, true);
            m_cLoading = 68;
        }
        break;
        case 68:
        {
            MakeSprite("Mbo", DEF_SPRID_WEAPON_M + 64 * 40, 56, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_M + i + 64 * 41] = new CSprite(&m_DDraw, "Mbo", i + 56 * 1, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 1] = new CSprite(&m_DDraw, "Msh", i + 7 * 0, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 2] = new CSprite(&m_DDraw, "Msh", i + 7 * 1, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 3] = new CSprite(&m_DDraw, "Msh", i + 7 * 2, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 4] = new CSprite(&m_DDraw, "Msh", i + 7 * 3, true);
            for (i = 0; i < 7; i++)	m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 5] = new CSprite(&m_DDraw, "Msh", i + 7 * 4, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 6] = new CSprite(&m_DDraw, "Msh", i + 7 * 5, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 7] = new CSprite(&m_DDraw, "Msh", i + 7 * 6, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 8] = new CSprite(&m_DDraw, "Msh", i + 7 * 7, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_M + i + 8 * 9] = new CSprite(&m_DDraw, "Msh", i + 7 * 8, true);
            m_cLoading = 72;
        }
        break;
        case 72:
        {
            MakeSprite("Mmantle01", DEF_SPRID_MANTLE_M + 15 * 1, 12, true);
            MakeSprite("Mmantle02", DEF_SPRID_MANTLE_M + 15 * 2, 12, true);
            MakeSprite("Mmantle03", DEF_SPRID_MANTLE_M + 15 * 3, 12, true);
            MakeSprite("Mmantle04", DEF_SPRID_MANTLE_M + 15 * 4, 12, true);
            MakeSprite("Mmantle05", DEF_SPRID_MANTLE_M + 15 * 5, 12, true);
            MakeSprite("Mmantle06", DEF_SPRID_MANTLE_M + 15 * 6, 12, true);
            MakeSprite("MHelm1", DEF_SPRID_HEAD_M + 15 * 1, 12, true);
            MakeSprite("MHelm2", DEF_SPRID_HEAD_M + 15 * 2, 12, true);
            MakeSprite("MHelm3", DEF_SPRID_HEAD_M + 15 * 3, 12, true);
            MakeSprite("MHelm4", DEF_SPRID_HEAD_M + 15 * 4, 12, true);
            MakeSprite("MHCap1", DEF_SPRID_HEAD_M + 15 * 11, 12, true);
            MakeSprite("MHCap2", DEF_SPRID_HEAD_M + 15 * 12, 12, true);
            MakeSprite("MHHelm1", DEF_SPRID_HEAD_M + 15 * 9, 12, true);
            MakeSprite("MHHelm2", DEF_SPRID_HEAD_M + 15 * 10, 12, true);
            MakeSprite("NMHelm1", DEF_SPRID_HEAD_M + 15 * 5, 12, true);
            MakeSprite("NMHelm2", DEF_SPRID_HEAD_M + 15 * 6, 12, true);
            MakeSprite("NMHelm3", DEF_SPRID_HEAD_M + 15 * 7, 12, true);
            MakeSprite("NMHelm4", DEF_SPRID_HEAD_M + 15 * 8, 12, true);
            m_cLoading = 76;
        }
        break;
        case 76:
        {
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15 * 0] = new CSprite(&m_DDraw, "Wpt", i, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15 * 1] = new CSprite(&m_DDraw, "Wpt", i + 12, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15 * 2] = new CSprite(&m_DDraw, "Wpt", i + 12 * 2, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15 * 3] = new CSprite(&m_DDraw, "Wpt", i + 12 * 3, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15 * 4] = new CSprite(&m_DDraw, "Wpt", i + 12 * 4, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15 * 5] = new CSprite(&m_DDraw, "Wpt", i + 12 * 5, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15 * 6] = new CSprite(&m_DDraw, "Wpt", i + 12 * 6, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_UNDIES_W + i + 15 * 7] = new CSprite(&m_DDraw, "Wpt", i + 12 * 7, true);

            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15 * 0] = new CSprite(&m_DDraw, "Whr", i + 0, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15 * 1] = new CSprite(&m_DDraw, "Whr", i + 12, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15 * 2] = new CSprite(&m_DDraw, "Whr", i + 12 * 2, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15 * 3] = new CSprite(&m_DDraw, "Whr", i + 12 * 3, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15 * 4] = new CSprite(&m_DDraw, "Whr", i + 12 * 4, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15 * 5] = new CSprite(&m_DDraw, "Whr", i + 12 * 5, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15 * 6] = new CSprite(&m_DDraw, "Whr", i + 12 * 6, true);
            for (i = 0; i < 12; i++) m_pSprite[DEF_SPRID_HAIR_W + i + 15 * 7] = new CSprite(&m_DDraw, "Whr", i + 12 * 7, true);
            m_cLoading = 80;
        }
        break;
        case 80:
        {
            MakeSprite("WBodice1", DEF_SPRID_BODYARMOR_W + 15 * 1, 12, true);
            MakeSprite("WBodice2", DEF_SPRID_BODYARMOR_W + 15 * 2, 12, true);
            MakeSprite("WLArmor", DEF_SPRID_BODYARMOR_W + 15 * 3, 12, true);
            MakeSprite("WCMail", DEF_SPRID_BODYARMOR_W + 15 * 4, 12, true);
            MakeSprite("WSMail", DEF_SPRID_BODYARMOR_W + 15 * 5, 12, true);
            MakeSprite("WPMail", DEF_SPRID_BODYARMOR_W + 15 * 6, 12, true);
            MakeSprite("WRobe1", DEF_SPRID_BODYARMOR_W + 15 * 7, 12, true);
            MakeSprite("WSanta", DEF_SPRID_BODYARMOR_W + 15 * 8, 12, true);
            MakeSprite("WHRobe1", DEF_SPRID_BODYARMOR_W + 15 * 11, 12, true); // hero
            MakeSprite("WHRobe2", DEF_SPRID_BODYARMOR_W + 15 * 12, 12, true); // hero
            MakeSprite("WHPMail1", DEF_SPRID_BODYARMOR_W + 15 * 9, 12, true); //hero
            MakeSprite("WHPMail2", DEF_SPRID_BODYARMOR_W + 15 * 10, 12, true); //hero
            MakeSprite("WChemiss", DEF_SPRID_BERK_W + 15 * 1, 12, true);
            MakeSprite("WShirt", DEF_SPRID_BERK_W + 15 * 2, 12, true);
            MakeSprite("WHauberk", DEF_SPRID_BERK_W + 15 * 3, 12, true);
            MakeSprite("WHHauberk1", DEF_SPRID_BERK_W + 15 * 4, 12, true);
            MakeSprite("WHHauberk2", DEF_SPRID_BERK_W + 15 * 5, 12, true);
            MakeSprite("WSkirt", DEF_SPRID_LEGG_W + 15 * 1, 12, true);
            MakeSprite("WTrouser", DEF_SPRID_LEGG_W + 15 * 2, 12, true);
            MakeSprite("WHTrouser", DEF_SPRID_LEGG_W + 15 * 3, 12, true);
            MakeSprite("WHLeggings1", DEF_SPRID_LEGG_W + 15 * 6, 12, true);
            MakeSprite("WHLeggings2", DEF_SPRID_LEGG_W + 15 * 7, 12, true);
            MakeSprite("WCHoses", DEF_SPRID_LEGG_W + 15 * 4, 12, true);
            MakeSprite("WLeggings", DEF_SPRID_LEGG_W + 15 * 5, 12, true);
            MakeSprite("WShoes", DEF_SPRID_BOOT_W + 15 * 1, 12, true);
            MakeSprite("WLBoots", DEF_SPRID_BOOT_W + 15 * 2, 12, true);
            m_cLoading = 84;
        }
        break;
        case 84:
        {
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 1] = new CSprite(&m_DDraw, "Wsw", i + 56 * 0, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 2] = new CSprite(&m_DDraw, "Wsw", i + 56 * 1, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 3] = new CSprite(&m_DDraw, "Wsw", i + 56 * 2, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 4] = new CSprite(&m_DDraw, "Wsw", i + 56 * 3, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 5] = new CSprite(&m_DDraw, "Wsw", i + 56 * 4, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 6] = new CSprite(&m_DDraw, "Wsw", i + 56 * 5, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 7] = new CSprite(&m_DDraw, "Wsw", i + 56 * 6, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 8] = new CSprite(&m_DDraw, "Wsw", i + 56 * 7, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 9] = new CSprite(&m_DDraw, "Wsw", i + 56 * 8, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 10] = new CSprite(&m_DDraw, "Wsw", i + 56 * 9, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 11] = new CSprite(&m_DDraw, "Wsw", i + 56 * 10, true);
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 12] = new CSprite(&m_DDraw, "Wsw", i + 56 * 11, true);

#ifdef DEF_EQUILIBRIUM_PROJECT // Women sword paks
            MakeSprite("Wswx", DEF_SPRID_WEAPON_W + 64 * 9, 56, true);
#else
            MakeSprite("Wswx", DEF_SPRID_WEAPON_W + 64 * 5, 56, true);
#endif
            MakeSprite("Wsw2", DEF_SPRID_WEAPON_W + 64 * 13, 56, true);
            MakeSprite("Wsw3", DEF_SPRID_WEAPON_W + 64 * 14, 56, true); // TheVampire
            MakeSprite("WStormBringer", DEF_SPRID_WEAPON_W + 64 * 15, 56, true);
            MakeSprite("WDarkExec", DEF_SPRID_WEAPON_W + 64 * 16, 56, true);
            MakeSprite("WKlonessBlade", DEF_SPRID_WEAPON_W + 64 * 17, 56, true);
            MakeSprite("WKlonessAstock", DEF_SPRID_WEAPON_W + 64 * 18, 56, true);
            MakeSprite("WDebastator", DEF_SPRID_WEAPON_W + 64 * 19, 56, true);
            m_cLoading = 88;
        }
        break;
        case 88:
        {
            MakeSprite("WAxe1", DEF_SPRID_WEAPON_W + 64 * 20, 56, true);// Axe
            MakeSprite("WAxe2", DEF_SPRID_WEAPON_W + 64 * 21, 56, true);
            MakeSprite("WAxe3", DEF_SPRID_WEAPON_W + 64 * 22, 56, true);
            MakeSprite("WAxe4", DEF_SPRID_WEAPON_W + 64 * 23, 56, true);
            MakeSprite("WAxe5", DEF_SPRID_WEAPON_W + 64 * 24, 56, true);
            MakeSprite("WpickAxe1", DEF_SPRID_WEAPON_W + 64 * 25, 56, true);
            MakeSprite("WAxe6", DEF_SPRID_WEAPON_W + 64 * 26, 56, true);
            MakeSprite("Whoe", DEF_SPRID_WEAPON_W + 64 * 27, 56, true);
            MakeSprite("WKlonessAxe", DEF_SPRID_WEAPON_W + 64 * 28, 56, true);
            MakeSprite("WLightBlade", DEF_SPRID_WEAPON_W + 64 * 29, 56, true);
            MakeSprite("WHammer", DEF_SPRID_WEAPON_W + 64 * 30, 56, true);
            MakeSprite("WBHammer", DEF_SPRID_WEAPON_W + 64 * 31, 56, true);
            MakeSprite("WBabHammer", DEF_SPRID_WEAPON_W + 64 * 32, 56, true);
            MakeSprite("WBShadowSword", DEF_SPRID_WEAPON_W + 64 * 33, 56, true);
            MakeSprite("WBerserkWand", DEF_SPRID_WEAPON_W + 64 * 34, 56, true);
            MakeSprite("Wstaff1", DEF_SPRID_WEAPON_W + 64 * 35, 56, true);// Staff
            MakeSprite("Wstaff2", DEF_SPRID_WEAPON_W + 64 * 36, 56, true);
            MakeSprite("WStaff3", DEF_SPRID_WEAPON_W + 64 * 37, 56, true);
            MakeSprite("WKlonessWand", DEF_SPRID_WEAPON_W + 64 * 39, 56, true);
            MakeSprite("WReMagicWand", DEF_SPRID_WEAPON_W + 64 * 38, 56, true);
            // bows 40 41 below
            MakeSprite("WDirectBow", DEF_SPRID_WEAPON_W + 64 * 42, 56, true);
            MakeSprite("WFireBow", DEF_SPRID_WEAPON_W + 64 * 43, 56, true);
            m_cLoading = 92;
        }
        break;
        case 92:
        {
            MakeSprite("Wmantle01", DEF_SPRID_MANTLE_W + 15 * 1, 12, true);
            MakeSprite("Wmantle02", DEF_SPRID_MANTLE_W + 15 * 2, 12, true);
            MakeSprite("Wmantle03", DEF_SPRID_MANTLE_W + 15 * 3, 12, true);
            MakeSprite("Wmantle04", DEF_SPRID_MANTLE_W + 15 * 4, 12, true);
            MakeSprite("Wmantle05", DEF_SPRID_MANTLE_W + 15 * 5, 12, true);
            MakeSprite("Wmantle06", DEF_SPRID_MANTLE_W + 15 * 6, 12, true);
            MakeSprite("WHelm1", DEF_SPRID_HEAD_W + 15 * 1, 12, true);
            MakeSprite("WHelm4", DEF_SPRID_HEAD_W + 15 * 4, 12, true);
            MakeSprite("WHHelm1", DEF_SPRID_HEAD_W + 15 * 9, 12, true);
            MakeSprite("WHHelm2", DEF_SPRID_HEAD_W + 15 * 10, 12, true);
            MakeSprite("WHCap1", DEF_SPRID_HEAD_W + 15 * 11, 12, true);
            MakeSprite("WHCap2", DEF_SPRID_HEAD_W + 15 * 12, 12, true);
            MakeSprite("NWHelm1", DEF_SPRID_HEAD_W + 15 * 5, 12, true);
            MakeSprite("NWHelm2", DEF_SPRID_HEAD_W + 15 * 6, 12, true);
            MakeSprite("NWHelm3", DEF_SPRID_HEAD_W + 15 * 7, 12, true);
            MakeSprite("NWHelm4", DEF_SPRID_HEAD_W + 15 * 8, 12, true);
            m_cLoading = 96;
        }
        break;
        case 96:
        {
            MakeSprite("Wbo", DEF_SPRID_WEAPON_W + 64 * 40, 56, true);// Bow
            for (i = 0; i < 56; i++) m_pSprite[DEF_SPRID_WEAPON_W + i + 64 * 41] = new CSprite(&m_DDraw, "Wbo", i + 56 * 1, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 1] = new CSprite(&m_DDraw, "Wsh", i + 7 * 0, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 2] = new CSprite(&m_DDraw, "Wsh", i + 7 * 1, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 3] = new CSprite(&m_DDraw, "Wsh", i + 7 * 2, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 4] = new CSprite(&m_DDraw, "Wsh", i + 7 * 3, true);
            for (i = 0; i < 7; i++)	m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 5] = new CSprite(&m_DDraw, "Wsh", i + 7 * 4, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 6] = new CSprite(&m_DDraw, "Wsh", i + 7 * 5, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 7] = new CSprite(&m_DDraw, "Wsh", i + 7 * 6, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 8] = new CSprite(&m_DDraw, "Wsh", i + 7 * 7, true);
            for (i = 0; i < 7; i++) m_pSprite[DEF_SPRID_SHIELD_W + i + 8 * 9] = new CSprite(&m_DDraw, "Wsh", i + 7 * 8, true);
            m_cLoading = 100;
        }
        break;
        case 100:
        {
            MakeEffectSpr("effect", 0, 10, false);
            MakeEffectSpr("effect2", 10, 3, false);
            MakeEffectSpr("effect3", 13, 6, false);
            MakeEffectSpr("effect4", 19, 5, false);
            for (i = 0; i <= 6; i++)
                m_pEffectSpr[i + 24] = new CSprite(&m_DDraw, "effect5", i + 1, false);
            MakeEffectSpr("CruEffect1", 31, 9, false);
            MakeEffectSpr("effect6", 40, 5, false);
            MakeEffectSpr("effect7", 45, 12, false);
            MakeEffectSpr("effect8", 57, 9, false);
            MakeEffectSpr("effect9", 66, 21, false);

            MakeEffectSpr("effect10", 87, 2, false);
            MakeEffectSpr("effect11", 89, 14, false);
            MakeEffectSpr("effect11s", 104, 1, false);

            MakeEffectSpr("effect13", 105, 3, false);
            MakeEffectSpr("effect14", 108, 10, false);


            MakeEffectSpr("yseffect2", 140, 8, false);
            MakeEffectSpr("effect12", 148, 4, false);
            MakeEffectSpr("yseffect3", 152, 16, false);
            MakeEffectSpr("yseffect4", 133, 7, false);


            if (m_bSoundFlag)
            {
                std::string path = {};
                for (i = 1; i <= 24; i++)
                {
                    path = fmt::format("data\\sounds\\C{}.wav", i);
                    CSoundBuffer[i].loadFromFile(path);
                    m_pCSound[i].setBuffer(CSoundBuffer[i]);
                }

                for (i = 1; i <= 156; i++)
                {
                    path = fmt::format("data\\sounds\\M{}.wav", i);
                    MSoundBuffer[i].loadFromFile(path);
                    m_pMSound[i].setBuffer(MSoundBuffer[i]);
                }
                for (i = 1; i <= 53; i++)
                {
                    path = fmt::format("data\\sounds\\E{}.wav", i);
                    ESoundBuffer[i].loadFromFile(path);
                    m_pESound[i].setBuffer(ESoundBuffer[i]);
                }
            }
            ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
        }
        break;
    }
}

void CGame::UpdateScreen_OnLoading_Progress()
{
    //m_DDraw.back_buffer.clear(sf::Color::Black);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOADING, m_DDraw.small_screen_offset_x, m_DDraw.small_screen_offset_y, 0, true);
    m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING]->PutSpriteFastWidth(471 + m_DDraw.small_screen_offset_x, 442  + m_DDraw.small_screen_offset_y, 1, m_cLoading, G_dwGlobalTime);
    //m_DDraw.iFlip();
}

void CGame::UpdateScreen_OnMsg()
{
    short msX, msY, msZ;
    char cLB, cRB;
    uint64_t dwTime = G_dwGlobalTime;
    m_DDraw.back_buffer.clear(sf::Color::Black);
    PutString(10, 10, m_cMsg, Color(255, 155, 155), false, 1);
    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
    if ((G_dwGlobalTime - m_dwTime) > 1500)
    {
        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
    }
}

void CGame::UpdateScreen_OnSelectCharacter()
{
    short sX, sY, msX, msY, msZ;
    char  cLB, cRB, cTotalChar;
    char  cMIresult;
    static class CMouseInterface * pMI;
    uint64_t dwTime;
    static uint64_t dwCTime;

    int iMIbuttonNum;

    dwTime = unixtime();
    sX = 0;
    sY = 0;
    cTotalChar = 0;

    if (m_cGameModeCount == 0)
    {
        //G_cSpriteAlphaDegree = 1;
        InitGameSettings();
        pMI = new class CMouseInterface;
        pMI->AddRect(100, 50, 210, 250);
        pMI->AddRect(211, 50, 321, 250);
        pMI->AddRect(322, 50, 431, 250);
        pMI->AddRect(432, 50, 542, 250);

        pMI->AddRect(360, 283, 545, 315);
        pMI->AddRect(360, 316, 545, 345);
        pMI->AddRect(360, 346, 545, 375);
        pMI->AddRect(360, 376, 545, 405);
        pMI->AddRect(360, 406, 545, 435);

        m_cMaxFocus = 4;
        if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
        if (m_cCurFocus < 1)		   m_cCurFocus = 1;

        m_cArrowPressed = 0;
        m_bEnterPressed = false;

        dwCTime = unixtime();
    }

    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_cArrowPressed != 0)
    {
        switch (m_cArrowPressed)
        {
            case 2:
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                break;
            case 4:
                m_cCurFocus--;
                if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
                break;
        }
        m_cArrowPressed = 0;
    }

    if (m_bEscPressed == true)
    {
        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
        delete pMI;
        m_bEscPressed = false;
        return;
    }

    if (m_bEnterPressed == true)
    {
        m_bEnterPressed = false;
        PlaySound('E', 14, 5);

        if (m_pCharList[m_cCurFocus - 1] != 0)
        {
            if (m_pCharList[m_cCurFocus - 1]->m_sSex != 0)
            {
                ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
                strcpy(m_cPlayerName, m_pCharList[m_cCurFocus - 1]->m_cName);
                m_iLevel = (int)m_pCharList[m_cCurFocus - 1]->m_sLevel;
                if (m_Misc.bCheckValidString(m_cPlayerName) == true)
                {
                    m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->_iCloseSprite();
                    m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->_iCloseSprite();
                    perform_login_connect();
                    ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                    m_dwConnectMode = MSGID_REQUEST_ENTERGAME;
                    m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW;
                    ZeroMemory(m_cMsg, sizeof(m_cMsg));
                    strcpy(m_cMsg, "33");
                    ZeroMemory(m_cMapName, sizeof(m_cMapName));
                    memcpy(m_cMapName, m_pCharList[m_cCurFocus - 1]->m_cMapName, 10);
                    delete pMI;
                    return;
                }
            }
        }
        else
        {
            _InitOnCreateNewCharacter();
            ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
            delete pMI;
            return;
        }
    }

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    UpdateScreen_OnSelectCharacter(sX, sY, msX, msY);

    if ((dwTime - dwCTime) > 100)
    {
        m_cMenuFrame++;
        dwCTime = dwTime;
    }
    if (m_cMenuFrame >= 8)
    {
        m_cMenuDirCnt++;
        if (m_cMenuDirCnt > 8)
        {
            m_cMenuDir++;
            m_cMenuDirCnt = 1;
        }
        m_cMenuFrame = 0;
    }
    if (m_cMenuDir > 8) m_cMenuDir = 1;

    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        PlaySound('E', 14, 5);

        switch (iMIbuttonNum)
        {
            case 1:
            case 2:
            case 3:
            case 4:
                if (m_cCurFocus != iMIbuttonNum)
                    m_cCurFocus = iMIbuttonNum;
                else
                {
                    if (m_pCharList[m_cCurFocus - 1] != 0)
                    {
                        if (m_pCharList[m_cCurFocus - 1]->m_sSex != 0)
                        {
                            ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
                            strcpy(m_cPlayerName, m_pCharList[m_cCurFocus - 1]->m_cName);
                            m_iLevel = (int)m_pCharList[m_cCurFocus - 1]->m_sLevel;
                            if (m_Misc.bCheckValidString(m_cPlayerName) == true)
                            {
                                m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->_iCloseSprite();
                                m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->_iCloseSprite();
                                perform_login_connect();
                                ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                                m_dwConnectMode = MSGID_REQUEST_ENTERGAME;
                                m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW;
                                ZeroMemory(m_cMsg, sizeof(m_cMsg));
                                strcpy(m_cMsg, "33");
                                ZeroMemory(m_cMapName, sizeof(m_cMapName));
                                memcpy(m_cMapName, m_pCharList[m_cCurFocus - 1]->m_cMapName, 10);
                                delete pMI;
                                return;
                            }
                        }
                    }
                    else
                    {
                        _InitOnCreateNewCharacter();
                        ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
                        delete pMI;
                        return;
                    }
                }
                break;

            case 5:
                if (m_pCharList[m_cCurFocus - 1] != 0)
                {
                    if (m_pCharList[m_cCurFocus - 1]->m_sSex != 0)
                    {
                        ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
                        strcpy(m_cPlayerName, m_pCharList[m_cCurFocus - 1]->m_cName);
                        m_iLevel = (int)m_pCharList[m_cCurFocus - 1]->m_sLevel;

                        if (m_Misc.bCheckValidString(m_cPlayerName) == true)
                        {
                            m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->_iCloseSprite();
                            m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->_iCloseSprite();
                            perform_login_connect();
                            ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                            m_dwConnectMode = MSGID_REQUEST_ENTERGAME;
                            m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NEW;
                            ZeroMemory(m_cMsg, sizeof(m_cMsg));
                            strcpy(m_cMsg, "33");
                            ZeroMemory(m_cMapName, sizeof(m_cMapName));
                            memcpy(m_cMapName, m_pCharList[m_cCurFocus - 1]->m_cMapName, 10);
                            delete pMI;
                            return;
                        }
                    }
                }
                break;

            case 6:
                if (m_iTotalChar < 4)
                {
                    _InitOnCreateNewCharacter();
                    ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
                    delete pMI;
                    return;
                }
                break;

            case 7:
                if ((m_pCharList[m_cCurFocus - 1] != 0) && (m_pCharList[m_cCurFocus - 1]->m_sLevel < DEF_MAX_DELETE_LEVEL))
                {
                    ChangeGameMode(DEF_GAMEMODE_ONQUERYDELETECHARACTER);
                    m_wEnterGameType = m_cCurFocus;
                    delete pMI;
                    return;
                }
                break;

            case 8:
                ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD);
                delete pMI;
                return;

            case 9:
                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                delete pMI;
                return;
        }
    }

    //	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
    //	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);
}


void CGame::UpdateScreen_OnConnecting()
{
    short sX, sY, msX, msY, msZ;
    char cLB, cRB;
    uint64_t dwTime = unixtime();
    static class CMouseInterface * pMI;
    static uint64_t dwMTime, dwCTime;

    if (m_cGameModeCount == 0)
    {
        m_bEnterPressed = false;
        m_bEscPressed = false;
        dwCTime = dwMTime = unixtime();
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_bEscPressed == true)
    {

        if ((dwTime - m_dwTime) > 1000)
        {
            ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
            if (log_ws)
                log_ws = nullptr;
            if (ws)
                ws = nullptr;
        }
        m_bEscPressed = false;
        return;
    }

    if ((dwTime - dwMTime) > 150) dwMTime = dwTime;

    if ((dwTime - dwCTime) > 100)
    {
        m_cMenuFrame++;
        dwCTime = dwTime;
    }
    if (m_cMenuFrame >= 8)
    {
        m_cMenuDirCnt++;
        if (m_cMenuDirCnt > 8)
        {
            m_cMenuDir++;
            m_cMenuDirCnt = 1;
        }
        m_cMenuFrame = 0;
    }
    if (m_cMenuDir > 8) m_cMenuDir = 1;

    m_DDraw.back_buffer.clear(sf::Color::Black);

    m_bIsHideLocalCursor = true;
    switch (m_cMsg[0])
    {
        case '0':
            _Draw_UpdateScreen_OnCreateNewAccount();
            break;

        case '1':
            sX = 146;
            sY = 114;
            _Draw_OnLogin(m_cAccountName, m_cAccountPassword, 0, 0);
            break;

        case '2':
            _bDraw_OnCreateNewCharacter(m_cPlayerName, 0, 0, 0);
            break;

        case '3':
            UpdateScreen_OnSelectCharacter(0, 0, 0, 0);
            break;

        case '4':
            // Change Password
            UpdateScreen_OnSelectCharacter(0, 0, 0, 0, true);
            break;

        case '5':
            m_DDraw.back_buffer.clear(sf::Color::Black);
            break;
    }
    m_bIsHideLocalCursor = false;

    m_DDraw.DrawShadowBox(0, 0, 639, 479);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 125, 2);
    wsprintfA(G_cTxt, "Connecting to Server... %3dSec", (dwTime - m_dwTime) / 1000);
    PutString_SprFont(172 + 35, 190, G_cTxt, 7, 0, 0);

    if ((dwTime - m_dwTime) > 7000)
    {
        PutAlignedString(180, 463, 195 + 30, UPDATE_SCREEN_ON_CONNECTING1);//"Press ESC key during long time of no"
        PutAlignedString(180, 463, 195 + 45, UPDATE_SCREEN_ON_CONNECTING2);//"connection and return to the main menu."
    }
    else PutAlignedString(180, 463, 195 + 30, UPDATE_SCREEN_ON_CONNECTING3);//"  Connecting to server. Please wait..."
    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 8, dwTime);
}

void CGame::UpdateScreen_OnWaitInitData()
{
    short msX, msY, msZ;
    char cLB, cRB;
    uint64_t dwTime = unixtime();

    if (m_cGameModeCount == 0)
    {
        m_bEnterPressed = false;
        m_bEscPressed = false;
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_bEscPressed == true)
    {
        if ((dwTime - m_dwTime) > 7000)
        {
            ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
            if (log_ws)
                log_ws = nullptr;
            if (ws)
                ws = nullptr;
        }
        m_bEscPressed = false;
        return;
    }

    m_DDraw.back_buffer.clear(sf::Color::Black);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 125, 2);

    wsprintfA(G_cTxt, "Waiting for response... %dsec", (dwTime - m_dwTime) / 1000);
    PutString_SprFont(172 + 44, 190, G_cTxt, 7, 0, 0);
    if ((dwTime - m_dwTime) > 7000)
    {
        PutAlignedString(174, 467, 190 + 30, UPDATE_SCREEN_ON_WAIT_INIT_DATA1);//"Press ESC key during long time of no"
        PutAlignedString(174, 467, 190 + 45, UPDATE_SCREEN_ON_WAIT_INIT_DATA2);//"connection and return to the main menu."
    }
    else PutAlignedString(174, 467, 195 + 30, UPDATE_SCREEN_ON_WAIT_INIT_DATA3);//  Connecting to server. Please wait..."

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 8, dwTime);
}

void CGame::UpdateScreen_OnConnectionLost()
{
    short msX, msY, msZ;
    char cLB, cRB;
    static uint64_t dwTime;
    if (m_cGameModeCount == 0)
    {
        dwTime = unixtime();
        if (m_bSoundFlag) m_pESound[38].stop();
        if ((m_bSoundFlag) && (m_bMusicStat == true))
        {
            m_pBGM.stop();
        }
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;
    m_DDraw.back_buffer.clear(sf::Color::Black);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 125, 2);
    PutString_SprFont(172 + 54, 180, "Connection Lost!", 7, 0, 0);
    PutString(172 + 50, 180 + 30, UPDATE_SCREEN_ON_CONNECTION_LOST, Color(0, 0, 0));//"
    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

    if ((unixtime() - m_dwTime) > 5000)
    {
        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
    }
}


bool CGame::_bDraw_OnCreateNewCharacter(char * pName, short msX, short msY, int iPoint)
{
    bool bFlag = true;
    uint64_t dwTime = unixtime();
    int i = 0;

    m_DDraw.back_buffer.clear(sf::Color::Black);

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_NEWCHAR, 0, 0, 0, true);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 69, true);
    PutAlignedString(64, 282, 90, _BDRAW_ON_CREATE_NEW_CHARACTER1, 5, 5, 5);//"
    PutAlignedString(57, 191, 110, DEF_MSG_CHARACTERNAME, 5, 5, 5);//"Character Name"
    if (m_cCurFocus != 1) PutString(197, 112, pName, Color(25, 35, 25));
    PutAlignedString(64, 282, 140, _BDRAW_ON_CREATE_NEW_CHARACTER2, 5, 5, 5);//"
    PutString(100, 160, DEF_MSG_GENDER, Color(5, 5, 5));//"Gender"
    PutString(100, 175, DEF_MSG_SKINCOLOR, Color(5, 5, 5));//"Skin Color"
    PutString(100, 190, DEF_MSG_HAIRSTYLE, Color(5, 5, 5));//"Hair Style"
    PutString(100, 205, DEF_MSG_HAIRCOLOR, Color(5, 5, 5));//"Hair Color"
    PutString(100, 220, DEF_MSG_UNDERWEARCOLOR, Color(5, 5, 5));//"Underwear Color"
    //PutAlignedString(64, 282, 245, _BDRAW_ON_CREATE_NEW_CHARACTER3, 5,5,5);
    //wsprintfA(G_cTxt, _BDRAW_ON_CREATE_NEW_CHARACTER4,  iPoint);//" %d points"
    //PutAlignedString(64, 282, 260, G_cTxt, 15,10,10);
    PutString(100, 275, DEF_MSG_STRENGTH, Color(5, 5, 5));//"Strength"
    PutString(100, 292, DEF_MSG_VITALITY, Color(5, 5, 5));//"Vitality"
    PutString(100, 309, DEF_MSG_DEXTERITY, Color(5, 5, 5));//"Dexterity"
    PutString(100, 326, DEF_MSG_INTELLIGENCE, Color(5, 5, 5));//"Intelligence"
    PutString(100, 343, DEF_MSG_MAGIC, Color(5, 5, 5));//"Magic"
    PutString(100, 360, DEF_MSG_CHARISMA, Color(5, 5, 5));//"Charisma"

    wsprintfA(G_cTxt, "%d", m_ccStr);
    PutString(204, 277 + 16 * i++, G_cTxt, Color(25, 35, 25));
    wsprintfA(G_cTxt, "%d", m_ccVit);
    PutString(204, 277 + 16 * i++, G_cTxt, Color(25, 35, 25));
    wsprintfA(G_cTxt, "%d", m_ccDex);
    PutString(204, 277 + 16 * i++, G_cTxt, Color(25, 35, 25));
    wsprintfA(G_cTxt, "%d", m_ccInt);
    PutString(204, 277 + 16 * i++, G_cTxt, Color(25, 35, 25));
    wsprintfA(G_cTxt, "%d", m_ccMag);
    PutString(204, 277 + 16 * i++, G_cTxt, Color(25, 35, 25));
    wsprintfA(G_cTxt, "%d", m_ccChr);
    PutString(204, 277 + 16 * i++, G_cTxt, Color(25, 35, 25));

    if (strlen(pName) <= 0) bFlag = false;
    if (iPoint > 0) bFlag = false;
    if (m_Misc.bCheckValidName(pName) == false) bFlag = false;
    if (_bCheckBadWords(pName) == true) bFlag = false;

    if ((bFlag == true) && (m_cCurFocus == 2)) m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(384, 445, 25, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(384, 445, 24, dwTime);
    if (m_cCurFocus == 3)
        m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(500, 445, 17, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(500, 445, 16, dwTime);
    if (m_cCurFocus == 4)
        m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(60, 445, 68, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(60, 445, 67, dwTime);
    if (m_cCurFocus == 5)
        m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(145, 445, 66, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(145, 445, 65, dwTime);
    if (m_cCurFocus == 6)
        m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(230, 445, 64, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(230, 445, 63, dwTime);
    /*if (m_cCurFocus == 4)
         m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(60, 245, 68, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(60, 245, 67, dwTime);
    if (m_cCurFocus == 5)
         m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(145, 245, 66, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(145, 245, 65, dwTime);
    if (m_cCurFocus == 6)
         m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(230, 245, 64, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(230, 245, 63, dwTime);*/

    ShowReceivedString();

    switch (m_cGender)
    {
        case 1:	_tmp_sOwnerType = 1; break;
        case 2:	_tmp_sOwnerType = 4; break; //@@@@@@@@@@@@@@@@@!!!!!!!!!!!!!!!!!
    }
    _tmp_sOwnerType += m_cSkinCol - 1;
    _tmp_cDir = m_cMenuDir;
    _tmp_sAppr1 = 0;
    _tmp_sAppr1 = _tmp_sAppr1 | (m_cUnderCol);
    _tmp_sAppr1 = _tmp_sAppr1 | (m_cHairStyle << 8);
    _tmp_sAppr1 = _tmp_sAppr1 | (m_cHairCol << 4);
    _tmp_sAppr2 = 0;
    _tmp_sAppr3 = 0;
    _tmp_sAppr4 = 0;
    ZeroMemory(_tmp_cName, sizeof(_tmp_cName));
    memcpy(_tmp_cName, m_cPlayerName, 10);
    _tmp_cAction = DEF_OBJECTMOVE;
    _tmp_cFrame = m_cMenuFrame;

    _Draw_CharacterBody(507, 267, _tmp_sOwnerType);

    DrawObject_OnMove_ForMenu(0, 0, 500, 174, false, dwTime, msX, msY);

    i = 0;

    PutString(445, 192, DEF_MSG_HITPOINT, Color(5, 5, 5));//"Hit Point"
    wsprintfA(G_cTxt, "%d", m_ccVit * 3 + 2 + m_ccStr / 2);
    PutString(550, 192 + 16 * i++, G_cTxt, Color(25, 35, 25));

    PutString(445, 208, DEF_MSG_MANAPOINT, Color(5, 5, 5));//"Mana Point"
    wsprintfA(G_cTxt, "%d", m_ccMag * 2 + 2 + m_ccInt / 2);
    PutString(550, 192 + 16 * i++, G_cTxt, Color(25, 35, 25));

    PutString(445, 224, DEF_MSG_STAMINARPOINT, Color(5, 5, 5));//"Staminar Point"
    wsprintfA(G_cTxt, "%d", m_ccStr * 2 + 2);
    PutString(550, 192 + 16 * i++, G_cTxt, Color(25, 35, 25));

    return bFlag;
}

void CGame::UpdateScreen_OnCreateNewCharacter()
{
    static class CMouseInterface * pMI;
    int i = 0;
    int iMIbuttonNum;
    static int iPoint;
    char cLB, cRB, cMIresult;
    static char cName[12];
    static char cPrevFocus;
    short msX, msY, msZ;
    bool bFlag;
    static uint64_t dwMTime;
    uint64_t dwTime = unixtime();

    if (m_cGameModeCount == 0)
    {
        pMI = new class CMouseInterface;
        pMI->AddRect(65 + 4, 65 + 45, 275 + 4, 82 + 45);

        pMI->AddRect(232 + 4, 111 + 45, 274 + 4 - 21, 124 + 45);
        pMI->AddRect(255 + 4, 111 + 45, 289 + 4 - 13, 124 + 45);

        pMI->AddRect(232 + 4, 126 + 45, 274 + 4 - 21, 139 + 45);
        pMI->AddRect(255 + 4, 126 + 45, 289 + 4 - 13, 139 + 45);

        pMI->AddRect(232 + 4, 141 + 45, 274 + 4 - 21, 154 + 45);
        pMI->AddRect(255 + 4, 141 + 45, 289 + 4 - 13, 154 + 45);

        pMI->AddRect(232 + 4, 156 + 45, 274 + 4 - 21, 169 + 45);
        pMI->AddRect(255 + 4, 156 + 45, 289 + 4 - 13, 169 + 45);

        pMI->AddRect(232 + 4, 171 + 45, 274 + 4 - 21, 184 + 45);
        pMI->AddRect(255 + 4, 171 + 45, 289 + 4 - 13, 184 + 45);


        pMI->AddRect(232 + 4, 231 + 45, 253 + 4, 244 + 45);
        pMI->AddRect(255 + 4, 231 + 45, 276 + 4, 244 + 45);

        pMI->AddRect(232 + 4, 246 + 45, 253 + 4, 259 + 45);
        pMI->AddRect(255 + 4, 246 + 45, 276 + 4, 259 + 45);

        pMI->AddRect(232 + 4, 261 + 45, 253 + 4, 274 + 45);
        pMI->AddRect(255 + 4, 261 + 45, 276 + 4, 274 + 45);

        pMI->AddRect(232 + 4, 276 + 45, 253 + 4, 289 + 45);
        pMI->AddRect(255 + 4, 276 + 45, 276 + 4, 289 + 45);

        pMI->AddRect(232 + 4, 291 + 45, 253 + 4, 304 + 45);
        pMI->AddRect(255 + 4, 291 + 45, 276 + 4, 304 + 45);

        pMI->AddRect(232 + 4, 306 + 45, 253 + 4, 319 + 45);
        pMI->AddRect(255 + 4, 306 + 45, 276 + 4, 319 + 45);

        pMI->AddRect(384, 445, 384 + 72, 445 + 15);
        pMI->AddRect(500, 445, 500 + 72, 445 + 15);

        pMI->AddRect(60, 445, 60 + 72, 445 + 15);
        pMI->AddRect(145, 445, 145 + 72, 445 + 15);
        pMI->AddRect(230, 445, 230 + 72, 445 + 15);

        iPoint = m_ccStr + m_ccVit + m_ccDex + m_ccInt + m_ccMag + m_ccChr;
        iPoint = 70 - iPoint;
        cPrevFocus = 1;
        m_cCurFocus = 1;
        m_cMaxFocus = 6;
        m_bEnterPressed = false;
        m_cArrowPressed = 0;
        dwMTime = unixtime();
        StartInputString(193 + 4, 65 + 45, 11, cName);
        ClearInputString();
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_cArrowPressed != 0)
    {
        switch (m_cArrowPressed)
        {
            case 1:
                m_cCurFocus--;
                if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
                break;

            case 3:
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                break;
        }
        m_cArrowPressed = 0;
    }

    if (cPrevFocus != m_cCurFocus)
    {
        EndInputString();
        switch (m_cCurFocus)
        {
            case 1:
                StartInputString(193 + 4, 65 + 45, 11, cName);
                break;
        }
        cPrevFocus = m_cCurFocus;
    }

    if (m_bEscPressed == true)
    {
        ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
        delete pMI;
        m_bEscPressed = false;
        return;
    }

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    bFlag = _bDraw_OnCreateNewCharacter(cName, msX, msY, iPoint);

    if ((dwTime - dwMTime) > 100)
    {
        m_cMenuFrame++;
        dwMTime = dwTime;
    }
    if (m_cMenuFrame >= 8)
    {
        m_cMenuDirCnt++;
        if (m_cMenuDirCnt > 8)
        {
            m_cMenuDir++;
            m_cMenuDirCnt = 1;
        }
        m_cMenuFrame = 0;
    }
    if (m_cMenuDir > 8) m_cMenuDir = 1;

    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        PlaySound('E', 14, 5);
        switch (iMIbuttonNum)
        {
            case 1:
                m_cCurFocus = 1;
                break;
            case 2:
                m_cGender--;
                if (m_cGender < 1) m_cGender = 2;
                break;
            case 3:
                m_cGender++;
                if (m_cGender > 2) m_cGender = 1;
                break;
            case 4:
                m_cSkinCol--;
                if (m_cSkinCol < 1) m_cSkinCol = 3;
                break;
            case 5:
                m_cSkinCol++;
                if (m_cSkinCol > 3) m_cSkinCol = 1;
                break;
            case 6:
                m_cHairStyle--;
                if (m_cHairStyle < 0) m_cHairStyle = 7;
                break;
            case 7:
                m_cHairStyle++;
                if (m_cHairStyle > 7) m_cHairStyle = 0;
                break;
            case 8:
                m_cHairCol--;
                if (m_cHairCol < 0) m_cHairCol = 15;
                break;
            case 9:
                m_cHairCol++;
                if (m_cHairCol > 15) m_cHairCol = 0;
                break;
            case 10:
                m_cUnderCol--;
                if (m_cUnderCol < 0) m_cUnderCol = 7;
                break;
            case 11:
                m_cUnderCol++;
                if (m_cUnderCol > 7) m_cUnderCol = 0;
                break;
            case 12:
                if (iPoint > 0)
                {
                    if (m_ccStr < 14)
                    {
                        m_ccStr++;
                        iPoint--;
                    }
                }
                break;
            case 13:
                if (m_ccStr > 10)
                {
                    m_ccStr--;
                    iPoint++;
                }
                break;
            case 14:
                if (iPoint > 0)
                {
                    if (m_ccVit < 14)
                    {
                        m_ccVit++;
                        iPoint--;
                    }
                }
                break;
            case 15:
                if (m_ccVit > 10)
                {
                    m_ccVit--;
                    iPoint++;
                }
                break;
            case 16:
                if (iPoint > 0)
                {
                    if (m_ccDex < 14)
                    {
                        m_ccDex++;
                        iPoint--;
                    }
                }
                break;
            case 17:
                if (m_ccDex > 10)
                {
                    m_ccDex--;
                    iPoint++;
                }
                break;
            case 18:
                if (iPoint > 0)
                {
                    if (m_ccInt < 14)
                    {
                        m_ccInt++;
                        iPoint--;
                    }
                }
                break;
            case 19:
                if (m_ccInt > 10)
                {
                    m_ccInt--;
                    iPoint++;
                }
                break;
            case 20:
                if (iPoint > 0)
                {
                    if (m_ccMag < 14)
                    {
                        m_ccMag++;
                        iPoint--;
                    }
                }
                break;
            case 21:
                if (m_ccMag > 10)
                {
                    m_ccMag--;
                    iPoint++;
                }
                break;
            case 22:
                if (iPoint > 0)
                {
                    if (m_ccChr < 14)
                    {
                        m_ccChr++;
                        iPoint--;
                    }
                }
                break;
            case 23:
                if (m_ccChr > 10)
                {
                    m_ccChr--;
                    iPoint++;
                }
                break;

            case 24:
                if (m_cCurFocus != 2)
                {
                    m_cCurFocus = 2;
                    return;
                }
                if (bFlag == false) return;
                //if (m_Misc.bCheckValidName(m_cPlayerName) == false) break;
                if (m_Misc.bCheckValidName(cName) == false) break;
                ZeroMemory(m_cPlayerName, sizeof(m_cPlayerName));
                strcpy(m_cPlayerName, cName);
                perform_login_connect();
                ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                m_dwConnectMode = MSGID_REQUEST_CREATENEWCHARACTER;
                ZeroMemory(m_cMsg, sizeof(m_cMsg));
                strcpy(m_cMsg, "22");
                delete pMI;
                return;


            case 25:
                if (m_cCurFocus != 3)
                {
                    m_cCurFocus = 3;
                    return;
                }
                ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                delete pMI;
                return;


            case 26: // WARRIOR
                if (m_cCurFocus != 4)
                {
                    m_cCurFocus = 4;
                    return;
                }

                m_ccMag = 10;
                m_ccInt = 10;
                m_ccChr = 10;
                m_ccStr = 14;
                m_ccVit = 12;
                m_ccDex = 14;
                iPoint = m_ccStr + m_ccVit + m_ccDex + m_ccInt + m_ccMag + m_ccChr;
                iPoint = 70 - iPoint;
                break;

            case 27: // MAGE
                if (m_cCurFocus != 5)
                {
                    m_cCurFocus = 5;
                    return;
                }

                m_ccMag = 14;
                m_ccInt = 14;
                m_ccChr = 10;
                m_ccStr = 10;
                m_ccVit = 12;
                m_ccDex = 10;
                iPoint = m_ccStr + m_ccVit + m_ccDex + m_ccInt + m_ccMag + m_ccChr;
                iPoint = 70 - iPoint;
                break;

            case 28: // PRIEST
                if (m_cCurFocus != 6)
                {
                    m_cCurFocus = 6;
                    return;
                }

                m_ccMag = 12;
                m_ccInt = 10;
                m_ccChr = 14;
                m_ccStr = 14;
                m_ccVit = 10;
                m_ccDex = 10;
                iPoint = m_ccStr + m_ccVit + m_ccDex + m_ccInt + m_ccMag + m_ccChr;
                iPoint = 70 - iPoint;
                break;
        }


    }

    if ((msX >= 65 + 4 - 127) && (msX <= 275 + 4) && (msY >= 65 + 45) && (msY <= 82 + 45))
    {
        PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER1);
    }
    else
        if ((msX >= 261 + 4 - 212) && (msX <= 289 + 4) && (msY >= 111 + 45) && (msY <= 124 + 45))
        {
            PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER2);
        }
        else
            if ((msX >= 261 + 4 - 212) && (msX <= 289 + 4) && (msY >= 126 + 45) && (msY <= 139 + 45))
            {
                PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER3);
            }
            else
                if ((msX >= 261 + 4 - 212) && (msX <= 289 + 4) && (msY >= 141 + 45) && (msY <= 154 + 45))
                {
                    PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER4);
                }
                else
                    if ((msX >= 261 + 4 - 212) && (msX <= 289 + 4) && (msY >= 156 + 45) && (msY <= 169 + 45))
                    {
                        PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER5);
                    }
                    else
                        if ((msX >= 261 + 4 - 212) && (msX <= 289 + 4) && (msY >= 171 + 45) && (msY <= 184 + 45))
                        {
                            PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER6);
                        }
                        else
                            if ((msX >= 240 + 4 - 175) && (msX <= 268 + 4) && (msY >= 231 + 45) && (msY <= 244 + 45))
                            {
                                // Str
                                i = 0;
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER7);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER8);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER9);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER10);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER11);
                            }
                            else if ((msX >= 240 + 4 - 175) && (msX <= 268 + 4) && (msY >= 246 + 45) && (msY <= 259 + 45))
                            {
                                // Vit
                                i = 0;
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER12);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER13);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER14);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER15);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER16);//"
                            }
                            else if ((msX >= 240 + 4 - 175) && (msX <= 268 + 4) && (msY >= 261 + 45) && (msY <= 274 + 45))
                            {
                                // Dex
                                i = 0;
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER17);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER18);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER19);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER20);//"
                            }
                            else if ((msX >= 240 + 4 - 175) && (msX <= 268 + 4) && (msY >= 276 + 45) && (msY <= 289 + 45))
                            {
                                // Int
                                i = 0;
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER21);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER22);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER23);//"
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER24);
                            }
                            else if ((msX >= 240 + 4 - 175) && (msX <= 268 + 4) && (msY >= 291 + 45) && (msY <= 304 + 45))
                            {
                                // Mag
                                i = 0;
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER25);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER26);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER27);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER28);
                            }
                            else if ((msX >= 240 + 4 - 175) && (msX <= 268 + 4) && (msY >= 306 + 45) && (msY <= 319 + 45))
                            {
                                // Charisma
                                i = 0;
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER29);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER30);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER31);
                                PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER32);
                            }
                            else if ((msX >= 384) && (msX <= 384 + 72) && (msY >= 445) && (msY <= 445 + 15))
                            {
                                m_cCurFocus = 2;
                                if (strlen(cName) <= 0)
                                {
                                    i = 0;
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER35);//"Please enter a character name."
                                }
                                else if (iPoint > 0)
                                {
                                    i = 0;
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER36);//"You need to select your character class."
                                }
                                else if (m_Misc.bCheckValidName(cName) == false)
                                {
                                    i = 0;
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER39);//"Cannot use special characters "
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER40);//"in your character's name. Please"
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER41);//"type another name."
                                }
                                else if (_bCheckBadWords(cName) == true)
                                {
                                    i = 0;
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER42);//"The character's name is not appropriate."
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER43);//"Please retry with another name."
                                }
                                else
                                {
                                    i = 0;
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER44);//"
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER45);//"
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER46);//"
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER47);//"
                                    PutAlignedString(370, 580, 345 + 16 * i++, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER48);//"
                                }
                            }
                            else if ((msX >= 500) && (msX <= 500 + 72) && (msY >= 445) && (msY <= 445 + 15))
                            {
                                m_cCurFocus = 3;
                                PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER49);
                            }

    if ((msX >= 60) && (msX <= 60 + 72) && (msY >= 445) && (msY <= 445 + 15))
    {
        m_cCurFocus = 4;
        PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER50);
    }

    if ((msX >= 145) && (msX <= 145 + 72) && (msY >= 445) && (msY <= 445 + 15))
    {
        m_cCurFocus = 5;
        PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER51);
    }

    if ((msX >= 230) && (msX <= 230 + 72) && (msY >= 445) && (msY <= 445 + 15))
    {
        m_cCurFocus = 6;
        PutAlignedString(370, 580, 345, UPDATE_SCREEN_ON_CREATE_NEW_CHARACTER52);
    }

    //	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
    //	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);
}


void CGame::UpdateScreen_OnLogin()
{
    short msX, msY, msZ, sX, sY;
    char cLB, cRB;
    char cMIresult;
    int  iMIbuttonNum;
    static class CMouseInterface * pMI;
    static char  cPassword[12], cPrevFocus;
    static char cName[12];
    sX = 146;
    sY = 114;
    if (m_cGameModeCount == 0)
    {
        EndInputString();
        pMI = new class CMouseInterface;
        pMI->AddRect(80 + m_DDraw.small_screen_offset_x, 151 + m_DDraw.small_screen_offset_y, 337 + m_DDraw.small_screen_offset_x, 179 + m_DDraw.small_screen_offset_y);
        pMI->AddRect(80 + m_DDraw.small_screen_offset_x, 180 + m_DDraw.small_screen_offset_y, 337 + m_DDraw.small_screen_offset_x, 205 + m_DDraw.small_screen_offset_y);
        pMI->AddRect(80 + m_DDraw.small_screen_offset_x, 280 + m_DDraw.small_screen_offset_y, 163 + m_DDraw.small_screen_offset_x, 302 + m_DDraw.small_screen_offset_y);
        pMI->AddRect(258 + m_DDraw.small_screen_offset_x, 280 + m_DDraw.small_screen_offset_y, 327 + m_DDraw.small_screen_offset_x, 302 + m_DDraw.small_screen_offset_y);
        cPrevFocus = 1;
        m_cCurFocus = 1;
        m_cMaxFocus = 4;
        m_bEnterPressed = false;
        m_cArrowPressed = 0;
        ZeroMemory(cName, sizeof(cName));
        ZeroMemory(cPassword, sizeof(cPassword));
        StartInputString(180 + m_DDraw.small_screen_offset_x, 162 + m_DDraw.small_screen_offset_y, 11, cName);
        ClearInputString();
    }

    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_cArrowPressed != 0)
    {
        switch (m_cArrowPressed)
        {
            case 1:
                m_cCurFocus--;
                if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
                break;

            case 2:
                if (m_cCurFocus == 3) m_cCurFocus = 4;
                else if (m_cCurFocus == 4) m_cCurFocus = 3;
                break;

            case 3:
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                break;

            case 4:
                if (m_cCurFocus == 3) m_cCurFocus = 4;
                else if (m_cCurFocus == 4) m_cCurFocus = 3;
                break;
        }
        m_cArrowPressed = 0;
    }

    if (m_bEnterPressed == true)
    {
        m_bEnterPressed = false;
        PlaySound('E', 14, 5);

        switch (m_cCurFocus)
        {
            case 1:
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                break;
            case 2:
            case 3:
                if ((strlen(cName) == 0) || (strlen(cPassword) == 0)) break;
                ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
                ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
                strcpy(m_cAccountName, cName);
                strcpy(m_cAccountPassword, cPassword);
                perform_login_connect();
                ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                m_dwConnectMode = MSGID_REQUEST_LOGIN;
                ZeroMemory(m_cMsg, sizeof(m_cMsg));
                strcpy(m_cMsg, "11");
                delete pMI;
                return;
            case 4:	// Cancel
#ifdef DEF_SELECTSERVER
                ChangeGameMode(DEF_GAMEMODE_ONSELECTSERVER);
#else
                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
#endif
                delete pMI;
                return;
        }
    }

    if (m_bEscPressed == true)
    {
        EndInputString();
        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
        delete pMI;
        m_bEscPressed = false;
        return;
    }

    if (cPrevFocus != m_cCurFocus)
    {
        EndInputString();
        switch (m_cCurFocus)
        {
            case 1:
                StartInputString(180 + m_DDraw.small_screen_offset_x, 162 + m_DDraw.small_screen_offset_y, 11, cName);
                break;
            case 2:
                StartInputString(180 + m_DDraw.small_screen_offset_x, 185 + m_DDraw.small_screen_offset_y, 11, cPassword, true);
                break;
            case 3:
            case 4:
                break;
        }
        cPrevFocus = m_cCurFocus;
    }


    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        PlaySound('E', 14, 5);
        switch (iMIbuttonNum)
        {
            case 1:
                m_cCurFocus = 1;
                break;

            case 2:
                m_cCurFocus = 2;
                break;

            case 3:
                if ((strlen(cName) == 0) || (strlen(cPassword) == 0)) break;
                EndInputString();
                ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
                ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
                strcpy(m_cAccountName, cName);
                strcpy(m_cAccountPassword, cPassword);
                perform_login_connect();
                ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                m_dwConnectMode = MSGID_REQUEST_LOGIN;
                ZeroMemory(m_cMsg, sizeof(m_cMsg));
                strcpy(m_cMsg, "11");
                delete pMI;
                return;

            case 4:
#ifdef DEF_SELECTSERVER
                ChangeGameMode(DEF_GAMEMODE_ONSELECTSERVER); // ONMAINMENU
#else
                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
#endif
                delete pMI;
                return;
        }
    }

    if ((msX >= 80 + m_DDraw.small_screen_offset_x) && (msX <= 163 + m_DDraw.small_screen_offset_x) && (msY >= 280 + m_DDraw.small_screen_offset_y) && (msY <= 302 + m_DDraw.small_screen_offset_y)) m_cCurFocus = 3;
    if ((msX >= 258 + m_DDraw.small_screen_offset_x) && (msX <= 327 + m_DDraw.small_screen_offset_x) && (msY >= 280 + m_DDraw.small_screen_offset_y) && (msY <= 302 + m_DDraw.small_screen_offset_y)) m_cCurFocus = 4;

    _Draw_OnLogin(cName, cPassword, msX, msY, m_cGameModeCount);
}

void CGame::UpdateScreen_OnSelectServer()
{
    short msX, msY, msZ, sX, sY;
    char cLB, cRB;
    char cMIresult;
    int  iMIbuttonNum;
    static class CMouseInterface * pMI;
    static char  cPrevFocus;
    uint64_t dwTime = unixtime();
    bool bFlag = true;

    sX = 146;
    sY = 114;
    if (m_cGameModeCount == 0)
    {
        EndInputString();

        pMI = new class CMouseInterface;
        pMI->AddRect(130, 177, 270, 198);
        pMI->AddRect(130, 199, 270, 225);
        pMI->AddRect(256, 279, 331, 308);

        cPrevFocus = 1;
        m_cCurFocus = 1;
        m_cMaxFocus = 3;

        m_bEnterPressed = false;
        m_cArrowPressed = 0;
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_cArrowPressed != 0)
    {
        switch (m_cArrowPressed)
        {
            case 1:
                m_cCurFocus--;
                if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
                break;

            case 3:
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                break;
        }
        m_cArrowPressed = 0;
    }

    if (m_bEnterPressed == true)
    {
        m_bEnterPressed = false;
        PlaySound('E', 14, 5);
        switch (m_cCurFocus)
        {
            case 1:
                if (strlen(m_cWorldServerName) == 0)
                    ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
                strcpy(m_cWorldServerName, NAME_WORLDNAME1);
                ChangeGameMode(DEF_GAMEMODE_ONLOGIN);
                delete pMI;
                return;

            case 2:
                ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
                strcpy(m_cWorldServerName, "WS2");
                ChangeGameMode(DEF_GAMEMODE_ONLOGIN);
                delete pMI;
                return;

            case 3:	// Cancel
                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                delete pMI;
                return;
        }
    }

    if (m_bEscPressed == true)
    {
        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
        delete pMI;
        m_bEscPressed = false;
        return;
    }
    if (cPrevFocus != m_cCurFocus)
    {
        cPrevFocus = m_cCurFocus;
    }
    m_DDraw.back_buffer.clear(sf::Color::Black);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 0, 0, 0, true);
    if (m_cGameModeCount > 20) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 40, 121, 1, true);
    else if ((m_cGameModeCount >= 15) && (m_cGameModeCount <= 20)) m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->PutTransSprite25(40, 121, 1, true);

    if (m_cGameModeCount > 20)
    {
        if (m_cCurFocus == 1) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 138, 177, 5, true);
        if (m_cCurFocus == 2) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 130, 205, 6, true);
        if (m_cCurFocus == 3) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 256, 282, 4, true);
    }
    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        PlaySound('E', 14, 5);

        switch (iMIbuttonNum)
        {
            case 1:
                if (m_cCurFocus == 1)
                {
                    ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
                    strcpy(m_cWorldServerName, NAME_WORLDNAME1);
                    ChangeGameMode(DEF_GAMEMODE_ONLOGIN);
                    delete pMI;
                    return;
                }
                else m_cCurFocus = 1;
                break;

            case 2:
                if (m_cCurFocus == 2)
                {
                    ZeroMemory(m_cWorldServerName, sizeof(m_cWorldServerName));
                    strcpy(m_cWorldServerName, "WS2");
                    ChangeGameMode(DEF_GAMEMODE_ONLOGIN);
                    delete pMI;
                    return;
                }
                else m_cCurFocus = 2;
                break;

            case 3:
                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                delete pMI;
                return;
        }
    }

    if ((msX >= 130) && (msX <= 295) && (msY >= 175) && (msY <= 198)) m_cCurFocus = 1;
    if ((msX >= 130) && (msX <= 295) && (msY >= 199) && (msY <= 225)) m_cCurFocus = 2;
    if ((msX >= 256) && (msX <= 331) && (msY >= 279) && (msY <= 308)) m_cCurFocus = 3;

    //	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
    //	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);
}


void CGame::UpdateScreen_OnQuit()
{
    short msX, msY, msZ;
    char cLB, cRB;
    char cMIresult;
    int  iMIbuttonNum;

    static class CMouseInterface * pMI;

    uint64_t dwTime = unixtime();

    if (m_cGameModeCount == 0)
    {
        if (ws)
            ws = nullptr;
        m_bEscPressed = false;
        m_bEnterPressed = false;
        pMI = new class CMouseInterface;
        pMI->AddRect(0, 0, 640, 480);
        m_bEnterPressed = false;
    }

    m_cGameModeCount++;
    if (m_cGameModeCount > 120) m_cGameModeCount = 120;

    m_DDraw.back_buffer.clear(sf::Color::Black);

    if (m_bEscPressed == true || m_bEnterPressed == true)
    {
        m_bEscPressed = false;
        m_bEnterPressed = false;
        delete pMI;
        ChangeGameMode(DEF_GAMEMODE_0);
        //SendMessage(m_hWnd, WM_DESTROY, 0, 0);
        return;
    }
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_QUIT, 0, 0, 0, true);
    if (m_cGameModeCount > 20) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_QUIT, 255, 123, 1, true);
    else if ((m_cGameModeCount >= 15) && (m_cGameModeCount <= 20)) m_pSprite[DEF_SPRID_INTERFACE_ND_QUIT]->PutTransSprite25(255, 123, 1, true);
    if (m_cGameModeCount == 100)
    {
        ChangeGameMode(DEF_GAMEMODE_0);
        delete pMI;
        //SendMessage(m_hWnd, WM_DESTROY, 0, 0);
        return;
    }
    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if ((cMIresult == DEF_MIRESULT_CLICK) && (iMIbuttonNum == 1))
    {
        ChangeGameMode(DEF_GAMEMODE_0);
        //SendMessage(m_hWnd, WM_DESTROY, 0, 0);
        delete pMI;
        return;
    }

    //	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
    //	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);
}

void CGame::UpdateScreen_OnQueryForceLogin()
{
    short msX, msY, msZ;
    char cLB, cRB;
    char cMIresult;
    int  iMIbuttonNum;

    static class CMouseInterface * pMI;
    static uint64_t dwCTime;
    uint64_t dwTime = unixtime();

    if (m_cGameModeCount == 0)
    {
        pMI = new class CMouseInterface;
        pMI->AddRect(200, 244, 200 + DEF_BTNSZX, 244 + DEF_BTNSZY);
        pMI->AddRect(370, 244, 370 + DEF_BTNSZX, 244 + DEF_BTNSZY);
        m_bEnterPressed = false;
        m_bEscPressed = false;
        m_cArrowPressed = 0;

        dwCTime = unixtime();

        PlaySound('E', 25, 0);
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_bEscPressed == true)
    {
        ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
        delete pMI;
        m_bEscPressed = false;
        return;
    }

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    UpdateScreen_OnSelectCharacter(0, 0, 0, 0);
    if ((m_cGameModeCount >= 0) && (m_cGameModeCount < 6))
    {
        m_DDraw.DrawShadowBox(0, 0, 639, 479);
    }
    else if (m_cGameModeCount >= 6)
    {
        m_DDraw.DrawShadowBox(0, 0, 639, 479);
        m_DDraw.DrawShadowBox(0, 0, 639, 479);
    }

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 130, 2);

    PutString_SprFont(172 + 86, 160, "Character on Use", 7, 0, 0);
    PutAlignedString(178, 453, 195, UPDATE_SCREEN_ON_QUERY_FORCE_LOGIN1);
    PutAlignedString(178, 453, 215, UPDATE_SCREEN_ON_QUERY_FORCE_LOGIN2);

    if ((msX >= 200) && (msX <= 200 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 200, 244, 19);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 200, 244, 18);

    if ((msX >= 370) && (msX <= 370 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 3);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 2);

    if ((dwTime - dwCTime) > 100)
    {
        m_cMenuFrame++;
        dwCTime = dwTime;
    }
    if (m_cMenuFrame >= 8)
    {
        m_cMenuDirCnt++;
        if (m_cMenuDirCnt > 8)
        {
            m_cMenuDir++;
            m_cMenuDirCnt = 1;
        }
        m_cMenuFrame = 0;
    }
    if (m_cMenuDir > 8) m_cMenuDir = 1;

    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        PlaySound('E', 14, 5);
        switch (iMIbuttonNum)
        {
            case 1:
                perform_login_connect();
                ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                m_dwConnectMode = MSGID_REQUEST_ENTERGAME;
                m_wEnterGameType = DEF_ENTERGAMEMSGTYPE_NOENTER_FORCEDISCONN;
                ZeroMemory(m_cMsg, sizeof(m_cMsg));
                strcpy(m_cMsg, "33");
                delete pMI;
                return;

            case 2:
                ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                delete pMI;
                break;
        }
    }
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
}

void CGame::UpdateScreen_OnSelectCharacter(short sX, short sY, short msX, short msY, bool bIgnoreFocus)
{
    int i;
    int iYear, iMonth, iDay, iHour, iMinute;
    __int64 iTemp1, iTemp2;
    char cTotalChar = 0;
    uint64_t dwTime = unixtime();
    sY = 10;
    m_DDraw.back_buffer.clear(sf::Color::Black);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_SELECTCHAR, 0, 0, 0);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 50);

    iTemp1 = 0;
    iTemp2 = 0;
    iYear = iMonth = iDay = iHour = iMinute = 0;
    for (i = 0; i < 4; i++)
    {
        if ((m_cCurFocus - 1 == i) && (bIgnoreFocus == false))
            m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(sX + 110 + i * 109 - 7, 63 - 9, 62, dwTime);
        else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(sX + 110 + i * 109 - 7, 63 - 9, 61, dwTime);

        if (m_pCharList[i] != 0)
        {
            cTotalChar++;
            switch (m_pCharList[i]->m_sSex)
            {
                case 1:	_tmp_sOwnerType = 1; break;
                case 2:	_tmp_sOwnerType = 4; break;
            }
            _tmp_sOwnerType += m_pCharList[i]->m_sSkinCol - 1;
            _tmp_cDir = m_cMenuDir;
            _tmp_sAppr1 = m_pCharList[i]->m_sAppr1;
            _tmp_sAppr2 = m_pCharList[i]->m_sAppr2;
            _tmp_sAppr3 = m_pCharList[i]->m_sAppr3;
            _tmp_sAppr4 = m_pCharList[i]->m_sAppr4;
            _tmp_iApprColor = m_pCharList[i]->m_iApprColor; // v1.4

            ZeroMemory(_tmp_cName, sizeof(_tmp_cName));
            memcpy(_tmp_cName, m_pCharList[i]->m_cName, 10);
            _tmp_cAction = DEF_OBJECTMOVE;
            _tmp_cFrame = m_cMenuFrame;

            if (m_pCharList[i]->m_sSex != 0)
            {
                if (m_Misc.bCheckValidString(m_pCharList[i]->m_cName) == true)
                {
                    m_pEffectSpr[0]->PutTransSprite(sX + 157 + i * 109, sY + 138, 1, dwTime);
                    DrawObject_OnMove_ForMenu(0, 0, sX + 157 + i * 109, sY + 138, false, dwTime, 0, 0);
                    PutString(sX + 112 + i * 109, sY + 179 - 9, m_pCharList[i]->m_cName, Color(51, 0, 51));//25,35,25);
                    int	_sLevel = m_pCharList[i]->m_sLevel;
                    wsprintfA(G_cTxt, "%d", _sLevel);
                    PutString(sX + 138 + i * 109, sY + 196 - 10, G_cTxt, Color(51, 0, 51)); //25,35,25);

                    wsprintfA(G_cTxt, "%d", m_pCharList[i]->m_iExp);
                    PutString(sX + 138 + i * 109, sY + 211 - 10, G_cTxt, Color(51, 0, 51)); //25,35,25);
                }
                iTemp2 = m_pCharList[i]->m_iYear * 1000000 + m_pCharList[i]->m_iMonth * 60000 + m_pCharList[i]->m_iDay * 1700 + m_pCharList[i]->m_iHour * 70 + m_pCharList[i]->m_iMinute;
                if (iTemp1 < iTemp2)
                {
                    iYear = m_pCharList[i]->m_iYear;
                    iMonth = m_pCharList[i]->m_iMonth;
                    iDay = m_pCharList[i]->m_iDay;
                    iHour = m_pCharList[i]->m_iHour;
                    iMinute = m_pCharList[i]->m_iMinute;
                    iTemp1 = iTemp2;
                }
            }
        }
    }
    i = 0;

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 51);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 52);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 53);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 54);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 55);

    if ((msX > 360) && (msY >= 283) && (msX < 545) & (msY <= 315))
    {
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 56);
        PutAlignedString(98, 357, 290 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER1);//"
        PutAlignedString(98, 357, 305 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER2);//"
        PutAlignedString(98, 357, 320 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER3);//"
        PutAlignedString(98, 357, 335 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER4);//"
    }
    else
        if ((msX > 360) && (msY >= 316) && (msX < 545) & (msY <= 345))
        {
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 57);
            PutAlignedString(98, 357, 305 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER5);//"

        }
        else
            if ((msX > 360) && (msY >= 346) && (msX < 545) & (msY <= 375))
            {

                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 58);
                PutAlignedString(98, 357, 275 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER6);//"
                PutAlignedString(98, 357, 290 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER7);//"
                PutAlignedString(98, 357, 305 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER8);//"
                PutAlignedString(98, 357, 320 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER9);//"
                PutAlignedString(98, 357, 335 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER10);//"
                PutAlignedString(98, 357, 350 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER11);//"

            }
            else if ((msX > 360) && (msY >= 376) && (msX < 545) & (msY <= 405))
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 59);
                PutAlignedString(98, 357, 305 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER12);//"
            }
            else if ((msX > 360) && (msY >= 406) && (msX < 545) & (msY <= 435))
            {
                DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 0, 0, 60);
                PutAlignedString(98, 357, 305 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER13);//"
            }
            else
            {
                if (cTotalChar == 0)
                {
                    PutAlignedString(98, 357, 275 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER14);//"
                    PutAlignedString(98, 357, 290 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER15);//"
                    PutAlignedString(98, 357, 305 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER16);//"
                    PutAlignedString(98, 357, 320 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER17);//"New Character
                    PutAlignedString(98, 357, 335 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER18);//"
                }
                else if (cTotalChar < 4)
                {
                    PutAlignedString(98, 357, 275 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER19);//"
                    PutAlignedString(98, 357, 290 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER20);//"Play¹
                    PutAlignedString(98, 357, 305 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER21);//"
                    PutAlignedString(98, 357, 320 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER22);//"
                    PutAlignedString(98, 357, 335 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER23);//"Delete Character
                    PutAlignedString(98, 357, 350 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER24);//"
                }
                if (cTotalChar == 4)
                {
                    PutAlignedString(98, 357, 290 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER25);//"
                    PutAlignedString(98, 357, 305 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER26);//"Play
                    PutAlignedString(98, 357, 320 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER27);//"Delete Character
                    PutAlignedString(98, 357, 335 + 15, UPDATE_SCREEN_ON_SELECT_CHARACTER28);//"
                }
            }
    int iTempMon, iTempDay, iTempHour, iTempMin;
    iTempMon = iTempDay = iTempHour = iTempMin = 0;

    if (m_iAccntYear != 0)
    {
        iTempMin = (m_iTimeLeftSecAccount / 60);
        wsprintfA(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER37, m_iAccntYear, m_iAccntMonth, m_iAccntDay, iTempMin);
    }
    else
    {
        if (m_iTimeLeftSecAccount > 0)
        {
            iTempDay = (m_iTimeLeftSecAccount / (60 * 60 * 24));
            iTempHour = (m_iTimeLeftSecAccount / (60 * 60)) % 24;
            iTempMin = (m_iTimeLeftSecAccount / 60) % 60;
            wsprintfA(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER38, iTempDay, iTempHour, iTempMin);
        }
        else strcpy(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER39);
    }
    PutAlignedString(98, 357, 385 + 10, G_cTxt);

    if (m_iIpYear != 0)
    {
        iTempHour = (m_iTimeLeftSecIP / (60 * 60));
        iTempMin = (m_iTimeLeftSecIP / 60) % 60;
        wsprintfA(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER40, m_iIpYear, m_iIpMonth, m_iIpDay, iTempHour, iTempMin);
    }
    else
    {
        if (m_iTimeLeftSecIP > 0)
        {
            iTempDay = (m_iTimeLeftSecIP / (60 * 60 * 24));
            iTempHour = (m_iTimeLeftSecIP / (60 * 60)) % 24;
            iTempMin = (m_iTimeLeftSecIP / 60) % 60;
            wsprintfA(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER41, iTempDay, iTempHour, iTempMin);
        }
        else strcpy(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER42);
    }
    PutAlignedString(98, 357, 400 + 10, G_cTxt);
    if (iYear != 0)
    {
        wsprintfA(G_cTxt, UPDATE_SCREEN_ON_SELECT_CHARACTER43, iYear, iMonth, iDay, iHour, iMinute);
        PutAlignedString(98, 357, 415 + 10, G_cTxt);
    }

#ifdef _DEBUG
    PutAlignedString(122, 315, 456, UPDATE_SCREEN_ON_SELECT_CHARACTER36);//"Test Server"
#else
    if (strcmp(m_cWorldServerName, NAME_WORLDNAME1) == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME1);//"ABADDON Server"
    else if (strcmp(m_cWorldServerName, "WS2") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME2);//"APOCALYPSE Server"
    else if (strcmp(m_cWorldServerName, "WS3") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME3);//"3rd Server"
    else if (strcmp(m_cWorldServerName, "WS4") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME4);//"4th Server"
    else if (strcmp(m_cWorldServerName, "WS5") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME5);//"5th Server"
    else if (strcmp(m_cWorldServerName, "WS6") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME6);//"6th Server"
    else if (strcmp(m_cWorldServerName, "WS7") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME7);//"7th Server"
    else if (strcmp(m_cWorldServerName, "WS8") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME8);//"8th Server"
    else if (strcmp(m_cWorldServerName, "WS9") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME9);//"9th Server"
    else if (strcmp(m_cWorldServerName, "WS10") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME10);//"10th Server"
    else if (strcmp(m_cWorldServerName, "WS11") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME11);//"11th Server"
    else if (strcmp(m_cWorldServerName, "WS12") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME12);//"12th Server"
    else if (strcmp(m_cWorldServerName, "WS13") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME13);//"13th Server"
    else if (strcmp(m_cWorldServerName, "WS14") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME14);//"14th Server"
    else if (strcmp(m_cWorldServerName, "WS15") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME15);//"15th Server"
    else if (strcmp(m_cWorldServerName, "WS16") == 0)
        PutAlignedString(129, 321, 456, MSG_WORLDNAME16);//"16th Server"
#endif



}

void CGame::UpdateScreen_OnWaitingResponse()
{
    short sX, sY, msX, msY, msZ;
    char cLB, cRB;

    uint64_t dwTime = unixtime();
    //static class CMouseInterface * pMI;
    static uint64_t dwCTime;

    if (m_cGameModeCount == 0)
    {
        m_bEnterPressed = false;
        m_bEscPressed = false;
        dwCTime = unixtime();
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_bEscPressed == true)
    {
        if ((dwTime - m_dwTime) > 7000)
        {
            ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
            if (log_ws)
                log_ws = nullptr;
            if (ws)
                ws = nullptr;
        }
        m_bEscPressed = false;
        return;
    }

    if ((dwTime - dwCTime) > 100)
    {
        m_cMenuFrame++;
        dwCTime = dwTime;
    }
    if (m_cMenuFrame >= 8)
    {
        m_cMenuDirCnt++;
        if (m_cMenuDirCnt > 8)
        {
            m_cMenuDir++;
            m_cMenuDirCnt = 1;
        }
        m_cMenuFrame = 0;
    }
    if (m_cMenuDir > 8) m_cMenuDir = 1;

    m_bIsHideLocalCursor = true;
    m_DDraw.back_buffer.clear(sf::Color::Black);
    switch (m_cMsg[0])
    {
        case '0':
            _Draw_UpdateScreen_OnCreateNewAccount();
            break;
        case '1':
            sX = 146;
            sY = 114;
            _Draw_OnLogin(m_cAccountName, m_cAccountPassword, 0, 0);
            break;
        case '2':
            _bDraw_OnCreateNewCharacter(m_cPlayerName, 0, 0, 0);
            break;
        case '3':
            UpdateScreen_OnSelectCharacter(0, 0, 0, 0);
            break;
        case '4':// Change Password
            UpdateScreen_OnSelectCharacter(0, 0, 0, 0, true);
            break;
        case '5':
            m_DDraw.back_buffer.clear(sf::Color::Black);
            break;
    }
    m_bIsHideLocalCursor = false;

    m_DDraw.DrawShadowBox(0, 0, 639, 479);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 125, 2);
    PutString_SprFont(172 + 44 - 17, 190, "Connected. Waiting for response...", 7, 0, 0);

    if ((dwTime - m_dwTime) > 7000)
    {
        PutAlignedString(180, 463, 195 + 30, UPDATE_SCREEN_ON_WATING_RESPONSE1);
        PutAlignedString(180, 463, 195 + 45, UPDATE_SCREEN_ON_WATING_RESPONSE2);
    }
    else PutAlignedString(180, 463, 195 + 30, UPDATE_SCREEN_ON_WATING_RESPONSE3);

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 8, dwTime);
}

void CGame::UpdateScreen_OnQueryDeleteCharacter()
{
    short msX, msY, msZ;
    char cLB, cRB;
    char cMIresult;
    int  iMIbuttonNum;

    static class CMouseInterface * pMI;
    static uint64_t dwCTime;
    uint64_t dwTime = unixtime();

    if (m_cGameModeCount == 0)
    {
        pMI = new class CMouseInterface;
        pMI->AddRect(200, 244, 200 + DEF_BTNSZX, 244 + DEF_BTNSZY);
        pMI->AddRect(370, 244, 370 + DEF_BTNSZX, 244 + DEF_BTNSZY);
        //m_cCurFocus = 1;
        //m_cMaxFocus = 2;
        m_bEnterPressed = false;
        m_cArrowPressed = 0;

        dwCTime = unixtime();

        PlaySound('E', 25, 0);
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_bEscPressed == true)
    {
        ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
        delete pMI;
        m_bEscPressed = false;
        return;
    }

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    UpdateScreen_OnSelectCharacter(0, 0, 500, 70);
    if ((m_cGameModeCount >= 0) && (m_cGameModeCount < 6))
    {
        m_DDraw.DrawShadowBox(0, 0, 639, 479);
    }
    else if (m_cGameModeCount >= 6)
    {
        m_DDraw.DrawShadowBox(0, 0, 639, 479);
        m_DDraw.DrawShadowBox(0, 0, 639, 479);
    }

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 125, 2);

    PutString_SprFont(172 + 86, 160, "Delete Character", 7, 0, 0);
    PutString(215, 195, UPDATE_SCREEN_ON_QUERY_DELETE_CHARACTER1, Color(5, 5, 5));//"Character Name"
    //"Character Name"
    PutString(335, 199, "__________", Color(5, 5, 5));
    PutString(335, 195, m_pCharList[m_wEnterGameType - 1]->m_cName, Color(25, 35, 25));
    PutAlignedString(178, 453, 220, UPDATE_SCREEN_ON_QUERY_DELETE_CHARACTER2);//"Do you want to delete the character above?"

    // v2.05
    if ((msX >= 200) && (msX <= 200 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 200, 244, 19);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 200, 244, 18);

    if ((msX >= 370) && (msX <= 370 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 3);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 2);

    if ((dwTime - dwCTime) > 100)
    {
        m_cMenuFrame++;
        dwCTime = dwTime;
    }
    if (m_cMenuFrame >= 8)
    {
        m_cMenuDirCnt++;
        if (m_cMenuDirCnt > 8)
        {
            m_cMenuDir++;
            m_cMenuDirCnt = 1;
        }
        m_cMenuFrame = 0;
    }
    if (m_cMenuDir > 8) m_cMenuDir = 1;

    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        PlaySound('E', 14, 5);
        switch (iMIbuttonNum)
        {
            case 1:
                perform_login_connect();
                ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                m_dwConnectMode = MSGID_REQUEST_DELETECHARACTER;
                ZeroMemory(m_cMsg, sizeof(m_cMsg));
                strcpy(m_cMsg, "33");
                delete pMI;
                return;

            case 2:
                ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                delete pMI;
                break;
        }
    }
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
}


void CGame::UpdateScreen_OnLogResMsg()
{
    short msX, msY, msZ, sX, sY;
    char  cLB, cRB;
    uint64_t dwTime = unixtime();
    static uint64_t dwCTime;
    static class CMouseInterface * pMI;
    int   iMIbuttonNum;
    char  cMIresult;


    if (m_cGameModeCount == 0)
    {
        pMI = new class CMouseInterface;
        pMI->AddRect(370, 240, 370 + DEF_BTNSZX, 240 + DEF_BTNSZY);
        m_bEnterPressed = false;
        m_bEscPressed = false;
        m_cArrowPressed = 0;
        dwCTime = unixtime();
        if (m_bSoundFlag) m_pESound[38].stop();
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if (m_bEscPressed == true || m_bEnterPressed)
    {
        switch (m_cMsg[0])
        {
            case '0':
                ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
                break;
            case '1':
                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                break;
            case '2':
                ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
                break;
            case '3':
                ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                break;
            case '4':
                ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                break;
            case '5':
                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                break;
            case '6':
                switch (m_cMsg[1])
                {
                    case 'B':
                        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                        break;
                    case 'C': ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD); break;
                    case 'M': ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD); break;
                }
                break;
            case '7':
            case '8':
                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                break;
        }

        delete pMI;
        m_bEscPressed = false;
        return;
    }

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;

    m_DDraw.back_buffer.clear(sf::Color::Black);

    switch (m_cMsg[0])
    {
        case '0':
        case '5':
            _Draw_UpdateScreen_OnCreateNewAccount();
            break;

        case '1':
        case '7':
            sX = 146;
            sY = 114;

            _Draw_OnLogin(m_cAccountName, m_cAccountPassword, 0, 0);
            break;

        case '2':
        case '4':
            _bDraw_OnCreateNewCharacter(m_cPlayerName, 0, 0, 0);
            break;

        case '3':
            sX = 0;
            sY = 0;
            UpdateScreen_OnSelectCharacter(sX, sY, 0, 0);
            break;

        case '6':
            sX = 146;
            sY = 114;

            UpdateScreen_OnSelectCharacter(0, 0, 0, 0, true);
            break;
        case '8':
            DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_MAINMENU, -1, -1, 0, true);
            break;
    }

    m_DDraw.DrawShadowBox(0, 0, 639, 479);

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 125, 2);

    if ((msX >= 370) && (msX <= 370 + DEF_BTNSZX) && (msY >= 244) && (msY <= 244 + DEF_BTNSZY))
        DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 1);
    else DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_BUTTON, 370, 244, 0);

    switch (m_cMsg[1])
    {
        case '1':
            PutString_SprFont(172 + 70, 165, "Password is not correct!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG5);//"
            break;

        case '2':
            PutString_SprFont(172 + 70, 165, "Not existing account!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG6);//"
            PutAlignedString(198, 453, 215, UPDATE_SCREEN_ON_LOG_MSG7);//"
            break;

        case '3':
            PutString_SprFont(172 + 10 + 34, 165, "Can not connect to game server!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG8);//"
            PutAlignedString(198, 453, 210, UPDATE_SCREEN_ON_LOG_MSG9);//"
            PutAlignedString(198, 453, 225, UPDATE_SCREEN_ON_LOG_MSG10);//"
            break;

        case '4':
            PutString_SprFont(172 + 58, 165, "New account created.", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG11);//"
            PutAlignedString(198, 453, 210, UPDATE_SCREEN_ON_LOG_MSG12);//"
            break;

        case '5':
            PutString_SprFont(172 + 58, 165, "Can not create new account!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG13);//"
            break;

        case '6':
            PutString_SprFont(172 + 36, 165, "Can not create new account!", 7, 0, 0);
            PutString_SprFont(172 + 24, 180, "Already existing account name.", 7, 0, 0);
            PutAlignedString(198, 453, 205, UPDATE_SCREEN_ON_LOG_MSG14);//"
            PutAlignedString(198, 453, 220, UPDATE_SCREEN_ON_LOG_MSG15);//"
            break;

        case '7':
            PutString_SprFont(172 + 58, 165, "New character created.", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG16);//"
            break;

        case '8':
            PutString_SprFont(172 + 58, 165, "Can not create new character!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG17);//"
            break;

        case '9':
            PutString_SprFont(172 + 36, 165, "Can not create new character!", 7, 0, 0);
            PutString_SprFont(172 + 24, 180, "Already existing character name.", 7, 0, 0);
            PutAlignedString(198, 453, 205, UPDATE_SCREEN_ON_LOG_MSG18);//"
            PutAlignedString(198, 453, 220, UPDATE_SCREEN_ON_LOG_MSG19);//"
            break;

        case 'A':
            PutString_SprFont(172 + 36 + 45, 165, "Character deleted.", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG20);//"

            break;
        case 'B':
            PutString_SprFont(172 + 36 + 45, 165, "Password changed.", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG21);//"
            break;
        case 'C':
            PutString_SprFont(172 + 36, 165, "Can not change password!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG22);//"
            break;

        case 'D':
            PutString_SprFont(172 + 10 + 34, 165, "Can not connect to game server!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG23);//"
            PutAlignedString(198, 453, 210, UPDATE_SCREEN_ON_LOG_MSG24);//"
            break;

        case 'E':
            PutString_SprFont(172 + 10 + 34, 165, "Can not connect to game server!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG25);//"
            PutAlignedString(198, 453, 210, UPDATE_SCREEN_ON_LOG_MSG26);//"
            PutAlignedString(198, 453, 225, UPDATE_SCREEN_ON_LOG_MSG27);//"
            break;

        case 'F':
            PutString_SprFont(172 + 10 + 34, 165, "Can not connect to game server!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG28);//"
            PutAlignedString(198, 453, 210, UPDATE_SCREEN_ON_LOG_MSG29);//"
            break;

        case 'G':
            PutString_SprFont(172 + 10 + 34, 165, "Can not connect to game server!", 7, 0, 0);
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG30);//"
            PutAlignedString(198, 453, 210, UPDATE_SCREEN_ON_LOG_MSG31);//"
            break;

        case 'H':
            PutString_SprFont(172 + 68, 165, "Connection Rejected!", 7, 0, 0);
            if (m_iBlockYear == 0)
            {
                PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG32);//"
                PutAlignedString(198, 453, 210, UPDATE_SCREEN_ON_LOG_MSG33);//"
            }
            else
            {
                PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG34);//"
                wsprintfA(G_cTxt, UPDATE_SCREEN_ON_LOG_MSG35, m_iBlockYear, m_iBlockMonth, m_iBlockDay);//"
                PutAlignedString(198, 453, 210, G_cTxt);
            }
            break;

        case 'I': //
            PutString_SprFont(172 + 68, 165, "Not Enough Point!", 7, 0, 0);
            PutAlignedString(198, 453, 210, "ÂI¼Æ¨Ï¥Î´Á­­¤wµ²§ô, ½Ð¦ÜGD2S.gamania.com©µªø¨Ï¥Î´Á­­");

            break;

        case 'J': // v2.15 2002-5-21
            PutString_SprFont(172 + 68, 165, "World Server Full", 7, 0, 0);
            PutAlignedString(198, 453, 210, "Please ! Try Other World Server");
            break;

        case 'M': 	// v2.18
            PutString_SprFont(172 + 68, 165, "Your password expired", 7, 0, 0);
            PutAlignedString(198, 453, 210, "Please! Change password");
            break;


        case 'U': // v2.15
            PutString_SprFont(172 + 68, 165, "Keycode input Success!", 7, 0, 0);
            PutAlignedString(198, 453, 210, "Keycode Registration successed.");

            break;

        case 'X':
            PutAlignedString(198, 453, 195, UPDATE_SCREEN_ON_LOG_MSG38);//"
            PutAlignedString(198, 453, 210, UPDATE_SCREEN_ON_LOG_MSG39);//"
            break;

        case 'Y':
            PutAlignedString(178, 453, 195, UPDATE_SCREEN_ON_LOG_MSG40);//"
            PutAlignedString(178, 453, 210, UPDATE_SCREEN_ON_LOG_MSG41);//"
            break;

        case 'Z':
            PutAlignedString(178, 453, 195, UPDATE_SCREEN_ON_LOG_MSG42);//"
            PutAlignedString(178, 453, 210, UPDATE_SCREEN_ON_LOG_MSG41);//"
            break;
    }

    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        switch (iMIbuttonNum)
        {
            case 1:
                switch (m_cMsg[0])
                {
                    case '0':
                        ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
                        break;
                    case '1':
                        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                        break;
                    case '2':
                        ChangeGameMode(DEF_GAMEMODE_ONCREATENEWCHARACTER);
                        break;
                    case '3':
                        ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                        break;
                    case '4':
                        ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                        break;
                    case '5':
                        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                        break;
                    case '6':
                        switch (m_cMsg[1])
                        {
                            case 'B':
                                ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                                break;
                            case 'C': ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD); break;
                            case 'M': ChangeGameMode(DEF_GAMEMODE_ONCHANGEPASSWORD); break;
                        }
                        break;
                    case '7':
                    case '8':
                        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
                        break;
                }
                delete pMI;
                return;
        }
    }

    if ((dwTime - dwCTime) > 100)
    {
        m_cMenuFrame++;
        dwCTime = dwTime;
    }
    if (m_cMenuFrame >= 8)
    {
        m_cMenuDirCnt++;
        if (m_cMenuDirCnt > 8)
        {
            m_cMenuDir++;
            m_cMenuDirCnt = 1;
        }
        m_cMenuFrame = 0;
    }
    if (m_cMenuDir > 8) m_cMenuDir = 1;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
}


void CGame::UpdateScreen_OnChangePassword()
{
    short msX, msY, msZ;
    char cLB, cRB;
    char cMIresult;
    int  iMIbuttonNum;
    static class CMouseInterface * pMI;
    static char  cName[12], cPassword[12], cNewPassword[12], cNewPassConfirm[12], cPrevFocus;
    static uint64_t dwCTime;
    uint64_t dwTime = unixtime();
    bool bFlag = true;

    if (m_cGameModeCount == 0)
    {
        EndInputString();

        pMI = new class CMouseInterface;
        pMI->AddRect(300, 148, 425, 170);
        pMI->AddRect(300, 172, 425, 194);
        pMI->AddRect(300, 196, 425, 218);
        pMI->AddRect(300, 220, 425, 242);

        pMI->AddRect(197, 320, 197 + DEF_BTNSZX, 320 + DEF_BTNSZY);
        pMI->AddRect(370, 320, 370 + DEF_BTNSZX, 320 + DEF_BTNSZY);

        cPrevFocus = 2; //1
        m_cCurFocus = 2; //1
        m_cMaxFocus = 6;
        m_bEnterPressed = false;
        m_cArrowPressed = 0;

        ZeroMemory(cName, sizeof(cName));
        ZeroMemory(cPassword, sizeof(cPassword));
        ZeroMemory(cNewPassword, sizeof(cNewPassword));
        ZeroMemory(cNewPassConfirm, sizeof(cNewPassConfirm));

        strcpy(cName, m_cAccountName);
        //StartInputString(314, 155, 11, cName);
        StartInputString(314, 179, 11, cPassword);
        ClearInputString();
        dwCTime = dwTime;
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    if ((dwTime - dwCTime) > 100)
    {
        m_cMenuFrame++;
        dwCTime = dwTime;
    }
    if (m_cMenuFrame >= 8)
    {
        m_cMenuDirCnt++;
        if (m_cMenuDirCnt > 8)
        {
            m_cMenuDir++;
            m_cMenuDirCnt = 1;
        }
        m_cMenuFrame = 0;
    }
    if (m_cMenuDir > 8) m_cMenuDir = 1;

    if (m_cArrowPressed != 0)
    {
        switch (m_cArrowPressed)
        {
            case 1:
                m_cCurFocus--;
                if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
                break;

            case 2:
                if (m_cCurFocus == 3) m_cCurFocus = 4;
                else if (m_cCurFocus == 4) m_cCurFocus = 3;
                break;

            case 3:
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                break;

            case 4:
                if (m_cCurFocus == 3) m_cCurFocus = 4;
                else if (m_cCurFocus == 4) m_cCurFocus = 3;
                break;
        }
        m_cArrowPressed = 0;
    }

    if (m_bEnterPressed == true)
    {
        PlaySound('E', 14, 5);
        switch (m_cCurFocus)
        {
            case 1:
            case 2:
            case 3:
            case 4:
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                break;

            case 5:	// Connect
                if ((m_Misc.bCheckValidString(cPassword) == false) || (strlen(cPassword) == 0) ||
                    (m_Misc.bCheckValidName(cNewPassword) == false) || (m_Misc.bCheckValidName(cNewPassConfirm) == false) ||
                    (strlen(cNewPassword) == 0) || (memcmp(cNewPassword, cNewPassConfirm, 10) != 0)) break;

                ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
                ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
                ZeroMemory(m_cNewPassword, sizeof(m_cNewPassword));
                ZeroMemory(m_cNewPassConfirm, sizeof(m_cNewPassConfirm));
                strcpy(m_cAccountName, cName);
                strcpy(m_cAccountPassword, cPassword);
                strcpy(m_cNewPassword, cNewPassword);
                strcpy(m_cNewPassConfirm, cNewPassConfirm);
                perform_login_connect();
                ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                m_dwConnectMode = MSGID_REQUEST_CHANGEPASSWORD;
                ZeroMemory(m_cMsg, sizeof(m_cMsg));
                strcpy(m_cMsg, "41");
                delete pMI;
                return;

            case 6:	// Cancel
                ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                //m_dwLoginMode = MSGID_REQUEST_LOGIN;
                delete pMI;
                return;
        }
        m_bEnterPressed = false;
    }

    if (m_bEscPressed == true)
    {
        ChangeGameMode(DEF_GAMEMODE_ONMAINMENU);
        delete pMI;
        m_bEscPressed = false;
        return;
    }

    if (cPrevFocus != m_cCurFocus)
    {
        EndInputString();
        switch (m_cCurFocus)
        {
            case 1:
                StartInputString(314, 155, 11, cName);
                break;
            case 2:
                StartInputString(314, 179, 11, cPassword);
                break;
            case 3:
                StartInputString(314, 203, 11, cNewPassword);
                break;
            case 4:
                StartInputString(314, 227, 11, cNewPassConfirm);
                break;
        }
        cPrevFocus = m_cCurFocus;
    }

    m_DDraw.back_buffer.clear(sf::Color::Black);

    UpdateScreen_OnSelectCharacter(0, 0, 0, 0, true);
    m_DDraw.DrawShadowBox(0, 0, 639, 479);//SelectCharacter

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 153, 112, 0);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_TEXT, 153, 112, 13);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 153 + 157, 112 + 109, 7);//

    PutString(206, 155, UPDATE_SCREEN_ON_CHANGE_PASSWORD1, Color(25, 35, 25));
    PutString(206, 179, UPDATE_SCREEN_ON_CHANGE_PASSWORD2, Color(25, 35, 25));
    PutString(206, 203, UPDATE_SCREEN_ON_CHANGE_PASSWORD3, Color(25, 35, 25));
    PutString(206, 227, UPDATE_SCREEN_ON_CHANGE_PASSWORD4, Color(25, 35, 25));

    if (m_cCurFocus != 1)
    {
        if (m_Misc.bCheckValidString(cName) != false)
            PutString(314, 155, cName, Color(25, 35, 25));
        else PutString(314, 155, cName, Color(55, 18, 13));
    }
    if ((m_Misc.bCheckValidString(cName) == false) || (strlen(cName) == 0)) bFlag = false;

    if (m_cCurFocus != 2)
    {
        if ((m_Misc.bCheckValidString(cPassword) != false))
            PutString(314, 179, cPassword, Color(25, 35, 25), true, 3);
        else PutString(314, 179, cPassword, Color(55, 18, 13), true, 3);
    }

    if (m_cCurFocus != 3)
    {
        if ((m_Misc.bCheckValidName(cNewPassword) != false))
            PutString(314, 203, cNewPassword, Color(25, 35, 25), true, 3);
        else PutString(314, 203, cNewPassword, Color(55, 18, 13), true, 3);
    }

    if (m_cCurFocus != 4)
    {
        if ((m_Misc.bCheckValidName(cNewPassConfirm) != false))
            PutString(314, 227, cNewPassConfirm, Color(25, 35, 25), true, 3);
        else PutString(314, 227, cNewPassConfirm, Color(55, 18, 13), true, 3);
    }

    if ((m_Misc.bCheckValidString(cPassword) == false) || (strlen(cPassword) == 0) ||
        (strlen(cNewPassword) < 8) || (memcmp(cNewPassword, cNewPassConfirm, 10) != 0) ||
        (memcmp(cPassword, cNewPassword, 10) == 0)) bFlag = false;


    if (m_cCurFocus == 1) ShowReceivedString();
    else if ((m_cCurFocus == 2) || (m_cCurFocus == 3) || (m_cCurFocus == 4)) ShowReceivedString(true);

    PutAlignedString(153, 487, 258, UPDATE_SCREEN_ON_CHANGE_PASSWORD5);//"
    PutAlignedString(153, 487, 273, UPDATE_SCREEN_ON_CHANGE_PASSWORD6);//"
    PutAlignedString(153, 487, 288, UPDATE_SCREEN_ON_CHANGE_PASSWORD7);//"

    if ((bFlag == true) && (m_cCurFocus == 5))
        m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(197, 320, 21, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(197, 320, 20, dwTime);

    if (m_cCurFocus == 6)
        m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(370, 320, 17, dwTime);
    else m_pSprite[DEF_SPRID_INTERFACE_ND_BUTTON]->PutSpriteFast(370, 320, 16, dwTime);

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        PlaySound('E', 14, 5);

        switch (iMIbuttonNum)
        {
            case 1:
            case 2:
            case 3:
            case 4:
                m_cCurFocus = iMIbuttonNum;
                break;

            case 5:
                if ((m_Misc.bCheckValidString(cPassword) == false) || (strlen(cPassword) == 0) ||
                    (m_Misc.bCheckValidName(cNewPassword) == false) || (m_Misc.bCheckValidName(cNewPassConfirm) == false) ||
                    (strlen(cNewPassword) == 0) || (memcmp(cNewPassword, cNewPassConfirm, 10) != 0)) break;

                EndInputString();
                ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
                ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));
                ZeroMemory(m_cNewPassword, sizeof(m_cNewPassword));
                ZeroMemory(m_cNewPassConfirm, sizeof(m_cNewPassConfirm));
                strcpy(m_cAccountName, cName);
                strcpy(m_cAccountPassword, cPassword);
                strcpy(m_cNewPassword, cNewPassword);
                strcpy(m_cNewPassConfirm, cNewPassConfirm);
                perform_login_connect();
                ChangeGameMode(DEF_GAMEMODE_ONCONNECTING);
                m_dwConnectMode = MSGID_REQUEST_CHANGEPASSWORD;
                ZeroMemory(m_cMsg, sizeof(m_cMsg));
                strcpy(m_cMsg, "41");
                delete pMI;
                return;

            case 6:
                // Cancel
                ChangeGameMode(DEF_GAMEMODE_ONSELECTCHARACTER);
                delete pMI;
                return;
        }
    }

    if ((msX >= 197) && (msX <= 197 + DEF_BTNSZX) && (msY >= 320) && (msY <= 320 + DEF_BTNSZY)) m_cCurFocus = 5;
    if ((msX >= 370) && (msX <= 370 + DEF_BTNSZX) && (msY >= 320) && (msY <= 320 + DEF_BTNSZY)) m_cCurFocus = 6;
}


void CGame::UpdateScreen_OnVersionNotMatch()
{
    short msX, msY, msZ = {};
    char cLB, cRB;
    char cMIresult;
    int  iMIbuttonNum;
    static class CMouseInterface * pMI;
    uint64_t dwTime = unixtime();
    if (m_cGameModeCount == 0)
    {
        ws->stop();
        ws = nullptr;
        pMI = new class CMouseInterface;
        pMI->AddRect(0, 0, 640, 480);
        m_bEnterPressed = false;
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 120) m_cGameModeCount = 120;
    m_DDraw.back_buffer.clear(sf::Color::Black);
    if (m_bEscPressed == true || m_bEnterPressed == true)
    {
        m_bEscPressed = false;
        m_bEnterPressed = false;
        delete pMI;
        ChangeGameMode(DEF_GAMEMODE_0);
        //SendMessage(m_hWnd, WM_DESTROY, 0, 0);
        return;
    }
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_QUIT, 0, 0, 0, true);
    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_GAME4, 162, 125, 2);
    PutAlignedString(168, 474, 160, UPDATE_SCREEN_ON_VERSION_NO_MATCH1);
    PutAlignedString(168, 474, 180, UPDATE_SCREEN_ON_VERSION_NO_MATCH2);
    PutAlignedString(168, 474, 250, MSG_HOMEPAGE);
    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);

    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if ((cMIresult == DEF_MIRESULT_CLICK) && (iMIbuttonNum == 1))
    {
        ChangeGameMode(DEF_GAMEMODE_0);
        delete pMI;
        //SendMessage(m_hWnd, WM_DESTROY, 0, 0);
        return;
    }
}


void CGame::UpdateScreen_OnGame()
{
    short sVal, sDivX, sModX, sDivY, sModY, sPivotX, sPivotY, sVPXsave, sVPYsave;
    static int  iUpdateRet = -1;
    short msX, msY, msZ, absX, absY, tX, tY;
    char cLB, cRB;
    char cItemColor;
    int  i, iAmount;
    uint64_t dwTime = unixtime();
    static uint64_t dwPrevChatTime = 0;
    //static int   imX = 0, imY = 0;
    static int iColorCounter = 5;
    static int iColorCounter2 = 11;

    if (m_cGameModeCount == 0)
    {
        m_DDraw.back_buffer.clear(sf::Color::Black);
        m_dwFPStime = m_dwCheckConnTime = m_dwCheckSprTime = m_dwCheckChatTime = dwTime;
        m_sFrameCount = 0;
        if (m_bMusicStat) StartBGM();
        //if(m_iLevel < 40) AddEventList(UPDATE_SCREEN_ONGAME12, 10);
    }

    m_cGameModeCount++;
    if (m_cGameModeCount > 20) m_cGameModeCount = 20;
    // ----------------------------------------------------

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    m_dwCurTime = unixtime();

    if (m_bEnterPressed == true)
    {
        m_bEnterPressed = false;

        if ((m_bIsDialogEnabled[7] == true) && (m_stDialogBoxInfo[7].cMode == 1) && (iGetTopDialogBoxIndex() == 7))
        {

            EndInputString();

            m_bEnterPressed = false;
            if (strlen(m_cGuildName) == 0) return;
            if (strcmp(m_cGuildName, "NONE") != 0)
            {
                bSendCommand(MSGID_REQUEST_CREATENEWGUILD, DEF_MSGTYPE_CONFIRM, 0, 0, 0, 0, 0);
                m_stDialogBoxInfo[7].cMode = 2;
                //
            }
        }
        else if ((m_bIsDialogEnabled[17] == true) && (m_stDialogBoxInfo[17].cMode == 1) && (iGetTopDialogBoxIndex() == 17))
        {
            // Drop Item Query

            EndInputString();

            if (m_bSkillUsingStatus == true)
            {
                AddEventList(UPDATE_SCREEN_ONGAME1, 10);
                return;
            }

            if ((m_bIsDialogEnabled[20] == true)
                && ((m_stDialogBoxInfo[20].cMode == 1) || (m_stDialogBoxInfo[20].cMode == 2)))
            {
                AddEventList(UPDATE_SCREEN_ONGAME1, 10);//"You can not give or drop before the actual Item transaction."
                return;
            }

            if ((m_bIsDialogEnabled[4] == true) || (m_bIsDialogEnabled[23] == true) || (m_bIsDialogEnabled[26] == true))
            {
                AddEventList(UPDATE_SCREEN_ONGAME1, 10);
                return;
            }

            if (strlen(m_cAmountString) == 0) return;
            iAmount = atoi(m_cAmountString);

            if ((int)(m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount) < iAmount)
            {
                iAmount = m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount;
            }

            if (iAmount != 0)
            {
                if ((int)(m_pItemList[m_stDialogBoxInfo[17].sView]->m_dwCount) >= iAmount)
                {
                    if (m_stDialogBoxInfo[17].sV1 != 0)
                    {
                        absX = abs(m_stDialogBoxInfo[17].sV1 - m_sPlayerX);
                        absY = abs(m_stDialogBoxInfo[17].sV2 - m_sPlayerY);

                        if ((absX == 0) && (absY == 0))
                            AddEventList(UPDATE_SCREEN_ONGAME5, 10);
                        else if ((absX <= 8) && (absY <= 8))
                        {
                            switch (m_stDialogBoxInfo[17].sV3)
                            {
                                case 1:
                                case 2:
                                case 3:
                                case 4:
                                case 5:
                                case 6:
                                    EnableDialogBox(20, 1, m_stDialogBoxInfo[17].sView, m_stDialogBoxInfo[17].sV3);
                                    m_stDialogBoxInfo[20].sV3 = iAmount;
                                    m_stDialogBoxInfo[20].sV4 = m_wCommObjectID;	// v1.4
                                    m_stDialogBoxInfo[20].sV5 = m_stDialogBoxInfo[17].sV1;
                                    m_stDialogBoxInfo[20].sV6 = m_stDialogBoxInfo[17].sV2;

                                    tX = msX - 117;
                                    tY = msY - 50;
                                    if (tX < 0) tX = 0;
                                    if ((tX + 235) > 639) tX = 639 - 235;
                                    if (tY < 0) tY = 0;
                                    if ((tY + 100) > 479) tY = 479 - 100;
                                    m_stDialogBoxInfo[20].sX = tX;
                                    m_stDialogBoxInfo[20].sY = tY;

                                    ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
                                    strcpy(m_stDialogBoxInfo[20].cStr, m_stDialogBoxInfo[17].cStr);
                                    break;

                                case 20:
                                    EnableDialogBox(20, 3, m_stDialogBoxInfo[17].sView, m_stDialogBoxInfo[17].sV3);
                                    m_stDialogBoxInfo[20].sV3 = iAmount;
                                    m_stDialogBoxInfo[20].sV4 = m_wCommObjectID;
                                    m_stDialogBoxInfo[20].sV5 = m_stDialogBoxInfo[17].sV1;
                                    m_stDialogBoxInfo[20].sV6 = m_stDialogBoxInfo[17].sV2;

                                    tX = msX - 117;
                                    tY = msY - 50;
                                    if (tX < 0) tX = 0;
                                    if ((tX + 235) > 639) tX = 639 - 235;
                                    if (tY < 0) tY = 0;
                                    if ((tY + 100) > 479) tY = 479 - 100;

                                    m_stDialogBoxInfo[20].sX = tX;
                                    m_stDialogBoxInfo[20].sY = tY;

                                    ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
                                    GetNpcName(m_stDialogBoxInfo[17].sV3, m_stDialogBoxInfo[20].cStr);
                                    break;

                                case 15:
                                case 24:
                                    EnableDialogBox(20, 2, m_stDialogBoxInfo[17].sView, m_stDialogBoxInfo[17].sV3);
                                    m_stDialogBoxInfo[20].sV3 = iAmount;
                                    m_stDialogBoxInfo[20].sV4 = m_wCommObjectID;

                                    tX = msX - 117;
                                    tY = msY - 50;
                                    if (tX < 0) tX = 0;
                                    if ((tX + 235) > 639) tX = 639 - 235;
                                    if (tY < 0) tY = 0;
                                    if ((tY + 100) > 479) tY = 479 - 100;
                                    m_stDialogBoxInfo[20].sX = tX;
                                    m_stDialogBoxInfo[20].sY = tY;

                                    ZeroMemory(m_stDialogBoxInfo[20].cStr, sizeof(m_stDialogBoxInfo[20].cStr));
                                    GetNpcName(m_stDialogBoxInfo[17].sV3, m_stDialogBoxInfo[20].cStr);
                                    break;

                                case 1000: // Trade stackable items
                                    // hum, déjà affiché? , j'attends le retour et je désactive!
                                    /*m_stDialogBoxInfo[27].sV1 = m_pItemList[m_stDialogBoxInfo[17].sV4]->m_sSprite;
                                    m_stDialogBoxInfo[27].sV2 = m_pItemList[m_stDialogBoxInfo[17].sV4]->m_sSpriteFrame;
                                    m_stDialogBoxInfo[27].sV3 = iAmount;
                                    m_stDialogBoxInfo[27].sV4 = m_pItemList[m_stDialogBoxInfo[17].sV4]->m_cItemColor;*/

                                    if (m_stDialogBoxExchangeInfo[0].sV1 == -1)			m_stDialogBoxExchangeInfo[0].sItemID = m_stDialogBoxInfo[17].sV4;
                                    else if (m_stDialogBoxExchangeInfo[1].sV1 == -1)	m_stDialogBoxExchangeInfo[1].sItemID = m_stDialogBoxInfo[17].sV4;
                                    else if (m_stDialogBoxExchangeInfo[2].sV1 == -1)	m_stDialogBoxExchangeInfo[2].sItemID = m_stDialogBoxInfo[17].sV4;
                                    else if (m_stDialogBoxExchangeInfo[3].sV1 == -1)	m_stDialogBoxExchangeInfo[3].sItemID = m_stDialogBoxInfo[17].sV4;
                                    else return; // Impossible case, tested at function beginning

                                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_SETEXCHANGEITEM, 0, m_stDialogBoxInfo[17].sV4, iAmount, 0, 0);
                                    break;

                                case 1001:
                                    // Sell List
                                    for (i = 0; i < DEF_MAXSELLLIST; i++)
                                        if (m_stSellItemList[i].iIndex == -1)
                                        {
                                            m_stSellItemList[i].iIndex = m_stDialogBoxInfo[17].sV4;
                                            m_stSellItemList[i].iAmount = iAmount;
                                            m_bIsItemDisabled[m_stDialogBoxInfo[17].sV4] = true;
                                            break;
                                        }
                                    if (i == DEF_MAXSELLLIST) AddEventList(UPDATE_SCREEN_ONGAME6, 10);
                                    break;

                                case 1002:
                                    if (_iGetBankItemCount() >= (DEF_MAXBANKITEMS - 1)) AddEventList(DLGBOX_CLICK_NPCACTION_QUERY9, 10);
                                    else bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, m_stDialogBoxInfo[39].sV1, iAmount, m_stDialogBoxInfo[39].sV5, m_stDialogBoxInfo[39].sV6, m_pItemList[m_stDialogBoxInfo[39].sV1]->m_cName, m_stDialogBoxInfo[39].sV4); //v1.4
                                    break;

                                default:
                                    bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_GIVEITEMTOCHAR, (char)(m_stDialogBoxInfo[17].sView), iAmount, m_stDialogBoxInfo[17].sV1, m_stDialogBoxInfo[17].sV2, m_pItemList[m_stDialogBoxInfo[17].sView]->m_cName);
                                    break;
                            }
                            m_bIsItemDisabled[m_stDialogBoxInfo[17].sView] = true;
                        }
                        else AddEventList(UPDATE_SCREEN_ONGAME7, 10);
                    }
                    else
                    {
                        if (iAmount <= 0)
                        {
                            AddEventList(UPDATE_SCREEN_ONGAME8, 10);
                        }
                        else
                        {
                            bSendCommand(MSGID_COMMAND_COMMON, DEF_COMMONTYPE_ITEMDROP, 0, m_stDialogBoxInfo[17].sView, iAmount, 0, m_pItemList[m_stDialogBoxInfo[17].sView]->m_cName);
                            m_bIsItemDisabled[m_stDialogBoxInfo[17].sView] = true;
                        }
                    }
                }
                else
                {
                    AddEventList(UPDATE_SCREEN_ONGAME9, 10);//"You entered more quantity that you can carry."
                }
            }
            DisableDialogBox(17);
        }
        else
        {
            if (!m_bInputStatus)
            {
                switch (m_cBackupChatMsg[0])
                {
                    case '!':
                    case '@':
                    case '#':
                    case '$':
                    case '^':
                        ZeroMemory(m_cChatMsg, sizeof(m_cChatMsg));
                        m_cChatMsg[0] = m_cBackupChatMsg[0];
                        StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
                        break;
                    default:
                        StartInputString(10, 414, sizeof(m_cChatMsg), m_cChatMsg);
                        ClearInputString();
                        break;
                }
            }
            else
            {
                EndInputString();
                ZeroMemory(G_cTxt, sizeof(G_cTxt));
                ReceiveString((char *)G_cTxt);
                ZeroMemory(m_cBackupChatMsg, sizeof(m_cBackupChatMsg));
                strcpy(m_cBackupChatMsg, G_cTxt);
                if ((m_dwCurTime - dwPrevChatTime) < 700)
                {
                }
                else
                {
                    dwPrevChatTime = m_dwCurTime;
                    if (strlen(G_cTxt) > 0)
                    {
                        if ((G_cTxt[0] == '!') || (G_cTxt[0] == '~'))
                        {
                            if (m_Misc.bCheckIMEString(G_cTxt) == false) return;
                        }
                        bSendCommand(MSGID_COMMAND_CHATMSG, 0, 0, 0, 0, 0, G_cTxt);
                    }
                }
            }
        }
    }

    sVPXsave = m_sViewPointX;
    sVPYsave = m_sViewPointY;

    if ((m_iCameraShakingDegree > 0) && (iUpdateRet != 0))
    {
        m_sViewPointX += m_iCameraShakingDegree - (rand() % m_iCameraShakingDegree * 2);
        m_sViewPointY += m_iCameraShakingDegree - (rand() % m_iCameraShakingDegree * 2);
        m_iCameraShakingDegree--;
        if (m_iCameraShakingDegree <= 0) m_iCameraShakingDegree = 0;
    }
    sPivotX = m_pMapData->m_sPivotX;
    sPivotY = m_pMapData->m_sPivotY;
    sVal = m_sViewPointX - (sPivotX * 32);
    sDivX = sVal / 32;
    sModX = sVal % 32;
    sVal = m_sViewPointY - (sPivotY * 32);
    sDivY = sVal / 32;
    sModY = sVal % 32;
    if (iUpdateRet != 0)
        DrawBackground(sDivX, sModX, sDivY, sModY);

    if (iUpdateRet != 0)
        DrawEffectLights();
    if (iUpdateRet != 0)
        DrawObjects(sPivotX, sPivotY, sDivX, sDivY, sModX, sModY, msX, msY);

    if (iUpdateRet != 0)
    {
        DrawEffects();
        DrawWhetherEffects();
        DrawChatMsgs(-100, 0, 800, 600);
        WhetherObjectFrameCounter();
    }

    if (m_cMapIndex == 26)	// Add Apocalypse map effect (fires in inferniaA)
    {
        m_pEffectSpr[89]->PutTransSprite(1296 - m_sViewPointX, 1283 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
        m_pEffectSpr[89]->PutTransSprite(1520 - m_sViewPointX, 1123 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
        m_pEffectSpr[89]->PutTransSprite(1488 - m_sViewPointX, 3971 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
        m_pEffectSpr[93]->PutTransSprite(2574 - m_sViewPointX, 3677 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
        m_pEffectSpr[93]->PutTransSprite(3018 - m_sViewPointX, 3973 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
    }
    else if (m_cMapIndex == 27)	// Add Apocalypse map effect (fires in inferniaB)
    {
        m_pEffectSpr[89]->PutTransSprite(1293 - m_sViewPointX, 3657 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
        m_pEffectSpr[89]->PutTransSprite(944 - m_sViewPointX, 3881 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
        m_pEffectSpr[89]->PutTransSprite(1325 - m_sViewPointX, 4137 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
        m_pEffectSpr[89]->PutTransSprite(1648 - m_sViewPointX, 3913 - m_sViewPointY, _tmp_iEffectFrame % 12, 0);
    }
    // Add Apocalypse Gate and apocalypse map effects (if no Gate, m_iGatePositX will be -1...
    if ((m_iGatePositX >= m_sViewPointX / 32) && (m_iGatePositX <= m_sViewPointX / 32 + 20)
        && (m_iGatePositY >= m_sViewPointY / 32) && (m_iGatePositY <= m_sViewPointY / 32 + 15))
    {
        m_pEffectSpr[101]->PutTransSprite(m_iGatePositX * 32 - m_sViewPointX - 96, m_iGatePositY * 32 - m_sViewPointY - 69, _tmp_iEffectFrame % 30, dwTime);
    }
    if (iUpdateRet != 0)
        DrawDialogBoxs(msX, msY, msZ, cLB);

    if ((iUpdateRet != 0) && m_bInputStatus)
    {
        if (((m_bIsDialogEnabled[7] == true) && (m_stDialogBoxInfo[7].cMode == 1)) ||
            ((m_bIsDialogEnabled[17] == true) && (m_stDialogBoxInfo[17].cMode == 1)))
        {
        }
        else m_DDraw.DrawShadowBox(0, 413, 639, 429);
        ShowReceivedString();
    }

    if (iUpdateRet != 0)
        ShowEventList(m_dwCurTime);

    if ((iUpdateRet != 0) && (m_stMCursor.cSelectedObjectType == DEF_SELECTEDOBJTYPE_ITEM) &&
        (m_pItemList[m_stMCursor.sSelectedObjectID] != 0))
    {
        cItemColor = m_pItemList[m_stMCursor.sSelectedObjectID]->m_cItemColor;
        if (cItemColor != 0)
        {
            if ((m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos == DEF_EQUIPPOS_LHAND) ||
                (m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos == DEF_EQUIPPOS_RHAND) ||
                (m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos == DEF_EQUIPPOS_TWOHAND))
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSprite]->PutSpriteRGB(msX - m_stMCursor.sDistX, msY - m_stMCursor.sDistY,
                    m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSpriteFrame,
                    m_wWR[cItemColor] - m_wR[0], m_wWG[cItemColor] - m_wG[0], m_wWB[cItemColor] - m_wB[0],
                    dwTime);
            }
            else
            {
                m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSprite]->PutSpriteRGB(msX - m_stMCursor.sDistX, msY - m_stMCursor.sDistY,
                    m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSpriteFrame,
                    m_wR[cItemColor] - m_wR[0], m_wG[cItemColor] - m_wG[0], m_wB[cItemColor] - m_wB[0],
                    dwTime);
            }
        }
        else m_pSprite[DEF_SPRID_ITEMPACK_PIVOTPOINT + m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSprite]->PutSpriteFast(msX - m_stMCursor.sDistX, msY - m_stMCursor.sDistY,
            m_pItemList[m_stMCursor.sSelectedObjectID]->m_sSpriteFrame, dwTime);

        char cStr1[64], cStr2[64], cStr3[64];
        int  iLoc;
        GetItemName(m_pItemList[m_stMCursor.sSelectedObjectID], cStr1, cStr2, cStr3);

        iLoc = 0;
        if (strlen(cStr1) != 0)
        {
            if (m_bIsSpecial)
                PutString(msX, msY + 25, cStr1, Color(0, 255, 50), false, 1);
            else
                PutString(msX, msY + 25, cStr1, Color(255, 255, 255), false, 1);
            iLoc += 15;
        }
        if (strlen(cStr2) != 0)
        {
            PutString(msX, msY + 25 + iLoc, cStr2, Color(150, 150, 150), false, 1);
            iLoc += 15;
        }
        if (strlen(cStr3) != 0)
        {
            PutString(msX, msY + 25 + iLoc, cStr3, Color(150, 150, 150), false, 1);
            iLoc += 15;
        }
        if ((m_pItemList[m_stMCursor.sSelectedObjectID]->m_sLevelLimit != 0) && ((m_pItemList[m_stMCursor.sSelectedObjectID]->m_dwAttribute & 0x00000001) == 0))
        {
            wsprintfA(G_cTxt, "%s: %d", DRAW_DIALOGBOX_SHOP24, m_pItemList[m_stMCursor.sSelectedObjectID]->m_sLevelLimit);//"·¹º§ Á¦ÇÑ: %d"
            PutString(msX, msY + 25 + iLoc, G_cTxt, Color(150, 150, 150), false, 1);
            iLoc += 15;
        }
        if ((m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos != DEF_EQUIPPOS_NONE) && (m_pItemList[m_stMCursor.sSelectedObjectID]->m_wWeight >= 1100))
        {
            int	_wWeight = 0;
            if (m_pItemList[m_stMCursor.sSelectedObjectID]->m_wWeight % 100) _wWeight = 1;
            wsprintfA(G_cTxt, DRAW_DIALOGBOX_SHOP15, m_pItemList[m_stMCursor.sSelectedObjectID]->m_wWeight / 100 + _wWeight);
            PutString(msX, msY + 25 + iLoc, G_cTxt, Color(150, 150, 150), false, 1);
            iLoc += 15;
        }
        if (m_pItemList[m_stMCursor.sSelectedObjectID]->m_cEquipPos != DEF_EQUIPPOS_NONE)
        {
            wsprintfA(G_cTxt, UPDATE_SCREEN_ONGAME10, m_pItemList[m_stMCursor.sSelectedObjectID]->m_wCurLifeSpan);
            PutString(msX, msY + 25 + iLoc, G_cTxt, Color(150, 150, 150), false, 1);
            iLoc += 15;
        }
        if (iLoc == 15)
        {
            iLoc = 0;
            for (int iTmp = 0; iTmp < DEF_MAXITEMS; iTmp++)
            {
                if (m_pItemList[iTmp] != 0)
                {
                    if (strcmp(m_pItemList[iTmp]->m_cName, m_pItemList[m_stMCursor.sSelectedObjectID]->m_cName) == 0) iLoc++;
                }
            }
            if (iLoc > 1)
            {
                wsprintfA(G_cTxt, DEF_MSG_TOTAL_NUMBER, iLoc);
                PutString(msX, msY + 40, G_cTxt, Color(150, 150, 150), false, 1);
            }
        }
    }

    // Add Apocalypse map effect (druncncity bubbles)
    if (m_cMapIndex == 25)
    {
        bAddNewEffect(13, m_sViewPointX + rand() % 640, m_sViewPointY + rand() % 480, 0, 0, -1 * (rand() % 80), 1);
        DrawDruncncity();
    }

    // adding Heldenian turret count
    if ((iUpdateRet != 0) && (m_iHeldenianAresdenLeftTower != -1)
        && (memcmp(m_cCurLocation, "BtField", 7) == 0))
    {
        wsprintfA(G_cTxt, "Aresden Flags : %d", m_iHeldenianAresdenFlags);
        PutString(10, 140, G_cTxt, Color(255, 255, 255));
        wsprintfA(G_cTxt, "Aresden Flags : %d", m_iHeldenianElvineFlags);
        PutString(10, 160, G_cTxt, Color(255, 255, 255));
        wsprintfA(G_cTxt, "Aresden's rest building number : %d", m_iHeldenianAresdenLeftTower);
        PutString(10, 180, G_cTxt, Color(255, 255, 255));
        wsprintfA(G_cTxt, "Elvine's rest building number : %d", m_iHeldenianElvineLeftTower);
        PutString(10, 200, G_cTxt, Color(255, 255, 255));
    }
    DrawTopMsg();

#ifdef _DEBUG
    wsprintfA(G_cTxt, "M(%d,%d) T(%d,%d)", msX, msY, (m_sViewPointX + msX) / 32, (m_sViewPointY + msY) / 32);
    PutString(msX, msY + 30, G_cTxt, Color(255, 255, 255));
#endif

    // LogOut process
#ifdef DEF_EQUILIBRIUM_PROJECT // m_bFullParalyze prevents logout
    if ((m_cLogOutCount > 0) && (m_bFullParalyze == false))
    {
        if ((dwTime - m_dwLogOutCountTime) > 1000)
        {
            m_cLogOutCount--;
            m_dwLogOutCountTime = dwTime;
            wsprintfA(G_cTxt, UPDATE_SCREEN_ONGAME13, m_cLogOutCount);
            AddEventList(G_cTxt, 10);
        }
    }
    else if ((m_cLogOutCount > 0) && (m_bFullParalyze == true) && (m_bForceDisconn == false))
    {
        m_cLogOutCount = -1;
        AddEventList(MOTION_RESPONSE_HANDLER3, 10);//"Logout count cancels if held by Medusa Kiss."
    }
#else
    if (m_cLogOutCount > 0)
    {
        if ((dwTime - m_dwLogOutCountTime) > 1000)
        {
            m_cLogOutCount--;
            m_dwLogOutCountTime = dwTime;
            wsprintfA(G_cTxt, UPDATE_SCREEN_ONGAME13, m_cLogOutCount);//"Logging out...%d"
            AddEventList(G_cTxt, 10);
        }
    }
#endif


    // Logout
    if (m_cLogOutCount == 0)
    {
        ws->stop();
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

    // Restart Process
    if (m_cRestartCount > 0)
    {
        if ((dwTime - m_dwRestartCountTime) > 1000)
        {
            m_cRestartCount--;
            m_dwRestartCountTime = dwTime;
            wsprintfA(G_cTxt, UPDATE_SCREEN_ONGAME14, m_cRestartCount); // "Restarting game...%d"
            AddEventList(G_cTxt, 10);
        }
    }
    // Restart
    if (m_cRestartCount == 0)
    {
        m_cRestartCount = -1;
        bSendCommand(MSGID_REQUEST_RESTART, 0, 0, 0, 0, 0, 0);
        return;
    }

    if (m_iLU_Point > 0) PutString_SprFont(560, 390, "Level Up", 250, 250, 0);

    if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0, 0, 639, 479);
    if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0, 0, 639, 479);

    if (m_bIsObserverMode == true)
    {
        m_DDraw.PutPixel(msX, msY, 255, 255, 255);
        m_DDraw.PutPixel(msX + 1, msY, 255, 255, 255);
        m_DDraw.PutPixel(msX - 1, msY, 255, 255, 255);
        m_DDraw.PutPixel(msX, msY + 1, 255, 255, 255);
        m_DDraw.PutPixel(msX, msY - 1, 255, 255, 255);
    }
    else m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, m_stMCursor.sCursorFrame, dwTime);

    if (iUpdateRet == 0) m_sFrameCount++;
    else m_sFrameCount += 256;

    if (dwTime - m_dwFPStime > 500)
    {
        m_dwFPStime = dwTime;
        m_sFPS = m_sFrameCount >> 7;
        if (m_sFPS < 10) m_sFPS += 6;
        m_sFrameCount = 0;
    }

    if (iUpdateRet != 0)
    {
        if (m_bShowFPS)
        {
            wsprintfA(G_cTxt, "fps : %d", m_sFPS);
            PutString(10, 100, G_cTxt, Color(255, 255, 255));
        }

        // Couleurs 13 et 14 d'armes tournantes // //m_Misc.ColorTransfer
        iColorCounter++;
        if (iColorCounter > 20) iColorCounter = 1;
        if (iColorCounter < 11) //1..6 
        {
            m_wWR[14] += 1; // rouge<->bleu
            m_wWG[14] -= 1;
            m_wWB[14] -= 1;
            if ((iColorCounter % 2) == 1) m_wWR[13] += 1; //blanc<->jaune
            if ((iColorCounter % 3) == 1) m_wWG[13] -= 1;
            m_wWB[13] -= 1;
        }
        else // 7..12
        {
            m_wWR[14] -= 1; // rouge<->bleu
            m_wWG[14] += 1;
            m_wWB[14] += 1;
            if ((iColorCounter % 2) == 1) m_wWR[13] -= 1; // blanc<->jaune
            if ((iColorCounter % 3) == 2) m_wWG[13] += 1;
            m_wWB[13] += 1;
        }
        // Couleur 12 d'armes tournantes
        iColorCounter2++;
        if (iColorCounter2 > 72) iColorCounter2 = 1;
        if (iColorCounter2 <= 36)
        {
            if (iColorCounter2 > 31) m_wWR[12] += 1; // noir<-> rouge
        }
        else // 7..12
        {
            if (iColorCounter2 < 42) m_wWR[12] -= 1; // noir<-> rouge
        }
    }

    // m_iPlayerStatus 0x000F
    iUpdateRet = m_pMapData->iObjectFrameCounter(m_cPlayerName, m_sViewPointX, m_sViewPointY);

    if ((bEffectFrameCounter() == true) && (iUpdateRet == 0)) iUpdateRet = -1;
    if (iUpdateRet == 2)
    {
        m_bCommandAvailable = true;
        m_dwCommandTime = 0;
    }
    CommandProcessor(msX, msY, ((sDivX + sPivotX) * 32 + sModX + msX - 17) / 32 + 1, ((sDivY + sPivotY) * 32 + sModY + msY - 17) / 32 + 1, cLB, cRB);

    m_sViewPointX = sVPXsave;
    m_sViewPointY = sVPYsave;

    if (iUpdateRet > 0) CalcViewPoint();

    if (m_bIsObserverMode)
    {
        if ((dwTime - m_dwObserverCamTime) > 25)
        {
            m_dwObserverCamTime = dwTime;
            CalcViewPoint();
            iUpdateRet = -1;
        }
    }

    if (iUpdateRet > 0)
    {
        if (m_bDrawFlagDir == false)
        {
            m_iDrawFlag++;
            if (m_iDrawFlag >= 25)
            {
                m_iDrawFlag = 25;
                m_bDrawFlagDir = true;
            }
        }
        else
        {
            m_iDrawFlag--;
            if (m_iDrawFlag < 0)
            {
                m_iDrawFlag = 0;
                m_bDrawFlagDir = false;
            }
        }
    }
    // iUpdateRet
}


void CGame::UpdateScreen_OnMainMenu()
{
    short msX, msY, msZ;
    char cLB, cRB, cMIresult;
    int  iMIbuttonNum;
    static class CMouseInterface * pMI;
    uint64_t dwTime = G_dwGlobalTime;

    m_iItemDropCnt = 0;
    m_bItemDrop = false;

    if (m_cGameModeCount == 0)
    {
        if (m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING] != 0)
        {
            delete m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING];
            m_pSprite[DEF_SPRID_INTERFACE_ND_LOADING] = 0;
        }
        draw_version = true;
        EndInputString();
        pMI = new class CMouseInterface;

        pMI->AddRect(385 + m_DDraw.small_screen_offset_x, 178 + m_DDraw.small_screen_offset_y, 548 + m_DDraw.small_screen_offset_x, 199 + m_DDraw.small_screen_offset_y);
        pMI->AddRect(385 + m_DDraw.small_screen_offset_x, 216 + m_DDraw.small_screen_offset_y, 548 + m_DDraw.small_screen_offset_x, 237 + m_DDraw.small_screen_offset_y);
        pMI->AddRect(385 + m_DDraw.small_screen_offset_x, 255 + m_DDraw.small_screen_offset_y, 548 + m_DDraw.small_screen_offset_x, 276 + m_DDraw.small_screen_offset_y);
        m_stMCursor.sX = m_DDraw.GetWidth() / 2;
        m_stMCursor.sY = m_DDraw.GetHeight() / 2;

        m_cCurFocus = 1;
        m_cMaxFocus = 3;

        m_bEnterPressed = false;
        m_cArrowPressed = 0;
    }
    m_cGameModeCount++;
    if (m_cGameModeCount > 100) m_cGameModeCount = 100;

    m_DDraw.back_buffer.clear(sf::Color::Black);

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_MAINMENU, m_DDraw.small_screen_offset_x, m_DDraw.small_screen_offset_y, 0, true);

    cLB = m_stMCursor.LB;
    cRB = m_stMCursor.RB;
    msX = m_stMCursor.sX;
    msY = m_stMCursor.sY;
    msZ = m_stMCursor.sZ;
    
    if ((msX >= 385 + m_DDraw.small_screen_offset_x) && (msY >= 178 + m_DDraw.small_screen_offset_y) && (msX <= 548 + m_DDraw.small_screen_offset_x) && (msY <= 199 + m_DDraw.small_screen_offset_y)) m_cCurFocus = 1;
    if ((msX >= 385 + m_DDraw.small_screen_offset_x) && (msY >= 216 + m_DDraw.small_screen_offset_y) && (msX <= 548 + m_DDraw.small_screen_offset_x) && (msY <= 237 + m_DDraw.small_screen_offset_y)) m_cCurFocus = 2;
    if ((msX >= 385 + m_DDraw.small_screen_offset_x) && (msY >= 255 + m_DDraw.small_screen_offset_y) && (msX <= 548 + m_DDraw.small_screen_offset_x) && (msY <= 276 + m_DDraw.small_screen_offset_y)) m_cCurFocus = 3;

    switch (m_cCurFocus)
    {
        case 1:
            m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->PutSpriteFast(385 + m_DDraw.small_screen_offset_x, 178 + m_DDraw.small_screen_offset_y, 1, dwTime);
            break;
        case 2:
            m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->PutSpriteFast(385 + m_DDraw.small_screen_offset_x, 216 + m_DDraw.small_screen_offset_y, 2, dwTime);
            break;
        case 3:
            m_pSprite[DEF_SPRID_INTERFACE_ND_MAINMENU]->PutSpriteFast(385 + m_DDraw.small_screen_offset_x, 255 + m_DDraw.small_screen_offset_y, 3, dwTime);
            break;
    }

    //m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
    //m_pSprite[DEF_SPRID_INTERFACE_ADDINTERFACE]->PutTransSpriteRGB(msX, msY, 1, 0, 0, 0, dwTime);

    if (m_cArrowPressed != 0)
    {
        switch (m_cArrowPressed)
        {
            case 1:
                m_cCurFocus--;
                if (m_cCurFocus <= 0) m_cCurFocus = m_cMaxFocus;
                break;
            case 3:
                m_cCurFocus++;
                if (m_cCurFocus > m_cMaxFocus) m_cCurFocus = 1;
                break;
        }
        m_cArrowPressed = 0;
    }

    if (m_bEnterPressed == true)
    {
        // Enter
        PlaySound('E', 14, 5);
        m_bEnterPressed = false;
        switch (m_cCurFocus)
        {
            case 1:
                delete pMI;
                ChangeGameMode(DEF_GAMEMODE_ONSELECTSERVER);
                return;
            case 2:
#ifdef DEF_MAKE_ACCOUNT
                ClearContents_OnSelectCharacter();
                delete pMI;
                //ChangeGameMode(DEF_GAMEMODE_ONAGREEMENT);
                ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
#endif
                return;
            case 3:
                delete pMI;
                ChangeGameMode(DEF_GAMEMODE_ONQUIT);
                return;
        }
    }

    iMIbuttonNum = pMI->iGetStatus(msX, msY, cLB, &cMIresult);
    if (cMIresult == DEF_MIRESULT_CLICK)
    {
        PlaySound('E', 14, 5);
        m_cCurFocus = iMIbuttonNum;
        switch (iMIbuttonNum)
        {
            case 1:
                ChangeGameMode(DEF_GAMEMODE_ONSELECTSERVER);
                delete pMI;
                break;

            case 2:
#ifdef DEF_MAKE_ACCOUNT
                ClearContents_OnSelectCharacter();
                delete pMI;
                //ChangeGameMode(DEF_GAMEMODE_ONAGREEMENT);
                ChangeGameMode(DEF_GAMEMODE_ONCREATENEWACCOUNT);
#endif
                return;
            case 3:
                delete pMI;
                ChangeGameMode(DEF_GAMEMODE_ONQUIT);
                return;
        }
    }
    //	if ((msX >= 112) && (msY >= 150) && (msX <= 247) && (msY <= 191)) m_cCurFocus = 1;
    //	if ((msX >= 73) && (msY >= 192) && (msX <= 281) && (msY <= 230)) m_cCurFocus = 2;
    //	if ((msX >= 120) && (msY >= 231) && (msX <= 239) && (msY <= 262)) m_cCurFocus = 3;

    //	if (m_cGameModeCount < 6) m_DDraw.DrawShadowBox(0,0,639,479);
    //	if (m_cGameModeCount < 2) m_DDraw.DrawShadowBox(0,0,639,479);
}


void CGame::_Draw_OnLogin(char * pAccount, char * pPassword, int msX, int msY, int iFrame)
{
    bool bFlag = true;
    uint64_t dwTime = unixtime();

    m_DDraw.back_buffer.clear(sf::Color::Black);

    DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, m_DDraw.small_screen_offset_x, m_DDraw.small_screen_offset_y, 0, true);

    if ((iFrame >= 15) && (iFrame <= 20)) m_pSprite[DEF_SPRID_INTERFACE_ND_LOGIN]->PutTransSprite25(39 + m_DDraw.small_screen_offset_x, 121 + m_DDraw.small_screen_offset_y, 2, true);
    else if (iFrame > 20) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 39 + m_DDraw.small_screen_offset_x, 121 + m_DDraw.small_screen_offset_y, 2, true);

    if (m_cCurFocus != 1)
    {
        if (m_Misc.bCheckValidName(pAccount) != false)
            PutString2(180 + m_DDraw.small_screen_offset_x, 162 + m_DDraw.small_screen_offset_y, pAccount, 200, 200, 200);
        else PutString2(180 + m_DDraw.small_screen_offset_x, 162 + m_DDraw.small_screen_offset_y, pAccount, 200, 100, 100);
    }
    if ((m_Misc.bCheckValidName(pAccount) == false) || (strlen(pAccount) == 0)) bFlag = false;

    if (m_cCurFocus != 2)
    {
        if ((m_Misc.bCheckValidString(pPassword) != false))
            PutString(180 + m_DDraw.small_screen_offset_x, 185 + m_DDraw.small_screen_offset_y, pPassword, Color(200, 200, 200), true, 1);
        else PutString(180 + m_DDraw.small_screen_offset_x, 185 + m_DDraw.small_screen_offset_y, pPassword, Color(200, 100, 100), true, 1);
    }
    if ((m_Misc.bCheckValidString(pPassword) == false) || (strlen(pPassword) == 0)) bFlag = false;

    if (m_cCurFocus == 1)
        ShowReceivedString();
    else
        if (m_cCurFocus == 2)
            ShowReceivedString(true);

    if (bFlag == true)
    {
        if (m_cCurFocus == 3) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 80 + m_DDraw.small_screen_offset_x, 282 + m_DDraw.small_screen_offset_y, 3, true);
    }
    if (m_cCurFocus == 4) DrawNewDialogBox(DEF_SPRID_INTERFACE_ND_LOGIN, 256 + m_DDraw.small_screen_offset_x, 282 + m_DDraw.small_screen_offset_y, 4, true);
    if ((m_bIsHideLocalCursor != true) && (msX != 0) && (msY != 0))
    {
        m_pSprite[DEF_SPRID_MOUSECURSOR]->PutSpriteFast(msX, msY, 0, dwTime);
    }
}
