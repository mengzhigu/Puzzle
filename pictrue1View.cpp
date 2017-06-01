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
		//随机时间
	srand((unsigned)time(NULL));	

	//默认进入游戏是初级
	m_nStage=STAGE1;				

	//CBitmap 对象关联位图句柄
	m_bitmap.LoadBitmap(IDB_BITMAP2);	//m_bitmap是程序运行过程中的当前位图

	m_bitmap1.LoadBitmap(IDB_BITMAP2);
	m_bitmap2.LoadBitmap(IDB_BITMAP3);
	m_bitmap3.LoadBitmap(IDB_BITMAP4);
	m_bitmap4.LoadBitmap(IDB_BITMAP5);

	//未设置定时器
	m_bTimer=FALSE;

	//[开始按钮] 同时可以把一些初始化的工作放到这个函数里面来执行
	OnStart();			

}


void CPictrue1View::OnStart()
{
	m_bitmap.GetBitmap(&m_bmp);			//m_bmp获得位图信息 放到BITMAP结构体中
	m_nPicWidth= ID_PIC_SIZE/m_nStage;	// 图像宽度 = 图像的大小/分的块数相当于一个正方形做的
	
	RandPic();
	
	//被分割后每一小片图片在窗口显示的大小
	//图片的高和宽可能不一样 要区分开来
	m_nImgOrgX=m_bmp.bmWidth/m_nStage;//bmWidth是系统中图片的宽度
	m_nImgOrgY=m_bmp.bmHeight/m_nStage;

	m_nSecend=0;	//已用时间
	m_nStep=0;		//已走步数
	m_nStart=0;		//是否已经开始拼图游戏 如果已经开始了 则开始计时和计步
	
	if (m_bTimer)		//因为每次都要清空，如果当前有定时器存在  则删除定时器
	{
		KillTimer(1);//是一毫秒为单位的
		m_bTimer=FALSE;	//删除定时器后 现在就没有定时器了
	}		
}

void CPictrue1View::RandPic()
{
	int randNum;					//存储随机数
	int i,j;

	int randArr[STAGE3*STAGE3];		//存储随机数的数组

	int reverSum;					//存储逆序和

	//do while();循环 确保随机后的拼图有解  
	do 
	{
		reverSum=0;
		//for循环:只用存储 m_nStage*m_nStage 个随机数即可
		// 0 2 3
		// 4 5 6
		// 7 8 9
		for (i=1 ;i<m_nStage*m_nStage ;i++)
		{
			randNum=int(rand()%(m_nStage*m_nStage-1))+2;	//获得 2 -- m_nStage*m_nStage的随机数
			//比较重复情况
			for (j=1 ;j<i ;j++)			
			{	
				if (randArr[j] == randNum)	//用上面获得的随机数 和他之前的随机数比较
				{							//如果发现有重复的随机数 则重新随机
					j=0;
					randNum=int(rand()%(m_nStage*m_nStage-1))+2;
				}
			}
			
			randArr[i]=randNum;				//整形数组存储不重复的随机数
			
			//获得逆序和
			for (int n=1 ;n<=i ;n++)		
			{
				if (randArr[i]<randArr[n])
				{
					reverSum++;
				}
			}			
		}	
	}while(reverSum%2!=0);	//如果逆序和为奇数 则重新随即
	
	randArr[0]=0;	//第一个赋值为 0
	//向m_pShow数组中赋值
	int pic=0;									
	for (i=0 ;i<m_nStage ;i++)		//   0   *   *
	{								//   *   *   *
		for (j=0 ;j<m_nStage;j++)	//   *   *   *
		{	
				
				m_pShow[i][j].picIn=i*m_nStage+j;	//picIn 是真实的
				m_pShow[i][j].picOut=randArr[pic];	//picOut 是显示的 取出数组中的不重复的随机数
				pic++;
		}
	}
	
	m_pShow[0][0].picIn=0;		//第一行第一个为0 
	m_pShow[0][0].picOut=0;		//0 表示 为空 可以移到到那个位置

	//随机生成完毕
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
	GetWindowRect(&rect);		//获得窗口矩形区域
	ScreenToClient(&rect);		//屏幕坐标 转换为 客户区坐标
	
	CBrush bkBrush(BKCOLOR);	//构造黑色背景画刷
	pDC->FillRect(CRect(rect.left+5,rect.top+5,rect.right,rect.bottom),&bkBrush);
	//填充窗口矩形区域 +5 显得立体感强

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
			
			 if (m_pShow[i][j].picOut == 0)//绘制第一行第一张图
			{
				pDC->Rectangle(XXX + j*m_nPicWidth  ,YYY + (i-1)*m_nPicWidth,
							XXX + (j+1)*m_nPicWidth  ,YYY + i*m_nPicWidth	);

			}
			else
			{
				pDC->StretchBlt(
					XXX + j*m_nPicWidth  ,
					YYY + (i-1)*m_nPicWidth,				//在视类这一点输出
					m_nPicWidth,
					m_nPicWidth,
					&dcCompatible,							//视类窗口中 矩形的高和宽
					((m_pShow[i][j].picOut-1)%m_nStage) * m_nImgOrgX, 
					((m_pShow[i][j].picOut-1)/m_nStage) * m_nImgOrgY,	//m_nImgOrgX*i ,m_nImgOrgY*j ,
					m_nImgOrgX ,
					m_nImgOrgY ,
					SRCCOPY
					);
			}
		}
	}
	//绘制左边的图形
	
   //左上角的参照图  参照图就是当前的图片
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
		// - - 横线
		pDC->MoveTo(ID_SIDE*3/2,ID_SIDE+ID_IMG_SIZE*2/m_nStage*i);
		pDC->LineTo(ID_SIDE*3/2+ID_IMG_SIZE*2,ID_SIDE+ID_IMG_SIZE*2/m_nStage*i);

		// | | 竖线
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
	strTime.Format("已用时间: %d 秒",m_nSecend);
	strStep.Format("已走步数: %d 步",m_nStep);
	
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


