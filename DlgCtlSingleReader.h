#pragma once
#include "afxwin.h"


// CDlgCtlSingleReader �Ի���

class CDlgCtlSingleReader : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCtlSingleReader)

public:
	CDlgCtlSingleReader(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCtlSingleReader();

// �Ի�������
	enum { IDD = IDD_DIALOG_CTL_SINGLE_READE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnCbnSelchangeComboReader();
	CComboBox m_CtlComboReader;
	int nIndexReader;
	virtual BOOL OnInitDialog();
};
