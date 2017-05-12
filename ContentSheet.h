#pragma once

#include "DlgHistory.h"
#include "DlgMainShow.h"
#include "DlgShowAnt1.h"
#include "DlgShowAnt2.h"
#include "DlgShowAnt3.h"
#include "DlgShowAnt4.h"
#include "DlgAlarmShow.h"
// CContentSheet

class CContentSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CContentSheet)

public:
	CContentSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CContentSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CContentSheet();
public:
	CDlgHistory *pDlgHistory;
	CDlgMainShow *pDlgMainShow;
	CDlgShowAnt1 *pDlgShowAnt1;
	CDlgShowAnt2 *pDlgShowAnt2;
	CDlgShowAnt3 *pDlgShowAnt3;
	CDlgShowAnt4 *pDlgShowAnt4;
	CDlgAlarmShow *pDlgAlarmShow;

	CDlgHistory m_DlgHistory;
	CDlgMainShow m_DlgMainShow;
	CDlgShowAnt1 m_DlgShowAnt1;
	CDlgShowAnt2 m_DlgShowAnt2;
	CDlgShowAnt3 m_DlgShowAnt3;
	CDlgShowAnt4 m_DlgShowAnt4;
	CDlgAlarmShow m_DlgAlarmShow;

protected:
	DECLARE_MESSAGE_MAP()
};


