// ShowMessageView.cpp : 实现文件
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


// CShowMessageView 诊断

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


// CShowMessageView 消息处理程序


void CShowMessageView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	this->ShowWindow(SW_MAXIMIZE);

	CWnd *pchild = this->GetWindow(GW_CHILD);//只有一个顶层子窗口
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

	// TODO: 在此添加专用代码和/或调用基类
	m_CtlListAlarm.DeleteAllItems();
	m_CtlListAlarm.InsertColumn(0,"警报位置");
	m_CtlListAlarm.InsertColumn(1,"警报时间");
	m_CtlListAlarm.InsertColumn(2,"警报温度");
	m_CtlListAlarm.InsertColumn(3,"警报信息");
	m_CtlListAlarm.SetColumnWidth(0,250);
	m_CtlListAlarm.SetColumnWidth(1,250);
	m_CtlListAlarm.SetColumnWidth(2,150);
	m_CtlListAlarm.SetColumnWidth(3,160);
	m_CtlListAlarm.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

}


//void CShowMessageView::OnNMClickListShowMessage(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	CDlgShowAlarmDetail m_dlg;
//	m_dlg.DoModal();
//	*pResult = 0;
//}
