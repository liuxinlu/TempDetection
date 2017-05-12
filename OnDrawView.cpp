// OnDrawView.cpp : implementation file
//

#include "stdafx.h"
#include "TempDetection.h"
#include "OnDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnDrawView

IMPLEMENT_DYNCREATE(COnDrawView, CView)

BEGIN_MESSAGE_MAP(COnDrawView, CView)
//{{AFX_MSG_MAP(contentView)
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnDrawView construction/destruction



COnDrawView::COnDrawView(): m_sheet("")
{
	
}
COnDrawView::~COnDrawView()
{
}
void COnDrawView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


#ifdef _DEBUG
void COnDrawView::AssertValid() const
{
	CView::AssertValid();
}

void COnDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG
void COnDrawView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	pSheet=&m_sheet;

	m_sheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	//使选项卡的按钮在下面
	//::SetWindowLong(m_sheet.GetTabControl()->m_hWnd, GWL_STYLE,
	//	::GetWindowLong(m_sheet.GetTabControl()->m_hWnd, GWL_STYLE) | TCS_RIGHT);
	if(m_sheet.m_hWnd)
		m_sheet.ShowWindow(SW_SHOWMAXIMIZED);//显示选项卡
	
	GetParentFrame()-> ShowWindow(SW_SHOWMAXIMIZED); //最大化
	
}

void COnDrawView::OnSize(UINT nType, int cx, int cy) 
{
	//	CView::OnSize(nType, cx, cy);
	this->ShowWindow(SW_SHOWMAXIMIZED);
	CWnd *psheet = this->GetWindow(GW_CHILD);//m_messageSheet是resultview的唯一顶层子窗口
	if(psheet != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		psheet->ScreenToClient(&rect);
		psheet->SetWindowPos(NULL, 0, 0, rect.Width() , rect.Height() ,
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
		CWnd *ptab = this->m_sheet.GetTabControl();
		if(ptab != NULL)
		{
			ptab->ScreenToClient(&rect);
			ptab->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
				SWP_NOZORDER | SWP_NOACTIVATE);
			
			//让PropertySheet自动调整page的大小
			this->m_sheet.SetActivePage(this->m_sheet.GetActiveIndex());
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CColorView drawing

/////////////////////////////////////////////////////////////////////////////
// COnDrawView message handlers
