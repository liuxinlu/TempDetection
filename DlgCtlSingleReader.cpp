// DlgCtlSingleReader.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgCtlSingleReader.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgCtlSingleReader �Ի���
char SingleStartCMD[15]       ={0x00,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//��ʼ
char SingleStopCMD[15]        ={0x00,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//ֹͣ

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


// CDlgCtlSingleReader ��Ϣ�������


void CDlgCtlSingleReader::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
	SingleStartCMD[0]=(char)(nIndexReader+1);
	pMain->SendCMD(SingleStartCMD);
}


void CDlgCtlSingleReader::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
	SingleStopCMD[0]=(char)(nIndexReader+1);
	pMain->SendCMD(SingleStopCMD);
}


void CDlgCtlSingleReader::OnCbnSelchangeComboReader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReader=m_CtlComboReader.GetCurSel();
}


BOOL CDlgCtlSingleReader::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	nIndexReader=0;

	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndexReader);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
