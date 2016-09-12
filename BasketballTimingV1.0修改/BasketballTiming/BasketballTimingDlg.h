
// BasketballTimingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
//#include <opencv.hpp>
#include <iostream>

//using namespace cv;
using namespace std;

// CBasketballTimingDlg �Ի���
class CBasketballTimingDlg : public CDialogEx
{
// ����
public:
	CBasketballTimingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BASKETBALLTIMING_DIALOG };

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
	int m_iAScore;  // A�ӷ���
	int m_iBScore;  // B�ӷ���
	afx_msg void OnBnClickedBtnascoreadd();
	afx_msg void OnBnClickedBtnascoremin();
	afx_msg void OnBnClickedBtnareset();
	afx_msg void OnBnClickedBtnbscoreadd();
	afx_msg void OnBnClickedBtnbscoremin();
	afx_msg void OnBnClickedBtnbreset();
	int m_i24second;    // 24s
	int m_iHalfTime;    // �볡ʱ��
	afx_msg void OnBnClickedBtn24add();
	afx_msg void OnBnClickedBtn24min();
	afx_msg void OnBnClickedBtn24reset();
	afx_msg void OnBnClickedBtnhtmadd();
	afx_msg void OnBnClickedBtnhtmmin();
	afx_msg void OnBnClickedBtnhtsadd();
	afx_msg void OnBnClickedBtnhtsmin();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CFont font;    // ��������/��С
	CFont fontnum; // ��������/��С
	CFont fonttitle; // ��������
	CEdit m_ctrAScore;
	COLORREF ColorA; // A�ӷ�����ɫ
	COLORREF ColorB; // B�ӷ�����ɫ
	afx_msg void OnBnClickedBtnstart();
	afx_msg void OnBnClickedBtnpause();
	afx_msg void OnTimer(UINT_PTR nIDEvent); // ��ʱ������
	void UpdataTime();   // ����ʱ�亯��
	void GameOver();     // 24���ȫ������
	void TimeShow(int HalfTime, int i24Sec, bool b24Show = true);
	afx_msg void OnBnClickedBtnbeep();
	// ���߳���ز���������
	HANDLE hProcessThread;
	static DWORD WINAPI ThreadFun(LPVOID pthread);
	BOOL bTimeUpdate;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
