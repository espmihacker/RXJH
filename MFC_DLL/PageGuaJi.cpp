// PageGuaJi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_DLL.h"
#include "PageGuaJi.h"
#include "afxdialogex.h"


// CPageGuaJi �Ի���

IMPLEMENT_DYNAMIC(CPageGuaJi, CDialogEx)

CPageGuaJi::CPageGuaJi(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPageGuaJi::IDD, pParent)
	, m_chk_isAutoAttackMonster(FALSE)
{

}

CPageGuaJi::~CPageGuaJi()
{
}

void CPageGuaJi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_AUTO_ATTACK_MONSTER, m_chk_isAutoAttackMonster);
}


BEGIN_MESSAGE_MAP(CPageGuaJi, CDialogEx)
END_MESSAGE_MAP()


// CPageGuaJi ��Ϣ�������
