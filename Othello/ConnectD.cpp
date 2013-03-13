// ConnectD.cpp : implementation file
//

#include "stdafx.h"
#include "myapplechess.h"
#include "ConnectD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectD dialog


CConnectD::CConnectD(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConnectD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectD)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectD, CDialog)
	//{{AFX_MSG_MAP(CConnectD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectD message handlers

void CConnectD::OnOK() 
{
	// TODO: Add extra validation here
	
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
	CDialog::OnOK();
}

void CConnectD::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
