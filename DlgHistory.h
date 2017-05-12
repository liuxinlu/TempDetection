#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "atlcomtime.h"
#include "iplotx.h"
#include "afxwin.h"

// CDlgHistory �Ի���

class CDlgHistory : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgHistory)

public:
	CDlgHistory();
	virtual ~CDlgHistory();

// �Ի�������
	enum { IDD = IDD_DIALOG_HISTORY };

//	int SearchId;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CDateTimeCtrl m_CtlDateTimeStartTime;
	CDateTimeCtrl m_CtlDateTimeStopTime;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	COleDateTime m_DataBegin;
	COleDateTime m_DataEnding;
	CiPlotX m_CtlChart;
	int nIndexAnt;
	int nIndexSensor;
	int nIndexReader;
	CString strReader;
	afx_msg void OnCbnSelchangeComboAnt();
	afx_msg void OnCbnSelchangeComboSensor();
	CComboBox m_CtlComboAnt;
	CComboBox m_CtlComboSensor;
	afx_msg void OnCbnSelchangeComboReader();
	CComboBox m_CtlComboReaderID;
};
