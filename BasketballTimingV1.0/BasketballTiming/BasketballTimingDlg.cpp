
// BasketballTimingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BasketballTiming.h"
#include "BasketballTimingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBasketballTimingDlg 对话框




CBasketballTimingDlg::CBasketballTimingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBasketballTimingDlg::IDD, pParent)
	, m_iAScore(0)
	, m_iBScore(0)
	, m_i24second(24)
	, m_iHalfTime(900)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBasketballTimingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDTASCORESW, m_iAScore);
	DDV_MinMaxInt(pDX, m_iAScore, 0, 1000);
	DDX_Text(pDX, IDC_EDTBSCORE, m_iBScore);
	DDV_MinMaxInt(pDX, m_iBScore, 0, 1000);
	DDX_Text(pDX, IDC_EDT24SEC, m_i24second);
	DDV_MinMaxInt(pDX, m_i24second, 0, 24);
	DDX_Control(pDX, IDC_EDTASCORESW, m_ctrAScore);
}

BEGIN_MESSAGE_MAP(CBasketballTimingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNASCOREADD, &CBasketballTimingDlg::OnBnClickedBtnascoreadd)
	ON_BN_CLICKED(IDC_BTNASCOREMIN, &CBasketballTimingDlg::OnBnClickedBtnascoremin)
	ON_BN_CLICKED(IDC_BTNARESET, &CBasketballTimingDlg::OnBnClickedBtnareset)
	ON_BN_CLICKED(IDC_BTNBSCOREADD, &CBasketballTimingDlg::OnBnClickedBtnbscoreadd)
	ON_BN_CLICKED(IDC_BTNBSCOREMIN, &CBasketballTimingDlg::OnBnClickedBtnbscoremin)
	ON_BN_CLICKED(IDC_BTNBRESET, &CBasketballTimingDlg::OnBnClickedBtnbreset)
	ON_BN_CLICKED(IDC_BTN24ADD, &CBasketballTimingDlg::OnBnClickedBtn24add)
	ON_BN_CLICKED(IDC_BTN24MIN, &CBasketballTimingDlg::OnBnClickedBtn24min)
	ON_BN_CLICKED(IDC_BTN24RESET, &CBasketballTimingDlg::OnBnClickedBtn24reset)
	ON_BN_CLICKED(IDC_BTNHTMADD, &CBasketballTimingDlg::OnBnClickedBtnhtmadd)
	ON_BN_CLICKED(IDC_BTNHTMMIN, &CBasketballTimingDlg::OnBnClickedBtnhtmmin)
	ON_BN_CLICKED(IDC_BTNHTSADD, &CBasketballTimingDlg::OnBnClickedBtnhtsadd)
	ON_BN_CLICKED(IDC_BTNHTSMIN, &CBasketballTimingDlg::OnBnClickedBtnhtsmin)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNSTART, &CBasketballTimingDlg::OnBnClickedBtnstart)
	ON_BN_CLICKED(IDC_BTNPAUSE, &CBasketballTimingDlg::OnBnClickedBtnpause)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CBasketballTimingDlg 消息处理程序

BOOL CBasketballTimingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect re;
	GetClientRect(&re);
	CString str;
	str.Format(_T("%d, %d"), re.bottom, re.right);
	GetDlgItem(IDC_EDTTEST)->SetWindowText(str);
	str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
	GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);

	font.CreateFont(
		36,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		(_T("楷体")));                 // lpszFacename

	GetDlgItem(IDC_STATICC)->SetFont(&font);
	GetDlgItem(IDC_STATICD)->SetFont(&font);
	GetDlgItem(IDC_STATICA)->SetFont(&font);
	GetDlgItem(IDC_STATICB)->SetFont(&font);

	fontnum.CreateFont(
		200,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		(_T("Arial")));                 // lpszFacename
	GetDlgItem(IDC_EDTASCORESW)->SetFont(&fontnum);
	GetDlgItem(IDC_EDTBSCORE)->SetFont(&fontnum);
	GetDlgItem(IDC_EDT24SEC)->SetFont(&fontnum);
	GetDlgItem(IDC_EDTHALFTIME)->SetFont(&fontnum);

	GetDlgItem(IDC_STATICF)->SetFont(&font);

	fonttitle.CreatePointFont(500,_T("方正小标宋简体"));
	GetDlgItem(IDC_STATICE)->SetFont(&fonttitle);

	ColorA = RGB(10,10,255); // A队的颜色
	ColorB = RGB(255,0,0); // B队的颜色
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBasketballTimingDlg::OnPaint()
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
		CPaintDC dc(this);
		CRect rc;
		GetClientRect(&rc);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);

		BITMAP bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBasketballTimingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBasketballTimingDlg::OnBnClickedBtnascoreadd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iAScore++;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTASCORESW)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnascoremin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iAScore > 0 ? m_iAScore-- : 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTASCORESW)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnareset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iAScore = 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTASCORESW)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnbscoreadd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iBScore++;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTBSCORE)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnbscoremin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iBScore > 0 ? m_iBScore-- : 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTBSCORE)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnbreset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iBScore = 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTBSCORE)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtn24add()
{
	// TODO: 在此添加控件通知处理程序代码
	m_i24second < 24 ? m_i24second++ : 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDT24SEC)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtn24min()
{
	// TODO: 在此添加控件通知处理程序代码
	m_i24second > 0 ? m_i24second-- : 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDT24SEC)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtn24reset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_i24second = 24;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDT24SEC)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnhtmadd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iHalfTime < 840 ? m_iHalfTime += 60 : m_iHalfTime = 900;
	CString str;
	str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
	GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);
	CRect rc;
	GetDlgItem(IDC_EDTHALFTIME)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnhtmmin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iHalfTime > 60 ? m_iHalfTime -= 60 : 0;
	CString str;
	str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
	GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);
	CRect rc;
	GetDlgItem(IDC_EDTHALFTIME)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnhtsadd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iHalfTime  < 900 ? m_iHalfTime++ : 0;
	CString str;
	str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
	GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);
	CRect rc;
	GetDlgItem(IDC_EDTHALFTIME)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnhtsmin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iHalfTime > 0 ? m_iHalfTime-- : 0;
	CString str;
	str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
	GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);
	CRect rc;
	GetDlgItem(IDC_EDTHALFTIME)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


