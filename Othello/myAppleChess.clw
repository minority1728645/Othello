; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServThread
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "myapplechess.h"
LastPage=0

ClassCount=9
Class1=CMainFrame
Class2=CMyAppleChessApp
Class3=CAboutDlg
Class4=CMyAppleChessDoc
Class5=CMyAppleChessView

ResourceCount=5
Resource1=IDR_MAINFRAME
Class6=COption
Resource2=IDD_ABOUTBOX
Resource3=IDD_DIALOG1
Resource4=IDD_Connect
Class7=CConnectD
Class8=CServThread
Class9=CClieThread
Resource5=IDD_DIALOG2

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CMyAppleChessApp]
Type=0
BaseClass=CWinApp
HeaderFile=myAppleChess.h
ImplementationFile=myAppleChess.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=myAppleChess.cpp
ImplementationFile=myAppleChess.cpp
LastObject=ID_APP_EXIT

[CLS:CMyAppleChessDoc]
Type=0
BaseClass=CDocument
HeaderFile=myAppleChessDoc.h
ImplementationFile=myAppleChessDoc.cpp

[CLS:CMyAppleChessView]
Type=0
BaseClass=CView
HeaderFile=myAppleChessView.h
ImplementationFile=myAppleChessView.cpp
LastObject=CMyAppleChessView
Filter=C
VirtualFilter=VWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:COption]
Type=0
HeaderFile=Option.h
ImplementationFile=Option.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=COption

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342308361
Control6=IDC_RADIO4,button,1342177289
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_Connect]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IPADDRESS1,SysIPAddress32,1342242816

[CLS:CConnectD]
Type=0
HeaderFile=ConnectD.h
ImplementationFile=ConnectD.cpp
BaseClass=CDialog
Filter=D
LastObject=CConnectD
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control4=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_REPLAY
CommandCount=17

[CLS:CServThread]
Type=0
HeaderFile=ServThread.h
ImplementationFile=ServThread.cpp
BaseClass=CWinThread
Filter=W
LastObject=CServThread
VirtualFilter=TC

[CLS:CClieThread]
Type=0
HeaderFile=ClieThread.h
ImplementationFile=ClieThread.cpp
BaseClass=CWinThread
Filter=D
LastObject=CClieThread

