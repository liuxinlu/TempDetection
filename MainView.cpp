// MainView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "MainView.h"


// CMainView

IMPLEMENT_DYNCREATE(CMainView, CFormView)

CMainView::CMainView()
	: CFormView(CMainView::IDD)
	m_sheet("")
{

}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainView, CFormView)
END_MESSAGE_MAP()


// CMainView ���

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainView ��Ϣ�������
