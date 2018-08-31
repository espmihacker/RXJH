// InjectDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

#define GameClasName "D3D Window"
#define dllName "MFC_DLL.dll"

void InjectDll(HWND hGame, const char* dllFullPath) {

	DWORD pid = 0;
	DWORD byWriteSize = NULL;
	HANDLE hProcess = NULL;
	LPDWORD addressDW = NULL;
	HANDLE hThread = NULL;

	if(hGame != 0) {
		//根据游戏句柄获取进程ID
		GetWindowThreadProcessId(hGame, &pid);
		if(pid != 0) {
			//通过进行PID获取进程句柄
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			if(hProcess != NULL) {
				//在游戏进程分配一片内存空间
				addressDW = (LPDWORD)VirtualAllocEx(hProcess, NULL, 256, MEM_COMMIT, PAGE_READWRITE);
				if(addressDW != 0) {
					//写入DLL路径名
					WriteProcessMemory(hProcess, addressDW, dllFullPath, strlen(dllFullPath)+1, &byWriteSize);
					if(byWriteSize >= strlen(dllFullPath)){
						hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, addressDW, NULL, NULL);
						WaitForSingleObject(hThread, 0xFFFFFFFF); //等待注入的dll线程执行完毕
						CloseHandle(hThread);
						VirtualFreeEx(hProcess, addressDW, 256, MEM_COMMIT);
						CloseHandle(hProcess);
					}else{
						printf("error:写入DLL路径失败！");
					}
				}
			}
		}
	}
		
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//获取游戏窗口句柄
	HWND hGame = FindWindow(GameClasName, NULL);

	//获取当前路径
	char dirName[256] = "";
	char dllPath[256] = "";
	GetCurrentDirectoryA(sizeof(dirName), dirName);
	//strcpy_s复制，strcat_s粘贴
	strcpy_s(dllPath, dirName);
	strcat_s(dllPath, "\\");
	strcat_s(dllPath, dllName);

	//printf("%s", dllPath);

	//注入DLL
	InjectDll(hGame, dllPath);

	//getchar();

	return 0;
}

