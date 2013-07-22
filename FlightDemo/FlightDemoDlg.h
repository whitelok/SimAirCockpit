// FlightDemoDlg.h : ͷ�ļ�
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
// CFlightDemoDlg �Ի���
class CFlightDemoDlg : public CDialog
{
// ����
public:
	CFlightDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
    virtual ~CFlightDemoDlg();
// �Ի�������
	enum { IDD = IDD_FLIGHTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CFlightGetInfo *pflightgetinfo;               //�����ֱ�
    CFlightSocket  *pflightsocket;                //���ӷɻ�
	CDashboard     m_dashboard;                   //�����Ǳ���
	CWingDash      m_wingdash;                    //�����Ǳ���
	CListDash      m_listdash;                    //�����Ǳ���
	CDirectionDash m_diredash;                    //�����Ǳ���

public:
	CFlightWing    m_flightwing;
	CFlightDire    m_flightdire;

public:
	int m_scwidth;
	int m_scheight;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
