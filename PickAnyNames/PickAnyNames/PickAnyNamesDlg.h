
// PickAnyNamesDlg.h : 头文件
//

#pragma once
#include <vector>
#include <iostream>


// CPickAnyNamesDlg 对话框
class CPickAnyNamesDlg : public CDialogEx
{
// 构造
public:
	CPickAnyNamesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PICKANYNAMES_DIALOG };

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
	CFont font;
	CFont font1;
	CStdioFile namefile;
	std::vector<CString> CStr;
	bool bStart;
	int cnt;
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
