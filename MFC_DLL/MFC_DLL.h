// MFC_DLL.h : MFC_DLL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_DLLApp
// �йش���ʵ�ֵ���Ϣ������� MFC_DLL.cpp
//

class CMFC_DLLApp : public CWinApp
{
public:
	CMFC_DLLApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
