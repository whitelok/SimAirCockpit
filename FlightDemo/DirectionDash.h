#pragma once


// CDirectionDash �Ի���

UINT OnShowdireNum(LPVOID lParam);

class CDirectionDash : public CDialog
{
	DECLARE_DYNAMIC(CDirectionDash)

public:
	CDirectionDash(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDirectionDash();

// �Ի�������
	enum { IDD = IDD_DIRECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void OnDireInitDC(void);
};
