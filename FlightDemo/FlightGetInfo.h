#pragma once

#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#define M_MAX   1950
#define M_MIN   1050
#define WM_GETJOTSTICK WM_USER+100
//UINT OnGetJoyInfo(LPVOID lParam);
// CFlightGetInfo
class CFlightGetInfo : public CWinThread
{
	DECLARE_DYNCREATE(CFlightGetInfo)

public:
	CFlightGetInfo();           // 动态创建所使用的受保护的构造函数
	virtual ~CFlightGetInfo();

public:
	   JOYCAPS       m_joycaps;
	   UINT          m_joyx;
	   UINT          m_joyy;
	   UINT          m_joyz;
	   UINT          m_joyr;
	   UINT          m_rand;
       JOYINFOEX     m_joyinfo;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();


protected:
	afx_msg void OnGetJoystick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	void OnChangeData(int a, int b, UINT X1, UINT Y1, UINT &X2,UINT &Y2);
};


