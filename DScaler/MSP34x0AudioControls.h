//
// $Id$
//
/////////////////////////////////////////////////////////////////////////////
//
// copyleft 2002 itt@myself.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
//
/////////////////////////////////////////////////////////////////////////////

/**
 * @file msp34x0audiocontrols.h msp34x0audiocontrols Header
 */

#ifdef WANT_BT8X8_SUPPORT

#if !defined(__MSP34X0AUDIOCONTROLS_H__)
#define __MSP34X0AUDIOCONTROLS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BT848_Defines.h"
#include "Setting.h"

#include "AudioControls.h"

class CMSP34x0AudioControls : public CMSP34x0, public CAudioControls
{
public:
    CMSP34x0AudioControls();
    virtual ~CMSP34x0AudioControls() {};
    void SetDolby(long Mode, long nNoise, long nSpatial, long nPan, long Panorama);

    // from IAudioControls
    BOOL HasMute();
    void SetMute(BOOL mute=TRUE);
    BOOL IsMuted();
    void SetVolume(WORD nVolume);
    WORD GetVolume();
    void SetBalance(WORD nBalance);
    WORD GetBalance();
    void SetBass(WORD nLevel);
    WORD GetBass();
    void SetTreble(WORD nLevel);
    WORD GetTreble();
    BOOL HasEqualizers();
    WORD GetEqualizerCount();
    void SetEqualizerLevel(WORD nIndex, WORD nLevel);
    WORD GetEqualizerLevel(WORD nIndex);
    BOOL HasBassBoost();
    void SetBassBoost(BOOL bBoost);
    BOOL IsBassBoosted();
    BOOL HasLoudness();
    void SetLoudness(WORD nLevel);
    WORD GetLoudness();
    BOOL HasAutoVolumeCorrection();
    void SetAutoVolumeCorrection(long milliSeconds);
    long GetAutoVolumeCorrection();
    BOOL HasSpatialEffect();
    void SetSpatialEffect(int nLevel);
    int  GetSpatialEffect();

private:
    BOOL m_bMuted;
    int m_nVolume;
    int m_nBalance;
    int m_nBass;
    int m_nTreble;
    BOOL m_bBassBoost;
};

#endif // !defined(__MSP34X0AUDIOCONTROLS_H__)

#endif