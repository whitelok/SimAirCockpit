// FlightDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FlightDemo.h"
#include "FlightDemoDlg.h"

#ifdef _DEBUG
HWND m_mainhwnd;
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFlightDemoDlg �Ի���




CFlightDemoDlg::CFlightDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlightDemoDlg::IDD, pParent)


	, m_IP(_T("192.168.0.105"))
	, m_port(55555)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFlightDemoDlg::~CFlightDemoDlg()
{

}
void CFlightDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP, m_IP);
	DDX_Text(pDX, IDC_PORT, m_port);
}

BEGIN_MESSAGE_MAP(CFlightDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LINEJOYSTICK, &CFlightDemoDlg::OnBnClickedLinejoystick)
	ON_BN_CLICKED(IDC_LINEFLIGHT, &CFlightDemoDlg::OnBnClickedLineflight)
	ON_BN_CLICKED(IDC_SHOWFLIINFO, &CFlightDemoDlg::OnBnClickedShowfliinfo)
	ON_BN_CLICKED(IDC_MODFLIGHT, &CFlightDemoDlg::OnBnClickedModflight)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFlightDemoDlg ��Ϣ�������

BOOL CFlightDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	m_mainhwnd=this->GetSafeHwnd();
	pflightsocket=(CFlightSocket*)AfxBeginThread(RUNTIME_CLASS(CFlightSocket));
	pflightsocket->SetThreadPriority(THREAD_PRIORITY_HIGHEST);
	pflightgetinfo=(CFlightGetInfo*)AfxBeginThread(RUNTIME_CLASS(CFlightGetInfo));
	this->MoveWindow(0,0,830,600,1);
	this->GetWindowRect(&m_mainrect);
	int m_childwidth=(int)(m_mainrect.Width()-60)/5;
	int m_childheight=(int)(m_mainrect.Height()-300)/6;
	
	//�Ի��򲼾�
  
    int m_begintop=m_mainrect.top+10;
	int m_beginleft=10;
    int m_begintwidth=100;
	int m_beginheight=20;

    GetDlgItem(IDC_SROLL)->MoveWindow(m_begintop,m_beginleft,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_WING)->MoveWindow(m_begintop,m_beginleft+m_beginheight,m_begintwidth,m_beginheight,1);
    
	GetDlgItem(IDC_SPITCH)->MoveWindow(m_begintop,m_beginleft+m_beginheight*2,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_LIFT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*3,m_begintwidth,m_beginheight,1);
	
	GetDlgItem(IDC_STHR)->MoveWindow(m_begintop,m_beginleft+m_beginheight*4,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_MPH)->MoveWindow(m_begintop,m_beginleft+m_beginheight*5,m_begintwidth,m_beginheight,1);
	
	GetDlgItem(IDC_SYAM)->MoveWindow(m_begintop,m_beginleft+m_beginheight*6,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_DIRECTION)->MoveWindow(m_begintop,m_beginleft+m_beginheight*7,m_begintwidth,m_beginheight,1);
	
	GetDlgItem(IDC_SFLAG)->MoveWindow(m_begintop,m_beginleft+m_beginheight*8,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_FLAG)->MoveWindow(m_begintop,m_beginleft+m_beginheight*9,m_begintwidth,m_beginheight,1);

	//�Ի�����߲���
	//���ӷ������йذ�ť����
	GetDlgItem(IDC_SIP)->MoveWindow(m_begintop,m_beginleft+m_beginheight*10+10,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_IP)->MoveWindow(m_begintop,m_beginleft+m_beginheight*11+10,m_begintwidth,m_beginheight,1);
    GetDlgItem(IDC_SPORT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*12+10,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_PORT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*13+10,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_LINEFLIGHT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*14+20,m_begintwidth,m_beginheight,1);
    
	//���ӵ�ͼ�йذ�ť����
//	GetDlgItem(IDC_XTEXT)->MoveWindow(m_mainrect.top+10,200,70,30,1);
//    GetDlgItem(IDC_XNUM)->MoveWindow(m_mainrect.top+10,230,100,30,1);
	GetDlgItem(IDC_YTEXT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*15+20,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_YNUM)->MoveWindow(m_begintop,m_beginleft+m_beginheight*16+20,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_SENDEARTH)->MoveWindow(m_begintop,m_beginleft+m_beginheight*17+30,m_begintwidth,m_beginheight,1);

	//���Ӳ����� ��������ť����
	GetDlgItem(IDC_LINEJOYSTICK)->MoveWindow(m_begintop,m_beginleft+m_beginheight*18+40,m_begintwidth,m_beginheight,1);
    GetDlgItem(IDC_MODFLIGHT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*19+50,m_begintwidth,m_beginheight,1);
    GetDlgItem(IDC_SHOWFLIINFO)->MoveWindow(m_begintop,m_beginleft+m_beginheight*20+60,m_begintwidth,m_beginheight,1);
    GetDlgItem(IDC_PLAY)->MoveWindow(m_begintop,m_beginleft+m_beginheight*21+70,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_GOOGLEEARTH)->MoveWindow(m_begintop,m_beginleft+m_beginheight*22+80,m_begintwidth,m_beginheight,1);
	
	
	m_scwidth=GetSystemMetrics(SM_CXSCREEN);
	m_scheight=GetSystemMetrics(SM_CYSCREEN);

	this->OnBnClickedShowfliinfo();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFlightDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFlightDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		 CPaintDC m_bgdc(this); 
         CRect m_bgrect;    
         GetClientRect(m_bgrect);    
         m_bgdc.FillSolidRect(m_bgrect, RGB(125,125,125));
		 CDialog::OnPaint();

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFlightDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFlightDemoDlg::OnBnClickedLinejoystick()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pflightgetinfo->PostThreadMessageA(WM_GETJOTSTICK,NULL,NULL);
}



void CFlightDemoDlg::OnBnClickedLineflight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	pflightsocket->PostThreadMessageA(WM_FLIGHTSOCK,(WPARAM)m_port,(LPARAM)&m_IP);
}

void CFlightDemoDlg::OnBnClickedShowfliinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	    m_dashboard.Create(CDashboard::IDD);           //�����Ǳ���	
		m_dashboard.MoveWindow(m_mainrect.top+120,0,350,300,1);
		m_dashboard.ShowWindow(SW_SHOW);
		m_dashboard.OnInitDC();
     
	    m_wingdash.Create(CWingDash::IDD);           //�����Ǳ���
		m_wingdash.MoveWindow(m_mainrect.top+470,0,350,300,1);	   
		m_wingdash.ShowWindow(SW_SHOW);
		m_wingdash.OnWingInitDC();

        m_listdash.Create(CListDash::IDD);           //�����Ǳ���
		m_listdash.MoveWindow(m_mainrect.top+120,300,350,300,1);	   
		m_listdash.ShowWindow(SW_SHOW);
		m_listdash.OnLiftInitDC();

	    m_diredash.Create(CDirectionDash::IDD);       //�����Ǳ���
		m_diredash.MoveWindow(m_mainrect.top+470,300,350,300,1);	   
		m_diredash.ShowWindow(SW_SHOW);
		m_diredash.OnDireInitDC();

		::EnableWindow((this->GetDlgItem(IDC_SHOWFLIINFO))->GetSafeHwnd(),FALSE);
}

void CFlightDemoDlg::OnBnClickedModflight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_flightwing.Create(CFlightWing::IDD);
	m_flightwing.MoveWindow(0,0,840,300);
	m_flightwing.ShowWindow(SW_SHOW);
	m_flightwing.OnBFlightWing();

	m_flightdire.Create(CFlightDire::IDD);
	m_flightdire.MoveWindow(0,300,840,300);
	m_flightdire.ShowWindow(SW_SHOW);
	m_flightdire.OnBFlightDire();

	::EnableWindow((this->GetDlgItem(IDC_MODFLIGHT))->GetSafeHwnd(),FALSE);
}



HBRUSH CFlightDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_SROLL:
	case IDC_SPITCH:
	case IDC_STHR:
	case IDC_SYAM:
	case IDC_SFLAG:
	case IDC_YTEXT: 
	case IDC_SIP:
	case IDC_SPORT:
		{
			pDC->SetTextColor(RGB(255,0,0)); 
			pDC->SetBkColor(RGB(125,125,125));
			HBRUSH m_brush=::CreateSolidBrush(RGB(125,125,125));
			return m_brush;
		}
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