// 3*3 初级
void CPictrue1View::OnStage1() 
{
	// TODO: Add your command handler code here

	m_nStage=STAGE1;
//MF_BYCOMMAND标志时，系统在由指定菜单句柄标识的菜单里选取那些打开了子菜单的菜单项
//MF_BYCOMMAND 指定参数给出已存在的菜单项的命令ID号。...当应用指定了MF_BYCOMMAND标志，那么 Windows将检测所有的属于CMenu的弹出菜单项。
//MF_UNCHECKED：清除命令旁的复选标志 MF_DISABLED：禁止此菜单命令，但是不变灰显示 MF_ENABLED：允许此菜单命令，恢复到正常状态 
//如果成功，则返回非零值，否则为0	
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_EASY,MF_BYCOMMAND | MF_CHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_MIDDLE,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_HARD,MF_BYCOMMAND | MF_UNCHECKED);

	OnStart();
	Invalidate(TRUE);	
}



// 4*4 中级
void CPictrue1View::OnStage2() 
{
	m_nStage=STAGE2;

	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_EASY,MF_BYCOMMAND | MF_UNCHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_MIDDLE,MF_BYCOMMAND | MF_CHECKED);
	GetParent()->GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_GAME_HARD,MF_BYCOMMAND | MF_UNCHECKED);

	OnStart();
	Invalidate(TRUE);
}



