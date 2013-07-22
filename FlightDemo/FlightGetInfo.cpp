// FlightGetInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "FlightDemo.h"
#include "FlightGetInfo.h"
#include "math.h"

// CFlightGetInfo
extern HWND m_mainhwnd;
IMPLEMENT_DYNCREATE(CFlightGetInfo, CWinThread)

CFlightGetInfo::CFlightGetInfo()
{
}

CFlightGetInfo::~CFlightGetInfo()
{
}

BOOL CFlightGetInfo::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	m_joyinfo.dwFlags=JOY_RETURNALL;
	return 1;
}

int CFlightGetInfo::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CFlightGetInfo, CWinThread)
	ON_THREAD_MESSAGE(WM_GETJOTSTICK,OnGetJoystick)
END_MESSAGE_MAP()


// CFlightGetInfo 消息处理程序
void CFlightGetInfo::OnGetJoystick(WPARAM wParam,LPARAM lParam)
{
	
	if(JOYERR_NOERROR!=joyGetDevCaps(JOYSTICKID1,&m_joycaps,sizeof(m_joycaps)))    //寻找已经连接的手柄摇杆
	{
		AfxMessageBox(_T("Can not find the Joystick!"));
	}
	else
	{
		m_rand=m_joycaps.wXmax;
		EnableWindow(GetDlgItem(m_mainhwnd,IDC_LINEJOYSTICK),FALSE);
		if(JOYERR_NOERROR!=joyGetPosEx(JOYSTICKID1,&m_joyinfo))                    //初始化获取手柄摇杆的状态数据
		{
			AfxMessageBox(_T("Can not get the Joystick Infomation!"));
            EnableWindow(GetDlgItem(m_mainhwnd,IDC_LINEJOYSTICK),TRUE);
		}
		else                                                      
		{
			DWORD m_mph=0xffff;
			if((UINT)m_joyinfo.dwZpos<(UINT)m_mph)                                            //判断手柄摇杆的油门是否复位
			{
				AfxMessageBox(_T("MPH not reset"));
				EnableWindow(GetDlgItem(m_mainhwnd,IDC_LINEJOYSTICK),TRUE);
			}
			else
			{
				//CWinThread *p=::AfxBeginThread(OnGetJoyInfo,(LPVOID)m_rand);

				while(1)
				{
					//m_criticalsection.Lock();
					if(JOYERR_NOERROR==joyGetPosEx(JOYSTICKID1,&m_joyinfo))                  //获取手柄摇杆数据
					  {
						  if(m_joyinfo.dwButtons&JOY_BUTTON2)                                //加锁
						  {
							  m_flightinfo.m_uwing=1850;
							  m_flightinfo.m_ulift=1500;
							  m_flightinfo.m_umph=1070;
							  m_flightinfo.m_udirection=1500;
							  m_flightinfo.m_uCH5=1150;
							  m_flightinfo.m_uCH6=1150;
							  m_flightinfo.m_uCH7=1150;
							  m_flightinfo.m_uflag=m_flightinfo.OnChange();
							  m_flightinfo.OnSendNum();
						  }
						  else
						  {
						    m_joyx=m_joyinfo.dwXpos;
							m_joyy=m_joyinfo.dwYpos;
							m_joyz=m_joyinfo.dwZpos;
							m_joyr=m_joyinfo.dwRpos;
                            m_joyx=(UINT)(m_joyx*(M_MAX-M_MIN+1)/m_rand)+M_MIN;
							m_joyy=(UINT)M_MAX-(m_joyy*(M_MAX-M_MIN+1)/m_rand);
							m_joyz=(UINT)(M_MAX-m_joyz*(M_MAX-M_MIN)/m_rand);
							m_joyr=(UINT)(m_joyr*(M_MAX-M_MIN+1)/m_rand)+M_MIN;

							//this->OnChangeData(1500,M_MAX-M_MIN,m_joyx,m_joyy,m_joyx,m_joyy);
						  
							m_flightinfo.m_uwing=m_joyx;
                            m_flightinfo.m_ulift=m_joyy;
							m_flightinfo.m_umph=m_joyz;
							m_flightinfo.m_udirection=m_joyr;
					        m_flightinfo.m_uCH5=1500;
						    m_flightinfo.m_uCH6=1500;
							m_flightinfo.m_uCH7=1500;
							m_flightinfo.m_uflag=m_flightinfo.OnChange();
							m_flightinfo.OnSendNum();
						  }

					  }
					else
					{
					  AfxMessageBox(_T("Connect faile,please check the Joystick!"));
                      EnableWindow(GetDlgItem(m_mainhwnd,IDC_LINEJOYSTICK),TRUE);
					  break;
					}
					Sleep(7);
				//	m_criticalsection.Unlock();
				}
			}
		}
	}
}

