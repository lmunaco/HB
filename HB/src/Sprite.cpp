//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include <fmt/format.h>
#include <iostream>
#include "Sprite.h"
#include "DXC_ddraw.h"

extern char G_cSpriteAlphaDegree;

extern int G_iAddTable31[64][510], G_iAddTable63[64][510];
extern int G_iAddTransTable31[510][64], G_iAddTransTable63[510][64];

extern long    G_lTransG100[64][64], G_lTransRB100[64][64];
extern long    G_lTransG70[64][64], G_lTransRB70[64][64];
extern long    G_lTransG50[64][64], G_lTransRB50[64][64];
extern long    G_lTransG25[64][64], G_lTransRB25[64][64];
extern long    G_lTransG2[64][64], G_lTransRB2[64][64];
extern void SetRect(RECT & lprc, int xLeft, int yTop, int xRight, int yBottom);

extern uint64_t unixtime();

CSprite::CSprite(DXC_ddraw * renderer, const char * cPakFileName, short sNthFile, bool bAlphaEffect)
{
    this->renderer = renderer;

    m_stBrush = nullptr;
    m_bIsSurfaceEmpty = true;

    m_cAlphaDegree = 1;
    m_bOnCriticalSection = false;
    m_iTotalFrame = 0;

    sprite_ = nullptr;

    m_cPakFileName = cPakFileName;
    m_bAlphaEffect = bAlphaEffect;
    wPageid = sNthFile;

    std::ifstream hPakFile(fmt::format("sprites\\{}.pak", m_cPakFileName), std::ios::in | std::ios::binary);
    
    if (!hPakFile.is_open())
    {
        throw std::exception("Sprite file not open");
    }

    if (!sprite_)
    {
        uint64_t iASDstart = 0;
        hPakFile.seekg(24 + wPageid * 8, std::ios::beg);
        hPakFile.read((char *)&iASDstart, 4);
        hPakFile.seekg(iASDstart + 100, std::ios::beg);
        hPakFile.read((char *)&m_iTotalFrame, 4);

        m_dwBitmapFileStartLoc = iASDstart + (108 + (12 * m_iTotalFrame));
        m_stBrush = new stBrush[m_iTotalFrame];
        hPakFile.read((char *)m_stBrush, 12 * m_iTotalFrame);

        sprite_ = new sf::Sprite[m_iTotalFrame];
    }

    hPakFile.close();

    m_dwRefTime = unixtime();
}

CSprite::~CSprite()
{
    if (m_stBrush != nullptr) delete[] m_stBrush;
    if (sprite_) delete[] sprite_;
}

bool CSprite::_iOpenSprite()
{
    if (!m_bIsSurfaceEmpty)
    {
        return false;
    }

    unsigned char * m_lpDib = nullptr;
    uint32_t filesize = 0;
    std::ifstream szfile(fmt::format("sprites\\{}.pak", m_cPakFileName), std::ios::in | std::ios::binary);
    if (!szfile.is_open())
    {
        return false;
    }

    uint32_t encryption = 0;

    szfile.seekg(m_dwBitmapFileStartLoc, std::ios::beg);
    szfile.read((char *)&filesize, 4);
    m_lpDib = (unsigned char *)new unsigned char[filesize];

    szfile.read((char *)&encryption, 4);

    szfile.read((char *)m_lpDib, filesize);

    sf::MemoryInputStream is;
    is.open((char *)m_lpDib, filesize);

    if (!texture.loadFromStream(is))
    {
        std::cout << "Failed to load " << m_cPakFileName << "\n";
        delete[] m_lpDib;
        return false;
    }
    delete[] m_lpDib;

    for (int i = 0; i < m_iTotalFrame; ++i)
    {
        sprite_[i].setTexture(texture);
        sprite_[i].setTextureRect(sf::IntRect(m_stBrush[i].sx, m_stBrush[i].sy, m_stBrush[i].szx, m_stBrush[i].szy));
    }

    m_bIsSurfaceEmpty = false;

    //CreateShadow();

    return true;
}

void CSprite::_iCloseSprite()
{
//     if (m_stBrush == nullptr) return;
//     if (sprite_)
//     {
//         delete[] sprite_;
//         sprite_ = nullptr;
//     }
//     m_bIsSurfaceEmpty = true;
//     m_cAlphaDegree = 1;
}

