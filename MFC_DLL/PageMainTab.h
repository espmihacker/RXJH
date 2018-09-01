#pragma once
#include "PageGuaJi.h"
#include "afxcmn.h"


// CPageMainTab 对话框

class CPageMainTab : public CDialogEx
{
	DECLARE_DYNAMIC(CPageMainTab)

public:
	CPageMainTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPageMainTab();

	// 对话框数据
	enum { IDD = IDD_DIALOG_TABWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_ctl_tabMain;
	//挂机Tab
	CPageGuaJi m_PageGuiJi;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnSupply();
	afx_msg void OnBnClickedStartAuto();
	afx_msg void OnBnClickedBtnStop();
};
