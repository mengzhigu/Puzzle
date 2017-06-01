// pictrue1View.cpp : implementation of the CPictrue1View class
//

#include "stdafx.h"
#include "pictrue1.h"

#include "pictrue1Doc.h"
#include "pictrue1View.h"
   
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



      
/////////////////////////////////////////////////////////////////////////////
// CPictrue1View
    

IMPLEMENT_DYNCREATE(CPictrue1View, CView)

BEGIN_MESSAGE_MAP(CPictrue1View, CView)
	//{{AFX_MSG_MAP(CPictrue1View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		
	ON_COMMAND(ID_GAME_EASY, OnStage1)
	ON_COMMAND(ID_GAME_MIDDLE, OnStage2)
	ON_COMMAND(ID_GAME_HARD, OnStage3)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_COMMAND(ID_PICTURE1, OnPicture1)
	ON_COMMAND(ID_PICTURE2, OnPicture2)
	ON_COMMAND(ID_PICTURE3, OnPicture3)
	ON_WM_TIMER()
	ON_COMMAND(ID_PICTURE4, OnPicture4)
	ON_COMMAND(ID_FILE_OPEN, OnPicSelect)
	ON_COMMAND(ID_GAME_START, OnBegin)

	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

    
/////////////////////////////////////////////////////////////////////////////
// CPictrue1View construction/destruction

CPictrue1View::CPictrue1View()
{
	// TODO: add construction code here
		//���ʱ��
	srand((unsigned)time(NULL));	

	//Ĭ�Ͻ�����Ϸ�ǳ���
	m_nStage=STAGE1;				

	//CBitmap �������λͼ���
	m_bitmap.LoadBitmap(IDB_BITMAP2);	//m_bitmap�ǳ������й����еĵ�ǰλͼ

	m_bitmap1.LoadBitmap(IDB_BITMAP2);
	m_bitmap2.LoadBitmap(IDB_BITMAP3);
	m_bitmap3.LoadBitmap(IDB_BITMAP4);
	m_bitmap4.LoadBitmap(IDB_BITMAP5);

	//δ���ö�ʱ��
	m_bTimer=FALSE;

	//[��ʼ��ť] ͬʱ���԰�һЩ��ʼ���Ĺ����ŵ��������������ִ��
	OnStart();			

}


void CPictrue1View::OnStart()
{
	m_bitmap.GetBitmap(&m_bmp);			//m_bmp���λͼ��Ϣ �ŵ�BITMAP�ṹ����
	m_nPicWidth= ID_PIC_SIZE/m_nStage;	// ͼ���� = ͼ��Ĵ�С/�ֵĿ����൱��һ������������
	
	RandPic();
	
	//���ָ��ÿһСƬͼƬ�ڴ�����ʾ�Ĵ�С
	//ͼƬ�ĸߺͿ���ܲ�һ�� Ҫ���ֿ���
	m_nImgOrgX=m_bmp.bmWidth/m_nStage;//bmWidth��ϵͳ��ͼƬ�Ŀ��
	m_nImgOrgY=m_bmp.bmHeight/m_nStage;

	m_nSecend=0;	//����ʱ��
	m_nStep=0;		//���߲���
	m_nStart=0;		//�Ƿ��Ѿ���ʼƴͼ��Ϸ ����Ѿ���ʼ�� ��ʼ��ʱ�ͼƲ�
	
	if (m_bTimer)		//��Ϊÿ�ζ�Ҫ��գ������ǰ�ж�ʱ������  ��ɾ����ʱ��
	{
		KillTimer(1);//��һ����Ϊ��λ��
		m_bTimer=FALSE;	//ɾ����ʱ���� ���ھ�û�ж�ʱ����
	}		
}

