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
//�����������߳��ﴫ��,�Ұ�һ���ֱ����������ȫ�ֵ�
#define STARTPTX 323 //���̵���ʼx����
#define STARTPTY 261 //���̵���ʼy����
#define RADIUS 13    //���Ӱ뾶
#define BKCOLOR RGB(255,255,0)   //���̱���ɫ
#define MAX 8          //���̸���
#define MAXSTEP 30     //��һ�������ܵ������
#define LENGTH MAX*32  //ÿ��32������
#define INBORAD(s,t) (s>=0 && s<MAX && t>=0 && t<MAX)   //�ж��Ƿ���������
struct structNext{      //�洢��һ�������
	int i;              //����λ��
	int j;
	int intNextManual[MAX][MAX];
	int intValue;       //����ֵĺ�����-�������Ĳ�ֵ
};
class CMyAppleChessView : public CView
{
private:
	bool m_bSingle;//����
	bool m_bMuti;//����
	bool m_musicon;//����
	bool Clicked;//�Ƿ񱻵��
	CPoint prepoint;
	CBitmap m_bitmap;//һ��λͼ����
	BITMAP bm;//λͼ��Ϣ�ṹ
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
	CEdit *mainEdit;//���ֿؼ�

	COption op;//ѡ��Ի���
    CServThread* m_pServThread;//�����з������߳�
	CClieThread* m_pClieThread;//�����пͻ����߳�
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
    afx_msg LRESULT OnRivalDown(WPARAM wParam,LPARAM lParam);//������Ϣ��Ӧ����
	DECLARE_MESSAGE_MAP()

private:
	void CheckDirect(int i, int j, int dx, int dy, int Flag, int intChess[MAX][MAX], bool* pboolVaild);
	void CheckNext(int i, int j, int Flag);
	BOOL FillNext();    //�Ʋ���һ�����������
	int m_intFlag;    //���ķ�����
	structNext m_Next[MAXSTEP];  //�����һ�ε����п������
	int m_intNextNumber;  //������ֵ�����
	CString m_strOut;     //��ʾ������ַ���
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
