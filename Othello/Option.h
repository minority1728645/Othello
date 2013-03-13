#if !defined(AFX_OPTION_H__D53C9D84_56BC_49FE_801D_56770AFDB562__INCLUDED_)
#define AFX_OPTION_H__D53C9D84_56BC_49FE_801D_56770AFDB562__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Option.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COption dialog

class COption : public CDialog
{
// Construction
public:
	void EnableBlack();
	void UnableBlack();
	COption(CWnd* pParent = NULL);   // standard constructor
	bool preIsBlack;
	bool musicOpen,preMusicOpen;
	bool m_end;
// Dialog Data
	//{{AFX_DATA(COption)
	enum { IDD = IDD_DIALOG1 };
	int		m_radio;
	int		m_music;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COption)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTION_H__D53C9D84_56BC_49FE_801D_56770AFDB562__INCLUDED_)