void CSprite::_GetSpriteRect(int sX, int sY, int sFrame)
{
    short dX, dY, sx, sy, szx, szy, pvx, pvy;
    if (this == 0) return;
    if (m_stBrush == 0) return;
    if ((m_iTotalFrame - 1 < sFrame) || (sFrame < 0)) return;

    sx = m_stBrush[sFrame].sx;
    sy = m_stBrush[sFrame].sy;
    szx = m_stBrush[sFrame].szx;
    szy = m_stBrush[sFrame].szy;
    pvx = m_stBrush[sFrame].pvx;
    pvy = m_stBrush[sFrame].pvy;

    dX = sX + pvx;
    dY = sY + pvy;

    // v1.4
    m_rcBound.top = -1;
    m_rcBound.bottom = -1;
    m_rcBound.left = -1;
    m_rcBound.right = -1;

    if (dX < 0)
    {
        sx = sx + (0 - dX);
        szx = szx - (0 - dX);
        if (szx < 0)
        {
            m_rcBound.top = -1;
            return;
        }
        dX = (short)0;
    }
    else if (dX + szx > renderer->GetWidth())
    {
        szx = szx - ((dX + szx) - (short)renderer->GetWidth());
        if (szx < 0)
        {
            m_rcBound.top = -1;
            return;
        }
    }

    if (dY < 0)
    {
        sy = sy + (0 - dY);
        szy = szy - (0 - dY);
        if (szy < 0)
        {
            m_rcBound.top = -1;
            return;
        }
        dY = (short)0;
    }
    else if (dY + szy > renderer->GetHeight())
    {
        szy = szy - ((dY + szy) - (short)renderer->GetHeight());
        if (szy < 0)
        {
            m_rcBound.top = -1;
            return;
        }
    }

    SetRect(m_rcBound, dX, dY, dX + szx, dY + szy);
    m_sPivotX = pvx;
    m_sPivotY = pvy;
}

bool CSprite::_bCheckCollison(int sX, int sY, short sFrame, int msX, int msY)
{
    short dX, dY, sx, sy, szx, szy, pvx, pvy;

    if (this == nullptr) return false;
    if (m_stBrush == nullptr) return false;
    if ((m_iTotalFrame - 1 < sFrame) || (sFrame < 0)) return false;
    if (m_bIsSurfaceEmpty == true) return false;
    if (msX < 3) return false;
    if (msX > renderer->GetWidth() - 3) return false;
    if (msY < 3) return false;
    if (msY > renderer->GetHeight() - 3) return false;

    sx = m_stBrush[sFrame].sx;
    sy = m_stBrush[sFrame].sy;
    szx = m_stBrush[sFrame].szx;
    szy = m_stBrush[sFrame].szy;
    pvx = m_stBrush[sFrame].pvx;
    pvy = m_stBrush[sFrame].pvy;

    dX = sX + pvx;
    dY = sY + pvy;

    if (msX < dX) return false;
    if (msX > dX + szx) return false;
    if (msY < dY) return false;
    if (msY > dY + szy) return false;

    //	if (dX < 0+3) return false;
    //	if (dX+szx > renderer->GetWidth()-3) return false;
    //	if (dY < 0+3) return false;
    //	if (dY+szy > renderer->GetHeight()-3) return false;

    if (dX < 3)
    {
        sx = sx + (3 - dX);
        szx = szx - (- dX);
        if (szx < 0)
        {
            m_rcBound.top = -1;
            return false;
        }
        dX = (short)3;
    }
    else if (dX + szx > renderer->GetWidth() - 3)
    {
        szx = szx - ((dX + szx) - (short)renderer->GetWidth() - 3);
        if (szx < 0)
        {
            m_rcBound.top = -1;
            return false;
        }
    }

    if (dY < 3)
    {
        sy = sy + (3 - dY);
        szy = szy - (3 - dY);
        if (szy < 0)
        {
            m_rcBound.top = -1;
            return false;
        }
        dY = (short)3;
    }
    else if (dY + szy > renderer->GetHeight() - 3)
    {
        szy = szy - ((dY + szy) - (short)renderer->GetHeight() - 3);
        if (szy < 0)
        {
            m_rcBound.top = -1;
            return false;
        }
    }

    SetRect(m_rcBound, dX, dY, dX + szx, dY + szy);

    Color pixel = texture.copyToImage().getPixel(sx, sy);
    if (pixel.a == Color::Transparent.a)
        return false;
    return true;
}

