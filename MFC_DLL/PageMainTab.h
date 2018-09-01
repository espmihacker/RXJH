#pragma once
#include "PageGuaJi.h"
#include "afxcmn.h"


// CPageMainTab �Ի���

class CPageMainTab : public CDialogEx
{
	DECLARE_DYNAMIC(CPageMainTab)

public:
	CPageMainTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageMainTab();

	// �Ի�������
	enum { IDD = IDD_DIALOG_TABWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_ctl_tabMain;
	//�һ�Tab
	CPageGuaJi m_PageGuiJi;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnSupply();
	afx_msg void OnBnClickedStartAuto();
	afx_msg void OnBnClickedBtnStop();
};
