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
				//g_tActionListObj.UseAction("������Ϣ");

				//g_tRoleObj.selectObj(g_tMonsterListObj.getData()->tMonsterList[1].ndIndexByAllObj);

				//�Զ����
				//g_tRoleObj.getData()->AutoAttackMonster();

				//��������
				//g_tSkillList.getData()->dbgPrintMsg();

				//���ü���
				//g_tSkillList.getData()->dropSkillF1F10("ħ��ն", 2);

				//ʹ�ü���
				//g_tF1_F10List.getData()->useSkillByName("ħ��ն");

				//��������
				//g_tSkillList.getData()->practiceSkill("��������");

				//����ѧϰ��������
				//for(int i = 0; i < 32; i++){
				//	g_tSkillList.getData()->isCanStudy(i);
				//}
				//

				//g_tBackPackListObj.getData()->selectGoods(1);
				//g_tBackPackListObj.getData()->moveGoodToDepot(1);

				//���Ը���װ��
				//g_tBackPackListObj.getData()->selectGoods(0);
				//g_tBackPackListObj.getData()->moveGoodToEquip(g_tBackPackListObj.ndHandguardL);
				//-
				//g_tBackPackListObj.getData()->moveGoodToEquipHandguardL(g_tBackPackListObj.ndHandguardL, "Ƥ����");

				//���Դ�NPC�Ի���
				//g_tRoleObj.OpenNpcByNpcName("Τ��");//1-ƽʮָ

				//���Ի�ȡNPC��ַ
				//DbgPrintfMine("%X",g_tMonsterListObj.getData()->GetNpcObjByName("Τ��"));

				//���Դ��N����Ʒ���ֿ�
				BYTE nbData[0x90] = {
					0x00,0x00,0x94,0x00,0x8C,0x00,0x01,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0xF1,0xF1,
					0xF1,0x00,0x65,0xCA,0x9A,0x3B,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0xDA,0x19,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0xD0,0xD1,0x1A,0x2A,0x05,
					0x7D,0x0C,0x65,0xCA,0x9A,0x3B,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0xB6,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCA,0x80,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0xC1,0x80,0x00,0x00,
					0x00,0x00,0x00,0x00,0xD2,0x80,0x38,0x79,0xD0,0x80,0x35,0x6F,0xC1,0x80,0x38,0x70
				};

				PTSAVE_DEPOT_DATA pSavaData = (PTSAVE_DEPOT_DATA)nbData;
				pSavaData->ndId1_A = 0x3B9ACA65;
				pSavaData->ndId1_A = pSavaData->ndId1_A;
				pSavaData->nqId2 = 0x0C7D052DC2AB21A3;
				pSavaData->nwGoodSaveNum = 1;
				pSavaData->nwCurGoodNum = 3;
				pSavaData->nbIndexForBackpack = 0;


				__asm
				{
					mov ecx,pSavaData
					lea ecx,nbData
					/*
					//-------------------------------------//
					//��ƷID���1
					mov dword ptr ss:[ecx+0x12],0x3B9ACA65
					mov dword ptr ss:[ecx+0x32],0x3B9ACA65
					//����
					mov word ptr ss:[ecx+0x1A],1
					//��ƷID���2
					mov dword ptr ss:[ecx+0x2A],0xC2AB21A3
					mov dword ptr ss:[ecx+0x2A+4],0x0C7D052D
					//
					//��Ʒ����
					mov word ptr ss:[ecx+0x3A],0x4
					//��Ʒ�ڱ����е��±�
					mov BYTE ptr ss:[ecx+0x43],0x0
					//--------------------------------------//
					*/
					push 0x8E
					push ecx
					mov ecx,dword ptr ds:[0x117F3A0]
					mov eax,0x004E8800
						call eax
				}

				DbgPrintfMine("���Դ��N����Ʒ���ֿ�");

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
