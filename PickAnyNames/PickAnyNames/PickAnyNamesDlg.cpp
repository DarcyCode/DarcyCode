
// PickAnyNamesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PickAnyNames.h"
#include "PickAnyNamesDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPickAnyNamesDlg 对话框




CPickAnyNamesDlg::CPickAnyNamesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPickAnyNamesDlg::IDD, pParent)
	, bStart(false)
	, cnt(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPickAnyNamesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPickAnyNamesDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSTART, &CPickAnyNamesDlg::OnBnClickedButtonstart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPickAnyNamesDlg 消息处理程序

BOOL CPickAnyNamesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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
	GetDlgItem(IDC_BUTTONSTART)->SetFont(&font);
	GetDlgItem(IDOK)->SetFont(&font);
	font1.CreateFont(
		90,                        // nHeight
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
		(_T("黑体")));                 // lpszFacename
	GetDlgItem(IDC_EDITNAMESHOW)->SetFont(&font1);
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定
	if(namefile.Open(L"names.txt", CFile::modeRead))
	{
		CString str;
		while(namefile.ReadString(str)&&(!str.IsEmpty()))
			CStr.push_back(str);
	}
	setlocale( LC_CTYPE, old_locale );    
	free( old_locale );//还原区域设定
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPickAnyNamesDlg::OnPaint()
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
HCURSOR CPickAnyNamesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPickAnyNamesDlg::OnBnClickedButtonstart()
{
	// TODO: 在此添加控件通知处理程序代码
	bStart = !bStart;
	if (bStart)
	{
		GetDlgItem(IDC_BUTTONSTART)->SetWindowText(L"暂停");
		SetTimer(0,90,NULL);
	}
	else
	{
		GetDlgItem(IDC_BUTTONSTART)->SetWindowText(L"开始");
		KillTimer(0);
	}
}


void CPickAnyNamesDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (CStr.size()==0)
		return;
	int t = cnt++%CStr.size();
	GetDlgItem(IDC_EDITNAMESHOW)->SetWindowText(CStr[t]);
	CDialogEx::OnTimer(nIDEvent);
}
