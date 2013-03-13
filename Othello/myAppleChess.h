// myAppleChess.h : main header file for the MYAPPLECHESS application
//

#if !defined(AFX_MYAPPLECHESS_H__C14DDA18_0698_4CCE_A62D_983DF5DF876A__INCLUDED_)
#define AFX_MYAPPLECHESS_H__C14DDA18_0698_4CCE_A62D_983DF5DF876A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessApp:
// See myAppleChess.cpp for the implementation of this class
//

class CMyAppleChessApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMyAppleChessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAppleChessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyAppleChessApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYAPPLECHESS_H__C14DDA18_0698_4CCE_A62D_983DF5DF876A__INCLUDED_)
