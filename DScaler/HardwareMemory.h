/////////////////////////////////////////////////////////////////////////////
// $Id: HardwareMemory.h,v 1.5 2001-11-02 16:30:08 adcockj Exp $
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2001 John Adcock.  All rights reserved.
/////////////////////////////////////////////////////////////////////////////
//
//  This file is subject to the terms of the GNU General Public License as
//  published by the Free Software Foundation.  A copy of this license is
//  included with this software distribution in the file COPYING.  If you
//  do not have a copy, you may obtain a copy by writing to the Free
//  Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details
/////////////////////////////////////////////////////////////////////////////

#ifndef __HARDWAREMEMORY_H___
#define __HARDWAREMEMORY_H___

#include "HardwareDriver.h"

class CHardwareMemory
{
public:
    void* GetUserPointer();
    DWORD TranslateToPhysical(void* pUser, DWORD dwSizeWanted, DWORD* pdwSizeAvailable);
    BOOL IsValid();
protected:
    CHardwareMemory(CHardwareDriver* m_pDriver);
    ~CHardwareMemory();
    TMemStruct* m_pMemStruct;
    CHardwareDriver* m_pDriver;
};

class CUserMemory : public CHardwareMemory
{
public:
    CUserMemory(CHardwareDriver* pDriver, size_t Bytes);
    ~CUserMemory();
private:
    DWORD m_AllocatedBlock;
};

class CContigMemory : public CHardwareMemory
{
public:
    CContigMemory(CHardwareDriver* pDriver, size_t Bytes);
    ~CContigMemory();
};

#endif