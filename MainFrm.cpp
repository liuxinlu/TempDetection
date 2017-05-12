
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "TempDetection.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include <windows.h>

#include "MainFrm.h"
#include "TempDetectionView.h"
#include "OnDrawView.h"
#include "ShowMessageView.h"
#include "CommEdit.h"
#include "DlgCalibrate.h"
#include "DlgConfig.h"
#include "DlgMainShow.h"
#include "DlgPosition.h"
#include "DlgUserSet.h"
#include "DlgFactorySet.h"
#include "DlgUpdateFirmware.h"
#include "DlgChangeUser.h"
#include "DlgPowerControl.h"
#include "DlgAlarmHistory.h"
#include "DlgSetAlarm.h"
#include "DlgModifyReaderID.h"
#include "DlgCtlSingleReader.h"

static bool EnableTimer=FALSE;
static long SetTime=30;
LARGE_INTEGER litmp;
LONGLONG llQFreq,llQPartOld,llQPartNew;
double fFreq;

UINT OneMilliSecondProc(LPVOID lParam); //������ʱ������

UINT OneMilliSecondProc(LPVOID lParam)
{
	CMainFrame* pDlg = (CMainFrame*)lParam;
	LARGE_INTEGER frequence, privious, current, interval; 
	if(!QueryPerformanceFrequency( &frequence)) 
	{ 
		::MessageBox(NULL, "Your computer hardware doesn't support the high-resolution performance counter", 
			"Not Support", MB_ICONEXCLAMATION | MB_OK); //����������ʾ��Ϣ 
		return 0;
	} 
	interval.QuadPart = frequence.QuadPart * SetTime / 1000; 
	QueryPerformanceCounter( &current ); 
	while(EnableTimer)
	{
		privious = current; 
		while( current.QuadPart - privious.QuadPart < interval.QuadPart ) 
			QueryPerformanceCounter(&current);
		::SendMessage(pDlg->m_hWnd,WM_UPDATETIME,0,0);//������Ϣ֪ͨ�Ի���ø���ʱ����
	}
	return 0;
}

IMPLEMENT_DYNAMIC(CCommSplitWnd, CSplitterWnd)//20:00

CCommSplitWnd::CCommSplitWnd()//20:00
{
}

CCommSplitWnd::~CCommSplitWnd()//20:00
{
}
BEGIN_MESSAGE_MAP(CCommSplitWnd, CSplitterWnd)//20:00

END_MESSAGE_MAP()//20:00

