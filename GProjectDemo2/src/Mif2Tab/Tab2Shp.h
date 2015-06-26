// Tab2Shp.h : main header file for the TAB2SHP application
//

#if !defined(AFX_TAB2SHP_H__14816534_E792_4316_96A0_D87632AA6474__INCLUDED_)
#define AFX_TAB2SHP_H__14816534_E792_4316_96A0_D87632AA6474__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTab2ShpApp:
// See Tab2Shp.cpp for the implementation of this class
//

class CTab2ShpApp : public CWinApp
{
public:
	CTab2ShpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab2ShpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTab2ShpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB2SHP_H__14816534_E792_4316_96A0_D87632AA6474__INCLUDED_)
