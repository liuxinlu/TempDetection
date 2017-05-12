// DlgMainShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgMainShow.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern double LastRecvTemp[30][4][12];//���������յ����¶�����
extern int LastAlarmStatus[30][4][12];//���汨��״̬��0Ϊ�޾�����1Ϊ�о�����2��3��4��ʾ״̬������Ϊ��������
extern int UserSelectReader;//�û�ѡ��Ķ�����
extern int LastRecvPower[30][4][12];//���������յ��Ĺ���

// CDlgMainShow �Ի���

IMPLEMENT_DYNAMIC(CDlgMainShow, CPropertyPage)

CDlgMainShow::CDlgMainShow()
	: CPropertyPage(CDlgMainShow::IDD)
{

}

CDlgMainShow::~CDlgMainShow()
{
}

void CDlgMainShow::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART_SHOW1_01, m_CtlTChart1_01);
	DDX_Control(pDX, IDC_TCHART_SHOW1_02, m_CtlTChart1_02);
	DDX_Control(pDX, IDC_TCHART_SHOW1_03, m_CtlTChart1_03);
	DDX_Control(pDX, IDC_TCHART_SHOW1_04, m_CtlTChart1_04);
	DDX_Control(pDX, IDC_TCHART_SHOW1_05, m_CtlTChart1_05);
	DDX_Control(pDX, IDC_TCHART_SHOW1_06, m_CtlTChart1_06);
	DDX_Control(pDX, IDC_TCHART_SHOW1_07, m_CtlTChart1_07);
	DDX_Control(pDX, IDC_TCHART_SHOW1_08, m_CtlTChart1_08);
	DDX_Control(pDX, IDC_TCHART_SHOW1_09, m_CtlTChart1_09);
	DDX_Control(pDX, IDC_TCHART_SHOW1_10, m_CtlTChart1_10);
	DDX_Control(pDX, IDC_TCHART_SHOW1_11, m_CtlTChart1_11);
	DDX_Control(pDX, IDC_TCHART_SHOW1_12, m_CtlTChart1_12);
	DDX_Control(pDX, IDC_TCHART_SHOW2_01, m_CtlTChart2_01);
	DDX_Control(pDX, IDC_TCHART_SHOW2_02, m_CtlTChart2_02);
	DDX_Control(pDX, IDC_TCHART_SHOW2_03, m_CtlTChart2_03);
	DDX_Control(pDX, IDC_TCHART_SHOW2_04, m_CtlTChart2_04);
	DDX_Control(pDX, IDC_TCHART_SHOW2_05, m_CtlTChart2_05);
	DDX_Control(pDX, IDC_TCHART_SHOW2_06, m_CtlTChart2_06);
	DDX_Control(pDX, IDC_TCHART_SHOW2_07, m_CtlTChart2_07);
	DDX_Control(pDX, IDC_TCHART_SHOW2_08, m_CtlTChart2_08);
	DDX_Control(pDX, IDC_TCHART_SHOW2_09, m_CtlTChart2_09);
	DDX_Control(pDX, IDC_TCHART_SHOW2_10, m_CtlTChart2_10);
	DDX_Control(pDX, IDC_TCHART_SHOW2_11, m_CtlTChart2_11);
	DDX_Control(pDX, IDC_TCHART_SHOW2_12, m_CtlTChart2_12);
	DDX_Control(pDX, IDC_TCHART_SHOW3_01, m_CtlTChart3_01);
	DDX_Control(pDX, IDC_TCHART_SHOW3_02, m_CtlTChart3_02);
	DDX_Control(pDX, IDC_TCHART_SHOW3_03, m_CtlTChart3_03);
	DDX_Control(pDX, IDC_TCHART_SHOW3_04, m_CtlTChart3_04);
	DDX_Control(pDX, IDC_TCHART_SHOW3_05, m_CtlTChart3_05);
	DDX_Control(pDX, IDC_TCHART_SHOW3_06, m_CtlTChart3_06);
	DDX_Control(pDX, IDC_TCHART_SHOW3_07, m_CtlTChart3_07);
	DDX_Control(pDX, IDC_TCHART_SHOW3_08, m_CtlTChart3_08);
	DDX_Control(pDX, IDC_TCHART_SHOW3_09, m_CtlTChart3_09);
	DDX_Control(pDX, IDC_TCHART_SHOW3_10, m_CtlTChart3_10);
	DDX_Control(pDX, IDC_TCHART_SHOW3_11, m_CtlTChart3_11);
	DDX_Control(pDX, IDC_TCHART_SHOW3_12, m_CtlTChart3_12);
	DDX_Control(pDX, IDC_TCHART_SHOW4_01, m_CtlTChart4_01);
	DDX_Control(pDX, IDC_TCHART_SHOW4_02, m_CtlTChart4_02);
	DDX_Control(pDX, IDC_TCHART_SHOW4_03, m_CtlTChart4_03);
	DDX_Control(pDX, IDC_TCHART_SHOW4_04, m_CtlTChart4_04);
	DDX_Control(pDX, IDC_TCHART_SHOW4_05, m_CtlTChart4_05);
	DDX_Control(pDX, IDC_TCHART_SHOW4_06, m_CtlTChart4_06);
	DDX_Control(pDX, IDC_TCHART_SHOW4_07, m_CtlTChart4_07);
	DDX_Control(pDX, IDC_TCHART_SHOW4_08, m_CtlTChart4_08);
	DDX_Control(pDX, IDC_TCHART_SHOW4_09, m_CtlTChart4_09);
	DDX_Control(pDX, IDC_TCHART_SHOW4_10, m_CtlTChart4_10);
	DDX_Control(pDX, IDC_TCHART_SHOW4_11, m_CtlTChart4_11);
	DDX_Control(pDX, IDC_TCHART_SHOW4_12, m_CtlTChart4_12);
}


