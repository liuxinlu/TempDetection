#pragma once
#include "afxcmn.h"


// CDlgAlarmShow 对话框

class CDlgAlarmShow : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgAlarmShow)

public:
	CDlgAlarmShow();
	virtual ~CDlgAlarmShow();

// 对话框数据
	enum { IDD = IDD_DIALOG_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_CtlListAlarm;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
