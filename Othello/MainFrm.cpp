// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "myAppleChess.h"

#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	CSplashWnd::ShowSplashScreen(this);

	ModifyStyle(WS_BORDER|WS_THICKFRAME|WS_DLGFRAME,NULL);
    DrawMenuBar(); 

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetMenu(NULL); 
	//����ϵͳ��������
    CBitmap cBitmap;
	cBitmap.LoadBitmap(IDB_BITMAP1);
    CDC *pDC = this->GetDC();
    CDC memDC;//�����봫��DC���ݵ���ʱDC
    memDC.CreateCompatibleDC(pDC);
    CBitmap *pOldMemBmp=NULL;
    pOldMemBmp=memDC.SelectObject(&cBitmap);//��λͼѡ����ʱDC
    wndRgn.CreateRectRgn(0,0,0,0);//�����ܵĴ������򣬳�ʼregionΪ0
    BITMAP bit;   
    cBitmap.GetBitmap (&bit);//ȡ��λͼ����
    int y;
	int iX = 0;
	int iLeftX=0;
    for(y=0;y<bit.bmHeight; y++)
    {
        CRgn rgnTemp;
        while(iX<bit.bmWidth )
        {
            //����͸��ɫ�ҵ���һ����͸��ɫ�ĵ�.
            while (iX<bit.bmWidth&&(memDC.GetPixel(iX, y)==RGB(0,255,0)||memDC.GetPixel(iX, y)==RGB(0,254,0)))
			{ iX++;}
            //��ס�����ʼ��
            iLeftX = iX;
            //Ѱ���¸�͸��ɫ�ĵ�
            while (iX<bit.bmWidth&&memDC.GetPixel(iX,y)!=RGB(0,255,0)&&memDC.GetPixel(iX,y)!=RGB(0,254,0))
                ++iX;
            //����һ������������ص���Ϊ1���ص���ʱregion
            rgnTemp.CreateRectRgn(iLeftX, y, iX, y+1);
            //�ϲ�����"region".
            wndRgn.CombineRgn(&wndRgn, &rgnTemp, RGN_OR);
            rgnTemp.DeleteObject();
        } 
        iX = 0;
    }
    if(pOldMemBmp)
    memDC.SelectObject(pOldMemBmp);
    CWnd * pWnd = pDC->GetWindow();
    pWnd->SetWindowRgn(wndRgn, TRUE); 
	
	CenterWindow();//���ھ���
    
	// CG: The following line was added by the Splash Screen component.
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx=WINDOWW;
	cs.cy=WINDOWH;//���ô�С
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	AnimateWindow(m_hWnd,500,AW_HIDE|AW_CENTER);
	CFrameWnd::OnClose();
}