int CCommSplitWnd::HitTest(CPoint pt)const
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ASSERT_VALID(this);
	//return CSplitterWnd::OnSetCursor(pWnd, nHitTest, message);
	return 0;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char StartCMD[15]       ={0x00,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//��ʼ
char StopCMD[15]        ={0x00,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//ֹͣ
char CallReaderCMD[15]  ={0x00,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//����
char SynchronousCMD[15] ={0x00,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//ͬ��

int CalibrateFlag;//У׼�ı�־��1Ϊ��ʼУ׼���棬0ΪֹͣУ׼

_ConnectionPtr m_pConnection;
CString SystemIniFilePath;//����ϵͳ��ز������ļ�
CString SystemLogPath;//����ϵͳ����log
CString DBFilePath;//���ݿ��ļ�·��
CString RecordID;//ÿ�β����ļ�¼ID
unsigned int m_FreqData[30][4][12]={0};//У׼���棺�����յ������µ�Ƶ��ֵ
float m_TempData[30][4][12]={0};//У׼���棺�����յ������µ��¶�ֵ
int WrongFlagCount[4][12]={0};//��Ϊ�յ�״̬��Ϣ�ļ�����ÿ������ֵ��3�����ж���
int UserSetAlarmHigh;//�����û����õı�����ֵ����
int UserSetAlarmLow;//�����û����õı�����ֵ����
int AlarmCount;//��¼��������Ϣ����
bool AlarmSound;
bool PortOpenFlag;//true�Ѿ��� falseδ�򿪶˿�
bool StartFlag;//��ʼ�ı�־��1Ϊ��ʼ��0Ϊֹͣ
int ReceiveDataCount;//�����������
int LoginDomainSet;//Ȩ�����ñ�־��0Ϊ����Ա��1Ϊһ���û�
CString LoginName;
int UserDefineReader[30]={0};//������ʹ��״̬
CStringArray strReaderPositionArray;//���������λ����Ϣ30��С
CStringArray strSensorPositionArray;//���洫����λ����Ϣ30*4*12��С
int AlarmTempSave[2][30]={0};//���汨���¶ȣ�0Ϊ���£�1Ϊ����
int SensorPowerSet[30][4][12]={0};//���洫����˥��ֵ
int UserSelectReader;//�û�ѡ��Ķ�����
int UserSetLoopTime;//�û��趨��ѯʱ��
double LastRecvTemp[30][4][12]={0};//���������յ����¶�����
int LastRecvPower[30][4][12]={0};//���������յ��Ĺ���
int LastAlarmStatus[30][4][12]={0};//���汨��״̬��0Ϊ�޾�����1Ϊ�о�����2��3��4��ʾ״̬������Ϊ��������
int UserSelectReaderForCal;//У׼���棺�û�ѡ��Ķ�����
int UserSetSynchronous;//�û��趨ͬ��ָ��ķ��ͼ��
int SynchronousCount;//��¼���͵���ָ��ĸ��������ڷ���ͬ��ָ��
bool SendCMDStatus;//��������״̬����falseΪ����ͬ��ָ�trueΪ���͵���ָ��
bool Menu_Communicate;
bool Menu_Exit;
bool Menu_StartMem;
bool Menu_StopMem;
bool Menu_Refresh;
bool Menu_Calibration;
bool Menu_UserSetPosition;
bool Menu_ReaderConfig;
bool Menu_PowerControl;
bool Menu_UpdateFirmware;
bool Menu_FactorySet;
bool Menu_UserSet;
bool Menu_ModifyReaderID;
bool Menu_ScanReader;
bool Menu_CtlSingleReader;
bool Menu_ChangeUser;
bool Menu_ShowAlarmHistory;
bool Menu_SetSilent;
bool Menu_SetAlarmTemp;

#define ID_TIMER_LOOP 1
#define ID_TIMER_WAIT 2
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_UPDATE_COMMAND_UI(ID_COMMUNICATE, &CMainFrame::OnUpdateCommunicate)
	ON_COMMAND(ID_CALIBRATION, &CMainFrame::OnCalibration)
	ON_UPDATE_COMMAND_UI(ID_USER_SET_POSITION, &CMainFrame::OnUpdateUserSetPosition)
	ON_COMMAND(ID_COMMUNICATE, &CMainFrame::OnCommunicate)
	ON_UPDATE_COMMAND_UI(ID_CALIBRATION, &CMainFrame::OnUpdateCalibration)
	ON_COMMAND(ID_USER_SET_POSITION, &CMainFrame::OnUserSetPosition)
	ON_COMMAND(ID_EXIT, &CMainFrame::OnExit)
	ON_UPDATE_COMMAND_UI(ID_EXIT, &CMainFrame::OnUpdateExit)
	ON_COMMAND(ID_READER_CONFIG, &CMainFrame::OnReaderConfig)
	ON_UPDATE_COMMAND_UI(ID_READER_CONFIG, &CMainFrame::OnUpdateReaderConfig)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_USER_SET, &CMainFrame::OnUserSet)
	ON_UPDATE_COMMAND_UI(ID_USER_SET, &CMainFrame::OnUpdateUserSet)
	ON_COMMAND(ID_FACTORY_SET, &CMainFrame::OnFactorySet)
	ON_UPDATE_COMMAND_UI(ID_FACTORY_SET, &CMainFrame::OnUpdateFactorySet)
	ON_COMMAND(ID_UPDATE_FIRMWARE, &CMainFrame::OnUpdateFirmware)
	ON_UPDATE_COMMAND_UI(ID_UPDATE_FIRMWARE, &CMainFrame::OnUpdateUpdateFirmware)
	ON_COMMAND(ID_START_MEM, &CMainFrame::OnStartMem)
	ON_UPDATE_COMMAND_UI(ID_START_MEM, &CMainFrame::OnUpdateStartMem)
	ON_COMMAND(ID_STOP_MEM, &CMainFrame::OnStopMem)
	ON_UPDATE_COMMAND_UI(ID_STOP_MEM, &CMainFrame::OnUpdateStopMem)
	ON_COMMAND(ID_CHANGE_USER, &CMainFrame::OnChangeUser)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_USER, &CMainFrame::OnUpdateChangeUser)
	ON_COMMAND(ID_POWER_CONTROL, &CMainFrame::OnPowerControl)
	ON_UPDATE_COMMAND_UI(ID_POWER_CONTROL, &CMainFrame::OnUpdatePowerControl)
	ON_COMMAND(ID_REFRESH, &CMainFrame::OnRefresh)
	ON_UPDATE_COMMAND_UI(ID_REFRESH, &CMainFrame::OnUpdateRefresh)
	ON_COMMAND(ID_SET_ALARM_TEMP, &CMainFrame::OnSetAlarmTemp)
	ON_UPDATE_COMMAND_UI(ID_SET_ALARM_TEMP, &CMainFrame::OnUpdateSetAlarmTemp)
	ON_COMMAND(ID_SET_SILENT, &CMainFrame::OnSetSilent)
	ON_UPDATE_COMMAND_UI(ID_SET_SILENT, &CMainFrame::OnUpdateSetSilent)
	ON_COMMAND(ID_SHOW_ALARM_HISTORY, &CMainFrame::OnShowAlarmHistory)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ALARM_HISTORY, &CMainFrame::OnUpdateShowAlarmHistory)
	ON_COMMAND(ID_SCAN_READER, &CMainFrame::OnScanReader)
	ON_UPDATE_COMMAND_UI(ID_SCAN_READER, &CMainFrame::OnUpdateScanReader)
	ON_COMMAND(ID_CTL_SINGLE_READER, &CMainFrame::OnCtlSingleReader)
	ON_UPDATE_COMMAND_UI(ID_CTL_SINGLE_READER, &CMainFrame::OnUpdateCtlSingleReader)
	ON_COMMAND(ID_MODIFY_READR_ID, &CMainFrame::OnModifyReadrId)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_READR_ID, &CMainFrame::OnUpdateModifyReadrId)
	ON_WM_TIMER()
	ON_MESSAGE(WM_UPDATETIME,OnUpdateTime)      //������Ϣӳ��
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_CONDITION,
	//ID_LOGIN_USER,
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
	: CountLoop(0)
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);

	PortOpenFlag=FALSE;
	StartFlag=0;
	CalibrateFlag=0;

	Menu_Communicate=TRUE;
	Menu_Exit=TRUE;
	Menu_StartMem=FALSE;
	Menu_StopMem=FALSE;
	Menu_Refresh=FALSE;
	Menu_Calibration=FALSE;
	Menu_UserSetPosition=FALSE;
	Menu_ReaderConfig=FALSE;
	Menu_PowerControl=FALSE;
	Menu_UpdateFirmware=FALSE;
	Menu_FactorySet=FALSE;
	Menu_UserSet=FALSE;
	Menu_ChangeUser=TRUE;
	Menu_ScanReader=FALSE;
	Menu_CtlSingleReader=FALSE;
	Menu_ShowAlarmHistory=FALSE;
	Menu_SetAlarmTemp=FALSE;
	Menu_ModifyReaderID=FALSE;

	TIMECAPS tc;
	MMRESULT bError;

	//���ú���timeGetDevCapsȡ��ϵͳ�ֱ��ʵ�ȡֵ��Χ������д����˳�
	bError=timeGetDevCaps(&tc,sizeof(TIMECAPS)); 
	if(!bError==TIMERR_NOERROR) 	
	{ 
		MessageBox("Get system accuracy failed!");
	}
	// �ֱ��ʵ�ֵ���ܳ���ϵͳ��ȡֵ��Χ 
	wAccuracy=min(max(tc.wPeriodMin,TIMER_ACCURACY),tc.wPeriodMax);
	//����timeBeginPeriod�������ö�ʱ���ķֱ��� 
	timeBeginPeriod(wAccuracy); 
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	////���ÿ�����ϽǵĹرհ�ť/////////////////////////
	CMenu* pMenu=GetSystemMenu(FALSE);
	int x=pMenu->GetMenuItemCount();
	UINT pID=pMenu->GetMenuItemID(x-1);
	pMenu-> EnableMenuItem(pID,MF_DISABLED);//��ϵͳ�رղ˵���� 

	if (!m_wndStatusBar.Create(this) ||!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // fail to create
	}	
	//CString strToolBarName;
	//bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	//ASSERT(bNameValid);
	//m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// �����û�����Ĺ���������:
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("δ�ܴ���״̬��\n");
	//	return -1;      // δ�ܴ���
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	//m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	// ���ù�������ͣ�����ڲ˵��滻
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	//CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// �����û�����Ĺ�����ͼ��
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
	//CList<UINT, UINT> lstBasicCommands;

	//lstBasicCommands.AddTail(ID_FILE_NEW);
	//lstBasicCommands.AddTail(ID_FILE_OPEN);
	//lstBasicCommands.AddTail(ID_FILE_SAVE);
	//lstBasicCommands.AddTail(ID_FILE_PRINT);
	//lstBasicCommands.AddTail(ID_APP_EXIT);
	//lstBasicCommands.AddTail(ID_EDIT_CUT);
	//lstBasicCommands.AddTail(ID_EDIT_PASTE);
	//lstBasicCommands.AddTail(ID_EDIT_UNDO);
	//lstBasicCommands.AddTail(ID_APP_ABOUT);
	//lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	//lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	//CMFCToolBar::SetBasicCommands(lstBasicCommands);
	if(!m_MSComm.Create(NULL,0,CRect(0,0,0,0),this,IDC_MSCOMM1)) 
	{ 
		AfxMessageBox( "�����ؼ�ʧ�� "); 
	} 
	HMODULE Positionmodule = GetModuleHandle(0); 
	char pPositionFileName[MAX_PATH]; 
	GetModuleFileName(Positionmodule, pPositionFileName, MAX_PATH); 

	CString csPositionFullPath(pPositionFileName); 
	int nPos = csPositionFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		AfxMessageBox("�Ҳ���SystemInstall.ini�����ļ�"); 
	SystemIniFilePath=csPositionFullPath.Left( nPos ); 
	SystemLogPath=SystemIniFilePath+"\\SysLog.log";
	SystemIniFilePath=SystemIniFilePath+"\\SystemInstall.ini";

	CreateDataBase();

	//����״̬����ʾ��½�û���
	SetStatusBar(2,"��¼�û�"+LoginName);

	ReadPositionFromDB();
	ReadINIFile(SystemIniFilePath);	
	
	QueryPerformanceFrequency(&litmp);
	llQFreq=litmp.QuadPart;
	fFreq=(double)llQFreq;

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	//return m_wndSplitter.Create(this,
	//	2, 2,               // TODO: ��������������
	//	CSize(10, 10),      // TODO: ������С�����С
	//	pContext);
	CRect rs;  
	GetClientRect(&rs);  //�õ�������CFormView�Ĵ�С��λ��   
	//---------------------------------------------------------
	//m_wndSpliter,m_wndSpliter2��Ϊ��Ա������CSplitterWnd���
	//CTest1,CTest2,CTest3���̳���CView
	//---------------------------------------------------------
	//��һ�ηָ�������������
	m_wndSplitter.CreateStatic( this, 1, 2 );
	m_wndSplitter.SetColumnInfo( 0, rs.right/6, 50 );

	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CTempDetectionView), CSize(rs.right/6, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(COnDrawView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	////�ڶ��ηָ�������������
	//m_wndSplitterLeft.CreateStatic( &m_wndSplitter, 2, 1, WS_CHILD|WS_VISIBLE, m_wndSplitter.IdFromRowCol(0,0) );
	//m_wndSplitterLeft.CreateView( 0, 0, RUNTIME_CLASS(CTempDetectionView), CSize(0,0), pContext );
	//m_wndSplitterLeft.CreateView( 1, 0, RUNTIME_CLASS(CAlarmSetView), CSize(0,0), pContext );
	//m_wndSplitterLeft.SetRowInfo( 0, rs.bottom*2/3, 50 );

	//m_wndSplitterRight.CreateStatic( &m_wndSplitter, 2, 1, WS_CHILD|WS_VISIBLE, m_wndSplitter.IdFromRowCol(0,1) );
	//m_wndSplitterRight.CreateView( 0, 0, RUNTIME_CLASS(COnDrawView), CSize(0,0), pContext );
	//m_wndSplitterRight.CreateView( 1, 0, RUNTIME_CLASS(CShowMessageView), CSize(0,0), pContext );
	//m_wndSplitterRight.SetRowInfo( 0, rs.bottom*7/8, 50 );
	return TRUE; //��Ҫ
	// activate the input view
	SetActiveView((CView*)m_wndSplitter.GetPane(0,1));

	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN);
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
	cs.y = cs.cy ;
	cs.x = cs.cx;

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ���ཫִ�������Ĺ���

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnUpdateCommunicate(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_Communicate); 
}


void CMainFrame::OnUpdateUserSetPosition(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_UserSetPosition); 
}


void CMainFrame::OnUpdateCalibration(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_Calibration); 
}

void CMainFrame::OnUpdateFactorySet(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_FactorySet); 
}


void CMainFrame::OnUpdateUserSet(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_UserSet); 
}


void CMainFrame::OnUpdateChangeUser(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_ChangeUser); 
}


void CMainFrame::OnUpdatePowerControl(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_PowerControl); 
}


void CMainFrame::OnUpdateUpdateFirmware(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_UpdateFirmware); 
}

/////////////����Ϊ�ֹ���ӵĴ���///////////////////////////////////////////////

