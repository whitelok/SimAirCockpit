#pragma once


// CFlightDire 对话框
UINT OnFlightDireMod(LPVOID lParam);
class CFlightDire : public CDialog
{
	DECLARE_DYNAMIC(CFlightDire)

public:
	CFlightDire(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFlightDire();

// 对话框数据
	enum { IDD = IDD_FLIGHTDIRE };

public:
   //  ULONG_PTR m_flightdiretoken;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void OnBFlightDire(void);
};
