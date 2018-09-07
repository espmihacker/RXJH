#include <Windows.h>
#include "StructGame.h"
#include "HookGameMainThread.h"
#include "global_Var.h"

HHOOK g_hhkGame;
const DWORD MyMsgCode = RegisterWindowMessageA("MyMsgCode");

LRESULT CALLBACK GameWndProc(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	){
	CWPSTRUCT *lpArg = (CWPSTRUCT*)lParam;
	if(nCode == HC_ACTION){
		if(lpArg->hwnd == getGameWndHandle() && MyMsgCode){
			//DbgPrintfMine("消息传到  %d\r\n", lpArg->lParam);
			switch(lpArg->wParam){
			case MSG_USEGOODBYNAME:
				//TBACK_PACK_LIST_OBJ g_tBackPackListObj;
				g_tBackPackListObj.useGoodByIndex((char*)lpArg->lParam);
				DbgPrintfMine("使用[金创药(小)]成功！\r\n");
				break;
			case MSG_DROPSKILL2F1F10:
				g_tSkillList.getData()->dropSkillF1F10((char*)lpArg->lParam);
				break;
			case MSG_USESKILLBYNAME:
				g_tSkillList.getData()->dropSkillF1F10((char*)lpArg->lParam);
				g_tF1_F10List.getData()->useSkillByName((char*)lpArg->lParam);
				break;
			case MSG_AUTOATTACKBYSKILL:
				msgDropSkillF1F10((char*)lpArg->lParam);
				//char* szpSkillName = ((char*)lpArg->lParam);
				g_tRoleObj.getData()->autoAttackMonsterBySkill((char*)lpArg->lParam);
				break;
			case MSG_FINDWAY:
				{
					int *niXY = (int*)lpArg->lParam;
					g_tRoleObj.getData()->findWay(niXY[0], niXY[1]);
				}
				break;
			case MSG_TEST:
				//g_tMonsterListObj.getData()->dbgPrintMsg();
				
				//DbgPrintfMine("X=%f Y=%f",g_tRoleObj.getData()->flCurX,g_tRoleObj.getData()->flCurY);

				//g_tMonsterListObj.getData()->dbgPrintMsg();

				//g_tActionListObj.getData()->dbgPrintMsg();
				//g_tActionListObj.UseAction(1);
				//g_tActionListObj.UseAction("运气调息");

				//g_tRoleObj.selectObj(g_tMonsterListObj.getData()->tMonsterList[1].ndIndexByAllObj);

				//自动打怪
				//g_tRoleObj.getData()->AutoAttackMonster();

				//技能数组
				//g_tSkillList.getData()->dbgPrintMsg();

				//放置技能
				//g_tSkillList.getData()->dropSkillF1F10("魔龙斩", 2);

				g_tF1_F10List.getData()->useSkillByName("魔龙斩");

				//修炼技能
				//g_tSkillList.getData()->practiceSkill("猛龙破天");

				//测试学习技能条件
				//for(int i = 0; i < 32; i++){
				//	g_tSkillList.getData()->isCanStudy(i);
				//}
				//

				//g_tBackPackListObj.getData()->selectGoods(1);
				//g_tBackPackListObj.getData()->moveGoodToDepot(1);
				break;
			}
			return 1;
		}
	}
	return CallNextHookEx(g_hhkGame, nCode, wParam, lParam);
}


DWORD hookMainThread(){
	HWND hGame = getGameWndHandle();
	DWORD ndThreadId = GetWindowThreadProcessId(hGame, NULL);
	if(ndThreadId != 0){
		g_hhkGame = SetWindowsHookExA(WH_CALLWNDPROC, GameWndProc, NULL, ndThreadId);
	}

	return 1;
}

DWORD unHookMainThread(){
	UnhookWindowsHookEx(g_hhkGame);

	return 1;
}

DWORD msgUserGoodsForName(char* szpGoodName){
	::SendMessageA(getGameWndHandle(), MyMsgCode, MSG_USEGOODBYNAME, (LPARAM)szpGoodName);

	return 1;
}

DWORD msgDropSkillF1F10(char* szpSkillName){
	::SendMessageA(getGameWndHandle(), MyMsgCode, MSG_DROPSKILL2F1F10, (LPARAM)szpSkillName);

	return 1;
}

DWORD msgUseSkillByName(char* szpSkillName){
	::SendMessageA(getGameWndHandle(), MyMsgCode, MSG_USESKILLBYNAME, (LPARAM)szpSkillName);

	return 1;
}

DWORD msgAutoAttackMonsterBySkill(char* szpSkillName){
	::SendMessageA(getGameWndHandle(), MyMsgCode, MSG_AUTOATTACKBYSKILL, (LPARAM)szpSkillName);

	return 1;
}

BOOL msgFindWay(int niX, int niY){
	int niXY[2] = {0};
	niXY[0] = niX;
	niXY[1] = niY;
	::SendMessageA(getGameWndHandle(), MyMsgCode, MSG_FINDWAY, (LPARAM)niXY);

	return 1;
}

DWORD msgTest(LPVOID lpData){
	::SendMessageA(getGameWndHandle(), MyMsgCode, MSG_TEST, (LPARAM)lpData);

	return 1;
}
