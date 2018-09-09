#include "AutoPlay.h"
#include "HookGameMainThread.h"

CAutoPlay g_cAutoPlay;

CAutoPlay::CAutoPlay(void)
{
	ndFrequencyForAttackPickThread = 1000;//��ּ��
	/* ���û�����ʽ�ӱܱ������Ľ��� */
	DWORD proc = NULL;
	__asm
	{
		mov eax, ThreadPro_AutoAttackMonsterAndPickGood
		mov proc,eax
	}
	//__stdcall
	hT_AutoAttackPick = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, this, CREATE_SUSPENDED, NULL);//��ȫ���� ��ջ��С �ص����� NULL 
}


CAutoPlay::~CAutoPlay(void)
{
	//����Ĺ���
	TerminateThread(hT_AutoAttackPick, 1);//ǿ�ƹر��߳�
}

//__thiscall
void CAutoPlay::ThreadPro_AutoAttackMonsterAndPickGood(LPVOID lpData){
	__asm{
		mov ecx,lpData
		mov this,ecx
	}
	while(TRUE){
		//����
		//���
		if(isAutoAttackMonster){
			msgAutoAttackMonsterBySkill("����");
		}
		Sleep(ndFrequencyForAttackPickThread);
	}
}


void CAutoPlay::autoPlay(){
	//�ָ��߳�ִ��
	ResumeThread(hT_AutoAttackPick);
}


void CAutoPlay::stopPlay(){
	//�����߳�ִ��
	SuspendThread(hT_AutoAttackPick);
}