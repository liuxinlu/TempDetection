#pragma once
#include "afxwin.h"


// CDlgPowerControl �Ի���

class CDlgPowerControl : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPowerControl)

public:
	CDlgPowerControl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPowerControl();

// �Ի�������
	enum { IDD = IDD_DIALOG_POWER_CONTROL };

public:
	int nIndexAntID;
	int nIndexSensorID;
	int nIndexPowerID;
	int nIndexReaderID;
	CString strSetPower;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboAnt();
	afx_msg void OnCbnSelchangeComboSensorid();
	afx_msg void OnCbnSelchangeComboRfloss();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonClose();
	CComboBox m_CtlComboAntID;
	CComboBox m_CtlComboRFLoss;
	CComboBox m_CtlComboSensorID;
	CComboBox m_CtlComboReaderID;
	afx_msg void OnCbnSelchangeComboReader();
};
