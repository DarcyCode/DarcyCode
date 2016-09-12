
// BasketballTimingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BasketballTiming.h"
#include "BasketballTimingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBasketballTimingDlg �Ի���




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


// CBasketballTimingDlg ��Ϣ�������

BOOL CBasketballTimingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
		(_T("����")));                 // lpszFacename

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

	fonttitle.CreatePointFont(500,_T("����С���μ���"));
	GetDlgItem(IDC_STATICE)->SetFont(&fonttitle);

	ColorA = RGB(10,10,255); // A�ӵ���ɫ
	ColorB = RGB(255,0,0); // B�ӵ���ɫ
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBasketballTimingDlg::OnPaint()
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBasketballTimingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBasketballTimingDlg::OnBnClickedBtnascoreadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iAScore++;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTASCORESW)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnascoremin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iAScore > 0 ? m_iAScore-- : 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTASCORESW)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnareset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iAScore = 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTASCORESW)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnbscoreadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iBScore++;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTBSCORE)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnbscoremin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iBScore > 0 ? m_iBScore-- : 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTBSCORE)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnbreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iBScore = 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDTBSCORE)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtn24add()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_i24second < 24 ? m_i24second++ : 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDT24SEC)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtn24min()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_i24second > 0 ? m_i24second-- : 0;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDT24SEC)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtn24reset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_i24second = 24;
	UpdateData(FALSE);
	CRect rc;
	GetDlgItem(IDC_EDT24SEC)->GetWindowRect(&rc);
	InvalidateRect(rc);
}


void CBasketballTimingDlg::OnBnClickedBtnhtmadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ˸��� DC ���κ���
	if (pWnd->GetDlgCtrlID() == IDC_STATICA)
	{
		pDC->SetTextColor(ColorA);  //������ɫ
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDTASCORESW)
	{
		pDC->SetTextColor(ColorA);  //������ɫ
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATICB)
	{
		pDC->SetTextColor(ColorB);  //������ɫ
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDTBSCORE)
	{
		pDC->SetTextColor(ColorB);  //������ɫ
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CBasketballTimingDlg::OnBnClickedBtnstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(0);
	SetTimer(1,100,NULL);
}


void CBasketballTimingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 0:
		// ��ʱ��С��24s��24����㲻��ʾ
		// 24s��ʱ����ʱ�䵽������
		m_iHalfTime > m_i24second ? (m_i24second > 0 ? m_i24second-- : 0) : 0;
		m_iHalfTime > 0 ? m_iHalfTime-- : 0;
		UpdataTime();
		break;
	case 1:  // ʱ�䵽��ʱ
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
	// 1����ʱ�����24s��24sδ��
	// 2����ʱ�����24s��24s��
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