void CSprite::PutShiftSpriteFast(int sX, int sY, int shX, int shY, int sFrame, uint64_t dwTime)
{
    short dX, dY, sx, sy, szx, szy, pvx, pvy;
    RECT rcRect{};
    if (this == nullptr) return;
    if (m_stBrush == nullptr) return;
    m_rcBound.top = -1;
    if ((m_iTotalFrame - 1 < sFrame) || (sFrame < 0)) return;
    m_bOnCriticalSection = true;

    sx = m_stBrush[sFrame].sx;
    sy = m_stBrush[sFrame].sy;
    szx = 128;//m_stBrush[sFrame].szx;
    szy = 128;//m_stBrush[sFrame].szy;
    pvx = m_stBrush[sFrame].pvx;
    pvy = m_stBrush[sFrame].pvy;

    sx += shX;
    sy += shY;

    dX = sX + pvx;
    dY = sY + pvy;

    if (dX < 0)
    {
        sx = sx + (0 - dX);
        szx = szx - (0 - dX);
        if (szx <= 0)
        {
            m_rcBound.top = -1;
            return;
        }
        dX = (short)0;
    }
    else if (dX + szx > renderer->GetWidth())
    {
        szx = szx - ((dX + szx) - (short)renderer->GetWidth());
        if (szx <= 0)
        {
            m_rcBound.top = -1;
            return;
        }
    }

    if (dY < 0)
    {
        sy = sy + (0 - dY);
        szy = szy - (0 - dY);
        if (szy <= 0)
        {
            m_rcBound.top = -1;
            return;
        }
        dY = (short)0;
    }
    else if (dY + szy > renderer->GetHeight())
    {
        szy = szy - ((dY + szy) - (short)renderer->GetHeight());
        if (szy <= 0)
        {
            m_rcBound.top = -1;
            return;
        }
    }

    m_dwRefTime = dwTime;

    if (m_bIsSurfaceEmpty == true)
    {
        if (_iOpenSprite() == false) return;
    }

    //SetRect(&rcRect,  sx, sy, sx + szx, sy + szy); // our fictitious sprite bitmap is 
    //SetRect(&m_rcBound, dX, dY, dX + szx, dY + szy);
    rcRect.left = sx;
    rcRect.top = sy;
    rcRect.right = sx + szx;
    rcRect.bottom = sy + szy;

    m_rcBound.left = dX;
    m_rcBound.top = dY;
    m_rcBound.right = dX + szx;
    m_rcBound.bottom = dY + szy;

    sprite_[sFrame].setPosition(sX + szx, sY + szy);
    renderer->back_buffer.draw(sprite_[sFrame]);

    m_bOnCriticalSection = false;
}

void CSprite::PutRevTransSprite(int sX, int sY, int sFrame, uint64_t dwTime, int alphaDepth)
{
    int dX, dY, sx, sy, szx, szy, pvx, pvy;//,sTmp;

    if (this == 0) return;
    if (m_stBrush == 0) return;
    m_rcBound.top = -1;
    if ((m_iTotalFrame - 1 < sFrame) || (sFrame < 0)) return;
    m_bOnCriticalSection = true;

    sx = m_stBrush[sFrame].sx;
    sy = m_stBrush[sFrame].sy;
    szx = m_stBrush[sFrame].szx;
    szy = m_stBrush[sFrame].szy;
    pvx = m_stBrush[sFrame].pvx;
    pvy = m_stBrush[sFrame].pvy;

    dX = sX + pvx;
    dY = sY + pvy;

    if (dX < 0)
    {
        sx = sx + (0 - dX);
        szx = szx - (0 - dX);
        if (szx < 0)
        {
            m_rcBound.top = -1;
            return;
        }
        dX = (short)0;
    }
    else if (dX + szx > renderer->GetWidth())
    {
        szx = szx - ((dX + szx) - (short)renderer->GetWidth());
        if (szx < 0)
        {
            m_rcBound.top = -1;
            return;
        }
    }

    if (dY < 0)
    {
        sy = sy + (0 - dY);
        szy = szy - (0 - dY);
        if (szy < 0)
        {
            m_rcBound.top = -1;
            return;
        }
        dY = (short)0;
    }
    else if (dY + szy > renderer->GetHeight())
    {
        szy = szy - ((dY + szy) - (short)renderer->GetHeight());
        if (szy < 0)
        {
            m_rcBound.top = -1;
            return;
        }
    }

    m_dwRefTime = dwTime;

    if (m_bIsSurfaceEmpty == true)
    {
        if (_iOpenSprite() == false) return;
    }

    SetRect(m_rcBound, dX, dY, dX + szx, dY + szy);

    sprite_[sFrame].setPosition(sX + szx, sY + szy);
    renderer->back_buffer.draw(sprite_[sFrame]);

    m_bOnCriticalSection = false;
}

void CSprite::draw_to(int sX, int sY, int sFrame, uint64_t dwTime, sf::Color color, int draw_mode)
{
    if (m_bIsSurfaceEmpty && _iOpenSprite() == false)
        return;
    if ((uint32_t)sFrame >= m_iTotalFrame || sFrame < 0)
    {
        std::cout << "Sprite out_of_bounds! - " << sFrame << " - " << m_cPakFileName << '\n';
        return;
    }
    sprite_[sFrame].setColor(color);
    sprite_[sFrame].setPosition(sX + m_stBrush[sFrame].pvx, sY + m_stBrush[sFrame].pvy);
    renderer->draw_to(sprite_[sFrame], draw_mode);
}

