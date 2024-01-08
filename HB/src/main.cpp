//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

// -------------------------------------------------------------- 
//                      Helbreath Client 						  
//
//                      1998.10 by Soph
//
// --------------------------------------------------------------


#include <cstdio>
#include <cstdlib>
#include <process.h>
#include <iostream>
#include <string>
#include <cstdint>
#include <sys/timeb.h>
#include <condition_variable>
#include <filesystem>
#include <intrin.h>
#include <fmt/format.h>
#include <ixwebsocket/IXWebSocket.h>
#include "Game.h"
#include "GlobalDef.h"

char G_cSpriteAlphaDegree;
CGame * game;

bool isrunning = true;
bool is_ui_running = true;
bool restart_ui = false;

std::condition_variable cv;
std::condition_variable cv2;

#if defined(WIN32)
#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <WinBase.h>
#endif

bool isvm()
{
    unsigned int cpuInfo[4] = {};
    __cpuid((int *)cpuInfo, 1);
    return ((cpuInfo[2] >> 31) & 1) == 1;
}

constexpr uint64_t BUFSIZE = 2048;
#define UNLIMITED_CLIENTS

int main(int argc, char * argv[])
{
#if defined(WIN32)
    ix::initNetSystem();
#endif
    srand((unsigned)time(nullptr));

    std::filesystem::current_path("../");
    std::wstring p = std::filesystem::current_path().native();

    game = new CGame();

#if !defined(_DEBUG) && !defined(UNLIMITED_CLIENTS)
    game->m_cAccountName = received_login.substr(0, pos);
    game->m_cAccountPassword = received_login.substr(pos + 1);
    game->autologin = true;
#endif

    game->inside_vm = isvm();


    if (argc >= 2)
    {
        for (int i = 0; i < argc; ++i)
        {
#ifdef _DEBUG

            if (memcmp(argv[i], "-data=", 6) == 0)
            {
                char * ctx;
                char * c = strtok_s(argv[i], "=:", &ctx);
//                 game->m_cAccountName = strtok_s(nullptr, "=:", &ctx);
//                 game->m_cAccountPassword = strtok_s(nullptr, "=:", &ctx);
                strcpy(game->m_cAccountName, strtok_s(nullptr, "=:", &ctx));
                strcpy(game->m_cAccountPassword, strtok_s(nullptr, "=:", &ctx));
                game->autologin = true;
            }
            else if (memcmp(argv[i], "-login=", 7) == 0)
            {
                char * ctx;
                char * c = strtok_s(argv[i], "=:", &ctx);
                game->login_server_address = strtok_s(nullptr, "=:", &ctx);
                game->login_server_port = atoi(strtok_s(nullptr, "=:", &ctx));
                game->autologin = true;
            }

            //debug only stuff
            else if (memcmp(argv[i], "-res=", 5) == 0)
            {
                char * ctx;
                char * c = strtok_s(argv[i], "=x", &ctx);
                game->m_DDraw.screenwidth = atoi(strtok_s(nullptr, "=x", &ctx));
                game->m_DDraw.screenheight = atoi(strtok_s(nullptr, "=x", &ctx));
                game->m_DDraw.autoresolution = true;
            }
            else if (memcmp(argv[i], "-vres=", 6) == 0)
            {
                char * ctx;
                char * c = strtok_s(argv[i], "=x", &ctx);
                game->m_DDraw.screenwidth_v = atoi(strtok_s(nullptr, "=x", &ctx));
                game->m_DDraw.screenheight_v = atoi(strtok_s(nullptr, "=x", &ctx));
                game->m_DDraw.autovresolution = true;
            }
#endif
        }
    }

    if (game->bInit() == false)
    {
        return false;
    }

    game->m_DDraw.window.setMouseCursorGrabbed(game->m_DDraw.clipmousegame);
    game->m_DDraw.window.setMouseCursorVisible(false);

    sf::Event event;
    sf::RenderWindow & window = game->m_DDraw.window;

    while (window.isOpen() && isrunning)
    {
        //timers first
        game->OnTimer();
        game->fps.update();

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                isrunning = false;
                window.close();
                break;
            }

            game->OnEvent(event);
        }

        {
            std::unique_lock<std::mutex> l(game->screenupdate);
            window.clear(sf::Color::Black);
            game->m_DDraw.window.clear(sf::Color::Black);

            game->UpdateScreen();

            game->m_DDraw.window.setPosition(sf::Vector2i(0, 0));

            window.display();
        }
    }
    isrunning = false;

    game->Quit();
    if (window.isOpen())
        window.close();

    if (game->ws)
        game->ws->stop();
    delete game;

#if !defined(_DEBUG) && !defined(UNLIMITED_CLIENTS)
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
#endif

    return 0;
}
