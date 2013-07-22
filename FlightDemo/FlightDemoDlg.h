// FlightDemoDlg.h : 头文件
//

#pragma once
#include "FlightDire.h"
#include "FlightWing.h"
#include "DirectionDash.h"
#include "ListDash.h"
#include "WingDash.h"
#include "Dashboard.h"
#include "FlightGetInfo.h"
#include "FlightSocket.h"
#include "afxwin.h"
// CFlightDemoDlg 对话框
class CFlightDemoDlg : public CDialog
{
// 构造
public:
	CFlightDemoDlg(CWnd* pParent = NULL);	// 标准构造函数
    virtual ~CFlightDemoDlg();
// 对话框数据
	enum { IDD = IDD_FLIGHTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CFlightGetInfo *pflightgetinfo;               //连接手柄
    CFlightSocket  *pflightsocket;                //连接飞机
	CDashboard     m_dashboard;                   //油门仪表盘
	CWingDash      m_wingdash;                    //副翼仪表盘
	CListDash      m_listdash;                    //升降仪表盘
	CDirectionDash m_diredash;                    //方向仪表盘

public:
	CFlightWing    m_flightwing;
	CFlightDire    m_flightdire;

public:
	int m_scwidth;
	int m_scheight;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
public:
	afx_msg void OnBnClickedLinejoystick();
	afx_msg void OnBnClickedLineflight();
	CString m_IP;
	UINT m_port;
	afx_msg void OnBnClickedShowfliinfo();
	afx_msg void OnBnClickedModflight();

public:
	CRect   m_mainrect;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
