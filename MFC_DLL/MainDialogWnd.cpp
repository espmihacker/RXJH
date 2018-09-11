// MainDialogWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "MFC_DLL.h"
#include "MainDialogWnd.h"
#include "BaseGame.h"
#include "StructGame.h"
#include "HookGameMainThread.h"
#include "global_Var.h"

// CMainDialogWnd �Ի���

IMPLEMENT_DYNAMIC(CMainDialogWnd, CDialogEx)

CMainDialogWnd::CMainDialogWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDialogWnd::IDD, pParent)
{

}

CMainDialogWnd::~CMainDialogWnd()
{
}

void CMainDialogWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDialogWnd, CDialogEx)
	ON_WM_CLOSE()//�رմ�����Ϣ
	ON_BN_CLICKED(IDC_BTN_TEST, &CMainDialogWnd::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDialogWnd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDialogWnd::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainDialogWnd::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainDialogWnd::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMainDialogWnd::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMainDialogWnd ��Ϣ�������

void CMainDialogWnd::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	unHookMainThread();//ж����Ϣ
	CDialogEx::OnClose();
}

void CMainDialogWnd::OnBnClickedBtnTest()
{
	//TRACE("GameData:�ҵĵ�����Ϣ\r\n");
	//TRACE("GameData:������=%s\r\n", BaseRole);
	//TRACE("GameData:����ȼ�=%d\r\n", *(BYTE*)(BaseRole + 0x34));
	//TRACE("GameData:��������=%s\r\n", (char*)(BaseRole + 0x36));

	//TRACE("GameData:����HP=%d | %d\r\n", *(DWORD*)(BaseRole + 0x80), *(DWORD*)(BaseRole + 0x8C));
	//TRACE("GameData:����MP=%d | %d\r\n", *(DWORD*)(BaseRole + 0x84), *(DWORD*)(BaseRole + 0x90));
	//TRACE("GameData:��ŭֵ=%d\r\n", *(DWORD*)(BaseRole + 0x88));
	//TRACE("GameData:���ֵ=%d\r\n", *(DWORD*)(BaseRole + 0xE4));

	TROLE_PROPERTY role;
	TROLE_PROPERTY* roleData = role.getData();
	TRACE("GameData:��������=%s\r\n", roleData->szpRoleName);
	TRACE("GameData:����ȼ�=%d\r\n", roleData->ndLevel);
	TRACE("GameData:����ְҵ=%d\r\n", roleData->ndLevelְҵ);
	TRACE("GameData:��������=%s\r\n", roleData->szp����);
	TRACE("GameData:����HP=%d | %d\r\n", roleData->ndHp, roleData->ndMaxHp);
	TRACE("GameData:����MP=%d | %d\r\n", roleData->ndMp, roleData->ndMaxMp);
	TRACE("GameData:��ŭֵ=%d\r\n", roleData->ndAngry);
	
	TRACE("GameData:��=%d\r\n", roleData->nd��);
	TRACE("GameData:��=%d\r\n", roleData->nd��);
	TRACE("GameData:��=%d\r\n", roleData->nd��);
	TRACE("GameData:��=%d\r\n", roleData->nd��);

	TRACE("GameData:������=%d\r\n", roleData->nd������);
	TRACE("GameData:������=%d\r\n", roleData->nd������);
	TRACE("GameData:������=%d\r\n", roleData->nd������);
	TRACE("GameData:�ر���=%d\r\n", roleData->nd�ر���);

	TRACE("GameData:���=%d\r\n", roleData->nqMoney);
	TRACE("GameData:����=%d | %d\r\n", roleData->nw����, roleData->nwMax����);

	TRACE("GameData:ʣ����������=%d\r\n", roleData->ndPoint����);

	//���Ա���
	for(int i = 0; i < nDepotListSize; i++){
		if(g_tBackPackListObj.getData()->mtGoodList[i].ndGoodNum == 0){
			continue;
		}
		TRACE("GameData:��%d��%s(%d):%s\r\n", i+1,\
			g_tBackPackListObj.getData()->mtGoodList[i].szpGoodName,\
			g_tBackPackListObj.getData()->mtGoodList[i].ndGoodNum,\
			g_tBackPackListObj.getData()->mtGoodList[i].szpGoodDesc);
	}

	//���Դ򿪲ֿ�
	g_tRoleObj.getData()->OpenDepot();

	//BOOL bFlag = tGoodList.useGoodForIndex("��ҩ(С)");
	////int xy = tGoodList.getGoodIndexByName("��ҩ(С)");
	//if(bFlag){
	//	TRACE("GameData:ʹ��[��ҩ(С)]�ɹ���\r\n");
	//}

	//g_tRoleObj.getData()->findWay(-250, 1180);
	//msgFindWay(-200, 900);
}


void CMainDialogWnd::OnBnClickedButton2()
{
	hookMainThread();
}


void CMainDialogWnd::OnBnClickedButton3()
{
	unHookMainThread();
}


void CMainDialogWnd::OnBnClickedButton4()
{
	msgUserGoodsForName("��ҩ(С)");
}


void CMainDialogWnd::OnBnClickedButton5()
{

	msgTest(NULL);
	//Sleep(200);
	//msgTest(NULL);

	//"ħ��ն"
	//msgUseSkillByName("ħ��ն");

	//ʹ�ü����Զ����
	//msgAutoAttackMonsterBySkill("ħ��ն");
}


void CMainDialogWnd::OnBnClickedButton6()
{
	m_PageMainTab.ShowWindow(SW_SHOW);
}

//��д�ķ���
BOOL CMainDialogWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_PageMainTab.Create(CPageMainTab::IDD);//����ΪID

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
