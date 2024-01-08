//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include <cstring>
#include <fmt/format.h>
#include <chrono>
#include <sstream>
#include <direct.h>
#include "DXC_ddraw.h"
#include "Game.h"
#include "lan_eng.h"

extern long    G_lTransG100[64][64], G_lTransRB100[64][64];
extern long    G_lTransG70[64][64], G_lTransRB70[64][64];
extern long    G_lTransG50[64][64], G_lTransRB50[64][64];
extern long    G_lTransG25[64][64], G_lTransRB25[64][64];
extern long    G_lTransG2[64][64], G_lTransRB2[64][64];

DXC_ddraw::DXC_ddraw(CGame * game)
{
    m_cPixelFormat = 0;

    m_bFullMode = false;

    window_name = fmt::format("Helbreath Xtreme {}.{}.{}", DEF_UPPERVERSION, DEF_LOWERVERSION, DEF_PATCHVERSION);

    this->game = game;
}

DXC_ddraw::~DXC_ddraw()
{
}

bool DXC_ddraw::bInit(bool fullscreen)
{
    this->fullscreen = fullscreen;


    sf::ContextSettings context;

    window.create(sf::VideoMode(screenwidth, screenheight), window_name, (fullscreen ? sf::Style::Fullscreen : (sf::Style::Close)), context);

    handle = window.getSystemHandle();

    if (vsync)
        window.setVerticalSyncEnabled(true);
    else
        window.setVerticalSyncEnabled(false);

    frame_limit = 0;

    front_buffer.create(screenwidth_v, screenheight_v);
    back_buffer.create(screenwidth_v + 300, screenheight_v + 300);
    background_buffer.create(screenwidth_v + 300, screenheight_v + 300);

    sf::Font s;
    s.loadFromFile("fonts/Arya-Regular.ttf");
    _font.insert(std::pair<std::string, sf::Font>("arya", s));

    s.loadFromFile("fonts/OpenSans-Regular.ttf");
    _font.insert(std::pair<std::string, sf::Font>("default", s));

    s.loadFromFile("fonts/PoetsenOne-Regular.ttf");
    _font.insert(std::pair<std::string, sf::Font>("test", s));

    //create_load_list();

    _text.setFont(_font.at("arya"));
    background_buffer_sprite = sf::Sprite(background_buffer.getTexture());
    back_buffer_sprite = sf::Sprite(back_buffer.getTexture());
    front_buffer_sprite = sf::Sprite(front_buffer.getTexture());

    small_screen_offset_x = screenwidth_v / 2 - 640 / 2;
    small_screen_offset_y = screenheight_v / 2 - 480 / 2;

//     back_buffer_sprite.setScale(zoom / 100, zoom / 100);
//     back_buffer_sprite.setPosition({
//         (float(GetWidth()) / 2) - (float(GetVirtualWidth()) * (zoom / 100)) / 2 - sModX,
//         (float(GetHeight()) / 2) - (float(GetVirtualHeight()) * (zoom / 100)) / 2 - sModY
//     });

//     front_buffer_sprite.setScale(zoom / 100, zoom / 100);
//     front_buffer_sprite.setPosition({
//         (float(GetWidth()) / 2) - (float(GetVirtualWidth()) * (zoom / 100)) / 2 - sModX,
//         (float(GetHeight()) / 2) - (float(GetVirtualHeight()) * (zoom / 100)) / 2 - sModY
//     });

//     background_buffer_sprite.setPosition({
//         (float(GetWidth()) / 2) - float(GetVirtualWidth()) / 2,
//         (float(GetHeight()) / 2) - float(GetVirtualHeight()) / 2
//     });
//     
//     back_buffer_sprite.setPosition({
//         (float(GetWidth()) / 2) - float(GetVirtualWidth()) / 2,
//         (float(GetHeight()) / 2) - float(GetVirtualHeight()) / 2
//     });
// 
//     front_buffer_sprite.setPosition({
//         (float(GetWidth()) / 2) - float(GetVirtualWidth()) / 2,
//         (float(GetHeight()) / 2) - float(GetVirtualHeight()) / 2
//     });

    return true;
}

void DXC_ddraw::iFlip()
{
//     back_buffer.display();
// 
//     front_buffer.draw(back_buffer_sprite);
}

