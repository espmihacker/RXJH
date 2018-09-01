#include "AutoPlay.h"
#include "HookGameMainThread.h"

CAutoPlay g_cAutoPlay;

CAutoPlay::CAutoPlay(void)
{
	ndFrequencyForAttackPickThread = 1000;//打怪间隔
	hT_AutoAttackPick = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPro_AutoAttackMonsterAndPickGood, NULL, CREATE_SUSPENDED, NULL);//安全属性 堆栈大小 回调函数 NULL 
}


CAutoPlay::~CAutoPlay(void)
{
	//清理的工作
	TerminateThread(hT_AutoAttackPick, 1);
}

void CAutoPlay::ThreadPro_AutoAttackMonsterAndPickGood(void){
	while(TRUE){
		//捡物
		//打怪
		if(g_cAutoPlay.isAutoAttackMonster){
			msgAutoAttackMonsterBySkill("攻击");
		}
		Sleep(g_cAutoPlay.ndFrequencyForAttackPickThread);
	}
}


void CAutoPlay::autoPlay(){
	//恢复线程执行
	ResumeThread(hT_AutoAttackPick);
}


void CAutoPlay::stopPlay(){
	//挂起线程执行
	SuspendThread(hT_AutoAttackPick);
}