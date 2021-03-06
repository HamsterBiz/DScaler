/////////////////////////////////////////////////////////////////////////////
// $Id$
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2000 John Adcock.  All rights reserved.
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
//
// This software was based on Multidec 5.6 Those portions are
// Copyright (C) 1999/2000 Espresso (echter_espresso@hotmail.com)
//
/////////////////////////////////////////////////////////////////////////////

/**
 * @file fieldtiming.h fieldtiming Header file
 */

#ifndef __FIELDTIMING_H___
#define __FIELDTIMING_H___

#include "settings.h"
#include "DS_Deinterlace.h"

extern long MaxFieldShift;
extern BOOL bAlwaysSleep;

// Get Hold of the FieldTiming.c file settings
SETTING* Timing_GetSetting(TIMING_SETTING Setting);
void Timing_SetMenu(HMENU hMenu);

void Timing_UpdateRunningAverage(TDeinterlaceInfo* pInfo, int NumFields);
void Timing_Setup();
void Timing_CleanUp();
void Timing_WaitForNextField(TDeinterlaceInfo* pInfo);
void Timing_Reset();
void Timing_WaitForTimeToFlip(TDeinterlaceInfo* pInfo, DEINTERLACE_METHOD* CurrentMethod, BOOL* bStopThread);
int Timing_GetDroppedFields();
void Timing_ResetDroppedFields();
int Timing_GetNotWaitedFields();
void Timing_ResetNotWaitedFields();
int Timing_GetLateFields();
void Timing_ResetLateFields();
int Timing_GetUsedFields();
void Timing_ResetUsedFields();
int Timing_GetNoFlipAtTime();
void Timing_ResetNoFlipAtTime();
void Timing_IncrementUsedFields();
void Timing_AddDroppedFields(int nDropped);
void Timing_IncrementNotWaitedFields();
void Timing_AddLateFields(int nLate);
void Timing_IncrementNoFlipAtTime();
void Timimg_AutoFormatDetect(TDeinterlaceInfo* pInfo, int NumFields);
void Timing_SmartSleep(TDeinterlaceInfo* pInfo, BOOL bRunningLate, BOOL& bSleptAlready);
void Timing_SetFlipAdjustFlag(BOOL NewValue);


#endif
