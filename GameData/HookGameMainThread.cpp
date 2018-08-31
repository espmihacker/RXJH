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
			//DbgPrintfMine("��Ϣ����  %d\r\n", lpArg->lParam);
			switch(lpArg->wParam){
			case MSG_USEGOODBYNAME:
				//TBACK_PACK_LIST_OBJ g_tBackPackListObj;
				g_tBackPackListObj.useGoodByIndex((char*)lpArg->lParam);
				DbgPrintfMine("ʹ��[��ҩ(С)]�ɹ���\r\n");
				break;
			case MSG_TEST:
				//g_tMonsterListObj.getData()->dbgPrintMsg();
				
				//DbgPrintfMine("X=%d Y=%d",g_tRoleObj.getData()->flCurX,g_tRoleObj.getData()->flCurY);

				//TACTION_LIST_OBJ g_tActionListObj;
				//g_tActionListObj.getData()->dbgPrintMsg();
				//g_tActionListObj.UseAction(1);
				//g_tActionListObj.UseAction("������Ϣ");

				//g_tRoleObj.selectObj(g_tMonsterListObj.getData()->tMonsterList[1].ndIndexByAllObj);

				//�Զ����
				//g_tRoleObj.getData()->AutoAttackMonster();

				//��������
				//g_tSkillList.getData()->dbgPrintMsg();

				//���ü���
				//g_tSkillList.getData()->dropSkillF1F10("ħ��ն", 2);

				g_tF1_F10List.getData()->useSkillByName("ħ��ն");

				
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

DWORD msgUserGoodsForName(char* szpName){
	::SendMessageA(getGameWndHandle(), MyMsgCode, MSG_USEGOODBYNAME, (LPARAM)szpName);

	return 1;
}

DWORD msgTest(LPVOID lpData){
	::SendMessageA(getGameWndHandle(), MyMsgCode, MSG_TEST, (LPARAM)lpData);

	return 1;
}