HBRUSH CBasketballTimingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特
	if (pWnd->GetDlgCtrlID() == IDC_STATICA)
	{
		pDC->SetTextColor(ColorA);  //字体颜色
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDTASCORESW)
	{
		pDC->SetTextColor(ColorA);  //字体颜色
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATICB)
	{
		pDC->SetTextColor(ColorB);  //字体颜色
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDTBSCORE)
	{
		pDC->SetTextColor(ColorB);  //字体颜色
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CBasketballTimingDlg::OnBnClickedBtnstart()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if (m_iHalfTime < m_i24second)
	{
		str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
		GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);
		GetDlgItem(IDC_EDT24SEC)->SetWindowText(_T(""));
		CRect rc;
		GetDlgItem(IDC_EDTHALFTIME)->GetWindowRect(&rc);
		InvalidateRect(rc);
		GetDlgItem(IDC_EDT24SEC)->GetWindowRect(&rc);
		InvalidateRect(rc);
	}
	SetTimer(0, 900, NULL);
}


void CBasketballTimingDlg::OnBnClickedBtnpause()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(0);
	SetTimer(1,100,NULL);
}


void CBasketballTimingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 0:
		// 总时间小于24s，24秒归零不显示
		// 24s计时或总时间到，报警
		m_iHalfTime > m_i24second ? (m_i24second > 0 ? m_i24second-- : 0) : 0;
		m_iHalfTime > 0 ? m_iHalfTime-- : 0;
		UpdataTime();
		break;
	case 1:  // 时间到计时
		GameOver();
		KillTimer(1);
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CBasketballTimingDlg::UpdataTime()
{
	CRect rc;
	GetDlgItem(IDC_EDTHALFTIME)->GetWindowRect(&rc);
	InvalidateRect(rc);
	GetDlgItem(IDC_EDT24SEC)->GetWindowRect(&rc);
	InvalidateRect(rc);
	CString str;
	// 1、总时间大于24s，24s未到
	// 2、总时间大于24s，24s到
	if (m_iHalfTime < 1)
	{
		GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(_T("0:00"));
		GetDlgItem(IDC_EDT24SEC)->SetWindowText(_T(""));
		KillTimer(0);
		SetTimer(1,100,NULL);
		return;
	}
	if (m_iHalfTime < m_i24second)
	{
		str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
		GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);
		str.Format(_T("%d"), 0);
		GetDlgItem(IDC_EDT24SEC)->SetWindowText(_T(""));
		return;
	}
	if (m_i24second < 1)
	{
		str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
		GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);
		GetDlgItem(IDC_EDT24SEC)->SetWindowText(_T("0"));
		KillTimer(0);
		SetTimer(1,100,NULL);
		return;
	}
	str.Format(_T("%d:%02d"), m_iHalfTime/60, m_iHalfTime%60);
	GetDlgItem(IDC_EDTHALFTIME)->SetWindowText(str);
	str.Format(_T("%d"), m_i24second);
	GetDlgItem(IDC_EDT24SEC)->SetWindowText(str);
}

void CBasketballTimingDlg::GameOver()
{
	Beep(1500,1500);
}
