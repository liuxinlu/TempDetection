#pragma once
#include "tchart.h"
#include "axis.h"
#include "axes.h"
#include "scroll.h"
#include "series.h"
#include "gaugeseries.h"
#include "numericgauge.h"
#include "numericmarker.h"
#include "teeshapepanel.h"
#include "teefont.h"
#include "lineargauge.h"
#include "gaugepointerrange.h"
#include "gradient.h"
// CDlgMainShow 对话框

class CDlgMainShow : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgMainShow)

public:
	CDlgMainShow();
	virtual ~CDlgMainShow();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAIN_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTChart m_CtlTChart1_01;
	CTChart m_CtlTChart1_02;
	CTChart m_CtlTChart1_03;
	CTChart m_CtlTChart1_04;
	CTChart m_CtlTChart1_05;
	CTChart m_CtlTChart1_06;
	CTChart m_CtlTChart1_07;
	CTChart m_CtlTChart1_08;
	CTChart m_CtlTChart1_09;
	CTChart m_CtlTChart1_10;
	CTChart m_CtlTChart1_11;
	CTChart m_CtlTChart1_12;
	CTChart m_CtlTChart2_01;
	CTChart m_CtlTChart2_02;
	CTChart m_CtlTChart2_03;
	CTChart m_CtlTChart2_04;
	CTChart m_CtlTChart2_05;
	CTChart m_CtlTChart2_06;
	CTChart m_CtlTChart2_07;
	CTChart m_CtlTChart2_08;
	CTChart m_CtlTChart2_09;
	CTChart m_CtlTChart2_10;
	CTChart m_CtlTChart2_11;
	CTChart m_CtlTChart2_12;
	CTChart m_CtlTChart3_01;
	CTChart m_CtlTChart3_02;
	CTChart m_CtlTChart3_03;
	CTChart m_CtlTChart3_04;
	CTChart m_CtlTChart3_05;
	CTChart m_CtlTChart3_06;
	CTChart m_CtlTChart3_07;
	CTChart m_CtlTChart3_08;
	CTChart m_CtlTChart3_09;
	CTChart m_CtlTChart3_10;
	CTChart m_CtlTChart3_11;
	CTChart m_CtlTChart3_12;
	CTChart m_CtlTChart4_01;
	CTChart m_CtlTChart4_02;
	CTChart m_CtlTChart4_03;
	CTChart m_CtlTChart4_04;
	CTChart m_CtlTChart4_05;
	CTChart m_CtlTChart4_06;
	CTChart m_CtlTChart4_07;
	CTChart m_CtlTChart4_08;
	CTChart m_CtlTChart4_09;
	CTChart m_CtlTChart4_10;
	CTChart m_CtlTChart4_11;
	CTChart m_CtlTChart4_12;


	virtual BOOL OnInitDialog();
	void ShowData(void);
};
