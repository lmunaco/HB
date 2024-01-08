//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <functional>
#include <mutex>
#include <queue>
#include <process.h>
#include <direct.h>
#include <set>
#include <deque>
#include <chrono>
#include <queue>
#include <atomic>
#include <mutex>
#include <future>
#include <memory>
#include <fmt/core.h>
#include <fmt/format.h>

#include "GlobalDef.h"
#include "Sprite.h"
#include "SpriteID.h"
#include "Misc.h"
#include "StrTok.h"
#include "Msg.h"
#include "Effect.h"
#include "MapData.h"
#include "ActionID.h"
#include "NetMessages.h"
#include "MouseInterface.h"
#include "CharInfo.h"
#include "Item.h"
#include "Magic.h"
#include "Skill.h"
#include "DynamicObjectID.h"
#include "BuildItem.h"
#include "ItemName.h"
#include "Fps.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ixwebsocket/IXWebSocketCloseConstants.h>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include "DXC_ddraw.h"
#include "defines.h"

#include "streams.h"

#include "json.hpp"

using sf::Keyboard;
using sf::Color;
using namespace std::chrono;
using namespace std::chrono_literals;

namespace ix
{
class WebSocket;
struct WebSocketMessage;
using WebSocketMessagePtr = std::unique_ptr<WebSocketMessage>;
};

#pragma region defines
//v2.18
#define DEF_BTNSZX				74
#define DEF_BTNSZY				20
#define DEF_LBTNPOSX			30
#define DEF_RBTNPOSX			154
#define DEF_BTNPOSY				292

#define DEF_INDEX4_MSGID		0
#define DEF_INDEX2_MSGTYPE		4

#define DEF_SOCKETBLOCKLIMIT	300

#define DEF_MAXSPRITES			25000
#define DEF_MAXTILES			1000
#define DEF_MAXEFFECTSPR		300
#define DEF_MAXSOUNDEFFECTS		200
#define DEF_MAXCHATMSGS			500
#define DEF_MAXWHISPERMSG		5
#define DEF_MAXCHATSCROLLMSGS	80
#define DEF_MAXEFFECTS			600
#define DEF_CHATTIMEOUT_A		4000
#define DEF_CHATTIMEOUT_B		500
#define DEF_CHATTIMEOUT_C		2000
#define DEF_MAXITEMS			50
#define DEF_MAXBANKITEMS		121
#define DEF_MAXGUILDSMAN		32
#define DEF_MAXMENUITEMS		150
#define DEF_TEXTDLGMAXLINES		300

#define DEF_MAXMAGICTYPE		100
#define DEF_MAXSKILLTYPE		60
#define DEF_MAXWHETHEROBJECTS	600
#define DEF_MAXBUILDITEMS		100
#define DEF_MAXGAMEMSGS			300
#define DEF_MAXITEMNAMES		1000
#define DEF_MAXGUILDNAMES		100
#define DEF_MAXSELLLIST			12

#define WM_USER_GAMESOCKETEVENT	WM_USER + 2000
#define WM_USER_LOGSOCKETEVENT	WM_USER + 2001
#define WM_USER_MP3_EVENT		WM_USER + 2002

#define DEF_GAMEMODE_0					-2
#define DEF_GAMEMODE_ONQUIT					-1
#define DEF_GAMEMODE_ONMAINMENU				0
#define DEF_GAMEMODE_ONCONNECTING			1
#define DEF_GAMEMODE_ONLOADING				2
#define DEF_GAMEMODE_ONWAITINGINITDATA		3
#define DEF_GAMEMODE_ONMAINGAME				4
#define DEF_GAMEMODE_ONCONNECTIONLOST		5
#define DEF_GAMEMODE_ONMSG					6
#define DEF_GAMEMODE_ONCREATENEWACCOUNT		7
#define DEF_GAMEMODE_ONLOGIN				8
#define DEF_GAMEMODE_ONQUERYFORCELOGIN		9
#define DEF_GAMEMODE_ONSELECTCHARACTER		10
#define DEF_GAMEMODE_ONCREATENEWCHARACTER	11
#define DEF_GAMEMODE_ONWAITINGRESPONSE		12
#define DEF_GAMEMODE_ONQUERYDELETECHARACTER 13
#define DEF_GAMEMODE_ONLOGRESMSG			14
#define DEF_GAMEMODE_ONCHANGEPASSWORD		15
#define DEF_GAMEMODE_ONVERSIONNOTMATCH		17
#define DEF_GAMEMODE_ONINTRODUCTION			18
#define DEF_GAMEMODE_ONAGREEMENT			19
#define DEF_GAMEMODE_ONSELECTSERVER			20
#define DEF_GAMEMODE_ONINPUTKEYCODE			21

#define DEF_SERVERTYPE_GAME			1
#define DEF_SERVERTYPE_LOG			2

#define DEF_CURSORSTATUS_0		0
#define DEF_CURSORSTATUS_PRESSED	1
#define DEF_CURSORSTATUS_SELECTED	2
#define DEF_CURSORSTATUS_DRAGGING	3

#define DEF_SELECTEDOBJTYPE_DLGBOX	1
#define DEF_SELECTEDOBJTYPE_ITEM	2

#define DEF_DOUBLECLICKTIME			300
#define DEF_MAXPARTYMEMBERS			8
#define DEF_MAXCRUSADESTRUCTURES	300
#pragma endregion

extern void * G_hWnd;

class connection;
using connection_ptr = std::shared_ptr<connection>;
using nlohmann::json;
class CMapData;

using std::make_shared;
using std::make_unique;
using sf::RenderStates;
using sf::RenderWindow;
using sf::Sprite;
using sf::Color;
using sf::Drawable;

#define FONT_BUILTIN 0
#define FONT_TREBMS6PX 1
#define FONT_TREBMS8PX 2
#define FONT_TREBMS10PX 3
#define FONT_TREBMS12PX 4
#define FONT_TREBMS14PX 5
#define FONT_TREBMS16PX 6

