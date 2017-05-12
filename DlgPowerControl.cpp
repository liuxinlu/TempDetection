// DlgPowerControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgPowerControl.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern bool PortOpenFlag;//true�Ѿ��� falseδ�򿪶˿�
extern int SensorPowerSet[30][4][12];//���洫����˥��ֵ

char PowerSetCMD[15]    ={0x00,0x45,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//˥��

// CDlgPowerControl �Ի���

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


// CDlgPowerControl ��Ϣ�������


BOOL CDlgPowerControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgPowerControl::OnCbnSelchangeComboAnt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexAntID = m_CtlComboAntID.GetCurSel();	
	nIndexPowerID=SensorPowerSet[nIndexReaderID][nIndexAntID][nIndexSensorID];
	CComboBox*   pComb_Power   =   (CComboBox*)GetDlgItem(IDC_COMBO_RFLOSS);   
	ASSERT(pComb_Power);   
	pComb_Power->SetCurSel(nIndexPowerID);
}


void CDlgPowerControl::OnCbnSelchangeComboSensorid()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexSensorID = m_CtlComboSensorID.GetCurSel();	
	nIndexPowerID=SensorPowerSet[nIndexReaderID][nIndexAntID][nIndexSensorID];
	CComboBox*   pComb_Power   =   (CComboBox*)GetDlgItem(IDC_COMBO_RFLOSS);   
	ASSERT(pComb_Power);   
	pComb_Power->SetCurSel(nIndexPowerID);
}


void CDlgPowerControl::OnCbnSelchangeComboRfloss()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexPowerID = m_CtlComboRFLoss.GetCurSel();	
	m_CtlComboRFLoss.GetLBText(nIndexPowerID,strSetPower);
}


void CDlgPowerControl::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ����ָ��
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
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
		AfxMessageBox("���ȴ򿪶˿ڣ��ٽ��п��Ʋ�����");
	}
}


void CDlgPowerControl::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void CDlgPowerControl::OnCbnSelchangeComboReader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReaderID = m_CtlComboReaderID.GetCurSel();	
	nIndexPowerID=SensorPowerSet[nIndexReaderID][nIndexAntID][nIndexSensorID];
	CComboBox*   pComb_Power   =   (CComboBox*)GetDlgItem(IDC_COMBO_RFLOSS);   
	ASSERT(pComb_Power);   
	pComb_Power->SetCurSel(nIndexPowerID);
}
