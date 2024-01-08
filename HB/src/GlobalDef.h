//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

/*** Put here global data for your server ***/
#define NAME_WORLDNAME1 "HelbreathX" // Name for default (1st) server
#define MSG_WORLDNAME1 "Helbreath Xtreme" // Long name for 1st server...
#define MSG_HOMEPAGE "https://www.helbreath.x/"
#define DEF_UPPERVERSION 0
#define DEF_LOWERVERSION 0
#define DEF_PATCHVERSION 1
#define DEF_GAME_SERVER_IP "127.0.0.1"
#define DEF_LOGIN_SERVER_IP "127.0.0.1"
#define DEF_LOGIN_SERVER_PORT 80

#define DEF_MAX_STATS 250
#define DEF_MAX_DELETE_LEVEL 50 // Max level to delete a character from client

#define DEF_SNOW_POSITION_Y 430 // Used to change snow position il status bar changed.(def 426)

/*** Some more compilation options ***/




//#define DEF_USING_WIN_IME // Used for unicode characters (unchecked)
//#define DEF_MAKE_ACCOUNT // Enable acc creation. Missing sprites, fixed!
//#define DEF_SELECTSERVER // Show/Hides server selection screen.

// #define DEF_COMMA_GOLD // Allows to show comma nbe as original HB (ie: 1,200,000)
// #define DEF_4XXP_PER_LVL // limits xp niv 140, then 4 x XP per lvl (affects XP shown as % on status)


// #define _DEBUG // Multi-Client, Instant-logout, Version check, Badwords,
// Mics debug msgs, CtrlQ for admins, Show status, Cursor position
//#define DEF_WINDOWED_MODE // Shows HB in a windowed mode (for debug purpose only, sprite will bug....)


#define DEF_ANTI_HACK
// changes CCM routine to send "real checked time" instead of "sending time". 
// CCM is reduced to 6150, and cKeys reduced to F5

#define DEF_MULTI_SHORTCUT // Uses 6 shortcuts. (F1, F2, F3, F10, F11, F12) 
 // Ctrl+H used for help, Ctrl+W used for tranparency, Ctrl+X for systemdiag.

//#define DEF_EQUILIBRIUM_PROJECT // A enlever avant release, définit un certain nombre de particularités EP


/*** Special conditions ***/
#ifndef _DEBUG
#undef DEF_WINDOWED_MODE
#endif

#ifdef DEF_ANTI_HACK
#define DEF_CCM_DELAY 6150
#define DEF_HIDDEN_UPPERVERSION 4
#define DEF_HIDDEN_LOWERVERSION 96
//that can be whatever number you wish, 1 byte-sized numbers will work fine
#define DEF_VERSIONPLUSMODIFIER 1+(DEF_HIDDEN_LOWERVERSION % 7) 

#else
#define DEF_VERSIONPLUSMODIFIER 0 
#endif
