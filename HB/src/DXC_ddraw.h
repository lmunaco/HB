//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include <cmath>
#include <memory>
#include <cstring>
#include "Misc.h"
#include "GlobalDef.h"
#include <SFML/Graphics.hpp>
#include "polyfill.h"

using sf::RenderStates;
using sf::RenderWindow;
using sf::Sprite;
using sf::Color;
using sf::Drawable;

#define DS_FRONT 0
#define DS_BACK 1
#define DS_BG 2
#define DS_WIN 3

class CGame;

class DXC_ddraw
{
public:
    DXC_ddraw(CGame * game);
    ~DXC_ddraw();
    bool bInit(bool fullscreen);
    void ChangeDisplayMode();
    void text_out(int x, int y, std::string cStr, Color rgb);
    long _CalcMinValue(int iS, int iD, char cMode);
    long _CalcMaxValue(int iS, int iD, char cMode, char cMethod, double dAlpha);
    void PutPixel(short sX, short sY, uint16_t wR, uint16_t wG, uint16_t wB);
    void DrawShadowBox(short sX, short sY, short dX, short dY, int iType = 0);
    void iFlip();
    void CreateScreenShot();

    long    m_lTransG100[64][64], m_lTransRB100[64][64];
    long    m_lTransG70[64][64], m_lTransRB70[64][64];
    long    m_lTransG50[64][64], m_lTransRB50[64][64];
    long    m_lTransG25[64][64], m_lTransRB25[64][64];
    long    m_lTransG2[64][64], m_lTransRB2[64][64];
    long    m_lFadeG[64][64], m_lFadeRB[64][64];

    bool m_bFullMode;

    CGame * game;

    RECT  m_rcClipArea, m_rcFlipping;
    short  m_sBackB4Pitch;
    char   m_cPixelFormat;
    
    uint8_t drawState = DS_BACK;
    std::string window_name;
    uint32_t frame_limit = 60;
    uint32_t frame_limit_bg = 30;
    std::map<std::string, sf::Font> _font;
    bool clipmousegame = false;
    bool clipmousewindow = false;
    bool isactive = true;
    uint16_t screenwidth;
    uint16_t screenheight;
    uint16_t screenwidth_v;
    uint16_t screenheight_v;
    uint16_t small_screen_offset_x = 0;
    uint16_t small_screen_offset_y = 0;
    bool autoresolution = false;
    bool autovresolution = false;
    bool fullscreen = false;
    bool wasinactive = false;
    bool vsync = false;
    bool fullscreenswap = false;
    std::string workingdirectory;

    sf::RenderTexture front_buffer;
    sf::RenderTexture back_buffer;
    sf::RenderTexture background_buffer;
    sf::Sprite front_buffer_sprite;
    sf::Sprite back_buffer_sprite;
    sf::Sprite background_buffer_sprite;
    sf::RenderWindow window;
    sf::WindowHandle handle;
    sf::Text _text;

    uint8_t getRenderTarget();
    void setRenderTarget(uint8_t s, bool clearbuffer = false, Color color = Color(0, 0, 0));
    void SetResolution(uint16_t width, uint16_t height)
    {
        screenwidth = width;
        screenheight = height;
    }
    void SetVirtualResolution(uint16_t width, uint16_t height)
    {
        screenwidth_v = width;
        screenheight_v = height;
    }
    void draw(const Drawable & drawable, const RenderStates & states = RenderStates::Default);
    void draw_to(const Drawable & drawable, int draw_mode, const RenderStates & states = RenderStates::Default);
    __forceinline uint16_t GetWidth() { return screenwidth; }
    __forceinline uint16_t GetHeight() { return screenheight; }

    __forceinline uint16_t GetVirtualWidth() { return screenwidth_v; }
    __forceinline uint16_t GetVirtualHeight() { return screenheight_v; }
    sf::Font & GetFont(std::string font = "default");
};
