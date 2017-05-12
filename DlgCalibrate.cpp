// DlgCalibrate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgCalibrate.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern unsigned int m_FreqData[30][4][12];//У׼���棺�����յ������µ�Ƶ��ֵ
extern float m_TempData[30][4][12];//У׼���棺�����յ������µ��¶�ֵ
extern bool PortOpenFlag;//true�Ѿ��� falseδ�򿪶˿�
extern int CalibrateFlag;//У׼�ı�־��1Ϊ��ʼУ׼���棬0ΪֹͣУ׼
extern bool StartFlag;//��ʼ�ı�־��1Ϊ��ʼ��0Ϊֹͣ
extern int ReceiveDataCount;//�����������
extern int UserSelectReaderForCal;//У׼���棺�û�ѡ��Ķ�����

char CalCMD[15]            ={0x00,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//У׼
CString CalAllTemp;

UINT CalAllReaderProc(LPVOID lParam); //����У׼�߳�

UINT CalAllReaderProc(LPVOID lParam) 
{
	CDlgCalibrate* pDlg = (CDlgCalibrate*)lParam;
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��

	int i=UserSelectReaderForCal;
	CString str;
	str.Format("%d",i+1);
	pDlg->GetDlgItem(IDC_STATIC_CAL)->SetWindowText("����У׼��ȡ��"+str+"����");
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 12; k++)
		{
			pDlg->m_CtlProgressCal.StepIt();

			if (m_FreqData[i][j][k]>10)
			{
				CalCMD[0]=(char)(i+1);
				CalCMD[2]=(char)j;
				CalCMD[3]=(char)k;
				CalCMD[5]=(char)(atoi(CalAllTemp)&0x00ff);
				CalCMD[4]=(char)((atoi(CalAllTemp)&0xff00)>>8);
				CalCMD[9]=(char)(m_FreqData[i][j][k]&0x000000ff);
				CalCMD[8]=(char)((m_FreqData[i][j][k]&0x0000ff00)>>8);
				CalCMD[7]=(char)((m_FreqData[i][j][k]&0x00ff0000)>>16);
				CalCMD[6]=(char)((m_FreqData[i][j][k]&0xff000000)>>24);
				pMain->SendCMD(CalCMD);
				Sleep(200);
			}
		}
	}

	pDlg->GetDlgItem(IDC_PROGRESS_CAL)->ShowWindow(FALSE);
	pDlg->GetDlgItem(IDC_STATIC_CAL)->ShowWindow(FALSE);
	pDlg->GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_CALIBRATE)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_BUTTON_CALIBRATE_ALL)->EnableWindow(TRUE);
	return 0;
}
// CDlgCalibrate �Ի���

IMPLEMENT_DYNAMIC(CDlgCalibrate, CDialogEx)

CDlgCalibrate::CDlgCalibrate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCalibrate::IDD, pParent)
{

}

CDlgCalibrate::~CDlgCalibrate()
{
}

void CDlgCalibrate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SENSOR_ID, m_CtlComboSensorID);
	DDX_Control(pDX, IDC_COMBO_ANT_ID, m_CtlComboAntID);
	DDX_Control(pDX, IDC_COMBO_READER, m_CtlComboReaderID);
	DDX_Control(pDX, IDC_PROGRESS_CAL, m_CtlProgressCal);
}


BEGIN_MESSAGE_MAP(CDlgCalibrate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATE, &CDlgCalibrate::OnBnClickedButtonCalibrate)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgCalibrate::OnBnClickedButtonClose)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR_ID, &CDlgCalibrate::OnCbnSelchangeComboSensorId)
	ON_CBN_SELCHANGE(IDC_COMBO_ANT_ID, &CDlgCalibrate::OnCbnSelchangeComboAntId)
	ON_BN_CLICKED(IDC_BUTTON_CALIBRATE_ALL, &CDlgCalibrate::OnBnClickedButtonCalibrateAll)
	ON_BN_CLICKED(IDC_BUTTON_START_MEM, &CDlgCalibrate::OnBnClickedButtonStartMem)
	ON_BN_CLICKED(IDC_BUTTON_STOP_MEM, &CDlgCalibrate::OnBnClickedButtonStopMem)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlgCalibrate::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_COMBO_READER, &CDlgCalibrate::OnCbnSelchangeComboReader)
END_MESSAGE_MAP()


// CDlgCalibrate ��Ϣ�������


