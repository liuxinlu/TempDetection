// DlgHistory.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgHistory.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "iplotchannelx.h"
#include "iplotaxisx.h"
#include "iplottoolbarx.h"
//使用全局变量
extern _ConnectionPtr m_pConnection;

// CDlgHistory 对话框

IMPLEMENT_DYNAMIC(CDlgHistory, CPropertyPage)

CDlgHistory::CDlgHistory()
	: CPropertyPage(CDlgHistory::IDD)
	, m_DataBegin(COleDateTime::GetCurrentTime())
	, m_DataEnding(COleDateTime::GetCurrentTime())
{

}

CDlgHistory::~CDlgHistory()
{
}

void CDlgHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME, m_CtlDateTimeStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STOPTIME, m_CtlDateTimeStopTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTTIME, m_DataBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOPTIME, m_DataEnding);
	DDX_Control(pDX,IDC_TCHART_HISTORY,m_CtlChart);
	DDX_Control(pDX, IDC_COMBO_ANT, m_CtlComboAnt);
	DDX_Control(pDX, IDC_COMBO_SENSOR, m_CtlComboSensor);
	DDX_Control(pDX, IDC_COMBO_READER, m_CtlComboReaderID);
}


BEGIN_MESSAGE_MAP(CDlgHistory, CPropertyPage)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgHistory::OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_ANT, &CDlgHistory::OnCbnSelchangeComboAnt)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR, &CDlgHistory::OnCbnSelchangeComboSensor)
	ON_CBN_SELCHANGE(IDC_COMBO_READER, &CDlgHistory::OnCbnSelchangeComboReader)
END_MESSAGE_MAP()


// CDlgHistory 消息处理程序


void CDlgHistory::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_CtlChart.GetSafeHwnd()) //判断RichEdit控件是否初始化成功   
	{  
		if (nType==SIZE_RESTORED)  
		{  
			CRect rs;  
			GetClientRect(&rs);  //得到父窗体CFormView的大小和位置   
			//m_IPlotCh.SetWindowPos(this,rs.top,rs.left,rs.Width(),rs.Height(),SWP_SHOWWINDOW|SWP_NOZORDER);  
			m_CtlChart.SetWindowPos(NULL,0,rs.bottom/8,rs.right,rs.bottom*7/8,SWP_SHOWWINDOW | SWP_NOZORDER); //设定控件尺寸，bottom-50是为了让出状态条位置。
			//按照父窗体的大小和位置，将RichEdit控件移到相应的位置   
		}  
	} 
}


BOOL CDlgHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CtlDateTimeStartTime.SetFormat("yyy-MM-dd HH:mm:ss");
	m_CtlDateTimeStopTime.SetFormat("yyy-MM-dd HH:mm:ss");
	strReader="读卡器1";
	nIndexReader=0;
	nIndexAnt=0;
	nIndexSensor=0;
	CComboBox*   pComb_Ant   =   (CComboBox*)GetDlgItem(IDC_COMBO_ANT);   
	ASSERT(pComb_Ant);   
	pComb_Ant->SetCurSel(nIndexAnt);
	CComboBox*   pComb_Sensor   =   (CComboBox*)GetDlgItem(IDC_COMBO_SENSOR);   
	ASSERT(pComb_Sensor);   
	pComb_Sensor->SetCurSel(nIndexSensor);
	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndexReader);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgHistory::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(FALSE);
	CString AntID,SensorID,StrStartTime,StrStopTime;
	////////历史记录的画图模块///////////////////////////////////////////////////////////////////
	m_CtlChart.GetToolBar(0).DoButtonClickResume();
	m_CtlChart.GetYAxis(0).SetSpan(100);
	m_CtlChart.GetYAxis(0).SetMin(0);
	m_CtlChart.GetXAxis(0).SetMin(72686);
	m_CtlChart.GetXAxis(0).SetSpan(0.00694444444444444);
	m_CtlChart.GetChannel(0).Clear();

	AntID.Format("%d",nIndexAnt+1);
	AntID="天线"+AntID;
	SensorID.Format("%d",nIndexSensor+1);
	SensorID="传感器"+SensorID;
	StrStartTime.Format("%f",m_DataBegin);
	StrStopTime.Format("%f",m_DataEnding);

	_bstr_t bstrSQLdata ="SELECT Temperature,RecordTime FROM DB_Data where ReaderID='"+strReader+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"' and RecordTime<"+StrStopTime+" and RecordTime>"+StrStartTime+" order by DataID;";
	_RecordsetPtr m_pRecordsetch;
	m_pRecordsetch.CreateInstance(__uuidof(Recordset));
	//取得表中记录
	m_pRecordsetch->Open(bstrSQLdata,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	if (!m_pRecordsetch->adoEOF)
	{
		while(!m_pRecordsetch->adoEOF)
		{
			CString temper=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("Temperature");
			CString time=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("RecordTime");
			temper.ReleaseBuffer();
			m_CtlChart.GetChannel(0).AddXY(atof(time), atof(temper));
			m_pRecordsetch->MoveNext();
		}
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		m_CtlChart.GetYAxis(0).ZoomToFitFast();
	} 
	else
	{
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		AfxMessageBox("查询不到数据！");
	}
	m_pRecordsetch->Close();
}



void CDlgHistory::OnCbnSelchangeComboAnt()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexAnt=m_CtlComboAnt.GetCurSel();

}


void CDlgHistory::OnCbnSelchangeComboSensor()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexSensor=m_CtlComboSensor.GetCurSel();
}


void CDlgHistory::OnCbnSelchangeComboReader()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexReader=m_CtlComboReaderID.GetCurSel();
	m_CtlComboReaderID.GetLBText(nIndexReader,strReader);
}
