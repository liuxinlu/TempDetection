#pragma once
#include "afxwin.h"


// CCommEdit �Ի���

class CCommEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CCommEdit)

public:
	CCommEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommEdit();

// �Ի�������
	enum { IDD = IDD_DIALOG_COMMUNICATE };

	int nIndex_comm;
	CString m_baud;
	int nIndex_baud;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