void CDlgCalibrate::OnBnClickedButtonCalibrate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (PortOpenFlag)
	{
		//��ȡ����ָ��
		CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
		CString SetTemp;
		CString Ant_Cmd,Sensor_Cmd;
		CString strFreq;
		GetDlgItem(IDC_EDIT_CALI_TEMP)->GetWindowTextA(SetTemp);
		if (SetTemp.GetLength()!=4)
		{
			AfxMessageBox("��������ȷ�����ָ�ʽ�����¶�Ϊ��+-��3λ���������֣�");
		}else if (ShowFreq.GetLength()!=9)
		{
			AfxMessageBox("�˴�������Ƶ��ֵ��������ѡ������²��£�");
		}
		else
		{
			CalCMD[0]=(char)(nIndex_Reader+1);
			CalCMD[2]=(char)nIndex_Ant;
			CalCMD[3]=(char)nIndex_Sensor;
			CalCMD[5]=(char)(atoi(SetTemp)&0x00ff);
			CalCMD[4]=(char)((atoi(SetTemp)&0xff00)>>8);
			CalCMD[9]=(char)(atol(ShowFreq)&0x000000ff);
			CalCMD[8]=(char)((atol(ShowFreq)&0x0000ff00)>>8);
			CalCMD[7]=(char)((atol(ShowFreq)&0x00ff0000)>>16);
			CalCMD[6]=(char)((atol(ShowFreq)&0xff000000)>>24);
			pMain->SendCMD(CalCMD);

			AfxMessageBox("У׼��ɣ�");
		}
	} 
	else
	{
		AfxMessageBox("���ȴ򿪶˿ڣ��ٽ��п��Ʋ�����");
	}

}


void CDlgCalibrate::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void CDlgCalibrate::OnCbnSelchangeComboSensorId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndex_Sensor = m_CtlComboSensorID.GetCurSel();

	if (m_FreqData[nIndex_Reader][nIndex_Ant][nIndex_Sensor]>10)
	{
		ShowFreq.Format("%d",m_FreqData[nIndex_Reader][nIndex_Ant][nIndex_Sensor]);
		GetDlgItem(IDC_EDIT_CALI_TEMP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FREQ)->SetWindowTextA(ShowFreq);
	}else
	{
		GetDlgItem(IDC_EDIT_CALI_TEMP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FREQ)->SetWindowTextA("");
	}
}


BOOL CDlgCalibrate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT_CALI_TEMP)->EnableWindow(FALSE);
	nIndex_Sensor=0;
	nIndex_Ant=0;
	nIndex_Reader=0;
	UserSelectReaderForCal=0;

	OnBnClickedButtonClear();

	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndex_Reader);

	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CALIBRATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CALIBRATE_ALL)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



void CDlgCalibrate::OnCbnSelchangeComboAntId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndex_Ant = m_CtlComboAntID.GetCurSel();

	if (m_FreqData[nIndex_Reader][nIndex_Ant][nIndex_Sensor]>10)
	{
		ShowFreq.Format("%d",m_FreqData[nIndex_Reader][nIndex_Ant][nIndex_Sensor]);
		GetDlgItem(IDC_EDIT_FREQ)->SetWindowTextA(ShowFreq);
		GetDlgItem(IDC_EDIT_CALI_TEMP)->EnableWindow(TRUE);
	}else
	{
		GetDlgItem(IDC_EDIT_CALI_TEMP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FREQ)->SetWindowTextA("");
	}
}


void CDlgCalibrate::OnBnClickedButtonCalibrateAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (PortOpenFlag)
	{
		CString SetTemp;
		GetDlgItem(IDC_EDIT_CALI_TEMP_ALL)->GetWindowTextA(SetTemp);
		if (SetTemp.GetLength()!=4)
		{
			AfxMessageBox("��������ȷ�����ָ�ʽ�����¶�Ϊ��+-��3λ���������֣�");
		}else{
			GetDlgItem(IDC_PROGRESS_CAL)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_CAL)->ShowWindow(TRUE);
			GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CALIBRATE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CALIBRATE_ALL)->EnableWindow(FALSE);
			m_CtlProgressCal.SetRange(0,4*12);
			m_CtlProgressCal.SetStep(1);
			m_CtlProgressCal.SetPos(0);
			CalAllTemp=SetTemp;
			AfxBeginThread(CalAllReaderProc,this);
		}
	} 
	else
	{
		AfxMessageBox("���ȴ򿪶˿ڣ��ٽ��п��Ʋ�����");
	}

}


