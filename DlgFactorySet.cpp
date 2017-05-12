// DlgFactorySet.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgFactorySet.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgFactorySet 对话框
extern int UserSetLoopTime;//用户设定轮询时间
extern CString SystemIniFilePath;//保存系统相关参数的文件
extern int UserSetSynchronous;//用户设定同步指令的发送间隔

char SendFreqCMD[15]    ={0x00,0x46,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//发射频率
char RecvFreqCMD[15]    ={0x00,0x47,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//接收频率

IMPLEMENT_DYNAMIC(CDlgFactorySet, CDialogEx)

CDlgFactorySet::CDlgFactorySet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgFactorySet::IDD, pParent)
	, nIndexAnt1(0)
	, nIndexAnt2(0)
{

}

CDlgFactorySet::~CDlgFactorySet()
{
}

void CDlgFactorySet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ANT_ID1, m_CtlComboAnt1);
	DDX_Control(pDX, IDC_COMBO_ANT_ID2, m_CtlComboAnt2);
	DDX_Control(pDX, IDC_COMBO_READER_SEND, m_CtlComboReaderSend);
	DDX_Control(pDX, IDC_COMBO_READER_RECV, m_CtlComboReaderRecv);
	DDX_Control(pDX, IDC_COMBO_SYNCHRONOUS, m_CtlComboSynchronous);
}


BEGIN_MESSAGE_MAP(CDlgFactorySet, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEND_FREQ, &CDlgFactorySet::OnBnClickedButtonSendFreq)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVE_FREQ, &CDlgFactorySet::OnBnClickedButtonReceiveFreq)
	ON_CBN_SELCHANGE(IDC_COMBO_ANT_ID1, &CDlgFactorySet::OnCbnSelchangeComboAntId1)
	ON_CBN_SELCHANGE(IDC_COMBO_ANT_ID2, &CDlgFactorySet::OnCbnSelchangeComboAntId2)
	ON_CBN_SELCHANGE(IDC_COMBO_READER_RECV, &CDlgFactorySet::OnCbnSelchangeComboReaderRecv)
	ON_CBN_SELCHANGE(IDC_COMBO_READER_SEND, &CDlgFactorySet::OnCbnSelchangeComboReaderSend)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_LOOP_TIME, &CDlgFactorySet::OnBnClickedButtonSaveLoopTime)
	ON_CBN_SELCHANGE(IDC_COMBO_SYNCHRONOUS, &CDlgFactorySet::OnCbnSelchangeComboSynchronous)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SYNCHRONOUS, &CDlgFactorySet::OnBnClickedButtonSaveSynchronous)
END_MESSAGE_MAP()


// CDlgFactorySet 消息处理程序




void CDlgFactorySet::OnBnClickedButtonSendFreq()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFreq;

	//获取串口指针
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	GetDlgItem(IDC_EDIT_SEND_FREQ)->GetWindowTextA(strFreq);
	if (strFreq.GetLength()!=9)
	{
		AfxMessageBox("请输入正确的频率值！");
	}else
	{
		SendFreqCMD[0]=(char)(nindexReaderSend+1);
		SendFreqCMD[2]=(char)(nIndexAnt1+1);
		SendFreqCMD[6]=(char)(atol(strFreq)&0x000000ff);
		SendFreqCMD[5]=(char)((atol(strFreq)&0x0000ff00)>>8);
		SendFreqCMD[4]=(char)((atol(strFreq)&0x00ff0000)>>16);
		SendFreqCMD[3]=(char)((atol(strFreq)&0xff000000)>>24);
		pMain->SendCMD(SendFreqCMD);
		AfxMessageBox("发送完毕！");
	}
}


void CDlgFactorySet::OnBnClickedButtonReceiveFreq()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFreq;

	//获取串口指针
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	GetDlgItem(IDC_EDIT_RECEIVE_FREQ)->GetWindowTextA(strFreq);
	if (strFreq.GetLength()!=9)
	{
		AfxMessageBox("请输入正确的频率值！");
	}else
	{
		RecvFreqCMD[0]=(char)(nindexReaderSend+1);
		RecvFreqCMD[2]=(char)(nIndexAnt1+1);
		RecvFreqCMD[6]=(char)(atol(strFreq)&0x000000ff);
		RecvFreqCMD[5]=(char)((atol(strFreq)&0x0000ff00)>>8);
		RecvFreqCMD[4]=(char)((atol(strFreq)&0x00ff0000)>>16);
		RecvFreqCMD[3]=(char)((atol(strFreq)&0xff000000)>>24);
		pMain->SendCMD(RecvFreqCMD);
		AfxMessageBox("发送完毕！");
	}
}


void CDlgFactorySet::OnCbnSelchangeComboAntId1()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexAnt1=m_CtlComboAnt1.GetCurSel();
}


void CDlgFactorySet::OnCbnSelchangeComboAntId2()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexAnt2=m_CtlComboAnt2.GetCurSel();
}


BOOL CDlgFactorySet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	nIndexAnt2=0;
	nIndexAnt1=0;
	nIndexReaderRecv=0;
	nindexReaderSend=0;

	CComboBox*   pComb_Ant1   =   (CComboBox*)GetDlgItem(IDC_COMBO_ANT_ID1);   
	ASSERT(pComb_Ant1);   
	pComb_Ant1->SetCurSel(nIndexAnt1);
	CComboBox*   pComb_Ant2   =   (CComboBox*)GetDlgItem(IDC_COMBO_ANT_ID2);   
	ASSERT(pComb_Ant2);   
	pComb_Ant2->SetCurSel(nIndexAnt2);

	CComboBox*   pComb_ReaderSend   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER_SEND);   
	ASSERT(pComb_ReaderSend);   
	pComb_ReaderSend->SetCurSel(nindexReaderSend);
	CComboBox*   pComb_ReaderRecv   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER_RECV);   
	ASSERT(pComb_ReaderRecv);   
	pComb_ReaderRecv->SetCurSel(nIndexReaderRecv);

	nIndexSynchronous=UserSetSynchronous;
	CComboBox*   pComb_Syn   =   (CComboBox*)GetDlgItem(IDC_COMBO_SYNCHRONOUS);   
	ASSERT(pComb_Syn);   
	pComb_Syn->SetCurSel(nIndexSynchronous);

	CString temp;
	temp.Format("%d",UserSetLoopTime);
	GetDlgItem(IDC_EDIT_SET_LOOP_TIME)->SetWindowTextA(temp);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgFactorySet::OnCbnSelchangeComboReaderRecv()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexReaderRecv=m_CtlComboReaderRecv.GetCurSel();
}


void CDlgFactorySet::OnCbnSelchangeComboReaderSend()
{
	// TODO: 在此添加控件通知处理程序代码
	nindexReaderSend=m_CtlComboReaderSend.GetCurSel();
}


void CDlgFactorySet::OnBnClickedButtonSaveLoopTime()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	GetDlgItem(IDC_EDIT_SET_LOOP_TIME)->GetWindowTextA(temp);
	UserSetLoopTime=atoi(temp);
	WritePrivateProfileString("LOOPTIME","Time",temp,SystemIniFilePath);
}


void CDlgFactorySet::OnCbnSelchangeComboSynchronous()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndexSynchronous=m_CtlComboSynchronous.GetCurSel();
}


void CDlgFactorySet::OnBnClickedButtonSaveSynchronous()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	temp.Format("%d",nIndexSynchronous);
	UserSetSynchronous=nIndexSynchronous;
	WritePrivateProfileString("SYNCHRONOUS","Set",temp,SystemIniFilePath);
}
