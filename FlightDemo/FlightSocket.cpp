// FlightSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "FlightDemo.h"
#include "FlightSocket.h"


// CFlightSocket
extern HWND m_mainhwnd;
IMPLEMENT_DYNCREATE(CFlightSocket, CWinThread)

CFlightSocket::CFlightSocket()
{
	m_socket=NULL;
}

CFlightSocket::~CFlightSocket()
{
}

BOOL CFlightSocket::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
    WSAStartup(MAKEWORD(2,0),&wsd);
	m_socket=socket(AF_INET,SOCK_STREAM,0);
	if(m_socket==INVALID_SOCKET)
	{
		AfxMessageBox(_T("Build the socket fail！"));
		return TRUE;
	}
	

	return TRUE;
}

int CFlightSocket::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	if(m_socket!=NULL)
	{
		shutdown(m_socket,SD_BOTH);
		closesocket(m_socket);
	}
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CFlightSocket, CWinThread)
	ON_THREAD_MESSAGE(WM_FLIGHTSOCK,OnFlightSocket)
END_MESSAGE_MAP()


// CFlightSocket 消息处理程序
void CFlightSocket::OnFlightSocket(WPARAM wParam,LPARAM lParam)
{
	UINT m_uPort=(UINT)wParam;
	CString *m_sIP;
	m_sIP=(CString*)lParam;	
	//AfxMessageBox(m_sIP->GetBuffer(0));
	m_addr.sin_family=AF_INET;
	m_addr.sin_port=htons(m_uPort);
	m_addr.sin_addr.S_un.S_addr=inet_addr(m_sIP->GetBuffer(0));
	ret=connect(m_socket,(LPSOCKADDR)&m_addr,sizeof(m_addr));
	if(ret==SOCKET_ERROR)
	{
		AfxMessageBox(_T("Connect flight fail！"));
		return;
	}
	else
	{
		//AfxMessageBox(_T("tt"));
	//AfxMessageBox(_T("连接成功！"));
	unsigned long ul=1;
	int ret=ioctlsocket(m_socket,FIONBIO,(unsigned long*)&ul);
	       if(ret==SOCKET_ERROR) 
	           {
		            AfxMessageBox(_T("Build the non_blocking socket fail！"));
		            return ;
	            }
	       else
	            {
					EnableWindow(GetDlgItem(m_mainhwnd,IDC_LINEFLIGHT),FALSE);
	                this->OnSend();
					return;
		   }
    }
}

void CFlightSocket::OnSend(void)
{
	int m_net;
	while(1){
	
	data[0]=m_flightinfo.m_cbegin[0];
    data[1]=m_flightinfo.m_cbegin[1];
	data[2]=m_flightinfo.m_csize;
	data[3]=m_flightinfo.m_ccommand;
	data[4]=m_flightinfo.m_cwing[0];
	data[5]=m_flightinfo.m_cwing[1];
	data[6]=m_flightinfo.m_clift[0];
	data[7]=m_flightinfo.m_clift[1];
	data[8]=m_flightinfo.m_cmph[0];
	data[9]=m_flightinfo.m_cmph[1];
	data[10]=m_flightinfo.m_cdirection[0];
	data[11]=m_flightinfo.m_cdirection[1];
	data[12]=m_flightinfo.m_cCH5[0];
	data[13]=m_flightinfo.m_cCH5[1];
	data[14]=m_flightinfo.m_cCH6[0];
	data[15]=m_flightinfo.m_cCH6[1];
	data[16]=m_flightinfo.m_cCH7[0];
	data[17]=m_flightinfo.m_cCH7[1];
	data[18]=m_flightinfo.m_cflag;
	data[19]=m_flightinfo.m_cend;
	m_net=send(m_socket,(char*)data,sizeof(data),0);
//	if(m_net==SOCKET_ERROR)
//	{
//	   EnableWindow(GetDlgItem(m_mainhwnd,IDC_LINEFLIGHT),TRUE);
//	   break;
//	}
    CString m_sr;//(&m_flightinfo.m_cwing[0]);
	m_sr.Format(_T("%d"),m_flightinfo.m_uwing);
	SetDlgItemTextA(m_mainhwnd,IDC_WING, m_sr);
    m_sr.Format(_T("%d"),m_flightinfo.m_ulift);
	SetDlgItemTextA(m_mainhwnd,IDC_LIFT, m_sr);
	m_sr.Format(_T("%d"),m_flightinfo.m_umph);
	SetDlgItemTextA(m_mainhwnd,IDC_MPH, m_sr);
    m_sr.Format(_T("%d"),m_flightinfo.m_udirection);
	SetDlgItemTextA(m_mainhwnd,IDC_DIRECTION, m_sr);
	m_sr.Format(_T("%d"),m_flightinfo.m_uflag);
	SetDlgItemTextA(m_mainhwnd,IDC_FLAG, m_sr);
	Sleep(5);
	}
}
