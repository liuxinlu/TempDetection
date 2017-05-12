// DlgChangeUser.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgChangeUser.h"
#include "afxdialogex.h"
#include "MainFrm.h"
extern _ConnectionPtr m_pConnection;
extern int LoginDomainSet;//权限设置标志，0为管理员，1为一般用户
extern CString LoginName;
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

// CDlgChangeUser 对话框

IMPLEMENT_DYNAMIC(CDlgChangeUser, CDialogEx)

CDlgChangeUser::CDlgChangeUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChangeUser::IDD, pParent)
{

}

CDlgChangeUser::~CDlgChangeUser()
{
}

void CDlgChangeUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgChangeUser, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_USER, &CDlgChangeUser::OnBnClickedButtonChangeUser)
END_MESSAGE_MAP()


// CDlgChangeUser 消息处理程序


void CDlgChangeUser::OnBnClickedButtonChangeUser()
{
	// TODO: 在此添加控件通知处理程序代码
	CString StrName,StrPassword;
	GetDlgItem(IDC_EDIT_USER_NAME)->GetWindowTextA(StrName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowTextA(StrPassword);
	_bstr_t bstrSQL ="SELECT UserPassword,Domain FROM db_user where UserName='"+StrName+"'";
	_RecordsetPtr m_pRecordset1;
	m_pRecordset1.CreateInstance(__uuidof(Recordset));
	//取得表中记录
	m_pRecordset1->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	if(!m_pRecordset1->adoEOF)
	{
		CString pass=m_pRecordset1->GetCollect("UserPassword");
		if (!pass.Compare(StrPassword))
		{
			CString domain=m_pRecordset1->GetCollect("Domain");
			LoginDomainSet=atoi(domain);
			LoginName=StrName;
			//设置状态栏显示登陆用户名
			CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
			pMain->SetStatusBar(2,"登录用户"+LoginName); 

			switch (LoginDomainSet)
			{
			case 0:
				Menu_Communicate=TRUE;
				Menu_Exit=TRUE;
				Menu_StartMem=TRUE;
				Menu_StopMem=TRUE;
				Menu_Refresh=TRUE;
				Menu_Calibration=TRUE;
				Menu_UserSetPosition=TRUE;
				Menu_ReaderConfig=TRUE;
				Menu_PowerControl=TRUE;
				Menu_UpdateFirmware=TRUE;
				Menu_FactorySet=TRUE;
				Menu_UserSet=TRUE;
				Menu_ScanReader=TRUE;
				Menu_CtlSingleReader=TRUE;
				Menu_ShowAlarmHistory=TRUE;
				Menu_SetAlarmTemp=TRUE;
				Menu_ModifyReaderID=TRUE;
				break;
			case 1:
				Menu_Communicate=TRUE;
				Menu_Exit=TRUE;
				Menu_StartMem=TRUE;
				Menu_StopMem=TRUE;
				Menu_Refresh=TRUE;
				Menu_Calibration=FALSE;
				Menu_UserSetPosition=FALSE;
				Menu_ReaderConfig=FALSE;
				Menu_PowerControl=FALSE;
				Menu_UpdateFirmware=FALSE;
				Menu_FactorySet=FALSE;
				Menu_UserSet=FALSE;
				Menu_ScanReader=TRUE;
				Menu_CtlSingleReader=TRUE;
				Menu_ShowAlarmHistory=TRUE;
				Menu_SetAlarmTemp=TRUE;
				Menu_ModifyReaderID=FALSE;
				break;
			default:
				break;
			}
			OnOK();
		}else
		{
			AfxMessageBox("请输入正确的密码！");
		}		
	}else
	{
		AfxMessageBox("请输入正确的用户名！");
	}
}
