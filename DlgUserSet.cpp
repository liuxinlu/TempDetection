// DlgUserSet.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgUserSet.h"
#include "afxdialogex.h"
#include "MainFrm.h"
extern _ConnectionPtr m_pConnection;

// CDlgUserSet 对话框

IMPLEMENT_DYNAMIC(CDlgUserSet, CDialogEx)

CDlgUserSet::CDlgUserSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUserSet::IDD, pParent)
	, SelectUser(_T(""))
{

}

CDlgUserSet::~CDlgUserSet()
{
}

void CDlgUserSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_CtlListUser);
	DDX_Control(pDX, IDC_CHECK_ADMIN, m_CtlCheckAdmin);
}


BEGIN_MESSAGE_MAP(CDlgUserSet, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LIST_ALL, &CDlgUserSet::OnBnClickedButtonListAll)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgUserSet::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_ALERT, &CDlgUserSet::OnBnClickedButtonAlert)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgUserSet::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_CHECK_ADMIN, &CDlgUserSet::OnBnClickedCheckAdmin)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER, &CDlgUserSet::OnNMClickListUser)
END_MESSAGE_MAP()


// CDlgUserSet 消息处理程序


void CDlgUserSet::OnBnClickedButtonListAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_CtlListUser.DeleteAllItems();
	m_CtlListUser.SetRedraw(FALSE);
	_bstr_t bstrSQL ="SELECT * FROM db_user";
	int i=0;
	_RecordsetPtr m_pRecordset1;
	m_pRecordset1.CreateInstance(__uuidof(Recordset));
	//取得表中记录
	m_pRecordset1->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	while(!m_pRecordset1->adoEOF)
	{
		m_CtlListUser.InsertItem(i,"");
		m_CtlListUser.SetItemText(i,0,(char*)(_bstr_t)m_pRecordset1->GetCollect("UserName"));
		m_CtlListUser.SetItemText(i,1,(char*)(_bstr_t)m_pRecordset1->GetCollect("Domain"));
		i++;
		m_pRecordset1->MoveNext();
	}
	m_pRecordset1->Close();
	m_CtlListUser.SetRedraw(TRUE);	
}


void CDlgUserSet::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString StrName,StrPass,StrDomain;
	GetDlgItem(IDC_EDIT_USER_NAME)->GetWindowTextA(StrName);
	GetDlgItem(IDC_EDIT_USER_PASSWORD)->GetWindowTextA(StrPass);
	if(m_CtlCheckAdmin.GetCheck() == BST_CHECKED) 
	{
		StrDomain="0";
	} 
	else if(m_CtlCheckAdmin.GetCheck() == BST_UNCHECKED) 
	{
		StrDomain="1";
	}		
	if (StrName.GetLength()>0)
	{
		_bstr_t bstrSQL ="SELECT * FROM db_user where UserName='"+StrName+"'";
		_RecordsetPtr m_pRecordset1;
		m_pRecordset1.CreateInstance(__uuidof(Recordset));
		//取得表中记录
		m_pRecordset1->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		if(!m_pRecordset1->adoEOF)
		{
			AfxMessageBox("已经存在相同的用户名！");
			m_pRecordset1->MoveNext();
		}else
		{

			_variant_t RecordsAffected;
			try
			{
				_bstr_t strCmd="INSERT INTO db_user(UserName,UserPassword,Domain) VALUES('"+StrName+"','"+StrPass+"',"+StrDomain+")";
				m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
			}
			catch(_com_error e)
			{
				CString errormessage;
				errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
				AfxMessageBox(errormessage);
				return;
			}
			OnBnClickedButtonListAll();
			GetDlgItem(IDC_EDIT_USER_NAME)->SetWindowTextA("");
			GetDlgItem(IDC_EDIT_USER_PASSWORD)->SetWindowTextA("");
			m_CtlCheckAdmin.SetCheck(FALSE);
		}
		m_pRecordset1->Close();
	}else
	{
		AfxMessageBox("请输入正确的用户名！");
	}
}


void CDlgUserSet::OnBnClickedButtonAlert()
{
	// TODO: 在此添加控件通知处理程序代码
	CString StrName,StrPass,StrDomain;
	GetDlgItem(IDC_EDIT_USER_NAME)->GetWindowTextA(StrName);
	GetDlgItem(IDC_EDIT_USER_PASSWORD)->GetWindowTextA(StrPass);
	if(m_CtlCheckAdmin.GetCheck() == BST_CHECKED) 
	{
		StrDomain="0";
	} 
	else if(m_CtlCheckAdmin.GetCheck() == BST_UNCHECKED) 
	{
		StrDomain="1";
	}		

	_variant_t RecordsAffected;
	try
	{
		_bstr_t strCmd="update db_user set UserPassword='"+StrPass+"',Domain="+StrDomain+" where UserName='"+StrName+"'";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CDlgUserSet::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	_variant_t RecordsAffected;
	CString strDelete;
	_bstr_t sql1;
	if (SelectUser.GetLength()>0)
	{
		strDelete="DELETE FROM db_user WHERE UserName = '"+SelectUser+"'";
		sql1 = strDelete;
		m_pConnection->Execute(sql1,&RecordsAffected,adCmdText);
		OnBnClickedButtonListAll();
		GetDlgItem(IDC_EDIT_USER_NAME)->SetWindowTextA("");
		GetDlgItem(IDC_EDIT_USER_PASSWORD)->SetWindowTextA("");
		m_CtlCheckAdmin.SetCheck(FALSE);

	}
}


void CDlgUserSet::OnBnClickedCheckAdmin()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgUserSet::OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_USER_PASSWORD)->SetWindowTextA("");
	POSITION pos = NULL;
	int nIndex = -1;
	pos = m_CtlListUser.GetFirstSelectedItemPosition();
	nIndex = m_CtlListUser.GetNextSelectedItem(pos);
	CString UserName  = m_CtlListUser.GetItemText(nIndex, 0);
	CString UserDomain  = m_CtlListUser.GetItemText(nIndex, 1);
	if (UserName.GetLength()>0)
	{
		SelectUser=UserName;

		GetDlgItem(IDC_EDIT_USER_NAME)->SetWindowTextA(UserName);
		switch (atoi(UserDomain))
		{
		case 0:
			m_CtlCheckAdmin.SetCheck(TRUE);
			break;
		case 1:
			m_CtlCheckAdmin.SetCheck(FALSE);
			break;
		default:
			break;
		}
		OnBnClickedButtonListAll();
	}

	*pResult = 0;
}


BOOL CDlgUserSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CtlListUser.DeleteAllItems();
	m_CtlListUser.InsertColumn(0,"用户名");
	m_CtlListUser.InsertColumn(1,"权限");
	m_CtlListUser.SetColumnWidth(0,130);
	m_CtlListUser.SetColumnWidth(1,50);
	m_CtlListUser.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	SelectUser="";
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
