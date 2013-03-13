// myAppleChessDoc.cpp : implementation of the CMyAppleChessDoc class
//

#include "stdafx.h"
#include "myAppleChess.h"

#include "myAppleChessDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessDoc

IMPLEMENT_DYNCREATE(CMyAppleChessDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyAppleChessDoc, CDocument)
	//{{AFX_MSG_MAP(CMyAppleChessDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessDoc construction/destruction

CMyAppleChessDoc::CMyAppleChessDoc()
{
	// TODO: add one-time construction code here

}

CMyAppleChessDoc::~CMyAppleChessDoc()
{
}

BOOL CMyAppleChessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessDoc serialization

void CMyAppleChessDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessDoc diagnostics

#ifdef _DEBUG
void CMyAppleChessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyAppleChessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyAppleChessDoc commands
