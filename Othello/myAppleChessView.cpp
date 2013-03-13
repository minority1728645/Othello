// myAppleChessView.cpp : implementation of the CMyAppleChessView class
//

#include "stdafx.h"
#include "myAppleChess.h"

#include "myAppleChessDoc.h"
#include "myAppleChessView.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessView

IMPLEMENT_DYNCREATE(CMyAppleChessView, CView)

BEGIN_MESSAGE_MAP(CMyAppleChessView, CView)
	//{{AFX_MSG_MAP(CMyAppleChessView)
	ON_COMMAND(ID_REPLAY, OnReplay)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RIVALDOWN,OnRivalDown)
	ON_BN_CLICKED(ID_Exit, OnExit)
	ON_BN_CLICKED(ID_Option, OnOption)
	ON_BN_CLICKED(ID_Single, OnSingle)
	ON_BN_CLICKED(ID_Muti, OnMuti)
	ON_BN_CLICKED(ID_Back,OnBack)
	ON_BN_CLICKED(ID_Connect,OnConnect)
	ON_BN_CLICKED(ID_Build,OnBuild)
	ON_BN_CLICKED(ID_Send,OnSend)//������Ϣӳ��
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessView construction/destruction

CMyAppleChessView::CMyAppleChessView()
{
	// TODO: add construction code here
}
CMyAppleChessView::~CMyAppleChessView()
{
}
BOOL CMyAppleChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessView drawing

void CMyAppleChessView::OnDraw(CDC* pDC)
{
	CMyAppleChessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//������
	int i;
	int j;
	int intPerLength = (int)(LENGTH/MAX);
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(intChessManual[i][j]==1)  //����
			{
				pDC->SelectObject(pBrushW);
				int intCenterPTX=STARTPTX+i*intPerLength+intPerLength/2+1;
				int intCenterPTY=STARTPTY+j*intPerLength+intPerLength/2+1;
				pDC->SetBrushOrg(intCenterPTX-RADIUS, intCenterPTY-RADIUS); //����λͼ��ˢԭ��
				pDC->Ellipse(CRect(intCenterPTX-RADIUS,intCenterPTY-RADIUS,
					         intCenterPTX+RADIUS,intCenterPTY+RADIUS));
			}
			else
			{
				if(intChessManual[i][j]==-1) //����
				{
					pDC->SelectObject(pBrushB);
					int intCenterPTX=STARTPTX+i*intPerLength+intPerLength/2+1;
					int intCenterPTY=STARTPTY+j*intPerLength+intPerLength/2+1;
					pDC->SetBrushOrg(intCenterPTX-RADIUS, intCenterPTY-RADIUS); //����λͼ��ˢԭ��
					pDC->Ellipse(CRect(intCenterPTX-RADIUS,intCenterPTY-RADIUS,
						intCenterPTX+RADIUS,intCenterPTY+RADIUS));
				}
			}
		}
	}
	//��ʾ��Ϣ
	pDC->TextOut(STARTPTX+LENGTH+20,STARTPTY-20,m_strOut);
}

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessView printing

BOOL CMyAppleChessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyAppleChessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyAppleChessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessView diagnostics

#ifdef _DEBUG
void CMyAppleChessView::AssertValid() const
{
	CView::AssertValid();
}

void CMyAppleChessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyAppleChessDoc* CMyAppleChessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyAppleChessDoc)));
	return (CMyAppleChessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessView message handlers

void CMyAppleChessView::OnReplay() 
{
	// TODO: Add your command handler code here
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			intChessManual[i][j]=0;
		}
	}

	intChessManual[3][3]=1;   //White
	intChessManual[4][4]=1;
	intChessManual[3][4]=-1;  //Black
	intChessManual[4][3]=-1;
	
	m_intFlag=-1; //��������
	FillNext(); //�Ʋ���һ��

	m_strOut="�ֺ��� ������-������=00";
	InvalidateRect(CRect(STARTPTX,STARTPTY,STARTPTX+LENGTH,STARTPTY+LENGTH),TRUE);
	InvalidateRect(CRect(STARTPTX+LENGTH+20,STARTPTY-20,STARTPTX+LENGTH+320,STARTPTY+30),TRUE);
}

