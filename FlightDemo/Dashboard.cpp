// Dashboard.cpp : 实现文件
//

#include "stdafx.h"
#include "FlightDemo.h"
#include "Dashboard.h"
#include "math.h"

// CDashboard 对话框

CDC  *m_dashboarddc;
CRect m_rect;

IMPLEMENT_DYNAMIC(CDashboard, CDialog)

CDashboard::CDashboard(CWnd* pParent /*=NULL*/)
	: CDialog(CDashboard::IDD, pParent)
{

}

CDashboard::~CDashboard()
{
}

void CDashboard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDashboard, CDialog)
END_MESSAGE_MAP()


// CDashboard 消息处理程序

BOOL CDashboard::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDashboard::OnInitDC()
{
	m_dashboarddc=this->GetWindowDC();
	this->GetClientRect(&m_rect);
	CWinThread *pwinmph=AfxBeginThread(OnShowNum,NULL);
}

UINT OnShowNum(LPVOID lParam)
{                                        
  	int x=0;
	int y=0;
	int t=0;
   	double pi=3.1415926535898;
	double r=170;
    int a=0;
    int b=0;
	int m_shownum=0;
 	BITMAP  m_bitmapinfo;                                       //位图信息结构                  
	CBitmap m_bitmap;                                           //位图处理类  
	
	CDC  m_men;
	m_men.CreateCompatibleDC(m_dashboarddc);

	CPen m_pen1(NULL,3,RGB(255,0,0));
	CPen m_pen2(NULL,5,RGB(255,0,0));
	
	CRect m_childrect;
	m_childrect.top=0;
	m_childrect.left=0;
    m_childrect.bottom=600;
    m_childrect.right=700;

	
	while(1){
    m_bitmap.LoadBitmapA(MAKEINTRESOURCEA(IDB_THR));
    m_bitmap.GetBitmap(&m_bitmapinfo);
	m_men.SelectObject(&m_bitmap);
	
	m_shownum=(int)m_flightinfo.m_umph; 
	
	m_men.SelectObject(&m_pen1);
	m_men.SelectStockObject(NULL_BRUSH);
	m_men.Ellipse(m_rect.Width()/2-14-15+5+120,m_rect.Height()/2+6-15-2+110,m_rect.Width()/2-14+15+5+120,m_rect.Height()/2+6+15-2+110);
	m_pen1.DeleteObject();
	
	m_men.SelectObject(&m_pen2);   
	m_men.Ellipse(m_rect.Width()/2-14-5+5+120,m_rect.Height()/2+6-5-2+110,m_rect.Width()/2-14+5+5+120,m_rect.Height()/2+6+5-2+110);
	m_pen2.DeleteObject();
	
	m_men.SelectObject(&m_pen1);
	m_men.MoveTo(m_rect.Width()/2-14+5+120,m_rect.Height()/2+6-2+110);
    x=m_rect.Width()/2-14+5+120;
	y=m_rect.Height()/2+6-2+110;
	t=(int)((m_shownum-1050)*180/900);
    a=x-(int)(r*cos(t*pi/180));
	b=y-(int)(r*sin(t*pi/180));
	m_men.LineTo(a,b);
	m_pen1.DeleteObject();

	m_dashboarddc->SetStretchBltMode(HALFTONE);
    m_dashboarddc->StretchBlt(m_rect.top,m_rect.left,m_rect.Width(),m_rect.Height(),&m_men,0,0,m_bitmapinfo.bmWidth,m_bitmapinfo.bmHeight,SRCCOPY);

	m_bitmap.DeleteObject();


	Sleep(13);
	}
	
	DeleteDC(m_men.m_hDC);
    return 1;
}








