// MFC_DLL.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "MFC_DLL.h"
#include "MainDialogWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFC_DLLApp

BEGIN_MESSAGE_MAP(CMFC_DLLApp, CWinApp)
END_MESSAGE_MAP()


// CMFC_DLLApp 构造

CMFC_DLLApp::CMFC_DLLApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMFC_DLLApp 对象

CMFC_DLLApp theApp;


// CMFC_DLLApp 初始化
CMainDialogWnd *PMainDialog;

DWORD WINAPI ShowDialog(LPARAM lpData) {
	//添加显示窗口的代码
	PMainDialog = new CMainDialogWnd;
	PMainDialog->DoModal();//阻塞的方式
	
	delete PMainDialog;//释放new分配的空间

	//关闭此窗口后,释放mfc_dll.dll
	FreeLibraryAndExitThread(theApp.m_hInstance, 1);//(GetModuleHandle("mfc_dll.dll"))

	return TRUE;
}

BOOL CMFC_DLLApp::InitInstance()
{
	CWinApp::InitInstance();

	//创建线程启动窗口
	::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ShowDialog, NULL, NULL, NULL);

	return TRUE;
}
