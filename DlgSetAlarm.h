#pragma once
#include "afxwin.h"


// CDlgSetAlarm �Ի���

class CDlgSetAlarm : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetAlarm)

public:
	CDlgSetAlarm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetAlarm();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboReaderId();
	afx_msg void OnBnClickedButtonSaveAlarm();
	afx_msg void OnBnClickedButtonCannecl();
	CComboBox m_CtlComboReader;
	int nIndexReader;
	virtual BOOL OnInitDialog();
};