BEGIN_MESSAGE_MAP(CDlgMainShow, CPropertyPage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgMainShow ��Ϣ�������


void CDlgMainShow::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}


BOOL CDlgMainShow::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_CtlTChart1_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart1_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ

	m_CtlTChart2_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart2_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ


	m_CtlTChart3_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart3_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ


	m_CtlTChart4_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	m_CtlTChart4_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgMainShow::ShowData(void)
{
	if (LastAlarmStatus[UserSelectReader-1][0][0]==0)
	{
		m_CtlTChart1_01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][0]);//�趨�¶�ֵ
		m_CtlTChart1_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][0]==1)
	{
		m_CtlTChart1_01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][0]);//�趨�¶�ֵ
		m_CtlTChart1_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][1]==0)
	{
		m_CtlTChart1_02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][1]);//�趨�¶�ֵ
		m_CtlTChart1_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][1]==1)
	{
		m_CtlTChart1_02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][1]);//�趨�¶�ֵ
		m_CtlTChart1_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][2]==0)
	{
		m_CtlTChart1_03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][2]);//�趨�¶�ֵ
		m_CtlTChart1_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][2]==1)
	{
		m_CtlTChart1_03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][2]);//�趨�¶�ֵ
		m_CtlTChart1_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][3]==0)
	{
		m_CtlTChart1_04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][3]);//�趨�¶�ֵ
		m_CtlTChart1_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][3]==1)
	{
		m_CtlTChart1_04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][3]);//�趨�¶�ֵ
		m_CtlTChart1_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][4]==0)
	{
		m_CtlTChart1_05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][4]);//�趨�¶�ֵ
		m_CtlTChart1_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][4]==1)
	{
		m_CtlTChart1_05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][4]);//�趨�¶�ֵ
		m_CtlTChart1_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][5]==0)
	{
		m_CtlTChart1_06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][5]);//�趨�¶�ֵ
		m_CtlTChart1_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][5]==1)
	{
		m_CtlTChart1_06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][5]);//�趨�¶�ֵ
		m_CtlTChart1_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][6]==0)
	{
		m_CtlTChart1_07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][6]);//�趨�¶�ֵ
		m_CtlTChart1_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][6]==1)
	{
		m_CtlTChart1_07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][6]);//�趨�¶�ֵ
		m_CtlTChart1_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][7]==0)
	{
		m_CtlTChart1_08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][7]);//�趨�¶�ֵ
		m_CtlTChart1_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][7]==1)
	{
		m_CtlTChart1_08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][7]);//�趨�¶�ֵ
		m_CtlTChart1_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][8]==0)
	{
		m_CtlTChart1_09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][8]);//�趨�¶�ֵ
		m_CtlTChart1_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][8]==1)
	{
		m_CtlTChart1_09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][8]);//�趨�¶�ֵ
		m_CtlTChart1_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][9]==0)
	{
		m_CtlTChart1_10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][9]);//�趨�¶�ֵ
		m_CtlTChart1_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][9]==1)
	{
		m_CtlTChart1_10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][9]);//�趨�¶�ֵ
		m_CtlTChart1_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][10]==0)
	{
		m_CtlTChart1_11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][10]);//�趨�¶�ֵ
		m_CtlTChart1_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][10]==1)
	{
		m_CtlTChart1_11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][10]);//�趨�¶�ֵ
		m_CtlTChart1_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][0][11]==0)
	{
		m_CtlTChart1_12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][11]);//�趨�¶�ֵ
		m_CtlTChart1_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][0][11]==1)
	{
		m_CtlTChart1_12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][0][11]);//�趨�¶�ֵ
		m_CtlTChart1_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart1_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart1_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][0]==0)
	{
		m_CtlTChart2_01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][0]);//�趨�¶�ֵ
		m_CtlTChart2_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][0]==1)
	{
		m_CtlTChart2_01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][0]);//�趨�¶�ֵ
		m_CtlTChart2_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][1]==0)
	{
		m_CtlTChart2_02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][1]);//�趨�¶�ֵ
		m_CtlTChart2_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][1]==1)
	{
		m_CtlTChart2_02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][1]);//�趨�¶�ֵ
		m_CtlTChart2_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][2]==0)
	{
		m_CtlTChart2_03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][2]);//�趨�¶�ֵ
		m_CtlTChart2_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][2]==1)
	{
		m_CtlTChart2_03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][2]);//�趨�¶�ֵ
		m_CtlTChart2_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][3]==0)
	{
		m_CtlTChart2_04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][3]);//�趨�¶�ֵ
		m_CtlTChart2_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][3]==1)
	{
		m_CtlTChart2_04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][3]);//�趨�¶�ֵ
		m_CtlTChart2_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][4]==0)
	{
		m_CtlTChart2_05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][4]);//�趨�¶�ֵ
		m_CtlTChart2_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][4]==1)
	{
		m_CtlTChart2_05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][4]);//�趨�¶�ֵ
		m_CtlTChart2_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][5]==0)
	{
		m_CtlTChart2_06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][5]);//�趨�¶�ֵ
		m_CtlTChart2_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][5]==1)
	{
		m_CtlTChart2_06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][5]);//�趨�¶�ֵ
		m_CtlTChart2_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][6]==0)
	{
		m_CtlTChart2_07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][6]);//�趨�¶�ֵ
		m_CtlTChart2_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][6]==1)
	{
		m_CtlTChart2_07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][6]);//�趨�¶�ֵ
		m_CtlTChart2_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][7]==0)
	{
		m_CtlTChart2_08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][7]);//�趨�¶�ֵ
		m_CtlTChart2_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][7]==1)
	{
		m_CtlTChart2_08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][7]);//�趨�¶�ֵ
		m_CtlTChart2_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][8]==0)
	{
		m_CtlTChart2_09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][8]);//�趨�¶�ֵ
		m_CtlTChart2_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][8]==1)
	{
		m_CtlTChart2_09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][8]);//�趨�¶�ֵ
		m_CtlTChart2_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][9]==0)
	{
		m_CtlTChart2_10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][9]);//�趨�¶�ֵ
		m_CtlTChart2_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][9]==1)
	{
		m_CtlTChart2_10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][9]);//�趨�¶�ֵ
		m_CtlTChart2_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][10]==0)
	{
		m_CtlTChart2_11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][10]);//�趨�¶�ֵ
		m_CtlTChart2_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][10]==1)
	{
		m_CtlTChart2_11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][10]);//�趨�¶�ֵ
		m_CtlTChart2_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][1][11]==0)
	{
		m_CtlTChart2_12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][11]);//�趨�¶�ֵ
		m_CtlTChart2_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][1][11]==1)
	{
		m_CtlTChart2_12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][11]);//�趨�¶�ֵ
		m_CtlTChart2_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart2_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart2_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][0]==0)
	{
		m_CtlTChart3_01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][0]);//�趨�¶�ֵ
		m_CtlTChart3_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][0]==1)
	{
		m_CtlTChart3_01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][0]);//�趨�¶�ֵ
		m_CtlTChart3_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][1]==0)
	{
		m_CtlTChart3_02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][1]);//�趨�¶�ֵ
		m_CtlTChart3_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][1]==1)
	{
		m_CtlTChart3_02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][1]);//�趨�¶�ֵ
		m_CtlTChart3_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][2]==0)
	{
		m_CtlTChart3_03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][2]);//�趨�¶�ֵ
		m_CtlTChart3_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][2]==1)
	{
		m_CtlTChart3_03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][2]);//�趨�¶�ֵ
		m_CtlTChart3_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][3]==0)
	{
		m_CtlTChart3_04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][3]);//�趨�¶�ֵ
		m_CtlTChart3_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][3]==1)
	{
		m_CtlTChart3_04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][3]);//�趨�¶�ֵ
		m_CtlTChart3_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][4]==0)
	{
		m_CtlTChart3_05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][4]);//�趨�¶�ֵ
		m_CtlTChart3_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][4]==1)
	{
		m_CtlTChart3_05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][4]);//�趨�¶�ֵ
		m_CtlTChart3_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][5]==0)
	{
		m_CtlTChart3_06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][5]);//�趨�¶�ֵ
		m_CtlTChart3_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][5]==1)
	{
		m_CtlTChart3_06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][5]);//�趨�¶�ֵ
		m_CtlTChart3_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][6]==0)
	{
		m_CtlTChart3_07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][6]);//�趨�¶�ֵ
		m_CtlTChart3_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][6]==1)
	{
		m_CtlTChart3_07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][6]);//�趨�¶�ֵ
		m_CtlTChart3_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][7]==0)
	{
		m_CtlTChart3_08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][7]);//�趨�¶�ֵ
		m_CtlTChart3_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][7]==1)
	{
		m_CtlTChart3_08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][7]);//�趨�¶�ֵ
		m_CtlTChart3_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][8]==0)
	{
		m_CtlTChart3_09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][8]);//�趨�¶�ֵ
		m_CtlTChart3_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][8]==1)
	{
		m_CtlTChart3_09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][8]);//�趨�¶�ֵ
		m_CtlTChart3_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][9]==0)
	{
		m_CtlTChart3_10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][9]);//�趨�¶�ֵ
		m_CtlTChart3_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][9]==1)
	{
		m_CtlTChart3_10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][9]);//�趨�¶�ֵ
		m_CtlTChart3_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][10]==0)
	{
		m_CtlTChart3_11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][10]);//�趨�¶�ֵ
		m_CtlTChart3_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][10]==1)
	{
		m_CtlTChart3_11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][10]);//�趨�¶�ֵ
		m_CtlTChart3_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][2][11]==0)
	{
		m_CtlTChart3_12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][11]);//�趨�¶�ֵ
		m_CtlTChart3_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][2][11]==1)
	{
		m_CtlTChart3_12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][2][11]);//�趨�¶�ֵ
		m_CtlTChart3_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart3_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart3_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][0]==0)
	{
		m_CtlTChart4_01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][0]);//�趨�¶�ֵ
		m_CtlTChart4_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][0]==1)
	{
		m_CtlTChart4_01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][0]);//�趨�¶�ֵ
		m_CtlTChart4_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][1]==0)
	{
		m_CtlTChart4_02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][1]);//�趨�¶�ֵ
		m_CtlTChart4_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][1]==1)
	{
		m_CtlTChart4_02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][1]);//�趨�¶�ֵ
		m_CtlTChart4_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][2]==0)
	{
		m_CtlTChart4_03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][2]);//�趨�¶�ֵ
		m_CtlTChart4_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][2]==1)
	{
		m_CtlTChart4_03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][2]);//�趨�¶�ֵ
		m_CtlTChart4_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][3]==0)
	{
		m_CtlTChart4_04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][3]);//�趨�¶�ֵ
		m_CtlTChart4_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][3]==1)
	{
		m_CtlTChart4_04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][3]);//�趨�¶�ֵ
		m_CtlTChart4_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][4]==0)
	{
		m_CtlTChart4_05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][4]);//�趨�¶�ֵ
		m_CtlTChart4_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][4]==1)
	{
		m_CtlTChart4_05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][4]);//�趨�¶�ֵ
		m_CtlTChart4_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][5]==0)
	{
		m_CtlTChart4_06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][5]);//�趨�¶�ֵ
		m_CtlTChart4_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][5]==1)
	{
		m_CtlTChart4_06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][5]);//�趨�¶�ֵ
		m_CtlTChart4_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][6]==0)
	{
		m_CtlTChart4_07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][6]);//�趨�¶�ֵ
		m_CtlTChart4_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][6]==1)
	{
		m_CtlTChart4_07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][6]);//�趨�¶�ֵ
		m_CtlTChart4_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][7]==0)
	{
		m_CtlTChart4_08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][7]);//�趨�¶�ֵ
		m_CtlTChart4_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][7]==1)
	{
		m_CtlTChart4_08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][7]);//�趨�¶�ֵ
		m_CtlTChart4_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][8]==0)
	{
		m_CtlTChart4_09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][8]);//�趨�¶�ֵ
		m_CtlTChart4_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][8]==1)
	{
		m_CtlTChart4_09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][8]);//�趨�¶�ֵ
		m_CtlTChart4_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][9]==0)
	{
		m_CtlTChart4_10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][9]);//�趨�¶�ֵ
		m_CtlTChart4_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][9]==1)
	{
		m_CtlTChart4_10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][9]);//�趨�¶�ֵ
		m_CtlTChart4_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][10]==0)
	{
		m_CtlTChart4_11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][10]);//�趨�¶�ֵ
		m_CtlTChart4_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][10]==1)
	{
		m_CtlTChart4_11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][10]);//�趨�¶�ֵ
		m_CtlTChart4_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}

	if (LastAlarmStatus[UserSelectReader-1][3][11]==0)
	{
		m_CtlTChart4_12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][11]);//�趨�¶�ֵ
		m_CtlTChart4_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	} 
	else if (LastAlarmStatus[UserSelectReader-1][3][11]==1)
	{
		m_CtlTChart4_12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][3][11]);//�趨�¶�ֵ
		m_CtlTChart4_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
	}else
	{
		m_CtlTChart4_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
		m_CtlTChart4_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
	}
}
