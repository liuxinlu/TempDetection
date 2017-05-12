
// TempDetectionView.cpp : CTempDetectionView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TempDetection.h"
#endif

#include "TempDetectionDoc.h"
#include "TempDetectionView.h"

extern bool PortOpenFlag;//true已经打开 false未打开端口
extern int UserDefineReader[30];//读卡器使能状态
extern CStringArray strReaderPositionArray;//保存读卡器位置信息30大小
extern int UserSelectReader;//用户选择的读卡器

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTempDetectionView

IMPLEMENT_DYNCREATE(CTempDetectionView, CFormView)

BEGIN_MESSAGE_MAP(CTempDetectionView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_START_MEM, &CTempDetectionView::OnBnClickedButtonStartMem)
	ON_BN_CLICKED(IDC_BUTTON_STOP_MEM, &CTempDetectionView::OnBnClickedButtonStopMem)
	ON_NOTIFY(NM_CLICK, IDC_TREE_WINDOWS, &CTempDetectionView::OnNMClickTreeWindows)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TREE_WINDOWS, &CTempDetectionView::OnNMCustomdrawTreeWindows)
END_MESSAGE_MAP()

// CTempDetectionView 构造/析构

CTempDetectionView::CTempDetectionView()
	: CFormView(CTempDetectionView::IDD)
{
	// TODO: 在此处添加构造代码

}

CTempDetectionView::~CTempDetectionView()
{
}

void CTempDetectionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START_MEM, m_CtlBtnStartMem);
	DDX_Control(pDX, IDC_BUTTON_STOP_MEM, m_CtlBtnStopMem);
	DDX_Control(pDX, IDC_TREE_WINDOWS, m_TreeCtl);
}

BOOL CTempDetectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CTempDetectionView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();

	pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针

	m_CtlBtnStartMem.SetIcon(IDI_ICON_START/*导入的那个icon ID*/);
	m_CtlBtnStartMem.SetFlat(TRUE/*让这个按钮扁平还是立体*/);
	m_CtlBtnStartMem.SetTooltipText("开始测量");
	m_CtlBtnStopMem.SetIcon(IDI_ICON_STOP/*导入的那个icon ID*/);
	m_CtlBtnStopMem.SetFlat(TRUE/*让这个按钮扁平还是立体*/);
	m_CtlBtnStopMem.SetTooltipText("停止测量");

	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);

	m_TreeCtl.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT); //ModifyStyle 设置风格
	HTREEITEM hItem = m_TreeCtl.InsertItem("无源无线温度监控系统",NULL,NULL);///root就是节点的标题 

	for (int i = 0; i < 30; i++)
	{
		if (UserDefineReader[i]==1)
		{
			CString temp=strReaderPositionArray.GetAt(i);
			temp.ReleaseBuffer();
			CString str;
			str.Format("%d",i+1);
			if (i<9)
			{
				HTREEITEM Child_hItem=m_TreeCtl.InsertItem(temp+"(读卡器0"+str+")",NULL,NULL,hItem); 
			}else
			{
				HTREEITEM Child_hItem=m_TreeCtl.InsertItem(temp+"(读卡器"+str+")",NULL,NULL,hItem); 
			}
		}	
	}
	m_TreeCtl.Expand(hItem,TVE_EXPAND); // 展开根节点
	m_TreeCtl.SetFocus();
}

void CTempDetectionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTempDetectionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTempDetectionView 诊断

#ifdef _DEBUG
void CTempDetectionView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTempDetectionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTempDetectionDoc* CTempDetectionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTempDetectionDoc)));
	return (CTempDetectionDoc*)m_pDocument;
}
#endif //_DEBUG


// CTempDetectionView 消息处理程序


void CTempDetectionView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	this->ShowWindow(SW_MAXIMIZE);

	CWnd *pchild = this->GetWindow(GW_CHILD);//只有一个顶层子窗口
	if(pchild != NULL){
		CRect rect;
		this->GetWindowRect(&rect);
		pchild->ScreenToClient(&rect);
		pchild->SetWindowPos(NULL, 0, 100, rect.Width(), rect.Height()-100,
			SWP_NOZORDER | SWP_NOACTIVATE);
	}	
}


void CTempDetectionView::OnBnClickedButtonStartMem()
{
	// TODO: 在此添加控件通知处理程序代码
	pMain->OnStartMem();
}


