// ContentSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "ContentSheet.h"


// CContentSheet

IMPLEMENT_DYNAMIC(CContentSheet, CPropertySheet)

CContentSheet::CContentSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CContentSheet::CContentSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	pDlgMainShow=&m_DlgMainShow;
	pDlgShowAnt1=&m_DlgShowAnt1;
	pDlgShowAnt2=&m_DlgShowAnt2;
	pDlgShowAnt3=&m_DlgShowAnt3;
	pDlgShowAnt4=&m_DlgShowAnt4;
	pDlgAlarmShow=&m_DlgAlarmShow;
	pDlgHistory=&m_DlgHistory;
	m_DlgMainShow.m_psp.dwFlags   |=   PSP_PREMATURE;
	AddPage(&m_DlgMainShow);	// First page
	AddPage(&m_DlgShowAnt1);
	AddPage(&m_DlgShowAnt2);
	AddPage(&m_DlgShowAnt3);
	AddPage(&m_DlgShowAnt4);
	AddPage(&m_DlgAlarmShow);
	AddPage(&m_DlgHistory);
}

CContentSheet::~CContentSheet()
{
}


BEGIN_MESSAGE_MAP(CContentSheet, CPropertySheet)
END_MESSAGE_MAP()


// CContentSheet 消息处理程序
