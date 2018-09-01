#pragma once
#include <Windows.h>


class CAutoPlay
{
	//应用设置
public:
	CAutoPlay(void);
	~CAutoPlay(void);

	BOOL isAutoAttackMonster;//是否自动打怪
	DWORD ndFrequencyForAttackPickThread;//主线程延时
	HANDLE hT_AutoAttackPick;//主线程句柄

	static void ThreadPro_AutoAttackMonsterAndPickGood(void);
	//开始挂机
	void autoPlay();
	//停止挂机
	void stopPlay();
};

