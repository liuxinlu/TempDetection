// DlgAlarmShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgAlarmShow.h"
#include "afxdialogex.h"


// CDlgAlarmShow �Ի���

IMPLEMENT_DYNAMIC(CDlgAlarmShow, CPropertyPage)

CDlgAlarmShow::CDlgAlarmShow()
	: CPropertyPage(CDlgAlarmShow::IDD)
{

}

CDlgAlarmShow::~CDlgAlarmShow()
{
}

void CDlgAlarmShow::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOW_MESSAGE, m_CtlListAlarm);
}


BEGIN_MESSAGE_MAP(CDlgAlarmShow, CPropertyPage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgAlarmShow ��Ϣ�������


BOOL CDlgAlarmShow::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_CtlListAlarm.DeleteAllItems();
	m_CtlListAlarm.InsertColumn(0,"������");
	m_CtlListAlarm.InsertColumn(1,"����");
	m_CtlListAlarm.InsertColumn(2,"������");
	m_CtlListAlarm.InsertColumn(3,"����ʱ��");
	m_CtlListAlarm.InsertColumn(4,"�����¶�");
	m_CtlListAlarm.InsertColumn(5,"������Ϣ");
	m_CtlListAlarm.SetColumnWidth(0,100);
	m_CtlListAlarm.SetColumnWidth(1,100);
	m_CtlListAlarm.SetColumnWidth(2,100);
	m_CtlListAlarm.SetColumnWidth(3,170);
	m_CtlListAlarm.SetColumnWidth(4,170);
	m_CtlListAlarm.SetColumnWidth(5,170);
	m_CtlListAlarm.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgAlarmShow::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);
	if (m_CtlListAlarm.GetSafeHwnd()) //�ж�RichEdit�ؼ��Ƿ��ʼ���ɹ�   
	{  
		if (nType==SIZE_RESTORED)  
		{  
			CRect rs;  
			GetClientRect(&rs);  //�õ�������CFormView�Ĵ�С��λ��   
			//m_IPlotCh.SetWindowPos(this,rs.top,rs.left,rs.Width(),rs.Height(),SWP_SHOWWINDOW|SWP_NOZORDER);  
			m_CtlListAlarm.SetWindowPos(NULL,0,0,rs.right,rs.bottom,SWP_SHOWWINDOW | SWP_NOZORDER); //�趨�ؼ��ߴ磬bottom-50��Ϊ���ó�״̬��λ�á�
			//���ո�����Ĵ�С��λ�ã���RichEdit�ؼ��Ƶ���Ӧ��λ��   
		}  
	} 

	// TODO: �ڴ˴������Ϣ����������
}
