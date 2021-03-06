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
 * @file Bt8x8GPIOAudioDecoder.cpp CBt8x8GPIOAudioDecoder Implementation
 */

#include "stdafx.h"

#ifdef WANT_BT8X8_SUPPORT

#include "Bt8x8GPIOAudioDecoder.h"
#include "Bt848_Defines.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBt8x8GPIOAudioDecoder::CBt8x8GPIOAudioDecoder(CPCICard* pPCICard, const DWORD dwGPOE, const DWORD dwStereo, const DWORD dwMono, const DWORD dwLang1) :
    m_pPCICard(pPCICard),
    m_GPOE(dwGPOE),
    m_GPDATA_Stereo(dwStereo),
    m_GPDATA_Mono(dwMono),
    m_GPDATA_Lang1(dwLang1)
{
}

void CBt8x8GPIOAudioDecoder::SetSoundChannel(eSoundChannel soundChannel)
{
    DWORD con;

    if (soundChannel == SOUNDCHANNEL_LANGUAGE1)
    {
        con = m_GPDATA_Lang1;
    }
    else if (soundChannel == SOUNDCHANNEL_STEREO)
    {
        con = m_GPDATA_Stereo;
    } else
    {
        con = m_GPDATA_Mono;
    }

    m_pPCICard->OrDataDword(BT848_GPIO_DATA, m_GPOE);
    m_pPCICard->AndOrDataDword(BT848_GPIO_DATA, con, ~m_GPOE);
}

#endif // WANT_BT8X8_SUPPORT