void CTempDetectionView::OnBnClickedButtonStopMem()
{
	// TODO: 在此添加控件通知处理程序代码
	pMain->OnStopMem();
}

void CTempDetectionView::InitImageLists()
{

	CBitmap bmp;
	// normal tree images
	m_imgNormal.Create(16,
		15,
		TRUE,
		20,	// number of initial images
		20);

	ASSERT(m_imgNormal.m_hImageList);

	bmp.LoadBitmap(IDB_BITMAP2);
	m_imgNormal.Add( &bmp, RGB(255,255,255));
	bmp.DeleteObject();
}

void CTempDetectionView::SetButtonStatus(BOOL Flag)
{
	if (Flag)
	{
		GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(TRUE);
	}else
	{
		GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);
	}
}


void CTempDetectionView::StopMem(void)
{
	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);
}


void CTempDetectionView::StartMem(void)
{
	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(TRUE);
}


void CTempDetectionView::OnNMClickTreeWindows(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CString strSelect;
	/************************** 通过识别控件中鼠标位置获取当前选择项 ***********************************/ 
	// 获取当前选择的项
	CPoint ptCurSel(0,0);
	TVHITTESTINFO HitTestInfo;
	// 通过鼠标在客户区中的位置
	GetCursorPos(&ptCurSel); 
	m_TreeCtl.ScreenToClient(&ptCurSel);   
	// 获取当前选择的是哪一项
	HitTestInfo.pt = ptCurSel;   
	HTREEITEM hSelect = m_TreeCtl.HitTest(&HitTestInfo);

	if(hSelect != NULL)
	{
		str = m_TreeCtl.GetItemText(hSelect);
		//::AfxMessageBox( str); 
	}
	strSelect=str;
	// 设置该项为选中状态 
	m_TreeCtl.SelectItem(hSelect);
	str=str.Right(3);
	str=str.Left(2);
	if (str!="低"&&str!="")
	{
		UserSelectReader=atoi(str);
		pMain->ShowPosition(UserSelectReader-1,TRUE);
		pMain->OnRefresh();
		pMain->ShowAllLastData();
		GetDlgItem(IDC_STATIC_SHOW_SELECT)->SetWindowText("当前显示:"+strSelect);
	}else
	{
		pMain->ShowPosition(UserSelectReader-1,FALSE);
		pMain->OnRefresh();
	}


	*pResult = 0;
}


//void CTempDetectionView::OnNMCustomdrawTreeWindows(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//	if (UserSelectReader>0)
//	{
//		LPNMTVCUSTOMDRAW pDraw=(LPNMTVCUSTOMDRAW)pNMHDR;
//		DWORD dwDrawStage=pDraw->nmcd.dwDrawStage;
//		UINT uItemState =pDraw->nmcd.uItemState;
//		//
//		*pResult=CDRF_NOTIFYITEMDRAW;
//		//|CDRF_NOTIFYPOSTPAINT|CDRF_NOTIFYSUBITEMDRAW|CDRF_NOTIFYPOSTERASE;
//		CDC* pdc=CDC::FromHandle(pDraw->nmcd.hdc);
//		CRect rc;
//		HTREEITEM hItem=(HTREEITEM) pDraw->nmcd.dwItemSpec;
//		m_TreeCtl.GetItemRect(hItem,&rc,FALSE);//FALSE);text only
//		CString txt=m_TreeCtl.GetItemText(hItem);
//		if((dwDrawStage & CDDS_ITEM) && (uItemState & CDIS_SELECTED))
//		{// 
//			pdc->FillSolidRect(&rc,RGB(49,106,197));//clr);
//			//
//			pdc->SetTextColor(RGB(255,255,255));//white
//			pdc->SetBkColor(RGB(49,106,197));//clr);
//			//
//
//			CFont* pfnt=pdc->GetCurrentFont();
//			//
//			pdc->TextOut(rc.left+2,rc.top+2,txt);
//			pdc->SelectObject(pfnt);
//
//			*pResult |= CDRF_SKIPDEFAULT;
//			// afxDump << "1\n";
//		}
//		else // without these ,1st blue !
//		{
//			pdc->FillSolidRect(&rc, GetSysColor(COLOR_WINDOW));
//			pdc->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
//			pdc->TextOut(rc.left+2, rc.top+2, txt);
//			// afxDump << "2\n";
//		}
//	}
//}
