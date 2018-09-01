// PageMainTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_DLL.h"
#include "PageMainTab.h"
#include "afxdialogex.h"
#include "global_Var.h"

// CPageMainTab �Ի���

IMPLEMENT_DYNAMIC(CPageMainTab, CDialogEx)

CPageMainTab::CPageMainTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPageMainTab::IDD, pParent)
{

}

CPageMainTab::~CPageMainTab()
{
}

void CPageMainTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_ctl_tabMain);
}


BEGIN_MESSAGE_MAP(CPageMainTab, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CPageMainTab::OnTcnSelchangeTabMain)
	ON_BN_CLICKED(IDC_BTN_SUPPLY, &CPageMainTab::OnBnClickedBtnSupply)
	ON_BN_CLICKED(IDC_START_AUTO, &CPageMainTab::OnBnClickedStartAuto)
	ON_BN_CLICKED(IDC_BTN_STOP, &CPageMainTab::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CPageMainTab ��Ϣ�������


BOOL CPageMainTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//ȡ��ѡ���λ��
	RECT tabRect;
	m_ctl_tabMain.GetClientRect(&tabRect);

	//ȥ��������ť��λ��
	tabRect.top += 23;
	tabRect.left += 3;
	tabRect.bottom -= 3;
	tabRect.right -= 3;

	m_ctl_tabMain.InsertItem(0,"�һ�");
	m_PageGuiJi.Create(CPageGuaJi::IDD);
	m_PageGuiJi.SetParent(&m_ctl_tabMain);//���ø��ؼ�
	m_PageGuiJi.MoveWindow(&tabRect);
	m_PageGuiJi.ShowWindow(SW_SHOW);


	m_ctl_tabMain.InsertItem(1,"����");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPageMainTab::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch(m_ctl_tabMain.GetCurSel()){
	case 0:
		m_PageGuiJi.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_PageGuiJi.ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}


void CPageMainTab::OnBnClickedBtnSupply()
{
	m_PageGuiJi.UpdateData(TRUE);//���½������ݵ�������
	g_cAutoPlay.isAutoAttackMonster = m_PageGuiJi.m_chk_isAutoAttackMonster;
}


void CPageMainTab::OnBnClickedStartAuto()
{
	g_cAutoPlay.autoPlay();
}


void CPageMainTab::OnBnClickedBtnStop()
{
	g_cAutoPlay.stopPlay();
}
