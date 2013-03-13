#if !defined(AFX_CLIETHREAD_H__341D485D_C63F_4DCF_BCF9_09D9D4ECD2BD__INCLUDED_)
#define AFX_CLIETHREAD_H__341D485D_C63F_4DCF_BCF9_09D9D4ECD2BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClieThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClieThread thread

class CClieThread : public CWinThread
{
	DECLARE_DYNCREATE(CClieThread)
protected:
	CClieThread();           // protected constructor used by dynamic creation
	SOCKET sockClient;

// Attributes
public:

// Operations
public:
	CWinThread* m_pRecvThread;
	static UINT ThreadRecv(LPVOID pParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClieThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CClieThread();

	// Generated message map functions
	//{{AFX_MSG(CClieThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LONG OnMyDown(UINT wParam,LONG lParam);
	afx_msg LONG OnSend(UINT wParam,LONG lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIETHREAD_H__341D485D_C63F_4DCF_BCF9_09D9D4ECD2BD__INCLUDED_)
