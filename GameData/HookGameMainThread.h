
#ifndef __HOOK_GAME_MAIN_THREAD_H__
#define __HOOK_GAME_MAIN_THREAD_H__

#define MSG_TEST 2333 //����
#define MSG_USEGOODBYNAME 1000 //ʹ����Ʒ
#define MSG_USESKILLBYNAME 1001 //ʹ�ü���
#define MSG_DROPSKILL2F1F10 1002 //ʹ�ü���
#define MSG_AUTOATTACKBYSKILL 1003 //ʹ�ü����Զ����
#define MSG_FINDWAY 1004			//�Զ�Ѱ·
#define MSG_SAVEGOODTODEPOT 1005	//���

//���µĺ��������ڷ����̺߳���ִ��
DWORD msgTest(LPVOID lpData);
DWORD hookMainThread();
DWORD unHookMainThread();

//��Ʒ
DWORD msgUserGoodsForName(char* szpGoodName);

//����
DWORD msgUseSkillByName(char* szpSkillName);
DWORD msgDropSkillF1F10(char* szpSkillName);

//���
DWORD msgAutoAttackMonsterBySkill(char* szpSkillName);

//Ѱ·
BOOL msgFindWay(int niX, int niY);

//���
BOOL msgSaveGoodToDepot(char* szpGoodName, DWORD ndGoodNum);

#endif