void CDlgCalibrate::OnBnClickedButtonStartMem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ����ָ��
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��
	
	//���Ϳ�ʼ����ָ��
	pMain->StartMem();

	CalibrateFlag=1;

	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CALIBRATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CALIBRATE_ALL)->EnableWindow(FALSE);
}


void CDlgCalibrate::OnBnClickedButtonStopMem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ����ָ��
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//��ȡMainFrameָ��

	pMain->StopMem();
	CalibrateFlag=0;
	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLEAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CALIBRATE_ALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CALIBRATE)->EnableWindow(TRUE);
}


void CDlgCalibrate::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_STATIC_FREQ1_1)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_2)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_3)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_4)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_5)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_6)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_7)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_8)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_9)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_10)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_11)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ1_12)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_1)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_2)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_3)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_4)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_5)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_6)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_7)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_8)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_9)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_10)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_11)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ2_12)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_1)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_2)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_3)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_4)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_5)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_6)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_7)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_8)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_9)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_10)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_11)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ3_12)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_1)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_2)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_3)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_4)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_5)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_6)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_7)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_8)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_9)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_10)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_11)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_FREQ4_12)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_1)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_2)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_3)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_4)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_5)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_6)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_7)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_8)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_9)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_10)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_11)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP1_12)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_1)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_2)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_3)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_4)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_5)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_6)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_7)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_8)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_9)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_10)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_11)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP2_12)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_1)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_2)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_3)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_4)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_5)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_6)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_7)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_8)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_9)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_10)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_11)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP3_12)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_1)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_2)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_3)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_4)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_5)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_6)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_7)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_8)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_9)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_10)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_11)->SetWindowTextA("");
	GetDlgItem(IDC_STATIC_TEMP4_12)->SetWindowTextA("");
}