class CGame
{
public:
    bool inside_vm = false;
    bool autologin = false;
    bool loggedin = false;
    Fps fps;
    uint64_t ping = 0;
    bool draw_version = true;

    std::mutex screenupdate;
    std::mutex socketmut;

    struct MsgQueueEntry
    {
        MsgQueueEntry()
        {
            data = 0;
            size = 0;
        }
        ~MsgQueueEntry() { delete[] data; }
        char * data;
        uint32_t size;
    };
    using MsgQueue = std::list<std::shared_ptr<MsgQueueEntry>>;
    MsgQueue socketpipe;
    MsgQueue loginpipe;
    void PutMsgQueue(MsgQueue & q, char * data, uint32_t size);
    void PutMsgQueue(std::shared_ptr<MsgQueueEntry>, MsgQueue & q);
    std::shared_ptr<MsgQueueEntry> GetMsgQueue();
    std::shared_ptr<MsgQueueEntry> GetLoginMsgQueue();

    std::unique_ptr<ix::WebSocket> ws;
    std::unique_ptr<ix::WebSocket> log_ws;

    std::string game_server_address;
    uint16_t game_server_port;
    std::string login_server_address;
    uint16_t login_server_port;

    void on_message(const ix::WebSocketMessagePtr & msg);
    bool is_connected() const;
    bool is_closed() const;
    bool is_connecting() const;
    bool is_closing() const;

    void perform_connect();
    void perform_login_connect();
    void connection_loss_gamemode();

    int write(const char * data, const uint64_t size);
    int write(StreamWrite & sw);
    int write(nlohmann::json & obj);

    int log_write(const char * data, const uint64_t size);
    int log_write(StreamWrite & sw);
    int log_write(nlohmann::json & obj);

    void handle_stop();
    void close(uint32_t code = ix::WebSocketCloseConstants::kNormalClosureCode, const std::string & reason = ix::WebSocketCloseConstants::kNormalClosureMessage);

    void OnEvent(sf::Event event);



    void CheckActiveAura(short sX, short sY, uint64_t dwTime, short sOwnerType);
    void CheckActiveAura2(short sX, short sY, uint64_t dwTime, short sOwnerType);

    void DrawDialogBox_ChangeStatsMajestic(short msX, short msY);
    void DlgBoxClick_ChangeStatsMajestic(short msX, short msY);

    char cStateChange1;
    char cStateChange2;
    char cStateChange3;

    int m_iTeleportMapCount;
    void ResponseTeleportList(char * pData);
    void ResponseChargedTeleport(char * pData);

    void ItemEquipHandler(char cItemID);
    void ReleaseEquipHandler(char cEquipPos);

