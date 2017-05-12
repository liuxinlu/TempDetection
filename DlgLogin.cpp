// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgLogin.h"
#include "afxdialogex.h"
#include "MainFrm.h"
extern int LoginDomainSet;//Ȩ�����ñ�־��0Ϊ����Ա��1Ϊһ���û�
extern CString LoginName;

// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogin::IDD, pParent)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DEFAULT, m_BtnDefault);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CDlgLogin::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_CHECK_, &CDlgLogin::OnBnClickedCheck)
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������


void CDlgLogin::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString StrName,StrPassword;
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowTextA(StrName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowTextA(StrPassword);
	_bstr_t bstrSQL ="SELECT UserPassword,Domain FROM db_user where UserName='"+StrName+"'";
	_RecordsetPtr m_pRecordset1;
	m_pRecordset1.CreateInstance(__uuidof(Recordset));
	//ȡ�ñ��м�¼
	m_pRecordset1->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	if(!m_pRecordset1->adoEOF)
	{
		CString pass=m_pRecordset1->GetCollect("UserPassword");
		if (!pass.Compare(StrPassword))
		{
			CString domain=m_pRecordset1->GetCollect("Domain");
			LoginDomainSet=atoi(domain);
			LoginName=StrName;
			OnBnClickedCheck();
			OnOK();
		}else
		{
			AfxMessageBox("��������ȷ�����룡");
		}		
	}else
	{
		AfxMessageBox("��������ȷ���û�����");
	}
}


BOOL CDlgLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//�����ݿ��ļ�
	CoInitialize(NULL);
	m_pConnection.CreateInstance(__uuidof(Connection));
	try
	{
		m_pConnection->Open("Driver=MySQL ODBC 5.1 Driver;Server=127.0.0.1;Database=sawdb","root","123456",adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}


	HMODULE Positionmodule = GetModuleHandle(0); 
	char pPositionFileName[MAX_PATH]; 
	GetModuleFileName(Positionmodule, pPositionFileName, MAX_PATH); 

	CString csPositionFullPath(pPositionFileName); 
	int nPos = csPositionFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		AfxMessageBox("�Ҳ���SystemInstall.ini�����ļ�"); 
	SystemIniFilePath=csPositionFullPath.Left( nPos ); 
	SystemIniFilePath=SystemIniFilePath+"\\SystemInstall.ini";

	CString strName,strPassword,strDefault;
	GetPrivateProfileString("LOGIN","Name","default",strName.GetBuffer(MAX_PATH),MAX_PATH,SystemIniFilePath); 
	GetPrivateProfileString("LOGIN","Password","default",strPassword.GetBuffer(MAX_PATH),MAX_PATH,SystemIniFilePath); 
	GetPrivateProfileString("LOGIN","Default","default",strDefault.GetBuffer(MAX_PATH),MAX_PATH,SystemIniFilePath); 
	strName.ReleaseBuffer();
	strPassword.ReleaseBuffer();
	strDefault.ReleaseBuffer();
	if (atoi(strDefault)==1)
	{
		GetDlgItem(IDC_EDIT_USERNAME)->SetWindowTextA(strName);
		GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextA(strPassword);
		((CButton*)GetDlgItem(IDC_CHECK_DEFAULT))->SetCheck(BST_CHECKED);
	} 
	else
	{
		GetDlgItem(IDC_EDIT_USERNAME)->SetWindowTextA("");
		GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextA("");
		((CButton*)GetDlgItem(IDC_CHECK_DEFAULT))->SetCheck(BST_UNCHECKED);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CDlgLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//�ж��Ƿ�Ϊ������Ϣ
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//�ж��Ƿ��¼���F1��
		if(pMsg->wParam==VK_RETURN)//ϵͳ�Լ�
		{
			OnBnClickedButtonLogin();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgLogin::OnBnClickedCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strName,strPassword,strDefault;
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowTextA(strName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowTextA(strPassword);
	if(m_BtnDefault.GetCheck() == BST_CHECKED) 
	{
		WritePrivateProfileString ("LOGIN","Name", strName, SystemIniFilePath);   
		WritePrivateProfileString ("LOGIN","Password", strPassword, SystemIniFilePath);   
		strDefault="1";
		WritePrivateProfileString ("LOGIN","Default", strDefault, SystemIniFilePath);   
	} 
	else if(m_BtnDefault.GetCheck() == BST_UNCHECKED) 
	{
		WritePrivateProfileString ("LOGIN","Name", "", SystemIniFilePath);   
		WritePrivateProfileString ("LOGIN","Password", "", SystemIniFilePath);   
		strDefault="0";
		WritePrivateProfileString ("LOGIN","Default", strDefault, SystemIniFilePath);   
	}		
}
