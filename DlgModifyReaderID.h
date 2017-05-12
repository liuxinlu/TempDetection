#pragma once
#include "afxwin.h"


// CDlgModifyReaderID �Ի���

class CDlgModifyReaderID : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgModifyReaderID)

public:
	CDlgModifyReaderID(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgModifyReaderID();

// �Ի�������
	enum { IDD = IDD_DIALOG_MODIFY_READER_ID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_CtlComboReaderOld;
	CComboBox m_CtlComboReaderNew;
	int nIndexReaderOld;
	int nIndexReaderNew;
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnCbnSelchangeComboReaderNew();
	afx_msg void OnCbnSelchangeComboReaderOld();
	virtual BOOL OnInitDialog();
};
