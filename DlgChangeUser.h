#pragma once


// CDlgChangeUser �Ի���

class CDlgChangeUser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChangeUser)

public:
	CDlgChangeUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChangeUser();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHANGE_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChangeUser();
};
