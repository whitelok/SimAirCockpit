#pragma once


// CFlightDire �Ի���
UINT OnFlightDireMod(LPVOID lParam);
class CFlightDire : public CDialog
{
	DECLARE_DYNAMIC(CFlightDire)

public:
	CFlightDire(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFlightDire();

// �Ի�������
	enum { IDD = IDD_FLIGHTDIRE };

public:
   //  ULONG_PTR m_flightdiretoken;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void OnBFlightDire(void);
};
