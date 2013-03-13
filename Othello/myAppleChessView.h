// myAppleChessView.h : interface of the CMyAppleChessView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYAPPLECHESSVIEW_H__44C50360_9C63_45A9_8FC0_036AE1887C4B__INCLUDED_)
#define AFX_MYAPPLECHESSVIEW_H__44C50360_9C63_45A9_8FC0_036AE1887C4B__INCLUDED_
#include "Option.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ServThread.h"
#include "ClieThread.h"
//由于懒得往线程里传参,我把一部分变量定义成了全局的
#define STARTPTX 323 //棋盘的起始x坐标
#define STARTPTY 261 //棋盘的起始y坐标
#define RADIUS 13    //棋子半径
#define BKCOLOR RGB(255,255,0)   //棋盘背景色
#define MAX 8          //棋盘格数
#define MAXSTEP 30     //下一步最多可能的棋局数
#define LENGTH MAX*32  //每格32个像素
#define INBORAD(s,t) (s>=0 && s<MAX && t>=0 && t<MAX)   //判断是否在棋盘中
struct structNext{      //存储下一步的棋局
	int i;              //落子位置
	int j;
	int intNextManual[MAX][MAX];
	int intValue;       //本棋局的黑棋数-白棋数的差值
};
class CMyAppleChessView : public CView
{
private:
	bool m_bSingle;//单机
	bool m_bMuti;//联机
	bool m_musicon;//音乐
	bool Clicked;//是否被点击
	CPoint prepoint;
	CBitmap m_bitmap;//一个位图对象
	BITMAP bm;//位图信息结构
	CDC dcImage;
	CBrush *pBrushB;
	CBrush *pBrushW;
	CButton *single;
	CButton *muti;
	CButton *option;
	CButton *exit1;
	CButton *back;
	CButton *connectBtn;
	CButton *buildservBtn;
	CButton *sendBtn;
	CEdit *sendEdit;
	CEdit *mainEdit;//各种控件

	COption op;//选项对话框
    CServThread* m_pServThread;//联机中服务器线程
	CClieThread* m_pClieThread;//联机中客户端线程
protected: // create from serialization only
	CMyAppleChessView();
	DECLARE_DYNCREATE(CMyAppleChessView)
// Attributes
public:
	CMyAppleChessDoc* GetDocument();
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAppleChessView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CMyAppleChessView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyAppleChessView)
	afx_msg void OnReplay();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnExit();
	afx_msg void OnMuti();
	afx_msg void OnSingle();
	afx_msg void OnOption();
	afx_msg void OnBack();
	afx_msg void OnConnect();
	afx_msg void OnBuild();
	afx_msg void OnSend();
    afx_msg LRESULT OnRivalDown(WPARAM wParam,LPARAM lParam);//各种消息响应函数
	DECLARE_MESSAGE_MAP()

private:
	void CheckDirect(int i, int j, int dx, int dy, int Flag, int intChess[MAX][MAX], bool* pboolVaild);
	void CheckNext(int i, int j, int Flag);
	BOOL FillNext();    //推测下一步的所有棋局
	int m_intFlag;    //轮哪方下子
	structNext m_Next[MAXSTEP];  //存放下一次的所有可能棋局
	int m_intNextNumber;  //可能棋局的总数
	CString m_strOut;     //提示的输出字符串
	void Restart();
	bool m_isServ;
	bool m_isClie;

};



#ifndef _DEBUG  // debug version in myAppleChessView.cpp
inline CMyAppleChessDoc* CMyAppleChessView::GetDocument()
   { return (CMyAppleChessDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYAPPLECHESSVIEW_H__44C50360_9C63_45A9_8FC0_036AE1887C4B__INCLUDED_)
