// DlgUpdateFirmware.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgUpdateFirmware.h"
#include "afxdialogex.h"

char FirmwareCMD[15]    ={0x00,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//�̼�����

// CDlgUpdateFirmware �Ի���

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


// CDlgUpdateFirmware ��Ϣ�������


void CDlgUpdateFirmware::OnBnClickedButtonFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgUpdateFirmware::OnBnClickedButtonDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgUpdateFirmware::OnCbnSelchangeComboReader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReader = m_CtlComboReader.GetCurSel();	
}


BOOL CDlgUpdateFirmware::OnInitDialog()
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
