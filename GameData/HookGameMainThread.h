
#ifndef __HOOK_GAME_MAIN_THREAD_H__
#define __HOOK_GAME_MAIN_THREAD_H__

#define MSG_USEGOODBYNAME 1000 //ʹ����Ʒ
#define MSG_TEST 1001 //ʹ����Ʒ

DWORD hookMainThread();
DWORD unHookMainThread();
DWORD msgUserGoodsForName(char* szpName);
DWORD msgTest(LPVOID lpData);

#endif