
// PickSomeoneDlg.h : ͷ�ļ�
//

#pragma once

#include <opencv.hpp>
#include "CvvImage.h"
using namespace cv;


// CPickSomeoneDlg �Ի���
class CPickSomeoneDlg : public CDialogEx
{
// ����
public:
	CPickSomeoneDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PICKSOMEONE_DIALOG };

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

// �Լ����
	Mat ImgSrc;
	bool bStart;
	void ShowImage(Mat src, UINT ID);
	int cnt;
	vector<CString> ImageNames;
	void GetFileFromDir(CString csDirPath);
	CFont font;
	HACCEL m_hAccel;
	int Speed;
public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