void CPictrue1View::RandPic()
{
	int randNum;					//�洢�����
	int i,j;

	int randArr[STAGE3*STAGE3];		//�洢�����������

	int reverSum;					//�洢�����

	//do while();ѭ�� ȷ��������ƴͼ�н�  
	do 
	{
		reverSum=0;
		//forѭ��:ֻ�ô洢 m_nStage*m_nStage �����������
		// 0 2 3
		// 4 5 6
		// 7 8 9
		for (i=1 ;i<m_nStage*m_nStage ;i++)
		{
			randNum=int(rand()%(m_nStage*m_nStage-1))+2;	//��� 2 -- m_nStage*m_nStage�������
			//�Ƚ��ظ����
			for (j=1 ;j<i ;j++)			
			{	
				if (randArr[j] == randNum)	//�������õ������ ����֮ǰ��������Ƚ�
				{							//����������ظ�������� ���������
					j=0;
					randNum=int(rand()%(m_nStage*m_nStage-1))+2;
				}
			}
			
			randArr[i]=randNum;				//��������洢���ظ��������
			
			//��������
			for (int n=1 ;n<=i ;n++)		
			{
				if (randArr[i]<randArr[n])
				{
					reverSum++;
				}
			}			
		}	
	}while(reverSum%2!=0);	//��������Ϊ���� �������漴
	
	randArr[0]=0;	//��һ����ֵΪ 0
	//��m_pShow�����и�ֵ
	int pic=0;									
	for (i=0 ;i<m_nStage ;i++)		//   0   *   *
	{								//   *   *   *
		for (j=0 ;j<m_nStage;j++)	//   *   *   *
		{	
				
				m_pShow[i][j].picIn=i*m_nStage+j;	//picIn ����ʵ��
				m_pShow[i][j].picOut=randArr[pic];	//picOut ����ʾ�� ȡ�������еĲ��ظ��������
				pic++;
		}
	}
	
	m_pShow[0][0].picIn=0;		//��һ�е�һ��Ϊ0 
	m_pShow[0][0].picOut=0;		//0 ��ʾ Ϊ�� �����Ƶ����Ǹ�λ��

	//����������
}

CPictrue1View::~CPictrue1View()
{
	
}

BOOL CPictrue1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPictrue1View drawing
     

