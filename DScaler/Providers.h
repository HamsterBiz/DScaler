/////////////////////////////////////////////////////////////////////////////
// $Id: Providers.h,v 1.8 2002-01-24 00:00:13 robmuller Exp $
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

#ifndef __PROVIDERS_H___
#define __PROVIDERS_H___

#include "Source.h"

int Providers_Load(HMENU hMenu);
void Providers_Unload();
BOOL Providers_HandleWindowsCommands(HWND hWnd, UINT wParam, LONG lParam);
void Provider_HandleTimerMessages(int TimerId);
CSource* Providers_GetCurrentSource();
BOOL Providers_AddSource(CSource* pSource, HMENU hMenu);
BOOL Providers_RemoveSource(CSource* pSource, HMENU hMenu);
void Providers_SetMenu(HMENU hMenu);
void Providers_UpdateMenu(HMENU hMenu);
long Providers_GetNumber();
CSource*  Providers_GetByIndex(long Index);
void Providers_ReadFromIni();
void Providers_WriteToIni(BOOL bOptimizeFileAccess);

#endif