void CMyAppleChessView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	::SetFocus(m_hWnd);
	int xPT=(int)floor((point.x-STARTPTX)/double(LENGTH/MAX));
	int yPT=(int)floor((point.y-STARTPTY)/double(LENGTH/MAX));
	if((m_bSingle||(m_bMuti&&myTurn))&&INBORAD(xPT,yPT))
	{
		
		for(int s=0;s<=m_intNextNumber;s++)
		{
			if(m_Next[s].i==xPT&&m_Next[s].j==yPT)
			{
				
				for(int m=0;m<MAX;m++)
				{
					for(int n=0;n<MAX;n++)
					{
						intChessManual[m][n]=m_Next[s].intNextManual[m][n];
					}
				}
				InvalidateRect(CRect(STARTPTX,STARTPTY,STARTPTX+LENGTH,STARTPTY+LENGTH),false);
				m_intFlag=-m_intFlag;
				myTurn=false;
				posiX=(char)xPT;
				posiY=(char)yPT;

				CString strTemp;
				strTemp.Format("% .2d",-m_Next[s].intValue);   //��ʾ����
				if(m_intFlag==1)
				m_strOut="�ְ��� ������-��������"+strTemp;
				else
				m_strOut="�ֺ��� ������-��������"+strTemp;
				InvalidateRect(CRect(STARTPTX+LENGTH+20,STARTPTY-20,STARTPTX+LENGTH+320,STARTPTY+30),false);
				
				if(m_bMuti&&m_isServ)
				{
					m_pServThread->PostThreadMessage(WM_MYDOWN,NULL,NULL);
				}
				else if(m_bMuti&&m_isClie)
				{
					m_pClieThread->PostThreadMessage(WM_MYDOWN,NULL,NULL);
				}
				if(!FillNext())  //�Ƿ�����һ��
				{
					m_bSingle=false;
					m_bMuti=false;
					if(m_Next[s].intValue==0)
					{
						MessageBox("ƽ��!");
					}
					if(m_Next[s].intValue>0)
					{
						MessageBox("��ʤ!");
					}
					else
					{
						MessageBox("��ʤ!");
					}
				}
				break;
			}
		
		}
	}
	else 
	{
		Clicked=true;
		prepoint=point;
	}
	CView::OnLButtonDown(nFlags, point);
}


LRESULT CMyAppleChessView::OnRivalDown(WPARAM wParam,LPARAM lParam)
{
	for(int s=0;s<=m_intNextNumber;s++)
		{
			if(m_Next[s].i==((int)posiX)&&m_Next[s].j==((int)posiY))
			{
				
				for(int m=0;m<MAX;m++)
				{
					for(int n=0;n<MAX;n++)
					{
						intChessManual[m][n]=m_Next[s].intNextManual[m][n];
					}
				}
				InvalidateRect(CRect(STARTPTX,STARTPTY,STARTPTX+LENGTH,STARTPTY+LENGTH),false);
				m_intFlag=-m_intFlag;
				
				CString strTemp;
				strTemp.Format("% .2d",-m_Next[s].intValue);   //��ʾ����
				if(m_intFlag==1)
				m_strOut="�ְ��� ������-��������"+strTemp;
				else
				m_strOut="�ֺ��� ������-��������"+strTemp;
				InvalidateRect(CRect(STARTPTX+LENGTH+20,STARTPTY-20,STARTPTX+LENGTH+320,STARTPTY+30),false);
				if(!FillNext())  //�Ƿ�����һ��
				{
					m_bSingle=false;
					m_bMuti=false;
					
					if(m_Next[s].intValue==0)
					{
						MessageBox("ƽ��!");
					}
					if(m_Next[s].intValue>0)
					{
						MessageBox("��ʤ!");
					}
					else
					{
						MessageBox("��ʤ!");
					}
				}
				break;
			}
		}
	myTurn=true;
	
	return 0;
}
//�ú������ĳһ�������ϵ����Ƿ񹹳��˼л�֮�ƣ�������dx��dy�Ĳ�ͬ�������ʾ
//��dx=0,dy=1��ʾ�·���dx=-1,dy=-1��ʾ���Ϸ���
//i,j��ʾ����λ��
//flag=-1,���壻flag=1,����
void CMyAppleChessView::CheckDirect(int i, int j, int dx, int dy, int Flag, int intChess[MAX][MAX], bool *pboolVaild)
{
	int s=i+dx;
	int t=j+dy;
	bool boolFristOK=false;

	while(INBORAD(s,t) && intChess[s][t]==-m_intFlag) 
	{
		s+=dx;
		t+=dy;
		boolFristOK=true;   //�����˼л�֮��
	}

	if(INBORAD(s,t) && boolFristOK && intChess[s][t]==m_intFlag)
	{
		*pboolVaild=true;    //�÷���������Ч
		do
		{
			s-=dx;
			t-=dy;
			intChess[s][t]=m_intFlag;   //�ı���ֳԵ��Է�����
		}while(s!=i || t!=j);
	}
}
//�����i,j���������Ƿ����

