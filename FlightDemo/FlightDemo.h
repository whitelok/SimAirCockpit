// FlightDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFlightDemoApp:
// �йش����ʵ�֣������ FlightDemo.cpp
//

class CFlightDemoApp : public CWinApp
{
public:
	CFlightDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

//GDI+��ʼ��
private:
	GdiplusStartupInput m_gdiplusstartupinput;
	ULONG_PTR  m_gdiplustoken;

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CFlightDemoApp theApp;