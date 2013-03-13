// myAppleChessDoc.h : interface of the CMyAppleChessDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYAPPLECHESSDOC_H__094B51BD_C454_4E65_87E2_D77E18997F50__INCLUDED_)
#define AFX_MYAPPLECHESSDOC_H__094B51BD_C454_4E65_87E2_D77E18997F50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyAppleChessDoc : public CDocument
{
protected: // create from serialization only
	CMyAppleChessDoc();
	DECLARE_DYNCREATE(CMyAppleChessDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAppleChessDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyAppleChessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyAppleChessDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYAPPLECHESSDOC_H__094B51BD_C454_4E65_87E2_D77E18997F50__INCLUDED_)
