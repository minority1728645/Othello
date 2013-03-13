// ClieThread.cpp : implementation file
//

#include "stdafx.h"
#include "myapplechess.h"
#include "ClieThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClieThread

IMPLEMENT_DYNCREATE(CClieThread, CWinThread)

CClieThread::CClieThread()
{
}

CClieThread::~CClieThread()
{
	closesocket(sockClient);
}

BOOL CClieThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	
	sockClient=socket(AF_INET,SOCK_STREAM,0);	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(dwIP);//服务器网络地址
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	//向服务器发出连接请求
	if(connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR))==0)
	{
		//接收数据	
		char recvChar;
		recv(sockClient,&recvChar,1,0);
		m_pRecvThread=AfxBeginThread(ThreadRecv,&sockClient);//开始接收数据线程
		if(recvChar=='B')
		{
			AfxMessageBox("您执白");
			myTurn=false;
		}
		else 
		{
			AfxMessageBox("您执黑");
			myTurn=true;
		}
	}
	else AfxMessageBox("连接失败!");	
	return TRUE;
}

int CClieThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	TerminateThread(m_pRecvThread->m_hThread,0);
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CClieThread, CWinThread)
	//{{AFX_MSG_MAP(CClieThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	
ON_THREAD_MESSAGE(WM_MYDOWN,OnMyDown)
ON_THREAD_MESSAGE(WM_SEND,OnSend)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClieThread message handlers
LONG CClieThread::OnMyDown(UINT wParam,LONG lParam)
{

	//向客户端发送数据
	char sendChess[3];
	sendChess[0]='C';
	sendChess[1]=posiX;
	sendChess[2]=posiY;
	send(sockClient,sendChess,3,0);
	return 0;
}

UINT CClieThread::ThreadRecv(LPVOID pParam)
{
	SOCKET sockClient=*((SOCKET*)pParam);
	char flag;
	while(true)
	{
		
		if(1==recv(sockClient,&flag,1,0))
		{
			if(flag=='C')
			{
				char recvChess[2];
				recv(sockClient,recvChess,2,0);
				posiX=recvChess[0];
				posiY=recvChess[1];
				::PostMessage(theHWND,WM_RIVALDOWN,NULL,NULL);
			}
			else if(flag=='T')
			{
				char num;
				recv(sockClient,&num,1,0);
				int len=(int)num;
				char *strRecv;
				strRecv=new char [len];
				recv(sockClient,strRecv,len,0);
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
LONG CClieThread::OnSend(UINT wParam,LONG lParam)
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
	send(sockClient,sendChar,len+3,0);
	delete [] sendChar;
	CString strTemp;
	(CWnd::FromHandle(theHWND))->GetDlgItemText(ID_MainEdit,strTemp);
	str+="\r\n";
	str+=strTemp;
	(CWnd::FromHandle(theHWND))->SetDlgItemText(ID_MainEdit,str);
	(CWnd::FromHandle(theHWND))->SetDlgItemText(ID_SendEdit,"");
	return 0;
}