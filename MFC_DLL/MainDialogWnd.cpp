// MainDialogWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "MFC_DLL.h"
#include "MainDialogWnd.h"
#include "BaseGame.h"
#include "StructGame.h"
#include "HookGameMainThread.h"

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
	ON_BN_CLICKED(IDC_BTN_TEST, &CMainDialogWnd::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDialogWnd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDialogWnd::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainDialogWnd::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainDialogWnd::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMainDialogWnd ��Ϣ�������

void CMainDialogWnd::OnBnClickedBtnTest()
{
	//TRACE("GameDebug:�ҵĵ�����Ϣ\r\n");
	//TRACE("GameDebug:������=%s\r\n", BaseRole);
	//TRACE("GameDebug:����ȼ�=%d\r\n", *(BYTE*)(BaseRole + 0x34));
	//TRACE("GameDebug:��������=%s\r\n", (char*)(BaseRole + 0x36));

	//TRACE("GameDebug:����HP=%d | %d\r\n", *(DWORD*)(BaseRole + 0x80), *(DWORD*)(BaseRole + 0x8C));
	//TRACE("GameDebug:����MP=%d | %d\r\n", *(DWORD*)(BaseRole + 0x84), *(DWORD*)(BaseRole + 0x90));
	//TRACE("GameDebug:��ŭֵ=%d\r\n", *(DWORD*)(BaseRole + 0x88));
	//TRACE("GameDebug:���ֵ=%d\r\n", *(DWORD*)(BaseRole + 0xE4));

	TROLE_PROPERTY role;
	TROLE_PROPERTY* roleData = role.getData();
	TRACE("GameDebug:��������=%s\r\n", roleData->szpRoleName);
	TRACE("GameDebug:����ȼ�=%d\r\n", roleData->ndLevel);
	TRACE("GameDebug:����ְҵ=%d\r\n", roleData->ndLevelְҵ);
	TRACE("GameDebug:��������=%s\r\n", roleData->szp����);
	TRACE("GameDebug:����HP=%d | %d\r\n", roleData->ndHp, roleData->ndMaxHp);
	TRACE("GameDebug:����MP=%d | %d\r\n", roleData->ndMp, roleData->ndMaxMp);
	TRACE("GameDebug:��ŭֵ=%d\r\n", roleData->ndAngry);
	
	TRACE("GameDebug:��=%d\r\n", roleData->nd��);
	TRACE("GameDebug:��=%d\r\n", roleData->nd��);
	TRACE("GameDebug:��=%d\r\n", roleData->nd��);
	TRACE("GameDebug:��=%d\r\n", roleData->nd��);

	TRACE("GameDebug:������=%d\r\n", roleData->nd������);
	TRACE("GameDebug:������=%d\r\n", roleData->nd������);
	TRACE("GameDebug:������=%d\r\n", roleData->nd������);
	TRACE("GameDebug:�ر���=%d\r\n", roleData->nd�ر���);

	TRACE("GameDebug:���=%d\r\n", roleData->nqMoney);
	TRACE("GameDebug:����=%d | %d\r\n", roleData->nw����, roleData->nwMax����);

	TRACE("GameDebug:ʣ����������=%d\r\n", roleData->ndPoint����);

	//���Ա���
	TBACK_PACK_LIST_OBJ tGoodList;
	tGoodList.getData();//��ʼ��
	//TBACK_PACK_LIST* bagData = tGoodList.getData();
	for(int i = 0; i < nBackPackSize; i++){
		if(tGoodList.mtGoodList[i].ndGoodNum == 0){
			continue;
		}
		TRACE("GameDebug:��%d��%s(%d):%s\r\n", i+1,\
			tGoodList.getData()->mtGoodList[i].szpGoodName,\
			tGoodList.getData()->mtGoodList[i].ndGoodNum,\
			tGoodList.getData()->mtGoodList[i].szpGoodDesc);
	}

	//BOOL bFlag = tGoodList.useGoodForIndex("��ҩ(С)");
	////int xy = tGoodList.getGoodIndexByName("��ҩ(С)");
	//if(bFlag){
	//	TRACE("GameDebug:ʹ��[��ҩ(С)]�ɹ���\r\n");
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
	msgUserGoodsForName("��ҩ(С)");
}


void CMainDialogWnd::OnBnClickedButton5()
{
	msgTest(NULL);
	Sleep(200);
	msgTest(NULL);
}
