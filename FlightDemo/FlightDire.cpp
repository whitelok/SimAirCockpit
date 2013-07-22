// FlightDire.cpp : 实现文件
//

#include "stdafx.h"
#include "FlightDemo.h"
#include "FlightDire.h"
#include "math.h"

// CFlightDire 对话框
HWND m_fdflightdire;
CDC  *m_flightdiredc;
CRect m_flightdirerect;
IMPLEMENT_DYNAMIC(CFlightDire, CDialog)

CFlightDire::CFlightDire(CWnd* pParent /*=NULL*/)
	: CDialog(CFlightDire::IDD, pParent)
{


}

CFlightDire::~CFlightDire()
{

}

void CFlightDire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFlightDire, CDialog)
END_MESSAGE_MAP()


// CFlightDire 消息处理程序

void CFlightDire::OnBFlightDire(void)
{
	m_flightdiredc=this->GetWindowDC();
	this->GetClientRect(&m_flightdirerect);
	m_fdflightdire=this->GetSafeHwnd();
	CWinThread *pwin=AfxBeginThread(OnFlightDireMod,NULL);
	pwin->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
}

UINT OnFlightDireMod(LPVOID lParam)
{
	
	static int m_mark=0;
	int m_h;
	int w;
	int h;
	int xIni=290;                //飞行器起始位置x
	int yIni=45;                 //飞行器起始位置y
	int xwid=250;                //飞行器宽度w
	int yhei=250;                //飞行器高度h
    
	Graphics m_fdgraphics(m_flightdiredc->m_hDC);
    Image  m_fdearthimage(L"D:\\Documents\\Visual Studio 2008\\Projects\\FlightDemo\\FlightDemo\\FlightDemo\\res\\fdearth.bmp");
	Point point1[]={Point(0,0),Point((int)m_flightdirerect.Width(),0),Point(0,(int)m_flightdirerect.Height())};
	Image  m_fdflightimage(L"D:\\Documents\\Visual Studio 2008\\Projects\\FlightDemo\\FlightDemo\\FlightDemo\\res\\fflight.gif");
	Point point2[]={Point(xIni,yIni),Point(xIni+xwid,yIni),Point(xIni,yhei+yIni)};
   
	static double t;
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
    Bitmap *pbmp=new Bitmap(m_flightdirerect.Width(),m_flightdirerect.Height());
	Graphics  *gh=gh->FromImage(pbmp);
	//错误检测
    CMemoryState m_begin,m_end,m_check;                      //内存泄露检测类对象
   
	while(1){
//	InvalidateRect(m_fdflightdire,&m_flightdirerect,FALSE);
	//m_fdgraphics.Clear(Color::White);
	
	//内存泄露检测
	m_begin.Checkpoint();
	gh->DrawImage(&m_fdearthimage,m_flightdirerect.top,m_flightdirerect.left,m_flightdirerect.Width(),m_flightdirerect.Height()+50);
	gh->DrawLine(&pen1,(int)m_flightdirerect.Width()/2,0,(int)m_flightdirerect.Width()/2-200,m_flightdirerect.Height());
    gh->DrawLine(&pen1,(int)m_flightdirerect.Width()/2,0,(int)m_flightdirerect.Width()/2+200,m_flightdirerect.Height());
	
	

	
	//位移线
	if(m_mark==0)
	{
    m_h=33;
	w=6;
	for(h=33;h<m_flightdirerect.Height();h=h+33)
	{
	    //int h=20;
        gh->DrawLine(&pen1,(int)m_flightdirerect.Width()/2-w,m_h,(int)m_flightdirerect.Width()/2+w,m_h);
		w=w+12;
		m_h=m_h+33;
	}
	   m_mark=1;
	}
	else
	{
     m_h=42;
	 w=6;
	   	for(h=42;h<m_flightdirerect.Height();h=h+42)
	{
	    //int h=20;
		//w=m_h-25;
        gh->DrawLine(&pen1,(int)m_flightdirerect.Width()/2-w,m_h,(int)m_flightdirerect.Width()/2+w,m_h);
	    w=w+14;
		m_h=m_h+42;
	}
	   m_mark=0;
	}


 //   m_fdgraphics.ResetTransform();
	
	//记录飞行器旋转角度
	if(m_flightinfo.m_udirection>1500)
		t=t+10;
	if(m_flightinfo.m_udirection<1500)
		t=t-10;
//	if(m_flightinfo.m_udirection==1500)
//		t=0;
	
	//飞行器围绕中心旋转
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
	if(t!=0)
    gh->TranslateTransform((REAL)xmove2,(REAL)ymove2);
	//m_graphics.ResetTransform();
	gh->DrawImage(&m_fdflightimage,point2,3);
	gh->ResetTransform();
	
	 m_fdgraphics.DrawImage(pbmp,m_flightdirerect.top,m_flightdirerect.left,m_flightdirerect.Width(),m_flightdirerect.Height());
	//内存泄露检测
	m_end.Checkpoint();
	if(m_check.Difference(m_begin,m_end))
	{
//		AfxMessageBox(_T("FlightDire memory leak!"));
	}

	Sleep(100);
	}
  return 1;
}