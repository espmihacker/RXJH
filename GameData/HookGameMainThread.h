
#ifndef __HOOK_GAME_MAIN_THREAD_H__
#define __HOOK_GAME_MAIN_THREAD_H__

#define MSG_TEST 2333 //测试
#define MSG_USEGOODBYNAME 1000 //使用物品
#define MSG_USESKILLBYNAME 1001 //使用技能
#define MSG_DROPSKILL2F1F10 1002 //使用技能
#define MSG_AUTOATTACKBYSKILL 1003 //使用技能自动打怪

//以下的函数可以在非主线程函数执行
DWORD msgTest(LPVOID lpData);
DWORD hookMainThread();
DWORD unHookMainThread();

//物品
DWORD msgUserGoodsForName(char* szpGoodName);

//技能
DWORD msgUseSkillByName(char* szpSkillName);
DWORD msgDropSkillF1F10(char* szpSkillName);

//打怪
DWORD msgAutoAttackMonsterBySkill(char* szpSkillName);

#endif