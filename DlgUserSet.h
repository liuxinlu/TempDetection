#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgUserSet 对话框

class CDlgUserSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUserSet)

public:
	CDlgUserSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUserSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_USER_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CtlListUser;
	afx_msg void OnBnClickedButtonListAll();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonAlert();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedCheckAdmin();
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_CtlCheckAdmin;
	virtual BOOL OnInitDialog();
	CString SelectUser;
};
