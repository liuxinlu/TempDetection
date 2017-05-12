// DlgAlarmHistory.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgAlarmHistory.h"
#include "afxdialogex.h"
#include "MainFrm.h"
//使用全局变量
extern _ConnectionPtr m_pConnection;


// CDlgAlarmHistory 对话框

IMPLEMENT_DYNAMIC(CDlgAlarmHistory, CDialogEx)

CDlgAlarmHistory::CDlgAlarmHistory(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAlarmHistory::IDD, pParent)
	, m_DataBegin(COleDateTime::GetCurrentTime())
	, m_DataEnding(COleDateTime::GetCurrentTime())
{

}

CDlgAlarmHistory::~CDlgAlarmHistory()
{
}

void CDlgAlarmHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOW_MESSAGE, m_CtlListAlarm);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTTIME, m_DataBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOPTIME, m_DataEnding);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME, m_CtlDateTimeStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STOPTIME, m_CtlDateTimeStopTime);
}


BEGIN_MESSAGE_MAP(CDlgAlarmHistory, CDialogEx)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SHOW_MESSAGE, &CDlgAlarmHistory::OnLvnItemchangedListShowMessage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgAlarmHistory::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CDlgAlarmHistory 消息处理程序


BOOL CDlgAlarmHistory::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CtlListAlarm.DeleteAllItems();
	m_CtlListAlarm.InsertColumn(0,"读卡器");
	m_CtlListAlarm.InsertColumn(1,"天线");
	m_CtlListAlarm.InsertColumn(2,"传感器");
	m_CtlListAlarm.InsertColumn(3,"警报时间");
	m_CtlListAlarm.InsertColumn(4,"警报温度");
	m_CtlListAlarm.InsertColumn(5,"警报信息");
	m_CtlListAlarm.SetColumnWidth(0,70);
	m_CtlListAlarm.SetColumnWidth(1,70);
	m_CtlListAlarm.SetColumnWidth(2,70);
	m_CtlListAlarm.SetColumnWidth(3,130);
	m_CtlListAlarm.SetColumnWidth(4,100);
	m_CtlListAlarm.SetColumnWidth(5,130);
	m_CtlListAlarm.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	m_CtlDateTimeStartTime.SetFormat("yyy-MM-dd HH:mm:ss");
	m_CtlDateTimeStopTime.SetFormat("yyy-MM-dd HH:mm:ss");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDlgAlarmHistory::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString StrStartTime,StrStopTime;
	GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(FALSE);
	StrStartTime.Format("%f",m_DataBegin);
	StrStopTime.Format("%f",m_DataEnding);
	m_CtlListAlarm.DeleteAllItems();
	int count=0;
	_bstr_t bstrSQLdata ="SELECT * FROM DB_Data where Notes='超限警报' and RecordTime<"+StrStopTime+" and RecordTime>"+StrStartTime+" order by DataID;";
	_RecordsetPtr m_pRecordsetch;
	m_pRecordsetch.CreateInstance(__uuidof(Recordset));
	//取得表中记录
	m_pRecordsetch->Open(bstrSQLdata,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	if (!m_pRecordsetch->adoEOF)
	{
		while(!m_pRecordsetch->adoEOF)
		{
			CString Reader=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("ReaderID");
			CString Ant=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("AntID");
			CString Sensor=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("SensorID");
			CString temp=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("Temperature");
			CString time=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("RecordTime");
			Reader.ReleaseBuffer();
			Ant.ReleaseBuffer();
			Sensor.ReleaseBuffer();
			temp.ReleaseBuffer();
			time.ReleaseBuffer();

			COleDateTime t=atof(time);
			CString strTime=t.Format("%Y-%m-%d %H-%M-%S");
			//温度超限警报
			m_CtlListAlarm.InsertItem(count,"");
			m_CtlListAlarm.SetItemText(count,0,Reader);
			m_CtlListAlarm.SetItemText(count,1,Ant);
			m_CtlListAlarm.SetItemText(count,2,Sensor);
			m_CtlListAlarm.SetItemText(count,3,strTime);
			m_CtlListAlarm.SetItemText(count,4,temp);
			m_CtlListAlarm.SetItemText(count,5,"温度超过阈值");
			count++;
			m_pRecordsetch->MoveNext();
		}
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		AfxMessageBox("查询不到数据！");
	}
	m_pRecordsetch->Close();
}
