#pragma once
#include "afxwin.h"


// CDlgSetAlarm 对话框

class CDlgSetAlarm : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetAlarm)

public:
	CDlgSetAlarm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetAlarm();

// 对话框数据
	enum { IDD = IDD_DIALOG_SET_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboReaderId();
	afx_msg void OnBnClickedButtonSaveAlarm();
	afx_msg void OnBnClickedButtonCannecl();
	CComboBox m_CtlComboReader;
	int nIndexReader;
	virtual BOOL OnInitDialog();
};
