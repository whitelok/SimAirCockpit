#pragma once


// CDashboard �Ի���

UINT OnShowNum(LPVOID lParam);

class CDashboard : public CDialog
{
	DECLARE_DYNAMIC(CDashboard)

public:
	CDashboard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDashboard();

// �Ի�������
	enum { IDD = IDD_DASHBOARD };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void OnInitDC();

};