void CFlightGetInfo::OnChangeData(int a, int b, UINT X1, UINT Y1, UINT &X2, UINT &Y2)    //a:初始值，b:范围，X1：副翼值，Y1：升降值，X2：输出副翼值，Y2：输出升降值
{
		double k7=(double)a;
		double k8=(double)a;   
	    double k1=(double)(abs(int(X1-a)));
		double k2=(double)(abs(int(Y1-a)));
		double k3=sqrt(k1*k1+k2*k2);
		if(k3>100)  k3=b/2;
		double pi=3.1415926;
		double k4=k2/k1;
		double k5=atan(k4)*180.0/pi;
		double k6;
		UINT c=(UINT)a;
		if(Y1<=c&&X1>=c)   k6=k5;
		if(Y1<=c&&X1<c)    k6=90-k5+90;
		if(Y1>c&&X1<=c)    k6=k5+180;
		if(Y1>=c&&X1>c)    k6=90-k5+270;
        if(k6>=0&&k6<90){
		        k7=a-(k3)*sin((double)((k6)*pi/180.0));
		        k8=a+(k3)*cos((double)((k6)*pi/180.0));}
        if(k6>=90&&k6<180){
                        k7=a-(k3)*sin((double)(180-k6)*pi/180.0);
                        k8=a-(k3)*cos((double)(180-k6)*pi/180.0);}
        if(k6>=180&&k6<270){
                        k7=a+(k3)*sin((double)(k6-180)*pi/180.0);
                        k8=a-(k3)*cos((double)(k6-180)*pi/180.0);}                      
        if(k6>=270&&k6<=360){
                      k7=a+(k3)*sin((double)(360-k6)*pi/180.0);
                      k8=a+(k3)*cos((double)(360-k6)*pi/180.0);}
		X2=(UINT)(k8);
		Y2=(UINT)(k7);
}




/*UINT OnGetJoyInfo(LPVOID lParam)
{
            UINT m_rand=(UINT)lParam;
			CFlightGetInfo m_flightgetinfo;
   			while(1)
				{
					  
					if(JOYERR_NOERROR==joyGetPosEx(JOYSTICKID1,&(m_flightgetinfo.m_joyinfo)))                  //获取手柄摇杆数据
					  {
						    m_flightgetinfo.m_joyx=(m_flightgetinfo.m_joyinfo).dwXpos;
							m_flightgetinfo.m_joyy=(m_flightgetinfo.m_joyinfo).dwYpos;
							m_flightgetinfo.m_joyz=(m_flightgetinfo.m_joyinfo).dwZpos;
							m_flightgetinfo.m_joyr=(m_flightgetinfo.m_joyinfo).dwRpos;
                            m_flightgetinfo.m_joyx=(UINT)(m_flightgetinfo.m_joyx*(M_MAX-M_MIN+1)/m_rand)+M_MIN;
							m_flightgetinfo.m_joyy=(UINT)M_MAX-(m_flightgetinfo.m_joyy*(M_MAX-M_MIN+1)/m_rand);
							m_flightgetinfo.m_joyz=(UINT)(M_MAX-m_flightgetinfo.m_joyz*(M_MAX-M_MIN)/m_rand);
							m_flightgetinfo.m_joyr=(UINT)(m_flightgetinfo.m_joyr*(M_MAX-M_MIN+1)/m_rand)+M_MIN;

							m_flightgetinfo.OnChangeData(1500,M_MAX-M_MIN,m_flightgetinfo.m_joyx,m_flightgetinfo.m_joyy,m_flightgetinfo.m_joyx,m_flightgetinfo.m_joyy);
							
							m_flightinfo.m_uwing=m_flightgetinfo.m_joyx;
                            m_flightinfo.m_ulift=m_flightgetinfo.m_joyy;
							m_flightinfo.m_umph=m_flightgetinfo.m_joyz;
							m_flightinfo.m_udirection=m_flightgetinfo.m_joyr;
							m_flightinfo.m_uflag=m_flightinfo.OnChange();
							m_flightinfo.OnSendNum();
							CString m_sr;//(&m_flightinfo.m_cwing[0]);
							  m_sr.Format(_T("%x"),m_flightinfo.m_cflag);
							  SetDlgItemTextW(m_mainhwnd,IDC_WING, m_sr);
							  m_sr.Format(_T("%d"),m_flightinfo.m_ulift);
							  SetDlgItemTextW(m_mainhwnd,IDC_LIFT, m_sr);
							  m_sr.Format(_T("%d"),m_flightinfo.m_umph);
							  SetDlgItemTextW(m_mainhwnd,IDC_MPH, m_sr);
							  m_sr.Format(_T("%d"),m_flightinfo.m_udirection);
							  SetDlgItemTextW(m_mainhwnd,IDC_DIRECTION, m_sr);
						      m_sr.Format(_T("%d"),m_flightinfo.m_uflag);
							  SetDlgItemTextW(m_mainhwnd,IDC_FLAG, m_sr);

					  }
					else
					{
					  AfxMessageBox(_T("Connect faile,please check the Joystick!"));
                      EnableWindow(GetDlgItem(m_mainhwnd,IDC_LINEJOYSTICK),TRUE);
					  break;
					}
				  
				}
	return 1;
}*/