void CPictrue1View::OnDraw(CDC* pDC)
{
CPictrue1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	

	CRect rect;
	GetWindowRect(&rect);		//��ô��ھ�������
	ScreenToClient(&rect);		//��Ļ���� ת��Ϊ �ͻ�������
	
	CBrush bkBrush(BKCOLOR);	//�����ɫ������ˢ
	pDC->FillRect(CRect(rect.left+5,rect.top+5,rect.right,rect.bottom),&bkBrush);
	//��䴰�ھ������� +5 �Ե������ǿ

	CDC dcCompatible;	
	dcCompatible.CreateCompatibleDC(pDC);
	dcCompatible.SelectObject(&m_bitmap);

    //start to draw the picture
	pDC->SetStretchBltMode(COLORONCOLOR);	//********
	int i ,j;
	for (i=0 ;i<m_nStage ;i++)
	{
		for (j=0 ;j<m_nStage ;j++)
		{
			
			 if (m_pShow[i][j].picOut == 0)//���Ƶ�һ�е�һ��ͼ
			{
				pDC->Rectangle(XXX + j*m_nPicWidth  ,YYY + (i-1)*m_nPicWidth,
							XXX + (j+1)*m_nPicWidth  ,YYY + i*m_nPicWidth	);

			}
			else
			{
				pDC->StretchBlt(
					XXX + j*m_nPicWidth  ,
					YYY + (i-1)*m_nPicWidth,				//��������һ�����
					m_nPicWidth,
					m_nPicWidth,
					&dcCompatible,							//���ര���� ���εĸߺͿ�
					((m_pShow[i][j].picOut-1)%m_nStage) * m_nImgOrgX, 
					((m_pShow[i][j].picOut-1)/m_nStage) * m_nImgOrgY,	//m_nImgOrgX*i ,m_nImgOrgY*j ,
					m_nImgOrgX ,
					m_nImgOrgY ,
					SRCCOPY
					);
			}
		}
	}
	//������ߵ�ͼ��
	
   //���ϽǵĲ���ͼ  ����ͼ���ǵ�ǰ��ͼƬ
	dcCompatible.SelectObject(&m_bitmap);

	pDC->StretchBlt(
		ID_SIDE*3/2,
		ID_SIDE,
		ID_IMG_SIZE*2,
		ID_IMG_SIZE*2,
		&dcCompatible,
		0, 
		0,
		m_bmp.bmWidth,
		m_bmp.bmHeight,
		SRCCOPY
		);

	for (i=1;i<m_nStage;i++)
	{
		// - - ����
		pDC->MoveTo(ID_SIDE*3/2,ID_SIDE+ID_IMG_SIZE*2/m_nStage*i);
		pDC->LineTo(ID_SIDE*3/2+ID_IMG_SIZE*2,ID_SIDE+ID_IMG_SIZE*2/m_nStage*i);

		// | | ����
		pDC->MoveTo(ID_SIDE*3/2+ID_IMG_SIZE*2/m_nStage*i,ID_SIDE);
		pDC->LineTo(ID_SIDE*3/2+ID_IMG_SIZE*2/m_nStage*i,ID_SIDE+ID_IMG_SIZE*2);

	}		


    //  the first example of pic
 	dcCompatible.SelectObject(&m_bitmap1);
	pDC->StretchBlt(
		ID_SIDE,
		ID_IMG_SIZE*2+ID_SIDE*2,
		ID_IMG_SIZE,
		ID_IMG_SIZE,
		&dcCompatible,
		0, 
		0,
		ID_PIC_SIZE,
		ID_PIC_SIZE,
		SRCCOPY
		);

   //  the second example of pic
	dcCompatible.SelectObject(&m_bitmap2);
	pDC->StretchBlt(
		ID_SIDE*2+ID_IMG_SIZE,
		ID_IMG_SIZE*2+ID_SIDE*2,
		ID_IMG_SIZE,
		ID_IMG_SIZE,
		&dcCompatible,
		0, 
		0,
		ID_PIC_SIZE,
		ID_PIC_SIZE,
		SRCCOPY
		);
    //  the third example of pic
	dcCompatible.SelectObject(&m_bitmap3);	
	pDC->StretchBlt(
		ID_SIDE,
		ID_IMG_SIZE*3+ID_SIDE*3,
		ID_IMG_SIZE,
		ID_IMG_SIZE,
		&dcCompatible,
		0, 
		0,
		ID_PIC_SIZE,
		ID_PIC_SIZE,
		SRCCOPY
		);
    //  the forth example of pic
	dcCompatible.SelectObject(&m_bitmap4);
	pDC->StretchBlt(
		ID_SIDE*2+ID_IMG_SIZE,
		ID_IMG_SIZE*3+ID_SIDE*3,
		ID_IMG_SIZE,
		ID_IMG_SIZE,
		&dcCompatible,
		0, 
		0,
		ID_PIC_SIZE,
		ID_PIC_SIZE,
		SRCCOPY
		);

    //show the mark information on the Right
	CString strTime,strStep;
	strTime.Format("����ʱ��: %d ��",m_nSecend);
	strStep.Format("���߲���: %d ��",m_nStep);
	
	pDC->SetBkColor(MARK_BK_COLOR);	//setting the backcolour of the mark
	
	pDC->TextOut(XXX + ID_PIC_SIZE +ID_SIDE/5 ,300,strTime);
	pDC->TextOut(XXX + ID_PIC_SIZE +ID_SIDE/5 ,350,strStep);

}


/////////////////////////////////////////////////////////////////////////////
// CPinTu01View diagnostics

#ifdef _DEBUG
void CPictrue1View::AssertValid() const
{
	CView::AssertValid();
}