    int  iGetManaCost(int iMagicNo);
    void UseMagic(int iMagicNo);
    bool _bCheckMoveable(short sx, short sy);
    bool FindGuildName(char * pName, int * ipIndex);
    void bItemDrop_SkillDialog();
    void bItemDrop_IconPannel(short msX, short msY);
    void bItemDrop_Character();
    void bItemDrop_Inventory(short msX, short msY);
    void bItemDrop_ItemUpgrade();
    void bItemDrop_SellList(short msX, short msY);
    void bItemDrop_ExchangeDialog(short msX, short msY);
    void bItemDrop_Bank(short msX, short msY);
    void bItemDrop_ExternalScreen(char cItemID, short msX, short msY);
    void CrusadeWarResult(int iWinnerSide);
    void CrusadeContributionResult(int iWarContribution);
    void CannotConstruct(int iCode);
    void DrawTopMsg();
    void SetTopMsg(const char * pString, unsigned char iLastSec);
    void DrawObjectFOE(int ix, int iy, int iFrame);
    void GrandMagicResult(char * pMapName, int iV1, int iV2, int iV3, int iV4, int iHP1, int iHP2, int iHP3, int iHP4);
    void MeteorStrikeComing(int iCode);
    void _Draw_OnLogin(char * pAccount, char * pPassword, int msX, int msY, int iFrame = 60000);
    void DrawNewDialogBox(char cType, int sX, int sY, int iFrame, bool bIsNoColorKey = false, bool bIsTrans = false);
    void AddMapStatusInfo(char * pData, bool bIsLastData);
    void _RequestMapStatus(const char * pMapName, int iMode);
    int  GetCharKind(char * str, int index);
    void ReceiveString(char * pString);
    void EndInputString();
    void ClearInputString();
    void ShowReceivedString(bool bIsHide = false);
    bool GetText(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
    bool bReadItemNameConfigFile();
    void DrawDialogBoxs(short msX, short msY, short msZ, char cLB);
    void DrawDialogBox_Character(short msX, short msY);//1
    void DrawDialogBox_Inventory(int msX, int msY);//2
    void DrawDialogBox_Magic(short msX, short msY, short msZ);//3
    void DrawDialogBox_GuildMenu(short msX, short msY);//7
    void DrawDialogBox_GuildOperation(short msX, short msY);//8
    void DrawDialogBox_GuideMap(short msX, short msY, char cLB);//9
    void DrawDialogBox_Chat(short msX, short msY, short msZ, char cLB);//10
    void DrawDialogBox_Shop(short msX, short msY, short msZ, char cLB);//11
    void DrawDialogBox_LevelUpSetting(short msX, short msY);//12
    void DrawDialogBox_CityHallMenu(short msX, short msY);//13
    void DrawDialogBox_Bank(short msX, short msY, short msZ, char cLB);//14
    void DrawDialogBox_Skill(short msX, short msY, short msZ, char cLB);//15
    void DrawDialogBox_MagicShop(short msX, short msY, short msZ);//16
    void DrawDialogBox_QueryDropItemAmount();//17
    void DrawDialogBox_Text(short msX, short msY, short msZ, char cLB);//18
    void DrawDialogBox_SysMenu(short msX, short msY, char cLB);//19
    void DrawDialogBox_NpcActionQuery(short msX, short msY);//20
    void DrawDialogBox_NpcTalk(short msX, short msY, char cLB);//21
    void DrawDialogBox_Map();//22
    void DrawDialogBox_SellorRepairItem(short msX, short msY);//23
    void DrawDialogBox_Fishing(short msX, short msY);//24
    void DrawDialogBox_ShutDownMsg(short msX, short msY);//25
    void DrawDialogBox_SkillDlg(short msX, short msY, short msZ, char cLB);//26
    void DrawDialogBox_Exchange(short msX, short msY);//27
    void DrawDialogBox_Quest(int msX, int msY);//28
    void DrawDialogBox_GaugePannel();//29
    void DrawDialogBox_IconPannel(short msX, short msY);//30
    void DrawDialogBox_SellList(short msX, short msY);//31
    void DrawDialogBox_Party(short msX, short msY);//32
    void DrawDialogBox_CrusadeJob(short msX, short msY);//33
    void DrawDialogBox_ItemUpgrade(int msX, int msY);//34
    void DrawDialogBox_Help(int msX, int msY);//35
    void DrawDialogBox_Commander(int msX, int msY);//36
    void DrawDialogBox_Constructor(int msX, int msY);//37
    void DrawDialogBox_Soldier(int msX, int msY);//38
    void DrawDialogBox_ItemDrop(short msX, short msY);//4
    void DrawDialogBox_WarningMsg(short msX, short msY);//6
    void DrawDialogBox_15AgeMsg(short msX, short msY);//5
    void DrawDialogBox_FeedBackCard(short msX, short msY);//40
    void DisplayCommaNumber_G_cTxt(int iGold);

    void DrawDialogBox_ConfirmExchange(short msX, short msY); //41

    void bItemDrop_Slates();
    void DlgBoxClick_Slates(short msX, short msY);
    void DrawDialogBox_Slates(short msX, short msY, short msZ, char cLB);//40

    bool _bCheckDlgBoxClick(short msX, short msY);
    void DlgBoxClick_WarningMsg(short msX, short msY);
    void DlgBoxClick_15AgeMsg(short msX, short msY);
    void DlgBoxClick_ItemDrop(short msX, short msY);
    void DlgBoxClick_Character(short msX, short msY);
    void DlgBoxClick_Inventory(short msX, short msY);
    void DlgBoxClick_Magic(short msX, short msY);
    void DlgBoxClick_GuildMenu(short msX, short msY);
    void DlgBoxClick_GuildOp(short msX, short msY);
    void DlgBoxClick_Shop(short msX, short msY);
    void DlgBoxClick_LevelUpSettings(short msX, short msY);
    void DlgBoxClick_CityhallMenu(short msX, short msY);
    void DlgBoxClick_Bank(short msX, short msY);
    void DlgBoxClick_Skill(short msX, short msY);
    void DlgBoxClick_MagicShop(short msX, short msY);
    void DlgBoxClick_FeedBackCard(short msX, short msY);
    void DlgBoxClick_Text(short msX, short msY);
    void DlgBoxClick_SysMenu(short msX, short msY);
    void DlgBoxClick_NpcActionQuery(short msX, short msY);
    void DlgBoxClick_NpcTalk(int msX, int msY);
    void DlgBoxClick_ItemSellorRepair(short msX, short msY);
    void DlgBoxClick_Fish(short msX, short msY);
    void DlgBoxClick_ShutDownMsg(short msX, short msY);
    void DlgBoxClick_SkillDlg(short msX, short msY);
    void DlgBoxClick_Exchange(short msX, short msY);

    void DlgBoxClick_Quest(int msX, int msY);
    void DlgBoxClick_SellList(short msX, short msY);
    void DlgBoxClick_IconPannel(short msX, short msY);
    void DlgBoxClick_Party(short msX, short msY);
    void DlgBoxClick_CrusadeJob(short msX, short msY);
    void DlgBoxClick_ItemUpgrade(int msX, int msY);
    void DlgBoxClick_Help(int msX, int msY);
    void DlgBoxClick_Commander(int msX, int msY);
    void DlgBoxClick_Constructor(int msX, int msY);
    void DlgBoxClick_Soldier(int msX, int msY);
    void NotifyMsgHandler(char * pData);
    void NotifyMsg_GlobalAttackMode(char * pData);
    void NotifyMsg_QuestReward(char * pData);
    void NotifyMsg_QuestContents(char * pData);
    void NotifyMsg_ItemColorChange(char * pData);
    void NotifyMsg_DropItemFin_CountChanged(char * pData);
    void NotifyMsg_CannotGiveItem(char * pData);
    void NotifyMsg_GiveItemFin_CountChanged(char * pData);
    void NotifyMsg_SetExchangeItem(char * pData);
    void NotifyMsg_OpenExchageWindow(char * pData);
    void NotifyMsg_DownSkillIndexSet(char * pData);
    void NotifyMsg_AdminInfo(char * pData);
    void NotifyMsg_WhetherChange(char * pData);
    void NotifyMsg_FishChance(char * pData);
    void NotifyMsg_EventFishMode(char * pData);
    void NotifyMsg_NoticeMsg(char * pData);
    void NotifyMsg_RatingPlayer(char * pData);
    void NotifyMsg_CannotRating(char * pData);
    void NotifyMsg_PlayerShutUp(char * pData);
    void NotifyMsg_TimeChange(char * pData);
    void NotifyMsg_Hunger(char * pData);
    void NotifyMsg_PlayerProfile(char * pData);
    void NotifyMsg_WhisperMode(bool bActive, char * pData);
    void NotifyMsg_PlayerStatus(bool bOnGame, char * pData);
    void NotifyMsg_Charisma(char * pData);
    void NotifyMsg_ItemRepaired(char * pData);
    void NotifyMsg_RepairItemPrice(char * pData);
    void NotifyMsg_CannotRepairItem(char * pData);
    void NotifyMsg_CannotSellItem(char * pData);
    void NotifyMsg_SellItemPrice(char * pData);
    void NotifyMsg_ShowMap(char * pData);
    void NotifyMsg_SkillUsingEnd(char * pData);
    void NotifyMsg_TotalUsers(char * pData);
    void NotifyMsg_MagicEffectOff(char * pData);
    void NotifyMsg_MagicEffectOn(char * pData);
    void NotifyMsg_SetItemCount(char * pData);
    void NotifyMsg_ItemDepleted_EraseItem(char * pData);
    void NotifyMsg_ServerChange(char * pData);
    void NotifyMsg_Skill(char * pData);
    void NotifyMsg_DropItemFin_EraseItem(char * pData);
    void NotifyMsg_GiveItemFin_EraseItem(char * pData);
    void NotifyMsg_EnemyKillReward(char * pData);
    void NotifyMsg_PKcaptured(char * pData);
    void NotifyMsg_PKpenalty(char * pData);
    void NotifyMsg_ItemToBank(char * pData);
    void NotifyMsg_ItemLifeSpanEnd(char * pData);
    void NotifyMsg_ItemReleased(char * pData);
    void NotifyMsg_LevelUp(char * pData);
    void NotifyMsg_SettingSuccess(char * pData);
    void NotifyMsg_MP(char * pData);
    void NotifyMsg_SP(char * pData);
    void NotifyMsg_SkillTrainSuccess(char * pData);
    void NotifyMsg_MagicStudyFail(char * pData);
    void NotifyMsg_MagicStudySuccess(char * pData);
    void NotifyMsg_DismissGuildsMan(char * pData);
    void NotifyMsg_NewGuildsMan(char * pData);
    void NotifyMsg_CannotJoinMoreGuildsMan(char * pData);
    void NotifyMsg_GuildDisbanded(char * pData);
    void NotifyMsg_Exp(char * pData);
    void NotifyMsg_Killed(char * pData);
    void NotifyMsg_HP(char * pData);
    void NotifyMsg_ItemPurchased(char * pData);
    void NotifyMsg_DismissGuildReject(char * pData);
    void NotifyMsg_DismissGuildApprove(char * pData);
    void NotifyMsg_JoinGuildReject(char * pData);
    void NotifyMsg_JoinGuildApprove(char * pData);
    void NotifyMsg_QueryDismissGuildPermission(char * pData);
    void NotifyMsg_QueryJoinGuildPermission(char * pData);
    void NotifyMsg_ItemObtained(char * pData);
    void NotifyMsg_ForceDisconn(char * pData);
    void NotifyMsg_BanGuildMan(char * pData);

    void ResponsePanningHandler(char * pData);
    void UpdateScreen_OnSelectServer();
    void StartInputString(int sX, int sY, unsigned char iLen, char * pBuffer, bool bIsHide = false);
    void _SetIlusionEffect(int iOwnerH);
    int _iGetFOE(int iStatus);
    void NoticementHandler(char * pData);
    void GetItemName(char * cItemName, uint32_t dwAttribute, char * pStr1, char * pStr2, char * pStr3);
    void GetItemName(class CItem * pItem, char * pStr1, char * pStr2, char * pStr3);
    void _InitOnCreateNewCharacter();
    void _LoadGameMsgTextContents();
    bool _bCheckCurrentBuildItemStatus();
    bool _bCheckBuildItemStatus();
    bool _bDecodeBuildItemContents();
    bool _bCheckBadWords(char * pMsg);
    void GetNpcName(short sType, char * pName);


#ifdef DEF_MAKE_ACCOUNT
    int m_iAgreeView;
    void _LoadAgreementTextContents(char cType);
    void UpdateScreen_OnAgreement();
    void UpdateScreen_OnCreateNewAccount();
#endif


    void UseShortCut(int num);
    void UpdateScreen();
    void UpdateScreen_OnMainMenu();
    void UpdateScreen_OnGame();
    void UpdateScreen_OnConnecting();
    void UpdateScreen_OnWaitInitData();
    void MakeSprite(const char * FileName, short sStart, short sCount, bool bAlphaEffect = true);
    void MakeTileSpr(const char * FileName, short sStart, short sCount, bool bAlphaEffect = true);
    void MakeEffectSpr(const char * FileName, short sStart, short sCount, bool bAlphaEffect = true);
    void UpdateScreen_OnLoading(bool bActive);
    void UpdateScreen_OnConnectionLost();
    void UpdateScreen_OnLogin();
    void UpdateScreen_OnMsg();
    void UpdateScreen_OnQuit();
    void UpdateScreen_OnQueryForceLogin();
    void UpdateScreen_OnQueryDeleteCharacter();
    void UpdateScreen_OnWaitingResponse();
    void UpdateScreen_OnCreateNewCharacter();
    void UpdateScreen_OnSelectCharacter();
    void UpdateScreen_OnLogResMsg();
    void UpdateScreen_OnSelectCharacter(short sX, short sY, short msX, short msY, bool bIgnoreFocus = false);
    void UpdateScreen_OnChangePassword();
    void UpdateScreen_OnLoading_Progress();
    void UpdateScreen_OnVersionNotMatch();
    void NpcTalkHandler(char * pData);
    int  _iGetWeaponSkillType();
    void SetCameraShakingEffect(short sDist, int iMul = 0);
    bool bDlgBoxPress_SkillDlg(short msX, short msY);
    bool bDlgBoxPress_Inventory(short msX, short msY);
    bool bDlgBoxPress_Character(short msX, short msY);
    void ClearSkillUsingStatus();
    bool bCheckItemOperationEnabled(char cItemID);
    void _DrawThunderEffect(int sX, int sY, int dX, int dY, int rX, int rY, char cType);
    void DrawLine(int x0, int y0, int x1, int y1, Color color);
    void DrawLine2(int x0, int y0, int x1, int y1, int iR, int iG, int iB, int iA = 255);
    void DrawLine(int x0, int y0, int x1, int y1, int iR, int iG, int iB, int iA = 255);
    void SetWhetherStatus(bool bStart, char cType);
    void WhetherObjectFrameCounter();
    void DrawWhetherEffects();
    bool bCheckExID(char * pName);
    bool bCheckLocalChatCommand(const char * pMsg);
    char GetOfficialMapName(const char * pMapName, char * pName);
    int iGetLevelExp(int iLevel);
    int _iCalcTotalWeight();
    void DrawVersion();
    bool _bIsItemOnHand();
    void DynamicObjectHandler(char * pData);
    bool _bCheckItemByType(char cType);
    void _DrawBlackRect(int iSize);
    void DrawNpcName(short sX, short sY, short sOwnerType, int iStatus);
    void DrawObjectName(short sX, short sY, char * pName, int iStatus);
    void PlaySound(char cType, int iNum, int iDist, long lPan = 0);
    void _RemoveChatMsgListByObjectID(int iObjectID);
    void _LoadTextDlgContents(int cType);
    int  _iLoadTextDlgContents2(int iType);
    void DrawChatMsgs(short sX, short sY, short dX, short dY);
    void RequestFullObjectData(owner_type owner_type_, uint16_t wObjectID);
    bool bInitSkillCfgList();
    void DlbBoxDoubleClick_Inventory(short msX, short msY);
    void DlbBoxDoubleClick_Character(short msX, short msY);
    void DlbBoxDoubleClick_GuideMap(short msX, short msY);
    bool _bCheckDlgBoxDoubleClick(short msX, short msY);
    void EraseItem(char cItemID);
    void RetrieveItemHandler(char * pData);
    void CivilRightAdmissionHandler(char * pData);
    void _Draw_CharacterBody(short sX, short sY, short sType);
    void ClearContents_OnSelectCharacter();
    void ClearContents_OnCreateNewAccount();
    void _Draw_UpdateScreen_OnCreateNewAccount();
    bool _bDraw_OnCreateNewCharacter(char * pName, short msX, short msY, int iPoint);
    bool _bGetIsStringIsNumber(char * pStr);
    bool bInitMagicCfgList();
    bool __bDecodeContentsAndBuildItemForSaleList(char * pBuffer);
    void _LoadShopMenuContents(char cType);
    void PutChatScrollList(char * pMsg, char cType);
    void RequestTeleportAndWaitData();
    void DrawEffectLights();
    void PointCommandHandler(int indexX, int indexY, char cItemID = -1);
    void DrawEffects();
    void bAddNewEffect(short sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1 = 1);
    void AddEventList(const char * pTxt, char cColor = 0, bool bDupAllow = true);
    void ShowEventList(uint64_t dwTime);
    void SetItemCount(const char * pItemName, uint32_t dwCount);
    void _ShiftGuildOperationList();
    void _PutGuildOperationList(char * pName, char cOpMode);
    void DisbandGuildResponseHandler(char * pData);
    void InitPlayerCharacteristics(char * pData);
    void CreateNewGuildResponseHandler(char * pData);
    void _GetHairColorColor(int iColorType, int * pR, int * pG, int * pB);
    void InitGameSettings();
    void CommonEventHandler(char * pData);
    bool _bCheckDraggingItemRelease(short msX, short msY);
    void _SetItemOrder(char cWhere, char cItemID);
    int iGetTopDialogBoxIndex();
    void DisableDialogBox(int iBoxID);
    void EnableDialogBox(int iBoxID, int cType, int sV1, int sV2, char * pString = 0);
    void InitItemList(char * pData);
    int _iCheckDlgBoxFocus(short msX, short msY, char cButtonSide);
    void GetPlayerTurn();
    bool __fastcall DrawObject_OnDead(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnDying(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnMagic(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnAttack(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnAttackMove(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnStop(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnMove_ForMenu(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnMove(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnDamageMove(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnRun(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnDamage(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool __fastcall DrawObject_OnGetItem(int indexX, int indexY, int sX, int sY, bool bTrans, uint64_t dwTime, int msX, int msY);
    bool bEffectFrameCounter();
    void ClearGuildNameList();
    void DrawBackground(short sDivX, short sModX, short sDivY, short sModY);
    void DrawChatMsgBox(short sX, short sY, int iChatIndex, bool bIsPreDC);
    void ReleaseTimeoverChatMsg();
    void ChatMsgHandler(char * pData);
    void ReleaseUnusedSprites();
    void OnKeyUp(WPARAM wParam);
    void OnSysKeyDown(WPARAM wParam);
    void OnSysKeyUp(WPARAM wParam);
    void ChangeGameMode(char cMode);
    void PutString(int iX, int iY, std::string pString, Color color);
    void PutString(int iX, int iY, std::string pString, Color color, bool bHide, char cBGtype, bool bIsPreDC = false);
    void PutString2(int iX, int iY, std::string pString, short sR, short sG, short sB);
    void PutAlignedString(int iX1, int iX2, int iY, std::string pString, short sR = 0, short sG = 0, short sB = 0);
    void PutString_SprFont(int iX, int iY, std::string pStr, short sR, short sG, short sB);
    void PutString_SprFont2(int iX, int iY, std::string pStr, short sR, short sG, short sB);
    void PutString_SprFont3(int iX, int iY, std::string pStr, short sR, short sG, short sB, bool bTrans = false, int iType = 0);
    void PutString_SprNum(int iX, int iY, std::string pStr, short sR, short sG, short sB);
    void PutFontStringSize(std::string fontname, int iX, int iY, std::string text, Color color, int size);
    void PutFontString(std::string fontname, int iX, int iY, std::string pString, Color color = Color(255, 255, 255));
    void PutChatString(int iX, int iY, std::string, Color color = Color(255, 255, 255));
    void LogRecvMsgHandler(char * pData);
    void LogResponseHandler(char * pData);
    void OnTimer();
    void LogEventHandler(char * pData);
    void _ReadMapData(short sPivotX, short sPivotY, char * pData);
    void MotionEventHandler(char * pData);
    void InitDataResponseHandler(char * pData);
    void InitPlayerResponseHandler(char * pData);
    void ConnectionEstablishHandler(char cWhere);
    void MotionResponseHandler(char * pData);
    void GameRecvMsgHandler(uint32_t dwMsgSize, char * pData);
    void DrawObjects(short sPivotX, short sPivotY, short sDivX, short sDivY, short sModX, short sModY, short msX, short msY);
    bool bSendCommand(uint32_t dwMsgID, uint16_t wCommand, char cDir, int iV1, int iV2, int iV3, const char * pString, int iV4 = 0); // v1.4
    char cGetNextMoveDir(short sX, short sY, short dstX, short dstY, bool bMoveCheck = false, bool bMIM = false);
    void CommandProcessor(short msX, short msY, short indexX, short indexY, char cLB, char cRB);
    void CalcViewPoint();
    void OnKeyDown(WPARAM wParam);
    void Quit();
    bool bInit();

    void ReserveFightzoneResponseHandler(char * pData);
    int _iGetAttackType();
    bool __bDecodeBuildItemContents(char * pBuffer);
    int _iGetBankItemCount();
    int _iGetTotalItemNum();
    void StartBGM();

    int bHasHeroSet(short Appr3, short Appr4, char OwnerType);
    void ShowHeldenianVictory(short sSide);
    void DrawDialogBox_Resurect(short msX, short msY);
    void DlgBoxClick_Resurect(short msX, short msY);
    void DrawDialogBox_CMDHallMenu(short msX, short msY);
    void DlgBoxClick_CMDHallMenu(short msX, short msY);
    void ResponseHeldenianTeleportList(char * pData);
    void DKGlare(int iWeaponColor, int iWeaponIndex, int * iWeaponGlare);
    void DrawDruncncity();
    void DlgBoxClick_ConfirmExchange(short msX, short msY);
    void Abaddon_corpse(int sX, int sY);
    void DrawAngel(int iSprite, short sX, short sY, char cFrame, uint64_t dwTime);


    bool _ItemDropHistory(char * ItemName);
    CGame();
    virtual ~CGame();

    struct
    {
        short sX;
        short sY;
        short sZ;
        bool LB;
        bool RB;
        bool MB;
        short sCursorFrame;
        char cPrevStatus;
        char cSelectedObjectType;
        short sSelectedObjectID;
        short sPrevX, sPrevY, sDistX, sDistY;
        uint64_t dwSelectClickTime;
        short sClickX, sClickY;
    } m_stMCursor;

    struct
    {
        int   sV1, sV2, sV3, sV4, sV5, sV6, sV7, sV8, sV9, sV10, sV11, sV12, sV13, sV14; // v1.4 short
        uint32_t dwV1, dwV2, dwT1;
        bool  bFlag;
        short sX, sY;
        short sSizeX, sSizeY;
        short sView;
        char  cStr[32], cStr2[32], cStr3[32], cStr4[32];
        char  cMode;
        bool  bIsScrollSelected;
    } m_stDialogBoxInfo[61];
    char m_cDialogBoxOrder[61];
    bool m_bIsDialogEnabled[61];
    struct
    {
        int   sV1, sV2, sV3, sV4, sV5, sV6, sV7, sItemID;
        uint32_t dwV1;
        char  cStr1[32], cStr2[32];
    } m_stDialogBoxExchangeInfo[8];
    struct
    {
        int iIndex;
        int iAmount;
    } m_stSellItemList[DEF_MAXSELLLIST];

    struct
    {
        char cName[22];
        char cOpMode;
    } m_stGuildOpList[100];

    struct
    {
        uint64_t dwTime;
        char  cColor;
        char  cTxt[96];
    } m_stEventHistory[6];

    struct
    {
        uint64_t dwTime;
        char  cColor;
        char  cTxt[96];
    } m_stEventHistory2[6];

    struct
    {
        short sX, sY, sBX;
        char cStep;
    } m_stWhetherObject[DEF_MAXWHETHEROBJECTS];

    struct
    {
        bool bIsQuestCompleted;
        short sWho, sQuestType, sContribution, sTargetType, sTargetCount, sX, sY, sRange;
        short sCurrentCount;
        char cTargetName[22];
    } m_stQuest;

    struct
    {
        char cStatus;
        char cName[12];
    } m_stPartyMember[DEF_MAXPARTYMEMBERS];

    struct
    {
        short sX, sY;
        char cType;
        char cSide;
    } m_stCrusadeStructureInfo[DEF_MAXCRUSADESTRUCTURES];

    struct
    {
        char cName[12];
    } m_stPartyMemberNameList[DEF_MAXPARTYMEMBERS + 1];

    // v2.171 2002-6-14
    struct
    {
        uint64_t dwRefTime;
        int iGuildRank;
        char cCharName[12];
        char cGuildName[24];
    } m_stGuildName[DEF_MAXGUILDNAMES];

    struct
    {
        int iIndex;
        char mapname[12];
        int iX;
        int iY;
        int iCost;
    } m_stTeleportList[20];

    sf::Sound m_pCSound[30];
    sf::Sound m_pMSound[160];
    sf::Sound m_pESound[55];
    sf::SoundBuffer CSoundBuffer[30];
    sf::SoundBuffer MSoundBuffer[160];
    sf::SoundBuffer ESoundBuffer[55];
    sf::SoundBuffer bgmbuffer;
    sf::Sound m_pBGM;
    DXC_ddraw  m_DDraw;

    CMisc      m_Misc;
    CSprite * m_pSprite[DEF_MAXSPRITES];
    CSprite * m_pTileSpr[DEF_MAXTILES];
    CSprite * m_pEffectSpr[DEF_MAXEFFECTSPR];
    CMapData * m_pMapData;
    CMsg * m_pChatMsgList[DEF_MAXCHATMSGS];
    CMsg * m_pChatScrollList[DEF_MAXCHATSCROLLMSGS];
    CMsg * m_pWhisperMsg[DEF_MAXWHISPERMSG];
    CEffect * m_pEffectList[DEF_MAXEFFECTS];
    CItem * m_pItemList[DEF_MAXITEMS];
    CItem * m_pBankList[DEF_MAXBANKITEMS];
    CMagic * m_pMagicCfgList[DEF_MAXMAGICTYPE];
    CSkill * m_pSkillCfgList[DEF_MAXSKILLTYPE];
    CMsg * m_pMsgTextList[DEF_TEXTDLGMAXLINES];
    CMsg * m_pMsgTextList2[DEF_TEXTDLGMAXLINES];
    CMsg * m_pAgreeMsgTextList[DEF_TEXTDLGMAXLINES];
    CMsg * m_pExID;
    CBuildItem * m_pBuildItemList[DEF_MAXBUILDITEMS];
    CBuildItem * m_pDispBuildItemList[DEF_MAXBUILDITEMS];


    CItem * m_pItemForSaleList[DEF_MAXMENUITEMS];
    CCharInfo * m_pCharList[4];
    CMsg * m_pGameMsgList[DEF_MAXGAMEMSGS];
    CItemName * m_pItemNameList[DEF_MAXITEMNAMES];

    char * m_pInputBuffer;
    uint32_t m_inputMaxLen;

    uint64_t G_dwGlobalTime;
    uint64_t m_dwCommandTime; //v2.15 SpeedHack
    uint32_t m_dwConnectMode;
    uint64_t m_dwTime;
    uint64_t m_dwCurTime;
    uint64_t m_dwCheckConnTime, m_dwCheckSprTime, m_dwCheckChatTime;
    uint64_t m_dwDialogCloseTime;
    uint64_t m_dwLogOutCountTime;//was uint32_t
    uint64_t m_dwRestartCountTime;
    uint64_t m_dwWOFtime; //v1.4
    uint64_t m_dwObserverCamTime;
    uint64_t m_dwDamagedTime;
    uint64_t m_dwSpecialAbilitySettingTime;
    uint64_t m_dwCommanderCommandRequestedTime;
    uint64_t m_dwTopMsgTime;
    uint64_t m_dwEnvEffectTime;

    //v2.2
    uint64_t m_dwMonsterEventTime;
    short m_sMonsterID;
    short m_sEventX, m_sEventY;


    //v2.183 Hunter Mode;
    bool m_bHunter = false;
    bool m_bAresden = false;
    bool m_bCitizen = false;
    //v2.183 Hunter Mode;

    bool m_bZoomMap = false;
    bool m_bIsProgramActive = true;
    bool m_bCommandAvailable = true;
    bool m_bSoundFlag = false;
    bool m_bSoundStat = false;
    bool m_bMusicStat = false;
    bool m_bIsItemEquipped[DEF_MAXITEMS];
    bool m_bIsItemDisabled[DEF_MAXITEMS];
    bool m_bIsGetPointingMode = false;
    bool m_bEnterPressed = false;
    bool m_bEscPressed = false;
    bool m_bCtrlPressed = false;
    bool m_bRunningMode = false;
    bool m_bShiftPressed = false;
    bool m_altPressed = false;

    bool m_bDialogTrans = false;
    bool m_bIsCombatMode = false;
    bool m_bIsSafeAttackMode = false;
    bool m_bSkillUsingStatus = false;
    bool m_bItemUsingStatus = false;
    bool m_bIsWhetherEffect = false;
    bool m_bSuperAttackMode = false;
    bool m_bIsObserverMode = false;
    bool m_bIsObserverCommanded = false;
    bool m_bIsPoisoned = false;
    bool m_bIsFirstConn = false;
    bool m_bIsConfusion = false;
    bool m_bIsRedrawPDBGS = false;
    bool m_bDrawFlagDir = false;
    bool m_bIsCrusadeMode = false;
    bool m_bIsSpecialAbilityEnabled = false;
    bool m_bInputStatus = false;
    bool m_bToggleScreen = false;
    bool m_bIsSpecial = false;

    bool m_bIsF1HelpWindowEnabled = false;
    bool m_bIsTeleportRequested = false;
    bool m_bIsPrevMoveBlocked = false;
    bool m_bIsHideLocalCursor = false;

    bool m_bForceDisconn = false;
    bool m_bForceAttack = false;
    bool m_bParalyze = false;

    short m_sFrameCount;
    short m_sFPS;
    uint64_t m_dwFPStime;
    bool  m_bShowFPS;

    int m_iFightzoneNumber;
    int m_iFightzoneNumberTemp;
    int m_iPlayerApprColor; // v1.4
    bool m_iHP;//was int			// Hit Point
    bool m_iMP;//was int			// Mana Point
    bool m_iSP;//was int			// Staminar Point
    int m_iAC;						// Armor Class
    int m_iTHAC0;					// To Hit Armor Class 0

    int m_iLevel, m_iStr, m_iInt, m_iVit, m_iDex, m_iMag, m_iCharisma, m_iExp, m_iContribution;
    int m_iAngelicStr, m_iAngelicInt, m_iAngelicDex, m_iAngelicMag;

    int m_iEnemyKillCount;
    int m_iPKCount;
    int m_iRewardGold;
    int m_iGuildRank, m_iTotalGuildsMan;
    int m_iPointCommandType;
    int m_iTotalChar;
    //	int m_iAccountStatus;
    short m_sMagicShortCut;
    int m_iLU_Point;
    int m_iCameraShakingDegree;
    int m_iSuperAttackLeft;
    int m_iAccntYear, m_iAccntMonth, m_iAccntDay;
    int m_iIpYear, m_iIpMonth, m_iIpDay;
    int m_iDownSkillIndex;

    int m_iIlusionOwnerH;
    int m_iApprColor_IE;
    int m_iInputX, m_iInputY;
    int m_iPDBGSdivX, m_iPDBGSdivY;			   // Pre-Draw Background Surface
    short m_sRecentShortCut;
    short m_sShortCut[6]; // 6 shortcuts
    uint64_t m_iSpecialAbilityTimeLeftSec;
    int m_iDrawFlag;
    int m_iSpecialAbilityType;
    uint64_t m_iTimeLeftSecAccount, m_iTimeLeftSecIP;
    int m_iCrusadeDuty;
    int m_iLogServerPort;
    int m_iRating; //Rating

    int m_iPrevMoveX, m_iPrevMoveY;
    int m_iBlockYear, m_iBlockMonth, m_iBlockDay;
    unsigned char m_iTopMsgLastSec;
    int m_iConstructionPoint;
    int m_iWarContribution;
    int m_iConstructLocX, m_iConstructLocY;
    int m_iNetLagCount;
    int m_iTeleportLocX, m_iTeleportLocY;
    int m_iTotalPartyMember;
    int m_iPartyStatus;
    int m_iGizonItemUpgradeLeft;

    short m_sItemEquipmentStatus[DEF_MAXITEMEQUIPPOS];
    short m_sPlayerX, m_sPlayerY;
    short m_sPlayerObjectID;
    short m_sPlayerType;
    short m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4;
    int m_iPlayerStatus;
    short m_sMCX, m_sMCY;
    short m_sCommX, m_sCommY;
    int   m_iCastingMagicType;
    short m_sDamageMove, m_sDamageMoveAmount;
    short m_sAppr1_IE, m_sAppr2_IE, m_sAppr3_IE, m_sAppr4_IE;
    int m_iStatus_IE;
    short m_sViewDstX, m_sViewDstY;
    short m_sViewPointX, m_sViewPointY;
    short m_sVDL_X, m_sVDL_Y;

    uint16_t m_wCommObjectID;
    uint16_t m_wEnterGameType;
    uint16_t m_wR[16], m_wG[16], m_wB[16];
    uint16_t m_wWR[16], m_wWG[16], m_wWB[16];

    unsigned char m_cInputMaxLen;
    char m_cEdit[4];
    char G_cTxt[128];
    char m_cGameModeCount;
    char m_cBGMmapName[12];
    char m_cItemOrder[DEF_MAXITEMS];
    char m_cAmountString[12];
    char m_cLogOutCount;
    char m_cRestartCount;
    char m_cGameMode;
    char m_cWhisperIndex;
    char m_cAccountName[12];
    char m_cAccountPassword[12];
    char m_cAccountAge[12];
    char m_cNewPassword[12];
    char m_cNewPassConfirm[12];
    char m_cAccountCountry[18];
    char m_cAccountSSN[32];
    char m_cEmailAddr[52];
    char m_cAccountQuiz[46];// Quiz
    char m_cAccountAnswer[22];
    char m_cPlayerName[12];
    char m_cPlayerDir;
    char m_cMsg[200];
    char m_cLocation[12];
    char m_cCurLocation[12];
    char m_cGuildName[22];
    char m_cMCName[12];
    char m_cMapName[12];
    char m_cMapMessage[32];
    char m_cMapIndex;
    char m_cPlayerTurn;
    char m_cCommand;
    char m_cCurFocus, m_cMaxFocus;
    char m_cEnterCheck, m_cTabCheck, m_cLeftArrowCheck;
    char m_cArrowPressed;
    char m_cLogServerAddr[16];
    char m_cChatMsg[64];
    char m_cBackupChatMsg[64];
    char m_cGender, m_cSkinCol, m_cHairStyle, m_cHairCol, m_cUnderCol;
    char m_ccStr, m_ccVit, m_ccDex, m_ccInt, m_ccMag, m_ccChr;
    char m_cLU_Str, m_cLU_Vit, m_cLU_Dex, m_cLU_Int, m_cLU_Mag, m_cLU_Char;

    char m_cMagicMastery[DEF_MAXMAGICTYPE];
    unsigned char m_cSkillMastery[DEF_MAXSKILLTYPE]; // v1.4
    char m_cWorldServerName[32];
    char m_cDetailLevel;
    char m_cMenuDir, m_cMenuDirCnt, m_cMenuFrame;
    char m_cSoundVolume, m_cMusicVolume;
    char m_cWhetherEffectType;
    char m_cWhetherStatus;
    char m_cIlusionOwnerType;
    char m_cName_IE[12];
    char m_sViewDX, m_sViewDY;
    char m_cCommandCount;
    char m_cLoading;
    char m_cDiscount;

    char m_cStatusMapName[12];
    char m_cTopMsg[64];
    char m_cTeleportMapName[12];
    char m_cConstructMapName[12];
    char m_cGameServerName[22]; //  Gateway

    char m_cItemDrop[25][25];

    RECT m_rcPlayerRect, m_rcBodyRect;
    void * m_hWnd;

    HANDLE m_hPakFile;

    bool m_bWhisper;
    bool m_bShout;

    bool m_bItemDrop;
    int  m_iItemDropCnt;

    char m_cGateMapName[12];
    int  m_iGatePositX, m_iGatePositY;
    int m_iHeldenianAresdenLeftTower;
    int m_iHeldenianElvineLeftTower;
    int m_iHeldenianAresdenFlags;
    int m_iHeldenianElvineFlags;
    bool m_bIllusionMVT;
    int m_iGameServerMode;
    bool m_bIsXmas;
    bool m_bUsingSlate;
    bool m_bIsHeldenianMode;
    bool m_bIsHeldenianMap;

    bool m_bIsAvatarMode;
    bool m_bIsAvatarMessenger;

    //bool _bDecodeCraftItemContents();
    //bool __bDecodeCraftItemContents(char *pBuffer);
    //bool _bCheckCraftItemStatus();
    //bool _bCheckCurrentCraftItemStatus();

    class CBuildItem * m_pCraftItemList[DEF_MAXBUILDITEMS];
    class CBuildItem * m_pDispCraftItemList[DEF_MAXBUILDITEMS];
    int   m_iContributionPrice;

    char m_cTakeHeroItemName[100]; // hero item str


#ifdef DEF_ANTI_HACK
    uint32_t	m_dwCRC32;
    uint16_t	m_wCRC16_1;
    uint16_t	m_wCRC16_2;
    bool	m_bUseCRC_2;

    bool m_bHackMoveBlocked;
#endif

#ifdef DEF_EQUILIBRIUM_PROJECT
    bool m_bFullParalyze;// lvl 20 para spell that prevents even casting turning, hitting, using item
    bool m_bVK_OEM_7Pressed;
#endif


};
