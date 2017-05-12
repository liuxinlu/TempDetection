#pragma once


// CDlgChangeUser 对话框

class CDlgChangeUser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChangeUser)

public:
	CDlgChangeUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChangeUser();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHANGE_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChangeUser();
};
