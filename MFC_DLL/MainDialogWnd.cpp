// MainDialogWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "MFC_DLL.h"
#include "MainDialogWnd.h"
#include "BaseGame.h"
#include "StructGame.h"
#include "HookGameMainThread.h"

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
	ON_BN_CLICKED(IDC_BTN_TEST, &CMainDialogWnd::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDialogWnd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDialogWnd::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainDialogWnd::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainDialogWnd::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMainDialogWnd::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMainDialogWnd 消息处理程序

void CMainDialogWnd::OnBnClickedBtnTest()
{
	//TRACE("GameDebug:我的调试信息\r\n");
	//TRACE("GameDebug:人物名=%s\r\n", BaseRole);
	//TRACE("GameDebug:人物等级=%d\r\n", *(BYTE*)(BaseRole + 0x34));
	//TRACE("GameDebug:人物名声=%s\r\n", (char*)(BaseRole + 0x36));

	//TRACE("GameDebug:人物HP=%d | %d\r\n", *(DWORD*)(BaseRole + 0x80), *(DWORD*)(BaseRole + 0x8C));
	//TRACE("GameDebug:人物MP=%d | %d\r\n", *(DWORD*)(BaseRole + 0x84), *(DWORD*)(BaseRole + 0x90));
	//TRACE("GameDebug:愤怒值=%d\r\n", *(DWORD*)(BaseRole + 0x88));
	//TRACE("GameDebug:金币值=%d\r\n", *(DWORD*)(BaseRole + 0xE4));

	TROLE_PROPERTY role;
	TROLE_PROPERTY* roleData = role.getData();
	TRACE("GameDebug:人物名字=%s\r\n", roleData->szpRoleName);
	TRACE("GameDebug:人物等级=%d\r\n", roleData->ndLevel);
	TRACE("GameDebug:人物职业=%d\r\n", roleData->ndLevel职业);
	TRACE("GameDebug:人物名声=%s\r\n", roleData->szp名声);
	TRACE("GameDebug:人物HP=%d | %d\r\n", roleData->ndHp, roleData->ndMaxHp);
	TRACE("GameDebug:人物MP=%d | %d\r\n", roleData->ndMp, roleData->ndMaxMp);
	TRACE("GameDebug:愤怒值=%d\r\n", roleData->ndAngry);
	
	TRACE("GameDebug:心=%d\r\n", roleData->nd心);
	TRACE("GameDebug:气=%d\r\n", roleData->nd气);
	TRACE("GameDebug:体=%d\r\n", roleData->nd体);
	TRACE("GameDebug:魄=%d\r\n", roleData->nd魄);

	TRACE("GameDebug:攻击力=%d\r\n", roleData->nd攻击力);
	TRACE("GameDebug:防御力=%d\r\n", roleData->nd防御力);
	TRACE("GameDebug:命中率=%d\r\n", roleData->nd命中率);
	TRACE("GameDebug:回避率=%d\r\n", roleData->nd回避率);

	TRACE("GameDebug:金币=%d\r\n", roleData->nqMoney);
	TRACE("GameDebug:负重=%d | %d\r\n", roleData->nw负重, roleData->nwMax负重);

	TRACE("GameDebug:剩余气功点数=%d\r\n", roleData->ndPoint气功);

	//测试背包
	TBACK_PACK_LIST_OBJ tGoodList;
	tGoodList.getData();//初始化
	//TBACK_PACK_LIST* bagData = tGoodList.getData();
	for(int i = 0; i < nBackPackSize; i++){
		if(tGoodList.mtGoodList[i].ndGoodNum == 0){
			continue;
		}
		TRACE("GameDebug:第%d格，%s(%d):%s\r\n", i+1,\
			tGoodList.getData()->mtGoodList[i].szpGoodName,\
			tGoodList.getData()->mtGoodList[i].ndGoodNum,\
			tGoodList.getData()->mtGoodList[i].szpGoodDesc);
	}

	//BOOL bFlag = tGoodList.useGoodForIndex("金创药(小)");
	////int xy = tGoodList.getGoodIndexByName("金创药(小)");
	//if(bFlag){
	//	TRACE("GameDebug:使用[金创药(小)]成功！\r\n");
	//}
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
