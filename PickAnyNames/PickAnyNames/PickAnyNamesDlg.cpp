
// PickAnyNamesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PickAnyNames.h"
#include "PickAnyNamesDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPickAnyNamesDlg �Ի���




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


// CPickAnyNamesDlg ��Ϣ�������

BOOL CPickAnyNamesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
		(_T("����")));                 // lpszFacename
	GetDlgItem(IDC_EDITNAMESHOW)->SetFont(&font1);
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨
	if(namefile.Open(L"names.txt", CFile::modeRead))
	{
		CString str;
		while(namefile.ReadString(str)&&(!str.IsEmpty()))
			CStr.push_back(str);
	}
	setlocale( LC_CTYPE, old_locale );    
	free( old_locale );//��ԭ�����趨
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPickAnyNamesDlg::OnPaint()
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
HCURSOR CPickAnyNamesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPickAnyNamesDlg::OnBnClickedButtonstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bStart = !bStart;
	if (bStart)
	{
		GetDlgItem(IDC_BUTTONSTART)->SetWindowText(L"��ͣ");
		SetTimer(0,90,NULL);
	}
	else
	{
		GetDlgItem(IDC_BUTTONSTART)->SetWindowText(L"��ʼ");
		KillTimer(0);
	}
}


void CPickAnyNamesDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (CStr.size()==0)
		return;
	int t = cnt++%CStr.size();
	GetDlgItem(IDC_EDITNAMESHOW)->SetWindowText(CStr[t]);
	CDialogEx::OnTimer(nIDEvent);
}
