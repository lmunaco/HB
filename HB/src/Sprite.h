//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include <cstdio>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <fstream>
#include "polyfill.h"

class DXC_ddraw;

class CSprite
{
public:
    CSprite(DXC_ddraw * renderer, const char * cPakFileName, short sNthFile, bool bAlphaEffect = true);
    ~CSprite();

    void PutSpriteRGB(int sX, int sY, int sFrame, int sRed, int sGreen, int sBlue, uint64_t dwTime);

    void PutSpriteFast(int sX, int sY, int sFrame, uint64_t dwTime);
    void PutShiftSpriteFast(int sX, int sY, int shX, int shY, int sFrame, uint64_t dwTime);
    void PutShiftTransSprite2(int sX, int sY, int shX, int shY, int sFrame, uint64_t dwTime);
    void PutSpriteFastWidth(int sX, int sY, int sFrame, int sWidth, uint64_t dwTime);
    void PutSpriteFastNoColorKey(int sX, int sY, int sFrame, uint64_t dwTime);

    void PutTransSprite(int sX, int sY, int sFrame, uint64_t dwTime, int alphaDepth = 30);
    void PutTransSprite2(int sX, int sY, int sFrame, uint64_t dwTime);
    void PutTransSprite_NoColorKey(int sX, int sY, int sFrame, uint64_t dwTime, int alphaDepth = 0);
    void PutTransSpriteRGB_NoColorKey(int sX, int sY, int sFrame, int sRed, int sGreen, int sBlue, uint64_t dwTime);
    void PutTransSpriteRGB(int sX, int sY, int sFrame, int sRed, int sGreen, int sBlue, uint64_t dwTime);
    void PutTransSprite70(int sX, int sY, int sFrame, uint64_t dwTime);
    void PutTransSprite50(int sX, int sY, int sFrame, uint64_t dwTime);
    void PutTransSprite25(int sX, int sY, int sFrame, uint64_t dwTime);
    void PutTransSprite70_NoColorKey(int sX, int sY, int sFrame, uint64_t dwTime);
    void PutTransSprite50_NoColorKey(int sX, int sY, int sFrame, uint64_t dwTime);
    void PutTransSprite25_NoColorKey(int sX, int sY, int sFrame, uint64_t dwTime);

    void PutShadowSpriteClip(int sX, int sY, int sFrame, uint64_t dwTime);
    void PutShadowSprite(int sX, int sY, int sFrame, uint64_t dwTime);

    void PutRevTransSprite(int sX, int sY, int sFrame, uint64_t dwTime, int alphaDepth = 0);

    void PutFadeSprite(short sX, short sY, short sFrame, uint64_t dwTime);
    void PutFadeSpriteDst(uint16_t * pDstAddr, short sPitch, short sX, short sY, short sFrame, uint64_t dwTime);

    void DrawSubSprite(int sX, int sY, int sFrame, uint64_t dwTime = 0, sf::Color color = sf::Color(255, 255, 255));
    void DrawSpriteNCK(int sX, int sY, int sFrame, uint64_t dwTime = 0, sf::Color color = sf::Color(255, 255, 255));
    void DrawRGBNCK(int sX, int sY, int sFrame, uint64_t dwTime, sf::Color color = sf::Color(255, 255, 255));
    void DrawSprite(int sX, int sY, int sFrame, uint64_t dwTime = 0, sf::Color color = sf::Color(255, 255, 255));
    void DrawScaledSprite(int sX, int sY, int sFrame, int sWidth, int sHeight, uint64_t dwTime = 0, sf::Color color = sf::Color(255, 255, 255));
    void DrawRGB(int sX, int sY, int sFrame, uint64_t dwTime, sf::Color color = sf::Color(255, 255, 255));
    void DrawWidth(int sX, int sY, int sFrame, int sWidth, uint64_t dwTime, sf::Color color = sf::Color(255, 255, 255));
    void DrawShadow(int sX, int sY, int sFrame, uint64_t dwTime, sf::Color color = sf::Color(255, 255, 255));

    bool _bCheckCollison(int sX, int sY, short sFrame, int msX, int msY);
    void _GetSpriteRect(int sX, int sY, int sFrame);
    void _iCloseSprite();
    bool _iOpenSprite();

    void draw_to(int sX, int sY, int sFrame, uint64_t dwTime, sf::Color color, int draw_mode);

    RECT m_rcBound{};
    uint64_t m_dwRefTime = 0;
    bool m_bIsSurfaceEmpty = true;
    bool m_bOnCriticalSection = false;
    bool m_bAlphaEffect = false;
    short m_sPivotX = 0, m_sPivotY = 0;
    uint32_t m_dwBitmapFileStartLoc = 0;
    short m_sPitch = 0;
    uint64_t m_iTotalFrame = 0;
    char m_cAlphaDegree = 0;
    uint16_t m_wBitmapSizeX = 0, m_wBitmapSizeY = 0;
    uint16_t m_wColorKey = 0;
    std::string m_cPakFileName;
    stBrush * m_stBrush = nullptr;
    uint64_t wPageid = 0;
    DXC_ddraw * renderer;

private:
    sf::Sprite * sprite_ = nullptr;
    sf::Texture texture;
};
