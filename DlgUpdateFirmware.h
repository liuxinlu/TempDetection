#pragma once
#include "afxwin.h"


// CDlgUpdateFirmware 对话框

class CDlgUpdateFirmware : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUpdateFirmware)

public:
	CDlgUpdateFirmware(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUpdateFirmware();

// 对话框数据
	enum { IDD = IDD_DIALOG_UPDATE_FIRMWARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_CtlComboReader;
	int nIndexReader;
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnCbnSelchangeComboReader();
	virtual BOOL OnInitDialog();
};
