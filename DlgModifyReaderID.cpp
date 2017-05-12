// DlgModifyReaderID.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgModifyReaderID.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgModifyReaderID �Ի���
char ModifyReaderCMD[15]={0x00,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//�޸Ķ�������

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


// CDlgModifyReaderID ��Ϣ�������


void CDlgModifyReaderID::OnBnClickedButtonModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
	ModifyReaderCMD[0]=(char)nIndexReaderOld;
	ModifyReaderCMD[2]=(char)(nIndexReaderNew+1);
	pMain->SendCMD(ModifyReaderCMD);
}


void CDlgModifyReaderID::OnCbnSelchangeComboReaderNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReaderNew=m_CtlComboReaderNew.GetCurSel();
}


void CDlgModifyReaderID::OnCbnSelchangeComboReaderOld()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReaderOld=m_CtlComboReaderOld.GetCurSel();
}


BOOL CDlgModifyReaderID::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	nIndexReaderNew=0;
	nIndexReaderOld=0;

	CComboBox*   pComb_Reader_Old   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER_OLD);   
	ASSERT(pComb_Reader_Old);   
	pComb_Reader_Old->SetCurSel(nIndexReaderOld);
	CComboBox*   pComb_Reader_New   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER_NEW);   
	ASSERT(pComb_Reader_New);   
	pComb_Reader_New->SetCurSel(nIndexReaderNew);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
