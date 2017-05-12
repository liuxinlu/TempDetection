// DlgUpdateFirmware.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgUpdateFirmware.h"
#include "afxdialogex.h"

char FirmwareCMD[15]    ={0x00,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//固件升级

// CDlgUpdateFirmware 对话框

IMPLEMENT_DYNAMIC(CDlgUpdateFirmware, CDialogEx)

CDlgUpdateFirmware::CDlgUpdateFirmware(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUpdateFirmware::IDD, pParent)
{

}

CDlgUpdateFirmware::~CDlgUpdateFirmware()
{
}

void CDlgUpdateFirmware::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_READER, m_CtlComboReader);
}


BEGIN_MESSAGE_MAP(CDlgUpdateFirmware, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CDlgUpdateFirmware::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CDlgUpdateFirmware::OnBnClickedButtonDown)
	ON_CBN_SELCHANGE(IDC_COMBO_READER, &CDlgUpdateFirmware::OnCbnSelchangeComboReader)
END_MESSAGE_MAP()


// CDlgUpdateFirmware 消息处理程序


void CDlgUpdateFirmware::OnBnClickedButtonFile()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgUpdateFirmware::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgUpdateFirmware::OnCbnSelchangeComboReader()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexReader = m_CtlComboReader.GetCurSel();	
}


BOOL CDlgUpdateFirmware::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	nIndexReader=0;
	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndexReader);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
