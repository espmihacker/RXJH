#include "AutoPlay.h"
#include "HookGameMainThread.h"

CAutoPlay g_cAutoPlay;

CAutoPlay::CAutoPlay(void)
{
	ndFrequencyForAttackPickThread = 1000;//打怪间隔
	/* 采用汇编的形式逃避编译器的解释 */
	DWORD proc = NULL;
	__asm
	{
		mov eax, ThreadPro_AutoAttackMonsterAndPickGood
		mov proc,eax
	}
	//__stdcall
	hT_AutoAttackPick = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, this, CREATE_SUSPENDED, NULL);//安全属性 堆栈大小 回调函数 NULL 
}


CAutoPlay::~CAutoPlay(void)
{
	//清理的工作
	TerminateThread(hT_AutoAttackPick, 1);
}

//__thiscall
void CAutoPlay::ThreadPro_AutoAttackMonsterAndPickGood(LPVOID lpData){
	__asm{
		mov ecx,lpData
		mov this,ecx
	}
	while(TRUE){
		//捡物
		//打怪
		if(isAutoAttackMonster){
			msgAutoAttackMonsterBySkill("攻击");
		}
		Sleep(ndFrequencyForAttackPickThread);
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