BEGIN_EVENTSINK_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_EVENTSINK_MAP(CAboutDlg)
	ON_EVENT(CMainFrame, IDC_MSCOMM1, 1, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CMainFrame::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len;
	CString TemperText,FreqText,PowerText;
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	char RecvData[15]={0};

	if(m_MSComm.GetCommEvent()==2)
	{

		variant_inp=m_MSComm.GetInput(); //��������
		safearray_inp=variant_inp;  //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
		len=safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���

		if (StartFlag==1)
		{
			for(LONG k=0;k<len;k++)
				safearray_inp.GetElement(&k,&rxdata[k+ReceiveDataCount]);//ת��ΪBYTE������
			safearray_inp.Clear();

			if (CalibrateFlag==0)
			{
				ReceiveDataCount+=len;
				if (ReceiveDataCount>=15&&rxdata[1]==67)
				{
					for (int i = 0; i < 15; i++)
					{
						RecvData[i]=rxdata[i];
					}
					WORD RecvCRC=GetCheckCode(RecvData,13);
					if ((RecvCRC&0x00ff)==rxdata[14]&&((RecvCRC&0xff00)>>8)==rxdata[13])
					{
						if (rxdata[2]==0x01)
						{
							if (rxdata[0]==UserSelectReader)
							{
								switch (rxdata[3])
								{
								case 0x00:
									MainStatusShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,rxdata[0],rxdata[4],0,0);
									MainStatusShowAnt1(rxdata[4]);
									break;
								case 0x01:
									MainStatusShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,rxdata[0],rxdata[4],0,1);
									MainStatusShowAnt2(rxdata[4]);
									break;
								case 0x02:
									MainStatusShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,rxdata[0],rxdata[4],0,2);
									MainStatusShowAnt3(rxdata[4]);
									break;
								case 0x03:
									MainStatusShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,rxdata[0],rxdata[4],0,3);
									MainStatusShowAnt4(rxdata[4]);
									break;
								default:
									break;
								}
							}
						}
						else if (rxdata[2]==0x02)
						{
							if (rxdata[0]==UserSelectReader)
							{
								switch (rxdata[3])
								{
								case 0x00:
									MainStatusShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,rxdata[0],rxdata[4],1,0);
									MainStatusShowAnt1(rxdata[4]);
									break;
								case 0x01:
									MainStatusShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,rxdata[0],rxdata[4],1,1);
									MainStatusShowAnt2(rxdata[4]);
									break;
								case 0x02:
									MainStatusShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,rxdata[0],rxdata[4],1,2);
									MainStatusShowAnt3(rxdata[4]);
									break;
								case 0x03:
									MainStatusShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,rxdata[0],rxdata[4],1,3);
									MainStatusShowAnt4(rxdata[4]);
									break;
								default:
									break;
								}
							}
						}
						else
						{
							//RecAllDataFlag=TRUE;
							//���¶����ݲ�ת��
							Temper_Data=0xffff&rxdata[6]+((0xffff&rxdata[5])<<8);
							//�չ������ݣ���ת��
							Power_Data=0xffff&rxdata[8]+((0xffff&rxdata[7])<<8);
							//��Ƶ�����ݣ���ת��
							Freq_Data=0xffffffff&rxdata[12]+((0xffffffff&rxdata[11])<<8)+((0xffffffff&rxdata[10])<<16)+((0xffffffff&rxdata[9])<<24);

							switch (rxdata[0])//��һ���⣺������ID
							{
							case 0x01://������1
								DataOperate("������1",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x02://������2
								DataOperate("������2",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x03://������3
								DataOperate("������3",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x04://������4
								DataOperate("������4",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x05://������5
								DataOperate("������5",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x06://������6
								DataOperate("������6",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x07://������7
								DataOperate("������7",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x08://������8
								DataOperate("������8",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x09://������9
								DataOperate("������9",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x0a://������10
								DataOperate("������10",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x0b://������11
								DataOperate("������11",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x0c://������12
								DataOperate("������12",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x0d://������13
								DataOperate("������13",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x0e://������14
								DataOperate("������14",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x0f://������15
								DataOperate("������15",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x10://������16
								DataOperate("������16",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x11://������17
								DataOperate("������17",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x12://������18
								DataOperate("������18",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x13://������19
								DataOperate("������19",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x14://������20
								DataOperate("������20",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x15://������21
								DataOperate("������21",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x16://������22
								DataOperate("������22",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x17://������23
								DataOperate("������23",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x18://������24
								DataOperate("������24",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x19://������25
								DataOperate("������25",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x1a://������26
								DataOperate("������26",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x1b://������27
								DataOperate("������27",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x1c://������28
								DataOperate("������28",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x1d://������29
								DataOperate("������29",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							case 0x1e://������30
								DataOperate("������30",rxdata[3],rxdata[4],Power_Data,Freq_Data,Temper_Data);
								break;
							default:
								break;
							}//switch (rxdata[1])//��һ���⣺������ID

						}
					}
					ReceiveDataCount=0;
					memset(rxdata,0,864); //ÿ�ν���ǰ��ջ�����
				}else if (ReceiveDataCount>=15&&rxdata[1]!=67)
				{
					ReceiveDataCount=0;
					memset(rxdata,0,864); //ÿ�ν���ǰ��ջ�����
				}
			} 
			else
			{
				HWND hWndSensorCalibrate=::FindWindow(NULL,"������У׼");      //�õ��Ի���ľ��
				CDlgCalibrate* pWndSensorCalibrate= (CDlgCalibrate*)FromHandle(hWndSensorCalibrate); //�ɾ���õ��Ի���Ķ���ָ��

				if (hWndSensorCalibrate)
				{
					ReceiveDataCount+=len;
					if (ReceiveDataCount>=15&&rxdata[1]==67)
					{
						for (int i = 0; i < 15; i++)
						{
							RecvData[i]=rxdata[i];
						}
						WORD RecvCRC=GetCheckCode(RecvData,13);
						if ((RecvCRC&0x00ff)==rxdata[14]&&((RecvCRC&0xff00)>>8)==rxdata[13])
						{
							//���¶����ݲ�ת��
							Temper_Data=0xffff&rxdata[6]+((0xffff&rxdata[5])<<8);
							//�չ������ݣ���ת��
							Power_Data=0xffff&rxdata[8]+((0xffff&rxdata[7])<<8);
							//��Ƶ�����ݣ���ת��
							Freq_Data=0xffffffff&rxdata[12]+((0xffffffff&rxdata[11])<<8)+((0xffffffff&rxdata[10])<<16)+((0xffffffff&rxdata[9])<<24);

							if(rxdata[2]==0x01)//����"
							{
								m_FreqData[rxdata[0]-1][rxdata[3]][rxdata[4]]=rxdata[2];
							}else if(rxdata[2]==0x02)//���ʵ�
							{
								m_FreqData[rxdata[0]-1][rxdata[3]][rxdata[4]]=rxdata[2];
							}else if(rxdata[2]==0x03)//�ź���
							{
								m_FreqData[rxdata[0]-1][rxdata[3]][rxdata[4]]=rxdata[2];
							}else
							{
								double GetTemp;
								if (Temper_Data&0x8000)
								{
									unsigned int temp1=(~Temper_Data+1)&0x0000ffff;
									int tempdata=temp1%16;
									GetTemp=(double)(temp1/16)+(double)tempdata/16;
									GetTemp=-GetTemp;
								} 
								else
								{
									unsigned int temp1=Temper_Data;
									int tempdata=temp1%16;
									GetTemp=(double)(temp1/16)+(double)tempdata/16;
								}
								m_TempData[rxdata[0]-1][rxdata[3]][rxdata[4]]=GetTemp;
								m_FreqData[rxdata[0]-1][rxdata[3]][rxdata[4]]=Freq_Data;
							}
							if ((rxdata[0]-1)==UserSelectReaderForCal)
							{
								switch (rxdata[3])
								{
								case 0x00:
									switch (rxdata[4])
									{
									case 0x00:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_1,IDC_STATIC_FREQ1_1);
										break;
									case 0x01:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_2,IDC_STATIC_FREQ1_2);
										break;
									case 0x02:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_3,IDC_STATIC_FREQ1_3);
										break;
									case 0x03:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_4,IDC_STATIC_FREQ1_4);
										break;
									case 0x04:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_5,IDC_STATIC_FREQ1_5);
										break;
									case 0x05:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_6,IDC_STATIC_FREQ1_6);
										break;
									case 0x06:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_7,IDC_STATIC_FREQ1_7);
										break;
									case 0x07:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_8,IDC_STATIC_FREQ1_8);
										break;
									case 0x08:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_9,IDC_STATIC_FREQ1_9);
										break;
									case 0x09:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_10,IDC_STATIC_FREQ1_10);
										break;
									case 0x0a:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_11,IDC_STATIC_FREQ1_11);
										break;
									case 0x0b:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP1_12,IDC_STATIC_FREQ1_12);
										break;
									default:
										break;
									}
									break;
								case 0x01:
									switch (rxdata[2])
									{
									case 0x00:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_1,IDC_STATIC_FREQ2_1);
										break;
									case 0x01:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_2,IDC_STATIC_FREQ2_2);
										break;
									case 0x02:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_3,IDC_STATIC_FREQ2_3);
										break;
									case 0x03:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_4,IDC_STATIC_FREQ2_4);
										break;
									case 0x04:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_5,IDC_STATIC_FREQ2_5);
										break;
									case 0x05:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_6,IDC_STATIC_FREQ2_6);
										break;
									case 0x06:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_7,IDC_STATIC_FREQ2_7);
										break;
									case 0x07:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_8,IDC_STATIC_FREQ2_8);
										break;
									case 0x08:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_9,IDC_STATIC_FREQ2_9);
										break;
									case 0x09:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_10,IDC_STATIC_FREQ2_10);
										break;
									case 0x0a:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_11,IDC_STATIC_FREQ2_11);
										break;
									case 0x0b:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP2_12,IDC_STATIC_FREQ2_12);
										break;
									default:
										break;
									}
									break;
								case 0x02:
									switch (rxdata[2])
									{
									case 0x00:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_1,IDC_STATIC_FREQ3_1);
										break;
									case 0x01:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_2,IDC_STATIC_FREQ3_2);
										break;
									case 0x02:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_3,IDC_STATIC_FREQ3_3);
										break;
									case 0x03:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_4,IDC_STATIC_FREQ3_4);
										break;
									case 0x04:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_5,IDC_STATIC_FREQ3_5);
										break;
									case 0x05:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_6,IDC_STATIC_FREQ3_6);
										break;
									case 0x06:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_7,IDC_STATIC_FREQ3_7);
										break;
									case 0x07:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_8,IDC_STATIC_FREQ3_8);
										break;
									case 0x08:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_9,IDC_STATIC_FREQ3_9);
										break;
									case 0x09:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_10,IDC_STATIC_FREQ3_10);
										break;
									case 0x0a:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_11,IDC_STATIC_FREQ3_11);
										break;
									case 0x0b:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP3_12,IDC_STATIC_FREQ3_12);
										break;
									default:
										break;
									}
									break;
								case 0x03:
									switch (rxdata[2])
									{
									case 0x00:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_1,IDC_STATIC_FREQ4_1);
										break;
									case 0x01:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_2,IDC_STATIC_FREQ4_2);
										break;
									case 0x02:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_3,IDC_STATIC_FREQ4_3);
										break;
									case 0x03:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_4,IDC_STATIC_FREQ4_4);
										break;
									case 0x04:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_5,IDC_STATIC_FREQ4_5);
										break;
									case 0x05:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_6,IDC_STATIC_FREQ4_6);
										break;
									case 0x06:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_7,IDC_STATIC_FREQ4_7);
										break;
									case 0x07:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_8,IDC_STATIC_FREQ4_8);
										break;
									case 0x08:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_9,IDC_STATIC_FREQ4_9);
										break;
									case 0x09:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_10,IDC_STATIC_FREQ4_10);
										break;
									case 0x0a:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_11,IDC_STATIC_FREQ4_11);
										break;
									case 0x0b:
										DataFix(pWndSensorCalibrate,rxdata[2],Temper_Data,Freq_Data,IDC_STATIC_TEMP4_12,IDC_STATIC_FREQ4_12);
										break;
									default:
										break;
									}
									break;
								default:
									break;
								}
							}
						}
						ReceiveDataCount=0;
						memset(rxdata,0,864); //ÿ�ν���ǰ��ջ�����
					}
				}
			}
		}
	}
}
void CMainFrame::OnCommunicate()
{
	// TODO: �ڴ���������������
	CString str;  
	str.Format(_T("%s, %s [L%d] "), __FILE__, __FUNCTION__, __LINE__);  
	str += "loging...";  
	OutputLog(SystemLogPath, str); 
	ActivePage();
	CTempDetectionView *pViewMainShow=(CTempDetectionView*)m_wndSplitter.GetPane(0,0);
	pViewMainShow->m_TreeCtl.EnableWindow(TRUE);
	CCommEdit m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUserSetPosition()
{
	// TODO: �ڴ���������������
	CString str;  
	str.Format(_T("%s, %s [L%d] "), __FILE__, __FUNCTION__, __LINE__);  
	str += "loging...";  
	OutputLog(SystemLogPath, str); 

	CDlgPosition m_dlg;
	m_dlg.DoModal();
}




void CMainFrame::OnCalibration()
{
	// TODO: �ڴ���������������
	CDlgCalibrate m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::CreateDataBase(void)
{
	//�����ݿ��ļ�
	CoInitialize(NULL);
	m_pConnection.CreateInstance(__uuidof(Connection));
	try
	{
		m_pConnection->Open("Driver=MySQL ODBC 5.1 Driver;Server=127.0.0.1;Database=sawdb","root","123456",adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}
void CMainFrame::InsertIntoData(CString RecordID,CString ReaderID,CString AntID, CString SensorID,CString Temperature,CString RFPower,CString Frequency,CString RecordTime,CString Notes)
{
	try
	{
		_bstr_t strCmd="INSERT INTO DB_Data (RecordID,ReaderID,AntID,SensorID,Temperature,RFPower,Frequency,RecordTime,Notes) VALUES('"+RecordID+"','"+ReaderID+"','"+AntID+"','"+SensorID+"','"+Temperature+"','"+RFPower+"','"+Frequency+"','"+RecordTime+"','"+Notes+"')";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}
void CMainFrame::InsertIntoTest(CString S_Time)
{
	try
	{
		_bstr_t strCmd="INSERT INTO DB_Record (StartTime) VALUES('"+S_Time+"')";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}

}
CString CMainFrame::GetRecordID()
{
	_bstr_t bSQL ="select RecordID from DB_Record order by RecordID desc limit 0,1";
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//ȡ�ñ��м�¼
	m_pRecordset->Open(bSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	return (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("RecordID");
}
void CMainFrame::UpdateTest(CString e_time)
{
	try
	{
		_bstr_t strCmd="UPDATE DB_Record SET EndTime='"+e_time+"' WHERE RecordID="+RecordID;
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}

BOOL CMainFrame::DBisOpen()
{
	if(m_pConnection )
		return m_pConnection->GetState() != adStateClosed;
	return FALSE;
}


void CMainFrame::OnExit()
{
	// TODO: �ڴ���������������
	if(MessageBox("ȷ���˳�","�˳�ϵͳ",MB_YESNO|MB_ICONQUESTION)==IDYES) 
	{
		this->SendMessage(WM_CLOSE);
	}	
}


void CMainFrame::OnUpdateExit(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_Exit); 
}


void CMainFrame::OnReaderConfig()
{
	// TODO: �ڴ���������������
	CDlgConfig m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateReaderConfig(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_ReaderConfig); 
}
unsigned int CMainFrame::ascii2hex(char *buf, int len)
{
	int i = 0, j = 0;  
	unsigned int ret = 0;  
	char p[2] = {0};  
	int tmp = 1;  
	for(i = 0; i<len; i++)
	{  
		memcpy(p,&buf[i],1);     
		switch (p[0])
		{  
		case 'A':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 10*tmp;  
			break;  
		case 'B':             
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 11*tmp;  
			break;  
		case 'C':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 12*tmp;  
			break;  
		case 'D':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 13*tmp;  
			break;  
		case 'E':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 14*tmp;  
			break;  
		case 'F':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 15*tmp;  
			break;  
		case 'a':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 10*tmp;  
			break;  
		case 'b':             
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 11*tmp;  
			break;  
		case 'c':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 12*tmp;  
			break;  
		case 'd':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 13*tmp;  
			break;  
		case 'e':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 14*tmp;  
			break;  
		case 'f':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 15*tmp;  
			break;  
		default:  
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += atoi(p)*tmp;  
			break;  
		}  
	}  
	return ret;  
}
void CMainFrame::DataOperate(CString Reader,char Ant,char Sensor,unsigned int Power,unsigned int Frequence, int Temp)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	switch (Ant)//�ڶ����⣺����ID
	{
	case 0x00://����0						
		switch (Sensor)//�������⣺��ǩID//
		{
		case 0x00:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������1",0,Power,Frequence, Temp);
			break;
		case 0x01:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������2",1,Power,Frequence, Temp);
			break;
		case 0x02:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������3",2,Power,Frequence, Temp);
			break;
		case 0x03:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������4",3,Power,Frequence, Temp);
			break;
		case 0x04:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������5",4,Power,Frequence, Temp);
			break;
		case 0x05:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������6",5,Power,Frequence, Temp);
			break;
		case 0x06:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������7",6,Power,Frequence, Temp);
			break;
		case 0x07:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������8",7,Power,Frequence, Temp);
			break;
		case 0x08:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������9",8,Power,Frequence, Temp);
			break;
		case 0x09:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������10",9,Power,Frequence, Temp);
			break;
		case 0x0a:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������11",10,Power,Frequence, Temp);
			break;
		case 0x0b:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt1,Reader,"����1","������12",11,Power,Frequence, Temp);
			break;
		default:
			break;
		}//switch (rxdata[k+2])//�������⣺��ǩID
		break;
	case 0x01://�ڶ����⣺����1
		switch (Sensor)//�������⣺��ǩID
		{
		case 0x00:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������1",0,Power,Frequence, Temp);
			break;
		case 0x01:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������2",1,Power,Frequence, Temp);
			break;
		case 0x02:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������3",2,Power,Frequence, Temp);
			break;
		case 0x03:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������4",3,Power,Frequence, Temp);
			break;
		case 0x04:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������5",4,Power,Frequence, Temp);
			break;
		case 0x05:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������6",5,Power,Frequence, Temp);
			break;
		case 0x06:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������7",6,Power,Frequence, Temp);
			break;
		case 0x07:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������8",7,Power,Frequence, Temp);
			break;
		case 0x08:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������9",8,Power,Frequence, Temp);
			break;
		case 0x09:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������10",9,Power,Frequence, Temp);
			break;
		case 0x0a:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������11",10,Power,Frequence, Temp);
			break;
		case 0x0b:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt2,Reader,"����2","������12",11,Power,Frequence, Temp);
			break;
		default:
			break;
		}//switch (rxdata[k+2])//�������⣺��ǩID
		break;
	case 0x02://�ڶ����⣺����1
		switch (Sensor)//�������⣺��ǩID
		{
		case 0x00:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������1",0,Power,Frequence, Temp);
			break;
		case 0x01:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������2",1,Power,Frequence, Temp);
			break;
		case 0x02:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������3",2,Power,Frequence, Temp);
			break;
		case 0x03:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������4",3,Power,Frequence, Temp);
			break;
		case 0x04:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������5",4,Power,Frequence, Temp);
			break;
		case 0x05:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������6",5,Power,Frequence, Temp);
			break;
		case 0x06:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������7",6,Power,Frequence, Temp);
			break;
		case 0x07:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������8",7,Power,Frequence, Temp);
			break;
		case 0x08:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������9",8,Power,Frequence, Temp);
			break;
		case 0x09:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������10",9,Power,Frequence, Temp);
			break;
		case 0x0a:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������11",10,Power,Frequence, Temp);
			break;
		case 0x0b:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt3,Reader,"����3","������12",11,Power,Frequence, Temp);
			break;
		default:
			break;
		}//switch (rxdata[k+2])//�������⣺��ǩID
		break;
	case 0x03://�ڶ����⣺����1
		switch (Sensor)//�������⣺��ǩID
		{
		case 0x00:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������1",0,Power,Frequence, Temp);
			break;
		case 0x01:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������2",1,Power,Frequence, Temp);
			break;
		case 0x02:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������3",2,Power,Frequence, Temp);
			break;
		case 0x03:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������4",3,Power,Frequence, Temp);
			break;
		case 0x04:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������5",4,Power,Frequence, Temp);
			break;
		case 0x05:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������6",5,Power,Frequence, Temp);
			break;
		case 0x06:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������7",6,Power,Frequence, Temp);
			break;
		case 0x07:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������8",7,Power,Frequence, Temp);
			break;
		case 0x08:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������9",8,Power,Frequence, Temp);
			break;
		case 0x09:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������10",9,Power,Frequence, Temp);
			break;
		case 0x0a:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������11",10,Power,Frequence, Temp);
			break;
		case 0x0b:
			MainTemperShow((CDlgShowAnt1*)pViewMainShow->pSheet->pDlgShowAnt4,Reader,"����4","������12",11,Power,Frequence, Temp);
			break;
		default:
			break;
		}//switch (rxdata[k+2])//�������⣺��ǩID
		break;
	default:
		break;
	}//switch (rxdata[k+3])//�ڶ����⣺����ID
}
void CMainFrame::MainTemperShow(CDlgShowAnt1* pMainShow,CString Reader,CString Ant,CString Sensor,int SensorID,unsigned int Power,unsigned int Frequence, int Temp)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	CString strTemp,strFreq,strPower,strTime;
	CString StrTemperRase,StrSensorNO,strShowTime;
	double GetTemp;

	double TimeNow=COleDateTime::GetCurrentTime();//��������
	COleDateTime t=COleDateTime::GetCurrentTime();
	strShowTime=t.Format("%Y-%m-%d %H-%M-%S");
	if (Temp&0x8000)
	{
		unsigned int temp1=(~Temp+1)&0x0000ffff;
		int tempdata=temp1%16;
		GetTemp=(double)(temp1/16)+(double)tempdata/16;
		GetTemp=-GetTemp;
	} 
	else
	{
		unsigned int temp1=Temp;
		int tempdata=temp1%16;
		GetTemp=(double)(temp1/16)+(double)tempdata/16;
	}
	strTemp.Format("%.1f",GetTemp);//�޸Ĵ洢txt�����ݸ�ʽ
	strPower.Format("%d",Power);//�޸Ĵ洢txt�����ݸ�ʽ
	strFreq.Format("%d",Frequence);//�޸Ĵ洢txt�����ݸ�ʽ
	strTime.Format("%f",TimeNow);//�޸Ĵ洢txt�����ݸ�ʽdate
	int Power2Signal=(Power-2000)/80;//power��2000-10000

	int RecvReader;
	int len=Reader.GetLength();
	if (len==7)
	{
		RecvReader=atoi(Reader.Right(1));
	} 
	else if(len==8)
	{
		RecvReader=atoi(Reader.Right(2));
	}
	LastRecvTemp[RecvReader-1][atoi(Ant.Right(1))-1][SensorID]=atof(strTemp);
	LastRecvPower[RecvReader-1][atoi(Ant.Right(1))-1][SensorID]=Power2Signal;
	//�¶ȳ��޾���
	if (GetTemp>AlarmTempSave[0][RecvReader-1]||GetTemp<AlarmTempSave[1][RecvReader-1])
	{
		LastAlarmStatus[RecvReader-1][atoi(Ant.Right(1))-1][SensorID]=1;
		Menu_SetSilent=TRUE;
		InsertIntoData(RecordID,Reader,Ant,Sensor,strTemp,strPower,strFreq,strTime,"���޾���");
		//�¶ȳ��޾���
		pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.InsertItem(AlarmCount,"");
		StrSensorNO.Format("%d",SensorID+1);
		pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.SetItemText(AlarmCount,0,Reader);
		pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.SetItemText(AlarmCount,1,Ant);
		pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.SetItemText(AlarmCount,2,"������"+StrSensorNO);
		pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.SetItemText(AlarmCount,3,strShowTime);
		pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.SetItemText(AlarmCount,4,strTemp);
		pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.SetItemText(AlarmCount,5,"�¶ȳ�����ֵ");
		AlarmCount++;
		if (AlarmSound==0)
		{
			//����call2.wav					
			AlarmSound=PlaySound("Alarm.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		if (RecvReader==UserSelectReader)
		{
			WrongFlagCount[atoi(Ant.Right(1))-1][SensorID]=0;
			MainTempShow(strTemp,1,Ant,SensorID);
			switch (SensorID)
			{
			case 0:
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 1:
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 2:
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 3:
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 4:
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 5:
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 6:
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 7:
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 8:
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 9:
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 10:
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 11:
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			default:
				break;
			}
		}
	}else
	{
		LastAlarmStatus[RecvReader-1][atoi(Ant.Right(1))-1][SensorID]=0;
		InsertIntoData(RecordID,Reader,Ant,Sensor,strTemp,strPower,strFreq,strTime,"����");
		if (RecvReader==UserSelectReader)
		{
			WrongFlagCount[atoi(Ant.Right(1))-1][SensorID]=0;
			MainTempShow(strTemp,0,Ant,SensorID);
			switch (SensorID)
			{
			case 0:
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 1:
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 2:
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 3:
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 4:
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 5:
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 6:
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 7:
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 8:
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 9:
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 10:
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			case 11:
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(atof(strTemp));//�趨�¶�ֵ
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(Power2Signal);
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
				break;
			default:
				break;
			}
		}
	}
}
void CMainFrame::MainStatusShow(CDlgShowAnt1* pMainShow,char Reader,char Sensor, int Status,int AntID)
{
	LastAlarmStatus[Reader-1][AntID][Sensor]=Status+2;
	int SensorID;
	switch (Sensor)
	{
	case 0x00:			
		SensorID=0;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x01:
		SensorID=1;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x02:
		SensorID=2;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x03:
		SensorID=3;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x04:
		SensorID=4;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x05:
		SensorID=5;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x06:
		SensorID=6;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x07:
		SensorID=7;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x08:
		SensorID=8;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x09:
		SensorID=9;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x0a:
		SensorID=10;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	case 0x0b:
		SensorID=11;
		WrongFlagCount[AntID][SensorID]++;
		if (WrongFlagCount[AntID][SensorID]>3)
		{
			if (Status==0)
			{
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==1)
			{
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==2)
			{
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
				pMainShow->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
				pMainShow->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
			}else if (Status==3)
			{
			}
		}
		break;
	default:
		break;
	}
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = 100 ; 
	lpMMI->ptMinTrackSize.y = 100 ; 
	lpMMI->ptMaxTrackSize.x = 1024 ; 
	lpMMI->ptMaxTrackSize.y = 750; 
	CFrameWndEx::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::ActivePage(void)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	//CSplitterWnd* m_wndSplitter=(CSplitterWnd*)GetParent(); 
	//CIPServerView* m_pane2View=(CIPServerView*)m_wndSplitter->GetPane(0,1); 
	//pViewMainShow->m_sheet.SetActivePage(29); 
	pViewMainShow->m_sheet.SetActivePage(6); 
	pViewMainShow->m_sheet.SetActivePage(5); 
	pViewMainShow->m_sheet.SetActivePage(4); 
	pViewMainShow->m_sheet.SetActivePage(3); 
	pViewMainShow->m_sheet.SetActivePage(2); 
	pViewMainShow->m_sheet.SetActivePage(1); 
	pViewMainShow->m_sheet.SetActivePage(0); 
}


void CMainFrame::ClearShowMessage(void)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.DeleteAllItems();
	AlarmCount=0;
}


void CMainFrame::OnUserSet()
{
	// TODO: �ڴ���������������
	CDlgUserSet m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnFactorySet()
{
	// TODO: �ڴ���������������
	CDlgFactorySet m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OutputLog(LPCTSTR logName, CString msg)
{
	try
	{
		//�����ļ��Ĵ򿪲���
		CStdioFile outFile(logName, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		CString msLine;
		CTime tt = CTime::GetCurrentTime();

		//��ΪLog�ļ�������Ҫ��ÿ��Log��ʱ�����ʱ���ʽ�����ɶ��壬
		//����ĸ�ʽ�磺2010-June-10 Thursday, 15:58:12
		msLine = tt.Format("[%Y-%B-%d %A, %H:%M:%S] ") + msg;
		msLine += "\n\r";

		//���ļ�ĩβ�����¼�¼
		outFile.SeekToEnd();
		outFile.WriteString( msLine );
		outFile.Close();
	}
	catch(CFileException *fx)
	{
		fx->Delete();
	}
}


void CMainFrame::OnStartMem()
{
	// TODO: �ڴ���������������

	ActivePage();
	ClearShowMessage();
	if (PortOpenFlag)
	{
		CTempDetectionView *pViewMainShow=(CTempDetectionView*)m_wndSplitter.GetPane(0,0);
		pViewMainShow->SetButtonStatus(TRUE);
		pViewMainShow->StartMem();
		///////�����ݿ��в���ʵ���¼///////////////////////////
		CTime currenttime=CTime::GetCurrentTime();   
		CString s_time=currenttime.Format("%Y-%m-%d %H:%M:%S"); 
		InsertIntoTest(s_time);	
		RecordID=GetRecordID();
		ReceiveDataCount=0;
		//���Ϳ�ʼ����ָ��
		SendCMD(StartCMD);
		Sleep(50);
		m_MSComm.SetInBufferCount(0);

		SetTimer(ID_TIMER_WAIT,2000,NULL);//��������ʱ��

		StartFlag=1;

		for (int k = 0; k < 30; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					m_FreqData[k][i][j]=0;
					m_TempData[k][i][j]=0;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				WrongFlagCount[i][j]=0;
			}
		}
		//����״̬����ʾʵ�����
		SetStatusBar(1,"��ʼ����");

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 12; k++)
				{
					LastRecvTemp[i][j][k]=0;
					LastRecvPower[i][j][k]=0;
					LastAlarmStatus[i][j][k]=0;
				}
			}
		}
		Menu_Exit=FALSE;
		Menu_StartMem=FALSE;
		Menu_StopMem=TRUE;
		Menu_Refresh=TRUE;
		Menu_Calibration=FALSE;
		Menu_UserSetPosition=FALSE;
		Menu_ReaderConfig=FALSE;
		Menu_PowerControl=FALSE;
		Menu_UpdateFirmware=FALSE;
		Menu_FactorySet=FALSE;
		Menu_UserSet=FALSE;
		Menu_ChangeUser=FALSE;
		Menu_ScanReader=FALSE;
		Menu_CtlSingleReader=TRUE;
		Menu_ShowAlarmHistory=FALSE;
		Menu_SetAlarmTemp=TRUE;
		Menu_ModifyReaderID=FALSE;
	}else
	{
		AfxMessageBox("���ȴ򿪶˿ڣ��ٽ��п��Ʋ�����");
	}
}


void CMainFrame::OnUpdateStartMem(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_StartMem); 
}


void CMainFrame::OnStopMem()
{
	// TODO: �ڴ���������������
	if (PortOpenFlag)
	{
		if(MessageBox("ȷ��ֹͣ�¶ȼ��","ֹͣ���",MB_YESNO|MB_ICONQUESTION)==IDYES) 
		{
			while (1)
			{
				if (m_MSComm.GetInBufferCount()==0)
				{
					//KillTimer(ID_TIMER_LOOP);
					StopTimer();
					Sleep(400);
					SendCMD(StopCMD);
					Sleep(50);
					m_MSComm.SetInBufferCount(0);

					StartFlag=0;
					break;
				}
			}
			CTempDetectionView *pViewMainShow=(CTempDetectionView*)m_wndSplitter.GetPane(0,0);
			pViewMainShow->SetButtonStatus(FALSE);
			pViewMainShow->StopMem();
			///////��ȡֹͣʵ��ʱ�䣬���������ݿ�///////////////////////////////////////////
			CTime currenttime=CTime::GetCurrentTime();   
			CString e_time=currenttime.Format("%Y-%m-%d %H:%M:%S"); 
			UpdateTest(e_time);

			//�رձ�����
			PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
			//Alarm=FALSE;
			//����״̬����ʾʵ�����
			SetStatusBar(1,"ֹͣ����");
			Menu_Exit=TRUE;
			Menu_StartMem=TRUE;
			Menu_StopMem=FALSE;
			Menu_Refresh=FALSE;
			Menu_ChangeUser=TRUE;
			Menu_ScanReader=TRUE;
			Menu_CtlSingleReader=TRUE;
			Menu_ShowAlarmHistory=TRUE;
			Menu_SetAlarmTemp=TRUE;
			if (LoginDomainSet==0)
			{
				Menu_Calibration=TRUE;
				Menu_UserSetPosition=TRUE;
				Menu_ReaderConfig=TRUE;
				Menu_PowerControl=TRUE;
				Menu_UpdateFirmware=TRUE;
				Menu_FactorySet=TRUE;
				Menu_UserSet=TRUE;
				Menu_ModifyReaderID=TRUE;
			} 
			else
			{
				Menu_Calibration=FALSE;
				Menu_UserSetPosition=FALSE;
				Menu_ReaderConfig=FALSE;
				Menu_PowerControl=FALSE;
				Menu_UpdateFirmware=FALSE;
				Menu_FactorySet=FALSE;
				Menu_UserSet=FALSE;
				Menu_ModifyReaderID=FALSE;
			}
		}	
	}else
	{
		AfxMessageBox("���ȴ򿪶˿ڣ��ٽ��п��Ʋ�����");
	}
}


void CMainFrame::OnUpdateStopMem(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_StopMem); 
}