void CMyAppleChessView::CheckNext(int i,int j, int intFlag)
{
	bool boolVaild=false;
	int intTempChess[8][8];
	int s;
	int t;
	
	for(s=0;s<MAX;s++)   //���Ƶ�ǰ���
		for(t=0;t<MAX;t++)
			intTempChess[s][t]=intChessManual[s][t];
	
	//��8������ֱ���
	CheckDirect(i,j,1,0,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,0,1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,-1,0,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,0,-1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,1,1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,-1,-1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,1,-1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,-1,1,intFlag,intTempChess,&boolVaild);
	if(boolVaild) //��������������������ֱ��浽m_NEXT��
	{
		m_intNextNumber++;
		m_Next[m_intNextNumber].i=i;
		m_Next[m_intNextNumber].j=j;
		int intTotal=0;
		for (s=0;s<MAX;s++)
			for(t=0;t<MAX;t++)
			{
				m_Next[m_intNextNumber].intNextManual[s][t]=intTempChess[s][t];
				intTotal+=intTempChess[s][t];
			}
		m_Next[m_intNextNumber].intValue=intTotal;
	}
}
//�ҳ���һ�������п�����ִ�ŵ�m_Next��
BOOL CMyAppleChessView::FillNext()
{
	m_intNextNumber=-1;
	
	for(int i=0;i<MAX;i++)  //�Ե�ǰ��ֵ����пո����Ƿ��������
		for(int j=0;j<MAX;j++)
			if(intChessManual[i][j]==0)
				CheckNext(i,j,m_intFlag);
	i++;
	if(m_intNextNumber>=0)
		return true;   //���ٴ���һ�����ܵ����Ӵ�
	else
		return false;
}
BOOL CMyAppleChessView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
	
	return TRUE;
}
void CMyAppleChessView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Clicked=false;
	CView::OnLButtonUp(nFlags, point);
}
void CMyAppleChessView::OnMouseMove(UINT nFlags, CPoint point) 
//���ڽ�����MFC�Ĳ˵����������ȣ�����Ҫдһ�������ƶ�����
{
	// TODO: Add your message handler code here and/or call default
	if(Clicked)   
	{       
	     int nX = point.x - prepoint.x;
	     int nY = point.y - prepoint.y;
	     CRect rect;
		 GetWindowRect(&rect);   
	     rect.OffsetRect(nX,nY);
		 GetParentOwner()->MoveWindow(rect.TopLeft().x,rect.TopLeft().y,WINDOWW,WINDOWH,TRUE);
	}
	CView::OnMouseMove(nFlags, point);
}
int CMyAppleChessView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_strOut="";
	
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			intChessManual[i][j]=0;
		}
	}
	m_bSingle=false;
	m_bMuti=false;
	return 0;
}

