// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D50D4EBF_57D7_4A60_B4AE_52A949A6BDB1__INCLUDED_)
#define AFX_STDAFX_H__D50D4EBF_57D7_4A60_B4AE_52A949A6BDB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define   WINVER   0x0500   //VC6����AnimateWindow
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#endif // _AFX_NO_AFXCMN_SUPPORT
#include <MMSYSTEM.h>
#pragma comment( lib, "Winmm.lib")

//#include <WinSock2.h>
//#pragma comment (lib,"Ws2_32.lib") //�����Ws2_32.lib
#include <Afxsock.h>

#include "ConnectD.h"

#define WM_SEND WM_USER+3
#define WM_RIVALDOWN WM_USER+2
#define WM_MYDOWN WM_USER+1


#define WINDOWW 1200
#define WINDOWH 800

#define STARTPTX 323 //���̵���ʼx����
#define STARTPTY 261 //���̵���ʼy����
#define RADIUS 13    //���Ӱ뾶
#define BKCOLOR RGB(255,255,0)   //���̱���ɫ
#define MAX 8          //���̸���
#define MAXSTEP 30     //��һ�������ܵ������
#define LENGTH MAX*32  //ÿ��32������
#define INBORAD(s,t) (s>=0 && s<MAX && t>=0 && t<MAX)   //�ж��Ƿ���������
extern bool isBlack;
extern int intChessManual[MAX][MAX];    //��ǰ�����
extern DWORD dwIP;
extern HWND theHWND;
extern bool myTurn;
extern char posiX;
extern char posiY;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D50D4EBF_57D7_4A60_B4AE_52A949A6BDB1__INCLUDED_)