void CSprite::DrawScaledSprite(int sX, int sY, int sFrame, int sWidth, int sHeight, uint64_t dwTime, sf::Color color)
{
    if (m_bIsSurfaceEmpty && _iOpenSprite() == false)
        return;
    sf::FloatRect f = sprite_[sFrame].getLocalBounds();
    sprite_[sFrame].setScale((sWidth / f.width) * 100, (sHeight / f.height) * 100);
    sprite_[sFrame].setColor(color);
    sprite_[sFrame].setPosition(sX + m_stBrush[sFrame].pvx, sY + m_stBrush[sFrame].pvy);
    renderer->draw(sprite_[sFrame]);
    sprite_[sFrame].setScale(1.0, 1.0);
}

void CSprite::DrawWidth(int sX, int sY, int sFrame, int sWidth, uint64_t dwTime, sf::Color color)
{
    if (m_bIsSurfaceEmpty && _iOpenSprite() == false)
        return;
    sprite_[sFrame].setTextureRect(sf::IntRect(m_stBrush[sFrame].sx, m_stBrush[sFrame].sy, sWidth, m_stBrush[sFrame].szy));
    sprite_[sFrame].setColor(color);
    sprite_[sFrame].setPosition(sX + m_stBrush[sFrame].pvx, sY + m_stBrush[sFrame].pvy);
    renderer->draw(sprite_[sFrame]);
    sprite_[sFrame].setTextureRect(sf::IntRect(m_stBrush[sFrame].sx, m_stBrush[sFrame].sy, m_stBrush[sFrame].szx, m_stBrush[sFrame].szy));
}

void CSprite::PutSpriteFast(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255));
}

void CSprite::PutSpriteFastNoColorKey(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255));
}

void CSprite::PutSpriteFastWidth(int sX, int sY, int sFrame, int sWidth, uint64_t dwTime)
{
    DrawWidth(sX, sY, sFrame, sWidth, dwTime, sf::Color(255, 255, 255));
}

void CSprite::PutShadowSprite(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255));
}

void CSprite::PutShadowSpriteClip(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255));
}

void CSprite::PutTransSprite(int sX, int sY, int sFrame, uint64_t dwTime, int alphaDepth)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255, alphaDepth));
}

void CSprite::PutTransSprite_NoColorKey(int sX, int sY, int sFrame, uint64_t dwTime, int alphaDepth)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255, alphaDepth));
}

void CSprite::PutTransSprite70(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255, 180));
}

void CSprite::PutTransSprite70_NoColorKey(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255, 180));
}

void CSprite::PutTransSprite50(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255, 125));
}

void CSprite::PutTransSprite50_NoColorKey(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255, 125));
}

void CSprite::PutTransSprite25(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255, 64));
}

void CSprite::PutTransSprite25_NoColorKey(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255, 64));
}

void CSprite::PutTransSprite2(int sX, int sY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(180, 255, 255));
}

void CSprite::PutShiftTransSprite2(int sX, int sY, int shX, int shY, int sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255));
}

void CSprite::PutFadeSprite(short sX, short sY, short sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255));
}

void CSprite::PutFadeSpriteDst(uint16_t * pDstAddr, short sPitch, short sX, short sY, short sFrame, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(255, 255, 255));
}

void CSprite::PutSpriteRGB(int sX, int sY, int sFrame, int sRed, int sGreen, int sBlue, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(sRed, sGreen, sBlue, 255));
}

void CSprite::PutTransSpriteRGB(int sX, int sY, int sFrame, int sRed, int sGreen, int sBlue, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(sRed, sGreen, sBlue, 180));
}

void CSprite::PutTransSpriteRGB_NoColorKey(int sX, int sY, int sFrame, int sRed, int sGreen, int sBlue, uint64_t dwTime)
{
    DrawSprite(sX, sY, sFrame, dwTime, sf::Color(sRed, sGreen, sBlue, 180));
}

void CSprite::DrawSprite(int sX, int sY, int sFrame, uint64_t dwTime, sf::Color color)
{
    DrawRGB(sX, sY, sFrame, dwTime, color);
}

void CSprite::DrawRGB(int sX, int sY, int sFrame, uint64_t dwTime, sf::Color color)
{
    if (m_bIsSurfaceEmpty && _iOpenSprite() == false)
        return;
    if (sFrame >= m_iTotalFrame)
    {
        std::cout << "Sprite out_of_bounds! - " << sFrame << " - " << m_cPakFileName << '\n';
        return;
    }
    sprite_[sFrame].setColor(color);
    sprite_[sFrame].setPosition(sX + m_stBrush[sFrame].pvx, sY + m_stBrush[sFrame].pvy);
    renderer->draw(sprite_[sFrame]);
}
