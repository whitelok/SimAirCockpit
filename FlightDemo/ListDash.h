#pragma once


// CListDash 对话框

UINT OnShowLiftNum(LPVOID lParam);

class CListDash : public CDialog
{
	DECLARE_DYNAMIC(CListDash)

public:
	CListDash(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CListDash();

// 对话框数据
	enum { IDD = IDD_LIFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void OnLiftInitDC(void);
};
