// MFC_DLL.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "MFC_DLL.h"
#include "MainDialogWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CMFC_DLLApp

BEGIN_MESSAGE_MAP(CMFC_DLLApp, CWinApp)
END_MESSAGE_MAP()


// CMFC_DLLApp ����

CMFC_DLLApp::CMFC_DLLApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFC_DLLApp ����

CMFC_DLLApp theApp;


// CMFC_DLLApp ��ʼ��
CMainDialogWnd *PMainDialog;

DWORD WINAPI ShowDialog(LPARAM lpData) {
	//�����ʾ���ڵĴ���
	PMainDialog = new CMainDialogWnd;
	PMainDialog->DoModal();//�����ķ�ʽ
	
	delete PMainDialog;//�ͷ�new����Ŀռ�

	//�رմ˴��ں�,�ͷ�mfc_dll.dll
	FreeLibraryAndExitThread(theApp.m_hInstance, 1);//(GetModuleHandle("mfc_dll.dll"))

	return TRUE;
}

BOOL CMFC_DLLApp::InitInstance()
{
	CWinApp::InitInstance();

	//�����߳���������
	::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ShowDialog, NULL, NULL, NULL);

	return TRUE;
}
