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
	ON_BN_CLICKED(ID_Send,OnSend)//各种消息映射
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
	//画棋谱
	int i;
	int j;
	int intPerLength = (int)(LENGTH/MAX);
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(intChessManual[i][j]==1)  //白棋
			{
				pDC->SelectObject(pBrushW);
				int intCenterPTX=STARTPTX+i*intPerLength+intPerLength/2+1;
				int intCenterPTY=STARTPTY+j*intPerLength+intPerLength/2+1;
				pDC->SetBrushOrg(intCenterPTX-RADIUS, intCenterPTY-RADIUS); //设置位图画刷原点
				pDC->Ellipse(CRect(intCenterPTX-RADIUS,intCenterPTY-RADIUS,
					         intCenterPTX+RADIUS,intCenterPTY+RADIUS));
			}
			else
			{
				if(intChessManual[i][j]==-1) //黑棋
				{
					pDC->SelectObject(pBrushB);
					int intCenterPTX=STARTPTX+i*intPerLength+intPerLength/2+1;
					int intCenterPTY=STARTPTY+j*intPerLength+intPerLength/2+1;
					pDC->SetBrushOrg(intCenterPTX-RADIUS, intCenterPTY-RADIUS); //设置位图画刷原点
					pDC->Ellipse(CRect(intCenterPTX-RADIUS,intCenterPTY-RADIUS,
						intCenterPTX+RADIUS,intCenterPTY+RADIUS));
				}
			}
		}
	}
	//提示信息
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
	
	m_intFlag=-1; //黑棋先行
	FillNext(); //推测下一步

	m_strOut="轮黑下 黑棋数-白棋数=00";
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
				strTemp.Format("% .2d",-m_Next[s].intValue);   //显示文字
				if(m_intFlag==1)
				m_strOut="轮白下 黑棋数-白棋数＝"+strTemp;
				else
				m_strOut="轮黑下 黑棋数-白棋数＝"+strTemp;
				InvalidateRect(CRect(STARTPTX+LENGTH+20,STARTPTY-20,STARTPTX+LENGTH+320,STARTPTY+30),false);
				
				if(m_bMuti&&m_isServ)
				{
					m_pServThread->PostThreadMessage(WM_MYDOWN,NULL,NULL);
				}
				else if(m_bMuti&&m_isClie)
				{
					m_pClieThread->PostThreadMessage(WM_MYDOWN,NULL,NULL);
				}
				if(!FillNext())  //是否还有下一步
				{
					m_bSingle=false;
					m_bMuti=false;
					if(m_Next[s].intValue==0)
					{
						MessageBox("平局!");
					}
					if(m_Next[s].intValue>0)
					{
						MessageBox("白胜!");
					}
					else
					{
						MessageBox("黑胜!");
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
				strTemp.Format("% .2d",-m_Next[s].intValue);   //显示文字
				if(m_intFlag==1)
				m_strOut="轮白下 黑棋数-白棋数＝"+strTemp;
				else
				m_strOut="轮黑下 黑棋数-白棋数＝"+strTemp;
				InvalidateRect(CRect(STARTPTX+LENGTH+20,STARTPTY-20,STARTPTX+LENGTH+320,STARTPTY+30),false);
				if(!FillNext())  //是否还有下一步
				{
					m_bSingle=false;
					m_bMuti=false;
					
					if(m_Next[s].intValue==0)
					{
						MessageBox("平局!");
					}
					if(m_Next[s].intValue>0)
					{
						MessageBox("白胜!");
					}
					else
					{
						MessageBox("黑胜!");
					}
				}
				break;
			}
		}
	myTurn=true;
	
	return 0;
}
//该函数检查某一个方向上的子是否构成了夹击之势，方向由dx和dy的不同组合来表示
//如dx=0,dy=1表示下方，dx=-1,dy=-1表示左上方等
//i,j表示落子位置
//flag=-1,黑棋；flag=1,白棋
void CMyAppleChessView::CheckDirect(int i, int j, int dx, int dy, int Flag, int intChess[MAX][MAX], bool *pboolVaild)
{
	int s=i+dx;
	int t=j+dy;
	bool boolFristOK=false;

	while(INBORAD(s,t) && intChess[s][t]==-m_intFlag) 
	{
		s+=dx;
		t+=dy;
		boolFristOK=true;   //构成了夹击之势
	}

	if(INBORAD(s,t) && boolFristOK && intChess[s][t]==m_intFlag)
	{
		*pboolVaild=true;    //该方向落子有效
		do
		{
			s-=dx;
			t-=dy;
			intChess[s][t]=m_intFlag;   //改变棋局吃掉对方的子
		}while(s!=i || t!=j);
	}
}
//检查在i,j处的落子是否可以

void CMyAppleChessView::CheckNext(int i,int j, int intFlag)
{
	bool boolVaild=false;
	int intTempChess[8][8];
	int s;
	int t;
	
	for(s=0;s<MAX;s++)   //复制当前棋局
		for(t=0;t<MAX;t++)
			intTempChess[s][t]=intChessManual[s][t];
	
	//对8个方向分别检查
	CheckDirect(i,j,1,0,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,0,1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,-1,0,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,0,-1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,1,1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,-1,-1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,1,-1,intFlag,intTempChess,&boolVaild);
	CheckDirect(i,j,-1,1,intFlag,intTempChess,&boolVaild);
	if(boolVaild) //符合落子条件，将该棋局保存到m_NEXT中
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
//找出下一步的所有可能棋局存放到m_Next中
BOOL CMyAppleChessView::FillNext()
{
	m_intNextNumber=-1;
	
	for(int i=0;i<MAX;i++)  //对当前棋局的所有空格检查是否可以落子
		for(int j=0;j<MAX;j++)
			if(intChessManual[i][j]==0)
				CheckNext(i,j,m_intFlag);
	i++;
	if(m_intNextNumber>=0)
		return true;   //至少存在一个可能的落子处
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
//由于禁用了MFC的菜单栏标题栏等，所以要写一个窗口移动函数
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
void CMyAppleChessView::OnSingle()//单机
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
void CMyAppleChessView::OnMuti()//联机
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
	//背景音乐
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_LOOP);

	CClientDC pDC(this);

	CBitmap pBlack;
	CBitmap pWhite;
	pBlack.LoadBitmap(IDB_BITMAP3);
	pWhite.LoadBitmap(IDB_BITMAP2);
	m_bitmap.LoadBitmap(IDB_BITMAP1);
	m_bitmap.GetBitmap(&bm);//将位图数据存入位图结构
	dcImage.CreateCompatibleDC(&pDC);
	dcImage.SelectObject(&m_bitmap);
	Clicked=false;

	pBrushB=new CBrush;
	pBrushB->CreatePatternBrush(&pBlack); 
	pBrushW=new CBrush;
	pBrushW->CreatePatternBrush(&pWhite); 
	//建立控件
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
	
	AnimateWindow(GetParent()->m_hWnd,500,AW_CENTER);//动画显示窗口
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
			(CClieThread*)AfxBeginThread(RUNTIME_CLASS(CClieThread));//开始客户端线程
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
		(CServThread*)AfxBeginThread(RUNTIME_CLASS(CServThread));//开始服务器线程
	::SetFocus(m_hWnd);
}
void CMyAppleChessView::OnSend()//向线程中发送消息
{
	if(m_isServ)
	{m_pServThread->PostThreadMessage(WM_SEND,NULL,NULL);}
	else if(m_isClie)
	{m_pClieThread->PostThreadMessage(WM_SEND,NULL,NULL);}
}