void CMainFrame::OnChangeUser()
{
	// TODO: �ڴ���������������
	ActivePage();
	CTempDetectionView *pViewMainShow=(CTempDetectionView*)m_wndSplitter.GetPane(0,0);
	pViewMainShow->m_TreeCtl.EnableWindow(TRUE);

	CDlgChangeUser m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnPowerControl()
{
	// TODO: �ڴ���������������
	CDlgPowerControl m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnRefresh()
{
	// TODO: �ڴ���������������
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart01.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart02.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart03.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart04.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart05.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart06.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart07.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart08.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart09.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart10.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart11.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart12.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt1->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart01.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart02.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart03.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart04.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart05.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart06.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart07.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart08.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart09.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart10.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart11.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart12.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt2->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart01.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart02.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart03.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart04.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart05.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart06.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart07.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart08.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart09.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart10.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart11.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart12.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt3->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart01.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart02.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart03.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart04.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart05.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart06.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart07.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart08.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart09.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart10.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart11.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart12.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));//�趨��λ������ɫ
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	pViewMainShow->pSheet->pDlgShowAnt4->m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
	pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ

}


void CMainFrame::OnUpdateRefresh(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_Refresh); 
}

void CMainFrame::MainStatusShowAnt1(char Sensor)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	switch (Sensor)
	{
	case 0x00:
		if (WrongFlagCount[0][0]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x01:
		if (WrongFlagCount[0][1]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x02:
		if (WrongFlagCount[0][2]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x03:
		if (WrongFlagCount[0][3]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x04:
		if (WrongFlagCount[0][4]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x05:
		if (WrongFlagCount[0][5]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x06:
		if (WrongFlagCount[0][6]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x07:
		if (WrongFlagCount[0][7]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x08:
		if (WrongFlagCount[0][8]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x09:
		if (WrongFlagCount[0][9]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x0a:
		if (WrongFlagCount[0][10]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x0b:
		if (WrongFlagCount[0][11]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	default:
		break;
	}
}
void CMainFrame::MainStatusShowAnt2(char Sensor)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	switch (Sensor)
	{
	case 0x00:
		if (WrongFlagCount[1][0]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x01:
		if (WrongFlagCount[1][1]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x02:
		if (WrongFlagCount[1][2]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x03:
		if (WrongFlagCount[1][3]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x04:
		if (WrongFlagCount[1][4]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x05:
		if (WrongFlagCount[1][5]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x06:
		if (WrongFlagCount[1][6]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x07:
		if (WrongFlagCount[1][7]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x08:
		if (WrongFlagCount[1][8]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x09:
		if (WrongFlagCount[1][9]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x0a:
		if (WrongFlagCount[1][10]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x0b:
		if (WrongFlagCount[1][11]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	default:
		break;
	}

}
void CMainFrame::MainStatusShowAnt3(char Sensor)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	switch (Sensor)
	{
	case 0x00:
		if (WrongFlagCount[2][0]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x01:
		if (WrongFlagCount[2][1]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x02:
		if (WrongFlagCount[2][2]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x03:
		if (WrongFlagCount[2][3]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x04:
		if (WrongFlagCount[2][4]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x05:
		if (WrongFlagCount[2][5]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x06:
		if (WrongFlagCount[2][6]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x07:
		if (WrongFlagCount[2][7]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x08:
		if (WrongFlagCount[2][8]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x09:
		if (WrongFlagCount[2][9]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x0a:
		if (WrongFlagCount[2][10]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x0b:
		if (WrongFlagCount[2][11]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	default:
		break;
	}

}
void CMainFrame::MainStatusShowAnt4(char Sensor)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	switch (Sensor)
	{
	case 0x00:
		if (WrongFlagCount[3][0]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_01.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x01:
		if (WrongFlagCount[3][1]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_02.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x02:
		if (WrongFlagCount[3][2]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_03.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x03:
		if (WrongFlagCount[3][3]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_04.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x04:
		if (WrongFlagCount[3][4]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_05.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x05:
		if (WrongFlagCount[3][5]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_06.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x06:
		if (WrongFlagCount[3][6]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_07.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x07:
		if (WrongFlagCount[3][7]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_08.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x08:
		if (WrongFlagCount[3][8]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_09.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x09:
		if (WrongFlagCount[3][9]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_10.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x0a:
		if (WrongFlagCount[3][10]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_11.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	case 0x0b:
		if (WrongFlagCount[3][11]>3)
		{
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_12.Series(0).GetAsNumericGauge().SetValue(0);//�趨�¶�ֵ
			pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));//�趨�¶�������ɫ
		}
		break;
	default:
		break;
	}
}

int CMainFrame::DataFix(CDlgCalibrate* pWndSensorFix,char status,int GetTemperData,int GetFreqData,int StaticTemper,int StaticFreq)
{
	CString TemperTxt,FreqTxt,PowerTxt;//���ڱ���txt�ı�������
	CString TemperText,FreqText,PowerText;
	if(status==0x01)
	{
		pWndSensorFix->GetDlgItem(StaticTemper)->SetWindowText("");
		pWndSensorFix->GetDlgItem(StaticFreq)->SetWindowText("����");
		return 0;
	}else if(status==0x02)
	{
		pWndSensorFix->GetDlgItem(StaticTemper)->SetWindowText("");
		pWndSensorFix->GetDlgItem(StaticFreq)->SetWindowText("���ʵ�");
		return 0;
	}else if(status==0x03)
	{
		pWndSensorFix->GetDlgItem(StaticTemper)->SetWindowText("");
		pWndSensorFix->GetDlgItem(StaticFreq)->SetWindowText("�ź���");
		return 0;
	}else
	{
		double GetTemp;
		if (GetTemperData&0x8000)
		{
			unsigned int temp1=(~GetTemperData+1)&0x0000ffff;
			int tempdata=temp1%16;
			GetTemp=(double)(temp1/16)+(double)tempdata/16;
			GetTemp=-GetTemp;
		} 
		else
		{
			unsigned int temp1=GetTemperData;
			int tempdata=temp1%16;
			GetTemp=(double)(temp1/16)+(double)tempdata/16;
		}
		TemperTxt.Format("%.1f",GetTemp);//�޸Ĵ洢txt�����ݸ�ʽtemper
		FreqTxt.Format("%d",GetFreqData);//�޸Ĵ洢txt�����ݸ�ʽfreq
		TemperText="T:"+TemperTxt+"��";
		FreqText="F:"+FreqTxt;
		pWndSensorFix->GetDlgItem(StaticTemper)->SetWindowText(TemperText);
		pWndSensorFix->GetDlgItem(StaticFreq)->SetWindowText(FreqText);
		return GetFreqData;
	}
}


void CMainFrame::ShowPosition(int ReaderID,bool status)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	if (!status)
	{
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ

		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ

		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ

		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText("");//�趨��ע��Ϣ
	} 
	else
	{
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+0));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+1));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+2));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+3));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+4));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+5));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+6));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+7));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+8));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+9));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+10));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt1->m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+11));//�趨��ע��Ϣ

		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+0));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+1));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+2));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+3));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+4));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+5));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+6));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+7));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+8));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+9));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+10));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt2->m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12+11));//�趨��ע��Ϣ

		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+0));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+1));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+2));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+3));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+4));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+5));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+6));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+7));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+8));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+9));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+10));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt3->m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*2+11));//�趨��ע��Ϣ

		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+0));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+1));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+2));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+3));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+4));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+5));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+6));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+7));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+8));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+9));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+10));//�趨��ע��Ϣ
		pViewMainShow->pSheet->pDlgShowAnt4->m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText(strSensorPositionArray.GetAt(ReaderID*4*12+12*3+11));//�趨��ע��Ϣ
	}
}


