/////////////////////////////////////////////////////////////////////////////
// $Id: DevEnum.cpp,v 1.1 2001-12-09 22:01:48 tobbej Exp $
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2001 Torbj�rn Jansson.  All rights reserved.
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
// Change Log
//
// Date          Developer             Changes
//
//
/////////////////////////////////////////////////////////////////////////////
// CVS Log
//
// $Log: not supported by cvs2svn $
//
/////////////////////////////////////////////////////////////////////////////

/**
 * @file DevEnum.cpp implementation of the CDevEnum class.
 */

#include "stdafx.h"
#include "DevEnum.h"

#include "exception.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDevEnum::CDevEnum()
:m_pSysDevEnum(NULL),m_pEnumCat(NULL)
{
	createSysEnum();
}

CDevEnum::CDevEnum(REFCLSID devClass)
:m_pSysDevEnum(NULL),m_pEnumCat(NULL)
{
	createSysEnum();
	initEnum(devClass);
}

CDevEnum::~CDevEnum()
{

}

void CDevEnum::initEnum(REFCLSID devClass)
{
	HRESULT hr;
	if(m_pEnumCat!=NULL)
	{
		m_pEnumCat.Release();
		m_pEnumCat=NULL;
	}

	hr=m_pSysDevEnum->CreateClassEnumerator(devClass, &m_pEnumCat, 0);
	if(hr!=S_OK)
	{
		throw CDevEnumException("Cant create Class enumerator",hr);
	}
}

bool CDevEnum::getNext()
{
	CComPtr<IMoniker> pMoniker;
	ULONG cFetched;

	//check that device enumerator is initialized
	if(m_pEnumCat==NULL)
	{
		throw CDevEnumException("initialize device enumerator before using it");
	}
	
	if(m_pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
	{
		m_pPropBag.Release();
		pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&m_pPropBag);

		//get the moniker's DisplayName
		//(used to create this device)
		WCHAR *szDisplayName=NULL;
		if(SUCCEEDED(pMoniker->GetDisplayName(NULL,NULL,&szDisplayName)))
		{
			m_DisplayName.Format("%S",szDisplayName ? szDisplayName : L"");
			CoTaskMemFree(szDisplayName);
		}
		else
		{
			//s�tt den till en tom str�ng om de blev fel
			m_DisplayName="";
		}

		return true;

	}
	else
	{
		return false;
	}
}

void CDevEnum::createSysEnum()
{
	HRESULT hr=m_pSysDevEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
	if(FAILED(hr))
	{
		//throw an exception
		//this error shoud never hapend unless somting is very wrong (or com is not initialized)
		throw CDevEnumException("Cant create System Device Enumerator",hr);
	}
}

void CDevEnum::createDevice(string displayName,REFIID interf, void *device)
{
	WCHAR *name;

	//covert to wide char
	int n=MultiByteToWideChar(CP_ACP, 0, displayName.c_str(), -1, NULL, 0);
	name=new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, displayName.c_str(), -1, name, n);

	//try to create a moniker
	CComPtr<IBindCtx> pBC;
	CComPtr<IMoniker> pmDev;
	HRESULT hr = CreateBindCtx(0, &pBC);
	if(SUCCEEDED(hr))
	{
		DWORD dwEaten;
		hr = MkParseDisplayName(pBC, name, &dwEaten, &pmDev);	

		if(FAILED(hr))
		{
			delete [] name;
			throw(CDevEnumException("createDevice: cant create moniker",hr));
		}
	}
	hr = pmDev->BindToObject(0, 0, interf, (void**)device);
	if(FAILED(hr))
	{
		delete [] name;
		throw(CDevEnumException("createDevice: BindToObject failed",hr));
	}
	
	delete [] name;
	
}

string CDevEnum::getProperty(string szName)
{
	USES_CONVERSION;

	VARIANT varProperty;
	HRESULT hr;
	LPCOLESTR oleProperty=T2OLE(szName.c_str());
	varProperty.vt = VT_BSTR;
	hr = m_pPropBag->Read(oleProperty, &varProperty, 0);
	if(SUCCEEDED(hr))
	{
		CString tmp;
		tmp.Format("%S",varProperty.bstrVal);
		SysFreeString(varProperty.bstrVal);
		return tmp;
	}
	else
	{
		//shoud probably use an exception insted
		return "";
	}
}
