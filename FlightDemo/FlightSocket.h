#pragma once
#include "winsock.h"
#pragma comment(lib,"ws2_32.lib")
#define WM_FLIGHTSOCK WM_USER+101

// CFlightSocket

class CFlightSocket : public CWinThread
{
	DECLARE_DYNCREATE(CFlightSocket)

public:
	CFlightSocket();           // 动态创建所使用的受保护的构造函数
	virtual ~CFlightSocket();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	WSADATA wsd;
    SOCKET m_socket;
	struct sockaddr_in m_addr;
	int ret;
	unsigned char data[20];
protected:
afx_msg void OnFlightSocket(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	void OnSend(void);
};