void CDlgCalibrate::OnCbnSelchangeComboReader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndex_Reader=m_CtlComboReaderID.GetCurSel();
	UserSelectReaderForCal=nIndex_Reader;
	DataShow(m_TempData[nIndex_Reader][0][0],m_FreqData[nIndex_Reader][0][0],IDC_STATIC_TEMP1_1,IDC_STATIC_FREQ1_1);
	DataShow(m_TempData[nIndex_Reader][0][1],m_FreqData[nIndex_Reader][0][1],IDC_STATIC_TEMP1_2,IDC_STATIC_FREQ1_2);
	DataShow(m_TempData[nIndex_Reader][0][2],m_FreqData[nIndex_Reader][0][2],IDC_STATIC_TEMP1_3,IDC_STATIC_FREQ1_3);
	DataShow(m_TempData[nIndex_Reader][0][3],m_FreqData[nIndex_Reader][0][3],IDC_STATIC_TEMP1_4,IDC_STATIC_FREQ1_4);
	DataShow(m_TempData[nIndex_Reader][0][4],m_FreqData[nIndex_Reader][0][4],IDC_STATIC_TEMP1_5,IDC_STATIC_FREQ1_5);
	DataShow(m_TempData[nIndex_Reader][0][5],m_FreqData[nIndex_Reader][0][5],IDC_STATIC_TEMP1_6,IDC_STATIC_FREQ1_6);
	DataShow(m_TempData[nIndex_Reader][0][6],m_FreqData[nIndex_Reader][0][6],IDC_STATIC_TEMP1_7,IDC_STATIC_FREQ1_7);
	DataShow(m_TempData[nIndex_Reader][0][7],m_FreqData[nIndex_Reader][0][7],IDC_STATIC_TEMP1_8,IDC_STATIC_FREQ1_8);
	DataShow(m_TempData[nIndex_Reader][0][8],m_FreqData[nIndex_Reader][0][8],IDC_STATIC_TEMP1_9,IDC_STATIC_FREQ1_9);
	DataShow(m_TempData[nIndex_Reader][0][9],m_FreqData[nIndex_Reader][0][9],IDC_STATIC_TEMP1_10,IDC_STATIC_FREQ1_10);
	DataShow(m_TempData[nIndex_Reader][0][10],m_FreqData[nIndex_Reader][0][10],IDC_STATIC_TEMP1_11,IDC_STATIC_FREQ1_11);
	DataShow(m_TempData[nIndex_Reader][0][11],m_FreqData[nIndex_Reader][0][11],IDC_STATIC_TEMP1_12,IDC_STATIC_FREQ1_12);

	DataShow(m_TempData[nIndex_Reader][1][0],m_FreqData[nIndex_Reader][1][0],IDC_STATIC_TEMP2_1,IDC_STATIC_FREQ2_1);
	DataShow(m_TempData[nIndex_Reader][1][1],m_FreqData[nIndex_Reader][1][1],IDC_STATIC_TEMP2_2,IDC_STATIC_FREQ2_2);
	DataShow(m_TempData[nIndex_Reader][1][2],m_FreqData[nIndex_Reader][1][2],IDC_STATIC_TEMP2_3,IDC_STATIC_FREQ2_3);
	DataShow(m_TempData[nIndex_Reader][1][3],m_FreqData[nIndex_Reader][1][3],IDC_STATIC_TEMP2_4,IDC_STATIC_FREQ2_4);
	DataShow(m_TempData[nIndex_Reader][1][4],m_FreqData[nIndex_Reader][1][4],IDC_STATIC_TEMP2_5,IDC_STATIC_FREQ2_5);
	DataShow(m_TempData[nIndex_Reader][1][5],m_FreqData[nIndex_Reader][1][5],IDC_STATIC_TEMP2_6,IDC_STATIC_FREQ2_6);
	DataShow(m_TempData[nIndex_Reader][1][6],m_FreqData[nIndex_Reader][1][6],IDC_STATIC_TEMP2_7,IDC_STATIC_FREQ2_7);
	DataShow(m_TempData[nIndex_Reader][1][7],m_FreqData[nIndex_Reader][1][7],IDC_STATIC_TEMP2_8,IDC_STATIC_FREQ2_8);
	DataShow(m_TempData[nIndex_Reader][1][8],m_FreqData[nIndex_Reader][1][8],IDC_STATIC_TEMP2_9,IDC_STATIC_FREQ2_9);
	DataShow(m_TempData[nIndex_Reader][1][9],m_FreqData[nIndex_Reader][1][9],IDC_STATIC_TEMP2_10,IDC_STATIC_FREQ2_10);
	DataShow(m_TempData[nIndex_Reader][1][10],m_FreqData[nIndex_Reader][1][10],IDC_STATIC_TEMP2_11,IDC_STATIC_FREQ2_11);
	DataShow(m_TempData[nIndex_Reader][1][11],m_FreqData[nIndex_Reader][1][11],IDC_STATIC_TEMP2_12,IDC_STATIC_FREQ2_12);

	DataShow(m_TempData[nIndex_Reader][2][0],m_FreqData[nIndex_Reader][2][0],IDC_STATIC_TEMP3_1,IDC_STATIC_FREQ3_1);
	DataShow(m_TempData[nIndex_Reader][2][1],m_FreqData[nIndex_Reader][2][1],IDC_STATIC_TEMP3_2,IDC_STATIC_FREQ3_2);
	DataShow(m_TempData[nIndex_Reader][2][2],m_FreqData[nIndex_Reader][2][2],IDC_STATIC_TEMP3_3,IDC_STATIC_FREQ3_3);
	DataShow(m_TempData[nIndex_Reader][2][3],m_FreqData[nIndex_Reader][2][3],IDC_STATIC_TEMP3_4,IDC_STATIC_FREQ3_4);
	DataShow(m_TempData[nIndex_Reader][2][4],m_FreqData[nIndex_Reader][2][4],IDC_STATIC_TEMP3_5,IDC_STATIC_FREQ3_5);
	DataShow(m_TempData[nIndex_Reader][2][5],m_FreqData[nIndex_Reader][2][5],IDC_STATIC_TEMP3_6,IDC_STATIC_FREQ3_6);
	DataShow(m_TempData[nIndex_Reader][2][6],m_FreqData[nIndex_Reader][2][6],IDC_STATIC_TEMP3_7,IDC_STATIC_FREQ3_7);
	DataShow(m_TempData[nIndex_Reader][2][7],m_FreqData[nIndex_Reader][2][7],IDC_STATIC_TEMP3_8,IDC_STATIC_FREQ3_8);
	DataShow(m_TempData[nIndex_Reader][2][8],m_FreqData[nIndex_Reader][2][8],IDC_STATIC_TEMP3_9,IDC_STATIC_FREQ3_9);
	DataShow(m_TempData[nIndex_Reader][2][9],m_FreqData[nIndex_Reader][2][9],IDC_STATIC_TEMP3_10,IDC_STATIC_FREQ3_10);
	DataShow(m_TempData[nIndex_Reader][2][10],m_FreqData[nIndex_Reader][2][10],IDC_STATIC_TEMP3_11,IDC_STATIC_FREQ3_11);
	DataShow(m_TempData[nIndex_Reader][2][11],m_FreqData[nIndex_Reader][2][11],IDC_STATIC_TEMP3_12,IDC_STATIC_FREQ3_12);

	DataShow(m_TempData[nIndex_Reader][3][0],m_FreqData[nIndex_Reader][3][0],IDC_STATIC_TEMP4_1,IDC_STATIC_FREQ4_1);
	DataShow(m_TempData[nIndex_Reader][3][1],m_FreqData[nIndex_Reader][3][1],IDC_STATIC_TEMP4_2,IDC_STATIC_FREQ4_2);
	DataShow(m_TempData[nIndex_Reader][3][2],m_FreqData[nIndex_Reader][3][2],IDC_STATIC_TEMP4_3,IDC_STATIC_FREQ4_3);
	DataShow(m_TempData[nIndex_Reader][3][3],m_FreqData[nIndex_Reader][3][3],IDC_STATIC_TEMP4_4,IDC_STATIC_FREQ4_4);
	DataShow(m_TempData[nIndex_Reader][3][4],m_FreqData[nIndex_Reader][3][4],IDC_STATIC_TEMP4_5,IDC_STATIC_FREQ4_5);
	DataShow(m_TempData[nIndex_Reader][3][5],m_FreqData[nIndex_Reader][3][5],IDC_STATIC_TEMP4_6,IDC_STATIC_FREQ4_6);
	DataShow(m_TempData[nIndex_Reader][3][6],m_FreqData[nIndex_Reader][3][6],IDC_STATIC_TEMP4_7,IDC_STATIC_FREQ4_7);
	DataShow(m_TempData[nIndex_Reader][3][7],m_FreqData[nIndex_Reader][3][7],IDC_STATIC_TEMP4_8,IDC_STATIC_FREQ4_8);
	DataShow(m_TempData[nIndex_Reader][3][8],m_FreqData[nIndex_Reader][3][8],IDC_STATIC_TEMP4_9,IDC_STATIC_FREQ4_9);
	DataShow(m_TempData[nIndex_Reader][3][9],m_FreqData[nIndex_Reader][3][9],IDC_STATIC_TEMP4_10,IDC_STATIC_FREQ4_10);
	DataShow(m_TempData[nIndex_Reader][3][10],m_FreqData[nIndex_Reader][3][10],IDC_STATIC_TEMP4_11,IDC_STATIC_FREQ4_11);
	DataShow(m_TempData[nIndex_Reader][3][11],m_FreqData[nIndex_Reader][3][11],IDC_STATIC_TEMP4_12,IDC_STATIC_FREQ4_12);
}

