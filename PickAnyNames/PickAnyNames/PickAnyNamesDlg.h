
// PickAnyNamesDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
#include <iostream>


// CPickAnyNamesDlg �Ի���
class CPickAnyNamesDlg : public CDialogEx
{
// ����
public:
	CPickAnyNamesDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PICKANYNAMES_DIALOG };

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
	CFont font;
	CFont font1;
	CStdioFile namefile;
	std::vector<CString> CStr;
	bool bStart;
	int cnt;
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
