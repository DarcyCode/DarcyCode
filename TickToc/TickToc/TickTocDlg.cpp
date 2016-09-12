
// TickTocDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TickToc.h"
#include "TickTocDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTickTocDlg 对话框




CTickTocDlg::CTickTocDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTickTocDlg::IDD, pParent)
	, Time(10)
	, m_iTime(10)
	, bstart(false)
	, bset(false)
	, m_iTimeShow(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTickTocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SETTIME, m_iTime);
	DDV_MinMaxInt(pDX, m_iTime, 0, 99999);
	DDX_Text(pDX, IDC_STATIC_TIME, m_iTimeShow);
	DDV_MinMaxInt(pDX, m_iTimeShow, 0, 99999);
}

BEGIN_MESSAGE_MAP(CTickTocDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_START, &CTickTocDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_SETTIME, &CTickTocDlg::OnBnClickedBtnSettime)
	ON_BN_CLICKED(IDC_BTN_RESET, &CTickTocDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CTickTocDlg 消息处理程序

BOOL CTickTocDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	fontnum.CreateFont(
		270,                        // nHeight
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
	fontbtn.CreateFont(
		24,                        // nHeight
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
		(_T("楷体")));             // lpszFacename
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&fontnum);
	GetDlgItem(IDC_EDIT_SETTIME)->SetFont(&fontbtn);
	GetDlgItem(IDC_BTN_START)->SetFont(&fontbtn);
	GetDlgItem(IDC_BTN_SETTIME)->SetFont(&fontbtn);
	GetDlgItem(IDOK)->SetFont(&fontbtn);
	GetDlgItem(IDC_STATIC1)->SetFont(&fontbtn);
	GetDlgItem(IDC_BTN_RESET)->SetFont(&fontbtn);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTickTocDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTickTocDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTickTocDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_iTimeShow > 1)
	{
		--m_iTimeShow;
		UpdateData(FALSE);
		m_iTimeShow > 10?0:Beep(2000,200);
	}
	else
	{
		m_iTimeShow = 0;
		UpdateData(FALSE);
		KillTimer(0);
		Beep(600, 1000);
		OnBnClickedBtnStart();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CTickTocDlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	bstart = !bstart;
	if (bstart)
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(L"停止计时");
		SetTimer(0,1000,NULL);
		GetDlgItem(IDC_BTN_SETTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(L"开始计时");
		KillTimer(0);
		GetDlgItem(IDC_BTN_SETTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(TRUE);
	}
}


void CTickTocDlg::OnBnClickedBtnSettime()
{
	// TODO: 在此添加控件通知处理程序代码
	bset = !bset;
	if (bset)
	{
		GetDlgItem(IDC_EDIT_SETTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SETTIME)->SetWindowText(L"更新时间");
		GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_SETTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SETTIME)->SetWindowText(L"设置时间");
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(TRUE);
		UpdateData(TRUE);
		m_iTimeShow = m_iTime;
		UpdateData(FALSE);
	}
}


void CTickTocDlg::OnBnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iTimeShow = m_iTime;
	UpdateData(FALSE);
}