void CDlgCalibrate::DataShow(float GetTemperData,int GetFreqData,int StaticTemper,int StaticFreq)
{
	CString TemperTxt,FreqTxt;//���ڱ���txt�ı�������
	CString TemperText,FreqText;
	if(GetFreqData==0x01)
	{
		GetDlgItem(StaticTemper)->SetWindowText("");
		GetDlgItem(StaticFreq)->SetWindowText("����");
	}else if(GetFreqData==0x02)
	{
		GetDlgItem(StaticTemper)->SetWindowText("");
		GetDlgItem(StaticFreq)->SetWindowText("���ʵ�");
	}else if(GetFreqData==0x03)
	{
		GetDlgItem(StaticTemper)->SetWindowText("");
		GetDlgItem(StaticFreq)->SetWindowText("�ź���");
	}else if(GetFreqData==0)
	{
		GetDlgItem(StaticTemper)->SetWindowText("");
		GetDlgItem(StaticFreq)->SetWindowText("");
	}else
	{
		TemperTxt.Format("%.1f",GetTemperData);//�޸Ĵ洢txt�����ݸ�ʽtemper
		FreqTxt.Format("%d",GetFreqData);//�޸Ĵ洢txt�����ݸ�ʽfreq
		TemperText="T:"+TemperTxt+"��";
		FreqText="F:"+FreqTxt;
		GetDlgItem(StaticTemper)->SetWindowText(TemperText);
		GetDlgItem(StaticFreq)->SetWindowText(FreqText);
	}
}

