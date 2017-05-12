#pragma once
#include "afxwin.h"


// CCommEdit 对话框

class CCommEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CCommEdit)

public:
	CCommEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommEdit();

// 对话框数据
	enum { IDD = IDD_DIALOG_COMMUNICATE };

	int nIndex_comm;
	CString m_baud;
	int nIndex_baud;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboComm();
	afx_msg void OnCbnSelchangeComboBaud();
	afx_msg void OnBnClickedButtonOpenPort();
	afx_msg void OnBnClickedButtonClosePort();
	virtual BOOL OnInitDialog();
	CComboBox m_CommSelect;
	CComboBox m_CommBaud;
};
