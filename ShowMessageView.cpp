// ShowMessageView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "ShowMessageView.h"

// CShowMessageView

IMPLEMENT_DYNCREATE(CShowMessageView, CFormView)

CShowMessageView::CShowMessageView()
	: CFormView(CShowMessageView::IDD)
{

}

CShowMessageView::~CShowMessageView()
{
}

void CShowMessageView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOW_MESSAGE, m_CtlListAlarm);
}

BEGIN_MESSAGE_MAP(CShowMessageView, CFormView)
	ON_WM_SIZE()
//	ON_NOTIFY(NM_CLICK, IDC_LIST_SHOW_MESSAGE, &CShowMessageView::OnNMClickListShowMessage)
END_MESSAGE_MAP()


// CShowMessageView ���

#ifdef _DEBUG
void CShowMessageView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowMessageView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowMessageView ��Ϣ�������


void CShowMessageView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	this->ShowWindow(SW_MAXIMIZE);

	CWnd *pchild = this->GetWindow(GW_CHILD);//ֻ��һ�������Ӵ���
	if(pchild != NULL){
		CRect rect;
		this->GetWindowRect(&rect);
		pchild->ScreenToClient(&rect);
		pchild->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
			SWP_NOZORDER | SWP_NOACTIVATE);
	}	
}


void CShowMessageView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_CtlListAlarm.DeleteAllItems();
	m_CtlListAlarm.InsertColumn(0,"����λ��");
	m_CtlListAlarm.InsertColumn(1,"����ʱ��");
	m_CtlListAlarm.InsertColumn(2,"�����¶�");
	m_CtlListAlarm.InsertColumn(3,"������Ϣ");
	m_CtlListAlarm.SetColumnWidth(0,250);
	m_CtlListAlarm.SetColumnWidth(1,250);
	m_CtlListAlarm.SetColumnWidth(2,150);
	m_CtlListAlarm.SetColumnWidth(3,160);
	m_CtlListAlarm.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

}


//void CShowMessageView::OnNMClickListShowMessage(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDlgShowAlarmDetail m_dlg;
//	m_dlg.DoModal();
//	*pResult = 0;
//}
