#pragma once
#include <Windows.h>


class CAutoPlay
{
	//Ӧ������
public:
	CAutoPlay(void);
	~CAutoPlay(void);

	BOOL isAutoAttackMonster;//�Ƿ��Զ����
	DWORD ndFrequencyForAttackPickThread;//���߳���ʱ
	HANDLE hT_AutoAttackPick;//���߳̾��

	static void ThreadPro_AutoAttackMonsterAndPickGood(void);
	//��ʼ�һ�
	void autoPlay();
	//ֹͣ�һ�
	void stopPlay();
};

