
// PickSomeoneDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PickSomeone.h"
#include "PickSomeoneDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPickSomeoneDlg �Ի���




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


// CPickSomeoneDlg ��Ϣ�������

BOOL CPickSomeoneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
		(_T("����")));                 // lpszFacename
	GetDlgItem(IDC_BTN_START)->SetFont(&font);
	GetDlgItem(IDOK)->SetFont(&font);
	GetDlgItem(IDC_STATIC_NAME)->SetFont(&font);

	Speed = GetPrivateProfileInt(_T("Speed"), _T("speed"), 5, _T("./config.ini"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPickSomeoneDlg::OnPaint()
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
		if (!ImgSrc.empty())
		{
			ShowImage(ImgSrc, IDC_STATIC_IMSHOW);
		}
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	CDC* pDC = GetDlgItem( ID ) ->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	GetDlgItem(ID)->GetClientRect( &rect );	// ��ȡ�ؼ��ߴ�λ��
	CvvImage cimg;
	IplImage cpy = src;
	cimg.CopyOf( &cpy );						// ����ͼƬ
	cimg.DrawToHDC( hDC, &rect );				// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC( pDC );
}



void CPickSomeoneDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (bStart)
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(L"��ʼ");
		KillTimer(0);
		bStart = false;
		MessageBeep(MB_OK);
	}
	else
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(L"ֹͣ");
		SetTimer(0,500/Speed,NULL);
		bStart = true;
	}
}


void CPickSomeoneDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ˸��� DC ���κ�����
//	if (nCtlColor==CTLCOLOR_STATIC)
	{
//		pWnd->SetFont(&font);
//		GetDlgItem(IDC_STATIC_NAME)->SetFont(&font);
//		pDC->SetBkColor(RGB(255,0,0));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
	// TODO: �ڴ����ר�ô����/����û���
	if (m_hAccel) 
	{
		if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg)) 
		{

			OnBnClickedBtnStart();     //���ذ�ť����ĺ�����
			return(TRUE);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
