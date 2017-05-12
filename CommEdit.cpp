// CommEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "CommEdit.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern CString SystemIniFilePath;//保存系统相关参数的文件
extern bool PortOpenFlag;//true已经打开 false未打开端口
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

extern int LoginDomainSet;//权限设置标志，0为管理员，1为一般用户

// CCommEdit 对话框

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


// CCommEdit 消息处理程序


void CCommEdit::OnCbnSelchangeComboComm()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndex_comm = m_CommSelect.GetCurSel();
	//向INI文件中添加键值   
	CString StrPort;
	StrPort.Format("%d",nIndex_comm);
	WritePrivateProfileString ("COMM", "Port", StrPort, SystemIniFilePath);   
}


void CCommEdit::OnCbnSelchangeComboBaud()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndex_baud = m_CommBaud.GetCurSel();
	m_CommBaud.GetLBText(nIndex_baud, m_baud);			
	//向INI文件中添加键值   
	CString StrPort;
	StrPort.Format("%d",nIndex_baud);
	WritePrivateProfileString ("COMM", "Baud", StrPort, SystemIniFilePath);   
}


void CCommEdit::OnBnClickedButtonOpenPort()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针

	if(pMain->m_MSComm.GetPortOpen())	//如果串口是打开的，则行关闭串口
		pMain->m_MSComm.SetPortOpen(FALSE); 	

	pMain->m_MSComm.SetCommPort(nIndex_comm+1);		//选择COM1
	pMain->m_MSComm.SetInputMode(1);				//以二进制方式读写数据
	pMain->m_MSComm.SetInBufferSize(2048);			//接收缓冲区
	pMain->m_MSComm.SetOutBufferSize(512);		    //发送缓冲区
	pMain->m_MSComm.SetInputLen(0);				    //设置当前接收区数据长度为0,表示全部读取
	pMain->m_MSComm.SetRThreshold(1);				//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm事件
	pMain->m_MSComm.SetSettings(m_baud+",n,8,1");   //波特率：baud，无检验位，8个数据位，1个停止位

	if(!pMain->m_MSComm.GetPortOpen())				//如果串口没有打开则打开
	{	
		try
		{
			pMain->m_MSComm.SetPortOpen(TRUE);		//打开串口
			pMain->m_MSComm.SetInBufferCount(0);
			pMain->m_MSComm.GetInput();				//先预读缓冲区以清除残留数据
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
			AfxMessageBox("串口不存在或被其他程序占用，请重新设置串口！");
			PortOpenFlag=FALSE;
		}	
	}
	else
	{
		AfxMessageBox("打开端口失败，请确认端口信息!");
		PortOpenFlag=FALSE;
	}
}


void CCommEdit::OnBnClickedButtonClosePort()
{
	// TODO: 在此添加控件通知处理程序代码
	////////关闭串口////////////
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	if(pMain->m_MSComm.GetPortOpen())	//如果串口是打开的，则行关闭串口
		pMain->m_MSComm.SetPortOpen(FALSE); 	
	PortOpenFlag=FALSE;
}


BOOL CCommEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	// 异常: OCX 属性页应返回 FALSE
}
