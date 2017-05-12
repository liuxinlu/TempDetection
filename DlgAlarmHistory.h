#pragma once
#include "afxcmn.h"
#include "atlcomtime.h"
#include "afxdtctl.h"


// CDlgAlarmHistory 对话框

class CDlgAlarmHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAlarmHistory)

public:
	CDlgAlarmHistory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAlarmHistory();

// 对话框数据
	enum { IDD = IDD_DIALOG_ALARM_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	afx_msg void OnLvnItemchangedListShowMessage(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_CtlListAlarm;
	afx_msg void OnBnClickedButtonSearch();
	COleDateTime m_DataBegin;
	COleDateTime m_DataEnding;
	CDateTimeCtrl m_CtlDateTimeStartTime;
	CDateTimeCtrl m_CtlDateTimeStopTime;
};
