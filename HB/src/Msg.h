//
// Copyright (c) Sharon Fox (sharon at sharonfox dot dev)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include <cstdint>

class CMsg  
{
public:
	CMsg(char cType, const char * pMsg, uint64_t dwTime);
	virtual ~CMsg();

	char m_cType;
	char * m_pMsg;
	short m_sX, m_sY;
    uint64_t m_dwTime;

	int m_iObjectID;

};
