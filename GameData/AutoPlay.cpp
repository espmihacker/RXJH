#include "AutoPlay.h"
#include "HookGameMainThread.h"

CAutoPlay g_cAutoPlay;

CAutoPlay::CAutoPlay(void)
{
	ndFrequencyForAttackPickThread = 1000;//��ּ��
	hT_AutoAttackPick = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPro_AutoAttackMonsterAndPickGood, NULL, CREATE_SUSPENDED, NULL);//��ȫ���� ��ջ��С �ص����� NULL 
}


CAutoPlay::~CAutoPlay(void)
{
	//����Ĺ���
	TerminateThread(hT_AutoAttackPick, 1);
}

void CAutoPlay::ThreadPro_AutoAttackMonsterAndPickGood(void){
	while(TRUE){
		//����
		//���
		if(g_cAutoPlay.isAutoAttackMonster){
			msgAutoAttackMonsterBySkill("����");
		}
		Sleep(g_cAutoPlay.ndFrequencyForAttackPickThread);
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