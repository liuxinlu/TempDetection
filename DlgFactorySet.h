#pragma once
#include "afxwin.h"


// CDlgFactorySet �Ի���

class CDlgFactorySet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFactorySet)

public:
	CDlgFactorySet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFactorySet();

// �Ի�������
	enum { IDD = IDD_DIALOG_FACTORY_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButtonSendFreq();
	afx_msg void OnBnClickedButtonReceiveFreq();
	afx_msg void OnCbnSelchangeComboAntId1();
	afx_msg void OnCbnSelchangeComboAntId2();
	int nIndexAnt1;
	int nIndexAnt2;
	int nindexReaderSend;
	int nIndexReaderRecv;
	int nIndexSynchronous;

	virtual BOOL OnInitDialog();
	CComboBox m_CtlComboAnt1;
	CComboBox m_CtlComboAnt2;
	CComboBox m_CtlComboReaderSend;
	CComboBox m_CtlComboReaderRecv;
	afx_msg void OnCbnSelchangeComboReaderRecv();
	afx_msg void OnCbnSelchangeComboReaderSend();
	afx_msg void OnBnClickedButtonSaveLoopTime();
	afx_msg void OnCbnSelchangeComboSynchronous();
	CComboBox m_CtlComboSynchronous;
	afx_msg void OnBnClickedButtonSaveSynchronous();
};
