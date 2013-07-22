#pragma once


// CWingDash 对话框

UINT OnShowWingNum(LPVOID lParam);

class CWingDash : public CDialog
{
	DECLARE_DYNAMIC(CWingDash)

public:
	CWingDash(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWingDash();

// 对话框数据
	enum { IDD = IDD_WING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void OnWingInitDC(void);
	virtual BOOL OnInitDialog();
};
