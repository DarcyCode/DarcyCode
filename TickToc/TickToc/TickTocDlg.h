
// TickTocDlg.h : ͷ�ļ�
//

#pragma once


// CTickTocDlg �Ի���
class CTickTocDlg : public CDialogEx
{
// ����
public:
	CTickTocDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TICKTOC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int Time;
	CFont fontnum;
	CFont fontbtn;
	int m_iTime;
	bool bstart;
	bool bset;
	int m_iTimeShow;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnSettime();
	afx_msg void OnBnClickedBtnReset();
};