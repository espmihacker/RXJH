// MainDialogWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "MFC_DLL.h"
#include "MainDialogWnd.h"
#include "BaseGame.h"
#include "StructGame.h"
#include "HookGameMainThread.h"
#include "global_Var.h"

// CMainDialogWnd 对话框

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
	ON_WM_CLOSE()//关闭窗体消息
	ON_BN_CLICKED(IDC_BTN_TEST, &CMainDialogWnd::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDialogWnd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDialogWnd::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainDialogWnd::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainDialogWnd::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMainDialogWnd::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMainDialogWnd 消息处理程序

void CMainDialogWnd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	unHookMainThread();//卸载消息
	CDialogEx::OnClose();
}

void CMainDialogWnd::OnBnClickedBtnTest()
{
	//TRACE("GameData:我的调试信息\r\n");
	//TRACE("GameData:人物名=%s\r\n", BaseRole);
	//TRACE("GameData:人物等级=%d\r\n", *(BYTE*)(BaseRole + 0x34));
	//TRACE("GameData:人物名声=%s\r\n", (char*)(BaseRole + 0x36));

	//TRACE("GameData:人物HP=%d | %d\r\n", *(DWORD*)(BaseRole + 0x80), *(DWORD*)(BaseRole + 0x8C));
	//TRACE("GameData:人物MP=%d | %d\r\n", *(DWORD*)(BaseRole + 0x84), *(DWORD*)(BaseRole + 0x90));
	//TRACE("GameData:愤怒值=%d\r\n", *(DWORD*)(BaseRole + 0x88));
	//TRACE("GameData:金币值=%d\r\n", *(DWORD*)(BaseRole + 0xE4));

	TROLE_PROPERTY role;
	TROLE_PROPERTY* roleData = role.getData();
	TRACE("GameData:人物名字=%s\r\n", roleData->szpRoleName);
	TRACE("GameData:人物等级=%d\r\n", roleData->ndLevel);
	TRACE("GameData:人物职业=%d\r\n", roleData->ndLevel职业);
	TRACE("GameData:人物名声=%s\r\n", roleData->szp名声);
	TRACE("GameData:人物HP=%d | %d\r\n", roleData->ndHp, roleData->ndMaxHp);
	TRACE("GameData:人物MP=%d | %d\r\n", roleData->ndMp, roleData->ndMaxMp);
	TRACE("GameData:愤怒值=%d\r\n", roleData->ndAngry);
	
	TRACE("GameData:心=%d\r\n", roleData->nd心);
	TRACE("GameData:气=%d\r\n", roleData->nd气);
	TRACE("GameData:体=%d\r\n", roleData->nd体);
	TRACE("GameData:魄=%d\r\n", roleData->nd魄);

	TRACE("GameData:攻击力=%d\r\n", roleData->nd攻击力);
	TRACE("GameData:防御力=%d\r\n", roleData->nd防御力);
	TRACE("GameData:命中率=%d\r\n", roleData->nd命中率);
	TRACE("GameData:回避率=%d\r\n", roleData->nd回避率);

	TRACE("GameData:金币=%d\r\n", roleData->nqMoney);
	TRACE("GameData:负重=%d | %d\r\n", roleData->nw负重, roleData->nwMax负重);

	TRACE("GameData:剩余气功点数=%d\r\n", roleData->ndPoint气功);

	//测试背包
	for(int i = 0; i < nBackPackSize; i++){
		if(g_tBackPackListObj.getData()->mtGoodList[i].ndGoodNum == 0){
			continue;
		}
		TRACE("GameData:第%d格，%s(%d):%s\r\n", i+1,\
			g_tBackPackListObj.getData()->mtGoodList[i].szpGoodName,\
			g_tBackPackListObj.getData()->mtGoodList[i].ndGoodNum,\
			g_tBackPackListObj.getData()->mtGoodList[i].szpGoodDesc);
	}

	//测试打开仓库
	g_tRoleObj.getData()->OpenDepot();

	//BOOL bFlag = tGoodList.useGoodForIndex("金创药(小)");
	////int xy = tGoodList.getGoodIndexByName("金创药(小)");
	//if(bFlag){
	//	TRACE("GameData:使用[金创药(小)]成功！\r\n");
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
	msgUserGoodsForName("金创药(小)");
}


void CMainDialogWnd::OnBnClickedButton5()
{

	msgTest(NULL);
	//Sleep(200);
	//msgTest(NULL);

	//"魔龙斩"
	//msgUseSkillByName("魔龙斩");

	//使用技能自动打怪
	//msgAutoAttackMonsterBySkill("魔龙斩");
}


void CMainDialogWnd::OnBnClickedButton6()
{
	m_PageMainTab.ShowWindow(SW_SHOW);
}

//重写的方法
BOOL CMainDialogWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_PageMainTab.Create(CPageMainTab::IDD);//参数为ID

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
