/////////////////////////////////////////////////////////////////////////////
// $Id: DScalerApp.cpp,v 1.1 2001-06-22 19:24:53 tobbej Exp $
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2000 John Adcock.  All rights reserved.
/////////////////////////////////////////////////////////////////////////////
//
//	This file is subject to the terms of the GNU General Public License as
//	published by the Free Software Foundation.  A copy of this license is
//	included with this software distribution in the file COPYING.  If you
//	do not have a copy, you may obtain a copy by writing to the Free
//	Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//
//	This software is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details
/////////////////////////////////////////////////////////////////////////////
// Change Log
//
// Date          Developer             Changes
//
// 22 Jun 2001   Torbj�rn Jansson      Initial release
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DScalerApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDScalerApp

BEGIN_MESSAGE_MAP(CDScalerApp, CWinApp)
	//{{AFX_MSG_MAP(CDScalerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDScalerApp construction

CDScalerApp::CDScalerApp()
{

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDScalerApp object

CDScalerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDScalerApp initialization

//the old winmain
int APIENTRY WinMainOld(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

BOOL CDScalerApp::InitInstance()
{
#ifdef _DEBUG

	/*
	Turn on memory leak debuging.
	to be able to see were the memory was allocated (filename + linenumber)
	the following code is needed first in cpp files (standard code generated by classwizard):

	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
	*/
	afxMemDF=allocMemDF|checkAlwaysMemDF|delayFreeMemDF;
#endif

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	/*
	If we change WritePrivateProfileInt/WritePrivateProfileString to AfxGetApp()->WriteProfileInt/string
	we coud easily change DScaler to write to eighter registry or ini file.
	*/
	//Use registry for saving settings.
	//without this (if i remember right) AfxGetApp()->WriteProfileInt/string goes to ini file
	SetRegistryKey(_T("DScaler"));

	//call the real winmain
	WinMainOld(m_hInstance,m_hPrevInstance,m_lpCmdLine,m_nCmdShow);

	//return false so message loop dont start
	return FALSE;
}
