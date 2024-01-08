//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#include "Item.h"
#include "polyfill.h"

CItem::CItem()
{
    ZeroMemory(m_cName, sizeof(m_cName));
    m_sSprite = 0;
    m_sSpriteFrame = 0;
    m_dwAttribute = 0;
    m_sItemSpecEffectValue1 = 0;
    m_sItemSpecEffectValue2 = 0;
    m_sItemSpecEffectValue3 = 0;
}

CItem::~CItem()
{

}
