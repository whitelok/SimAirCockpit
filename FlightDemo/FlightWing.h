#pragma once


// CFlightWing �Ի���
UINT OnFlightMod(LPVOID lParam);
class CFlightWing : public CDialog
{
	DECLARE_DYNAMIC(CFlightWing)

public:
	CFlightWing(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFlightWing();

// �Ի�������
	enum { IDD = IDD_FLIGHTWING };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:

   //  ULONG_PTR m_gdiplustoken;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void OnBFlightWing(void);
};
