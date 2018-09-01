#pragma once
#include "PageMainTab.h"

// CMainDialogWnd 对话框

class CMainDialogWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDialogWnd)

public:
	CMainDialogWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDialogWnd();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();

	CPageMainTab m_PageMainTab;
	virtual BOOL OnInitDialog();
};