void CMainFrame::MainTempShow(CString Temp, int Status, CString Ant,int SensorID)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	switch (atoi(Ant.Right(1)))
	{
	case 1:
		switch (SensorID)
		{
		case 0:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_01.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_01.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 1:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_02.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_02.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_03.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_03.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_04.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_04.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 4:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_05.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_05.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 5:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_06.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_06.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 6:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_07.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_07.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 7:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_08.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_08.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_09.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_09.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 9:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_10.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_10.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 10:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_11.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_11.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 11:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_12.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_12.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart1_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	break;
	case 2:
		switch (SensorID)
		{
		case 0:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_01.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_01.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 1:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_02.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_02.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_03.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_03.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_04.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_04.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 4:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_05.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_05.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 5:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_06.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_06.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 6:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_07.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_07.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 7:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_08.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_08.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_09.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_09.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 9:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_10.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_10.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 10:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_11.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_11.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 11:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_12.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_12.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart2_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (SensorID)
		{
		case 0:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_01.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_01.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 1:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_02.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_02.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_03.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_03.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_04.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_04.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 4:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_05.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_05.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 5:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_06.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_06.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 6:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_07.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_07.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 7:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_08.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_08.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_09.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_09.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 9:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_10.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_10.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 10:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_11.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_11.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 11:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_12.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_12.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart3_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (SensorID)
		{
		case 0:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_01.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_01.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 1:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_02.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_02.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_03.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_03.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_04.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_04.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 4:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_05.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_05.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 5:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_06.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_06.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 6:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_07.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_07.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 7:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_08.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_08.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_09.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_09.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 9:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_10.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_10.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 10:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_11.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_11.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		case 11:
			switch (Status)
			{
			case 0:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_12.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));//�趨�¶�������ɫ
				break;
			case 1:
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_12.Series(0).GetAsNumericGauge().SetValue(atof(Temp));//�趨�¶�ֵ
				pViewMainShow->pSheet->pDlgMainShow->m_CtlTChart4_12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));//�趨�¶�������ɫ
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}


void CMainFrame::OnUpdateFirmware()
{
	// TODO: �ڴ���������������
	CDlgUpdateFirmware m_dlg;
	m_dlg.DoModal();
}




void CMainFrame::SetStatusBar(int index, CString Str)
{
	m_wndStatusBar.SetPaneText(index,Str); 
}


void CMainFrame::OnSetAlarmTemp()
{
	// TODO: �ڴ���������������
	CDlgSetAlarm m_dlg;
	m_dlg.DoModal();
}






WORD CMainFrame::GetCheckCode(const char * pSendBuf, int nEnd)
{
	WORD wCrc = WORD(0xFFFF);
	for(int i=0; i<nEnd; i++)
	{
		wCrc ^= WORD(BYTE(pSendBuf[i]));
		for(int j=0; j<8; j++)
		{
			if(wCrc & 1)
			{
				wCrc >>= 1; 
				wCrc ^= 0xA001; 
			}
			else
			{
				wCrc >>= 1; 
			}
		}
	}
	return wCrc;
}

void CMainFrame::SendCMD(char* pSendBuf)
{
	WORD GetCRC=GetCheckCode(pSendBuf,13);
	pSendBuf[14]=GetCRC&0x00ff;
	pSendBuf[13]=(GetCRC&0xff00)>>8;
	CByteArray arraySend;
	arraySend.RemoveAll();
	arraySend.SetSize(15);
	for(int i=0;i<15;i++)
	{
		arraySend.SetAt(i,pSendBuf[i]);
	}
	m_MSComm.SetOutput(COleVariant(arraySend));
}

void CMainFrame::OnUpdateSetAlarmTemp(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_SetAlarmTemp); 
}


