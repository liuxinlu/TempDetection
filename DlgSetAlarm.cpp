// DlgSetAlarm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgSetAlarm.h"
#include "afxdialogex.h"
#include "MainFrm.h"
extern int AlarmTempSave[2][30];//���汨���¶ȣ�0Ϊ���£�1Ϊ����

// CDlgSetAlarm �Ի���

IMPLEMENT_DYNAMIC(CDlgSetAlarm, CDialogEx)

CDlgSetAlarm::CDlgSetAlarm(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetAlarm::IDD, pParent)
{

}

CDlgSetAlarm::~CDlgSetAlarm()
{
}

void CDlgSetAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_READER_ID, m_CtlComboReader);
}


BEGIN_MESSAGE_MAP(CDlgSetAlarm, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_READER_ID, &CDlgSetAlarm::OnCbnSelchangeComboReaderId)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_ALARM, &CDlgSetAlarm::OnBnClickedButtonSaveAlarm)
	ON_BN_CLICKED(IDC_BUTTON_CANNECL, &CDlgSetAlarm::OnBnClickedButtonCannecl)
END_MESSAGE_MAP()


// CDlgSetAlarm ��Ϣ�������


void CDlgSetAlarm::OnCbnSelchangeComboReaderId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReader=m_CtlComboReader.GetCurSel();
	CString str1,str2;
	str1.Format("%d",AlarmTempSave[0][nIndexReader]);
	str2.Format("%d",AlarmTempSave[1][nIndexReader]);
	GetDlgItem(IDC_EDIT_ALARM_HIGH_TEMP)->SetWindowTextA(str1);
	GetDlgItem(IDC_EDIT_ALARM_LOW_TEMP)->SetWindowTextA(str2);
}


void CDlgSetAlarm::OnBnClickedButtonSaveAlarm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str1,str2,str3;
	GetDlgItem(IDC_EDIT_ALARM_HIGH_TEMP)->GetWindowTextA(str1);
	GetDlgItem(IDC_EDIT_ALARM_LOW_TEMP)->GetWindowTextA(str2);
	AlarmTempSave[0][nIndexReader]=atoi(str1);
	AlarmTempSave[1][nIndexReader]=atoi(str2);
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
	str3.Format("%d",nIndexReader+1);
	pMain->UpdateAlarmTemp(str3,str1,str2);
}


void CDlgSetAlarm::OnBnClickedButtonCannecl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


BOOL CDlgSetAlarm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	nIndexReader=0;

	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER_ID);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndexReader);

	CString str1,str2;
	str1.Format("%d",AlarmTempSave[0][0]);
	str2.Format("%d",AlarmTempSave[1][0]);
	GetDlgItem(IDC_EDIT_ALARM_HIGH_TEMP)->SetWindowTextA(str1);
	GetDlgItem(IDC_EDIT_ALARM_LOW_TEMP)->SetWindowTextA(str2);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
