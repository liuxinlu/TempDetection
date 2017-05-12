// DlgCtlSingleReader.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgCtlSingleReader.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgCtlSingleReader 对话框
char SingleStartCMD[15]       ={0x00,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//开始
char SingleStopCMD[15]        ={0x00,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//停止

IMPLEMENT_DYNAMIC(CDlgCtlSingleReader, CDialogEx)

CDlgCtlSingleReader::CDlgCtlSingleReader(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCtlSingleReader::IDD, pParent)
{

}

CDlgCtlSingleReader::~CDlgCtlSingleReader()
{
}

void CDlgCtlSingleReader::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_READER, m_CtlComboReader);
}


BEGIN_MESSAGE_MAP(CDlgCtlSingleReader, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDlgCtlSingleReader::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlgCtlSingleReader::OnBnClickedButtonStop)
	ON_CBN_SELCHANGE(IDC_COMBO_READER, &CDlgCtlSingleReader::OnCbnSelchangeComboReader)
END_MESSAGE_MAP()


// CDlgCtlSingleReader 消息处理程序


void CDlgCtlSingleReader::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	SingleStartCMD[0]=(char)(nIndexReader+1);
	pMain->SendCMD(SingleStartCMD);
}


void CDlgCtlSingleReader::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	SingleStopCMD[0]=(char)(nIndexReader+1);
	pMain->SendCMD(SingleStopCMD);
}


void CDlgCtlSingleReader::OnCbnSelchangeComboReader()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexReader=m_CtlComboReader.GetCurSel();
}


BOOL CDlgCtlSingleReader::OnInitDialog()
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
