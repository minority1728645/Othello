// ServThread.cpp : implementation file
//

#include "stdafx.h"
#include "myapplechess.h"
#include "ServThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CServThread


IMPLEMENT_DYNCREATE(CServThread, CWinThread)

CServThread::CServThread()
{
}

CServThread::~CServThread()
{
	closesocket(sockConn);
}

BOOL CServThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	// TODO:  perform any per-thread cleanup here
	//创建用于监听的套接字
	sockSrv=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN addrSrv;//用于保存本地地址和指定的端口
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//本地地址，任意地址，转换为网络字节顺序
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	listen(sockSrv,1);
	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR);
	sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
	closesocket(sockSrv);
	CString strConnect;
	strConnect.Format("与%s连接成功",inet_ntoa(addrClient.sin_addr));
	AfxMessageBox(strConnect);
	char sendChar;
	if(isBlack)sendChar='B';
	else sendChar='W';
	myTurn=isBlack;
	//向客户端发送数据
	send(sockConn,&sendChar,1,0);
	m_pRecvThread=AfxBeginThread(ThreadRecv,&sockConn);//开始接收数据线程
	return TRUE;
}

int CServThread::ExitInstance()
{
	TerminateThread(m_pRecvThread->m_hThread,0);
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CServThread, CWinThread)
	//{{AFX_MSG_MAP(CServThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
ON_THREAD_MESSAGE(WM_MYDOWN,OnMyDown)
ON_THREAD_MESSAGE(WM_SEND,OnSend)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServThread message handlers
LONG CServThread::OnMyDown(UINT wParam,LONG lParam)
{
	char sendChess[3];
	sendChess[0]='C';
	sendChess[1]=posiX;
	sendChess[2]=posiY;
	//向客户端发送数据
	send(sockConn,sendChess,3,0);
	return 0;
}

int CServThread::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CWinThread::Run();
}
UINT CServThread::ThreadRecv(LPVOID pParam)
{
	
	SOCKET sockConn=*((SOCKET*)pParam);
	char flag;
	while(true)
	{
		if(1==recv(sockConn,&flag,1,0))
		{
			if(flag=='C')
			{
				char recvChess[2];
				recv(sockConn,recvChess,2,0);
				posiX=recvChess[0];
				posiY=recvChess[1];
				::PostMessage(theHWND,WM_RIVALDOWN,NULL,NULL);
			}
			else if(flag=='T')
			{
				char num;
				recv(sockConn,&num,1,0);
				int len=(int)num;
				char *strRecv;
				strRecv=new char [len];
				recv(sockConn,strRecv,len,0);
				CString str;
				str.Format("对方:%s",strRecv);
				delete [] strRecv;
				CString strTemp;
				(CWnd::FromHandle(theHWND))->GetDlgItemText(ID_MainEdit,strTemp);
				str+="\r\n";
				str+=strTemp;
				(CWnd::FromHandle(theHWND))->SetDlgItemText(ID_MainEdit,str);
			}
		}
		else
		{
			CString str="连接断开!";
			CString strTemp;
			(CWnd::FromHandle(theHWND))->GetDlgItemText(ID_MainEdit,strTemp);
			str+="\r\n";
			str+=strTemp;
			(CWnd::FromHandle(theHWND))->SetDlgItemText(ID_MainEdit,str);
			break;
		}
	}
	return 0;
}
LONG CServThread::OnSend(UINT wParam,LONG lParam)
{
	CString str,strSend;
	(CWnd::FromHandle(theHWND))->GetDlgItemText(ID_SendEdit,strSend);
	str.Format("我:%s",strSend);
	int len=strSend.GetLength();
	char* sendChar;
	sendChar=new char [len+3];
	sendChar[0]='T';sendChar[1]=(char)(len+1);sendChar[len+2]='\0';
	for(int i=2;i<len+2;i++)
	{
		sendChar[i]=strSend[i-2];
	}
	send(sockConn,sendChar,len+3,0);
	delete [] sendChar;
	CString strTemp;
	(CWnd::FromHandle(theHWND))->GetDlgItemText(ID_MainEdit,strTemp);
	str+="\r\n";
	str+=strTemp;
	(CWnd::FromHandle(theHWND))->SetDlgItemText(ID_MainEdit,str);
	(CWnd::FromHandle(theHWND))->SetDlgItemText(ID_SendEdit,"");
	return 0;
}