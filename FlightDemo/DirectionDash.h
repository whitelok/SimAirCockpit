#pragma once


// CDirectionDash 对话框

UINT OnShowdireNum(LPVOID lParam);

class CDirectionDash : public CDialog
{
	DECLARE_DYNAMIC(CDirectionDash)

public:
	CDirectionDash(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDirectionDash();

// 对话框数据
	enum { IDD = IDD_DIRECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void OnDireInitDC(void);
};
