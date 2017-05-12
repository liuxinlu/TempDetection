// DlgPowerControl.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgPowerControl.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern bool PortOpenFlag;//true已经打开 false未打开端口
extern int SensorPowerSet[30][4][12];//保存传感器衰减值

char PowerSetCMD[15]    ={0x00,0x45,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//衰减

// CDlgPowerControl 对话框

IMPLEMENT_DYNAMIC(CDlgPowerControl, CDialogEx)

CDlgPowerControl::CDlgPowerControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPowerControl::IDD, pParent)
{

}

CDlgPowerControl::~CDlgPowerControl()
{
}

void CDlgPowerControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ANT, m_CtlComboAntID);
	DDX_Control(pDX, IDC_COMBO_RFLOSS, m_CtlComboRFLoss);
	DDX_Control(pDX, IDC_COMBO_SENSORID, m_CtlComboSensorID);
	DDX_Control(pDX, IDC_COMBO_READER, m_CtlComboReaderID);
}


BEGIN_MESSAGE_MAP(CDlgPowerControl, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_ANT, &CDlgPowerControl::OnCbnSelchangeComboAnt)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSORID, &CDlgPowerControl::OnCbnSelchangeComboSensorid)
	ON_CBN_SELCHANGE(IDC_COMBO_RFLOSS, &CDlgPowerControl::OnCbnSelchangeComboRfloss)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgPowerControl::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgPowerControl::OnBnClickedButtonClose)
	ON_CBN_SELCHANGE(IDC_COMBO_READER, &CDlgPowerControl::OnCbnSelchangeComboReader)
END_MESSAGE_MAP()


// CDlgPowerControl 消息处理程序


BOOL CDlgPowerControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	nIndexAntID=0;
	nIndexSensorID=0;
	nIndexReaderID=0;
	strSetPower="00";
	CComboBox*   pComb_Ant   =   (CComboBox*)GetDlgItem(IDC_COMBO_ANT);   
	ASSERT(pComb_Ant);   
	pComb_Ant->SetCurSel(nIndexAntID);
	CComboBox*   pComb_Sensor   =   (CComboBox*)GetDlgItem(IDC_COMBO_SENSORID);   
	ASSERT(pComb_Sensor);   
	pComb_Sensor->SetCurSel(nIndexSensorID);
	nIndexPowerID=SensorPowerSet[nIndexReaderID][nIndexAntID][nIndexSensorID];
	CComboBox*   pComb_Power   =   (CComboBox*)GetDlgItem(IDC_COMBO_RFLOSS);   
	ASSERT(pComb_Power);   
	pComb_Power->SetCurSel(nIndexPowerID);
	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndexReaderID);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgPowerControl::OnCbnSelchangeComboAnt()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexAntID = m_CtlComboAntID.GetCurSel();	
	nIndexPowerID=SensorPowerSet[nIndexReaderID][nIndexAntID][nIndexSensorID];
	CComboBox*   pComb_Power   =   (CComboBox*)GetDlgItem(IDC_COMBO_RFLOSS);   
	ASSERT(pComb_Power);   
	pComb_Power->SetCurSel(nIndexPowerID);
}


void CDlgPowerControl::OnCbnSelchangeComboSensorid()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexSensorID = m_CtlComboSensorID.GetCurSel();	
	nIndexPowerID=SensorPowerSet[nIndexReaderID][nIndexAntID][nIndexSensorID];
	CComboBox*   pComb_Power   =   (CComboBox*)GetDlgItem(IDC_COMBO_RFLOSS);   
	ASSERT(pComb_Power);   
	pComb_Power->SetCurSel(nIndexPowerID);
}


void CDlgPowerControl::OnCbnSelchangeComboRfloss()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexPowerID = m_CtlComboRFLoss.GetCurSel();	
	m_CtlComboRFLoss.GetLBText(nIndexPowerID,strSetPower);
}


void CDlgPowerControl::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取串口指针
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	CString str1,str2,str3,str4;
	str1.Format("%d",nIndexReaderID+1);
	str2.Format("%d",nIndexAntID+1);
	str3.Format("%d",nIndexSensorID+1);
	str4.Format("%d",nIndexPowerID);

	if (PortOpenFlag)
	{
		PowerSetCMD[0]=(char)(nIndexReaderID+1);
		PowerSetCMD[2]=(char)(nIndexAntID+1);
		PowerSetCMD[3]=(char)(nIndexSensorID+1);
		PowerSetCMD[4]=(char)atoi(strSetPower);
		pMain->SendCMD(PowerSetCMD);
		SensorPowerSet[nIndexReaderID][nIndexAntID][nIndexSensorID]=nIndexPowerID;
		pMain->UpdateSensorPower(str1,str2,str3,str4);
	} 
	else
	{
		AfxMessageBox("请先打开端口，再进行控制操作！");
	}
}


void CDlgPowerControl::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CDlgPowerControl::OnCbnSelchangeComboReader()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexReaderID = m_CtlComboReaderID.GetCurSel();	
	nIndexPowerID=SensorPowerSet[nIndexReaderID][nIndexAntID][nIndexSensorID];
	CComboBox*   pComb_Power   =   (CComboBox*)GetDlgItem(IDC_COMBO_RFLOSS);   
	ASSERT(pComb_Power);   
	pComb_Power->SetCurSel(nIndexPowerID);
}
