#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgPosition �Ի���

class CDlgPosition : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPosition)

public:
	CDlgPosition(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPosition();

// �Ի�������
	enum { IDD = IDD_DIALOG_POSITION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CtlListPosition;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonClear();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListPosition(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboListAnt();
	CComboBox m_CtlComboAnt;
	int nIndexAnt;
	int nIndexSensor;
	afx_msg void OnNMClickListPositionReader(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_CtlListReaderPosition;
	int nIndexReader;
	afx_msg void OnBnClickedButtonSaveReader();
	afx_msg void OnBnClickedButtonClearReader();
};
