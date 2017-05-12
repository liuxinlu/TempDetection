// DlgShowAnt2.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgShowAnt2.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern double LastRecvTemp[30][4][12];//保存最新收到的温度数据，-1000，-2000，-3000表示状态，其他为正常数据
extern int LastAlarmStatus[30][4][12];//保存报警状态，0为无警报，1为有警报，2，3，4表示状态，其他为正常数据
extern int UserSelectReader;//用户选择的读卡器
extern int LastRecvPower[30][4][12];//保存最新收到的功率，-1000，-2000，-3000表示状态，其他为正常数据

// CDlgShowAnt2 对话框

IMPLEMENT_DYNAMIC(CDlgShowAnt2, CPropertyPage)

CDlgShowAnt2::CDlgShowAnt2()
	: CPropertyPage(CDlgShowAnt2::IDD)
{

}

CDlgShowAnt2::~CDlgShowAnt2()
{
}

void CDlgShowAnt2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART_SHOW01, m_CtlTChart01);
	DDX_Control(pDX, IDC_TCHART_SHOW02, m_CtlTChart02);
	DDX_Control(pDX, IDC_TCHART_SHOW03, m_CtlTChart03);
	DDX_Control(pDX, IDC_TCHART_SHOW04, m_CtlTChart04);
	DDX_Control(pDX, IDC_TCHART_SHOW05, m_CtlTChart05);
	DDX_Control(pDX, IDC_TCHART_SHOW06, m_CtlTChart06);
	DDX_Control(pDX, IDC_TCHART_SHOW07, m_CtlTChart07);
	DDX_Control(pDX, IDC_TCHART_SHOW08, m_CtlTChart08);
	DDX_Control(pDX, IDC_TCHART_SHOW09, m_CtlTChart09);
	DDX_Control(pDX, IDC_TCHART_SHOW10, m_CtlTChart10);
	DDX_Control(pDX, IDC_TCHART_SHOW11, m_CtlTChart11);
	DDX_Control(pDX, IDC_TCHART_SHOW12, m_CtlTChart12);
	DDX_Control(pDX, IDC_TCHART_POWER1, m_CtlPowerChart01);
	DDX_Control(pDX, IDC_TCHART_POWER2, m_CtlPowerChart02);
	DDX_Control(pDX, IDC_TCHART_POWER3, m_CtlPowerChart03);
	DDX_Control(pDX, IDC_TCHART_POWER4, m_CtlPowerChart04);
	DDX_Control(pDX, IDC_TCHART_POWER5, m_CtlPowerChart05);
	DDX_Control(pDX, IDC_TCHART_POWER6, m_CtlPowerChart06);
	DDX_Control(pDX, IDC_TCHART_POWER7, m_CtlPowerChart07);
	DDX_Control(pDX, IDC_TCHART_POWER8, m_CtlPowerChart08);
	DDX_Control(pDX, IDC_TCHART_POWER9, m_CtlPowerChart09);
	DDX_Control(pDX, IDC_TCHART_POWER10, m_CtlPowerChart10);
	DDX_Control(pDX, IDC_TCHART_POWER11, m_CtlPowerChart11);
	DDX_Control(pDX, IDC_TCHART_POWER12, m_CtlPowerChart12);
}


BEGIN_MESSAGE_MAP(CDlgShowAnt2, CPropertyPage)
END_MESSAGE_MAP()


// CDlgShowAnt2 消息处理程序


BOOL CDlgShowAnt2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart01.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart02.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart03.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart04.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart05.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart06.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart07.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart08.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart09.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart10.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart11.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
	m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText("未知位置");//设定备注信息
	m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
	m_CtlTChart12.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//设定单位字体颜色
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;//获取MainFrame指针
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgShowAnt2::ShowData(void)
{
	switch (LastAlarmStatus[UserSelectReader-1][1][0])
	{
	case 0:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][0]);//设定温度值
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][0]);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][0]);//设定温度值
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][0]);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][1])
	{
	case 0:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][1]);//设定温度值
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][1]);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][1]);//设定温度值
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][1]);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][2])
	{
	case 0:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][2]);//设定温度值
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][2]);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][2]);//设定温度值
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][2]);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][3])
	{
	case 0:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][3]);//设定温度值
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][3]);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][3]);//设定温度值
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][3]);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][4])
	{
	case 0:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][4]);//设定温度值
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][4]);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][4]);//设定温度值
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][4]);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][5])
	{
	case 0:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][5]);//设定温度值
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][5]);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][5]);//设定温度值
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][5]);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][6])
	{
	case 0:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][6]);//设定温度值
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][6]);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][6]);//设定温度值
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][6]);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][7])
	{
	case 0:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][7]);//设定温度值
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][7]);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][7]);//设定温度值
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][7]);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][8])
	{
	case 0:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][8]);//设定温度值
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][8]);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][8]);//设定温度值
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][8]);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][9])
	{
	case 0:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][9]);//设定温度值
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][9]);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][9]);//设定温度值
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][9]);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][10])
	{
	case 0:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][10]);//设定温度值
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][10]);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][10]);//设定温度值
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][10]);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[UserSelectReader-1][1][11])
	{
	case 0:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][11]);//设定温度值
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//设定温度字体颜色
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][11]);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[UserSelectReader-1][1][11]);//设定温度值
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//设定温度字体颜色
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[UserSelectReader-1][1][11]);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//设定温度值
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//设定温度字体颜色
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}
}
