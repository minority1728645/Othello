// Option.cpp : implementation file
//

#include "stdafx.h"
#include "myapplechess.h"
#include "Option.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COption dialog

COption::COption(CWnd* pParent /*=NULL*/)
	: CDialog(COption::IDD, pParent)
{
	//{{AFX_DATA_INIT(COption)
	m_radio = -1;
	m_music = -1;
	//}}AFX_DATA_INIT
	m_radio=0;
	isBlack=true;
	preIsBlack=isBlack;
	m_music=0;
	musicOpen=true;
	preMusicOpen=musicOpen;
}


void COption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COption)
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Radio(pDX, IDC_RADIO3, m_music);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COption, CDialog)
	//{{AFX_MSG_MAP(COption)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COption message handlers


BOOL COption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	UpdateData(FALSE);
	if(m_end)
	{
		EnableBlack();
        
	}
	else
	{
		m_radio=0;
	    isBlack=false;
	    preIsBlack=isBlack;
		UpdateData(FALSE);
		UnableBlack();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void COption::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	preIsBlack=isBlack;
	if(m_radio==0)
	{
		isBlack=true;
	}
}

void COption::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	preIsBlack=isBlack;
	if(m_radio==1)
	{
		isBlack=false;
	}
}

void COption::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	preMusicOpen=musicOpen;
	if(m_music==0)
	{
		musicOpen=true;
	}
}

void COption::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	preMusicOpen=musicOpen;
	if(m_music==1)
	{
		musicOpen=false;
	}
}

void COption::OnCancel() 
{
	// TODO: Add extra cleanup here
	musicOpen=preMusicOpen;
	if(musicOpen)m_music=0;
	else m_music=1;

	isBlack=preIsBlack;
	if(isBlack)m_radio=0;
	else m_radio=1;

	CDialog::OnCancel();
}

void COption::UnableBlack()
{
    ((CButton*)GetDlgItem(IDC_RADIO1))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO2))->EnableWindow(FALSE);
}

void COption::OnOK() 
{
	// TODO: Add extra validation here

	preMusicOpen=musicOpen;

	preIsBlack=isBlack;

	CDialog::OnOK();
}

void COption::EnableBlack()
{
	((CButton*)GetDlgItem(IDC_RADIO1))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO2))->EnableWindow(TRUE);
}