void CPictrue1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPictrue1Doc* CPictrue1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPictrue1Doc)));
	return (CPictrue1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPinTu01View message handlers


// 3*3 ����
void CPictrue1View::OnStage1() 
{
	// TODO: Add your command handler code here

	m_nStage=STAGE1;
//MF_BYCOMMAND��־ʱ��ϵͳ����ָ���˵������ʶ�Ĳ˵���ѡȡ��Щ�����Ӳ˵��Ĳ˵���
//MF_BYCOMMAND ָ�����������Ѵ��ڵĲ˵��������ID�š�...��Ӧ��ָ����MF_BYCOMMAND��־����ô Windows��������е�����CMenu�ĵ����˵��
//MF_UNCHECKED����������Եĸ�ѡ��־ MF_DISABLED����ֹ�˲˵�������ǲ������ʾ MF_ENABLED������˲˵�����ָ�������״̬ 
//����ɹ����򷵻ط���ֵ������Ϊ0	
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_EASY,MF_BYCOMMAND | MF_CHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_MIDDLE,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_HARD,MF_BYCOMMAND | MF_UNCHECKED);

	OnStart();
	Invalidate(TRUE);	
}



// 4*4 �м�
void CPictrue1View::OnStage2() 
{
	m_nStage=STAGE2;

	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_EASY,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_MIDDLE,MF_BYCOMMAND | MF_CHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_HARD,MF_BYCOMMAND | MF_UNCHECKED);

	OnStart();
	Invalidate(TRUE);
}



//5*5 �߼�
void CPictrue1View::OnStage3() 
{
	m_nStage=STAGE3;

	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_EASY,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_MIDDLE,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_HARD,MF_BYCOMMAND | MF_CHECKED);

	OnStart();
	Invalidate();
}
void CPictrue1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//����[1][0]���Ͻ� �� x����Ϊ XXX  y����ΪYYY
	int x1=XXX;	
	int y1=YYY-m_nPicWidth;	

	//���½�����
	int x2=XXX+ID_PIC_SIZE;
	int y2=YYY+ID_PIC_SIZE;


	int OKflag=0;	//�����ж��Ƿ����ƴͼ 
	//�ж��Ƿ���ƴͼ������
	if ( (point.x >= x1 && point.x<=x2 ) && ( point.y >= y1 && point.y<=y2 ) )
	{	
		//OKflag=0;
		int xOrg=(point.x-x1)/m_nPicWidth;	//��������ڵ� ��ά����
		int yOrg=(point.y-y1)/m_nPicWidth;
		int xNew,yNew;

		if ((xOrg==1 && yOrg==0)||(xOrg==0 && yOrg==1))
		{
			m_nStart++;			
		}

		if (yOrg < m_nStage)
		{
			
			if ( (yOrg-1)>=0 && m_pShow[yOrg-1][xOrg].picOut==0 )				//�ж��Ƿ��ƶ�������(x,y-1)
			{
				xNew=xOrg;
				yNew=yOrg-1;

				//���[1][0]λ�� ˵����ʼƴͼ��Ϸ
			}
			else if ( (yOrg+1)<m_nStage && m_pShow[yOrg+1][xOrg].picOut==0 )	//�ж��Ƿ��ƶ�������(x,y+1)
			{
				xNew=xOrg;
				yNew=yOrg+1;
			}
			else if ( (xOrg-1)>=0 && m_pShow[yOrg][xOrg-1].picOut==0 )			//�ж��Ƿ��ƶ������(x-1,y)
			{
				xNew=xOrg-1;
				yNew=yOrg;
			}
			else if ( (xOrg+1)<m_nStage && m_pShow[yOrg][xOrg+1].picOut==0 )	//�ж��Ƿ��ƶ����ұ�(x+1,y)
			{
				xNew=xOrg+1;
				yNew=yOrg;
			}
			else return;			//���ز���Ӧ�ĵ���¼�

			//��ʱ����ʼ����
			if (m_nStart==1 && !m_bTimer)
			{
				SetTimer(1,1000,NULL);
				m_bTimer=TRUE; //�����ж�ʱ����
			}

			CString strStep;
			strStep.Format("���߲���: %d ��",++m_nStep);

			CClientDC dc(this);
			dc.SetBkColor(MARK_BK_COLOR);
			dc.TextOut(XXX + ID_PIC_SIZE +ID_SIDE/5 ,350,strStep);


			//��ʼ�ֲ��ػ�
 			CDC *pDC=GetDC();
 			CDC dcCompatible;
 			dcCompatible.CreateCompatibleDC(pDC);
			dcCompatible.SelectObject(&m_bitmap);

			pDC->SetStretchBltMode(COLORONCOLOR); 

			//�Ƚ�������������ͼƬ �ƶ�����λ��(�ƶ����հ׵���)
			pDC->StretchBlt(
				XXX + xNew*m_nPicWidth,
				YYY + (yNew-1)*m_nPicWidth,
				m_nPicWidth,
				m_nPicWidth,
				&dcCompatible,
				((m_pShow[yOrg][xOrg].picOut-1)%m_nStage) * m_nImgOrgX, 
				((m_pShow[yOrg][xOrg].picOut-1)/m_nStage) * m_nImgOrgY,
				m_nImgOrgX ,
				m_nImgOrgY ,
				SRCCOPY
					);

			m_pShow[yNew][xNew].picOut=m_pShow[yOrg][xOrg].picOut;	//���� picOut
			m_pShow[yOrg][xOrg].picOut=0;

			//���ƿհ׵ط�(ע�������Ѿ�������picOut��)

			pDC->Rectangle(XXX + xOrg*m_nPicWidth  ,YYY + (yOrg-1)*m_nPicWidth,
							XXX + (xOrg+1)*m_nPicWidth  ,YYY + yOrg*m_nPicWidth	);

		}
	
		if (m_pShow[0][0].picOut==m_pShow[0][0].picIn)
		{
			if (IsWin(m_nStage))
			{
				
			}
		}		
		else
		{
			return ;
		}
	}

	//�ж��Ƿ�����ߵ�4��ͼƬ�ڵ��
	//��ʼ��CPoint���� �ֱ�洢4��ͼƬ�����Ͻ�����
	CPoint pt[4]={
        CPoint(ID_SIDE,ID_SIDE*2+ID_IMG_SIZE*2),
		CPoint(ID_SIDE*2+ID_IMG_SIZE  ,ID_SIDE*2+ID_IMG_SIZE*2),
		CPoint(ID_SIDE,ID_SIDE*3+ID_IMG_SIZE*3),
		CPoint(ID_SIDE*2+ID_IMG_SIZE  ,ID_SIDE*3+ID_IMG_SIZE*3)
	};
		
	for (int i=0;i<4;i++)
	{
		if (point.x >= pt[i].x && point.x <= pt[i].x + ID_IMG_SIZE 
			&&  point.y >= pt[i].y && point.y <= pt[i].y + ID_IMG_SIZE)
		{
			switch (i)
			{
			case 0:OnPicture1();break;
			case 1:OnPicture2();break;
			case 2:OnPicture3();break;
			case 3:OnPicture4();break;		
			}			
			break;	//�˳�ѭ��
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

int CPictrue1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//�������
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR3)));
	
	return 0;
}




