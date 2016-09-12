
// PickSomeoneDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PickSomeone.h"
#include "PickSomeoneDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPickSomeoneDlg 对话框




CPickSomeoneDlg::CPickSomeoneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPickSomeoneDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPickSomeoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPickSomeoneDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CPickSomeoneDlg::OnBnClickedBtnStart)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPickSomeoneDlg 消息处理程序

BOOL CPickSomeoneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	cnt = 0;
	bStart = false;
	ImgSrc = Mat::zeros(300,300,CV_8U);
	ShowImage(ImgSrc, IDC_STATIC_IMSHOW);
	GetFileFromDir(L"./images");
	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_ACCELERATOR1));
//	font.CreatePointFont(300, _T("Helvetica"),NULL);
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
	GetDlgItem(IDC_BTN_START)->SetFont(&font);
	GetDlgItem(IDOK)->SetFont(&font);
	GetDlgItem(IDC_STATIC_NAME)->SetFont(&font);

	Speed = GetPrivateProfileInt(_T("Speed"), _T("speed"), 5, _T("./config.ini"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPickSomeoneDlg::OnPaint()
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
		if (!ImgSrc.empty())
		{
			ShowImage(ImgSrc, IDC_STATIC_IMSHOW);
		}
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPickSomeoneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPickSomeoneDlg::ShowImage(Mat src, UINT ID)
{
	if (src.empty())
	{
		return;
	}
	CDC* pDC = GetDlgItem( ID ) ->GetDC();		// 获得显示控件的 DC
	HDC hDC = pDC->GetSafeHdc();				// 获取 HDC(设备句柄) 来进行绘图操作
	CRect rect;
	GetDlgItem(ID)->GetClientRect( &rect );	// 获取控件尺寸位置
	CvvImage cimg;
	IplImage cpy = src;
	cimg.CopyOf( &cpy );						// 复制图片
	cimg.DrawToHDC( hDC, &rect );				// 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
}



void CPickSomeoneDlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (bStart)
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(L"开始");
		KillTimer(0);
		bStart = false;
		MessageBeep(MB_OK);
	}
	else
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(L"停止");
		SetTimer(0,500/Speed,NULL);
		bStart = true;
	}
}


void CPickSomeoneDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int i = cnt%ImageNames.size();
	++cnt;
	CString filename;
	filename = L"./images/"+ImageNames[i];
	string ff = CStringA(filename);
	ImgSrc = imread(ff);
	filename = ImageNames[i].Left(ImageNames[i].GetLength()-4);
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(filename);
	ShowImage(ImgSrc, IDC_STATIC_IMSHOW);
//	Beep(6000,100);
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CPickSomeoneDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性
//	if (nCtlColor==CTLCOLOR_STATIC)
	{
//		pWnd->SetFont(&font);
//		GetDlgItem(IDC_STATIC_NAME)->SetFont(&font);
//		pDC->SetBkColor(RGB(255,0,0));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CPickSomeoneDlg::GetFileFromDir(CString csDirPath)
{
	ImageNames.clear();
	csDirPath+="\\*.jpg";
	HANDLE file;
	WIN32_FIND_DATA fileData;
//	char line[1024];
//	char fn[1000];
	//mbstowcs(fn,csDirPath.GetBuffer(),999);
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
	ImageNames.push_back(fileData.cFileName);
	BOOL bState = false;
	bState = FindNextFile(file, &fileData);
	while(bState){
		//wcstombs(line,(const char*)fileData.cFileName,259);
		ImageNames.push_back(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}
}


BOOL CPickSomeoneDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_hAccel) 
	{
		if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg)) 
		{

			OnBnClickedBtnStart();     //隐藏按钮处理的函数；
			return(TRUE);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
