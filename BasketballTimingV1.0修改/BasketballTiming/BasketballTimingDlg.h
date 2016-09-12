
// BasketballTimingDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
//#include <opencv.hpp>
#include <iostream>

//using namespace cv;
using namespace std;

// CBasketballTimingDlg 对话框
class CBasketballTimingDlg : public CDialogEx
{
// 构造
public:
	CBasketballTimingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BASKETBALLTIMING_DIALOG };

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
public:
	int m_iAScore;  // A队分数
	int m_iBScore;  // B队分数
	afx_msg void OnBnClickedBtnascoreadd();
	afx_msg void OnBnClickedBtnascoremin();
	afx_msg void OnBnClickedBtnareset();
	afx_msg void OnBnClickedBtnbscoreadd();
	afx_msg void OnBnClickedBtnbscoremin();
	afx_msg void OnBnClickedBtnbreset();
	int m_i24second;    // 24s
	int m_iHalfTime;    // 半场时间
	afx_msg void OnBnClickedBtn24add();
	afx_msg void OnBnClickedBtn24min();
	afx_msg void OnBnClickedBtn24reset();
	afx_msg void OnBnClickedBtnhtmadd();
	afx_msg void OnBnClickedBtnhtmmin();
	afx_msg void OnBnClickedBtnhtsadd();
	afx_msg void OnBnClickedBtnhtsmin();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CFont font;    // 文字字体/大小
	CFont fontnum; // 数字字体/大小
	CFont fonttitle; // 标题字体
	CEdit m_ctrAScore;
	COLORREF ColorA; // A队分数颜色
	COLORREF ColorB; // B队分数颜色
	afx_msg void OnBnClickedBtnstart();
	afx_msg void OnBnClickedBtnpause();
	afx_msg void OnTimer(UINT_PTR nIDEvent); // 定时器函数
	void UpdataTime();   // 更新时间函数
	void GameOver();     // 24秒或全场结束
	void TimeShow(int HalfTime, int i24Sec, bool b24Show = true);
	afx_msg void OnBnClickedBtnbeep();
	// 多线程相关参数及函数
	HANDLE hProcessThread;
	static DWORD WINAPI ThreadFun(LPVOID pthread);
	BOOL bTimeUpdate;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
