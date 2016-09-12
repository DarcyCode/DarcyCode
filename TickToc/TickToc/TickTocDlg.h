
// TickTocDlg.h : 头文件
//

#pragma once


// CTickTocDlg 对话框
class CTickTocDlg : public CDialogEx
{
// 构造
public:
	CTickTocDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TICKTOC_DIALOG };

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
