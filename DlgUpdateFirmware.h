#pragma once
#include "afxwin.h"


// CDlgUpdateFirmware �Ի���

class CDlgUpdateFirmware : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUpdateFirmware)

public:
	CDlgUpdateFirmware(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUpdateFirmware();

// �Ի�������
	enum { IDD = IDD_DIALOG_UPDATE_FIRMWARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_CtlComboReader;
	int nIndexReader;
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnCbnSelchangeComboReader();
	virtual BOOL OnInitDialog();
};
