// FlightDemo.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CFlightDemoApp:
// 有关此类的实现，请参阅 FlightDemo.cpp
//

class CFlightDemoApp : public CWinApp
{
public:
	CFlightDemoApp();

// 重写
	public:
	virtual BOOL InitInstance();

//GDI+初始化
private:
	GdiplusStartupInput m_gdiplusstartupinput;
	ULONG_PTR  m_gdiplustoken;

// 实现

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CFlightDemoApp theApp;