#pragma once


// CFlightWing 对话框
UINT OnFlightMod(LPVOID lParam);
class CFlightWing : public CDialog
{
	DECLARE_DYNAMIC(CFlightWing)

public:
	CFlightWing(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFlightWing();

// 对话框数据
	enum { IDD = IDD_FLIGHTWING };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

   //  ULONG_PTR m_gdiplustoken;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void OnBFlightWing(void);
};
