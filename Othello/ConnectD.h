#if !defined(AFX_CONNECTD_H__A389BB01_1B13_4596_A1CA_026964E9F7C3__INCLUDED_)
#define AFX_CONNECTD_H__A389BB01_1B13_4596_A1CA_026964E9F7C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectD.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CConnectD dialog
#include "resource.h"
class CConnectD : public CDialog
{
// Construction
public:
	CConnectD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectD)
	enum { IDD = IDD_DIALOG2 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConnectD)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTD_H__A389BB01_1B13_4596_A1CA_026964E9F7C3__INCLUDED_)