void CPictrue1View::OnTimer(UINT nIDEvent) 
{
	CString strTime,strStep;
	strTime.Format("����ʱ��: %d ��",++m_nSecend);

	CClientDC dc(this);
	dc.SetBkColor(MARK_BK_COLOR);
	dc.TextOut(XXX + ID_PIC_SIZE +ID_SIDE/5 ,300,strTime);
	
	CView::OnTimer(nIDEvent);
}

void CPictrue1View::OnPicture1() 
{
	m_bitmap.DeleteObject();
	m_bitmap.LoadBitmap(IDB_BITMAP2);

	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE1,MF_BYCOMMAND | MF_CHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE2,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE3,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE4,MF_BYCOMMAND | MF_UNCHECKED);		

	OnStart();
	Invalidate();		
}



void CPictrue1View::OnPicture2() 
{
	m_bitmap.DeleteObject();
	m_bitmap.LoadBitmap(IDB_BITMAP3);

	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE1,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE2,MF_BYCOMMAND | MF_CHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE3,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE4,MF_BYCOMMAND | MF_UNCHECKED);		

	OnStart();
	Invalidate();	
}

void CPictrue1View::OnPicture3() 
{
	m_bitmap.DeleteObject();
	m_bitmap.LoadBitmap(IDB_BITMAP4);

	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE1,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE2,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE3,MF_BYCOMMAND | MF_CHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE4,MF_BYCOMMAND | MF_UNCHECKED);		

	OnStart();
	Invalidate();
}



