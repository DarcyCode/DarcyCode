
// PickSomeoneDlg.h : 头文件
//

#pragma once

#include <opencv.hpp>
#include "CvvImage.h"
using namespace cv;


// CPickSomeoneDlg 对话框
class CPickSomeoneDlg : public CDialogEx
{
// 构造
public:
	CPickSomeoneDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PICKSOMEONE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

// 自己添加
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
