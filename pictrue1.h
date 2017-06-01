// pictrue1.h : main header file for the PICTRUE1 application
//

#if !defined(AFX_PICTRUE1_H__44915D20_E7C4_450D_81EB_8F8E87ABFC6D__INCLUDED_)
#define AFX_PICTRUE1_H__44915D20_E7C4_450D_81EB_8F8E87ABFC6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#define STAGE1                          3
#define STAGE2                          4
#define STAGE3                          5
#define ID_SIDE                         50
#define ID_IMG_SIZE                     100
#define ID_PIC_SIZE                     400

#define IDD_ABOUTBOX                    100

#define BKCOLOR							RGB(0,0,0)
#define MARK_BK_COLOR					RGB(255,255,255)

#define XXX								ID_SIDE*3 + ID_IMG_SIZE*2
#define YYY								ID_SIDE*5



#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPictrue1App:
// See pictrue1.cpp for the implementation of this class
//

class CPictrue1App : public CWinApp
{
public:
	CPictrue1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictrue1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPictrue1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTRUE1_H__44915D20_E7C4_450D_81EB_8F8E87ABFC6D__INCLUDED_)
