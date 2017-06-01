// pictrue1Doc.cpp : implementation of the CPictrue1Doc class
//

#include "stdafx.h"
#include "pictrue1.h"

#include "pictrue1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictrue1Doc

IMPLEMENT_DYNCREATE(CPictrue1Doc, CDocument)

BEGIN_MESSAGE_MAP(CPictrue1Doc, CDocument)
	//{{AFX_MSG_MAP(CPictrue1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictrue1Doc construction/destruction

CPictrue1Doc::CPictrue1Doc()
{
	// TODO: add one-time construction code here

}

CPictrue1Doc::~CPictrue1Doc()
{
}

BOOL CPictrue1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPictrue1Doc serialization

void CPictrue1Doc::Serialize(CArchive& ar)
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
// CPictrue1Doc diagnostics

#ifdef _DEBUG
void CPictrue1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPictrue1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictrue1Doc commands
