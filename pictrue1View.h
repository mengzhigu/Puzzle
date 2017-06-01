// pictrue1View.h : interface of the CPictrue1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTRUE1VIEW_H__B3AD57A0_446B_417E_B888_C1A61534CD44__INCLUDED_)
#define AFX_PICTRUE1VIEW_H__B3AD57A0_446B_417E_B888_C1A61534CD44__INCLUDED_



#define ID_IMG_SIZE 100

#include "PcShow.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


 class CPictrue1View : public CView
{
public: // create from serialization only
	CPictrue1View();
	DECLARE_DYNCREATE(CPictrue1View)

// Attributes
public:
	CPictrue1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictrue1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	//virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//void Show();
	//int Judgmentcomplexity(); 
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPictrue1View();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPictrue1View)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnStage1();
	afx_msg void OnStage2();
	afx_msg void OnStage3();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPicture1();
	afx_msg void OnPicture2();
	afx_msg void OnPicture3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPicture4();
	afx_msg void OnPicSelect();
	afx_msg void OnBegin();
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void OnStart();
	BOOL m_bTimer;
	int m_nSecend;
	int m_nStep;
	int m_nStart;//是对打开游戏是否的判断依据
	CBitmap m_bitmap;	
	CBitmap m_bitmap1;
	CBitmap m_bitmap2;
	CBitmap m_bitmap3;
	CBitmap m_bitmap4;


	int m_nImgOrgY;
	int m_nImgOrgX;//每一小片图片在窗口显示的大小
	BITMAP m_bmp;
	int m_nPicWidth;//位图的宽度
	int m_nStage;//每行分的块数
	void RandPic();
	BOOL IsWin(int m_nstage);
void Prompt();

	CPcShow m_pShow[STAGE3+1][STAGE3];
};
#ifndef _DEBUG  // debug version in pictrue1View.cpp
inline CPictrue1Doc* CPictrue1View::GetDocument()
   { return (CPictrue1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTRUE1VIEW_H__B3AD57A0_446B_417E_B888_C1A61534CD44__INCLUDED_)