void DXC_ddraw::ChangeDisplayMode()
{
    window.close();
    sf::ContextSettings context;
    fullscreen = !fullscreen;
    window.create(sf::VideoMode(screenwidth, screenheight), window_name, (fullscreen ? sf::Style::Fullscreen : sf::Style::Close), context);
}

void DXC_ddraw::text_out(int x, int y, std::string cStr, Color rgb)
{
    //SetTextColor(m_hDC, rgb);
    //::TextOut(m_hDC, x, y, cStr, strlen(cStr));
}

long DXC_ddraw::_CalcMaxValue(int iS, int iD, char cMode, char cMethod, double dAlpha)
{
    long Sum;
    double dTmp;

    switch (cMethod)
    {
    case 1:
        dTmp = (double)iS;
        dTmp = dTmp * dAlpha;
        iS = (int)dTmp;
        Sum = (iS)+(iD);
        if (Sum < iD) Sum = iD;
        break;

    case 2:
        Sum = (iS + iD) / 2;
        break;
    }

    switch (cMode)
    {
    case 'G':
        switch (m_cPixelFormat)
        {
        case 1:
            if (Sum >= 64) Sum = 63; //v1.3
            break;
        case 2:
            if (Sum >= 32) Sum = 31;
            break;
        }
        break;

    default:
        if (Sum >= 32) Sum = 31;
        break;
    }

    return Sum;
}

long DXC_ddraw::_CalcMinValue(int iS, int iD, char cMode)
{
    long Sum;


    Sum = iD - iS;
    if (Sum < 0) Sum = 0;

    switch (cMode)
    {
    case 'G':
        switch (m_cPixelFormat)
        {
        case 1:
            if (Sum >= 64) Sum = 63;
            break;
        case 2:
            if (Sum >= 32) Sum = 31;
            break;
        }
        break;

    default:
        if (Sum >= 32) Sum = 31;
        break;
    }

    return Sum;
}

void DXC_ddraw::DrawShadowBox(short sX, short sY, short dX, short dY, int iType)
{
//     WORD * pDst, wValue;
//     int ix, iy;
// 
//     pDst = (WORD *)m_pBackB4Addr + sX + ((sY)*m_sBackB4Pitch);
// 
//     if (iType == 0)
//     {
//         switch (m_cPixelFormat)
//         {
//         case 1:
//             for (iy = 0; iy <= (dY - sY); iy++)
//             {
//                 for (ix = 0; ix <= (dX - sX); ix++)
//                     pDst[ix] = (pDst[ix] & 0xf7de) >> 1;
// 
//                 pDst += m_sBackB4Pitch;
//             }
//             break;
// 
//         case 2:
//             for (iy = 0; iy <= (dY - sY); iy++)
//             {
//                 for (ix = 0; ix <= (dX - sX); ix++)
//                     pDst[ix] = (pDst[ix] & 0x7bde) >> 1;
// 
//                 pDst += m_sBackB4Pitch;
//             }
//             break;
//         }
//     }
//     else
//     {
//         switch (iType)
//         {
//         case 1:
//             if (m_cPixelFormat == 1)
//                 wValue = 0x38e7;
//             else wValue = 0x1ce7;
//             break;
// 
//         case 2:
//             if (m_cPixelFormat == 1)
//                 wValue = 0x1863;
//             else wValue = 0xc63;
//             break;
//         }
// 
//         for (iy = 0; iy <= (dY - sY); iy++)
//         {
//             for (ix = 0; ix <= (dX - sX); ix++)
//                 pDst[ix] = wValue;
// 
//             pDst += m_sBackB4Pitch;
//         }
//     }
}

void DXC_ddraw::PutPixel(short sX, short sY, uint16_t wR, uint16_t wG, uint16_t wB)
{
//     WORD * pDst;
// 
//     if ((sX < 0) || (sY < 0) || (sX > 639) || (sY > 479)) return;
// 
//     pDst = (WORD *)m_pBackB4Addr + sX + ((sY)*m_sBackB4Pitch);
// 
//     switch (m_cPixelFormat)
//     {
//     case 1:
//         *pDst = (WORD)(((wR >> 3) << 11) | ((wG >> 2) << 5) | (wB >> 3));
//         //*pDst = (WORD)((wR<<11) | (wG<<5) | wB);
//         break;
//     case 2:
//         *pDst = (WORD)(((wR >> 3) << 10) | ((wG >> 3) << 5) | (wB >> 3));
//         //*pDst = (WORD)((wR<<10) | (wG<<5) | wB);
//         break;
//     }
}