//5*5 高级
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
	//数组[1][0]左上角 的 x坐标为 XXX  y坐标为YYY
	int x1=XXX;	
	int y1=YYY-m_nPicWidth;	

	//右下角坐标
	int x2=XXX+ID_PIC_SIZE;
	int y2=YYY+ID_PIC_SIZE;


	int OKflag=0;	//用来判断是否完成拼图 
	//判断是否在拼图区域内
	if ( (point.x >= x1 && point.x<=x2 ) && ( point.y >= y1 && point.y<=y2 ) )
	{	
		//OKflag=0;
		int xOrg=(point.x-x1)/m_nPicWidth;	//鼠标点击所在的 二维坐标
		int yOrg=(point.y-y1)/m_nPicWidth;
		int xNew,yNew;

		if ((xOrg==1 && yOrg==0)||(xOrg==0 && yOrg==1))
		{
			m_nStart++;			
		}

		if (yOrg < m_nStage)
		{
			
			if ( (yOrg-1)>=0 && m_pShow[yOrg-1][xOrg].picOut==0 )				//判断是否移动到上面(x,y-1)
			{
				xNew=xOrg;
				yNew=yOrg-1;

				//点击[1][0]位置 说明开始拼图游戏
			}
			else if ( (yOrg+1)<m_nStage && m_pShow[yOrg+1][xOrg].picOut==0 )	//判断是否移动到下面(x,y+1)
			{
				xNew=xOrg;
				yNew=yOrg+1;
			}
			else if ( (xOrg-1)>=0 && m_pShow[yOrg][xOrg-1].picOut==0 )			//判断是否移动到左边(x-1,y)
			{
				xNew=xOrg-1;
				yNew=yOrg;
			}
			else if ( (xOrg+1)<m_nStage && m_pShow[yOrg][xOrg+1].picOut==0 )	//判断是否移动到右边(x+1,y)
			{
				xNew=xOrg+1;
				yNew=yOrg;
			}
			else return;			//返回不响应的点击事件

			//定时器开始运行
			if (m_nStart==1 && !m_bTimer)
			{
				SetTimer(1,1000,NULL);
				m_bTimer=TRUE; //现在有定时器了
			}

			CString strStep;
			strStep.Format("已走步数: %d 步",++m_nStep);

			CClientDC dc(this);
			dc.SetBkColor(MARK_BK_COLOR);
			dc.TextOut(XXX + ID_PIC_SIZE +ID_SIDE/5 ,350,strStep);


			//开始局部重绘
 			CDC *pDC=GetDC();
 			CDC dcCompatible;
 			dcCompatible.CreateCompatibleDC(pDC);
			dcCompatible.SelectObject(&m_bitmap);

			pDC->SetStretchBltMode(COLORONCOLOR); 

			//先将点击所在坐标的图片 移动到新位置(移动到空白地区)
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

			m_pShow[yNew][xNew].picOut=m_pShow[yOrg][xOrg].picOut;	//交换 picOut
			m_pShow[yOrg][xOrg].picOut=0;

			//绘制空白地方(注意现在已经交换过picOut了)

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

	//判断是否在左边的4张图片内点击
	//初始化CPoint数组 分别存储4张图片的左上角坐标
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
			break;	//退出循环
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

int CPictrue1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//设置鼠标
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR3)));
	
	return 0;
}




void CPictrue1View::OnTimer(UINT nIDEvent) 
{
	CString strTime,strStep;
	strTime.Format("已用时间: %d 秒",++m_nSecend);

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

//图片自定义的对话框
void CPictrue1View::OnPicSelect() 
{
	CFileDialog dlg(TRUE,NULL,NULL,NULL,"位图文件(*.bmp)|*.bmp");

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

//[开始按钮]
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

	if (m_nStage==STAGE1)		//初级提示语
	{
		strTmp.Format("挑战成功!\n所用时间: %d 秒\t 所用步数: %d 步",
		m_nSecend,m_nStep);	
	}
	else if (m_nStage==STAGE2)	//中级提示语
	{
		strTmp.Format("恭喜你!挑战成功!\n所用时间: %d 秒\t 所用步数: %d 步",
		m_nSecend,m_nStep);
	}
	else if (m_nStage==STAGE3)	//高级提示语
	{						
		strTmp.Format("成功啦!你真棒!\n所用时间: %d 秒\t 所用步数: %d 步",				
		m_nSecend,m_nStep);
	}
				
	MessageBox(strTmp,"  拼图游戏  ");
}
//判断拼图是否完成
BOOL CPictrue1View::IsWin(int m_nstage)
{
	int OKflag = 0;
	//每个小图片都判断一次
	for (int i=0 ;i<m_nStage ;i++)
	{
				
		for (int j=0 ;j<m_nStage ;j++)
		{
			if (m_pShow[i][j].picOut==m_pShow[i][j].picIn+1)	//In的坐标是从0开始的  Out的坐标是从1开始的
			{													//如果发现不= 立刻退出判断
				OKflag++;	
			}
		}

	}

	if (OKflag >= (m_nStage*m_nStage-1)	)//OKflag未 -- 操作 则说明In和Out都一样 
	{
		CDC *pDC=GetDC();
 		CDC dcCompatible;
 	    dcCompatible.CreateCompatibleDC(pDC);
		dcCompatible.SelectObject(&m_bitmap);
		pDC->SetStretchBltMode(COLORONCOLOR);
		m_pShow[0][0].picOut=1;
		pDC->StretchBlt(
			XXX,
			YYY -m_nPicWidth,				//在视类这一点输出
			m_nPicWidth,
			m_nPicWidth,
			&dcCompatible,							//视类窗口中 矩形的高和宽
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


	

