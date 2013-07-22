// FlightWing.cpp : 实现文件
//

#include "stdafx.h"
#include "FlightDemo.h"
#include "FlightWing.h"
#include "math.h"


// CFlightWing 对话框
extern HWND m_mainhwnd;
 CDC  *m_flightwingdc;
 CRect m_flightwrect;
IMPLEMENT_DYNAMIC(CFlightWing, CDialog)

CFlightWing::CFlightWing(CWnd* pParent /*=NULL*/)
	: CDialog(CFlightWing::IDD, pParent)
{

}

CFlightWing::~CFlightWing()
{

}

void CFlightWing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFlightWing, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFlightWing 消息处理程序

BOOL CFlightWing::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFlightWing::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码

	// 不为绘图消息调用 CDialog::OnPaint()
}

void CFlightWing::OnBFlightWing(void)
{
	m_flightwingdc=this->GetWindowDC();
    this->GetClientRect(&m_flightwrect);
	CWinThread *pwin=AfxBeginThread(OnFlightMod,NULL);
	pwin->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);

}


UINT OnFlightMod(LPVOID lParam)
{
	static int m_mark=0;
	int m_h;
	int h;
	int w;
	int xIni=280;                    //飞行器起始位置x
	int yIni=92;                     //飞行器起始位置y
	int xwid=250;                    //飞行器宽度w
	int yhei=170;                    //飞行器高度
    double g;
	
	Graphics m_graphics(m_flightwingdc->m_hDC);
    Image  m_earthimage(L"D:\\Documents\\Visual Studio 2008\\Projects\\FlightDemo\\FlightDemo\\FlightDemo\\res\\earth.bmp");
	Image  m_flightimage(L"D:\\Documents\\Visual Studio 2008\\Projects\\FlightDemo\\FlightDemo\\FlightDemo\\res\\bflight.gif");

	double t;
	double pi=3.1415926535898;
	double k1;
	double j1;
	double l1;
	double Y1;
	double X1;
	double xmove1;
	double ymove1;

    double k2;
	double j2;
	double l2;
	double Y2;
	double X2;
	double xmove2;
	double ymove2;
	
	Pen pen1(Color::OrangeRed,3);
    Bitmap *pbmp=new Bitmap(m_flightwrect.Width(),m_flightwrect.Height());
	Graphics  *gh=gh->FromImage(pbmp);
	
	//错误检测
    CMemoryState m_begin,m_end,m_check;                      //内存泄露检测类对象
 	

	while(1){
   
	
		

	//内存泄露检测
	m_begin.Checkpoint();
	
	gh->DrawImage(&m_earthimage,m_flightwrect.top,m_flightwrect.left,m_flightwrect.Width()+12,m_flightwrect.Height()+50);	
	gh->DrawLine(&pen1,m_flightwrect.Width()/2-9,m_flightwrect.Height()/2+60,m_flightwrect.Width()/2-9-(m_flightwrect.Height()/2+107),m_flightwrect.Height());
    gh->DrawLine(&pen1,m_flightwrect.Width()/2-9,m_flightwrect.Height()/2+60,m_flightwrect.Width()/2-9+(m_flightwrect.Height()/2+107),m_flightwrect.Height());
	
	//位移线
	if(m_mark==0)
	{
    m_h=10;
	for(h=10;h<m_flightwrect.Height()/2-60;h=h+10)
	{
	    //int h=20;
		
	    w=m_h+15;
        gh->DrawLine(&pen1,m_flightwrect.Width()/2-9-w,m_flightwrect.Height()/2+60+m_h,m_flightwrect.Width()/2-9+w,m_flightwrect.Height()/2+60+m_h);
		m_h=m_h+10;
	}
	   m_mark=1;
	}
	else
	{
     m_h=18;
	   	for(h=18;h<m_flightwrect.Height()/2-60;h=h+18)
	{
	    //int h=20;
	    w=m_h+15;
        gh->DrawLine(&pen1,m_flightwrect.Width()/2-9-w,m_flightwrect.Height()/2+60+m_h,m_flightwrect.Width()/2-9+w,m_flightwrect.Height()/2+60+m_h);
	    m_h=m_h+18;
	}
	   m_mark=0;
	}
    gh->ResetTransform();

	//飞行器围绕飞行器中心旋转.
    t=-30+(m_flightinfo.m_uwing-1050.0)*60/900;
	gh->RotateTransform((REAL)t);
    k1=xIni/yIni;
	j1=atan(k1);
	l1=sqrt(double(xIni*xIni+yIni*yIni));
	Y1=l1*cos(j1+t*pi/180);
	X1=l1*sin(j1+t*pi/180);
	xmove1=X1-xIni;
	ymove1=Y1-yIni;
	gh->TranslateTransform((REAL)xmove1,(REAL)ymove1);
    k2=(xIni+xwid)/(yhei+yIni);
	j2=atan(k2);
	l2=sqrt(double((xwid/2)*(xwid/2)+(yhei/2)*(yhei/2)));
	Y2=l2*cos(j2+t*pi/180);
	X2=l2*sin(j2+t*pi/180);
	xmove2=X2-xwid/2;
	ymove2=Y2-yhei/2;
    gh->TranslateTransform((REAL)xmove2,(REAL)ymove2);
	
	//m_graphics.ResetTransform();
	//飞行器上下平移
    g=(m_flightinfo.m_ulift-1500.0)*250/900;                           //升降像素
	
	gh->TranslateTransform((REAL)0,(REAL)g);                    //升降操作

	
	//主画图
	gh->DrawImage(&m_flightimage,(REAL)xIni,(REAL)yIni,(REAL)xwid,(REAL)yhei);
	gh->ResetTransform();
    
	m_graphics.DrawImage(pbmp,m_flightwrect.top,m_flightwrect.left,m_flightwrect.Width(),m_flightwrect.Height());

	
	//内存泄露检测
	m_end.Checkpoint();
	if(m_check.Difference(m_begin,m_end))
	{
//		AfxMessageBox(_T("FlightWing memory leak!"));
	}
	
	Sleep(100);
	}
    
    delete pbmp;
	return 1;
}


