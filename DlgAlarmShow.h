#pragma once
#include "afxcmn.h"


// CDlgAlarmShow �Ի���

class CDlgAlarmShow : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgAlarmShow)

public:
	CDlgAlarmShow();
	virtual ~CDlgAlarmShow();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_CtlListAlarm;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
