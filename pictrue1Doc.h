// pictrue1Doc.h : interface of the CPictrue1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTRUE1DOC_H__3FAC6065_77EC_4DFE_8FEB_C1EA7462D865__INCLUDED_)
#define AFX_PICTRUE1DOC_H__3FAC6065_77EC_4DFE_8FEB_C1EA7462D865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPictrue1Doc : public CDocument
{
protected: // create from serialization only
	CPictrue1Doc();
	DECLARE_DYNCREATE(CPictrue1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictrue1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPictrue1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPictrue1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTRUE1DOC_H__3FAC6065_77EC_4DFE_8FEB_C1EA7462D865__INCLUDED_)