void CMyAppleChessView::OnExit()
{
	GetParentOwner()->SendMessage(WM_CLOSE);
}
void CMyAppleChessView::OnSingle()//����
{
	m_bSingle=true;
	m_bMuti=false;
	exit1->ShowWindow(SW_HIDE); 
	single->ShowWindow(SW_HIDE); 
	muti->ShowWindow(SW_HIDE); 
	back->ShowWindow(SW_SHOW);
	connectBtn->ShowWindow(SW_HIDE);
	buildservBtn->ShowWindow(SW_HIDE);
	sendBtn->ShowWindow(SW_HIDE);
	sendEdit->ShowWindow(SW_HIDE);
	mainEdit->ShowWindow(SW_HIDE);
	OnReplay();
}
void CMyAppleChessView::OnMuti()//����
{
	m_bSingle=false;
	m_bMuti=true;
	exit1->ShowWindow(SW_HIDE); 
	single->ShowWindow(SW_HIDE); 
	muti->ShowWindow(SW_HIDE); 
	back->ShowWindow(SW_SHOW);
	connectBtn->ShowWindow(SW_SHOW);
	buildservBtn->ShowWindow(SW_SHOW);
	sendBtn->ShowWindow(SW_SHOW);
	sendEdit->ShowWindow(SW_SHOW);
	mainEdit->ShowWindow(SW_SHOW);
	OnReplay();
}
void CMyAppleChessView::OnOption()
{
	op.m_end=m_bMuti;
	op.DoModal();
	if(op.m_music)
	{
        PlaySound(NULL,NULL,SND_FILENAME);

		m_musicon=false;
	}
	else
	{
		if(!m_musicon)
		{
 		PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(),SND_FILENAME|SND_RESOURCE|SND_ASYNC|SND_LOOP);
		m_musicon=true;
		}
	}
}
void CMyAppleChessView::OnBack()
{
	exit1->ShowWindow(SW_SHOW); 
	single->ShowWindow(SW_SHOW); 
	muti->ShowWindow(SW_SHOW); 
	back->ShowWindow(SW_HIDE);
	connectBtn->ShowWindow(SW_HIDE);
	buildservBtn->ShowWindow(SW_HIDE);
	sendBtn->ShowWindow(SW_HIDE);
	sendEdit->ShowWindow(SW_HIDE);
	mainEdit->ShowWindow(SW_HIDE);
	if(m_isServ)
	{
		m_isServ=false;
		m_pServThread->PostThreadMessage(WM_QUIT,NULL,NULL);
	}
	else if(m_isClie)
	{
		m_isClie=false;
		m_pClieThread->PostThreadMessage(WM_QUIT,NULL,NULL);
	}
	Restart();
}
void CMyAppleChessView::Restart()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			intChessManual[i][j]=0;
		}
	}
	m_bSingle=false;
	m_bMuti=false;
	m_intFlag=-1;
    InvalidateRect(CRect(STARTPTX,STARTPTY,STARTPTX+LENGTH,STARTPTY+LENGTH),TRUE);
	InvalidateRect(CRect(STARTPTX+LENGTH+20,STARTPTY,STARTPTX+LENGTH+320,STARTPTY+30),FALSE);
	m_strOut="";
}
void CMyAppleChessView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	myTurn=false;
	theHWND=m_hWnd;

	m_isServ=false;
	m_isClie=false;
	m_musicon=true;
	//��������
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_LOOP);

	CClientDC pDC(this);

	CBitmap pBlack;
	CBitmap pWhite;
	pBlack.LoadBitmap(IDB_BITMAP3);
	pWhite.LoadBitmap(IDB_BITMAP2);
	m_bitmap.LoadBitmap(IDB_BITMAP1);
	m_bitmap.GetBitmap(&bm);//��λͼ���ݴ���λͼ�ṹ
	dcImage.CreateCompatibleDC(&pDC);
	dcImage.SelectObject(&m_bitmap);
	Clicked=false;

	pBrushB=new CBrush;
	pBrushB->CreatePatternBrush(&pBlack); 
	pBrushW=new CBrush;
	pBrushW->CreatePatternBrush(&pWhite); 
	//�����ؼ�
	exit1=new CButton;
	exit1->Create(NULL,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP,
		CRect(STARTPTX+LENGTH+10,STARTPTY+210,STARTPTX+LENGTH+91,STARTPTY+249),this,ID_Exit);
	single=new CButton;
	single->Create(NULL,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP,
		CRect(STARTPTX+LENGTH+10,STARTPTY,STARTPTX+LENGTH+91,STARTPTY+39),this,ID_Single);
	muti=new CButton;
	muti->Create(NULL,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP,
		CRect(STARTPTX+LENGTH+10,STARTPTY+70,STARTPTX+LENGTH+91,STARTPTY+109),this,ID_Muti);
	option=new CButton;
	option->Create(NULL,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_BITMAP,
		CRect(STARTPTX+LENGTH+10,STARTPTY+140,STARTPTX+LENGTH+91,STARTPTY+179),this,ID_Option);
	back=new CButton;
	back->Create(NULL,WS_CHILD|BS_PUSHBUTTON|BS_BITMAP,
		CRect(STARTPTX+LENGTH+10,STARTPTY+210,STARTPTX+LENGTH+91,STARTPTY+249),this,ID_Back);
	connectBtn=new CButton;
	connectBtn->Create(NULL,WS_CHILD|BS_PUSHBUTTON|BS_BITMAP,
		CRect(STARTPTX+LENGTH+10,STARTPTY+70,STARTPTX+LENGTH+91,STARTPTY+109),this,ID_Connect);
	buildservBtn=new CButton;
	buildservBtn->Create(NULL,WS_CHILD|BS_PUSHBUTTON|BS_BITMAP,
		CRect(STARTPTX+LENGTH+10,STARTPTY,STARTPTX+LENGTH+91,STARTPTY+39),this,ID_Build);
	sendBtn=new CButton;
	sendBtn->Create(NULL,WS_CHILD|BS_PUSHBUTTON|BS_BITMAP,
		CRect(STARTPTX+LENGTH+500,STARTPTY+210,STARTPTX+LENGTH+580,STARTPTY+249),this,ID_Send);
	sendEdit=new CEdit;
	sendEdit->Create(WS_CHILD|WS_BORDER,
		CRect(STARTPTX+LENGTH+100,STARTPTY+210,STARTPTX+LENGTH+480,STARTPTY+249),this,ID_SendEdit);
	mainEdit=new CEdit;
	mainEdit->Create(WS_CHILD|WS_BORDER|WS_VSCROLL|ES_AUTOVSCROLL|ES_MULTILINE,
		CRect(STARTPTX+LENGTH+100,STARTPTY,STARTPTX+LENGTH+580,STARTPTY+200),this,ID_MainEdit);
	mainEdit->SetReadOnly();
	// If no bitmap is defined for the button, define the bitmap to the
	// system close bitmap.
	if (exit1->GetBitmap() == NULL)
    exit1->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EXIT)));
	if (single->GetBitmap() == NULL)
    single->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_SINGLE)));
	if (muti->GetBitmap() == NULL)
    muti->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_MUTI)));
	if (option->GetBitmap() == NULL)
    option->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_OPTION)));
	if (back->GetBitmap() == NULL)
    back->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BACK)));
	if (connectBtn->GetBitmap() == NULL)
    connectBtn->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_CONNECT)));
	if (buildservBtn->GetBitmap() == NULL)
    buildservBtn->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BUILD)));
	if (sendBtn->GetBitmap() == NULL)
    sendBtn->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_SEND)));
	
	AnimateWindow(GetParent()->m_hWnd,500,AW_CENTER);//������ʾ����
	::SetFocus(m_hWnd);
}


void CMyAppleChessView::OnConnect()
{
	CConnectD connectDlg;
	if(IDOK==connectDlg.DoModal())
	{
		m_isServ=false;
		m_isClie=true;
		buildservBtn->ShowWindow(FALSE);
		connectBtn->ShowWindow(FALSE);
		m_pClieThread=
			(CClieThread*)AfxBeginThread(RUNTIME_CLASS(CClieThread));//��ʼ�ͻ����߳�
		::SetFocus(m_hWnd);
	}
}
void CMyAppleChessView::OnBuild()
{
	m_isServ=true;
	m_isClie=false;
	connectBtn->ShowWindow(FALSE);
	buildservBtn->ShowWindow(FALSE);
	m_pServThread=
		(CServThread*)AfxBeginThread(RUNTIME_CLASS(CServThread));//��ʼ�������߳�
	::SetFocus(m_hWnd);
}
void CMyAppleChessView::OnSend()//���߳��з�����Ϣ
{
	if(m_isServ)
	{m_pServThread->PostThreadMessage(WM_SEND,NULL,NULL);}
	else if(m_isClie)
	{m_pClieThread->PostThreadMessage(WM_SEND,NULL,NULL);}
}
