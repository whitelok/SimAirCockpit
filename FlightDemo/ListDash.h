#pragma once


// CListDash �Ի���

UINT OnShowLiftNum(LPVOID lParam);

class CListDash : public CDialog
{
	DECLARE_DYNAMIC(CListDash)

public:
	CListDash(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CListDash();

// �Ի�������
	enum { IDD = IDD_LIFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void OnLiftInitDC(void);
};
