// InjectDll.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

#define GameClasName "D3D Window"
#define GameCaption "YB_OnlineClient"
#define dllName "MFC_DLL.dll"

void InjectDll(HWND hGame, const char* dllFullPath) {

	DWORD pid = 0;
	DWORD byWriteSize = NULL;
	HANDLE hProcess = NULL;
	LPDWORD addressDW = NULL;
	HANDLE hThread = NULL;

	if(hGame != 0) {
		//������Ϸ�����ȡ����ID
		GetWindowThreadProcessId(hGame, &pid);
		if(pid != 0) {
			//ͨ������PID��ȡ���̾��
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			if(hProcess != NULL) {
				//����Ϸ���̷���һƬ�ڴ�ռ�
				addressDW = (LPDWORD)VirtualAllocEx(hProcess, NULL, 256, MEM_COMMIT, PAGE_READWRITE);
				if(addressDW != 0) {
					//д��DLL·����
					WriteProcessMemory(hProcess, addressDW, dllFullPath, strlen(dllFullPath)+1, &byWriteSize);
					if(byWriteSize >= strlen(dllFullPath)){
						hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, addressDW, NULL, NULL);
						WaitForSingleObject(hThread, 0xFFFFFFFF); //�ȴ�ע���dll�߳�ִ�����
						CloseHandle(hThread);
						VirtualFreeEx(hProcess, addressDW, 256, MEM_COMMIT);
						CloseHandle(hProcess);
					}else{
						printf("error:д��DLL·��ʧ�ܣ�");
					}
				}
			}
		}
	}
		
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//��ȡ��Ϸ���ھ��
	HWND hGame = FindWindow(GameClasName, GameCaption);

	//��ȡ��ǰ·��
	char dirName[256] = "";
	char dllPath[256] = "";
	GetCurrentDirectoryA(sizeof(dirName), dirName);
	//strcpy_s���ƣ�strcat_sճ��
	strcpy_s(dllPath, dirName);
	strcat_s(dllPath, "\\");
	strcat_s(dllPath, dllName);

	//printf("%s", dllPath);

	//ע��DLL
	InjectDll(hGame, dllPath);

	//getchar();

	return 0;
}

