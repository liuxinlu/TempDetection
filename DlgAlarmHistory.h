#pragma once
#include "afxcmn.h"
#include "atlcomtime.h"
#include "afxdtctl.h"


// CDlgAlarmHistory �Ի���

class CDlgAlarmHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAlarmHistory)

public:
	CDlgAlarmHistory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAlarmHistory();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALARM_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
