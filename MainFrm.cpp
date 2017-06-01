// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "pictrue1.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
if( !CFrameWnd::PreCreateWindow(cs) )
   return FALSE;
// TODO: Modify the Window class or styles here by modifying
// the CREATESTRUCT cs
//cs.hMenu = NULL;//ȥ���˵�
cs.style&=~WS_MAXIMIZEBOX; //���ð�����󻯰�ť 
cs.style&=~WS_THICKFRAME;//��ֹ�û��ı䴰�ڴ�С

cs.style&=~FWS_ADDTOTITLE;//��FWS_ADDTOTITLEȥ��

cs. lpszName = "ƴͼ��Ϸ";//�ı���⣬�滻�Լ��ı���
return TRUE;



}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG

void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	
	//����ͼ��
	SetIcon(m_hIcon,TRUE);
//	SetIcon(m_hIcon,FALSE);
	
	SetWindowPos(NULL,100 ,100 ,ID_SIDE*6+ID_IMG_SIZE*2+ID_PIC_SIZE ,ID_PIC_SIZE+ID_SIDE*6 ,SWP_NOZORDER | SWP_NOMOVE);

	GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_EASY,MF_BYCOMMAND | MF_CHECKED);		//���� Ĭ�ϵĳ����˵�
	GetMenu()->GetSubMenu(1)->CheckMenuItem(IDB_BITMAP2,MF_BYCOMMAND | MF_CHECKED);	//���� Ĭ�ϵ� ��һ��ͼƬ

	return 0;
}

