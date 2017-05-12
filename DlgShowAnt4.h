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

// CDlgShowAnt4 �Ի���

class CDlgShowAnt4 : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgShowAnt4)

public:
	CDlgShowAnt4();
	virtual ~CDlgShowAnt4();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOW_ANT4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTChart m_CtlTChart01;
	CTChart m_CtlTChart02;
	CTChart m_CtlTChart03;
	CTChart m_CtlTChart04;
	CTChart m_CtlTChart05;
	CTChart m_CtlTChart06;
	CTChart m_CtlTChart07;
	CTChart m_CtlTChart08;
	CTChart m_CtlTChart09;
	CTChart m_CtlTChart10;
	CTChart m_CtlTChart11;
	CTChart m_CtlTChart12;
	CTChart m_CtlPowerChart01;
	CTChart m_CtlPowerChart02;
	CTChart m_CtlPowerChart03;
	CTChart m_CtlPowerChart04;
	CTChart m_CtlPowerChart05;
	CTChart m_CtlPowerChart06;
	CTChart m_CtlPowerChart07;
	CTChart m_CtlPowerChart08;
	CTChart m_CtlPowerChart09;
	CTChart m_CtlPowerChart10;
	CTChart m_CtlPowerChart11;
	CTChart m_CtlPowerChart12;
	void ShowData(void);
};
