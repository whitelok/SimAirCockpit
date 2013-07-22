#pragma once


// CDashboard 对话框

UINT OnShowNum(LPVOID lParam);

class CDashboard : public CDialog
{
	DECLARE_DYNAMIC(CDashboard)

public:
	CDashboard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDashboard();

// 对话框数据
	enum { IDD = IDD_DASHBOARD };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void OnInitDC();

};
