// DlgAlarmShow.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgAlarmShow.h"
#include "afxdialogex.h"


// CDlgAlarmShow 对话框

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


// CDlgAlarmShow 消息处理程序


BOOL CDlgAlarmShow::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CtlListAlarm.DeleteAllItems();
	m_CtlListAlarm.InsertColumn(0,"读卡器");
	m_CtlListAlarm.InsertColumn(1,"天线");
	m_CtlListAlarm.InsertColumn(2,"传感器");
	m_CtlListAlarm.InsertColumn(3,"警报时间");
	m_CtlListAlarm.InsertColumn(4,"警报温度");
	m_CtlListAlarm.InsertColumn(5,"警报信息");
	m_CtlListAlarm.SetColumnWidth(0,100);
	m_CtlListAlarm.SetColumnWidth(1,100);
	m_CtlListAlarm.SetColumnWidth(2,100);
	m_CtlListAlarm.SetColumnWidth(3,170);
	m_CtlListAlarm.SetColumnWidth(4,170);
	m_CtlListAlarm.SetColumnWidth(5,170);
	m_CtlListAlarm.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgAlarmShow::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);
	if (m_CtlListAlarm.GetSafeHwnd()) //判断RichEdit控件是否初始化成功   
	{  
		if (nType==SIZE_RESTORED)  
		{  
			CRect rs;  
			GetClientRect(&rs);  //得到父窗体CFormView的大小和位置   
			//m_IPlotCh.SetWindowPos(this,rs.top,rs.left,rs.Width(),rs.Height(),SWP_SHOWWINDOW|SWP_NOZORDER);  
			m_CtlListAlarm.SetWindowPos(NULL,0,0,rs.right,rs.bottom,SWP_SHOWWINDOW | SWP_NOZORDER); //设定控件尺寸，bottom-50是为了让出状态条位置。
			//按照父窗体的大小和位置，将RichEdit控件移到相应的位置   
		}  
	} 

	// TODO: 在此处添加消息处理程序代码
}
