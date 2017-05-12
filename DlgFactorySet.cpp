// DlgFactorySet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgFactorySet.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgFactorySet �Ի���
extern int UserSetLoopTime;//�û��趨��ѯʱ��
extern CString SystemIniFilePath;//����ϵͳ��ز������ļ�
extern int UserSetSynchronous;//�û��趨ͬ��ָ��ķ��ͼ��

char SendFreqCMD[15]    ={0x00,0x46,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//����Ƶ��
char RecvFreqCMD[15]    ={0x00,0x47,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//����Ƶ��

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


// CDlgFactorySet ��Ϣ�������




void CDlgFactorySet::OnBnClickedButtonSendFreq()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFreq;

	//��ȡ����ָ��
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
	GetDlgItem(IDC_EDIT_SEND_FREQ)->GetWindowTextA(strFreq);
	if (strFreq.GetLength()!=9)
	{
		AfxMessageBox("��������ȷ��Ƶ��ֵ��");
	}else
	{
		SendFreqCMD[0]=(char)(nindexReaderSend+1);
		SendFreqCMD[2]=(char)(nIndexAnt1+1);
		SendFreqCMD[6]=(char)(atol(strFreq)&0x000000ff);
		SendFreqCMD[5]=(char)((atol(strFreq)&0x0000ff00)>>8);
		SendFreqCMD[4]=(char)((atol(strFreq)&0x00ff0000)>>16);
		SendFreqCMD[3]=(char)((atol(strFreq)&0xff000000)>>24);
		pMain->SendCMD(SendFreqCMD);
		AfxMessageBox("������ϣ�");
	}
}


void CDlgFactorySet::OnBnClickedButtonReceiveFreq()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFreq;

	//��ȡ����ָ��
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
	GetDlgItem(IDC_EDIT_RECEIVE_FREQ)->GetWindowTextA(strFreq);
	if (strFreq.GetLength()!=9)
	{
		AfxMessageBox("��������ȷ��Ƶ��ֵ��");
	}else
	{
		RecvFreqCMD[0]=(char)(nindexReaderSend+1);
		RecvFreqCMD[2]=(char)(nIndexAnt1+1);
		RecvFreqCMD[6]=(char)(atol(strFreq)&0x000000ff);
		RecvFreqCMD[5]=(char)((atol(strFreq)&0x0000ff00)>>8);
		RecvFreqCMD[4]=(char)((atol(strFreq)&0x00ff0000)>>16);
		RecvFreqCMD[3]=(char)((atol(strFreq)&0xff000000)>>24);
		pMain->SendCMD(RecvFreqCMD);
		AfxMessageBox("������ϣ�");
	}
}


void CDlgFactorySet::OnCbnSelchangeComboAntId1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexAnt1=m_CtlComboAnt1.GetCurSel();
}


void CDlgFactorySet::OnCbnSelchangeComboAntId2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexAnt2=m_CtlComboAnt2.GetCurSel();
}


BOOL CDlgFactorySet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgFactorySet::OnCbnSelchangeComboReaderRecv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReaderRecv=m_CtlComboReaderRecv.GetCurSel();
}


void CDlgFactorySet::OnCbnSelchangeComboReaderSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nindexReaderSend=m_CtlComboReaderSend.GetCurSel();
}


void CDlgFactorySet::OnBnClickedButtonSaveLoopTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	GetDlgItem(IDC_EDIT_SET_LOOP_TIME)->GetWindowTextA(temp);
	UserSetLoopTime=atoi(temp);
	WritePrivateProfileString("LOOPTIME","Time",temp,SystemIniFilePath);
}


void CDlgFactorySet::OnCbnSelchangeComboSynchronous()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexSynchronous=m_CtlComboSynchronous.GetCurSel();
}


void CDlgFactorySet::OnBnClickedButtonSaveSynchronous()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	temp.Format("%d",nIndexSynchronous);
	UserSetSynchronous=nIndexSynchronous;
	WritePrivateProfileString("SYNCHRONOUS","Set",temp,SystemIniFilePath);
}