uint8_t DXC_ddraw::getRenderTarget()
{
    return drawState;
}

void DXC_ddraw::setRenderTarget(uint8_t s, bool clearbuffer, Color color)
{
    drawState = s;
    if (s == DS_FRONT)
    {
        if (clearbuffer)
            front_buffer.clear(color);
    }
    else if (s == DS_BG)
    {
        if (clearbuffer)
            background_buffer.clear(color);
    }
    else if (s == DS_BACK)
    {
        if (clearbuffer)
            back_buffer.clear(color);
    }
    else if (s == DS_WIN)
    {
        if (clearbuffer)
            window.clear(color);
    }
}

sf::Font & DXC_ddraw::GetFont(std::string font)
{
    auto it = _font.find(font);
    if (it != _font.end())
        return it->second;

    it = _font.find("default");
    if (it != _font.end())
        return it->second;

    throw std::out_of_range("Font not found");
}

void DXC_ddraw::CreateScreenShot()
{
    time_t t = time(0); // get time now
    struct tm * now = localtime(&t);
    
    _text.setFont(_font.at("default"));
    _text.setString("Helbreath Xtreme");
    _text.setFillColor(sf::Color::White);
    sf::FloatRect bounds = _text.getLocalBounds();
    _text.setPosition(float(GetWidth() - 180), 10);
    _text.setCharacterSize(12);

    sf::Texture tex;
    sf::RenderTexture rtex;
    tex.create(window.getSize().x, window.getSize().y);
    rtex.create(window.getSize().x, window.getSize().y);
    tex.update(window);

    sf::Sprite sprite;
    sprite.setTexture(tex);

    rtex.draw(sprite);
    rtex.draw(_text);
    _text.setString(std::format("%F %T"));
    _text.setPosition(float(GetWidth() - 180), 30);
    rtex.draw(_text);

    _mkdir("screenshots");
    char tempstr[300] = {};

    for (int i = 0; i < 100; ++i)
    {
        if (i == 0)
            std::format_to(tempstr, "screenshots\\HelShot%04d%02d%02d_%02d%02d%02d.jpg",
                (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday,
                now->tm_hour, now->tm_min, now->tm_sec);
        else
            std::format_to(tempstr, "screenshots\\HelShot%04d%02d%02d_%02d%02d%02d_%d.jpg",
                (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday,
                now->tm_hour, now->tm_min, now->tm_sec, i);

        if (_access(tempstr, 0) == -1)
        {
            sf::Image img = rtex.getTexture().copyToImage();
            img.flipVertically();
            img.saveToFile(tempstr);

            game->AddEventList(fmt::format(NOTIFYMSG_CREATE_SCREENSHOT1, tempstr).c_str(), 10);
            return;
        }
    }
    game->AddEventList(NOTIFYMSG_CREATE_SCREENSHOT2, 10);
}

void DXC_ddraw::draw(const Drawable & drawable, const RenderStates & states)
{
    if (drawState == DS_FRONT)
    {
        //render to front buffer
        front_buffer.draw(drawable, states);
    }
    else if (drawState == DS_BG)
    {
        //render to background
        background_buffer.draw(drawable, states);
    }
    else if (drawState == DS_BACK)
    {
        //render to back buffer
        back_buffer.draw(drawable, states);
    }
    else if (drawState == DS_WIN)
    {
        //render directly to window
        window.draw(drawable, states);
    }
}

void DXC_ddraw::draw_to(const Drawable & drawable, int draw_mode, const RenderStates & states)
{
    if (draw_mode == DS_FRONT)
    {
        //render to front buffer
        front_buffer.draw(drawable, states);
    }
    else if (draw_mode == DS_BG)
    {
        //render to background
        background_buffer.draw(drawable, states);
    }
    else if (draw_mode == DS_BACK)
    {
        //render to back buffer
        back_buffer.draw(drawable, states);
    }
    else if (draw_mode == DS_WIN)
    {
        //render directly to window
        window.draw(drawable, states);
    }
}

