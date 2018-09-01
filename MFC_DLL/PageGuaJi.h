#pragma once


// CPageGuaJi 对话框

class CPageGuaJi : public CDialogEx
{
	DECLARE_DYNAMIC(CPageGuaJi)

public:
	CPageGuaJi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPageGuaJi();

// 对话框数据
	enum { IDD = IDD_PAGE_GUAJI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_chk_isAutoAttackMonster;
};
