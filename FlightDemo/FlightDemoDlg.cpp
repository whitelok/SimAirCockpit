// FlightDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FlightDemo.h"
#include "FlightDemoDlg.h"

#ifdef _DEBUG
HWND m_mainhwnd;
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CFlightDemoDlg 对话框




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


// CFlightDemoDlg 消息处理程序

BOOL CFlightDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	m_mainhwnd=this->GetSafeHwnd();
	pflightsocket=(CFlightSocket*)AfxBeginThread(RUNTIME_CLASS(CFlightSocket));
	pflightsocket->SetThreadPriority(THREAD_PRIORITY_HIGHEST);
	pflightgetinfo=(CFlightGetInfo*)AfxBeginThread(RUNTIME_CLASS(CFlightGetInfo));
	this->MoveWindow(0,0,830,600,1);
	this->GetWindowRect(&m_mainrect);
	int m_childwidth=(int)(m_mainrect.Width()-60)/5;
	int m_childheight=(int)(m_mainrect.Height()-300)/6;
	
	//对话框布局
  
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

	//对话框左边布局
	//连接飞行器有关按钮布局
	GetDlgItem(IDC_SIP)->MoveWindow(m_begintop,m_beginleft+m_beginheight*10+10,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_IP)->MoveWindow(m_begintop,m_beginleft+m_beginheight*11+10,m_begintwidth,m_beginheight,1);
    GetDlgItem(IDC_SPORT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*12+10,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_PORT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*13+10,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_LINEFLIGHT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*14+20,m_begintwidth,m_beginheight,1);
    
	//连接地图有关按钮布局
//	GetDlgItem(IDC_XTEXT)->MoveWindow(m_mainrect.top+10,200,70,30,1);
//    GetDlgItem(IDC_XNUM)->MoveWindow(m_mainrect.top+10,230,100,30,1);
	GetDlgItem(IDC_YTEXT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*15+20,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_YNUM)->MoveWindow(m_begintop,m_beginleft+m_beginheight*16+20,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_SENDEARTH)->MoveWindow(m_begintop,m_beginleft+m_beginheight*17+30,m_begintwidth,m_beginheight,1);

	//连接操作杆 飞行器按钮布局
	GetDlgItem(IDC_LINEJOYSTICK)->MoveWindow(m_begintop,m_beginleft+m_beginheight*18+40,m_begintwidth,m_beginheight,1);
    GetDlgItem(IDC_MODFLIGHT)->MoveWindow(m_begintop,m_beginleft+m_beginheight*19+50,m_begintwidth,m_beginheight,1);
    GetDlgItem(IDC_SHOWFLIINFO)->MoveWindow(m_begintop,m_beginleft+m_beginheight*20+60,m_begintwidth,m_beginheight,1);
    GetDlgItem(IDC_PLAY)->MoveWindow(m_begintop,m_beginleft+m_beginheight*21+70,m_begintwidth,m_beginheight,1);
	GetDlgItem(IDC_GOOGLEEARTH)->MoveWindow(m_begintop,m_beginleft+m_beginheight*22+80,m_begintwidth,m_beginheight,1);
	
	
	m_scwidth=GetSystemMetrics(SM_CXSCREEN);
	m_scheight=GetSystemMetrics(SM_CYSCREEN);

	this->OnBnClickedShowfliinfo();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFlightDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFlightDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFlightDemoDlg::OnBnClickedLinejoystick()
{
	// TODO: 在此添加控件通知处理程序代码
	pflightgetinfo->PostThreadMessageA(WM_GETJOTSTICK,NULL,NULL);
}



void CFlightDemoDlg::OnBnClickedLineflight()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pflightsocket->PostThreadMessageA(WM_FLIGHTSOCK,(WPARAM)m_port,(LPARAM)&m_IP);
}

void CFlightDemoDlg::OnBnClickedShowfliinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	    m_dashboard.Create(CDashboard::IDD);           //油门仪表盘	
		m_dashboard.MoveWindow(m_mainrect.top+120,0,350,300,1);
		m_dashboard.ShowWindow(SW_SHOW);
		m_dashboard.OnInitDC();
     
	    m_wingdash.Create(CWingDash::IDD);           //副翼仪表盘
		m_wingdash.MoveWindow(m_mainrect.top+470,0,350,300,1);	   
		m_wingdash.ShowWindow(SW_SHOW);
		m_wingdash.OnWingInitDC();

        m_listdash.Create(CListDash::IDD);           //升降仪表盘
		m_listdash.MoveWindow(m_mainrect.top+120,300,350,300,1);	   
		m_listdash.ShowWindow(SW_SHOW);
		m_listdash.OnLiftInitDC();

	    m_diredash.Create(CDirectionDash::IDD);       //方向仪表盘
		m_diredash.MoveWindow(m_mainrect.top+470,300,350,300,1);	   
		m_diredash.ShowWindow(SW_SHOW);
		m_diredash.OnDireInitDC();

		::EnableWindow((this->GetDlgItem(IDC_SHOWFLIINFO))->GetSafeHwnd(),FALSE);
}

void CFlightDemoDlg::OnBnClickedModflight()
{
	// TODO: 在此添加控件通知处理程序代码
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

	// TODO:  在此更改 DC 的任何属性
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
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
