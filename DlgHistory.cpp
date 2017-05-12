// DlgHistory.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgHistory.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "iplotchannelx.h"
#include "iplotaxisx.h"
#include "iplottoolbarx.h"
//ʹ��ȫ�ֱ���
extern _ConnectionPtr m_pConnection;

// CDlgHistory �Ի���

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


// CDlgHistory ��Ϣ�������


void CDlgHistory::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_CtlChart.GetSafeHwnd()) //�ж�RichEdit�ؼ��Ƿ��ʼ���ɹ�   
	{  
		if (nType==SIZE_RESTORED)  
		{  
			CRect rs;  
			GetClientRect(&rs);  //�õ�������CFormView�Ĵ�С��λ��   
			//m_IPlotCh.SetWindowPos(this,rs.top,rs.left,rs.Width(),rs.Height(),SWP_SHOWWINDOW|SWP_NOZORDER);  
			m_CtlChart.SetWindowPos(NULL,0,rs.bottom/8,rs.right,rs.bottom*7/8,SWP_SHOWWINDOW | SWP_NOZORDER); //�趨�ؼ��ߴ磬bottom-50��Ϊ���ó�״̬��λ�á�
			//���ո�����Ĵ�С��λ�ã���RichEdit�ؼ��Ƶ���Ӧ��λ��   
		}  
	} 
}


BOOL CDlgHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_CtlDateTimeStartTime.SetFormat("yyy-MM-dd HH:mm:ss");
	m_CtlDateTimeStopTime.SetFormat("yyy-MM-dd HH:mm:ss");
	strReader="������1";
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgHistory::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(FALSE);
	CString AntID,SensorID,StrStartTime,StrStopTime;
	////////��ʷ��¼�Ļ�ͼģ��///////////////////////////////////////////////////////////////////
	m_CtlChart.GetToolBar(0).DoButtonClickResume();
	m_CtlChart.GetYAxis(0).SetSpan(100);
	m_CtlChart.GetYAxis(0).SetMin(0);
	m_CtlChart.GetXAxis(0).SetMin(72686);
	m_CtlChart.GetXAxis(0).SetSpan(0.00694444444444444);
	m_CtlChart.GetChannel(0).Clear();

	AntID.Format("%d",nIndexAnt+1);
	AntID="����"+AntID;
	SensorID.Format("%d",nIndexSensor+1);
	SensorID="������"+SensorID;
	StrStartTime.Format("%f",m_DataBegin);
	StrStopTime.Format("%f",m_DataEnding);

	_bstr_t bstrSQLdata ="SELECT Temperature,RecordTime FROM DB_Data where ReaderID='"+strReader+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"' and RecordTime<"+StrStopTime+" and RecordTime>"+StrStartTime+" order by DataID;";
	_RecordsetPtr m_pRecordsetch;
	m_pRecordsetch.CreateInstance(__uuidof(Recordset));
	//ȡ�ñ��м�¼
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
		AfxMessageBox("��ѯ�������ݣ�");
	}
	m_pRecordsetch->Close();
}



void CDlgHistory::OnCbnSelchangeComboAnt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexAnt=m_CtlComboAnt.GetCurSel();

}


void CDlgHistory::OnCbnSelchangeComboSensor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexSensor=m_CtlComboSensor.GetCurSel();
}


void CDlgHistory::OnCbnSelchangeComboReader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReader=m_CtlComboReaderID.GetCurSel();
	m_CtlComboReaderID.GetLBText(nIndexReader,strReader);
}
