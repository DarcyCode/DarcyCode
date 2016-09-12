
// TickTocDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TickToc.h"
#include "TickTocDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTickTocDlg �Ի���




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


// CTickTocDlg ��Ϣ�������

BOOL CTickTocDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
		(_T("����")));             // lpszFacename
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&fontnum);
	GetDlgItem(IDC_EDIT_SETTIME)->SetFont(&fontbtn);
	GetDlgItem(IDC_BTN_START)->SetFont(&fontbtn);
	GetDlgItem(IDC_BTN_SETTIME)->SetFont(&fontbtn);
	GetDlgItem(IDOK)->SetFont(&fontbtn);
	GetDlgItem(IDC_STATIC1)->SetFont(&fontbtn);
	GetDlgItem(IDC_BTN_RESET)->SetFont(&fontbtn);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTickTocDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTickTocDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTickTocDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bstart = !bstart;
	if (bstart)
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(L"ֹͣ��ʱ");
		SetTimer(0,1000,NULL);
		GetDlgItem(IDC_BTN_SETTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_START)->SetWindowText(L"��ʼ��ʱ");
		KillTimer(0);
		GetDlgItem(IDC_BTN_SETTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(TRUE);
	}
}


void CTickTocDlg::OnBnClickedBtnSettime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bset = !bset;
	if (bset)
	{
		GetDlgItem(IDC_EDIT_SETTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SETTIME)->SetWindowText(L"����ʱ��");
		GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_SETTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SETTIME)->SetWindowText(L"����ʱ��");
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(TRUE);
		UpdateData(TRUE);
		m_iTimeShow = m_iTime;
		UpdateData(FALSE);
	}
}


void CTickTocDlg::OnBnClickedBtnReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iTimeShow = m_iTime;
	UpdateData(FALSE);
}
