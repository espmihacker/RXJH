#pragma once


// CPageGuaJi �Ի���

class CPageGuaJi : public CDialogEx
{
	DECLARE_DYNAMIC(CPageGuaJi)

public:
	CPageGuaJi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageGuaJi();

// �Ի�������
	enum { IDD = IDD_PAGE_GUAJI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_chk_isAutoAttackMonster;
};
