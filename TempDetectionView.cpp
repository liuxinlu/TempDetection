
// TempDetectionView.cpp : CTempDetectionView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "TempDetection.h"
#endif

#include "TempDetectionDoc.h"
#include "TempDetectionView.h"

extern bool PortOpenFlag;//true�Ѿ��� falseδ�򿪶˿�
extern int UserDefineReader[30];//������ʹ��״̬
extern CStringArray strReaderPositionArray;//���������λ����Ϣ30��С
extern int UserSelectReader;//�û�ѡ��Ķ�����

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

// CTempDetectionView ����/����

CTempDetectionView::CTempDetectionView()
	: CFormView(CTempDetectionView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CTempDetectionView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();

	pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��

	m_CtlBtnStartMem.SetIcon(IDI_ICON_START/*������Ǹ�icon ID*/);
	m_CtlBtnStartMem.SetFlat(TRUE/*�������ť��ƽ��������*/);
	m_CtlBtnStartMem.SetTooltipText("��ʼ����");
	m_CtlBtnStopMem.SetIcon(IDI_ICON_STOP/*������Ǹ�icon ID*/);
	m_CtlBtnStopMem.SetFlat(TRUE/*�������ť��ƽ��������*/);
	m_CtlBtnStopMem.SetTooltipText("ֹͣ����");

	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);

	m_TreeCtl.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT); //ModifyStyle ���÷��
	HTREEITEM hItem = m_TreeCtl.InsertItem("��Դ�����¶ȼ��ϵͳ",NULL,NULL);///root���ǽڵ�ı��� 

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
				HTREEITEM Child_hItem=m_TreeCtl.InsertItem(temp+"(������0"+str+")",NULL,NULL,hItem); 
			}else
			{
				HTREEITEM Child_hItem=m_TreeCtl.InsertItem(temp+"(������"+str+")",NULL,NULL,hItem); 
			}
		}	
	}
	m_TreeCtl.Expand(hItem,TVE_EXPAND); // չ�����ڵ�
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


// CTempDetectionView ���

#ifdef _DEBUG
void CTempDetectionView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTempDetectionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTempDetectionDoc* CTempDetectionView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTempDetectionDoc)));
	return (CTempDetectionDoc*)m_pDocument;
}
#endif //_DEBUG


// CTempDetectionView ��Ϣ�������


void CTempDetectionView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	this->ShowWindow(SW_MAXIMIZE);

	CWnd *pchild = this->GetWindow(GW_CHILD);//ֻ��һ�������Ӵ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pMain->OnStartMem();
}


void CTempDetectionView::OnBnClickedButtonStopMem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	CString strSelect;
	/************************** ͨ��ʶ��ؼ������λ�û�ȡ��ǰѡ���� ***********************************/ 
	// ��ȡ��ǰѡ�����
	CPoint ptCurSel(0,0);
	TVHITTESTINFO HitTestInfo;
	// ͨ������ڿͻ����е�λ��
	GetCursorPos(&ptCurSel); 
	m_TreeCtl.ScreenToClient(&ptCurSel);   
	// ��ȡ��ǰѡ�������һ��
	HitTestInfo.pt = ptCurSel;   
	HTREEITEM hSelect = m_TreeCtl.HitTest(&HitTestInfo);

	if(hSelect != NULL)
	{
		str = m_TreeCtl.GetItemText(hSelect);
		//::AfxMessageBox( str); 
	}
	strSelect=str;
	// ���ø���Ϊѡ��״̬ 
	m_TreeCtl.SelectItem(hSelect);
	str=str.Right(3);
	str=str.Left(2);
	if (str!="��"&&str!="")
	{
		UserSelectReader=atoi(str);
		pMain->ShowPosition(UserSelectReader-1,TRUE);
		pMain->OnRefresh();
		pMain->ShowAllLastData();
		GetDlgItem(IDC_STATIC_SHOW_SELECT)->SetWindowText("��ǰ��ʾ:"+strSelect);
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