void CPictrue1View::OnPicture4() 
{
	m_bitmap.DeleteObject();
	m_bitmap.LoadBitmap(IDB_BITMAP5);

	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE1,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE2,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE3,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE4,MF_BYCOMMAND | MF_CHECKED);		

	OnStart();
	Invalidate();
}

//ͼƬ�Զ���ĶԻ���
void CPictrue1View::OnPicSelect() 
{
	CFileDialog dlg(TRUE,NULL,NULL,NULL,"λͼ�ļ�(*.bmp)|*.bmp");

	if(dlg.DoModal()==IDOK)
	{

		HBITMAP	hbitmap=(HBITMAP)::LoadImage(NULL,dlg.GetFileName(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

		m_bitmap.DeleteObject();
		m_bitmap.Attach(hbitmap);
	    GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE1,MF_BYCOMMAND | MF_UNCHECKED);
	    GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE2,MF_BYCOMMAND | MF_UNCHECKED);
	    GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE3,MF_BYCOMMAND | MF_UNCHECKED);
	    GetParent()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_PICTURE4,MF_BYCOMMAND | MF_UNCHECKED);	

		OnStart();
		Invalidate();
	}
}

//[��ʼ��ť]
void CPictrue1View::OnBegin() 
{
	OnStart();
	Invalidate();	
}
void CPictrue1View::Prompt()
{
	KillTimer(1);
	m_bTimer=FALSE;

	CString strTmp;

	if (m_nStage==STAGE1)		//������ʾ��
	{
		strTmp.Format("��ս�ɹ�!\n����ʱ��: %d ��\t ���ò���: %d ��",
		m_nSecend,m_nStep);	
	}
	else if (m_nStage==STAGE2)	//�м���ʾ��
	{
		strTmp.Format("��ϲ��!��ս�ɹ�!\n����ʱ��: %d ��\t ���ò���: %d ��",
		m_nSecend,m_nStep);
	}
	else if (m_nStage==STAGE3)	//�߼���ʾ��
	{						
		strTmp.Format("�ɹ���!�����!\n����ʱ��: %d ��\t ���ò���: %d ��",				
		m_nSecend,m_nStep);
	}
				
	MessageBox(strTmp,"  ƴͼ��Ϸ  ");
}
//�ж�ƴͼ�Ƿ����
BOOL CPictrue1View::IsWin(int m_nstage)
{
	int OKflag = 0;
	//ÿ��СͼƬ���ж�һ��
	for (int i=0 ;i<m_nStage ;i++)
	{
				
		for (int j=0 ;j<m_nStage ;j++)
		{
			if (m_pShow[i][j].picOut==m_pShow[i][j].picIn+1)	//In�������Ǵ�0��ʼ��  Out�������Ǵ�1��ʼ��
			{													//������ֲ�= �����˳��ж�
				OKflag++;	
			}
		}

	}

	if (OKflag >= (m_nStage*m_nStage-1)	)//OKflagδ -- ���� ��˵��In��Out��һ�� 
	{
		CDC *pDC=GetDC();
 		CDC dcCompatible;
 	    dcCompatible.CreateCompatibleDC(pDC);
		dcCompatible.SelectObject(&m_bitmap);
		pDC->SetStretchBltMode(COLORONCOLOR);
		m_pShow[0][0].picOut=1;
		pDC->StretchBlt(
			XXX,
			YYY -m_nPicWidth,				//��������һ�����
			m_nPicWidth,
			m_nPicWidth,
			&dcCompatible,							//���ര���� ���εĸߺͿ�
			((m_pShow[0][0].picOut-1)%m_nStage) * m_nImgOrgX, 
			((m_pShow[0][0].picOut-1)/m_nStage) * m_nImgOrgY,	//m_nImgOrgX*i ,m_nImgOrgY*j ,
			m_nImgOrgX ,
			m_nImgOrgY ,
			SRCCOPY
				);
		Prompt();
		ReleaseDC(pDC);
		return true;
	}
	else
	{
		return false;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CPictrue1View printing


	