void CMainFrame::OnSetSilent()
{
	// TODO: �ڴ���������������
	Menu_SetSilent=FALSE;
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void CMainFrame::OnUpdateSetSilent(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_SetSilent); 
}


void CMainFrame::OnShowAlarmHistory()
{
	// TODO: �ڴ���������������
	CDlgAlarmHistory m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateShowAlarmHistory(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_ShowAlarmHistory); 
}

void CMainFrame::OnScanReader()
{
	// TODO: �ڴ���������������
}


void CMainFrame::OnUpdateScanReader(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_ScanReader); 
}


void CMainFrame::OnCtlSingleReader()
{
	// TODO: �ڴ���������������
	CDlgCtlSingleReader m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateCtlSingleReader(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_CtlSingleReader); 
}


void CMainFrame::OnModifyReadrId()
{
	// TODO: �ڴ���������������
	CDlgModifyReaderID m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateModifyReadrId(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(Menu_ModifyReaderID); 
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case ID_TIMER_WAIT:
		KillTimer(ID_TIMER_WAIT);
		//SetTimer(ID_TIMER_LOOP,UserSetLoopTime,NULL);//��������ʱ��
		StartTimer(m_hWnd,UserSetLoopTime);
		CountLoop=1;
		SynchronousCount=0;
		SendCMDStatus=TRUE;
		break;
	case ID_TIMER_LOOP:
		CallReaderCMD[0]=CountLoop;
		CountLoop++;
		if (CountLoop==31)
		{
			CountLoop=1;
		}
		SendCMD(CallReaderCMD);
		break;
	default:
		break;
	}
	CFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::ReadPositionFromDB(void)
{
	CString strPositon,strID,strHigh,strlow;
	strReaderPositionArray.RemoveAll();
	strReaderPositionArray.SetSize(30);

	_bstr_t bstrSQLReader ="SELECT ID,Position,HighTemp,LowTemp FROM db_reader_position order by ID;";
	_RecordsetPtr m_pRecordReader;
	m_pRecordReader.CreateInstance(__uuidof(Recordset));
	//ȡ�ñ��м�¼
	m_pRecordReader->Open(bstrSQLReader,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	while(!m_pRecordReader->adoEOF)
	{
		strID=(LPCSTR)(_bstr_t)m_pRecordReader->GetCollect("ID");
		strID.ReleaseBuffer();
		strReaderPositionArray.SetAt(atoi(strID)-1,(LPCSTR)(_bstr_t)m_pRecordReader->GetCollect("Position"));
		AlarmTempSave[0][atoi(strID)-1]=atoi((LPCSTR)(_bstr_t)m_pRecordReader->GetCollect("HighTemp"));
		AlarmTempSave[1][atoi(strID)-1]=atoi((LPCSTR)(_bstr_t)m_pRecordReader->GetCollect("LowTemp"));
		strID.FreeExtra();
		strID.Empty();
		m_pRecordReader->MoveNext();
	}
	m_pRecordReader->Close();

	int i,j,k;
	i=0;
	j=0;
	k=0;
	strSensorPositionArray.RemoveAll();
	strSensorPositionArray.SetSize(1440);
	_bstr_t bstrSQLSensor ="SELECT ID,Position,Power FROM db_sensor_position order by ID;";
	_RecordsetPtr m_pRecordSensor;
	m_pRecordSensor.CreateInstance(__uuidof(Recordset));
	//ȡ�ñ��м�¼
	m_pRecordSensor->Open(bstrSQLSensor,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	while(!m_pRecordSensor->adoEOF)
	{
		CString strPositon=(LPCSTR)(_bstr_t)m_pRecordSensor->GetCollect("Position");
		CString strID=(LPCSTR)(_bstr_t)m_pRecordSensor->GetCollect("ID");
		CString strPower=(LPCSTR)(_bstr_t)m_pRecordSensor->GetCollect("Power");
		strPositon.ReleaseBuffer();
		strID.ReleaseBuffer();
		strPower.ReleaseBuffer();
		strSensorPositionArray.SetAt(atoi(strID)-25,strPositon);
		SensorPowerSet[i][j][k]=atoi(strPower);
		k++;
		if (k==12)
		{
			k=0;
			j++;
			if (j==4)
			{
				j=0;
				i++;
				if (i==30)
				{
					i=0;
				}
			}
		}
		m_pRecordSensor->MoveNext();
	}
	m_pRecordSensor->Close();
}


void CMainFrame::UpdateReaderPosition(CString ReaderID, CString Positon)
{
	try
	{
		_bstr_t strCmd="UPDATE db_reader_position SET Position='"+Positon+"' WHERE ReaderID="+ReaderID;
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CMainFrame::UpdateAlarmTemp(CString ReaderID, CString HighTemp, CString LowTemp)
{
	try
	{
		_bstr_t strCmd="UPDATE db_reader_position SET HighTemp='"+HighTemp+"',LowTemp='"+LowTemp+"' WHERE ReaderID="+ReaderID;
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CMainFrame::UpdateSensorPositon(CString ReaderID, CString AntID, CString SensorID, CString Positon)
{
	try
	{
		_bstr_t strCmd="UPDATE db_sensor_position SET Position='"+Positon+"' WHERE ReaderID='"+ReaderID+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"'";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CMainFrame::UpdateSensorPower(CString ReaderID, CString AntID, CString SensorID, CString Power)
{
	try
	{
		_bstr_t strCmd="UPDATE db_sensor_position SET Position='"+Power+"' WHERE ReaderID='"+ReaderID+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"'";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CMainFrame::ReadINIFile(CString FileName)
{
	for (int i = 0; i < 30; i++)
	{
		CString nindex,temp;
		nindex.Format("%d",i+1);
		GetPrivateProfileString("READER",nindex,"default",temp.GetBuffer(MAX_PATH),MAX_PATH,FileName); 
		temp.ReleaseBuffer();
		UserDefineReader[i]=atoi(temp);
	}
	CString temp;
	GetPrivateProfileString("LOOPTIME","Time","default",temp.GetBuffer(MAX_PATH),MAX_PATH,FileName); 
	temp.ReleaseBuffer();
	UserSetLoopTime=atoi(temp);
	CString temp2;
	GetPrivateProfileString("SYNCHRONOUS","Set","default",temp2.GetBuffer(MAX_PATH),MAX_PATH,FileName); 
	temp2.ReleaseBuffer();
	UserSetSynchronous=atoi(temp2);
}


void CMainFrame::ShowAllLastData(void)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	pViewMainShow->pSheet->pDlgShowAnt1->ShowData();
	pViewMainShow->pSheet->pDlgShowAnt2->ShowData();
	pViewMainShow->pSheet->pDlgShowAnt3->ShowData();
	pViewMainShow->pSheet->pDlgShowAnt4->ShowData();
	pViewMainShow->pSheet->pDlgMainShow->ShowData();
}


void CMainFrame::StartTimer(HWND hd,long time)
{
	SetTime=time;
	EnableTimer=TRUE;
	AfxBeginThread(OneMilliSecondProc,this);//������ʱ��
}
void CMainFrame::StopTimer()
{
	EnableTimer=FALSE;
}

LRESULT CMainFrame::OnUpdateTime(WPARAM wParam,LPARAM lParam)
{

	QueryPerformanceCounter(&litmp);
	llQPartNew=litmp.QuadPart;
	double x=((double)(llQPartNew-llQPartOld))/fFreq;

	if (EnableTimer)
	{
		switch (SendCMDStatus)
		{
		case true:
			CallReaderCMD[0]=CountLoop;
			CountLoop++;
			if (CountLoop==31)
			{
				CountLoop=1;
			}
			if(x>(UserSetLoopTime-5)*0.001)
			{
				llQPartOld=llQPartNew;
				SendCMD(CallReaderCMD);
				if (UserSetSynchronous!=0)
				{
					SynchronousCount++;
					if (SynchronousCount==UserSetSynchronous)
					{
						SendCMDStatus=FALSE;
					}
				} 
			}else
			{
				CountLoop--;
			}
			break;
		case false:
			if(x>(UserSetLoopTime-5)*0.001)
			{
				SynchronousCount=0;
				SendCMDStatus=TRUE;
				llQPartOld=llQPartNew;
				SendCMD(SynchronousCMD);
			}
			break;
		}
	}

	return 0;
}


void CMainFrame::StartMem(void)
{
	if (PortOpenFlag)
	{
		ReceiveDataCount=0;
		//���Ϳ�ʼ����ָ��
		SendCMD(StartCMD);
		Sleep(50);
		m_MSComm.SetInBufferCount(0);

		SetTimer(ID_TIMER_WAIT,2000,NULL);//��������ʱ��

		StartFlag=1;

		for (int k = 0; k < 30; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					m_FreqData[k][i][j]=0;
					m_TempData[k][i][j]=0;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				WrongFlagCount[i][j]=0;
			}
		}

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 12; k++)
				{
					LastRecvTemp[i][j][k]=0;
					LastRecvPower[i][j][k]=0;
					LastAlarmStatus[i][j][k]=0;
				}
			}
		}
	}else
	{
		AfxMessageBox("���ȴ򿪶˿ڣ��ٽ��п��Ʋ�����");
	}
}


void CMainFrame::StopMem(void)
{
	if (PortOpenFlag)
	{
		while (1)
		{
			if (m_MSComm.GetInBufferCount()==0)
			{
				//KillTimer(ID_TIMER_LOOP);
				StopTimer();
				Sleep(400);
				SendCMD(StopCMD);
				Sleep(50);
				m_MSComm.SetInBufferCount(0);
				StartFlag=0;
				break;
			}
		}
	}else
	{
		AfxMessageBox("���ȴ򿪶˿ڣ��ٽ��п��Ʋ�����");
	}
}
