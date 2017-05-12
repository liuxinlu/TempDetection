// CommEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "CommEdit.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern CString SystemIniFilePath;//����ϵͳ��ز������ļ�
extern bool PortOpenFlag;//true�Ѿ��� falseδ�򿪶˿�
extern bool Menu_Communicate;
extern bool Menu_Exit;
extern bool Menu_StartMem;
extern bool Menu_StopMem;
extern bool Menu_Refresh;
extern bool Menu_Calibration;
extern bool Menu_UserSetPosition;
extern bool Menu_ReaderConfig;
extern bool Menu_PowerControl;
extern bool Menu_UpdateFirmware;
extern bool Menu_FactorySet;
extern bool Menu_UserSet;
extern bool Menu_ModifyReaderID;
extern bool Menu_ScanReader;
extern bool Menu_CtlSingleReader;
extern bool Menu_ShowAlarmHistory;
extern bool Menu_SetAlarmTemp;

extern int LoginDomainSet;//Ȩ�����ñ�־��0Ϊ����Ա��1Ϊһ���û�

// CCommEdit �Ի���

IMPLEMENT_DYNAMIC(CCommEdit, CDialogEx)

CCommEdit::CCommEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommEdit::IDD, pParent)
{

}

CCommEdit::~CCommEdit()
{
}

void CCommEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMM, m_CommSelect);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_CommBaud);
}


BEGIN_MESSAGE_MAP(CCommEdit, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_COMM, &CCommEdit::OnCbnSelchangeComboComm)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, &CCommEdit::OnCbnSelchangeComboBaud)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PORT, &CCommEdit::OnBnClickedButtonOpenPort)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_PORT, &CCommEdit::OnBnClickedButtonClosePort)
END_MESSAGE_MAP()


// CCommEdit ��Ϣ�������


void CCommEdit::OnCbnSelchangeComboComm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndex_comm = m_CommSelect.GetCurSel();
	//��INI�ļ�����Ӽ�ֵ   
	CString StrPort;
	StrPort.Format("%d",nIndex_comm);
	WritePrivateProfileString ("COMM", "Port", StrPort, SystemIniFilePath);   
}


void CCommEdit::OnCbnSelchangeComboBaud()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndex_baud = m_CommBaud.GetCurSel();
	m_CommBaud.GetLBText(nIndex_baud, m_baud);			
	//��INI�ļ�����Ӽ�ֵ   
	CString StrPort;
	StrPort.Format("%d",nIndex_baud);
	WritePrivateProfileString ("COMM", "Baud", StrPort, SystemIniFilePath);   
}


void CCommEdit::OnBnClickedButtonOpenPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��

	if(pMain->m_MSComm.GetPortOpen())	//��������Ǵ򿪵ģ����йرմ���
		pMain->m_MSComm.SetPortOpen(FALSE); 	

	pMain->m_MSComm.SetCommPort(nIndex_comm+1);		//ѡ��COM1
	pMain->m_MSComm.SetInputMode(1);				//�Զ����Ʒ�ʽ��д����
	pMain->m_MSComm.SetInBufferSize(2048);			//���ջ�����
	pMain->m_MSComm.SetOutBufferSize(512);		    //���ͻ�����
	pMain->m_MSComm.SetInputLen(0);				    //���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ
	pMain->m_MSComm.SetRThreshold(1);				//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm�¼�
	pMain->m_MSComm.SetSettings(m_baud+",n,8,1");   //�����ʣ�baud���޼���λ��8������λ��1��ֹͣλ

	if(!pMain->m_MSComm.GetPortOpen())				//�������û�д����
	{	
		try
		{
			pMain->m_MSComm.SetPortOpen(TRUE);		//�򿪴���
			pMain->m_MSComm.SetInBufferCount(0);
			pMain->m_MSComm.GetInput();				//��Ԥ���������������������
			PortOpenFlag=TRUE;

			Menu_StartMem=TRUE;
			Menu_StopMem=FALSE;
			Menu_Refresh=FALSE;
			Menu_ScanReader=TRUE;
			Menu_CtlSingleReader=TRUE;
			Menu_ShowAlarmHistory=TRUE;
			Menu_SetAlarmTemp=TRUE;
			switch (LoginDomainSet)
			{
			case 0:
				Menu_Calibration=TRUE;
				Menu_UserSetPosition=TRUE;
				Menu_ReaderConfig=TRUE;
				Menu_PowerControl=TRUE;
				Menu_UpdateFirmware=TRUE;
				Menu_FactorySet=TRUE;
				Menu_UserSet=TRUE;
				Menu_ModifyReaderID=TRUE;
				break;
			case 1:
				Menu_Calibration=FALSE;
				Menu_UserSetPosition=FALSE;
				Menu_ReaderConfig=FALSE;
				Menu_PowerControl=FALSE;
				Menu_UpdateFirmware=FALSE;
				Menu_FactorySet=FALSE;
				Menu_UserSet=FALSE;
				Menu_ModifyReaderID=FALSE;
				break;
			default:
				break;
			}
			OnOK();
		}
		catch (CException *e)
		{
			AfxMessageBox("���ڲ����ڻ���������ռ�ã����������ô��ڣ�");
			PortOpenFlag=FALSE;
		}	
	}
	else
	{
		AfxMessageBox("�򿪶˿�ʧ�ܣ���ȷ�϶˿���Ϣ!");
		PortOpenFlag=FALSE;
	}
}


void CCommEdit::OnBnClickedButtonClosePort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	////////�رմ���////////////
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
	if(pMain->m_MSComm.GetPortOpen())	//��������Ǵ򿪵ģ����йرմ���
		pMain->m_MSComm.SetPortOpen(FALSE); 	
	PortOpenFlag=FALSE;
}


BOOL CCommEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strPort,strBaud;
	GetPrivateProfileString("COMM", "Port", 0,  strPort.GetBuffer(MAX_PATH),MAX_PATH, SystemIniFilePath);  
	GetPrivateProfileString("COMM", "Baud", 0,  strBaud.GetBuffer(MAX_PATH),MAX_PATH, SystemIniFilePath);  
	CComboBox*   pComb_comm   =   (CComboBox*)GetDlgItem(IDC_COMBO_COMM);   
	ASSERT(pComb_comm);   
	pComb_comm->SetCurSel(atoi(strPort));
	nIndex_comm=atoi(strPort);
	CComboBox*   pComb_baud   =   (CComboBox*)GetDlgItem(IDC_COMBO_BAUD);   
	ASSERT(pComb_baud);   
	pComb_baud->SetCurSel(atoi(strBaud));
	nIndex_baud=atoi(strBaud);
	m_CommBaud.GetLBText(nIndex_baud, m_baud);			

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
