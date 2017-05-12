#pragma once
#include "afxwin.h"


// CDlgCtlSingleReader 对话框

class CDlgCtlSingleReader : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCtlSingleReader)

public:
	CDlgCtlSingleReader(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCtlSingleReader();

// 对话框数据
	enum { IDD = IDD_DIALOG_CTL_SINGLE_READE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnCbnSelchangeComboReader();
	CComboBox m_CtlComboReader;
	int nIndexReader;
	virtual BOOL OnInitDialog();
};
