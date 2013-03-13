#if !defined(AFX_SERVTHREAD_H__A2F46D98_C8E4_4935_825D_2EF57E50FBF4__INCLUDED_)
#define AFX_SERVTHREAD_H__A2F46D98_C8E4_4935_825D_2EF57E50FBF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServThread.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServThread thread

class CServThread : public CWinThread
{
	DECLARE_DYNCREATE(CServThread)
protected:
	CServThread();           // protected constructor used by dynamic creation
	SOCKET sockSrv;
	SOCKET sockConn;
// Attributes
public:

// Operations
public:
	CWinThread* m_pRecvThread;
	static UINT ThreadRecv(LPVOID pParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CServThread();

	// Generated message map functions
	//{{AFX_MSG(CServThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LONG OnMyDown(UINT wParam,LONG lParam);
	afx_msg LONG OnSend(UINT wParam,LONG lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVTHREAD_H__A2F46D98_C8E4_4935_825D_2EF57E50FBF4__INCLUDED_)
