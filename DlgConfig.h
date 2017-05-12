#pragma once
#include "afxwin.h"
#include "IconListBox.h"


// CDlgConfig 对话框

class CDlgConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfig)

public:
	CDlgConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgConfig();
	int nIndex_Ant;
	int nIndexReaderID;
// 对话框数据
	enum { IDD = IDD_DIALOG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnCbnSelchangeComboAnt();
	CComboBox m_CtlComboAnt;
	CButtonST  m_CtlBtnDown;
	CButtonST  m_CtlBtnClose;

	virtual BOOL OnInitDialog();
	CComboBox m_CtlComboReaderID;
	afx_msg void OnCbnSelchangeComboReader();
};
