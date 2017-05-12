#pragma once
#include "afxwin.h"
#import "c:\Program Files\Common Files\System\ado\msadox.dll" 
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace \
	rename("EOF","adoEOF")rename("BOF","adoBOF")


// CDlgLogin 对话框

class CDlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogin();

	_ConnectionPtr m_pConnection;
// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheck();
	CButton m_BtnDefault;
	CString SystemIniFilePath;
};
