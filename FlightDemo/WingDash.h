#pragma once


// CWingDash �Ի���

UINT OnShowWingNum(LPVOID lParam);

class CWingDash : public CDialog
{
	DECLARE_DYNAMIC(CWingDash)

public:
	CWingDash(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWingDash();

// �Ի�������
	enum { IDD = IDD_WING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void OnWingInitDC(void);
	virtual BOOL OnInitDialog();
};
