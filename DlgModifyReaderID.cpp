// DlgModifyReaderID.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgModifyReaderID.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgModifyReaderID 对话框
char ModifyReaderCMD[15]={0x00,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//修改读卡器号

IMPLEMENT_DYNAMIC(CDlgModifyReaderID, CDialogEx)

CDlgModifyReaderID::CDlgModifyReaderID(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgModifyReaderID::IDD, pParent)
{

}

CDlgModifyReaderID::~CDlgModifyReaderID()
{
}

void CDlgModifyReaderID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_READER_OLD, m_CtlComboReaderOld);
	DDX_Control(pDX, IDC_COMBO_READER_NEW, m_CtlComboReaderNew);
}


BEGIN_MESSAGE_MAP(CDlgModifyReaderID, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CDlgModifyReaderID::OnBnClickedButtonModify)
	ON_CBN_SELCHANGE(IDC_COMBO_READER_NEW, &CDlgModifyReaderID::OnCbnSelchangeComboReaderNew)
	ON_CBN_SELCHANGE(IDC_COMBO_READER_OLD, &CDlgModifyReaderID::OnCbnSelchangeComboReaderOld)
END_MESSAGE_MAP()


// CDlgModifyReaderID 消息处理程序


void CDlgModifyReaderID::OnBnClickedButtonModify()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	ModifyReaderCMD[0]=(char)nIndexReaderOld;
	ModifyReaderCMD[2]=(char)(nIndexReaderNew+1);
	pMain->SendCMD(ModifyReaderCMD);
}


void CDlgModifyReaderID::OnCbnSelchangeComboReaderNew()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexReaderNew=m_CtlComboReaderNew.GetCurSel();
}


void CDlgModifyReaderID::OnCbnSelchangeComboReaderOld()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexReaderOld=m_CtlComboReaderOld.GetCurSel();
}


BOOL CDlgModifyReaderID::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	nIndexReaderNew=0;
	nIndexReaderOld=0;

	CComboBox*   pComb_Reader_Old   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER_OLD);   
	ASSERT(pComb_Reader_Old);   
	pComb_Reader_Old->SetCurSel(nIndexReaderOld);
	CComboBox*   pComb_Reader_New   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER_NEW);   
	ASSERT(pComb_Reader_New);   
	pComb_Reader_New->SetCurSel(nIndexReaderNew);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
